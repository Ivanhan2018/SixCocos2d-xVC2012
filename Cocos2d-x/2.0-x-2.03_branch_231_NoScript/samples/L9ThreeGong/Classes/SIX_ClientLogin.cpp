#include "SIX_ClientLogin.h"
#include "SIX_PlayerMgr.h"
#include "SIX_RoomMgr.h"
#include "SIX_ClientHall.h"
#include <SIX_GlobalMgr.h>

extern SIX_SceneLogin *pSceneLogin;
extern SIX_SceneHall *pSceneHall;

SIX_ClientLogin *SIX_ClientLogin::m_gClientLogin = 0;

SIX_ClientLogin::SIX_ClientLogin()
{
	m_ConnectionType = CONNECTION_LOGIN;
	m_bRoomListRequested = false;
}

SIX_ClientLogin::~SIX_ClientLogin()
{
}

void SIX_ClientLogin::SetConnectionType(ConnectionType ctType)
{
	m_ConnectionType = ctType;
}

ConnectionType SIX_ClientLogin::GetConnectionType()
{
	return m_ConnectionType;
}

void SIX_ClientLogin::Connect(bool bReconnected,int iReconnectDelay)
{
	m_gClientLogin = SIX_ClientLogin::GetInstance();
	m_gClientLogin->init((char*)(SIX_GlobalMgr::GetInstance()->GetConfig()->ip.c_str()),SIX_GlobalMgr::GetInstance()->GetConfig()->port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass(),bReconnected,iReconnectDelay);
	m_gClientLogin->start();
}

void SIX_ClientLogin::Disconnect()
{
	if (!m_gClientLogin)
		return;
	m_gClientLogin->stop();
}

void SIX_ClientLogin::HandlePacketRaw(int m_MainCode,int m_SubCode,unsigned char* m_Data,unsigned int m_DataLen)
{
	// ҵ����
	switch (m_MainCode)
	{
		// OnClose
	case -1:
		{
			switch (m_SubCode)
			{
				// ��ʼ�ǵ���Чֵ
			case CLOSE_TYPE_NO:
				{
					SIXLog("�ͻ�����Ч�ر�");
					break;
				}
				// �ͻ��������ر�
			case CLOSE_TYPE_CLIENT_CLOSE:
				{
					SIXLog("�ͻ��������ر�");
					this->setNeedExit(true);
					break;
				}
				// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�
			case CLOSE_TYPE_FLASH_CLOSE:
				{
					SIXLog("��������");
					// Ӧ�������UI��ʾ
					// Cool.Cat
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneLogin,"SIX_SceneLogin"))
						return;
					//pSceneLogin->ShowFlashBox(this,true);
					break;
				}
				// ����������رտͻ���
			case CLOSE_TYPE_SERVER_POWER_CLOSE:
				{
					SIXLog("����������ر�");
					//// Ӧ�������UI��ʾ
					//// Cool.Cat
					//if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
					//	return;
					//pSceneGate->ShowCloseBox(true);
					m_ConnectionType = CONNECTION_LOGIN;
					SIX_ClientLogin::GetInstance()->Disconnect();
					break;
				}
			}
			break;
		}
	case 0:
		{
			switch (m_SubCode)
			{
				// OnConnect
			case CONNECT_SUCCESSED:
				{
					SIXLog("���ӳɹ������ڵ�¼����[%s:%d][%s][%s]...",
						this->GetRoomInfo()->szIP,
						this->GetRoomInfo()->iPort,
						this->GetRoomInfo()->szName,
						this->GetRoomInfo()->szPassword
					);

					// �޸�����
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall"))
					{
						CMD_ModifyUserData UserData;
						UserData.lUserID= SIX_PlayerMgr::GetInstance()->getMyUserIdx();
						UserData.lSyslogoid = SIX_PlayerMgr::GetInstance()->getMyLogoID();
						memcpy(UserData.szNickName, SIX_PlayerMgr::GetInstance()->getMyNickName(), sizeof(UserData.szNickName));
						this->send_data(MAIN_MSG_LOGIN,SUB_CS_UPDATE_USER_DATA,&UserData,sizeof(UserData));
						return;
					}

					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneLogin,"SIX_SceneLogin"))
						return;

					bool isGuest = true;
					bool isRegister = true;
					// �û���¼���
					if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
					{
						// �ֶ���¼
						if (pSceneLogin->getLoginPanel()->getCheckStatus()!=BTN_REGISTER)
						{
							isRegister = false;
						}
						// �ֶ�ע��
						else
						{
							isGuest = false;
						}
					}

					// �ο͵�¼/ע��
					if (isRegister)
					{
						if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
							pSceneLogin->getLoginPanel()->showRegTips(/*��������ע����Ϣ ...*/XorStr<0x40,21,0x0D660E33>("\x95\xBC\x96\x99\x83\xAE\x81\xB4\x9F\xEB\xF8\xAA\x9C\x88\x81\xED\x70\x7F\x7C\x7D"+0x0D660E33).s);

						// ��ȡ�豸��info
						char info[32] = {0};
						memset(&info,0,sizeof(info));
						SIX_GlobalMgr::GetInstance()->GetSystemInfo()->getDeviceInfo(info);

						// ����md5=MD5(info)
						char md5[33] = {0};
						memset(&md5,0,sizeof(md5));
						ERROR_INFO err = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->HashByMD5(info,strlen(info),md5);
						if (err!=ERROR_NONE)
						{
							if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
								pSceneLogin->getLoginPanel()->showRegTips(/*�û�ע����Ϣ�쳣��*/XorStr<0x08,19,0x6B32FC6C>("\xDB\xCA\xB1\xAC\xDB\xAF\xBC\xEE\xC0\xD4\xDD\xB1\xC6\xF9\xA5\xB4\xBB\xB8"+0x6B32FC6C).s);
							return;
						}

						// ����CRC32(md5)
						unsigned crc32 = SIX_GlobalMgr::GetInstance()->GetFS()->GetMicroEncryptAndDecrypt()->CRC_Stream((unsigned char*)md5,strlen(md5));
						if (crc32==0)
						{
							if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
								pSceneLogin->getLoginPanel()->showRegTips(/*�û�ע����Ϣ�쳣����*/XorStr<0x98,21,0xA797DB86>("\x4B\x5A\x21\x3C\x4B\x3F\x2C\x7E\x70\x64\x6D\x01\x76\x49\x15\x04\x0B\x08\x09\x0A"+0xA797DB86).s);
							return;
						}

						SIXLog("info[%s].md5[%s].crc32[0x%08X]",info,md5,crc32);

						CMD_CS_UserRegister pData;
						memset(&pData,0,sizeof(pData));
#ifdef WIN32
						// PC
						pData.iPlatformNo = 2;
						// �ǳ�=Win_CRC32(MD5(�豸��))(Win_XXXXXXXX)
						sprintf_s(info,31,/*%08X*/XorStr<0x15,5,0xD348C9D4>("\x30\x26\x2F\x40"+0xD348C9D4).s,crc32);
						sprintf_s(pData.szName,/*WIN_%08X*/XorStr<0x97,9,0xE163B17A>("\xC0\xD1\xD7\xC5\xBE\xAC\xA5\xC6"+0xE163B17A).s,crc32);
						sprintf_s(pData.szNickName,/*WIN_%08X*/XorStr<0x97,9,0xE163B17A>("\xC0\xD1\xD7\xC5\xBE\xAC\xA5\xC6"+0xE163B17A).s,crc32);
#else
						// �ֻ�
						if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
						{
							pData.iPlatformNo = 1;
							snprintf(info,31,/*%08X*/XorStr<0x15,5,0xD348C9D4>("\x30\x26\x2F\x40"+0xD348C9D4).s,crc32);
							snprintf(pData.szName,sizeof(pData.szNickName)-1,/*AND_%08X*/XorStr<0xCD,9,0xBA16CBBE>("\x8C\x80\x8B\x8F\xF4\xE2\xEB\x8C"+0xBA16CBBE).s,crc32);
							snprintf(pData.szNickName,sizeof(pData.szNickName)-1,/*AND_%08X*/XorStr<0xCD,9,0xBA16CBBE>("\x8C\x80\x8B\x8F\xF4\xE2\xEB\x8C"+0xBA16CBBE).s,crc32);
						}
						// ��ҳ(Web�˿���)
						else
							pData.iPlatformNo = 3;
#endif
						// �οͿ��ٽ���
						if (isGuest)
							pData.iEnterMode = 1;
						// �ֶ�ע��
						else
							pData.iEnterMode = 0;
						// �豸��
						memcpy(pData.szMachineCode,info,strlen(info));
						// �û���
						memcpy(pData.szName,SIX_PlayerMgr::GetInstance()->getMyName(),strlen(SIX_PlayerMgr::GetInstance()->getMyName()));
						// ����
						memcpy(pData.szPwd,SIX_PlayerMgr::GetInstance()->getMyPass(),strlen(SIX_PlayerMgr::GetInstance()->getMyPass()));
						// �Ա�
						pData.iSex = 0;
						this->send_data(MAIN_MSG_LOGIN,SUB_CS_USER_REGISTER,&pData,sizeof(pData));
					}
					// ��¼
					else
					{
						CMD_CS_UserLogin pData;
						memcpy(pData.szIp,this->GetRoomInfo()->szIP,19);
						memcpy(pData.szName,this->GetRoomInfo()->szName,31);
						memcpy(pData.szPwd,this->GetRoomInfo()->szPassword,32);
						this->send_data(MAIN_MSG_LOGIN,SUB_CS_USER_LOGIN,&pData,sizeof(pData));
					}
					break;
				}
				// OnConnect
			case RECONNECT_SUCCESSED:
				{
					SIXLog("���������ɹ�...");
					pSceneLogin->ShowFlashBox(this,false);
					this->setReconnect(true);
					break;
				}
				// OnConnectFail
			case CONNECT_FAILED:
				{
					SIXLog("����ʧ��");
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneLogin,"SIX_SceneLogin"))
						return;
					if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
					{
						pSceneLogin->getLoginPanel()->showLoginTips(/*����������ʧ�ܣ������ԣ�*/XorStr<0xF8,25,0xFF483E1A>("\x4F\x07\x34\x0A\x3A\x0A\x3F\x53\xBD\xD2\xC8\xA4\xB4\xD9\xA5\xAB\xCF\xE2\xDC\xD3\xC6\xD9\xAD\xAE"+0xFF483E1A).s);
						pSceneLogin->getLoginPanel()->DoLockPanel(false);
					}
					else
					{
#ifdef WIN32
						CCMessageBox(/*����������ʧ�ܣ������ԣ�*/XorStr<0xF8,25,0xFF483E1A>("\x4F\x07\x34\x0A\x3A\x0A\x3F\x53\xBD\xD2\xC8\xA4\xB4\xD9\xA5\xAB\xCF\xE2\xDC\xD3\xC6\xD9\xAD\xAE"+0xFF483E1A).s,0);
#else
						CCMessageBox(SIX_Utility::GetInstance()->G2U(/*����������ʧ�ܣ������ԣ�*/XorStr<0xF8,25,0xFF483E1A>("\x4F\x07\x34\x0A\x3A\x0A\x3F\x53\xBD\xD2\xC8\xA4\xB4\xD9\xA5\xAB\xCF\xE2\xDC\xD3\xC6\xD9\xAD\xAE"+0xFF483E1A).s).c_str(),0);
#endif
					}
					break;
				}
				// OnCommError
			case COMM_ERROR:
				{
					SIXLog("����ͨѶ�쳣");
					break;
				}
				// OnSendFailed
			case SEND_ERROR:
				{
					SIXLog("����ʧ��");
					break;
				}
			default:
				{
					SIXLog("HandlePacketRaw.MainCode[%d].SubCode[%d].Unknown!",m_MainCode,m_SubCode);
					break;
				}
			}
			break;
		}
		// ��¼��Ϣ
	case MAIN_MSG_LOGIN:
		{
			HandlePacketLogin(m_SubCode,m_Data,m_DataLen);
			break;
		}
	default:
		{
			SIXLog("HandlePacketRaw.MainCode[%d].Unknown!",m_MainCode);
			break;
		}
	}
}

void SIX_ClientLogin::HandlePacketLogin(int subCode,unsigned char *pData,int pDataLen)
{
	switch (subCode)
	{
		// ע��
	case SUB_SC_USER_REGISTER_FINISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneLogin,"SIX_SceneLogin"))
				return;

			// ע��ɹ��Ļ��������յ���¼�ɹ�����Ϣ
			CMD_CS_UserRegisterRet *pck = (CMD_CS_UserRegisterRet*)pData;
			if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
			{
				switch (pck->iRet)
				{
				case 20:pSceneLogin->getLoginPanel()->showRegTips(/*�û����Ѵ��ڣ�*/XorStr<0x7F,15,0xE81EDC6F>("\xAC\x43\x3A\x25\x40\x7F\x57\x57\x33\x6E\x5D\x50\x28\x2D"+0xE81EDC6F).s);break;
				case 30:pSceneLogin->getLoginPanel()->showRegTips(/*�û��ǳ��Ѵ��ڣ�*/XorStr<0xFE,17,0x9C41460D>("\x2D\x3C\xBB\xA6\xE8\xC4\xB7\xC3\xD4\xD6\xBC\xEF\xDE\xD1\xAF\xAC"+0x9C41460D).s);break;
				case 40:pSceneLogin->getLoginPanel()->showRegTips(/*�û��豸�Ѵ��ڣ�*/XorStr<0x9F,17,0xCE7DE9A9>("\x4C\x63\x1A\x05\x6A\x4C\x14\x1E\x75\x79\x1D\x4C\x7F\x76\x0E\x0F"+0xCE7DE9A9).s);break;
				case 0:pSceneLogin->getLoginPanel()->showRegTips(/*ע��ɹ���*/XorStr<0x93,11,0x59F44FEC>("\x44\x36\x27\x77\x24\x51\x20\x3C\x38\x3D"+0x59F44FEC).s);break;
				default:pSceneLogin->getLoginPanel()->showRegTips(/*ע��ʱ�����쳣������ϵ�ͷ���*/XorStr<0x32,29,0xF3B2A3B5>("\xE5\x91\x86\xD4\xFC\x86\x8B\xCF\xF5\xED\xEE\xD1\x8D\x9C\xE3\xED\x85\xA8\x85\xEF\x89\xF2\xF7\x84\xFD\xB5\xEF\xEC"+0xF3B2A3B5).s);break;
				}

				// ע��ʧ��ʱ��������UI
				if (pck->iRet!=0)
				{
					pSceneLogin->getLoginPanel()->DoLockPanel(false);
				}
			}

			break;
		}
		// ��¼
	case SUB_SC_USER_LOGIN_SUC:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneLogin,"SIX_SceneLogin"))
				return;

			CMD_SC_UserLoginInfo *pck = (CMD_SC_UserLoginInfo*)pData;
			SIXLog("pck.iRet[%d]",pck->iRet);
			// �ɹ�
			if (pck->iRet==RET_LOGIN_OPERATE_SUCCEED)
			{
				SIX_PlayerMgr::GetInstance()->setMyUserIdx(pck->llUserID);
				SIX_PlayerMgr::GetInstance()->setMyNickName(pck->szNickName);
				SIX_PlayerMgr::GetInstance()->setMyChip(pck->llGold>0?pck->llGold:pck->llPoint);
				SIX_PlayerMgr::GetInstance()->setMyLogoID(pck->lSysLogoID);

				if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
				{
					// ע��ɹ����Զ���¼
					if (pSceneLogin->getLoginPanel()->getCheckStatus()==BTN_REGISTER)
					{
						pSceneLogin->getLoginPanel()->showRegTips(/*��¼�ɹ������ڻ�ȡ��Ϸ���� ...*/XorStr<0xCC,31,0xDF96926B>("\x79\x0A\x0C\x73\x63\x18\x6B\x75\x77\x79\x03\x2A\x0C\x03\x61\x2A\x14\x7C\x0D\x11\x2F\x56\x28\x1E\x5A\x38\xC6\xC9\xC6\xC7"+0xDF96926B).s);
					}
					// ������¼
					else
					{
						pSceneLogin->getLoginPanel()->showLoginTips(/*��¼�ɹ������ڻ�ȡ��Ϸ���� ...*/XorStr<0xCC,31,0xDF96926B>("\x79\x0A\x0C\x73\x63\x18\x6B\x75\x77\x79\x03\x2A\x0C\x03\x61\x2A\x14\x7C\x0D\x11\x2F\x56\x28\x1E\x5A\x38\xC6\xC9\xC6\xC7"+0xDF96926B).s);
					}
				}
			}
			// �û������� �� �������
			else if (pck->iRet==RET_USER_NOT_EXIST)
			{
				if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
				{
					pSceneLogin->getLoginPanel()->showLoginTips(/*�û������� �� �������*/XorStr<0x25,25,0xFC1B7FFA>("\xF6\xE5\x9C\x8F\x9B\x91\x9F\xCA\xF9\xF4\x0F\x8B\xC3\x12\xF0\xE8\xF7\xDD\x83\xD5\xF7\xC9\x98\x9D"+0xFC1B7FFA).s);
					pSceneLogin->getLoginPanel()->DoLockPanel(false);
				}
			}
			break;
		}
		// ������Ϸ�б�(������)
	case SUB_SC_GAME_LIST:
		{
			CMD_SC_GAME_LIST *pGameList = (CMD_SC_GAME_LIST *)pData;
			SIXLog("��Ϸ�б�[ID=%d,Type=%d,GameName=%s,ProgressName=%s]", pGameList->iID, pGameList->iGameType, pGameList->szGameName, pGameList->szProgressName);
			break;
		}
		// �����������б�
	case SUB_CSG_PLAZA_LIST:
		{
			CMD_PlazaServerList *pck = (CMD_PlazaServerList*)pData;
			if (!pck)
			{
				// �����������б�Ϊ�գ�
				if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
				{
					// ע��ɹ����Զ���¼
					if (pSceneLogin->getLoginPanel()->getCheckStatus()==BTN_REGISTER)
					{
						pSceneLogin->getLoginPanel()->showRegTips(/*��Ϸ����������ά���У����Ժ����� ...*/XorStr<0xD1,37,0x5FFB0730>("\x02\x1C\x1C\x63\x61\x25\x1B\x24\x6E\x24\x15\x2D\x1B\x29\x11\x4C\x5A\x46\x35\x34\x46\x4A\x20\x03\x20\x3E\x51\x1E\x3B\x36\x25\x24\xD1\xDC\xDD\xDA"+0x5FFB0730).s);
					}
					// ������¼
					else
					{
						pSceneLogin->getLoginPanel()->showLoginTips(/*��Ϸ����������ά���У����Ժ����� ...*/XorStr<0xD1,37,0x5FFB0730>("\x02\x1C\x1C\x63\x61\x25\x1B\x24\x6E\x24\x15\x2D\x1B\x29\x11\x4C\x5A\x46\x35\x34\x46\x4A\x20\x03\x20\x3E\x51\x1E\x3B\x36\x25\x24\xD1\xDC\xDD\xDA"+0x5FFB0730).s);
					}
					pSceneLogin->getLoginPanel()->DoLockPanel(false);
				}
				return;
			}

			SIXLog("��ȡ��������������Ϣ[%s:%d]",
				pck->szIp,
				pck->iPort);

			SIX_ClientHall::GetInstance()->AddServer(pck);
			break;
		}
		// �����б�
	case SUB_CSG_GAME_ROOM_LIST:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneLogin,"SIX_SceneLogin"))
				return;

			SIXLog("���շ����б�...");

			CMD_SC_RoomList *pck = (CMD_SC_RoomList*)pData;
			if (NULL==pck)
			{
				CCMessageBox(/*exit*/XorStr<0x91,5,0x868C75B9>("\xF4\xEA\xFA\xE0"+0x868C75B9).s,0);
				return;
			}
			
			SIXLog("�����б�.iGameID[%d].lParentId[%lld].iRoomId[%d].lGameType[%d].iRoomTeltComIp[%lld].iRoomUnicomIp[%lld].iRoomMobileIp[%lld].iRoomPort[%d].szRoomName[%s].bAutoSit[%d].iBasePoint[%d].lDoorsill[%d]",
				pck->iGameID,
				pck->lParentId,
				pck->iRoomId,
				pck->iRoomType,
				pck->lRoomTeltComIp,
				pck->lRoomUnicomIp,
				pck->lRoomMobileIp,
				pck->iRoomPort,
				SIX_Utility::GetInstance()->G2U(pck->szRoomName).c_str(),
				pck->bAutoSit,
				pck->iBasePoint,
				pck->iDoorsill);

			CMD_SC_RoomList *pRoomItem = new CMD_SC_RoomList();
			memcpy(pRoomItem, pck, sizeof(CMD_SC_RoomList));

			SIX_RoomMgr::GetInstance()->Add(pRoomItem);
			break;
		}
		// �����б����
	case SUB_SC_USER_LOGIN_FINISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneLogin,"SIX_SceneLogin"))
				return;
			SIXLog("�����б�������!");

			this->setRoomListRequested(true);
			
			// �û�ID��0��ʾ��¼�ɹ�
			if (SIX_PlayerMgr::GetInstance()->getMyUserIdx()>0)
			{
				if (pSceneLogin->getLoginPanel() && pSceneLogin->getLoginPanel()->IsShow())
				{
					// ע��ɹ����Զ���¼
					if (pSceneLogin->getLoginPanel()->getCheckStatus()==BTN_REGISTER)
						pSceneLogin->getLoginPanel()->showRegTips(/*��ȡ��Ϸ������ɣ�*/XorStr<0x1C,19,0x5033B985>("\xA7\xEC\xD6\xBE\xF3\xEF\xED\x94\xEE\xD8\x98\xFA\xE5\xC3\x99\xE2\x8F\x8C"+0x5033B985).s);
					// ������¼
					else
						pSceneLogin->getLoginPanel()->showLoginTips(/*��ȡ��Ϸ������ɣ�*/XorStr<0x1C,19,0x5033B985>("\xA7\xEC\xD6\xBE\xF3\xEF\xED\x94\xEE\xD8\x98\xFA\xE5\xC3\x99\xE2\x8F\x8C"+0x5033B985).s);
					pSceneLogin->getLoginPanel()->Show(false);
					pSceneLogin->getLoginPanel()->DoLockPanel(false);
				}
				// �οͿ��ٽ���
				else
				{
					pSceneLogin->DoChangeScene();
				}
			}
			break;
		}
	case SUB_CS_UPDATE_USER_DATA_SUC:
		{
			CMD_ModifyUserData * pModify = (CMD_ModifyUserData *)pData;
			if (0==pModify  ||  sizeof(CMD_ModifyUserData)!=pDataLen)
			{
#ifdef WIN32
				CCMessageBox(/*�޸�����ʧ�ܣ�*/XorStr<0x84,15,0x8B2F8E45>("\x54\x5B\x3E\x43\x5F\x43\x4B\x44\x46\x2A\x3E\x53\x33\x30"+0x8B2F8E45).s, 0);
#else
				CCMessageBox(SIX_Utility::GetInstance()->G2U(/*�޸�����ʧ�ܣ�*/XorStr<0x84,15,0x8B2F8E45>("\x54\x5B\x3E\x43\x5F\x43\x4B\x44\x46\x2A\x3E\x53\x33\x30"+0x8B2F8E45).s).c_str(), 0);
#endif
			}
			else
			{
				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall")  && 0!=pSceneHall)
				{
					SIX_PlayerMgr::GetInstance()->setMyNickName(pModify->szNickName);
					SIX_PlayerMgr::GetInstance()->setMyLogoID(pModify->lSyslogoid);
					pSceneHall->setNickName(pModify->szNickName);
					pSceneHall->setFaceLogo(pModify->lSyslogoid);
				}
				SIXLog("�޸����ϳɹ���");
			}
			break;
		}
	default:
		{
			SIXLog("δ�������Ϣ, subCode=%d", subCode);
			break;
		}
	}
}

void SIX_ClientLogin::ShowMsgBox(const char *fmt,...)
{
	SIX_MsgBox *pMsgBox = SIX_MsgBox::Create(0.0,0.0,ccc4(0,0,0,0),409.0,254.0,false,true);
	if (!pMsgBox)
		return;
	pMsgBox->InitMask(ccc4(0,0,0,128));
	pMsgBox->backgroundWithFile("tipbox.png");
	pMsgBox->buttonSubmitWithFileCell("return.png",3);
	pMsgBox->GetBtnSubmit()->setPosition(ccp(270,35));
	pMsgBox->setTextAttribute(20,80,369,140,"����",12);
	//pMsgBox->setRectDirty();

	char szBuf[1024] = {0};

	va_list ap;
	va_start(ap,fmt);
	vsnprintf(szBuf,1023,fmt,ap);
	va_end(ap);

	pMsgBox->setString(SIX_Utility::GetInstance()->G2U(szBuf).c_str());
	pMsgBox->Show();
}
#include "SIX_ClientLogin.h"

extern SIX_SceneGate *pSceneGate;

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

void SIX_ClientLogin::Connect()
{
	m_gClientLogin = SIX_ClientLogin::GetInstance();
	string ip=SIX_GlobalMgr::GetInstance()->GetConfig()->ip;
	unsigned int port=SIX_GlobalMgr::GetInstance()->GetConfig()->port;
	m_gClientLogin->init((char*)(ip.c_str()),port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass());
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
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
						return;
					pSceneGate->ShowFlashBox(this,true);
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

					if (CONNECTION_EXPLOIT == GetConnectionType())
					{
						this->send_data(MAIN_MSG_RANKING,SUB_CSG_GET_FEATS_RANKING);
					}
					else if(CONNECTION_MATCH == GetConnectionType())
					{
						this->send_data(MAIN_MSG_RANKING,SUB_CSG_GET_MATCH_RANKING);
					}
					else if (CONNECTION_MY_EXPLOIT == GetConnectionType())
					{
						CMD_CS_UPD_FEATS_RANKING_REWARD FeatsRankingReward;
						pSceneGate->getRanking()->GetMyRankingData(FeatsRankingReward);
						this->send_data(MAIN_MSG_RANKING,SUB_CS_UPD_USER_FEATS_RANKING, &FeatsRankingReward, sizeof(FeatsRankingReward));
					}
					else if (CONNECTION_MY_MATCH == GetConnectionType())
					{
						CMD_CS_UPD_MATCH_RANKING_REWARD MatchRankingReward;
						pSceneGate->getRanking()->GetMyRankingData(MatchRankingReward);
						this->send_data(MAIN_MSG_RANKING,SUB_CS_UPD_USER_MATCH_RANKING, &MatchRankingReward, sizeof(MatchRankingReward));
					}
					else
					{
						CMD_CS_UserLogin pData;
						memcpy(pData.szIp,this->GetRoomInfo()->szIP,19);
						memcpy(pData.szName,this->GetRoomInfo()->szName,31);
						memcpy(pData.szPwd,this->GetRoomInfo()->szPassword,32);
						pData.iGameID = 1;
						this->send_data(MAIN_MSG_LOGIN,SUB_CS_USER_LOGIN,&pData,sizeof(pData));
					}
					break;
				}
				// OnConnect
			case RECONNECT_SUCCESSED:
				{
					SIXLog("���������ɹ�...");
					pSceneGate->ShowFlashBox(this,false);
					this->setReconnect(true);

					if (CONNECTION_EXPLOIT == GetConnectionType())
					{
						this->send_data(MAIN_MSG_RANKING,SUB_CSG_GET_FEATS_RANKING);
					}
					else if(CONNECTION_MATCH == GetConnectionType())
					{
						this->send_data(MAIN_MSG_RANKING,SUB_CSG_GET_MATCH_RANKING);
					}
					else if (CONNECTION_MY_EXPLOIT == GetConnectionType())
					{
						CMD_CS_UPD_FEATS_RANKING_REWARD FeatsRankingReward;
						pSceneGate->getRanking()->GetMyRankingData(FeatsRankingReward);
						this->send_data(MAIN_MSG_RANKING,SUB_CS_UPD_USER_FEATS_RANKING);
					}
					else if (CONNECTION_MY_MATCH == GetConnectionType())
					{
						CMD_CS_UPD_MATCH_RANKING_REWARD MatchRankingReward;
						pSceneGate->getRanking()->GetMyRankingData(MatchRankingReward);
						this->send_data(MAIN_MSG_RANKING,SUB_CS_UPD_USER_MATCH_RANKING);
					}
					else
					{
						CMD_CS_UserLogin pData;
						memcpy(pData.szIp,this->GetRoomInfo()->szIP,19);
						memcpy(pData.szName,this->GetRoomInfo()->szName,31);
						memcpy(pData.szPwd,this->GetRoomInfo()->szPassword,32);
						pData.iGameID = 1;
						this->send_data(MAIN_MSG_LOGIN,SUB_CS_USER_LOGIN,&pData,sizeof(pData));
					}
					break;
				}
				// OnConnectFail
			case CONNECT_FAILED:
				{
					SIXLog("����ʧ��");
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
						return;
					if (pSceneGate->getLoginPanel() && pSceneGate->getLoginPanel()->IsShow())
					{
						pSceneGate->getLoginPanel()->showTips(SIX_Utility::GetInstance()->G2U(/*����ʧ�ܣ������ԣ�*/XorStr<0x6B,19,0x39E1A93C>("\xAA\xC0\xD0\xBD\xA5\xD7\xC1\xAE\xD0\xD8\xB2\x9D\xA1\xA0\xB3\xAE\xD8\xDD"+0x39E1A93C).s).c_str());
						pSceneGate->getLoginPanel()->DoLockPanel(false);
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
		// ���а���Ϣ
	case MAIN_MSG_RANKING:
		{
			HandlePacketRanking(m_SubCode,m_Data,m_DataLen);
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
		// ��¼
	case SUB_SC_USER_LOGIN_SUC:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
				return;

			CMD_SC_UserLoginInfo *pck = (CMD_SC_UserLoginInfo*)pData;
			// �ɹ�
			if (pck->iRet==RET_LOGIN_OPERATE_SUCCEED)
			{
				SIX_PlayerMgr::GetInstance()->setMyUserIdx(pck->llUserID);
				if (pSceneGate->getLoginPanel() && pSceneGate->getLoginPanel()->IsShow())
					pSceneGate->getLoginPanel()->showTips(SIX_Utility::GetInstance()->G2U(/*��¼�ɹ������ڻ�ȡ��Ϸ���� ...*/XorStr<0xCC,31,0xDF96926B>("\x79\x0A\x0C\x73\x63\x18\x6B\x75\x77\x79\x03\x2A\x0C\x03\x61\x2A\x14\x7C\x0D\x11\x2F\x56\x28\x1E\x5A\x38\xC6\xC9\xC6\xC7"+0xDF96926B).s).c_str());
			}
			// �û������� �� �������
			else if (pck->iRet==RET_USER_NOT_EXIST)
			{
				if (pSceneGate->getLoginPanel() && pSceneGate->getLoginPanel()->IsShow())
				{
					pSceneGate->getLoginPanel()->showTips(SIX_Utility::GetInstance()->G2U(/*�û������� �� �������*/XorStr<0x25,25,0xFC1B7FFA>("\xF6\xE5\x9C\x8F\x9B\x91\x9F\xCA\xF9\xF4\x0F\x8B\xC3\x12\xF0\xE8\xF7\xDD\x83\xD5\xF7\xC9\x98\x9D"+0xFC1B7FFA).s).c_str());
					pSceneGate->getLoginPanel()->DoLockPanel(false);
				}
			}
			break;
		}
		// �����б�
	case SUB_CSG_GAME_ROOM_LIST:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
				return;

			SIXLog("���շ����б�...");

			CMD_SC_RoomList *pck = (CMD_SC_RoomList*)pData;
			if (NULL==pck)
			{
				return;
			}

			//wstring name(SIX_Utility::GetInstance()->Utf8ToUnicode(pck->szRoomName).c_str());
			//string realName(SIX_Utility::GetInstance()->UnicodeToAnsi(name.c_str()).c_str());

			SIXLog("�����б�.iGameID[%d].lParentId[%lld].iRoomId[%d].lGameType[%lld].iRoomTeltComIp[%lld].iRoomUnicomIp[%lld].iRoomMobileIp[%lld].iRoomPort[%d].szRoomName[%s].bAutoSit[%d].iBasePoint[%d].lDoorsill[%lld]",
				pck->iGameID,
				pck->lParentId,
				pck->iRoomId,
				pck->lGameType,
				pck->lRoomTeltComIp,
				pck->lRoomUnicomIp,
				pck->lRoomMobileIp,
				pck->iRoomPort,
				SIX_Utility::GetInstance()->G2U(pck->szRoomName).c_str(),
				pck->bAutoSit,
				pck->iBasePoint,
				pck->lDoorsill);

			CMD_SC_RoomList *pRoomItem = new CMD_SC_RoomList();
			memcpy(pRoomItem, pck, sizeof(CMD_SC_RoomList));

			SIX_RoomMgr::GetInstance()->Add(pRoomItem);
			break;
		}
		// �����б����
	case SUB_SC_USER_LOGIN_FINISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
				return;
			SIXLog("�����б�������!");

			this->setRoomListRequested(true);
			
			// �û�ID��0��ʾ��¼�ɹ�
			if (SIX_PlayerMgr::GetInstance()->getMyUserIdx()>0)
			{
				if (pSceneGate->getLoginPanel() && pSceneGate->getLoginPanel()->IsShow())
				{
					pSceneGate->getLoginPanel()->showTips(SIX_Utility::GetInstance()->G2U(/*��ȡ��Ϸ������ɣ�*/XorStr<0x1C,19,0x5033B985>("\xA7\xEC\xD6\xBE\xF3\xEF\xED\x94\xEE\xD8\x98\xFA\xE5\xC3\x99\xE2\x8F\x8C"+0x5033B985).s).c_str());
					pSceneGate->getLoginPanel()->Show(false);
					pSceneGate->getLoginPanel()->DoLockPanel(false);
				}
			}
			break;
		}
	}
}

void SIX_ClientLogin::HandlePacketRanking(int subCode,unsigned char *pData,int pDataLen)
{
	if (NULL == pSceneGate->getRanking())
		return;

	switch (subCode)
	{
	case SUB_CSG_GET_FEATS_RANKING:	// ���������ع�ѫ������Ϣ
		{
			pSceneGate->getRanking()->SetExploitData(pData, pDataLen);
			break;
		}
	case SUB_SC_GET_FEATS_RANKING_FINISH:	// ���������ع�ѫ������Ϣ���
		{
			// ��ȡ��������
			pSceneGate->getRanking()->SetShowData();
			pSceneGate->getRanking()->SetLinkGetExploit();

			SIX_ClientLogin::GetInstance()->Disconnect();
			SIX_ClientLogin::GetInstance()->SetConnectionType(CONNECTION_LOGIN);
			break;
		}
	case SUB_CSG_GET_MATCH_RANKING:	// ���������ر���������Ϣ
		{
			pSceneGate->getRanking()->SetMatchData(pData, pDataLen);
			break;
		}
	case SUB_SC_GET_MATCH_RANKING_FINISH:	// ���������ر���������Ϣ���
		{
			pSceneGate->getRanking()->SetShowData();
			pSceneGate->getRanking()->SetLinkGetMatch();

			SIX_ClientLogin::GetInstance()->Disconnect();
			SIX_ClientLogin::GetInstance()->SetConnectionType(CONNECTION_LOGIN);
			break;
		}
	case SUB_SC_UPD_USER_FEATS_RANKING_SUC:	// �ͻ�����ȡ��ѫ���������ɹ�
		{
			ShowMsgBox("��ȡ��ѫ���������ɹ���");
			pSceneGate->getRanking()->SetLinkGetMyExpoit();
			break;
		}
	case SUB_SC_UPD_USER_FEATS_RANKING_ERR:	// �ͻ�����ȡ��ѫ��������ʧ��
		{
			CMD_SC_UPD_FEATS_RANKING_ERR *pFeatsRanking = (CMD_SC_UPD_FEATS_RANKING_ERR *)pData;
			switch (pFeatsRanking->iRet)
			{
			case RET_RANKING_NOT_CURRENT_USER: ShowMsgBox("������ȡ���˽�����"); break;
			case RET_RANKING_IS_GET: ShowMsgBox("�����Ѿ���ȡ���ˣ�"); break;
			case RET_RANKING_SEND_ID_NOT_EXIST: ShowMsgBox("����ID�����ڣ�"); break;
			default: ShowMsgBox("��ȡʧ�ܣ�δ֪ԭ��"); break;
			}
			pSceneGate->getRanking()->SetLinkGetMyExpoit();
			break;
		}
	case SUB_SC_UPD_USER_MATCH_RANKING_SUC:		// �ͻ�����ȡ�������������ɹ�
		{
			ShowMsgBox("��ȡ�������������ɹ���");
			pSceneGate->getRanking()->SetLinkGetMyMatch();
			break;
		}
	case SUB_SC_UPD_USER_MATCH_RANKING_ERR:		// �ͻ�����ȡ������������ʧ��
		{
			CMD_SC_UPD_MATCH_RANKING_ERR *pFeatsRanking = (CMD_SC_UPD_MATCH_RANKING_ERR *)pData;
			switch (pFeatsRanking->iRet)
			{
			case RET_RANKING_NOT_CURRENT_USER: ShowMsgBox("������ȡ���˽�����"); break;
			case RET_RANKING_IS_GET: ShowMsgBox("�����Ѿ���ȡ���ˣ�"); break;
			case RET_RANKING_SEND_ID_NOT_EXIST: ShowMsgBox("����ID�����ڣ�"); break;
			default: ShowMsgBox("��ȡʧ�ܣ�δ֪ԭ��"); break;
			}
			pSceneGate->getRanking()->SetLinkGetMyMatch();
			break;
		}
	default:
		{
			CCAssert(1, "δ�������Ϣ����");
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
	pMsgBox->buttonSubmitWithFileCell("Common/Button/return.png",3);
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
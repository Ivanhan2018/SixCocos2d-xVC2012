#include "SIX_ClientHall.h"
#include "SIX_PlayerMgr.h"
#include "SIX_RoomMgr.h"
#include <SIX_GlobalMgr.h>
#include "SIX_SceneHall.h"

extern SIX_SceneHall *pSceneHall;

SIX_ClientHall *SIX_ClientHall::m_gClientHall = 0;

SIX_ClientHall::SIX_ClientHall()
{
	m_nConnectServerIndex = 0;
}

SIX_ClientHall::~SIX_ClientHall()
{
	while (m_QueueData.size())
	{
		senddata *pSendData = m_QueueData.front();
		delete []pSendData->pData;
		delete pSendData;
		m_QueueData.pop();
	}

	m_vPlazaServer.clear();
}

void SIX_ClientHall::OnRelease()
{
	CC_SAFE_DELETE(m_gClientHall);
}

void SIX_ClientHall::SendData(int iMainCode, int iSubCode, BYTE* pData/*=NULL*/, int iDataLen/*=0*/)
{
	senddata *pSendData = new senddata;
	pSendData->nMainCode = iMainCode;
	pSendData->nSubCode = iSubCode;
	pSendData->nDataLen = iDataLen;
	if (0 < iDataLen)
	{
		pSendData->pData = new BYTE[iDataLen];
		memcpy(pSendData->pData, pData, iDataLen);
	}
	m_QueueData.push(pSendData);
}

void SIX_ClientHall::Connect(bool bReconnected,int iReconnectDelay)
{
	bool bIsEmpty = (m_nConnectServerIndex>=m_vPlazaServer.size()  ||  m_vPlazaServer.empty())  ?  true  :  false;
	m_gClientHall = SIX_ClientHall::GetInstance();
	m_gClientHall->init(bIsEmpty?"":m_vPlazaServer.at(m_nConnectServerIndex).szIp,bIsEmpty?0:m_vPlazaServer.at(m_nConnectServerIndex).iPort,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass(),bReconnected,iReconnectDelay);
	m_gClientHall->start();
}

void SIX_ClientHall::Disconnect()
{
	if (!m_gClientHall)
		return;
	m_gClientHall->stop();

	while (m_QueueData.size())
	{
		senddata *pSendData = m_QueueData.front();
		delete []pSendData->pData;
		delete pSendData;
		m_QueueData.pop();
	}
}

void SIX_ClientHall::AddServer(CMD_PlazaServerList *pServer)
{
	CMD_PlazaServerList server;
	memcpy(&server, pServer, sizeof(server));
	m_vPlazaServer.push_back(server);

	srand(SIX_Utility::GetInstance()->GetTickCount());
	m_nConnectServerIndex = rand()%m_vPlazaServer.size();
}

void SIX_ClientHall::ShowMsgBox(const char *fmt,...)
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

void SIX_ClientHall::HandlePacketRaw(int nMainCode,int nSubCode,unsigned char* pData,unsigned int unDataLen)
{
	// ҵ����
	switch (nMainCode)
	{
		// OnClose
	case -1:
		{
			switch (nSubCode)
			{
				// ��ʼ�ǵ���Чֵ
			case CLOSE_TYPE_NO:
				{
					SIXLog("����������-�ͻ�����Ч�ر�");
					break;
				}
				// �ͻ��������ر�
			case CLOSE_TYPE_CLIENT_CLOSE:
				{
					SIXLog("����������-�ͻ��������ر�");
					this->setNeedExit(true);
					break;
				}
				// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�
			case CLOSE_TYPE_FLASH_CLOSE:
				{
					SIXLog("����������-��������");
					// Ӧ�������UI��ʾ
					// Cool.Cat
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneLogin"))
						return;
					pSceneHall->ShowFlashBox(this,true);
					break;
				}
				// ����������رտͻ���
			case CLOSE_TYPE_SERVER_POWER_CLOSE:
				{
					SIXLog("����������-����������ر�");
					//// Ӧ�������UI��ʾ
					//// Cool.Cat
					//if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
					//	return;
					//pSceneGate->ShowCloseBox(true);
					//SIX_ClientHall::GetInstance()->Disconnect();
					break;
				}
			}
			break;
		}
	case 0:
		{
			switch (nSubCode)
			{
				// OnConnect
			case CONNECT_SUCCESSED:
				{
					SIXLog("�������������ӳɹ����������Ӵ���������[%s:%d]",
						this->GetRoomInfo()->szIP,
						this->GetRoomInfo()->iPort
						);

					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall, "SIX_SceneHall"))
						return;

					// ���ͻ����е���Ϣ
					while (!m_QueueData.empty())
					{
						senddata *pSendData = m_QueueData.front();
						if (NULL != pSendData)
						{
							send_data(pSendData->nMainCode,pSendData->nSubCode,pSendData->pData,pSendData->nDataLen);
							delete []pSendData->pData;
							delete pSendData;
							m_QueueData.pop();
						}
					}
					break;
				}
				// OnConnect
			case RECONNECT_SUCCESSED:
				{
					SIXLog("�������������������ɹ�...");
					break;
				}
				// OnConnectFail
			case CONNECT_FAILED:
				{
					SIXLog("��������������ʧ��");
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall"))
						return;
					if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndShop()  &&  0!=pSceneHall->GetPopWndShop()->GetPointCardWnd())
					{
						pSceneHall->GetPopWndShop()->GetPointCardWnd()->DoLockPanel(false);
						pSceneHall->GetPopWndShop()->GetPointCardWnd()->showTips(/*��������������ʧ�ܣ�*/XorStr<0x96,21,0x08F595F3>("\x22\x64\x54\x65\x2D\x65\x52\x6C\x58\x68\x61\x0D\x1F\x70\x6E\x02\x16\x7B\x0B\x08"+0x08F595F3).s);
					}

					break;
				}
				// OnCommError
			case COMM_ERROR:
				{
					SIXLog("����������-����ͨѶ�쳣");
					break;
				}
				// OnSendFailed
			case SEND_ERROR:
				{
					SIXLog("����������-����ʧ��");
					break;
				}
			default:
				{
					SIXLog("HandlePacketRaw.MainCode[%d].SubCode[%d].Unknown!",nMainCode,nSubCode);
					break;
				}
			}
			break;
		}
	case MAIN_MSG_TASK:		// ����
		{
			HandlePacketTask(nSubCode, pData, unDataLen);
			break;
		}
	case MAIN_MSG_ACTIVITY:		// �
		{
			HandlePacketActivity(nSubCode, pData, unDataLen);
			break;
		}
	case MAIN_MSG_PLAZA_RANKING:	// ���а�
		{
			HandlePacketTopList(nSubCode, pData, unDataLen);
			break;
		}
	case MAIN_MSG_SHOP:		// �̳�
		{
			HandlePacketShop(nSubCode, pData, unDataLen);
			break;
		}
	case MAIN_MSG_HALL:		// ��ʼ����
		{
			HandlePacketInitHall(nSubCode, pData, unDataLen);
			break;
		}
	default:
		{
			SIXLog("HandlePacketRaw.MainCode[%d].Unknown!",nMainCode);
			break;
		}
	}
}

void SIX_ClientHall::HandlePacketTask(int subCode,unsigned char *pData,int nDataLen)
{
	switch (subCode)
	{
	case SUB_CSG_TASK_LIST:	// ���������б�
		{
			if (sizeof(CMD_SC_TaskList) != nDataLen)
				return;

			CMD_SC_TaskList *pTaskList = (CMD_SC_TaskList *)pData;
			if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndTask())
				pSceneHall->GetPopWndTask()->SetData(pTaskList);
			break;
		}
	case SUB_CSG_TASK_LIST_COMPLETE:	// ���������б����
		{
			Disconnect();
			if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndTask())
				pSceneHall->GetPopWndTask()->SetReceiveDataComplete();
			break;
		}
	case SUB_SC_GET_NEXT_TASK:	// ��ȡ��һ������
		{
			if (sizeof(CMD_SC_GET_NEXT_TASK) != nDataLen)
				return;

			CMD_SC_GET_NEXT_TASK *pNextTask = (CMD_SC_GET_NEXT_TASK *)pData;
			if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndTask())
				pSceneHall->GetPopWndTask()->SetNextData(pNextTask);
			break;
		}
	case SUB_CSG_RECEIVE_REWARD:	// ��ȡ������
		{
			Disconnect();
			break;
		}
	}
}

void SIX_ClientHall::HandlePacketActivity(int subCode,unsigned char *pData,int nDataLen)
{
	switch (subCode)
	{
	default:
		{
			break;
		}
	}
}

void SIX_ClientHall::HandlePacketTopList(int subCode,unsigned char *pData,int nDataLen)
{
	switch (subCode)
	{
	default:
		{
			break;
		}
	}
}

void SIX_ClientHall::HandlePacketShop(int subCode,unsigned char *pData,int nDataLen)
{
	switch (subCode)
	{
	case SUB_CSG_POINTCARD:	// �㿨��ֵ
		{
			if (nDataLen != sizeof(int))
				return;
			if (0==pSceneHall  ||  0==pSceneHall->GetPopWndShop()  ||  0==pSceneHall->GetPopWndShop()->GetPointCardWnd())
				return;

			int *pResult = (int *)pData;
			pSceneHall->GetPopWndShop()->GetPointCardWnd()->DoLockPanel(false);
			if (0 == *pResult)
			{
				pSceneHall->GetPopWndShop()->GetPointCardWnd()->EmptyCardAndPW();
				pSceneHall->GetPopWndShop()->GetPointCardWnd()->showTips(/*��ֵ�ɹ���*/XorStr<0xAF,11,0x538310BC>("\x1C\x54\x67\x07\x00\x7D\x0C\x10\x14\x19"+0x538310BC).s);
			}
			else
			{
				pSceneHall->GetPopWndShop()->GetPointCardWnd()->showTips(/*��ֵʧ�ܣ����鿨�ţ����ܣ�*/XorStr<0xDE,29,0x14E159C7>("\x6D\x3B\x36\x54\x28\x44\x54\x39\x45\x4B\x2F\x02\x56\x07\x5E\x04\x51\x47\x4A\x34\x51\x5F\x4B\x5D\x35\x2B\x5B\x58"+0x14E159C7).s);
			}
		}
	default:
		{
			break;
		}
	}
}

void SIX_ClientHall::HandlePacketInitHall(int subCode,unsigned char *pData,int nDataLen)
{
	switch (subCode)
	{
	case SUB_CSG_INIT_HALL:
		{
			CMD_InitHall *pInitHall = (CMD_InitHall *)pData;
			if (nDataLen != sizeof(CMD_InitHall))
				return;

			pSceneHall->setReward(pInitHall->iCurCompleteTaskCount);
		}
	default:	break;
	}
}
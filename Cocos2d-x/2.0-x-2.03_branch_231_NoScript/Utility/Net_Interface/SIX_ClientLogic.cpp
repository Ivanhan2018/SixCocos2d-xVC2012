#include "SIX_ClientLogic.h"

// �����ں˿ͻ��˵� Lib
#if _WIN64	// 64λϵ��ϵͳ
	#if _DEBUG
		#pragma comment(lib, "./x64/ClientSkeleton64_d.lib") 
	#else
		#pragma comment(lib, "ClientSkeleton64.lib") 
	#endif
#elif _WIN32		// 32λϵ��ϵͳ
	#if _DEBUG	
		#pragma comment(lib, "ClientSkeleton32_d.lib") 	
	#else
		#pragma comment(lib, "ClientSkeleton32.lib") 
	#endif
#endif

SIX_ClientLogic::SIX_ClientLogic(void)
{
	m_NeedExit = false;
}

SIX_ClientLogic::~SIX_ClientLogic(void)
{
	SIXLog("~SIX_ClientLogic");
}

// ------------------------
void SIX_ClientLogic::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	//SIXLog("OnConnect.bIsReconnect[%d]",bIsReconnect);
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(0,0,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientLogic::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	//SIXLog("OnConnectFail.bIsReconnect[%d].iError[%d]",bIsReconnect,iError);
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(0,-1,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientLogic::OnCommError(char* pszError)
{
	//SIXLog("OnCommError.pszError[%s]",pszError);
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(0,-3,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientLogic::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	//SIXLog("OnSend.iMainCode[%d].iSubCode[%d].pData[0x%08X].iDataLen[%d]",iMainCode,iSubCode,pData,iDataLen);
}

void SIX_ClientLogic::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	//SIXLog("OnSendFailed.iMainCode[%d].iSubCode[%d].pData[0x%08X].iDataLen[%d]",iMainCode,iSubCode,pData,iDataLen);
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(0,-4,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientLogic::OnClose(bool bClientClose)
{
	//SIXLog("OnClose.bClientClose[%d]",bClientClose);
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(0,-2,0,0);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);
}

void SIX_ClientLogic::OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	MSG_INFO *pMsg = new MSG_INFO();
	pMsg->Creae(iMainCode,iSubCode,(char*)pData,iDataLen);
	SIX_Proxy::GetInstance()->PushEvent(pMsg);

	//switch(iMainCode)
	//{
	//case ROOM_MAIN:	// ������Ϣ
	//	{
	//		switch(iSubCode)
	//		{
	//		case ROOM_SUB_LOGIN_FAIL:
	//			{
	//				LOGIN_ROOM_FAIL* pReal = (LOGIN_ROOM_FAIL*)pData;
	//				SIXLog("�û���¼ʧ�ܣ������룺%d", pReal->iErrCode);
	//				return;
	//			}
	//		case ROOM_SUB_USER_INFO:	// �û���Ϣ
	//			{
	//				assert(sizeof(USER_INFO)==iDataLen);
	//				if(sizeof(USER_INFO)!=iDataLen)		// ����
	//					return;

	//				USER_INFO* pReal = (USER_INFO*)pData;
	//				SIXLog("�û���Ϣ,������%s���ǳƣ�%s", SIX_Utility::GetInstance()->G2U(pReal->szName).c_str(), SIX_Utility::GetInstance()->G2U(pReal->szNickname).c_str());

	//				return;
	//			}
	//		case ROOM_SUB_USER_LIST:	// �����û��б�
	//			{
	//				USER_INFO* pUserInfo = (USER_INFO*)pData;
	//				vecUserInfo.push_back(*pUserInfo);

	//				return;
	//			}
	//		case ROOM_SUB_USER_LIST_OVER:	// �����û��б����
	//			{
	//				SIXLog("���ڵ��û��б�");

	//				// ��ӡ�û��б�
	//				for(int i=0; i<vecUserInfo.size(); i++)
	//				{
	//					USER_INFO* pUserInfo = &vecUserInfo[i];
	//					SIXLog("������%s���ǳƣ�%s", SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(), SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str());
	//				}

	//				vecUserInfo.clear();  // �д˾����´νӵ��������û��б�ʱ�Ͳ��������

	//				return;
	//			}
	//		case ROOM_SUB_LEAVE_ROOM:	// �뷿�ɹ�
	//			{
	//				LEAVE_ROOM_RESULT* pReal = (LEAVE_ROOM_RESULT*)pData;
	//				if(0 == pReal->iErrCode)
	//				{
	//					SIXLog("%s �뷿�ɹ���", SIX_Utility::GetInstance()->G2U(pReal->userInfo.szName).c_str());
	//				}
	//				else
	//				{
	//					SIXLog("%s ���ڷ����ڣ�", SIX_Utility::GetInstance()->G2U(pReal->userInfo.szName).c_str());
	//					close(TRUE);	// �����رշ����
	//				}

	//				//close(TRUE);	// �����رշ����
	//			}
	//		}

	//		return;
	//	}
	//case ROOM_MAIN_DB:	// �����漰д���ݿ����Ϣ
	//	{
	//		switch(iSubCode)
	//		{
	//		case ROOM_SUB_WRITE_SCORE_RESULT:
	//			{
	//				WRITE_SCORE_RESULT* pReal = (WRITE_SCORE_RESULT*)pData;
	//				SIXLog("д�ֽ��������ֵ%d����ǰ��ֵ%d", pReal->iRes, pReal->lScore);
	//				break;
	//			}
	//		}

	//	}
	//case TABLE_MAIN:	//
	//	{
	//		switch(iSubCode)
	//		{
	//		case TABLE_SUB_SITDOWN:
	//			{
	//				SITDOWN* pReal = (SITDOWN*)pData;
	//				if(0==pReal->iRes)
	//				{
	//					SIXLog("���£�����%d , ����%d", pReal->iTableNo, pReal->iSeatNo);
	//				}
	//				else
	//				{
	//					SIXLog("����ʧ�ܣ�����%d , ����%d , ������ %d", pReal->iTableNo, pReal->iSeatNo, pReal->iRes);
	//				}

	//				return;
	//			}
	//		case TABLE_SUB_LEAVE_SEAT:
	//			{
	//				LEAVE_SEAT* pReal = (LEAVE_SEAT*)pData;
	//				if(0==pReal->iRes)
	//				{
	//					SIXLog("����");
	//				}
	//				else
	//				{
	//					SIXLog("����ʧ��");
	//				}

	//				return;
	//			}
	//		case TABLE_SUB_FIRE:
	//			{
	//				SHOT_FIRE_RESULT* pReal = (SHOT_FIRE_RESULT*)pData;
	//				if(0==pReal->iRes)
	//				{
	//					SIXLog("%s ����, ����%d ����%d �ӵ���%d", 
	//						SIX_Utility::GetInstance()->G2U(pReal->szName).c_str(), pReal->iTableNo, pReal->iSeatNo, pReal->iBulletNum);
	//				}
	//				else
	//				{
	//					SIXLog("����ʧ�ܣ������� %d", pReal->iRes);
	//				}
	//			}
	//		}
	//
	//	}
	//}
}

bool SIX_ClientLogic::IsNeedExit()
{
	return m_NeedExit;
}

int SIX_ClientLogic::stop()
{
	m_NeedExit = true;
	return ::IBaseTableClient::stop();
}

// ����
int SIX_ClientLogic::test()
{
	//MY_TEST sendData;
	//sendData.a = 1001;
	//sendData.b = 1002;

	//int iType = 1;
	//if(0 == iType)	// ������Ϣ����Ӧ�ò�
	//{
	//	send_data(ROOM_MAIN, ROOM_SUB_MY_TEST, (BYTE*)(&sendData), sizeof(sendData));
	//}
	//else if(1 == iType)	// ������Ϣ����Ӧ�ò�
	//{
	//	send_data(TABLE_MAIN, ROOM_SUB_MY_TEST, (BYTE*)(&sendData), sizeof(sendData));
	//}

	return 0;
}

// ����
int SIX_ClientLogic::fire()
{
	static int iTestNo = 0;

	SHOT_FIRE sendData;
	sendData.iTestNo = iTestNo++;
	send_data(TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&sendData), sizeof(sendData));

	return 0;
}

// ��ÿͻ���������Ϣ����Ҫ���ڵ��ԣ�Ŀ���ǵ���ʱ�Զ����ò�ͬ���û���
int SIX_ClientLogic::RandomUser(char* pszName)
{
	int iSeatNo = SIX_Utility::GetInstance()->RNDNUM(0,9);
	switch(iSeatNo)
	{
	case 0:sprintf(pszName, "����");break;
	case 1:sprintf(pszName, "����");break;
	case 2:sprintf(pszName, "��һ");break;
	case 3:sprintf(pszName, "���");break;
	case 4:sprintf(pszName, "����");break;
	case 5:sprintf(pszName, "����");break;
	case 6:sprintf(pszName, "����");break;
	case 7:sprintf(pszName, "���");break;
	case 8:sprintf(pszName, "Ǯ��");break;
	case 9:sprintf(pszName, "��ë");break;
	default:sprintf(pszName, "��ë");break;
	}

	return iSeatNo % 4;
}
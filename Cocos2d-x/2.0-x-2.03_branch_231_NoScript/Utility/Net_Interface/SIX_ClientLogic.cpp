#include "SIX_ClientLogic.h"

// 加载内核客户端的 Lib
#if _WIN64	// 64位系作系统
	#if _DEBUG
		#pragma comment(lib, "./x64/ClientSkeleton64_d.lib") 
	#else
		#pragma comment(lib, "ClientSkeleton64.lib") 
	#endif
#elif _WIN32		// 32位系作系统
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
	//case ROOM_MAIN:	// 房间消息
	//	{
	//		switch(iSubCode)
	//		{
	//		case ROOM_SUB_LOGIN_FAIL:
	//			{
	//				LOGIN_ROOM_FAIL* pReal = (LOGIN_ROOM_FAIL*)pData;
	//				SIXLog("用户登录失败，错误码：%d", pReal->iErrCode);
	//				return;
	//			}
	//		case ROOM_SUB_USER_INFO:	// 用户信息
	//			{
	//				assert(sizeof(USER_INFO)==iDataLen);
	//				if(sizeof(USER_INFO)!=iDataLen)		// 安检
	//					return;

	//				USER_INFO* pReal = (USER_INFO*)pData;
	//				SIXLog("用户信息,姓名：%s，昵称：%s", SIX_Utility::GetInstance()->G2U(pReal->szName).c_str(), SIX_Utility::GetInstance()->G2U(pReal->szNickname).c_str());

	//				return;
	//			}
	//		case ROOM_SUB_USER_LIST:	// 接收用户列表
	//			{
	//				USER_INFO* pUserInfo = (USER_INFO*)pData;
	//				vecUserInfo.push_back(*pUserInfo);

	//				return;
	//			}
	//		case ROOM_SUB_USER_LIST_OVER:	// 接收用户列表结束
	//			{
	//				SIXLog("房内的用户列表：");

	//				// 列印用户列表
	//				for(int i=0; i<vecUserInfo.size(); i++)
	//				{
	//					USER_INFO* pUserInfo = &vecUserInfo[i];
	//					SIXLog("姓名：%s，昵称：%s", SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(), SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str());
	//				}

	//				vecUserInfo.clear();  // 有此句则下次接到【批量用户列表】时就不会叠加啦

	//				return;
	//			}
	//		case ROOM_SUB_LEAVE_ROOM:	// 离房成功
	//			{
	//				LEAVE_ROOM_RESULT* pReal = (LEAVE_ROOM_RESULT*)pData;
	//				if(0 == pReal->iErrCode)
	//				{
	//					SIXLog("%s 离房成功！", SIX_Utility::GetInstance()->G2U(pReal->userInfo.szName).c_str());
	//				}
	//				else
	//				{
	//					SIXLog("%s 不在房间内！", SIX_Utility::GetInstance()->G2U(pReal->userInfo.szName).c_str());
	//					close(TRUE);	// 主动关闭服务端
	//				}

	//				//close(TRUE);	// 主动关闭服务端
	//			}
	//		}

	//		return;
	//	}
	//case ROOM_MAIN_DB:	// 房间涉及写数据库的消息
	//	{
	//		switch(iSubCode)
	//		{
	//		case ROOM_SUB_WRITE_SCORE_RESULT:
	//			{
	//				WRITE_SCORE_RESULT* pReal = (WRITE_SCORE_RESULT*)pData;
	//				SIXLog("写分结束，结果值%d，当前分值%d", pReal->iRes, pReal->lScore);
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
	//					SIXLog("坐下，桌号%d , 座号%d", pReal->iTableNo, pReal->iSeatNo);
	//				}
	//				else
	//				{
	//					SIXLog("坐下失败，桌号%d , 座号%d , 错误码 %d", pReal->iTableNo, pReal->iSeatNo, pReal->iRes);
	//				}

	//				return;
	//			}
	//		case TABLE_SUB_LEAVE_SEAT:
	//			{
	//				LEAVE_SEAT* pReal = (LEAVE_SEAT*)pData;
	//				if(0==pReal->iRes)
	//				{
	//					SIXLog("离座");
	//				}
	//				else
	//				{
	//					SIXLog("离座失败");
	//				}

	//				return;
	//			}
	//		case TABLE_SUB_FIRE:
	//			{
	//				SHOT_FIRE_RESULT* pReal = (SHOT_FIRE_RESULT*)pData;
	//				if(0==pReal->iRes)
	//				{
	//					SIXLog("%s 开火, 桌号%d 座号%d 子弹数%d", 
	//						SIX_Utility::GetInstance()->G2U(pReal->szName).c_str(), pReal->iTableNo, pReal->iSeatNo, pReal->iBulletNum);
	//				}
	//				else
	//				{
	//					SIXLog("开火失败，错误码 %d", pReal->iRes);
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

// 测试
int SIX_ClientLogic::test()
{
	//MY_TEST sendData;
	//sendData.a = 1001;
	//sendData.b = 1002;

	//int iType = 1;
	//if(0 == iType)	// 房间消息传入应用层
	//{
	//	send_data(ROOM_MAIN, ROOM_SUB_MY_TEST, (BYTE*)(&sendData), sizeof(sendData));
	//}
	//else if(1 == iType)	// 桌子消息传入应用层
	//{
	//	send_data(TABLE_MAIN, ROOM_SUB_MY_TEST, (BYTE*)(&sendData), sizeof(sendData));
	//}

	return 0;
}

// 开火
int SIX_ClientLogic::fire()
{
	static int iTestNo = 0;

	SHOT_FIRE sendData;
	sendData.iTestNo = iTestNo++;
	send_data(TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&sendData), sizeof(sendData));

	return 0;
}

// 获得客户端配置信息，主要用于调试，目的是调试时自动启用不同的用户名
int SIX_ClientLogic::RandomUser(char* pszName)
{
	int iSeatNo = SIX_Utility::GetInstance()->RNDNUM(0,9);
	switch(iSeatNo)
	{
	case 0:sprintf(pszName, "张三");break;
	case 1:sprintf(pszName, "李四");break;
	case 2:sprintf(pszName, "孙一");break;
	case 3:sprintf(pszName, "杨二");break;
	case 4:sprintf(pszName, "王五");break;
	case 5:sprintf(pszName, "赵六");break;
	case 6:sprintf(pszName, "孙七");break;
	case 7:sprintf(pszName, "金八");break;
	case 8:sprintf(pszName, "钱九");break;
	case 9:sprintf(pszName, "懂毛");break;
	default:sprintf(pszName, "懂毛");break;
	}

	return iSeatNo % 4;
}
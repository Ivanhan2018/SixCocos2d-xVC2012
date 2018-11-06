#include "./PublicHead.h"
#include "ClientLogic.h"
#include "Often.h"

// 加载内核客户端的 Lib
#if _WIN64	// 64位系作系统
	#if _DEBUG	
		#pragma comment(lib, "../../../PUBLIC_LIB/x64/ClientSkeleton64_d.lib") 
	#else
		#pragma comment(lib, "../../../PUBLIC_LIB/x64/ClientSkeleton64.lib") 
	#endif
#else		// 32位系作系统
	#if _DEBUG	
		#pragma comment(lib, "../../../PUBLIC_LIB/x32/ClientSkeleton32_d.lib") 	
	#else
		#pragma comment(lib, "../../../PUBLIC_LIB/x32/ClientSkeleton32.lib") 
	#endif
#endif

CClientLogic::CClientLogic(void)
{
	m_byGameState=E_GAME_FREE;
	m_IsAndroid=true;
}

CClientLogic::~CClientLogic(void)
{
}

void CClientLogic::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	COften::OutputInfo("CClientLogic::OnConnect");
	if(m_IsAndroid)
	{
		login_room();
	}
}

void CClientLogic::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
	COften::OutputInfo("CClientLogic::OnConnectFail");
}

void CClientLogic::OnCommError(char* pszError)
{
	COften::OutputInfo("CClientLogic::OnCommError");
}

void CClientLogic::OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	COften::OutputInfo("CClientLogic::OnSend");
}

void CClientLogic::OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	COften::OutputInfo("CClientLogic::OnSendFailed");
}

void CClientLogic::OnClose(CLOSE_TYPE iCloseType)
{
	COften::OutputInfo("CClientLogic::OnClose");
}

void CClientLogic::OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iMainCode)
	{
	case ROOM_MAIN:	// 房间消息
		{
			handle_room_msg(iSubCode, pData, iDataLen);

			break;
		}
	case ROOM_MGR_SERVER:	// 房管服务器相关
		{
			handle_write_db_msg(iSubCode, pData, iDataLen);
			break;
		}
	case TABLE_MAIN:	// 桌子消息
		{
			handle_table_msg(iSubCode, pData, iDataLen);
			break;
		}
	case MANAGER_MAIN:	// 管理员消息
		{
			handle_magager_msg(iSubCode, pData, iDataLen);
			break;
		}
	}
}

// 处理房间消息
void CClientLogic::handle_room_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case ROOM_SUB_LOGIN_FAIL:
		{
			LOGIN_ROOM_FAIL* pReal = (LOGIN_ROOM_FAIL*)pData;
			printf("用户登录失败，错误码：%d  \n", pReal->iErrCode);
			return;
		}
	case ROOM_SUB_LOGIN_SUCC:	// 房间内广播，登录房间成功
		{
			assert(sizeof(LOGIN_ROOM_SUCC)==iDataLen);
			if(sizeof(LOGIN_ROOM_SUCC)!=iDataLen)		// 安检
				return;

			LOGIN_ROOM_SUCC* pReal = (LOGIN_ROOM_SUCC*)pData;

			_snprintf(m_stLoginSucc.szIP, sizeof(m_stLoginSucc.szIP), "%s", pReal->szIP);
			m_stLoginSucc.iPort = pReal->iPort;
			m_stLoginSucc.bAlreadyInRoom = pReal->bAlreadyInRoom;
			printf("登录房间成功：iPort=%d  \n", pReal->iPort);

			USER_INFO_SIM *pUserInfo = &pReal->userInfo;
			printf("自己[%lld]：szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);
		    memcpy(&m_MeUserInfo,pUserInfo,sizeof(USER_INFO_SIM));

			if(m_IsAndroid)
			{
				sit_down(pUserInfo->lUserId%10,-1);
			}

			return;

		}
	case ROOM_SUB_RECOME:	// 断线重入
		{
			assert(sizeof(RECOME_AFTER_CUT)==iDataLen);
			if(sizeof(RECOME_AFTER_CUT)!=iDataLen)		// 安检
				return;

			RECOME_AFTER_CUT* pReal = (RECOME_AFTER_CUT*)pData;
			printf("%s 断线重入，桌号%d ， 座号%d \n", pReal->szName, pReal->iTableNo, pReal->iSeatNo);

			return;
		}
	case ROOM_SUB_USER_INFO:	// 登录者的信息
		{
			assert(sizeof(USER_INFO)==iDataLen);
			if(sizeof(USER_INFO)!=iDataLen)		// 安检
				return;

			USER_INFO* pReal = (USER_INFO*)pData;
			printf("用户信息, 姓名：%s，  昵称：%s, \n", pReal->szName, pReal->szNickname);

			return;
		}
	case ROOM_SUB_USER_LIST:	// 接收用户列表
		{
			//USER_INFO* pUserInfo = (USER_INFO*)pData;
			//vecUserInfo.push_back(*pUserInfo);
			printf("接收玩家列表...\n");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;

			printf("玩家[%lld]：szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);

			return;
		}
	case ROOM_SUB_USER_LIST_OVER:	// 接收用户列表结束
		{
			printf("房内的用户列表结束：  \n");

			//// 列印用户列表
			//for(int i=0; i<vecUserInfo.size(); i++)
			//{
			//	USER_INFO* pUserInfo = &vecUserInfo[i];
			//	printf("  姓名：%s，  昵称：%s, \n", pUserInfo->szName, pUserInfo->szNickname);
			//}

			//vecUserInfo.clear();  // 有此句则下次接到【批量用户列表】时就不会叠加啦

			return;
		}
	case ROOM_SUB_TABLE_LIST:
		{
			printf("接收桌子列表...\n");
			SERVER_ROOM_INFO_SIM *packet = (SERVER_ROOM_INFO_SIM*)pData;
			printf("房间ID[%d]：房间人数[%ld].房内桌子的数量[%d].每桌人数[%d].游戏类型[%d].倍频[%d]\n",packet->iRoomId,packet->iRoomPeopleCount,packet->iTables,packet->iSeatNum,packet->iRoomType,packet->iBasePoint);
			
			memcpy(&m_roomInfo,packet,sizeof(SERVER_ROOM_INFO_SIM));

			break;
		}
	case ROOM_SUB_LEAVE_ROOM:	// 离房成功
		{
			LEAVE_ROOM_RESULT* pReal = (LEAVE_ROOM_RESULT*)pData;
			int a=0;
			//if(0 == pReal->iErrCode)
			//{
			//	printf("%s 离房成功 \n", pReal->userInfo.szName);
			//}
			//else
			//{
			//	printf("%s 不在房间内！ \n", pReal->userInfo.szName);
			//	close(CLOSE_TYPE_CLIENT_CLOSE);	// 客户端主动关闭，主动关闭服务端
			//}
			if(m_IsAndroid)
			{

			}
		}
	}
}

// 处理房间涉及写数据库的消息
void CClientLogic::handle_write_db_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case RMS_SUB_WRITE_SCORE_RESULT:
		{
			WRITE_SCORE_RESULT* pReal = (WRITE_SCORE_RESULT*)pData;
			//if(0==pReal->iRes)
			//	printf("写分返回, 用户ID=%I64d 当前的分值=%I64d 积分=%I64d \n",pReal->lUserId, pReal->lGold, pReal->lPoint);
			//else
			//	printf("写分返回，错误码=%d \n", pReal->iRes);
			break;
		}
	}
}

// 处理桌子消息
void CClientLogic::handle_table_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case TABLE_SUB_SITDOWN:
		{
			SITDOWN* pReal = (SITDOWN*)pData;
			if(0==pReal->iRes)
			{
				printf("用户ID%I64d 坐下，桌号%d , 座号%d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo);
				if(m_IsAndroid && m_MeUserInfo.lUserId==pReal->lUserId)
				{
					raise_hand();
				}
			}
			else
				printf("用户ID%I64d 坐下失败，桌号%d , 座号%d , 错误码 %d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo, pReal->iRes);

			break;
		}
	case TABLE_SUB_LEAVE_SEAT:
		{
			LEAVE_SEAT* pReal = (LEAVE_SEAT*)pData;
			if(0==pReal->iRes)
			{
				printf("第%d桌, 第%d座 ，已经离座 \n", pReal->iTableNo, pReal->iSeatNo);
				if(m_IsAndroid && m_MeUserInfo.lUserId==pReal->lUserId)
				{
					sit_down(pReal->iTableNo, pReal->iSeatNo);
				}
			}
			else
				printf("离座失败，可能早已不在此座位啦 \n");

			break;
		}
	case TABLE_SUB_WRITE_SCORE_RET:
		{
			WRITE_SCORE_RESULT* pReal = (WRITE_SCORE_RESULT*)pData;
			//if(0==pReal->iRes)
			//	printf("写分返回, 用户ID=%I64d 当前的分值=%I64d 积分=%I64d \n",pReal->lUserId, pReal->lGold, pReal->lPoint);
			//else
			//	printf("写分返回，错误码=%d \n", pReal->iRes);

			break;
		}
	case TABLE_SUB_RAISE_HAND://用户举手
		{
			RAISE_HAND* pReal = (RAISE_HAND*)pData;
			if(0==pReal->iRes)
			{
				printf("用户ID%lld 举手\n", pReal->lUserId);
			}
			else
			{
				printf("用户ID%I64d 举手失败, 错误码 %d \n", pReal->lUserId, pReal->iRes);
			}

			break;
		}
	case RSP_CALL_BANKER_NOTIFY:		//可以抢庄
		{
			Rsp_CallBankerNotify* pReal = (Rsp_CallBankerNotify*)pData;
			printf("可以抢庄了 iServerSecs=%d \n",pReal->iServerSecs);
			m_byGameState=E_GAME_CALL_BANKER;

			break;
		}
	case RSP_CALL_BANKER_RESULT://抢庄结果
		{
			Rsp_BankerC3Info* pReal = (Rsp_BankerC3Info*)pData;
			printf("可以下注了 wBankerUser=%d C3=%I64d C2=%I64d C1=%I64d \n",pReal->wBankerUser,pReal->C3,pReal->C2,pReal->C1);
			m_byGameState=E_GAME_CALL_SCORE;

			break;
		}
	case RSP_USER_CHIPIN:		//用户下注
		{
			Req_UserChipin* pReal = (Req_UserChipin*)pData;
			printf("用户下注返回 用户ID=%I64d 座位号=%d 下注额=%I64d \n",pReal->llUserID,pReal->iSeatNo,pReal->lScore);

			break;
		}
	case RSP_SEND_CARD_LIST://发牌
		{
			Rsp_SendCard_List* pReal = (Rsp_SendCard_List*)pData;
			for(int i=0;i<pReal->nCount;i++)
			{
				Rsp_SendCard *pSendCard=&pReal->m_SendCards[i];
				printf("扑克数据=(%d,%d,%d) 用户ID=%I64d 座位号=%d \n",(int)pSendCard->cbUserCardData[0],(int)pSendCard->cbUserCardData[1],(int)pSendCard->cbUserCardData[2],pSendCard->llUserID,pSendCard->iSeatNo);
			}
			m_byGameState=E_GAME_SHOW_CARD;

			break;
		}
	case RSP_GAME_END_LIST://一局游戏结束
		{
			Rsp_GameEnd_List* pReal = (Rsp_GameEnd_List*)pData;
			for(int i=0;i<pReal->nCount;i++)
			{
				Rsp_GameEnd *pGameEnd=&pReal->m_GameEnds[i];//&(*pReal)[i];
				printf("一局游戏结束 用户ID=%I64d 座位号=%d 游戏税收=%I64d 筹码增量=%I64d 牌型=%d 点数=%d \n",pGameEnd->llUserID,pGameEnd->iSeatNo,pGameEnd->lGameTax,pGameEnd->lGameScore,(int)pGameEnd->CardType,(int)pGameEnd->CardPoint);
			}
			m_byGameState=E_GAME_FREE;
			if(m_IsAndroid)
			{
				raise_hand();
			}

			break;
		}

	}
}

// 处理管理员消息
void CClientLogic::handle_magager_msg(int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case MANAGER_SUB_POWER_ERR:	// 无此管理权限
		{
			MANAGER_POWER_ERR* pReal = (MANAGER_POWER_ERR*)pData;
			printf("管理员施权失败，你并无 %d 权限 \n", pReal->iWantPower);
			break;
		}
	case MANAGER_SUB_TICK_ONE_LEAVE_SEAT:	// 踢一个玩家离座
		{
			TICK_ONE_LEAVE_SEAT* pReal = (TICK_ONE_LEAVE_SEAT*)pData;
			if(0==pReal->iRes)
				printf("踢 桌号%d 座号%d 离座成功 \n", pReal->iTableNo, pReal->iSeatNo);
			else
				printf("踢 桌号%d 座号%d 离座失败，错误码 %d \n", pReal->iTableNo, pReal->iSeatNo, pReal->iRes);

			break;
		}
	case MANAGER_SUB_TICK_TABLE_LEAVE_SEAT:	// 踢一桌玩家离座
		{
			TICK_TABLE_LEAVE_SEAT* pReal = (TICK_TABLE_LEAVE_SEAT*)pData;

			if(0==pReal->iRes)
				printf("踢 桌号%d 全桌离座成功 \n", pReal->iTableNo);
			else
				printf("踢 桌号%d 全桌离座失败，错误码 %d \n", pReal->iTableNo, pReal->iRes);

			break;
		}
	case MANAGER_SUB_TICK_ALL_LEAVE_SEAT:	// 踢所有在座的玩家离座
		{
			TICK_ALL_LEAVE_SEAT* pReal = (TICK_ALL_LEAVE_SEAT*)pData;

			if(0==pReal->iRes)
				printf("踢所有在座的玩家离座成功 \n");
			else
				printf("踢所有在座的玩家离座失败，错误码 %d \n", pReal->iRes);

			break;
		}
	case MANAGER_SUB_TICK_USER_OUT_ROOM:	// 踢玩家离房
		{
			TICK_USER_OUT_ROOM* pReal = (TICK_USER_OUT_ROOM*)pData;

			if(0==pReal->iRes)
			{
				switch(pReal->iTickMode)
				{
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE_SEAT:	// 按桌号、座号踢
					{
						printf("%s 【桌号%d 座号%d】 被管理员踢出房间 \n", 
									pReal->szName, pReal->iTableNo, pReal->iSeatNo);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_NAME:	// 按名字踢
					{
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE:	// 按桌号踢，踢一整桌人离房
					{
						printf("第%d桌全桌人被管理员踢出房间 \n", 
								pReal->iTableNo);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_ALL:	// 踢所有的人离房
					{
						printf("所有的人被管理员踢出房间 \n");
						break;
					}
				}

				close(CLOSE_TYPE_CLIENT_CLOSE);	// 断开服务器，客户端主动关闭
				printf_s("其实这里也可以结束进程啦，按 X 键结束进程...... \n ");	// 其实这里也可以结束进程啦，待做

			}
			else
			{
				switch(pReal->iTickMode)
				{
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE_SEAT:	// 按桌号、座号踢
					{
						printf("踢 %s 【桌号%d 座号%d】 离房失败！错误码%d \n", 
								pReal->szName, pReal->iTableNo, pReal->iSeatNo, pReal->iRes);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_NAME:	// 按名字踢
					{
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_TABLE:	// 按桌号踢，踢一整桌人离房
					{
						printf("踢 桌号%d 离房失败！错误码%d \n", 
								pReal->iTableNo, pReal->iRes);
						break;
					}
				case TICK_USER_OUT_ROOM::TICK_BY_ALL:	// 踢所有的人离房
					{
						printf("踢所有的人离房失败！错误码%d \n", pReal->iRes);
						break;
					}
				}
			}

			break;
		}
	}
}


int CClientLogic::ConnectRoom(string str[5])
{
	int iRes = 0;

	// 桌子的框架参数，构造函数里有默认值
	CLIENT_FRAME_PARAM frameParam;	
	frameParam.iSendHeartbeatTime = 30*1000;

	// 客户端的房间信息，应该从命令行传入的或者是管道从大厅程序中传入的，还未做???
	CLIENT_ROOM_INFO clientRoomInfo;


	_snprintf(clientRoomInfo.szIP, sizeof(clientRoomInfo.szIP)-1,str[3].c_str());		// 本地房间IP


	clientRoomInfo.iPort=atoi(str[4].c_str());												// 房间端口

	//_snprintf(clientRoomInfo.szName, sizeof(clientRoomInfo.szName)-1, szName);		// 用户名
	strcpy(clientRoomInfo.szName,str[1].c_str());
	_snprintf(clientRoomInfo.szPassword, sizeof(clientRoomInfo.szPassword)-1,str[2].c_str());	// 密码

	setUserID(atoi(str[0].c_str()));

	iRes = init(clientRoomInfo, frameParam);
	iRes = start();
	return iRes;
}
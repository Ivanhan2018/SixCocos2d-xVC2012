#include "SIX_ClientRoom.h"
#include "SIX_MatchEnd.h"

extern SIX_SceneGate *pSceneGate;
extern SIX_SceneGame *pSceneGame;

SIX_ClientRoom *SIX_ClientRoom::m_gClientRoom = 0;

SIX_ClientRoom::SIX_ClientRoom()
{
	m_tRaiseHandTime=0;
	m_tClientServerTimeInterval=0;
	memset(&m_FishListInfos[0],0,sizeof(m_FishListInfos));
}

SIX_ClientRoom::~SIX_ClientRoom()
{
}

void SIX_ClientRoom::Connect(const char *addr,int port)
{
	m_gClientRoom = SIX_ClientRoom::GetInstance();
#ifdef LOCAL_SERVER
	m_gClientRoom->init("127.0.0.1",port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass());
#else
	m_gClientRoom->init((char*)addr,port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass());
#endif
	m_gClientRoom->start();
}

void SIX_ClientRoom::Disconnect()
{
	SIX_PlayerMgr::GetInstance()->Destory();

	if (!m_gClientRoom)
		return;
	m_gClientRoom->stop();
}

void SIX_ClientRoom::HandlePacketRaw(int m_MainCode,int m_SubCode,unsigned char* m_Data,unsigned int m_DataLen)
{
	// 业务处理
	switch (m_MainCode)
	{
		// OnClose
	case -1:
		{
			switch (m_SubCode)
			{
				// 初始是的无效值
			case CLOSE_TYPE_NO:
				{
					SIXLog("客户端无效关闭");
					break;
				}
				// 客户端主动关闭
			case CLOSE_TYPE_CLIENT_CLOSE:
				{
					SIXLog("客户端主动关闭");
					this->setNeedExit(true);
					// 如果是长时间未发射子弹导致的断开，需要切换回关卡场景
					// 这里要做修改...
					// Cool.Cat
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						// 切换到关卡场景
						SIX_Proxy::GetInstance()->SetChangeScene(true);
					}
					break;
				}
				// 闪断，例如手工禁用【本地连接】的方式模拟路由信号不稳定
			case CLOSE_TYPE_FLASH_CLOSE:
				{
					SIXLog("网络闪断");
					// 应给与界面UI提示
					// Cool.Cat
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
					{
						pSceneGate->ShowFlashBox(this,true);
						break;
					}
					else if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						pSceneGame->ShowFlashBox(this,true);
						break;
					}
					break;
				}
				// 服务端主动关闭客户端
			case CLOSE_TYPE_SERVER_POWER_CLOSE:
				{
					SIXLog("服务端主动关闭");
					// 应给与界面UI提示
					// Cool.Cat
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						this->setNeedExit(true);
						// 切换到关卡场景，比赛是由服务端主动关闭客户端，所以要排除
						if (3 != PlayerTreasureInfo::Instance().m_lGameType)
							SIX_Proxy::GetInstance()->SetChangeScene(true);
					}
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
					SIXLog("连接成功，正在登录房间[%s:%d][%s][%s]...",
						this->GetRoomInfo()->szIP,
						this->GetRoomInfo()->iPort,
						this->GetRoomInfo()->szName,
						this->GetRoomInfo()->szPassword
					);
					this->login_room();
					break;
				}
				// OnConnect
			case RECONNECT_SUCCESSED:
				{
					SIXLog("断线重连成功...");
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
					{
						pSceneGate->ShowFlashBox(this,false);
					}
					else if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						pSceneGame->ShowFlashBox(this,false);
					}
					this->setReconnect(true);
					this->login_room();
					//// 请求桌子列表
					//this->query_table_list();
					//// 请求用户列表
					//this->query_user_list();
					break;
				}
				// OnConnectFail
			case CONNECT_FAILED:
				{
					SIXLog("连接失败");
					break;
				}
				// OnCommError
			case COMM_ERROR:
				{
					SIXLog("网络通讯异常");
					break;
				}
				// OnSendFailed
			case SEND_ERROR:
				{
					SIXLog("发送失败");
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
		// 房间消息
	case ROOM_MAIN:
		{
			HandlePacketRoom(m_SubCode,m_Data,m_DataLen);
			break;
		}
		// 桌子消息
	case TABLE_MAIN:
		{
			HandlePacketTable(m_SubCode,m_Data,m_DataLen);
			break;
		}
		// 比赛消息
	case MATCH_MAIN:
		{
			HandlePacketMatch(m_SubCode,m_Data,m_DataLen);
			break;
		}
	default:
		{
			SIXLog("HandlePacketRaw.MainCode[%d].Unknown!",m_MainCode);
			break;
		}
	}

	this->SendNetGapTime();
}

void SIX_ClientRoom::HandlePacketRoom(int subCode,unsigned char *pData,int pDataLen)
{
	switch (subCode)
	{
	case ROOM_SUB_LOGIN_FAIL:
		{
			LOGIN_ROOM_FAIL *packet = (LOGIN_ROOM_FAIL*)pData;
			SIXLog("用户登陆失败.iErrCode[%d]",packet->iErrCode);
			
			ShowMsgBox("用户登陆失败.iErrCode[%d]",packet->iErrCode);
			break;
		}
	case ROOM_SUB_RECOME:
		{
			RECOME_AFTER_CUT *recome = (RECOME_AFTER_CUT*)pData;
			SIXLog("[%s]断线重连进入.iTableNo[%d].iSeatNo[%d]",recome->szName,recome->iTableNo,recome->iSeatNo);
			break;
		}
	case ROOM_SUB_LOGIN_SUCC:
		{
			LOGIN_ROOM_SUCC* pReal = (LOGIN_ROOM_SUCC*)pData;

			_snprintf(this->GetLoginInfo().szIP, sizeof(this->GetLoginInfo().szIP), "%s", pReal->szIP);
			this->GetLoginInfo().iPort = pReal->iPort;
			this->GetLoginInfo().bAlreadyInRoom = pReal->bAlreadyInRoom;

			SIXLog("登录成功...")
			LOGIN_ROOM_SUCC *packet = (LOGIN_ROOM_SUCC*)pData;
			USER_INFO_SIM pUserInfo = packet->userInfo;
			SIXLog("自己[%lld]：szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]",
				pUserInfo.lUserId,
				SIX_Utility::GetInstance()->G2U(pUserInfo.szName).c_str(),
				SIX_Utility::GetInstance()->G2U(pUserInfo.szNickname).c_str(),
				pUserInfo.iTableNo,
				pUserInfo.iSeatNo,
				pUserInfo.lGoldLogin,
				pUserInfo.stUserState);

			//g_pShipMgr->mMyUserID = pUserInfo.lUserId;
			//g_pShipMgr->mPlayerList.clear();

			PLAYER_LIST *pPlayer = new PLAYER_LIST();
			pPlayer->iTableId = pUserInfo.iTableNo;
			pPlayer->SeatId = pUserInfo.iSeatNo;
			pPlayer->lGoldLogin = pUserInfo.lGoldLogin;
			pPlayer->lPointLogin = pUserInfo.lPointLogin;
			pPlayer->UserIdx = pUserInfo.lUserId;
			memcpy(pPlayer->szName, pUserInfo.szName, sizeof(pPlayer->szName));
			memcpy(pPlayer->szNickname, pUserInfo.szNickname, sizeof(pPlayer->szNickname));
			if (!SIX_PlayerMgr::GetInstance()->Add(pPlayer->UserIdx,pPlayer))
			{
				//// 有可能客户端是网络闪断后重新连接上，所以这里可能会添加失败，应该不做任何处理
				//// Cool.Cat
				//CCAssert(0,"AddSelfPlayer.Error!");
				//return;
			}

			SIX_PlayerMgr::GetInstance()->setMyUserIdx(pPlayer->UserIdx);

			// 要检查是否在房间场景
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				// UI提示
				pSceneGate->getRoomList()->ShowTableLoading(false);
#ifdef WIN32
				CCString *title = CCString::createWithFormat("%s - [%d.%d.%d.%04d] - %s[%s][%lld]",PROJECT_NAME,VER_MAIN,VER_CHILD,VER_STAGE,VER_BUILD,pUserInfo.szName,pUserInfo.szNickname,pUserInfo.lUserId);
				CCEGLView::sharedOpenGLView()->setWindowTitle(title->getCString());
#endif
				//ShowMsgBox("登录成功！\n+++ 你的个人数据 +++\n用户ID：%lld\n用户名：%s\n昵　称：%s",pUserInfo.lUserId,pUserInfo.szName,pUserInfo.szNickname);
			}
			break;
		}
	case ROOM_SUB_TABLE_LIST:
		{
			SIXLog("接收桌子列表...");
			SERVER_ROOM_INFO_SIM *packet = (SERVER_ROOM_INFO_SIM*)pData;
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				// 如果进入的房间不是自动入座的
				if (!pSceneGate->getRoomList()->getAutoSit())
					pSceneGate->getRoomList()->RefreshTableList(packet->iRoomPeopleCount,packet->iTables,packet->iSeatNum);
			}
			//add by Ivan_han 20130716
			PlayerTreasureInfo::Instance().m_lGameType=packet->lGameType;
			PlayerTreasureInfo::Instance().m_iBasePoint=packet->iBasePoint;
			break;
		}
	/*case ROOM_SUB_TABLE_LIST_OVER:
		{
			SIXLog("接收桌子列表完成...");
			break;
		}*/
	case ROOM_SUB_USER_LIST:
		{
			SIXLog("接收玩家列表...");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;

			//add by Ivan_han 20130904
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				if(pSceneGate->getConsoleGM())
				{
					pSceneGate->getConsoleGM()->ON_ROOM_SUB_USER_LIST(pUserInfo->lUserId,SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(),SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str(),pUserInfo->stUserState,pUserInfo->iTableNo,pUserInfo->iSeatNo,pUserInfo->lGoldLogin,pUserInfo->lPointLogin);
				}
			}

			// 用户已经存在
			if (SIX_PlayerMgr::GetInstance()->Get(pUserInfo->lUserId))
			{
				if (SIX_PlayerMgr::GetInstance()->getMyUserIdx()==pUserInfo->lUserId)
				{
					SIX_PlayerMgr::GetInstance()->setMyTableIdx(pUserInfo->iTableNo);
					SIX_PlayerMgr::GetInstance()->setMySeatIdx(pUserInfo->iSeatNo);
				}
				return;
			}

			SIXLog("玩家[%lld]：szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]",
				pUserInfo->lUserId,
				SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(),
				SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str(),
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);

				PLAYER_LIST * pPlayerList = new PLAYER_LIST();
				pPlayerList->iTableId = pUserInfo->iTableNo;
				pPlayerList->SeatId = pUserInfo->iSeatNo;
				pPlayerList->UserIdx = pUserInfo->lUserId;
				//add by Ivan_han 20130713
				pPlayerList->lGoldLogin = pUserInfo->lGoldLogin;
				pPlayerList->lPointLogin = pUserInfo->lPointLogin;
				memcpy(pPlayerList->szName, pUserInfo->szName, sizeof(pPlayerList->szName));
				memcpy(pPlayerList->szNickname, pUserInfo->szNickname, sizeof(pPlayerList->szNickname));

				//g_pShipMgr->mPlayerList.push_back(pPlayerList);
				if (!SIX_PlayerMgr::GetInstance()->Add(pPlayerList->UserIdx,pPlayerList))
				{
					CCAssert(0,"AddPlayer.Error!");
					return;
				}

			// -- 玩家已经坐下的，绘制头像
			if (pUserInfo->lUserId!=INVALID_USER_ID && pUserInfo->iTableNo!=INVAL_TABLE_NO && pUserInfo->iSeatNo!=INVAL_SEAT_NO)
			{
				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
				{
					// 如果进入的房间不是自动入座的
					if (!pSceneGate->getRoomList()->getAutoSit())
						pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(pUserInfo->lUserId,pUserInfo->iTableNo,pUserInfo->iSeatNo,true);
				}
			}
			break;
		}
		
	case ROOM_SUB_USER_LIST_OVER:
		{
			SIXLog("接收玩家列表完成...");
			// 要判断当前场景
			// Cool.Cat
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
			{
				pSceneGate->getMatchList()->AutoSqueue();
				pSceneGate->getMatchList()->setLoginRoomSuccess( true );

				// 如果进入的房间是自动入座的
				if (pSceneGate->getRoomList()->getAutoSit())
				{
					// 绘制快速开始按钮
					pSceneGate->getRoomList()->ShowQucikStart();
				}

				// 如果自己已经有座位信息，说明自己是断线进来的，则直接让自己进游戏
				if (SIX_PlayerMgr::GetInstance()->getMyTableIdx()!=-1 && SIX_PlayerMgr::GetInstance()->getMySeatIdx()!=-1)
				{
					SIX_Proxy::GetInstance()->SetChangeScene(true);
					SIXLog("断线重入,切换场景...");
				}
			}
			break;
		}
	case ROOM_SUB_LEAVE_ROOM:
		{
			USER_INFO *pUserInfo = (USER_INFO*)pData;
			SIXLog("[%lld][%d/%d][%s][%s]离房成功",
				pUserInfo->lUserId,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				SIX_Utility::GetInstance()->G2U(pUserInfo->szName).c_str(),
				SIX_Utility::GetInstance()->G2U(pUserInfo->szNickname).c_str());
			// 如果是其他玩家离房，同时自己还在房间场景，需要清空其他玩家的座位
			// Cool.Cat
			if (pUserInfo->lUserId!=INVALID_USER_ID && pUserInfo->iTableNo!=INVAL_TABLE_NO && pUserInfo->iSeatNo!=INVAL_SEAT_NO)
			{
				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
				{
					pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(pUserInfo->lUserId,pUserInfo->iTableNo,pUserInfo->iSeatNo,false);
				}
			}
			SIX_PlayerMgr::GetInstance()->Del(pUserInfo->lUserId);
			break;
		}
	case ROOM_SUB_ROOM_USER_COUNT:
		{
			CMD_RoomUserCount *pRoomUserCount = (CMD_RoomUserCount *)pData;
			SIXLog("人数统计：房间人数[%d]，排队人数[%d]", pRoomUserCount->iRoomUserCount, pRoomUserCount->iArrangeQueueCount);
			break;
		}
	default:
		{
			SIXLog("HandlePacketRoom.subCode[%d].Unknown!",subCode);
			//ShowMsgBox(CCString::createWithFormat("HandlePacketRoom.subCode[%d].Unknown!",subCode)->getCString(),0);
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketTable(int subCode,unsigned char *pData,int pDataLen)
{
	switch (subCode)
	{
	case TABLE_SUB_SITDOWN:
		{
			SITDOWN *packet = (SITDOWN*)pData;
			switch (packet->iRes)
			{
				// ok
			case RET_TABLE_OPERATE_SUCCEED:
				{
					//if (!g_pShipMgr->ExistUserPlayer(packet->lUserId))
					//{// 不存在用户，请重新登录
					//	return ;
					//}
					////先进的玩家的玩家列表数据也要更新，add by Ivan_han 20130715
					//PLAYER_LIST *pPlayerList = NULL;
					//g_pShipMgr->GetUserPlayer(packet->lUserId, &pPlayerList);
					PLAYER_LIST *pPlayerList = SIX_PlayerMgr::GetInstance()->Get(packet->lUserId);
					if (!pPlayerList)
						return;
					//if (NULL != pPlayerList)
					//{
						pPlayerList->iTableId=packet->iTableNo;	// 桌号
						pPlayerList->SeatId=packet->iSeatNo;	// 座位号
						pPlayerList->lGoldLogin = packet->lGoldLogin;
						pPlayerList->lPointLogin = packet->lPointLogin;
					//}

					//if (-1 == g_pShipMgr->mMyTableID)
					if (packet->iTableNo!=-1 && packet->iSeatNo!=-1)
					{
						if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
							pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(packet->lUserId,packet->iTableNo,packet->iSeatNo,true);
					}
					//if (packet->lUserId==g_pShipMgr->mMyUserID)
					if (packet->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
					{
						// -- 给个标志位，在update里面去切换场景，这样看起来画面比较流畅
						SIX_PlayerMgr::GetInstance()->setMySeatIdx(packet->iSeatNo);
						SIX_PlayerMgr::GetInstance()->setMyTableIdx(packet->iTableNo);
						SIX_Proxy::GetInstance()->SetChangeScene(true);
						SIXLog("切换场景...");
					}
					// 跟自己同桌的其他玩家
					else if (packet->iTableNo == SIX_PlayerMgr::GetInstance()->getMyTableIdx())
					{
						CCLayerColor *pBG = dynamic_cast<CCLayerColor*>(pSceneGame->getChildren()->objectAtIndex(0));
						g_pShipMgr->Enter(pBG, packet->lUserId, packet->iSeatNo, false);
					}

					break;
				}
			case RET_TABLE_CHAIR_ERROR:
				{
					SIXLog("坐下失败！失败原因：该座位不存在！");
					ShowMsgBox("坐下失败！失败原因：该座位不存在！");
					break;
				}
			case RET_TABLE_CHAIR_OCCUPY:
				{
					SIXLog("坐下失败！失败原因：该座位已经有人啦！");
					ShowMsgBox("坐下失败！失败原因：该座位已经有人啦！",0);
					break;
				}
			case RET_TABLE_TABLE_START:
				{
					SIXLog("坐下失败！失败原因：桌子已经开始，不允许进入桌子了！");
					ShowMsgBox("坐下失败！失败原因：桌子已经开始，不允许进入桌子了！",0);
					break;
				}
			case RET_TABLE_ENTER_GOLD_LACK:
				{
					SIXLog("坐下失败！失败原因：金币不够进入该桌子！");
					ShowMsgBox("坐下失败！失败原因：金币不够进入该桌子！",0);
					break;
				}
			}
			break;
		}
/*	case TABLE_SUB_USER_INFO:		// 坐桌成功，获取到的桌内其它玩家列表
		{
			SIXLog("接收桌子玩家列表...");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;
			if (NULL != pUserInfo)
			{
				PLAYER_LIST *pPlayerList = NULL;
				g_pShipMgr->GetUserPlayer(pUserInfo->lUserId, &pPlayerList);
				if (NULL != pPlayerList)
				{
					pPlayerList->lGoldLogin = pUserInfo->lGoldLogin;
					pPlayerList->lPointLogin = pUserInfo->lPointLogin;
				}
			}
			break;
		}
	case TABLE_SUB_SITDOWN_FINISH:				// 用户坐桌完成
		{
			SIXLog("坐桌完成...");
			break;
		}*/
	case TABLE_SUB_LEAVE_SEAT:
		{
			LEAVE_SEAT *packet = (LEAVE_SEAT*)pData;
			switch (packet->iRes)
			{
			case 0:
				{
					// 这个判断要去掉
					// Cool.Cat
					//if (NULL==g_pShipMgr->getMySelfShip()  ||  packet->lUserId == g_pShipMgr->getMySelfShip()->m_UserID)
					//	return;

					if (-1 == SIX_PlayerMgr::GetInstance()->getMyTableIdx())
					{
						if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGate,"SIX_SceneGate"))
							pSceneGate->getRoomList()->SwitchSitDownOrLeaveSeat(packet->lUserId,packet->iTableNo,packet->iSeatNo,false);
					}

					//vector<PLAYER_LIST*>::const_iterator it = g_pShipMgr->mPlayerList.begin();
					//for (; it != g_pShipMgr->mPlayerList.end(); ++it )
					//{
					//	PLAYER_LIST * pPlayer = *it;
					//	if (pPlayer->SeatId == packet->iSeatNo  &&  pPlayer->iTableId == packet->iTableNo)
					//	{
					//		g_pShipMgr->Leave( packet->lUserId );
					//		g_pShipMgr->mPlayerList.erase( it );
					//		break;
					//	}
					//}

					SIXLog("[%d][%d][%lld]离座成功",packet->iTableNo,packet->iSeatNo,packet->lUserId);
					SIX_PlayerMgr::GetInstance()->LeaveSeat(packet->lUserId,packet->iTableNo,packet->iSeatNo);
					break;
				}
			case 5:
			case 10:
				{
					SIXLog("离开座位失败！失败原因：该座位不存在！");
					ShowMsgBox("离开座位失败！失败原因：该座位不存在！",0);
					break;
				}
			case 20:
				{
					SIXLog("离开座位失败！失败原因：该座位上还没有人坐呢！");
					ShowMsgBox("离开座位失败！失败原因：该座位上还没有人坐呢！",0);
					break;
				}
			}
			break;
		}
	case TABLE_SUB_RECOMEAFTERCUT:
		{
			CMD_SC_RECOMEAFTERCUT *pRecome = (CMD_SC_RECOMEAFTERCUT*)pData;
			break;
		}
	case TABLE_SUB_INIT_GAME:
		{
			INIT_GAME *pInit = (INIT_GAME *)pData;
			if (NULL == pInit  && SCENES_MIN > pInit->iScenesID  &&  SCENES_MAX < pInit->iScenesID)
			{
				CCAssert(0,"");
				break;
			}
			if(NULL == pSceneGame)
			{
				CCAssert(0,"");
				break;
			}
			
			// 当前时间 - 已经运行时间 = 客户端开机的日历时刻（常量CK）
			//ULONGLONG ullRunTime = SIX_ClientRoom::GetTickCount64();//c2
			ULONGLONG ullRunTime = SIX_Utility::GetInstance()->GetTickCount();
			//ULONGLONG ullRunTime1 = CEasyDataTime::get_current_time_diff_millitm_from_1970();//客户端收包的日历时刻（变量CT）
			ULONGLONG ullRunTime1 = SIX_Utility::GetInstance()->GetTickCount();
			ULONGLONG tStartComputerTime =ullRunTime1 - ullRunTime;//CK
			/*
				add by Ivan_han 20130628
				记发包延迟为ε'，服务器处理举手请求时间为△S≈0，收包延迟为ε≈ε'，时间同步信息到达时刻为c2，则收包延迟ε≈(c2-c1)/2
			*/
			ULONGLONG Epsilon=(ullRunTime-m_tRaiseHandTime)/2;
			long long dT=pInit->tCurrentServerTime-ullRunTime1+Epsilon;//dT=ST-CT+ε（ε>0代表本次收包延迟）表示在同一真实时刻，服务器端调用CEasyDataTime::get_current_time_diff_millitm_from_1970()的值与客户端端调用CEasyDataTime::get_current_time_diff_millitm_from_1970()的值的时间差
			/*
			    add by Ivan_han 20130612
				m_tClientServerTimeInterval=△t=CK-SK+dT表示在同一真实时刻，客户端调用GetTickCount64()的值与服务器端调用GetTickCount64()的值的时间差，
				当服务器与客户端在同一台机器上时，△t=0。
				虽然△t不一定就等于客户端开机的真实时刻与服务器端开机的真实时刻的时间差，
				因为客户端、服务器端与真实时间可能不一致，
				但是不管客户端、服务器端是否与真实时间是否一致，△t都是有用的。
				一般来说（假定客户端、服务器端与真实时间都一致的情况），△t>0<=>CK>SK表示服务器端先开机。
			*/
			m_tClientServerTimeInterval = (tStartComputerTime - pInit->tServerTime+dT);//△t=CK-SK+dT
			pSceneGame->RefreshScenes( pInit->iScenesID );
			g_pBulletMgr->m_uiMaxBulletCount = pInit->uiBulletMaxCount;
			break;
		}
	case TABLE_SUB_FIRE:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			SHOT_FIRE *pReal = (SHOT_FIRE*)pData;
			switch (pReal->iRes)
			{
			case 0:
				{
					if (pReal->iUserID != g_pShipMgr->getMySelfShip()->m_UserID)
					{
						CCPoint ptDes(pReal->fDesPT.x, pReal->fDesPT.y);
						ptDes = g_pShipMgr->SP2CP( ptDes );
						g_pShipMgr->onShootBullet(pReal->iUserID, pReal->iID, ptDes, pReal->bRepeatShoot,false);
					}
					//add by Ivan_han 20130716
					CShip *pShip=g_pShipMgr->getShip(pReal->iUserID);
					if(pShip)
					{
						pShip->setBulletCount(pReal->iUserBulletCount);
					}
					break;
				}
			case RET_GAME_ERROR_CODE_BULLET_LACK:	// add by cxf
				{
					// 用户子弹不够
					if (pReal->iUserID == g_pShipMgr->getMySelfShip()->m_UserID)
						ShowMsgBox("子弹不够，请购买子弹。",0);
					break;
				}
			default: break;
			}
			break;
		}
	case TABLE_SUB_REFLECTION:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			BULLET_REFLECTION *pReflection = (BULLET_REFLECTION*)pData;
			if ( 0 == pReflection->iRes )
			{
				CCPoint ptCur(pReflection->fCurPos.x, pReflection->fCurPos.y);
				CCPoint ptMove(pReflection->fMovePos.x, pReflection->fMovePos.y);
				ptCur = g_pShipMgr->SP2CP( ptCur );
				//ptMove = g_pShipMgr->SP2CP( ptMove );
				ptMove = g_pShipMgr->SD2CD( ptMove );
				g_pBulletMgr->onReflectionBullect(pReflection->llUserID, pReflection->llID, TPoint(ptCur.x, ptCur.y), pReflection->fCurRotation, TPoint(ptMove.x, ptMove.y), pReflection->fMoveTime, pReflection->iReflectionCount, pReflection->iReflectionMax);
			}
			break;
		}
	case TABLE_SUB_CAPTURE_FISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			CAPTURE_FISH *pReal = (CAPTURE_FISH*)pData;
			if ( 0 == pReal->iRes )
			{
				//g_FishMgr->CaptureOneFish( pReal->llUserID, pReal->llBulletID, pReal->chFishID, pReal->chDeadFishID );
				//add by Ivan_han 20130718
				vector<unsigned int> vFishID(pReal->FishIDs,pReal->FishIDs+pReal->nFishCount);
				vector<unsigned int> vDeadFishID;
				for(unsigned int i=0;i<pReal->nDeadFishCount;i++)
				{
					vDeadFishID.push_back((*pReal)[i]);
				}
				g_FishMgr->CaptureFish( pReal->llUserID, pReal->llBulletID,vFishID,vDeadFishID,pReal->FallIntegral,pReal->GunGrade,pReal->DeadFullScreenBombFishID);
				//add by Ivan_han 20130716
				CShip *pShip=g_pShipMgr->getShip(pReal->llUserID);
				if(pShip)
				{
					if (pReal->FallIntegral>0)
						pShip->setFishCoin(pReal->llUserGameCoinCount);
				}
				//add by Ivan_han 20130724
				if (pReal->llUserID == g_pShipMgr->getMySelfShip()->m_UserID)
				{
					PlayerTreasureInfo::Instance().UpdateFishKindNums(pReal->FishKindNums);
				}
				break;
			}
			break;
		}
	//add by Ivan_han 20130713
	case TABLE_SUB_BUY_BULLET_RET:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			USER_BUY_BULLET_RET *pReal = (USER_BUY_BULLET_RET*)pData;
			switch (pReal->iRes)
			{
			case RET_GAME_OPERATE_SUCCEED:
				{
					CShip *pShip = g_pShipMgr->getShip( pReal->llUserID);
					if (NULL == pShip)
						return;
					unsigned long long llBulletNum=g_pShipMgr->getMySelfShip()->getBulletCount()+pReal->iBulletNum;
					pShip->setBulletCount(llBulletNum);
					pShip->setGoldCoin(pReal->llGold,3,false);
					break;
				}
			case RET_GAME_USER_NOT_EXIST:
				{
					ShowMsgBox("用户不存在",0);
					break;
				}
			case RET_GAME_BUY_BULLET_GOLD_LACK:
				{
					ShowMsgBox("金币不够购买子弹",0);
					break;
				}
			default: break;
			}

			break;
		}
	//add by Ivan_han 20130713
	case TABLE_SUB_WRITE_SCORE_RET:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			WRITE_SCORE_RESULT *pReal = (WRITE_SCORE_RESULT*)pData;
			switch (pReal->iRes)
			{
			case 0:
				{
					CShip *pShip = g_pShipMgr->getShip( pReal->lUserId);
					if (NULL == pShip)
						return;
					pShip->setFishCoin(0);
					pShip->setBulletCount(0);
					if(PlayerTreasureInfo::Instance().m_lGameType==2||pReal->lGold>0)
						pShip->setGoldCoin(pReal->lGold,3,true);
					else
						pShip->setGoldCoin(pReal->lPoint,3,true);
					break;
				}
			default: break;
			}

			// 只有从游戏场景切换出来时才可能进来这里
			// Cool.Cat
			if (pSceneGame->IsWaitForChangeScene())
			{
				SIX_Proxy::GetInstance()->SetChangeScene(true);
				return;
			}
			break;
		}
	//add by Ivan_han 20130724
	case RSP_SET_GUNGRADE:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Req_SetGunGrade *pReal = (Req_SetGunGrade*)pData;
			switch (pReal->iRes)
			{
			case RET_GAME_OPERATE_SUCCEED:
				{
					CShip *pShip = g_pShipMgr->getShip( pReal->llUserID);
					if (NULL == pShip)
						return;
					pShip->setGunGrade(pReal->GunGrade);
					if (NULL != pShip->m_gun)
						pShip->m_gun->m_curGunType=pReal->GunGrade;
					break;
				}
			case RET_GAME_USER_NOT_EXIST:
				{
					ShowMsgBox("用户不存在",0);
					break;
				}
			default: break;
			}
			break;
	}
	case RSP_USER_SHOOT:
		{
			break;
		}
    //add by Ivan_han 20130902
	case TABLE_SUB_ANTI_ADDICTION:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			CMD_SC_ANTI_ADDICTION *pReal = (CMD_SC_ANTI_ADDICTION*)pData;
			pSceneGame->SetSysTip(pReal->szContent);
			SIX_Utility::GetInstance()->performWithDelay(pSceneGame,callfunc_selector(SIX_SceneGame::ClearSysTip),30);
			break;
		}
	//add by Ivan_han 20130806
	case RSP_CHANGE_SCENE:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			if(g_FishMgr)
				g_FishMgr->SpeedUpAllFish();

			Rsp_ChangeScene *pReal = (Rsp_ChangeScene*)pData;
			if (0 < SIX_PopWnd::GetPopWndCount())
				return;
			pSceneGame->RiseTide(pReal->SeaSceneKind, 4.0f, 0.1f,pReal->bRToL);
			break;
		}
	case RSP_ADD_ONE_FISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish *pReal = (Rsp_AddOneFish*)pData;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			long long llInitElapsed=ClientBuildTime-pReal->BuildTraceTime+m_tClientServerTimeInterval;
			float InitElapsed =llInitElapsed * 0.001;
			OnAddOneFish(pReal,InitElapsed,pReal->BuildTraceTime);
			break;
		}
	case RSP_ADD_ONE_FISH_ARR:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_Arr *pReal = (Rsp_AddOneFish_Arr*)pData;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			for(int i=0;i<(int)(pReal->nFishCount);i++)
			{
				long long llInitElapsed=ClientBuildTime-pReal->Arr[i].BuildTraceTime+m_tClientServerTimeInterval;
				float InitElapsed =llInitElapsed * 0.001;
				OnAddOneFish(&pReal->Arr[i],InitElapsed,pReal->Arr[i].BuildTraceTime);
			}
			break;
		}
	case RSP_ADD_ONE_FISH_LIST:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_List *pReal = (Rsp_AddOneFish_List*)pData;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			//SIX_Utility::GetInstance()->TimerStart();
			for(int i=0;i<(int)(pReal->nFishCount);i++)
			{
				long long llInitElapsed=ClientBuildTime-(*pReal)[i].BuildTraceTime+m_tClientServerTimeInterval;
				float InitElapsed =llInitElapsed * 0.001;
				OnAddOneFish(&(*pReal)[i],InitElapsed,(*pReal)[i].BuildTraceTime);
			}
			//SIX_Utility::GetInstance()->TimerEnd();
			//double time = SIX_Utility::GetInstance()->Fixed(SIX_Utility::GetInstance()->GetMilliseconds(),4);
			//SIXLog("RSP_ADD_ONE_FISH_LIST.time[%04f]",time);
			break;
		}
	case RSP_ADD_ONE_FISH_LIST_UNFINISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_List *pReal = (Rsp_AddOneFish_List*)pData;
			//SIXLog("BusyFishListCount()=%d",BusyFishListCount());
			int ret=IsNeedMalloc(pReal->FishGroupID);
			if(ret)
			{
				FishListInfo *pInfo=GetFishListInfo(pReal->FishGroupID,true);
				if(pInfo==NULL)
					return;
				pInfo->pReal=(Rsp_AddOneFish_List *)malloc(sizeof(Rsp_AddOneFish_List)+sizeof(Rsp_AddOneFish)*pReal->nTotalFishCount);
				pInfo->FishGroupID=pReal->FishGroupID;
				pInfo->RecvCount=pReal->nFishCount;
				memcpy(pInfo->pReal,pReal,sizeof(Rsp_AddOneFish_List)+sizeof(Rsp_AddOneFish)*pReal->nFishCount);
			}
			else
			{
				FishListInfo *pInfo=GetFishListInfo(pReal->FishGroupID,false);
				if(pInfo==NULL)
					return;
				memcpy(&(*(pInfo->pReal))[pInfo->RecvCount],&(*pReal)[0],sizeof(Rsp_AddOneFish)*pReal->nFishCount);
				pInfo->RecvCount+=pReal->nFishCount;
				pInfo->pReal->nFishCount+=pReal->nFishCount;
			}
			//for(int i=0;i<pReal->nFishCount;i++)
			//{
			//	m_vecFish.push_back((*pReal)[i]);
			//}
			break;
		}
	case RSP_ADD_ONE_FISH_LIST_FINISH:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			Rsp_AddOneFish_List *pReal = (Rsp_AddOneFish_List*)pData;
			//SIXLog("BusyFishListCount()=%d",BusyFishListCount());
			//for(int i=0;i<pReal->nFishCount;i++)
			//{
			//	m_vecFish.push_back((*pReal)[i]);
			//}
			FishListInfo *pInfo=GetFishListInfo(pReal->FishGroupID,false);
			if(pInfo==NULL)
				return;
			memcpy(&(*(pInfo->pReal))[pInfo->RecvCount],&(*pReal)[0],sizeof(Rsp_AddOneFish)*pReal->nFishCount);
			pInfo->RecvCount+=pReal->nFishCount;
			pInfo->pReal->nFishCount+=pReal->nFishCount;
			Rsp_AddOneFish_List *pReal1 =pInfo->pReal;
			//TBuildTraceTime ClientBuildTime=SIX_ClientRoom::GetTickCount64();
			TBuildTraceTime ClientBuildTime = SIX_Utility::GetInstance()->GetTickCount();
			for(int i=0;i<(int)(pReal1->nTotalFishCount);i++)
			{
				long long llInitElapsed=ClientBuildTime-(*pReal1)[i].BuildTraceTime+m_tClientServerTimeInterval;
				float InitElapsed =llInitElapsed * 0.001;
				OnAddOneFish(&(*pReal1)[i],InitElapsed,(*pReal1)[i].BuildTraceTime);
			}

			//m_vecFish.clear();
			free(pInfo->pReal);
			pInfo->pReal=NULL;
			pInfo->FishGroupID=0;
			pInfo->RecvCount=0;
			break;
		}
	case TABLE_SUB_NET_GAP_TIME:
		{// 拼网络延迟		// add by cxf
			if (NULL == pData)
			{
				break;
			}
			CMD_NET_GAP_TIME *pNetGapTime = (CMD_NET_GAP_TIME*)pData;
			//if (g_pShipMgr->ExistUserPlayer(pNetGapTime->llUserID))
			if (!SIX_PlayerMgr::GetInstance()->Get(pNetGapTime->llUserID))
			{// 用户已经存在
				CShip *pShip = g_pShipMgr->getShip( pNetGapTime->llUserID);
				if (NULL == pShip)
				{
					return;
				}
				//_timeb timebuffer;
				//_ftime( &timebuffer );		// 获取当前时间
				//long long llTIme = timebuffer.time*1000 + timebuffer.millitm;	// 转换毫秒
				//long long delay = CEasyDataTime::get_current_time_diff_millitm_from_1970() - pNetGapTime->llSendTime;
				long long delay = SIX_Utility::GetInstance()->GetTickCount() - pNetGapTime->llSendTime;
				pShip->setNetGapTime(delay);
			}
			break;
		}
	case TABLE_SUB_USER_OVERTIME:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			// 超过60秒未发射子弹，出倒计时提示
			USER_OVERTIME_SURPLUS *packet = (USER_OVERTIME_SURPLUS*)pData;
			pSceneGame->ShowCountDown(packet->iSurplusTime);
			break;
		}
	case TABLE_SUB_USER_DATA_CHANGE:
		{
			CMD_SC_USER_DATA_CHANGE *userDataChange = (CMD_SC_USER_DATA_CHANGE*)pData;
			if (NULL==userDataChange)
			{
				return;
			}
			//PLAYER_LIST *pPlayerList = NULL;
			//g_pShipMgr->GetUserPlayer(userDataChange->lUserId, &pPlayerList);
			PLAYER_LIST *pPlayerList = SIX_PlayerMgr::GetInstance()->Get(userDataChange->lUserId);
			if (NULL != pPlayerList)
			{
				pPlayerList->lGoldLogin += userDataChange->iGold;
				pPlayerList->lPointLogin += userDataChange->iPoint;
			}
			CShip *pShip = g_pShipMgr->getShip( userDataChange->lUserId);
			if (NULL!=pShip)
			{
				pShip->setBulletCount(userDataChange->iPresentBullet);
			}
			SIXLog("用户数据改变了！目前在桌子开始的时候收取台费改变金币");
			//ShowMsgBox("用户数据改变了！目前在桌子开始的时候收取台费改变金币");
			break;
		}
	case TABLE_SUB_GAME_BEGIN:
		{// 桌子开始
			SIXLog("桌子开始！如果是比赛场的话，把界面上的等待其它玩家参加比赛的框去掉");
			//ShowMsgBox("桌子开始！如果是比赛场的话，把界面上的等待其它玩家参加比赛的框去掉");
			break;
		}
	default:
		{
			SIXLog("HandlePacketTable.subCode[%d].Unknown!",subCode);
			//ShowMsgBox(CCString::createWithFormat("HandlePacketTable.subCode[%d].Unknown!",subCode)->getCString(),0);
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketMatch(int subCode,unsigned char *pData,int pDataLen)
{
	switch (subCode)
	{
	case MATCH_SUB_SC_ARRANGE_QUEUE_FINISH:	// 排队完成
		{
			break;
		}
	case MATCH_SUB_SC_CANCEL_ARRANGE_QUEUE_FINISH:	// 返回取消排队完成
		{
			break;
		}
	case MATCH_SUB_SC_GAME_END:	// 比赛结束
		{
			CMD_MatchEnd * pMatchEnd = (CMD_MatchEnd *)pData;

			SIX_MatchEnd *pWndMatchEnd = SIX_MatchEnd::Create(0, 0, ccc4(0,0,0,0), 592, 401, false, true);
			pWndMatchEnd->InitMask(ccc4(0,0,0,128));
			pWndMatchEnd->backgroundWithFile("Common/MatchEnd/matchEndBG.png");
			pWndMatchEnd->SetMatchData( pMatchEnd );
			pWndMatchEnd->SetMyselfID( SIX_PlayerMgr::GetInstance()->getMyUserIdx() );
			pWndMatchEnd->Show( true );
			break;
		}
	case MATCH_SUB_SC_MATCH_COUNTDOWN:
		{
			if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				return;
			if (!pSceneGame->IsInited())
				return;

			CMD_SC_MATCH_COUNTDOWN * pCountdown = (CMD_SC_MATCH_COUNTDOWN *)pData;
			pSceneGame->SetMatchCountdown(pCountdown->iMatchCountDown);
			SIXLog("比赛倒计时[%d]!",pCountdown->iMatchCountDown);
			break;
		}
	default:
		{
			SIXLog("HandlePacketMatch.subCode[%d].Unknown!",subCode);
			//ShowMsgBox(CCString::createWithFormat("HandlePacketMatch.subCode[%d].Unknown!",subCode)->getCString(),0);
			break;
		}
	}
}

void SIX_ClientRoom::OnAddOneFish(Rsp_AddOneFish *pReal,float InitElapsed,TBuildTraceTime BuildTraceTime)
{
	if(InitElapsed>pReal->FishMoveSecs)
		return;
	//pathType==4时为Curve类的静态成员函数定义的轨迹
	CCPoint startCP=g_pShipMgr->SP2CP(CCP(pReal->startP));//代表点
	//FishPathType=1,代表方向
	CCPoint arg1CP=ccpSub(g_pShipMgr->SP2CP(CCP(pReal->arg1)),g_pShipMgr->SP2CP(ccp(0,0)));//代表方向，≠CCP(pReal->arg1),≠g_pShipMgr->SP2CP(CCP(pReal->arg1))
	if(pReal->FishPathType==2||pReal->FishPathType==5||pReal->FishPathType==7)
		arg1CP=g_pShipMgr->SP2CP(CCP(pReal->arg1));//代表点
	if(pReal->FishPathType==3||pReal->FishPathType==4||pReal->FishPathType==6)
		arg1CP=CCP(pReal->arg1);//既不代表点，也不代表方向，仅用于存储
	//FishPathType=5,代表点
	CCPoint arg2CP=g_pShipMgr->SP2CP(CCP(pReal->arg2));
	if(pReal->FishPathType==3)
	{
		arg2CP=ccp(pReal->arg2.x,g_pShipMgr->SD2CD(pReal->arg2.y));//y分量代表方向
	}
	if(pReal->FishPathType==7)
	{
		arg2CP=CCP(pReal->arg2);//既不代表点，也不代表方向，仅用于存储
	}
	//FishPathType=5,代表点
	CCPoint arg3CP=g_pShipMgr->SP2CP(CCP(pReal->arg3));
	if(pReal->FishPathType==3||pReal->FishPathType==6||pReal->FishPathType==7)
	{
		arg3CP=CCP(pReal->arg3);//既不代表点，也不代表方向，仅用于存储
	}
	g_FishMgr->addOneFish(pReal->FishID, pReal->FishKind, pReal->FishPathType, pReal->FishMoveSecs,pReal->FishMoveStatus, InitElapsed,BuildTraceTime,startCP, arg1CP, arg2CP, arg3CP);
}

//unsigned long long SIX_ClientRoom::GetTickCount64()
//{
//	////#ifdef WIN32
//	//#if 0
//	//	return ::GetTickCount64();
//	//#else
//	//	//此时假定客户端的开机时刻是1970年
//	//	return CEasyDataTime::get_current_time_diff_millitm_from_1970();
//	//#endif
//	return SIX_Utility::GetInstance()->GetTickCount();
//}

bool SIX_ClientRoom::IsNeedMalloc(TFishGroupID FishGroupID)
{
	for(int i=0;i<20;i++)
	{
		if(m_FishListInfos[i].FishGroupID==FishGroupID)
		{
			return false;
		}
	}
	return true;
}

FishListInfo *SIX_ClientRoom::GetFishListInfo(TFishGroupID FishGroupID,bool isFirst)
{
	if(isFirst)
	{
		for(int i=0;i<20;i++)
		{
			if(m_FishListInfos[i].FishGroupID==0)
			{
				//m_FishListInfos[i].FishGroupID=FishGroupID;
				return &m_FishListInfos[i];
			}
		}
	}
	else
	{
		for(int i=0;i<20;i++)
		{
			if(m_FishListInfos[i].FishGroupID==FishGroupID)
			{
				return &m_FishListInfos[i];
			}
		}
	}
	return NULL;
}

int SIX_ClientRoom::BusyFishListCount()const
{
	int nCount=0;
	for(int i=0;i<20;i++)
	{
		if(m_FishListInfos[i].FishGroupID>0)
		{
			nCount++;
		}
	}
	return nCount;
}

void SIX_ClientRoom::login_room()
{
	if (this->getNeedExit())
		return;

	LOGIN_ROOM sendData;
	memset(&sendData, 0, sizeof(LOGIN_ROOM));
	
	if(this->GetLoginInfo().bAlreadyInRoom)	// 已经在房间里啦
	{
		if( 0==STRCMP(this->GetRoomInfo()->szIP, this->GetLoginInfo().szIP) && this->GetRoomInfo()->iPort==this->GetLoginInfo().iPort )	// 已经在此房间里啦
		{
			SIXLog("直接重新显示该房间，因为已经在此房间里啦 ");
		}
		else	// 经在某个房间里啦，请先退出房间
		{
			SIXLog("您已经在某个房间里啦，请先退出房间 \n");
		}
	}
	else	// 申请登录房间
	{
		sendData.lUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
		memcpy(sendData.szName, this->GetRoomInfo()->szName, sizeof(sendData.szName));
		memcpy(sendData.szPassword, this->GetRoomInfo()->szPassword, sizeof(sendData.szPassword));

		send_data(ROOM_MAIN, ROOM_SUB_LOGIN, (BYTE*)(&sendData), sizeof(sendData));
	}
}

void SIX_ClientRoom::leave_room()
{
	if (this->getNeedExit())
		return;
	send_data(ROOM_MAIN, ROOM_SUB_LEAVE_ROOM, 0, 0);
}

void SIX_ClientRoom::sit_down(int iTableNo, int iSeatNo)
{
	if (this->getNeedExit())
		return;

	SITDOWN sendData;
	sendData.iTableNo = iTableNo;
	sendData.iSeatNo = iSeatNo;

	send_data(TABLE_MAIN, TABLE_SUB_SITDOWN, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::raise_hand()
{
	if (this->getNeedExit())
		return;

	RAISE_HAND sendData;

	// 能够开始游戏，坐下后的消息，客户端要等到初始化完毕后，发此消息，服务端才发鱼
	send_data(TABLE_MAIN, TABLE_SUB_RAISE_HAND, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::leave_seat()
{
	if (this->getNeedExit())
		return;

	send_data(TABLE_MAIN, TABLE_SUB_LEAVE_SEAT, 0, 0);
}

void SIX_ClientRoom::query_table_list()
{
	if (this->getNeedExit())
		return;

	send_data(ROOM_MAIN, ROOM_SUB_TABLE_LIST);
}

void SIX_ClientRoom::query_user_list()
{
	if (this->getNeedExit())
		return;

	send_data(ROOM_MAIN, ROOM_SUB_USER_LIST);
}

void SIX_ClientRoom::write_score(const CMD_WRITE_SCORE& score)
{
	if (this->getNeedExit())
		return;

	send_data(TABLE_MAIN, TABLE_SUB_WRITE_SCORE, (BYTE*)(&score), sizeof(score));
}

void SIX_ClientRoom::tick_one_leave_seat(int iTableNo, int iSeatNo)
{
	if (this->getNeedExit())
		return;

	// 踢一个玩家离座
	TICK_ONE_LEAVE_SEAT sendData;
	sendData.iTableNo = iTableNo;
	sendData.iSeatNo = iSeatNo;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_ONE_LEAVE_SEAT, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_table_leave_seat(int iTableNo)
{
	if (this->getNeedExit())
		return;

	// 踢一个玩家离座
	TICK_TABLE_LEAVE_SEAT sendData;
	sendData.iTableNo = iTableNo;
	sendData.bWriteScore = true;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_TABLE_LEAVE_SEAT, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_all_leave_seat()
{
	if (this->getNeedExit())
		return;

	TICK_ALL_LEAVE_SEAT sendData;
	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_ALL_LEAVE_SEAT, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_user_out_room(int iTableNo, int iSeatNo)
{
	if (this->getNeedExit())
		return;

	TICK_USER_OUT_ROOM sendData;
	sendData.iTickMode = TICK_USER_OUT_ROOM::TICK_BY_TABLE_SEAT;	// 按桌号、座号踢
	sendData.bWriteScore = true;
	sendData.iTableNo = iTableNo;
	sendData.iSeatNo = iSeatNo;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_USER_OUT_ROOM, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_user_out_room(int iTableNo)
{
	if (this->getNeedExit())
		return;

	TICK_USER_OUT_ROOM sendData;
	sendData.iTickMode = TICK_USER_OUT_ROOM::TICK_BY_TABLE;	// 
	sendData.bWriteScore = true;
	sendData.iTableNo = iTableNo;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_USER_OUT_ROOM, (BYTE*)(&sendData), sizeof(sendData));
}

void SIX_ClientRoom::tick_user_out_room()
{
	if (this->getNeedExit())
		return;

	TICK_USER_OUT_ROOM sendData;
	sendData.iTickMode = TICK_USER_OUT_ROOM::TICK_BY_ALL;	// 
	sendData.bWriteScore = true;
	sendData.iTableNo = INVAL_TABLE_NO;

	send_data(MANAGER_MAIN, MANAGER_SUB_TICK_USER_OUT_ROOM, (BYTE*)(&sendData), sizeof(sendData));
}

// add by cxf
// 发送时间（用来获取网络延迟信息）
void SIX_ClientRoom::SendNetGapTime()
{
	if (!g_pShipMgr)
	{
		return;
	}
	if (SIX_PlayerMgr::GetInstance()->getMyUserIdx() > 0)
	{// 用户已经存在
		CShip *pShip = g_pShipMgr->getMySelfShip();
		if (NULL == pShip)
		{// 
			return;
		}
		//static unsigned int iSend = 0;

		//// SendNetGapTime()调度时间不确定，所以采用下面的办法
		//// Cool.Cat
		//if (iSend < 3600 && iSend >0)
		//{// 60 秒发送一次
		//	iSend ++;
		//	return;
		//}
		//iSend = 1;

		//_timeb timebuffer;
		//_ftime( &timebuffer );												// 获取系统时间
		//long long llTIme = timebuffer.time*1000 + timebuffer.millitm;		// 当前秒时间

		//long long llTIme = CEasyDataTime::get_current_time_diff_millitm_from_1970();
		long long llTIme = SIX_Utility::GetInstance()->GetTickCount();

		// 10秒一次ping包
		//if (pShip->getLastPingTime()!=0 && pShip->getLastPingTime()+1000*10<llTIme)
		if (pShip->getLastPingTime()!=0 && pShip->getLastPingTime()+1000*10>llTIme)
			return;

		pShip->setLastPingTime(llTIme);

		CMD_NET_GAP_TIME pNetGapTime;
		pNetGapTime.llUserID =SIX_PlayerMgr::GetInstance()->getMyUserIdx();
		pNetGapTime.llSendTime = llTIme;
		this->send_data(TABLE_MAIN, TABLE_SUB_NET_GAP_TIME, &pNetGapTime, sizeof(pNetGapTime));
	}
}
void SIX_ClientRoom::ShowMsgBox(const char *fmt,...)
{
	SIX_MsgBox *pMsgBox = SIX_MsgBox::Create(0.0,0.0,ccc4(0,0,0,0),409.0,254.0,false,true);
	if (!pMsgBox)
		return;
	pMsgBox->InitMask(ccc4(0,0,0,128));
	pMsgBox->backgroundWithFile("tipbox.png");
	pMsgBox->buttonSubmitWithFileCell("Common/Button/return.png",3);
	pMsgBox->GetBtnSubmit()->setPosition(ccp(270,35));
	pMsgBox->setTextAttribute(20,80,369,140,"宋体",12);
	//pMsgBox->setRectDirty();

	char szBuf[1024] = {0};

    va_list ap;
    va_start(ap,fmt);
	vsnprintf(szBuf,1023,fmt,ap);
    va_end(ap);

	pMsgBox->setString(SIX_Utility::GetInstance()->G2U(szBuf).c_str());
	pMsgBox->Show();
}
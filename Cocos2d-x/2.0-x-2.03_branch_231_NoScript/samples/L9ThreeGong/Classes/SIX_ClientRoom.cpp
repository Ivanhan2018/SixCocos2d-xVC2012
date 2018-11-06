#include "SIX_ClientRoom.h"
#include "SIX_PlayerMgr.h"
#include "SIX_SceneGame.h"
#include "SIX_SceneHall.h"
#include "SIX_RoomMgr.h"
#include <SIX_TMap.h>

extern SIX_SceneHall *pSceneHall;
extern SIX_SceneGame *pSceneGame;

SIX_ClientRoom *SIX_ClientRoom::m_gClientRoom = 0;

SIX_ClientRoom::SIX_ClientRoom()
{
	m_bAutoSitDown = true;
	m_bLogicConnect = false;
}

SIX_ClientRoom::~SIX_ClientRoom()
{
}

void SIX_ClientRoom::Connect(const char *addr,int port,bool bReconnected/*=true*/,int iReconnectDelay/*=MAX_RECONNECT_DELAY*/, bool bAutoSitDown/*=true*/)
{
	m_gClientRoom = SIX_ClientRoom::GetInstance();
	m_gClientRoom->m_bAutoSitDown = bAutoSitDown;
	m_gClientRoom->m_bLogicConnect = true;

//#define LOCAL_SERVER
#ifdef LOCAL_SERVER
	m_gClientRoom->init("192.168.1.167",port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass(),bReconnected,iReconnectDelay);
#else
	m_gClientRoom->init((char*)addr,port,SIX_PlayerMgr::GetInstance()->getMyName(),SIX_PlayerMgr::GetInstance()->getMyPass(),bReconnected,iReconnectDelay);
#endif
	m_gClientRoom->start();
}

void SIX_ClientRoom::Disconnect()
{
	// 清理本桌用户信息
	SIX_PlayerMgr::GetInstance()->clearPlayers();
	// 清理SIX_PlayerMgr
	SIX_PlayerMgr::GetInstance()->Destory();

	if (!m_gClientRoom)
		return;

	m_gClientRoom->m_bLogicConnect = false;
	m_gClientRoom->stop();
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

		// 房间登录包延迟1s发送，这种情况下MSG队列会一直阻塞，直到延迟包发送完成，才继续发送后续封包
		// Cool.Cat
		int retv = send_data(ROOM_MAIN, ROOM_SUB_LOGIN, (BYTE*)(&sendData), sizeof(sendData));
		SIXLog("正在登录房间.retv[%d]...",retv);
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

	SIXLog("SIX_ClientRoom::sit_down iTableNo=%d, iSeatNo=%d",iTableNo,iSeatNo)
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
					break;
				}
				// 闪断，例如手工禁用【本地连接】的方式模拟路由信号不稳定
			case CLOSE_TYPE_FLASH_CLOSE:
				{
					SIXLog("网络闪断");
					break;
				}
				// 服务端主动关闭客户端
			case CLOSE_TYPE_SERVER_POWER_CLOSE:
				{
					SIXLog("服务端主动关闭");
					break;
				}
			}
			m_bLogicConnect = false;
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
					this->setReconnect(true);
					this->login_room();
					break;
				}
				// OnConnect
			case RECONNECT_SUCCESSED:
				{
					SIXLog("断线重连成功...");
					this->setReconnect(true);
					this->login_room();
					break;
				}
				// OnConnectFail
			case CONNECT_FAILED:
				{
					SIXLog("连接失败");
					if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall") &&
						!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
						return;

					if (0 != pSceneHall  &&  0 != pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
						pSceneHall->GetPopWndRoomList()->SetReceiveDataComplete(true, true);

#ifdef WIN32
					CCMessageBox(/*服务器连接失败，请重试！*/XorStr<0xF8,25,0xFF483E1A>("\x4F\x07\x34\x0A\x3A\x0A\x3F\x53\xBD\xD2\xC8\xA4\xB4\xD9\xA5\xAB\xCF\xE2\xDC\xD3\xC6\xD9\xAD\xAE"+0xFF483E1A).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*服务器连接失败，请重试！*/XorStr<0xF8,25,0xFF483E1A>("\x4F\x07\x34\x0A\x3A\x0A\x3F\x53\xBD\xD2\xC8\xA4\xB4\xD9\xA5\xAB\xCF\xE2\xDC\xD3\xC6\xD9\xAD\xAE"+0xFF483E1A).s).c_str(),0);
#endif
					m_bLogicConnect = false;
					break;
				}
				// OnCommError
			case COMM_ERROR:
				{
					SIXLog("网络通讯异常");
					m_bLogicConnect = false;
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
}

void SIX_ClientRoom::auto_sit_down()
{
	int TableIdx=0;
	int SeatIdx=0;
	char sz[20]={0};
	for(int i=1;i<100;i++)
	{
		sprintf(sz,"T%d",i);
		if(STRCMP(this->GetRoomInfo()->szName,sz)==0)
		{
			TableIdx=i/10;
			SeatIdx=(i%10)%6;
			break;
		} 
	}
	this->sit_down(TableIdx,SeatIdx);
}

void SIX_ClientRoom::HandlePacketRoom(int iSubCode,unsigned char *pData,int iDataLen)
{
	switch(iSubCode)
	{
	case ROOM_SUB_LOGIN_FAIL:
		{
			LOGIN_ROOM_FAIL* pReal = (LOGIN_ROOM_FAIL*)pData;
			SIXLog("用户登录失败，错误码：%d  \n", pReal->iErrCode);
			return;
		}
	case ROOM_SUB_LOGIN_SUCC:	// 房间内广播，登录房间成功
		{
			assert(sizeof(LOGIN_ROOM_SUCC)==iDataLen);
			if(sizeof(LOGIN_ROOM_SUCC)!=iDataLen)		// 安检
				return;

			LOGIN_ROOM_SUCC* pReal = (LOGIN_ROOM_SUCC*)pData;
            SIXLog("登录房间成功：iPort=%d  \n", pReal->iPort);

			USER_INFO_SIM *pUserInfo = &pReal->userInfo;
			SIXLog("自己[%lld]：szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);
			//memcpy(&m_MeUserInfo,pUserInfo,sizeof(USER_INFO_SIM));
			SIX_PlayerMgr::GetInstance()->setMyUserIdentity(pUserInfo->lIdentity);
			SIX_PlayerMgr::GetInstance()->setMySeatIdx(pUserInfo->iSeatNo);
			SIX_PlayerMgr::GetInstance()->setMyTableIdx(pUserInfo->iTableNo);

			// 断线
			if (pUserInfo->stUserState>US_ONLINE_LEAVE_SIT)
			{
				SIXLog("断线重连进入房间...");
			}

			SIX_RoomMgr::GetInstance()->InitRoom();
			return;

		}
	case ROOM_SUB_RECOME:	// 断线重入
		{
			assert(sizeof(RECOME_AFTER_CUT)==iDataLen);
			if(sizeof(RECOME_AFTER_CUT)!=iDataLen)		// 安检
				return;

			RECOME_AFTER_CUT* pReal = (RECOME_AFTER_CUT*)pData;
			SIXLog("%s 断线重入，桌号%d ， 座号%d \n", pReal->szName, pReal->iTableNo, pReal->iSeatNo);

			return;
		}
	case ROOM_SUB_USER_INFO:	// 登录者的信息
		{
			assert(sizeof(USER_INFO)==iDataLen);
			if(sizeof(USER_INFO)!=iDataLen)		// 安检
				return;

			USER_INFO* pReal = (USER_INFO*)pData;
			SIXLog("用户信息, 姓名：%s，  昵称：%s, \n", pReal->szName, pReal->szNickname);

			return;
		}
	case ROOM_SUB_USER_LIST:	// 接收用户列表
		{
			//USER_INFO* pUserInfo = (USER_INFO*)pData;
			//vecUserInfo.push_back(*pUserInfo);
			SIXLog("接收玩家列表...\n");
			USER_INFO_SIM *pUserInfo = (USER_INFO_SIM*)pData;

			SIXLog("玩家[%lld]：szName[%s].szNickname[%s].iTableNo[%d].iSeatNo[%d].lGoldLogin[%lld].stUserState[%d]\n",
				pUserInfo->lUserId,
				pUserInfo->szName,
				pUserInfo->szNickname,
				pUserInfo->iTableNo,
				pUserInfo->iSeatNo,
				pUserInfo->lGoldLogin,
				pUserInfo->stUserState);

			// 保存用户列表(场景退出时会自动释放)
			// Cool.Cat
			USER_INFO_SIM *pPlayer = new USER_INFO_SIM();
			memcpy(pPlayer,pUserInfo,sizeof(*pUserInfo));
			SIX_PlayerMgr::GetInstance()->Add(pPlayer->lUserId,pPlayer);

			SIX_RoomMgr::GetInstance()->SetTablePlayerCount(pPlayer->iTableNo, 1);
			return;
		}
	case ROOM_SUB_USER_LOGIN_FINISH:	// 登陆完成
		{
			if (0 != pSceneHall  &&  0 != pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
			{
				pSceneHall->GetPopWndRoomList()->SetReceiveDataComplete();
				for (int i=0; i<SIX_RoomMgr::GetInstance()->GetTableCount(); ++i)
				{
					pSceneHall->GetPopWndRoomList()->SetTablePeopleNumber(i, SIX_RoomMgr::GetInstance()->GetTablePlayerCount(i));
				}
			}

			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall"))
			{
				if (-1!=SIX_PlayerMgr::GetInstance()->getMyTableIdx()  &&  -1!=SIX_PlayerMgr::GetInstance()->getMySeatIdx())
				{
					SIX_Proxy::GetInstance()->SetChangeScene(true);
					SIX_RoomMgr::GetInstance()->SetCurRoomID(-1);
				}
				else
				{
					if (m_bAutoSitDown)
					{
						this->sit_down(SIX_PlayerMgr::GetInstance()->getMyTableIdx(), SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					}
				}
			}
			return;
		}
	case ROOM_SUB_USER_LIST_OVER:	// 接收用户列表结束
		{
			SIXLog("房内的用户列表结束：  \n");

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
			SIXLog("接收桌子列表...\n");
			SERVER_ROOM_INFO_SIM *packet = (SERVER_ROOM_INFO_SIM*)pData;
			SIXLog("房间人数[%ld]：房内桌子的数量[%d].每桌人数[%d].游戏类型[%d].倍频[%d]\n",packet->iRoomPeopleCount,packet->iTables,packet->iSeatNum,packet->iRoomType,packet->iBasePoint);

			break;
		}
	case ROOM_SUB_LEAVE_ROOM:	// 离房成功
		{
			LEAVE_ROOM_RESULT* pReal = (LEAVE_ROOM_RESULT*)pData;

			// 跟自己同桌的玩家
			if (pReal->iTableNo==SIX_PlayerMgr::GetInstance()->getMyTableIdx() && pReal->lUserId!=SIX_PlayerMgr::GetInstance()->getMyUserIdx())
			{
				if (pReal->iSeatNo>=0 && pReal->iSeatNo<GAME_PLAYER_COUNT)
				{
					if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
					{
						// 刷新游戏场景UI
						int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						// 用户信息区隐藏
						pSceneGame->showPlayerZoneShow(ViewID,false);
						// 牌堆隐藏
						pSceneGame->showCardSuit(ViewID,false);
						// 隐藏统计面板
						pSceneGame->showStatsPanel(ViewID,0,false,false,false);
						// 隐藏筹码区
						pSceneGame->SetChipPanelNumber(ViewID,0,false);
						// 隐藏庄家标志
						pSceneGame->showPlayerRubBanker(ViewID,false);
					}
				}
			}

			// 清理用户数据
			for (int j=0;j<GAME_PLAYER_COUNT;j++)
			{
				SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[j];
				if (pPlayer && pPlayer->UserIdx==pReal->lUserId)
				{
					memset(pPlayer,0,sizeof(*pPlayer));
				}
			}

			SIX_PlayerMgr::GetInstance()->Del(pReal->lUserId);

			//if(0 == pReal->iErrCode)
			//{
			//	printf("%s 离房成功 \n", pReal->userInfo.szName);
			//}
			//else
			//{
			//	printf("%s 不在房间内！ \n", pReal->userInfo.szName);
			//	close(CLOSE_TYPE_CLIENT_CLOSE);	// 客户端主动关闭，主动关闭服务端
			//}
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
			SIXLog("未处理的消息 iSubCode = %d", iSubCode);
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketTable(int iSubCode,unsigned char *pData,int iDataLen)
{
	switch(iSubCode)
	{
	//case TABLE_SUB_SITDOWN:
	//	{
	//		SITDOWN* pReal = (SITDOWN*)pData;
	//		if(0==pReal->iRes)
	//		{
	//			SIXLog("用户ID%I64d 坐下，桌号%d , 座号%d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo);
	//		}
	//		else
	//		{
	//			SIXLog("用户ID%I64d 坐下失败，桌号%d , 座号%d , 错误码 %d \n", pReal->lUserId ,pReal->iTableNo, pReal->iSeatNo, pReal->iRes);
	//		}

	//		break;
	//	}
	case TABLE_SUB_SITDOWN:
		{
			SITDOWN *packet=(SITDOWN*)pData;
			switch (packet->iRes)
			{
			case RET_TABLE_OPERATE_SUCCEED:
				{
					bool sameTable = false;
					// 自己坐下
					if (packet->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
					{
						sameTable = true;
						SIX_PlayerMgr::GetInstance()->setMySeatIdx(packet->iSeatNo);
						SIX_PlayerMgr::GetInstance()->setMyTableIdx(packet->iTableNo);
					}
					// 跟自己同桌的其他玩家
					else if (packet->iTableNo == SIX_PlayerMgr::GetInstance()->getMyTableIdx())
					{
						sameTable = true;
					}

					// 更新用户在房间用户列表中的座号椅号
					USER_INFO_SIM *pPlayer = SIX_PlayerMgr::GetInstance()->Get(packet->lUserId);
					if (pPlayer)
					{
						pPlayer->iTableNo = packet->iTableNo;
						pPlayer->iSeatNo = packet->iSeatNo;
						pPlayer->stUserState = US_ONLINE_SITDOWN;
						SIX_RoomMgr::GetInstance()->SetTablePlayerCount(pPlayer->iTableNo, 1);
						if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
							pSceneHall->GetPopWndRoomList()->SetTablePeopleNumber(pPlayer->iTableNo, SIX_RoomMgr::GetInstance()->GetTablePlayerCount(pPlayer->iTableNo));
					}

					// 自己 或 跟自己同桌的用户坐下时处理
					if (sameTable)
					{
						// 遍历当前房间用户列表，处理已经在自己前面坐下的同坐用户
						SIX_TMap<long long,USER_INFO_SIM*>::KV_MAP mmap = SIX_PlayerMgr::GetInstance()->GetMap();
						SIX_TMap<long long,USER_INFO_SIM*>::KV_ITER iter = mmap.begin();
						for (;iter!=mmap.end();iter++)
						{
							USER_INFO_SIM *pPlayer = iter->second;
							if (!pPlayer)
								continue;

							// 查找与自己同桌的用户，包括自己
							if (SIX_PlayerMgr::GetInstance()->getMyTableIdx()==pPlayer->iTableNo)
							{
								//if (pPlayer->iSeatNo<0 || pPlayer->iSeatNo>=MAX_PLAYER_COUNT)
								//{
								//	CCString *errMsg = CCString::createWithFormat("坐桌.桌号[%d].椅号[%d].用户ID[%lld].昵称[%s].该用户椅号溢出！",
								//		pPlayer->iTableNo,pPlayer->iSeatNo,pPlayer->lUserId,pPlayer->szNickname);
								//	SIXLog("%s",SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str());
								//	CCMessageBox(SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str(),0);
								//	continue;
								//}
								if (pPlayer->iSeatNo<0 || pPlayer->iSeatNo>=GAME_PLAYER_COUNT)
									continue;

								SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[pPlayer->iSeatNo];
								// 桌号
								pSinglePlayer->iTableId = pPlayer->iTableNo;
								// 座号
								pSinglePlayer->SeatId = pPlayer->iSeatNo;
								// 用户ID
								pSinglePlayer->UserIdx = pPlayer->lUserId;
								// 金币
								pSinglePlayer->lGoldLogin = pPlayer->lGoldLogin;
								// 积分
								pSinglePlayer->lPointLogin = pPlayer->lPointLogin;
								// 头像
								pSinglePlayer->lSysLogoID = pPlayer->lSysLogoID;
								// 帐号
								memcpy(pSinglePlayer->szName,pPlayer->szNickname,sizeof(pPlayer->szName));
								// 昵称
								memcpy(pSinglePlayer->szNickname,pPlayer->szNickname,sizeof(pPlayer->szNickname));
								// 举手
								pSinglePlayer->bRaiseHand = (pPlayer->stUserState==US_ONLINE_SITDOWN_RAISE)?true:false;

								// 如果不是自己
								if (SIX_PlayerMgr::GetInstance()->getMyUserIdx()!=packet->lUserId)
								{
									if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
									{
										// 刷新游戏场景UI
										int ViewID=SIX_PlayerMgr::getViewID(pPlayer->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
										// 用户信息区显示
										pSceneGame->showPlayerZoneShow(ViewID,true);
										// 设置显示用户昵称
										pSceneGame->setPlayerZoneNickName(ViewID,pPlayer->szNickname);
										// 设置显示用户头像
										pSceneGame->setPlayerZoneFaceLogo(ViewID,pPlayer->lSysLogoID);
										// 设置显示用户筹码
										pSceneGame->setPlayerZoneChip(ViewID,pPlayer->lGoldLogin);
										// 设置用户信息区透明度
										pSceneGame->setPlayerZoneOpacity(ViewID,pSinglePlayer->bRaiseHand?255:128);
										// 牌堆隐藏
										pSceneGame->showCardSuit(ViewID,false);
									}
								}
							}
						}
					}

					// for test
					// Cool.Cat
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[i];
						if (!pSinglePlayer)
							continue;
						SIXLog("pSinglePlayer[%d].iTableId[%d].SeatId[%d].UserIdx[%lld].szName[%s].szNickname[%s]",
							i,
							pSinglePlayer->iTableId,
							pSinglePlayer->SeatId,
							pSinglePlayer->UserIdx,
							pSinglePlayer->szName,
							pSinglePlayer->szNickname);
					}
					SIXLog("---------------------------------");

					// 如果是自己坐下，切换到游戏场景
					if (packet->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
					{
						SIXLog("SetChangeScene...");
						SIX_Proxy::GetInstance()->SetChangeScene(true);
						SIX_RoomMgr::GetInstance()->SetCurRoomID(-1);
						// 记录切换场景前收到坐下包的时间
						// Cool.Cat
						SIX_PlayerMgr::GetInstance()->setLastRecvSitDownTime(SIX_Utility::GetInstance()->GetTickCount());
					}

					break;
				}
			case RET_TABLE_CHAIR_ERROR:
				{
					SIXLog("坐下失败！失败原因：该座位不存在！");
#ifdef WIN32
					CCMessageBox(/*坐下失败！失败原因：该座位不存在！*/XorStr<0xA7,35,0x175E755F>("\x70\x50\x66\x68\x61\x0B\x1D\x72\x0C\x11\x7B\x15\x03\x68\x61\x1B\x65\x4A\x1A\x00\x03\x7F\x6A\x47\x71\x7B\x73\x79\x77\x22\x11\x1C\x64\x69"+0x175E755F).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*坐下失败！失败原因：该座位不存在！*/XorStr<0xA7,35,0x175E755F>("\x70\x50\x66\x68\x61\x0B\x1D\x72\x0C\x11\x7B\x15\x03\x68\x61\x1B\x65\x4A\x1A\x00\x03\x7F\x6A\x47\x71\x7B\x73\x79\x77\x22\x11\x1C\x64\x69"+0x175E755F).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_CHAIR_OCCUPY:
				{
					SIXLog("坐下失败！失败原因：该座位已经有人啦！");
#ifdef WIN32
					CCMessageBox(/*坐下失败！失败原因：该座位已经有人啦！*/XorStr<0x03,39,0xB1C6D99D>("\xD4\xFC\xCA\xC4\xCD\xAF\xB9\xD6\xA8\xAD\xC7\xA9\xBF\xCC\xC5\xBF\xC1\xE6\xB6\xAC\xAF\xDB\xCE\xE3\xD5\xA7\xCF\xCF\xA1\x8D\xF2\xF2\xEB\xEF\xE5\x94\x84\x89"+0xB1C6D99D).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*坐下失败！失败原因：该座位已经有人啦！*/XorStr<0x03,39,0xB1C6D99D>("\xD4\xFC\xCA\xC4\xCD\xAF\xB9\xD6\xA8\xAD\xC7\xA9\xBF\xCC\xC5\xBF\xC1\xE6\xB6\xAC\xAF\xDB\xCE\xE3\xD5\xA7\xCF\xCF\xA1\x8D\xF2\xF2\xEB\xEF\xE5\x94\x84\x89"+0xB1C6D99D).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_TABLE_START:
				{
					SIXLog("坐下失败！失败原因：桌子已经开始，不允许进入桌子了！");
#ifdef WIN32
					CCMessageBox(/*坐下失败！失败原因：桌子已经开始，不允许进入桌子了！*/XorStr<0x8B,53,0x85F86ECB>("\x5C\x74\x42\x4C\x45\x37\x21\x4E\x30\x35\x5F\x31\x27\x44\x4D\x37\x49\x6E\x3E\x24\x48\x60\x76\x71\x71\x75\x1B\x0B\x18\x02\x63\x16\x08\x00\x1F\x15\x7B\x7A\x61\x5F\x0E\x4C\x7D\x5D\x60\x78\x6E\x69\x7A\x77\x1E\x1F"+0x85F86ECB).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*坐下失败！失败原因：桌子已经开始，不允许进入桌子了！*/XorStr<0x8B,53,0x85F86ECB>("\x5C\x74\x42\x4C\x45\x37\x21\x4E\x30\x35\x5F\x31\x27\x44\x4D\x37\x49\x6E\x3E\x24\x48\x60\x76\x71\x71\x75\x1B\x0B\x18\x02\x63\x16\x08\x00\x1F\x15\x7B\x7A\x61\x5F\x0E\x4C\x7D\x5D\x60\x78\x6E\x69\x7A\x77\x1E\x1F"+0x85F86ECB).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_ENTER_GOLD_LACK:
				{
					SIXLog("坐下失败！失败原因：金币不够进入该桌子！");
#ifdef WIN32
					CCMessageBox(/*坐下失败！失败原因：金币不够进入该桌子！*/XorStr<0x1F,41,0xDFC7080A>("\xC8\xD8\xEE\xE0\xE9\x83\x95\xFA\x84\x89\xE3\x8D\x9B\xF0\xF9\x83\xFD\xC2\x92\x88\x8E\xC4\x84\xE4\x85\x83\x80\x81\x86\xC4\xF5\xD5\x87\x83\x96\x82\x94\x97\xE6\xE7"+0xDFC7080A).s,0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*坐下失败！失败原因：金币不够进入该桌子！*/XorStr<0x1F,41,0xDFC7080A>("\xC8\xD8\xEE\xE0\xE9\x83\x95\xFA\x84\x89\xE3\x8D\x9B\xF0\xF9\x83\xFD\xC2\x92\x88\x8E\xC4\x84\xE4\x85\x83\x80\x81\x86\xC4\xF5\xD5\x87\x83\x96\x82\x94\x97\xE6\xE7"+0xDFC7080A).s).c_str(),0);
#endif
					break;
				}
			case RET_TABLE_NOT_FOUND_FIT:
				{
					SIXLog("坐下失败！失败原因：未找到合适的椅子和桌子，可能桌子人数已满！");
#ifdef WIN32
					CCMessageBox(/*坐下失败！失败原因：未找到合适的椅子和桌子，可能桌子人数已满！*/XorStr<0x87,63,0x1BB84B06>("\x50\x70\x46\x48\x41\x2B\x3D\x52\x2C\x31\x5B\x35\x23\x48\x41\x3B\x45\x6A\x3A\x20\x55\x28\x48\x4C\x2A\x1D\x1B\x6D\x69\x6E\x10\x62\x75\x66\x7E\x79\x11\x61\x7A\x6E\x78\x63\x12\x1E\x0C\x7D\x71\x6A\x60\x78\x6E\x69\x73\x77\x77\x43\x6D\x11\x03\x38\x60\x65"+0x1BB84B06).s, 0);
#else
					CCMessageBox(SIX_Utility::GetInstance()->G2U(/*坐下失败！失败原因：未找到合适的椅子和桌子，可能桌子人数已满！*/XorStr<0x87,63,0x1BB84B06>("\x50\x70\x46\x48\x41\x2B\x3D\x52\x2C\x31\x5B\x35\x23\x48\x41\x3B\x45\x6A\x3A\x20\x55\x28\x48\x4C\x2A\x1D\x1B\x6D\x69\x6E\x10\x62\x75\x66\x7E\x79\x11\x61\x7A\x6E\x78\x63\x12\x1E\x0C\x7D\x71\x6A\x60\x78\x6E\x69\x73\x77\x77\x43\x6D\x11\x03\x38\x60\x65"+0x1BB84B06).s).c_str(), 0);
#endif
				}
			}
			break;
		}

	case TABLE_SUB_LEAVE_SEAT:
		{
			LEAVE_SEAT* pReal = (LEAVE_SEAT*)pData;

			// 如果是自己离桌
			if (pReal->lUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
			{
				if (pReal->iRes==0)
				{
					SIXLog("第%d桌, 第%d座 ，离座成功！ \n", pReal->iTableNo, pReal->iSeatNo);
				}
				else
				{
					SIXLog("第%d桌, 第%d座 ，离座失败！ \n", pReal->iTableNo, pReal->iSeatNo);
				}

				SIX_PlayerMgr::GetInstance()->setMySeatIdx(pReal->iSeatNo);
				SIX_PlayerMgr::GetInstance()->setMyTableIdx(pReal->iTableNo);
				SIX_Proxy::GetInstance()->SetChangeScene(true);
			}
			// 否则如果是跟自己同桌的其他用户离桌
			else if (pReal->iTableNo==SIX_PlayerMgr::GetInstance()->getMyTableIdx())
			{
				// 查找离桌用户在房间列表中的数据
				USER_INFO_SIM *pPlayer = SIX_PlayerMgr::GetInstance()->Get(pReal->lUserId);
				if (!pPlayer)
					return;

				//if (pReal->iSeatNo<0 || pReal->iSeatNo>=MAX_PLAYER_COUNT)
				//{
				//	CCString *errMsg = CCString::createWithFormat("离桌.桌号[%d].椅号[%d].用户ID[%lld].昵称[%s].该用户椅号溢出！",
				//		pPlayer->iTableNo,pPlayer->iSeatNo,pPlayer->lUserId,pPlayer->szNickname);
				//	SIXLog("%s",SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str());
				//	CCMessageBox(SIX_Utility::GetInstance()->G2U(errMsg->getCString()).c_str(),0);
				//	return;
				//}
				if (pReal->iSeatNo<0 || pReal->iSeatNo>=GAME_PLAYER_COUNT)
					break;

				pPlayer->stUserState = US_ONLINE_LEAVE_SIT;

				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				{
					// 刷新游戏场景UI
					int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					// 用户信息区隐藏
					pSceneGame->showPlayerZoneShow(ViewID,false);
					// 牌堆隐藏
					pSceneGame->showCardSuit(ViewID,false);
					// 隐藏统计面板
					pSceneGame->showStatsPanel(ViewID,0,false,false,false);
					// 隐藏筹码区
					pSceneGame->SetChipPanelNumber(ViewID,0,false);
					// 隐藏庄家标志
					pSceneGame->showPlayerRubBanker(ViewID,false);
				}
			}

			SIX_RoomMgr::GetInstance()->SetTablePlayerCount(pReal->iTableNo, -1);
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneHall,"SIX_SceneHall"))
			{
				if (0!=pSceneHall  &&  0!=pSceneHall->GetPopWndRoomList()  &&  pSceneHall->GetPopWndRoomList()->IsShow())
					pSceneHall->GetPopWndRoomList()->SetTablePeopleNumber(pReal->iTableNo, SIX_RoomMgr::GetInstance()->GetTablePlayerCount(pReal->iTableNo));
			}
			break;
		}
	case TABLE_SUB_TABLE_SPEAK:
		{
			CMD_ChatContent *pChat = (CMD_ChatContent *)pData;
			if (0==pChat  ||  sizeof(CMD_ChatContent) != iDataLen)
			{
				return;
			}

			SIXLog("%s：%s", pChat->szSpeakNickName, pChat->szCentent);
			if (0 != pSceneGame  &&  SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				pSceneGame->getWndMessage()->ReceiInformation(pChat);
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
				SIXLog("用户ID%lld 举手\n", pReal->lUserId);

				// 查找离桌用户在房间列表中的数据
				USER_INFO_SIM *pPlayer = SIX_PlayerMgr::GetInstance()->Get(pReal->lUserId);
				if (!pPlayer)
					return;

				pPlayer->stUserState = US_ONLINE_SITDOWN_RAISE;

				SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[pReal->iSeatNo];
				if (pSinglePlayer && pSinglePlayer->UserIdx)
					pSinglePlayer->bRaiseHand = true;

				if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
				{
					// 刷新该用户信息区透明度
					int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					// 设置用户信息区透明度
					pSceneGame->setPlayerZoneOpacity(ViewID,255);
				}
			}
			else
			{
				CCString *pErr = CCString::createWithFormat("用户ID%I64d 举手失败, 错误码 %d", pReal->lUserId, pReal->iRes);
				SIXLog("%s",pErr->getCString());
#ifdef WIN32
				CCMessageBox(pErr->getCString(),0);
#else
				CCMessageBox(SIX_Utility::GetInstance()->G2U(pErr->getCString()).c_str(),0);
#endif
			}

			break;
		}
	case RSP_CALL_BANKER_NOTIFY:		//可以抢庄
		{
			Rsp_CallBankerNotify* pReal = (Rsp_CallBankerNotify*)pData;
			SIXLog("可以抢庄了");
			//m_byGameState=E_GAME_CALL_BANKER;
			// 抢庄音效
			// add by Ivan_han 20131102
			SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(1000,false);

			// 显示抢庄按钮
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				pSceneGame->showCountDown(true,SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_RUBBANKER"));
				pSceneGame->showBtnRubBanker(true);
				// 抢庄开始则禁止切换到大厅场景
				// Cool.Cat
				SIX_PlayerMgr::GetInstance()->setAllowChangeToHall(false);
			}
			break;
		}
	case RSP_USER_CALL_BANKER:		//用户抢庄
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Req_UserCallBanker* pReal = (Req_UserCallBanker*)pData;
				SIXLog("用户抢庄返回 用户ID=%lld 座位号=%d 是否抢庄=%d TError=%d \n",pReal->llUserID,pReal->iSeatNo,pReal->bCall,pReal->iRes);
				int ViewID = SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
				// 显示抢庄提示
				pSceneGame->showTipRubBanker(ViewID,pReal->bCall,true);

				// 如果是自己抢庄返回，设置标志位
				if (pReal->iSeatNo==SIX_PlayerMgr::GetInstance()->getMySeatIdx())
				{
					SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[SIX_PlayerMgr::GetInstance()->getMySeatIdx()];
					if (pPlayer && !pPlayer->byCallBanker)
						pPlayer->byCallBanker = 1;
				}
			}
			break;
		}
	case RSP_CALL_BANKER_RESULT://抢庄结果
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Rsp_BankerC3Info* pReal = (Rsp_BankerC3Info*)pData;
				SIXLog("可以下注了 wBankerUser=%d C3=%lld C2=%lld C1=%lld 是否经过抢庄环节=%d ，抢庄人数=%d \n",pReal->wBankerUser,pReal->C3,pReal->C2,pReal->C1,pReal->bNeedCallBanker,pReal->CallBankerNum);
				//m_byGameState=E_GAME_CALL_SCORE;

				// 隐藏抢庄按钮区
				pSceneGame->showBtnRubBanker(false);
				pSceneGame->showCountDown(false);

				// 下注开始则禁止切换到大厅场景
				// Cool.Cat
				SIX_PlayerMgr::GetInstance()->setAllowChangeToHall(false);

				SIX_PlayerMgr::GetInstance()->m_wBankerChairID = pReal->wBankerUser;

				// 抢庄结果需要做丢骰子动画
				if (pReal->bNeedCallBanker && pReal->CallBankerNum!=1)
				{
					// 移除庄家标志
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						int ViewID=SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						pSceneGame->showPlayerRubBanker(ViewID,false);
					}

					// 随机骰子测试
					unsigned num[2] = {0,0};
					num[0] = pReal->dice[0];
					num[1] = pReal->dice[1];
					//int ViewID=SIX_PlayerMgr::getViewID(pReal->wBankerUser,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					// 携带包数据
					long long *pData = new long long[5];
					pData[0] = (long long)pSceneGame;
					pData[1] = (long long)pReal->wBankerUser;
					pData[2] = pReal->C1;
					pData[3] = pReal->C2;
					pData[4] = pReal->C3;
					SIXLog("ViewID[%d/%lld].C1/C2/C3[%lld/%lld/%lld]",pReal->wBankerUser,pData[1],pData[2],pData[3],pData[4]);
					pSceneGame->showAnimateThrowDice(num,sizeof(num)/sizeof(unsigned int),pData);
				}
				// 1个人抢庄
				// Cool.Cat
				else if (pReal->CallBankerNum==1)
				{
					// 移除庄家标志
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						int ViewID=SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						pSceneGame->showPlayerRubBanker(ViewID,false);
					}

					// 移动庄家骰子到洗牌区
					pSceneGame->MoveBankerFlagToShuffleArea(pReal->wBankerUser);
					// 移动庄家骰子到庄家区域
					pSceneGame->MoveBankerFlagToBankerArea(pReal->C1,pReal->C2,pReal->C3);
				}
				else
				{
					// 隐藏抢庄提示
					for (int i=0;i<GAME_PLAYER_COUNT;i++)
					{
						int ViewID = SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
						pSceneGame->showTipRubBanker(ViewID,false,false);
					}

					// 设置庄家标志
					int ViewID=SIX_PlayerMgr::getViewID(pReal->wBankerUser,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					pSceneGame->showPlayerRubBanker(ViewID,true);

					// 闲家显示下注按钮
					if(pReal->wBankerUser!=SIX_PlayerMgr::GetInstance()->getMySeatIdx())
					{
						pSceneGame->showCountDown(true,SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_CHIPIN"));
						pSceneGame->showBtnChipin(true);
						pSceneGame->SetBtnChipPoint(pReal->C1,pReal->C2,pReal->C3);
					}
					else
					{
						// 等待闲家下注提示
						pSceneGame->showSprChip(true);
						//散仙庄家显示杀大赔小按钮
						if(SIX_PlayerMgr::GetInstance()->IsSanXianIdentity())
						{
							pSceneGame->showBtnKill(true);
						}
					}
				}
			}
			break;
		}
	case RSP_DICE_NOTIFY:
		{
			//if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			//{
			//	Rsp_BankerC3Info* pReal = (Rsp_BankerC3Info*)pData;
			//}
			break;
		}
	case RSP_USER_CHIPIN:		//用户下注
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Req_UserChipin* pReal = (Req_UserChipin*)pData;
				int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
				SIXLog("用户下注返回 用户ID=%I64d 座位号=%d 下注额=%I64d TError=%d ViewID=%d\n",pReal->llUserID,pReal->iSeatNo,pReal->lScore,pReal->iRes,ViewID);

				// 下注动画
				// Cool.Cat
				pSceneGame->showAnimateChip(ViewID,pReal->lScore);

				// 如果自己是下注玩家，隐藏下注按钮
				if(ViewID==3)
					pSceneGame->showBtnChipin(false);
			}
			break;
		}
		// 所有用户下注完成
	case RSP_CALL_SCORE_END_NOTIFY:
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				SIXLog("洗牌动画1");
				// 隐藏等待闲家下注
				pSceneGame->showSprChip(false);
			}
			break;
		}
	case RSP_SEND_CARD_LIST://发牌
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				pSceneGame->showBtnKill(false);
				pSceneGame->showCountDown(false);
				Rsp_SendCard_List *pCardList = (Rsp_SendCard_List*)pData;
				for(int i=0;i<pCardList->nCount;i++) 
				{
					// 做洗牌发牌动作
					// Cool.Cat
					Rsp_SendCard* pReal = (Rsp_SendCard*)(&pCardList->m_SendCards[i]);
					int ViewID=SIX_PlayerMgr::getViewID(pReal->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					SIXLog("扑克数据=(%d,%d,%d) 用户ID=%I64d 座位号=%d ViewID=%d \n",(int)pReal->cbUserCardData[0],(int)pReal->cbUserCardData[1],(int)pReal->cbUserCardData[2],pReal->llUserID,pReal->iSeatNo,ViewID);

					for (int j=0;j<GAME_PLAYER_COUNT;j++)
					{
						SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[j];
						if (!pPlayer || (pPlayer && pPlayer->UserIdx!=pReal->llUserID))
							continue;

						// save it~
						memcpy(pPlayer->UserCardData,pReal->cbUserCardData,sizeof(pPlayer->UserCardData));
					}
				}
				// 洗牌动画
				SIXLog("洗牌动画2");
				pSceneGame->showAnimateShuffleAndDealCard();
			}
			break;
		}
	case RSP_SEND_FINISH:		//用户搓牌完毕
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Rsp_SendFinish* pReal = (Rsp_SendFinish*)pData;
				SIXLog("用户搓牌完毕返回 用户ID=%I64d 座位号=%d TError=%d \n",pReal->llUserID,pReal->iSeatNo,pReal->iRes);
			}
			break;
		}
	case RSP_GAME_END_LIST://一局游戏结束
		{
			if (SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
			{
				Rsp_GameEnd_List* pReal = (Rsp_GameEnd_List*)pData;
				SIX_TVector<CUSTOM_INFO*> customVec;
				for(int i=0;i<pReal->nCount;i++)
				{
					Rsp_GameEnd *pGameEnd=&pReal->m_GameEnds[i];//&(*pReal)[i];
					int ViewID=SIX_PlayerMgr::getViewID(pGameEnd->iSeatNo,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
					//SIXLog("一局游戏结束 用户ID=%I64d 座位号=%d 游戏税收=%lld 筹码增量=%lld 牌型=%d 点数=%d \n",pGameEnd->llUserID,pGameEnd->iSeatNo,pGameEnd->lGameTax,pGameEnd->lGameScore,(int)pGameEnd->CardType,(int)pGameEnd->CardPoint);
					//for (int j=0;j<3;j++)
					//	pSceneGame->SetCardFrontShow(ViewID,j,true);
					//// 显示每个用户胜负统计面板
					//bool isWin = pGameEnd->lGameScore>0?true:false;
					//pSceneGame->showStatsPanel(ViewID,pGameEnd->CardPoint,isWin,pGameEnd->CardType==1,pGameEnd->CardType==2,pGameEnd->CardType==4);

					//// 自己的处理
					//if (ViewID==3)
					//{
					//	// 胜负动画
					//	// Cool.Cat
					//	// 胜
					//	pSceneGame->showStatsMySelfWinOrLose(pGameEnd->lGameScore>0?true:false);
					//	TChip Chip=SIX_PlayerMgr::GetInstance()->getMyChip()+pGameEnd->lGameScore;
					//	SIX_PlayerMgr::GetInstance()->setMyChip(Chip);
					//}
					// 庄家不记录
					int BankerViewID = SIX_PlayerMgr::getViewID(SIX_PlayerMgr::GetInstance()->m_wBankerChairID,SIX_PlayerMgr::GetInstance()->getMySeatIdx());

					//WLOG("llUserID[%lld].iSeatNo[%u].BankerViewID[%d].ViewID[%d].getMySeatIdx[%lld].m_wBankerChairID[%u].lGameScore[%lld]",
					//	pGameEnd->llUserID,
					//	pGameEnd->iSeatNo,
					//	BankerViewID,
					//	ViewID,
					//	SIX_PlayerMgr::GetInstance()->getMySeatIdx(),
					//	SIX_PlayerMgr::GetInstance()->m_wBankerChairID,
					//	pGameEnd->lGameScore);

					//if (BankerViewID==ViewID)
					//	continue;

					// save it~
					CUSTOM_INFO *pCustomInfo = new CUSTOM_INFO();
					pCustomInfo->ViewID = ViewID;
					pCustomInfo->bBanker = (BankerViewID==ViewID)?true:false;
					pCustomInfo->ChipCount = pGameEnd->lGameScore;
					pCustomInfo->UserID = pGameEnd->llUserID;
					pCustomInfo->lGameTax = pGameEnd->lGameTax;
					pCustomInfo->CardType = pGameEnd->CardType;
					pCustomInfo->CardPoint = pGameEnd->CardPoint;
					customVec.Push(pCustomInfo);
					//SIX_PlayerMgr::GetInstance()->mCustomWin.Push(pCustomInfo);
				}
				// 结算闲家排序(默认顺时针)
				pSceneGame->doSortCustomInfo(&customVec,true);
				// 筹码结算动画
				// Cool.Cat
				//pSceneGame->showAnimateSettleAccounts();
				pSceneGame->showAnimateSettleAccountsFinal();

				SIXLog("牌局结束！");
			}
			break;
		}
	}
}

void SIX_ClientRoom::HandlePacketMatch(int iSubCode,unsigned char *pData,int iDataLen)
{

}

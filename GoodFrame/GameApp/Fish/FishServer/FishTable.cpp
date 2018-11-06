
#include "./PublicHead.h"
#include "./EndlessLoopGuard.h"	// 死循环守护
#include "./FishTable.h"
#include "./IRoomMgr.h"
#include "./EasyDataTime.h"//add by Ivan_han 20130612
#include "./TimeInterval.h"

CFishTable::CFishTable(void)
{
	//CTimeInterval timeInterval(true, __FUNCTION__);

	m_stFishTraceMgr.set_fish_table(this);
	m_stBulletMgr.set_fish_table(this);
	m_stAwardPool.set_fish_table(this);
	//m_stAwardPool.Init(10000,8000,1000,0);

	//CTabFishItem *m_pFishLocalInfo=(CTabFishItem *)CTabFishCache::Instance().Find(2);
    //double mu=PoolAndFish::Instance().m_mu;
	memset(m_gameUserInfo, 0, sizeof(m_gameUserInfo));
}


CFishTable::~CFishTable(void)
{
	memset(m_gameUserInfo, 0, sizeof(m_gameUserInfo));
}

void CFishTable::OnInit()
{
	// 删除所有定时器
	KillAllTimer();
	// 比赛剩余时间
	m_iMatchCountDown = 0;
	// 
	m_eGamePhase = ENUM_GAME_PHASE::ENUM_GAME_START;
}
// 删除所有定时器
void CFishTable::KillAllTimer()
{
	// 删除子弹存活定时器
	kill_table_timer(IDI_BULLET_OVERTIME); 
	// 删除操作超时定时器
	kill_table_timer(IDI_FIRE_OVERTIME);
	// 比赛倒计时定时器
	kill_table_timer(IDI_GAME_END_TIMER);
}

// 断线
int CFishTable::OnCut(LONGLONG lUserId)
{
	char szBuf[64]={0};
	sprintf(szBuf,"lUserId=%I64d 断线 ",lUserId);
	COften::OutputInfo(szBuf);
	return 0;
}

// 断线重入响应，仅仅在用用户名、密码登录房间时才会响应
int CFishTable::OnRecomeAfterCut(int iSeatNo)
{
	COften::OutputInfo("断线重入响应");
	SEAT_INFO *pSeatInfo = is_valid_seat_no(iSeatNo);
	if (pSeatInfo && pSeatInfo->pSingleUser)
	{
		if (m_gameUserInfo[iSeatNo].lUserID!=pSeatInfo->pSingleUser->get_user_id())
		{// 重入用户错误
			return -1;
		}
		m_gameUserInfo[iSeatNo].bExit = true;;
		// 用户数据改变
		CMD_SC_RECOMEAFTERCUT recomeAfterCut;
		recomeAfterCut.lUserId = m_gameUserInfo[iSeatNo].lUserID;
		recomeAfterCut.lGoldChange = pSeatInfo->pSingleUser->get_gold_login()-m_gameUserInfo[iSeatNo].lGoldChange;
		recomeAfterCut.lPointChange = pSeatInfo->pSingleUser->get_point_login()-m_gameUserInfo[iSeatNo].lPointChange;

		send_game_data(pSeatInfo->pSingleUser->get_channel(),TABLE_MAIN, TABLE_SUB_RECOMEAFTERCUT, (BYTE*)&recomeAfterCut, sizeof(CMD_SC_RECOMEAFTERCUT));

		// 标志有开火操作
		pSeatInfo->bWarning = false;											
		pSeatInfo->nOperateTime = (unsigned int)time(NULL);
		return 0;
	}
}

// 响应桌子消息
void CFishTable::OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// 自动归池信号

	int iRes = 0;
	int iErr = 0;

	switch(iSubCode)
	{
	case TABLE_SUB_FIRE:	// 开火
		{
			if (m_iGameSysState != GAME_SYS_STATE_RUNING)
			{
				return;
			}
			assert(iDataLen==sizeof(SHOT_FIRE));
			if (sizeof(SHOT_FIRE)!=iDataLen)
			{
				return;
			}

			SHOT_FIRE* pReal = (SHOT_FIRE*)pData;
			if (NULL != pReal)
			{
				fire(iSeatNo, pReal);
			}
			break;
		}
	case TABLE_SUB_REFLECTION:	// 子弹反射
		{
			if (m_iGameSysState != GAME_SYS_STATE_RUNING)
			{
				return;
			}
			assert(iDataLen==sizeof(BULLET_REFLECTION));
			if (sizeof(BULLET_REFLECTION)!=iDataLen)
			{
				return;
			}

			BULLET_REFLECTION* pReal = (BULLET_REFLECTION *)pData;
			if (NULL != pReal)
			{
				BulletReflection(iSeatNo, pReal);
			}
			break;
		}
	case TABLE_SUB_CAPTURE_FISH:	// 捕获鱼
		{
			if (m_iGameSysState != GAME_SYS_STATE_RUNING)
			{
				return;
			}
			assert(iDataLen==sizeof(CAPTURE_FISH));
			if (sizeof(CAPTURE_FISH)!=iDataLen)
			{
				return;
			}

			CAPTURE_FISH* pReal = (CAPTURE_FISH *)pData;
			if (NULL != pReal)
			{
				CaptureFish(iSeatNo, pReal);
			}
			break;
		}
	case ROOM_SUB_MY_TEST:	// 测试
		{
			break;
		}
	case TABLE_SUB_BUY_BULLET: // 购买子弹
		{
			assert(iDataLen==sizeof(USER_BUY_BULLET));
			if (sizeof(USER_BUY_BULLET)!=iDataLen)
			{
				return;
			}

			USER_BUY_BULLET * pBuyBullet = (USER_BUY_BULLET*)pData;
			if (NULL!=pBuyBullet)
			{
				UserBuyBullet(iSeatNo, pBuyBullet);
			}
			break;
		}
	//add by Ivan_han 20130724
	case REQ_SET_GUNGRADE:
		{
			assert(iDataLen==sizeof(Req_SetGunGrade));
			if (sizeof(Req_SetGunGrade)!=iDataLen)
			{
				return;
			}

			Req_SetGunGrade * pReq = (Req_SetGunGrade*)pData;
			if (NULL!=pReq)
			{
				UserSetGunGrade(iSeatNo, pReq);
			}
			break;
		}
	}
}

// 桌子定时器响应
int CFishTable::OnTableTimer(int iTableNo, int iIDEvent)
{
#if 0	// 测试用
	static LONGLONG lCount = 0;
	DWORD dwThreadId = GetCurrentThreadId();
	long long lStartTime = GetTickCount64();
	printf("iTableNo=%d, iIDEvent=%d, lCount=%I64d, dwThreadId=%d, lStartTime=%I64d \n", 
		iTableNo, iIDEvent, lCount++, dwThreadId, lStartTime);
#endif

	if (iTableNo !=  m_stTableInfo.iTableNo)
		return 0;

	srand((unsigned int)time(NULL));

	switch(iIDEvent)
	{
	case IDI_Adjust_Vh:
	case IDI_Adjust_Vl:
		{
			m_stAwardPool.OnTableTimer(iTableNo,iIDEvent);			
		}
		break;
	case IDI_STATUS:
		{
			//m_StatusManager.OnTimerMessage(wTimerID,wBindParam);
			break;
		}
	case IDI_AWARD_POOL_SAVE:
		{
			//SaveToDB();

			break;
		}
	case IDI_FIRE_OVERTIME:
		{// 操作发射子弹超时
			OnCheckOverTime();
			break;
		}
	case IDI_GAME_END_TIMER:
		{// 比赛倒计时
			if (ROOM_GAME_TYPE_MATCH==m_pRoomMgr->get_server_room_info().iRoomType)
			{
				m_iMatchCountDown--;
				if (m_iMatchCountDown<=0)
				{
					OnMatchEnd();
					break;
				}
				else
				{
					CMD_SC_MATCH_COUNTDOWN countDown;
					countDown.iMatchCountDown = m_iMatchCountDown;
					send_table_data(MATCH_MAIN, MATCH_SUB_SC_MATCH_COUNTDOWN, (BYTE*)(&countDown), sizeof(CMD_SC_MATCH_COUNTDOWN));
					break;
				}
				bool bIsMatchEnd = true;
				for (int i=0;i<GAME_PLAYER_COUNT;++i)
				{
					if (m_gameUserInfo[i].bExit)
					{
						bIsMatchEnd=false;
						break;
					}
				}
				if (bIsMatchEnd)
				{// 所有用户没有子弹则结束游戏
					COften::OutputInfo("全部用户退出，比赛游戏结束");
					// 比赛结束
					OnMatchEnd();
					break;
				}
				break;
			}
		}
	case IDI_BULLET_OVERTIME:
		{// 检查子弹是否有没删除的
			m_stBulletMgr.CheckBulletOverTime();
			break;
		}
	default:
		return  m_stFishTraceMgr.OnTableTimer(iTableNo,iIDEvent);	
	}
	return 0;
}

//游戏开始
int CFishTable::OnGameBegin()
{
	COften::OutputInfo("游戏开始！");
	// 游戏开始初始化
	OnInit();

	m_stFishTraceMgr.OnGameBegin();
	m_stAwardPool.OnGameBegin();

	// 设置子弹存活时间
	set_table_timer(IDI_BULLET_OVERTIME, TIME_BULLET_OVERTIME);
	// 设置操作超时定时器 (超过预定时间未发射子弹则踢出玩家)		add by cxf
	set_table_timer(IDI_FIRE_OVERTIME, TIME_FIRE_OVERTIME);
	// 设置结束游戏定时器
	if (ROOM_GAME_TYPE_MATCH==m_pRoomMgr->get_server_room_info().iRoomType)
	{// 比赛场
		m_iMatchCountDown = m_pRoomMgr->get_server_room_info().iGameTime;
		if (m_iMatchCountDown>0)
		{
			set_table_timer(IDI_GAME_END_TIMER, 1000);	// 每一秒钟检查是否比赛结束
		}
	}

	return 0;
}

// 比赛场初始化用户信息
void CFishTable::OnSitDownInit(int iSeatNo)
{
	CSingleUser *pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{// 无此用户
		return;
	}

	// 清空子弹
	m_stBulletMgr.ClearBullet( pSingleUser->get_user_id() );

	memset(&m_gameUserInfo[iSeatNo], 0, sizeof(CMD_GameUserInfo));
	m_gameUserInfo[iSeatNo].bExit = true;
	m_gameUserInfo[iSeatNo].lUserID = pSingleUser->get_user_id();			// 用户ID
	pSingleUser->get_name(m_gameUserInfo[iSeatNo].szName, USER_NAME_LEN);	// 用户名
	memcpy(m_gameUserInfo[iSeatNo].szNickname, pSingleUser->get_user_info_sim().szNickname,USER_NAME_LEN ); // 昵称
	m_gameUserInfo[iSeatNo].iBulletCount = 0;	// 子弹数量
	m_gameUserInfo[iSeatNo].lGameCoin = 0;		// 鱼币
	m_gameUserInfo[iSeatNo].lGoldChange = 0;	// 当前改动金币
	m_gameUserInfo[iSeatNo].lPointChange = 0;	// 当前改动积分
	m_gameUserInfo[iSeatNo].lCurrentTime = (long long)time(NULL);

	m_gameUserInfo[iSeatNo].lAntiAddictionTime = pSingleUser->get_user_info().lAntiAddictionTime;
	m_gameUserInfo[iSeatNo].lAntiAddictionPlayTime = pSingleUser->get_user_info().lAntiAddictionPlayTime;
}
// 举手
int CFishTable::OnRaiseHand(int iSeatNo)
{
	COften::OutputInfo("举手！");
#if USESLEEP
	//模拟外网C->S的ε'
	srand(time(0));
	int ms=rand()%4000+2000;
	Sleep(ms);
#endif
	CSingleUser* pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{
		COften::OutputInfo("举手用户不存在！");
		return 0;
	}

	// 设置场景
	int iScenesID=SCENES_MIN;
	if (SCENES_MIN <= m_stTableInfo.iScenesID  &&  SCENES_MAX >= m_stTableInfo.iScenesID)
	{
		iScenesID=m_stTableInfo.iScenesID;
	}

	// 当前时间 - 已经运行时间 = 服务器开机日历时刻（常量SK）
	ULONGLONG ullRunTime = CFishTable::GetTickCount64();
	ULONGLONG ullRunTime1 = CEasyDataTime::get_current_time_diff_millitm_from_1970();
	ULONGLONG tStartComputerTime =ullRunTime1 - ullRunTime;//SK

	#if USESLEEP
			//模拟外网S->C的ε
			Sleep(ms);
	#endif

	INIT_GAME stInitGame;
	stInitGame.iScenesID = iScenesID;
	stInitGame.tServerTime = tStartComputerTime;
	stInitGame.tCurrentServerTime = ullRunTime1;
	stInitGame.uiBulletMaxCount = m_stBulletMgr.GetBulletMaxCount();
	send_data(iSeatNo, TABLE_MAIN, TABLE_SUB_INIT_GAME, (BYTE*)&stInitGame, sizeof(INIT_GAME));


	//add by Ivan_han 20130814
	if(pSingleUser->get_seat_no()>=0 && pSingleUser->get_seat_no()<GAME_PLAYER_COUNT)
	{
		PlayerFactorInfo *pPlayerFactorInfo=&(m_stAwardPool.m_GameFactorsMgr.m_PlayerFactorInfo[pSingleUser->get_seat_no()]);
		if(pPlayerFactorInfo!=NULL)
		{
			EASY_DATA_TIME	stRegistTime;
			memcpy(&stRegistTime,&(pSingleUser->get_user_info().stRegistTime),sizeof(stRegistTime));
			CEasyDataTime RegisterTime;
			int ret=RegisterTime.set_date_time(stRegistTime);
			CEasyDataTime dt1970;

			long TimeZone=0;
			int ret1=_get_timezone(&TimeZone);//在调用localtime之后再调用_get_timezone，输出参数为负数，否则输出参数为正数
			TimeZone=-TimeZone;
			int h=TimeZone/3600;
			int m=(TimeZone%3600)/60;
			int s=(TimeZone%3600)%60;

			int ret2=dt1970.set_date_time(1970,1,1,h,m,s);
			int ret3=RegisterTime.compare(dt1970,pPlayerFactorInfo->m_PlayerNewFlagInfo.m_PlayerRegisterTime);

			pPlayerFactorInfo->m_PlayerGameTimeInfo.m_PlayerBeginGameTime=ullRunTime1;
		}
	}

	//add by Ivan_han 20130819
	vector<SEAT_INFO*>::iterator it=m_vecSeatInfo.begin();
	for (;it!=m_vecSeatInfo.end();++it)
	{
		SEAT_INFO *seatInfo = (SEAT_INFO*)*it;
		if (NULL==seatInfo)
		{// 椅子不存在
			continue;
		}
		if (!seatInfo->pSingleUser)
		{// 用户不存在
			continue;
		}

		if (pSingleUser==seatInfo->pSingleUser)
		{// 举手者自己
			continue;
		}

		PlayerFactorInfo *pPlayerFactorInfo=&(m_stAwardPool.m_GameFactorsMgr.m_PlayerFactorInfo[seatInfo->pSingleUser->get_seat_no()]);
		if(pPlayerFactorInfo!=NULL)
		{
			Req_SetGunGrade rsp;
			rsp.llUserID = seatInfo->pSingleUser->get_user_id();
			rsp.GunGrade =pPlayerFactorInfo->m_PlayerCannonGradeInfo.m_CannonGrade;
			send_data(iSeatNo,TABLE_MAIN, RSP_SET_GUNGRADE, (BYTE*)&rsp, sizeof(rsp));
		}
	}

	m_stFishTraceMgr.OnRaiseHand(iSeatNo);

	// 子弹发给刚举手的玩家
	m_stBulletMgr.ShootAllBullet( iSeatNo );

	return 0;
}

// 离座之前
int CFishTable::OnLeaveSeatBefore( LONGLONG lUserId,int iSeatNo)
{
	// 玩家退出子弹清空
	m_stBulletMgr.ClearBullet( lUserId );

	// 写分
	OnAccounts(iSeatNo);
	return 0;
}

// 离座之后
int CFishTable::OnLeaveSeatLast(int iSeatNo)
{
	// 标志用户离座
	m_gameUserInfo[iSeatNo].bExit = false;

	// 离座后检查是否结束游戏
	can_finish_game();

	return 0;
}

//游戏结束
int CFishTable::OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	COften::OutputInfo("桌子游戏结束");

	m_stFishTraceMgr.OnGameFinish(bDeskStation,bCloseFlag);
	m_stAwardPool.OnGameFinish(bDeskStation,bCloseFlag);
	// 删除所有定时器
	KillAllTimer();
	// 游戏结束初始化
	OnInit();

	return 0;
}

unsigned long long CFishTable::GetTickCount64()
{
#if 0
	return ::GetTickCount64();
#else
	//此时假定客户端的服务器时刻是1970年
	return CEasyDataTime::get_current_time_diff_millitm_from_1970();
#endif
}

/* --------------------------------------------------------------------------
函数说明：开火
传入参数：
	iSeatNo		座位
传出参数：
	pMsgBlock	消息块
	pUserInfo	用户参数
返回值：
    参考 TASK_MSG_RESULT 枚举
--------------------------------------------------------------------------*/
int CFishTable::fire(int iSeatNo, SHOT_FIRE* pReal)
{
	SEAT_INFO* pSeat = NULL;
	SHOT_FIRE Data;
	memcpy(&Data, pReal, sizeof(SHOT_FIRE));
	int iRet = Check(&pSeat, iSeatNo);
	if (0!=iRet)
	{
		return -1;
	}
	Data.iTableNo = m_stTableInfo.iTableNo;
	Data.iSeatNo = iSeatNo;

	if ( m_stBulletMgr.GetBulletMaxCount() <= m_stBulletMgr.GetBulletCount( pReal->iUserID ))
	{
		char szBuf[64]={0};
		sprintf(szBuf,"子弹数量超过最大数量,子弹数量=", m_stBulletMgr.GetBulletCount( pReal->iUserID ));
		COften::OutputInfo(szBuf);
		// 子弹超过最大数目
		Data.iRes = 50;
	}
	
	if(0==Data.iRes )
	{
		// 用户子弹处理   
		CSingleUser * pSingleUse = get_SingleUser_by_seatNo(iSeatNo);
		if (!pSingleUse)
		{
			char szBuf[64]={0};
			sprintf(szBuf,"开火用户不存在,椅子ID=", iSeatNo);
			COften::OutputError(szBuf);
			return 0;
		}
		long long lUserID = pSingleUse->get_user_id();

		if (m_gameUserInfo[iSeatNo].iBulletCount < Data.iBulletNum )
		{// 用户子弹不够
			m_stBulletMgr.RemoveBullet( Data.iID ); // 删除无效子弹
			Data.iRes = RET_GAME_ERROR_CODE_BULLET_LACK;
			send_data(iSeatNo,TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&Data), sizeof(Data));

			return Data.iRes;
		}

		m_gameUserInfo[iSeatNo].iBulletCount = m_gameUserInfo[iSeatNo].iBulletCount-Data.iBulletNum;
		// 更新操作时间
		pSeat->bWarning = false;											// 标志有开火操作
		pSeat->nOperateTime = (unsigned int)time(NULL);						// 开火时间
		Data.iUserBulletCount = m_gameUserInfo[iSeatNo].iBulletCount;		// 子弹总数
		m_stBulletMgr.addBullet( pReal );

		// 广播
		broadcast_raise_hand(TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&Data), sizeof(Data));

		m_stAwardPool.Put(Data.iBulletNum);

		//当子弹不足当前倍率时，自动降低到最适宜倍率，add by Ivan_han 20130827
		if(Data.iUserBulletCount>0 && Data.iUserBulletCount<Data.iBulletNum)
		{
			PlayerFactorInfo *pPlayerFactorInfo=&(m_stAwardPool.m_GameFactorsMgr.m_PlayerFactorInfo[iSeatNo]);
			if(pPlayerFactorInfo!=NULL)
			{
				pPlayerFactorInfo->m_PlayerCannonGradeInfo.m_CannonGrade=Data.iUserBulletCount;
				Req_SetGunGrade rsp;
				rsp.llUserID =lUserID;
				rsp.GunGrade =pPlayerFactorInfo->m_PlayerCannonGradeInfo.m_CannonGrade;
				broadcast_raise_hand(TABLE_MAIN, RSP_SET_GUNGRADE, (BYTE*)(&rsp), sizeof(Req_SetGunGrade));
			}
		}
	}
	return Data.iRes;
}

/// 子弹反射
int CFishTable::BulletReflection(int iSeatNo, BULLET_REFLECTION* pReal)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	SEAT_INFO* pSeat = NULL;
	BULLET_REFLECTION Data;
	memcpy(&Data, pReal, sizeof(BULLET_REFLECTION));
	int iRet = Check(&pSeat, iSeatNo);
	if (0!=iRet)
	{
		return -1;
	}
	// 检查子弹  // add by cxf
	TGunGrade GunGrade = m_stBulletMgr.IsExistBullet(Data.llID);
	if(!GunGrade)
	{// 子弹不存在
		char szBuf[64]={0};
		sprintf(szBuf,"反射子弹不存在,子弹ID=%d", Data.llID);
		COften::OutputInfo(szBuf);
		Data.iRes = -10;
	}
	else
	{// 子弹反射
		BOOL bCanReflection = m_stBulletMgr.ReflectionBullet( pReal );
		Data.iReflectionMax = pReal->iReflectionMax;
		Data.iReflectionCount = pReal->iReflectionCount;
		if (!bCanReflection )
		{
			Data.iRes = 10;		// 子弹超过反弹次数或子弹不存在
			m_stBulletMgr.RemoveBullet( pReal->llID );
		}
	}

	if(0==Data.iRes )
	{
		broadcast_raise_hand(TABLE_MAIN, TABLE_SUB_REFLECTION, (BYTE*)(&Data), sizeof(Data));
	}

	return Data.iRes;
}

/// 捕获鱼
int CFishTable::CaptureFish(int iSeatNo, CAPTURE_FISH* pReal)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	SEAT_INFO* pSeat = NULL;
	CAPTURE_FISH Data = *pReal;
	int iRet = Check(&pSeat, iSeatNo);
	if (0!=iRet)
	{
		return -1;
	}

	// 检查子弹  // add by cxf
	TGunGrade GunGrade = m_stBulletMgr.IsExistBullet(Data.llBulletID);
	if(!GunGrade)
	{// 子弹不存在
		char szBuf[64]={0};
		sprintf(szBuf,"捕获鱼子弹不存在,子弹ID=%d", Data.llBulletID);
		COften::OutputInfo(szBuf);
		Data.iRes = -10;
	}

	//非法数据，add by Ivan_han 20130723
	if(pReal->nFishCount>12||pReal->nFishCount<1)
	{
		char szBuf[64]={0};
		sprintf(szBuf,"碰撞鱼的数量不合法,数量=%d", pReal->nFishCount);
		COften::OutputError(szBuf);
		Data.iRes = -20;
	}

	if(0==Data.iRes )
	{
		//add by Ivan_han 20130607
		// 解析鱼ID
		vector<TFishID> vFishID(pReal->FishIDs,pReal->FishIDs+pReal->nFishCount);
		vector<TFishID> vDeadFishID;
		int iFeats = 0;		// 功勋
		//在这里调用奖池模块的代码
	#if 1
		vector<TFishNumOfAck> vFishNumOfAck;
		vector<TFishKind> retFishKinds=m_stFishTraceMgr.GetFishKinds(vFishID,vFishNumOfAck);
		TFallIntegral retG=m_stAwardPool.m_GameFactorsMgr.OnAttackSettlement(iSeatNo,vFishID,retFishKinds,vFishNumOfAck,vDeadFishID,GunGrade, iFeats);
		Data.FallIntegral=retG;
		m_stFishTraceMgr.UpdateSomeFishTrace(vFishID,vDeadFishID);
	#else
		vDeadFishID.insert(vDeadFishID.begin(),vFishID.begin(),vFishID.end());
	#endif

		if (pSeat->pSingleUser && retG > 0)
		{// 修改鱼币
			m_gameUserInfo[iSeatNo].lGameCoin += (int)retG;
			if (ROOM_GAME_TYPE_GOLD==m_pRoomMgr->get_server_room_info().iRoomType)
			{// 金币场才有功勋
				m_gameUserInfo[iSeatNo].iFeats += iFeats;
			}
		}

		Data.llUserGameCoinCount = m_gameUserInfo[iSeatNo].lGameCoin;	// 用户当然鱼币数量
		vector<TFishKind> vDeadFishKind;
		TFishID DeadFullScreenBombFishID=0;
		vector<TFishID> vDeadFishID1=m_stFishTraceMgr.DestroySomeFishTrace(vDeadFishID,vDeadFishKind,DeadFullScreenBombFishID);	
		CAPTURE_FISH_MAX real;
		memcpy(&real,&Data,sizeof(CAPTURE_FISH));
		real.SetData(vDeadFishID1);
		real.DeadFullScreenBombFishID=DeadFullScreenBombFishID;
		//printf("死鱼条数：%d，实际发送长度：%d\n",real.nDeadFishCount,real.getLength());

		//add by Ivan_han 20130810
		TWinIntegral WinIntegral=m_gameUserInfo[iSeatNo].lGameCoin+m_gameUserInfo[iSeatNo].iBulletCount-m_gameUserInfo[iSeatNo].iBuyBulletCount/*pSeat->pSingleUser->get_gold_change()*m_pRoomMgr->m_stServerRoomInfo.iBasePoint*/;
		//printf("玩家座位号：%d，输赢渔币：%I64d\n",pSeat->iSeatNo,WinIntegral);
		//add by Ivan_han 20130814
		unsigned long long Now=GetTickCount64();
		PlayerFactorInfo *pPlayerFactorInfo=&(m_stAwardPool.m_GameFactorsMgr.m_PlayerFactorInfo[iSeatNo]);
		if(pPlayerFactorInfo!=NULL)
		{
			if(Now>=pPlayerFactorInfo->m_PlayerProfitInfo.m_T+pPlayerFactorInfo->m_PlayerProfitInfo.m_dT)
			{
				pPlayerFactorInfo->m_PlayerProfitInfo.m_PlayerProfit=WinIntegral-pPlayerFactorInfo->m_PlayerProfitInfo.m_PlayerProfit;
				pPlayerFactorInfo->m_PlayerProfitInfo.m_T=Now;
			}

			if(pPlayerFactorInfo->m_PlayerNewFlagInfo.m_PlayerNewFlag)
			{
				long long now=CEasyDataTime::get_current_time_diff_second_from_1970();
				long long diff=now-pPlayerFactorInfo->m_PlayerNewFlagInfo.m_PlayerRegisterTime;
				//玩家注册时间超过24小时，玩家失去新手标示
				if(diff>3600)
					pPlayerFactorInfo->m_PlayerNewFlagInfo.m_PlayerNewFlag=false;
			}

			pPlayerFactorInfo->m_PlayerGameTimeInfo.m_PlayerGameTime=Now-pPlayerFactorInfo->m_PlayerGameTimeInfo.m_PlayerBeginGameTime;
		}

		int nCount=(int)vDeadFishKind.size();
		for(unsigned int i=0;i<nCount;i++)
		{
			int idx=CFishTable::GetIndexFromArray(vDeadFishKind[i]);
			if(idx>-1)
				real.FishKindNums[idx]+=1;
		}
		real.GunGrade=GunGrade;

		broadcast_raise_hand(TABLE_MAIN, TABLE_SUB_CAPTURE_FISH, (BYTE*)(&real),real.getLength());
	}

	m_stBulletMgr.RemoveBullet( Data.llBulletID );

	if (ROOM_GAME_TYPE_MATCH==m_pRoomMgr->get_server_room_info().iRoomType)
	{// 比赛场
		if (OnCheckAllUserBullet())
		{// 所有用户没有子弹则结束游戏
			// 比赛结束
			OnMatchEnd();
		}
	}

	return Data.iRes;
}

TBulletID CFishTable::getNewBulletID()
{
	static TBulletID BulletID=0;
	BulletID++;
	if(BulletID==0)
		BulletID++;
	return BulletID;
}

CFishTraceMgr& CFishTable::getFishTraceMgr()
{
	return m_stFishTraceMgr;
}

int CFishTable::GetIndexFromArray(TFishKind fishType)
{
	static int ARR_FISHSAMPLE[] = {1,2,3,4,5,6,7,8,9,10,15,18,20,25,30,40,12,112,113};
	static int ARR_FISHSAMPLE_COUNT = sizeof(ARR_FISHSAMPLE)/sizeof(int);

	for(int i=0;i<ARR_FISHSAMPLE_COUNT;i++)
	{
		//add by Ivan_han 20130731
		if (fishType%100==ARR_FISHSAMPLE[i])
			return i;
	}
	return -1;
}

int CFishTable::Check(SEAT_INFO** pSeatInfo, int iSeatNo)
{
	*pSeatInfo = is_valid_seat_no( iSeatNo );
	
	if( !pSeatInfo )
	{
		return 20;
	}
	else if (!(*pSeatInfo)->pSingleUser)
	{
		return 40;
	}
	else // 座位上有人
	{
		#if 0
				// 改变用户的值，用途：测试锁
				pSeatInfo->pSingleUser->change_user_test(pReal->iTestNo, m_stTableInfo.iTableNo, iSeatNo);
		#endif
		return 0;
	}
}

// 设置炮的等级
void CFishTable::UserSetGunGrade(int iSeatNo,Req_SetGunGrade * pReq)
{
	if(m_pRoomMgr==NULL)
	{// 房间错误
		return;
	}
	Req_SetGunGrade rsp;
	rsp.iRes = RET_GAME_OPERATE_SUCCEED;				//成功标志
	rsp.llUserID = pReq->llUserID;				// 用户ID
	rsp.GunGrade=(pReq->GunGrade>20||pReq->GunGrade<1)?1:pReq->GunGrade;

	CSingleUser* pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{// 用户不存在
		rsp.iRes = RET_GAME_USER_NOT_EXIST;
	}

	if (RET_GAME_OPERATE_SUCCEED == rsp.iRes)
	{// 正确
		broadcast_raise_hand(TABLE_MAIN, RSP_SET_GUNGRADE, (BYTE*)(&rsp), sizeof(Req_SetGunGrade));
		//add by Ivan_han 20130819
		PlayerFactorInfo *pPlayerFactorInfo=&(m_stAwardPool.m_GameFactorsMgr.m_PlayerFactorInfo[iSeatNo]);
		if(pPlayerFactorInfo!=NULL)
		{
			pPlayerFactorInfo->m_PlayerCannonGradeInfo.m_CannonGrade=rsp.GunGrade;
		}
	}
	else
	{// 错误
		send_data(iSeatNo,TABLE_MAIN, RSP_SET_GUNGRADE, (BYTE*)(&rsp), sizeof(Req_SetGunGrade));
	}
}

// 购买子弹
void CFishTable::UserBuyBullet(int iSeatNo, USER_BUY_BULLET * userBuyBullet)
{
	if(m_pRoomMgr==NULL)
	{// 房间错误
		return;
	}
	long long iRoomType = m_pRoomMgr->get_server_room_info().iRoomType;		// 游戏类型(1:积分场;2:金币场;3:比赛场)

	if (ROOM_GAME_TYPE_MATCH==iRoomType)
	{// 比赛场不可以购买子弹
		return;
	}

	USER_BUY_BULLET_RET buyBulletRet;
	buyBulletRet.iRes = RET_GAME_OPERATE_SUCCEED;					// 购买成功标志
	buyBulletRet.llUserID = userBuyBullet->llUserID;				// 用户ID
	buyBulletRet.iSeatNo = iSeatNo;									// 椅子号

	CSingleUser* pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{// 用户不存在
		buyBulletRet.iRes = RET_GAME_USER_NOT_EXIST;
	}
	long long llGold = pSingleUser->get_gold_login();			// 用户当前金币
	int iBasePoint = m_pRoomMgr->get_server_room_info().iBasePoint;			// 当前房间倍率
	if (ROOM_GAME_TYPE_GOLD==iRoomType)
	{// 金币场
		if ((userBuyBullet->iBulletNum * iBasePoint) > llGold )
		{// 本身金币不够够买此数量子弹
			buyBulletRet.iRes = RET_GAME_BUY_BULLET_GOLD_LACK;
		}
	}

	if (RET_GAME_OPERATE_SUCCEED == buyBulletRet.iRes)
	{// 购买子弹
		m_gameUserInfo[iSeatNo].iBuyBulletCount += userBuyBullet->iBulletNum;				// 购买子弹数量
		m_gameUserInfo[iSeatNo].iBulletCount += userBuyBullet->iBulletNum;					// 增加购买子弹数量
		buyBulletRet.iBulletNum = userBuyBullet->iBulletNum;								// 购买数量
		if (ROOM_GAME_TYPE_GOLD==iRoomType)
		{// 金币场
			m_gameUserInfo[iSeatNo].lGoldChange += (-(userBuyBullet->iBulletNum * iBasePoint));	// 添加购买所需金币
		}
		else if(ROOM_GAME_TYPE_POINT==iRoomType)
		{// 积分场
			m_gameUserInfo[iSeatNo].lPointChange += (-(userBuyBullet->iBulletNum * iBasePoint));	// 添加购买所需金币
		}

		buyBulletRet.llGold = pSingleUser->get_gold_login() + m_gameUserInfo[iSeatNo].lGoldChange;		// 自身金币
		buyBulletRet.llPoint = pSingleUser->get_point_login() + m_gameUserInfo[iSeatNo].lPointChange;	// 自身积分

		send_table_data(TABLE_MAIN, TABLE_SUB_BUY_BULLET_RET, (BYTE*)(&buyBulletRet), sizeof(USER_BUY_BULLET_RET));
	}
	else
	{// 子弹购买错误
		send_data(iSeatNo,TABLE_MAIN, TABLE_SUB_BUY_BULLET_RET, (BYTE*)(&buyBulletRet), sizeof(USER_BUY_BULLET_RET));
	}
}

// 检查超时退出桌子 add by cxf
void CFishTable::OnCheckOverTime()
{
	if (GAME_SYS_STATE_RUNING!=m_iGameSysState)
	{// 游戏未开始不踢人
		return;
	}

	if (ROOM_GAME_TYPE_MATCH==m_pRoomMgr->get_server_room_info().iRoomType)
	{// 比赛游戏不踢人
		return;
	}

	vector<SEAT_INFO*>::iterator it = m_vecSeatInfo.begin();
	for (;it!=m_vecSeatInfo.end();++it)
	{
		SEAT_INFO * seatInfo = *it;
		if (!seatInfo->pSingleUser)
		{// 桌子没坐人
			continue;
		}

		LONGLONG llChannel = seatInfo->pSingleUser->get_channel();
		unsigned int nTime = (unsigned int)time(NULL) - (seatInfo->nOperateTime);
		if (nTime >= FIER_OVERTIME_TIME)
		{// 用户开火超时
			char szBuf[64]={0};
			sprintf(szBuf,"开火超时踢出,UserId=%d; 子弹数量=%d ",seatInfo->pSingleUser->get_user_id(), m_stBulletMgr.GetBulletCount(seatInfo->pSingleUser->get_user_id()));
			COften::OutputInfo(szBuf);
			m_pRoomMgr->OnKickOutUser(llChannel);							// 退出用户
		}
		else if (!seatInfo->bWarning && nTime >= FIER_OVERTIME_WARNING_TIME)
		{
			seatInfo->bWarning = true;
			USER_OVERTIME_SURPLUS surplus;
			surplus.iSurplusTime = 15;
			send_game_data(llChannel,TABLE_MAIN,TABLE_SUB_USER_OVERTIME, (BYTE *)&surplus, sizeof(USER_OVERTIME_SURPLUS));		// 用户超时没开火
		}
	}
}

// 检查用户子弹是否还有
bool CFishTable::OnCheckAllUserBullet()
{
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		int iBulletCount = m_gameUserInfo[i].iBulletCount;
		if (iBulletCount>0)
		{// 玩家还有子弹
			return false;
		}
	}
	return true;
}

// 比赛名次排序
void CFishTable::SortMatch(CMD_GameUserInfo matchUserInfo[])
{
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		for (int j=i+1;j<GAME_PLAYER_COUNT;++j)
		{
			if (matchUserInfo[i].lGameCoin<matchUserInfo[j].lGameCoin)
			{// 鱼币算排名
				CMD_GameUserInfo matchInfo;
				matchInfo = matchUserInfo[i];
				matchUserInfo[i] = matchUserInfo[j];
				matchUserInfo[j] = matchInfo;
			}
			else if(matchUserInfo[i].lGameCoin==matchUserInfo[j].lGameCoin)
			{// 打的鱼币相等
				if (matchUserInfo[i].iBulletCount<matchUserInfo[j].iBulletCount)
				{// 子弹数量算排名
					CMD_GameUserInfo matchInfo;
					matchInfo = matchUserInfo[i];
					matchUserInfo[i] = matchUserInfo[j];
					matchUserInfo[j] = matchInfo;
				}
				else if(matchUserInfo[i].lUserID<matchUserInfo[j].lUserID)
				{// 用户ID 算排名
					CMD_GameUserInfo matchInfo;
					matchInfo = matchUserInfo[i];
					matchUserInfo[i] = matchUserInfo[j];
					matchUserInfo[j] = matchInfo;
				}
			}
		}
	}
}

// 收取台费 和赠送子弹
void CFishTable::TradeFee()
{
	if (NULL==m_pRoomMgr)
	{// 房间错误
		return;
	}

	int iEnterTradeGold		= m_pRoomMgr->get_server_room_info().iEnterTradeGold;			// 进入扣除金币
	int iEnterTradePoint	= m_pRoomMgr->get_server_room_info().iEnterTradePoint;			// 进入扣除积分
	int iEnterPresentBullet	= m_pRoomMgr->get_server_room_info().iEnterPresentBullet;		// 开始赠送子弹

	if (0==iEnterTradeGold&&0==iEnterTradePoint&&0==iEnterPresentBullet)
	{
		return;
	}

	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		if (0==m_gameUserInfo[i].lUserID)
		{
			continue;
		}

		m_gameUserInfo[i].lGoldChange += (-iEnterTradeGold);	// 进入扣除金币
		m_gameUserInfo[i].lPointChange += (-iEnterTradePoint);	// 进入扣除积分
		m_gameUserInfo[i].iBulletCount += iEnterPresentBullet;	// 进入赠送子弹数量

		if (iEnterTradeGold!=0 || iEnterTradePoint!=0 || iEnterPresentBullet!=0)
		{
			// 用户数据改变
			CMD_SC_USER_DATA_CHANGE userInfoChange;
			userInfoChange.lUserId = m_gameUserInfo[i].lUserID;
			userInfoChange.iGold = -iEnterTradeGold;
			userInfoChange.iPoint = -iEnterTradePoint;
			send_table_data(TABLE_MAIN, TABLE_SUB_USER_DATA_CHANGE, (BYTE*)&userInfoChange, sizeof(CMD_SC_USER_DATA_CHANGE));
		}
	}
}

// 用户坐下
void CFishTable::OnUserSitDown(int iSeatNo)
{
	// 初始化用户游戏信息
	OnSitDownInit(iSeatNo);
}

// 比赛结束
void CFishTable::OnMatchEnd()
{
	if (m_eGamePhase!=ENUM_GAME_PHASE::ENUM_GAME_START)
	{
		return;
	}
	m_eGamePhase = ENUM_GAME_PHASE::ENUM_GAME_END;

	kill_table_timer(IDI_GAME_END_TIMER);// 比赛倒计时

	CMD_GameUserInfo matchInfo[GAME_PLAYER_COUNT];
	memcpy(matchInfo, m_gameUserInfo, sizeof(matchInfo));
	// 比赛排名
	SortMatch(matchInfo);

	CMD_MatchEnd matchEnd;
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{// 设置发送结算包
		matchEnd.lUserID[i] = matchInfo[i].lUserID;
		memcpy(matchEnd.szName[i], matchInfo[i].szName, USER_NAME_LEN);
		memcpy(matchEnd.szNickname[i], matchInfo[i].szNickname, USER_NAME_LEN);
		matchEnd.lGameCoin[i] = matchInfo[i].lGameCoin;
		matchEnd.lGoldChange[i] = matchInfo[i].lGoldChange;
		matchEnd.lPointChange[i] = matchInfo[i].lPointChange;
	}
	matchEnd.iRewardGold[0] = m_pRoomMgr->get_server_room_info().iRewardGold1;		// 第一名奖励
	matchEnd.iRewardGold[1] = m_pRoomMgr->get_server_room_info().iRewardGold2;		// 第二名奖励

	// 广播桌子游戏结束
	send_table_data(MATCH_MAIN, MATCH_SUB_SC_GAME_END, (BYTE *)&matchEnd, sizeof(CMD_MatchEnd));

	// 写如比赛
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		if (matchEnd.lUserID[i] < 1)
		{// 用户不存在
			continue;
		}
		
		CMD_MatchAccounts matchAccount;
		matchAccount.lGold = matchEnd.lGoldChange[i];			// 变动金币
		matchAccount.lPoint = matchEnd.lPointChange[i];			// 变动积分 
		matchAccount.lGameCoin = matchEnd.lGameCoin[i];			// 鱼币
		matchAccount.iRewardGold = matchEnd.iRewardGold[i];		// 奖励

		OnUserMatchAccounts(i, matchAccount);
	}

	for (int i=0;i<m_vecSeatInfo.size();++i)
	{
		CSingleUser* pSingleUser = get_SingleUser_by_seatNo(i);
		if (NULL != pSingleUser)
		{
			m_pRoomMgr->OnKickOutUser(pSingleUser->get_channel());		// 退出用户
		}
	}

	memset(m_gameUserInfo, 0, sizeof(m_gameUserInfo));
	// 游戏结束初始化
	OnInit();
}

// 结算
int CFishTable::OnAccounts(int iSeatNo)
{
	if(!m_pRoomMgr)	
	{
		return 10;
	}

	long long iRoomType = m_pRoomMgr->get_server_room_info().iRoomType;
	if (iRoomType == ROOM_GAME_TYPE_MATCH)
	{// 比赛场不允许中途结算
		return 30;
	}

	CMD_WRITE_SCORE sendData;
	memset(&sendData, 0, sizeof(CMD_WRITE_SCORE));

	long long lGameCoin = m_gameUserInfo[iSeatNo].lGameCoin;
	int iBasePoint = m_pRoomMgr->get_server_room_info().iBasePoint;		// 房间倍率
	int iBulletCount = m_gameUserInfo[iSeatNo].iBulletCount;		// 剩余子弹数量

	if (ROOM_GAME_TYPE_GOLD==iRoomType)
	{// 金币场
		sendData.lGold			= (lGameCoin * iBasePoint)+(iBulletCount * iBasePoint)+ m_gameUserInfo[iSeatNo].lGoldChange;// (鱼币*房间倍率)+(子弹数量*房间倍率)+修改金币(如:购买子弹所需金币)
	}
	else if(ROOM_GAME_TYPE_POINT==iRoomType)
	{// 积分场
		sendData.lPoint			= (lGameCoin * iBasePoint)+(iBulletCount * iBasePoint)+ m_gameUserInfo[iSeatNo].lPointChange;// (鱼币*房间倍率)+(子弹数量*房间倍率)+修改积分(如:购买子弹所需积分)
	}
	sendData.llGameCoin		= lGameCoin;													// 鱼币
	sendData.iBuyBulletCount= m_gameUserInfo[iSeatNo].iBuyBulletCount;						// 用户购买子弹数量
	sendData.iBulletCount	= iBulletCount;													// 余剩子弹
	sendData.iFeats			= m_gameUserInfo[iSeatNo].iFeats*iBasePoint;					// 功勋
	
	OnUserAccountsWrite(iSeatNo, sendData);

	// 初始化游戏用户数据
	m_gameUserInfo[iSeatNo].iBuyBulletCount = 0;
	m_gameUserInfo[iSeatNo].iBulletCount = 0;
	m_gameUserInfo[iSeatNo].iFeats = 0;
	m_gameUserInfo[iSeatNo].lGameCoin = 0;
	m_gameUserInfo[iSeatNo].lGoldChange = 0;
	m_gameUserInfo[iSeatNo].lPointChange = 0;

	return 0;
}

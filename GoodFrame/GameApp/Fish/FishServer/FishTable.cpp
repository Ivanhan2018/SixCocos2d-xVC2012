
#include "./PublicHead.h"
#include "./EndlessLoopGuard.h"	// ��ѭ���ػ�
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
	// ɾ�����ж�ʱ��
	KillAllTimer();
	// ����ʣ��ʱ��
	m_iMatchCountDown = 0;
	// 
	m_eGamePhase = ENUM_GAME_PHASE::ENUM_GAME_START;
}
// ɾ�����ж�ʱ��
void CFishTable::KillAllTimer()
{
	// ɾ���ӵ���ʱ��
	kill_table_timer(IDI_BULLET_OVERTIME); 
	// ɾ��������ʱ��ʱ��
	kill_table_timer(IDI_FIRE_OVERTIME);
	// ��������ʱ��ʱ��
	kill_table_timer(IDI_GAME_END_TIMER);
}

// ����
int CFishTable::OnCut(LONGLONG lUserId)
{
	char szBuf[64]={0};
	sprintf(szBuf,"lUserId=%I64d ���� ",lUserId);
	COften::OutputInfo(szBuf);
	return 0;
}

// ����������Ӧ�����������û����������¼����ʱ�Ż���Ӧ
int CFishTable::OnRecomeAfterCut(int iSeatNo)
{
	COften::OutputInfo("����������Ӧ");
	SEAT_INFO *pSeatInfo = is_valid_seat_no(iSeatNo);
	if (pSeatInfo && pSeatInfo->pSingleUser)
	{
		if (m_gameUserInfo[iSeatNo].lUserID!=pSeatInfo->pSingleUser->get_user_id())
		{// �����û�����
			return -1;
		}
		m_gameUserInfo[iSeatNo].bExit = true;;
		// �û����ݸı�
		CMD_SC_RECOMEAFTERCUT recomeAfterCut;
		recomeAfterCut.lUserId = m_gameUserInfo[iSeatNo].lUserID;
		recomeAfterCut.lGoldChange = pSeatInfo->pSingleUser->get_gold_login()-m_gameUserInfo[iSeatNo].lGoldChange;
		recomeAfterCut.lPointChange = pSeatInfo->pSingleUser->get_point_login()-m_gameUserInfo[iSeatNo].lPointChange;

		send_game_data(pSeatInfo->pSingleUser->get_channel(),TABLE_MAIN, TABLE_SUB_RECOMEAFTERCUT, (BYTE*)&recomeAfterCut, sizeof(CMD_SC_RECOMEAFTERCUT));

		// ��־�п������
		pSeatInfo->bWarning = false;											
		pSeatInfo->nOperateTime = (unsigned int)time(NULL);
		return 0;
	}
}

// ��Ӧ������Ϣ
void CFishTable::OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// �Զ�����ź�

	int iRes = 0;
	int iErr = 0;

	switch(iSubCode)
	{
	case TABLE_SUB_FIRE:	// ����
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
	case TABLE_SUB_REFLECTION:	// �ӵ�����
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
	case TABLE_SUB_CAPTURE_FISH:	// ������
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
	case ROOM_SUB_MY_TEST:	// ����
		{
			break;
		}
	case TABLE_SUB_BUY_BULLET: // �����ӵ�
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

// ���Ӷ�ʱ����Ӧ
int CFishTable::OnTableTimer(int iTableNo, int iIDEvent)
{
#if 0	// ������
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
		{// ���������ӵ���ʱ
			OnCheckOverTime();
			break;
		}
	case IDI_GAME_END_TIMER:
		{// ��������ʱ
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
				{// �����û�û���ӵ��������Ϸ
					COften::OutputInfo("ȫ���û��˳���������Ϸ����");
					// ��������
					OnMatchEnd();
					break;
				}
				break;
			}
		}
	case IDI_BULLET_OVERTIME:
		{// ����ӵ��Ƿ���ûɾ����
			m_stBulletMgr.CheckBulletOverTime();
			break;
		}
	default:
		return  m_stFishTraceMgr.OnTableTimer(iTableNo,iIDEvent);	
	}
	return 0;
}

//��Ϸ��ʼ
int CFishTable::OnGameBegin()
{
	COften::OutputInfo("��Ϸ��ʼ��");
	// ��Ϸ��ʼ��ʼ��
	OnInit();

	m_stFishTraceMgr.OnGameBegin();
	m_stAwardPool.OnGameBegin();

	// �����ӵ����ʱ��
	set_table_timer(IDI_BULLET_OVERTIME, TIME_BULLET_OVERTIME);
	// ���ò�����ʱ��ʱ�� (����Ԥ��ʱ��δ�����ӵ����߳����)		add by cxf
	set_table_timer(IDI_FIRE_OVERTIME, TIME_FIRE_OVERTIME);
	// ���ý�����Ϸ��ʱ��
	if (ROOM_GAME_TYPE_MATCH==m_pRoomMgr->get_server_room_info().iRoomType)
	{// ������
		m_iMatchCountDown = m_pRoomMgr->get_server_room_info().iGameTime;
		if (m_iMatchCountDown>0)
		{
			set_table_timer(IDI_GAME_END_TIMER, 1000);	// ÿһ���Ӽ���Ƿ��������
		}
	}

	return 0;
}

// ��������ʼ���û���Ϣ
void CFishTable::OnSitDownInit(int iSeatNo)
{
	CSingleUser *pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{// �޴��û�
		return;
	}

	// ����ӵ�
	m_stBulletMgr.ClearBullet( pSingleUser->get_user_id() );

	memset(&m_gameUserInfo[iSeatNo], 0, sizeof(CMD_GameUserInfo));
	m_gameUserInfo[iSeatNo].bExit = true;
	m_gameUserInfo[iSeatNo].lUserID = pSingleUser->get_user_id();			// �û�ID
	pSingleUser->get_name(m_gameUserInfo[iSeatNo].szName, USER_NAME_LEN);	// �û���
	memcpy(m_gameUserInfo[iSeatNo].szNickname, pSingleUser->get_user_info_sim().szNickname,USER_NAME_LEN ); // �ǳ�
	m_gameUserInfo[iSeatNo].iBulletCount = 0;	// �ӵ�����
	m_gameUserInfo[iSeatNo].lGameCoin = 0;		// ���
	m_gameUserInfo[iSeatNo].lGoldChange = 0;	// ��ǰ�Ķ����
	m_gameUserInfo[iSeatNo].lPointChange = 0;	// ��ǰ�Ķ�����
	m_gameUserInfo[iSeatNo].lCurrentTime = (long long)time(NULL);

	m_gameUserInfo[iSeatNo].lAntiAddictionTime = pSingleUser->get_user_info().lAntiAddictionTime;
	m_gameUserInfo[iSeatNo].lAntiAddictionPlayTime = pSingleUser->get_user_info().lAntiAddictionPlayTime;
}
// ����
int CFishTable::OnRaiseHand(int iSeatNo)
{
	COften::OutputInfo("���֣�");
#if USESLEEP
	//ģ������C->S�Ħ�'
	srand(time(0));
	int ms=rand()%4000+2000;
	Sleep(ms);
#endif
	CSingleUser* pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{
		COften::OutputInfo("�����û������ڣ�");
		return 0;
	}

	// ���ó���
	int iScenesID=SCENES_MIN;
	if (SCENES_MIN <= m_stTableInfo.iScenesID  &&  SCENES_MAX >= m_stTableInfo.iScenesID)
	{
		iScenesID=m_stTableInfo.iScenesID;
	}

	// ��ǰʱ�� - �Ѿ�����ʱ�� = ��������������ʱ�̣�����SK��
	ULONGLONG ullRunTime = CFishTable::GetTickCount64();
	ULONGLONG ullRunTime1 = CEasyDataTime::get_current_time_diff_millitm_from_1970();
	ULONGLONG tStartComputerTime =ullRunTime1 - ullRunTime;//SK

	#if USESLEEP
			//ģ������S->C�Ħ�
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
			int ret1=_get_timezone(&TimeZone);//�ڵ���localtime֮���ٵ���_get_timezone���������Ϊ�����������������Ϊ����
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
		{// ���Ӳ�����
			continue;
		}
		if (!seatInfo->pSingleUser)
		{// �û�������
			continue;
		}

		if (pSingleUser==seatInfo->pSingleUser)
		{// �������Լ�
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

	// �ӵ������վ��ֵ����
	m_stBulletMgr.ShootAllBullet( iSeatNo );

	return 0;
}

// ����֮ǰ
int CFishTable::OnLeaveSeatBefore( LONGLONG lUserId,int iSeatNo)
{
	// ����˳��ӵ����
	m_stBulletMgr.ClearBullet( lUserId );

	// д��
	OnAccounts(iSeatNo);
	return 0;
}

// ����֮��
int CFishTable::OnLeaveSeatLast(int iSeatNo)
{
	// ��־�û�����
	m_gameUserInfo[iSeatNo].bExit = false;

	// ���������Ƿ������Ϸ
	can_finish_game();

	return 0;
}

//��Ϸ����
int CFishTable::OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	COften::OutputInfo("������Ϸ����");

	m_stFishTraceMgr.OnGameFinish(bDeskStation,bCloseFlag);
	m_stAwardPool.OnGameFinish(bDeskStation,bCloseFlag);
	// ɾ�����ж�ʱ��
	KillAllTimer();
	// ��Ϸ������ʼ��
	OnInit();

	return 0;
}

unsigned long long CFishTable::GetTickCount64()
{
#if 0
	return ::GetTickCount64();
#else
	//��ʱ�ٶ��ͻ��˵ķ�����ʱ����1970��
	return CEasyDataTime::get_current_time_diff_millitm_from_1970();
#endif
}

/* --------------------------------------------------------------------------
����˵��������
���������
	iSeatNo		��λ
����������
	pMsgBlock	��Ϣ��
	pUserInfo	�û�����
����ֵ��
    �ο� TASK_MSG_RESULT ö��
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
		sprintf(szBuf,"�ӵ����������������,�ӵ�����=", m_stBulletMgr.GetBulletCount( pReal->iUserID ));
		COften::OutputInfo(szBuf);
		// �ӵ����������Ŀ
		Data.iRes = 50;
	}
	
	if(0==Data.iRes )
	{
		// �û��ӵ�����   
		CSingleUser * pSingleUse = get_SingleUser_by_seatNo(iSeatNo);
		if (!pSingleUse)
		{
			char szBuf[64]={0};
			sprintf(szBuf,"�����û�������,����ID=", iSeatNo);
			COften::OutputError(szBuf);
			return 0;
		}
		long long lUserID = pSingleUse->get_user_id();

		if (m_gameUserInfo[iSeatNo].iBulletCount < Data.iBulletNum )
		{// �û��ӵ�����
			m_stBulletMgr.RemoveBullet( Data.iID ); // ɾ����Ч�ӵ�
			Data.iRes = RET_GAME_ERROR_CODE_BULLET_LACK;
			send_data(iSeatNo,TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&Data), sizeof(Data));

			return Data.iRes;
		}

		m_gameUserInfo[iSeatNo].iBulletCount = m_gameUserInfo[iSeatNo].iBulletCount-Data.iBulletNum;
		// ���²���ʱ��
		pSeat->bWarning = false;											// ��־�п������
		pSeat->nOperateTime = (unsigned int)time(NULL);						// ����ʱ��
		Data.iUserBulletCount = m_gameUserInfo[iSeatNo].iBulletCount;		// �ӵ�����
		m_stBulletMgr.addBullet( pReal );

		// �㲥
		broadcast_raise_hand(TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&Data), sizeof(Data));

		m_stAwardPool.Put(Data.iBulletNum);

		//���ӵ����㵱ǰ����ʱ���Զ����͵������˱��ʣ�add by Ivan_han 20130827
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

/// �ӵ�����
int CFishTable::BulletReflection(int iSeatNo, BULLET_REFLECTION* pReal)
{
	// ��ѭ����⣬������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	SEAT_INFO* pSeat = NULL;
	BULLET_REFLECTION Data;
	memcpy(&Data, pReal, sizeof(BULLET_REFLECTION));
	int iRet = Check(&pSeat, iSeatNo);
	if (0!=iRet)
	{
		return -1;
	}
	// ����ӵ�  // add by cxf
	TGunGrade GunGrade = m_stBulletMgr.IsExistBullet(Data.llID);
	if(!GunGrade)
	{// �ӵ�������
		char szBuf[64]={0};
		sprintf(szBuf,"�����ӵ�������,�ӵ�ID=%d", Data.llID);
		COften::OutputInfo(szBuf);
		Data.iRes = -10;
	}
	else
	{// �ӵ�����
		BOOL bCanReflection = m_stBulletMgr.ReflectionBullet( pReal );
		Data.iReflectionMax = pReal->iReflectionMax;
		Data.iReflectionCount = pReal->iReflectionCount;
		if (!bCanReflection )
		{
			Data.iRes = 10;		// �ӵ����������������ӵ�������
			m_stBulletMgr.RemoveBullet( pReal->llID );
		}
	}

	if(0==Data.iRes )
	{
		broadcast_raise_hand(TABLE_MAIN, TABLE_SUB_REFLECTION, (BYTE*)(&Data), sizeof(Data));
	}

	return Data.iRes;
}

/// ������
int CFishTable::CaptureFish(int iSeatNo, CAPTURE_FISH* pReal)
{
	// ��ѭ����⣬������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	SEAT_INFO* pSeat = NULL;
	CAPTURE_FISH Data = *pReal;
	int iRet = Check(&pSeat, iSeatNo);
	if (0!=iRet)
	{
		return -1;
	}

	// ����ӵ�  // add by cxf
	TGunGrade GunGrade = m_stBulletMgr.IsExistBullet(Data.llBulletID);
	if(!GunGrade)
	{// �ӵ�������
		char szBuf[64]={0};
		sprintf(szBuf,"�������ӵ�������,�ӵ�ID=%d", Data.llBulletID);
		COften::OutputInfo(szBuf);
		Data.iRes = -10;
	}

	//�Ƿ����ݣ�add by Ivan_han 20130723
	if(pReal->nFishCount>12||pReal->nFishCount<1)
	{
		char szBuf[64]={0};
		sprintf(szBuf,"��ײ����������Ϸ�,����=%d", pReal->nFishCount);
		COften::OutputError(szBuf);
		Data.iRes = -20;
	}

	if(0==Data.iRes )
	{
		//add by Ivan_han 20130607
		// ������ID
		vector<TFishID> vFishID(pReal->FishIDs,pReal->FishIDs+pReal->nFishCount);
		vector<TFishID> vDeadFishID;
		int iFeats = 0;		// ��ѫ
		//��������ý���ģ��Ĵ���
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
		{// �޸����
			m_gameUserInfo[iSeatNo].lGameCoin += (int)retG;
			if (ROOM_GAME_TYPE_GOLD==m_pRoomMgr->get_server_room_info().iRoomType)
			{// ��ҳ����й�ѫ
				m_gameUserInfo[iSeatNo].iFeats += iFeats;
			}
		}

		Data.llUserGameCoinCount = m_gameUserInfo[iSeatNo].lGameCoin;	// �û���Ȼ�������
		vector<TFishKind> vDeadFishKind;
		TFishID DeadFullScreenBombFishID=0;
		vector<TFishID> vDeadFishID1=m_stFishTraceMgr.DestroySomeFishTrace(vDeadFishID,vDeadFishKind,DeadFullScreenBombFishID);	
		CAPTURE_FISH_MAX real;
		memcpy(&real,&Data,sizeof(CAPTURE_FISH));
		real.SetData(vDeadFishID1);
		real.DeadFullScreenBombFishID=DeadFullScreenBombFishID;
		//printf("����������%d��ʵ�ʷ��ͳ��ȣ�%d\n",real.nDeadFishCount,real.getLength());

		//add by Ivan_han 20130810
		TWinIntegral WinIntegral=m_gameUserInfo[iSeatNo].lGameCoin+m_gameUserInfo[iSeatNo].iBulletCount-m_gameUserInfo[iSeatNo].iBuyBulletCount/*pSeat->pSingleUser->get_gold_change()*m_pRoomMgr->m_stServerRoomInfo.iBasePoint*/;
		//printf("�����λ�ţ�%d����Ӯ��ң�%I64d\n",pSeat->iSeatNo,WinIntegral);
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
				//���ע��ʱ�䳬��24Сʱ�����ʧȥ���ֱ�ʾ
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
	{// ������
		if (OnCheckAllUserBullet())
		{// �����û�û���ӵ��������Ϸ
			// ��������
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
	else // ��λ������
	{
		#if 0
				// �ı��û���ֵ����;��������
				pSeatInfo->pSingleUser->change_user_test(pReal->iTestNo, m_stTableInfo.iTableNo, iSeatNo);
		#endif
		return 0;
	}
}

// �����ڵĵȼ�
void CFishTable::UserSetGunGrade(int iSeatNo,Req_SetGunGrade * pReq)
{
	if(m_pRoomMgr==NULL)
	{// �������
		return;
	}
	Req_SetGunGrade rsp;
	rsp.iRes = RET_GAME_OPERATE_SUCCEED;				//�ɹ���־
	rsp.llUserID = pReq->llUserID;				// �û�ID
	rsp.GunGrade=(pReq->GunGrade>20||pReq->GunGrade<1)?1:pReq->GunGrade;

	CSingleUser* pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{// �û�������
		rsp.iRes = RET_GAME_USER_NOT_EXIST;
	}

	if (RET_GAME_OPERATE_SUCCEED == rsp.iRes)
	{// ��ȷ
		broadcast_raise_hand(TABLE_MAIN, RSP_SET_GUNGRADE, (BYTE*)(&rsp), sizeof(Req_SetGunGrade));
		//add by Ivan_han 20130819
		PlayerFactorInfo *pPlayerFactorInfo=&(m_stAwardPool.m_GameFactorsMgr.m_PlayerFactorInfo[iSeatNo]);
		if(pPlayerFactorInfo!=NULL)
		{
			pPlayerFactorInfo->m_PlayerCannonGradeInfo.m_CannonGrade=rsp.GunGrade;
		}
	}
	else
	{// ����
		send_data(iSeatNo,TABLE_MAIN, RSP_SET_GUNGRADE, (BYTE*)(&rsp), sizeof(Req_SetGunGrade));
	}
}

// �����ӵ�
void CFishTable::UserBuyBullet(int iSeatNo, USER_BUY_BULLET * userBuyBullet)
{
	if(m_pRoomMgr==NULL)
	{// �������
		return;
	}
	long long iRoomType = m_pRoomMgr->get_server_room_info().iRoomType;		// ��Ϸ����(1:���ֳ�;2:��ҳ�;3:������)

	if (ROOM_GAME_TYPE_MATCH==iRoomType)
	{// �����������Թ����ӵ�
		return;
	}

	USER_BUY_BULLET_RET buyBulletRet;
	buyBulletRet.iRes = RET_GAME_OPERATE_SUCCEED;					// ����ɹ���־
	buyBulletRet.llUserID = userBuyBullet->llUserID;				// �û�ID
	buyBulletRet.iSeatNo = iSeatNo;									// ���Ӻ�

	CSingleUser* pSingleUser = get_SingleUser_by_seatNo(iSeatNo);
	if (!pSingleUser)
	{// �û�������
		buyBulletRet.iRes = RET_GAME_USER_NOT_EXIST;
	}
	long long llGold = pSingleUser->get_gold_login();			// �û���ǰ���
	int iBasePoint = m_pRoomMgr->get_server_room_info().iBasePoint;			// ��ǰ���䱶��
	if (ROOM_GAME_TYPE_GOLD==iRoomType)
	{// ��ҳ�
		if ((userBuyBullet->iBulletNum * iBasePoint) > llGold )
		{// �����Ҳ�������������ӵ�
			buyBulletRet.iRes = RET_GAME_BUY_BULLET_GOLD_LACK;
		}
	}

	if (RET_GAME_OPERATE_SUCCEED == buyBulletRet.iRes)
	{// �����ӵ�
		m_gameUserInfo[iSeatNo].iBuyBulletCount += userBuyBullet->iBulletNum;				// �����ӵ�����
		m_gameUserInfo[iSeatNo].iBulletCount += userBuyBullet->iBulletNum;					// ���ӹ����ӵ�����
		buyBulletRet.iBulletNum = userBuyBullet->iBulletNum;								// ��������
		if (ROOM_GAME_TYPE_GOLD==iRoomType)
		{// ��ҳ�
			m_gameUserInfo[iSeatNo].lGoldChange += (-(userBuyBullet->iBulletNum * iBasePoint));	// ��ӹ���������
		}
		else if(ROOM_GAME_TYPE_POINT==iRoomType)
		{// ���ֳ�
			m_gameUserInfo[iSeatNo].lPointChange += (-(userBuyBullet->iBulletNum * iBasePoint));	// ��ӹ���������
		}

		buyBulletRet.llGold = pSingleUser->get_gold_login() + m_gameUserInfo[iSeatNo].lGoldChange;		// ������
		buyBulletRet.llPoint = pSingleUser->get_point_login() + m_gameUserInfo[iSeatNo].lPointChange;	// �������

		send_table_data(TABLE_MAIN, TABLE_SUB_BUY_BULLET_RET, (BYTE*)(&buyBulletRet), sizeof(USER_BUY_BULLET_RET));
	}
	else
	{// �ӵ��������
		send_data(iSeatNo,TABLE_MAIN, TABLE_SUB_BUY_BULLET_RET, (BYTE*)(&buyBulletRet), sizeof(USER_BUY_BULLET_RET));
	}
}

// ��鳬ʱ�˳����� add by cxf
void CFishTable::OnCheckOverTime()
{
	if (GAME_SYS_STATE_RUNING!=m_iGameSysState)
	{// ��Ϸδ��ʼ������
		return;
	}

	if (ROOM_GAME_TYPE_MATCH==m_pRoomMgr->get_server_room_info().iRoomType)
	{// ������Ϸ������
		return;
	}

	vector<SEAT_INFO*>::iterator it = m_vecSeatInfo.begin();
	for (;it!=m_vecSeatInfo.end();++it)
	{
		SEAT_INFO * seatInfo = *it;
		if (!seatInfo->pSingleUser)
		{// ����û����
			continue;
		}

		LONGLONG llChannel = seatInfo->pSingleUser->get_channel();
		unsigned int nTime = (unsigned int)time(NULL) - (seatInfo->nOperateTime);
		if (nTime >= FIER_OVERTIME_TIME)
		{// �û�����ʱ
			char szBuf[64]={0};
			sprintf(szBuf,"����ʱ�߳�,UserId=%d; �ӵ�����=%d ",seatInfo->pSingleUser->get_user_id(), m_stBulletMgr.GetBulletCount(seatInfo->pSingleUser->get_user_id()));
			COften::OutputInfo(szBuf);
			m_pRoomMgr->OnKickOutUser(llChannel);							// �˳��û�
		}
		else if (!seatInfo->bWarning && nTime >= FIER_OVERTIME_WARNING_TIME)
		{
			seatInfo->bWarning = true;
			USER_OVERTIME_SURPLUS surplus;
			surplus.iSurplusTime = 15;
			send_game_data(llChannel,TABLE_MAIN,TABLE_SUB_USER_OVERTIME, (BYTE *)&surplus, sizeof(USER_OVERTIME_SURPLUS));		// �û���ʱû����
		}
	}
}

// ����û��ӵ��Ƿ���
bool CFishTable::OnCheckAllUserBullet()
{
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		int iBulletCount = m_gameUserInfo[i].iBulletCount;
		if (iBulletCount>0)
		{// ��һ����ӵ�
			return false;
		}
	}
	return true;
}

// ������������
void CFishTable::SortMatch(CMD_GameUserInfo matchUserInfo[])
{
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		for (int j=i+1;j<GAME_PLAYER_COUNT;++j)
		{
			if (matchUserInfo[i].lGameCoin<matchUserInfo[j].lGameCoin)
			{// ���������
				CMD_GameUserInfo matchInfo;
				matchInfo = matchUserInfo[i];
				matchUserInfo[i] = matchUserInfo[j];
				matchUserInfo[j] = matchInfo;
			}
			else if(matchUserInfo[i].lGameCoin==matchUserInfo[j].lGameCoin)
			{// ���������
				if (matchUserInfo[i].iBulletCount<matchUserInfo[j].iBulletCount)
				{// �ӵ�����������
					CMD_GameUserInfo matchInfo;
					matchInfo = matchUserInfo[i];
					matchUserInfo[i] = matchUserInfo[j];
					matchUserInfo[j] = matchInfo;
				}
				else if(matchUserInfo[i].lUserID<matchUserInfo[j].lUserID)
				{// �û�ID ������
					CMD_GameUserInfo matchInfo;
					matchInfo = matchUserInfo[i];
					matchUserInfo[i] = matchUserInfo[j];
					matchUserInfo[j] = matchInfo;
				}
			}
		}
	}
}

// ��ȡ̨�� �������ӵ�
void CFishTable::TradeFee()
{
	if (NULL==m_pRoomMgr)
	{// �������
		return;
	}

	int iEnterTradeGold		= m_pRoomMgr->get_server_room_info().iEnterTradeGold;			// ����۳����
	int iEnterTradePoint	= m_pRoomMgr->get_server_room_info().iEnterTradePoint;			// ����۳�����
	int iEnterPresentBullet	= m_pRoomMgr->get_server_room_info().iEnterPresentBullet;		// ��ʼ�����ӵ�

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

		m_gameUserInfo[i].lGoldChange += (-iEnterTradeGold);	// ����۳����
		m_gameUserInfo[i].lPointChange += (-iEnterTradePoint);	// ����۳�����
		m_gameUserInfo[i].iBulletCount += iEnterPresentBullet;	// ���������ӵ�����

		if (iEnterTradeGold!=0 || iEnterTradePoint!=0 || iEnterPresentBullet!=0)
		{
			// �û����ݸı�
			CMD_SC_USER_DATA_CHANGE userInfoChange;
			userInfoChange.lUserId = m_gameUserInfo[i].lUserID;
			userInfoChange.iGold = -iEnterTradeGold;
			userInfoChange.iPoint = -iEnterTradePoint;
			send_table_data(TABLE_MAIN, TABLE_SUB_USER_DATA_CHANGE, (BYTE*)&userInfoChange, sizeof(CMD_SC_USER_DATA_CHANGE));
		}
	}
}

// �û�����
void CFishTable::OnUserSitDown(int iSeatNo)
{
	// ��ʼ���û���Ϸ��Ϣ
	OnSitDownInit(iSeatNo);
}

// ��������
void CFishTable::OnMatchEnd()
{
	if (m_eGamePhase!=ENUM_GAME_PHASE::ENUM_GAME_START)
	{
		return;
	}
	m_eGamePhase = ENUM_GAME_PHASE::ENUM_GAME_END;

	kill_table_timer(IDI_GAME_END_TIMER);// ��������ʱ

	CMD_GameUserInfo matchInfo[GAME_PLAYER_COUNT];
	memcpy(matchInfo, m_gameUserInfo, sizeof(matchInfo));
	// ��������
	SortMatch(matchInfo);

	CMD_MatchEnd matchEnd;
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{// ���÷��ͽ����
		matchEnd.lUserID[i] = matchInfo[i].lUserID;
		memcpy(matchEnd.szName[i], matchInfo[i].szName, USER_NAME_LEN);
		memcpy(matchEnd.szNickname[i], matchInfo[i].szNickname, USER_NAME_LEN);
		matchEnd.lGameCoin[i] = matchInfo[i].lGameCoin;
		matchEnd.lGoldChange[i] = matchInfo[i].lGoldChange;
		matchEnd.lPointChange[i] = matchInfo[i].lPointChange;
	}
	matchEnd.iRewardGold[0] = m_pRoomMgr->get_server_room_info().iRewardGold1;		// ��һ������
	matchEnd.iRewardGold[1] = m_pRoomMgr->get_server_room_info().iRewardGold2;		// �ڶ�������

	// �㲥������Ϸ����
	send_table_data(MATCH_MAIN, MATCH_SUB_SC_GAME_END, (BYTE *)&matchEnd, sizeof(CMD_MatchEnd));

	// д�����
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		if (matchEnd.lUserID[i] < 1)
		{// �û�������
			continue;
		}
		
		CMD_MatchAccounts matchAccount;
		matchAccount.lGold = matchEnd.lGoldChange[i];			// �䶯���
		matchAccount.lPoint = matchEnd.lPointChange[i];			// �䶯���� 
		matchAccount.lGameCoin = matchEnd.lGameCoin[i];			// ���
		matchAccount.iRewardGold = matchEnd.iRewardGold[i];		// ����

		OnUserMatchAccounts(i, matchAccount);
	}

	for (int i=0;i<m_vecSeatInfo.size();++i)
	{
		CSingleUser* pSingleUser = get_SingleUser_by_seatNo(i);
		if (NULL != pSingleUser)
		{
			m_pRoomMgr->OnKickOutUser(pSingleUser->get_channel());		// �˳��û�
		}
	}

	memset(m_gameUserInfo, 0, sizeof(m_gameUserInfo));
	// ��Ϸ������ʼ��
	OnInit();
}

// ����
int CFishTable::OnAccounts(int iSeatNo)
{
	if(!m_pRoomMgr)	
	{
		return 10;
	}

	long long iRoomType = m_pRoomMgr->get_server_room_info().iRoomType;
	if (iRoomType == ROOM_GAME_TYPE_MATCH)
	{// ��������������;����
		return 30;
	}

	CMD_WRITE_SCORE sendData;
	memset(&sendData, 0, sizeof(CMD_WRITE_SCORE));

	long long lGameCoin = m_gameUserInfo[iSeatNo].lGameCoin;
	int iBasePoint = m_pRoomMgr->get_server_room_info().iBasePoint;		// ���䱶��
	int iBulletCount = m_gameUserInfo[iSeatNo].iBulletCount;		// ʣ���ӵ�����

	if (ROOM_GAME_TYPE_GOLD==iRoomType)
	{// ��ҳ�
		sendData.lGold			= (lGameCoin * iBasePoint)+(iBulletCount * iBasePoint)+ m_gameUserInfo[iSeatNo].lGoldChange;// (���*���䱶��)+(�ӵ�����*���䱶��)+�޸Ľ��(��:�����ӵ�������)
	}
	else if(ROOM_GAME_TYPE_POINT==iRoomType)
	{// ���ֳ�
		sendData.lPoint			= (lGameCoin * iBasePoint)+(iBulletCount * iBasePoint)+ m_gameUserInfo[iSeatNo].lPointChange;// (���*���䱶��)+(�ӵ�����*���䱶��)+�޸Ļ���(��:�����ӵ��������)
	}
	sendData.llGameCoin		= lGameCoin;													// ���
	sendData.iBuyBulletCount= m_gameUserInfo[iSeatNo].iBuyBulletCount;						// �û������ӵ�����
	sendData.iBulletCount	= iBulletCount;													// ��ʣ�ӵ�
	sendData.iFeats			= m_gameUserInfo[iSeatNo].iFeats*iBasePoint;					// ��ѫ
	
	OnUserAccountsWrite(iSeatNo, sendData);

	// ��ʼ����Ϸ�û�����
	m_gameUserInfo[iSeatNo].iBuyBulletCount = 0;
	m_gameUserInfo[iSeatNo].iBulletCount = 0;
	m_gameUserInfo[iSeatNo].iFeats = 0;
	m_gameUserInfo[iSeatNo].lGameCoin = 0;
	m_gameUserInfo[iSeatNo].lGoldChange = 0;
	m_gameUserInfo[iSeatNo].lPointChange = 0;

	return 0;
}

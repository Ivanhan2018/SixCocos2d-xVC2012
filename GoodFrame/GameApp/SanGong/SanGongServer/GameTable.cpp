#include "PublicHead.h"
#include "GameTable.h"
#include "Config.h"

CGameTable::CGameTable(void)
{
	m_GameStateMgr.m_pGameTable=this;
	m_wBankerChairID=INVALID_CHAIR;
	m_nKillMode=0;
	m_dice[0]=0;
	m_dice[1]=0;
	m_CallBankerNum=0;
	m_wOldBankerUserID=0;
	m_vecOldUserIDs.clear();
}

CGameTable::~CGameTable(void)
{

}

void CGameTable::OnInit()
{
	if(m_wBankerChairID!=INVALID_CHAIR)
		m_wOldBankerUserID=m_Players[m_wBankerChairID].m_llUserID;
	m_vecOldUserIDs.clear();
	for (int i=0;i<GAME_PLAYER_COUNT;++i)
	{
		if(m_Players[i].m_llUserID>0)
		{
			m_vecOldUserIDs.push_back(m_Players[i].m_llUserID);
		}
		m_Players[i].Init();
	}
	m_wBankerChairID=INVALID_CHAIR;
	m_nKillMode=0;
	m_dice[0]=0;
	m_dice[1]=0;
	m_CallBankerNum=0;
}

TChip CGameTable::calcC3(TChip Z,TChip X,TChip F,unsigned long long N)
{
	TChip min=Z/(9*N);
	if(X/9<min)
		min=X/9;
	if(F/(9*N)<min)
		min=F/(9*N);
	return min;
}

unsigned long long CGameTable::GetTickCount64()
{
#if 0
	return ::GetTickCount64();
#else
	//��ʱ�ٶ��ͻ��˵ķ�����ʱ����1970��
	return CEasyDataTime::get_current_time_diff_millitm_from_1970();
#endif
}

vector<SEAT_INFO*> CGameTable::GetPlayers(bool bRefresh/*=false*/)
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	vector<SEAT_INFO*> vecSeatInfo;
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

		//add by Ivan_han 20131021
		if(seatInfo->pSingleUser->get_seat_no()<0||seatInfo->pSingleUser->get_seat_no()>=GAME_PLAYER_COUNT)
			continue;
		if(bRefresh==false && seatInfo->pSingleUser->get_user_id()!=m_Players[seatInfo->pSingleUser->get_seat_no()].m_llUserID)
			continue;

		//add by Ivan_han 20131029
		if(seatInfo->pSingleUser->get_user_state()==US_ONLINE_SITDOWN)
			continue;

		vecSeatInfo.push_back(seatInfo);
		int seat_no=seatInfo->pSingleUser->get_seat_no();
		if(bRefresh && seat_no>=0 && seat_no<GAME_PLAYER_COUNT)
		{
			m_Players[seat_no].m_llUserID=seatInfo->pSingleUser->get_user_id();
			m_Players[seat_no].m_Chip=(seatInfo->pSingleUser->get_gold_login()>0?seatInfo->pSingleUser->get_gold_login():seatInfo->pSingleUser->get_point_login());
		}
	}
	return vecSeatInfo;
}

vector<TChairID> CGameTable::GetPlayersNoOp1(vector<TChairID> &vecCall,vector<TChairID> &vecNoCall)
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	vector<TChairID> vecChairID;
	vecCall.clear();
	vecNoCall.clear();
	for(int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		if(m_Players[i].m_llUserID>0 && m_Players[i].m_byCallBanker==INVALID_BYTE)
			vecChairID.push_back(i);
		if(m_Players[i].m_llUserID>0 && m_Players[i].m_byCallBanker==1)
			vecCall.push_back(i);
		if(m_Players[i].m_llUserID>0 && m_Players[i].m_byCallBanker==0)
			vecNoCall.push_back(i);
	}
	return vecChairID;
}

vector<TChairID> CGameTable::GetPlayersNoOp2()
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	vector<TChairID> vecChairID;
	for(int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		if(i==m_wBankerChairID)
			continue;
		if(m_Players[i].m_llUserID>0 && m_Players[i].m_llUserChipIn==0)
			vecChairID.push_back(i);
	}
	return vecChairID;
}

vector<TChairID> CGameTable::GetPlayersNoOp3()
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	vector<TChairID> vecChairID;
	for(int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		if(m_Players[i].m_llUserID>0 && m_Players[i].m_cbUserSendFinish==0)
			vecChairID.push_back(i);
	}
	return vecChairID;
}

vector<TChairID> CGameTable::GetPlayersNoOp4()
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	vector<TChairID> vecChairID;
	for(int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		if(m_Players[i].m_llUserID>0 && m_Players[i].m_cbUserShowFinish==0)
			vecChairID.push_back(i);
	}
	return vecChairID;
}

bool CGameTable::CheckNeedCallBanker()
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	if(m_wOldBankerUserID==0)
	{
		return true; 
	}

	//������Ϸ�е�����б�
	vector<TUserID> vecUserIDs;
	vector<TChairID> vecChairIDs;
	vector<TChip> vecChips;
	int iBankerIndex=-1;

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
		if (seatInfo->pSingleUser->get_user_state()==US_ONLINE_SITDOWN)
		{// �Թ��û�
			continue;
		}
		TUserID llUserID=seatInfo->pSingleUser->get_user_id();
		vecUserIDs.push_back(llUserID);
		vecChairIDs.push_back(seatInfo->pSingleUser->get_seat_no());
		vecChips.push_back(seatInfo->pSingleUser->get_gold_login());
		if(llUserID==m_wOldBankerUserID && m_wOldBankerUserID>0)
		{
			iBankerIndex=vecUserIDs.size()-1; 
		}
	}

	//������뿪���¼���ʱ��Ҫ������ׯ
	if(m_vecOldUserIDs.size()!=vecUserIDs.size())
	{
		return true;
	}
	
	//ֻҪ�κ�һ���мұ���һ�ֵ�ׯ��Ǯ��(nCount>0)�������¿�һ������������ׯ
	if(iBankerIndex>-1)
	{
		int nCount=count_if(vecChips.begin(),vecChips.end(),bind2nd(greater<TChip>(),vecChips[iBankerIndex]));
		if(nCount==0)
		{
			m_wBankerChairID=vecChairIDs[iBankerIndex];
			m_CallBankerNum=0;
			return false; 
		}
	}

	return true;
}

// ����
int CGameTable::OnCut(LONGLONG lUserId)
{
	char szBuf[64]={0};
	sprintf(szBuf,"lUserId=%I64d ���� ",lUserId);
	COften::OutputInfo(szBuf);
	return 0;
}

// ����������Ӧ�����������û����������¼����ʱ�Ż���Ӧ
int CGameTable::OnRecomeAfterCut(int iSeatNo)
{
	COften::OutputInfo("����������Ӧ");
	return 0;
}

// ���Ӷ�ʱ����Ӧ
int CGameTable::OnTableTimer(int iTableNo, int iIDEvent)
{
	if (iTableNo!=m_stTableInfo.iTableNo)
		return 0;

	//�¼�����
	switch (iIDEvent)
	{
	default:
		if(m_GameStateMgr.m_pCurGameState)
		{
			return m_GameStateMgr.m_pCurGameState->OnTableTimer(iTableNo,iIDEvent);
		}
		break;
	}
	return 0;
}

// �û�����
void CGameTable::OnUserSitDown(int iSeatNo)
{
	//add by Ivan_han 20131103
	e_GameState byGameState=m_GameStateMgr.GetGameState();
	//��Ϸ�Ѿ���ʼ
	if (E_GAME_FREE!=byGameState)
	{
		Rsp_BankerChipinSendCardInfo rsp;
		rsp.curGameState=byGameState;
		for(int i=0;i<GAME_PLAYER_COUNT;i++)
		{
			rsp.byCallBanker[i]=m_Players[i].m_byCallBanker;
			rsp.llUserChipIn[i]=m_Players[i].m_llUserChipIn;
			rsp.cbUserCardData[i][0]=m_Players[i].m_cbUserCardData[0];
			rsp.cbUserCardData[i][1]=m_Players[i].m_cbUserCardData[1];
			rsp.cbUserCardData[i][2]=m_Players[i].m_cbUserCardData[2];
		}
		rsp.wBankerChairID=(byGameState>E_GAME_CALL_BANKER?m_wBankerChairID:INVALID_CHAIR);
		send_data(iSeatNo,TABLE_MAIN,RSP_BANKER_CHIPIN_SENDCARD_INFO,(BYTE*)&rsp, sizeof(Rsp_BankerChipinSendCardInfo));
		return;
	}
}

// ����
int CGameTable::OnRaiseHand(int iSeatNo)
{
	//char szBuf[64]={0};
	//sprintf(szBuf, "�������Ӻ�=%d",iSeatNo);
	//COften::OutputInfo(szBuf);

	return 0;
}

//��Ϸ��ʼ
int CGameTable::OnGameBegin()
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	COften::OutputInfo("��Ϸ��ʼ��");

	bool bNeedCallBanker=CheckNeedCallBanker();
	m_GameStateMgr.OnGameBegin(bNeedCallBanker);

	return 0;
}

void CGameTable::SendCard()
{
	// �����ѭ����������ڵ�һ��
	CEndlessLoopGuard stEndlessLoopGuard(m_pEndlessLoop, __FUNCTION__);

	Rsp_SendCard_List rsp;
	TCardData	m_cbUserCardData[GAME_PLAYER_COUNT][MAX_COUNT]={0};
	srand(time(0));
	m_GameLogic.RandCardList(m_cbUserCardData[0],sizeof(m_cbUserCardData)/sizeof(m_cbUserCardData[0][0]));
	int j=0;
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

		//add by Ivan_han 20131021
		if(seatInfo->pSingleUser->get_seat_no()<0||seatInfo->pSingleUser->get_seat_no()>=GAME_PLAYER_COUNT)
			continue;
		if(seatInfo->pSingleUser->get_user_id()!=m_Players[seatInfo->pSingleUser->get_seat_no()].m_llUserID)
			continue;

		Rsp_SendCard SendCard;
		SendCard.llUserID =seatInfo->pSingleUser->get_user_id();
		SendCard.iSeatNo =seatInfo->pSingleUser->get_seat_no();
		//SendCard.CardType=m_GameLogic.GetCardType(m_cbUserCardData[j],MAX_COUNT);
		//SendCard.m_CardPoint=m_GameLogic.GetCardPoint(m_cbUserCardData[j],MAX_COUNT);
		//��ׯ�ҡ��мҷ�ָ���ƣ�������
		if(SangongConfig::Instance().m_Enable==1)
		{
			if(SendCard.iSeatNo==m_wBankerChairID)
			{
				memcpy(m_cbUserCardData[j],SangongConfig::Instance().m_cbBankerCardData,sizeof(TCardData)*MAX_COUNT);
			}
			else
			{
				memcpy(m_cbUserCardData[j],SangongConfig::Instance().m_cbNoBankerCardData,sizeof(TCardData)*MAX_COUNT);
			}
		}
#if 0
        if(SendCard.iSeatNo==m_wBankerChairID)
		{
			TCardData cbCardData[MAX_COUNT]={0x0A,0x13,0x2D};
			memcpy(m_cbUserCardData[j],cbCardData,sizeof(TCardData)*MAX_COUNT);
		}
#endif
		memcpy(SendCard.cbUserCardData,m_cbUserCardData[j],sizeof(TCardData)*MAX_COUNT);
		memcpy(&rsp.m_SendCards[rsp.nCount],&SendCard, sizeof(Rsp_SendCard));
		rsp.nCount+=1;
		//send_table_data(TABLE_MAIN,RSP_SEND_CARD,(BYTE*)&SendCard, sizeof(Rsp_SendCard));
#if 0
		m_Players[SendCard.iSeatNo].m_llUserID=SendCard.llUserID;
		memcpy(m_Players[SendCard.iSeatNo].m_cbUserCardData,m_cbUserCardData[j],sizeof(TCardData)*MAX_COUNT);
		m_GameLogic.SortCardList(m_cbUserCardData[j],MAX_COUNT);
		m_Players[SendCard.iSeatNo].m_CardTypeMulti=m_GameLogic.GetCardTimes(m_cbUserCardData[j],MAX_COUNT);
		m_Players[SendCard.iSeatNo].m_CardType=m_GameLogic.GetCardType(m_cbUserCardData[j],MAX_COUNT);
		m_Players[SendCard.iSeatNo].m_CardPoint=m_GameLogic.GetCardPoint(m_cbUserCardData[j],MAX_COUNT);
#else
		SetPlayersCardData(SendCard);
#endif
		j++;
#if _DEBUG
		/*cout<<"�û�ID="<<SendCard.llUserID<<"��λ��="<<SendCard.iSeatNo<<":";
		for(int k=0;k<MAX_COUNT;k++)
		{
			cout<<(int)SendCard.cbUserCardData[k]<<"("<<CGameLogic::GetCardName(SendCard.cbUserCardData[k])<<")"<<" ";
		}
		cout<<" m_CardTypeMulti="<<(int)m_Players[SendCard.iSeatNo].m_CardTypeMulti;
		cout<<" m_CardType="<<(int)m_Players[SendCard.iSeatNo].m_CardType;
		cout<<" m_CardPoint="<<(int)m_Players[SendCard.iSeatNo].m_CardPoint;
		cout<<" m_llUserChipIn="<<(int)m_Players[SendCard.iSeatNo].m_llUserChipIn;
		cout<<endl;*/
		/*
		char szBuf[256]={0};
		string strBuf="";
		sprintf(szBuf, "�û�ID=%d ��λ��=%d :", SendCard.llUserID, SendCard.iSeatNo);
		strBuf.append(szBuf);
		for(int k=0;k<MAX_COUNT;k++)
		{
			sprintf(szBuf, "%d (%s)", (int)SendCard.cbUserCardData[k], CGameLogic::GetCardName(SendCard.cbUserCardData[k]));
			strBuf.append(szBuf);
		}
		sprintf(szBuf, " m_CardTypeMulti=%d m_CardType=%d m_CardPoint=%d m_llUserChipIn=%d", 
			(int)m_Players[SendCard.iSeatNo].m_CardTypeMulti, (int)m_Players[SendCard.iSeatNo].m_CardType, (int)m_Players[SendCard.iSeatNo].m_CardPoint, (int)m_Players[SendCard.iSeatNo].m_llUserChipIn);
		strBuf.append(szBuf);
		strcpy(szBuf, strBuf.c_str());
		write_log(true, 0, szBuf, 256);*/
#endif
	}

	//�����ﻻ�Ƹ�ׯ��
	if(m_nKillMode==1)
	{
		vector<TChip> vecUserChipIn;
		for(int i=0;i<rsp.nCount;i++)
		{
			TChairID ChairID=rsp.m_SendCards[i].iSeatNo;
			vecUserChipIn.push_back(m_Players[ChairID].m_llUserChipIn);
		}
		bool IsChange=CGameTable::CheckKillCardToBanker(&rsp,vecUserChipIn,m_wBankerChairID);
		if(IsChange)
		{
			for(int i=0;i<rsp.nCount;i++)
			{
				SetPlayersCardData(rsp.m_SendCards[i]);
			}
		}
	}
#if 0
	TChairID iSeatNo;
	bool IsChange=CGameTable::CheckGoodCardToBanker(&rsp,m_wBankerChairID,iSeatNo);
	if(IsChange)
	{
		for(int i=0;i<rsp.nCount;i++)
		{
			SetPlayersCardData(rsp.m_SendCards[i]);
		}
	}
#endif

	send_table_data(TABLE_MAIN,RSP_SEND_CARD_LIST,(BYTE*)&rsp, sizeof(Rsp_SendCard_List));
}

bool CGameTable::CheckGoodCardToBanker(Rsp_SendCard_List *pRsp,TChairID wBankerChairID,TChairID &iSeatNo)
{
	int BankerIndex=-1;
	for(int i=0;i<pRsp->nCount;i++)
	{
		if(pRsp->m_SendCards[i].iSeatNo==wBankerChairID)
		{
		   BankerIndex=i;
		   break;
		}
	}
	if(BankerIndex==-1)
		return false;

	int NewBankerIndex=BankerIndex;
	for(int i=0;i<pRsp->nCount;i++)
	{
		if(i==BankerIndex)
			continue;

		if (CGameLogic::CompareCard(pRsp->m_SendCards[i].cbUserCardData,pRsp->m_SendCards[NewBankerIndex].cbUserCardData,MAX_COUNT)==true) 
		{
			NewBankerIndex=i;
		}
	}
	if(NewBankerIndex==-1 || NewBankerIndex==BankerIndex)
		return false;

	TCardData cbUserCardData[3];
	memcpy(cbUserCardData,pRsp->m_SendCards[NewBankerIndex].cbUserCardData,sizeof(TCardData)*MAX_COUNT);
	memcpy(pRsp->m_SendCards[NewBankerIndex].cbUserCardData,pRsp->m_SendCards[BankerIndex].cbUserCardData,sizeof(TCardData)*MAX_COUNT);
	memcpy(pRsp->m_SendCards[BankerIndex].cbUserCardData,cbUserCardData,sizeof(TCardData)*MAX_COUNT);
	
	//���������Ƶ��м��û�
	iSeatNo=pRsp->m_SendCards[NewBankerIndex].iSeatNo;

	return true;
}

bool CGameTable::CheckKillCardToBanker(Rsp_SendCard_List *pRsp,const vector<TChip> &vecUserChipIn,TChairID wBankerChairID)
{
	if(pRsp->nCount!=vecUserChipIn.size())
		return false;

	int iBankerIndex=-1;
	vector<int> WinnerIndex;
	vector<int> LoserIndex;
	vector<TChip> retGameScore=CheckCard(pRsp,vecUserChipIn,wBankerChairID,iBankerIndex,WinnerIndex,LoserIndex);
	if(iBankerIndex==-1)
		return false;
	//ɢ��ׯ�һ�Ƣǰ��˰ǰ��������
	TChip BankerGameScore=retGameScore[iBankerIndex];
	//�ж�ɢ��ׯ���Ƿ�ӮǮ��ɱ����С
	if(BankerGameScore>0 && WinnerIndex.size()>0)
	{
		return false;
	}
	else
	{
		//ɢ��ׯ�һ�Ƣ���˰ǰ��������
		TChip NewBankerGameScore=BankerGameScore;
		//��໻��WinnerIndex.size()��
		for(int i=0;i<WinnerIndex.size();i++)
		{
			int mWinnerIndex=WinnerIndex[i];
			int mWinnerGameScore=retGameScore[mWinnerIndex];
			TCardData cbUserCardData[3];
			memcpy(cbUserCardData,pRsp->m_SendCards[mWinnerIndex].cbUserCardData,sizeof(TCardData)*MAX_COUNT);
			memcpy(pRsp->m_SendCards[mWinnerIndex].cbUserCardData,pRsp->m_SendCards[iBankerIndex].cbUserCardData,sizeof(TCardData)*MAX_COUNT);
			memcpy(pRsp->m_SendCards[iBankerIndex].cbUserCardData,cbUserCardData,sizeof(TCardData)*MAX_COUNT);

			vector<TChip> retGameScore=CheckCard(pRsp,vecUserChipIn,wBankerChairID,iBankerIndex,WinnerIndex,LoserIndex);
			if(iBankerIndex==-1)
				return true;
			NewBankerGameScore=retGameScore[iBankerIndex];
			if(NewBankerGameScore>0 && WinnerIndex.size()>0)
				return true;
		}
		//�������ͨɱ
		if(NewBankerGameScore>0 && WinnerIndex.size()==0)
			return true;
		//��������䣬�ٻ�һ�Σ���ʱֱ�ӷ�����Ƹ�ɢ��ׯ��ͨɱ
		TChairID iSeatNo;
		bool IsChange=CheckGoodCardToBanker(pRsp,wBankerChairID,iSeatNo);
		return true;
	}

	return false;
}

vector<TChip> CGameTable::CheckCard(Rsp_SendCard_List *pRsp,const vector<TChip> &vecUserChipIn,TChairID wBankerChairID,int &iBankerIndex,vector<int> &WinnerIndex,vector<int> &LoserIndex)
{
	vector<TChip> retGameScore(3);
	WinnerIndex.clear();
	LoserIndex.clear();

	int BankerIndex=-1;
	for(int i=0;i<pRsp->nCount;i++)
	{
		if(pRsp->m_SendCards[i].iSeatNo==wBankerChairID)
		{
			BankerIndex=i;
			break;
		}
	}
	iBankerIndex=BankerIndex;
	if(BankerIndex==-1)
		return retGameScore;

	TCardTypeMulti BankerCardTypeMulti=CGameLogic::GetCardTimes(pRsp->m_SendCards[BankerIndex].cbUserCardData,MAX_COUNT);

	for(int i=0;i<pRsp->nCount;i++)
	{
		if(i==BankerIndex)
			continue;

		//�Ա��˿�
		if(CGameLogic::CompareCard(pRsp->m_SendCards[i].cbUserCardData,pRsp->m_SendCards[BankerIndex].cbUserCardData,MAX_COUNT)==true) 
		{
			TCardTypeMulti CardTypeMulti=CGameLogic::GetCardTimes(pRsp->m_SendCards[i].cbUserCardData,MAX_COUNT);
			retGameScore[i]+=CardTypeMulti*vecUserChipIn[i];
			retGameScore[BankerIndex]-=CardTypeMulti*vecUserChipIn[i];
			WinnerIndex.push_back(i);
		}
		else
		{
			retGameScore[i]-=BankerCardTypeMulti*vecUserChipIn[i];
			retGameScore[BankerIndex]+=BankerCardTypeMulti*vecUserChipIn[i];
			LoserIndex.push_back(i);
		}
	}
	
	return retGameScore;
}

void CGameTable::SetPlayersCardData(Rsp_SendCard SendCard)
{
	if(SendCard.iSeatNo>=0 && SendCard.iSeatNo<GAME_PLAYER_COUNT)
	{
		m_Players[SendCard.iSeatNo].m_llUserID=SendCard.llUserID;
		memcpy(m_Players[SendCard.iSeatNo].m_cbUserCardData,SendCard.cbUserCardData,sizeof(TCardData)*MAX_COUNT);
		m_Players[SendCard.iSeatNo].m_CardTypeMulti=m_GameLogic.GetCardTimes(SendCard.cbUserCardData,MAX_COUNT);
		m_Players[SendCard.iSeatNo].m_CardType=m_GameLogic.GetCardType(SendCard.cbUserCardData,MAX_COUNT);
		m_Players[SendCard.iSeatNo].m_CardPoint=m_GameLogic.GetCardPoint(SendCard.cbUserCardData,MAX_COUNT);
	}
}

void CGameTable::SendCallBankerResult(bool bNeedCallBanker,int iSubCode)
{
	vector<SEAT_INFO*> vecSeatInfo=GetPlayers(false);
	int nSize=vecSeatInfo.size();

	//��������������F
	TChip F=m_pRoomMgr->get_server_room_info().iMostToLostMoney;
	//Rsp_BankerC3Info rsp;
	for(int i=0;i<nSize;i++)
	{
		int seat_no=vecSeatInfo[i]->pSingleUser->get_seat_no();
		if(seat_no!=m_wBankerChairID)
			m_Players[seat_no].m_llMaxChip=CGameTable::calcC3(m_Players[m_wBankerChairID].m_Chip,m_Players[seat_no].m_Chip,F,nSize-1);

		Rsp_BankerC3Info rsp;
		rsp.bNeedCallBanker=bNeedCallBanker;
		rsp.wBankerUser=m_wBankerChairID;
		rsp.dice[0]=m_dice[0];
		rsp.dice[1]=m_dice[1];
		rsp.CallBankerNum=m_CallBankerNum;
		rsp.C1=m_Players[seat_no].m_llMaxChip/4;
		rsp.C2=m_Players[seat_no].m_llMaxChip/2;
		rsp.C3=m_Players[seat_no].m_llMaxChip;
		send_data(seat_no,TABLE_MAIN,iSubCode/*RSP_CALL_BANKER_RESULT*/,(BYTE*)&rsp, sizeof(Rsp_BankerC3Info));
		//add by Ivan_han 20131029
		send_table_state_user(TABLE_MAIN,iSubCode,(BYTE*)&rsp, sizeof(Rsp_BankerC3Info),US_ONLINE_SITDOWN);
	}
	//send_table_data(TABLE_MAIN,iSubCode/*RSP_CALL_BANKER_RESULT*/,(BYTE*)&rsp, sizeof(Rsp_BankerC3Info));

#ifdef _DEBUG
	//if(iSubCode==RSP_DICE_NOTIFY)
	//	printf("%s ���Զ������� bNeedCallBanker=%d wBankerUser=%d C3=%I64d C2=%I64d C1=%I64d \n",COften::GetCurrentTime_str().c_str(),bNeedCallBanker,rsp.wBankerUser,rsp.C3,rsp.C2,rsp.C1);
	//else if(iSubCode==RSP_CALL_BANKER_RESULT)
	//	printf("%s ������ע�� bNeedCallBanker=%d wBankerUser=%d C3=%I64d C2=%I64d C1=%I64d \n",COften::GetCurrentTime_str().c_str(),bNeedCallBanker,rsp.wBankerUser,rsp.C3,rsp.C2,rsp.C1);


	/*char szBuf[256]={0};
	if(iSubCode==RSP_DICE_NOTIFY)
	{
		sprintf(szBuf,"%s ���Զ������� bNeedCallBanker=%d wBankerUser=%d C3=%I64d C2=%I64d C1=%I64d ",COften::GetCurrentTime_str().c_str(),bNeedCallBanker,rsp.wBankerUser,rsp.C3,rsp.C2,rsp.C1);
	}
	else if(iSubCode==RSP_CALL_BANKER_RESULT)
	{
		sprintf(szBuf,"%s ������ע�� bNeedCallBanker=%d wBankerUser=%d C3=%I64d C2=%I64d C1=%I64d ",COften::GetCurrentTime_str().c_str(),bNeedCallBanker,rsp.wBankerUser,rsp.C3,rsp.C2,rsp.C1);
	}
	write_log(true, 0, szBuf, 256);
	*/
#endif
}

void CGameTable::SendUserDefaultChipin()
{
	vector<TChairID> vecChairID=GetPlayersNoOp2();
	for(int i=0;i<vecChairID.size();i++)
	{
		Req_UserChipin rsp;
		rsp.llUserID=m_Players[vecChairID[i]].m_llUserID;
		rsp.iSeatNo=vecChairID[i];
		rsp.lScore=m_Players[vecChairID[i]].m_llMaxChip/4;
		m_Players[vecChairID[i]].m_llUserChipIn=rsp.lScore;
		send_table_data(TABLE_MAIN,RSP_USER_CHIPIN,(BYTE*)&rsp, sizeof(Req_UserChipin));
	}
}

bool CGameTable::OverCallBanker(bool bTimeOver)
{
	vector<TChairID> vecCall;
	vector<TChairID> vecNoCall;
	vector<TChairID> vecChairID=GetPlayersNoOp1(vecCall,vecNoCall);

	//ʱ�䵽�˽�����ׯ����
	if(bTimeOver)
	{
		//��ׯ����û�������������Ϊ����
		for(int i=0;i<vecChairID.size();i++)
		{
			Req_UserCallBanker rsp;
			rsp.llUserID=m_Players[vecChairID[i]].m_llUserID;
			rsp.iSeatNo=vecChairID[i];
			rsp.bCall=false;
			send_table_data(TABLE_MAIN,RSP_USER_CALL_BANKER,(BYTE*)&rsp,sizeof(Req_UserCallBanker));
		}
		if(vecCall.size()>0)
		{
			//���ѡһ��ׯ��
			int index=RandSetBanker(vecCall);
		}
		return true;
	}

	//���������Ҷ���ѡ������ǰ������ׯ����
	if(vecChairID.size()==0)
	{
		if(vecCall.size()>0)
		{
			//���ѡһ��ׯ��
			int index=RandSetBanker(vecCall);
		}
		m_GameStateMgr.SwitchGameState();
		return true;
	}
	return false;
}

int CGameTable::RandSetBanker(const vector<TChairID> &vecCall)
{
	if(vecCall.size()>0)
	{
		////���ѡһ��ׯ��
		//srand(time(0));
		//m_dice[0]=CGameLogic::GetRand(1,6);
		//m_dice[1]=CGameLogic::GetRand(1,6);
		//int index=(m_dice[0]+m_dice[1])%(vecCall.size());
		//m_wBankerChairID=vecCall[index];
		//m_CallBankerNum=vecCall.size();
		//return index;
		//������ׯʱ�����ϣ����Ǳ��չ�Ǯ������ȣ���Ǯһ���࣬����Ǯ����֮�����ȡһ����
		vector<int> vecMaxs;
		TChip maxChip=0;
		int nSize=vecCall.size();
		for (int i=0;i<nSize;i++)
		{
			TChairID ChairID=vecCall[i];
			TChip Chip=m_Players[ChairID].m_Chip;
			if(Chip>maxChip)
			{
				//vecMaxs.push_back(i);
				maxChip=Chip;
			}
		}
		for (int i=0;i<nSize;i++)
		{
			TChairID ChairID=vecCall[i];
			TChip Chip=m_Players[ChairID].m_Chip;
			if(Chip==maxChip)
			{
				vecMaxs.push_back(i);
			}
		}
		//����Ǯ������ׯ
		if(vecMaxs.size()>0)
		{
			//���ѡһ��ׯ��
			int nSize=vecMaxs.size();
			srand(time(0));
			m_dice[0]=CGameLogic::GetRand(1,6);
			m_dice[1]=CGameLogic::GetRand(1,6);
			int index=(m_dice[0]+m_dice[1])%nSize;
			m_wBankerChairID=vecCall[vecMaxs[index]];
			m_CallBankerNum=vecCall.size();
			return vecMaxs[index];
		}
	}
	return -1;
}

int CGameTable::RandSetBanker(const vector<SEAT_INFO*> &vecSeatInfo)
{
	if(vecSeatInfo.size()>0)
	{
		if(CGameLogic::SelectBoolByProb(SangongConfig::Instance().m_BankerProb))
		{
			vector<int> vecMaxs;
			TChip maxChip=0;
			int nSize=vecSeatInfo.size();
			for (int i=0;i<nSize;i++)
			{
				TChip Chip=vecSeatInfo[i]->pSingleUser->get_gold_login();
				if(Chip>maxChip)
				{
					//vecMaxs.push_back(i);
					maxChip=Chip;
				}
			}
			for (int i=0;i<nSize;i++)
			{
				TChip Chip=vecSeatInfo[i]->pSingleUser->get_gold_login();
				if(Chip==maxChip)
				{
					vecMaxs.push_back(i);
				}
			}

			//����Ǯ������ׯ
			if(vecMaxs.size()>0)
			{
				//���ѡһ��ׯ��
				int nSize=vecMaxs.size();
				srand(time(0));
				m_dice[0]=CGameLogic::GetRand(1,6);
				m_dice[1]=CGameLogic::GetRand(1,6);
				int index=(m_dice[0]+m_dice[1])%nSize;
				CSingleUser* pSingleUser=vecSeatInfo[vecMaxs[index]]->pSingleUser;
				m_wBankerChairID=pSingleUser->get_seat_no();
				m_CallBankerNum=0;
				return vecMaxs[index];
			}
		}
		else
		{
			//���ѡһ��ׯ��
			int nSize=vecSeatInfo.size();
			srand(time(0));
			m_dice[0]=CGameLogic::GetRand(1,6);
			m_dice[1]=CGameLogic::GetRand(1,6);
			int index=(m_dice[0]+m_dice[1])%nSize;
			CSingleUser* pSingleUser=vecSeatInfo[index]->pSingleUser;
			m_wBankerChairID=pSingleUser->get_seat_no();
			m_CallBankerNum=0;
			return index;
		}
	}
	return -1;
}

void CGameTable::OnUserCallBanker(int iSeatNo,Req_UserCallBanker *callBanker)
{
	if (E_GAME_CALL_BANKER!=m_GameStateMgr.GetGameState())
	{// �׶δ���
		callBanker->iRes=10;
		send_data(iSeatNo,TABLE_MAIN,RSP_USER_CALL_BANKER,(BYTE*)callBanker, sizeof(Req_UserCallBanker));
		return;
	}
	if (INVALID_BYTE!=m_Players[iSeatNo].m_byCallBanker)
	{// �в�����
		callBanker->iRes=20;
		send_data(iSeatNo,TABLE_MAIN,RSP_USER_CALL_BANKER,(BYTE*)callBanker, sizeof(Req_UserCallBanker));
		return;
	}
	m_Players[iSeatNo].m_byCallBanker=callBanker->bCall;
	send_table_data(TABLE_MAIN,RSP_USER_CALL_BANKER,(BYTE*)callBanker, sizeof(Req_UserCallBanker));

    //printf("%s �û���ׯ���� m_byCallBanker=%d iSeatNo=%d llUserID=%I64d \n",COften::GetCurrentTime_str().c_str(),m_Players[iSeatNo].m_byCallBanker,iSeatNo,callBanker->llUserID);
	bool ret=OverCallBanker(false);
}

void CGameTable::OnUserKill(int iSeatNo,Req_UserKill * pReq)
{
	if(pReq->KillMode==0)
		return;

	if(E_GAME_CALL_SCORE!=m_GameStateMgr.GetGameState())
	{// �׶δ���
		pReq->iRes=10;
		send_data(iSeatNo,TABLE_MAIN, RSP_USER_KILL, (BYTE*)pReq, sizeof(Req_UserKill));
		return;
	}
	if(m_nKillMode>0)
	{// �в�����
		pReq->iRes=20;
		send_data(iSeatNo,TABLE_MAIN, RSP_USER_KILL, (BYTE*)pReq, sizeof(Req_UserKill));
		return;
	}

	m_nKillMode=pReq->KillMode;
	send_data(iSeatNo,TABLE_MAIN,RSP_USER_KILL, (BYTE*)pReq, sizeof(Req_UserKill));
}

void CGameTable::OnUserChipin(int iSeatNo,Req_UserChipin * pReq)
{
	if (E_GAME_CALL_SCORE!=m_GameStateMgr.GetGameState())
	{// �׶δ���
		pReq->iRes=10;
		send_data(iSeatNo,TABLE_MAIN, RSP_USER_CHIPIN, (BYTE*)pReq, sizeof(Req_UserChipin));
		return;
	}
	if (m_Players[iSeatNo].m_llUserChipIn>0)
	{// �в�����
		pReq->iRes=20;
		send_data(iSeatNo,TABLE_MAIN, RSP_USER_CHIPIN, (BYTE*)pReq, sizeof(Req_UserChipin));
		return;
	}
	m_Players[iSeatNo].m_llUserChipIn=pReq->lScore;
	send_table_data(TABLE_MAIN, RSP_USER_CHIPIN, (BYTE*)pReq, sizeof(Req_UserChipin));

	//��������мҶ��Ѿ���ע������ǰ������ע����
	vector<TChairID> vecChairID=GetPlayersNoOp2();
	if(vecChairID.size()==0)
	{
		m_GameStateMgr.SwitchGameState();
	}
}

void CGameTable::OnUserSendFinish(int iSeatNo)
{
	Rsp_SendFinish rsp;
	rsp.iSeatNo=iSeatNo;
	rsp.llUserID=m_Players[iSeatNo].m_llUserID;

	if (E_GAME_SEND_CARD!=m_GameStateMgr.GetGameState())
	{// �׶δ���
		rsp.iRes=10;
		send_data(iSeatNo,TABLE_MAIN, RSP_SEND_FINISH, (BYTE*)&rsp, sizeof(Rsp_SendFinish));
		return;
	}
	if (m_Players[iSeatNo].m_cbUserSendFinish>0)
	{// �в�����
		rsp.iRes=20;
		send_data(iSeatNo,TABLE_MAIN, RSP_SEND_FINISH, (BYTE*)&rsp, sizeof(Rsp_SendFinish));
		return;
	}
	m_Players[iSeatNo].m_cbUserSendFinish=1;

	send_table_data(TABLE_MAIN, RSP_SEND_FINISH, (BYTE*)&rsp, sizeof(Rsp_SendFinish));

	//���������Ҷ����궯��������ǰ����ϴ�ơ����ƻ���
	vector<TChairID> vecChairID=GetPlayersNoOp3();
	if(vecChairID.size()==0)
	{
		m_GameStateMgr.SwitchGameState();
	}
}

void CGameTable::OnUserShowFinish(int iSeatNo)
{
	Rsp_ShowFinish rsp;
	rsp.iSeatNo=iSeatNo;
	rsp.llUserID=m_Players[iSeatNo].m_llUserID;

	if (E_GAME_SHOW_CARD!=m_GameStateMgr.GetGameState())
	{// �׶δ���
		rsp.iRes=10;
		send_data(iSeatNo,TABLE_MAIN, RSP_SHOW_FINISH, (BYTE*)&rsp, sizeof(Rsp_ShowFinish));
		return;
	}
	if (m_Players[iSeatNo].m_cbUserShowFinish>0)
	{// �в�����
		rsp.iRes=20;
		send_data(iSeatNo,TABLE_MAIN, RSP_SHOW_FINISH, (BYTE*)&rsp, sizeof(Rsp_ShowFinish));
		return;
	}
	m_Players[iSeatNo].m_cbUserShowFinish=1;

	send_table_data(TABLE_MAIN, RSP_SHOW_FINISH, (BYTE*)&rsp, sizeof(Rsp_ShowFinish));

	//���������Ҷ����궯��������ǰ�������ƻ���
	vector<TChairID> vecChairID=GetPlayersNoOp4();
	if(vecChairID.size()==0)
	{
		m_GameStateMgr.SwitchGameState();
	}
}

// ��Ӧ������Ϣ
void CGameTable::OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen)
{
	switch(iSubCode)
	{
	case REQ_USER_CALL_BANKER://�û���ׯ
		{
			Req_UserCallBanker *callBanker = (Req_UserCallBanker*)pData;
			if (NULL!=callBanker)
			{
				OnUserCallBanker(iSeatNo,callBanker);
			}
			break;
		}
	case REQ_USER_KILL://ɢ��ɱ����С
		{
			Req_UserKill *pUserKill = (Req_UserKill*)pData;
			if (NULL!=pUserKill)
			{
				OnUserKill(iSeatNo,pUserKill);
			}
			break;
		}
	case REQ_USER_CHIPIN://�û���ע
		{
			Req_UserChipin *pUserChipin = (Req_UserChipin*)pData;
			if (NULL!=pUserChipin)
			{
				OnUserChipin(iSeatNo,pUserChipin);
			}
			break;
		}
	case REQ_SEND_FINISH://�ͻ�������ϴ�ơ����ƶ���
		{
			OnUserSendFinish(iSeatNo);
			break;
		}
	case REQ_SHOW_FINISH://�ͻ���������ƶ���
		{
			OnUserShowFinish(iSeatNo);
			break;
		}
	default:
		{
			break;
		}
	}
}

// ����
int CGameTable::OnAccounts(int iSeatNo)
{
	return 0;
}

//��Ϸ����
int CGameTable::OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	COften::OutputInfo("������Ϸ����");

	// ��Ϸ������ʼ��
	OnInit();

	return 0;
}

void CGameTable::SendGameEndList()
{
	//��Ϸһ�ֽ���ʱ
	//Rsp_GameEnd_List_MAX rsp;
	Rsp_GameEnd_List rsp;
	TChip	m_lGameScore[GAME_PLAYER_COUNT]={0};//������Ϣ
	TChip   llRevenueSum=0;//��˰����
	SEAT_INFO *BankerSeatInfo=NULL;
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
		int seat_no=seatInfo->pSingleUser->get_seat_no();
		if (seat_no==m_wBankerChairID)
		{// �û�����
			BankerSeatInfo=seatInfo;
			continue;
		}

		//add by Ivan_han 20131021
		if(seatInfo->pSingleUser->get_seat_no()<0||seatInfo->pSingleUser->get_seat_no()>=GAME_PLAYER_COUNT)
			continue;
		if(seatInfo->pSingleUser->get_user_id()!=m_Players[seatInfo->pSingleUser->get_seat_no()].m_llUserID)
			continue;

		//�Ա��˿�
		if (m_GameLogic.CompareCard(m_Players[seat_no].m_cbUserCardData,m_Players[m_wBankerChairID].m_cbUserCardData,MAX_COUNT,2)==true) 
		{
			m_lGameScore[seat_no]+=m_Players[seat_no].m_CardTypeMulti*m_Players[seat_no].m_llUserChipIn;
			m_lGameScore[m_wBankerChairID]-=m_Players[seat_no].m_CardTypeMulti*m_Players[seat_no].m_llUserChipIn;
		}
		else
		{
			m_lGameScore[seat_no]-=m_Players[m_wBankerChairID].m_CardTypeMulti*m_Players[seat_no].m_llUserChipIn;
			m_lGameScore[m_wBankerChairID]+=m_Players[m_wBankerChairID].m_CardTypeMulti*m_Players[seat_no].m_llUserChipIn;
		}

		Rsp_GameEnd GameEnd;
		GameEnd.llUserID =seatInfo->pSingleUser->get_user_id();
		GameEnd.iSeatNo =seat_no;
		if (m_lGameScore[seat_no]>0)
		{
			GameEnd.lGameTax =m_lGameScore[seat_no]*(TChip)m_pRoomMgr->get_server_room_info().iRevenueRate/100;
			GameEnd.lGameScore =m_lGameScore[seat_no]-GameEnd.lGameTax;
			llRevenueSum+=GameEnd.lGameTax;
		}
		else
		{
			GameEnd.lGameTax =0;
			GameEnd.lGameScore =m_lGameScore[seat_no];
		}
		GameEnd.CardType=m_Players[seat_no].m_CardType;
		GameEnd.CardPoint=m_Players[seat_no].m_CardPoint;

		m_Players[seat_no].m_llGameTax=GameEnd.lGameTax;
		m_Players[seat_no].m_llGameScore=GameEnd.lGameScore;

		//send_table_data(TABLE_MAIN,RSP_GAME_END,(BYTE*)&GameEnd,sizeof(Rsp_GameEnd));
		memcpy(&rsp.m_GameEnds[rsp.nCount],&GameEnd,sizeof(Rsp_GameEnd));
        rsp.nCount+=1;
	}

	if(BankerSeatInfo!=NULL)
	{
		Rsp_GameEnd GameEnd;
		GameEnd.llUserID=BankerSeatInfo->pSingleUser->get_user_id();
		GameEnd.iSeatNo=m_wBankerChairID;
		if (m_lGameScore[m_wBankerChairID]>0)
		{
			GameEnd.lGameTax =m_lGameScore[m_wBankerChairID]*(TChip)m_pRoomMgr->get_server_room_info().iRevenueRate/100;
			GameEnd.lGameScore =m_lGameScore[m_wBankerChairID]-GameEnd.lGameTax;
			llRevenueSum+=GameEnd.lGameTax;
		}
		else
		{
			GameEnd.lGameTax =0;
			GameEnd.lGameScore =m_lGameScore[m_wBankerChairID];
		}
		GameEnd.CardType=m_Players[m_wBankerChairID].m_CardType;
		GameEnd.CardPoint=m_Players[m_wBankerChairID].m_CardPoint;

		m_Players[m_wBankerChairID].m_llGameTax=GameEnd.lGameTax;
		m_Players[m_wBankerChairID].m_llGameScore=GameEnd.lGameScore;

		//send_table_data(TABLE_MAIN,RSP_GAME_END,(BYTE*)&GameEnd,sizeof(Rsp_GameEnd));
		memcpy(&rsp.m_GameEnds[rsp.nCount],&GameEnd,sizeof(Rsp_GameEnd));
		rsp.nCount+=1;
	}
	send_table_data(TABLE_MAIN,RSP_GAME_END_LIST,(BYTE*)&rsp,sizeof(Rsp_GameEnd_List)/*rsp.getLength()*/);

	//д��
	Rsp_GameEnd_List* pReal=&rsp;
	for(int i=0;i<pReal->nCount;i++)
	{
		Rsp_GameEnd *pGameEnd=&pReal->m_GameEnds[i];
		CMD_WRITE_SCORE sendData;
		sendData.lRevenue=pGameEnd->lGameTax;
		if(pGameEnd->lGameScore>0)
		{
			sendData.iWin=1;
			sendData.lRevenue=pGameEnd->lGameTax;
			sendData.lGold=pGameEnd->lGameScore;
			sendData.lExp=0;
		}
		else
		{
			sendData.iLost=1;
			sendData.lGold=pGameEnd->lGameScore;
			sendData.lExp=0;
		}
        OnUserAccountsWrite(pGameEnd->iSeatNo,sendData);
#ifdef _DEBUG
		//printf("һ����Ϸ���� �û�ID=%I64d ��λ��=%d ��Ϸ˰��=%I64d ��������=%I64d ����=%d ����=%d \n",pGameEnd->llUserID,pGameEnd->iSeatNo,pGameEnd->lGameTax,pGameEnd->lGameScore,(int)pGameEnd->CardType,(int)pGameEnd->CardPoint);
		//char szBuf[256]={0};
		//sprintf(szBuf, "һ����Ϸ���� �û�ID=%I64d ��λ��=%d ��Ϸ˰��=%I64d ��������=%I64d ����=%d ����=%d ",pGameEnd->llUserID,pGameEnd->iSeatNo,pGameEnd->lGameTax,pGameEnd->lGameScore,(int)pGameEnd->CardType,(int)pGameEnd->CardPoint);
		//write_log(true, 0, szBuf, 256);
#endif
	}
}

// ����֮ǰ
int CGameTable::OnLeaveSeatBefore(LONGLONG lUserId,int iSeatNo)
{
	////ׯ��������������ѡׯ
	//if(lUserId==m_wOldBankerUserID)
	//{
	//	m_wOldBankerUserID=0;
	//}
	//������뿪���¼���ʱ��Ҫ������ׯ
	vector<TUserID>::iterator p;
	p=find(m_vecOldUserIDs.begin(),m_vecOldUserIDs.end(),lUserId);
	if(p!=m_vecOldUserIDs.end())
	{
		m_wOldBankerUserID=0;
	}
	return 0;
}

// ����֮��
int CGameTable::OnLeaveSeatLast(int iSeatNo)
{
	return 0;
}

// ��ȡ̨��
void CGameTable::TradeFee()
{

}

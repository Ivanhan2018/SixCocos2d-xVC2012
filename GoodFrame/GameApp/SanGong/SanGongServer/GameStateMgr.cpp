#include "stdafx.h"
#include "GameStateMgr.h"
#include "GameTable.h"
#include "Config.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FreeGameState::FreeGameState(GameStateMgr *pGameStateMgr): m_pGameStateMgr(pGameStateMgr)
{

}
FreeGameState::~FreeGameState()
{

}

bool FreeGameState::Enter()
{
	if(m_pGameStateMgr==NULL)
		return false;

	return true;
}

bool FreeGameState::Leave()
{
	if(m_pGameStateMgr==NULL)
		return false;

	return true;
}

e_GameState FreeGameState::GetState()
{
	return E_GAME_FREE;
}


int FreeGameState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pGameStateMgr==NULL)
		return 0;

	 if (1 == iIDEvent)
	 {

	 }
	 return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CallBankerGameState::CallBankerGameState(GameStateMgr *pGameStateMgr): m_pGameStateMgr(pGameStateMgr)
{

}
CallBankerGameState::~CallBankerGameState()
{

}

bool CallBankerGameState::Enter()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	// 发送可以抢庄消息
	Rsp_CallBankerNotify callBanker;
	//callBanker.byGameState = E_GAME_CALL_BANKER;
	callBanker.iServerSecs = TIME_CALL_BANKER/1000;
	m_pGameStateMgr->m_pGameTable->send_table_data(TABLE_MAIN, RSP_CALL_BANKER_NOTIFY, (BYTE*)&callBanker, sizeof(Rsp_CallBankerNotify));

	m_EnterTime=CGameTable::GetTickCount64();
	m_pGameStateMgr->m_pGameTable->set_table_timer(IDI_CALL_BANKER,SangongConfig::Instance().GetCallBankerTime()/*TIME_CALL_BANKER*/);
	return true;
}

bool CallBankerGameState::Leave()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	//add by Ivan_han 20131024
	bool ret=m_pGameStateMgr->m_pGameTable->OverCallBanker(true);

	//发送骰子点数消息
	m_pGameStateMgr->m_pGameTable->SendCallBankerResult(true,RSP_DICE_NOTIFY);

	m_pGameStateMgr->m_pGameTable->kill_table_timer(IDI_CALL_BANKER);
	m_EnterTime=0;
	return true;
}

e_GameState CallBankerGameState::GetState()
{
	return E_GAME_CALL_BANKER;
}


int CallBankerGameState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pGameStateMgr==NULL)
		return 0;

	if(IDI_CALL_BANKER == iIDEvent)
	{
		m_pGameStateMgr->SwitchGameState();
		return 0;
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CallBankerEndGameState::CallBankerEndGameState(GameStateMgr *pGameStateMgr): m_pGameStateMgr(pGameStateMgr)
{

}
CallBankerEndGameState::~CallBankerEndGameState()
{

}

bool CallBankerEndGameState::Enter()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	m_EnterTime=CGameTable::GetTickCount64();
	m_pGameStateMgr->m_pGameTable->set_table_timer(IDI_CALL_BANKER_END,SangongConfig::Instance().GetCallBankerEndTime()/*TIME_CALL_BANKER_END*/);
	return true;
}

bool CallBankerEndGameState::Leave()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	//发送抢庄结果消息
	m_pGameStateMgr->m_pGameTable->SendCallBankerResult(true,RSP_CALL_BANKER_RESULT);

	m_pGameStateMgr->m_pGameTable->kill_table_timer(IDI_CALL_BANKER_END);
	m_EnterTime=0;
	return true;
}

e_GameState CallBankerEndGameState::GetState()
{
	return E_GAME_CALL_BANKER_END;
}


int CallBankerEndGameState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pGameStateMgr==NULL)
		return 0;

	if(IDI_CALL_BANKER_END == iIDEvent)
	{
		m_pGameStateMgr->SwitchGameState();
		return 0;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 CallScoreGameState::CallScoreGameState(GameStateMgr *pGameStateMgr): m_pGameStateMgr(pGameStateMgr)
 {

 }

 CallScoreGameState::~CallScoreGameState()
 {

 }

 bool CallScoreGameState::Enter()
 {
	 if(m_pGameStateMgr==NULL)
		 return false;
	 if(m_pGameStateMgr->m_pGameTable==NULL)
		 return false;
	 m_EnterTime=CGameTable::GetTickCount64();
	 m_pGameStateMgr->m_pGameTable->set_table_timer(IDI_CALL_SCORE,SangongConfig::Instance().GetCallScoreTime()/*TIME_CALL_SCORE*/);
	 return true;
 }

 bool CallScoreGameState::Leave()
 {
	 if(m_pGameStateMgr==NULL)
		 return false;
	 if(m_pGameStateMgr->m_pGameTable==NULL)
		 return false;

	 m_pGameStateMgr->m_pGameTable->SendUserDefaultChipin();

	 m_pGameStateMgr->m_pGameTable->kill_table_timer(IDI_CALL_SCORE);
	 m_EnterTime=0;
	 return true;
 }
 
e_GameState CallScoreGameState::GetState()
{
	  return E_GAME_CALL_SCORE;
}

int CallScoreGameState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pGameStateMgr==NULL)
		return 0;

	if(IDI_CALL_SCORE == iIDEvent)
	{
		m_pGameStateMgr->SwitchGameState();
		return 0;
	}

	return 0;
 }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CallScoreEndGameState::CallScoreEndGameState(GameStateMgr *pGameStateMgr): m_pGameStateMgr(pGameStateMgr)
{

}

CallScoreEndGameState::~CallScoreEndGameState()
{

}

bool CallScoreEndGameState::Enter()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	// 发送下注结束消息
	m_pGameStateMgr->m_pGameTable->send_table_data(TABLE_MAIN, RSP_CALL_SCORE_END_NOTIFY, (BYTE*)0,0);

	m_EnterTime=CGameTable::GetTickCount64();
	m_pGameStateMgr->m_pGameTable->set_table_timer(IDI_CALL_SCORE_END,SangongConfig::Instance().GetCallScoreEndTime()/*TIME_CALL_SCORE_END*/);
	return true;
}

bool CallScoreEndGameState::Leave()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	m_pGameStateMgr->m_pGameTable->kill_table_timer(IDI_CALL_SCORE_END);
	m_EnterTime=0;
	return true;
}

e_GameState CallScoreEndGameState::GetState()
{
	return E_GAME_CALL_SCORE_END;
}

int CallScoreEndGameState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pGameStateMgr==NULL)
		return 0;

	if(IDI_CALL_SCORE_END == iIDEvent)
	{
		m_pGameStateMgr->SwitchGameState();
		return 0;
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SendCardGameState::SendCardGameState(GameStateMgr *pGameStateMgr): m_pGameStateMgr(pGameStateMgr)
{

}

SendCardGameState::~SendCardGameState()
{

}

bool SendCardGameState::Enter()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	//发送发牌消息
	m_pGameStateMgr->m_pGameTable->SendCard();

	m_EnterTime=CGameTable::GetTickCount64();

	/*
		add by Ivan_han 20131102
		客户端做完洗牌、发牌动画的时间=0.45n+2.5，n是本局实际人数
		服务器端留3秒冗余时间
		所以10秒改为0.45n+5.5,即n=2-5,分别为6.4秒，6.85秒，7.3秒，7.75秒
	*/
	vector<SEAT_INFO*> vecSeatInfo=m_pGameStateMgr->m_pGameTable->GetPlayers(false);
	int nSize=vecSeatInfo.size();
	int nSeverSendCardTime=450*nSize+5500;
	m_pGameStateMgr->m_pGameTable->set_table_timer(IDI_SEND_CARD,nSeverSendCardTime);
	return true;
}

bool SendCardGameState::Leave()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;
	m_pGameStateMgr->m_pGameTable->kill_table_timer(IDI_SEND_CARD);
	m_EnterTime=0;
	return true;
}

e_GameState SendCardGameState::GetState()
{
	return E_GAME_SEND_CARD;
}

int SendCardGameState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pGameStateMgr==NULL)
		return 0;

	if(IDI_SEND_CARD == iIDEvent)
	{
		m_pGameStateMgr->SwitchGameState();
		return 0;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShowCardGameState::ShowCardGameState(GameStateMgr *pGameStateMgr): m_pGameStateMgr(pGameStateMgr)
{

}

ShowCardGameState::~ShowCardGameState()
{

}

bool ShowCardGameState::Enter()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;

	//add by Ivan_han 20131104
	m_pGameStateMgr->m_pGameTable->SendGameEndList();

	m_EnterTime=CGameTable::GetTickCount64();

	/*
		add by Ivan_han 20131104
		客户端做完比牌动画的时间=2.5n+3，n是本局实际人数
		服务器端留3秒冗余时间
		所以10秒改为2.5n+6,即n=2-5,分别为11秒，13.5秒，16秒，18.5秒
	*/
	vector<SEAT_INFO*> vecSeatInfo=m_pGameStateMgr->m_pGameTable->GetPlayers(false);
	int nSize=vecSeatInfo.size();
	int nSeverShowCardTime=2500*nSize+6000;
	m_pGameStateMgr->m_pGameTable->set_table_timer(IDI_SHOW_CARD,nSeverShowCardTime);
	return true;
}

bool ShowCardGameState::Leave()
{
	if(m_pGameStateMgr==NULL)
		return false;
	if(m_pGameStateMgr->m_pGameTable==NULL)
		return false;
	m_pGameStateMgr->m_pGameTable->kill_table_timer(IDI_SHOW_CARD);
	m_EnterTime=0;
	return true;
}

e_GameState ShowCardGameState::GetState()
{
	return E_GAME_SHOW_CARD;
}

int ShowCardGameState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pGameStateMgr==NULL)
		return 0;

	if(IDI_SHOW_CARD == iIDEvent)
	{
		m_pGameStateMgr->SwitchGameState();
		return 0;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 GameStateMgr::GameStateMgr(CGameTable * pGameTable):m_pGameTable(pGameTable)
 {
	 m_pCurGameState=NULL;
	 m_FreeGameState.m_pGameStateMgr=this;
	 m_CallBankerGameState.m_pGameStateMgr=this;
	 m_CallBankerEndGameState.m_pGameStateMgr=this;
	 m_CallScoreGameState.m_pGameStateMgr=this;
	 m_CallScoreEndGameState.m_pGameStateMgr=this;
	 m_SendCardGameState.m_pGameStateMgr=this;
	 m_ShowCardGameState.m_pGameStateMgr=this;
 }


 e_GameState GameStateMgr::GetGameState()
 {
	 if(m_pCurGameState)
	 {
		 return m_pCurGameState->GetState();
	 }

	 return E_GAME_FREE;
 }


 void GameStateMgr::SwitchGameState()
 {
	 if (m_pCurGameState == NULL)
	 {
		 m_pCurGameState = &m_FreeGameState;
	 }
	 else 
	 {
		 m_pCurGameState->Leave();
		 if (m_pCurGameState == &m_FreeGameState)
		 {
			 m_pCurGameState = &m_CallBankerGameState;
		 }
		 else if (m_pCurGameState == &m_CallBankerGameState)
		 {
			 m_pCurGameState = &m_CallBankerEndGameState;
		 }
		 else if (m_pCurGameState == &m_CallBankerEndGameState)
		 {
			 m_pCurGameState = &m_CallScoreGameState;
		 }
		 else if (m_pCurGameState == &m_CallScoreGameState)
		 {
			 m_pCurGameState = &m_CallScoreEndGameState;
		 }
		 else if (m_pCurGameState == &m_CallScoreEndGameState)
		 {
			 m_pCurGameState = &m_SendCardGameState;
		 }
		 else if (m_pCurGameState == &m_SendCardGameState)
		 {
			 m_pCurGameState = &m_ShowCardGameState;
		 }
		 else
		 {
			 m_pCurGameState = &m_FreeGameState;
			 //时间到/时间未到，但所有玩家比牌完毕，通知骨架结束本局游戏
			 //m_pGameTable->OnGameFinish(0,0);
			 m_pGameTable->can_finish_game();
		 }
		 m_pCurGameState->Enter();
	 }
 }


 int GameStateMgr::OnGameBegin(bool bNeedCallBanker)
 {
	 if(m_pCurGameState)
	 {
		 m_pCurGameState->Leave();
	 }
	 //更新m_Players的用户ID
	 vector<SEAT_INFO*> vecSeatInfo=m_pGameTable->GetPlayers(true);
	 if(bNeedCallBanker)
	 {
		 //随机选一个庄家
		 int index=m_pGameTable->RandSetBanker(vecSeatInfo);

		 m_pCurGameState=&m_CallBankerGameState;
	 }
	 else
	 {
		
		 
		 m_pCurGameState=&m_CallScoreGameState;

		//发送抢庄结果消息
		m_pGameTable->SendCallBankerResult(false,RSP_CALL_BANKER_RESULT);

	 }
	 m_pCurGameState->Enter();
	 return 0;
 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
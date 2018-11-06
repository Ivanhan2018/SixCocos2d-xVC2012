#pragma once
#include"../GameMsg/CMD_SanGong.h"

class CGameTable;
class GameStateMgr;


//////////////////////////////////////////////////////////////////////////
//三公游戏状态
struct IGameState
{
	virtual ~IGameState(){}
	virtual bool Enter()=0;
	virtual bool Leave()=0;
	virtual e_GameState GetState()=0;
	// 桌子定时器响应
	virtual int OnTableTimer(int iTableNo, int iIDEvent)=0;
};

//空闲状态
class FreeGameState : public IGameState
{
public:
	FreeGameState(GameStateMgr *pGameStateMgr=NULL);
	~FreeGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
};


//抢庄状态
class CallBankerGameState : public IGameState
{
public:
	CallBankerGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallBankerGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//抢庄后、下注前状态
class CallBankerEndGameState : public IGameState
{
public:
	CallBankerEndGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallBankerEndGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};


//下注状态
class CallScoreGameState : public IGameState
{
public:
	CallScoreGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallScoreGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//下注后、摊牌前状态
class CallScoreEndGameState : public IGameState
{
public:
	CallScoreEndGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallScoreEndGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//洗牌、发牌状态
class SendCardGameState : public IGameState
{
public:
	SendCardGameState(GameStateMgr *pGameStateMgr=NULL);
	~SendCardGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//比牌状态
class ShowCardGameState : public IGameState
{
public:
	ShowCardGameState(GameStateMgr *pGameStateMgr=NULL);
	~ShowCardGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//三公游戏状态管理
class GameStateMgr
{
public:
	GameStateMgr(CGameTable * pGameTable=NULL);
	//获得当前游戏状态
	e_GameState GetGameState();
	//切换游戏状态
	void SwitchGameState();
	//游戏开始
	int OnGameBegin(bool bNeedCallBanker);
public:
	CGameTable * m_pGameTable;
	//游戏状态
	IGameState *         m_pCurGameState;//当前游戏状态
	FreeGameState        m_FreeGameState;//空闲状态
	CallBankerGameState  m_CallBankerGameState;//抢庄状态
	CallBankerEndGameState m_CallBankerEndGameState;//抢庄后、下注前状态
	CallScoreGameState   m_CallScoreGameState;//下注状态
	CallScoreEndGameState m_CallScoreEndGameState;//下注后、摊牌前状态
	SendCardGameState    m_SendCardGameState;//洗牌、发牌状态
	ShowCardGameState    m_ShowCardGameState;//比牌状态
};
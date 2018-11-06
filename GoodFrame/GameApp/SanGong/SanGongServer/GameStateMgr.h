#pragma once
#include"../GameMsg/CMD_SanGong.h"

class CGameTable;
class GameStateMgr;


//////////////////////////////////////////////////////////////////////////
//������Ϸ״̬
struct IGameState
{
	virtual ~IGameState(){}
	virtual bool Enter()=0;
	virtual bool Leave()=0;
	virtual e_GameState GetState()=0;
	// ���Ӷ�ʱ����Ӧ
	virtual int OnTableTimer(int iTableNo, int iIDEvent)=0;
};

//����״̬
class FreeGameState : public IGameState
{
public:
	FreeGameState(GameStateMgr *pGameStateMgr=NULL);
	~FreeGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
};


//��ׯ״̬
class CallBankerGameState : public IGameState
{
public:
	CallBankerGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallBankerGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//��ׯ����עǰ״̬
class CallBankerEndGameState : public IGameState
{
public:
	CallBankerEndGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallBankerEndGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};


//��ע״̬
class CallScoreGameState : public IGameState
{
public:
	CallScoreGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallScoreGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//��ע��̯��ǰ״̬
class CallScoreEndGameState : public IGameState
{
public:
	CallScoreEndGameState(GameStateMgr *pGameStateMgr=NULL);
	~CallScoreEndGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//ϴ�ơ�����״̬
class SendCardGameState : public IGameState
{
public:
	SendCardGameState(GameStateMgr *pGameStateMgr=NULL);
	~SendCardGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//����״̬
class ShowCardGameState : public IGameState
{
public:
	ShowCardGameState(GameStateMgr *pGameStateMgr=NULL);
	~ShowCardGameState();
	bool Enter();
	bool Leave();
	e_GameState GetState();
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	GameStateMgr *m_pGameStateMgr;
	unsigned long long m_EnterTime;
};

//������Ϸ״̬����
class GameStateMgr
{
public:
	GameStateMgr(CGameTable * pGameTable=NULL);
	//��õ�ǰ��Ϸ״̬
	e_GameState GetGameState();
	//�л���Ϸ״̬
	void SwitchGameState();
	//��Ϸ��ʼ
	int OnGameBegin(bool bNeedCallBanker);
public:
	CGameTable * m_pGameTable;
	//��Ϸ״̬
	IGameState *         m_pCurGameState;//��ǰ��Ϸ״̬
	FreeGameState        m_FreeGameState;//����״̬
	CallBankerGameState  m_CallBankerGameState;//��ׯ״̬
	CallBankerEndGameState m_CallBankerEndGameState;//��ׯ����עǰ״̬
	CallScoreGameState   m_CallScoreGameState;//��ע״̬
	CallScoreEndGameState m_CallScoreEndGameState;//��ע��̯��ǰ״̬
	SendCardGameState    m_SendCardGameState;//ϴ�ơ�����״̬
	ShowCardGameState    m_ShowCardGameState;//����״̬
};
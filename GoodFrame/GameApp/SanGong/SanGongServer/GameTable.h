#ifndef GAME_TABLE_H
#define GAME_TABLE_H

#include "ThreadGuard.h"
#include "IBaseTable.h"
#include "../GameMsg/CMD_SanGong.h"
#include "GameServerSkeleton.h"
#include "GameStateMgr.h"
#include "GameLogic.h"

//add by Ivan_han 20131008
//////////////////////////////////////////////////////////////////////////
// ��ʱ��ID
#define IDI_CALL_BANKER			1									//��ׯ
#define IDI_CALL_BANKER_END		2									//��ׯ����עǰ
#define IDI_CALL_SCORE			3									//��ע
#define IDI_CALL_SCORE_END		4									//��ע��̯��ǰ
#define IDI_SEND_CARD			5									//ϴ�ơ�����
#define IDI_SHOW_CARD			6									//����

// ��ʱ�����ʱ��(����һ�μ��л���Ϸ״̬)
#define TIME_CALL_BANKER		5000							    //��ׯʱ��
#define TIME_CALL_BANKER_END	1000								//old:��ׯ����עǰ��������4��
#define TIME_CALL_SCORE		    14000								//��עʱ��
#define TIME_CALL_SCORE_END		1000								//old:��ע��̯��ǰ
#define TIME_SEND_CARD			10000								//ϴ�ơ�����ʱ��
#define TIME_SHOW_CARD			10000								//����ʱ��


////����6������
//#define IDI_BANKER_START		1//��ʼʱ��
//#define IDI_PLAYER_START		2//��עʱ��
//#define IDI_CHANGE_BANKER		4//��ׯʱ��
//#define IDI_CONTINUE			5//����ʱ��
//////////////////////////////////////////////////////////////////////////

struct SinglePlayer
{
	SinglePlayer()
	{
		Init();
	}
	void Init()
	{
		memset(this, 0, sizeof(*this));
		m_byCallBanker=INVALID_BYTE;
	}
	TChip	m_Chip;				//����ʱ����
	TChip   m_llMaxChip;        //�����עC3
	TChip	m_llUserChipIn;				//��ע��Ϣ
	TUserID	m_llUserID;//Ϊ0��ʾ�뿪��������û��
	TCardData m_cbUserCardData[3];		//�˿�����
	TCardTypeMulti m_CardTypeMulti;//�˿����ݾ��������ͱ���
	TCardType m_CardType;
	TCardPoint m_CardPoint;
	unsigned char m_cbUserSendFinish;//ϴ�ơ�������ɱ�־={0,1}
	unsigned char m_cbUserShowFinish;//������ɱ�־={0,1}
	unsigned char m_byCallBanker;//��ׯ��־={255,0,1}
	TChip m_llGameTax;			//��Ϸ˰��
	TChip m_llGameScore;		//��������
};

class CGameTable : public IBaseTable
{
public:
	CGameTable(void);
	~CGameTable(void);

public:
	// ��ʼ��
	void OnInit();

	// ��Ӧ������Ϣ
	void OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen);

	// ����֮ǰ
	virtual int OnLeaveSeatBefore( LONGLONG lUserId, int iSeatNo);

	// ����֮��
	virtual int OnLeaveSeatLast(int iSeatNo);

public:
	//--- Ҫ�Ӹ���̳еĴ��麯�� --------------------------------

	// ����
	virtual int OnCut(LONGLONG lUserId);

	// ����������Ӧ�����������û����������¼����ʱ�Ż���Ӧ
	virtual int OnRecomeAfterCut(int iSeatNo);

	//��Ϸ��ʼ
	virtual int OnGameBegin();

	//��Ϸ����
	virtual int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	// ���Ӷ�ʱ����Ӧ
	virtual int OnTableTimer(int iTableNo, int iIDEvent);

	// ����
	virtual int OnRaiseHand(int iSeatNo);

	// ��ȡ̨��
	virtual void TradeFee();

	// ����
	virtual int OnAccounts(int iSeatNo);

	// �û�����
	virtual void OnUserSitDown(int iSeatNo);

public:
	//��ǰ����ʱ��
	static unsigned long long GetTickCount64();

    //ׯ�ҳ���ΪZ���мҳ���ΪX����������������ΪF���м�����ΪN
	static TChip calcC3(TChip Z,TChip X,TChip F,unsigned long long N);

	//��������б�
	vector<SEAT_INFO*> GetPlayers(bool bRefresh=false);

	//������ׯ����û��ѡ����ׯ���롾������������б�
	vector<TChairID> GetPlayersNoOp1(vector<TChairID> &vecCall,vector<TChairID> &vecNoCall);

	//����û��������ע���м��б�
	vector<TChairID> GetPlayersNoOp2();

	//����û������֪ͨ����������ϴ�ơ����ƶ���������б�
	vector<TChairID> GetPlayersNoOp3();

	//����û������֪ͨ������������ƶ���������б�
	vector<TChairID> GetPlayersNoOp4();

	//�����Ƿ���Ҫ������ׯ����
	bool CheckNeedCallBanker();

	//����
	void SendCard();

	//���ƻ���ׯ�ң�������������Ƶ��м��û�
	static bool CheckGoodCardToBanker(Rsp_SendCard_List *pRsp,TChairID wBankerChairID,TChairID &iSeatNo);

	//ɢ��ׯ��ɱ����С
	static bool CheckKillCardToBanker(Rsp_SendCard_List *pRsp,const vector<TChip> &vecUserChipIn,TChairID wBankerChairID);

	//˰ǰ��Ӯ������������Winner��ʾӮ���мҼ��ϣ�Loser��ʾ����мҼ���
	static vector<TChip> CheckCard(Rsp_SendCard_List *pRsp,const vector<TChip> &vecUserChipIn,TChairID wBankerChairID,int &iBankerIndex,vector<int> &WinnerIndex,vector<int> &LoserIndex);

	//����m_Players���û�ID���˿�����
	void SetPlayersCardData(Rsp_SendCard SendCard);

	//��ׯ���
	void SendCallBankerResult(bool bNeedCallBanker,int iSubCode);

	//ʱ�䵽��δ��ע���м�Ĭ��ѡ��C1
	void SendUserDefaultChipin();

	//����ׯ�Ҳ�������ׯ״̬<bTimeOver=trueʱ�䵽�ˣ�falseʱ��û��>
	bool OverCallBanker(bool bTimeOver);

	//���ѡһ��ׯ��
	int RandSetBanker(const vector<TChairID> &vecCall);

	//���ѡһ��ׯ��
	int RandSetBanker(const vector<SEAT_INFO*> &vecSeatInfo);

	// ��ׯ 
	void OnUserCallBanker(int iSeatNo,Req_UserCallBanker *callBanker);

	// ɢ��ɱ����С
	void OnUserKill(int iSeatNo,Req_UserKill * pReq);

	// ��ע
	void OnUserChipin(int iSeatNo,Req_UserChipin * pReq);

	// ϴ�ơ��������
	void OnUserSendFinish(int iSeatNo);

	// �������
	void OnUserShowFinish(int iSeatNo);

	// ��Ϸһ�ֽ��㣬֪ͨ�ͻ��˿�ʼ����
	void SendGameEndList();

public:
	//��Ϸ״̬����ʵ��������Ϸ��������
	GameStateMgr m_GameStateMgr;

	//ʵ�ַ��ơ����ͼ���С�����ͱ��ʵ���Ϸ�߼�
	CGameLogic m_GameLogic;

	//�û���һ����Ϸ�еĲ�����Ϣ���˿�����
	SinglePlayer m_Players[GAME_PLAYER_COUNT];

	//һ����Ϸ�е�ׯ���û�
	TChairID m_wBankerChairID;

	//ɢ�ɲ���ģʽ={0��ɢ�ɲ���,1ɱ����С,��}
	int m_nKillMode;

	//�������ӵ���
	unsigned int m_dice[2];

	//��ׯ����={0,1,��}
	unsigned int m_CallBankerNum;

	//��һ����Ϸ�е�ׯ���û�
	TUserID m_wOldBankerUserID;

	//��һ����Ϸ�е�����б�
	vector<TUserID> m_vecOldUserIDs;
};

#endif
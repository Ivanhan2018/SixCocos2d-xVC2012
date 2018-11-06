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
// 定时器ID
#define IDI_CALL_BANKER			1									//抢庄
#define IDI_CALL_BANKER_END		2									//抢庄后、下注前
#define IDI_CALL_SCORE			3									//下注
#define IDI_CALL_SCORE_END		4									//下注后、摊牌前
#define IDI_SEND_CARD			5									//洗牌、发牌
#define IDI_SHOW_CARD			6									//比牌

// 定时器间隔时间(触发一次即切换游戏状态)
#define TIME_CALL_BANKER		5000							    //抢庄时间
#define TIME_CALL_BANKER_END	1000								//old:抢庄后、下注前，丢骰子4秒
#define TIME_CALL_SCORE		    14000								//下注时间
#define TIME_CALL_SCORE_END		1000								//old:下注后、摊牌前
#define TIME_SEND_CARD			10000								//洗牌、发牌时间
#define TIME_SHOW_CARD			10000								//比牌时间


////网狐6人三公
//#define IDI_BANKER_START		1//开始时间
//#define IDI_PLAYER_START		2//下注时间
//#define IDI_CHANGE_BANKER		4//抢庄时间
//#define IDI_CONTINUE			5//继续时间
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
	TChip	m_Chip;				//入座时筹码
	TChip   m_llMaxChip;        //最大下注C3
	TChip	m_llUserChipIn;				//下注信息
	TUserID	m_llUserID;//为0表示离开或椅子上没人
	TCardData m_cbUserCardData[3];		//扑克数据
	TCardTypeMulti m_CardTypeMulti;//扑克数据决定的牌型倍率
	TCardType m_CardType;
	TCardPoint m_CardPoint;
	unsigned char m_cbUserSendFinish;//洗牌、发牌完成标志={0,1}
	unsigned char m_cbUserShowFinish;//比牌完成标志={0,1}
	unsigned char m_byCallBanker;//抢庄标志={255,0,1}
	TChip m_llGameTax;			//游戏税收
	TChip m_llGameScore;		//筹码增量
};

class CGameTable : public IBaseTable
{
public:
	CGameTable(void);
	~CGameTable(void);

public:
	// 初始化
	void OnInit();

	// 响应桌子消息
	void OnTableMsg(int iSeatNo, int iSubCode, const BYTE* pData, int iDataLen);

	// 离座之前
	virtual int OnLeaveSeatBefore( LONGLONG lUserId, int iSeatNo);

	// 离座之后
	virtual int OnLeaveSeatLast(int iSeatNo);

public:
	//--- 要从父类继承的纯虚函数 --------------------------------

	// 断线
	virtual int OnCut(LONGLONG lUserId);

	// 断线重入响应，仅仅在用用户名、密码登录房间时才会响应
	virtual int OnRecomeAfterCut(int iSeatNo);

	//游戏开始
	virtual int OnGameBegin();

	//游戏结束
	virtual int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	// 桌子定时器响应
	virtual int OnTableTimer(int iTableNo, int iIDEvent);

	// 举手
	virtual int OnRaiseHand(int iSeatNo);

	// 收取台费
	virtual void TradeFee();

	// 结算
	virtual int OnAccounts(int iSeatNo);

	// 用户坐下
	virtual void OnUserSitDown(int iSeatNo);

public:
	//当前毫秒时刻
	static unsigned long long GetTickCount64();

    //庄家筹码为Z，闲家筹码为X，房间筹码最大限制为F，闲家人数为N
	static TChip calcC3(TChip Z,TChip X,TChip F,unsigned long long N);

	//本局玩家列表
	vector<SEAT_INFO*> GetPlayers(bool bRefresh=false);

	//本局抢庄环节没有选择【抢庄】与【不抢】的玩家列表
	vector<TChairID> GetPlayersNoOp1(vector<TChairID> &vecCall,vector<TChairID> &vecNoCall);

	//本局没有主动下注的闲家列表
	vector<TChairID> GetPlayersNoOp2();

	//本局没有主动通知服务器做完洗牌、发牌动画的玩家列表
	vector<TChairID> GetPlayersNoOp3();

	//本局没有主动通知服务器做完比牌动画的玩家列表
	vector<TChairID> GetPlayersNoOp4();

	//本局是否需要经过抢庄环节
	bool CheckNeedCallBanker();

	//发牌
	void SendCard();

	//好牌换给庄家，输出被换掉好牌的闲家用户
	static bool CheckGoodCardToBanker(Rsp_SendCard_List *pRsp,TChairID wBankerChairID,TChairID &iSeatNo);

	//散仙庄家杀大赔小
	static bool CheckKillCardToBanker(Rsp_SendCard_List *pRsp,const vector<TChip> &vecUserChipIn,TChairID wBankerChairID);

	//税前输赢情况，输出参数Winner表示赢的闲家集合，Loser表示输的闲家集合
	static vector<TChip> CheckCard(Rsp_SendCard_List *pRsp,const vector<TChip> &vecUserChipIn,TChairID wBankerChairID,int &iBankerIndex,vector<int> &WinnerIndex,vector<int> &LoserIndex);

	//更新m_Players的用户ID、扑克数据
	void SetPlayersCardData(Rsp_SendCard SendCard);

	//抢庄结果
	void SendCallBankerResult(bool bNeedCallBanker,int iSubCode);

	//时间到，未下注的闲家默认选择C1
	void SendUserDefaultChipin();

	//决定庄家并结束抢庄状态<bTimeOver=true时间到了，false时间没到>
	bool OverCallBanker(bool bTimeOver);

	//随机选一个庄家
	int RandSetBanker(const vector<TChairID> &vecCall);

	//随机选一个庄家
	int RandSetBanker(const vector<SEAT_INFO*> &vecSeatInfo);

	// 抢庄 
	void OnUserCallBanker(int iSeatNo,Req_UserCallBanker *callBanker);

	// 散仙杀大赔小
	void OnUserKill(int iSeatNo,Req_UserKill * pReq);

	// 下注
	void OnUserChipin(int iSeatNo,Req_UserChipin * pReq);

	// 洗牌、发牌完毕
	void OnUserSendFinish(int iSeatNo);

	// 比牌完毕
	void OnUserShowFinish(int iSeatNo);

	// 游戏一局结算，通知客户端开始比牌
	void SendGameEndList();

public:
	//游戏状态管理，实现三公游戏基本规则
	GameStateMgr m_GameStateMgr;

	//实现发牌、牌型及大小、牌型倍率的游戏逻辑
	CGameLogic m_GameLogic;

	//用户在一局游戏中的操作信息、扑克数据
	SinglePlayer m_Players[GAME_PLAYER_COUNT];

	//一局游戏中的庄家用户
	TChairID m_wBankerChairID;

	//散仙操作模式={0无散仙操作,1杀大赔小,…}
	int m_nKillMode;

	//两个骰子点数
	unsigned int m_dice[2];

	//抢庄人数={0,1,…}
	unsigned int m_CallBankerNum;

	//上一局游戏中的庄家用户
	TUserID m_wOldBankerUserID;

	//上一局游戏中的玩家列表
	vector<TUserID> m_vecOldUserIDs;
};

#endif
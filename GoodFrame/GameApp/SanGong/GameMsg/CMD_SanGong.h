#ifndef CMD_SANGONG_H
#define CMD_SANGONG_H

/*
**description:
******CS  -> 客户端发往服务器的
******SC  -> 服务器发往客户端的
******CSG -> 客户端/服务器互用
******MAIN -> 主消息
******SUB -> 子消息
*/

#include "PublicMacro.h"
#include <string.h>

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

// 游戏状态:5+1+14+1+(0.45n+5.5)+(2.5n+6)
enum e_GameState:unsigned char
{
	E_GAME_FREE = 0,		// 空闲状态，游戏没开始或已结束
	//E_GAME_START,			// 开始状态
	E_GAME_CALL_BANKER,	    // 抢庄状态
	E_GAME_CALL_BANKER_END,	    // 抢庄后、下注前状态
	E_GAME_CALL_SCORE,		// 下注状态
	E_GAME_CALL_SCORE_END,		// 下注后、摊牌前状态
	E_GAME_SEND_CARD,		// 洗牌、发牌状态
	E_GAME_SHOW_CARD,		// 比牌状态
	//E_GAME_ERROR,           // 错误状态 
};

//////////////////////////////////////////////////////////////////////////
//相关宏定义
#define GAME_PLAYER_COUNT			(5)									// 游戏人数

//无效数值
#define INVALID_BYTE				((unsigned char)(0xFF))						//无效数值
#define INVALID_WORD				((unsigned short int)(0xFFFF))				//无效数值
#define INVALID_DWORD				((unsigned long)(0xFFFFFFFF))				//无效数值
#define INVALID_TABLE				INVALID_DWORD						//无效桌子
#define INVALID_CHAIR				INVALID_WORD						//无效椅子

#define LO4(c)           ((((unsigned char)(c)) & 0x0f))
#define HI4(c)           ((((unsigned char)(c)) & 0xf0)>>4)
#define CARD_VALUE(cbCardData) LO4(cbCardData)//获取数值
#define CARD_COLOR(cbCardData) HI4(cbCardData)//获取花色
#define CARD_COLOR_C(cbCardData) (CARD_TYPE)(CARD_COLOR(cbCardData)<4?(4-CARD_COLOR(cbCardData)):(cbCardData-73))//获取客户端扑克类型
//////////////////////////////////////////////////////////////////////////////////
//带语义数据类型
typedef long long TChip;//筹码和下注的数额
typedef unsigned long long TUserID;//用户ID
typedef unsigned int TTableID;//桌子号
typedef unsigned short int TChairID;//椅子号，用户位置
typedef unsigned char TCardData;//单张扑克
typedef unsigned char TCardType;//牌型={1散牌和7-9点,2三公,4炸弹,5王炸,6爆玖}
typedef unsigned char TCardTypeMulti;//牌型倍率={9,8,7,6,5,3,2,1}
typedef unsigned char TCardPoint;//牌的点数={0,…,9}
typedef int TError;//0表示成功,10表示阶段错误，20表示有操作过，30表示不是散仙玩家
///////////////////////////////////////////////////////////////////////////////

/**************************************************************************
//三公房间服务器
**************************************************************************/
enum PROTOCOL_THREEKING
{
	REQ_USER_CALL_BANKER=400,//用户抢庄
	REQ_USER_CHIPIN,//用户下注
	REQ_SEND_FINISH,//客户端做完洗牌、发牌动画,无对应结构体，对机器人或正常客户端，过滤发牌动作,直接发送"洗牌、发牌完成"
	REQ_USER_KILL,//散仙杀大赔小
	REQ_SHOW_FINISH,//客户端做完比牌动画,无对应结构体，对机器人或正常客户端，过滤比牌动作,直接发送"比牌完成"
	
	RSP_CALL_BANKER_NOTIFY=500,//可以抢庄通知
	RSP_USER_CALL_BANKER,//用户抢庄返回
	RSP_DICE_NOTIFY,//骰子点数消息
	RSP_CALL_BANKER_RESULT,//抢庄结果
	RSP_USER_CHIPIN,//用户下注
	RSP_CALL_SCORE_END_NOTIFY,//下注结束消息,无对应结构体
	RSP_SEND_CARD_LIST,//发牌消息
	RSP_SEND_FINISH,//客户端做完洗牌、发牌动画返回
	RSP_GAME_END_LIST,//游戏结束
	RSP_USER_KILL,//散仙杀大赔小返回
	RSP_BANKER_CHIPIN_SENDCARD_INFO,//中途进桌的玩家收到的同步消息
	RSP_SHOW_FINISH,//客户端做完比牌动画返回

	// 为了防止消息ID重复。此消息ID从600开始不能大于等于2000 (因为在GameSkeletonMsgCode.h中也用到了桌子消息)
};

struct Rsp_BankerChipinSendCardInfo
{
	Rsp_BankerChipinSendCardInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	e_GameState curGameState;//当前游戏状态={E_GAME_CALL_BANKER,E_GAME_CALL_BANKER_END,E_GAME_CALL_SCORE,E_GAME_CALL_SCORE_END,E_GAME_SEND_CARD,E_GAME_SHOW_CARD}
	unsigned long long llElapsedMs;//当前游戏状态消逝的毫秒数，目前填0
	unsigned char byCallBanker[GAME_PLAYER_COUNT];//用户抢庄标志={255,0,1}
	TChairID wBankerChairID;//庄家用户={INVALID_CHAIR,0,1,2,3,4}
	TChip llUserChipIn[GAME_PLAYER_COUNT];//用户下注信息
	TCardData cbUserCardData[GAME_PLAYER_COUNT][3];//用户扑克
	TChip llGameTax[GAME_PLAYER_COUNT];//用户游戏税收
	TChip llGameScore[GAME_PLAYER_COUNT];//用户筹码增量
};

// 抢庄环节开始后下发的可以抢庄消息
struct Rsp_CallBankerNotify
{
	Rsp_CallBankerNotify()
	{
		memset(this, 0, sizeof(*this));
	}
	int iServerSecs;
};

// 抢庄环节的用户抢庄消息
struct Req_UserCallBanker
{
	Req_UserCallBanker()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TTableID iSeatNo;
	bool bCall;	// 是否抢庄
	//S->C使用的字段
	TError iRes;
};

//下注环节的散仙杀大赔小消息
struct Req_UserKill
{
	Req_UserKill()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TTableID iSeatNo;
	int KillMode;//散仙操作模式={0无散仙操作,1杀大赔小,…}
	//S->C使用的字段
	TError iRes;
};

//下注环节闲家的下注消息
struct Req_UserChipin
{
	Req_UserChipin()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TTableID iSeatNo;
	TChip lScore;//下注数目,C1,C2,C3中的一个值
	//S->C使用的字段
	TError iRes;
};


//抢庄结果，对应RSP_CALL_BANKER_RESULT
//庄家确定后下发的庄家位置、单个闲家的筹码下注额
// 抢庄后、下注前环节开始后下发的骰子点数消息，无Rsp_DiceNotify
struct Rsp_BankerC3Info
{
	Rsp_BankerC3Info()
	{
		memset(this, 0, sizeof(*this));
	}
	bool bNeedCallBanker;//是否经过抢庄环节
	unsigned int dice[2];//两个骰子点数
	unsigned int CallBankerNum;//抢庄人数={0,1,…},如果为1不丢骰子
	TChairID wBankerUser;
	TChip C3;//最大的筹码下注额
	TChip C2;//中间的筹码下注额=C3/2
	TChip C1;//最小的筹码下注额=C3/4
};

struct Rsp_SendCard
{
	Rsp_SendCard()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TCardData cbUserCardData[3];
};

//进入洗牌、发牌环节的游戏发牌，对应RSP_SEND_CARD_LIST
struct Rsp_SendCard_List
{
	Rsp_SendCard_List(){memset(this, 0, sizeof(*this));}
	unsigned int nCount;
	Rsp_SendCard m_SendCards[GAME_PLAYER_COUNT];
};

//洗牌、发牌环节庄家和闲家的动画完毕返回，对应RSP_SEND_FINISH
struct Rsp_SendFinish
{
	Rsp_SendFinish()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TError iRes;
};

//比牌环节庄家和闲家的动画完毕返回，对应RSP_SHOW_FINISH
struct Rsp_ShowFinish
{
	Rsp_ShowFinish()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TError iRes;
};

struct Rsp_GameEnd
{
	Rsp_GameEnd()
	{
		memset(this, 0, sizeof(*this));
	}
	TUserID	llUserID;
	TChairID iSeatNo;
	TChip lGameTax;				//游戏税收
	TChip lGameScore;			//筹码增量
	TCardType CardType;
	TCardPoint CardPoint;
};

//一局游戏结束时的游戏结算，对应RSP_GAME_END_LIST
struct Rsp_GameEnd_List
{
	Rsp_GameEnd_List(){memset(this, 0, sizeof(*this));}
	unsigned int nCount;
    Rsp_GameEnd m_GameEnds[GAME_PLAYER_COUNT];
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
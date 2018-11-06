#ifndef CMD_PAOHUZI_HEAD_FILE
#define CMD_PAOHUZI_HEAD_FILE
#include "common/Define.h"
///////////////////////////////////////////////////////////////////////////////////////
//公共宏定义

//#define KIND_ID						ID_LAND						        //游戏 I D
#define GAME_PLAYER					3									//游戏人数
//#define GAME_NAME					TEXT("斗地主游戏")					//游戏名字
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_GOLD)	//游戏类型
#define MAX_COUNT					20
#define GAME_WIDTH				1024
#define GAME_HEIGHT				738

//聊天组件的位置
#define CHAT_DLG_X					740                     
#define CHAT_DLG_Y					650
////////////////////////////////////////////////////////////////////////////////////////

//服务器命令结构
#define REC_SUB_S_SEND_CARD				100									//发牌命令
#define REC_SUB_S_LAND_SCORE			101									//叫分命令
#define REC_SUB_S_GAME_START			102									//游戏开始
#define REC_SUB_S_OUT_CARD				103									//用户出牌
#define REC_SUB_S_PASS_CARD				104									//放弃出牌
#define REC_SUB_S_GAME_END				105									//游戏结束
#define REC_SUB_S_SPRING                106                                 //春天消息
#define REC_SUB_S_OUTCARD_TIMES         108                                 //出牌次数    
#define REC_SUB_S_LOOK_TRUSTEE          109                                 //托管查询
#define REC_SUB_S_WARN_INFO             111                                 //报警消息
#define REC_SUB_S_OFFLINE_CARD          125                                 //断线出牌
#define REC_SUB_S_USER_OFFLINE          150                                 //玩家断线
#define REC_SUB_S_DAOFAN                151                                 //用户倒反
#define REC_SUB_S_OPENCARD			152									//用户明牌
#define REC_SUB_S_TIMETOCLOSE			154								//解散用户
#define GS_WK_SCORE                    50                                   //叫分状态        

//服务端消息
#define SUB_S_GAME_READY             5001                //通知客户端发送准备请求
#define SUB_C_GAME_READY             5002                //通知客户端发送准备请求
#define SUB_S_ALL_READY              5003                //通知客户端已经准备好的人
#define SUB_C_ALL_READY              5004                //通知服务端已经准备好的人
#define SUB_C_ANDROCHAIR             5005                //机器人椅子号
//#define SUB_C_MATCH_TYPE             5006                //比赛类型
#define SUB_SC_READYTIMEOUT					72				//准备超时
#define SUB_S_GAMESTART					5008				//游戏开始
/////////////////////////////////////////////////////////////////////////////////////////

//客户端消息
#define SUB_C_CLIENT_READY           4001                //客户端准备好了
//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define REC_SUB_C_LAND_SCORE			1									//用户叫分
#define REC_SUB_C_OUT_CART				2									//用户出牌
#define REC_SUB_C_PASS_CARD				3									//放弃出牌
#define REC_SUB_C_TRUSTEE				4									//托管消息
#define REC_SUB_C_GAME_END              5                                   //游戏结束
#define REC_SUB_C_LOOKTRUSTEE           6                                   //查询托管
#define REC_SUB_C_WARN_INFO             12									//报警消息
#define REC_SUB_C_TURN_COUNT            13									//出牌轮数
#define REC_SUB_C_CONTINUE              14                                  //按键继续
#define REC_SUB_C_DAOFAN                15                                  //用户倒反
#define	REC_SUB_S_GOLDEGG               16                                  //送金蛋
#define REC_SUB_S_RESED_CARD            17                                   //重新发牌（用于纠错）
#define REC_SUB_C_OPNE_CARD				18								//--玩家明牌
#define REC_SUB_S_BEILV						20								//--倍率变化
#define REC_SUB_S_ONLINE					22								//--玩家在线标志
#define REC_SUB_C_OVER						24								//--客户端主动结束，用于测试
//----------------------------

//--玩家断线重连标志
struct CMD_S_UserOffLine
{
	WORD    m_userID;
	bool        m_isOnline;
};

//发送扑克
struct CMD_S_SendAllCard
{
	WORD				 			wCurrentUser;						//当前玩家
	BYTE								bCardData[GAME_PLAYER][MAX_COUNT];			//扑克列
	BYTE                            bMingPai[MAX_COUNT];                           //明牌
	BYTE								bBackCardData[GAME_PLAYER];					//底牌扑克
	LONG							lBaseScore;							//基础积分
	bool								bDog;								//gou
};


//游戏叫分
struct CMD_S_StatusScore
{
	BYTE							bLandScore;							//地主分数
	LONG							lBaseScore;							//基础积分
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bScoreInfo[GAME_PLAYER];			//叫分信息
	BYTE							bCardData[GAME_PLAYER][20];			//手上扑克
	bool							bUserTrustee[GAME_PLAYER];			//玩家托管
	BYTE							bBackCardData[GAME_PLAYER];			//底牌扑克
	WORD						wOpenCard[GAME_PLAYER];				//明牌  倍率相乘
	//历史积分
	long long						lTurnScore[GAME_PLAYER];			//积分信息
	long long						lCollectScore[GAME_PLAYER];			//积分信息
};
//送金蛋
struct CMD_S_GoldEgg
{
	WORD                            bCurrentUser;                       //当前玩家
	BYTE                            bGoldEgg;                           //金蛋数目
};

//用户明牌
struct CMD_S_OPENCARD
{
	WORD	bOpenUser;
};

//用户明牌
struct CMD_C_OPENCARD
{
	WORD	bOpenUser;
	WORD		bNum;
};

//用户叫分(客户端)
struct CMD_C_LandScore  
{
	bool								  bLandScore;							//地主分数
    WORD                            bLandUser;                          //叫分用户
};
//用户倒反
struct CMD_C_DAOFAN
{
	WORD                            m_bUserDaofanID;
};
//用户准备好了
struct CMD_C_START
{
	WORD							bCurrentUser;                     //开始用户 
	bool								bOpenCard;							//明牌开始
};
struct CMD_S_READY
{
	WORD							bCurrentUser;                     //开始用户 
	bool								bOpenCard;							//明牌开始
};
struct CMD_S_DAOFAN
{
	WORD                            m_bUserDaofanID;								//当前用户
};
//用户叫分（服务端）
struct CMD_S_LandScore
{
	bool								bCanLand;							//有无叫分
	WORD							bLandUser;							//叫分玩家
	WORD							wLanddata;							//叫分玩家标识--用于标记抢地主和叫地主
	WORD				 			wCurrentUser;						//当前玩家
	WORD							wCurrentData;						//当前玩家标识
	//BYTE							bLandScore;							//上次叫分
	//BYTE							bCurrentScore;						//当前叫分
	//bool                            bGameStart;                         //游戏开始标志
};



//倍率变化
struct CMD_S_BEILV
{
	WORD beillu[GAME_PLAYER];							//倍率
};

//用户出牌（服务端）
//struct CMD_S_OutCard
//{
//	BYTE							bCardCount;							//出牌数目
//	WORD				 			wCurrentUser;						//当前玩家
//	WORD							wOutCardUser;						//出牌玩家
//	BYTE							bCardData[MAX_COUNT];						//扑克列表
//	bool                            bIsNoGameEnd;                       //是否结束
//};

//出牌（客户端）
//struct CMD_C_OutCard
//{
//	BYTE							bCardCount;							//出牌数目
//	BYTE							bCardData[MAX_COUNT];						//扑克列表
//	WORD                            wOutCardUser;                       //出牌玩家
//};


//放弃出牌
//struct CMD_S_PassCard
//{
//	bool							bNewTurn;							//一轮开始
//	WORD				 			wPassUser;							//放弃玩家
//	WORD				 			wCurrentUser;						//当前玩家
//};
//重新发牌（用于纠错）
struct CMD_S_ReSedCrad
{
	WORD                            bTurnUser;                          //上一轮出牌用户
	BYTE							bTurnCount;							//上一轮出牌牌数目
	BYTE							bTurnData[MAX_COUNT];						//扑克列表
	BYTE							bCardCount;							//牌数目
	BYTE							bCardData[MAX_COUNT];						//扑克列表
};

//出牌轮数
struct CMD_S_TurnCount
{
	WORD                            wTurnChairID;                       //玩家ID
	WORD                            wTurnCount;                         //轮数
};


//用户报警
struct CMD_S_WarnInfo
{
	WORD                           wWarnUser;                           //报警玩家
	bool                           bWarn;                               //报警信息
	WORD                           wWarnNum;                            //报警时牌数目
};
//托管结构
struct CMD_C_UserTrustee {
	WORD							wUserChairID;						//玩家椅子
	bool							bTrustee;							//托管标识
};



//出牌提示
struct CMD_S_OutCardNotify
{
	BYTE							bOutCard;							//出牌标志
	WORD							wCurrentUser;						//当前用户
};


////////////////////////////////////////////////////////////////////////////////////////////////
#endif
#ifndef CMD_GAME_HEAD_FILE
#define CMD_GAME_HEAD_FILE

#pragma pack(1)

#include "Define.h"
#include "Packet.h"
//////////////////////////////////////////////////////////////////////////////////
//服务定义

//游戏属性
#define DDZ_KIND_ID						201									//游戏 I D
#define HLDDZ_KIND_ID					212									//游戏 I D
#define GAME_NAME					TEXT("斗地主")						//游戏名字

//组件属性
#define GAME_PLAYER					3									//游戏人数
#define VERSION_SERVER				PROCESS_VERSION(1,0,3)				//程序版本
#define VERSION_CLIENT				PROCESS_VERSION(1,0,3)				//程序版本

//////////////////////////////////////////////////////////////////////////////////

//数目定义
#define MAX_COUNT					20									//最大数目
#define FULL_COUNT					54									//全牌数目

//逻辑数目
#define NORMAL_COUNT				17									//常规数目
#define DISPATCH_COUNT				51									//派发数目
#define GOOD_CARD_COUTN				38									//好牌数目

//数值掩码
#define	MASK_COLOR					0xF0								//花色掩码
#define	MASK_VALUE					0x0F								//数值掩码

//逻辑类型
#define CT_ERROR					0									//错误类型
#define CT_SINGLE					1									//单牌类型
#define CT_DOUBLE					2									//对牌类型
#define CT_THREE					3									//三条类型
#define CT_SINGLE_LINE				4									//单连类型
#define CT_DOUBLE_LINE				5									//对连类型
#define CT_THREE_LINE				6									//三连类型
#define CT_THREE_TAKE_ONE			7									//三带一单
#define CT_THREE_TAKE_TWO			8									//三带一对
#define CT_FOUR_TAKE_ONE			9									//四带两单
#define CT_FOUR_TAKE_TWO			10									//四带两对
#define CT_BOMB_CARD				11									//炸弹类型
#define CT_MISSILE_CARD				12									//火箭类型

//////////////////////////////////////////////////////////////////////////////////
//状态定义

#define DDZ_GAME_SCENE_FREE				GAME_STATUS_FREE					//等待开始
#define DDZ_GAME_SCENE_CALL				GAME_STATUS_PLAY					//叫分状态
#define DDZ_GAME_SCENE_DOUBLE			GAME_STATUS_PLAY+1					//加倍状态
#define DDZ_GAME_SCENE_PLAY				GAME_STATUS_PLAY+2					//游戏进行

//状态定义

#define HLDDZ_GAME_SCENE_FREE				GAME_STATUS_FREE					//等待开始
#define HLDDZ_GAME_SCENE_CALL				GAME_STATUS_PLAY					//叫地主状态
#define HLDDZ_GAME_SCENE_ROD				GAME_STATUS_PLAY+1					//抢地主状态
#define HLDDZ_GAME_SCENE_ADD				GAME_STATUS_PLAY+2					//加倍状态
#define HLDDZ_GAME_SCENE_PLAY				GAME_STATUS_PLAY+3					//游戏进行

//底牌类型
#define BCT_GENERAL					0									//普通类型
#define BCT_FULSH					1									//顺子类型
#define BCT_STRAIGHT				2									//同花类型
#define BCT_STRAIGHT_FULSH			3									//同花顺类型
#define BCT_SINGLE_MISSILE			4									//单王类型
#define BCT_DOUBLE_MISSILE			5									//对王类型
#define BCT_THREE					6									//三条类型

//叫地主
#define HLDDZ_CB_NOT_CALL					0									//没叫地主
#define HLDDZ_CB_CALL_BENKER				1									//叫地主
#define HLDDZ_CB_NO_CALL_BENKER			2									//不叫地主

//抢地主
#define HLDDZ_CB_NOT_ROD					0									//没抢地主
#define HLDDZ_CB_ROD_BANKER				1									//抢地主
#define HLDDZ_CB_NO_ROD_BANKER			2									//不抢地主
#define HLDDZ_CB_CAN_NO_ROD				3									//不能抢

//加倍信息
#define CB_NOT_ADD_DOUBLE			0									//没加倍
#define CB_ADD_DOUBLE				1									//加倍标志
#define CB_NO_ADD_DOUBLE			2									//不加倍

//阶段变量
#define HLDDZ_CSD_NORMAL                  0
#define HLDDZ_CSD_SNATCHLAND              1
#define HLDDZ_CSD_BRIGHTCARD              2
#define HLDDZ_CSD_GAMESTART               3

//空闲状态
struct CMD_S_StatusFree
{
	//游戏属性
	int							lCellScore;							//基础积分
    
	//时间信息
	_BYTE_							cbTimeOutCard;						//出牌时间
	_BYTE_							cbTimeCallScore;					//叫分时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
    
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
};

//空闲状态
struct HLDDZ_CMD_S_StatusFree
{
	//游戏属性
	int							lCellScore;							//基础积分
    
	//时间信息
	_BYTE_							cbTimeCallBanker;					//叫地主时间
	_BYTE_							cbTimeRodBanker;					//抢地主时间
	_BYTE_							cbTimeAddDouble;					//加倍时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
	_BYTE_							cbTimeOutCard;						//出牌时间
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
	bool							bTrustee[GAME_PLAYER];				//是否托管
};

//叫分状态
struct CMD_S_StatusCall
{
	//时间信息
	_BYTE_							cbTimeOutCard;						//出牌时间
	_BYTE_							cbTimeCallScore;					//叫分时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
    
	//游戏信息
	int							lCellScore;							//单元积分
	unsigned short							wCurrentUser;						//当前玩家
	_BYTE_							cbBankerScore;						//庄家叫分
	_BYTE_							cbScoreInfo[GAME_PLAYER];			//叫分信息
	_BYTE_							cbHandCardData[NORMAL_COUNT];		//手上扑克
    
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
};

//叫地主状态
struct HLDDZ_CMD_S_StatusCall
{
	//时间信息
	_BYTE_							cbTimeCallBanker;					//叫地主时间
	_BYTE_							cbTimeRodBanker;					//抢地主时间
	_BYTE_							cbTimeAddDouble;					//加倍时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
	_BYTE_							cbTimeOutCard;						//出牌时间
    
	//游戏信息
	int							    lCellScore;							//单元积分
	_WORD_							wFirstUser;							//首叫用户
	_WORD_							wFirstValidUser;					//首叫明牌
	_WORD_							wCurrentUser;						//当前玩家
	_WORD_							wStartTime;							//初始倍数
	_WORD_							wValidCardTime;						//明牌倍数
	bool							bValidCardInfo[GAME_PLAYER];		//明牌信息
	_BYTE_							cbCallBankerInfo[GAME_PLAYER];		//叫地主信息
	_BYTE_							cbHandCardData[GAME_PLAYER][NORMAL_COUNT];		//手上扑克
    
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
	bool							bTrustee[GAME_PLAYER];				//是否托管
};

//抢地主状态
struct HLDDZ_CMD_S_StatusRod
{
	//时间信息
	_BYTE_							cbTimeCallBanker;					//叫地主时间
	_BYTE_							cbTimeRodBanker;					//抢地主时间
	_BYTE_							cbTimeAddDouble;					//加倍时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
	_BYTE_							cbTimeOutCard;						//出牌时间
    
	//游戏信息
	int							lCellScore;							//单元积分
	_WORD_							wFirstUser;							//首叫用户
	_WORD_							wFirstValidUser;					//首叫明牌
	_WORD_							wBankerUser;						//庄家用户
	_WORD_							wCurrentUser;						//当前用户
    
	_WORD_							wStartTime;							//初始倍数
	_WORD_							wValidCardTime;						//明牌倍数
	_WORD_							wRodBankerTime;						//抢地主倍数
    
	bool							bValidCardInfo[GAME_PLAYER];		//明牌信息
	_BYTE_							cbCallBankerInfo[GAME_PLAYER];		//叫地主信息
	_BYTE_							cbRodBankerInfo[GAME_PLAYER];		//抢地主信息
	_BYTE_							cbValidCardInfo[GAME_PLAYER];		//叫地主信息
	_BYTE_							cbHandCardData[GAME_PLAYER][NORMAL_COUNT];		//手上扑克
    
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
	bool							bTrustee[GAME_PLAYER];				//是否托管
};

//加倍状态
struct CMD_S_StatusDouble
{
	//时间信息
	_BYTE_							cbTimeOutCard;						//出牌时间
	_BYTE_							cbTimeCallScore;					//叫分时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
    
	//游戏信息
	int							lCellScore;							//单元积分
	unsigned short							wCurrentUser;						//当前玩家
	unsigned short							wBankerUser;						//庄家用户
	_BYTE_							cbBankerScore;						//庄家叫分
	_BYTE_							cbDoubleInfo[GAME_PLAYER];			//加倍信息
    
	//扑克信息
	_BYTE_							cbBankerCard[3];					//游戏底牌
	_BYTE_							cbHandCardData[MAX_COUNT];			//手上扑克
	_BYTE_							cbHandCardCount[GAME_PLAYER];		//扑克数目
    
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
};

//倍数信息
struct HLDDZ_CMD_S_DoubleInfo
{
	//公共位数
	_WORD_							wStartTime;								//初始倍数
	_WORD_							wValidCardTime;							//明牌倍数
	_WORD_							wRodBankerTime;							//抢地主倍数
	_WORD_							wBackCardTime;							//底牌倍数
	_WORD_							wBombTime;								//炸弹倍数
	_WORD_							wChunTianbTime;							//春天倍数
	_WORD_							wCardTypeTime;							//牌型倍数
    
	//加倍过程
	_WORD_							wUserDouble[GAME_PLAYER];				//用户加倍
    
	//用户信息
	_WORD_							wBankerUser;							//庄家用户
	_WORD_							wMeChairID;								//玩家自己
};

//加倍状态
struct HLDDZ_CMD_S_StatusDouble
{
	//时间信息
	_BYTE_							cbTimeCallBanker;					//叫地主时间
	_BYTE_							cbTimeRodBanker;					//抢地主时间
	_BYTE_							cbTimeAddDouble;					//加倍时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
	_BYTE_							cbTimeOutCard;						//出牌时间
    
	//游戏信息
	int							lCellScore;							//单元积分
	_WORD_							wBankerUser;						//庄家用户
	_WORD_							wCurrentUser;						//当前用户
	_WORD_							wStartTime;							//初始倍数
	_WORD_							wValidCardTime;						//明牌倍数
	_WORD_							wRodBankerTime;						//抢地主倍数
	_WORD_							wBackCardTime;						//底牌倍数
    
	bool							bValidCardInfo[GAME_PLAYER];		//明牌信息
	_BYTE_							cbCallBankerInfo[GAME_PLAYER];		//叫地主信息
	_BYTE_							cbRodBankerInfo[GAME_PLAYER];		//抢地主信息
	_BYTE_							cbAddDoubleInfo[GAME_PLAYER];		//加倍信息
	
	//扑克信息
	_BYTE_							cbBankerCard[3];					//游戏底牌
	_BYTE_							cbHandCardCount[GAME_PLAYER];		//扑克数目
	_BYTE_							cbHandCardData[GAME_PLAYER][MAX_COUNT];		//手上扑克
    
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
	bool							bTrustee[GAME_PLAYER];				//是否托管
};

//游戏状态
struct CMD_S_StatusPlay
{
	//时间信息
	_BYTE_							cbTimeOutCard;						//出牌时间
	_BYTE_							cbTimeCallScore;					//叫分时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
    
	//游戏变量
	int							lCellScore;							//单元积分
	_BYTE_							cbBombCount;						//炸弹次数
	unsigned short							wBankerUser;						//庄家用户
	unsigned short							wCurrentUser;						//当前玩家
	_BYTE_							cbBankerScore;						//庄家叫分
    
	//出牌信息
	unsigned short							wTurnWiner;							//胜利玩家
	_BYTE_							cbTurnCardCount;					//出牌数目
	_BYTE_							cbTurnCardData[MAX_COUNT];			//出牌数据
    
	//扑克信息
	_BYTE_							cbBankerCard[3];					//游戏底牌
	_BYTE_							cbHandCardData[MAX_COUNT];			//手上扑克
	_BYTE_							cbHandCardCount[GAME_PLAYER];		//扑克数目
    
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
};

//游戏状态
struct HLDDZ_CMD_S_StatusPlay
{
	//时间信息
	_BYTE_							cbTimeCallBanker;					//叫地主时间
	_BYTE_							cbTimeRodBanker;					//抢地主时间
	_BYTE_							cbTimeAddDouble;					//加倍时间
	_BYTE_							cbTimeStartGame;					//开始时间
	_BYTE_							cbTimeHeadOutCard;					//首出时间
	_BYTE_							cbTimeOutCard;						//出牌时间
    
	//游戏变量
	int							lCellScore;							//单元积分
	_WORD_							wBankerUser;						//庄家用户
	_WORD_							wCurrentUser;						//当前玩家
    
	_WORD_							wStartTime;							//初始倍数
	_WORD_							wValidCardTime;						//明牌倍数
	_WORD_							wRodBankerTime;						//抢地主倍数
	_WORD_							wBackCardTime;						//底牌倍数
	_WORD_							wBombTime;							//炸弹倍数
	_WORD_							wCardTypeTime;						//牌型倍数
    
	_BYTE_							cbBombCount;						//炸弹次数
	_BYTE_							cbCallBankerInfo[GAME_PLAYER];		//叫地主信息
	_BYTE_							cbRodBankerInfo[GAME_PLAYER];		//抢地主信息
	_BYTE_							cbAddDoubleInfo[GAME_PLAYER];		//加倍信息
	bool							bValidCardInfo[GAME_PLAYER];		//明牌信息
    
	//出牌信息
	_WORD_							wTurnWiner;							//胜利玩家
	_BYTE_							cbTurnCardCount;					//出牌数目
	_BYTE_							cbTurnCardData[MAX_COUNT];			//出牌数据
    
	//扑克信息
	_BYTE_							cbBankerCard[3];					//游戏底牌
	_BYTE_							cbHandCardCount[GAME_PLAYER];		//扑克数目
	_BYTE_							cbHandCardData[GAME_PLAYER][MAX_COUNT];		//手上扑克
	
	//历史积分
	SCORE							lTurnScore[GAME_PLAYER];			//积分信息
	SCORE							lCollectScore[GAME_PLAYER];			//积分信息
	bool							bTrustee[GAME_PLAYER];				//是否托管
};

//////////////////////////////////////////////////////////////////////////////////
//命令定义

#define SUB_S_GAME_START			100									//游戏开始
#define SUB_S_CALL_SCORE			101									//用户叫分
#define SUB_S_DOUBLE_SCORE          102                                 //用户加倍
#define SUB_S_BANKER_INFO			103									//庄家信息
#define SUB_S_OUT_CARD				104									//用户出牌
#define SUB_S_PASS_CARD				105									//用户放弃
#define SUB_S_GAME_CONCLUDE			106									//游戏结束
#define SUB_S_SET_BASESCORE			107									//设置基数
#define SUB_S_TRUSTEE               108                                 //用户托管
//命令定义

#define HLDDZ_SUB_S_GAME_START              100									//游戏开始
#define HLDDZ_SUB_S_CALL_SCORE              101									//用户叫分
#define HLDDZ_SUB_S_CALL_BANKER             101									//叫地主
#define HLDDZ_SUB_S_BANKER_INFO             102									//庄家信息
#define HLDDZ_SUB_S_ROD_BANKER              103									//抢地主
#define HLDDZ_SUB_S_DOUBLE                  104									//加倍信息
#define HLDDZ_SUB_S_VALID_CARD              105									//用户明牌
#define HLDDZ_SUB_S_OUT_CARD				106                                 //用户出牌
#define HLDDZ_SUB_S_PASS_CARD				107                                 //用户放弃
#define HLDDZ_SUB_S_OUT_START_START         108									//开始出牌
#define HLDDZ_SUB_S_GAME_CONCLUDE			109                                 //游戏结束
#define HLDDZ_SUB_S_SET_BASESCORE			110                                 //设置基数
#define HLDDZ_SUB_S_TRUSTEE                 111									//用户托管
#define HLDDZ_SUB_S_NEWBANK                 112                                 //新的地主

//发送扑克
struct CMD_S_GameStart
{
	unsigned short							wStartUser;							//开始玩家
	unsigned short				 			wCurrentUser;						//当前玩家
	_BYTE_							cbValidCardData;					//明牌扑克
	_BYTE_							cbValidCardIndex;					//明牌位置
	_BYTE_							cbCardData[NORMAL_COUNT];			//扑克列表
};


//开始信息
struct HLDDZ_CMD_S_Game_Start
{
	_WORD_				 			wBankerUser;						//庄家玩家
	_WORD_				 			wCurrentUser;						//当前玩家
	_BYTE_							cbCardData[MAX_COUNT];				//扑克数据
    
};

//用户叫地主
struct HLDDZ_CMD_S_CallBanker
{
	_WORD_				 			wCurrentUser;						//当前玩家
	_WORD_							wLastUser;							//叫地主玩家
	_BYTE_							cbCallInfo;							//叫地主
};

//用户抢地主
struct HLDDZ_CMD_S_RodBanker
{
	_WORD_							wRodBankerTime;						//抢地主倍数
    
	_WORD_				 			wBankerUser;						//庄家玩家
	_WORD_				 			wCurrentUser;						//当前玩家
	_WORD_							wLastUser;							//抢地主玩家
	_BYTE_							cbRodlInfo;							//抢地主
};

//发送扑克
struct HLDDZ_CMD_S_GameStart
{
	_WORD_							wStartUser;							//开始玩家
	_WORD_				 			wCurrentUser;						//当前玩家
	_WORD_							wStartTime;							//初始倍数
	bool							bValidCard;							//是否明牌
	_BYTE_							cbValidCardData;					//明牌扑克
	_BYTE_							cbValidCardIndex;					//明牌位置
	_BYTE_							cbCardData[NORMAL_COUNT];			//扑克列表
	bool							bMatchGame;							//是否比赛
};

//发送扑克
struct HLDDZ_CMD_S_SendAllCard
{
	_WORD_				 			wCurrentUser;						//当前玩家
	_BYTE_							bCardData[GAME_PLAYER][20];			//扑克列表
	_BYTE_							bBackCardData[3];					//底牌扑克
	bool							bUserBrightCard[GAME_PLAYER];		//玩家亮牌
};

//用户叫分
struct CMD_S_CallScore
{
	unsigned short				 			wCurrentUser;						//当前玩家
	unsigned short							wCallScoreUser;						//叫分玩家
	_BYTE_							cbCurrentScore;						//当前叫分
	_BYTE_							cbUserCallScore;					//上次叫分
};

//用户叫分
struct HLDDZ_CMD_S_CallScore
{
	_WORD_				 			wCurrentUser;						//当前玩家
	_WORD_							wCallScoreUser;						//叫分玩家
	_BYTE_							cbCurrentScore;						//当前叫分
	_BYTE_							cbUserCallScore;					//上次叫分
};

//用户加倍
struct CMD_S_DoubleScore
{
	unsigned short				 			wCurrentUser;						//当前玩家
	unsigned short							wDoubleUser;						//加倍玩家
	_BYTE_							cbDoubleScore;						//当前加倍
	_BYTE_							cbDoubleInfo[GAME_PLAYER];			//加倍信息
};

//明牌开始
struct HLDDZ_CMD_S_BrightStart
{
	_WORD_							wBrightUser;						//明牌玩家
	bool							bBright;							//明牌标识
	_BYTE_							cbCurrentBrightTime;				//当前倍数
};

//加倍信息
struct HLDDZ_CMD_S_Double
{
	_WORD_							wCurrentUser;						//当前用户
	_BYTE_							cbDouble;							//是否加倍
	_BYTE_							bBackCard[3];						//底牌扑克
};

//庄家信息
struct CMD_S_BankerInfo
{
	unsigned short				 			wBankerUser;						//庄家玩家
	unsigned short				 			wCurrentUser;						//当前玩家
	_BYTE_							cbBankerScore;						//庄家叫分
	_BYTE_							cbBankerCard[3];					//庄家扑克
};


//庄家信息
struct HLDDZ_CMD_S_BankerInfo
{
	_WORD_				 			wBankerUser;						//庄家玩家
	_WORD_				 			wCurrentUser;						//当前玩家
	_WORD_							wBackCardTime;						//底牌倍数
	_BYTE_							cbBankerCard[3];					//庄家扑克
	_BYTE_							cbBackCardType;						//底牌类型
	bool							bDoubleInfo[3];						//能否加倍
};

//用户明牌
struct HLDDZ_CMD_S_ValidCard
{
	_WORD_							wFirstValidUser;					//首叫明牌
	_WORD_							wValidCardTime;						//明牌倍数
    
	_WORD_							wValidUser;                         //明牌用户
	_BYTE_							cbCardCount;						//明牌数目
	_BYTE_							cbCardData[MAX_COUNT];				//扑克数据
};

//用户出牌
struct CMD_S_OutCard
{
	_BYTE_							cbCardCount;						//出牌数目
	unsigned short				 			wCurrentUser;						//当前玩家
	unsigned short							wOutCardUser;						//出牌玩家
	_BYTE_							cbCardData[MAX_COUNT];				//扑克列表
};

//放弃出牌
struct CMD_S_PassCard
{
	_BYTE_							cbTurnOver;							//一轮结束
	unsigned short				 			wCurrentUser;						//当前玩家
	unsigned short				 			wPassCardUser;						//放弃玩家
};

//游戏结束
struct CMD_S_GameConclude
{
	//积分变量
	int							lCellScore;							//单元积分
	SCORE							lGameScore[GAME_PLAYER];			//游戏积分
    
	//春天标志
	_BYTE_							bChunTian;							//春天标志
	_BYTE_							bFanChunTian;						//春天标志
    
	//炸弹信息
	_BYTE_							cbBombCount;						//炸弹个数
	_BYTE_							cbEachBombCount[GAME_PLAYER];		//炸弹个数
    
	//游戏信息
	_BYTE_							cbBankerScore;						//叫分数目
	_BYTE_							cbCardCount[GAME_PLAYER];			//扑克数目
	_BYTE_							cbHandCardData[FULL_COUNT];			//扑克列表
};

//游戏结束
struct HLDDZ_CMD_S_GameConclude
{
	//积分变量
	int							lCellScore;							//单元积分（底分）
	SCORE							lGameScore[GAME_PLAYER];			//游戏积分
    
	//春天标志
	_BYTE_							bChunTian;							//春天标志
	_BYTE_							bFanChunTian;						//春天标志
    
	//炸弹信息
	_BYTE_							cbBombCount;						//炸弹个数
	_BYTE_							cbEachBombCount[GAME_PLAYER];		//炸弹个数
	//游戏信息
	_BYTE_							cbCardCount[GAME_PLAYER];			//扑克数目
	_BYTE_							cbHandCardData[FULL_COUNT];			//扑克列表
};

//放弃出牌
struct CMD_S_Trustee
{
	unsigned short				 			wTrusteeUser;						//托管玩家
	bool				 			bTrustee;							//是否托管
};

//用户托管
struct HLDDZ_CMD_S_Trustee
{
	bool							bTrustee;							//是否托管
	_WORD_							wChairID;							//托管用户
};

//通过明牌的新地主
struct HLDDZ_CMD_NEW_BANK
{
	_BYTE_                          wCurrentUser;                       //通过明牌的新地主
};

//////////////////////////////////////////////////////////////////////////////////
//命令定义

#define SUB_C_CALL_SCORE			1									//用户叫分
#define SUB_C_DOUBLE_SCORE			2									//用户加倍
#define SUB_C_OUT_CARD				3									//用户出牌
#define SUB_C_PASS_CARD				4									//用户放弃
#define SUB_C_TRUSTEE               5                                   //用户托管

#define HLDDZ_SUB_C_VALID_CARD			1									//用户明牌
#define HLDDZ_SUB_C_CALL_SCORE			2									//用户叫分
#define HLDDZ_SUB_C_CALL_BANKER			2									//用户叫地主
#define HLDDZ_SUB_C_ROD_BANKER			3									//用户抢地主
#define HLDDZ_SUB_C_DOUBLE				4									//用户加倍
#define HLDDZ_SUB_C_OUT_CARD				5									//用户出牌
#define HLDDZ_SUB_C_PASS_CARD				6									//用户放弃
#define HLDDZ_SUB_C_TRUSTEE				7									//用户托管
#define HLDDZ_SUB_C_BRIGHT_START			8									//明牌开始

//用户叫分
struct CMD_C_CallScore
{
	_BYTE_							cbCallScore;						//叫分数目
};

//用户叫分
struct HLDDZ_CMD_C_CallScore
{
	_BYTE_							cbCallScore;						//叫分数目
};

//用户叫地主
struct HLDDZ_CMD_C_CallBanker
{
	_BYTE_							cbCallInfo;							//叫地主
};

//用户抢地主
struct HLDDZ_CMD_C_RodBanker
{
	_BYTE_							cbRodInfo;							//抢地主
};

//用户加倍
struct CMD_C_DoubleScore
{
	_BYTE_							cbDoubleScore;						//加倍数目
};

//用户加倍
struct HLDDZ_CMD_C_Double
{
	_BYTE_							cbDoubleInfo;						//加倍信息
};

//用户出牌
struct CMD_C_OutCard
{
	_BYTE_							cbCardCount;						//出牌数目
	_BYTE_							cbCardData[MAX_COUNT];				//扑克数据
};

//放弃出牌
struct CMD_C_Trustee
{
	bool				 			bTrustee;							//是否托管
};

//////////////////////////////////////////////////////////////////////////////////
//音乐 动画 消息定义
#define MS_music                            1                           // 音乐消息
#define MS_Act                              2                           // 动画消息
#define MS_PlayerEnter                      3                           // 用户进入消息

// 消息结构信息
struct MessageStruct{
    int     type;           // 消息类型
    
    int     musicType;      // 音效类型
    
    bool    sex;            // 性别
    int     value;          // 携带值
    
    unsigned char    cbCardData[MAX_COUNT];// 出牌数据
};

#pragma pack()

#endif
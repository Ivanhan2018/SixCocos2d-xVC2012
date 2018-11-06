#ifndef PRO_FISH_H
#define PRO_FISH_H
#include <string.h>
#include "DB_Head.h"
#include "PublicMacro.h"
#include <map>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//相关宏定义

#define GAME_PLAYER_COUNT			(4)									// 游戏人数

#define MAX_HIT_FISH_COUNT    5//单发炮弹最大射中鱼的个数
#define CCP(pt) ccp(pt.x,pt.y)
//add by Ivan_han 20130724
//#define MAKE32(Lo16,Hi16)      ((unsigned int)(((unsigned short int)(Lo16)) | ((unsigned int)((unsigned short int)(Hi16))) << 16))
//#define LO16(l)           ((unsigned short int)(((unsigned int)(l)) & 0xffff))
//#define HI16(l)           ((unsigned short int)((((unsigned int)(l)) >> 16) & 0xffff))
//////////////////////////////////////////////////////////////////////////////////
typedef unsigned int TSeaSceneKind;    //海底场景号
typedef unsigned int TGunGrade;  //炮的等级，也称为几号炮
typedef unsigned short int TFishKind;    //鱼号1-99
typedef unsigned int TFishMulti;    //鱼的倍率
typedef unsigned long long TBulletID;	 //一发炮弹标识
typedef unsigned int TFishID;    //一条鱼标识
typedef unsigned int TTableID;   //桌子号
typedef unsigned int TChairID;   //椅子号
typedef float TAngle; //发射角度
typedef unsigned short int TFishPathType;    //鱼轨迹类型<1直线，2圆，3摆线，4任意曲线，5三阶贝塞尔曲线，6阿基米德螺线>
typedef unsigned short int TFishGroupType;    //鱼群鱼阵类型<0单鱼，1圆直线阵LtoR，2-4网狐直线阵LtoR，5任意直线阵LToR，11-15直线阵RToL，鱼群类型以101开始>，避免发重复鱼群、鱼阵的发鱼策略要用到
typedef unsigned int TFishGroupID;    //鱼阵ID，收发大包数据时用到
typedef unsigned char TFishMoveSecs;//鱼轨迹时长，也就是鱼的最长存活时间
typedef unsigned char TFishMoveStatus;//鱼轨迹状态<0正常状态，1鱼轨迹加速且不可捕获状态，2鱼轨迹加速虽不同步但可捕获状态>，单鱼场景->鱼阵场景时用到
typedef unsigned char TFishNumOfAck;//鱼被攻击次数，奖池算法要用到
typedef unsigned long long TBuildTraceTime;//服务器端轨迹建立时间ms
typedef long long TFallIntegral;//渔币增量或掉落积分(>=0)
typedef long long TWinIntegral;//扣除炮弹成本后赢的积分
//typedef unsigned int TFishKindNum;//统计渔获时用到，FishKindNum=FishKind(4)+Num(4)

const int SCENES_MIN = 1;			// 场景ID 最小值
const int SCENES_MAX = 4;			// 场景ID 最大值

struct qcPoint
{
	float x, y;
	qcPoint() : x(0), y(0) {}
	qcPoint(float _x, float _y) : x(_x), y(_y) {}
	qcPoint& operator= (const qcPoint& point) {x = point.x; y = point.y; return *this;}
};

typedef qcPoint TPoint;


///////////////////////////////////////////////////////////////////////////////

/**************************************************************************
//捕鱼房间服务器
**************************************************************************/
enum PROTOCOL_FISH
{
	TABLE_SUB_BUY_BULLET				= 210,	// 购买子弹
	TABLE_SUB_BUY_BULLET_RET			= 220,	// 购买子弹返回
	TABLE_SUB_EXCHANGE_INFO_RET			= 250,	// 返回兑换信息
	//TABLE_SUB_USER_INFO					= 260,	// 用户信息	
	TABLE_SUB_USER_OVERTIME				= 271,	// 用户超时退出


	REQ_BUY_BULLET=400,									//购买子弹
	REQ_USER_SHOOT,									//发射炮弹
	REQ_CAPTURE_FISH,									//捕获几条鱼
	REQ_GET_SCORE_INFO,								//分数信息
	REQ_SET_PROPABILITY,								//设置概率
	REQ_CALC_SCORE,									//计算分数
	REQ_SET_GUNGRADE,								//设置炮的等级，add by Ivan_han 20130724
	REQ_HIT_FISH,										//捕获鱼群
	REQ_OPEN_BOSSBOX,                                 //打开宝箱
	REQ_SHOOT_FORCECANNON,                            //使用能量炮

	RSP_GAME_SCENE=500,									//场景消息
	RSP_ADD_ONE_FISH,                                    //添加一条鱼轨迹
	RSP_ADD_ONE_FISH_LIST_UNFINISH,						//添加一个鱼轨迹阵，大包数据未发送完毕
	RSP_ADD_ONE_FISH_LIST_FINISH,						//添加一个鱼轨迹阵，大包数据已发送完毕
	RSP_ADD_ONE_FISH_ARR,								//添加一个鱼轨迹阵
	RSP_ADD_ONE_FISH_LIST,								//添加一个鱼轨迹阵
	RSP_USER_SHOOT,									//发射炮弹
	RSP_CAPTURE_FISH,									//捕获鱼群
	RSP_BULLET_COUNT,									//子弹数目
	RSP_COIN_COUNT,									//金币数目
	RSP_FISH_COUNT,									//鱼群数目
	RSP_CHANGE_SCENE,									//切换场景，涨潮（捕渔期->休渔期），add by Ivan_han 20130806
	RSP_SET_GUNGRADE,								//设置炮的等级，add by Ivan_han 20130724
	RSP_BONUS_INFO,									//彩金信息
	RSP_GAME_MESSAGE,									//游戏消息
	RSP_GET_PROP,                                     //获得道具
	RSP_OPEN_BOSSBOX,                                 //打开宝箱
	RSP_SHOOT_FORCECANNON,                            //使用能量炮
	// 为了防止消息ID重复。此消息ID从600开始不能大于等于2000 (因为在GameSkeletonMsgCode.h中也用到了桌子消息)
};

//桌子错误码		// add by cxf
enum GAME_RETURN_CODE
{
	RET_GAME_OPERATE_SUCCEED				= 0,		// 操作成功
	RET_GAME_USER_NOT_EXIST					= 10,		// 用户不存在
	RET_GAME_BUY_BULLET_GOLD_LACK			= 20,		// 金币不够购买子弹
	RET_GAME_ERROR_CODE_BULLET_LACK			= 30,		// 缺少子弹
	RET_GAME_BUY_BULLET_FAIL				= 40,		// 购买子弹失败
};

//切换场景，涨潮
struct Rsp_ChangeScene
{
	TSeaSceneKind SeaSceneKind;
	bool          bRToL;       //暂时都设置为true
};

//发一条指定轨迹的鱼,参见CFishMgr:addOneFish
struct Rsp_AddOneFish
{
    Rsp_AddOneFish(){memset(this, 0, sizeof(*this));}
	TTableID TableID;

	TFishKind FishKind;
	TFishPathType FishPathType;

	TFishGroupType FishGroupType;
	TFishMoveStatus FishMoveStatus;
	TFishNumOfAck FishNumOfAck;

	TFishMoveSecs FishMoveSecs;
	TFishMoveSecs FishEntryTime;
	TFishMoveSecs FishDepartureTime;
	TFishMoveSecs reserved;

	TBuildTraceTime BuildTraceTime;
	TFishID FishID;
	TPoint	startP;
	TPoint  arg1;
	TPoint  arg2;
	TPoint  arg3;
};

//设置炮的等级
struct Req_SetGunGrade
{
	Req_SetGunGrade(){memset(this, 0, sizeof(*this));}
	long long		llUserID;// 用户ID
	TGunGrade		GunGrade;
	//S->C使用的字段
	int iRes;
};

//发一批指定轨迹的鱼,参见CFishMgr:addOneGroupFish
struct Rsp_AddOneFish_Arr
{
	Rsp_AddOneFish_Arr(){memset(this, 0, sizeof(*this));}
	TTableID TableID;
	unsigned int nFishCount;
	Rsp_AddOneFish Arr[20];
};

//发一批指定轨迹的鱼,参见CFishMgr:addOneGroupFish
struct Rsp_AddOneFish_List
{
	Rsp_AddOneFish_List(){memset(this, 0, sizeof(*this));}
	//TTableID TableID;
	TFishGroupID FishGroupID;
	unsigned int nFishCount;
	unsigned int nTotalFishCount;//大包数据中的总条数
	inline Rsp_AddOneFish & operator [](unsigned int);
	int getLength()const{return sizeof(*this) + nFishCount * sizeof(Rsp_AddOneFish);}
};

inline Rsp_AddOneFish & Rsp_AddOneFish_List::operator [](unsigned int index)
{
	return ((Rsp_AddOneFish *)((unsigned char *)this + sizeof(*this)))[index];
}

// 断线重入
struct CMD_SC_RECOMEAFTERCUT
{
	CMD_SC_RECOMEAFTERCUT()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lUserId;					// 用户ID
	int					iBuyBulletCount;	// 购买子弹数量
	int					iBulletCount;		// 剩余子弹数量
	int					iFeats;				// 功勋
	long long			lGameCoin;			// 鱼币
	long long			lGoldChange;		// 金币
	long long			lPointChange;		// 积分
};
// 开火
const int BULLET_REFLECTION_MAX = 3; // 子弹反弹最大次数
struct SHOT_FIRE
{
	SHOT_FIRE(TBulletID iID,long long iUserID,int iBulletNum,int iBulletType,TGunGrade iGunType,int iRes,
		TPoint fDesPT, TPoint fPlayerPos, bool bRepeatShoot,bool bHaveCarry=false)
	{
		memset(this, 0, sizeof(*this));
		this->bHaveCarry = bHaveCarry;
		this->bRepeatShoot = bRepeatShoot;
		this->iID = iID;
		this->iUserID = iUserID;
		this->iBulletNum = iBulletNum;
		this->iBulletType = iBulletType;
		this->iGunType = iGunType;
		this->iRes = iRes;
		this->fDesPT = fDesPT;
		this->fPlayerPos = fPlayerPos;
	}
	SHOT_FIRE()
	{
		memset(this, 0, sizeof(*this));
	}
	bool bHaveCarry;		// 有射程
	bool bRepeatShoot;		// 连续发射（防止控制发射机制拦截）
	int iTableNo;			// 桌号
	int iSeatNo;			// 座位号
	int iBulletNum;			// 子弹数量
	int iBulletType;		// 子弹类型
	TGunGrade iGunType;		// 炮管类型
	int iRes;	
	TBulletID iID;		// 子弹ID
	long long iUserID;		// 用户ID
	TPoint fDesPT;			// 子弹目的地X坐标
	TPoint fPlayerPos;		// 玩家玩置
	int iUserBulletCount;	// 用户子弹总数
};

// 子弹反射
struct BULLET_REFLECTION
{
	BULLET_REFLECTION()
	{	
		memset(this, 0, sizeof(*this)); 
		iReflectionMax = BULLET_REFLECTION_MAX;
	}

	int iRes;	
	int iReflectionCount;			//反射次数
	int iReflectionMax;			//反射最大次数
	float fMoveTime;				// 移动时间
	float fCurRotation;			// 当前角度
	TBulletID llID;					// 子弹ID
	long long llUserID;			// 用户ID
	TPoint fCurPos;					// 子弹当前位置，碰撞点collidePT
	TPoint fMovePos;				// 子弹要移动到的位置，反射方向(反射输出向量)newMoveBy
};

/// 捕获鱼
struct CAPTURE_FISH
{
	CAPTURE_FISH() {	memset(this, 0, sizeof(*this));	}
	int iRes;
	TBulletID llBulletID;
	long long llUserID;
	unsigned int nFishCount;//碰撞检测到的鱼条数
	TFishID FishIDs[12];
	//add by Ivan_han 20130724，S->C返回包用到
	TFishID DeadFullScreenBombFishID;//DeadFullScreenBombFishID=0表示没有击毙全屏炸弹
	unsigned int FishKindNums[19];//索引0-18对应的鱼号依次为1,2,3,4,5,6,7,8,9,10,15,18,20,25,30,40,12,112,113
	TFallIntegral FallIntegral;
	TGunGrade GunGrade;
	long long  llUserGameCoinCount;  // 用户鱼币总数
	unsigned int nDeadFishCount;//死鱼条数
	inline TFishID & operator [](unsigned int);
	int getLength()const{return sizeof(*this) + nDeadFishCount * sizeof(TFishID);}
};

inline TFishID & CAPTURE_FISH::operator [](unsigned int index)
{
	return ((TFishID *)((unsigned char *)this + sizeof(*this)))[index];
}

//add by Ivan_han 20130718
struct CAPTURE_FISH_MAX :public CAPTURE_FISH
{
	TFishID m_DeadFishIDs[300];
	void SetData(const vector<TFishID> & vDeadFish)
	{
		nDeadFishCount=(vDeadFish.size()>300?300:vDeadFish.size());
		for(unsigned int i=0;i<nDeadFishCount;i++)
			m_DeadFishIDs[i]=vDeadFish[i];
	}
};


/// 服务器保存的子弹数据
struct BULLET_DATA
{
	BULLET_DATA() { memset(this, 0, sizeof(*this)); }
	void SetFire(SHOT_FIRE *pFire)
	{
		Fire = *pFire;
	}
	void SetReflection(BULLET_REFLECTION *pReflection)
	{
		// Reflection = *pReflection; //del cxf
		Reflection.iRes = pReflection->iRes;
		Reflection.fMoveTime = pReflection->fMoveTime;					// 移动时间
		Reflection.fCurRotation = pReflection->fCurRotation;			// 当前角度
		Reflection.llID = pReflection->llID;							// 子弹ID
		Reflection.llUserID = pReflection->llUserID;					// 用户ID
		Reflection.fCurPos = pReflection->fCurPos;						// 子弹当前位置
		Reflection.fMovePos = pReflection->fMovePos;					// 子弹要移动到的位置
	}

	SHOT_FIRE Fire;
	BULLET_REFLECTION Reflection;
	unsigned int nCurrTime;			// 当前子弹创建时间
};
typedef std::map<long long, BULLET_DATA *> MAP_BULLET;

/// 初始游戏
struct INIT_GAME
{
	INIT_GAME()
	{
		iScenesID = 0;
		tServerTime = 0;
		tCurrentServerTime=0;
	}

	int iScenesID;									///< 场景ID
	unsigned int uiBulletMaxCount;						///< 单个玩家子弹最大数目
	unsigned long long tServerTime;							///< 服务器开机的日历时刻（常量SK）
	unsigned long long tCurrentServerTime;					///< 服务器发包的日历时刻（变量ST），注意CEasyDataTime::get_current_time_diff_millitm_from_1970()返回的不是当前真实时刻至1970年1月1日的毫秒差值
};

/*
author cxf
description 购买子弹		
*/
struct USER_BUY_BULLET
{
	USER_BUY_BULLET()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		llUserID;					// 用户ID
	int				iBulletNum;					// 购买子弹数量
};

/*
author cxf
description 购买子弹返回信息		
*/
struct USER_BUY_BULLET_RET
{
	USER_BUY_BULLET_RET()
	{
		memset(this, 0, sizeof(this));
	}

	int				iRes;						// 返回状态(0:成功;10:用户错误;20:金币不够;)
	long long		llUserID;					// 用户ID
	int				iSeatNo;					// 椅子号
	int				iBulletNum;					// 购买子弹数量
	long long		llGold;						// 自身金币数
	long long		llPoint;					// 自身积分
};

/*
author cxf
description 兑换信息
*/
struct USER_EXCHANGE_INFO
{
	USER_EXCHANGE_INFO()
	{
		memset(this, 0, sizeof(*this));
	}

	int				iRes;						// 返回状态(0:成功;10:用户错误;20:金币不够;)
	long long		llUserID;					// 用户ID
	int				iSeatNo;					// 椅子号
	int				iBulletNum;					// 子弹数量
	int				iBulletScore;				// 子弹可以兑换金币数
	long long		llGameCoin;					// 鱼币
	long long		llGameCoinScore;			// 鱼币可以兑换金币数
	long long		llGold;						// 自身金币数
};

// 超时断开剩余
struct USER_OVERTIME_SURPLUS
{
	USER_OVERTIME_SURPLUS()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSurplusTime;				// 断开网络剩余时间 (秒为单位)
};

// 比赛用户信息
struct CMD_GameUserInfo
{
	CMD_GameUserInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	bool				bExit;							// 是否退出游戏(false:退出游戏; true:在游戏)
	long long			lUserID;						// 用户ID
	char				szName[USER_NAME_LEN];			// 用户名
	char				szNickname[USER_NAME_LEN];		// 昵称
	int					iBuyBulletCount;				// 购买子弹数量
	int					iBulletCount;					// 子弹数量
	int					iFeats;							// 功勋
	long long			lGameCoin;						// 鱼币
	long long			lGoldChange;					// 金币
	long long			lPointChange;					// 积分
	long long			lAntiAddictionTime;				// 防沉迷时间
	long long			lAntiAddictionPlayTime;			// 防沉迷游戏时长

	long long			lCurrentTime;					// 坐下时间
};

// 比赛结束信息
struct CMD_MatchEnd
{
	CMD_MatchEnd()
	{
		memset(this, 0, sizeof(CMD_MatchEnd));
	}
	long long			lUserID[GAME_PLAYER_COUNT];							// 用户ID
	char				szName[GAME_PLAYER_COUNT][USER_NAME_LEN];			// 用户名
	char				szNickname[GAME_PLAYER_COUNT][USER_NAME_LEN];		// 昵称
	long long			lGameCoin[GAME_PLAYER_COUNT];						// 鱼币
	int					iRewardGold[GAME_PLAYER_COUNT];						// 奖励金币
	long long			lGoldChange[GAME_PLAYER_COUNT];						// 金币
	long long			lPointChange[GAME_PLAYER_COUNT];					// 积分
};

//////////////////////////////////////////////////////////////////////////

#endif
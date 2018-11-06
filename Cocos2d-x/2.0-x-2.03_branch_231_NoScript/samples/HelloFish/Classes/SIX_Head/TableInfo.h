
#ifndef TABLE_INFO_H
#define TABLE_INFO_H

#include "./PublicMacro.h"

class CSingleUser;
//typedef int BOOL;	// 微软内定的类型

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

//--- 宏定义的消息码 -----------------------------------------------




//--- 枚举 ---------------------------------------------------------


enum // 游戏系统的状态
{
	GAME_SYS_STATE_NO = 0,	// 游戏未开始
	GAME_SYS_STATE_RUNING,	// 游戏进行中
	GAME_SYS_STATE_PAUSH,	// 游戏冻结，即暂停
};

enum  // 游戏开始的类型
{
	GAME_BEGIN_TYPE_AUTO = 0,	// 不管有无人坐下都会自动开始
	GAME_BEGIN_TYPE_ONLY_ONE,// 只要有一个坐下就开始
	GAME_BEGIN_TYPE_ALL_SIT,// 全都坐下才开始
	GAME_BEGIN_TYPE_ANY,// 座位数量内的任意几个人都可以开打，比如2个人也可以打，三个人也可以打
};

//--- 结构 ---------------------------------------------------------
struct SEAT_INFO;

// 桌子信息
struct TABLE_INFO:public DATA_BASE<TABLE_INFO>
{
	TABLE_INFO() {	memset(this, 0, sizeof(*this)); }
	

	int	iTableNo;	// 桌号
	int	iSeatNum;	// 每桌座位数
	int	iScenesID; // 场景ID
};

// 座位信息
struct SEAT_INFO:public DATA_BASE<SEAT_INFO>
{
	SEAT_INFO()
	{
		memset(this, 0, sizeof(*this)); 
	//	bFreeSeat = true;
		pSingleUser = NULL;
		bWarning = false;
	}

	//int			 iSeatNo;		// 座位号
	//bool		 bFreeSeat;		// 空座位
	unsigned int nOperateTime;	// 操作时间		// add by cxf(用于时间段内未开火则退出桌子)
	bool		 bWarning;		// 是否发送过超时警告
	CSingleUser* pSingleUser;	// 单个用户
};

// 坐下
struct SITDOWN:public DATA_BASE<SITDOWN>
{
	enum
	{
		ERR_CAN_NOT_BEGIN = 1000,		// 不能开始游戏
		ERR_CAN_NOT_SIT_DOWN = 1010,	// 房间禁止坐下状态
	};

	SITDOWN()
	{
		memset(this, 0, sizeof(*this));
		lUserId = INVALID_USER_ID;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}

	long long lUserId; 

	int iTableNo;	// 桌号
	int iSeatNo;	// 座位号
	int iRes;		// 结果值
	//add by Ivan_han 20130713
	long long	lGoldLogin;		// 登录时的金币值
	long long	lPointLogin;	// 登录时的积分

};

// 举手，坐下后的消息，客户端要等到初始化完毕后，发此消息，服务端才发鱼
struct RAISE_HAND : public DATA_BASE<RAISE_HAND>
{
	RAISE_HAND()
	{
		memset(this, 0, sizeof(*this));
	}
	
	int iRes;		// 结果值
};

// 离座
struct LEAVE_SEAT:public DATA_BASE<LEAVE_SEAT>
{
	LEAVE_SEAT(long long UserId=INVALID_USER_ID,int TableNo=INVAL_TABLE_NO,int SeatNo=INVAL_SEAT_NO) 
	{	
		memset(this, 0, sizeof(*this));	
		lUserId = UserId;
		iTableNo = TableNo;
		iSeatNo = SeatNo;
	}

	long long lUserId;

	int iTableNo;	// 桌号
	int iSeatNo;	// 座位号
	int iRes;
};

// 踢一个玩家离座
struct TICK_ONE_LEAVE_SEAT:public DATA_BASE<TICK_ONE_LEAVE_SEAT>
{
	enum
	{
		TFLS_MGR_ERR = 1,	// 管理者非法
		TFLS_TABLE_ERR,		// 桌号非法
		TFLS_SEAT_ERR,		// 座号非法
	};

	TICK_ONE_LEAVE_SEAT()
	{
		iRes = 0;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}

	int iRes;
	int	iTableNo;		// 被踢的桌号
	int	iSeatNo;		// 被踢的座号
};

// 踢一桌玩家离座
struct TICK_TABLE_LEAVE_SEAT:public DATA_BASE<TICK_TABLE_LEAVE_SEAT>
{
	enum
	{
		TFLS_MGR_ERR = 1,	// 管理者非法
		TFLS_TABLE_ERR,		// 桌号非法
	};

	TICK_TABLE_LEAVE_SEAT()
	{
		iRes = 0;
		iTableNo = INVAL_TABLE_NO;
		bWriteScore = false;
	}

	int iRes;
	int	iTableNo;		// 被踢的桌号
	bool bWriteScore;	// 踢完后是否写分
};

// 踢所有在座的玩家离座
struct TICK_ALL_LEAVE_SEAT:public DATA_BASE<TICK_ALL_LEAVE_SEAT>
{
	enum
	{
		TFLS_MGR_ERR = 1,	// 管理者非法
	};

	TICK_ALL_LEAVE_SEAT()
	{
		iRes = 0;
		bWriteScore = false;
	}

	int iRes;
	bool bWriteScore;	// 踢完后是否写分
};

// 
struct CMD_SC_USER_DATA_CHANGE
{
	CMD_SC_USER_DATA_CHANGE()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lUserId;				// 用户ID
	int			iGold;					// 用户金币
	int			iPoint;					// 用户积分
	int			iPresentBullet;			// 赠送子弹数量
};

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

struct CMD_SC_ANTI_ADDICTION
{
	CMD_SC_ANTI_ADDICTION()
	{
		memset(this, 0, sizeof(*this));
	}
	long long lUserId;					// 用户ID
	char szContent[CHAT_CONTENT_LEN];	// 内容
};

struct CMD_SC_MATCH_COUNTDOWN
{
	CMD_SC_MATCH_COUNTDOWN()
	{
		memset(this, 0, sizeof(*this));
	}
	int iMatchCountDown;
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
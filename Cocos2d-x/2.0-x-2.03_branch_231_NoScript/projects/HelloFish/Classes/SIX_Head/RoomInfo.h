
#ifndef ROOM_INFO_H
#define ROOM_INFO_H

#include "./PublicMacro.h"

#include "UserInfo.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

#define ROOM_GAME_TYPE_POINT					(1)						// 积分场
#define ROOM_GAME_TYPE_GOLD						(2)						// 金币场
#define ROOM_GAME_TYPE_MATCH					(3)						// 比赛场

//--- 枚举 ---------------------------------------------------------
enum ROOM_STATE	// 房间状态，二进制掩码
{
	RS_CAN_LOGIN	= 0x0000000000000001,	// 登录房间
	RS_CAN_SIT		= 0x0000000000000002,	// 入座
};

//--- 结构 ---------------------------------------------------------

struct MY_TEST
{
	int a;
	int b;
};

struct ROOM_MGR_CONFIG	// 房管配制文件参数
{
	ROOM_MGR_CONFIG()
	{
		iRoomMgrPort=6150;
		sprintf(DbIp, "127.0.0.1");
		iDbPort=3306; 
	}

	int iRoomMgrPort;			// 房管监听端口，用来监听房间
	char DbIp[IP_ADDRES_LEN];	// 房管连接的数据库Ip
	int iDbPort;				// 房管连接的数据库的监听端口
	char szDbUserName[DB_USER_NAME_LEN];		// 数据库用户名称
	char szDbUserPwd[DB_PASS_LEN];				// 数据库用户密码
	char szDbName[DB_NAME_LEN];					// 数据库名字
};

struct REQUEST_ROOM_INFO	// 申请房间信息
{
	REQUEST_ROOM_INFO() {	memset(this, 0, sizeof(*this)); }

	int	iRoomId;			// 房间ID，是唯一的。注意前 100 的值归系统内部使用
};

struct REQUEST_ROOM_ERR	// 申请房间信息失败
{
	REQUEST_ROOM_ERR() {	memset(this, 0, sizeof(*this)); }

	int	iRoomId;	// 房间ID，是唯一的。注意前 100 的值归系统内部使用
	int	iRes;		// 失败码
};

// 桌子的框架参数
struct CLIENT_FRAME_PARAM:public DATA_BASE<CLIENT_FRAME_PARAM>
{
	CLIENT_FRAME_PARAM()
	{
		iMsgBlockSize = 2048;
		iSendHeartbeatTime = 30*1000;	// 30 秒，标准默认值;
		iShrinkPoolsTime = 3*60*1000;	// 标准默认值的（5分钟）

		bAutoReConnect = true;
		iAutoReConnectTime = 2*1000;
	}

	int iMsgBlockSize;				// 内核消息块的长度
	long long iSendHeartbeatTime;	// 发送心跳包的时间，单位是 ms
	long long iShrinkPoolsTime;		// 收缩各种池的时间，单位是 ms

	bool bAutoReConnect;			// TRUE 表示断线后自动重连，FALSE 表示断线后不再重连
	int  iAutoReConnectTime;		// 断线重连的间隔时间，单位ms
};

// 连接房管服务器 RMS（RoomMgrServer ）的参数
struct CLIENT_TO_RMS_PARAM:public DATA_BASE<CLIENT_TO_RMS_PARAM>
{
	CLIENT_TO_RMS_PARAM(char *IP="127.0.0.1",int Port=6150,int MsgBlockSize=2048,int SendHeartbeatTime=30*1000,int ShrinkPoolsTime=3*60*1000,bool AutoReConnect=true,int AutoReConnectTime=2*1000)
	{ 
		_snprintf(szIP, sizeof(szIP)-1,"%s", IP);
		iPort = Port;

		iMsgBlockSize = MsgBlockSize;
		iSendHeartbeatTime = SendHeartbeatTime;	// 30 秒，标准默认值;
		iShrinkPoolsTime = ShrinkPoolsTime;	// 标准默认值的（5分钟）

		bAutoReConnect = AutoReConnect;
		iAutoReConnectTime = AutoReConnectTime;
	}

	char szIP[IP_ADDRES_LEN];	// 房间服的IP
	int	 iPort;					// 房间服的端口

	int iMsgBlockSize;				// 内核消息块的长度
	long long iSendHeartbeatTime;	// 发送心跳包的时间，单位是 ms
	long long iShrinkPoolsTime;		// 收缩各种池的时间，单位是 ms

	bool bAutoReConnect;			// TRUE 表示断线后自动重连，FALSE 表示断线后不再重连
	int  iAutoReConnectTime;		// 断线重连的间隔时间，单位ms
};

struct ROOM_CONFIG	// 房间配置文件参数
{
	ROOM_CONFIG()
	{
		memset(this, 0, sizeof(*this));
	}

	int		lRoomId;			// 本房间的ID
	int		iLogicThreadNum;	// 房间逻辑任务线程数量
	int		iDbThreadNum;		// 数据库任务线程数量

	char	szRoomMgrIp[IP_ADDRES_LEN];	// 房管IP
	int		RoomMgrPort;				// 房管监听端口
};

// 房间配置 add by cxf
struct SERVER_ROOM_CONFIG
{
	SERVER_ROOM_CONFIG()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iId;										// 配置ID
	int				iRoomId;									// 房间ID
	int				iBeginMode;									// 开始模式(0没有人也开始，1有人进入就开始，2桌子坐满就开始)
	int				iStartNotEnter;								// 游戏开始不能进入(0:不能进入;1:能进入);如:比赛场已经在进行中是不能进入游戏的。
	int				iEnterTradeGold;							// 进入上缴报名金币
	int				iEnterTradePoint;							// 进入上缴报名积分
	int				iEnterPresentBullet;						// 进入赠送子弹
	int				iGameTime;									// 每局最大结束时间
};

// 房间奖励 add by cxf
struct SERVER_ROOM_REWARD
{
	SERVER_ROOM_REWARD()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iRoomId;									// 房间ID
	int				iRewardGold1;								// 奖励金币第一名
	int				iRewardGold2;								// 奖励金币第二名
};

// 服务端的房间信息
struct SERVER_ROOM_INFO:public DATA_BASE<SERVER_ROOM_INFO>
{
	SERVER_ROOM_INFO() 
	{ 
		memset(this, 0, sizeof(*this)); 
		
		lRoomTeltComIp = 0x0100007F;	// 1.0.0.127 ，房间的中国电信IP，主要是客户端用这个值。经过 inet_ntoa 解析出来就是 127.0.0.1
		lRoomUnicomIp = 0x0100007F;		// 1.0.0.127 ，房间的中国联通IP ，也包括了网通等
		lRoomMobileIp = 0x0100007F;		// 1.0.0.127 ，房间的中国移动IP

		iRoomPort = 5150;

		iOnlyReadDbIp = 0x6301A8C0;	// 99.1.168.192 经过 inet_ntoa 解析出来就是192.168.1.99
		iOnlyReadDbPort = 3306;

		iCanEnableRoom = 1;

		iTables = 10;	
		iSeatNum = 4;	

		iRoomVer = 0x00000001;
	}

	int			iRes;

	long long	lParentId;			// 父节点ID，通常用于树型组件的定位
	int			iRoomId;			// 房间ID，是唯一的。注意前 100 的值归系统内部使用

	char		szRoomName[ROOM_NAME_LEN];	// 房间名称
	int			iRoomPort;					// 房间的监听端口

	long long	lRoomTeltComIp;	// 房间的中国电信IP，主要是客户端用这个值
	long long	lRoomUnicomIp;	// 房间的中国联通IP ，也包括了网通等，主要是客户端用这个值
	long long	lRoomMobileIp;	// 房间的中国移动IP，主要是客户端用这个值

	int			iOnlyReadDbIp;							// 房间相连的只读数据库IP
	char		szOnlyReadDbName[DB_NAME_LEN];			// 房间相连的只读数据库名称，通常是 six_devisions
	char		szOnlyReadDbUserName[DB_USER_NAME_LEN];	// 房间相连的只读数据库用户名称，通常是 root
	char		szOnlyReadDbPass[DB_PASS_LEN];			// 房间相连的只读数据库密码

	int			iOnlyReadDbPort;	// 房间相连的只读数据库监听端口

	int			iCanEnableRoom;		// 1 允许启动房控，0 此房间已被禁用

	long long	lGameType;		// 游戏类型，以二字节单位表示含义：
	                            //     最低二字节表示：扑克类、棋类、休闲类。
								//     再高二字节表示：普通游戏、金币游戏、比赛游戏、测试类游戏。cxf:1=积分房间、2=金币游戏、3=比赛游戏、4=测试类游戏

	int	iTables;		// 房内桌子的数量
	int iSeatNum;		// 每桌人数，即每桌的座位数量

	int	iBasePoint;	// 倍频，10倍区、50倍区、100倍区
	long long	lDoorsill;	// 进入的门槛，假设为n ，即需要n的积分或金币才能进入房间。

	long long	lRoomRule;		// 房间规则，如会员房间、地址限制、允许旁观、自动坐下、限制座位、限制同IP
	long long	lRoomRuleEx;	// 房间规则扩展 

	char		szFightTable[FIGHT_TABLE_NAME_LEN];	// 战斗结果对应的表名：1、金币类游戏通常是 game_money，
													//                     2、比赛类游戏通常是 match_x_x ，
													//                     3、积分游戏如“三人挖坑”是 Cavern ，所有的“三人挖坑”积分游戏都用 Cavern 表

	int				iCanAutoOpenRoom;	// 1 表示允许自动启动房间，0 表示禁止自动启动房间
	EASY_DATA_TIME	stOpenRoomTime;		// 自动启动房间的时间
	int				iCanCloseRoom;		// 1 表示允许自动关闭房间，0 表示禁止自动关闭房间
	EASY_DATA_TIME	stCloseRoomTime;	// 自动关闭房间的时间

	
	char szRoomMessage[ROOM_MESSAGE_LEN];	// 玩家进入房间时会收到的消息提示。
	char szGameMessage[GAME_MESSAGE_LEN];	// 玩家进入游戏时会收到的消息提示。

	int	iClientVer;	// 客户端程序对应的版本号
	int	iRoomVer;	// 房间程序对应的版本号

	int	iRoomPeopleCount;

	SERVER_ROOM_CONFIG roomConfig;				// 房间配置
	SERVER_ROOM_REWARD roomReward;				// 房间奖励
};

/*
author cxf
date 2013-07-06
description 房间信息简化信息
*/
struct SERVER_ROOM_INFO_SIM
{
	SERVER_ROOM_INFO_SIM()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lParentId;					// 父节点ID，通常用于树型组件的定位
	int			iRoomId;					// 房间ID，是唯一的。注意前 100 的值归系统内部使用
	long long	lGameType;					// 游戏类型: 1=积分房间、2=金币游戏、3=比赛游戏、4=测试类游戏。
	int			iBasePoint;					// 倍频，10倍区、50倍区、100倍区
	long long	lRoomRule;					// 房间规则，如会员房间、地址限制、允许旁观、自动坐下、限制座位、限制同IP(暂时没用上)
	char		szRoomName[ROOM_NAME_LEN];	// 房间名称
	int			iTables;					// 房内桌子的数量
	int			iSeatNum;					// 每桌人数，即每桌的座位数量
	int			iRoomPeopleCount;			// 房间人数
};
// 客户端的房间信息
struct CLIENT_ROOM_INFO:public DATA_BASE<CLIENT_ROOM_INFO>
{
	CLIENT_ROOM_INFO(char *IP="",int Port=0,char *Name="",char *Password="") 
	{ 
		memset(this, 0, sizeof(*this)); 
		_snprintf(szIP,sizeof(szIP),"%s",IP);
		iPort = Port;

		_snprintf(szName,sizeof(szName),"%s",Name);
		_snprintf(szPassword,sizeof(szPassword),"%s",Password);
	}

	char szIP[IP_ADDRES_LEN];	// 房间服的IP
	int	 iPort;					// 房间服的端口

	char szName[USER_NAME_LEN];			// 用户名
	char szPassword[USER_PASSWORD_LEN];	// 加密后的密码，例如用 MD5 加密后不可逆的密码

	
};

// 登录房间
struct LOGIN_ROOM:public DATA_BASE<LOGIN_ROOM>
{
	LOGIN_ROOM()
	{ 
		memset(this, 0, sizeof(*this)); 
	}
	long long lUserID;
	char szName[USER_NAME_LEN];			// 用户名
	char szPassword[USER_PASSWORD_LEN];	// 加密后的密码，例如用 MD5 加密后不可逆的密码
};

// 登录房间成功
struct LOGIN_ROOM_SUCC
{
	LOGIN_ROOM_SUCC() 
	{ 
		memset(this, 0, sizeof(*this)); 
		bAlreadyInRoom = false;
	}

	// 可以安排一些房间的信息

	char szIP[IP_ADDRES_LEN];	// 房间服的IP
	int	 iPort;					// 房间服的端口
	bool bAlreadyInRoom;		// 已经在房间里啦

	USER_INFO_SIM userInfo;	// 用户信
};

struct RECOME_AFTER_CUT	// 断线重入
{
	RECOME_AFTER_CUT()
	{
		memset(this, 0, sizeof(*this)); 

		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
		bAlreadyInRoom = true;
	}

	int	 iErrCode;	// 若登录是成功，返回0值。
					// 若是登录失败，返回非0值的错误码如下：

	int	 iPort;				// 房间服的端口

	bool bAlreadyInRoom;	// 已经在房间里啦
	int iTableNo;	// 桌号
	int iSeatNo;	// 座位号

	char szName[USER_NAME_LEN];			// 用户名
};

// 登录房间失败
struct LOGIN_ROOM_FAIL:public DATA_BASE<LOGIN_ROOM_FAIL>
{
	enum
	{
		ERR_CAN_NOT_LOGIN = 10,	// 房间禁止登录状态
		ERR_01 = 20,				// 用户名与密码不符，或不存在该用户
		ERR_02 = 30,				// 用户名不唯一
		ERR_30 = 40,				// 服务骨骼增加用户失败
	};

	LOGIN_ROOM_FAIL() { memset(this, 0, sizeof(*this)); }

	int	 iErrCode;	// 若登录是成功，返回0值。
					// 若是登录失败，返回非0值的错误码如下：
};

// 离开房间的结果
struct LEAVE_ROOM_RESULT:public DATA_BASE<LEAVE_ROOM_RESULT>
{
	LEAVE_ROOM_RESULT() { memset(this, 0, sizeof(*this)); }

	USER_INFO userInfo;
	int	 iErrCode;	// 若登录是成功，返回0值。
					// 若是登录失败，返回非0值的错误码如下：
};

struct MANAGER_POWER_ERR:public DATA_BASE<MANAGER_POWER_ERR>	// 无此管理权限
{
	MANAGER_POWER_ERR()
	{
		iWantPower = 0;
	}
	int iWantPower;		// 想施加的权限
};


// 踢玩家离房
struct TICK_USER_OUT_ROOM:public DATA_BASE<TICK_USER_OUT_ROOM>
{
	enum
	{
		TUOR_NO_FIND = 10,			// 房内无此玩家，可能他还没登录房间
		TUOR_TABLE_ERR = 15,		// 桌号非法
		TUOR_SEAT_NO_USER = 20,		// 座号上没有人
	};

	enum
	{
		TICK_BY_TABLE_SEAT = 10,	// 按桌号、座号踢
		TICK_BY_NAME = 20,			// 按名字踢
		TICK_BY_TABLE = 30,			// 按桌号踢，踢一整桌人离房
		TICK_BY_ALL = 40,			// 踢所有的人离房
	};

	TICK_USER_OUT_ROOM()
	{
		iRes = 0;
		iTickMode = TICK_BY_TABLE_SEAT;
		bWriteScore = false;	
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
		memset(szName, 0, sizeof(szName));
	}

	int iRes;			// 踢的结果
	int iTickMode;		// 踢的方式，参考 TICK_BY_TABLE_SEAT 等
	bool bWriteScore;	// 踢完后是否写金币变化值
	int	iTableNo;		// 被踢的桌号
	int	iSeatNo;		// 被踢的座号
	
	char szName[USER_NAME_LEN];			// 用户名
};

// 写金币变化值
struct CMD_WRITE_SCORE:public DATA_BASE<CMD_WRITE_SCORE>
{
	CMD_WRITE_SCORE() 
	{ 
		memset(this, 0, sizeof(*this)); 
		lUserId = INVALID_USER_ID;
		lChannelNo = INVALID_CHANNEL_NO;
	}

	long long	llType;			// 类型：积分表、金币表
	long long	lUserId;		// 房管需要这个进行用户操作，房管并不能用通道号去操作数据库
	long long	lChannelNo;		// 踢玩家后消息会从房管服回来，那时 CSingleUser* 早已经不存在啦，所以必需要从房管传回玩家的通道
	long long	lGold;			// 金币的变化量
	long long	lPoint;			// 积分的变化量
	long long	llGameCoin;		// 鱼币币量
	int			iBasePoint;		// 房间倍率
	int			iBuyBulletCount;// 购买子弹数量
	int			iBulletCount;	// 剩余子弹数量
	int			iTableNo;		// 桌子号
	int			iRoomNo;		// 房间号
	int			iFeats;			// 功勋
	long long	lAntiAddictionTime;// 防沉迷时间
	long long	lAntiAddictionPlayTime;// 防沉迷游戏时长
};

// 写金币变化值结果
struct WRITE_SCORE_RESULT:public DATA_BASE<WRITE_SCORE_RESULT>
{
	WRITE_SCORE_RESULT()
	{	
		memset(this, 0, sizeof(*this)); 
		lUserId = INVALID_USER_ID;
	}

	int			iRes;
	LONGLONG	lUserId;		// 房管需要这个进行用户操作，房管并不能用通道号去操作数据库
	LONGLONG	lGold;			// 当前的分值
	LONGLONG    lPoint;			// 积分
};

// 拼网络延迟
struct CMD_NET_GAP_TIME
{
	CMD_NET_GAP_TIME()
	{
		memset(this,0,sizeof(*this));
	}
	long long		llUserID;				// 用户ID
	long long		llSendTime;				// 发送时间
};

// 排队
struct CMD_USER_ARRANGE_QUEUE_LIST
{
	CMD_USER_ARRANGE_QUEUE_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lUserId;				// 用户ID
	long long	lChannelNo;				// 用户通道
};

// 排队完成
struct CMD_USER_ARRANGE_QUEUE_FINISH
{
	CMD_USER_ARRANGE_QUEUE_FINISH()
	{
		memset(this,0,sizeof(*this));
	}
	int				iRet;				// 排队状态
};

// 取消排队完成
struct CMD_USER_CANCEL_ARRANGE_QUEUE_FINISH
{
	CMD_USER_CANCEL_ARRANGE_QUEUE_FINISH()
	{
		memset(this,0,sizeof(*this));
	}
	int				iRet;				// 取消状态
};


// 写分
struct CMD_MatchAccounts
{
	CMD_MatchAccounts()
	{
		memset(this,0,sizeof(*this));
	}
	long long			lUserID;						// 用户ID
	long long			lGoldChange;					// 变动金币
	long long			lPointChange;					// 变动积分
	long long			lGameCoin;						// 游戏币
	int					iRewardGold;					// 奖励金币
	int					iTableNo;						// 桌子号
	int					iRoomID;						// 房间号
	long long			lAntiAddictionTime;				// 防沉迷时间
	long long			lAntiAddictionPlayTime;			// 防沉迷游戏时长
};

//OnAntiAddiction是否启用防沉迷
struct CMD_Anti_Addiction
{
	CMD_Anti_Addiction()
	{
		memset(this,0,sizeof(*this));
	}
	bool bIsAntiAddiction;
};

struct CMD_RoomUserCount
{
	CMD_RoomUserCount()
	{
		memset(this,0,sizeof(*this));
	}
	int iRoomUserCount;								// 房间人数
	int iArrangeQueueCount;							// 排队人数
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
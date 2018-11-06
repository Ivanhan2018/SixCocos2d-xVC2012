
/*
**服务器内部使用头文件
**description:
**    C		 -> 中心服务器
**	  L		 -> 登录服务器
**    G		 -> 游戏服务器
**    D		 -> 数据库服务器
**    F		 -> 查询服务器
**    P		 -> 大厅服务器
**    **G	 -> 代表互用消息

**    (LC)         -> 登录服务器发往中心服务器
**    (GC)         -> 游戏服务器发往中心服务器
**    (DC)         -> 数据库服务器发往中心服务器
**    (DCG)        -> 数据库服务器发往中心服务器/中心服务器发往数据库服务器
******MAIN		   -> 内部服务器主消息
******SUB		   -> 内部服务器子消息
*/

#include "PublicMacro.h"

#ifndef CMD_INNER_SERVER_H
#define CMD_INNER_SERVER_H

// 登录服主消息
#define MAIN_LCG_LOGIN										10000
#define SUB_LC_LOGIN_REGISTER								10001		// 登录服务器注册
#define SUB_CL_GAME_REGISTER_NOTIFY							10002		// 游戏服务器注册通知
#define SUB_CL_PLAZA_REGISTER_NOTIFY						10003		// 大厅服务器注册通知
#define SUB_CL_GAME_CLOSE_NOTIFY							10004		// 游戏服务器关闭通知
#define SUB_CL_PLAZA_CLOSE_NOTIFY							10005		// 大厅服务器关闭通知

// DB服主消息
#define MAIN_LCG_WRITEDB									11000
#define SUB_LC_WRITEDB_REGISTER								11001

// 大厅服主消息
#define MAIN_PCG_PLAZA										12000
#define SUB_PC_PLAZA_REGISTER								12001

// 游戏服主消息
#define MAIN_GCG_GAME										13000
#define SUB_GC_GAME_REGISTER								13001

enum // 游戏
{
	GAME_FISH = 1,		// 捕鱼游戏
	GAME_SANGONG = 2,	// 三公游戏
	GAME_NIUNIU = 3,	// 牛牛游戏
	GAME_SHIDIANBAN = 4,// 十点半游戏
};


// 服务器关闭通知
struct CMD_ServerCloseNotify
{
	CMD_ServerCloseNotify()
	{
		memset(this, 0, sizeof(*this));
	}
	long long lHandleId;
};

// 登录服务器注册
struct CMD_Login_Register
{
	CMD_Login_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lChannelNo;				// 通道号
	int			iPort;					// 端口
};

// DB服务器注册
struct CMD_WriteDbServer_Register
{
	CMD_WriteDbServer_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lChannelNo;				// 通道号
	int			iPort;					// 端口
};

// DB服务器注册
struct CMD_PlazaServer_Register
{
	CMD_PlazaServer_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long	lChannelNo;				// 通道号
	int			iPort;					// 端口
	char		szIp[IP_ADDRES_LEN];	// IP
};

// 游戏
struct CMD_GameServer_Register
{
	CMD_GameServer_Register()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lChannelNo;							// 通道号

	long long		lParentId;							// 父节点（关卡 1:初级场;2:中级场....）..
	int				iGameID;							// 游戏ID(比如：1捕鱼; 2斗地主; 3麻将...)
	int				iRoomType;							// 游戏类型(1=积分房间、2=金币游戏、3=比赛游戏)..
	int				iRoomId;							// 房间ID
	long long		lRoomTeltComIp;						// 房间的中国电信IP
	long long 		lRoomUnicomIp;						// 房间的中国联通IP
	long long		lRoomMobileIp;						// 房间的中国移动IP
	int				iRoomPort;							// 房间端口
	char			szRoomName[ROOM_NAME_LEN];			// 房间名字
	bool			bAutoSit;							// 是否自动入座(0:不自动，需要手动点坐桌和椅子进入; 1:自动入座，不需要点击椅子号)
	int				iBasePoint;							// 倍率..
	int				iDoorsill;							// 进入门槛(自身金币少于门槛不能进入房间)..
	int				iMaxDoorsill;						// 最高进入门槛(自身金币少于门槛不能进入房间)..
	int				iTables;							// 房内桌子的数量
	int				iSeatNum;							// 每桌人数，即每桌的座位数量

	int				iEnterTradeGold;					// 报名费(金币)
	int				iEnterTradePoint;					// 报名费(积分)
	int				iRewardGold1;						// 第一名奖励
	int				iRewardGold2;						// 第二名奖励
	int				iPlayerCount;						// 游戏人数
};

#endif

#ifndef USER_INFO_H
#define USER_INFO_H

#include "./PublicMacro.h"
#include "./EasyDataTime.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

struct EASY_DATA_TIME;

enum USER_STATE	// 用户状态
{
	US_OFFLINE = 0,				// 离线，不在房间里
	US_ONLINE_LEAVE_SIT,		// 在线，在房间里，但离座
	US_ONLINE_SITDOWN,			// 在线，在房间里，在坐，但没举手
	US_ONLINE_SITDOWN_RAISE,	// 在线,在房间里，在坐，已举手
	US_ONLINE_PLAYLING,			// 在游戏中
	US_WAIT_RECONNECT,			// 断线后等待重入
};

// 用户身份
enum UserIdentity
{// 身份标识是用位表示00000001=1表示高级玩家,00000010=2表示一级管理员........
	US_IDENTITY_HIGH_PLAYER = 1,				// 高级玩家(在游戏中可以获取好牌)
	//xxx					= 2,				// 一级管理员
	//xxx					= 4,				// 二级管理员
	//xxx					= 8,				// 三级管理员
	//....
};

// 客户端的用户信息
struct USER_INFO
{
	USER_INFO()
	{
		memset(this, 0, sizeof(*this));

		lChannelNo = INVALID_CHANNEL_NO;
		lUserId = INVALID_USER_ID;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}
	
	char				szName[USER_NAME_LEN];					// 用户帐号即登录名称
	char				szNickname[USER_NAME_LEN];				// 昵称
	char				szPassword[USER_PASSWORD_LEN];			// 登录密码，MD5 后的值
	char				szBankPassword[USER_PASSWORD_LEN];		// 银行密码，MD5 后的值
	char				szIdentityCard[USER_IDENTITY_CARD_LEN];	// 身份征号码

	EASY_DATA_TIME		stRegistTime;							// 注册时间
	EASY_DATA_TIME		stLastLoginTime;						// 最后登陆时间

	int					iSex;									// 性别：0男性、1女性
	int					iRegisterIP;							// 注册 IP
	int					iLastLoginIP;							// 最后登陆 IP
	int					iTableNo;								// 桌号
	int					iSeatNo;								// 座位号
	int					iFeats;									// 功勋

	long long			lChannelNo;								// 通道号，服务端专用
	long long			lUserId;								// 用户ID
	long long			lClubId;								// 社团ID，社团功能可以包下一些桌子，只有该社团成员才能入坐。
	long long			lIdentity;								// 玩家的身份：一级管理员、二级管理员、黄钻会员、绿钻会员、普通玩家等
	long long			lMasterPower;							// 管理权限（是掩码）：允许发警告消息、允许发游戏信息、禁止其他人游戏、踢玩家下线、允许加减分数、禁止进入银行 等
	long long			lMasterPowerEx;							// 管理权限，扩展
	long long			lGamePower;								// 玩家游戏权限（是掩码）：允许游戏聊天、允许发短信息、许任何旁观 等
	long long			lGamePowerEx;							// 玩家游戏权限，扩展。
	long long			lSysLogoID;								// 系统提供的头像系列。
	long long			lExperience;							// 经验值
	long long			lAllLoginCounts;						// 总登陆次数
	long long			lGoldLogin;								// 登录时的金币值
	long long			lPointLogin;							// 登录时的积分
	long long			lNetGapTime;							// 用户发送ping时间
	long long			lAntiAddictionTime;						// 防沉迷时间
	long long			lAntiAddictionPlayTime;					// 用户防沉迷游戏时间
	bool				bIsJuveniles;							// true:是未成年;false:成年人
	long long			lRevenue;								// 税收
	int					iWinCount;								// 赢数量
	int					iLostCount;								// 输数量
	USER_STATE			stUserState;							// 用户状态
};

// 客户端的用户信息
struct USER_INFO_SIM
{
	USER_INFO_SIM()
	{
		memset(this, 0, sizeof(*this));
		lUserId = INVALID_USER_ID;
		iTableNo = INVAL_TABLE_NO;
		iSeatNo = INVAL_SEAT_NO;
	}

	long long	lUserId;						// 用户ID
	char		szName[USER_NAME_LEN];			// 用户帐号即登录名称
	char		szNickname[USER_NAME_LEN];		// 昵称
	char		szPassword[USER_PASSWORD_LEN];	// 登录密码，MD5 后的值
	int			iSex;							// 性别：0男性、1女性

	long long	lIdentity;						// 玩家的身份：一级管理员、二级管理员、黄钻会员、绿钻会员、普通玩家等
	long long	lMasterPower;					// 管理权限（是掩码）：允许发警告消息、允许发游戏信息、禁止其他人游戏、踢玩家下线、允许加减分数、禁止进入银行 等
	long long	lGamePower;						// 玩家游戏权限（是掩码）：允许游戏聊天、允许发短信息、许任何旁观 等
	long long	lSysLogoID;						// 系统提供的头像系列。
	long long	lExperience;					// 经验值
	long long	lGoldLogin;						// 登录时的金币值
	long long	lPointLogin;					// 登录时的积分
	int			iTableNo;						// 桌号
	int			iSeatNo;						// 座位号
	USER_STATE	stUserState;					// 用户状态
};

// 任务列表
struct CMD_UserTaskInfo
{
	CMD_UserTaskInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	long long lUserId;	// 用户ID
	int iTaskId;		// 任务ID
	int	iSchedule;		// 任务当前完成进度值	
};

// 局数日志
struct CMD_UserBattleRecord
{
	CMD_UserBattleRecord()
	{
		memset(this, 0, sizeof(*this));
	}
	int iResult;		// 当局结果(0:输;1:赢;2:平)
};

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif

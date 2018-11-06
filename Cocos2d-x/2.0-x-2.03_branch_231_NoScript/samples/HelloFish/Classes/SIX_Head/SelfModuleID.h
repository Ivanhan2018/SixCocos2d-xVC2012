
#ifndef SELF_MODULE_ID
#define SELF_MODULE_ID

#ifdef WIN32
#include <tchar.h>
#include <strsafe.h>
#pragma comment(lib, "strsafe.lib") 
#endif
#include "PublicMacro.h"			// add by cxf

enum TASK_MODULE_ID	// 任务模块的 ID
{
	MODULE_ID_MY_LOGIC = 1,
	MODULE_ID_OTHER_LOGIC = 2,
	MODULE_ID_DB_MY_NAME = 3,
};

#define TIMER_ID_TEST_01 1
#define TIMER_ID_TEST_02 2

// 定时器ID
#define TIMER_ID_GET_FEATS_LIST		100		// 功勋列表
#define TIMER_ID_GET_MATCH_LIST		101		// 比赛列表
#define TIMER_ID_GENERATE_RANKING	102		// 生成排名
#define TIMER_ID_GET_GAME_ROOM_INFO	103		// 获取游戏和房间

// 定时器时间 generate
#define TIMER_TIME_GET_FEATS_LIST	(60*1000)*60	// 获取功勋时间
#define TIMER_TIME_GET_MATCH_LIST	(60*1000)*60	// 获取比赛时间
#define TIMER_TIME_GENERATE_RANKING	(60*1000)*60	// 获取比赛时间
#define TIMER_TIME_GET_GAME_ROOM_INFO (60*1000)*10	// 获取游戏和房间时间


#define MAIN_TEST_USER_INFO		10	// 模拟申请用户信息
#define SUB_TEST_USER_INFO_01  101	// 显示用户信息	
#define SUB_TEST_USER_INFO_02  102	// 不显示用户信息
#define SUB_HALL_LOGIN		 103	// 大厅登陆

#define MAIN_TEST_INTENSIVE     15	// 系统密集测试用
#define SUB_TEST_INTENSIVE_01 1001	// 密集测试，不处理就直接回发给对端
#define SUB_TEST_INTENSIVE_02 1003	// 密集测试，简单处理后就直接回发给对端

#define MAIN_TEST_DB  20				// 测试数据库
#define SUB_TEST_DB_INTENSIVE				201	// 密集测试数据库
#define SUB_TEST_DB_COMPREHENSIVE			202	// 综合测试数据库
#define SUB_TEST_REQUEST_USER_LIST			301	// 申请用户列表
#define SUB_TEST_REQUEST_USER_LIST_OVER		302	// 用户列表结束

#define MAIN_TEST_IMMEDIATELY_CUT		25	// 收到包立刻断开


/*
**author : add by cxf
**description:
******CS  -> 客户端发往服务器的
******SC  -> 服务器发往客户端的
******CSG -> 客户端/服务器互用
******MAIN_MSG -> 主消息
******SUB -> 子消息
*/
#define MAIN_MSG_LOGIN						2000		// 用户登录主消息
#define SUB_CS_USER_LOGIN					2101		// 用户登录子消息
#define SUB_SC_USER_LOGIN_SUC				2102		// 用户登录成功
#define SUB_SC_USER_LOGIN_FINISH			2103		// 用户登录完成
#define SUB_SC_GAME_LIST					2104		// 游戏列表
#define SUB_CSG_GAME_ROOM_LIST				2015		// 房间列表
#define SUB_SC_GAME_ROOM_LIST_SEDN_FINISH	2016		// 房间列表发送完成

#define SUB_CS_USER_REGISTER				2120		// 用户注册
#define SUB_SC_USER_REGISTER_FINISH			2121		// 用户注册成功
#define SUB_CS_UPDATE_USER_IDENTITY			2122		// 修改用户身份
#define SUB_CS_UPDATE_USER_IDENTITY_SUC		2123		// 修改用户身份完成
#define SUB_CS_UPDATE_USER_SYSLOGOID		2124		// 修改用户头像
#define SUB_CS_UPDATE_USER_SYSLOGOID_SUC	2125		// 修改用户头像完成

#define MAIN_MSG_SYS						3000		// 系统主消息（比如登录时个公告等等）

#define MAIN_MSG_RANKING					4000		// 用户排名
#define SUB_CSG_GET_FEATS_RANKING			4001		// 获取功勋排名
#define SUB_SC_GET_FEATS_RANKING_FINISH		4002		// 获取功勋排名完成
#define SUB_CS_UPD_USER_FEATS_RANKING		4003		// 领取用户功勋排名奖励
#define SUB_SC_UPD_USER_FEATS_RANKING_SUC	4004		// 领取用户功勋排名奖励成功
#define SUB_SC_UPD_USER_FEATS_RANKING_ERR	4005		// 领取用户功勋排名奖励失败
#define SUB_CSG_GET_MATCH_RANKING			4006		// 获取比赛排名
#define SUB_SC_GET_MATCH_RANKING_FINISH		4007		// 获取比赛排名完成
#define SUB_CS_UPD_USER_MATCH_RANKING		4008		// 领取用户比赛排名奖励
#define SUB_SC_UPD_USER_MATCH_RANKING_SUC	4009		// 领取用户比赛排名奖励成功
#define SUB_SC_UPD_USER_MATCH_RANKING_ERR	4010		// 领取用户比赛排名奖励失败


// 所有登录服操作
#define	RET_LOGIN_OPERATE_SUCCEED			0			// 操作成功
// 登录
#define	RET_USER_NOT_EXIST					10			// 用户名或密码错误
// 注册
#define	RET_USER_NAME_EXIST					20			// 帐号已经存在
#define RET_USER_NAME_IS_EMPTY				21			// 用户名为空
#define	RET_USER_NICKNAME_EXIST				30			// 昵称已经存在
// 领取奖励
#define RET_RANKING_NOT_CURRENT_USER		40			// 不能领取别人奖励
#define RET_RANKING_IS_GET					50			// 奖励已经领取过了
#define RET_RANKING_SEND_ID_NOT_EXIST		60			// 名次ID不存在

// 用户登录
struct CMD_CS_UserLogin
{
	CMD_CS_UserLogin()
	{
		memset(this,0,sizeof(*this));
	}
	char		szName[USER_NAME_LEN];					// 帐号
	char		szPwd[USER_PASSWORD_LEN];				// 密码
	char		szIp[IP_ADDRES_LEN];					// IP地址(服务器用)
	int			iGameID;								// 游戏ID(0:大厅登录;非0:游戏登录)
};

// 用户登录成功
struct CMD_SC_UserLoginInfo
{
	CMD_SC_UserLoginInfo()
	{
		memset(this, 0, sizeof(*this));
		iRet = -1;
	}
	int				iRet;								// 返回状态(0:成功;1:)
	LONGLONG		llUserID;							// 用户ID
	LONGLONG		llGold;								// 金币
	LONGLONG		llPoint;							// 积分
	char			szName[USER_NAME_LEN];				// 帐号
	char			szNickName[USER_NAME_LEN];			// 用户呢称
	int				iSex;								// 性别
	LONGLONG		lSysLogoID;							// 头像ID
	LONGLONG		lExperience;						// 经验值
	char			szIdCardNo[USER_IDENTITY_CARD_LEN];	// 身份证号码
	char			szIdCardName[USER_REAL_NAME_LEN];	// 身份证名字
};

// 游戏信息
struct CMD_SC_GAME_LIST
{
	CMD_SC_GAME_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iRet;								// 返回值
	int				iID;								// 游戏ID
	char			szGameName[GAME_NAME_LEN];			// 游戏名字
	char			szProgressName[PROGRESS_NAME_LEN];	// 游戏进程名字长度
	int				iGameType;							// 游戏类型
	int				iSortVal;							// 排序
};

// 功勋信息
struct CMD_SC_FEATS_LIST
{
	CMD_SC_FEATS_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// 列表ID
	int				iID;									// ID
	long long		lUserID;								// 用户ID
	char			szNickName[USER_NAME_LEN];				// 用户呢称
	int				iRankingCode;							// 排名编码
	int				iRankingNo;								// 排名
	int				iFeats;									// 功勋
	int				iRewardGold;							// 奖励金币
	int				iIsGet;									// 是否已经领取
};

// 信息
struct CMD_SC_MATCH_LIST
{
	CMD_SC_MATCH_LIST()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// 列表ID
	int				iID;									// ID
	long long		lUserID;								// 用户ID
	char			szNickName[USER_NAME_LEN];				// 用户呢称
	int				iRankingCode;							// 排名编码
	int				iRankingNo;								// 排名
	int				iGameCoin;								// 鱼币
	int				iRewardGold;							// 奖励金币
	int				iIsGet;									// 是否已经领取
};

// 领取功勋奖励
struct CMD_CS_UPD_FEATS_RANKING_REWARD
{
	CMD_CS_UPD_FEATS_RANKING_REWARD()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// 列表ID
	int				iID;									// ID
	long long		lUserID;								// 用户ID
	int				iRankingNo;								// 排名
};

// 领取比赛奖励
struct CMD_CS_UPD_MATCH_RANKING_REWARD
{
	CMD_CS_UPD_MATCH_RANKING_REWARD()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iSortId;								// 列表ID
	int				iID;									// ID
	long long		lUserID;								// 用户ID
	int				iRankingNo;								// 排名
};

// 领取功勋奖励成功
struct CMD_SC_UPD_FEATS_RANKING_SUC
{
	CMD_SC_UPD_FEATS_RANKING_SUC()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iID;									// ID
	long long		lUserID;								// 用户ID
	int				iRewardGold;							// 奖励金币
};

// 领取比赛奖励成功
struct CMD_SC_UPD_MATCH_RANKING_SUC
{
	CMD_SC_UPD_MATCH_RANKING_SUC()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iID;									// ID
	long long		lUserID;								// 用户ID
	int				iRewardGold;							// 奖励金币
};

// 领取功勋奖励失败
struct CMD_SC_UPD_FEATS_RANKING_ERR
{
	CMD_SC_UPD_FEATS_RANKING_ERR()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lUserID;								// 用户ID
	int				iRet;									// 失败原因
};

// 领取比赛奖励失败
struct CMD_SC_UPD_MATCH_RANKING_ERR
{
	CMD_SC_UPD_MATCH_RANKING_ERR()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lUserID;								// 用户ID
	int				iRet;									// 失败原因
};

// 用户登录
struct CMD_CS_UserRegister
{
	CMD_CS_UserRegister()
	{
		memset(this,0,sizeof(*this));
	}
	char		szName[USER_NAME_LEN];					// 帐号
	char		szPwd[USER_PASSWORD_LEN];				// 密码
	char		szNickName[USER_NAME_LEN];				// 昵称
	char		szIp[IP_ADDRES_LEN];					// IP地址(服务器用)
	int			iSex;									// 性别
	char		szIdCardNo[USER_IDENTITY_CARD_LEN];		// 身份证号码
	char		szIdCardName[USER_REAL_NAME_LEN];		// 身份证名字
};

// 修改身份
struct CMD_CS_UpdateUserIdentity
{
	CMD_CS_UpdateUserIdentity()
	{
		memset(this,0,sizeof(*this));
	}
	long long	lUserID;								// 用户ID
	char		szIdCardNo[USER_IDENTITY_CARD_LEN];		// 身份证号码
	char		szIdCardName[USER_REAL_NAME_LEN];		// 身份证名字
};

// 修改身份返回
struct CMD_CS_UpdateUserIdentityRet
{
	CMD_CS_UpdateUserIdentityRet()
	{
		memset(this,0,sizeof(*this));
	}
	int			iRet;									// 返回值
	long long	lUserID;								// 用户ID
	char		szIdCardNo[USER_IDENTITY_CARD_LEN];		// 身份证号码
	char		szIdCardName[USER_REAL_NAME_LEN];		// 身份证名字
};

// 修改头像
struct CMD_CS_UpdateUserSyslogoid
{
	CMD_CS_UpdateUserSyslogoid()
	{
		memset(this,0,sizeof(*this));
	}
	long long	lUserID;								// 用户ID
	long long	lSyslogoid;								// 头像
};

// 修改头像返回
struct CMD_CS_UpdateUserSyslogoidRet
{
	CMD_CS_UpdateUserSyslogoidRet()
	{
		memset(this,0,sizeof(*this));
	}
	int			iRet;									// 返回值(0正确;!0错误)
	long long	lUserID;								// 用户ID
	long long	lSyslogoid;								// 头像
};

// 用户注册状态
struct CMD_CS_UserRegisterRet
{
	CMD_CS_UserRegisterRet()
	{
		memset(this,0,sizeof(*this));
	}
	int				iRet;								// 返回值
};

// 获取房间列表
struct CMD_CS_RequestRoomList
{
	CMD_CS_RequestRoomList()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iGameID;							// 游戏ID(比如：1捕鱼; 2斗地主; 3麻将...)
};

// 房间列表
struct CMD_SC_RoomList
{
	CMD_SC_RoomList()
	{
		memset(this, 0, sizeof(*this));
	}
	long long		lParentId;							// 父节点（关卡 1:初级场;2:中级场....）..
	int				iGameID;							// 游戏ID(比如：1捕鱼; 2斗地主; 3麻将...)
	long long		lGameType;							// 游戏类型(1=积分房间、2=金币游戏、3=比赛游戏)..
	int				iRoomId;							// 房间ID
	long long		lRoomTeltComIp;						// 房间的中国电信IP
	long long 		lRoomUnicomIp;						// 房间的中国联通IP
	long long		lRoomMobileIp;						// 房间的中国移动IP
	int				iRoomPort;							// 房间端口
	char			szRoomName[ROOM_NAME_LEN];			// 房间名字
	bool			bAutoSit;							// 是否自动入座(0:不自动，需要手动点坐桌和椅子进入; 1:自动入座，不需要点击椅子号)
	int				iBasePoint;							// 倍率..
	long long		lDoorsill;							// 进入门槛(自身金币少于门槛不能进入房间)..
	int				iTables;							// 房内桌子的数量
	int				iSeatNum;							// 每桌人数，即每桌的座位数量
	int				iEnterTradeGold;					// 报名费(金币)
	int				iEnterTradePoint;					// 报名费(积分)
	int				iRewardGold1;						// 第一名奖励
	int				iRewardGold2;						// 第二名奖励
};

// 登录服内部配置
struct CMD_INNER_LoginConfig
{
	CMD_INNER_LoginConfig()
	{
		memset(this, 0, sizeof(*this));
	}
	int				iListenPort;						// 监听端口
	int				iDbPort;							// 数据库端口
	char			szDbIp[IP_ADDRES_LEN];				// 数据库地址
	char			szDbUserName[DB_USER_NAME_LEN];		// 数据库用户名
	char			szDbUserPwd[DB_PASS_LEN];			// 数据库密码
	char			szDbName[DB_NAME_LEN];				// 数据库名字
};
// add end

struct TEST_USER_INFO	// 测试用
{
	TEST_USER_INFO(){	memset(this, 0, sizeof(*this));	}

	//// 获得真实的长度
	//int GetLen() 
	//{
	//	size_t iNameLen = 0;
	//	//StringCchLength(szName, _countof(szName), &iNameLen);
	//	StringCchLength(szName, sizeof(szName), &iNameLen);
	//	iNameLen++;  // 加入结束符 0 的长度
	//	int iSize = (int)sizeof(*this) - (int)sizeof(szName) + (int)iNameLen*(int)sizeof(TCHAR);
	//	return iSize;
	//}

	int		iAge; 
	wchar_t	szName[128];
};

struct TEST_DB_QUERY
{
	TEST_DB_QUERY(){	memset(this, 0, sizeof(*this));	}

	int		iQueryType;		// 查询的类型
	char	szContent[64];	// 内容
};

#endif

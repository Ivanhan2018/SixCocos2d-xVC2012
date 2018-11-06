#ifndef CMD_PLAZA_H
#define CMD_PLAZA_H

#include "PublicMacro.h"

#ifdef WIN32
#pragma pack(push)
#endif
#pragma pack(8)

/*
**description:
******CS  -> 客户端发往服务器的
******SC  -> 服务器发往客户端的
******CSG -> 客户端/服务器互用
******MAIN -> 主消息
******SUB -> 子消息
*/

#define MAIN_MSG_TASK					5000					// 任务
#define SUB_CSG_TASK_LIST				5001					// 获取任务列表
#define SUB_CSG_TASK_LIST_COMPLETE		5002					// 获取任务列表完成
#define SUB_CSG_RECEIVE_REWARD			5003					// 领取任务奖励
#define SUB_SC_GET_NEXT_TASK			5004					// 获取下一个任务

#define MAIN_MSG_ACTIVITY				5100					// 活动
#define SUB_CSG_ACTIVITY_LIST			5101					// 获取活动列表
#define SUB_CSG_ACTIVITY_LIST_COMPLETE	5102					// 获取活动列表完成

#define MAIN_MSG_PLAZA_RANKING			5200					// 排行
#define SUB_CSG_RANKING					5201					// 排行榜
#define SUB_CSG_RANKING_COMPLETE		5103					// 获取排行榜完成
#define SUB_SC_MY_RANKING				5202					// 我自己的排名

#define MAIN_MSG_SHOP					5300					// 商城
#define SUB_CSG_POINTCARD				5301					// 点卡充值

#define MAIN_MSG_HALL					5400					// 大厅
#define SUB_CSG_INIT_HALL				5401					// 获取大厅数据

#define MAIN_MSG_BANKER					5500					// 银行管理
#define SUB_CSG_BANKER_INFO				5501					// 获取银行信息
#define SUB_CS_SET_BANKER_PWD			5502					// 设置银行密码
#define SUB_SC_SET_BANKER_RET			5503					// 设置密码返回
#define SUB_CS_BANKER_DRAWINGS			5504					// 银行取款
#define SUB_SC_BANKER_DRAWINGS_RET		5505					// 取款返回
#define SUB_CS_BANKER_DEPOSIT			5506					// 银行存款
#define SUB_SC_BANKER_DEPOSIT_RET		5507					// 存款返回


// =================================错误序列号
// 更换密码
#define IDI_ERROR_BANKER_OLD_PWD		1000					// 旧密码错误
// 银行取款
#define IDI_ERROR_BANKER_PWD			1001					// 银行密码错误
#define IDI_BANKER_GLOD_DEFICIENCY		1002					// 银行金币不够
// 银行存款
#define IDI_USER_NOT_EXIST				1003					// 用户不存在
#define IDI_GLOD_DEFICIENCY				1004					// 自身金币不够


// 计时器ID
const int TIMER_ID_UPDATE = 100;								// 更新计时器
// 计时器时间
const int TIMER_TIME = 60*1000*60*24;							// 24小时

// 大厅配置
struct CMD_PlazaServerList
{
	CMD_PlazaServerList()
	{
		memset(this, 0, sizeof(*this));
	}
	int			iPort;					// 端口
	char		szIp[IP_ADDRES_LEN];	// IP

};
// 登录服内部配置
struct CMD_PlazaConfig
{
	CMD_PlazaConfig()
	{
		memset(this, 0, sizeof(*this));
	}
	char			szLocalIp[IP_ADDRES_LEN];					// 本机IP
	int				iPort;										// 监听端口
	int				iDbPort;									// 数据库端口
	char			szDbIp[IP_ADDRES_LEN];						// 数据库地址
	char			szDbUserName[DB_USER_NAME_LEN];				// 数据库用户名
	char			szDbUserPwd[DB_PASS_LEN];					// 数据库密码
	char			szDbName[DB_NAME_LEN];						// 数据库名字
	char			szCenterIp[IP_ADDRES_LEN];					// 中心服务器Ip
	int				iCenterPort;								// 中心服务器端口
};

// 任务列表
struct  CMD_SC_TaskList
{
	CMD_SC_TaskList()
	{
		memset(this, 0, sizeof(*this));
	}
	int			nIsEveryday;								// 是否每天任务
	int			nID;												// 任务ID
	int			nTypeID;									// 类型ID
	int			nGameID;									// 任务所属游戏ID（0共用任务，1<专属游戏任务）
	int			nReward;									// 任务奖励
	int			nState;										// 任务状态（0可以接受，1进行中，2任务完成，3奖励已领取）
	int			nCurSchedule;							// 当前进度
	int			nTotalSchedule;						// 总进度
	int			nPriority;									// 优先级
	char		szTaskName[TASK_NAME_LEN];		// 任务名字
	char		szTaskDescription[DESCRIPTION_LEN];	// 任务描述
};
struct CMD_CS_TaskList
{
	CMD_CS_TaskList()
	{
		memset(this, 0, sizeof(*this));
	}
	int					nGame;							// 游戏ID
	long long		lUserID;							// 用户ID
};
// 领取任务奖励
struct CMD_CSG_TaskAward
{
	CMD_CSG_TaskAward()
	{
		memset(this, 0, sizeof(*this));
	}
	int					nRet;							// 领取奖励（0：成功）
	int					nTaskID;						// 任务ID
	int					nReward;					// 任务奖励
	long long		lUserID;						// 用户ID
};
// 获取下一个任务
struct CMD_SC_GET_NEXT_TASK
{
	CMD_SC_GET_NEXT_TASK()
	{
		memset(this, 0, sizeof(*this));
	}

	int					nLastTaskID;				// 上一个任务ID
	CMD_SC_TaskList NextTask;
};


// 领取奖励
struct CMD_SC_Award
{
	CMD_SC_Award()
	{
		memset(this, 0, sizeof(*this));
	}

	int					nAwardID;					// 奖励ID
	int					nReward;					// 任务奖励
	int					nCount;						// 数目
	char				szFileName[FILE_NAME_LEN];		// 奖励类型对应的文件名
	char				szDescription[DESCRIPTION_LEN];		// 说明
};
struct CMD_CS_Award
{
	CMD_CS_Award()
	{
		memset(this, 0, sizeof(*this));
	}

	int					nTaskID;						// 任务ID
	int					nRet;							// 领取奖励（0：成功）
	int					nReward;					// 任务奖励
	long long		lUserID;						// 用户ID
};

// 活动列表
struct CMD_SC_ActivityList
{
	CMD_SC_ActivityList()
	{
		memset(this, 0, sizeof(*this));
	}
	int			nID;															// 活动ID
	char			szStartTime[TIME_LEN];					// 开始时间
	char			szEndTime[TIME_LEN];						// 结束时间
	char			szName[ACTIVITY_NAME_LEN];							// 活动名字
	char			szTitle[ACTIVITY_TITLE_LEN];							// 活动标题
	char			szDescription[DESCRIPTION_LEN];		// 活动描述
};

// 排行榜
struct CMD_SC_RankingList
{
	CMD_SC_RankingList()
	{
		memset(this, 0, sizeof(*this));
	}
	int				nRank;																		// 排名
	long long	nValue;																		// 排行值（金币或积分）
	long long	lSyslogoid;																// 头像ID
	char				szNickName[USER_NAME_LEN];										// 昵称
};

struct CMD_CSG_Ranking
{
	CMD_CSG_Ranking()
	{
		memset(this, 0, sizeof(*this));
	}
	int					nMyRank;																// 自己的排名
	long long		lUserID;																	// 用户ID
};

// 商店
struct CMD_SC_Shop
{
	CMD_SC_Shop()
	{
		memset(this, 0, sizeof(*this));
	}
	int			nID;																				// 商品ID
	int			nGold;																		// 筹码
	int			nRenminbi;																// 人民币
};
struct CMD_PointCard_AddMoney
{
	CMD_PointCard_AddMoney()
	{
		memset(this, 0, sizeof(*this));
	}
	static const int CARD_LEN = 10;
	static const int PW_LEN = 7;

	long long		lUserID;																// 用户ID
	char					szCardNumber[CARD_LEN];							// 卡号
	char					szPassword[PW_LEN];										// 卡密
};

struct CMD_InitHall
{
	CMD_InitHall(){	memset(this, 0, sizeof(*this)); }

	long long		llUserID;
	int					iGameID;
	int					iCurCompleteTaskCount;							// 当前完成的任务数
};


// 获取银行信息
struct CMD_GetBankerInfo
{
	CMD_GetBankerInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// 用户ID
};

// 返回银行信息
struct CMD_BankerInfo
{
	CMD_BankerInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// 用户ID
	long long			lGold;								// 自身金币
	long long			lBankerGold;						// 银行金币
};

// 修改银行密码
struct CMD_SetBankerPwd
{
	CMD_SetBankerPwd()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// 用户ID
	char				szOldPwd[USER_PASSWORD_LEN];		// 旧密码
	char				szNewPwd[USER_PASSWORD_LEN];		// 新密码
};

// 修改银行密码返回
struct CMD_SetBankerPwdRet
{
	CMD_SetBankerPwdRet()
	{
		memset(this, 0, sizeof(*this));
	}
	int					iRet;								// 修改返回
	long long			lUserId;							// 用户ID
};

// 银行取款
struct CMD_BankerDrawings
{
	CMD_BankerDrawings()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// 用户ID
	char				szBankerPwd[USER_PASSWORD_LEN];		// 银行密码
	long long			lDrawingsGold;						// 取款金额
};

// 取款返回
struct CMD_BankerDrawingsRet
{
	CMD_BankerDrawingsRet()
	{
		memset(this, 0, sizeof(*this));
	}
	int					iRet;								// 取款返回状态
	long long			lUserId;							// 用户ID
	long long			lGold;								// 自身金币
	long long			lBankerGold;						// 银行金币
};

// 银行存款
struct CMD_BankerDeposit
{
	CMD_BankerDeposit()
	{
		memset(this, 0, sizeof(*this));
	}
	long long			lUserId;							// 用户ID
	long long			lDepositGold;						// 存款金额
};

// 存款返回
struct CMD_BankerDepositRet
{
	CMD_BankerDepositRet()
	{
		memset(this, 0, sizeof(*this));
	}
	int					iRet;								// 存款返回状态
	long long			lUserId;							// 用户ID
	long long			lGold;								// 自身金币
	long long			lBankerGold;						// 银行金币
};


#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif
#endif
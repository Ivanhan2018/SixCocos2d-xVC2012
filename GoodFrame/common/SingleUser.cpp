
#include "PublicHead.h"
#include "SingleUser.h"

#include <stdio.h>

CSingleUser::CSingleUser(void)
{
	memset(&m_userInfo,0,sizeof(m_userInfo));
	m_userInfo.lChannelNo = INVALID_CHANNEL_NO;
	m_userInfo.lUserId = INVALID_USER_ID;
	m_userInfo.iTableNo = INVAL_TABLE_NO;
	m_userInfo.iSeatNo = INVAL_SEAT_NO;
	m_userInfo.stUserState = US_OFFLINE;	// 用户状态
	m_iStepAntiAddiction = 0;
	m_pGameTaskPool = NULL;

	m_pGameTaskList = NULL;
	m_listBattleRecord.clear();
}


CSingleUser::~CSingleUser(void)
{
	exit_destroy();
}

// 改变用户的值，用途：测试锁
void CSingleUser::change_user_test(int iFireNo, int iTableNo, int iSeatNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);

	printf("Start 火号 %d, 开火线程 %d 桌号%d , 座号%d \n", 
		iFireNo, GetCurrentThreadId(), iTableNo, iSeatNo);

	printf("  放心改变 CSingleUser 实例的值吧，有锁的，火号 %d, 开火线程 %d 桌号%d , 座号%d \n", 
		iFireNo, GetCurrentThreadId(), iTableNo, iSeatNo);

	printf("End 火号 %d, 开火线程 %d 桌号%d , 座号%d \n\n", 
		iFireNo, GetCurrentThreadId(), iTableNo, iSeatNo);
}

void CSingleUser::set_game_task_pool(CLightweightPool<GameTaskList>* pGameTaskPool)
{
	if (NULL==m_pGameTaskPool)
	{
		m_pGameTaskPool = pGameTaskPool;
	}
}


// 初始化
void CSingleUser::init()
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	memset(&m_userInfo, 0, sizeof(m_userInfo));
	m_userInfo.lChannelNo = INVALID_CHANNEL_NO;
	m_userInfo.lUserId = INVALID_USER_ID;
	m_userInfo.iTableNo = INVAL_TABLE_NO;
	m_userInfo.iSeatNo = INVAL_SEAT_NO;
	m_userInfo.stUserState = US_OFFLINE;	// 用户状态
	m_lHeartBeatTime =(long long(time(NULL)));
	m_iStepAntiAddiction = 0;

	m_pGameTaskList = NULL;
	m_pGameTaskPool->retrieve(&m_pGameTaskList);
	assert(m_pGameTaskList);
	m_listBattleRecord.clear();
}

// 归档
void CSingleUser::exit_destroy()
{
	memset(&m_userInfo, 0, sizeof(m_userInfo));
	assert(m_pGameTaskList);

	m_pGameTaskPool->recycle(m_pGameTaskList);
	m_pGameTaskList = NULL;
	m_listBattleRecord.clear();
}

GameTaskList* CSingleUser::GetGameTaskListPtr()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_pGameTaskList;
}

// 设置用户信息
void CSingleUser::set_user_info(LONGLONG lNo, const USER_INFO* pUserInfo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	assert(pUserInfo);
	if(!pUserInfo)
	{
		return;
	}

	memcpy(&m_userInfo, pUserInfo, sizeof(m_userInfo));
	m_userInfo.lChannelNo = lNo;
}

// 获得用户信息
USER_INFO& CSingleUser::get_user_info()
{
	//CThreadGuardRead guard(&m_lockSingleUser);

	return m_userInfo;
}

USER_INFO_SIM CSingleUser::get_user_info_sim()
{
	//CThreadGuardRead guard(&m_lockSingleUser);

	USER_INFO_SIM userInfoSim;

	_snprintf(userInfoSim.szName, sizeof(userInfoSim.szName), m_userInfo.szName);
	_snprintf(userInfoSim.szPassword, sizeof(userInfoSim.szPassword), m_userInfo.szPassword);
	_snprintf(userInfoSim.szNickname, sizeof(userInfoSim.szNickname), m_userInfo.szNickname);

	userInfoSim.lUserId			= m_userInfo.lUserId;			// 用户ID
	userInfoSim.stUserState		= m_userInfo.stUserState;		// 用户状态
	userInfoSim.iTableNo		= m_userInfo.iTableNo;			// 桌号
	userInfoSim.iSeatNo			= m_userInfo.iSeatNo;			// 座位号
	userInfoSim.lGoldLogin		= m_userInfo.lGoldLogin;		// 进房间进的金币值
	userInfoSim.iSex			= m_userInfo.iSex;				// 性别：0男性、1女性
	userInfoSim.lIdentity		= m_userInfo.lIdentity;			// 玩家的身份：一级管理员、二级管理员、黄钻会员、绿钻会员、普通玩家等
	userInfoSim.lMasterPower	= m_userInfo.lMasterPower;		// 管理权限（是掩码）：允许发警告消息、允许发游戏信息、禁止其他人游戏、踢玩家下线、允许加减分数、禁止进入银行 等
	userInfoSim.lGamePower		= m_userInfo.lGamePower;		// 玩家游戏权限（是掩码）：允许游戏聊天、允许发短信息、许任何旁观 等
	userInfoSim.lSysLogoID		= m_userInfo.lSysLogoID;		// 系统提供的头像系列。
	userInfoSim.lExperience		= m_userInfo.lExperience;		// 经验值
	userInfoSim.lPointLogin		= m_userInfo.lPointLogin;		// 积分

	return userInfoSim;
}

// 获取用户ID
LONGLONG CSingleUser::get_user_id()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lUserId;		
}	

// 设置用户ID
void CSingleUser::set_user_id(LONGLONG lVal)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lUserId = lVal;		
}	

// 设置用户状态
void CSingleUser::set_user_state(USER_STATE userState)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.stUserState = userState;	
}

// 获取用户状态
USER_STATE CSingleUser::get_user_state()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.stUserState;	
}

// 设置通道号
void CSingleUser::set_channel(LONGLONG lNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lChannelNo = lNo;
}

// 获取通道号
LONGLONG CSingleUser::get_channel()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lChannelNo;
}

// 设置桌号
void CSingleUser::set_table_no(int iNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.iTableNo = iNo;		
}

// 获取桌号
int	CSingleUser::get_table_no()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.iTableNo;		
}

// 设置座位号
void CSingleUser::set_seat_no(int iNo)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.iSeatNo = iNo;		
}	


// 获取座位号
int	CSingleUser::get_seat_no()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.iSeatNo;		
}	

// 设置登录时的金币
void CSingleUser::set_gold_login(LONGLONG lVal)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lGoldLogin = lVal;		
}	

// 获取登录时的金币
LONGLONG CSingleUser::get_gold_login()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lGoldLogin;		
}	
// 修改金币 // add by cxf
void CSingleUser::change_gold_login(long long lVa)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lGoldLogin += lVa;		
}	

 // 获取登录时的积分
 LONGLONG CSingleUser::get_point_login()
 {
	 //CThreadGuardRead guard(&m_lockSingleUser);
	 return m_userInfo.lPointLogin;
 }

 // 设置登录时的积分
 void CSingleUser::set_point_login(LONGLONG lVal)
 {
	// CThreadGuardWrite guard(&m_lockSingleUser);
	 m_userInfo.lPointLogin = lVal;		
 }	

 // 设置登录时的积分
 void CSingleUser::change_point_login(long long lChange)
 {
	//CThreadGuardWrite guard(&m_lockSingleUser);
	  m_userInfo.lPointLogin += lChange;		
 }

 // 设置用户名
 void CSingleUser::set_name(const char* pszName)
 {
	 //CThreadGuardWrite guard(&m_lockSingleUser);

	 _snprintf(m_userInfo.szName, sizeof(m_userInfo.szName)-1, "%s", pszName);
 }	


 // 获取用户名
int CSingleUser::get_name(char* pszName, int iNameLen)
 {
	// CThreadGuardRead guard(&m_lockSingleUser);

	 if(!pszName)
		 return 10;
	 if(iNameLen<=0)
		 return 20;

	  _snprintf(pszName, iNameLen, "%s", m_userInfo.szName);

	 return 0;		
 }	

// 设置密码
void CSingleUser::set_password(const char* pszPassword)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);

	_snprintf(m_userInfo.szPassword, sizeof(m_userInfo.szPassword)-1, "%s", pszPassword);
}	

// 获取用户名
int CSingleUser::get_password(char* pszPassword, int iPasswordLen)
{
	//CThreadGuardRead guard(&m_lockSingleUser);

	if(!pszPassword)
		return 10;
	if(iPasswordLen<=0)
		return 20;

	_snprintf(pszPassword, iPasswordLen, "%s", m_userInfo.szPassword);

	return 0;		
}	

// 获取用户发送ping时间
long long CSingleUser::get_Net_Gap_Time()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_userInfo.lNetGapTime;
}

// 设置用户发送ping时间
void CSingleUser::set_Net_Gap_Time(long long llTime)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_userInfo.lNetGapTime = llTime;
}

// 获取用户心跳时间
long long CSingleUser::GetHeatBeatTime()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_lHeartBeatTime;
}

// 设置用户心跳时间
void CSingleUser::SetHeatBeatTime(long long lHeartBeatTime)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_lHeartBeatTime = lHeartBeatTime;
}

// 获取防沉迷提示步骤
int CSingleUser::GetStepAntiAddiction()
{
	//CThreadGuardRead guard(&m_lockSingleUser);
	return m_iStepAntiAddiction;
}

// 设置防沉迷提示步骤
void CSingleUser::SetStepAntiAddiction(int iStepAntiAddiction)
{
	//CThreadGuardWrite guard(&m_lockSingleUser);
	m_iStepAntiAddiction = iStepAntiAddiction;
}

// 用户是否有这身份
bool CSingleUser::GetIsIdentity(UserIdentity identityId)
{
	return identityId & m_userInfo.lIdentity;
}

// 增加战斗
void CSingleUser::AddBattleRecord(int iWinLost)
{
	if (m_listBattleRecord.size()>=10)
	{
		m_listBattleRecord.pop_front();
	}
	CMD_UserBattleRecord buf;
	buf.iResult = iWinLost;
	m_listBattleRecord.push_back(buf);
}

// 获取战斗记录输赢局数
int CSingleUser::GetBattleRecordWinLostCount(int iWinLost)
{
	int iCount=0;
	std::list<CMD_UserBattleRecord>::iterator it = m_listBattleRecord.begin();
	for(;it!=m_listBattleRecord.end();++it)
	{
		CMD_UserBattleRecord record = (CMD_UserBattleRecord)*it;
		if (iWinLost==record.iResult)
		{
			++iCount;
		}
	}
	return iCount;
}

/********************************************************************
	created:	2013/05/07
	created:	7:5:2013   16:45
	filename: 	E:\SixDivisions\GoodFRame\common\SingleUser.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	SingleUser
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef SINGLE_USER_H
#define SINGLE_USER_H

#include "RoomInfo.h"
#include "GameTaskList.h"
//#include "ThreadGuardEx.h"
#include "LightweightPool.h"
#include <list>

struct EASY_DATA_TIME;

// 单个用户
class __declspec(dllexport) CSingleUser
{
	// 本类不允许存在友元类，变量成员必需是私有，不允许公有变量，防止外部力量不经过 m_lockSingleUser 锁而直接改变本类实例的变量。
	// 因为本类所有变量成员的改变必需经过本类函数的 m_lockSingleUser 锁 ，否则不能保证线程级安全

public:
	CSingleUser(void);
	~CSingleUser(void);

public:

	// 改变用户的值，用途：测试锁
	void change_user_test(int iFireNo, int iTableNo, int iSeatNo);

	// 初始化
	void init();
	
	// 归档
	void exit_destroy();

	// 设置用户信息
	void set_user_info(LONGLONG lNo, const USER_INFO* pUserInfo);

	// 获得用户信息
	USER_INFO &get_user_info();
	// 获得用户信息
	USER_INFO_SIM get_user_info_sim();

	// 获取用户ID
	LONGLONG get_user_id();

	// 设置用户ID
	void set_user_id(LONGLONG lVal);

	// 设置用户状态
	void set_user_state(USER_STATE userState);

	// 获取用户状态
	USER_STATE get_user_state();

	// 设置通道号
	void set_channel(LONGLONG lNo);

	// 获取通道号
	LONGLONG get_channel();

	// 设置桌号
	void set_table_no(int iNo);

		// 获取桌号
	int	get_table_no();

	// 设置座位号
	void set_seat_no(int iNo);

		// 获取座位号
	int	get_seat_no();

	// 获取登录时的金币
	LONGLONG get_gold_login();

	// 设置登录时的金币
	void set_gold_login(LONGLONG lVal);
	
	// 修改金币
	void change_gold_login(long long lVal); 

	// 获取登录时的积分
	LONGLONG get_point_login();

	// 设置登录时的积分
	void set_point_login(LONGLONG lVal);

	// 修改积分
	void change_point_login(long long lChange);
	
	// 设置用户名
	void set_name(const char* pszName);

	// 获取用户名
	int get_name(char* pszName, int iNameLen);

	// 设置密码
	void set_password(const char* pszPassword);

	// 获取用户名
	int get_password(char* pszPassword, int iPasswordLen);

	// 获取上一次客户端发送时间
	long long get_Net_Gap_Time();

	// 设置客户端发送时间
	void set_Net_Gap_Time(long long llTime);

	// 设置心跳时间
	void SetHeatBeatTime(long long lHeartBeatTime);

	// 获取心跳时间
	long long GetHeatBeatTime();

	// 获取防沉迷提示步骤
	int GetStepAntiAddiction();

	// 设置防沉迷提示步骤
	void SetStepAntiAddiction(int iStepAntiAddiction);

	// 设置游戏任务池
	void set_game_task_pool(CLightweightPool<GameTaskList>* pGameTaskPool);

	// 获取游戏任务指针
	GameTaskList* GetGameTaskListPtr();

	// 获取用户是否有这身份
	bool GetIsIdentity(UserIdentity identityId);

	// 战斗记录========================================
	// 增加战斗
	void AddBattleRecord(int iResult);

	// 获取战斗记录输赢局数
	int GetBattleRecordWinLostCount(int iResult);
	//======================================

private:
	// 变量成员必需是私有，不允许公有变量，防止外部力量不经过 m_lockSingleUser 锁而直接改变本类实例的变量。
	// 因为本类所有变量成员的改变必需经过本类函数的 m_lockSingleUser 锁 ，否则不能保证线程级安全

//	CSRWLock		m_lockSingleUser;		// 针对本实例的锁，即每个用户都有一把锁，
											// 针对问题：密集开火时会出现多个线程同时竟争一个用户实例的成员
	USER_INFO		m_userInfo;				// 用户信息

	long long		m_lHeartBeatTime;		// 心跳时间

	int				m_iStepAntiAddiction;	// 防沉迷提示步骤
	
	GameTaskList*	m_pGameTaskList;		// 任务类

	CLightweightPool<GameTaskList>* m_pGameTaskPool;

	std::list<CMD_UserBattleRecord> m_listBattleRecord;	// 用户战斗记录;
};

#endif
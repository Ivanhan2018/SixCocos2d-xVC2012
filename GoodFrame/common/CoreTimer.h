
/********************************************************************
	created:	2013/02/19
	created:	20:2:2013   14:03
	filename: 	E:\SVN_2013\GoodFrame\common\CoreTimer.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	CoreTimer
	file ext:	h
	author:		侯国江
	
	purpose:	内核定时器
				投递到任务的方式，这种写法的好处：
				1、可以用多线程来处理定时器事件，不存在一个定时 iIDEvent 耗时过长的情况下就会阻塞别的定时 iIDEvent 
				2、多个定时 iIDEvent 同时响应时几乎可以并行执行
*********************************************************************/

#ifndef CORE_TIMER_H
#define CORE_TIMER_H

#include "./ThreadGuard.h"
#include "./BasicLogic.h"

#include <list>
using std::list;

class CCoreTimer :	public CBasicLogic
//class CCoreTimer
{
public:
	friend class CCoreServer;

	struct SET_TIMER_PARAM
	{
		SET_TIMER_PARAM()	{	memset(this, 0, sizeof(*this));	}
		long long iIDEvent;	// 定时器Id
		int iElapse;		// 响应时间，以 ms 为单位			
	};

	enum{	
			SET_TIMER = 10,		// 设置定时器
			KILL_TIMER = 20,	// 杀定时器
		};

	enum{	
			PULSE_TIME=20,		// 一个脉冲的时间，以ms为单位
		};

	struct TIMER_PARAM		// 定时器参数
	{
		TIMER_PARAM()	{ memset(this, 0, sizeof(*this)); }

		long long lCount;
		long long iIDEvent;
		int		 iPulseCount;	// 脉冲的倍数，这个不是 ms 啦，会换算成 PULSE_TIME 的整数倍
	};

public:
	CCoreTimer(void);
	~CCoreTimer(void);

private:

	static unsigned __stdcall  thread_spawn_timer(void* pParam);

public:
	
	// 从外部传入消息池
	int set_msg_pool(CMemBlockPool* pMsgPool);

	// 启动
	int start_timer();

	// 停止
	int stop_timer();

	// 设置定时器/修改定时器，当框架不存在此定时器时就是设置定时器，当框架存在此定时器时就是修改此定时器的间隔
	int set_timer(long long iIDEvent, int iElapse);

	// 结束定时器
	int kill_timer(long long iIDEvent);

public:
	// 响应任务消息
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock);

private:
	
	int SetTimer(long long iIDEvent, int iElapse);

	int KillTimer(long long iIDEvent);

	// 定时器响应
	int OnTimer();

public:
	BOOL	m_bIsExit;	// 结束了

private:
//	CCoreServer*	m_pCoreServer;
	CMemBlockPool*	m_pMsgPool;

	list<TIMER_PARAM>	m_listTimer;	// 定时器序列
	CCriticalSpection	m_lock;			// 锁 m_listTimer

	HANDLE			m_hThread;
	unsigned int	m_dwThreadID;
};

#endif
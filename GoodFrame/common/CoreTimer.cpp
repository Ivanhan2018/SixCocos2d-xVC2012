#include "./CoreTimer.h"
#include "./PublicHead.h"
#include "./CoreServer.h"
#include <process.h>

#include "./Often.h"


#define HAND_RESET_TIMER 0 // 1 表示手工设置定时器，但会导致定时器不准
                           // 0 表示自动设置定时器,定时器很精准

CCoreTimer::CCoreTimer(void)
{
	m_bIsExit = FALSE;

	m_hThread = NULL;
	m_dwThreadID = 0;

	m_pMsgPool = NULL;
}

CCoreTimer::~CCoreTimer(void)
{
	m_listTimer.clear();
}

// 从外部传入消息池
int CCoreTimer::set_msg_pool(CMemBlockPool* pMsgPool)
{
	m_pMsgPool = pMsgPool;
	set_mem_block_pool(pMsgPool);

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：设置定时器/修改定时器
传入参数：
	iIDEvent	定时器ID，当框架不存在此定时器时就是设置定时器，当框架存在此定时器时就是修改此定时器的间隔
	iElapse		响应时间，以 ms 为单位，误差精度为 PULSE_TIME ms
返回值：
	成功则返回 0，失败返回错误码如下：
		10	已存在 iIDEvent 了
--------------------------------------------------------------------------*/
int CCoreTimer::SetTimer(long long iIDEvent, int iElapse)
{
	CThreadGuard guard(&m_lock);

	TIMER_PARAM tmp;
	tmp.lCount = 0;
	tmp.iIDEvent = iIDEvent;

	int iPulseCount = iElapse/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	tmp.iPulseCount = iPulseCount;

	list<TIMER_PARAM>::iterator iter = m_listTimer.begin();
	BOOL bExist = FALSE;	// 已存在

	for( ; iter!=m_listTimer.end(); iter++)
	{
		TIMER_PARAM& tmp = *iter;
		if(tmp.iIDEvent == iIDEvent)	// 找到啦，已存在 iIDEvent 了，修改定时器的间隔
		{
			bExist = TRUE;

			TIMER_PARAM* pTimer = &(*iter);
			pTimer->lCount = 0;					// 很重要
			pTimer->iPulseCount = iPulseCount;

			return 0;	// 
		}
	}

	if(!bExist)	// 不存在，可以加入此定时器
	{
		m_listTimer.push_back(tmp);
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：设置定时器/修改定时器
传入参数：
	iIDEvent	定时器ID，当框架不存在此定时器时就是设置定时器，当框架存在此定时器时就是修改此定时器的间隔
	iElapse		响应时间，以 ms 为单位，误差精度为 PULSE_TIME ms
返回值：
	成功则返回 0，失败返回错误码如下：
		10	已存在 iIDEvent 了
--------------------------------------------------------------------------*/
int CCoreTimer::set_timer(long long iIDEvent, int iElapse)
{
	if(!m_pMsgPool)
		return 10;

	SET_TIMER_PARAM tmp;
	tmp.iIDEvent = iIDEvent;
	tmp.iElapse = iElapse;

	CMemBlock* pMemBlock = NULL;
	m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, SET_TIMER, 0, (BYTE*)(&tmp), sizeof(tmp), __FUNCTION__);

	if(pMemBlock)
		put(pMemBlock);

	return 0;	// 不存在 iIDEvent
}

/* --------------------------------------------------------------------------
函数说明：结束定时器
传入参数：
	iIDEvent	定时器ID
返回值：
	成功则返回 0，失败返回错误码如下：
		10	不存在 iIDEvent
--------------------------------------------------------------------------*/
int CCoreTimer::KillTimer(long long iIDEvent)
{
	CThreadGuard guard(&m_lock);

	list<TIMER_PARAM>::iterator iter = m_listTimer.begin();
	BOOL bExist = FALSE;	// 已存在

	for( ; iter!=m_listTimer.end(); iter++)	// 找到啦
	{
		TIMER_PARAM& tmp = *iter;
		if(tmp.iIDEvent == iIDEvent)	
		{
			m_listTimer.erase(iter);
			return 0;
		}
	}

	return 10;	// 不存在 iIDEvent
}

/* --------------------------------------------------------------------------
函数说明：结束定时器
传入参数：
	iIDEvent	定时器ID
返回值：
	成功则返回 0，失败返回错误码如下：
		10	不存在 iIDEvent
--------------------------------------------------------------------------*/
int CCoreTimer::kill_timer(long long iIDEvent)
{
	if(!m_pMsgPool)
		return 10;

	CMemBlock* pMemBlock = NULL;
	m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, KILL_TIMER, 0, (BYTE*)(&iIDEvent), sizeof(iIDEvent), __FUNCTION__);

	if(pMemBlock)
		put(pMemBlock);

	return 0;	// 不存在 iIDEvent
}

// 响应任务消息
TASK_MSG_RESULT CCoreTimer::OnTask(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// 自动归池信号

	int iMainCode = 0;
	int iSubCode = 0;
	BYTE* pData = NULL;
	int iDataLen = 0;

	// 获得内核消息的真实数据
	int iRes = m_pMsgPool->get_core_msg_data(pMsgBlock, &iMainCode, &iSubCode, pData, &iDataLen);
	assert(0==iRes);
	if(0!=iRes)
		return stTaskMsgResult;

	switch(iMainCode)
	{
	case SET_TIMER:
		{
			assert(sizeof(SET_TIMER_PARAM)==iDataLen);
			if(sizeof(SET_TIMER_PARAM)==iDataLen)
			{
				SET_TIMER_PARAM* pSetTimerParam = (SET_TIMER_PARAM*)(pData);
				SetTimer(pSetTimerParam->iIDEvent, pSetTimerParam->iElapse);

				//printf("SET_TIMER pIDEvent=%I64d iElapse=%d \n", pSetTimerParam->iIDEvent, pSetTimerParam->iElapse);
			}

			break;
		}
	case KILL_TIMER:	// 杀定时器
		{
			
			assert(sizeof(long long)==iDataLen);
			if(sizeof(long long)==iDataLen)
			{
				long long* pIDEvent = (long long*)(pData);
				KillTimer(*pIDEvent);

				//printf("KILL_TIMER pIDEvent=%I64d \n", *pIDEvent);
			}

			break;
		}
	}

	return stTaskMsgResult;
}

// 定时器响应
int CCoreTimer::OnTimer()
{
	CThreadGuard guard(&m_lock);

	if(!m_pCoreServer)
		return 10;

	list<TIMER_PARAM>::iterator iter = m_listTimer.begin();
	BOOL bExist = FALSE;	// 已存在

	for( ; iter!=m_listTimer.end(); iter++)	// 找到啦
	{
		TIMER_PARAM& tmp = *iter;

		tmp.lCount++;

		if(0 == tmp.lCount % (long long)tmp.iPulseCount)	// 脉冲响应
		{
			#if 0	// 测试用
				char szTmp[64] = {0};
				sprintf(szTmp, "lCount=%I64d iPulseCount=%d ", tmp.lCount, tmp.iPulseCount);
				COften::OutputInfo(szTmp);
			#endif

			m_pCoreServer->OnTimer(tmp.iIDEvent);		// 应用层响应定时器
		}
	}

	return 0;
}

// 启动
int CCoreTimer::start_timer()
{
	int iRes = 0;

	set_thread_num(1);	// 只用一个线程，保证消息的顺序

	iRes = start();

	m_hThread = (HANDLE)_beginthreadex( NULL, 0, &thread_spawn_timer, (void*)this, 0, &m_dwThreadID );

	if(!m_hThread)
		return 10;

	return 0;
}

// 停止
int CCoreTimer::stop_timer()
{
	int iRes = 0;
	m_bIsExit = TRUE;	// 结束了

	DWORD dwResult = WaitForSingleObject(m_hThread, WAIT_EXIT_TIME);	// 等待线程彻底的结束

	iRes = stop();

	return iRes;
}

/* --------------------------------------------------------------------------
函数说明：孵化一个定时器的线程
返回值：
    成功则返回 0，失败返回错误码如下：
		10	建立定时器失败
		20	SetWaitableTimer 失败
--------------------------------------------------------------------------*/
unsigned __stdcall  CCoreTimer::thread_spawn_timer(void* pParam)
{
	CCoreTimer* pThis = (CCoreTimer*)pParam;

	HANDLE hTimer = NULL;	
	DWORD dwResult = 0;
	LARGE_INTEGER liDueTime;

	// 正值是绝对时间；当设置为负数是相对时间。
	// 指明定时器在间隔多长时间后第一次响应，以千万分之一秒为单位
	liDueTime.QuadPart = (long long)PULSE_TIME * (-1) * 10000000 /1000;		
	int iLoopCount = 10;

	#if HAND_RESET_TIMER
		hTimer = CreateWaitableTimer(NULL, TRUE, NULL);	// 这句也行
	#else
		hTimer = CreateWaitableTimer(NULL, FALSE, NULL);	// 这句也行
	#endif

	if (!hTimer)
	{
		printf("CreateWaitableTimer failed , GetLastError()=%d \n", GetLastError());
		return 10;	// 建立定时器失败
	}

	printf("CreateWaitableTimer success  \n");

	LONG  lPeriod = (LONG)PULSE_TIME;	// 循环响应的周期， 以ms为单位

	if (!SetWaitableTimer(	hTimer, 
							&liDueTime,		// 指明定时器在间隔多长时间后第一次响应，以千万分之一秒为单位。
											// 正值是绝对时间，当设置为负数是相对时间。
							lPeriod,		// 周期
							NULL, 
							NULL, 
							0))
	{
		printf("SetWaitableTimer failed , GetLastError()=%d \n", GetLastError());

		return 20;	// SetWaitableTimer 失败
	}

	while(!pThis->m_bIsExit)	// 还未结束就继续循环
	{
		DWORD dwResult = WaitForSingleObject(hTimer, INFINITE);
		switch(dwResult)
		{
		case WAIT_OBJECT_0:	// 正常响应 hTimer 
			{
				pThis->OnTimer();

				#if HAND_RESET_TIMER
					if (!SetWaitableTimer(	hTimer, 
						&liDueTime,		// 指明定时器在间隔多长时间后第一次响应，以千万分之一秒为单位。
						// 正值是绝对时间，当设置为负数是相对时间。
						lPeriod,		// 周期
						NULL, 
						NULL, 
						0))
					{
						printf("SetWaitableTimer failed , GetLastError()=%d \n", GetLastError());

						return 20;	// SetWaitableTimer 失败
					}
				#endif

				break;
			}
		case WAIT_TIMEOUT:	// 超时
			{
				break;
			}
		default:
			{
				break;
			}
		}
	}

	CloseHandle(hTimer);

	return 0;
}
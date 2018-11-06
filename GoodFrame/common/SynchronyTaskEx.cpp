
#include "PublicHead.h"
#include "SynchronyTaskEx.h"

#include <process.h>

CSynchronyTaskEx::CSynchronyTaskEx(void)
: m_hSemaphore(m_hEvent[EVENT_MESSAGE])
, m_hStop(m_hEvent[EVENT_STOP])
{
	m_bChannelBindThread = false;	// true  表示通道号绑定线程，即一个通道号的数据只能在一个线程里执行，从而保证了此通道号内先到的数据执行完毕啦，才会去执行后到的数据。
									// false 表示线程与通道号是随机对应的，即一个通道号的数据可以在多个线程里执行，无法保证此通道号内数据的先后顺序，会出见先到的数据还在执行，后到的数据已经执行完毕啦。

	InterlockedExchange(&m_lDequeState, (long)TPM_CORE_NORMAL);

	m_iMessageLen = 2*1024;

	m_pITask = NULL;

	m_iState = STATE_NO;	// 无状态

	m_hSemaphore = CreateSemaphore(NULL,0, MAX_SEMAPHORE_NUMBER, NULL);
	m_hStop = CreateEvent(NULL, TRUE, FALSE, NULL);		// 第二个参数为 TRUE ，结束只需要执行一次 SetEvent(m_hStop) 就OK了

	m_iThreadNum = 1;
	memset(m_hThreads, 0, sizeof(m_hThreads));
	memset(m_dwThreadsID, 0, sizeof(m_dwThreadsID));

	m_hThread = 0;
	m_dwThreadID = 0;

	m_pMsgPool = NULL;

	m_nInitElementCount = CMemBlockPool::DEF_INIT_COUNT;	// 池的初始元素数量
	m_nMaxElementCount = CMemBlockPool::DEF_MAX_COUNT;		// 池内元素的上限值

	m_iElementAlert = min(10*1024, MAX_SEMAPHORE_NUMBER-10);
	m_iAlertSleepTime = 20;		// 到了警戒线的值时的睡眠时间，以ms为单位

	m_bRunStop = FALSE;		// 已经执行 stop 函数了

	timeStart = 0;	
	timeEnd = 0;
	timeSpace = 0;
	m_lPutCount = 0;
}

CSynchronyTaskEx::~CSynchronyTaskEx(void)
{
	
}

// 设置投递消息的模块地址
void CSynchronyTaskEx::set_listen_module(CSynchronyTaskExListener*	pITask)
{
	m_pITask = pITask;
}

// 设置消息池
void CSynchronyTaskEx::set_mem_block_pool(CMemBlockPool* pMsgPool)
{
	m_pMsgPool = pMsgPool;
}

// 获得消息池
CMemBlockPool* CSynchronyTaskEx::get_mem_block_pool()
{
	return m_pMsgPool;
}

// 设置池内初始元素的数量
void CSynchronyTaskEx::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
	m_iElementAlert = min(nInitBlkCount-10, MAX_SEMAPHORE_NUMBER-10);
}

// 设置池内元素的上限值
void CSynchronyTaskEx::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// 设置警戒下限值，注意：本函数与 set_init_block_count 同时应用时要放在它后面
void CSynchronyTaskEx::set_element_alert(int iElementAlert)
{
	// 在 iElementAlert、池内初始元素数量-10、最大的信标数量-10、 三者之间选一个最小值
	int iTmp = min(m_pMsgPool->get_init_element_count()-10, MAX_SEMAPHORE_NUMBER-10);
	m_iElementAlert = min(iTmp, iElementAlert);;				
}
						
// 设置到达警戒下限值时的睡眠时间，以ms为单位
void CSynchronyTaskEx::set_alert_sleep_time(int iAlertSleepTime)
{
	m_iAlertSleepTime = iAlertSleepTime;	
}

int CSynchronyTaskEx::get_deque_count()
{
	return (int)m_dequeMsg.size();
}

// 添加任务消息
int CSynchronyTaskEx::put(CMemBlock*& pMemBlock, BOOL bIsFront)
{
	if(TPM_CORE_EXIT == m_lDequeState)
		return 10;	// TPM_REFUSE_PUT 或 TPM_CORE_EXIT 状态

	int iMsgBlockSize = 0;

	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif
	
	int iElementNum = static_cast<int>(m_dequeMsg.size());	
	//m_iElementAlert = 100;	// 测试用，警戒线赋一个较低的值

	#if 1
		// 此段容易产生Z型死锁吗??? 应该不会吧
		// 产生者的任务数量到达警戒线时睡一会儿
		// 测试效率时关闭些段不能让它睡
		while(iElementNum >= m_iElementAlert)	
		{
			guard.leave();	// 很重要，否则消费线程无法解锁进行消费

			Sleep(m_iAlertSleepTime);	// 睡一会儿，让消费线程去消费任务消息

			iElementNum = static_cast<int>(m_dequeMsg.size());	// 这句不能屏蔽

			#if 0	// 测试用
				long long lLockCount = m_lock.get_count();
				printf_s("生产者 lLockCount=%I64d iElementNum=%d \n", lLockCount, iElementNum);
			#endif

			if(iElementNum<m_iElementAlert)	// 低于警戒值
			{
				guard.enter();	// 是退出循环时才起作用的，理论上讲不会产生Z型死锁
				break;
			}
			else	// 高于警戒值，继续循环等待
			{
				continue;
			}


		}
	#endif

	InterlockedIncrement64(&m_lPutCount);	// 原子方式增1

	DWORD dwError = 0;
	BOOL  bFlag = FALSE;

	if(bIsFront)	
		m_dequeMsg.push_front(pMemBlock);	// 加到双向队列的头部
	else
		m_dequeMsg.push_back(pMemBlock);	// 加到双向队列的尾部

	LONG lPrevCount;
	bFlag = ReleaseSemaphore(m_hSemaphore, 1, &lPrevCount);	// 生产 1 个信标资源

	dwError = GetLastError();
	if(!bFlag)
	{
		/*  出错时的解释
		ERROR_TOO_MANY_POSTS
		298
		Too many posts were made to a semaphore.
		*/

		static int iErrCount = 1;
		printf("ReleaseSemaphore 错误次数%d ，错误码%d \n", iErrCount++, dwError);
	}

	return 0;
}

// 设置消息的长度
void CSynchronyTaskEx::set_message_len(int iMessageLen)
{
	m_iMessageLen = iMessageLen;
}

// 获得消息的长度
int CSynchronyTaskEx::get_message_len()
{
	return m_iMessageLen;
}

// 设置消费线程的数量，即推送消息线程的数量
void CSynchronyTaskEx::set_thread_num(int iNum)
{
	if(iNum<=0)
		m_iThreadNum = 1;
	else if(iNum<=MAX_THREAD_NUM)
		m_iThreadNum = iNum;
	else
		m_iThreadNum = MAX_THREAD_NUM;

}

// 获得推送消息线程的数量
int CSynchronyTaskEx::get_thread_num()
{
	return m_iThreadNum;
}

// 获得队列的状态，参考 TPM_CORE_NORMAL
long CSynchronyTaskEx::get_deque_state()
{
	return m_lDequeState;
}

// 设置队列的状态，参考 TPM_CORE_NORMAL
void CSynchronyTaskEx::set_deque_state(long lDequeState)
{
	InterlockedExchange(&m_lDequeState, (long)lDequeState);
}

// 开始
int CSynchronyTaskEx::start()
{
	if( 0 == m_pITask )
	{
		return 10;	// m_pITask 未付值，用 set_listen_module 函数付值
	}

	if( 0 == m_iMessageLen )
	{
		return 20;	// m_iMessageLen 长度不应该是 0，用 set_message_len 函数设置消息的长度
	}

	if(!m_pMsgPool)
		return 30;	// m_pMsgPool 为空

	for(int i=0; i<m_iThreadNum; i++)
	{
		TASK_THREAD_PARAM* pTaskThreadParam = new TASK_THREAD_PARAM;
		pTaskThreadParam->pThis = this;
		pTaskThreadParam->iThreadNo = i;

		// 消费者线程，消费任务消息
		//m_hThreads[i] = (HANDLE)_beginthreadex( NULL, 0, &theads_consume_task, (void*)this, CREATE_SUSPENDED , &m_dwThreadsID[i] );
		m_hThreads[i] = (HANDLE)_beginthreadex( NULL, 0, &theads_consume_task, (void*)pTaskThreadParam, CREATE_SUSPENDED , &m_dwThreadsID[i] );

		if(!m_hThreads[i])
			return 40;	// 起动线程池失败

		// 设置线程优先级  THREAD_PRIORITY_NORMAL	THREAD_PRIORITY_BELOW_NORMAL , THREAD_PRIORITY_LOWEST 
		// 任务线程要比主线程低一个优先级，万一任务线程死循环了主线程还能分到时间片进行死循环检测
		SetThreadPriority(m_hThreads[i], THREAD_PRIORITY_BELOW_NORMAL);	
	}

	for(int i=0; i<m_iThreadNum; i++)
	{
		ResumeThread(m_hThreads[i]);
	}

	timeStart = GetTickCount64();

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：停止	
返回值：
	成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CSynchronyTaskEx::stop()
{
	if(m_bRunStop)
		return 10;	// 已经执行过 stop 了

	m_bRunStop = true;

	InterlockedExchange(&m_lDequeState, (long)TPM_CORE_EXIT);

	SetEvent(m_hStop);

	BOOL bIsWaitTime = FALSE;
	DWORD dwResult = WaitForMultipleObjects(m_iThreadNum, m_hThreads, TRUE, WAIT_EXIT_TIME);	// 等待线程彻底的结束

	if(WAIT_TIMEOUT==dwResult)
	{
		printf("等待信标超时 \n");
	}

	timeEnd = GetTickCount64();

	if(bIsWaitTime)
		timeSpace = timeEnd - timeStart - TERMINATE_CLOSE_THREAD_TIME;
	else
		timeSpace = timeEnd - timeStart;

	// 清空m_dequeMsg 任务消息双向队列
	clear_deque_msg();

	for(int i=0; i<EVENT_NUMBER; i++)
	{
		if(m_hEvent[i])
			CloseHandle(m_hEvent[i]);
	}
	
	return 0;
}

// 消费者线程，消费任务消息
unsigned __stdcall  CSynchronyTaskEx::theads_consume_task(void* pParam) 
{
	//CSynchronyTaskEx* pThis = static_cast<CSynchronyTaskEx*>(pParam);

	TASK_THREAD_PARAM* pTaskThreadParam = (TASK_THREAD_PARAM*)pParam;
	CSynchronyTaskEx* pThis = pTaskThreadParam->pThis;
	int iThreadNo = pTaskThreadParam->iThreadNo;	// 线程编号

	DWORD dwThreadId = GetCurrentThreadId();	// 测试用

	pThis->handle_task_msg_semaphore(pTaskThreadParam);

	if(pTaskThreadParam)
	{
		delete pTaskThreadParam;
	}

	return(0);
}

// 清空m_dequeMsg 任务消息双向队列
int CSynchronyTaskEx::clear_deque_msg()
{
	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	CMemBlock* pElement = NULL;
	BYTE* pMessage = NULL;

	// 将消息队列彻底清空、并归池
	while(m_dequeMsg.size() > 0)
	{
		pElement = m_dequeMsg.front();	// 获得队列的首值
		m_dequeMsg.pop_front();			// 出列

		#if 0	// 不需要归池了，关闭的速度快，但坏处是出池数与归池数不等
			if(pElement)
				delete pElement;
		#else	// 要归池，关闭的速度慢，好处是出池数与归池数相等
			pMessage = pElement->base();
			m_pMsgPool->recycle(pElement);	// 归池
		#endif
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：使用 Semaphore 处理多线程消息
传入参数：
	iThreadNo	线程编号
传出参数：
返回值：
    成功则返回 0，失败返回错误码如下：
-------------------------------------------------------------------------- */
int CSynchronyTaskEx::handle_task_msg_semaphore(TASK_THREAD_PARAM* pParam)
{
	TASK_THREAD_PARAM* pTaskThreadParam = (TASK_THREAD_PARAM*)pParam;
	CSynchronyTaskEx* pThis = pTaskThreadParam->pThis;
	int iThreadNo = pTaskThreadParam->iThreadNo;	// 线程编号

	while(true)
	{
		deque <int>::size_type iSize = m_dequeMsg.size();

		DWORD dwResult = WaitForMultipleObjects(EVENT_NUMBER, m_hEvent, FALSE, INFINITE);	// 等待线程彻底的结束

		switch(dwResult)
		{
		case WAIT_OBJECT_0:	// 工作消息
			{
				CMemBlock* pElement = NULL;

				#if USE_SRWLock
					CThreadGuardWrite guard(&m_lock);
				#else
					CThreadGuard guard(&m_lock);
				#endif

				iSize = m_dequeMsg.size();

				#if 0
					long long lLockCount = m_lock.get_count();
					int iElementNum = static_cast<int>(m_dequeMsg.size());	
					printf_s("消费者1 lLockCount=%I64d iElementNum=%d \n", lLockCount, iElementNum);
				#endif

				if(TPM_CORE_EXIT == m_lDequeState)	// 手工强制结束，停止接收（put）消息，停止执行 deque 中的消息 
				{
					return 0;	// 直接退出线程
				}

				if( m_dequeMsg.size() > 0 )
				{
					pElement = m_dequeMsg.front();	// 获得队列的首值
					m_dequeMsg.pop_front();			// 出列
				}
				else
				{
					continue;
				}
				
				guard.leave();	// 守护离开

				#if 0
					lLockCount = m_lock.get_count();
					iElementNum = static_cast<int>(m_dequeMsg.size());	
					printf_s("消费者2 lLockCount=%I64d iElementNum=%d \n", lLockCount, iElementNum);
				#endif

				#if 0
					DWORD dwStartTime = GetTickCount64();

				#endif

				if(pElement)
				{
					#if 0	// 测试用
						static long long lPredationCount = 0;	// 捕食成功次数
						printf("线程号%d，捕食成功次数 %I64d \n", iThreadNo, lPredationCount++);
					#endif

					// 让子类响应
					// 如果子类陷入死循环，则不会打印出“时间超长”
					m_pITask->OnConsumeTask(pElement);
				}

				#if 0
					DWORD dwEndTime = GetTickCount64();
					DWORD dwInterverTime = dwEndTime - dwStartTime;
					if(dwInterverTime > 2000)
					{
						printf_s("m_pITask->OnConsumeTask(pElement); 时间超长 dwInterverTime=%d ms \n", dwInterverTime);
					}
				#endif

				break;
			}
		case WAIT_OBJECT_0+1:	// 结束消息
			{
				int iTmp = 0;
				return 0;
			}
		}
	}

	return 0;
}

// 使用 Event 处理多线程消息
int CSynchronyTaskEx::handle_task_msg_Event()
{
	return 0;
}

#include "PublicHead.h"
#include "SynchronyTask.h"

#include <process.h>

CSynchronyTask::CSynchronyTask(void)
: m_hSemaphore(m_hEvent[EVENT_MESSAGE])
, m_hStop(m_hEvent[EVENT_STOP])
{
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

	m_iElementAlert = m_nMaxElementCount/2;
	m_iAlertSleepTime = 20;		// 到了警戒线的值时的睡眠时间，以ms为单位

	m_bRunStop = FALSE;		// 已经执行 stop 函数了

	timeStart = 0;	
	timeEnd = 0;
	timeSpace = 0;
	lPutCount = 0;
}

CSynchronyTask::~CSynchronyTask(void)
{
	
}

// 设置投递消息的模块地址
void CSynchronyTask::set_listen_module(CSynchronyTaskListener*	pITask)
{
	m_pITask = pITask;
}

// 设置池内初始元素的数量
void CSynchronyTask::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
	m_iElementAlert = m_nMaxElementCount/2;

}

// 设置池内元素的上限值
void CSynchronyTask::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// 设置警戒线的值，注意：本函数与 set_init_block_count 同时应用时要放在它后面
void CSynchronyTask::set_element_alert(int iElementAlert)
{
	m_iElementAlert = iElementAlert;					
}
						
// 设置到达警戒线的值时的睡眠时间，以ms为单位
void CSynchronyTask::set_alert_sleep_time(int iAlertSleepTime)
{
	m_iAlertSleepTime = iAlertSleepTime;	
}

// 添加任务消息
int CSynchronyTask::put(int iMessageType, int iMainCode, int iAssistantCode, const BYTE* pData, int iDataLen)
{
	if(TPM_CORE_EXIT == m_lDequeState)
		return 10;	// TPM_REFUSE_PUT 或 TPM_CORE_EXIT 状态

	int iMsgBlockSize = 0;

	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif
	
	// 到达警戒线时睡一会儿，有没有这个必要???
	// 测试效率时关闭些段不能让它睡
	if(0)	
	{
		int iElementNum = static_cast<int>(m_dequeMsg.size());	
		if(iElementNum >= m_iElementAlert)
		{
			Sleep(m_iAlertSleepTime);	// 到达警戒线，有没有这个必要??? 因为 m_pMsgPool 内的无素不够时会自动扩展的。
		}
	}

	// 长度检测
	int iLen = sizeof(iMainCode) + sizeof(iAssistantCode) + sizeof(iDataLen) + iDataLen;

	if( iLen > m_iMessageLen )
	{
		return 20;	// 消息超长了，可以用 set_message_len 将长度设置大一点
	}

	CMemBlock* pElement = NULL;	// 出池
	
	BOOL bFlag = m_pMsgPool->retrieve(&pElement, __FUNCTION__);	

	if (bFlag && pElement)
	{
		iMsgBlockSize = pElement->size();

		pElement->copy((BYTE*)(&iMessageType), sizeof(iMessageType));
		pElement->copy((BYTE*)(&iMainCode), sizeof(iMainCode));
		pElement->copy((BYTE*)(&iAssistantCode), sizeof(iAssistantCode));
		pElement->copy((BYTE*)(&iDataLen), sizeof(iDataLen));
		pElement->copy((BYTE*)pData, iDataLen);

		m_dequeMsg.push_back(pElement);

		lPutCount++ ;
	}
	else
	{
		return 30;	// 内存出池失败
	}

	DWORD dwError = 0;
	
	LONG lPrevCount;
	bFlag = ReleaseSemaphore(m_hSemaphore, 1, &lPrevCount);	// 生产 1 个信标资源
	if(!bFlag)
	{
		dwError = GetLastError();
		printf("ReleaseSemaphore 错误，错误码%d \n", dwError);
	}

	return 0;
}

// 设置消息的长度
void CSynchronyTask::set_message_len(int iMessageLen)
{
	m_iMessageLen = iMessageLen;
}

// 获得消息的长度
int CSynchronyTask::get_message_len()
{
	return m_iMessageLen;
}

// 设置消费线程的数量，即推送消息线程的数量
void CSynchronyTask::set_thread_num(int iNum)
{
	if(iNum<=0)
		m_iThreadNum = 1;
	else if(iNum<=MAX_THREAD_NUM)
		m_iThreadNum = iNum;
	else
		m_iThreadNum = MAX_THREAD_NUM;

}

// 获得推送消息线程的数量
int CSynchronyTask::get_thread_num()
{
	return m_iThreadNum;
}

// 获得队列的状态，参考 TPM_CORE_NORMAL
long CSynchronyTask::get_deque_state()
{
	return m_lDequeState;
}

// 设置队列的状态，参考 TPM_CORE_NORMAL
void CSynchronyTask::set_deque_state(long lDequeState)
{
	InterlockedExchange(&m_lDequeState, (long)lDequeState);
}

// 开始
int CSynchronyTask::start()
{
	if( 0 == m_pITask )
	{
		return 10;	// m_pITask 未付值，用 set_listen_module 函数付值
	}

	if( 0 == m_iMessageLen )
	{
		return 20;	// m_iMessageLen 长度不应该是 0，用 set_message_len 函数设置消息的长度
	}

	// 建立消息池
	if(!m_pMsgPool)
	{
		m_pMsgPool = new CMemBlockPool(m_iMessageLen, CMemBlockPool::DEF_INIT_COUNT, CMemBlockPool::DEF_MAX_COUNT);
		m_pMsgPool->init();

		printf("池内的当前元素数量 %d \n", m_pMsgPool->get_current_element_count());
	}

	for(int i=0; i<m_iThreadNum; i++)
	{
		// 消费者线程，消费任务消息
		m_hThreads[i] = (HANDLE)_beginthreadex( NULL, 0, &theads_consume_task, (void*)this, 0, &m_dwThreadsID[i] );

		if(!m_hThreads[i])
		{
			return 40;	// 起动多线程失败
		}
	}

	timeStart = GetTickCount64();

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：停止	
返回值：
	成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CSynchronyTask::stop()
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

	if(timeSpace>0)
	{
		printf("工作区内的结果：\n  实际次数：%I64d，总耗时：%d ms，%d次/ms \n\n", 
			lPutCount, timeSpace, lPutCount/timeSpace);
	}
	else
	{
		printf("工作区内的结果：\n  实际次数：%I64d，总耗时：%d ms \n\n", 
			lPutCount, timeSpace);
	}

	// 清空m_dequeMsg 任务消息双向队列
	clear_deque_msg();

	printf("池内的当前元素数量 %d，出池数量 %I64d，归池数量 %I64d \n ，\n按任意键释放池内的元素......\n", 
			m_pMsgPool->get_current_element_count(),
			m_pMsgPool->get_retrieve_count(),
			m_pMsgPool->get_recycle_count());

	// 清除 m_dequeMsg
	// 消息池释放元素及销毁
	if(m_pMsgPool->uninit())
	{
		delete m_pMsgPool;
	}

	getchar();	// 观察释放后的结果

	return 0;
}

// 消费者线程，消费任务消息
unsigned __stdcall  CSynchronyTask::theads_consume_task(void* pParam) 
{
	CSynchronyTask* pThis = static_cast<CSynchronyTask*>(pParam);
	DWORD dwThreadId = GetCurrentThreadId();	// 测试用

	pThis->handle_task_msg_semaphore();

	return(0);
}

// 清空m_dequeMsg 任务消息双向队列
int CSynchronyTask::clear_deque_msg()
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

// 使用 Semaphore 处理多线程消息
int CSynchronyTask::handle_task_msg_semaphore()
{
	while(true)
	{
		DWORD dwResult = WaitForMultipleObjects(EVENT_NUMBER, m_hEvent, FALSE, INFINITE);	// 等待线程彻底的结束
		switch(dwResult)
		{
		case WAIT_OBJECT_0:	// 工作消息
			{
				CMemBlock* pElement = NULL;
				BYTE* pMessage = NULL;


				#if USE_SRWLock
					CThreadGuardWrite guard(&m_lock);
				#else
					CThreadGuard guard(&m_lock);
				#endif

				deque <int>::size_type iSize = m_dequeMsg.size();

				if(TPM_CORE_EXIT == m_lDequeState)	// 手工强制结束，停止接收（put）消息，停止执行 deque 中的消息 
				{
					return 0;	// 直接退出线程
				}

				if( m_dequeMsg.size() > 0 )
				{
					pElement = m_dequeMsg.front();	// 获得队列的首值
					m_dequeMsg.pop_front();	// 出列

					pMessage = pElement->base();
				}
				else
				{
					continue;
				}

				guard.leave();	// 守护离开

				// 处理消息，可用于多线程任务

				if(pMessage)
				{
					// 解析消息
					int	    iMessageType = 0;
					int		iMainCode = 0;
					int		iAssistantCode = 0;
					BYTE*	pData = NULL;
					int		iDataLen = 0;

					BYTE* pPos = pMessage;

					memcpy(&iMessageType, pPos, sizeof(iMessageType));
					pPos += sizeof(iMessageType);

					memcpy(&iMainCode, pPos, sizeof(iMainCode));
					pPos += sizeof(iMainCode);

					memcpy(&iAssistantCode, pPos, sizeof(iAssistantCode));
					pPos += sizeof(iAssistantCode);

					memcpy(&iDataLen, pPos, sizeof(iDataLen));
					pPos += sizeof(iDataLen);

					pData = pPos;

					if(TPM_CORE_NORMAL==iMessageType)	// 内核心的正常消息
					{
						// 让子类响应
						m_pITask->OnConsumeTask(iMessageType, iMainCode, iAssistantCode, pData, iDataLen);
					}

					m_pMsgPool->recycle(pElement);	// 归池

					if(TPM_CORE_EXIT==iMessageType)	// 内核心的退出消息
					{
						return 0;	// 直接退出线程
					}
				}

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
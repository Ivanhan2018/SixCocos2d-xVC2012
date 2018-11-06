
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

	m_iState = STATE_NO;	// ��״̬

	m_hSemaphore = CreateSemaphore(NULL,0, MAX_SEMAPHORE_NUMBER, NULL);
	m_hStop = CreateEvent(NULL, TRUE, FALSE, NULL);		// �ڶ�������Ϊ TRUE ������ֻ��Ҫִ��һ�� SetEvent(m_hStop) ��OK��

	m_iThreadNum = 1;
	memset(m_hThreads, 0, sizeof(m_hThreads));
	memset(m_dwThreadsID, 0, sizeof(m_dwThreadsID));

	m_hThread = 0;
	m_dwThreadID = 0;

	m_pMsgPool = NULL;

	m_nInitElementCount = CMemBlockPool::DEF_INIT_COUNT;	// �صĳ�ʼԪ������
	m_nMaxElementCount = CMemBlockPool::DEF_MAX_COUNT;		// ����Ԫ�ص�����ֵ

	m_iElementAlert = m_nMaxElementCount/2;
	m_iAlertSleepTime = 20;		// ���˾����ߵ�ֵʱ��˯��ʱ�䣬��msΪ��λ

	m_bRunStop = FALSE;		// �Ѿ�ִ�� stop ������

	timeStart = 0;	
	timeEnd = 0;
	timeSpace = 0;
	lPutCount = 0;
}

CSynchronyTask::~CSynchronyTask(void)
{
	
}

// ����Ͷ����Ϣ��ģ���ַ
void CSynchronyTask::set_listen_module(CSynchronyTaskListener*	pITask)
{
	m_pITask = pITask;
}

// ���ó��ڳ�ʼԪ�ص�����
void CSynchronyTask::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
	m_iElementAlert = m_nMaxElementCount/2;

}

// ���ó���Ԫ�ص�����ֵ
void CSynchronyTask::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// ���þ����ߵ�ֵ��ע�⣺�������� set_init_block_count ͬʱӦ��ʱҪ����������
void CSynchronyTask::set_element_alert(int iElementAlert)
{
	m_iElementAlert = iElementAlert;					
}
						
// ���õ��ﾯ���ߵ�ֵʱ��˯��ʱ�䣬��msΪ��λ
void CSynchronyTask::set_alert_sleep_time(int iAlertSleepTime)
{
	m_iAlertSleepTime = iAlertSleepTime;	
}

// ���������Ϣ
int CSynchronyTask::put(int iMessageType, int iMainCode, int iAssistantCode, const BYTE* pData, int iDataLen)
{
	if(TPM_CORE_EXIT == m_lDequeState)
		return 10;	// TPM_REFUSE_PUT �� TPM_CORE_EXIT ״̬

	int iMsgBlockSize = 0;

	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif
	
	// ���ﾯ����ʱ˯һ�������û�������Ҫ???
	// ����Ч��ʱ�ر�Щ�β�������˯
	if(0)	
	{
		int iElementNum = static_cast<int>(m_dequeMsg.size());	
		if(iElementNum >= m_iElementAlert)
		{
			Sleep(m_iAlertSleepTime);	// ���ﾯ���ߣ���û�������Ҫ??? ��Ϊ m_pMsgPool �ڵ����ز���ʱ���Զ���չ�ġ�
		}
	}

	// ���ȼ��
	int iLen = sizeof(iMainCode) + sizeof(iAssistantCode) + sizeof(iDataLen) + iDataLen;

	if( iLen > m_iMessageLen )
	{
		return 20;	// ��Ϣ�����ˣ������� set_message_len ���������ô�һ��
	}

	CMemBlock* pElement = NULL;	// ����
	
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
		return 30;	// �ڴ����ʧ��
	}

	DWORD dwError = 0;
	
	LONG lPrevCount;
	bFlag = ReleaseSemaphore(m_hSemaphore, 1, &lPrevCount);	// ���� 1 ���ű���Դ
	if(!bFlag)
	{
		dwError = GetLastError();
		printf("ReleaseSemaphore ���󣬴�����%d \n", dwError);
	}

	return 0;
}

// ������Ϣ�ĳ���
void CSynchronyTask::set_message_len(int iMessageLen)
{
	m_iMessageLen = iMessageLen;
}

// �����Ϣ�ĳ���
int CSynchronyTask::get_message_len()
{
	return m_iMessageLen;
}

// ���������̵߳���������������Ϣ�̵߳�����
void CSynchronyTask::set_thread_num(int iNum)
{
	if(iNum<=0)
		m_iThreadNum = 1;
	else if(iNum<=MAX_THREAD_NUM)
		m_iThreadNum = iNum;
	else
		m_iThreadNum = MAX_THREAD_NUM;

}

// ���������Ϣ�̵߳�����
int CSynchronyTask::get_thread_num()
{
	return m_iThreadNum;
}

// ��ö��е�״̬���ο� TPM_CORE_NORMAL
long CSynchronyTask::get_deque_state()
{
	return m_lDequeState;
}

// ���ö��е�״̬���ο� TPM_CORE_NORMAL
void CSynchronyTask::set_deque_state(long lDequeState)
{
	InterlockedExchange(&m_lDequeState, (long)lDequeState);
}

// ��ʼ
int CSynchronyTask::start()
{
	if( 0 == m_pITask )
	{
		return 10;	// m_pITask δ��ֵ���� set_listen_module ������ֵ
	}

	if( 0 == m_iMessageLen )
	{
		return 20;	// m_iMessageLen ���Ȳ�Ӧ���� 0���� set_message_len ����������Ϣ�ĳ���
	}

	// ������Ϣ��
	if(!m_pMsgPool)
	{
		m_pMsgPool = new CMemBlockPool(m_iMessageLen, CMemBlockPool::DEF_INIT_COUNT, CMemBlockPool::DEF_MAX_COUNT);
		m_pMsgPool->init();

		printf("���ڵĵ�ǰԪ������ %d \n", m_pMsgPool->get_current_element_count());
	}

	for(int i=0; i<m_iThreadNum; i++)
	{
		// �������̣߳�����������Ϣ
		m_hThreads[i] = (HANDLE)_beginthreadex( NULL, 0, &theads_consume_task, (void*)this, 0, &m_dwThreadsID[i] );

		if(!m_hThreads[i])
		{
			return 40;	// �𶯶��߳�ʧ��
		}
	}

	timeStart = GetTickCount64();

	return 0;
}

/* --------------------------------------------------------------------------
����˵����ֹͣ	
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CSynchronyTask::stop()
{
	if(m_bRunStop)
		return 10;	// �Ѿ�ִ�й� stop ��

	m_bRunStop = true;

	InterlockedExchange(&m_lDequeState, (long)TPM_CORE_EXIT);

	SetEvent(m_hStop);

	BOOL bIsWaitTime = FALSE;
	DWORD dwResult = WaitForMultipleObjects(m_iThreadNum, m_hThreads, TRUE, WAIT_EXIT_TIME);	// �ȴ��̳߳��׵Ľ���

	if(WAIT_TIMEOUT==dwResult)
	{
		printf("�ȴ��ű곬ʱ \n");
	}

	timeEnd = GetTickCount64();

	if(bIsWaitTime)
		timeSpace = timeEnd - timeStart - TERMINATE_CLOSE_THREAD_TIME;
	else
		timeSpace = timeEnd - timeStart;

	if(timeSpace>0)
	{
		printf("�������ڵĽ����\n  ʵ�ʴ�����%I64d���ܺ�ʱ��%d ms��%d��/ms \n\n", 
			lPutCount, timeSpace, lPutCount/timeSpace);
	}
	else
	{
		printf("�������ڵĽ����\n  ʵ�ʴ�����%I64d���ܺ�ʱ��%d ms \n\n", 
			lPutCount, timeSpace);
	}

	// ���m_dequeMsg ������Ϣ˫�����
	clear_deque_msg();

	printf("���ڵĵ�ǰԪ������ %d���������� %I64d��������� %I64d \n ��\n��������ͷų��ڵ�Ԫ��......\n", 
			m_pMsgPool->get_current_element_count(),
			m_pMsgPool->get_retrieve_count(),
			m_pMsgPool->get_recycle_count());

	// ��� m_dequeMsg
	// ��Ϣ���ͷ�Ԫ�ؼ�����
	if(m_pMsgPool->uninit())
	{
		delete m_pMsgPool;
	}

	getchar();	// �۲��ͷź�Ľ��

	return 0;
}

// �������̣߳�����������Ϣ
unsigned __stdcall  CSynchronyTask::theads_consume_task(void* pParam) 
{
	CSynchronyTask* pThis = static_cast<CSynchronyTask*>(pParam);
	DWORD dwThreadId = GetCurrentThreadId();	// ������

	pThis->handle_task_msg_semaphore();

	return(0);
}

// ���m_dequeMsg ������Ϣ˫�����
int CSynchronyTask::clear_deque_msg()
{
	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	CMemBlock* pElement = NULL;
	BYTE* pMessage = NULL;

	// ����Ϣ���г�����ա������
	while(m_dequeMsg.size() > 0)
	{
		pElement = m_dequeMsg.front();	// ��ö��е���ֵ
		m_dequeMsg.pop_front();			// ����

		#if 0	// ����Ҫ����ˣ��رյ��ٶȿ죬�������ǳ���������������
			if(pElement)
				delete pElement;
		#else	// Ҫ��أ��رյ��ٶ������ô��ǳ��������������
			pMessage = pElement->base();
			m_pMsgPool->recycle(pElement);	// ���
		#endif
	}

	return 0;
}

// ʹ�� Semaphore ������߳���Ϣ
int CSynchronyTask::handle_task_msg_semaphore()
{
	while(true)
	{
		DWORD dwResult = WaitForMultipleObjects(EVENT_NUMBER, m_hEvent, FALSE, INFINITE);	// �ȴ��̳߳��׵Ľ���
		switch(dwResult)
		{
		case WAIT_OBJECT_0:	// ������Ϣ
			{
				CMemBlock* pElement = NULL;
				BYTE* pMessage = NULL;


				#if USE_SRWLock
					CThreadGuardWrite guard(&m_lock);
				#else
					CThreadGuard guard(&m_lock);
				#endif

				deque <int>::size_type iSize = m_dequeMsg.size();

				if(TPM_CORE_EXIT == m_lDequeState)	// �ֹ�ǿ�ƽ�����ֹͣ���գ�put����Ϣ��ִֹͣ�� deque �е���Ϣ 
				{
					return 0;	// ֱ���˳��߳�
				}

				if( m_dequeMsg.size() > 0 )
				{
					pElement = m_dequeMsg.front();	// ��ö��е���ֵ
					m_dequeMsg.pop_front();	// ����

					pMessage = pElement->base();
				}
				else
				{
					continue;
				}

				guard.leave();	// �ػ��뿪

				// ������Ϣ�������ڶ��߳�����

				if(pMessage)
				{
					// ������Ϣ
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

					if(TPM_CORE_NORMAL==iMessageType)	// �ں��ĵ�������Ϣ
					{
						// ��������Ӧ
						m_pITask->OnConsumeTask(iMessageType, iMainCode, iAssistantCode, pData, iDataLen);
					}

					m_pMsgPool->recycle(pElement);	// ���

					if(TPM_CORE_EXIT==iMessageType)	// �ں��ĵ��˳���Ϣ
					{
						return 0;	// ֱ���˳��߳�
					}
				}

				break;
			}
		case WAIT_OBJECT_0+1:	// ������Ϣ
			{
				int iTmp = 0;
				return 0;
			}
		}
	}

	return 0;
}
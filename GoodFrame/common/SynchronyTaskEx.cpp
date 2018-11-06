
#include "PublicHead.h"
#include "SynchronyTaskEx.h"

#include <process.h>

CSynchronyTaskEx::CSynchronyTaskEx(void)
: m_hSemaphore(m_hEvent[EVENT_MESSAGE])
, m_hStop(m_hEvent[EVENT_STOP])
{
	m_bChannelBindThread = false;	// true  ��ʾͨ���Ű��̣߳���һ��ͨ���ŵ�����ֻ����һ���߳���ִ�У��Ӷ���֤�˴�ͨ�������ȵ�������ִ����������Ż�ȥִ�к󵽵����ݡ�
									// false ��ʾ�߳���ͨ�����������Ӧ�ģ���һ��ͨ���ŵ����ݿ����ڶ���߳���ִ�У��޷���֤��ͨ���������ݵ��Ⱥ�˳�򣬻�����ȵ������ݻ���ִ�У��󵽵������Ѿ�ִ���������

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

	m_iElementAlert = min(10*1024, MAX_SEMAPHORE_NUMBER-10);
	m_iAlertSleepTime = 20;		// ���˾����ߵ�ֵʱ��˯��ʱ�䣬��msΪ��λ

	m_bRunStop = FALSE;		// �Ѿ�ִ�� stop ������

	timeStart = 0;	
	timeEnd = 0;
	timeSpace = 0;
	m_lPutCount = 0;
}

CSynchronyTaskEx::~CSynchronyTaskEx(void)
{
	
}

// ����Ͷ����Ϣ��ģ���ַ
void CSynchronyTaskEx::set_listen_module(CSynchronyTaskExListener*	pITask)
{
	m_pITask = pITask;
}

// ������Ϣ��
void CSynchronyTaskEx::set_mem_block_pool(CMemBlockPool* pMsgPool)
{
	m_pMsgPool = pMsgPool;
}

// �����Ϣ��
CMemBlockPool* CSynchronyTaskEx::get_mem_block_pool()
{
	return m_pMsgPool;
}

// ���ó��ڳ�ʼԪ�ص�����
void CSynchronyTaskEx::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
	m_iElementAlert = min(nInitBlkCount-10, MAX_SEMAPHORE_NUMBER-10);
}

// ���ó���Ԫ�ص�����ֵ
void CSynchronyTaskEx::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// ���þ�������ֵ��ע�⣺�������� set_init_block_count ͬʱӦ��ʱҪ����������
void CSynchronyTaskEx::set_element_alert(int iElementAlert)
{
	// �� iElementAlert�����ڳ�ʼԪ������-10�������ű�����-10�� ����֮��ѡһ����Сֵ
	int iTmp = min(m_pMsgPool->get_init_element_count()-10, MAX_SEMAPHORE_NUMBER-10);
	m_iElementAlert = min(iTmp, iElementAlert);;				
}
						
// ���õ��ﾯ������ֵʱ��˯��ʱ�䣬��msΪ��λ
void CSynchronyTaskEx::set_alert_sleep_time(int iAlertSleepTime)
{
	m_iAlertSleepTime = iAlertSleepTime;	
}

int CSynchronyTaskEx::get_deque_count()
{
	return (int)m_dequeMsg.size();
}

// ���������Ϣ
int CSynchronyTaskEx::put(CMemBlock*& pMemBlock, BOOL bIsFront)
{
	if(TPM_CORE_EXIT == m_lDequeState)
		return 10;	// TPM_REFUSE_PUT �� TPM_CORE_EXIT ״̬

	int iMsgBlockSize = 0;

	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif
	
	int iElementNum = static_cast<int>(m_dequeMsg.size());	
	//m_iElementAlert = 100;	// �����ã������߸�һ���ϵ͵�ֵ

	#if 1
		// �˶����ײ���Z��������??? Ӧ�ò����
		// �����ߵ������������ﾯ����ʱ˯һ���
		// ����Ч��ʱ�ر�Щ�β�������˯
		while(iElementNum >= m_iElementAlert)	
		{
			guard.leave();	// ����Ҫ�����������߳��޷�������������

			Sleep(m_iAlertSleepTime);	// ˯һ������������߳�ȥ����������Ϣ

			iElementNum = static_cast<int>(m_dequeMsg.size());	// ��䲻������

			#if 0	// ������
				long long lLockCount = m_lock.get_count();
				printf_s("������ lLockCount=%I64d iElementNum=%d \n", lLockCount, iElementNum);
			#endif

			if(iElementNum<m_iElementAlert)	// ���ھ���ֵ
			{
				guard.enter();	// ���˳�ѭ��ʱ�������õģ������Ͻ��������Z������
				break;
			}
			else	// ���ھ���ֵ������ѭ���ȴ�
			{
				continue;
			}


		}
	#endif

	InterlockedIncrement64(&m_lPutCount);	// ԭ�ӷ�ʽ��1

	DWORD dwError = 0;
	BOOL  bFlag = FALSE;

	if(bIsFront)	
		m_dequeMsg.push_front(pMemBlock);	// �ӵ�˫����е�ͷ��
	else
		m_dequeMsg.push_back(pMemBlock);	// �ӵ�˫����е�β��

	LONG lPrevCount;
	bFlag = ReleaseSemaphore(m_hSemaphore, 1, &lPrevCount);	// ���� 1 ���ű���Դ

	dwError = GetLastError();
	if(!bFlag)
	{
		/*  ����ʱ�Ľ���
		ERROR_TOO_MANY_POSTS
		298
		Too many posts were made to a semaphore.
		*/

		static int iErrCount = 1;
		printf("ReleaseSemaphore �������%d ��������%d \n", iErrCount++, dwError);
	}

	return 0;
}

// ������Ϣ�ĳ���
void CSynchronyTaskEx::set_message_len(int iMessageLen)
{
	m_iMessageLen = iMessageLen;
}

// �����Ϣ�ĳ���
int CSynchronyTaskEx::get_message_len()
{
	return m_iMessageLen;
}

// ���������̵߳���������������Ϣ�̵߳�����
void CSynchronyTaskEx::set_thread_num(int iNum)
{
	if(iNum<=0)
		m_iThreadNum = 1;
	else if(iNum<=MAX_THREAD_NUM)
		m_iThreadNum = iNum;
	else
		m_iThreadNum = MAX_THREAD_NUM;

}

// ���������Ϣ�̵߳�����
int CSynchronyTaskEx::get_thread_num()
{
	return m_iThreadNum;
}

// ��ö��е�״̬���ο� TPM_CORE_NORMAL
long CSynchronyTaskEx::get_deque_state()
{
	return m_lDequeState;
}

// ���ö��е�״̬���ο� TPM_CORE_NORMAL
void CSynchronyTaskEx::set_deque_state(long lDequeState)
{
	InterlockedExchange(&m_lDequeState, (long)lDequeState);
}

// ��ʼ
int CSynchronyTaskEx::start()
{
	if( 0 == m_pITask )
	{
		return 10;	// m_pITask δ��ֵ���� set_listen_module ������ֵ
	}

	if( 0 == m_iMessageLen )
	{
		return 20;	// m_iMessageLen ���Ȳ�Ӧ���� 0���� set_message_len ����������Ϣ�ĳ���
	}

	if(!m_pMsgPool)
		return 30;	// m_pMsgPool Ϊ��

	for(int i=0; i<m_iThreadNum; i++)
	{
		TASK_THREAD_PARAM* pTaskThreadParam = new TASK_THREAD_PARAM;
		pTaskThreadParam->pThis = this;
		pTaskThreadParam->iThreadNo = i;

		// �������̣߳�����������Ϣ
		//m_hThreads[i] = (HANDLE)_beginthreadex( NULL, 0, &theads_consume_task, (void*)this, CREATE_SUSPENDED , &m_dwThreadsID[i] );
		m_hThreads[i] = (HANDLE)_beginthreadex( NULL, 0, &theads_consume_task, (void*)pTaskThreadParam, CREATE_SUSPENDED , &m_dwThreadsID[i] );

		if(!m_hThreads[i])
			return 40;	// ���̳߳�ʧ��

		// �����߳����ȼ�  THREAD_PRIORITY_NORMAL	THREAD_PRIORITY_BELOW_NORMAL , THREAD_PRIORITY_LOWEST 
		// �����߳�Ҫ�����̵߳�һ�����ȼ�����һ�����߳���ѭ�������̻߳��ֵܷ�ʱ��Ƭ������ѭ�����
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
����˵����ֹͣ	
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CSynchronyTaskEx::stop()
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

	// ���m_dequeMsg ������Ϣ˫�����
	clear_deque_msg();

	for(int i=0; i<EVENT_NUMBER; i++)
	{
		if(m_hEvent[i])
			CloseHandle(m_hEvent[i]);
	}
	
	return 0;
}

// �������̣߳�����������Ϣ
unsigned __stdcall  CSynchronyTaskEx::theads_consume_task(void* pParam) 
{
	//CSynchronyTaskEx* pThis = static_cast<CSynchronyTaskEx*>(pParam);

	TASK_THREAD_PARAM* pTaskThreadParam = (TASK_THREAD_PARAM*)pParam;
	CSynchronyTaskEx* pThis = pTaskThreadParam->pThis;
	int iThreadNo = pTaskThreadParam->iThreadNo;	// �̱߳��

	DWORD dwThreadId = GetCurrentThreadId();	// ������

	pThis->handle_task_msg_semaphore(pTaskThreadParam);

	if(pTaskThreadParam)
	{
		delete pTaskThreadParam;
	}

	return(0);
}

// ���m_dequeMsg ������Ϣ˫�����
int CSynchronyTaskEx::clear_deque_msg()
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

/* --------------------------------------------------------------------------
����˵����ʹ�� Semaphore ������߳���Ϣ
���������
	iThreadNo	�̱߳��
����������
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
-------------------------------------------------------------------------- */
int CSynchronyTaskEx::handle_task_msg_semaphore(TASK_THREAD_PARAM* pParam)
{
	TASK_THREAD_PARAM* pTaskThreadParam = (TASK_THREAD_PARAM*)pParam;
	CSynchronyTaskEx* pThis = pTaskThreadParam->pThis;
	int iThreadNo = pTaskThreadParam->iThreadNo;	// �̱߳��

	while(true)
	{
		deque <int>::size_type iSize = m_dequeMsg.size();

		DWORD dwResult = WaitForMultipleObjects(EVENT_NUMBER, m_hEvent, FALSE, INFINITE);	// �ȴ��̳߳��׵Ľ���

		switch(dwResult)
		{
		case WAIT_OBJECT_0:	// ������Ϣ
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
					printf_s("������1 lLockCount=%I64d iElementNum=%d \n", lLockCount, iElementNum);
				#endif

				if(TPM_CORE_EXIT == m_lDequeState)	// �ֹ�ǿ�ƽ�����ֹͣ���գ�put����Ϣ��ִֹͣ�� deque �е���Ϣ 
				{
					return 0;	// ֱ���˳��߳�
				}

				if( m_dequeMsg.size() > 0 )
				{
					pElement = m_dequeMsg.front();	// ��ö��е���ֵ
					m_dequeMsg.pop_front();			// ����
				}
				else
				{
					continue;
				}
				
				guard.leave();	// �ػ��뿪

				#if 0
					lLockCount = m_lock.get_count();
					iElementNum = static_cast<int>(m_dequeMsg.size());	
					printf_s("������2 lLockCount=%I64d iElementNum=%d \n", lLockCount, iElementNum);
				#endif

				#if 0
					DWORD dwStartTime = GetTickCount64();

				#endif

				if(pElement)
				{
					#if 0	// ������
						static long long lPredationCount = 0;	// ��ʳ�ɹ�����
						printf("�̺߳�%d����ʳ�ɹ����� %I64d \n", iThreadNo, lPredationCount++);
					#endif

					// ��������Ӧ
					// �������������ѭ�����򲻻��ӡ����ʱ�䳬����
					m_pITask->OnConsumeTask(pElement);
				}

				#if 0
					DWORD dwEndTime = GetTickCount64();
					DWORD dwInterverTime = dwEndTime - dwStartTime;
					if(dwInterverTime > 2000)
					{
						printf_s("m_pITask->OnConsumeTask(pElement); ʱ�䳬�� dwInterverTime=%d ms \n", dwInterverTime);
					}
				#endif

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

// ʹ�� Event ������߳���Ϣ
int CSynchronyTaskEx::handle_task_msg_Event()
{
	return 0;
}
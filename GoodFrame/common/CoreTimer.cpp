#include "./CoreTimer.h"
#include "./PublicHead.h"
#include "./CoreServer.h"
#include <process.h>

#include "./Often.h"


#define HAND_RESET_TIMER 0 // 1 ��ʾ�ֹ����ö�ʱ�������ᵼ�¶�ʱ����׼
                           // 0 ��ʾ�Զ����ö�ʱ��,��ʱ���ܾ�׼

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

// ���ⲿ������Ϣ��
int CCoreTimer::set_msg_pool(CMemBlockPool* pMsgPool)
{
	m_pMsgPool = pMsgPool;
	set_mem_block_pool(pMsgPool);

	return 0;
}

/* --------------------------------------------------------------------------
����˵�������ö�ʱ��/�޸Ķ�ʱ��
���������
	iIDEvent	��ʱ��ID������ܲ����ڴ˶�ʱ��ʱ�������ö�ʱ��������ܴ��ڴ˶�ʱ��ʱ�����޸Ĵ˶�ʱ���ļ��
	iElapse		��Ӧʱ�䣬�� ms Ϊ��λ������Ϊ PULSE_TIME ms
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	�Ѵ��� iIDEvent ��
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
	BOOL bExist = FALSE;	// �Ѵ���

	for( ; iter!=m_listTimer.end(); iter++)
	{
		TIMER_PARAM& tmp = *iter;
		if(tmp.iIDEvent == iIDEvent)	// �ҵ������Ѵ��� iIDEvent �ˣ��޸Ķ�ʱ���ļ��
		{
			bExist = TRUE;

			TIMER_PARAM* pTimer = &(*iter);
			pTimer->lCount = 0;					// ����Ҫ
			pTimer->iPulseCount = iPulseCount;

			return 0;	// 
		}
	}

	if(!bExist)	// �����ڣ����Լ���˶�ʱ��
	{
		m_listTimer.push_back(tmp);
	}

	return 0;
}

/* --------------------------------------------------------------------------
����˵�������ö�ʱ��/�޸Ķ�ʱ��
���������
	iIDEvent	��ʱ��ID������ܲ����ڴ˶�ʱ��ʱ�������ö�ʱ��������ܴ��ڴ˶�ʱ��ʱ�����޸Ĵ˶�ʱ���ļ��
	iElapse		��Ӧʱ�䣬�� ms Ϊ��λ������Ϊ PULSE_TIME ms
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	�Ѵ��� iIDEvent ��
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

	return 0;	// ������ iIDEvent
}

/* --------------------------------------------------------------------------
����˵����������ʱ��
���������
	iIDEvent	��ʱ��ID
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	������ iIDEvent
--------------------------------------------------------------------------*/
int CCoreTimer::KillTimer(long long iIDEvent)
{
	CThreadGuard guard(&m_lock);

	list<TIMER_PARAM>::iterator iter = m_listTimer.begin();
	BOOL bExist = FALSE;	// �Ѵ���

	for( ; iter!=m_listTimer.end(); iter++)	// �ҵ���
	{
		TIMER_PARAM& tmp = *iter;
		if(tmp.iIDEvent == iIDEvent)	
		{
			m_listTimer.erase(iter);
			return 0;
		}
	}

	return 10;	// ������ iIDEvent
}

/* --------------------------------------------------------------------------
����˵����������ʱ��
���������
	iIDEvent	��ʱ��ID
����ֵ��
	�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	������ iIDEvent
--------------------------------------------------------------------------*/
int CCoreTimer::kill_timer(long long iIDEvent)
{
	if(!m_pMsgPool)
		return 10;

	CMemBlock* pMemBlock = NULL;
	m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, KILL_TIMER, 0, (BYTE*)(&iIDEvent), sizeof(iIDEvent), __FUNCTION__);

	if(pMemBlock)
		put(pMemBlock);

	return 0;	// ������ iIDEvent
}

// ��Ӧ������Ϣ
TASK_MSG_RESULT CCoreTimer::OnTask(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// �Զ�����ź�

	int iMainCode = 0;
	int iSubCode = 0;
	BYTE* pData = NULL;
	int iDataLen = 0;

	// ����ں���Ϣ����ʵ����
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
	case KILL_TIMER:	// ɱ��ʱ��
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

// ��ʱ����Ӧ
int CCoreTimer::OnTimer()
{
	CThreadGuard guard(&m_lock);

	if(!m_pCoreServer)
		return 10;

	list<TIMER_PARAM>::iterator iter = m_listTimer.begin();
	BOOL bExist = FALSE;	// �Ѵ���

	for( ; iter!=m_listTimer.end(); iter++)	// �ҵ���
	{
		TIMER_PARAM& tmp = *iter;

		tmp.lCount++;

		if(0 == tmp.lCount % (long long)tmp.iPulseCount)	// ������Ӧ
		{
			#if 0	// ������
				char szTmp[64] = {0};
				sprintf(szTmp, "lCount=%I64d iPulseCount=%d ", tmp.lCount, tmp.iPulseCount);
				COften::OutputInfo(szTmp);
			#endif

			m_pCoreServer->OnTimer(tmp.iIDEvent);		// Ӧ�ò���Ӧ��ʱ��
		}
	}

	return 0;
}

// ����
int CCoreTimer::start_timer()
{
	int iRes = 0;

	set_thread_num(1);	// ֻ��һ���̣߳���֤��Ϣ��˳��

	iRes = start();

	m_hThread = (HANDLE)_beginthreadex( NULL, 0, &thread_spawn_timer, (void*)this, 0, &m_dwThreadID );

	if(!m_hThread)
		return 10;

	return 0;
}

// ֹͣ
int CCoreTimer::stop_timer()
{
	int iRes = 0;
	m_bIsExit = TRUE;	// ������

	DWORD dwResult = WaitForSingleObject(m_hThread, WAIT_EXIT_TIME);	// �ȴ��̳߳��׵Ľ���

	iRes = stop();

	return iRes;
}

/* --------------------------------------------------------------------------
����˵��������һ����ʱ�����߳�
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	������ʱ��ʧ��
		20	SetWaitableTimer ʧ��
--------------------------------------------------------------------------*/
unsigned __stdcall  CCoreTimer::thread_spawn_timer(void* pParam)
{
	CCoreTimer* pThis = (CCoreTimer*)pParam;

	HANDLE hTimer = NULL;	
	DWORD dwResult = 0;
	LARGE_INTEGER liDueTime;

	// ��ֵ�Ǿ���ʱ�䣻������Ϊ���������ʱ�䡣
	// ָ����ʱ���ڼ���೤ʱ����һ����Ӧ����ǧ���֮һ��Ϊ��λ
	liDueTime.QuadPart = (long long)PULSE_TIME * (-1) * 10000000 /1000;		
	int iLoopCount = 10;

	#if HAND_RESET_TIMER
		hTimer = CreateWaitableTimer(NULL, TRUE, NULL);	// ���Ҳ��
	#else
		hTimer = CreateWaitableTimer(NULL, FALSE, NULL);	// ���Ҳ��
	#endif

	if (!hTimer)
	{
		printf("CreateWaitableTimer failed , GetLastError()=%d \n", GetLastError());
		return 10;	// ������ʱ��ʧ��
	}

	printf("CreateWaitableTimer success  \n");

	LONG  lPeriod = (LONG)PULSE_TIME;	// ѭ����Ӧ�����ڣ� ��msΪ��λ

	if (!SetWaitableTimer(	hTimer, 
							&liDueTime,		// ָ����ʱ���ڼ���೤ʱ����һ����Ӧ����ǧ���֮һ��Ϊ��λ��
											// ��ֵ�Ǿ���ʱ�䣬������Ϊ���������ʱ�䡣
							lPeriod,		// ����
							NULL, 
							NULL, 
							0))
	{
		printf("SetWaitableTimer failed , GetLastError()=%d \n", GetLastError());

		return 20;	// SetWaitableTimer ʧ��
	}

	while(!pThis->m_bIsExit)	// ��δ�����ͼ���ѭ��
	{
		DWORD dwResult = WaitForSingleObject(hTimer, INFINITE);
		switch(dwResult)
		{
		case WAIT_OBJECT_0:	// ������Ӧ hTimer 
			{
				pThis->OnTimer();

				#if HAND_RESET_TIMER
					if (!SetWaitableTimer(	hTimer, 
						&liDueTime,		// ָ����ʱ���ڼ���೤ʱ����һ����Ӧ����ǧ���֮һ��Ϊ��λ��
						// ��ֵ�Ǿ���ʱ�䣬������Ϊ���������ʱ�䡣
						lPeriod,		// ����
						NULL, 
						NULL, 
						0))
					{
						printf("SetWaitableTimer failed , GetLastError()=%d \n", GetLastError());

						return 20;	// SetWaitableTimer ʧ��
					}
				#endif

				break;
			}
		case WAIT_TIMEOUT:	// ��ʱ
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
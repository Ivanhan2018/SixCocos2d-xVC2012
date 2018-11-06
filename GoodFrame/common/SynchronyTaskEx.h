/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   22:56
	filename: 	c:\GoodFrame\MemPoolTest\MemPoolTest\SynchronyTaskEx.h
	file path:	c:\GoodFrame\MemPoolTest\MemPoolTest
	file base:	SynchronyTaskEx
	file ext:	h
	author:		hgj
	
	purpose:	ͬ��������չ����� CMemBlock*& 
*********************************************************************/

#ifndef SYNCHRONY_TASK_EX_H
#define SYNCHRONY_TASK_EX_H


#include "./CoreHead.h"
#include "./MemBlockPool.h"

// ���ű����Ͷ��̵߳���Ϣ���޸��ɵ������Ч�ʣ�950��/ms���ڴ�ռ�ü��ͣ�CPUռ�ü���
// ����ȥ���� Event ���Ͷ��̵߳���Ϣ��

struct TASK_THREAD_PARAM;	// �����̲߳���

// ͬ��������չ�Ľ���������� CMemBlock*& 
class __declspec(dllexport) CSynchronyTaskExListener
{
public:

	CSynchronyTaskExListener()
	{
		m_lReceiveCount = 0;
	}

	/* --------------------------------------------------------------------------
	����˵������������
	���������
		pMemBlock	������Ϣ
	��������
	    pMemBlock	������Ϣ
	--------------------------------------------------------------------------*/
	virtual int OnConsumeTask(CMemBlock*& pMemBlock) = 0;

	volatile long long m_lReceiveCount;	// ʵ���ܺ�
};

// ͬ�����񣬷�������put ʱ�ǿ����βε�
class __declspec(dllexport) CSynchronyTaskEx
{
public:
	CSynchronyTaskEx(void);
	~CSynchronyTaskEx(void);

	enum{ EVENT_NUMBER = 2, };	// �¼�������

	enum
	{
		EVENT_MESSAGE = 0,
		EVENT_STOP = 1,
	};	

	enum
	{
		STATE_NO = 0,		// ��״̬
		STATE_START = 1,	// �ѿ�ʼ
		STATE_STOP = 2,		// �ѽ���
	};

	enum {	MAX_THREAD_NUM = 30,	// �����߳�����
		 };

	enum{	
			MAX_SEMAPHORE_NUMBER=100*1024,	// ��׼ֵ�������ű�����
			//MAX_SEMAPHORE_NUMBER=10,	// �����ã������ű�����
		};

	enum{
			TERMINATE_CLOSE_THREAD_TIME = 15*1000, //	��׼ֵ��ǿ�ƹر��̵߳�ʱ�䣬�� ms Ϊ��λ
			//TERMINATE_CLOSE_THREAD_TIME = 10*1000, //	����ֵ�ǵûָ��ɱ�׼ֵ��ǿ�ƹر��̵߳�ʱ�䣬�� ms Ϊ��λ
		};

	enum{	IDLE_SPIN_UP_LIMIT =   5,	// ��ת����������
			IDLE_SPIN_SLEEP_TIME = 1,	// ��ת˯��ʱ�䣬�� ms Ϊ��λ
		}; 
public:

	// ����Ͷ����Ϣ��ģ���ַ
	void set_listen_module(CSynchronyTaskExListener*	pITask);

	// ���������̵߳���������������Ϣ�̵߳�����
	void set_thread_num(int iNum=1);

	// ���������Ϣ�̵߳�����
	int get_thread_num();

	// ������Ϣ��
	void set_mem_block_pool(CMemBlockPool* pMsgPool);

	// �����Ϣ��
	CMemBlockPool* get_mem_block_pool();

	/* --------------------------------------------------------------------------
	����˵������ʼ	
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	m_pITask δ��ֵ���� set_listen_module ������ֵ
			20	m_iMessageLen ���Ȳ�Ӧ���� 0���� set_message_len ����������Ϣ�ĳ���
			30  m_pMsgPool Ϊ��
			40  ���̳߳�ʧ��
	--------------------------------------------------------------------------*/
	int start();

	// ֹͣ
	int stop();

	/* --------------------------------------------------------------------------
	����˵�������������Ϣ
	���������
		pMemBlock	������Ϣ
		bIsFront	TRUE ��ʾ�ӵ�˫����е�ͷ����FALSE ��ʾ�ӵ�˫����е�β��
	����������
		pMemBlock	������Ϣ
	����ֵ��
		�ɹ��򷵻� 0 ��
		ʧ�ܷ��� �����룬���£�
			10  TPM_CORE_EXIT ״̬
			20	��Ϣ�����ˣ������� set_message_len ���������ô�һ��
			30	�ڴ����ʧ��
	--------------------------------------------------------------------------*/
	int put(CMemBlock*& pMemBlock, BOOL bIsFront=FALSE);

	// ������Ϣ�ĳ���
	void set_message_len(int iMessageLen);

	// �����Ϣ�ĳ���
	int get_message_len();

	// ���ó��ڳ�ʼԪ�ص�����
	void set_init_block_count(int nInitBlkCount);

	// ���ó���Ԫ�ص�����ֵ
	void set_max_block_count(int nMaxBlkCount);

	// ���þ����ߵ�ֵ��ע�⣺�������� set_init_block_count ͬʱӦ��ʱҪ����������
	void set_element_alert(int iElementAlert=CMemBlockPool::DEF_INIT_COUNT*100);

	// ���õ��ﾯ���ߵ�ֵʱ��˯��ʱ�䣬��msΪ��λ
	void set_alert_sleep_time(int iAlertSleepTime=20);

	// ��ö��е�״̬���ο� TPM_CORE_NORMAL
	long get_deque_state();

	// ���ö��е�״̬���ο� TPM_CORE_NORMAL
	void set_deque_state(long lDequeState);

	int get_deque_count();

	// ʹ�� Event ������߳���Ϣ
	int handle_task_msg_Event();

	// ʹ�� Semaphore ������߳���Ϣ
	int handle_task_msg_semaphore(TASK_THREAD_PARAM* pParam);

private:
	// �������̣߳�����������Ϣ
	static unsigned __stdcall  theads_consume_task(void* pParam);	

	// ���m_dequeMsg ������Ϣ˫�����
	int clear_deque_msg();

public:
	ULONGLONG timeStart;	
	ULONGLONG timeEnd;
	ULONGLONG timeSpace;	 

	volatile long long m_lPutCount;		// put ��ȥ���ܺ�

private:
	HANDLE		 m_hThreads[MAX_THREAD_NUM];
	unsigned int m_dwThreadsID[MAX_THREAD_NUM];
	int          m_iThreadNum;					// �̵߳�����

	HANDLE		 m_hThread;
	unsigned int m_dwThreadID;

	HANDLE	m_hEvent[EVENT_NUMBER];
	HANDLE& m_hSemaphore ;	// �ű������
	HANDLE& m_hStop;		// ����

	#if USE_SRWLock
		CSRWLock			m_lock;	// ��� m_dequeMsg ����
	#else
		CCriticalSpection	m_lock;	
	#endif

	deque<CMemBlock*>	m_dequeMsg;		// ������Ϣ˫����У�ÿ��CMemBlock*Ԫ�ؾ���һ��������Ϣ����ʵ����ָ�� m_pMsgPool �ڵ�Ԫ�أ�

	CSynchronyTaskExListener*	m_pITask;	// ͬ���������Ƿ��������� OnConsumeTask ��������

	int m_iState;	// ״̬

	CMemBlockPool*	m_pMsgPool;		// ����ľ������ݣ�ֻ�����ⲿ����ָ�룬�������ڲ� new 

	int m_iMessageLen;	// ��Ϣ�ĳ���

	int volatile	m_nInitElementCount;	// ���ڳ�ʼԪ�ص�����
	int	volatile	m_nMaxElementCount;		// ����Ԫ�ص�����ֵ

	int				m_iElementAlert;		// ����Ԫ�صľ����ߣ����ڵ��ڴ�ֵʱ put ��˯ m_iAlertSleepTime ms
	int				m_iAlertSleepTime;		// ���˾����ߵ�ֵʱ��˯��ʱ�䣬��msΪ��λ

	volatile long   m_lDequeState;	// ���е�״̬���ο� TPM_CORE_NORMAL

	BOOL			m_bRunStop;		// �Ѿ�ִ�� stop ������

	bool	m_bChannelBindThread;    // true  ��ʾͨ���Ű��̣߳���һ��ͨ���ŵ�����ֻ����һ���߳���ִ�У��Ӷ���֤�˴�ͨ�������ȵ�������ִ����������Ż�ȥִ�к󵽵����ݡ�
									 // false ��ʾ�߳���ͨ�����������Ӧ�ģ���һ��ͨ���ŵ����ݿ����ڶ���߳���ִ�У��޷���֤��ͨ���������ݵ��Ⱥ�˳�򣬻�����ȵ������ݻ���ִ�У��󵽵������Ѿ�ִ�������

};

struct TASK_THREAD_PARAM	// �����̲߳���
{
	TASK_THREAD_PARAM()
	{
		pThis = NULL;
		iThreadNo = 0;
	}

	CSynchronyTaskEx* pThis;
	int iThreadNo;	// �̱߳��
};

#endif
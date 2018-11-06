
#include ".\PublicHead.h"
#include ".\ThreadGuardEx.h"

/// �ؼ������ ////////////////////////////////////////////////////////////////////////////////
CSRWLock::CSRWLock()
{
	/*
	 ��ʼ������ ��ʼ�������ֵ���� 0 ��
	 �����߳��У�ִ�� AcquireSRWLockShared �� AcquireSRWLockExclusive ֮�������ɴ������ֵ��
	 ִ�� ReleaseSRWLockShared �� ReleaseSRWLockExclusive ֮�������ָֻ�����ֵ��
	*/
	InitializeSRWLock(&m_srwLock);

	lCount = 0;
};

CSRWLock::~CSRWLock()
{
};

// ���عؼ������
SRWLOCK* CSRWLock::get_srwLock()
{
	return &m_srwLock;
}

// ������ü�������ֵ�������ѯ��Ƕ�׶�����������
long long	CSRWLock::get_count()
{
	return lCount;
}

// ԭ�ӷ�ʽ��1
void CSRWLock::increment()
{
	InterlockedIncrement64(&lCount);
}

// ��ԭ�ӵķ�ʽ�� 1
void CSRWLock::decrement()
{
	InterlockedDecrement64(&lCount);
}


/// �̼߳���Ķ����� ////////////////////////////////////////////////////////////////////////////////
CThreadGuardEx::CThreadGuardEx(CSRWLock* p)
{
	m_bEnterState = false;

	m_pCSRWLock = NULL;

	if(p)
		m_pCSRWLock = p;
}

CThreadGuardEx::~CThreadGuardEx(void)
{
	
}



int CThreadGuardEx::test()
{
	return 0;
}

/// �̼߳���Ķ����� ////////////////////////////////////////////////////////////////////////////////

CThreadGuardRead::CThreadGuardRead(CSRWLock* p)
	:CThreadGuardEx(p)
{
	enter();
}

CThreadGuardRead::~CThreadGuardRead(void)
{
	leave();
}

#define TEST_SHOW_COUNT 0	// 1��ʾ��ʾ��������0��ʾ����ʾ������
#define OVER_COUNT_PRINT 1	// ���������ڴ�ֵ�ǲŴ�ӡ

// ����ؼ������
void CThreadGuardRead::enter()
{
	if(m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// ������
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::enter ��ǰ lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		AcquireSRWLockShared(m_pCSRWLock->get_srwLock());

		//InterlockedIncrement64(&m_pCSRWLock->lCount);	// ԭ�ӷ�ʽ��1 �����Ҫ���� AcquireSRWLockShared ���棬���䱣��
		m_pCSRWLock->increment();	// ԭ�ӷ�ʽ��1 �����Ҫ���� AcquireSRWLockShared ���棬���䱣��
		
		m_bEnterState = true;	// ��ʾ m_pCSRWLock ���� enter ״̬��

		#if TEST_SHOW_COUNT	// ������
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::enter ���� lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif
	}
}

// �뿪�ؼ������
void CThreadGuardRead::leave()
{
	if(m_bEnterState && m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// ������
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::leave ��ǰ lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		//InterlockedDecrement64(&m_pCSRWLock->lCount);	// ��ԭ�ӵķ�ʽ�� 1 , ���Ҫ���� ReleaseSRWLockShared ǰ�棬���䱣��
		m_pCSRWLock->decrement();	// ��ԭ�ӵķ�ʽ�� 1 , ���Ҫ���� ReleaseSRWLockShared ǰ�棬���䱣��

		ReleaseSRWLockShared(m_pCSRWLock->get_srwLock());
		
		#if TEST_SHOW_COUNT	// ������
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::leave ���� lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		m_bEnterState = false;	//��ʾ m_pCSRWLock ���� leave ״̬
	}
}

/// �̼߳����д���� ////////////////////////////////////////////////////////////////////////////////

CThreadGuardWrite::CThreadGuardWrite(CSRWLock* p)
	:CThreadGuardEx(p)
{
	enter();
}


CThreadGuardWrite::~CThreadGuardWrite(void)
{
	leave();
}

// ����ؼ������
void CThreadGuardWrite::enter()
{
	if(m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// ������
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::enter ��ǰ lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		AcquireSRWLockExclusive(m_pCSRWLock->get_srwLock());

		// ����������ܵ����ı���

		//InterlockedIncrement64(&m_pCSRWLock->lCount);	// ԭ�ӷ�ʽ��1�����Ҫ���� AcquireSRWLockExclusive ���棬���䱣��
		m_pCSRWLock->increment();	// ԭ�ӷ�ʽ��1�����Ҫ���� AcquireSRWLockExclusive ���棬���䱣��

		#if TEST_SHOW_COUNT	// ������
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::enter ���� lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		m_bEnterState = true;	// ��ʾ m_pCSRWLock ���� enter ״̬��
	}
}

// �뿪�ؼ������
void CThreadGuardWrite::leave()
{
	if(m_bEnterState && m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// ������
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::leave ��ǰ lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		//InterlockedDecrement64(&m_pCSRWLock->lCount);	// ��ԭ�ӵķ�ʽ�� 1 , ���Ҫ���� ReleaseSRWLockExclusive ǰ�棬���䱣��
		m_pCSRWLock->decrement();		// ��ԭ�ӵķ�ʽ�� 1 , ���Ҫ���� ReleaseSRWLockExclusive ǰ�棬���䱣��

		m_bEnterState = false;

		// ����������ܵ����ı���
		ReleaseSRWLockExclusive(m_pCSRWLock->get_srwLock());

		#if TEST_SHOW_COUNT	// ������
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::leave ���� lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif
	}
}

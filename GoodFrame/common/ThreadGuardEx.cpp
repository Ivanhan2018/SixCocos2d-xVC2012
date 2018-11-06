
#include ".\PublicHead.h"
#include ".\ThreadGuardEx.h"

/// 关键代码段 ////////////////////////////////////////////////////////////////////////////////
CSRWLock::CSRWLock()
{
	/*
	 初始化锁， 初始化后这个值会是 0 。
	 到了线程中，执行 AcquireSRWLockShared 或 AcquireSRWLockExclusive 之后，它会变成大于零的值，
	 执行 ReleaseSRWLockShared 或 ReleaseSRWLockExclusive 之后，它就又恢复成零值。
	*/
	InitializeSRWLock(&m_srwLock);

	lCount = 0;
};

CSRWLock::~CSRWLock()
{
};

// 返回关键代码段
SRWLOCK* CSRWLock::get_srwLock()
{
	return &m_srwLock;
}

// 获得引用计数器的值，方便查询因嵌套而引发的死锁
long long	CSRWLock::get_count()
{
	return lCount;
}

// 原子方式增1
void CSRWLock::increment()
{
	InterlockedIncrement64(&lCount);
}

// 以原子的方式减 1
void CSRWLock::decrement()
{
	InterlockedDecrement64(&lCount);
}


/// 线程级别的读守卫 ////////////////////////////////////////////////////////////////////////////////
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

/// 线程级别的读守卫 ////////////////////////////////////////////////////////////////////////////////

CThreadGuardRead::CThreadGuardRead(CSRWLock* p)
	:CThreadGuardEx(p)
{
	enter();
}

CThreadGuardRead::~CThreadGuardRead(void)
{
	leave();
}

#define TEST_SHOW_COUNT 0	// 1表示显示计数器，0表示不显示计数器
#define OVER_COUNT_PRINT 1	// 计数器大于此值是才打印

// 进入关键代码段
void CThreadGuardRead::enter()
{
	if(m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// 测试用
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::enter 锁前 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		AcquireSRWLockShared(m_pCSRWLock->get_srwLock());

		//InterlockedIncrement64(&m_pCSRWLock->lCount);	// 原子方式增1 ，这句要放在 AcquireSRWLockShared 后面，受其保护
		m_pCSRWLock->increment();	// 原子方式增1 ，这句要放在 AcquireSRWLockShared 后面，受其保护
		
		m_bEnterState = true;	// 表示 m_pCSRWLock 处于 enter 状态，

		#if TEST_SHOW_COUNT	// 测试用
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::enter 锁后 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif
	}
}

// 离开关键代码段
void CThreadGuardRead::leave()
{
	if(m_bEnterState && m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// 测试用
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::leave 锁前 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		//InterlockedDecrement64(&m_pCSRWLock->lCount);	// 以原子的方式减 1 , 这句要放在 ReleaseSRWLockShared 前面，受其保护
		m_pCSRWLock->decrement();	// 以原子的方式减 1 , 这句要放在 ReleaseSRWLockShared 前面，受其保护

		ReleaseSRWLockShared(m_pCSRWLock->get_srwLock());
		
		#if TEST_SHOW_COUNT	// 测试用
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Read::leave 锁后 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		m_bEnterState = false;	//表示 m_pCSRWLock 处于 leave 状态
	}
}

/// 线程级别的写守卫 ////////////////////////////////////////////////////////////////////////////////

CThreadGuardWrite::CThreadGuardWrite(CSRWLock* p)
	:CThreadGuardEx(p)
{
	enter();
}


CThreadGuardWrite::~CThreadGuardWrite(void)
{
	leave();
}

// 进入关键代码段
void CThreadGuardWrite::enter()
{
	if(m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// 测试用
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::enter 锁前 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		AcquireSRWLockExclusive(m_pCSRWLock->get_srwLock());

		// 下面的数数受到锁的保护

		//InterlockedIncrement64(&m_pCSRWLock->lCount);	// 原子方式增1，这句要放在 AcquireSRWLockExclusive 后面，受其保护
		m_pCSRWLock->increment();	// 原子方式增1，这句要放在 AcquireSRWLockExclusive 后面，受其保护

		#if TEST_SHOW_COUNT	// 测试用
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::enter 锁后 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		m_bEnterState = true;	// 表示 m_pCSRWLock 处于 enter 状态，
	}
}

// 离开关键代码段
void CThreadGuardWrite::leave()
{
	if(m_bEnterState && m_pCSRWLock)
	{
		#if TEST_SHOW_COUNT	// 测试用
			DWORD dwThreadId = GetCurrentThreadId();
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::leave 锁前 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif

		//InterlockedDecrement64(&m_pCSRWLock->lCount);	// 以原子的方式减 1 , 这句要放在 ReleaseSRWLockExclusive 前面，受其保护
		m_pCSRWLock->decrement();		// 以原子的方式减 1 , 这句要放在 ReleaseSRWLockExclusive 前面，受其保护

		m_bEnterState = false;

		// 上面的数数受到锁的保护
		ReleaseSRWLockExclusive(m_pCSRWLock->get_srwLock());

		#if TEST_SHOW_COUNT	// 测试用
			if(m_pCSRWLock->get_count()>OVER_COUNT_PRINT)
				printf("dwThreadId=%d Write::leave 锁后 lCount=%I64d \n", dwThreadId, m_pCSRWLock->get_count());
		#endif
	}
}

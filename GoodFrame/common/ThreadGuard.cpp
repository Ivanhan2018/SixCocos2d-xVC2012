
#include ".\PublicHead.h"
#include ".\ThreadGuard.h"

/// 关键代码段 ////////////////////////////////////////////////////////////////////////////////

/* --------------------------------------------------------------------------
函数说明：关键代码段
传入参数：
	bIsSpin		TRUE表示自旋，FALSE表示不自旋
	dwSpinCount	自旋次数
--------------------------------------------------------------------------*/
CCriticalSpection::CCriticalSpection(BOOL bIsSpin, DWORD dwSpinCount)
{
	m_bInitState = false;
	m_dwSpinCount = dwSpinCount;
	lCount = 0;

	for(int i=0; i<10; i++)
	{
		if(!m_bInitState)	// 处于 DeleteCriticalSection 状态
		{
			if(bIsSpin)	// 自旋转方式，在多线程、release 状态下，出池 1200次/ms，速度快多了
			{
				if (InitializeCriticalSectionAndSpinCount(&stCriticalSection, m_dwSpinCount))
				{
					m_bInitState = true;
					return;	// 成功就可以返回了
				}
			}
			else	// 非自旋转方式，在多线程、release 状态下，出池 650次/ms ，速度慢
			{
				InitializeCriticalSection(&stCriticalSection);
				m_bInitState = true;
				return;
			}
		}

		// 初始化关键代码段_循环锁 失败! 在内存不足的情况下会发生这种错误 
		Sleep(200);
	}
};

CCriticalSpection::~CCriticalSpection()
{
	if(m_bInitState)	// 处于 InitializeCriticalSectionAndSpinCount 状态
	{
		DeleteCriticalSection(&stCriticalSection);	// 清除关键代码段

		m_bInitState = false;
	}
};

// 返回关键代码段
CRITICAL_SECTION* CCriticalSpection::get_critical_section()
{
	return &stCriticalSection;
}

// 有效的
BOOL CCriticalSpection::is_validate()
{
	return m_bInitState;
}

// 获得引用计数器的值，方便查询因嵌套而引发的死锁
/*long */long	CCriticalSpection::get_count()
{
	return lCount;
}

/// 线程级别的读守卫 ////////////////////////////////////////////////////////////////////////////////

// 线程级别的守卫
CThreadGuard::CThreadGuard(CCriticalSpection* pCriticalSection)
{
	m_bEnterState = false;
	m_pCriticalSection = pCriticalSection;
	
	if(m_pCriticalSection->is_validate())
	{
		enter();
	}
}

CThreadGuard::~CThreadGuard(void)
{
	leave();
}

// 进入关键代码段
void CThreadGuard::enter()
{
	if(m_pCriticalSection)
	{
		::EnterCriticalSection(m_pCriticalSection->get_critical_section());

		// 下面的数数受到锁的保护

		//InterlockedIncrement64(&m_pCriticalSection->lCount);	// 原子方式增1，这句要放在 EnterCriticalSection 后面，受其保护
		InterlockedIncrement(&m_pCriticalSection->lCount);
		m_bEnterState = true;	// 表示 m_pCriticalSection 处于 enter 状态，
	}
}

// 离开关键代码段
void CThreadGuard::leave()
{
	if(m_bEnterState && m_pCriticalSection && m_pCriticalSection->is_validate() )
	{
		//InterlockedDecrement64(&m_pCriticalSection->lCount);	// 以原子的方式减 1, 这句要放在 LeaveCriticalSection 前面，受其保护
		InterlockedDecrement(&m_pCriticalSection->lCount);
		m_bEnterState = false;	// 表示 m_pCriticalSection 处于 leave 状态

		// 上面的数数受到锁的保护
		::LeaveCriticalSection(m_pCriticalSection->get_critical_section());
	}
}
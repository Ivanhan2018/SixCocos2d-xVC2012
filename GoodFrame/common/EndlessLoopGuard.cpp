
#include ".\PublicHead.h"
#include ".\EndlessLoopGuard.h"

/// 关键代码段 ////////////////////////////////////////////////////////////////////////////////
CEndlessLoop::CEndlessLoop()
{
	lCount = 0;
};

CEndlessLoop::~CEndlessLoop()
{
};

// 返回关键代码段
CCriticalSpection* CEndlessLoop::get_lock()
{
	return &m_lock;
}

// 获得引用计数器的值，方便查询因嵌套而引发的死锁
long long	CEndlessLoop::get_count()
{
	return lCount;
}

// 列印所有的死循环、死锁
int CEndlessLoop::display_all_guard(bool bDiaplay, vector<ENDLESS_LOOP_INFO>& vecEndlessLoopInfo)
{
#if CHECK_ENDLESS_LOOP

	::EnterCriticalSection(m_lock.get_critical_section());	// 进锁

	MAP_ENDLESS_LOOP* pMap =  &m_mapGuard;
	size_t iSize = pMap->size();

	if(iSize>0)
		printf_s("死循环监测，出现死循环，列表如下： \n");
	else
		printf_s("死循环监测，没有出现死循环 \n");

	MAP_ENDLESS_LOOP::iterator iter = pMap->begin();
	for( ; iter!= pMap->end(); iter++)
	{
		ENDLESS_LOOP_INFO* pLoopInfo = (ENDLESS_LOOP_INFO*)(&(*iter).second);
		if(pLoopInfo)
		{
			pLoopInfo->lDisplayTime = ::GetTickCount64();

			if(bDiaplay)
			{
				printf_s("  %s , 时间差 %d ms , 进入时间 %d, 列印时间 %d \n", 
						pLoopInfo->strSignName.c_str(), 
						pLoopInfo->lDisplayTime-pLoopInfo->lEnterTime,
						pLoopInfo->lEnterTime, 
						pLoopInfo->lDisplayTime
						);
			}

			vecEndlessLoopInfo.push_back(*pLoopInfo);
		}
	}

	::LeaveCriticalSection(m_lock.get_critical_section());	// 离锁
#endif

	return 0;
}

/// 死循环守护 ////////////////////////////////////////////////////////////////////////////////

CEndlessLoopGuard::CEndlessLoopGuard(CEndlessLoop* pLoop, char* pszSignName)
{
#if CHECK_ENDLESS_LOOP
	m_bEnterState = false;
	m_pEndlessLoop = pLoop;

	if(m_pEndlessLoop)
	{
		::EnterCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// 进锁
		{
			// 下面的数数受到锁的保护
			MAP_ENDLESS_LOOP* pMap =  &(m_pEndlessLoop->m_mapGuard);

			ENDLESS_LOOP_INFO loopInof;
			loopInof.lEnterTime = ::GetTickCount64();
			loopInof.lDisplayTime = 0;
			loopInof.strSignName = pszSignName;

			pMap->insert(PAIR_ENDLESS_LOOP(this, loopInof));

			InterlockedIncrement64(&m_pEndlessLoop->lCount);	// 原子方式增1 ，这句要放在 AcquireSRWLockShared 后面，受其保护
			m_bEnterState = true;	// 表示 m_pEndlessLoop 处于 enter 状态，
		}

		::LeaveCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// 离锁
	}
#endif
}

CEndlessLoopGuard::~CEndlessLoopGuard(void)
{
#if CHECK_ENDLESS_LOOP
	if(m_bEnterState && m_pEndlessLoop)
	{
		::EnterCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// 进锁

		InterlockedDecrement64(&m_pEndlessLoop->lCount);	// 以原子的方式减 1 , 这句要放在 ReleaseSRWLockShared 前面，受其保护
		m_bEnterState = false;	//表示 m_pEndlessLoop 处于 leave 状态

		MAP_ENDLESS_LOOP* pMap =  &(m_pEndlessLoop->m_mapGuard);
		MAP_ENDLESS_LOOP::iterator iter = pMap->find(this);

		if( iter != pMap->end())	// 找到了
		{
			pMap->erase(iter);
		}

		// 上面的数数受到锁的保护
		::LeaveCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// 离锁
	}
#endif
}

int CEndlessLoopGuard::test()
{
	return 0;
}

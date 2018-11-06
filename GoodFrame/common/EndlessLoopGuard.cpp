
#include ".\PublicHead.h"
#include ".\EndlessLoopGuard.h"

/// �ؼ������ ////////////////////////////////////////////////////////////////////////////////
CEndlessLoop::CEndlessLoop()
{
	lCount = 0;
};

CEndlessLoop::~CEndlessLoop()
{
};

// ���عؼ������
CCriticalSpection* CEndlessLoop::get_lock()
{
	return &m_lock;
}

// ������ü�������ֵ�������ѯ��Ƕ�׶�����������
long long	CEndlessLoop::get_count()
{
	return lCount;
}

// ��ӡ���е���ѭ��������
int CEndlessLoop::display_all_guard(bool bDiaplay, vector<ENDLESS_LOOP_INFO>& vecEndlessLoopInfo)
{
#if CHECK_ENDLESS_LOOP

	::EnterCriticalSection(m_lock.get_critical_section());	// ����

	MAP_ENDLESS_LOOP* pMap =  &m_mapGuard;
	size_t iSize = pMap->size();

	if(iSize>0)
		printf_s("��ѭ����⣬������ѭ�����б����£� \n");
	else
		printf_s("��ѭ����⣬û�г�����ѭ�� \n");

	MAP_ENDLESS_LOOP::iterator iter = pMap->begin();
	for( ; iter!= pMap->end(); iter++)
	{
		ENDLESS_LOOP_INFO* pLoopInfo = (ENDLESS_LOOP_INFO*)(&(*iter).second);
		if(pLoopInfo)
		{
			pLoopInfo->lDisplayTime = ::GetTickCount64();

			if(bDiaplay)
			{
				printf_s("  %s , ʱ��� %d ms , ����ʱ�� %d, ��ӡʱ�� %d \n", 
						pLoopInfo->strSignName.c_str(), 
						pLoopInfo->lDisplayTime-pLoopInfo->lEnterTime,
						pLoopInfo->lEnterTime, 
						pLoopInfo->lDisplayTime
						);
			}

			vecEndlessLoopInfo.push_back(*pLoopInfo);
		}
	}

	::LeaveCriticalSection(m_lock.get_critical_section());	// ����
#endif

	return 0;
}

/// ��ѭ���ػ� ////////////////////////////////////////////////////////////////////////////////

CEndlessLoopGuard::CEndlessLoopGuard(CEndlessLoop* pLoop, char* pszSignName)
{
#if CHECK_ENDLESS_LOOP
	m_bEnterState = false;
	m_pEndlessLoop = pLoop;

	if(m_pEndlessLoop)
	{
		::EnterCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// ����
		{
			// ����������ܵ����ı���
			MAP_ENDLESS_LOOP* pMap =  &(m_pEndlessLoop->m_mapGuard);

			ENDLESS_LOOP_INFO loopInof;
			loopInof.lEnterTime = ::GetTickCount64();
			loopInof.lDisplayTime = 0;
			loopInof.strSignName = pszSignName;

			pMap->insert(PAIR_ENDLESS_LOOP(this, loopInof));

			InterlockedIncrement64(&m_pEndlessLoop->lCount);	// ԭ�ӷ�ʽ��1 �����Ҫ���� AcquireSRWLockShared ���棬���䱣��
			m_bEnterState = true;	// ��ʾ m_pEndlessLoop ���� enter ״̬��
		}

		::LeaveCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// ����
	}
#endif
}

CEndlessLoopGuard::~CEndlessLoopGuard(void)
{
#if CHECK_ENDLESS_LOOP
	if(m_bEnterState && m_pEndlessLoop)
	{
		::EnterCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// ����

		InterlockedDecrement64(&m_pEndlessLoop->lCount);	// ��ԭ�ӵķ�ʽ�� 1 , ���Ҫ���� ReleaseSRWLockShared ǰ�棬���䱣��
		m_bEnterState = false;	//��ʾ m_pEndlessLoop ���� leave ״̬

		MAP_ENDLESS_LOOP* pMap =  &(m_pEndlessLoop->m_mapGuard);
		MAP_ENDLESS_LOOP::iterator iter = pMap->find(this);

		if( iter != pMap->end())	// �ҵ���
		{
			pMap->erase(iter);
		}

		// ����������ܵ����ı���
		::LeaveCriticalSection(m_pEndlessLoop->get_lock()->get_critical_section());	// ����
	}
#endif
}

int CEndlessLoopGuard::test()
{
	return 0;
}

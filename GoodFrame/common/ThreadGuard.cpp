
#include ".\PublicHead.h"
#include ".\ThreadGuard.h"

/// �ؼ������ ////////////////////////////////////////////////////////////////////////////////

/* --------------------------------------------------------------------------
����˵�����ؼ������
���������
	bIsSpin		TRUE��ʾ������FALSE��ʾ������
	dwSpinCount	��������
--------------------------------------------------------------------------*/
CCriticalSpection::CCriticalSpection(BOOL bIsSpin, DWORD dwSpinCount)
{
	m_bInitState = false;
	m_dwSpinCount = dwSpinCount;
	lCount = 0;

	for(int i=0; i<10; i++)
	{
		if(!m_bInitState)	// ���� DeleteCriticalSection ״̬
		{
			if(bIsSpin)	// ����ת��ʽ���ڶ��̡߳�release ״̬�£����� 1200��/ms���ٶȿ����
			{
				if (InitializeCriticalSectionAndSpinCount(&stCriticalSection, m_dwSpinCount))
				{
					m_bInitState = true;
					return;	// �ɹ��Ϳ��Է�����
				}
			}
			else	// ������ת��ʽ���ڶ��̡߳�release ״̬�£����� 650��/ms ���ٶ���
			{
				InitializeCriticalSection(&stCriticalSection);
				m_bInitState = true;
				return;
			}
		}

		// ��ʼ���ؼ������_ѭ���� ʧ��! ���ڴ治�������»ᷢ�����ִ��� 
		Sleep(200);
	}
};

CCriticalSpection::~CCriticalSpection()
{
	if(m_bInitState)	// ���� InitializeCriticalSectionAndSpinCount ״̬
	{
		DeleteCriticalSection(&stCriticalSection);	// ����ؼ������

		m_bInitState = false;
	}
};

// ���عؼ������
CRITICAL_SECTION* CCriticalSpection::get_critical_section()
{
	return &stCriticalSection;
}

// ��Ч��
BOOL CCriticalSpection::is_validate()
{
	return m_bInitState;
}

// ������ü�������ֵ�������ѯ��Ƕ�׶�����������
/*long */long	CCriticalSpection::get_count()
{
	return lCount;
}

/// �̼߳���Ķ����� ////////////////////////////////////////////////////////////////////////////////

// �̼߳��������
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

// ����ؼ������
void CThreadGuard::enter()
{
	if(m_pCriticalSection)
	{
		::EnterCriticalSection(m_pCriticalSection->get_critical_section());

		// ����������ܵ����ı���

		//InterlockedIncrement64(&m_pCriticalSection->lCount);	// ԭ�ӷ�ʽ��1�����Ҫ���� EnterCriticalSection ���棬���䱣��
		InterlockedIncrement(&m_pCriticalSection->lCount);
		m_bEnterState = true;	// ��ʾ m_pCriticalSection ���� enter ״̬��
	}
}

// �뿪�ؼ������
void CThreadGuard::leave()
{
	if(m_bEnterState && m_pCriticalSection && m_pCriticalSection->is_validate() )
	{
		//InterlockedDecrement64(&m_pCriticalSection->lCount);	// ��ԭ�ӵķ�ʽ�� 1, ���Ҫ���� LeaveCriticalSection ǰ�棬���䱣��
		InterlockedDecrement(&m_pCriticalSection->lCount);
		m_bEnterState = false;	// ��ʾ m_pCriticalSection ���� leave ״̬

		// ����������ܵ����ı���
		::LeaveCriticalSection(m_pCriticalSection->get_critical_section());
	}
}
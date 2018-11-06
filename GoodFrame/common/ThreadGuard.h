#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// �ؼ������
class __declspec(dllexport) CCriticalSpection
{
public:

	/* --------------------------------------------------------------------------
	����˵����
	���������
		bIsSpin		TRUE��ʾ������FALSE��ʾ������
		dwSpinCount	��������
	--------------------------------------------------------------------------*/
	CCriticalSpection(BOOL bIsSpin=TRUE, DWORD dwSpinCount=4000);
	~CCriticalSpection();
	
	// ���عؼ������
	CRITICAL_SECTION*	get_critical_section();

	// ��Ч��
	BOOL is_validate();

	// ������ü�������ֵ
	/*long */long	get_count();

public:
	/*long */long lCount;	// ���ü�����

private:
	CRITICAL_SECTION	stCriticalSection;
	DWORD				m_dwSpinCount;		// �����Ĵ���
	BOOL				m_bInitState;		// true ��ʾ m_pCriticalSection ���� InitializeCriticalSectionAndSpinCount ״̬��false ��ʾm_pCriticalSection ���� DeleteCriticalSection ״̬
};

// �̼߳��������
class __declspec(dllexport) CThreadGuard
{
public:
	CThreadGuard(CCriticalSpection* pCriticalSection);

	~CThreadGuard(void);

	// ����ؼ������
	void enter();

	// �뿪�ؼ������
	void leave();

private:

	// ��ʼ�������ٶ����������Զ����У��ŵ㣺��һ�����ڽ���ǰreturn�˻��쳣�ˣ�
	// g_SampleCS ��ͨ�������������ٵ��ؼ������
	CCriticalSpection*	m_pCriticalSection;

	BOOL				m_bEnterState;		// true  ��ʾ m_pCriticalSection ���� enter ״̬��
											// false ��ʾ m_pCriticalSection ���� leave ״̬
	

	
};

#endif

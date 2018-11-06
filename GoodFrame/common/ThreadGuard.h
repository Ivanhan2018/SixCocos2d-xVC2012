#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// 关键代码段
class __declspec(dllexport) CCriticalSpection
{
public:

	/* --------------------------------------------------------------------------
	函数说明：
	传入参数：
		bIsSpin		TRUE表示自旋，FALSE表示不自旋
		dwSpinCount	自旋次数
	--------------------------------------------------------------------------*/
	CCriticalSpection(BOOL bIsSpin=TRUE, DWORD dwSpinCount=4000);
	~CCriticalSpection();
	
	// 返回关键代码段
	CRITICAL_SECTION*	get_critical_section();

	// 有效的
	BOOL is_validate();

	// 获得引用计数器的值
	/*long */long	get_count();

public:
	/*long */long lCount;	// 引用计数器

private:
	CRITICAL_SECTION	stCriticalSection;
	DWORD				m_dwSpinCount;		// 自旋的次数
	BOOL				m_bInitState;		// true 表示 m_pCriticalSection 处于 InitializeCriticalSectionAndSpinCount 状态，false 表示m_pCriticalSection 处于 DeleteCriticalSection 状态
};

// 线程级别的守卫
class __declspec(dllexport) CThreadGuard
{
public:
	CThreadGuard(CCriticalSpection* pCriticalSection);

	~CThreadGuard(void);

	// 进入关键代码段
	void enter();

	// 离开关键代码段
	void leave();

private:

	// 初始化与销毁都已在类中自动进行，优点：万一程序在解锁前return了或异常了，
	// g_SampleCS 会通过析构自我销毁掉关键代码段
	CCriticalSpection*	m_pCriticalSection;

	BOOL				m_bEnterState;		// true  表示 m_pCriticalSection 处于 enter 状态，
											// false 表示 m_pCriticalSection 处于 leave 状态
	

	
};

#endif

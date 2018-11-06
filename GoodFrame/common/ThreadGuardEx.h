/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:43
	filename: 	C:\GoodFrame\common\ThreadGuardEx.h
	file path:	C:\GoodFrame\common
	file base:	ThreadGuardEx
	file ext:	h
	author:		侯国江
	
	purpose:	支持读写锁的读写守卫
*********************************************************************/

#ifndef THREAD_GUARD_EX_H
#define THREAD_GUARD_EX_H

// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// 读写锁
class __declspec(dllexport) CSRWLock
{
public:
	CSRWLock();
	~CSRWLock();
	
	// 返回关键代码段
	inline SRWLOCK*	get_srwLock();

	// 获得引用计数器的值，方便查询因嵌套而引发的死锁
	inline long long	get_count();

	// 原子方式增1
	inline void increment();

	// 以原子的方式减 1
	inline void decrement();

public:
	long long lCount;	// 引用计数器

private:
	SRWLOCK     m_srwLock; 	
};

///////////////////////////////////////////////////////////////////////////////////

// 线程级别的守卫，仅仅让 CThreadGuardRead、CThreadGuardWrite 来继承
class __declspec(dllexport) CThreadGuardEx
{
public:
	CThreadGuardEx(CSRWLock* p);

	~CThreadGuardEx(void);

protected:
	// 进入关键代码段
	virtual void enter()=0;

	// 离开关键代码段
	virtual void leave()=0;

public:
	int test();

protected:

	// 初始化与销毁都已在类中自动进行，优点：万一程序在解锁前return了或异常了，会通过析构自我解锁
	CSRWLock*	m_pCSRWLock;

	bool		m_bEnterState;	// true  表示 m_pCSRWLock 处于 enter 状态，
								// false 表示 m_pCSRWLock 处于 leave 状态
};

///////////////////////////////////////////////////////////////////////////////////

// 线程读守护
class __declspec(dllexport) CThreadGuardRead : public CThreadGuardEx
{
public:
	CThreadGuardRead(CSRWLock* p);
	~CThreadGuardRead(void);

//private:
public:
	// 进入关键代码段
	virtual void enter();

public:
	// 离开关键代码段
	virtual void leave();
};

///////////////////////////////////////////////////////////////////////////////////

// 线程写守护
class __declspec(dllexport) CThreadGuardWrite : public CThreadGuardEx
{
public:
	CThreadGuardWrite(CSRWLock* p);
	~CThreadGuardWrite(void);

public:
	// 进入关键代码段
	virtual void enter();

public:
	// 离开关键代码段
	virtual void leave();
};

#endif

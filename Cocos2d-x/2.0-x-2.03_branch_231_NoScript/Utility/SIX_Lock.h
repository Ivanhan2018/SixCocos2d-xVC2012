/***********************************************
Name£ºSIX_Lock
Desc£ºpthread_mutex_t/pthread_spinlock_t
Auth£ºCool.Cat@2013-04-16
***********************************************/
#pragma once

#ifdef WIN32
#include <Windows.h>
#endif
#include <pthread.h>
#include <SIX_Typedef.h>

class SIX_LockObj
{
public:
	SIX_LockObj(){}
	~SIX_LockObj(){}

	virtual void Lock() = 0;
	virtual void TryLock() = 0;
	virtual void Unlock() = 0;
};

class SIX_Mutex: public SIX_LockObj
{
public:
	SIX_Mutex()
	{
		pthread_mutex_init(&m_Mutex, 0);
	}

	~SIX_Mutex()
	{
		int iResult = pthread_mutex_destroy(&m_Mutex);
		if (iResult)
			SIXLog("pthread_mutex_destroy.Error");
	}

	void Lock()
	{
		int iResult = pthread_mutex_lock(&m_Mutex);
		if (iResult)
			SIXLog("pthread_mutex_lock.Error");
	}

	void TryLock()
	{
		int iResult = pthread_mutex_trylock(&m_Mutex);
		if (iResult)
			SIXLog("pthread_mutex_trylock.Error");
	}

	void Unlock()
	{
		int iResult = pthread_mutex_unlock(&m_Mutex);
		if (iResult)
			SIXLog("pthread_mutex_unlock.Error");
	}

private:
	pthread_mutex_t m_Mutex;
};

#ifdef WIN32
class SIX_SpinLock: public SIX_LockObj
{
public:
	SIX_SpinLock()
	{
		pthread_spin_init(&m_SpinLock, 0);
	}

	~SIX_SpinLock()
	{
		int iResult = pthread_spin_destroy(&m_SpinLock);
		if (iResult)
			SIXLog("pthread_spin_destroy.Error");
	}

	void Lock()
	{
		int iResult = pthread_spin_lock(&m_SpinLock);
		if (iResult)
			SIXLog("pthread_spin_lock.Error");
	}

	void TryLock()
	{
		int iResult = pthread_spin_trylock(&m_SpinLock);
		if (iResult)
			SIXLog("pthread_spin_trylock.Error");
	}

	void Unlock()
	{
		int iResult = pthread_spin_unlock(&m_SpinLock);
		if (iResult)
			SIXLog("pthread_spin_unlock.Error");
	}

private:
	pthread_spinlock_t m_SpinLock;
};
#endif

class SIX_Lock
{
public:
	SIX_Lock(SIX_LockObj *LockObj)
	{
		m_LockObj = LockObj;
		m_LockObj->Lock();
	}
	~SIX_Lock()
	{
		m_LockObj->Unlock();
	}
private:
	SIX_LockObj *m_LockObj;
};
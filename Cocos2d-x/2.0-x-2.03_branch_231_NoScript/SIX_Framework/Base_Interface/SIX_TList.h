/***********************************************
Name：SIX_TList
Desc：FIFO
Auth：Cool.Cat@2013-04-17
***********************************************/
#pragma once
#include <SIX_Lock.h>
#include <list>
using namespace std;

template<typename T>
class SIX_TList
{
public:
	typedef list<void*> MsgList;
	typedef list<void*>::iterator MsgIter;

	SIX_TList()
	{
#ifdef WIN32
		mutex = new SIX_SpinLock();
#else
		mutex = new SIX_Mutex();
#endif
		m_bInited = true;
	}

	~SIX_TList()
	{
		Destory();
		m_bInited = false;
		CC_SAFE_DELETE(mutex);
	}
public:
	T Front()
	{
		if (!m_bInited)
			return 0;
		T t = 0;
		SIX_Lock lock(mutex);
		// list的front在链表为空情况下居然返回非零
		// so只能每次判断下咯~
		if (!m_msgList.empty())
		{
			// 弹出表头
			t = (T)m_msgList.front();
		}
		return t;
	}

	// 弹出消息
	T Pop()
	{
		if (!m_bInited)
			return 0;
		T t = 0;
		SIX_Lock lock(mutex);
		// list的front在链表为空情况下居然返回非零
		// so只能每次判断下咯~
		if (!m_msgList.empty())
		{
			// 弹出表头
			t = (T)m_msgList.front();
			m_msgList.pop_front();
		}
		return t;		
	}

	// 插入消息
	void Push(T t)
	{
		if (!m_bInited)
			return;
		SIX_Lock lock(mutex);
		m_msgList.push_back(t);
	}

	void Destory()
	{
		if (!m_bInited)
			return;
		T t = 0;
		SIX_Lock lock(mutex);
		for (m_msgIter=m_msgList.begin();m_msgIter!=m_msgList.end();)
		{
			t = (T)(*m_msgIter);
			m_msgList.erase(m_msgIter++);
			if (t)
				CC_SAFE_DELETE(t);
		}
#ifdef WIN32
		m_msgList.swap(list<void*>());
#endif
		m_msgList.clear();
	}

	// 消息总数
	unsigned int GetCount()
	{
		if (!m_bInited)
			return 0;
		SIX_Lock lock(mutex);
		unsigned int count = m_msgList.size();
		return count;
	}
private:
	MsgList m_msgList;
	MsgIter m_msgIter;

#ifdef WIN32
	SIX_SpinLock *mutex;
#else
	SIX_Mutex *mutex;
#endif

	bool m_bInited;
};
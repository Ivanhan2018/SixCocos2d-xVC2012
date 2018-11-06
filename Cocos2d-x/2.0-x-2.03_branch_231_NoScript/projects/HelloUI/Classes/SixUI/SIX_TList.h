/***********************************************
Name��SIX_TList
Desc��FIFO
Auth��Cool.Cat@2013-04-17
***********************************************/
#pragma once
#include "SIX_Lock.h"
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
		mutex = new SIX_Mutex();
	}

	~SIX_TList()
	{
		Destory();
		CC_SAFE_DELETE(mutex);
	}
public:
	T Front()
	{
		T t = 0;
		SIX_Lock lock(mutex);
		// list��front������Ϊ������¾�Ȼ���ط���
		// soֻ��ÿ���ж��¿�~
		if (!m_msgList.empty())
		{
			// ������ͷ
			t = (T)m_msgList.front();
		}
		return t;
	}

	// ������Ϣ
	T Pop()
	{
		T t = 0;
		SIX_Lock lock(mutex);
		// list��front������Ϊ������¾�Ȼ���ط���
		// soֻ��ÿ���ж��¿�~
		if (!m_msgList.empty())
		{
			// ������ͷ
			t = (T)m_msgList.front();
			m_msgList.pop_front();
		}
		return t;		
	}

	// ������Ϣ
	void Push(T t)
	{
		SIX_Lock lock(mutex);
		m_msgList.push_back(t);
	}

	void Destory()
	{
		T t = 0;
		SIX_Lock lock(mutex);
		for (m_msgIter=m_msgList.begin();m_msgIter!=m_msgList.end();)
		{
			t = (T)(*m_msgIter);
			m_msgList.erase(m_msgIter++);
			if (t)
				CC_SAFE_DELETE(t);
		}
		m_msgList.clear();
	}

	// ��Ϣ����
	unsigned int GetCount()
	{
		SIX_Lock lock(mutex);
		unsigned int count = m_msgList.size();
		return count;		
	}
private:
	MsgList m_msgList;
	MsgIter m_msgIter;

	SIX_Mutex *mutex;
};
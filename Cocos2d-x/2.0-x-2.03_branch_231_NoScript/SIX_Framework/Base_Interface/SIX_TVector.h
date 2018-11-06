/***********************************************
Name：SIX_TVector
Desc：vector封装通用模板类
Auth：Cool.Cat@2013-10-11
***********************************************/
#pragma once
#include <SIX_Lock.h>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class SIX_TVector
{
public:
	typedef vector<void*> vList;
	typedef vector<void*>::iterator vIter;

	SIX_TVector()
	{
#ifdef WIN32
		mutex = new SIX_SpinLock();
#else
		mutex = new SIX_Mutex();
#endif
		m_bInited = true;
	}

	~SIX_TVector()
	{
		Destory();
		m_bInited = false;
		CC_SAFE_DELETE(mutex);
	}
public:
	// 取
	T Get(unsigned int idx)
	{
		if (!m_bInited)
			return 0;
		T t = 0;
		SIX_Lock lock(mutex);
		if (idx>=m_vList.size())
			return 0;
		if (!m_vList.empty())
		{
			t = (T)m_vList[idx];
		}
		return t;		
	}

	// 插
	void Push(T t)
	{
		if (!m_bInited)
			return;
		SIX_Lock lock(mutex);
		m_vList.push_back(t);
	}

	void Destory()
	{
		if (!m_bInited)
			return;
		T t = 0;
		SIX_Lock lock(mutex);
		for (m_vIter=m_vList.begin();m_vIter!=m_vList.end();)
		{
			t = (T)(*m_vIter);
			m_vIter = m_vList.erase(m_vIter);
			if (t)
				CC_SAFE_DELETE(t);
		}
#ifdef WIN32
		m_vList.swap(vector<void*>());
#endif
		m_vList.clear();
	}

	// 消息总数
	unsigned int GetCount()
	{
		if (!m_bInited)
			return 0;
		SIX_Lock lock(mutex);
		unsigned int count = m_vList.size();
		return count;
	}
private:
	vList m_vList;
	vIter m_vIter;

#ifdef WIN32
	SIX_SpinLock *mutex;
#else
	SIX_Mutex *mutex;
#endif

	bool m_bInited;
};
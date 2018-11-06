/***********************************************
Name：SIX_TMap
Desc：Map封装通用模板类
Auth：Cool.Cat@2013-08-06
***********************************************/
#pragma once
#include <SIX_Lock.h>
#include <map>
#include <algorithm>
using namespace std;

template<typename K,typename V>
class SIX_TMap
{
public:
	// 下面定义方式在GCC里会报错：expected nested-name-specifier invalid declarator before 'KV_MAP'。。。
	// 看来不能省事用typedef了，找时间改下~
	// 下面已改为通用写法，兼容gun-stl
	// Cool.Cat
	typedef map<K,V> KV_MAP;
	typedef typename map<K,V>::iterator KV_ITER;
#ifdef WIN32
	typedef typename pair<typename map<K,V>::iterator,bool> KV_PAIR;
#endif

	SIX_TMap()
	{
#ifdef WIN32
		mutex = new SIX_SpinLock();
#else
		mutex = new SIX_Mutex();
#endif
		m_bInited = true;
	}

	virtual ~SIX_TMap()
	{
		Destory();
		m_bInited = false;
		CC_SAFE_DELETE(mutex);
	}
public:
	V Get(K idx)
	{
		if (!m_bInited)
			return 0;
		SIX_Lock lock(mutex);
		m_iter = m_map.find(idx);
		if (m_iter!=m_map.end())
			return m_iter->second;
		return 0;
	}

	void Del(K idx)
	{
		if (!m_bInited)
			return;
		V v = Get(idx);
		if (!v)
			return;
		SIX_Lock lock(mutex);
		m_map.erase(idx);
		// 在删除之前丢出去，给最后一次执行机会...
		// Cool.Cat
		OnDelegateDestory(v);
		CC_SAFE_DELETE(v);
	}

	bool Add(K k,V v)
	{
		if (!m_bInited)
			return false;
		SIX_Lock lock(mutex);
#ifdef WIN32
		KV_PAIR status = m_map.insert(KV_MAP::value_type(k,v));
#else
		pair<typename map<K,V>::iterator,bool> status = m_map.insert(typename KV_MAP::value_type(k,v));
#endif
		return status.second;
	}

	void Destory()
	{
		if (!m_bInited)
			return;
		SIX_Lock lock(mutex);
		for (m_iter=m_map.begin();m_iter!=m_map.end();)
		{
			V v = m_iter->second;
			m_map.erase(m_iter++);
			// 在删除之前丢出去，给最后一次执行机会...
			// Cool.Cat
			OnDelegateDestory(v);
			CC_SAFE_DELETE(v);
		}
	}

	void Iteration()
	{
		if (!m_bInited)
			return;
		SIX_Lock lock(mutex);
		for (m_iter=m_map.begin();m_iter!=m_map.end();m_iter++)
		{
			V v = m_iter->second;
			OnDelegateIteration(v);
		}
	}

	unsigned int GetCount()
	{
		if (!m_bInited)
			return 0;
		return m_map.size();
	}

	KV_MAP GetMap(){return m_map;}
private:
	virtual void OnDelegateDestory(V){};
	virtual void OnDelegateIteration(V){};
protected:
	KV_MAP m_map;
	KV_ITER m_iter;

#ifdef WIN32
	SIX_SpinLock *mutex;
#else
	SIX_Mutex *mutex;
#endif

	bool m_bInited;
};
#pragma once
#ifdef WIN32
#include <Windows.h>
#endif

template <typename T>
class TSingleton
{
public:
	virtual ~TSingleton(){}
	static T *GetInstance() 
	{
		if (!m_Instance)
			m_Instance = new T;
		return m_Instance;
	}

protected:
	TSingleton(){}
	TSingleton(const TSingleton<T>&){}
	TSingleton<T>& operator=(const TSingleton<T>&){}

	static T *m_Instance;
};

template<typename T>
T *TSingleton<T>::m_Instance = 0;
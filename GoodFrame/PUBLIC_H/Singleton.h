/********************************************************************
	created:	2013/01/24
	created:	18:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		�����
	
	purpose:	����ģʽ��ͨ��

	��ע��		һ���������治Ҫ���õĵ���ģʽ�������������ܶ���벻�������⡣
				�ȫ�ľ���ֻ��һ�����ǵ���ģʽ��
*********************************************************************/

#ifndef SINGLETON_H
#define SINGLETON_H

template <class T> 
class __declspec(dllexport) CSingleton
{
public:
	CSingleton();
	~CSingleton();
public:
	static T* create();
	static void destroy();

	static T& get_singleton();
	static T* get_singleton_ptr();

private:
	static T* m_pT;
};

template <class T> 
CSingleton<T>::CSingleton()
{
	if(m_pT)
		return;

	m_pT = static_cast<T*>(this);
}

template <class T> 
CSingleton<T>::~CSingleton()
{
	if( m_pT )
		m_pT = 0;
}

template <class T> 
T& CSingleton<T>::get_singleton()
{  
	return ( *m_pT );  
}

template <class T> 
T* CSingleton<T>::get_singleton_ptr()
{  
	return ( m_pT );  
}

template <class T> 
T* CSingleton<T>::create()
{  
	if(!m_pT)
	{
		T* p = new T;
		return p;
	}
	return m_pT;
}

template <class T> 
void CSingleton<T>::destroy()
{  
	if(m_pT)
	{
		delete m_pT;
		m_pT = NULL;
	}
}

template<class T>
T *CSingleton<T>::m_pT = 0;

#endif
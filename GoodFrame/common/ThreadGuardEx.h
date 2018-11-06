/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:43
	filename: 	C:\GoodFrame\common\ThreadGuardEx.h
	file path:	C:\GoodFrame\common
	file base:	ThreadGuardEx
	file ext:	h
	author:		�����
	
	purpose:	֧�ֶ�д���Ķ�д����
*********************************************************************/

#ifndef THREAD_GUARD_EX_H
#define THREAD_GUARD_EX_H

// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// ��д��
class __declspec(dllexport) CSRWLock
{
public:
	CSRWLock();
	~CSRWLock();
	
	// ���عؼ������
	inline SRWLOCK*	get_srwLock();

	// ������ü�������ֵ�������ѯ��Ƕ�׶�����������
	inline long long	get_count();

	// ԭ�ӷ�ʽ��1
	inline void increment();

	// ��ԭ�ӵķ�ʽ�� 1
	inline void decrement();

public:
	long long lCount;	// ���ü�����

private:
	SRWLOCK     m_srwLock; 	
};

///////////////////////////////////////////////////////////////////////////////////

// �̼߳���������������� CThreadGuardRead��CThreadGuardWrite ���̳�
class __declspec(dllexport) CThreadGuardEx
{
public:
	CThreadGuardEx(CSRWLock* p);

	~CThreadGuardEx(void);

protected:
	// ����ؼ������
	virtual void enter()=0;

	// �뿪�ؼ������
	virtual void leave()=0;

public:
	int test();

protected:

	// ��ʼ�������ٶ����������Զ����У��ŵ㣺��һ�����ڽ���ǰreturn�˻��쳣�ˣ���ͨ���������ҽ���
	CSRWLock*	m_pCSRWLock;

	bool		m_bEnterState;	// true  ��ʾ m_pCSRWLock ���� enter ״̬��
								// false ��ʾ m_pCSRWLock ���� leave ״̬
};

///////////////////////////////////////////////////////////////////////////////////

// �̶߳��ػ�
class __declspec(dllexport) CThreadGuardRead : public CThreadGuardEx
{
public:
	CThreadGuardRead(CSRWLock* p);
	~CThreadGuardRead(void);

//private:
public:
	// ����ؼ������
	virtual void enter();

public:
	// �뿪�ؼ������
	virtual void leave();
};

///////////////////////////////////////////////////////////////////////////////////

// �߳�д�ػ�
class __declspec(dllexport) CThreadGuardWrite : public CThreadGuardEx
{
public:
	CThreadGuardWrite(CSRWLock* p);
	~CThreadGuardWrite(void);

public:
	// ����ؼ������
	virtual void enter();

public:
	// �뿪�ؼ������
	virtual void leave();
};

#endif

/***********************************************
Name��SIX_Thread
Desc��PThread��ƽ̨������ʹ��WinThread
Auth��Cool.Cat@2013-04-16
***********************************************/
#pragma once

#include <SIX_Typedef.h>
#include <pthread.h>

typedef void* (*tc_thread_func)(void*);

class SIX_Thread{
public:
	SIX_Thread();
	~SIX_Thread();
public:
	void SetJoinabled(bool joinabled);
	bool GetJoinabled();

	bool GetRunning();

	int BeginThread(void *pThis,tc_thread_func pFunc,int attr=PTHREAD_CREATE_JOINABLE);
	void EndThread();

	const unsigned int GetThreadID();
private:
	// �̱߳�ʶ��
	pthread_t m_pid;
	// �߳�����
	pthread_attr_t m_attr;
	// �Ƿ��ԷǷ�����ʽ����
	bool m_IsJoinabled;
};
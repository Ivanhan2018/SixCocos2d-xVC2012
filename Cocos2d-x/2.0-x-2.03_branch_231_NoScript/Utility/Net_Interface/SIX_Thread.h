/***********************************************
Name：SIX_Thread
Desc：PThread跨平台，不再使用WinThread
Auth：Cool.Cat@2013-04-16
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
	// 线程标识符
	pthread_t m_pid;
	// 线程属性
	pthread_attr_t m_attr;
	// 是否以非分离形式运行
	bool m_IsJoinabled;
};
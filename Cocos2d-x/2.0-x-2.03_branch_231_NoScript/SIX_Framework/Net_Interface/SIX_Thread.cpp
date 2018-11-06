#include "SIX_Thread.h"

SIX_Thread::SIX_Thread()
{
	SetJoinabled(false);
#ifdef WIN32
	m_attr = 0;
#endif
}

SIX_Thread::~SIX_Thread()
{
	EndThread();
}

void SIX_Thread::SetJoinabled(bool joinabled)
{
	m_IsJoinabled = joinabled;
}

bool SIX_Thread::GetJoinabled()
{
	return m_IsJoinabled;
}

bool SIX_Thread::GetRunning()
{
	// 非分离
	if (GetJoinabled())
	{
		// 检测线程是否活动(阻塞)
		// 0			=	线程仍然活动
		// ESRCH(3)		=	线程不存在 或 已经退出
		// EINVAL(22)	=	信号不合法
		int ErrorID = pthread_kill(m_pid,0);
		if (ErrorID!=0)
		{
			SIXLog("pthread_kill.Tid[0x%08X].ErrorID[%d]",GetThreadID(),ErrorID);
			return false;
		}
	}
	// 分离
	else
	{
	
	}
	return true;
}

int SIX_Thread::BeginThread(void *pThis,tc_thread_func pFunc,int attr)
{
#ifndef WIN32
	int rc = 0;
#endif
	int ErrorID = 0;
	int retv = 0;
	if (!pFunc)
	{
		retv = 1;
		goto clean;
	}

	if (attr!=PTHREAD_CREATE_JOINABLE && attr!=PTHREAD_CREATE_DETACHED)
	{
		retv = 2;
		goto clean;
	}

#ifndef WIN32
	sigset_t signal_mask;
	sigemptyset (&signal_mask);
	sigaddset (&signal_mask, SIGPIPE);
	rc = pthread_sigmask (SIG_BLOCK, &signal_mask, 0);
	if (rc != 0) {
		SIXLog("*** block sigpipe error ***");
	}
#endif

	// PTHREAD_CREATE_JOINABLE = 非线程分离，不必Sleep()
	if (attr==PTHREAD_CREATE_JOINABLE)
	{
		SetJoinabled(true);

		ErrorID = pthread_create(&m_pid,0,(tc_thread_func)pFunc,pThis);
		if (ErrorID!=0)
		{
			SIXLog("pthread_create.Error[%d]",ErrorID);
			retv = 5;
			goto clean;
		}
	}
	// PTHREAD_CREATE_DETACHED = 线程分离，则必须Sleep()
	else
	{
		SetJoinabled(false);

		ErrorID = pthread_attr_init(&m_attr);
		if (ErrorID!=0)
		{
			SIXLog("pthread_attr_init.Error[%d]",ErrorID);
			retv = 3;
			goto clean;
		}

		ErrorID = pthread_attr_setdetachstate(&m_attr,attr);
		if (ErrorID!=0)
		{
			SIXLog("pthread_attr_setdetachstate.Error[%d]",ErrorID);
			retv = 4;
			goto clean;
		}

		ErrorID = pthread_create(&m_pid,&m_attr,(tc_thread_func)pFunc,pThis);
		if (ErrorID!=0)
		{
			SIXLog("pthread_create.Error[%d]",ErrorID);
			retv = 5;
			goto clean;
		}

		ErrorID = pthread_attr_destroy(&m_attr);
		if (ErrorID!=0)
		{
			SIXLog("pthread_attr_destroy.Error[%d]",ErrorID);
			retv = 6;
			goto clean;
		}
	}
clean:
	return retv;
}

void SIX_Thread::EndThread()
{
	SIXLog("EndThread.Tid[0x%08X].Begin",GetThreadID());
	// 只有非分离状态才能join
	if (GetJoinabled())
	{
		// 获取
		int status=0;
		int ErrorID = pthread_join(m_pid,(void**)&status);
		if (ErrorID!=0)
		{
			SIXLog("pthread_join.Error[%d]",ErrorID);
		}
		else
		{
			SIXLog("pthread_join.Done.Status[%d]",status);
		}
	}
	// 如果是分离状态
	else
	{
	}
	SIXLog("EndThread.Tid[0x%08X].End",GetThreadID());
}

const unsigned int SIX_Thread::GetThreadID()
{
#ifdef WIN32
	return (const unsigned int)(m_pid.p);
#else
	return (const unsigned int)(m_pid);
#endif
}
#include "stdafx.h"
#include "SingleThread.h"
#include <crtdbg.h>
#include <process.h>
#include <windows.h>

SingleThread::SingleThread() : handle_(0)
{
}

SingleThread::~SingleThread()
{
	Stop();
}

bool SingleThread::Start()
{
	if (this->handle_) return false;

	unsigned int tid = 0;
	this->handle_ = (unsigned int)::_beginthreadex(0, 0, 
		this->_Entry, (void *)this, 0, &tid);
	
	return this->handle_ != 0;
}

void SingleThread::Stop()
{
	if (!this->handle_) return ;

	HANDLE tmp = (HANDLE)this->handle_;
	::WaitForSingleObject(tmp, INFINITE);
}

bool SingleThread::IsRun() const
{
	return this->handle_ != 0;
}

unsigned int __stdcall SingleThread::_Entry(void * ptr)
{
	SingleThread * task = (SingleThread *)ptr;
	_ASSERT(task);

	task->Execute();
	::CloseHandle((HANDLE)task->handle_);
	task->handle_ = 0;
	return 0;
}

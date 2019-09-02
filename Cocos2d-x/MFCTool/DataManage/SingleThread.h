#ifndef __INCLUDE_SINGLE_THREAD_H__
#define __INCLUDE_SINGLE_THREAD_H__

class SingleThread  
{
public:
	SingleThread();
	virtual ~SingleThread();

	bool Start();
	void Stop();
	
	bool IsRun() const;

protected:
    static unsigned int __stdcall _Entry(void *);
    virtual void Execute() = 0;

protected:
	bool run_;
	unsigned int handle_;
};

#endif // __INCLUDE_SINGLE_THREAD_H__

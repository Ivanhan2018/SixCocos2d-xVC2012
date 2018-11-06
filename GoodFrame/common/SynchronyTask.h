/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   22:56
	filename: 	c:\GoodFrame\MemPoolTest\MemPoolTest\SynchronyTask.h
	file path:	c:\GoodFrame\MemPoolTest\MemPoolTest
	file base:	SynchronyTask
	file ext:	h
	author:		hgj
	
	purpose:	同步任务
*********************************************************************/

#ifndef SYNCHRONY_TASK_H
#define SYNCHRONY_TASK_H


#include "./CoreHead.h"
#include "./MemBlockPool.h"

// 用信标推送多线程的消息，效率：500次/ms，内存占用极低，CPU占用极低
// 用 Event 推送多线程的消息，效率：300次/ms，内存占用高，CPU占用高

// 同步任务的接收器 
class __declspec(dllexport) CSynchronyTaskListener
{
public:

	/* --------------------------------------------------------------------------
	函数说明：消费任务
	传入参数：
		iMessageType	消息类型
		iMainCode		主消息码
		iAssistantCode	辅助消息码
		pBodyData		包体数据
		iBodyDataLen	包体数据的长度
	--------------------------------------------------------------------------*/
	virtual int OnConsumeTask(int iMessageType, int iMainCode, int iAssistantCode, const BYTE* pBodyData, int iBodyDataLen) = 0;
};

// 同步任务，发射器。put 时是拷贝形参的
class __declspec(dllexport) CSynchronyTask
{
public:
	CSynchronyTask(void);
	~CSynchronyTask(void);

	enum{ EVENT_NUMBER = 2, };	// 事件总数量

	enum
	{
		EVENT_MESSAGE = 0,
		EVENT_STOP = 1,
	};	

	enum
	{
		STATE_NO = 0,		// 无状态
		STATE_START = 1,	// 已开始
		STATE_STOP = 2,		// 已结束
	};

	enum {	MAX_THREAD_NUM = 30,	// 最大的线程数量
		 };

	enum{	MAX_SEMAPHORE_NUMBER=1024*1024,	// 最大的信标数量
		};

	enum{
			//TERMINATE_CLOSE_THREAD_TIME = 15*1000, //	标准值，强制关闭线程的时间，以 ms 为单位
			TERMINATE_CLOSE_THREAD_TIME = 10*1000, //	测试值记得恢复成标准值，强制关闭线程的时间，以 ms 为单位
		};

public:

	// 设置投递消息的模块地址
	void set_listen_module(CSynchronyTaskListener*	pITask);

	// 设置消费线程的数量，即推送消息线程的数量
	void set_thread_num(int iNum=1);

	// 获得推送消息线程的数量
	int get_thread_num();

	/* --------------------------------------------------------------------------
	函数说明：开始	
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	m_pITask 未付值，用 set_listen_module 函数付值
			20	m_iMessageLen 长度不应该是 0，用 set_message_len 函数设置消息的长度
			40  起动线程池失败
	--------------------------------------------------------------------------*/
	int start();

	// 停止
	int stop();

	/* --------------------------------------------------------------------------
	函数说明：添加任务消息
	传入参数：
		iMessageType	消息类型
		iMainCode		主消息码
		iAssistantCode	辅助消息码
		pBodyData		包体数据
		iBodyDataLen	包体数据的长度
	返回值：
		成功则返回 0 ；
		失败返回 错误码，如下：
			10  TPM_CORE_EXIT 状态
			20	消息超长了，可以用 set_message_len 将长度设置大一点
			30	内存出池失败
	--------------------------------------------------------------------------*/
	int put(int iMessageType, int iMainCode=0, int iAssistantCode=0, const BYTE* pData=0, int iDataLen=0);

	// 设置消息的长度
	void set_message_len(int iMessageLen);

	// 获得消息的长度
	int get_message_len();

	// 设置池内初始元素的数量
	void set_init_block_count(int nInitBlkCount);

	// 设置池内元素的上限值
	void set_max_block_count(int nMaxBlkCount);

	// 设置警戒线的值，注意：本函数与 set_init_block_count 同时应用时要放在它后面
	void set_element_alert(int iElementAlert=CMemBlockPool::DEF_INIT_COUNT*100);

	// 设置到达警戒线的值时的睡眠时间，以ms为单位
	void set_alert_sleep_time(int iAlertSleepTime=20);

	// 获得队列的状态，参考 TPM_CORE_NORMAL
	long get_deque_state();

	// 设置队列的状态，参考 TPM_CORE_NORMAL
	void set_deque_state(long lDequeState);

	// 使用 Event 处理多线程消息
	int handle_task_msg_Event();

	// 使用 Semaphore 处理多线程消息
	int handle_task_msg_semaphore();

private:
	// 消费者线程，消费任务消息
	static unsigned __stdcall  theads_consume_task(void* pParam);	

	// 清空m_dequeMsg 任务消息双向队列
	int clear_deque_msg();

public:
	ULONGLONG timeStart;	
	ULONGLONG timeEnd;
	ULONGLONG timeSpace;	 
	ULONGLONG lPutCount;	// put 函数加入的任务消息数量

private:
	HANDLE		 m_hThreads[MAX_THREAD_NUM];
	unsigned int m_dwThreadsID[MAX_THREAD_NUM];
	int          m_iThreadNum;					// 线程的数量

	HANDLE		 m_hThread;
	unsigned int m_dwThreadID;

	HANDLE	m_hEvent[EVENT_NUMBER];
	HANDLE& m_hSemaphore ;	// 信标对象句柄
	HANDLE& m_hStop;		// 结束

	#if USE_SRWLock
		CSRWLock			m_lock;	// 针对 m_dequeMsg 的锁
	#else
		CCriticalSpection	m_lock;	
	#endif

	deque<CMemBlock*>	m_dequeMsg;		// 任务消息双向队列，每个CMemBlock*元素就是一个任务消息（其实就是指向 m_pMsgPool 内的元素）

	CSynchronyTaskListener*	m_pITask;	// 同步任务，这是发射器，由 OnConsumeTask 函数接收

	int m_iState;	// 状态

	CMemBlockPool*	m_pMsgPool;			// 任务的具体内容
										// 在内部 New 出 CMemBlockPool 实例
	int m_iMessageLen;	// 消息的长度

	int volatile	m_nInitElementCount;	// 池内初始元素的数量
	int	volatile	m_nMaxElementCount;		// 池内元素的上限值

	int				m_iElementAlert;		// 池内元素的警戒线，大于等于此值时 put 会睡 m_iAlertSleepTime ms
	int				m_iAlertSleepTime;		// 到了警戒线的值时的睡眠时间，以ms为单位

	volatile long   m_lDequeState;	// 队列的状态，参考 TPM_CORE_NORMAL

	BOOL			m_bRunStop;		// 已经执行 stop 函数了
};

#endif
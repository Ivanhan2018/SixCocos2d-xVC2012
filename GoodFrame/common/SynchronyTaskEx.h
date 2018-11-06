/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   22:56
	filename: 	c:\GoodFrame\MemPoolTest\MemPoolTest\SynchronyTaskEx.h
	file path:	c:\GoodFrame\MemPoolTest\MemPoolTest
	file base:	SynchronyTaskEx
	file ext:	h
	author:		hgj
	
	purpose:	同步任务扩展，针对 CMemBlock*& 
*********************************************************************/

#ifndef SYNCHRONY_TASK_EX_H
#define SYNCHRONY_TASK_EX_H


#include "./CoreHead.h"
#include "./MemBlockPool.h"

// 用信标推送多线程的消息，无负荷的情况下效率：950次/ms，内存占用极低，CPU占用极低
// 不再去测试 Event 推送多线程的消息了

struct TASK_THREAD_PARAM;	// 任务线程参数

// 同步任务扩展的接收器，针对 CMemBlock*& 
class __declspec(dllexport) CSynchronyTaskExListener
{
public:

	CSynchronyTaskExListener()
	{
		m_lReceiveCount = 0;
	}

	/* --------------------------------------------------------------------------
	函数说明：消费任务
	传入参数：
		pMemBlock	任务消息
	传出参数
	    pMemBlock	任务消息
	--------------------------------------------------------------------------*/
	virtual int OnConsumeTask(CMemBlock*& pMemBlock) = 0;

	volatile long long m_lReceiveCount;	// 实收总和
};

// 同步任务，发射器。put 时是拷贝形参的
class __declspec(dllexport) CSynchronyTaskEx
{
public:
	CSynchronyTaskEx(void);
	~CSynchronyTaskEx(void);

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

	enum{	
			MAX_SEMAPHORE_NUMBER=100*1024,	// 标准值，最大的信标数量
			//MAX_SEMAPHORE_NUMBER=10,	// 测试用，最大的信标数量
		};

	enum{
			TERMINATE_CLOSE_THREAD_TIME = 15*1000, //	标准值，强制关闭线程的时间，以 ms 为单位
			//TERMINATE_CLOSE_THREAD_TIME = 10*1000, //	测试值记得恢复成标准值，强制关闭线程的时间，以 ms 为单位
		};

	enum{	IDLE_SPIN_UP_LIMIT =   5,	// 空转次数的上限
			IDLE_SPIN_SLEEP_TIME = 1,	// 空转睡眠时间，以 ms 为单位
		}; 
public:

	// 设置投递消息的模块地址
	void set_listen_module(CSynchronyTaskExListener*	pITask);

	// 设置消费线程的数量，即推送消息线程的数量
	void set_thread_num(int iNum=1);

	// 获得推送消息线程的数量
	int get_thread_num();

	// 设置消息池
	void set_mem_block_pool(CMemBlockPool* pMsgPool);

	// 获得消息池
	CMemBlockPool* get_mem_block_pool();

	/* --------------------------------------------------------------------------
	函数说明：开始	
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	m_pITask 未付值，用 set_listen_module 函数付值
			20	m_iMessageLen 长度不应该是 0，用 set_message_len 函数设置消息的长度
			30  m_pMsgPool 为空
			40  起动线程池失败
	--------------------------------------------------------------------------*/
	int start();

	// 停止
	int stop();

	/* --------------------------------------------------------------------------
	函数说明：添加任务消息
	传入参数：
		pMemBlock	任务消息
		bIsFront	TRUE 表示加到双向队列的头部，FALSE 表示加到双向队列的尾部
	传出参数：
		pMemBlock	任务消息
	返回值：
		成功则返回 0 ；
		失败返回 错误码，如下：
			10  TPM_CORE_EXIT 状态
			20	消息超长了，可以用 set_message_len 将长度设置大一点
			30	内存出池失败
	--------------------------------------------------------------------------*/
	int put(CMemBlock*& pMemBlock, BOOL bIsFront=FALSE);

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

	int get_deque_count();

	// 使用 Event 处理多线程消息
	int handle_task_msg_Event();

	// 使用 Semaphore 处理多线程消息
	int handle_task_msg_semaphore(TASK_THREAD_PARAM* pParam);

private:
	// 消费者线程，消费任务消息
	static unsigned __stdcall  theads_consume_task(void* pParam);	

	// 清空m_dequeMsg 任务消息双向队列
	int clear_deque_msg();

public:
	ULONGLONG timeStart;	
	ULONGLONG timeEnd;
	ULONGLONG timeSpace;	 

	volatile long long m_lPutCount;		// put 出去的总和

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

	CSynchronyTaskExListener*	m_pITask;	// 同步任务，这是发射器，由 OnConsumeTask 函数接收

	int m_iState;	// 状态

	CMemBlockPool*	m_pMsgPool;		// 任务的具体内容，只能由外部传入指针，不能在内部 new 

	int m_iMessageLen;	// 消息的长度

	int volatile	m_nInitElementCount;	// 池内初始元素的数量
	int	volatile	m_nMaxElementCount;		// 池内元素的上限值

	int				m_iElementAlert;		// 池内元素的警戒线，大于等于此值时 put 会睡 m_iAlertSleepTime ms
	int				m_iAlertSleepTime;		// 到了警戒线的值时的睡眠时间，以ms为单位

	volatile long   m_lDequeState;	// 队列的状态，参考 TPM_CORE_NORMAL

	BOOL			m_bRunStop;		// 已经执行 stop 函数了

	bool	m_bChannelBindThread;    // true  表示通道号绑定线程，即一个通道号的数据只能在一个线程里执行，从而保证了此通道号内先到的数据执行完毕啦，才会去执行后到的数据。
									 // false 表示线程与通道号是随机对应的，即一个通道号的数据可以在多个线程里执行，无法保证此通道号内数据的先后顺序，会出见先到的数据还在执行，后到的数据已经执行完毕啦

};

struct TASK_THREAD_PARAM	// 任务线程参数
{
	TASK_THREAD_PARAM()
	{
		pThis = NULL;
		iThreadNo = 0;
	}

	CSynchronyTaskEx* pThis;
	int iThreadNo;	// 线程编号
};

#endif
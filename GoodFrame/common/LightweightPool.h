/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:45
	filename: 	C:\GoodFrame\common\LightweightPool.h
	file path:	C:\GoodFrame\common
	file base:	LightweightPool
	file ext:	h
	author:		侯国江
	
	purpose:	很轻的、针对任何结构的池。安全、高效、方便。
*********************************************************************/


#ifndef LIGHTWEIGHT_POOL_H
#define LIGHTWEIGHT_POOL_H

#define USE_ThreadGuardEx 1 // 1表示使用 CThreadGuardEx，好处是效率高，坏处是不知是否稳定。效率：release、多线程下每毫秒 9654 次
						    // 0表示使用 CThreadGuard，好处是支持嵌套而且非常稳定，坏处是效率低。效率：release、多线程下每毫秒 1675 次，与 CThreadGuardEx 的差距是巨大的
#if USE_ThreadGuardEx
	#include "./ThreadGuardEx.h"
#else
	#include "./ThreadGuard.h"
#endif

#include <deque>
using std::deque ;

template<class T> 
class __declspec(dllexport) CLightweightPool
{
public:
	enum 
	{ 
		DEF_INIT_COUNT	=   256,	// 池的初始元素数量
		DEF_MAX_COUNT	= 25600,	// 池内元素的上限值
	};

	enum { AUTO_SHRINK_SERVICEPOOL = 300, // 5 分钟
		 };  

public:
	CLightweightPool(const char* pszPoolName, int nInitElementCount=DEF_INIT_COUNT, int nMaxElementCount=DEF_MAX_COUNT);
	~CLightweightPool(void);

public:

	int Test(int** pp);

	// 设置池内初始元素的数量
	void set_init_block_count(int nInitBlkCount);

	// 设置池内元素的上限值
	void set_max_block_count(int nMaxBlkCount);

	// 设置扩展失败次数
	void set_expand_fail_times(int iExpandFailTimes);

	// 设置扩展失败时的睡眠时间，以 ms 为单位
	void set_expand_fail_sleep_time(int iExpandFailSleepTime);

	// 使用定时器自动收缩池，定时器由别的类提供，很重要
	int use_timer_shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);

	BOOL	init();		// 初始化
	BOOL	uninit();	

	// 出池
	BOOL retrieve(T** ppT, BOOL bIsWait = TRUE);

	// 归池
	BOOL recycle(T* pT);

	// 获得池内当前元素的数量
	int get_current_element_count();

	// 扩展池的尺寸
	int expand_pool(int nCount, BOOL bLimitExpandLen = TRUE);		

	// 收缩池的尺寸
	int	 shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);	

	// 获得出池的数量
	LONGLONG get_retrieve_count();

	// 获得归池的数量
	LONGLONG get_recycle_count();	

private:

	deque<T*>	m_stack;	// 池

	#if USE_ThreadGuardEx
		CSRWLock			m_lock;
	#else
		CCriticalSpection	m_lock;	
	#endif
					
	char			m_szPoolName[128];

	float			m_fExpandParam;	// 扩展系数，收缩时只收至初始值乘以扩充系数之处

	int volatile	m_nInitElementCount;	// 池内初始元素的数量
	int	volatile	m_nMaxElementCount;		// 池内元素的上限值

	LONGLONG volatile m_lRetrieveCount;	// 出池的数量
	LONGLONG volatile m_lRecycleCount;	// 归池的数量

	long volatile	m_nAfterExpandOrShrinkCount;	// 池的元素数量，主要是扩展或收缩池后的数量，当消息归池或出池时并不影响它

	int		m_nExpandStep;			// 扩展步长，池内无元素时需要扩展的数量
	int		m_lPeriod;				// 定时收缩的时间间隔，以 ms 为单位

	int		m_iExpandFailTimes;		// 扩展失败次数
	int		m_iExpandFailSleepTime;	// 扩展失败时的睡眠时间，以 ms 为单位
};

///////////////////////////////////////////////////////////////////////////

template<class T> 
CLightweightPool<T>::CLightweightPool(const char* pszPoolName, int nInitElementCount, int nMaxElementCount)
{
	memset(m_szPoolName, 0, sizeof(m_szPoolName)); 
	_snprintf(m_szPoolName, sizeof(m_szPoolName)-1, "%s", pszPoolName);

	m_nInitElementCount = nInitElementCount;	// 池的初始元素数量
	m_nMaxElementCount = nMaxElementCount;		// 池内元素的上限值

	m_nAfterExpandOrShrinkCount = 0;

	if(m_nInitElementCount>=64)
		m_nExpandStep = m_nInitElementCount/10;
	else
		m_nExpandStep = m_nInitElementCount;

	m_lPeriod = 1000;	// 定时器每秒响应一次，但不一定收缩池，以 ms 为单位

	m_fExpandParam = 1.25;	// 扩展系数，收缩时只收至初始值乘以扩充系数之处

	m_iExpandFailTimes = 10;	// 扩展失败次数
	m_iExpandFailSleepTime = 1000;	// 扩展失败时的睡眠时间，以 ms 为单位

	m_lRetrieveCount = 0;	// 出池的数量
	m_lRecycleCount = 0;	// 归池的数量
}


template<class T> 
CLightweightPool<T>::~CLightweightPool(void)
{
	uninit();
}

template<typename T>
int CLightweightPool<T>::Test(int** pp)
{
	return 0;
}

// 设置池内初始元素的数量
template<typename T>
void CLightweightPool<T>::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
}

// 设置池内元素的上限值
template<typename T>
void CLightweightPool<T>::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// 设置扩展失败次数
template<typename T>
void CLightweightPool<T>::set_expand_fail_times(int iExpandFailTimes)
{
	m_iExpandFailTimes = iExpandFailTimes;		
}

// 设置扩展失败时的睡眠时间，以 ms 为单位
template<typename T>
void CLightweightPool<T>::set_expand_fail_sleep_time(int iExpandFailSleepTime)
{
	m_iExpandFailSleepTime = iExpandFailSleepTime;	
}

// 初始化
template<class T> 
BOOL CLightweightPool<T>::init()
{
	BOOL bResult = FALSE;

	if ( expand_pool(m_nInitElementCount, FALSE) > 0 )	// 扩展池的尺寸
	{
		bResult = TRUE;
	}

	return bResult;
}

// 结束初始化，与 init() 成对出现
template<class T> 
BOOL CLightweightPool<T>::uninit()
{
	#if USE_ThreadGuardEx
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	size_t	nRemainCount = m_stack.size();

	int iFactCount = 0;	// 实际收缩的数量

	for(int i = 0; i < nRemainCount; i++)
	{
		// 因为已是结束程序了，无需作 T_POOL_IS_DEQUE 的判断
		T* pT = m_stack.back();

		delete pT;

		m_stack.pop_back();
		
		InterlockedDecrement(&m_nAfterExpandOrShrinkCount);

		iFactCount++;
	}

	return (iFactCount == nRemainCount);
}

/* --------------------------------------------------------------------------
函数说明：出池
传入参数：
	bIsWait		如果从池中取消息记录未能成功，等待 1000 毫秒
传出参数：
	ppT		出池的 T 实例
返回值：
	成功则返回 TRUE，否则返回 FALSE 。
--------------------------------------------------------------------------*/
template<class T> 
BOOL CLightweightPool<T>::retrieve(T** ppT, BOOL bIsWait)
{
	#if USE_ThreadGuardEx
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	*ppT = NULL;

	BOOL	bResult = FALSE;
	int		iLoopCount = 0;
	BOOL	bExpand = FALSE;

	T*	pT = NULL;

	do
	{
		if( (m_nAfterExpandOrShrinkCount - (long)(m_stack.size())) < (long)m_nMaxElementCount )
		{
			if(m_stack.size() > 0)
			{
				pT = m_stack.front();
				m_stack.pop_front();  // 从池中将该记录移除，但该记录要传出并使用，所以不能 delete

				*ppT = pT;

				InterlockedIncrement64(&m_lRetrieveCount);

				bResult = TRUE;
			}
			else
			{
				bExpand = ( expand_pool(m_nExpandStep) >0 )? TRUE:FALSE;
			}
		}

		iLoopCount++;

		if((pT == NULL) && bIsWait && !bExpand)  
		{
			if( iLoopCount < m_iExpandFailTimes )	// 扩展失败次数
			{
				Sleep(m_iExpandFailSleepTime);	// 扩展失败时的睡眠时间，以 ms 为单位
			}
			else
			{
				bResult = FALSE;

				char szError[256] = {0};
				_snprintf(szError, sizeof(szError)-1, "%s CLightPool RetrievePool，池中元素已到达 %d 上限，无法再扩展 \n", 
						  m_szPoolName, m_nMaxElementCount);
				printf(szError);
				
				//DebugBreak();	// 设置断点

				break;
			}
		}

	}while((pT == NULL) && (bIsWait || bExpand));  // 出池失败或扩展池失败，继续循环

	return bResult;
}

/* --------------------------------------------------------------------------
 函数说明：归池
 传入参数：
 	pT	一条消息记录
 返回值：
 	成功则返回 TRUE，否则返回 FALSE 。
 --------------------------------------------------------------------------*/
template<class T> 
BOOL CLightweightPool<T>::recycle(T* pT)
{
	#if USE_ThreadGuardEx
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	BOOL	bResult = FALSE;

	if(pT)
	{
		m_stack.push_back(pT);
		
		InterlockedIncrement64(&m_lRecycleCount);

		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}

	return bResult;
}

/* --------------------------------------------------------------------------
函数说明：扩展池的尺寸
传入参数：
	nCount			需要扩展的尺寸
	bLimitExpandLen	控制扩展的长度
返回值：
	实际扩展的尺寸
/--------------------------------------------------------------------------*/
template<class T> 
int CLightweightPool<T>::expand_pool(int nCount, BOOL bLimitExpandLen)
{
	if( nCount <= 0 )
		return 0;

	// 主要是因为  Retrieve 调用 expand_pool 时 CThreadGuardWrite 镶套了而导致死锁
	//#if USE_ThreadGuardEx
	//	CThreadGuardWrite guard(&m_lock);
	//#else
	//	CThreadGuard guard(&m_lock);
	//#endif

	int nExpandCount = 0;

	if(bLimitExpandLen)
	{
		nExpandCount = ( nCount > m_nExpandStep )? m_nExpandStep : nCount;
	}
	else
	{
		nExpandCount = nCount;
	}

	int iFactCount = 0;	// 实际扩展的数量

	for(int i = 0; i < nExpandCount; i++)
	{
		T* pNew = NULL;
		pNew = new T;
		
		if(pNew)
		{
			m_stack.push_back(pNew);

			InterlockedIncrement(&m_nAfterExpandOrShrinkCount);
		}
		else
		{
			char szError[256] = {0};
			_snprintf(szError, sizeof(szError)-1, "expand_pool 函数，pNew = new T 异常 \n");
			printf(szError);

			break;
		}

		iFactCount++;
	}

	return iFactCount;
}

/* --------------------------------------------------------------------------
函数说明：收缩池的尺寸
传入参数：
	nAtLessShrinkCount	至少要收缩的数目
	fShrinkParam 收缩系数
返回值：
	实际收缩的尺寸
--------------------------------------------------------------------------*/
template<class T> 
int	 CLightweightPool<T>::shrink_pool(int nAtLessShrinkCount, float fShrinkParam)
{
	if( fShrinkParam <= 0 )
		return 0;

	#if USE_ThreadGuardEx
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	size_t	nRemainCount = m_stack.size();

	int nShrinkCount = (int)nRemainCount - m_nInitElementCount;
	
	if( nShrinkCount <= 0 )
		return 0;

	if( nShrinkCount > nAtLessShrinkCount )
	{
		nShrinkCount = (int)(nShrinkCount * fShrinkParam);

		if( nShrinkCount < nAtLessShrinkCount )
			nShrinkCount = nAtLessShrinkCount;
	}

	int iFactCount = 0;	// 实际收缩的数量

	for(int i = 0; i < nShrinkCount; i++)
	{
		T* pT = m_stack.front();
		m_stack.pop_front();

		delete pT;
		
		InterlockedDecrement(&m_nAfterExpandOrShrinkCount);

		iFactCount++;
	}

	return iFactCount;
}

/* --------------------------------------------------------------------------
函数说明：使用定时器自动收缩池，定时器由别的类提供
传入参数：
	nAtLessShrinkCount	至少要收缩的数目
	fShrinkParam 收缩系数
返回值：
	实际收缩的尺寸
--------------------------------------------------------------------------*/
template<class T> 
int CLightweightPool<T>::use_timer_shrink_pool(int nAtLessShrinkCount, float fShrinkParam)
{
	return shrink_pool(nAtLessShrinkCount, fShrinkParam);
}

template<class T> 
int CLightweightPool<T>::get_current_element_count()
{
	#if USE_ThreadGuardEx
		CThreadGuardRead guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif
	
	return static_cast<int>(m_stack.size());
}

// 获得出池的数量
template<class T> 
LONGLONG CLightweightPool<T>::get_retrieve_count()
{
	return m_lRetrieveCount;
}

// 获得归池的数量
template<class T> 
LONGLONG CLightweightPool<T>::get_recycle_count()
{
	return m_lRecycleCount;
}

#endif
/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:45
	filename: 	C:\GoodFrame\common\LightweightPool.h
	file path:	C:\GoodFrame\common
	file base:	LightweightPool
	file ext:	h
	author:		�����
	
	purpose:	����ġ�����κνṹ�ĳء���ȫ����Ч�����㡣
*********************************************************************/


#ifndef LIGHTWEIGHT_POOL_H
#define LIGHTWEIGHT_POOL_H

#define USE_ThreadGuardEx 1 // 1��ʾʹ�� CThreadGuardEx���ô���Ч�ʸߣ������ǲ�֪�Ƿ��ȶ���Ч�ʣ�release�����߳���ÿ���� 9654 ��
						    // 0��ʾʹ�� CThreadGuard���ô���֧��Ƕ�׶��ҷǳ��ȶ���������Ч�ʵ͡�Ч�ʣ�release�����߳���ÿ���� 1675 �Σ��� CThreadGuardEx �Ĳ���Ǿ޴��
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
		DEF_INIT_COUNT	=   256,	// �صĳ�ʼԪ������
		DEF_MAX_COUNT	= 25600,	// ����Ԫ�ص�����ֵ
	};

	enum { AUTO_SHRINK_SERVICEPOOL = 300, // 5 ����
		 };  

public:
	CLightweightPool(const char* pszPoolName, int nInitElementCount=DEF_INIT_COUNT, int nMaxElementCount=DEF_MAX_COUNT);
	~CLightweightPool(void);

public:

	int Test(int** pp);

	// ���ó��ڳ�ʼԪ�ص�����
	void set_init_block_count(int nInitBlkCount);

	// ���ó���Ԫ�ص�����ֵ
	void set_max_block_count(int nMaxBlkCount);

	// ������չʧ�ܴ���
	void set_expand_fail_times(int iExpandFailTimes);

	// ������չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
	void set_expand_fail_sleep_time(int iExpandFailSleepTime);

	// ʹ�ö�ʱ���Զ������أ���ʱ���ɱ�����ṩ������Ҫ
	int use_timer_shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);

	BOOL	init();		// ��ʼ��
	BOOL	uninit();	

	// ����
	BOOL retrieve(T** ppT, BOOL bIsWait = TRUE);

	// ���
	BOOL recycle(T* pT);

	// ��ó��ڵ�ǰԪ�ص�����
	int get_current_element_count();

	// ��չ�صĳߴ�
	int expand_pool(int nCount, BOOL bLimitExpandLen = TRUE);		

	// �����صĳߴ�
	int	 shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);	

	// ��ó��ص�����
	LONGLONG get_retrieve_count();

	// ��ù�ص�����
	LONGLONG get_recycle_count();	

private:

	deque<T*>	m_stack;	// ��

	#if USE_ThreadGuardEx
		CSRWLock			m_lock;
	#else
		CCriticalSpection	m_lock;	
	#endif
					
	char			m_szPoolName[128];

	float			m_fExpandParam;	// ��չϵ��������ʱֻ������ʼֵ��������ϵ��֮��

	int volatile	m_nInitElementCount;	// ���ڳ�ʼԪ�ص�����
	int	volatile	m_nMaxElementCount;		// ����Ԫ�ص�����ֵ

	LONGLONG volatile m_lRetrieveCount;	// ���ص�����
	LONGLONG volatile m_lRecycleCount;	// ��ص�����

	long volatile	m_nAfterExpandOrShrinkCount;	// �ص�Ԫ����������Ҫ����չ�������غ������������Ϣ��ػ����ʱ����Ӱ����

	int		m_nExpandStep;			// ��չ������������Ԫ��ʱ��Ҫ��չ������
	int		m_lPeriod;				// ��ʱ������ʱ�������� ms Ϊ��λ

	int		m_iExpandFailTimes;		// ��չʧ�ܴ���
	int		m_iExpandFailSleepTime;	// ��չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
};

///////////////////////////////////////////////////////////////////////////

template<class T> 
CLightweightPool<T>::CLightweightPool(const char* pszPoolName, int nInitElementCount, int nMaxElementCount)
{
	memset(m_szPoolName, 0, sizeof(m_szPoolName)); 
	_snprintf(m_szPoolName, sizeof(m_szPoolName)-1, "%s", pszPoolName);

	m_nInitElementCount = nInitElementCount;	// �صĳ�ʼԪ������
	m_nMaxElementCount = nMaxElementCount;		// ����Ԫ�ص�����ֵ

	m_nAfterExpandOrShrinkCount = 0;

	if(m_nInitElementCount>=64)
		m_nExpandStep = m_nInitElementCount/10;
	else
		m_nExpandStep = m_nInitElementCount;

	m_lPeriod = 1000;	// ��ʱ��ÿ����Ӧһ�Σ�����һ�������أ��� ms Ϊ��λ

	m_fExpandParam = 1.25;	// ��չϵ��������ʱֻ������ʼֵ��������ϵ��֮��

	m_iExpandFailTimes = 10;	// ��չʧ�ܴ���
	m_iExpandFailSleepTime = 1000;	// ��չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ

	m_lRetrieveCount = 0;	// ���ص�����
	m_lRecycleCount = 0;	// ��ص�����
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

// ���ó��ڳ�ʼԪ�ص�����
template<typename T>
void CLightweightPool<T>::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
}

// ���ó���Ԫ�ص�����ֵ
template<typename T>
void CLightweightPool<T>::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// ������չʧ�ܴ���
template<typename T>
void CLightweightPool<T>::set_expand_fail_times(int iExpandFailTimes)
{
	m_iExpandFailTimes = iExpandFailTimes;		
}

// ������չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
template<typename T>
void CLightweightPool<T>::set_expand_fail_sleep_time(int iExpandFailSleepTime)
{
	m_iExpandFailSleepTime = iExpandFailSleepTime;	
}

// ��ʼ��
template<class T> 
BOOL CLightweightPool<T>::init()
{
	BOOL bResult = FALSE;

	if ( expand_pool(m_nInitElementCount, FALSE) > 0 )	// ��չ�صĳߴ�
	{
		bResult = TRUE;
	}

	return bResult;
}

// ������ʼ������ init() �ɶԳ���
template<class T> 
BOOL CLightweightPool<T>::uninit()
{
	#if USE_ThreadGuardEx
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	size_t	nRemainCount = m_stack.size();

	int iFactCount = 0;	// ʵ������������

	for(int i = 0; i < nRemainCount; i++)
	{
		// ��Ϊ���ǽ��������ˣ������� T_POOL_IS_DEQUE ���ж�
		T* pT = m_stack.back();

		delete pT;

		m_stack.pop_back();
		
		InterlockedDecrement(&m_nAfterExpandOrShrinkCount);

		iFactCount++;
	}

	return (iFactCount == nRemainCount);
}

/* --------------------------------------------------------------------------
����˵��������
���������
	bIsWait		����ӳ���ȡ��Ϣ��¼δ�ܳɹ����ȴ� 1000 ����
����������
	ppT		���ص� T ʵ��
����ֵ��
	�ɹ��򷵻� TRUE�����򷵻� FALSE ��
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
				m_stack.pop_front();  // �ӳ��н��ü�¼�Ƴ������ü�¼Ҫ������ʹ�ã����Բ��� delete

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
			if( iLoopCount < m_iExpandFailTimes )	// ��չʧ�ܴ���
			{
				Sleep(m_iExpandFailSleepTime);	// ��չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
			}
			else
			{
				bResult = FALSE;

				char szError[256] = {0};
				_snprintf(szError, sizeof(szError)-1, "%s CLightPool RetrievePool������Ԫ���ѵ��� %d ���ޣ��޷�����չ \n", 
						  m_szPoolName, m_nMaxElementCount);
				printf(szError);
				
				//DebugBreak();	// ���öϵ�

				break;
			}
		}

	}while((pT == NULL) && (bIsWait || bExpand));  // ����ʧ�ܻ���չ��ʧ�ܣ�����ѭ��

	return bResult;
}

/* --------------------------------------------------------------------------
 ����˵�������
 ���������
 	pT	һ����Ϣ��¼
 ����ֵ��
 	�ɹ��򷵻� TRUE�����򷵻� FALSE ��
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
����˵������չ�صĳߴ�
���������
	nCount			��Ҫ��չ�ĳߴ�
	bLimitExpandLen	������չ�ĳ���
����ֵ��
	ʵ����չ�ĳߴ�
/--------------------------------------------------------------------------*/
template<class T> 
int CLightweightPool<T>::expand_pool(int nCount, BOOL bLimitExpandLen)
{
	if( nCount <= 0 )
		return 0;

	// ��Ҫ����Ϊ  Retrieve ���� expand_pool ʱ CThreadGuardWrite �����˶���������
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

	int iFactCount = 0;	// ʵ����չ������

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
			_snprintf(szError, sizeof(szError)-1, "expand_pool ������pNew = new T �쳣 \n");
			printf(szError);

			break;
		}

		iFactCount++;
	}

	return iFactCount;
}

/* --------------------------------------------------------------------------
����˵���������صĳߴ�
���������
	nAtLessShrinkCount	����Ҫ��������Ŀ
	fShrinkParam ����ϵ��
����ֵ��
	ʵ�������ĳߴ�
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

	int iFactCount = 0;	// ʵ������������

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
����˵����ʹ�ö�ʱ���Զ������أ���ʱ���ɱ�����ṩ
���������
	nAtLessShrinkCount	����Ҫ��������Ŀ
	fShrinkParam ����ϵ��
����ֵ��
	ʵ�������ĳߴ�
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

// ��ó��ص�����
template<class T> 
LONGLONG CLightweightPool<T>::get_retrieve_count()
{
	return m_lRetrieveCount;
}

// ��ù�ص�����
template<class T> 
LONGLONG CLightweightPool<T>::get_recycle_count()
{
	return m_lRecycleCount;
}

#endif
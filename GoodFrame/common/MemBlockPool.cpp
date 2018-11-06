
#include ".\PublicHead.h"
#include ".\MemBlockPool.h"
#include ".\CoreHead.h"

CMemBlockPool::CMemBlockPool(int iMsgBlockSize, int nInitElementCount, int nMaxElementCount)
{
	m_iMsgBlockSize = iMsgBlockSize;	// 消息元素的长度

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

CMemBlockPool::~CMemBlockPool(void)
{
	uninit();
}


int CMemBlockPool::Test(int** pp)
{
	return 0;
}

// 设置池内初始元素的数量
void CMemBlockPool::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
}

// 设置池内元素的上限值
void CMemBlockPool::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// 设置扩展失败次数
void CMemBlockPool::set_expand_fail_times(int iExpandFailTimes)
{
	m_iExpandFailTimes = iExpandFailTimes;		
}

// 设置扩展失败时的睡眠时间，以 ms 为单位
void CMemBlockPool::set_expand_fail_sleep_time(int iExpandFailSleepTime)
{
	m_iExpandFailSleepTime = iExpandFailSleepTime;	
}

// 获得池里内存块的尺寸
int CMemBlockPool::get_mem_block_size()
{
	return m_iMsgBlockSize;
}

// 获得池内初始元素数量
int CMemBlockPool::get_init_element_count()
{
	return m_nInitElementCount;
}

// 初始化
BOOL CMemBlockPool::init()
{
	BOOL bResult = FALSE;

	if ( expand_pool(m_nInitElementCount, FALSE) > 0 )	// 扩展池的尺寸
	{
		bResult = TRUE;
	}

	return bResult;
}

// 结束初始化，与 init() 成对出现
BOOL CMemBlockPool::uninit()
{
	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	size_t	nRemainCount = m_stack.size();

	int iFactCount = 0;	// 实际收缩的数量

	for(int i = 0; i < nRemainCount; i++)
	{
		// 因为已是结束程序了，无需作 T_POOL_IS_DEQUE 的判断
		CMemBlock* pMsgBlock = m_stack.back();

		delete pMsgBlock;

		m_stack.pop_back();
		
		InterlockedDecrement(&m_nAfterExpandOrShrinkCount);

		iFactCount++;
	}

	return (iFactCount == nRemainCount);
}

// 出池
BOOL CMemBlockPool::retrieve(CMemBlock** ppMsgBlock, char* pszTextMark, BOOL bIsWait)
{
	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	*ppMsgBlock = NULL;

	BOOL	bResult = FALSE;
	int		iLoopCount = 0;
	BOOL	bExpand = FALSE;

	CMemBlock*	pMsgBlk = NULL;

	do
	{
		if( (m_nAfterExpandOrShrinkCount - (long)(m_stack.size())) < (long)m_nMaxElementCount )
		{
			if(m_stack.size() > 0)
			{
				pMsgBlk = m_stack.front();
				m_stack.pop_front();  // 从池中将该记录移除，但该记录要传出并使用，所以不能 delete

				pMsgBlk->reset();	// 速度快，说明 memset 是很耗时的

				if(pszTextMark)
				{
					int iLen = min(CMemBlock::TEXT_MARK_LEN-1, lstrlenA(pszTextMark));

					// 设置文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
					pMsgBlk->set_text_mark(pszTextMark, iLen);

					pMsgBlk->m_bInPool = FALSE;	// 在池外
					pMsgBlk->timeOutPool = ::GetTickCount64();	// 出池时间
				}

				*ppMsgBlock = pMsgBlk;

				InterlockedIncrement64 (&m_lRetrieveCount);

				bResult = TRUE;
			}
			else
			{
				bExpand = ( expand_pool(m_nExpandStep, TRUE) >0 )? TRUE:FALSE;
				
			}
		}

		iLoopCount++;

		char szError[256] = {0};

		if((pMsgBlk == NULL) && bIsWait && !bExpand)  
		{
			#if 1
				// 这种睡眠的方式并不能解决问题，坏处是会导致所有的 put 都卡住，好处是几乎不会丢包
				// 实在卡得厉害就加大 nMaxBlkCount 值
				if( iLoopCount < m_iExpandFailTimes )	// 扩展失败次数
				{
					Sleep(m_iExpandFailSleepTime);	// 扩展失败时的睡眠时间，以 ms 为单位
				}
				else
				{
					bResult = FALSE;

					_snprintf(szError, sizeof(szError)-1, "CMemBlockPool 池中元素已到达 %d 上限，\n    无法再扩展,出池的数量 %d 归池的数量 %d \n",
								m_nMaxElementCount,
								m_lRetrieveCount,
								m_lRecycleCount);
					printf(szError);

					break;
				}
			#else
				// 将扩展失败的结果交给应用层，由应用层睡眠解决，但应用层处理会丢包
				_snprintf(szError, sizeof(szError), "CMemBlockPool 池中元素已到达 %d 上限，\n    无法再扩展,出池的数量 %d 归池的数量 %d \n",
							m_nMaxElementCount,
							m_lRetrieveCount,
							m_lRecycleCount);
				printf(szError);

				bResult = FALSE;
				break;
			#endif
		}

	}while((pMsgBlk == NULL) && (bIsWait || bExpand));  // 出池失败或扩展池失败，继续循环

	return bResult;
}

/* --------------------------------------------------------------------------
函数说明：归池
传入参数：
	pMsgBlock	一条消息记录
返回值：
	成功则返回 TRUE，否则返回 FALSE 。
--------------------------------------------------------------------------*/
BOOL CMemBlockPool::recycle(CMemBlock* pMsgBlock)
{
	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	BOOL	bResult = FALSE;

	if(pMsgBlock)
	{
		pMsgBlock->m_bInPool = TRUE;	// 在池内
		pMsgBlock->timeOutPool = 0;	// 出池时间
		pMsgBlock->clear_text_mark();	// 清空文字标识

		m_stack.push_back(pMsgBlock);
		
		InterlockedIncrement64 (&m_lRecycleCount);
		
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
	bLock			扩展的过程中加锁，
返回值：
	实际扩展的尺寸
--------------------------------------------------------------------------*/
int CMemBlockPool::expand_pool(int nCount, BOOL bLimitExpandLen)
{
	if( nCount <= 0 )
		return 0;

	// 主要是因为  Retrieve 调用 expand_pool 时 CThreadGuardWrite 镶套了而导致死锁
	//#if USE_SRWLock
	//	CThreadGuardWrite guard(&m_lock);	// 会死锁
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
		CMemBlock* pNew = NULL;
		pNew = new CMemBlock(m_iMsgBlockSize);
		
		if(pNew)
		{
			pNew->m_bInPool = TRUE;	// 在池内
			m_mapOriginalStub.insert(PAIR_ORIGINAL_STUB(pNew,0));	// 加入原始的存根

			m_stack.push_back(pNew);

			InterlockedIncrement(&m_nAfterExpandOrShrinkCount);
		}
		else
		{
			char szError[256] = {0};
			_snprintf(szError, sizeof(szError)-1, "expand_pool 函数，pNew = new CMemBlock 异常 \n");
			printf(szError);

			break;
		}

		iFactCount++;
	}

	printf("扩充 CMemBlockPool ，扩充数量 %d \n", iFactCount);

	return iFactCount;
}

/* --------------------------------------------------------------------------
函数说明：收缩池的尺寸，也可以启一个线程来进行收缩会更安全
传入参数：
	nAtLessShrinkCount	至少要收缩的数目
	fShrinkParam 收缩系数
返回值：
	实际收缩的尺寸
--------------------------------------------------------------------------*/
int	 CMemBlockPool::shrink_pool(int nAtLessShrinkCount, float fShrinkParam)
{
	if( fShrinkParam <= 0 )
		return 0;

	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	size_t	nRemainCount = m_stack.size();	// 当前池内的元素数数量

	int nShrinkCount = (int)nRemainCount - m_nInitElementCount;	// 差值，即要收缩的数量，
	
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
		CMemBlock* pMsgBlock = m_stack.front();
		m_stack.pop_front();

		{	// 从原始的存根里移除
			MAP_ORIGINAL_STUB::iterator iter =	m_mapOriginalStub.find((CMemBlock*)pMsgBlock);
			if(iter != m_mapOriginalStub.end())	// 找到啦
			{
				m_mapOriginalStub.erase(iter);
			}
			else	// 没找到
			{
				printf("池内的内存块 %d 未找到 \n", (DWORD)pMsgBlock);
			}
		}


		delete pMsgBlock;
		
		InterlockedDecrement(&m_nAfterExpandOrShrinkCount);

		iFactCount++;
	}

	printf("收缩 CMemBlockPool ，收缩数量 %d \n", iFactCount);

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
int CMemBlockPool::use_timer_shrink_pool(int nAtLessShrinkCount, float fShrinkParam)
{
	return shrink_pool(nAtLessShrinkCount, fShrinkParam);
}

 
int CMemBlockPool::get_current_element_count()
{
	#if USE_SRWLock
		CThreadGuardRead guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif
	
	return static_cast<int>(m_stack.size());
}

// 获得出池的数量
long long  CMemBlockPool::get_retrieve_count()
{
	return m_lRetrieveCount;
}

// 获得归池的数量
long long  CMemBlockPool::get_recycle_count()
{
	return m_lRecycleCount;
}

// 重新装填消息头，消息块内的包体内容保持原状不变
int CMemBlockPool::refill_head(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode)
{
	int iRes = 0;

	if(!pMemBlock)
		return 10;	// pMemBlock 是空值

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock 长度太短了

	pHead->lChannelNo = lChannelNo;
	pHead->iMainCode = iMainCode;
	pHead->iSubCode = iSubCode;

	return 0;
}

// 重新装填消息块，通道号、主码、辅助码保持原来的值不变
int CMemBlockPool::refill_content(CMemBlock*& pMemBlock, const BYTE* pBody, int iBodyLen)
{
	int iRes = 0;

	CORE_MSG_HEAD* pMsgHead = NULL;
	iRes = get_core_msg_head(pMemBlock, pMsgHead);

	if(0 != iRes)
	{
		assert(TRUE);
		return 5;
	}

	long long	lChannelNo = pMsgHead->lChannelNo;		// 通道号，服务端专用
	int			iMainCode = pMsgHead->iMainCode;;
	int			iSubCode = pMsgHead->iSubCode;;

	pMemBlock->clear();

	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// 包体内容超出消息块的长度啦

	int iSize = sizeof(CORE_MSG_HEAD);

	// 内容赋值
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	stCoreMsg.RaiseTotalSize(iBodyLen);

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// 包头赋值

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// 包体赋值

	return 0;
}

// 重新装填消息块，通道号保持原来的值不变
int CMemBlockPool::refill_content(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen)
{
	int iRes = 0;

	long long lChannelNo = INVALID_CHANNEL_NO;
	iRes = get_core_msg_channel(pMemBlock, lChannelNo);
	if(0 != iRes)
	{
		assert(TRUE);
		return 5;
	}

	pMemBlock->clear();

	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// 包体内容超出消息块的长度啦

	int iSize = sizeof(CORE_MSG_HEAD);

	// 内容赋值
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	stCoreMsg.RaiseTotalSize(iBodyLen);

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// 包头赋值

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// 包体赋值

	return 0;
}

// 重新装填消息块
int CMemBlockPool::refill_content(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen)
{
	int iRes = 0;

	pMemBlock->clear();

	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// 包体内容超出消息块的长度啦

	int iSize = sizeof(CORE_MSG_HEAD);

	// 内容赋值
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	stCoreMsg.RaiseTotalSize(iBodyLen);

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// 包头赋值

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// 包体赋值

	return 0;
}

// 向消息块追加内容
int CMemBlockPool::append_content(CMemBlock*& pMemBlock, const BYTE* pBody, int iBodyLen)
{
	int iRes = 0;

	if(!pMemBlock)
		return 5;	// 消息块为空

	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// 包体内容超出消息块的长度啦

	int iSize = sizeof(CORE_MSG_HEAD);

	// 追加的内容赋值
	if(pBody && iBodyLen>0)
	{
		CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

		if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
			return 20;	// pMemBlock 长度太短了

		pHead->RaiseTotalSize(iBodyLen);

		iRes = pMemBlock->copy(pBody, iBodyLen);	// 包体赋值
		if(0!=iRes)
			return 40;	// 包头或包体赋值失败
	}

	return 0;
}

// 出池一个主动关闭对端的消息块
int CMemBlockPool::retrieve_with_power_close(CMemBlock*& pMemBlock, char* pszTextMark, BOOL bIsWait)
{
	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// 出池

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// 消息块出池失败
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// 内容赋值
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.set_power_close_peer();

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// 包头赋值

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// 归池
		return 40;	// 包头或包体赋值失败
	}

	return 0;
}

// 出池一个携带错误内容的消息块，主要用于测试
int CMemBlockPool::retrieve_with_error_content(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark, BOOL bIsWait)
{
	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// 包体内容超出消息块的长度啦

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// 出池

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// 消息块出池失败
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// 内容赋值
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.RaiseTotalSize(iBodyLen);

	stCoreMsg.uFlag = 0x123;	// 固意写错

	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// 包头赋值

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// 包体赋值

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// 归池
		return 40;	// 包头或包体赋值失败
	}

	return 0;
}

// 出池一个携带指定内容的消息块
int CMemBlockPool::retrieve_with_content_no_channel(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark, BOOL bIsWait)
{
	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// 包体内容超出消息块的长度啦

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// 出池

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// 消息块出池失败
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// 内容赋值
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.RaiseTotalSize(iBodyLen);

	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// 包头赋值

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// 包体赋值

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// 归池
		return 40;	// 包头或包体赋值失败
	}

	return 0;
}

// 出池一个携带指定内容的消息块
int CMemBlockPool::retrieve_with_content(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark, BOOL bIsWait)
{
	// 获得池里内存块的尺寸
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// 包体内容超出消息块的长度啦

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// 出池

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// 消息块出池失败
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// 内容赋值
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.RaiseTotalSize(iBodyLen);

	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// 包头赋值

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// 包体赋值

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// 归池
		return 40;	// 包头或包体赋值失败
	}

	return 0;
}

// 获得内核消息的真实数据
int CMemBlockPool::get_core_msg_data(CMemBlock* pMemBlock, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen)
{
	pData = NULL;
	*iDataLen = 0;

	if(!pMemBlock)
		return 10;	// pMemBlock 是空值
	
	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();
	CORE_MSG_HEAD* pTmp;

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock 长度太短了

	*iMainCode = pHead->iMainCode;
	*iSubCode = pHead->iSubCode;

	if(pMemBlock->length() == sizeof(CORE_MSG_HEAD))	// 只有头，没有包体
	{
		return 0;
	}

	pTmp = (CORE_MSG_HEAD*)(pHead + 1);
	pData = (BYTE*)pTmp;

	*iDataLen = pHead->iTotalSize - sizeof(CORE_MSG_HEAD);

	return 0;
}

// 获得内核消息的真实数据，服务端专用
int CMemBlockPool::get_core_msg_data(CMemBlock* pMemBlock, long long* lChannelNo, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen)
{
	pData = NULL;
	*iDataLen = 0;

	if(!pMemBlock)
		return 10;	// pMemBlock 是空值

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();
	CORE_MSG_HEAD* pTmp;

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock 长度太短了

	*lChannelNo = pHead->lChannelNo;
	*iMainCode = pHead->iMainCode;
	*iSubCode = pHead->iSubCode;

	if(pMemBlock->length() == sizeof(CORE_MSG_HEAD))	// 只有头，没有包体
	{
		return 0;
	}

	pTmp = (CORE_MSG_HEAD*)(pHead + 1);
	pData = (BYTE*)pTmp;

	*iDataLen = pHead->iTotalSize - sizeof(CORE_MSG_HEAD);

	return 0;
}

// 获得内核消息的头
int CMemBlockPool::get_core_msg_head(CMemBlock* pMemBlock, CORE_MSG_HEAD*& pMsgHead)
{
	if(!pMemBlock)
		return 10;	// pMemBlock 是空值

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock 长度太短了

	pMsgHead = pHead;

	return 0;
}

// 获得内核消息的通道号
int CMemBlockPool::get_core_msg_channel(CMemBlock* pMemBlock, long long& lChannelNo)
{
	if(!pMemBlock)
		return 10;	// pMemBlock 是空值

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();


	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock 长度太短了

	lChannelNo = pHead->lChannelNo;

	return 0;
}

// 获得内核消息头内的参数值
int CMemBlockPool::get_core_head_param(CMemBlock* pMemBlock, TYPE_IN_HEAD typeInHead, int& iVal)
{
	if(!pMemBlock)
		return 10;	// pMemBlock 是空值
	
	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock 长度太短了

	switch(typeInHead)
	{
	case TIH_TOTAL_SIZE:
		iVal = pHead->iTotalSize;	// 整个消息的长度， sizeof(CORE_MSG) +  iBodyLen 
		break;
	case TIH_PEER_IP:
		iVal = pHead->dwPeerIP  ;	// 对端主机的IP
		break;
	case TIH_MAIN_CODE:
		iVal = pHead->iMainCode  ;
		break;
	case TIH_SUB_CODE:
		iVal = pHead->iSubCode  ;
		break;
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：列印未归池（在池外）的元素
传入参数：
	bDisplay		是否列印
	int iDisplayNum	未归池的最大显示数量
传出参数：
	vecOutPool	未归池（在池外）的元素数组
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CMemBlockPool::display_out_pool(BOOL bDisplay, vector<OUT_POOL_ELEMENT>& vecOutPool, int iDisplayNum)
{
	#if USE_SRWLock
		CThreadGuardRead guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	BOOL	bResult = FALSE;
	int		iCount = 0;

	size_t iSize = m_mapOriginalStub.size();
	if(bDisplay && iSize>0)
		printf("列印未归池元素： \n");

	MAP_ORIGINAL_STUB::iterator iter = m_mapOriginalStub.begin();
	for( ; iter!=m_mapOriginalStub.end(); iter++)
	{
		CMemBlock* pMsgBlock = (*iter).first;
		if(pMsgBlock && !pMsgBlock->m_bInPool)	// 池外的元素
		{
			OUT_POOL_ELEMENT tmp;
			tmp.timeOutPool = pMsgBlock->timeOutPool;	// 出池时间
			tmp.timeDisplay = ::GetTickCount64();		// 列印的时间
			pMsgBlock->get_text_mark(tmp.szTextMark, sizeof(tmp.szTextMark)-1);	// 文字标识

			if(bDisplay && iCount<iDisplayNum)
			{
				printf("  %s, %I64d，时差 %I64d，出池时间%I64d，当前时间%I64d \n", 
					    tmp.szTextMark, 
						(long long)pMsgBlock,
						tmp.timeDisplay - tmp.timeOutPool ,
						tmp.timeOutPool ,
						tmp.timeDisplay
					  );
			}

			vecOutPool.push_back(tmp);
			iCount++;
		}
	}

	if(bDisplay)
		printf("  未归池元素总数量：%d \n", iCount);

	return bResult;
}
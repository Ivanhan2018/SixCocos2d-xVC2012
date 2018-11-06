
#include ".\PublicHead.h"
#include ".\MemBlockPool.h"
#include ".\CoreHead.h"

CMemBlockPool::CMemBlockPool(int iMsgBlockSize, int nInitElementCount, int nMaxElementCount)
{
	m_iMsgBlockSize = iMsgBlockSize;	// ��ϢԪ�صĳ���

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

CMemBlockPool::~CMemBlockPool(void)
{
	uninit();
}


int CMemBlockPool::Test(int** pp)
{
	return 0;
}

// ���ó��ڳ�ʼԪ�ص�����
void CMemBlockPool::set_init_block_count(int nInitBlkCount)
{
	m_nInitElementCount = nInitBlkCount;
}

// ���ó���Ԫ�ص�����ֵ
void CMemBlockPool::set_max_block_count(int nMaxBlkCount)
{
	m_nMaxElementCount = nMaxBlkCount;
}

// ������չʧ�ܴ���
void CMemBlockPool::set_expand_fail_times(int iExpandFailTimes)
{
	m_iExpandFailTimes = iExpandFailTimes;		
}

// ������չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
void CMemBlockPool::set_expand_fail_sleep_time(int iExpandFailSleepTime)
{
	m_iExpandFailSleepTime = iExpandFailSleepTime;	
}

// ��ó����ڴ��ĳߴ�
int CMemBlockPool::get_mem_block_size()
{
	return m_iMsgBlockSize;
}

// ��ó��ڳ�ʼԪ������
int CMemBlockPool::get_init_element_count()
{
	return m_nInitElementCount;
}

// ��ʼ��
BOOL CMemBlockPool::init()
{
	BOOL bResult = FALSE;

	if ( expand_pool(m_nInitElementCount, FALSE) > 0 )	// ��չ�صĳߴ�
	{
		bResult = TRUE;
	}

	return bResult;
}

// ������ʼ������ init() �ɶԳ���
BOOL CMemBlockPool::uninit()
{
	#if USE_SRWLock
		CThreadGuardWrite guard(&m_lock);
	#else
		CThreadGuard guard(&m_lock);
	#endif

	size_t	nRemainCount = m_stack.size();

	int iFactCount = 0;	// ʵ������������

	for(int i = 0; i < nRemainCount; i++)
	{
		// ��Ϊ���ǽ��������ˣ������� T_POOL_IS_DEQUE ���ж�
		CMemBlock* pMsgBlock = m_stack.back();

		delete pMsgBlock;

		m_stack.pop_back();
		
		InterlockedDecrement(&m_nAfterExpandOrShrinkCount);

		iFactCount++;
	}

	return (iFactCount == nRemainCount);
}

// ����
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
				m_stack.pop_front();  // �ӳ��н��ü�¼�Ƴ������ü�¼Ҫ������ʹ�ã����Բ��� delete

				pMsgBlk->reset();	// �ٶȿ죬˵�� memset �Ǻܺ�ʱ��

				if(pszTextMark)
				{
					int iLen = min(CMemBlock::TEXT_MARK_LEN-1, lstrlenA(pszTextMark));

					// �������ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
					pMsgBlk->set_text_mark(pszTextMark, iLen);

					pMsgBlk->m_bInPool = FALSE;	// �ڳ���
					pMsgBlk->timeOutPool = ::GetTickCount64();	// ����ʱ��
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
				// ����˯�ߵķ�ʽ�����ܽ�����⣬�����ǻᵼ�����е� put ����ס���ô��Ǽ������ᶪ��
				// ʵ�ڿ��������ͼӴ� nMaxBlkCount ֵ
				if( iLoopCount < m_iExpandFailTimes )	// ��չʧ�ܴ���
				{
					Sleep(m_iExpandFailSleepTime);	// ��չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
				}
				else
				{
					bResult = FALSE;

					_snprintf(szError, sizeof(szError)-1, "CMemBlockPool ����Ԫ���ѵ��� %d ���ޣ�\n    �޷�����չ,���ص����� %d ��ص����� %d \n",
								m_nMaxElementCount,
								m_lRetrieveCount,
								m_lRecycleCount);
					printf(szError);

					break;
				}
			#else
				// ����չʧ�ܵĽ������Ӧ�ò㣬��Ӧ�ò�˯�߽������Ӧ�ò㴦��ᶪ��
				_snprintf(szError, sizeof(szError), "CMemBlockPool ����Ԫ���ѵ��� %d ���ޣ�\n    �޷�����չ,���ص����� %d ��ص����� %d \n",
							m_nMaxElementCount,
							m_lRetrieveCount,
							m_lRecycleCount);
				printf(szError);

				bResult = FALSE;
				break;
			#endif
		}

	}while((pMsgBlk == NULL) && (bIsWait || bExpand));  // ����ʧ�ܻ���չ��ʧ�ܣ�����ѭ��

	return bResult;
}

/* --------------------------------------------------------------------------
����˵�������
���������
	pMsgBlock	һ����Ϣ��¼
����ֵ��
	�ɹ��򷵻� TRUE�����򷵻� FALSE ��
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
		pMsgBlock->m_bInPool = TRUE;	// �ڳ���
		pMsgBlock->timeOutPool = 0;	// ����ʱ��
		pMsgBlock->clear_text_mark();	// ������ֱ�ʶ

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
����˵������չ�صĳߴ�
���������
	nCount			��Ҫ��չ�ĳߴ�
	bLimitExpandLen	������չ�ĳ���
	bLock			��չ�Ĺ����м�����
����ֵ��
	ʵ����չ�ĳߴ�
--------------------------------------------------------------------------*/
int CMemBlockPool::expand_pool(int nCount, BOOL bLimitExpandLen)
{
	if( nCount <= 0 )
		return 0;

	// ��Ҫ����Ϊ  Retrieve ���� expand_pool ʱ CThreadGuardWrite �����˶���������
	//#if USE_SRWLock
	//	CThreadGuardWrite guard(&m_lock);	// ������
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
		CMemBlock* pNew = NULL;
		pNew = new CMemBlock(m_iMsgBlockSize);
		
		if(pNew)
		{
			pNew->m_bInPool = TRUE;	// �ڳ���
			m_mapOriginalStub.insert(PAIR_ORIGINAL_STUB(pNew,0));	// ����ԭʼ�Ĵ��

			m_stack.push_back(pNew);

			InterlockedIncrement(&m_nAfterExpandOrShrinkCount);
		}
		else
		{
			char szError[256] = {0};
			_snprintf(szError, sizeof(szError)-1, "expand_pool ������pNew = new CMemBlock �쳣 \n");
			printf(szError);

			break;
		}

		iFactCount++;
	}

	printf("���� CMemBlockPool ���������� %d \n", iFactCount);

	return iFactCount;
}

/* --------------------------------------------------------------------------
����˵���������صĳߴ磬Ҳ������һ���߳����������������ȫ
���������
	nAtLessShrinkCount	����Ҫ��������Ŀ
	fShrinkParam ����ϵ��
����ֵ��
	ʵ�������ĳߴ�
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

	size_t	nRemainCount = m_stack.size();	// ��ǰ���ڵ�Ԫ��������

	int nShrinkCount = (int)nRemainCount - m_nInitElementCount;	// ��ֵ����Ҫ������������
	
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
		CMemBlock* pMsgBlock = m_stack.front();
		m_stack.pop_front();

		{	// ��ԭʼ�Ĵ�����Ƴ�
			MAP_ORIGINAL_STUB::iterator iter =	m_mapOriginalStub.find((CMemBlock*)pMsgBlock);
			if(iter != m_mapOriginalStub.end())	// �ҵ���
			{
				m_mapOriginalStub.erase(iter);
			}
			else	// û�ҵ�
			{
				printf("���ڵ��ڴ�� %d δ�ҵ� \n", (DWORD)pMsgBlock);
			}
		}


		delete pMsgBlock;
		
		InterlockedDecrement(&m_nAfterExpandOrShrinkCount);

		iFactCount++;
	}

	printf("���� CMemBlockPool ���������� %d \n", iFactCount);

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

// ��ó��ص�����
long long  CMemBlockPool::get_retrieve_count()
{
	return m_lRetrieveCount;
}

// ��ù�ص�����
long long  CMemBlockPool::get_recycle_count()
{
	return m_lRecycleCount;
}

// ����װ����Ϣͷ����Ϣ���ڵİ������ݱ���ԭ״����
int CMemBlockPool::refill_head(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode)
{
	int iRes = 0;

	if(!pMemBlock)
		return 10;	// pMemBlock �ǿ�ֵ

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock ����̫����

	pHead->lChannelNo = lChannelNo;
	pHead->iMainCode = iMainCode;
	pHead->iSubCode = iSubCode;

	return 0;
}

// ����װ����Ϣ�飬ͨ���š����롢�����뱣��ԭ����ֵ����
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

	long long	lChannelNo = pMsgHead->lChannelNo;		// ͨ���ţ������ר��
	int			iMainCode = pMsgHead->iMainCode;;
	int			iSubCode = pMsgHead->iSubCode;;

	pMemBlock->clear();

	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// �������ݳ�����Ϣ��ĳ�����

	int iSize = sizeof(CORE_MSG_HEAD);

	// ���ݸ�ֵ
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	stCoreMsg.RaiseTotalSize(iBodyLen);

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// ��ͷ��ֵ

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// ���帳ֵ

	return 0;
}

// ����װ����Ϣ�飬ͨ���ű���ԭ����ֵ����
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

	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// �������ݳ�����Ϣ��ĳ�����

	int iSize = sizeof(CORE_MSG_HEAD);

	// ���ݸ�ֵ
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	stCoreMsg.RaiseTotalSize(iBodyLen);

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// ��ͷ��ֵ

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// ���帳ֵ

	return 0;
}

// ����װ����Ϣ��
int CMemBlockPool::refill_content(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen)
{
	int iRes = 0;

	pMemBlock->clear();

	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// �������ݳ�����Ϣ��ĳ�����

	int iSize = sizeof(CORE_MSG_HEAD);

	// ���ݸ�ֵ
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	stCoreMsg.RaiseTotalSize(iBodyLen);

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// ��ͷ��ֵ

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// ���帳ֵ

	return 0;
}

// ����Ϣ��׷������
int CMemBlockPool::append_content(CMemBlock*& pMemBlock, const BYTE* pBody, int iBodyLen)
{
	int iRes = 0;

	if(!pMemBlock)
		return 5;	// ��Ϣ��Ϊ��

	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// �������ݳ�����Ϣ��ĳ�����

	int iSize = sizeof(CORE_MSG_HEAD);

	// ׷�ӵ����ݸ�ֵ
	if(pBody && iBodyLen>0)
	{
		CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

		if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
			return 20;	// pMemBlock ����̫����

		pHead->RaiseTotalSize(iBodyLen);

		iRes = pMemBlock->copy(pBody, iBodyLen);	// ���帳ֵ
		if(0!=iRes)
			return 40;	// ��ͷ����帳ֵʧ��
	}

	return 0;
}

// ����һ�������رնԶ˵���Ϣ��
int CMemBlockPool::retrieve_with_power_close(CMemBlock*& pMemBlock, char* pszTextMark, BOOL bIsWait)
{
	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// ����

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// ��Ϣ�����ʧ��
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// ���ݸ�ֵ
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.set_power_close_peer();

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// ��ͷ��ֵ

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// ���
		return 40;	// ��ͷ����帳ֵʧ��
	}

	return 0;
}

// ����һ��Я���������ݵ���Ϣ�飬��Ҫ���ڲ���
int CMemBlockPool::retrieve_with_error_content(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark, BOOL bIsWait)
{
	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// �������ݳ�����Ϣ��ĳ�����

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// ����

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// ��Ϣ�����ʧ��
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// ���ݸ�ֵ
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.RaiseTotalSize(iBodyLen);

	stCoreMsg.uFlag = 0x123;	// ����д��

	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// ��ͷ��ֵ

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// ���帳ֵ

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// ���
		return 40;	// ��ͷ����帳ֵʧ��
	}

	return 0;
}

// ����һ��Я��ָ�����ݵ���Ϣ��
int CMemBlockPool::retrieve_with_content_no_channel(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark, BOOL bIsWait)
{
	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// �������ݳ�����Ϣ��ĳ�����

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// ����

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// ��Ϣ�����ʧ��
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// ���ݸ�ֵ
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.RaiseTotalSize(iBodyLen);

	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// ��ͷ��ֵ

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// ���帳ֵ

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// ���
		return 40;	// ��ͷ����帳ֵʧ��
	}

	return 0;
}

// ����һ��Я��ָ�����ݵ���Ϣ��
int CMemBlockPool::retrieve_with_content(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark, BOOL bIsWait)
{
	// ��ó����ڴ��ĳߴ�
	int iMemSize = get_mem_block_size();

	if(sizeof(CORE_MSG_HEAD) + iBodyLen >= iMemSize)
		return 10;	// �������ݳ�����Ϣ��ĳ�����

	BOOL bFlag = retrieve(&pMemBlock, pszTextMark, bIsWait);	// ����

	if(!bFlag || !pMemBlock)
	{
		pMemBlock = NULL;
		return 20;	// ��Ϣ�����ʧ��
	}

	int iSize = sizeof(CORE_MSG_HEAD);

	// ���ݸ�ֵ
	CORE_MSG_HEAD stCoreMsg;
	stCoreMsg.RaiseTotalSize(iBodyLen);

	stCoreMsg.lChannelNo = lChannelNo;
	stCoreMsg.iMainCode = iMainCode;
	stCoreMsg.iSubCode = iSubCode;

	pMemBlock->copy((BYTE*)(&stCoreMsg), sizeof(stCoreMsg));	// ��ͷ��ֵ

	if(pBody && iBodyLen>0)
		pMemBlock->copy(pBody, iBodyLen);	// ���帳ֵ

	if(pMemBlock->length()<=0)
	{
		recycle(pMemBlock);	// ���
		return 40;	// ��ͷ����帳ֵʧ��
	}

	return 0;
}

// ����ں���Ϣ����ʵ����
int CMemBlockPool::get_core_msg_data(CMemBlock* pMemBlock, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen)
{
	pData = NULL;
	*iDataLen = 0;

	if(!pMemBlock)
		return 10;	// pMemBlock �ǿ�ֵ
	
	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();
	CORE_MSG_HEAD* pTmp;

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock ����̫����

	*iMainCode = pHead->iMainCode;
	*iSubCode = pHead->iSubCode;

	if(pMemBlock->length() == sizeof(CORE_MSG_HEAD))	// ֻ��ͷ��û�а���
	{
		return 0;
	}

	pTmp = (CORE_MSG_HEAD*)(pHead + 1);
	pData = (BYTE*)pTmp;

	*iDataLen = pHead->iTotalSize - sizeof(CORE_MSG_HEAD);

	return 0;
}

// ����ں���Ϣ����ʵ���ݣ������ר��
int CMemBlockPool::get_core_msg_data(CMemBlock* pMemBlock, long long* lChannelNo, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen)
{
	pData = NULL;
	*iDataLen = 0;

	if(!pMemBlock)
		return 10;	// pMemBlock �ǿ�ֵ

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();
	CORE_MSG_HEAD* pTmp;

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock ����̫����

	*lChannelNo = pHead->lChannelNo;
	*iMainCode = pHead->iMainCode;
	*iSubCode = pHead->iSubCode;

	if(pMemBlock->length() == sizeof(CORE_MSG_HEAD))	// ֻ��ͷ��û�а���
	{
		return 0;
	}

	pTmp = (CORE_MSG_HEAD*)(pHead + 1);
	pData = (BYTE*)pTmp;

	*iDataLen = pHead->iTotalSize - sizeof(CORE_MSG_HEAD);

	return 0;
}

// ����ں���Ϣ��ͷ
int CMemBlockPool::get_core_msg_head(CMemBlock* pMemBlock, CORE_MSG_HEAD*& pMsgHead)
{
	if(!pMemBlock)
		return 10;	// pMemBlock �ǿ�ֵ

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock ����̫����

	pMsgHead = pHead;

	return 0;
}

// ����ں���Ϣ��ͨ����
int CMemBlockPool::get_core_msg_channel(CMemBlock* pMemBlock, long long& lChannelNo)
{
	if(!pMemBlock)
		return 10;	// pMemBlock �ǿ�ֵ

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();


	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock ����̫����

	lChannelNo = pHead->lChannelNo;

	return 0;
}

// ����ں���Ϣͷ�ڵĲ���ֵ
int CMemBlockPool::get_core_head_param(CMemBlock* pMemBlock, TYPE_IN_HEAD typeInHead, int& iVal)
{
	if(!pMemBlock)
		return 10;	// pMemBlock �ǿ�ֵ
	
	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)pMemBlock->base();

	if(pMemBlock->length() < sizeof(CORE_MSG_HEAD) )
		return 20;	// pMemBlock ����̫����

	switch(typeInHead)
	{
	case TIH_TOTAL_SIZE:
		iVal = pHead->iTotalSize;	// ������Ϣ�ĳ��ȣ� sizeof(CORE_MSG) +  iBodyLen 
		break;
	case TIH_PEER_IP:
		iVal = pHead->dwPeerIP  ;	// �Զ�������IP
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
����˵������ӡδ��أ��ڳ��⣩��Ԫ��
���������
	bDisplay		�Ƿ���ӡ
	int iDisplayNum	δ��ص������ʾ����
����������
	vecOutPool	δ��أ��ڳ��⣩��Ԫ������
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
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
		printf("��ӡδ���Ԫ�أ� \n");

	MAP_ORIGINAL_STUB::iterator iter = m_mapOriginalStub.begin();
	for( ; iter!=m_mapOriginalStub.end(); iter++)
	{
		CMemBlock* pMsgBlock = (*iter).first;
		if(pMsgBlock && !pMsgBlock->m_bInPool)	// �����Ԫ��
		{
			OUT_POOL_ELEMENT tmp;
			tmp.timeOutPool = pMsgBlock->timeOutPool;	// ����ʱ��
			tmp.timeDisplay = ::GetTickCount64();		// ��ӡ��ʱ��
			pMsgBlock->get_text_mark(tmp.szTextMark, sizeof(tmp.szTextMark)-1);	// ���ֱ�ʶ

			if(bDisplay && iCount<iDisplayNum)
			{
				printf("  %s, %I64d��ʱ�� %I64d������ʱ��%I64d����ǰʱ��%I64d \n", 
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
		printf("  δ���Ԫ����������%d \n", iCount);

	return bResult;
}
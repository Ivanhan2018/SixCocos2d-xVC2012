
/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:41
	filename: 	C:\GoodFrame\common\MsgBlockPool.h
	file path:	C:\GoodFrame\common
	file base:	MsgBlockPool
	file ext:	h
	author:		hgj
	
	purpose:	��Ϣ�أ����̼߳���İ�ȫ
*********************************************************************/

#ifndef MEM_BLOCK_POOL_H
#define MEM_BLOCK_POOL_H

#include "./MemBlock.h"

#define USE_SRWLock 1 // 1��ʾʹ�� CThreadGuardEx���ô���Ч�ʸߣ������ǲ�֧��Ƕ�ס�Ч�ʣ�release�����߳���ÿ���� 7500 ��
					  // 0��ʾʹ�� CThreadGuard���ô���֧��Ƕ�׶��ǳ��ȶ���������Ч�ʵ͡�Ч�ʣ�release�����߳���ÿ���� 1118 ��
#if USE_SRWLock
	#include "./ThreadGuardEx.h"
#else
	#include "./ThreadGuard.h"
#endif

#include <deque>
#include <hash_map>
#include <vector>
using std::deque;
using std::hash_map;
using std::pair;
using std::vector;

struct CORE_MSG_HEAD;

struct OUT_POOL_ELEMENT	// δ���Ԫ��
{
	OUT_POOL_ELEMENT(){	memset(this, 0, sizeof(*this)); }

	char	szTextMark[CMemBlock::TEXT_MARK_LEN];	// ���ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ������ġ�ͨ���ǵ��õĺ�������
	long long timeOutPool;	// ����ʱ��
	long long timeDisplay;	// ��ӡ��ʱ��
};

// ��Ϣ�أ����̼߳���İ�ȫ
class __declspec(dllexport) CMemBlockPool
{
public:
	enum 
	{ 
		DEF_INIT_COUNT				=    256,
		DEF_MAX_COUNT				= 256*1024,	// ��׼ֵ
		//DEF_MAX_COUNT				= 1024*1024,	// ���޲���ʱ�õ�ֵ��ע��Ļر�׼ֵ
	};

	enum { AUTO_SHRINK_SERVICEPOOL			= 300, };  // 5 ����

	enum TYPE_IN_HEAD	// ��Ϣͷ�ڵ�����
	{
		TIH_TOTAL_SIZE, 
		TIH_PEER_IP,
		TIH_MAIN_CODE,
		TIH_SUB_CODE,
	};

	CMemBlockPool(int iMsgBlockSize=512, int nInitElementCount=DEF_INIT_COUNT, int nMaxElementCount=DEF_MAX_COUNT);

	~CMemBlockPool();

	inline int Test(int** pp);

	// ���ó��ڳ�ʼԪ�ص�����
	inline void set_init_block_count(int nInitBlkCount);

	// ���ó���Ԫ�ص�����ֵ
	inline void set_max_block_count(int nMaxBlkCount);

	// ������չʧ�ܴ���
	inline void set_expand_fail_times(int iExpandFailTimes);

	// ������չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
	inline void set_expand_fail_sleep_time(int iExpandFailSleepTime);

	// ʹ�ö�ʱ���Զ������أ���ʱ���ɱ�����ṩ������Ҫ
	inline int use_timer_shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);

	// ��ó����ڴ��ĳߴ�
	inline int get_mem_block_size();

	// ��ó��ڳ�ʼԪ������
	inline int get_init_element_count();

	BOOL	init();		// ��ʼ��
	BOOL	uninit();	// �ͷ���Դ

	/* --------------------------------------------------------------------------
	����˵��������
	���������
		pszTextMark ���ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ������ġ�ͨ���ǵ��õĺ�������
		bIsWait		����ӳ���ȡ��Ϣ��¼δ�ܳɹ����ȴ� 1000 ����
	����������
		ppMsgBlock		���ص� CMemBlock ʵ��
	����ֵ��
		�ɹ��򷵻� TRUE�����򷵻� FALSE ��
	--------------------------------------------------------------------------*/
	inline BOOL retrieve(CMemBlock** ppMsgBlock, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	/* --------------------------------------------------------------------------
	����˵��������װ����Ϣͷ����Ϣ���ڵİ������ݱ���ԭ״����
	���������
		lChannelNo	ͨ����
		iMainCode	����Ϣ��
		iSubCode	������Ϣ��
	����������
		pMemBlock	����װ��õ���Ϣ�飬��Ϣ���ڵİ������ݱ���ԭ״����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	�������ݳ�����Ϣ��ĳ�����
			20	��Ϣ�����ʧ��
			40	��ͷ����帳ֵʧ��
	--------------------------------------------------------------------------*/
	inline int refill_head(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode);

	/* --------------------------------------------------------------------------
	����˵��������װ����Ϣ�飬ͨ���š����롢�����뱣��ԭ����ֵ����
	���������
	    pMemBlock   Ҫ����װ�����Ϣ��
		pBody		���壬�� pBody Ϊ��ֵ���� pMsgBlock ����ԭ���İ������ݲ���
		iBodyLen	���峤�ȣ��� pBody Ϊ��ֵ���� pMsgBlock ����ԭ���İ������ݲ���
	����������
		pMemBlock	����װ��õ���Ϣ�飬ͨ���ű���ԭ����ֵ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	�������ݳ�����Ϣ��ĳ�����
			20	��Ϣ�����ʧ��
			40	��ͷ����帳ֵʧ��
	--------------------------------------------------------------------------*/
	inline int refill_content(CMemBlock*& pMemBlock, const BYTE* pBody, int iBodyLen);

	/* --------------------------------------------------------------------------
	����˵��������װ����Ϣ�飬ͨ���ű���ԭ����ֵ����
	���������
	    pMemBlock   Ҫ����װ�����Ϣ��
		pBody		���壬�� pBody Ϊ��ֵ���� pMsgBlock ����ԭ���İ������ݲ���
		iBodyLen	���峤�ȣ��� pBody Ϊ��ֵ���� pMsgBlock ����ԭ���İ������ݲ���
	����������
		pMemBlock	����װ��õ���Ϣ�飬ͨ���ű���ԭ����ֵ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	�������ݳ�����Ϣ��ĳ�����
			20	��Ϣ�����ʧ��
			40	��ͷ����帳ֵʧ��
	--------------------------------------------------------------------------*/
	inline int refill_content(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0);

	/* --------------------------------------------------------------------------
	����˵��������װ����Ϣ��
	���������
	    pMemBlock   Ҫ����װ�����Ϣ��
		pBody		���壬�� pBody Ϊ��ֵ���� pMsgBlock ����ԭ���İ������ݲ���
		iBodyLen	���峤�ȣ��� pBody Ϊ��ֵ���� pMsgBlock ����ԭ���İ������ݲ���
	����������
		pMemBlock	����װ��õ���Ϣ�飬ͨ���ű���ԭ����ֵ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	�������ݳ�����Ϣ��ĳ�����
			20	��Ϣ�����ʧ��
			40	��ͷ����帳ֵʧ��
	--------------------------------------------------------------------------*/
	inline int refill_content(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0);

	/* --------------------------------------------------------------------------
	����˵��������Ϣ��׷������
	���������
	    pMemBlock   Ҫ����װ�����Ϣ��
		pBody		����
		iBodyLen	���峤��
	����������
		pMemBlock	����װ��õ���Ϣ��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			 5	pMemBlock Ϊ�ա�
			10	�������ݳ�����Ϣ��ĳ�����
			20	pMemBlock ����̫����
			40	��ͷ����帳ֵʧ��
	--------------------------------------------------------------------------*/
	inline int append_content(CMemBlock*& pMemBlock, const BYTE* pBody, int iBodyLen);

	// ����һ�������رնԶ˵���Ϣ��
	inline int retrieve_with_power_close(CMemBlock*& pMemBlock, char* pszTextMark=NULL, BOOL bIsWait=TRUE);


	// ����һ��Я���������ݵ���Ϣ�飬��Ҫ���ڲ���
	inline int retrieve_with_error_content(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	/* --------------------------------------------------------------------------
	����˵��������һ��Я��ָ�����ݵ���Ϣ��
	���������
		iMainCode	����Ϣ��
		iSubCode	������Ϣ��
		pBody		����
		iBodyLen	���峤��
		pszTextMark ���ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ������ġ�ͨ���ǵ��õĺ�������
		bIsWait		����ӳ���ȡ��Ϣ��¼δ�ܳɹ����ȴ� 1000 ����
	����������
		pMemBlock		���ص� CMemBlock ʵ������Ҫ�ֹ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	�������ݳ�����Ϣ��ĳ�����
			20	��Ϣ�����ʧ��
			40	��ͷ����帳ֵʧ��
	--------------------------------------------------------------------------*/
	inline int retrieve_with_content_no_channel(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// ����һ��Я��ָ�����ݵ���Ϣ��
	/* --------------------------------------------------------------------------
	����˵��������һ��Я��ָ�����ݵ���Ϣ��
	���������
		lChannelNo	ͨ����
		iMainCode	����Ϣ��
		iSubCode	������Ϣ��
		pBody		����
		iBodyLen	���峤��
		pszTextMark ���ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ������ġ�ͨ���ǵ��õĺ�������
		bIsWait		����ӳ���ȡ��Ϣ��¼δ�ܳɹ����ȴ� 1000 ����
	����������
		pMemBlock		���ص� CMemBlock ʵ������Ҫ�ֹ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	�������ݳ�����Ϣ��ĳ�����
			20	��Ϣ�����ʧ��
			40	��ͷ����帳ֵʧ��
	--------------------------------------------------------------------------*/
	inline int retrieve_with_content(CMemBlock*& pMemBlock, LONGLONG lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	/* --------------------------------------------------------------------------
	����˵��������ں���Ϣ����ʵ����
	���������
		lChannelNo	ͨ����
		iMainCode	����Ϣ��
		iSubCode	������Ϣ��
		pData		����
		iDataLen	����ĳ���		
	����������
		pMemBlock	Я���ں˵���Ϣ��
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pMemBlock �ǿ�ֵ
			20	pMemBlock ����̫����
	--------------------------------------------------------------------------*/
	inline int get_core_msg_data(CMemBlock* pMemBlock, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen);

	/* --------------------------------------------------------------------------
	����˵��������ں���Ϣ����ʵ���ݣ������ר��
	���������
		pMemBlock	Я���ں˵���Ϣ��
	����������
		lChannelNo	ͨ����
		iMainCode	����Ϣ��
		iSubCode	������Ϣ��
		pData		����
		iDataLen	����ĳ���
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pMemBlock �ǿ�ֵ
			20	pMemBlock ����̫����
	--------------------------------------------------------------------------*/
	inline int get_core_msg_data(CMemBlock* pMemBlock, LONGLONG* lChannelNo, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen);

	/* --------------------------------------------------------------------------
	����˵��������ں���Ϣ��ͷ
	���������
		pMemBlock	Я���ں˵���Ϣ��
	����������
		pHead		�ں���Ϣ��ͷ
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pMemBlock �ǿ�ֵ
			20	pMemBlock ����̫����
	--------------------------------------------------------------------------*/
	inline int get_core_msg_head(CMemBlock* pMemBlock, CORE_MSG_HEAD*& pMsgHead);

	/* --------------------------------------------------------------------------
	����˵��������ں���Ϣ��ͨ����
	���������
		pMemBlock	Я���ں˵���Ϣ��
	����������
		lChannelNo		ͨ����
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	pMemBlock �ǿ�ֵ
			20	pMemBlock ����̫����
	--------------------------------------------------------------------------*/
	inline int get_core_msg_channel(CMemBlock* pMemBlock, LONGLONG& lChannelNo);

	// ����ں���Ϣͷ�ڵĲ���ֵ
	inline int get_core_head_param(CMemBlock* pMemBlock, TYPE_IN_HEAD typeInHead, int& iVal);

	// ���
	inline BOOL recycle(CMemBlock* pMsgBlock);

	// ��ó��ڵ�ǰԪ�ص�����
	inline int get_current_element_count();

	// ��ó��ص�����
	inline long long get_retrieve_count();

	// ��ù�ص�����
	inline long long get_recycle_count();	

	/* --------------------------------------------------------------------------
	����˵���������صĳߴ磬Ҳ������һ���߳����������������ȫ
	���������
		nAtLessShrinkCount	����Ҫ��������Ŀ
		fShrinkParam ����ϵ��
	����ֵ��
		ʵ�������ĳߴ�
	--------------------------------------------------------------------------*/
	int	 shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);	

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
	int display_out_pool(BOOL bDisplay, vector<OUT_POOL_ELEMENT>& vecOutPool, int iDisplayNum=20);

private:
	// ��չ�صĳߴ�
	int expand_pool(int nCount, BOOL bLimitExpandLen = TRUE);		

	
private:

	deque<CMemBlock*>	m_stack;	// ��

	typedef hash_map<CMemBlock*, int> MAP_ORIGINAL_STUB;
	typedef pair<CMemBlock*, int> PAIR_ORIGINAL_STUB;
	MAP_ORIGINAL_STUB	m_mapOriginalStub;	// ԭʼ�Ĵ������������չ����������� CMemBlock* ��
											// ���� CMemBlock* �������ض����������ڲ�ѯδ��ص� CMemBlock*

	#if USE_SRWLock
		CSRWLock			m_lock;	// ��ס m_stack �� m_mapOriginalStub
	#else
		CCriticalSpection	m_lock;	
	#endif

	int m_iMsgBlockSize;	// ��ϢԪ�صĳ���

	float			m_fExpandParam;	// ��չϵ��������ʱֻ������ʼֵ��������ϵ��֮��

	int volatile	m_nInitElementCount;	// ���ڳ�ʼԪ�ص�����
	int	volatile	m_nMaxElementCount;		// ����Ԫ�ص�����ֵ

	long long volatile m_lRetrieveCount;	// ���ص�����
	long long volatile m_lRecycleCount;	// ��ص�����

	long volatile	m_nAfterExpandOrShrinkCount;	// �ص�Ԫ����������Ҫ����չ�������غ������������Ϣ��ػ����ʱ����Ӱ����

	int		m_nExpandStep;			// ��չ������������Ԫ��ʱ��Ҫ��չ������
	int		m_lPeriod;				// ��ʱ������ʱ�������� ms Ϊ��λ

	int		m_iExpandFailTimes;		// ��չʧ�ܴ���
	int		m_iExpandFailSleepTime;	// ��չʧ��ʱ��˯��ʱ�䣬�� ms Ϊ��λ
};

#endif
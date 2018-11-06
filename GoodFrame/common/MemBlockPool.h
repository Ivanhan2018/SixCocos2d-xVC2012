
/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:41
	filename: 	C:\GoodFrame\common\MsgBlockPool.h
	file path:	C:\GoodFrame\common
	file base:	MsgBlockPool
	file ext:	h
	author:		hgj
	
	purpose:	消息池，有线程级别的安全
*********************************************************************/

#ifndef MEM_BLOCK_POOL_H
#define MEM_BLOCK_POOL_H

#include "./MemBlock.h"

#define USE_SRWLock 1 // 1表示使用 CThreadGuardEx，好处是效率高，坏处是不支持嵌套。效率：release、多线程下每毫秒 7500 次
					  // 0表示使用 CThreadGuard，好处是支持嵌套而非常稳定，坏处是效率低。效率：release、多线程下每毫秒 1118 次
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

struct OUT_POOL_ELEMENT	// 未归池元素
{
	OUT_POOL_ELEMENT(){	memset(this, 0, sizeof(*this)); }

	char	szTextMark[CMemBlock::TEXT_MARK_LEN];	// 文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的。通常是调用的函数名。
	long long timeOutPool;	// 出池时间
	long long timeDisplay;	// 列印的时间
};

// 消息池，有线程级别的安全
class __declspec(dllexport) CMemBlockPool
{
public:
	enum 
	{ 
		DEF_INIT_COUNT				=    256,
		DEF_MAX_COUNT				= 256*1024,	// 标准值
		//DEF_MAX_COUNT				= 1024*1024,	// 极限测试时用的值，注意改回标准值
	};

	enum { AUTO_SHRINK_SERVICEPOOL			= 300, };  // 5 分钟

	enum TYPE_IN_HEAD	// 消息头内的类型
	{
		TIH_TOTAL_SIZE, 
		TIH_PEER_IP,
		TIH_MAIN_CODE,
		TIH_SUB_CODE,
	};

	CMemBlockPool(int iMsgBlockSize=512, int nInitElementCount=DEF_INIT_COUNT, int nMaxElementCount=DEF_MAX_COUNT);

	~CMemBlockPool();

	inline int Test(int** pp);

	// 设置池内初始元素的数量
	inline void set_init_block_count(int nInitBlkCount);

	// 设置池内元素的上限值
	inline void set_max_block_count(int nMaxBlkCount);

	// 设置扩展失败次数
	inline void set_expand_fail_times(int iExpandFailTimes);

	// 设置扩展失败时的睡眠时间，以 ms 为单位
	inline void set_expand_fail_sleep_time(int iExpandFailSleepTime);

	// 使用定时器自动收缩池，定时器由别的类提供，很重要
	inline int use_timer_shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);

	// 获得池里内存块的尺寸
	inline int get_mem_block_size();

	// 获得池内初始元素数量
	inline int get_init_element_count();

	BOOL	init();		// 初始化
	BOOL	uninit();	// 释放资源

	/* --------------------------------------------------------------------------
	函数说明：出池
	传入参数：
		pszTextMark 文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的。通常是调用的函数名。
		bIsWait		如果从池中取消息记录未能成功，等待 1000 毫秒
	传出参数：
		ppMsgBlock		出池的 CMemBlock 实例
	返回值：
		成功则返回 TRUE，否则返回 FALSE 。
	--------------------------------------------------------------------------*/
	inline BOOL retrieve(CMemBlock** ppMsgBlock, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	/* --------------------------------------------------------------------------
	函数说明：重新装填消息头，消息块内的包体内容保持原状不变
	传入参数：
		lChannelNo	通道号
		iMainCode	主消息码
		iSubCode	辅助消息码
	传出参数：
		pMemBlock	重新装填好的消息块，消息块内的包体内容保持原状不变
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	包体内容超出消息块的长度啦
			20	消息块出池失败
			40	包头或包体赋值失败
	--------------------------------------------------------------------------*/
	inline int refill_head(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode);

	/* --------------------------------------------------------------------------
	函数说明：重新装填消息块，通道号、主码、辅助码保持原来的值不变
	传入参数：
	    pMemBlock   要重新装填的消息块
		pBody		包体，若 pBody 为空值，则 pMsgBlock 保持原来的包体内容不变
		iBodyLen	包体长度，若 pBody 为空值，则 pMsgBlock 保持原来的包体内容不变
	传出参数：
		pMemBlock	重新装填好的消息块，通道号保持原来的值不变
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	包体内容超出消息块的长度啦
			20	消息块出池失败
			40	包头或包体赋值失败
	--------------------------------------------------------------------------*/
	inline int refill_content(CMemBlock*& pMemBlock, const BYTE* pBody, int iBodyLen);

	/* --------------------------------------------------------------------------
	函数说明：重新装填消息块，通道号保持原来的值不变
	传入参数：
	    pMemBlock   要重新装填的消息块
		pBody		包体，若 pBody 为空值，则 pMsgBlock 保持原来的包体内容不变
		iBodyLen	包体长度，若 pBody 为空值，则 pMsgBlock 保持原来的包体内容不变
	传出参数：
		pMemBlock	重新装填好的消息块，通道号保持原来的值不变
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	包体内容超出消息块的长度啦
			20	消息块出池失败
			40	包头或包体赋值失败
	--------------------------------------------------------------------------*/
	inline int refill_content(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0);

	/* --------------------------------------------------------------------------
	函数说明：重新装填消息块
	传入参数：
	    pMemBlock   要重新装填的消息块
		pBody		包体，若 pBody 为空值，则 pMsgBlock 保持原来的包体内容不变
		iBodyLen	包体长度，若 pBody 为空值，则 pMsgBlock 保持原来的包体内容不变
	传出参数：
		pMemBlock	重新装填好的消息块，通道号保持原来的值不变
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	包体内容超出消息块的长度啦
			20	消息块出池失败
			40	包头或包体赋值失败
	--------------------------------------------------------------------------*/
	inline int refill_content(CMemBlock*& pMemBlock, long long lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0);

	/* --------------------------------------------------------------------------
	函数说明：向消息块追加内容
	传入参数：
	    pMemBlock   要重新装填的消息块
		pBody		包体
		iBodyLen	包体长度
	传出参数：
		pMemBlock	重新装填好的消息块
	返回值：
		成功则返回 0，失败返回错误码如下：
			 5	pMemBlock 为空。
			10	包体内容超出消息块的长度啦
			20	pMemBlock 长度太短了
			40	包头或包体赋值失败
	--------------------------------------------------------------------------*/
	inline int append_content(CMemBlock*& pMemBlock, const BYTE* pBody, int iBodyLen);

	// 出池一个主动关闭对端的消息块
	inline int retrieve_with_power_close(CMemBlock*& pMemBlock, char* pszTextMark=NULL, BOOL bIsWait=TRUE);


	// 出池一个携带错误内容的消息块，主要用于测试
	inline int retrieve_with_error_content(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	/* --------------------------------------------------------------------------
	函数说明：出池一个携带指定内容的消息块
	传入参数：
		iMainCode	主消息码
		iSubCode	辅助消息码
		pBody		包体
		iBodyLen	包体长度
		pszTextMark 文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的。通常是调用的函数名。
		bIsWait		如果从池中取消息记录未能成功，等待 1000 毫秒
	传出参数：
		pMemBlock		出池的 CMemBlock 实例，需要手工归池
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	包体内容超出消息块的长度啦
			20	消息块出池失败
			40	包头或包体赋值失败
	--------------------------------------------------------------------------*/
	inline int retrieve_with_content_no_channel(CMemBlock*& pMemBlock, int iMainCode, int iSubCode, const BYTE* pBody=NULL, int iBodyLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// 出池一个携带指定内容的消息块
	/* --------------------------------------------------------------------------
	函数说明：出池一个携带指定内容的消息块
	传入参数：
		lChannelNo	通道号
		iMainCode	主消息码
		iSubCode	辅助消息码
		pBody		包体
		iBodyLen	包体长度
		pszTextMark 文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的。通常是调用的函数名。
		bIsWait		如果从池中取消息记录未能成功，等待 1000 毫秒
	传出参数：
		pMemBlock		出池的 CMemBlock 实例，需要手工归池
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	包体内容超出消息块的长度啦
			20	消息块出池失败
			40	包头或包体赋值失败
	--------------------------------------------------------------------------*/
	inline int retrieve_with_content(CMemBlock*& pMemBlock, LONGLONG lChannelNo, int iMainCode, int iSubCode, const BYTE* pBody, int iBodyLen, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	/* --------------------------------------------------------------------------
	函数说明：获得内核消息的真实数据
	传入参数：
		lChannelNo	通道号
		iMainCode	主消息码
		iSubCode	辅助消息码
		pData		包体
		iDataLen	包体的长度		
	传出参数：
		pMemBlock	携带内核的消息块
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pMemBlock 是空值
			20	pMemBlock 长度太短了
	--------------------------------------------------------------------------*/
	inline int get_core_msg_data(CMemBlock* pMemBlock, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen);

	/* --------------------------------------------------------------------------
	函数说明：获得内核消息的真实数据，服务端专用
	传入参数：
		pMemBlock	携带内核的消息块
	传出参数：
		lChannelNo	通道号
		iMainCode	主消息码
		iSubCode	辅助消息码
		pData		包体
		iDataLen	包体的长度
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pMemBlock 是空值
			20	pMemBlock 长度太短了
	--------------------------------------------------------------------------*/
	inline int get_core_msg_data(CMemBlock* pMemBlock, LONGLONG* lChannelNo, int* iMainCode, int* iSubCode, BYTE*& pData, int* iDataLen);

	/* --------------------------------------------------------------------------
	函数说明：获得内核消息的头
	传入参数：
		pMemBlock	携带内核的消息块
	传出参数：
		pHead		内核消息的头
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pMemBlock 是空值
			20	pMemBlock 长度太短了
	--------------------------------------------------------------------------*/
	inline int get_core_msg_head(CMemBlock* pMemBlock, CORE_MSG_HEAD*& pMsgHead);

	/* --------------------------------------------------------------------------
	函数说明：获得内核消息的通道号
	传入参数：
		pMemBlock	携带内核的消息块
	传出参数：
		lChannelNo		通道号
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	pMemBlock 是空值
			20	pMemBlock 长度太短了
	--------------------------------------------------------------------------*/
	inline int get_core_msg_channel(CMemBlock* pMemBlock, LONGLONG& lChannelNo);

	// 获得内核消息头内的参数值
	inline int get_core_head_param(CMemBlock* pMemBlock, TYPE_IN_HEAD typeInHead, int& iVal);

	// 归池
	inline BOOL recycle(CMemBlock* pMsgBlock);

	// 获得池内当前元素的数量
	inline int get_current_element_count();

	// 获得出池的数量
	inline long long get_retrieve_count();

	// 获得归池的数量
	inline long long get_recycle_count();	

	/* --------------------------------------------------------------------------
	函数说明：收缩池的尺寸，也可以启一个线程来进行收缩会更安全
	传入参数：
		nAtLessShrinkCount	至少要收缩的数目
		fShrinkParam 收缩系数
	返回值：
		实际收缩的尺寸
	--------------------------------------------------------------------------*/
	int	 shrink_pool(int nAtLessShrinkCount = 512, float fShrinkParam = 0.5);	

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
	int display_out_pool(BOOL bDisplay, vector<OUT_POOL_ELEMENT>& vecOutPool, int iDisplayNum=20);

private:
	// 扩展池的尺寸
	int expand_pool(int nCount, BOOL bLimitExpandLen = TRUE);		

	
private:

	deque<CMemBlock*>	m_stack;	// 池

	typedef hash_map<CMemBlock*, int> MAP_ORIGINAL_STUB;
	typedef pair<CMemBlock*, int> PAIR_ORIGINAL_STUB;
	MAP_ORIGINAL_STUB	m_mapOriginalStub;	// 原始的存根，包括了扩展后与收缩后的 CMemBlock* ，
											// 无论 CMemBlock* 归池与出池都包括，用于查询未归池的 CMemBlock*

	#if USE_SRWLock
		CSRWLock			m_lock;	// 锁住 m_stack 与 m_mapOriginalStub
	#else
		CCriticalSpection	m_lock;	
	#endif

	int m_iMsgBlockSize;	// 消息元素的长度

	float			m_fExpandParam;	// 扩展系数，收缩时只收至初始值乘以扩充系数之处

	int volatile	m_nInitElementCount;	// 池内初始元素的数量
	int	volatile	m_nMaxElementCount;		// 池内元素的上限值

	long long volatile m_lRetrieveCount;	// 出池的数量
	long long volatile m_lRecycleCount;	// 归池的数量

	long volatile	m_nAfterExpandOrShrinkCount;	// 池的元素数量，主要是扩展或收缩池后的数量，当消息归池或出池时并不影响它

	int		m_nExpandStep;			// 扩展步长，池内无元素时需要扩展的数量
	int		m_lPeriod;				// 定时收缩的时间间隔，以 ms 为单位

	int		m_iExpandFailTimes;		// 扩展失败次数
	int		m_iExpandFailSleepTime;	// 扩展失败时的睡眠时间，以 ms 为单位
};

#endif
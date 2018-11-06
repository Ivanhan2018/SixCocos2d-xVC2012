
#include "PublicHead.h"
#include "MemBlock.h"

CMemBlock::CMemBlock(void)
{
	memset(this, 0, sizeof(*this));

	m_pData = NULL;
	m_iRdPtr = 0;		// 读串的起点
	m_iWdPtr = 0;

	m_iDataSize = MSG_BLOCK_SIZE;
	m_bInPool = TRUE;
	timeOutPool = 0;	// 出池时间

	memset(m_szTextMark, 0, sizeof(m_szTextMark));
	m_sizeTextMark = 0;

	create();
}

CMemBlock::CMemBlock(int iDataSize, char* pszTextMark, int iTextLen)
{
	m_pData = NULL;
	m_iRdPtr = 0;		// 读串的起点
	m_iWdPtr = 0;

	m_iDataSize = iDataSize;

	memset(m_szTextMark, 0, sizeof(m_szTextMark));
	m_sizeTextMark = 0;

	if(pszTextMark && iTextLen>0)
	{
		m_sizeTextMark = min(sizeof(m_szTextMark)-1, iTextLen);
		_snprintf(m_szTextMark, m_sizeTextMark, "%s", pszTextMark);
	}

	create();
}

CMemBlock::~CMemBlock(void)
{
	release();
}

/* --------------------------------------------------------------------------
函数说明：判断是有效的指针，不要过于依赖此函数，这样会掩盖很多本可以解决的问题
传入参数：
	pPointer	指针
返回值：
    有效的返回 TRUE，空指针返回 FALSE 。
--------------------------------------------------------------------------*/
BOOL CMemBlock::is_valid_point(const VOID* pPointer)
{
    if( NULL == pPointer )
        return FALSE;	// 空指针

    ULONG_PTR nPozition = (ULONG_PTR)pPointer;

	#if defined(_WIN64)

		if( (0xcdcdcdcdcdcdcdcd == nPozition) ||
			(0xcccccccccccccccc == nPozition) ||
			(0xfdfdfdfdfdfdfdfd == nPozition) ||
			(0xfeeefeeefeeefeee == nPozition) ||
			(0xdddddddddddddddd == nPozition) ||
			(0xabababababababab == nPozition) ||
			(0xfefefefefefefefe == nPozition) )
		{
			return FALSE;	// 空指针
		}

	#else
		if( (0xcdcdcdcd == nPozition) ||
			(0xcccccccc == nPozition) ||
			(0xfdfdfdfd == nPozition) ||
			(0xfeeefeee == nPozition) ||
			(0xdddddddd == nPozition) ||
			(0xabababab == nPozition) ||
			(0xfefefefe == nPozition) )
		{
			return FALSE;	// 空指针
		}

	#endif

    return TRUE;	// 有值
}

BOOL CMemBlock::create()
{
	if( m_iDataSize <= 0 )
		return FALSE;

	if(!m_pData)
	{
		m_pData = new BYTE[m_iDataSize];
		memset(m_pData, 0, m_iDataSize);
	}

	if(m_pData)
		return TRUE;

	return FALSE;
}

BOOL CMemBlock::release()
{
	//if(is_valid_point(m_pData))	// 尽量不要过于依赖此函数，这样会掩盖很多本可以解决的问题
	if(m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}

	if(!m_pData)
		return TRUE;

	return FALSE;
}

// 向消息块中考入内容
int CMemBlock::copy(CMemBlock* pMemBlock)
{
	if(!pMemBlock)
		return 10;

	return copy(pMemBlock->base(), pMemBlock->length());
}

// 向消息块中考入内容
int CMemBlock::copy(const BYTE* pData, int iDataLen)
{
	//--- 安检 -------------
	if(!pData)
		return 10;

	if(0==iDataLen)
		return 20;

	if(m_iDataSize - m_iWdPtr < iDataLen )
		return 30;

	//--- 考入内容 -----------

	int iWdPtrOld = m_iWdPtr;

	BYTE* p = m_pData + m_iWdPtr;
	memcpy(p, pData, iDataLen);

	m_iWdPtr += iDataLen;
	
	#if 0
		// 测试用
		if(m_iWdPtr>=480)
		{
			printf("超限了 \n");
		}
	#endif

	return 0;
}


// 移动写指针
int CMemBlock::write(int iLen)
{
	//--- 安检 -------------

	if(m_iDataSize < m_iWdPtr + iLen)
		return 10;

	//--- 考入内容 -----------

	int iWdPtrOld = m_iWdPtr;
	m_iWdPtr += iLen;
	
	#if 0	// 测试用
		if(m_iWdPtr>=480)
		{
			printf("超限了 \n");
		}
	#endif

	return 0;
}

// 移动读指针
int CMemBlock::rd_ptr(int iMove)
{
	int iTmp = iMove + m_iRdPtr;

	if(iTmp > m_iWdPtr)
		return 10;	// 超出写指针的长度了

	if(iTmp < 0)
		return 20;	// iMove 的负值过大

	m_iRdPtr += iMove;
	return 0;
}

// 获得读指针
BYTE* CMemBlock::rd_ptr()
{
	if(m_iRdPtr>=0 && m_iRdPtr<m_iDataSize)
		return &(m_pData[m_iRdPtr]);

	return NULL;
}

// 将残余的内容移到头
int CMemBlock::remains_move_to_head()
{
	if(0==m_iRdPtr)	// 读指针在最前端，不用移
		return 0;	

	int iInteval = m_iWdPtr - m_iRdPtr;

	if(iInteval>m_iDataSize)
		return 10;

	if(iInteval<=0)
		return 20;

	for(int i=0; i<iInteval; i++)
	{
		memcpy(&m_pData[i], &m_pData[i+m_iRdPtr], 1);
	}

	m_iRdPtr = 0;
	m_iWdPtr = iInteval;

	return 0;
}



// 获得文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
void CMemBlock::get_text_mark(char* pszTextMark, int iMaxLen)
{
	if(pszTextMark)
	{
		if(m_sizeTextMark>0)
		{
			_snprintf(pszTextMark, min(m_sizeTextMark, iMaxLen), "%s", m_szTextMark);
		}
	}
}

// 设置文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
void CMemBlock::set_text_mark(char* pszTextMark, int iTextLen)
{
	if(pszTextMark)
	{
		m_sizeTextMark = min(sizeof(m_szTextMark)-1, iTextLen);
		_snprintf(m_szTextMark, m_sizeTextMark, "%s", pszTextMark);
	}
	else
	{
		memset(m_szTextMark, 0, sizeof(m_szTextMark));
		m_sizeTextMark = 0;
	}
}

// 清空文字标识，目的是在查询未释放的内存是知道是程序的哪一句申请的
void CMemBlock::clear_text_mark()
{
	// 为了提高效率，不再对 m_szTextMark 整体清零，仅改 m_sizeTextMark 值

	m_szTextMark[0] = 0;				// 第一位清零
	m_szTextMark[TEXT_MARK_LEN-1] = 0;	// 最后一位清零，以保证长度安全
	m_sizeTextMark = 0;
}

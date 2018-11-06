
#include "PublicHead.h"
#include "MemBlock.h"

CMemBlock::CMemBlock(void)
{
	memset(this, 0, sizeof(*this));

	m_pData = NULL;
	m_iRdPtr = 0;		// ���������
	m_iWdPtr = 0;

	m_iDataSize = MSG_BLOCK_SIZE;
	m_bInPool = TRUE;
	timeOutPool = 0;	// ����ʱ��

	memset(m_szTextMark, 0, sizeof(m_szTextMark));
	m_sizeTextMark = 0;

	create();
}

CMemBlock::CMemBlock(int iDataSize, char* pszTextMark, int iTextLen)
{
	m_pData = NULL;
	m_iRdPtr = 0;		// ���������
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
����˵�����ж�����Ч��ָ�룬��Ҫ���������˺������������ڸǺܶ౾���Խ��������
���������
	pPointer	ָ��
����ֵ��
    ��Ч�ķ��� TRUE����ָ�뷵�� FALSE ��
--------------------------------------------------------------------------*/
BOOL CMemBlock::is_valid_point(const VOID* pPointer)
{
    if( NULL == pPointer )
        return FALSE;	// ��ָ��

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
			return FALSE;	// ��ָ��
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
			return FALSE;	// ��ָ��
		}

	#endif

    return TRUE;	// ��ֵ
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
	//if(is_valid_point(m_pData))	// ������Ҫ���������˺������������ڸǺܶ౾���Խ��������
	if(m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}

	if(!m_pData)
		return TRUE;

	return FALSE;
}

// ����Ϣ���п�������
int CMemBlock::copy(CMemBlock* pMemBlock)
{
	if(!pMemBlock)
		return 10;

	return copy(pMemBlock->base(), pMemBlock->length());
}

// ����Ϣ���п�������
int CMemBlock::copy(const BYTE* pData, int iDataLen)
{
	//--- ���� -------------
	if(!pData)
		return 10;

	if(0==iDataLen)
		return 20;

	if(m_iDataSize - m_iWdPtr < iDataLen )
		return 30;

	//--- �������� -----------

	int iWdPtrOld = m_iWdPtr;

	BYTE* p = m_pData + m_iWdPtr;
	memcpy(p, pData, iDataLen);

	m_iWdPtr += iDataLen;
	
	#if 0
		// ������
		if(m_iWdPtr>=480)
		{
			printf("������ \n");
		}
	#endif

	return 0;
}


// �ƶ�дָ��
int CMemBlock::write(int iLen)
{
	//--- ���� -------------

	if(m_iDataSize < m_iWdPtr + iLen)
		return 10;

	//--- �������� -----------

	int iWdPtrOld = m_iWdPtr;
	m_iWdPtr += iLen;
	
	#if 0	// ������
		if(m_iWdPtr>=480)
		{
			printf("������ \n");
		}
	#endif

	return 0;
}

// �ƶ���ָ��
int CMemBlock::rd_ptr(int iMove)
{
	int iTmp = iMove + m_iRdPtr;

	if(iTmp > m_iWdPtr)
		return 10;	// ����дָ��ĳ�����

	if(iTmp < 0)
		return 20;	// iMove �ĸ�ֵ����

	m_iRdPtr += iMove;
	return 0;
}

// ��ö�ָ��
BYTE* CMemBlock::rd_ptr()
{
	if(m_iRdPtr>=0 && m_iRdPtr<m_iDataSize)
		return &(m_pData[m_iRdPtr]);

	return NULL;
}

// ������������Ƶ�ͷ
int CMemBlock::remains_move_to_head()
{
	if(0==m_iRdPtr)	// ��ָ������ǰ�ˣ�������
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



// ������ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
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

// �������ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
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

// ������ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
void CMemBlock::clear_text_mark()
{
	// Ϊ�����Ч�ʣ����ٶ� m_szTextMark �������㣬���� m_sizeTextMark ֵ

	m_szTextMark[0] = 0;				// ��һλ����
	m_szTextMark[TEXT_MARK_LEN-1] = 0;	// ���һλ���㣬�Ա�֤���Ȱ�ȫ
	m_sizeTextMark = 0;
}

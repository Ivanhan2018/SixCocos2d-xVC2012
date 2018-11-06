/********************************************************************
	created:	2012/12/30
	created:	30:12:2012   11:44
	filename: 	C:\GoodFrame\common\MsgBlock.h
	file path:	C:\GoodFrame\common
	file base:	MsgBlock
	file ext:	h
	author:		hgj
	
	purpose:	��Ϣ���е���Ϣ��
*********************************************************************/

#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

// ����һЩ����
#pragma warning(disable:4995)
#pragma warning(disable:4996)
#pragma warning(disable:4251)

// ��� <windows.h>�а�����<winsock.h>ͷ�ļ��Ӷ��� #include "Winsock2.h" ���ͻ������
// һ��Ҫ���� #include <windows.h> ֮ǰ
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class __declspec(dllexport) CMemBlock
{
public:
	enum {	MSG_BLOCK_SIZE = 2048, // Ĭ�ϵ����ݿ鳤��
		 };

	enum{	TEXT_MARK_LEN = 64,	// ���ֱ�ʶ�ĳ��ȣ�Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
		};
	enum{
		STATE_IN_POOL = 0,	// �ڳ���
		STATE_OUT_POOL		// �ڳ���
	};
public:
	
	/* ----------------------------------------------------------
	���������
		iDataSize		����� pData �Ŀռ䣬�����ݿ�� BUFSIZ
		pszTextMark		���ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
		                ���������Ч��Ӱ��ǳ������£�
						    ��Ϊ NULL ��release�����̡߳�ThreadGuardEx ��ÿ���� 7500 ��
							��Ϊ�ִ�  ��release�����̡߳�ThreadGuardEx ��ÿ���� 1118 �Ρ�
						���飺���ں˴������Ϊд�����߱Ƚ��а��գ��� NULL ��
						      ��Ӧ�ò����Ϊ�˱Ƚ��ӣ�Ϊ��ȫ������ú�������Ϊ�ִ���
							  ���������ִ��������򾭹�ʱ����֤���ȶ����ٸĳ� NULL
	-----------------------------------------------------------*/
	CMemBlock(int iDataSize, char* pszTextMark=NULL, int iTextLen=0);

	CMemBlock(void);
	~CMemBlock(void);

	// �������Ϣ��������ռ䳤��
	int size()	{	return m_iDataSize;	}

	// ��Ч���ݵĳ��ȣ��� wr_ptr() �� rd_ptr() �Ĳ��ֵ 
	int length() {	return (m_iWdPtr - m_iRdPtr);  }

	// ��û��д���ݵĿռ䣬�� wr_ptr ����֮��Ŀռ䳤��
	int space()	{	return (m_iDataSize - m_iWdPtr);	}	

	// ָ����Ϣ���ͷ
	BYTE* base(){	return m_pData;	}	

	/* --------------------------------------------------------------------------
	����˵�����ƶ���ָ��
	���������
		iMove	�ƶ��ľ���
	����������
	����ֵ��
		�ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
			10	����дָ��ĳ�����
			20	iMove �ĸ�ֵ����
	--------------------------------------------------------------------------*/
	int rd_ptr(int iMove);

	// ��ö�ָ��
	BYTE* rd_ptr();

	// wd_ptr �Ƶ�����㣬�� m_pData �е��������ݲ�û���㣨�ɽ�ԼCPU������ʱ�䣩
	// �� clear �������˽���һ����˵�� memset �Ǻܺ�ʱ��
	void reset ()
	{	
		m_iRdPtr = 0;
		m_iWdPtr = 0; 
		m_pData[m_iDataSize-1] = 0; // ����������������һ��Ԫ����0	
	}

	// wd_ptr �Ƶ�����㣬�� m_pData �е�������������
	// �� reset �������˽���һ����˵�� memset �Ǻܺ�ʱ��
	void clear()
	{	
		memset(m_pData, 0, m_iDataSize); 
		m_iRdPtr = 0; 
		m_iWdPtr = 0;	
	}

	// ����Ϣ���п�������
	int copy(CMemBlock* pMemBlock);

	/* ----------------------------------------------------------
	����˵��������Ϣ���п�������
	���������
		pData		Ҫ���������
		iDataLen	Ҫ�������ݵĳ���
	����ֵ��
		�ɹ��򷵻� 0�����򷵻ش��������£�
			1  Ҫ���������Ϊ��
			2  Ҫ�������ݵĳ���Ϊ0
			3  Ҫ�������ݵĳ��ȳ���
	-----------------------------------------------------------*/
	int copy(const BYTE* pData, int iDataLen);

	/* ----------------------------------------------------------
	����˵�����ƶ�дָ��
	���������
		iLen	�ƶ��ĳ���
	����ֵ��
		�ɹ��򷵻� 0�����򷵻ش��������£�
			3  �ƶ��ĳ��ȳ���
	-----------------------------------------------------------*/
	int write(int iLen);


	// ������������Ƶ�ͷ
	int remains_move_to_head();

	// ������ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
	void get_text_mark(char* pszTextMark, int iMaxLen);

	// �������ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
	void set_text_mark(char* pszTextMark, int iTextLen);

	// ������ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ�������
	void clear_text_mark();

private:

	BOOL create();

	// �ͷ����е���Դ
	BOOL release();

	// �ж�����Ч��ָ��
	BOOL is_valid_point(const VOID* pPointer);

public:
	BOOL		m_bInPool;		// TRUE ��ʾ�ڳ��ڣ�FALSE ��ʾ�ڳ���
	long long	timeOutPool;	// ����ʱ�䣬��Ϊ��ֵ��ʾ�ڳ���

private:

	int	m_iDataSize;	// ����� pData �Ŀռ䣬�����ݿ�� BUFSIZ
	int m_iRdPtr;		// ���������
	int m_iWdPtr;		// д�������

	BYTE* m_pData;	

	char	m_szTextMark[TEXT_MARK_LEN];	// ���ֱ�ʶ��Ŀ�����ڲ�ѯδ�ͷŵ��ڴ���֪���ǳ������һ������ġ�ͨ���ǵ��õĺ�������
	int		m_sizeTextMark;					// ���ֱ�ʶ�ĳ���
};

#endif
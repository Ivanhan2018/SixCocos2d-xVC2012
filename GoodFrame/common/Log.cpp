
#include "./Log.h"
#include "./PublicHead.h"
#include "./Often.h"

// pszFileName �ļ���
CLog::CLog(TCHAR* pszFileName)
{
	m_hFile = INVALID_HANDLE_VALUE;	

	m_pMsgPool = NULL;

	m_iFileNo = 0;
	m_iLineCount = 0;		// �����ļ��е�ǰ�е�����
	m_iMaxLineCount = 5000;	// �����ļ�������е�����

	SYSTEMTIME timeCreateFile = { 0 };	// ������ʱ��
	GetSystemTime(&timeCreateFile);	// ��õ�ǰʱ��
	TCHAR szTmp[256];
	StringCchPrintf(szTmp, _countof(szTmp)-1, _T("%s%04d_%02d_%02d��%02d��%02d��%02d��"), 
		pszFileName,
		timeCreateFile.wYear,
		timeCreateFile.wMonth,
		timeCreateFile.wDay,
		timeCreateFile.wHour + 8,	// ��8�Ƕ��뱱��ʱ��
		timeCreateFile.wMinute,
		timeCreateFile.wSecond
		);
	m_strFile = szTmp;	// �Ȱ��ļ���������

	// ��־��·��
	m_strPath = COften::get_current_path() + _T("CORE_LOG\\");
}

CLog::~CLog(void)
{
}

int CLog::start_log()
{
	int iRes = 0;

	m_pMsgPool = new CMemBlockPool(1024, 64);
	assert(m_pMsgPool);
	if(!m_pMsgPool)
		return 10;

	m_pMsgPool->init();

	// ��ʼ�� m_stTaskSinkEx
	m_stTaskSinkEx.set_listen_module((CSynchronyTaskExListener*)this);	// ����Ǳ����
	m_stTaskSinkEx.set_thread_num(1);		// ������Ϣ�����̵߳���������Ĭ��ֵ������ʡ��
	m_stTaskSinkEx.set_message_len(1024);	// ��Ĭ��ֵ������ʡ��
	m_stTaskSinkEx.set_mem_block_pool(m_pMsgPool);	// �������ⲿ���� CMemBlockPool ʵ����ָ��

	iRes = m_stTaskSinkEx.start();

	iRes = create_file(m_iFileNo);
	if(iRes>0)
		return 30;

	if(iRes>0)
		return 40;

	return 0;
}

int CLog::stop_log()
{
	int iRes = 0;

	iRes = m_stTaskSinkEx.stop();
	if(iRes>0)
		return 10;

	m_pMsgPool->uninit();
	delete m_pMsgPool;

	iRes = close_current_file();
	if(iRes>0)
		return 20;

	return 0;
}

/* --------------------------------------------------------------------------
����˵����������־��·��
���������
	szPathName	·�����ƣ��ڴ�·���»���ʱ����Ϊ�ļ���
����������
����ֵ��
    �ɹ��򷵻� TRUE�����򷵻� FALSE ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
��ע��
--------------------------------------------------------------------------*/
int CLog::set_path(wstring wstrPathName)
{
	m_strPath = wstrPathName;

	return 0;
}

// �رյ�ǰ�򿪵��ļ�
int CLog::close_current_file()
{
	if(INVALID_HANDLE_VALUE!=m_hFile)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;

		return 0;
	}

	return 10;
}

/* --------------------------------------------------------------------------
����˵����
���������
	iFileNo		�ļ����
����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
		20	CreateFile ʧ��
--------------------------------------------------------------------------*/
int CLog::create_file(int iFileNo)
{
	assert(m_strPath.length()>0);

	int		iRes = 0;
	TCHAR	szPathFile[168];
	DWORD	dwError = 0;

	BOOL	bFlag;
	DWORD	dwRealWriteSize = 0;
	INT16	iUnidoceHead = 0xfeff;   // UNICODE �ļ���ͷ����û�������޷���������

	m_iLineCount = 0;

	// ����Ŀ¼
	COften::create_dir((TCHAR*)m_strPath.c_str(), static_cast<int>(m_strPath.length()));
	if(iRes>0)
		return 10;

	StringCchPrintf(szPathFile, _countof(szPathFile)-1, _T("%s%s__%04d.txt"), 
					m_strPath.c_str(),
					m_strFile.c_str(),
					iFileNo
					);

	try
	{
		m_hFile = (HANDLE)CreateFile(
									szPathFile, 
									GENERIC_READ | GENERIC_WRITE, 
									FILE_SHARE_READ | FILE_SHARE_WRITE, 
									NULL, 
									CREATE_ALWAYS, 
									NULL, 
									NULL);
		dwError = GetLastError();
		if (INVALID_HANDLE_VALUE==m_hFile)
			return 20;	// CreateFile ʧ��

		bFlag = WriteFile(m_hFile, (BYTE*)(&iUnidoceHead), sizeof(iUnidoceHead), &dwRealWriteSize, NULL);
	}
	catch (...)
	{
		return 100;	// �쳣
	}

	return 0;
}

/* --------------------------------------------------------------------------
����˵����д������
���������
	pData		����
	iDataLen	���ݵĳ���
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
		10	m_hFile ��Ч
		20	pData �ǿ�ֵ
		30	iDataLen ����Ϊ0
		50	create_file ʧ��
--------------------------------------------------------------------------*/
int CLog::write_file(unsigned char* pData, int iDataLen)
{
	if (INVALID_HANDLE_VALUE==m_hFile)
		return 10;	// m_hFile ��Ч

	if(!pData)
		return 20;	// pData �ǿ�ֵ

	if(iDataLen<=0)
		return 30;	// iDataLen ����Ϊ0

	if(m_iLineCount>=m_iMaxLineCount)
	{
		close_current_file();

		m_iFileNo++;
		if(create_file(m_iFileNo)>0)
			return 50;	// create_file ʧ��
	}

	BOOL	bFlag;
	DWORD	dwRealWriteSize;
	TCHAR	szReturnCharacter[8];	// �س����з�
	size_t	iLen = 0;
	StringCchPrintf(szReturnCharacter, _countof(szReturnCharacter)-1, _T("\r\n"));
	StringCchLength(szReturnCharacter, _countof(szReturnCharacter)-1, &iLen);

	try
	{
		// д������
		bFlag = WriteFile(m_hFile, pData, iDataLen, &dwRealWriteSize, NULL);
		if (!bFlag)
			return 20;	// д��ʧ��

		// д��س�����
		WriteFile(m_hFile, (BYTE*)szReturnCharacter, (DWORD)iLen*sizeof(TCHAR), &dwRealWriteSize, NULL);

		m_iLineCount++;
	}
	catch (...)
	{
		return 100;	// �쳣
	}

	return 0;
}

/* --------------------------------------------------------------------------
����˵����д����־���
���������
	iType			���ͣ��ο� LOG_ERR_TYPE ö�� 
	pszSentence		��־���
	iSentenceLen	��־���ĳ���
����������
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CLog::write_log(TCHAR* pszSentence, int iSentenceLen)
{
	if(!pszSentence)
		return 20;

	if(0==iSentenceLen)
		return 30;
/*
	SYSTEMTIME timeCurrent = { 0 };	// ������ʱ��
	GetSystemTime(&timeCurrent);	// ��õ�ǰʱ��

	wstring strTime;
	TCHAR szTime[32];
	StringCchPrintf(szTime, _countof(szTime)-1, _T("%04d_%02d_%02d %02d:%02d:%02d "), 
		timeCurrent.wYear,
		timeCurrent.wMonth,
		timeCurrent.wDay,
		timeCurrent.wHour,
		timeCurrent.wMinute,
		timeCurrent.wSecond
		);
	strTime = szTime;
	*/
	wstring strTime;
	TCHAR szTime[32];
	CEasyDataTime easy;
	int iYear, iMon, iDay, iHour, iMin, iSec;

	easy.get_current_time();	// ��õ��Եĵ�ǰʱ��
	easy.get_date_time(iYear, iMon, iDay, iHour, iMin, iSec);	// �������ʱ��ֵ
	StringCchPrintf(szTime, _countof(szTime)-1, _T("%04d_%02d_%02d %02d:%02d:%02d"), iYear, iMon, iDay, iHour, iMin, iSec);

	wstring strLog = strTime + pszSentence;

	CMemBlock* pMemBlock = NULL;
	int iMainCode = 0;
	int iSubCode = 0;

	int iRes = m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, 
												(BYTE*)(strLog.c_str()), static_cast<int>(strLog.length()*sizeof(TCHAR)), 
												__FUNCTION__);

	if(0==iRes && pMemBlock)
	{
		// Ͷ�ݵ���������д���ĺô���
		// 1�������ö��߳�������ʱ���¼���������һ����ʱ iIDEvent ��ʱ����������¾ͻ�������Ķ�ʱ iIDEvent 
		// 2�������ʱ iIDEvent ͬʱ����ʱ�������Բ���ִ��
		m_stTaskSinkEx.put(pMemBlock);	
	}
	
	return 0;
}

// ��������
int CLog::OnConsumeTask(CMemBlock*& pMemBlock)
{
	assert(m_strPath.length()>0);

	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// �Զ�����ź�

	int iMainCode = 0;
	int iSubCode = 0;
	BYTE* pData = NULL;
	int   iDataLen = 0;

	int iRes = m_pMsgPool->get_core_msg_data(pMemBlock, &iMainCode, &iSubCode, pData, &iDataLen);
	if(0==iRes && pData)
	{
		write_file(pData, iDataLen);
	}

	return stTaskMsgResult;
}
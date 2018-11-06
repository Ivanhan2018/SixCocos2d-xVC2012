
#include "./Log.h"
#include "./PublicHead.h"
#include "./Often.h"

// pszFileName 文件名
CLog::CLog(TCHAR* pszFileName)
{
	m_hFile = INVALID_HANDLE_VALUE;	

	m_pMsgPool = NULL;

	m_iFileNo = 0;
	m_iLineCount = 0;		// 单个文件中当前行的数量
	m_iMaxLineCount = 5000;	// 单个文件中最大行的数量

	SYSTEMTIME timeCreateFile = { 0 };	// 建档的时间
	GetSystemTime(&timeCreateFile);	// 获得当前时间
	TCHAR szTmp[256];
	StringCchPrintf(szTmp, _countof(szTmp)-1, _T("%s%04d_%02d_%02d【%02d：%02d：%02d】"), 
		pszFileName,
		timeCreateFile.wYear,
		timeCreateFile.wMonth,
		timeCreateFile.wDay,
		timeCreateFile.wHour + 8,	// 加8是对齐北京时间
		timeCreateFile.wMinute,
		timeCreateFile.wSecond
		);
	m_strFile = szTmp;	// 先把文件名定下来

	// 日志的路径
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

	// 初始化 m_stTaskSinkEx
	m_stTaskSinkEx.set_listen_module((CSynchronyTaskExListener*)this);	// 这句是必需的
	m_stTaskSinkEx.set_thread_num(1);		// 设置消息推送线程的数量，有默认值，可以省略
	m_stTaskSinkEx.set_message_len(1024);	// 有默认值，可以省略
	m_stTaskSinkEx.set_mem_block_pool(m_pMsgPool);	// 必需由外部传入 CMemBlockPool 实例的指针

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
函数说明：设置日志的路径
传入参数：
	szPathName	路径名称，在此路径下会以时间作为文件名
传出参数：
返回值：
    成功则返回 TRUE，否则返回 FALSE 。
    成功则返回 0，失败返回错误码如下：
备注：
--------------------------------------------------------------------------*/
int CLog::set_path(wstring wstrPathName)
{
	m_strPath = wstrPathName;

	return 0;
}

// 关闭当前打开的文件
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
函数说明：
传入参数：
	iFileNo		文件编号
返回值：
    成功则返回 0，否则返回错误码如下：
		20	CreateFile 失败
--------------------------------------------------------------------------*/
int CLog::create_file(int iFileNo)
{
	assert(m_strPath.length()>0);

	int		iRes = 0;
	TCHAR	szPathFile[168];
	DWORD	dwError = 0;

	BOOL	bFlag;
	DWORD	dwRealWriteSize = 0;
	INT16	iUnidoceHead = 0xfeff;   // UNICODE 文件的头部，没有它就无法输入中文

	m_iLineCount = 0;

	// 创建目录
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
			return 20;	// CreateFile 失败

		bFlag = WriteFile(m_hFile, (BYTE*)(&iUnidoceHead), sizeof(iUnidoceHead), &dwRealWriteSize, NULL);
	}
	catch (...)
	{
		return 100;	// 异常
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：写入内容
传入参数：
	pData		内容
	iDataLen	内容的长度
返回值：
    成功则返回 0，失败返回错误码如下：
		10	m_hFile 无效
		20	pData 是空值
		30	iDataLen 长度为0
		50	create_file 失败
--------------------------------------------------------------------------*/
int CLog::write_file(unsigned char* pData, int iDataLen)
{
	if (INVALID_HANDLE_VALUE==m_hFile)
		return 10;	// m_hFile 无效

	if(!pData)
		return 20;	// pData 是空值

	if(iDataLen<=0)
		return 30;	// iDataLen 长度为0

	if(m_iLineCount>=m_iMaxLineCount)
	{
		close_current_file();

		m_iFileNo++;
		if(create_file(m_iFileNo)>0)
			return 50;	// create_file 失败
	}

	BOOL	bFlag;
	DWORD	dwRealWriteSize;
	TCHAR	szReturnCharacter[8];	// 回车换行符
	size_t	iLen = 0;
	StringCchPrintf(szReturnCharacter, _countof(szReturnCharacter)-1, _T("\r\n"));
	StringCchLength(szReturnCharacter, _countof(szReturnCharacter)-1, &iLen);

	try
	{
		// 写入内容
		bFlag = WriteFile(m_hFile, pData, iDataLen, &dwRealWriteSize, NULL);
		if (!bFlag)
			return 20;	// 写入失败

		// 写入回车换行
		WriteFile(m_hFile, (BYTE*)szReturnCharacter, (DWORD)iLen*sizeof(TCHAR), &dwRealWriteSize, NULL);

		m_iLineCount++;
	}
	catch (...)
	{
		return 100;	// 异常
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：写入日志语句
传入参数：
	iType			类型，参考 LOG_ERR_TYPE 枚举 
	pszSentence		日志语句
	iSentenceLen	日志语句的长度
传出参数：
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CLog::write_log(TCHAR* pszSentence, int iSentenceLen)
{
	if(!pszSentence)
		return 20;

	if(0==iSentenceLen)
		return 30;
/*
	SYSTEMTIME timeCurrent = { 0 };	// 建档的时间
	GetSystemTime(&timeCurrent);	// 获得当前时间

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

	easy.get_current_time();	// 获得电脑的当前时间
	easy.get_date_time(iYear, iMon, iDay, iHour, iMin, iSec);	// 获得日期时间值
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
		// 投递到任务，这种写法的好处：
		// 1、可以用多线程来处理定时器事件，不存在一个定时 iIDEvent 耗时过长的情况下就会阻塞别的定时 iIDEvent 
		// 2、多个定时 iIDEvent 同时成立时几乎可以并行执行
		m_stTaskSinkEx.put(pMemBlock);	
	}
	
	return 0;
}

// 消费任务
int CLog::OnConsumeTask(CMemBlock*& pMemBlock)
{
	assert(m_strPath.length()>0);

	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// 自动归池信号

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
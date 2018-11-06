/********************************************************************
	created:	2013/02/20
	created:	20:2:2013   14:04
	filename: 	E:\SVN_2013\GoodFrame\common\Log.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	Log
	file ext:	h
	author:		侯国江
	
	purpose:	内核日志
*********************************************************************/

#ifndef LOG_H
#define LOG_H

#include "./SynchronyTaskEx.h"

#include <string>
using std::wstring;

class __declspec(dllexport) CLog : public CSynchronyTaskExListener
{
public:
	enum LOG_TYPE	// 日志类型
	{
		LOG_TYPE_PROMPT = 0,	// 提示
		LOG_TYPE_WARING = 1,	// 警告
		LOG_TYPE_ERR = 2,		// 错误与异常
	};
public:
	CLog(TCHAR* pszFileName);
	~CLog(void);

	// 启动
	int CLog::start_log();
	
	// 停止
	int CLog::stop_log();

	// 设置日志的路径
	int set_path(wstring wstrPathName);

	// 写入日志语句
	int write_log(TCHAR* pszSentence, int iSentenceLen);

private:
	int create_file(int iFileNo);

	// 关闭当前打开的文件
	int close_current_file();

	// 写入内容
	int write_file(unsigned char* pData, int iDataLe);

	// 消费任务
	virtual int OnConsumeTask(CMemBlock*& pMemBlock);

private:

	HANDLE	m_hFile;	

	wstring m_strPath;	// 日志的路径
	wstring m_strFile;

	int m_iFileNo;			// 文件的序号
	int m_iLineCount;		// 单个文件中当前行的数量
	int m_iMaxLineCount;	// 单个文件中最大行的数量 

	CSynchronyTaskEx m_stTaskSinkEx;	// 同步任务发射器，由 OnConsumeTask 函数接收
	CMemBlockPool*	m_pMsgPool;	

};

#endif
/********************************************************************
	created:	2013/02/20
	created:	20:2:2013   14:04
	filename: 	E:\SVN_2013\GoodFrame\common\Log.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	Log
	file ext:	h
	author:		�����
	
	purpose:	�ں���־
*********************************************************************/

#ifndef LOG_H
#define LOG_H

#include "./SynchronyTaskEx.h"

#include <string>
using std::wstring;

class __declspec(dllexport) CLog : public CSynchronyTaskExListener
{
public:
	enum LOG_TYPE	// ��־����
	{
		LOG_TYPE_PROMPT = 0,	// ��ʾ
		LOG_TYPE_WARING = 1,	// ����
		LOG_TYPE_ERR = 2,		// �������쳣
	};
public:
	CLog(TCHAR* pszFileName);
	~CLog(void);

	// ����
	int CLog::start_log();
	
	// ֹͣ
	int CLog::stop_log();

	// ������־��·��
	int set_path(wstring wstrPathName);

	// д����־���
	int write_log(TCHAR* pszSentence, int iSentenceLen);

private:
	int create_file(int iFileNo);

	// �رյ�ǰ�򿪵��ļ�
	int close_current_file();

	// д������
	int write_file(unsigned char* pData, int iDataLe);

	// ��������
	virtual int OnConsumeTask(CMemBlock*& pMemBlock);

private:

	HANDLE	m_hFile;	

	wstring m_strPath;	// ��־��·��
	wstring m_strFile;

	int m_iFileNo;			// �ļ������
	int m_iLineCount;		// �����ļ��е�ǰ�е�����
	int m_iMaxLineCount;	// �����ļ�������е����� 

	CSynchronyTaskEx m_stTaskSinkEx;	// ͬ�������������� OnConsumeTask ��������
	CMemBlockPool*	m_pMsgPool;	

};

#endif
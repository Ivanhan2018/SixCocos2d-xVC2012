/********************************************************************
	created:	2013/02/08
	created:	8:2:2013   13:16
	filename: 	E:\SVN_2013\GoodFrame\common\BasicLogic.h
	file path:	E:\SVN_2013\GoodFrame\common
	file base:	BasicLogic
	file ext:	h
	author:		侯国江
	
	purpose:	基本逻辑类，一切任务逻辑都以本类为父类
*********************************************************************/

#ifndef BASIC_LOGIC_H
#define BASIC_LOGIC_H

// 解决 <windows.h>中包含了<winsock.h>头文件从而与 #include "Winsock2.h" 相冲突的问题
// 一定要放在 #include <windows.h> 之前
#define WIN32_LEAN_AND_MEAN

#include "./SynchronyTaskEx.h"

class CCoreServer;

class __declspec(dllexport) CBasicLogic : public CSynchronyTaskExListener
{
public:
	friend class CCoreServer;

public:
	CBasicLogic(void);
	~CBasicLogic(void);

public:

	/* --------------------------------------------------------------------------
	函数说明：响应任务消息
	传入参数：
		pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
	传出参数：
		pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
	--------------------------------------------------------------------------*/
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock) = 0;

private:
	/* --------------------------------------------------------------------------
	函数说明：收到投递的任务消息
	传入参数：
		pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
	传出参数：
		pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
	--------------------------------------------------------------------------*/
	virtual int OnConsumeTask(CMemBlock*& pMsgBlock);

public:
	void set_core_server(CCoreServer* pCoreServer);

	// 设置推送消息线程的数量
	void set_thread_num(int iNum=1);

	// 设置消息池，必需由外部传入 CMemBlockPool 实例的指针
	void set_mem_block_pool(CMemBlockPool* pMsgPool);

	// 开始
	int start();

	// 停止
	int stop();

public:

	// 添加任务消息，需要手工归池
	// bIsFront	TRUE 表示加到双向队列的头部，FALSE 表示加到双向队列的尾部
	int put(CMemBlock*& pMemBlock, BOOL bIsFront=FALSE);

public:
	CSynchronyTaskEx m_stTaskSinkEx;	// 同步任务发射器，由 OnConsumeTask 函数接收

	CCoreServer* m_pCoreServer;

protected:
	BOOL	m_bIsDB;	// 是否数据库
};

#endif
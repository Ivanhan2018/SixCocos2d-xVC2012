
/********************************************************************
	created:	2013/10/07
	created:	7:10:2013   15:33
	filename: 	E:\SixDivisions\GoodFRame\common\Work.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	Work
	file ext:	h
	author:		侯国江
	
	purpose:	通用工作模块类
*********************************************************************/

#ifndef GENERAL_WORK_H
#define GENERAL_WORK_H

//class CWorker;
#include "./Worker.h"

// 通用工作类的发射器
class __declspec(dllexport) CGeneralWork
{
public:
	friend class CCoreServer;

	enum{	WORKER_MAX_NUM = 20,	// 工人最大数量
			WORKER_NUM = 6,			// 工人的默认数量
		};

	enum{
		ERR_GWH_pMsgPool_is_null = 10,		// m_pMsgPool 是空值
		ERR_GWH_m_pCoreServer_is_null = 20,	// m_pCoreServer 是空值
		};
public:
	CGeneralWork(void);
	~CGeneralWork(void);

public:

	// 开始
	int start();

	// 结束
	int stop();

public:

	// 获得内核框架的指针
	inline CCoreServer* get_core_server();

	// 设置内核框架的指针
	inline void set_core_server(CCoreServer* pCoreServer);

	// 设置工人数量
	inline void set_worker_num(int iWorkerNum);

	// 设置消息池，必需由外部传入 CMemBlockPool 实例的指针
	inline 	void set_mem_block_pool(CMemBlockPool* pMsgPool);

public:

	// 通道绑定工号，即一个通道号的数据只能在一个线程里执行，从而保证了此通道号内先到的数据执行完毕啦，才会去执行后到的数据。
	inline int channel_bind_worker_no(LONGLONG lChannelNo);

private:
	// 处理消息
	int handle_msg(CMemBlock*& pMsgBlock);

public:

	/* --------------------------------------------------------------------------
	函数说明：响应任务消息
	传入参数：
		pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
	传出参数：
		pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
	--------------------------------------------------------------------------*/
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock) = 0;

protected:
	CWorker* m_pWorker[WORKER_MAX_NUM];
	int		 m_iWorkerNum;	// 工人数量

	CCoreServer*	m_pCoreServer;	// 内核框架的指针
	CMemBlockPool*	m_pMsgPool;		// 消息池

public:
	BOOL	m_bIsDB;	// 是否数据库
};

#endif
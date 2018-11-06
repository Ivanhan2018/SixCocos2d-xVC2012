
#include "./PublicHead.h"
#include "./GeneralWork.h"
//#include "assert.h"

#include "./PublicHead.h"
#include "./CoreServer.h"

CGeneralWork::CGeneralWork(void)
{
	memset(m_pWorker, 0, sizeof(m_pWorker));
	m_iWorkerNum = WORKER_NUM;
	
	m_pCoreServer = NULL;
	m_pMsgPool = NULL;

	m_bIsDB = false;
}


CGeneralWork::~CGeneralWork(void)
{
}

// 设置内核框架的指针
void CGeneralWork::set_core_server(CCoreServer* pCoreServer)
{
	assert(pCoreServer);
	m_pCoreServer = pCoreServer;
}

// 获得内核框架的指针
CCoreServer* CGeneralWork::get_core_server()
{
	assert(m_pCoreServer);
	return m_pCoreServer;
}

// 设置消息池，必需由外部传入 CMemBlockPool 实例的指针
void CGeneralWork::set_mem_block_pool(CMemBlockPool* pMsgPool)
{
	assert(pMsgPool);
	if(!pMsgPool)
		return;

	m_pMsgPool = pMsgPool;
}

// 设置工人数量
void CGeneralWork::set_worker_num(int iWorkerNum)
{
	if(iWorkerNum<=0)
	{
		m_iWorkerNum = WORKER_NUM;
		return;
	}

	if(iWorkerNum < WORKER_MAX_NUM)
		m_iWorkerNum = iWorkerNum;
	else
		m_iWorkerNum = WORKER_MAX_NUM;
}

// 开始
int CGeneralWork::start()
{
	assert(m_pCoreServer);
	if(!m_pCoreServer)
		return ERR_GWH_m_pCoreServer_is_null;

	assert(m_pMsgPool);
	if(!m_pMsgPool)
		return ERR_GWH_pMsgPool_is_null;

	int iRes = 0;
	
	for(int i=0; i<m_iWorkerNum; i++)
	{	
		m_pWorker[i] = new CWorker;
		CWorker* pWork = m_pWorker[i];

		// 此处的形参铁定是1，才能保证“先完后执”的顺序。
		// 一个通道号的数据只能在一个线程里执行，从而保证了此通道号内先到的数据执行完毕啦，才会去执行后到的数据，即“先完后执”的顺序。
		pWork->set_thread_num(1);	

		pWork->set_core_server(m_pCoreServer);
		pWork->set_mem_block_pool(m_pMsgPool);	// 必需由外部传入 CMemBlockPool 实例的指针

		pWork->set_general_work(this);

		//iRes = regist_task_module(MODULE_ID_MY_LOGIC, m_pLogic, (CCoreServer*)this);	// 注册任务模块，此句不能省略

		assert(0==iRes);
		if(0!=iRes)
			break;

	}

	for(int i=0; i<m_iWorkerNum; i++)
	{
		iRes = m_pWorker[i]->start();	// 启动任务模块，此句不能省略
		assert(0==iRes);
	}

	return 0;
}

// 结束
int CGeneralWork::stop()
{
	int iRes = 0;

	for(int i=0; i<m_iWorkerNum; i++)
	{
		if(m_pWorker[i])
		{
			iRes = m_pWorker[i]->stop();	// 启动任务模块，此句不能省略
			assert(0==iRes);
		}
	}

	return 0;
}

// 通道绑定工号，即一个通道号的数据只能在一个线程里执行，从而保证了此通道号内先到的数据执行完毕啦，才会去执行后到的数据。
int CGeneralWork::channel_bind_worker_no(LONGLONG lChannelNo)
{
	int iWorkerNo = -1;

	if(lChannelNo>0)
	{
		// 工号
		iWorkerNo = lChannelNo % m_iWorkerNum;
	}
	
	return iWorkerNo;
}

// 处理消息，分配策略
int CGeneralWork::handle_msg(CMemBlock*& pMsgBlock)
{
	assert(m_pMsgPool);
	if(!m_pMsgPool)
		return ERR_GWH_pMsgPool_is_null;

	assert(m_pCoreServer);
	if(!m_pCoreServer)
		return ERR_GWH_m_pCoreServer_is_null;

	int iRes = 0;

	LONGLONG lChannelNo = INVALID_CHANNEL_NO;
	m_pMsgPool->get_core_msg_channel(pMsgBlock, lChannelNo);

	if(lChannelNo>0)
	{
		// 表示通道号绑定工人，即一个通道号的数据只能在一个线程里执行，从而保证了此通道号内先到的数据执行完毕啦，才会去执行后到的数据。
		int iWorkerNo = channel_bind_worker_no(lChannelNo);	

		CWorker* pWork = m_pWorker[iWorkerNo];
		iRes = pWork->put(pMsgBlock);
	}
	else if(TIMER_CHANNEL_NO==lChannelNo)	// 定时器的通道号
	{
		int iWorkerNo = m_iWorkerNum-1;		// 最后个一个工人

		CWorker* pWork = m_pWorker[iWorkerNo];
		iRes = pWork->put(pMsgBlock);
	}
	else if (PROFESSION_CHANNEL_NO==lChannelNo) // 专用通道号
	{
		int iWorkerNo = m_iWorkerNum-1;		// 最后个一个工人

		CWorker* pWork = m_pWorker[iWorkerNo];
		iRes = pWork->put(pMsgBlock);
	}
	else
	{
		m_pMsgPool->recycle(pMsgBlock);	// 消息归池
	}

	return iRes;
}
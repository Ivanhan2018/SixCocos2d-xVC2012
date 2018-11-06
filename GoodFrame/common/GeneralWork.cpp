
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

// �����ں˿�ܵ�ָ��
void CGeneralWork::set_core_server(CCoreServer* pCoreServer)
{
	assert(pCoreServer);
	m_pCoreServer = pCoreServer;
}

// ����ں˿�ܵ�ָ��
CCoreServer* CGeneralWork::get_core_server()
{
	assert(m_pCoreServer);
	return m_pCoreServer;
}

// ������Ϣ�أ��������ⲿ���� CMemBlockPool ʵ����ָ��
void CGeneralWork::set_mem_block_pool(CMemBlockPool* pMsgPool)
{
	assert(pMsgPool);
	if(!pMsgPool)
		return;

	m_pMsgPool = pMsgPool;
}

// ���ù�������
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

// ��ʼ
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

		// �˴����β�������1�����ܱ�֤�������ִ����˳��
		// һ��ͨ���ŵ�����ֻ����һ���߳���ִ�У��Ӷ���֤�˴�ͨ�������ȵ�������ִ����������Ż�ȥִ�к󵽵����ݣ����������ִ����˳��
		pWork->set_thread_num(1);	

		pWork->set_core_server(m_pCoreServer);
		pWork->set_mem_block_pool(m_pMsgPool);	// �������ⲿ���� CMemBlockPool ʵ����ָ��

		pWork->set_general_work(this);

		//iRes = regist_task_module(MODULE_ID_MY_LOGIC, m_pLogic, (CCoreServer*)this);	// ע������ģ�飬�˾䲻��ʡ��

		assert(0==iRes);
		if(0!=iRes)
			break;

	}

	for(int i=0; i<m_iWorkerNum; i++)
	{
		iRes = m_pWorker[i]->start();	// ��������ģ�飬�˾䲻��ʡ��
		assert(0==iRes);
	}

	return 0;
}

// ����
int CGeneralWork::stop()
{
	int iRes = 0;

	for(int i=0; i<m_iWorkerNum; i++)
	{
		if(m_pWorker[i])
		{
			iRes = m_pWorker[i]->stop();	// ��������ģ�飬�˾䲻��ʡ��
			assert(0==iRes);
		}
	}

	return 0;
}

// ͨ���󶨹��ţ���һ��ͨ���ŵ�����ֻ����һ���߳���ִ�У��Ӷ���֤�˴�ͨ�������ȵ�������ִ����������Ż�ȥִ�к󵽵����ݡ�
int CGeneralWork::channel_bind_worker_no(LONGLONG lChannelNo)
{
	int iWorkerNo = -1;

	if(lChannelNo>0)
	{
		// ����
		iWorkerNo = lChannelNo % m_iWorkerNum;
	}
	
	return iWorkerNo;
}

// ������Ϣ���������
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
		// ��ʾͨ���Ű󶨹��ˣ���һ��ͨ���ŵ�����ֻ����һ���߳���ִ�У��Ӷ���֤�˴�ͨ�������ȵ�������ִ����������Ż�ȥִ�к󵽵����ݡ�
		int iWorkerNo = channel_bind_worker_no(lChannelNo);	

		CWorker* pWork = m_pWorker[iWorkerNo];
		iRes = pWork->put(pMsgBlock);
	}
	else if(TIMER_CHANNEL_NO==lChannelNo)	// ��ʱ����ͨ����
	{
		int iWorkerNo = m_iWorkerNum-1;		// ����һ������

		CWorker* pWork = m_pWorker[iWorkerNo];
		iRes = pWork->put(pMsgBlock);
	}
	else if (PROFESSION_CHANNEL_NO==lChannelNo) // ר��ͨ����
	{
		int iWorkerNo = m_iWorkerNum-1;		// ����һ������

		CWorker* pWork = m_pWorker[iWorkerNo];
		iRes = pWork->put(pMsgBlock);
	}
	else
	{
		m_pMsgPool->recycle(pMsgBlock);	// ��Ϣ���
	}

	return iRes;
}
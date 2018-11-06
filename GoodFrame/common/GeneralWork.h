
/********************************************************************
	created:	2013/10/07
	created:	7:10:2013   15:33
	filename: 	E:\SixDivisions\GoodFRame\common\Work.h
	file path:	E:\SixDivisions\GoodFRame\common
	file base:	Work
	file ext:	h
	author:		�����
	
	purpose:	ͨ�ù���ģ����
*********************************************************************/

#ifndef GENERAL_WORK_H
#define GENERAL_WORK_H

//class CWorker;
#include "./Worker.h"

// ͨ�ù�����ķ�����
class __declspec(dllexport) CGeneralWork
{
public:
	friend class CCoreServer;

	enum{	WORKER_MAX_NUM = 20,	// �����������
			WORKER_NUM = 6,			// ���˵�Ĭ������
		};

	enum{
		ERR_GWH_pMsgPool_is_null = 10,		// m_pMsgPool �ǿ�ֵ
		ERR_GWH_m_pCoreServer_is_null = 20,	// m_pCoreServer �ǿ�ֵ
		};
public:
	CGeneralWork(void);
	~CGeneralWork(void);

public:

	// ��ʼ
	int start();

	// ����
	int stop();

public:

	// ����ں˿�ܵ�ָ��
	inline CCoreServer* get_core_server();

	// �����ں˿�ܵ�ָ��
	inline void set_core_server(CCoreServer* pCoreServer);

	// ���ù�������
	inline void set_worker_num(int iWorkerNum);

	// ������Ϣ�أ��������ⲿ���� CMemBlockPool ʵ����ָ��
	inline 	void set_mem_block_pool(CMemBlockPool* pMsgPool);

public:

	// ͨ���󶨹��ţ���һ��ͨ���ŵ�����ֻ����һ���߳���ִ�У��Ӷ���֤�˴�ͨ�������ȵ�������ִ����������Ż�ȥִ�к󵽵����ݡ�
	inline int channel_bind_worker_no(LONGLONG lChannelNo);

private:
	// ������Ϣ
	int handle_msg(CMemBlock*& pMsgBlock);

public:

	/* --------------------------------------------------------------------------
	����˵������Ӧ������Ϣ
	���������
		pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
	����������
		pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
	--------------------------------------------------------------------------*/
	virtual TASK_MSG_RESULT OnTask(CMemBlock*& pMsgBlock) = 0;

protected:
	CWorker* m_pWorker[WORKER_MAX_NUM];
	int		 m_iWorkerNum;	// ��������

	CCoreServer*	m_pCoreServer;	// �ں˿�ܵ�ָ��
	CMemBlockPool*	m_pMsgPool;		// ��Ϣ��

public:
	BOOL	m_bIsDB;	// �Ƿ����ݿ�
};

#endif
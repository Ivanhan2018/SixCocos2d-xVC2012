#include "Worker.h"
#include "./PublicHead.h"

#include "./GeneralWork.h"

CWorker::CWorker(void)
{
	m_pGeneralWork = NULL;
}


CWorker::~CWorker(void)
{
}

void CWorker::set_general_work(CGeneralWork* pGeneralWork)
{
	assert(pGeneralWork);
	m_pGeneralWork = pGeneralWork;
}


/* --------------------------------------------------------------------------
����˵������Ӧ������Ϣ
���������
	pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
����������
	pMsgBlock	������Ϣ��ע���Զ�����źţ�������أ����Բο� TASK_MSG_RESULT ��ֵ
--------------------------------------------------------------------------*/
TASK_MSG_RESULT CWorker::OnTask(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// �Զ�����ź�

	assert(pMsgBlock);
	if(!pMsgBlock)
		return stTaskMsgResult;

	assert(m_pGeneralWork);
	if(!m_pGeneralWork)
		return stTaskMsgResult;

	stTaskMsgResult = m_pGeneralWork->OnTask(pMsgBlock);

	return stTaskMsgResult;
}
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
函数说明：响应任务消息
传入参数：
	pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
传出参数：
	pMsgBlock	任务消息，注意自动归池信号，若不归池，可以参考 TASK_MSG_RESULT 的值
--------------------------------------------------------------------------*/
TASK_MSG_RESULT CWorker::OnTask(CMemBlock*& pMsgBlock)
{
	TASK_MSG_RESULT stTaskMsgResult = TMR_AUTO_RECYCLE;	// 自动归池信号

	assert(pMsgBlock);
	if(!pMsgBlock)
		return stTaskMsgResult;

	assert(m_pGeneralWork);
	if(!m_pGeneralWork)
		return stTaskMsgResult;

	stTaskMsgResult = m_pGeneralWork->OnTask(pMsgBlock);

	return stTaskMsgResult;
}
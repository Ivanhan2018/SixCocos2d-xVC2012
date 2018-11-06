#include "./PublicHead.h"
#include "./SendResult.h"

#include "./ServerHandle.h"

CSendResult::CSendResult(void)
{
	m_pServerHandle = NULL;
	m_pSendBlock = NULL;

	set_class_name_flag("CSendResult");
}


CSendResult::~CSendResult(void)
{
}

// 设置对端服务的指针
void CSendResult::set_service_handle(void* pServerHandlep)
{
	m_pServerHandle = pServerHandlep;
}

// 设置消息块的指针
void CSendResult::set_mem_block(CMemBlock*& pSendBlock)
{
	m_pSendBlock = pSendBlock;
}


int CSendResult::OnSendComplete(DWORD dwBytesTransfered)
{
	int				iResult = CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
	CServerHandle* pServerHandle = (CServerHandle*)m_pServerHandle;

	if(dwBytesTransfered > 0)
	{
		iResult = CCompleteResult::COMPLETE_RESULT_OK;
	}

	pServerHandle->OnSendComplete((CSendResult*)this, iResult, m_pSendBlock);

	return iResult;
}

int CSendResult::OnIoComplete(DWORD dwBytesTransfered)
{
	return (DWORD)OnSendComplete(dwBytesTransfered);
}
#include "./PublicHead.h"
#include "./ClientSendResult.h"

#include "CommTcpClient.h"

CClientSendResult::CClientSendResult(void)
{
	m_pMemBlock = NULL;
	m_pCommTcpClient = NULL;
}

CClientSendResult::~CClientSendResult(void)
{
}

// 设置宿主指针
void CClientSendResult::set_comm_tcp_client(CCommTcpClient* pCommTcpClient)
{
	m_pCommTcpClient = pCommTcpClient;
}

// 设置消息块的指针
void CClientSendResult::set_mem_block(CMemBlock*& pMemBlock)
{
	m_pMemBlock = pMemBlock;
}

int CClientSendResult::OnSendComplete(DWORD dwBytesTransfered)
{
	int	iResult = CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;

	assert(m_pCommTcpClient);
	if(!m_pCommTcpClient)
		return iResult;

	if(dwBytesTransfered > 0)
	{
		iResult = CCompleteResult::COMPLETE_RESULT_OK;
	}

	m_pCommTcpClient->OnSendComplete((CClientSendResult*)this, iResult, m_pMemBlock);
	
	return iResult;
}

int CClientSendResult::OnIoComplete(DWORD dwBytesTransfered)
{
	return (DWORD)OnSendComplete(dwBytesTransfered);
}
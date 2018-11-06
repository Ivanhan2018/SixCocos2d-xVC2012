/********************************************************************
	created:	2013/01/24
	created:	20:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef RECV_RESULT_H
#define RECV_RESULT_H

#include "./CompleteResult.h"
#include "./MemBlock.h"

class  __declspec(dllexport) CRecvResult  : public CCompleteResult
{
public:
	CRecvResult(void);
	~CRecvResult(void);

public:
	// 设置消息块的长度
	void	set_msg_block_size(int iMsgBlockSize);
	void	set_service_handle(void* pServerHandlep);

	virtual int OnIoComplete(DWORD dwBytesTransfered);

	int	recv_data();
	int	OnRecvComplete(DWORD dwBytesTransfered);
	

private:

	void*   m_pServerHandle;

	CMemBlock*	m_pRecv;			// 接收的消息块
	int			m_iMsgBlockSize;	// 消息块的长度
};

#endif
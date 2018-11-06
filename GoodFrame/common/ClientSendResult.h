/********************************************************************
	created:	2013/01/24
	created:	20:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		�����
	
	purpose:	
*********************************************************************/

#ifndef SEND_RESULT_H
#define SEND_RESULT_H

#include "CompleteResult.h"
#include "./MemBlock.h"

class CCommTcpClient;

class CClientSendResult : public CCompleteResult
{
public:
	friend class CCommTcpClient;

public:
	enum { SEND_BUF_SIZE	= 2048 };

public:
	CClientSendResult(void);
	~CClientSendResult(void);

public:

	// ��������ָ��
	void set_comm_tcp_client(CCommTcpClient* pCommTcpClient);

	// ������Ϣ���ָ��
	void set_mem_block(CMemBlock*& pMemBlock);

	int	OnSendComplete(DWORD dwBytesTransfered);
	int	OnIoComplete(DWORD dwBytesTransfered);

private:

	CMemBlock*	m_pMemBlock;
	CCommTcpClient* m_pCommTcpClient;
};

#endif
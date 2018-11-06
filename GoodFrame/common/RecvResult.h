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
	// ������Ϣ��ĳ���
	void	set_msg_block_size(int iMsgBlockSize);
	void	set_service_handle(void* pServerHandlep);

	virtual int OnIoComplete(DWORD dwBytesTransfered);

	int	recv_data();
	int	OnRecvComplete(DWORD dwBytesTransfered);
	

private:

	void*   m_pServerHandle;

	CMemBlock*	m_pRecv;			// ���յ���Ϣ��
	int			m_iMsgBlockSize;	// ��Ϣ��ĳ���
};

#endif
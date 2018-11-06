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

#include "./CompleteResult.h"
#include "./MemBlock.h"

class CSendResult : public CCompleteResult
{
public:
	CSendResult(void);
	~CSendResult(void);

public:

	// ���öԶ˷����ָ��
	void set_service_handle(void* pServerHandlep);

	// ������Ϣ���ָ��
	void set_mem_block(CMemBlock*& pSendBlock);

	int	OnSendComplete(DWORD dwBytesTransfered);

	virtual int	OnIoComplete(DWORD dwBytesTransfered);

public:

private:

	void*		m_pServerHandle;
	CMemBlock*	m_pSendBlock;
};

#endif
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

class CCommTcpClient;

class CClientRecvResult  : public CCompleteResult
{
public:
	enum{	CTC_ERR_recv_data = 10,		// ��ȡ����ʧ��
		};

public:
	friend class CCommTcpClient;

public:
	CClientRecvResult(void);
	~CClientRecvResult(void);

public:
	// ������Ϣ��ĳ���
	void	set_msg_block_size(int iMsgBlockSize);
	int		recv_data();

protected:

	// ��������ָ��
	void set_comm_tcp_client(CCommTcpClient* pCommTcpClient);

	virtual int OnIoComplete(DWORD dwBytesTransfered);

	int		OnRecvComplete(DWORD dwBytesTransfered);

private:

	CMemBlock*	m_pRecv;			// ���յ���Ϣ��
	int			m_iMsgBlockSize;	// ��Ϣ��ĳ���

	CCommTcpClient* m_pCommTcpClient;
};

#endif
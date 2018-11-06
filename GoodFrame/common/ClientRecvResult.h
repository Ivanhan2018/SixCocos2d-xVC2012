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

class CCommTcpClient;

class CClientRecvResult  : public CCompleteResult
{
public:
	enum{	CTC_ERR_recv_data = 10,		// 读取数据失败
		};

public:
	friend class CCommTcpClient;

public:
	CClientRecvResult(void);
	~CClientRecvResult(void);

public:
	// 设置消息块的长度
	void	set_msg_block_size(int iMsgBlockSize);
	int		recv_data();

protected:

	// 设置宿主指针
	void set_comm_tcp_client(CCommTcpClient* pCommTcpClient);

	virtual int OnIoComplete(DWORD dwBytesTransfered);

	int		OnRecvComplete(DWORD dwBytesTransfered);

private:

	CMemBlock*	m_pRecv;			// 接收的消息块
	int			m_iMsgBlockSize;	// 消息块的长度

	CCommTcpClient* m_pCommTcpClient;
};

#endif
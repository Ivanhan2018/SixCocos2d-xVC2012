
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

#ifndef ACCEPT_RESULT_H
#define ACCEPT_RESULT_H

#include "./ThreadGuard.h"
#include "./CompleteResult.h"

class __declspec(dllexport) CAcceptResult : public CCompleteResult
{
public:
	enum { OUTPUT_BUF_SIZE = 1024 };

	CAcceptResult(void);
	~CAcceptResult(void);

public:

	// 设置 CCommTcpServer 指针
	void set_comm_tcp_server(CCommTcpServer*	pCommTcpServer);

	virtual int	OnIoComplete(DWORD dwBytesTransfered);

	// 接收缓冲
	BYTE* get_out_buf();

	// 接收缓冲的长度
	DWORD get_out_buf_len();
	

private:
	BYTE m_szOutputBuf[OUTPUT_BUF_SIZE];

	CCommTcpServer*	m_pCommTcpServer;

	//CCriticalSpection  m_lockComplete;	// 锁 Close 的，为了安全（允许嵌套）
										// CAcceptResult 的实例是出池后独立的，并非共用，不存在用锁的道理呀???
};

#endif
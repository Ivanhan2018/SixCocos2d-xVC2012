
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

	// ���� CCommTcpServer ָ��
	void set_comm_tcp_server(CCommTcpServer*	pCommTcpServer);

	virtual int	OnIoComplete(DWORD dwBytesTransfered);

	// ���ջ���
	BYTE* get_out_buf();

	// ���ջ���ĳ���
	DWORD get_out_buf_len();
	

private:
	BYTE m_szOutputBuf[OUTPUT_BUF_SIZE];

	CCommTcpServer*	m_pCommTcpServer;

	//CCriticalSpection  m_lockComplete;	// �� Close �ģ�Ϊ�˰�ȫ������Ƕ�ף�
										// CAcceptResult ��ʵ���ǳ��غ�����ģ����ǹ��ã������������ĵ���ѽ???
};

#endif
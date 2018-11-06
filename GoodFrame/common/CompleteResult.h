/********************************************************************
	created:	2013/01/24
	created:	20:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		侯国江
	
	purpose:	完成端口的完成结果
*********************************************************************/

#ifndef COMPLETE_RESULT_H
#define COMPLETE_RESULT_H 

class CServerHandle;
class CCommTcpServer;

class __declspec(dllexport) CCompleteResult : public OVERLAPPED
{
public:

	enum {	COMPLETE_RESULT_OK			=  0,
			COMPLETE_RESULT_FAIL		= 10,
			COMPLETE_RESULT_SOCKCLOSE	= 20,
			COMPLETE_RESULT_EXIT		= 30,
		 };

public:
	CCompleteResult(void);
	~CCompleteResult(void);

public:
	void	init();
	void	set_service_handle(CServerHandle* pServerHandle);

	virtual int OnIoComplete(DWORD dwBytesTransfered) = 0;
	
	// 获得类名的标识
	char* get_class_name_flag();

	// 设置类名的标识
	void set_class_name_flag(char* pClassNameFlag);

public:
	DWORD				m_dwBytesReceived;

protected:
	CServerHandle*		m_pServerHandle;
	CCommTcpServer*	m_pTcpMsgTranSvr;

private:
	char	m_szClassNameFlag[32];	// 类名的标识
};

#endif
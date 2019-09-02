#ifndef SAMPLE_CLIENT_H
#define SAMPLE_CLIENT_H

#include "../PUBLIC_H/CoreClient.h"//CCoreClient
#include "../common/GerneralListen.h"//CGerneralSink

// 客户端通信类。不用单键模式，是因为一个工程中可能有多个客户端通信类实例。
class CClientComm : public CGerneralSink, public CCoreClient
{
public:
	friend class CDataManageDlg;

public:
	CClientComm(void);
	~CClientComm(void);

protected:		
	//--- 回调函数 ------------------------

	// 响应连接成功
	void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);

	// 响应连接失败
	void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);

	// 响应发送成功
	void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应发送失败，
	void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应关闭服务端
	virtual void OnClose(CLOSE_TYPE iCloseType);

	/* --------------------------------------------------------------------------
	函数说明：响应收包消息
	传入参数：
		pData		收到的数据
		iDataLen	收到的数据的长度
	--------------------------------------------------------------------------*/
	void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应通讯错误的消息
	void OnCommError(char* pszError);

public:
	// 发送一条信息
	void test04();

	// 写入日志文件
	void test11();

private:

};

#endif
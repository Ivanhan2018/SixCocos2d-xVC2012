/*********************************************************
Name：SIX_ClientBase
Desc：SOCKET交互基类接口。
Auth：Cool.Cat@2013-05-08
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_PackageMgr.h>
#include <SIX_Proxy.h>
#include <SIX_SocketClient.h>

class SIX_Proxy;
class SIX_SocketClient;

typedef enum {
	// 连接成功
	CONNECT_SUCCESSED	= 1,
	// 重连成功
	RECONNECT_SUCCESSED,
	// 连接失败
	CONNECT_FAILED,
	// 通讯异常
	COMM_ERROR,
	// 发送失败
	SEND_ERROR
} NETWORK_STATUS;

class SIX_ClientBase:public SIX_SocketClient
{
public:
	SIX_ClientBase();
	virtual ~SIX_ClientBase();
public:
	virtual void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);
	virtual void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);
	virtual void OnCommError(char* pszError);
	virtual void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);
	virtual void OnClose(CLOSE_TYPE iCloseType);
	// 桌子消息
	virtual void OnTableMsg(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	virtual void HandlePacketRaw(int,int,unsigned char*,unsigned int){};
	virtual void OnRelease(){};
public:
	virtual int init(char *ip,int port,char *name,char *pass,bool bReconnected=true,int iReconnectDelay=MAX_RECONNECT_DELAY);
	virtual int start();
	virtual int stop();

	virtual bool getNeedExit();
	virtual void setNeedExit(bool);

	virtual int RandomUser(char* pszName);

private:
	bool m_NeedExit;
};
#ifndef CONNECT_CENTER_SERVER_H
#define CONNECT_CENTER_SERVER_H

#include "CoreClient.h"
#include "PublicHead.h"
#include "CMD_InnerServer.h"
#include "RoomInfo.h"

class CConnectCenterServer : public CCoreClient
{
public:
	CConnectCenterServer();

	~CConnectCenterServer();
	
public:
	//--- 回调函数 -----------------------------------------------B--
	// 响应连接成功
	void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);

	// 响应连接失败
	void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);

	// 响应发送成功
	void OnSend(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应发送失败，
	void OnSendFailed(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应关闭服务端
	void OnClose(CLOSE_TYPE iCloseType);

	/* --------------------------------------------------------------------------
	函数说明：响应收包消息
	传入参数：
		pData		收到的数据
		iDataLen	收到的数据的长度
	--------------------------------------------------------------------------*/
	void OnRecv(int iMainCode, int iSubCode, const BYTE* pData, int iDataLen);

	// 响应通讯错误的消息
	void OnCommError(char* pszError);

private:
	void SetRegisterInfo(CMD_GameServer_Register &gameRegister);

public:
	SERVER_ROOM_INFO m_Config;		// 服务器配置

};

#endif
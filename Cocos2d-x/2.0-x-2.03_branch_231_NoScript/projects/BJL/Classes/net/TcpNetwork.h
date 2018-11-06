//
//  TcpNetwork.h
//  SDH
//
//  Created by zhouwei on 13-6-6.
//
//

#ifndef __SDH__TcpNetwork__
#define __SDH__TcpNetwork__

#include <iostream>
#include "common/Define.h"
#include "ans/BaseObject.h"
#include "event/GBEvent.h"
#include "net/GC_Socket.h"

//class MsgDispatch;
class ClientSock : public BaseObject
{
public:

	ClientSock();
	~ClientSock();

	void update();

	//判断释放连接游戏服务器
	bool isConectServer();

	//连接服务器
	bool connectGameServer(const char* ip, unsigned short port);

	void sendData(WORD wMainCmdID,WORD wSubCmdID);

	void sendData(void* pData,WORD wDataSize,WORD wMainCmdID,WORD wSubCmdID,WORD wRountID);

	void sendData(WORD wMainCmdID,WORD wSubCmdID,void* pData,DWORD wDataSize);

	void recvData(GBEventArg& arg);

	WORD encryptBuffer(BYTE pcbDataBuffer[], WORD wDataSize, WORD wBufferSize);

	WORD crevasseBuffer(BYTE pcbDataBuffer[], WORD wDataSize);

	//随机映射
	WORD SeedRandMap(WORD wSeed);

	//映射发送数据
	BYTE MapSendByte(BYTE const cbData);

	//映射接收数据
	BYTE MapRecvByte(BYTE const cbData);

	//重置
	void reset();

	//关闭套接字
	void closeSocket();

public:
	//void setDispatch(MsgDispatch* p) { m_pMsgDispatch = p; }
private:
	IGC_SocketStream* m_pISocketStrem;
	//MsgDispatch* m_pMsgDispatch;

private:
	BYTE  m_cbSendRound;
	BYTE  m_cbRecvRound;
	DWORD m_dwSendXorKey;
	DWORD m_dwRecvXorKey;
	DWORD m_dwSendPacketCount;
	DWORD m_dwRecvPacketCount;
};


#endif /* defined(__SDH__TcpNetwork__) */

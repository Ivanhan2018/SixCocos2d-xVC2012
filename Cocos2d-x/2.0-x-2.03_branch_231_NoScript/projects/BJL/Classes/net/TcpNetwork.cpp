//
//  TcpNetwork.cpp
//
//  Created by zhouwei on 13-6-6.
//
//

#include "TcpNetwork.h"
#include "common/GlobalDef.h"
#include "common/IDataArchive.h"
#include "common/Define.h"
#include "event/GBEvent.h"
#include "event/GBEventIDs.h"
#include "common/CMD_Plaza.h"
#include "common/GlobalDef.h"
#include "msgDispatch/MsgDispatch.h"
#include "net/common.h"

ClientSock::ClientSock()
{
    m_cbSendRound = 0;
	m_cbRecvRound = 0;
    m_dwSendXorKey = 0;
    m_dwRecvXorKey = 0;
    m_dwSendPacketCount =0;
    m_dwRecvPacketCount = 0;
   
    m_pISocketStrem = NULL;
}


ClientSock::~ClientSock()
{

}

void ClientSock::reset()
{
    m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0x12345678;
	m_dwRecvXorKey=0x12345678;
}

//判断是否连接游戏服务器
bool ClientSock::isConectServer()
{
    if (m_pISocketStrem)
    {
        return  true;
    }
    return false;
}

bool ClientSock::connectGameServer(const char* ip, unsigned short port)
{
    GC_SocketConnector SocketConnector;
    m_pISocketStrem = SocketConnector.Connect(ip, port);
    if (!m_pISocketStrem)
    {
        return false;
    }
    
    reset();
    return  true;
}

void ClientSock::update()
{    
    int nRetCode = 0;
    char szBuffer[4096] = {'\0'};
    int nSize = sizeof(szBuffer);
    while(true)
    {
		if (!m_pISocketStrem)
		{
			return;
		}

        timeval TimeoutValue    = {0, 0};
        
        nRetCode = m_pISocketStrem->CheckCanRecv(&TimeoutValue);
        if (nRetCode == -1)
        {
            break;
        }
        if (nRetCode == 0)
        {
            break;  // if no data arrive
        }

        nRetCode = m_pISocketStrem->Recv((char **)&szBuffer, &nSize);
   
        if (nRetCode < 0)
        {
            closeSocket();
            CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_NETWORKSHUT);
            break;
        }
        
        //printf("the message is:%s\n",szBuffer);
    
        tagBuffer tag;
        memset(tag.dateBuffer, 0, 81920);
        memcpy(tag.dateBuffer, szBuffer, 4096);
        tag.nDataSize = nSize;
        

		GBEvent::instance()->fire(GBEVENT_NETWORK,tag);
		//CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_ANS_NETWORK,&tag);
    }
}

void ClientSock::sendData(WORD wMainCmdID,WORD wSubCmdID)
{
    //构造数据
	BYTE cbDataBuffer[SOCKET_BUFFER];
    memset(cbDataBuffer, 0, SOCKET_BUFFER);
    
	CMD_Head* pHead=(CMD_Head*)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID=wMainCmdID;
	pHead->CommandInfo.wSubCmdID=wSubCmdID;
    
    //加密数据
	WORD wSendSize=sizeof(cbDataBuffer);
	if (!Common_MappedBuffer(cbDataBuffer, wSendSize))
	{
		CCLOG("==================Common_MappedBuffer FAILED===============");
		return ;
	}
    //m_ODSocket.Send(cbDataBuffer,wSendSize);
    m_pISocketStrem->Send((char*)cbDataBuffer,wSendSize);

}

void ClientSock::sendData(void* pData,WORD wDataSize,WORD wMainCmdID,WORD wSubCmdID,WORD wRountID)
{
    CMD_Head* pHead = new CMD_Head;
    pHead->CommandInfo.wMainCmdID = wMainCmdID;
    pHead->CommandInfo.wSubCmdID  = wSubCmdID;
    
    if (!pData || wDataSize <= 0)
    {
        memcpy(pHead + 1,pData,wDataSize);
    }
    //m_ODSocket.Send(pData,wDataSize);
    m_pISocketStrem->Send((char*)pData,wDataSize);
}

void ClientSock::sendData(WORD wMainCmdID,WORD wSubCmdID,void* pData,DWORD wDataSize)
{
    if (wDataSize>SOCKET_PACKET) return;
    
	//构造数据
	BYTE cbDataBuffer[SOCKET_BUFFER];
	memset(cbDataBuffer, 0, SOCKET_BUFFER);

	CMD_Head* pHead=(CMD_Head *)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID=wMainCmdID;
	pHead->CommandInfo.wSubCmdID=wSubCmdID;
	if (wDataSize>0)
	{
		assert(pData!=NULL);
		memcpy(pHead+1,pData,wDataSize);
	}

	/*
	CMD_Buffer tcp_buffer;
	memset(&tcp_buffer,0,sizeof(CMD_Buffer));
	tcp_buffer.Head.CommandInfo.wMainCmdID=wMainCmdID;
	tcp_buffer.Head.CommandInfo.wSubCmdID=wSubCmdID;
	memcpy(&tcp_buffer.cbBuffer,pData,wDataSize);*/	

	//加密数据
	WORD wSendSize = sizeof(CMD_Head) + wDataSize;
	if (!Common_MappedBuffer(cbDataBuffer, sizeof(CMD_Head) + wDataSize))
	{
		CCLOG("==================Common_MappedBuffer FAILED===============");
		return ;
	}
	
	//WORD wSendSize=encryptBuffer(cbDataBuffer,sizeof(CMD_Head) + wDataSize,sizeof(cbDataBuffer));
    CCLOG("send %d_%d,send data size = %d",wMainCmdID,wSubCmdID,wSendSize);

	if (m_pISocketStrem)
	{
		int ret = m_pISocketStrem->Send((char*)cbDataBuffer, wSendSize);
		//CCLOG("wMainCmdID =  %d,wSubCmdID = %d, err:ret == %d",wMainCmdID,wSubCmdID,ret);
	}
	else
	{
		CCLOG("send %d_%d,send data size = %d err:NULL == m_pISocketStrem",wMainCmdID,wSubCmdID,wSendSize);
	}
	
}
void ClientSock::recvData(GBEventArg& arg)
{
    tagBuffer& tag = (tagBuffer&)arg;

    //crevasseBuffer(tag.dateBuffer,tag.nDataSize);
    
    //GBEvent::instance()->fire(GBEVENT_READ,tag);
    //WORD wSubCmdID;
    //void *pBuffer;
    //WORD wDataSize;
    //m_GameFrame.onFrameMessage(wSubCmdID, tag.dateBuffer, tag.nDataSize);
}
//加密数据
WORD ClientSock::encryptBuffer(BYTE pcbDataBuffer[], WORD wDataSize, WORD wBufferSize)
{
   	//效验参数
	//ASSERT(wDataSize >= sizeof(CMD_Head));
	//ASSERT(wBufferSize >= (wDataSize + 2*sizeof(DWORD)));
	//ASSERT(wDataSize <= (sizeof(CMD_Head) + SOCKET_BUFFER));
    
	//调整长度
	WORD wEncryptSize = wDataSize - sizeof(CMD_Command), wSnapCount = 0;
	if ((wEncryptSize % sizeof(DWORD)) != 0)
	{
		wSnapCount = sizeof(DWORD) - wEncryptSize % sizeof(DWORD);
		memset(pcbDataBuffer + sizeof(CMD_Info) + wEncryptSize, 0, wSnapCount);
	}
    
	//效验码与字节映射
	BYTE cbCheckCode = 0;
	for (WORD i = sizeof(CMD_Info); i < wDataSize; i++)
	{
		cbCheckCode += pcbDataBuffer[i];
        
		pcbDataBuffer[i] = MapSendByte(pcbDataBuffer[i]);
        
	}
    
	//填写信息头
	CMD_Head * pHead = (CMD_Head *)pcbDataBuffer;
	pHead->CmdInfo.cbCheckCode = ~cbCheckCode + 1;
	pHead->CmdInfo.wPacketSize = wDataSize;
	pHead->CmdInfo.cbVersion = SOCKET_VER;
    
    

	//创建密钥
	DWORD dwXorKey = m_dwSendXorKey;
	if (m_dwSendPacketCount == 0)
	{        
        srand((unsigned)time(NULL));
		//生成第一次随机种子
        dwXorKey = rand();
        
        dwXorKey = 1;
		//随机映射种子
		dwXorKey = SeedRandMap((WORD)dwXorKey);
		dwXorKey |= ((DWORD)SeedRandMap((WORD)(dwXorKey >> 16))) << 16;
		dwXorKey ^= g_dwPacketKey;
		m_dwSendXorKey = dwXorKey;
		m_dwRecvXorKey = dwXorKey;
	}
    
	//加密数据
	WORD*  pwSeed = (WORD *)(pcbDataBuffer + sizeof(CMD_Info));
	DWORD* pdwXor = (DWORD *)(pcbDataBuffer + sizeof(CMD_Info));
	WORD wEncrypCount = (wEncryptSize + wSnapCount) / sizeof(DWORD);
	for (WORD i = 0; i < wEncrypCount; i++)
	{
		*pdwXor++ ^= dwXorKey;
		dwXorKey = SeedRandMap(*pwSeed++);
		dwXorKey |= ((DWORD)SeedRandMap(*pwSeed++)) << 16;
		dwXorKey ^= g_dwPacketKey;
	}
    
	//插入密钥
	if (m_dwSendPacketCount == 0)
	{
		memmove(pcbDataBuffer + sizeof(CMD_Head) + sizeof(DWORD), pcbDataBuffer + sizeof(CMD_Head), wDataSize);
		*((DWORD *)(pcbDataBuffer + sizeof(CMD_Head))) = m_dwSendXorKey;
		pHead->CmdInfo.wPacketSize += sizeof(DWORD);
		wDataSize += sizeof(DWORD);
	}
    
	//设置变量
	m_dwSendPacketCount++;
	m_dwSendXorKey = dwXorKey;
    
    return wDataSize;
}

//解密数据
WORD ClientSock::crevasseBuffer(BYTE pcbDataBuffer[], WORD wDataSize)
{
    if (m_dwSendPacketCount <=0 || wDataSize < sizeof(CMD_Head))
    {
        CCLOG("data check error!",__FILE__, __LINE__);
        CCLOG("m_dwSendPacketCount = %d,wDataSize = %d",m_dwSendPacketCount, wDataSize);
        return 0;
    }
    
	if(((CMD_Head *)pcbDataBuffer)->CmdInfo.wPacketSize != wDataSize)
    {
        CCLOG("data size error!",__FILE__, __LINE__);
        return 0;
    }
        
	//调整长度
	WORD wSnapCount = 0;
	if ((wDataSize % sizeof(DWORD)) != 0)
	{
		wSnapCount = sizeof(DWORD) - wDataSize % sizeof(DWORD);
		memset(pcbDataBuffer + wDataSize, 0, wSnapCount);
	}
    
	//解密数据
	DWORD dwXorKey = m_dwRecvXorKey;
	DWORD * pdwXor = (DWORD *)(pcbDataBuffer + sizeof(CMD_Info));
	WORD  * pwSeed = (WORD *)(pcbDataBuffer + sizeof(CMD_Info));
	WORD wEncrypCount = (wDataSize + wSnapCount - sizeof(CMD_Info)) / 4;
	for (WORD i = 0; i < wEncrypCount; i++)
	{
		if ((i == (wEncrypCount - 1)) && (wSnapCount > 0))
		{
			BYTE * pcbKey = ((BYTE *) & m_dwRecvXorKey) + sizeof(DWORD) - wSnapCount;
			memcpy(pcbDataBuffer + wDataSize, pcbKey, wSnapCount);
		}
		dwXorKey = SeedRandMap(*pwSeed++);
		dwXorKey |= ((DWORD)SeedRandMap(*pwSeed++)) << 16;
		dwXorKey ^= g_dwPacketKey;
		*pdwXor++ ^= m_dwRecvXorKey;
		m_dwRecvXorKey = dwXorKey;
    }
    
	//效验码与字节映射
	CMD_Head * pHead = (CMD_Head *)pcbDataBuffer;
	BYTE cbCheckCode = pHead->CmdInfo.cbCheckCode;
    
	for (int i = sizeof(CMD_Info); i < wDataSize; i++)
	{
		pcbDataBuffer[i] = MapRecvByte(pcbDataBuffer[i]);
		cbCheckCode += pcbDataBuffer[i];
    }
    
    if (cbCheckCode != 0 )
    {
        CCLOG("check code error",__FILE__, __LINE__);
        CCLOG("wDataSize = %d",wDataSize);
        return 0;
    }
    
    return wDataSize;
}

//随机映射
WORD ClientSock::SeedRandMap(WORD wSeed)
{
	DWORD dwHold = wSeed;
	return (WORD)((dwHold = dwHold * 241103L + 2533101L) >> 16);
}

//映射发送数据
BYTE ClientSock::MapSendByte(BYTE const cbData)
{
	BYTE cbMap = g_SendByteMap[(BYTE)(cbData+m_cbSendRound)];
	m_cbSendRound += 3;
	return cbMap;
}

//映射接收数据
BYTE ClientSock::MapRecvByte(BYTE const cbData)
{
	BYTE cbMap = g_RecvByteMap[cbData] - m_cbRecvRound;
	m_cbRecvRound += 3;
	return cbMap;
}

//关闭套接字
void ClientSock::closeSocket()
{
    if (m_pISocketStrem)
    {
        m_pISocketStrem->CloseSocket();
        m_pISocketStrem = NULL;
    }

    //恢复数据
	m_cbSendRound=0;
	m_cbRecvRound=0;
	m_dwSendXorKey=0;
	m_dwRecvXorKey=0;
	m_dwSendPacketCount=0;
	m_dwRecvPacketCount=0;
    //reset();
    CCLOG("close socket");
}



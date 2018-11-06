#include "cocos2d.h"
#include "ODSocket.h"
#include <stdio.h>
#include <assert.h>
#include <time.h>

#ifdef WIN32
#pragma comment(lib, "wsock32")
#endif

ODSocket::ODSocket(ITCPSocketSink *gameEngine)
{
    m_wRecvSize = 0;
	m_cbSendRound = 0;
	m_cbRecvRound = 0;
	m_dwSendXorKey = 0;
	m_dwRecvXorKey = 0;
	m_dwSendTickCount = 0;
	m_dwRecvTickCount = 0;
	m_dwSendPacketCount = 0;
	m_dwRecvPacketCount = 0;
	
	m_pITCPSocketSink = gameEngine;
	m_ProxyServerType = PROXY_NONE;
	m_cbSocketStatus = SOCKET_STATUS_IDLE;
	
    
	m_RandTimeValue=0;m_RandTimeFirst=0;
}

ODSocket::~ODSocket()
{
}

int ODSocket::Init()
{
#ifdef WIN32
	/*
     http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx
     
     typedef struct WSAData {
     _WORD_ wVersion;								//winsock version
     _WORD_ wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
     char szDescription[WSADESCRIPTION_LEN+1];
     char szSystemStatus[WSASYSSTATUS_LEN+1];
     unsigned short iMaxSockets;
     unsigned short iMaxUdpDg;
     char FAR * lpVendorInfo;
     }WSADATA, *LPWSADATA;
     */
    
	WSADATA wsaData;
#define MAKE_WORD_(a,b) ((_WORD_) (((_BYTE_) (a)) | ((_WORD_) ((_BYTE_) (b))) << 8))
	_WORD_ version = MAKE_WORD_(2, 0);
	
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
        //		cerr << "Initilize winsock error !" << endl;
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int ODSocket::Clean()
{
#ifdef WIN32
	CCLog("Clean WIN32");
	return (WSACleanup());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Clean Android");
	
	return 0;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCLog("Clean IOS");
	return 0;
#endif
}

ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

ODSocket::operator SOCKET ()
{
	return m_sock;
}

//create a socket object win/lin is the same
// af:

bool ODSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET ) {
		return false;
	}
	return true;
}


char  *ODSocket::jiexiyuming(const char *yuming){
    
    char ym[40] ;
    //yuming.copy(ym, 15);
    memcpy(ym, yuming, 40);
    printf("IP:%s \n",yuming);
    struct hostent *hp;
    struct in_addr in;
    struct sockaddr_in local_addr;
    
    hp = gethostbyname(ym);
    if(!(hp=gethostbyname(ym)))
    {
         return "error";
    }
    
    memcpy(&local_addr.sin_addr.s_addr,hp->h_addr,4);
    
    in.s_addr=local_addr.sin_addr.s_addr;
    printf("domain name :%s \n",ym);
    printf("IP:%s \n",inet_ntoa(in));
    
    return inet_ntoa(in);
}



bool ODSocket::Connect(const char* ip, unsigned short port)
{
    //m_RandTimeValue=0;m_RandTimeFirst=0;
	if(m_RandTimeFirst ==0)
	{
		m_RandTimeFirst =1;
	}
	else
	{
		m_RandTimeValue++;
	}
	
    char myIP[15];
    memcpy(myIP, jiexiyuming(ip), 15);
    
    //CC_ASSERT(m_cbSocketStatus == SOCKET_STATUS_IDLE);
    
	
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(myIP);
	svraddr.sin_port = htons(port);
    m_wRecvSize = 0;
	m_cbSendRound = 0;
	m_cbRecvRound = 0;
	m_dwSendXorKey = 0;
	m_dwRecvXorKey = 0;
	m_dwSendPacketCount = 0;
	m_dwRecvPacketCount = 0;
	
	CCLog("m_dwRecvXorKey::%d",m_dwSendXorKey);
	CCLog("m_dwRecvXorKey::%d",m_dwRecvXorKey);
    
	
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
    CCLog("m_sock : %d" , m_sock);
	if ( ret == SOCKET_ERROR ) {
		return false;
        std::cout<<"错误连接"<<std::endl;
	}
    perror("连接成功");
	return true;
}


//网络发送
int ODSocket::Send(void* buf, int len, int flags)
{
    //效验状态
	if (m_sock == INVALID_SOCKET) return false;
	
	int __BYTE__s;
	int count = 0;
    //构造数据
	while ( count < len ) {
        
		__BYTE__s = send(m_sock, (char*)buf + count, len - count, flags);
		if ( __BYTE__s == -1 || __BYTE__s == 0 )
			return -1;
		count += __BYTE__s;
	}
    // m_dwSendTickCount = getticketime() / 1000L;
	return count;
}

_D_WORD_ ODSocket::senddata(_WORD_ wMainCmdID, _WORD_ wSubCmdID)
{
    //效验状态
	if (m_sock == INVALID_SOCKET) return false;
	//if (m_cbSocketStatus != SOCKET_STATUS_CONNECT) return false;
    
	//构造数据
	_BYTE_ cbDataBuffer[SOCKET_TCP_BUFFER];
	TCP_Head * pHead = (TCP_Head *)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID = wMainCmdID;
	pHead->CommandInfo.wSubCmdID = wSubCmdID;
    
	//加密数据
	_WORD_ wSendSize = EncryptBuffer(cbDataBuffer, sizeof(TCP_Head), sizeof(cbDataBuffer));
    
	//发送数据
	return Send(cbDataBuffer, wSendSize);
}

//网络发送
_D_WORD_  ODSocket::SendData(_WORD_ wMainCmdID, _WORD_ wSubCmdID, void * pData, _WORD_ wDataSize)
{
    
	//效验状态
	if (m_sock == INVALID_SOCKET) return false;
	CCLog("测试发送数据");
    
    //连接状态判断 待处理
	//if (m_cbSocketStatus != SOCKET_STATUS_CONNECT) return false;
    
	//效验大小
    //CC_ASSERT(wDataSize <= SOCKET_TCP_BUFFER);
	if (wDataSize > SOCKET_TCP_BUFFER) return false;
    
	//构造数据
	_BYTE_ cbDataBuffer[SOCKET_TCP_BUFFER] = {0};
	TCP_Head * pHead = (TCP_Head *)cbDataBuffer;
	pHead->CommandInfo.wMainCmdID = wMainCmdID;
	pHead->CommandInfo.wSubCmdID = wSubCmdID;
	if (wDataSize > 0)
	{
		//CC_ASSERT(pData != NULL);
		//memset(pHead+1,1,10);wDataSize=10;
		//CopyMemory(pHead + 1, pData, wDataSize);
        memcpy(pHead +1, pData, wDataSize);
	}
    
    
    //    for (int i =0; i<wDataSize; i++) {
    //        std::cout<<cbDataBuffer[i];
    //    }
	_WORD_ wSendSize = EncryptBuffer(cbDataBuffer, sizeof(TCP_Head) + wDataSize, sizeof(cbDataBuffer));
    
	//发送数据
	return Send(cbDataBuffer,  wSendSize);
}


int ODSocket::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}


int ODSocket::Close()
{
#ifdef WIN32
	CCLog("Close WIN32");
	return (closesocket(m_sock));
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Close Android");
	memset(m_cbRecvBuf,0,sizeof(_BYTE_)*(SOCKET_TCP_BUFFER*10));
	int iRet = close(m_sock);
	//
	svraddr.sin_addr.s_addr = 0;
	svraddr.sin_port = 0;
	m_sock =INVALID_SOCKET;
	return (iRet);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCLog("Close IOS");
	return (close(m_sock));
#endif
}


int ODSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool ODSocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
    
	sprintf(ip,
            "%u.%u.%u.%u",
            (unsigned char)p->h_addr_list[0][0],
            (unsigned char)p->h_addr_list[0][1],
            (unsigned char)p->h_addr_list[0][2],
            (unsigned char)p->h_addr_list[0][3]);
	
	return true;
}

//获得系统时间
//_D_WORD_ ODSocket::getticketime(){
// cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);

// return oldTime = now.tv_sec*1000+now.tv_usec/1000;
//}




//网络读取数据



//数据加密，解密，以及使用的函数

//随机映射
_WORD_ ODSocket::SeedRandMap(_WORD_ wSeed)
{
	_D_WORD_ dwHold = wSeed;
	return (_WORD_)((dwHold = dwHold * 241103L + 2533101L) >> 16);
}

//映射发送数据
_BYTE_ ODSocket::MapSend_BYTE_(_BYTE_ const cbData)
{
	_BYTE_ cbMap = g_Send_BYTE_Map[(_BYTE_)(cbData+m_cbSendRound)];
    
	m_cbSendRound = m_cbSendRound + 3;
	return cbMap;
}

//映射接收数据
_BYTE_ ODSocket::MapRecv_BYTE_(_BYTE_ const cbData)
{
	_BYTE_ cbMap = g_Recv_BYTE_Map[cbData] - m_cbRecvRound;
	m_cbRecvRound += 3;
	return cbMap;
}

//解释服务器地址


//加密数据
_WORD_ ODSocket::EncryptBuffer(_BYTE_ pcbDataBuffer[], _WORD_ wDataSize, _WORD_ wBufferSize)
{
	//int i = 0;
	//效验参数
    
	//CC_ASSERT(wDataSize >= sizeof(TCP_Head));
	//CC_ASSERT(wBufferSize >= (wDataSize + 2*sizeof(_D_WORD_)));
	//CC_ASSERT(wDataSize <= (sizeof(TCP_Head) + SOCKET_TCP_BUFFER));
    
	//调整长度
	_WORD_ wEncryptSize = wDataSize - sizeof(TCP_Command), wSnapCount = 0;
	if ((wEncryptSize % sizeof(_D_WORD_)) != 0)
	{
		wSnapCount = sizeof(_D_WORD_) - wEncryptSize % sizeof(_D_WORD_);
		memset(pcbDataBuffer + sizeof(TCP_Info) + wEncryptSize, 0, wSnapCount);
	}
    
	//效验码与字节映射
	_BYTE_ cbCheckCode = 0;
	for (_WORD_ i = sizeof(TCP_Info); i < wDataSize; i++)
	{
		cbCheckCode += pcbDataBuffer[i];
		pcbDataBuffer[i] = MapSend_BYTE_(pcbDataBuffer[i]);
	}
    
	//填写信息头
	TCP_Head * pHead = (TCP_Head *)pcbDataBuffer;
	pHead->TCPInfo.cbCheckCode = ~cbCheckCode + 1;
	pHead->TCPInfo.wPacketSize = wDataSize;
	pHead->TCPInfo.cbDataKind = SOCKET_VER;
    
	//创建密钥
	_D_WORD_ dwXorKey = m_dwSendXorKey;
	if (m_dwSendPacketCount == 0)
	{
		//生成第一次随机种子
		/*GUID Guid;
         CoCreateGuid(&Guid);
         dwXorKey = GetTickCount() * GetTickCount();
         dwXorKey ^= Guid.Data1;
         dwXorKey ^= Guid.Data2;
         dwXorKey ^= Guid.Data3;
         dwXorKey ^= *((_D_WORD_ *)Guid.Data4);*/
        
		_D_WORD_ Guid1 = 12345;
		_D_WORD_ Guid2 = 23456;
		_D_WORD_ Guid3 = 34567;
		_D_WORD_ Guid4 = 45678;
        
		dwXorKey = 10;
		dwXorKey ^= Guid1;
		dwXorKey ^= Guid2;
		dwXorKey ^= Guid3;
		dwXorKey ^= Guid4;
        
		//随机映射种子
		dwXorKey = SeedRandMap((_WORD_)dwXorKey);
		dwXorKey |= ((_D_WORD_)SeedRandMap((_WORD_)(dwXorKey >> 16))) << 16;
		dwXorKey ^= g_dwPacketKey;
		m_dwSendXorKey = dwXorKey;
		m_dwRecvXorKey = dwXorKey;
		
		CCLog("****m_dwRecvXorKey****::%ld",m_dwRecvXorKey);
	}
    
	//加密数据
	_WORD_ * pwSeed = (_WORD_ *)(pcbDataBuffer + sizeof(TCP_Info));
	_D_WORD_ * pdwXor = (_D_WORD_ *)(pcbDataBuffer + sizeof(TCP_Info));
	_WORD_ wEncrypCount = (wEncryptSize + wSnapCount) / sizeof(_D_WORD_);
	for (_WORD_ i = 0; i < wEncrypCount; i++)
	{
		*pdwXor++ ^= dwXorKey;
		dwXorKey = SeedRandMap(*pwSeed++);
		dwXorKey |= ((_D_WORD_)SeedRandMap(*pwSeed++)) << 16;
		dwXorKey ^= g_dwPacketKey;
	}
    
	//插入密钥
	if (m_dwSendPacketCount == 0)
	{
		//MoveMemory(pcbDataBuffer + sizeof(TCP_Head) + sizeof(_D_WORD_), pcbDataBuffer + sizeof(TCP_Head), wDataSize);
        memmove(pcbDataBuffer + sizeof(TCP_Head) + sizeof(_D_WORD_), pcbDataBuffer + sizeof(TCP_Head), wDataSize);
		*((_D_WORD_ *)(pcbDataBuffer + sizeof(TCP_Head))) = m_dwSendXorKey;
		pHead->TCPInfo.wPacketSize += sizeof(_D_WORD_);
		wDataSize += sizeof(_D_WORD_);
	}
    
	//设置变量
	m_dwSendPacketCount++;
	m_dwSendXorKey = dwXorKey;
    
	return wDataSize;
}

//解密数据

_WORD_ ODSocket::CrevasseBuffer(_BYTE_ pcbDataBuffer[], _WORD_ wDataSize)
{
    
	//效验参数
    CC_ASSERT(m_dwSendPacketCount > 0);
    
    CC_ASSERT(wDataSize >= sizeof(TCP_Head));
    
    CC_ASSERT(((TCP_Head *)pcbDataBuffer)->TCPInfo.wPacketSize == wDataSize);
    
    CC_ASSERT(m_dwSendPacketCount > 0);
    
    CC_ASSERT(wDataSize >= sizeof(TCP_Head));
    
    CC_ASSERT(((TCP_Head *)pcbDataBuffer)->TCPInfo.wPacketSize == wDataSize);
    
	//调整长度
	_WORD_ wSnapCount = 0;
	if ((wDataSize % sizeof(_D_WORD_)) != 0)
	{
		wSnapCount = sizeof(_D_WORD_) - wDataSize % sizeof(_D_WORD_);
		memset(pcbDataBuffer + wDataSize, 0, wSnapCount);
		//CCLog("调整长度！");
	}
	//CCLog("****解密：m_dwRecvXorKey****::%ld",m_dwRecvXorKey);
    
	//解密数据
	_D_WORD_ dwXorKey = m_dwRecvXorKey;
	_D_WORD_ * pdwXor = (_D_WORD_ *)(pcbDataBuffer + sizeof(TCP_Info));
	_WORD_  * pwSeed = (_WORD_ *)(pcbDataBuffer + sizeof(TCP_Info));
	_WORD_ wEncrypCount = (wDataSize + wSnapCount - sizeof(TCP_Info)) / 4;
	for (_WORD_ i = 0; i < wEncrypCount; i++)
	{
		if ((i == (wEncrypCount - 1)) && (wSnapCount > 0))
		{
			_BYTE_ * pcbKey = ((_BYTE_ *) & m_dwRecvXorKey) + sizeof(_D_WORD_) - wSnapCount;
            
			//memccpy(pcbDataBuffer + wDataSize, pcbKey, wSnapCount);
            
            //CopyMemory(pcbDataBuffer + wDataSize, pcbKey, wSnapCount);
            
            memcpy(pcbDataBuffer + wDataSize, pcbKey, wSnapCount);
            
		}
		dwXorKey = SeedRandMap(*pwSeed++);
		dwXorKey |= ((_D_WORD_)SeedRandMap(*pwSeed++)) << 16;
		dwXorKey ^= g_dwPacketKey;
		*pdwXor++ ^= m_dwRecvXorKey;
		m_dwRecvXorKey = dwXorKey;
	}
	//效验码与字节映射
	TCP_Head * pHead = (TCP_Head *)pcbDataBuffer;
	_BYTE_ cbCheckCode = pHead->TCPInfo.cbCheckCode;
	//CCLog("效验数据字段 %d" ,cbCheckCode );
	for (int i = sizeof(TCP_Info); i < wDataSize; i++)
	{
		pcbDataBuffer[i] = MapRecv_BYTE_(pcbDataBuffer[i]);
        if (i == sizeof(TCP_Info)) {
            //CCLog("第一个效验数据字段:%d____i=%d" ,pcbDataBuffer[i],i );
        }
		cbCheckCode += pcbDataBuffer[i];
	}
	if (cbCheckCode != 0) CCLog("处理网络数据失败");
    
    
	return wDataSize;
}

//网络读取
_LRESULT_ ODSocket::OnSocketNotifyRead(int wParam, int lParam)
{
	try
	{
		//读取数据
        //CCLog("测试接收数据---begin");
		int m_RandTimeValueTemp =m_RandTimeValue;
		
		int iRetCode = recv(m_sock, (char *)m_cbRecvBuf + m_wRecvSize, sizeof(m_cbRecvBuf) - m_wRecvSize, 0);
        
        if(m_RandTimeValueTemp != m_RandTimeValue )
        {
            //CCLog("测试接收数据---error");
			return 0;
        }
        //CCLog("测试接收数据---succ");
        if (iRetCode == SOCKET_ERROR) {
            m_pITCPSocketSink->OnEventTCPSocketShut(GetSocketID(),0);
        }else{
            
            m_wRecvSize += iRetCode;
            
            //m_dwRecvTickCount = getticketime() / 1000L;
            //变量定义
            
            _WORD_ wPacketSize = 0;
            _BYTE_ cbDataBuffer[SOCKET_TCP_BUFFER+sizeof(TCP_Head)];
            TCP_Head * pHead = (TCP_Head *)m_cbRecvBuf;
            
            while (m_wRecvSize >= sizeof(TCP_Head))
            {
                
                //效验参数
                wPacketSize = pHead->TCPInfo.wPacketSize;
                
                CC_ASSERT(pHead->TCPInfo.cbDataKind == SOCKET_VER);
                CC_ASSERT(wPacketSize <= (SOCKET_TCP_BUFFER + sizeof(TCP_Head)));
                
                if (m_wRecvSize < wPacketSize) return 1;
                
                //拷贝数据
                m_dwRecvPacketCount++;
                //CopyMemory(cbDataBuffer, m_cbRecvBuf, wPacketSize);
                memcpy(cbDataBuffer, m_cbRecvBuf, wPacketSize);
                m_wRecvSize -= wPacketSize;
                
                //MoveMemory(m_cbRecvBuf, m_cbRecvBuf + wPacketSize, m_wRecvSize);
                memmove(m_cbRecvBuf, m_cbRecvBuf + wPacketSize, m_wRecvSize);
                //解密数据
                
				//CCLog("测试解密数据");
                _WORD_ wRealySize = CrevasseBuffer(cbDataBuffer, wPacketSize);
                CC_ASSERT(wRealySize >= sizeof(TCP_Head));
                
                //解释数据
                _WORD_ wDataSize = wRealySize - sizeof(TCP_Head);
                void * pDataBuffer = cbDataBuffer + sizeof(TCP_Head);
                TCP_Command Command = ((TCP_Head *)cbDataBuffer)->CommandInfo;
                
                CCLog("主命令 %d  子命令%d" , Command.wMainCmdID , Command.wSubCmdID);
                
                //内核命令
                if (Command.wMainCmdID == MDM_KN_COMMAND)
                {
                    switch (Command.wSubCmdID)
                    {
                        case SUB_KN_DETECT_SOCKET:	//网络检测
                        {
                            CCLog("******** -(-.-)- *******");
                            //发送数据
                            SendData(MDM_KN_COMMAND, SUB_KN_DETECT_SOCKET, pDataBuffer, wDataSize);
                            break;
                        }
                    }
                    continue;
                }
                
                
                //处理数据
                
                m_pITCPSocketSink->OnEventTCPSocketRead(GetSocketID(), Command, pDataBuffer, wDataSize);
                
                //if (bSuccess == false)  CCMessageBox("处理失败","网络数据处理失败");
                
                //bool bsycess = OnEventMissionRead(Command, pDataBuffer, wDataSize);
                
                //if (bsycess == false) throw "网络数据包处理失败";
                
            };
        }
	}
	catch (...)
	{
		//CloseSocket(SHUT_REASON_EXCEPTION);
        Close();
		return 0;
	}
    
	return 1;
}





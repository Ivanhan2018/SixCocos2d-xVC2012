
#include "./PublicHead.h"
#include "./CommTcpClient.h"


#include "./CoreClient.h"

#include <process.h>

CCommTcpClient::CCommTcpClient(void)
{
	m_pCoreClient = NULL;	// 宿主的指针

	m_hCompletionPort = NULL;

	m_hConnection = INVALID_SOCKET;

	m_pMsgPool = NULL;

	m_addrConnect.sin_family = AF_INET;
	m_addrConnect.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_addrConnect.sin_port = htons((unsigned short)5150);

	m_pStoreBox = NULL;
	m_iMsgBlockSize = 2048;

	m_iMsgPoolInitCount = 256;			// 消息池的最初元素数量
	m_iSendResultPoolInitCount = 256;	// 发送结果池的最初元素数量

	m_bAutoReConnect = true;		// 断线后自动重连
	m_iAutoReConnectTime = 2000;	// 断线后自动重连的间隔时间，单位ms，即断线后多少ms才能再次重连
	m_lConnectSuccedCount = 0;		// 连接成功的次数，用来判断是否断线重连

	m_hThreadShrinkPool = NULL;
	m_uThreadShrinkPoolId = 0;

	m_iPulseCount = 0;	// 脉冲计数器

	set_shrink_pools_time(5*60*1000);	// 收缩各种池的时间，默认是 5分钟
	set_send_heartbeat_time(30*1000);	// 发送心跳包的时间，默认是秒

	m_iCloseType = CLOSE_TYPE_NO;	// 关闭方式，参考 CLOSE_TYPE 宏

	InterlockedExchange(&m_iIsConnect, 0);	// 1表示连接中，0表示断线
}

CCommTcpClient::~CCommTcpClient(void)
{
	// 释放资源
	if(is_valid())
	{
		closesocket(m_hConnection);
		m_hConnection = INVALID_SOCKET;
	}

	if(m_pStoreBox)
	{
		delete m_pStoreBox;
		m_pStoreBox = NULL;
	}
}

// 设置宿主的指针
void CCommTcpClient::set_core_client(CCoreClient* pCoreClient)
{
	m_pCoreClient = pCoreClient;
}

// 设置消息块的长度
void CCommTcpClient::set_msg_block_size(int iMsgBlockSize)
{
	assert(iMsgBlockSize>0);
	m_iMsgBlockSize = iMsgBlockSize;

	// 设置消息块的长度，这一句一定要加，否则出现 ntdll.dll 的崩溃
	m_stRecvResult.set_msg_block_size(iMsgBlockSize);

	if(!m_pStoreBox)
	{
		m_pStoreBox = new CMemBlock(2*iMsgBlockSize+16);	// 加 16 是为了防止边界溢出
	}
}

// 设置发送结果池的最初元素数量
void CCommTcpClient::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	m_iSendResultPoolInitCount = iSendResultPoolInitCount;	
}

// 设置消息池的最初元素数量
void CCommTcpClient::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_iMsgPoolInitCount = iMsgPoolInitCount;	
}

// 设置断线重连的间隔时间，单位ms
void CCommTcpClient::set_reconnect_interval_time(int iAutoReConnectTime)
{
	m_iAutoReConnectTime = iAutoReConnectTime;
}

// 获得断线重连
bool CCommTcpClient::get_reconnect()
{
	return m_bAutoReConnect;
}

// 设置断线重连
void CCommTcpClient::set_reconnect(bool bAutoReConnect)
{
	m_bAutoReConnect = bAutoReConnect;
}

// 获得关闭方式
CLOSE_TYPE CCommTcpClient::get_close_type() 
{
	return m_iCloseType;
}

// 设置关闭方式
void CCommTcpClient::set_close_type(CLOSE_TYPE iCloseType) 
{
	m_iCloseType = iCloseType;
}

// 设置收缩各种池的时间，iShrinkPoolsTime 以 ms 为单位
void CCommTcpClient::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	//m_iShrinkPoolsTime = iShrinkPoolsTime;	

	LONGLONG iPulseCount = iShrinkPoolsTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iShrinkPoolsiPulseCount = iPulseCount;
}

// 设置发送心跳包的时间
void CCommTcpClient::set_send_heartbeat_time(LONGLONG iSendHeartbeatTime)
{
	LONGLONG iPulseCount = iSendHeartbeatTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iSendHeartbeatPulseCount = iPulseCount;
}

// 设置一些常用的 SOCKET 参数
void CCommTcpClient::set_sock_opt(SOCKET s)
{
	// 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历	TIME_WAIT 的过程：
	bool bDontLinger = false;
	setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(bool));

	#if 1
		// 接收缓冲区
		int nRecvBuf = SEND_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

		// 发送缓冲，系统默认的状态发送和接收一次为8688字节(约为8.5K)；
		// 在实际的过程中发送数据和接收数据量比较大，可以设置socket缓冲区，而避免了send(),recv()不断的循环收发：
		int nSendBuf = RECV_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	#else
		int nZero=0;

		// 如果在发送数据的时，希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能：
		::setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(nZero));

		// 同上在recv()完成上述功能(默认情况是将socket缓冲区的内容拷贝到系统缓冲区)：
		::setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&nZero, sizeof(nZero));
	#endif
};

// 初始化
int CCommTcpClient::init()
{
	int iResult = 0;

	int			iError;
	WSADATA		WsaData = {0};
	iError = WSAStartup(MAKEWORD(2,2),&WsaData);
	if (SOCKET_ERROR == iError)
	{
		return 10;	// 执行 WSAStartup 失败
	}

	m_stRecvResult.set_comm_tcp_client(this);

	// 消息池
	m_pMsgPool = new CMemBlockPool(m_iMsgBlockSize, m_iMsgPoolInitCount, 20*m_iMsgPoolInitCount);		
	if(m_pMsgPool)
		m_pMsgPool->init();
	else
		return 20;	// 建立消息池失败

	// 发送结果池
	m_pSendResultPool = new CLightweightPool<CClientSendResult>("发送结果池", m_iSendResultPoolInitCount, 20*m_iSendResultPoolInitCount);		
	if(m_pSendResultPool)
		m_pSendResultPool->init();
	else
		return 40;	// 建立发送结果池失败

	if(is_valid())
	{
		m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;
		close(m_iCloseType);	 // 客户端主动关闭
	}

	m_hConnection = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
   	iError = WSAGetLastError();
	if(!m_hConnection)
		return 50;	// m_hConnection 执行 WSASocket 失败

	set_sock_opt(m_hConnection);

	// 接收缓冲区
	int nRecvBuf = SEND_BUF_SIZE;
	setsockopt(m_hConnection, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//发送缓冲区
	int nSendBuf = RECV_BUF_SIZE;
	setsockopt(m_hConnection, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

	if(m_hCompletionPort)
	{
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;
	}
	m_hCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if(!m_hCompletionPort)
		return 60;	// CreateIoCompletionPort 失败

	// 建立 IOCP 的工作线程
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &thread_work, (void*)this,  CREATE_SUSPENDED, &m_dwThreadId); 
	if(!m_hThread)
		return 70;	// 建立 IOCP 的工作线程失败

	// 建立定时检查的线程
	m_hThreadShrinkPool = (HANDLE)_beginthreadex(NULL, 0, &thread_check, (void*)this,  CREATE_SUSPENDED, &m_uThreadShrinkPoolId); 
	if(!m_hThreadShrinkPool)
		return 90;	// 建立定时检查的线程失败

	return iResult;
}

int CCommTcpClient::start()
{
	int iResult = 0;
	m_bStop = false;

	// 启动定时检查的线程
	ResumeThread(m_hThreadShrinkPool);

	// 启动工作线程
	ResumeThread(m_hThread);

	return iResult;
}

int CCommTcpClient::stop()
{
	int iResult = 0;

	m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;

	power_close();		// 客户端主动关闭

	m_bStop = true;

	// 投递中止完成端口的命令
	::PostQueuedCompletionStatus(m_hCompletionPort, 0, 0, &m_stTerminateResult);

	// 等待 thread_work 线程安全结束
	WaitForSingleObject(m_hThread, INFINITE);

	// 等待定时检查的线程结束
	WaitForSingleObject(m_hThreadShrinkPool, INFINITE);

	return iResult;
}

// IOCP 的工作线程
unsigned __stdcall CCommTcpClient::thread_work(LPVOID lpParameter)
{
	CCommTcpClient*	pThis = (CCommTcpClient*)lpParameter;
	DWORD			dwResult = 0;// while dwResult isn't same as 0 the thread exit

	do
	{
		dwResult = pThis->connect_to_server();
		while((dwResult != CCompleteResult::COMPLETE_RESULT_EXIT) && (dwResult != CCompleteResult::COMPLETE_RESULT_SOCKCLOSE))
		{
			InterlockedExchange(&pThis->m_iIsConnect, 1);	// 1表示连接中，0表示断线
			dwResult = pThis->server_operate();
		}

		// 非结束，且是断线重连状态
		if(!pThis->m_bStop && pThis->m_bAutoReConnect)
		{
			InterlockedExchange(&pThis->m_iIsConnect, 0);	// 1表示连接中，0表示断线
			Sleep(pThis->m_iAutoReConnectTime);	// 睡一会儿再重连
		}
	}while(!pThis->m_bStop && pThis->m_bAutoReConnect);	// 非结束，且是断线重连状态


	return dwResult;
}

// 设置连接地址
void CCommTcpClient::set_connect_addr(const char* szListenAddr)
{
	m_addrConnect.sin_addr.s_addr = inet_addr(szListenAddr);
}

// 设置连接端口
void CCommTcpClient::set_connect_port(unsigned int nPort)
{
	m_addrConnect.sin_port = htons((unsigned short)nPort);
}

/* --------------------------------------------------------------------------
函数说明：连接成功的回调
传入参数：
	iResult	
	bIsReconnect	TRUE 表示断线重连
	addrConnect		要连接的服务端
--------------------------------------------------------------------------*/
void CCommTcpClient::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	#if 0	// 测试用
		char szPrompt[64];
		memset(szPrompt, 0, sizeof(szPrompt));

		char* pszIP = inet_ntoa((in_addr)addrConnect.sin_addr); // 获得IP地址 
		int	  iPort = ntohs(addrConnect.sin_port);				// 获得端口值 

		if(bIsReconnect)
			_snprintf(szPrompt, sizeof(szPrompt)-1, "断线重连成功 %s ：%d \n", pszIP, iPort);
		else
			_snprintf(szPrompt, sizeof(szPrompt)-1, "第一次连接成功 %s ：%d \n", pszIP, iPort);

		printf(szPrompt);
	#endif

	AFTER_CONN_SUCC* pAfterConnSucc = new AFTER_CONN_SUCC;	// 连接成功后
	pAfterConnSucc->bIsReconnect = bIsReconnect;
	pAfterConnSucc->addrConnect = addrConnect;
	pAfterConnSucc->pThis = this;

	#if 1
		// 等待服务器收到连接后初始化数据完毕。
		// 因为一连接成功，并不能马上发送数据，服务器还在初始化这个对端的数据，所以要等一会儿才能响应连接成功，这个等待还只能在线程里面
		m_hThreadAfterConn = (HANDLE)_beginthreadex( NULL, 0, &thread_wait_server_init, (void*)pAfterConnSucc, 0, &m_dwThreadAfterConn );
		if(!m_hThreadAfterConn)
		{
			printf("建立线程 thread_wait_server_init 失败 \n");
		}
	#endif

}

// 等待服务器收到连接后初始化数据完毕，
// 因为一连接成功，并不能马上发送数据，服务器还在初始化这个对端的数据，所以要等一会儿才能响应连接成功，这个等待还只能在线程里面
unsigned __stdcall  CCommTcpClient::thread_wait_server_init(void* pParam) 	
{
	if(pParam)
	{
		AFTER_CONN_SUCC* pAfterConnSucc = (AFTER_CONN_SUCC*)pParam;

		Sleep(300);	// 因为一连接成功，并不能马上发送数据，服务器还在初始化这个对端的数据，所以要等一会儿才能响应连接成功

		pAfterConnSucc->pThis->m_pCoreClient->OnConnect(pAfterConnSucc->bIsReconnect, pAfterConnSucc->addrConnect);

		delete pAfterConnSucc;
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：连接失败的回调
传入参数：
	bIsReconnect	TRUE 表示断线重连
	iError			WSAGetLastError() 产生的错误码	
	addrConnect		要连接的服务端
--------------------------------------------------------------------------*/
void CCommTcpClient::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
#if 0
	char szPrompt[64];
	memset(szPrompt, 0, sizeof(szPrompt));

	char* pszIP = inet_ntoa((in_addr)addrConnect.sin_addr); // 获得IP地址 
	int	  iPort = ntohs(addrConnect.sin_port);				// 获得端口值 

	if(bIsReconnect)
		_snprintf(szPrompt, sizeof(szPrompt)-1, "断线重连失败 %s ：%d \n", pszIP, iPort);
	else
		_snprintf(szPrompt, sizeof(szPrompt)-1, "第一次连接失败 %s ：%d \n", pszIP, iPort);

	printf(szPrompt);
#endif

	m_pCoreClient->OnConnectFail(bIsReconnect, iError, addrConnect);
}

// 响应关闭服务端
void CCommTcpClient::OnClose(CLOSE_TYPE iCloseType)
{
	m_pCoreClient->OnClose(iCloseType);
}

DWORD CCommTcpClient::connect_to_server()
{
	DWORD	dwResult = CCompleteResult::COMPLETE_RESULT_EXIT;
	int		iResult = 0;
	DWORD	dwFlag = 0;
	int		iError;

	iResult = connect(m_hConnection, (sockaddr*)&m_addrConnect, sizeof(m_addrConnect));
	iError = WSAGetLastError();

	// 连接成功的次数，用来判断是否断线重连
	bool bIsReconnect = (m_lConnectSuccedCount>0)? true:false;

	if(0 == iResult)
	{
		::CreateIoCompletionPort((HANDLE)m_hConnection, m_hCompletionPort, 0, 0);
		if(0 == m_stRecvResult.recv_data())	// 正常投递一个读
		{
			dwResult = CCompleteResult::COMPLETE_RESULT_OK;
		}

		m_lConnectSuccedCount++ ; 

		// 响应连接成功
		OnConnect(bIsReconnect, m_addrConnect);
	}
	else
	{
		// 响应连接失败
		OnConnectFail(bIsReconnect, iError, m_addrConnect);
	}

	return dwResult;
}

// 服务操作，主要响应收消息、发消息、Terminate
DWORD CCommTcpClient::server_operate()
{
	DWORD				dwError = 0;
	DWORD				dwResult = -1;
	bool				bResult = false;
	DWORD				dwBytesTransfered = 0;
	CCompleteResult*	pResult = NULL;
	PULONG_PTR			completionkey = 0;
	OVERLAPPED*			pOverlap = NULL;

	bResult = ::GetQueuedCompletionStatus(	m_hCompletionPort,
											&dwBytesTransfered,
											(PULONG_PTR)&completionkey,
											(LPOVERLAPPED*)&pOverlap,
											INFINITE);
	dwError = GetLastError();

	if(0==dwBytesTransfered || !bResult)
	{
		// 在客户端收到消息后立即回发、服务端收到消息后也立即回发的情况下， 
		// 服务端发出 closesocket 指令强制关闭客户端，客户端却无法响应关闭事件??? ，根本不会进到此段函数里面
		printf("收到 0 长度 \n");
	}

	if(pOverlap)
	{
		pResult = (CCompleteResult*)pOverlap;
		if(pResult)
		{
			dwResult = pResult->OnIoComplete(dwBytesTransfered);
		}
	}

	return dwResult;
}

// 主动关闭服务端，目的是让服务端能区别出客户端主动关闭与闪断
int CCommTcpClient::power_close()
{
	if(!is_valid())
		return 10;

	CMemBlock* pPowerCloseBlock = NULL;

	if(m_pMsgPool)
	{
		// 出池一个主动关闭对端的消息块
		m_pMsgPool->retrieve_with_power_close(pPowerCloseBlock, __FUNCTION__);

		if(pPowerCloseBlock)
		{
			send_data(pPowerCloseBlock);	// 向对端发送主动关闭的消息块
		}
	}

	close(CLOSE_TYPE_CLIENT_CLOSE);	// 客户端主动关闭

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：关闭服务端
传入参数：
	bClientClose	TRUE表示客户端主动关闭，FALSE表示被服务端关闭的
返回值：
    成功则返回 TRUE，否则返回 FALSE 。
--------------------------------------------------------------------------*/
bool CCommTcpClient::close(CLOSE_TYPE iCloseType)
{
	CThreadGuard guard(&m_lockClose);

	bool bResult = false;

	if(is_valid())
	{
		closesocket(m_hConnection);
		m_hConnection = INVALID_SOCKET;
		bResult = true;

		m_iCloseType = iCloseType;
		OnClose(m_iCloseType);	// 客户端主动关闭

		// 没有停止、开启了断线重连、被服务端关闭
		//if(!m_bStop && m_bAutoReConnect && !bClientClose)	// 没有停止并且开启了断线重连
		if(!m_bStop && m_bAutoReConnect && CLOSE_TYPE_FLASH_CLOSE==m_iCloseType)	// 没有停止、开启了断线重连、闪断
		{
			m_hConnection = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
	}

	if(CLOSE_TYPE_CLIENT_CLOSE==m_iCloseType || CLOSE_TYPE_NO)	// 客户端主动关闭或者未知原因
	{
		m_bStop = true;
	}

	return bResult;
}

/* --------------------------------------------------------------------------
函数说明：判断包的有效性
传入参数：
	pData				要判断的字节流，第一个包肯定位于字节流的最前端。注意：字节流通常会包含很多个包。
	iDataLen			字节流的长度
	iEveryMsgBlockLen	每个消息包的固定长度，其值通常为 512、1024、2048、4096 等很整齐的值
返回值：
	包是有效的则返回 0 ；
	包是无效的则返回错误码，错误码列表如下：
		10	标志位判断失败
		20	包的长度判断失败
--------------------------------------------------------------------------*/
int CCommTcpClient::is_packeg_valid(const BYTE* pData, int iDataLen)
{
	if( 0 == pData || 0 == iDataLen)
		return false;

	const CORE_MSG_HEAD* pCoreHead = (CORE_MSG_HEAD*)pData;

	if(0xaaaaaaaaaaaaaaaa != pCoreHead->uFlag)	// 标志位判断
	{
		return SHE_CoreHeadFlagFail;	// 标志位判断失败
	}

	// 包头若过来了，但包体还未发过来，就应该等到下一个包完整到达时才判断
	if(pCoreHead->iTotalSize > iDataLen)
		return SHE_PackageNotOver;

	//--- 长度判断 -----------------
	if (pCoreHead->iTotalSize > 0 && pCoreHead->iTotalSize <= m_iMsgBlockSize)
	{
	}
	else
	{
		return SHE_PackageLenFail;	// 包的长度判断失败
	}

	// 加密层判断，待做 ???

	return 0;
};

/* --------------------------------------------------------------------------
函数说明：制做成原子包，将 n 多个小包合成一个完整的包
传入参数：
    iResult	结果值，见 COMPLETE_RESULT_OK 等。
	pRecv	小包，pRecv 是不可以归池的。
返回值：
    成功则返回 0，否则返回错误码如下：
	     5  表示被对端主动关闭
		20  收到包的长度是零
	    40	校验包失败，包是无效的
		50  校验包失败，第一个包之后出现无效包
--------------------------------------------------------------------------*/
int CCommTcpClient::make_atom_msg_block_Old(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCoreClient);
	if(!m_pCoreClient)
		return SHE_m_pCoreClientIsNull;

	CMemBlock* pSmallPackeg = (CMemBlock*)pRecv;	// 小包

	if(pSmallPackeg->length()<=0)
	{
		printf("pSmallPackeg->length()=%d \n", pSmallPackeg->length());
		return SHE_SmallPackegIsZero;	// 收到包的长度是零
	}

	int	iRecvDataSize = 0;
	int	iMsgSize = 0;
	int	iFlag = 0;


	//--- 合并成一个原子包后，就可以出池一个消息块来放此原子包，此消息块就可以递送了 ------------
	//int iTotalSize = 0;

	int iPackegLen = pSmallPackeg->length();			
	int iTempStoreBoxLen = m_pStoreBox->length();	// 测试用，存储箱读写头差值长度

	m_pStoreBox->copy(pSmallPackeg->base(), pSmallPackeg->length());	// 消息进入存储箱

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

	// 判断包的有效性
	int iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());

	if( 0 != iVerifyResult )	// 校验包失败，包是无效的，也可以写入日写
	{
		printf("iVerifyResult=%d \n", iVerifyResult);
		m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;
		close(m_iCloseType);	// 客户端主动关闭

		return SHE_Verify_First_Fail;	// 校验包失败，第一个包是无效的
	}

	bool bFirstHead = true;	// 第一个头

	BYTE* pBody = NULL;	// 包体的长度
	int   iBodyLen = 0;	// 包体

	while(pHead->iTotalSize > 0 && pHead->iTotalSize <= m_iMsgBlockSize  && m_pStoreBox->length() >= pHead->iTotalSize) 
	{
		if(bFirstHead)	// 第一个头，因为已经判断过其有效性了，此处不需再一次判断
		{
			bFirstHead = false;	// 设置成不是第一个头
		}
		else
		{
			pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

			// 判断包的有效性
			iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());

			if( 0 != iVerifyResult )
			{
				printf("iVerifyResult=%d \n", iVerifyResult);
				
				#if 1	// 测试用
				    
				    iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());

					int iMainCode = 0;
					int iSubCode = 0;
					BYTE* pData = NULL;
					int iDataLen = 0;

					// 获得内核消息的真实数据
					m_pMsgPool->get_core_msg_data(m_pStoreBox, &iMainCode, &iSubCode, pData, &iDataLen);

					TEST_USER_INFO* p = (TEST_USER_INFO*)pData;
				#endif
				
				m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;
				close(m_iCloseType);	// 客户端主动关闭

				return SHE_Verify_Other_Fail;	// 校验包失败，第一个包之后出现无效包
			}
		}
		
		// 将原子包发向宿主
		CMemBlock* pAtomMsg = NULL;

		#if 1
			m_pMsgPool->retrieve(&pAtomMsg, __FUNCTION__);	// 出池一个原子消息块
			assert(pAtomMsg);
			if(!pAtomMsg)
				return SHE_pAtomMsg_retrieve_Fail;	// 原子包出池失败
		#else
			// 暂时用于测残包的
			
		#endif

		pAtomMsg->copy(m_pStoreBox->rd_ptr(), pHead->iTotalSize);	

		CORE_MSG_HEAD* pAtomMsgHead = (CORE_MSG_HEAD*)(pAtomMsg->base());	// 原子包的头

		// 是否主动关闭指定对端的指令，返回true表示是，返回false表示否
		if(pAtomMsgHead->is_power_close_peer())
		{
			return SHE_IS_POWER_CLOSED; // 表示被对端主动关闭
		}

		if( pAtomMsg->length()>0)
		{
			int iMainCode = 0;
			int iSubCode = 0;
			BYTE* pData = NULL;
			int iDataLen = 0;

			m_pMsgPool->get_core_msg_data(pAtomMsg, &iMainCode, &iSubCode, pData, &iDataLen);

			const BYTE* cpData = pData;
			m_pCoreClient->OnRecv(iMainCode, iSubCode, cpData, iDataLen);	// 响应收包消息
		}
		else
		{
			m_pCoreClient->OnCommError("CServerHandle::make_atom_msg_block ，pAtomMsg->length() 的值是 0 \n");
		}

		// 不管接收成功与失败，客户端的原子包都要归池
		// 因为客户端的应用层只操作 pData，并不直接操作原子包
		m_pMsgPool->recycle(pAtomMsg);	// 归池

		m_pStoreBox->rd_ptr(pHead->iTotalSize);

		pHead = (CORE_MSG_HEAD*)(m_pStoreBox->rd_ptr());
	}

	if( m_pStoreBox->length() > 0 )	// pRecv 内有不完整的包，保留残包
	{
		// 将残余的内容移到头
		m_pStoreBox->remains_move_to_head();
	}
	else	// pRecv 内都是完整的包，且而都已经处理了
	{
		//m_pStoreBox->reset();
		m_pStoreBox->clear();
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：制做成原子包，将 n 多个小包合成一个完整的包
传入参数：
    iResult	结果值，见 COMPLETE_RESULT_OK 等。
	pRecv	小包，pRecv 是不可以归池的。
返回值：
    成功则返回 0，否则返回错误码参考 SERVER_HANDLE_ERR 枚举：
--------------------------------------------------------------------------*/
int CCommTcpClient::make_atom_msg_block(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCoreClient);
	if(!m_pCoreClient)
	{
		printf("m_pCoreClient 是空值 \n");
		return SHE_m_pCoreClientIsNull;	// m_pCoreClient 是空值
	}

	CMemBlock* pSmallPackeg = (CMemBlock*)pRecv;	// 小包

	if(pSmallPackeg->length()<=0)
	{
		printf("pSmallPackeg->length()=%d \n", pSmallPackeg->length());
		return SHE_SmallPackegIsZero;	// 收到包的长度是零
	}

	int	iRecvDataSize = 0;
	int	iMsgSize = 0;
	int	iFlag = 0;

	//--- 合并成一个原子包后，就可以出池一个消息块来放此原子包，此消息块就可以递送了 ------------

	int iPackegLen = pSmallPackeg->length();			
	int iTempStoreBoxLen = m_pStoreBox->length();	// 测试用，存储箱读写头差值长度

	m_pStoreBox->copy(pSmallPackeg->base(), pSmallPackeg->length());	// 消息进入存储箱

	CORE_MSG_HEAD* pHead = NULL;
	int iVerifyResult = 0;	// 判断包的有效性
	int iCount = 0;

	bool bFirstHead = true;	// 第一个头

	BYTE* pBody = NULL;	// 包体的长度
	int   iBodyLen = 0;	// 包体
	int   iVerifyFailCount = 0;	// 包效验失败的次数

	do
	{
		pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

		// 判断包的有效性
		iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());
		if( 0 != iVerifyResult )
		{
			if(SHE_PackageNotOver==iVerifyResult)	// 包体还未发过来，就应该等到下一个包完整到达时才判断
				break;	// 退出循环

			iVerifyFailCount++;
			printf("iVerifyResult=%d iCount=%d \n", iVerifyResult,iCount);

			// 找到下一个包头的标志位
			bool bFind = false;
			while(m_pStoreBox->length()>0)
			{
				m_pStoreBox->rd_ptr(1);	// 消息存储箱的“读”位置下移一个字节
				pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();
				if(0xaaaaaaaaaaaaaaaa == pHead->uFlag)	// 找到包头啦
				{
					bFind = true;
					break;
				}
			}

			if(bFind)	// 找到包头啦
			{
				continue;
			}
			else	// 消息存储箱根本就没有包头
			{
				m_pStoreBox->reset();	// 消息存储箱刷新
				return SHE_Verify_Fail;
			}
		}

		// 将原子包发向宿主
		CMemBlock* pAtomMsg = NULL;

		#if 1
			m_pMsgPool->retrieve(&pAtomMsg, __FUNCTION__);	// 出池一个原子消息块
			assert(pAtomMsg);
			if(!pAtomMsg)
				return SHE_pAtomMsg_retrieve_Fail;	// 原子包出池失败
		#else
			// 暂时用于测残包的
			
		#endif

		pAtomMsg->copy(m_pStoreBox->rd_ptr(), pHead->iTotalSize);	

		CORE_MSG_HEAD* pAtomMsgHead = (CORE_MSG_HEAD*)(pAtomMsg->base());	// 原子包的头

		// 是否主动关闭指定对端的指令，返回true表示是，返回false表示否
		if(pAtomMsgHead->is_power_close_peer())
		{
			if(pAtomMsg)
				m_pMsgPool->recycle(pAtomMsg);	// 很重要

			return SHE_IS_POWER_CLOSED; // 表示被对端主动关闭
		}

		if( pAtomMsg->length()>0)
		{
			int iMainCode = 0;
			int iSubCode = 0;
			BYTE* pData = NULL;
			int iDataLen = 0;

			m_pMsgPool->get_core_msg_data(pAtomMsg, &iMainCode, &iSubCode, pData, &iDataLen);

			const BYTE* byData = pData;
			m_pCoreClient->OnRecv(iMainCode, iSubCode, byData, iDataLen);	// 响应收包消息
		}
		else
		{
			m_pCoreClient->OnCommError("CServerHandle::make_atom_msg_block ，pAtomMsg->length() 的值是 0 \n");
		}

		// 不管接收成功与失败，客户端的原子包都要归池
		// 因为客户端的应用层只操作 pData，并不直接操作原子包
		m_pMsgPool->recycle(pAtomMsg);	// 归池

		m_pStoreBox->rd_ptr(pHead->iTotalSize);

	} while(pHead->iTotalSize > 0 && pHead->iTotalSize <= m_iMsgBlockSize  && m_pStoreBox->length() >= pHead->iTotalSize) ;

	if( m_pStoreBox->length() > 0 )	// pRecv 内有不完整的包，保留残包
	{
		// 将残余的内容移到头
		m_pStoreBox->remains_move_to_head();
	}
	else	// pRecv 内都是完整的包，且而都已经处理了
	{
		m_pStoreBox->reset();
	}

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：接收小包已完成
传入参数：
    iResult	结果值，见 COMPLETE_RESULT_OK 等。
	pRecv	小包，pRecv 是不可以归池的。
返回值：
    参考 COMPLETE_RESULT_OK、COMPLETE_RESULT_FAIL、COMPLETE_RESULT_SOCKCLOSE、COMPLETE_RESULT_EXIT 等
--------------------------------------------------------------------------*/
int CCommTcpClient::OnRecvComplete(int iResult, const CMemBlock* pRecv)
{
	// 但从安全起见，还是画蛇舔足的加一个锁，心理上会感觉更安全。这也许这个锁是多余的 ???
	CThreadGuardWrite guard(&m_lockRecvComplete);

	//int iMakeAtomRes = 0;
	int iMakeAtomRes = 0;
	int iRecvDataRes = 0;

	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		// 制做成原子包，将 n 多个小包合成一个完整的包
		iMakeAtomRes = make_atom_msg_block(iResult, pRecv);	
		if(0==iMakeAtomRes)
		{
			// 调整 recv_data() 位置，把它放在前面,避免make_whole_packeg()及后面的close()里closesocket后无法产生OnClose因为不这样做那么在close之前无recv
			// 要注意的问题是该处是否会带来副作用,因此需要同步以保证时序
			iRecvDataRes = m_stRecvResult.recv_data();

			if(0!=iRecvDataRes)	// 读失败
			{
				// 读失败通常是指 Socket 已经被关闭啦，但关闭的原因不知。而且此处的关闭也不会被响应的，因为 socket 已经关闭啦。
				m_iCloseType = CLOSE_TYPE_NO;	// 
				close(m_iCloseType);	

				printf("初始是的无效值或者未知原因 \n");

				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}

			#if 0	// 此段没有太大的意义，读失败通常是指 Socket 已经被关闭啦，但关闭的原因不知
				if(0!=iRecvDataRes)	// 读失败
				{
					int iMaxCount = 20;
					int iSleepTime = 500;
					for(int i=0; i<iMaxCount; i++)	// 反复的读 iMaxCount 次
					{
						Sleep(iSleepTime);

						printf("反复的读取第 %d 次 \n", i);

						iRecvDataRes = m_stRecvResult.recv_data();
						if(0==iRecvDataRes)
							break;
					}
				}

				if(0!=iRecvDataRes)	// 反复读取失败
				{
					m_iCloseType = CLOSE_TYPE_WSARECV_ERR;	// 通讯包出错
					close(m_iCloseType);	

					printf("反复的读取都失败啦，主动关闭对端 \n");

					return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
				}
			#endif

		}
	}
	else
	{
		iMakeAtomRes = 180;
	}

	if(iMakeAtomRes>0)
	{
		#if 0
			if(SHE_IS_POWER_CLOSED==iMakeAtomRes)	// 表示表示被对端主动关闭
			{
				set_reconnect(false);	// 因为是表示被对端主动关闭，所以禁止断线重连

				//printf("需要删除打印:OnRecvComplete \n");
				m_iCloseType = CLOSE_TYPE_SERVER_POWER_CLOSE;	// 表示被对端主动关闭
				close(m_iCloseType);	
				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}

			m_iCloseType = CLOSE_TYPE_PACKAGE_ERR;	// 通讯包出错
			close(m_iCloseType);	// 闪断（例如手工禁用【本地连接】的方式模拟路由信号不稳定）不经过这里
									// 服务端 close 关闭与 power_close 关闭都不经过这里
									// 客户端 close 关闭与 power_close 关闭都不经过这里

			return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;

		#else
			switch(iMakeAtomRes)
			{
			case SHE_IS_POWER_CLOSED:	// 表示表示被对端主动关闭
				{
					set_reconnect(false);	// 因为是表示被对端主动关闭，所以禁止断线重连

					m_iCloseType = CLOSE_TYPE_SERVER_POWER_CLOSE;	// 表示被对端主动关闭
					close(m_iCloseType);	
					return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
				}
			case SHE_SmallPackegIsZero:	// 收到包的长度是零
				{
					// 些样的包不需要处理，直接越过就好
					// 投递一个读
					m_stRecvResult.recv_data();

					return CCompleteResult::COMPLETE_RESULT_OK;;
				}
			case SHE_Verify_Fail:	// 校验包失败
				{
					m_iCloseType = CLOSE_TYPE_PACKAGE_ERR;	// 通讯包出错
					close(m_iCloseType);	

					return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
				}
			}
			
		#endif
	}

	return CCompleteResult::COMPLETE_RESULT_OK;
}

/* ------------------------------------------------------------------------
函数说明：响应发送成功
传入参数：
	pSendBlock	发送消息块，无论发送成功或失败，消息块都会由框架系统自动归池，应用层不许将 pSendBlock 归池
--------------------------------------------------------------------------*/
void CCommTcpClient::OnSend(const CMemBlock* pSendBlock)
{
	int iMainCode = 0;
	int iSubCode = 0;
	BYTE* pData = NULL;
	int iDataLen = 0;

	m_pMsgPool->get_core_msg_data((CMemBlock*)pSendBlock, &iMainCode, &iSubCode, pData, &iDataLen);

	m_pCoreClient->OnSend(iMainCode, iSubCode, pData, iDataLen);
}

/* --------------------------------------------------------------------------
函数说明：响应发送失败
传入参数：
	lChannelNo	通道号
	pSendBlock	发送消息块，无论发送成功或失败，消息块都会由框架系统自动归池，应用层不许将 pSendBlock 归池
--------------------------------------------------------------------------*/
void CCommTcpClient::OnSendFailed(const CMemBlock* pSendBlock)
{
	int iMainCode = 0;
	int iSubCode = 0;
	BYTE* pData = NULL;
	int iDataLen = 0;

	m_pMsgPool->get_core_msg_data((CMemBlock*)pSendBlock, &iMainCode, &iSubCode, pData, &iDataLen);

	m_pCoreClient->OnSendFailed(iMainCode, iSubCode, pData, iDataLen);
}

// 发送完成，无论发送成功或失败，消息块都会由框架系统自动归池
void CCommTcpClient::OnSendComplete(CClientSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock)
{
	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		// 回调，发送成功
		OnSend(pSendBlock);	
	}
	else
	{
		// 发关失败
		OnSendFailed(pSendBlock);
	}

	// 无论发送成功或失败，消息块都要归池
	m_pMsgPool->recycle(pSendBlock);	

	// 无论发送成功或失败，都需要归池
	m_pSendResultPool->recycle(pSendResult);	// 发送结果归池
}

/* --------------------------------------------------------------------------
函数说明：发送数据
传入参数：
	lChannelNo	通道号
	pSendBlock	发送的消息块，注意：无论发送成功与失败框架系统都会将 pSendBlock 自动归池，
	                               
返回值：
    成功则返回 0，而且会回调 OnSend 函数。
	失败会回调 OnSendFailed 函数，返回错误码如下：
		10  无效的通道号
		20  无效的 pSendBlock
		30  发送结果出池失败
		80  WSASend 失败
--------------------------------------------------------------------------*/
int CCommTcpClient::send_data(CMemBlock*& pSendBlock)
{
	int		iResult = 0;
	int		nError = 0;
	WSABUF	wsabuf;
	CClientSendResult*	pSendResult = NULL;

	__try
	{
		if(!is_valid())
		{
			iResult = 10;	// 无效的通道号
			__leave;
		}

		if(!pSendBlock)
		{
			iResult = 20;	// 无效的 pSendBlock
			__leave;
		}
		
		m_pSendResultPool->retrieve(&pSendResult);	// 发送结果出池，记得归池
		if(!pSendResult)
		{
			iResult = 30;	// 发送结果出池失败
			__leave;
		}

		pSendResult->set_comm_tcp_client(this);
		pSendResult->set_mem_block(pSendBlock);

		DWORD m_dwBytesReceived = 0;

		wsabuf.buf = (char*)pSendBlock->base();
		wsabuf.len = pSendBlock->length();

		#if 1	// 测试用
			CORE_MSG_HEAD*  pMsgHead = NULL;
			m_pMsgPool->get_core_msg_head(pSendBlock, pMsgHead);
		#endif

		if(!is_valid())	// 在离 WSASend 最近的地方加一道保险
		{
			iResult = 10;	// 无效的通道号
			__leave;
		}

		iResult = WSASend(	m_hConnection,
			&wsabuf,
			1,
			&m_dwBytesReceived,
			0,
			pSendResult,
			NULL);

		if(iResult == 0)
		{
			iResult = 0;
		}
		else
		{
			nError = WSAGetLastError();
			if(WSA_IO_PENDING == nError)
			{
				iResult = 0;
			}
			else
			{
				iResult = 80;	//WSASend 失败
			}
		}
	}
	__finally
	{
		if(iResult>0)	// 发送错误，资源归池
		{
			if(pSendResult)
				m_pSendResultPool->recycle(pSendResult);

			// 如果对端是无效的，向无效的对端发数据根本不会响应 OnSendComplete 些函数
			// 所以必须在此处归池
			if(m_pMsgPool)
				m_pMsgPool->recycle(pSendBlock);	// 消息归池
		}
	}

	return iResult;
}

/* --------------------------------------------------------------------------
函数说明：发送数据
传入参数：
	pSendBlock	发送的消息块，注意：无论发送成功与失败框架系统都会将 pSendBlock 自动归池，                             
返回值：
    成功则返回 0，而且会回调 OnSend 函数。
	失败会回调 OnSendFailed 函数，返回错误码如下：
	     5  出池失败
		10  无效的通道号
		20  无效的 pSendBlock
		30  发送结果出池失败
		80  WSASend 失败
--------------------------------------------------------------------------*/
int CCommTcpClient::send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	if(!is_valid())
		return 10;

	CMemBlock* pMemBlock = NULL;	// 消息块出池，记得归池
	m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, __FUNCTION__);

	if(!pMemBlock)
		return 5;

	return send_data(pMemBlock);
}


/* --------------------------------------------------------------------------
函数说明：发送错误数据，用于测试
传入参数：	pSendBlock	发送的消息块，注意：无论发送成功与失败框架系统都会将 pSendBlock 自动归池，
	                               
返回值：
    成功则返回 0，而且会回调 OnSend 函数。
	失败会回调 OnSendFailed 函数，返回错误码如下：
	     5  出池失败
		10  无效的通道号
		20  无效的 pSendBlock
		30  发送结果出池失败
		80  WSASend 失败
--------------------------------------------------------------------------*/
int CCommTcpClient::send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	if(!is_valid())
		return 10;

	int iRes = 0;
	const int iErrCount = 5;	// 错误的次数

	CMemBlock* pMemBlockErr[iErrCount];	// 错误的消息块出池，记得归池
	memset(pMemBlockErr, 0, sizeof(pMemBlockErr));

	for(int i=0; i<iErrCount; i++)
	{
		m_pMsgPool->retrieve_with_error_content(pMemBlockErr[i], iMainCode, iSubCode, pData, iDataLen, __FUNCTION__);
	}

	CMemBlock* pMemBlock = NULL;	// 正确的消息块出池，记得归池
	m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, __FUNCTION__);

	if(!pMemBlock)
		return 5;

	for(int i=0; i<iErrCount; i++)	// 先发错包
	{
		iRes = send_data(pMemBlockErr[i]);	
	}

	iRes = send_data(pMemBlock);		// 最后发正确的包

	return iRes;
}

// 显示所有的池信息
void CCommTcpClient::display_all_pool()
{
	long long iRetrieveCount = m_pMsgPool->get_retrieve_count();
	long long iRecycleCount = m_pMsgPool->get_recycle_count();
	int iCurCount = m_pMsgPool->get_current_element_count();


	printf("池内情况：\n");
	printf("  m_pMsgPool，       出池数=%I64d 归池数=%I64d，池内当前元素=%d \n",
		iRetrieveCount, iRecycleCount, iCurCount);

	iRetrieveCount = m_pSendResultPool->get_retrieve_count();
	iRecycleCount = m_pSendResultPool->get_recycle_count();
	iCurCount = m_pSendResultPool->get_current_element_count();

	printf("  m_pSendResultPool，出池数=%I64d 归池数=%I64d，池内当前元素=%d \n", 
		   iRetrieveCount, iRecycleCount, iCurCount);
}

// 发送心跳包
int CCommTcpClient::send_heartbeat_packeg()
{
	if(!is_valid())
		return 10;

	int iMainCode = 0;
	int iSubCode = 0;
	CMemBlock* pMemBlock = NULL;	// 消息块出池，记得归池

	// 出池一个携带指定内容的消息块
	int iRes = m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, NULL, 0, __FUNCTION__);
	
	CORE_MSG_HEAD* pMsgHead = NULL;
	m_pMsgPool->get_core_msg_head(pMemBlock, pMsgHead);
	if(!pMsgHead)
		return 10;  // 消息头出错了

	pMsgHead->set_heartbeat();	// 设置成心跳包

	if(0==iRes && pMemBlock)
		send_data(pMemBlock);

	return 0;
}

// 定时检查的线程
unsigned __stdcall CCommTcpClient::thread_check(LPVOID lpParameter)
{
	CCommTcpClient* pThis = (CCommTcpClient*)lpParameter;

	int iInterval = 0;

	while(!pThis->m_bStop)
	{
		pThis->m_iPulseCount++;

		// 收缩一次，以 PULSE_TIME 脉冲为基本单位，即 N 个 PULSE_TIME 收缩一次
		if(0 == pThis->m_iPulseCount % pThis->m_iShrinkPoolsiPulseCount)
		{
			iInterval = pThis->m_pMsgPool->get_current_element_count() - pThis->m_iMsgPoolInitCount;
			if(iInterval > pThis->m_iMsgPoolInitCount)	// 间距大于初值才有收缩的意义
			{
				pThis->m_pMsgPool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pSendResultPool->get_current_element_count() - pThis->m_iSendResultPoolInitCount;
			if(iInterval > pThis->m_iSendResultPoolInitCount)	// 间距大于初值才有收缩的意义
			{
				pThis->m_pSendResultPool->shrink_pool(iInterval, 0.25);
			}

			//printf("各种池收缩一次 \n");
		}

		// 发送一次心跳包
		if(pThis->is_valid() && 0 == pThis->m_iPulseCount % pThis->m_iSendHeartbeatPulseCount)
		{
			//DWORD dwThreadId = GetCurrentThreadId();

			//char szTmp[128] = {0};
			//sprintf(szTmp, "发送心跳包,线程ID=%d 脉冲计数器=%I64d ", dwThreadId, pThis->m_iPulseCount);
			//COften::OutputInfo(szTmp);

			// 发送心跳包
			pThis->send_heartbeat_packeg();
		}

		Sleep(PULSE_TIME);
	}

	return 0;
}
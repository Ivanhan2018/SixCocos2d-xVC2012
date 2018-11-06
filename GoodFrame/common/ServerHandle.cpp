

#include "./ServerHandle.h"

#include "./CommTcpServer.h"

CServerHandle::CServerHandle(void)
{
	m_pCommTcpServer = NULL;

	m_hSocket = INVALID_SOCKET;
	m_lChannelNo = INVALID_CHANNEL_NO;

	m_stRecvResult.set_service_handle((void*)this);

	m_nRecvBufNonius = 0;
	m_nPendingIo = 0;
	m_lHeartbeatTime = 0;

	m_pStoreBox = NULL;
	m_iMsgBlockSize = 2048;

	m_bIsOpen = FALSE;

	m_iPowerClosePeerTime = 0;	// 主动关闭对端的时间

	m_iCloseType = CLOSE_TYPE_FLASH_CLOSE;	// 关闭方式，参考 CLOSE_TYPE 宏
											// 默认是闪断

	m_iVerifyFailCount = 0;	// 包效验失败的次数
}

CServerHandle::~CServerHandle(void)
{
	// 释放资源
	if(INVALID_SOCKET != m_hSocket)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}

	if(m_pStoreBox)
	{
		delete m_pStoreBox;
		m_pStoreBox = NULL;
	}
}

// 设置 CCommTcpServer 指针
void CServerHandle::set_comm_tcp_server(CCommTcpServer*	pCommTcpServer)
{
	m_pCommTcpServer = pCommTcpServer;
}

// 设置消息块的长度
void CServerHandle::set_msg_block_size(int iMsgBlockSize)
{
	assert(iMsgBlockSize>0);
	m_iMsgBlockSize = iMsgBlockSize;

	m_stRecvResult.set_msg_block_size(iMsgBlockSize);

	if(!m_pStoreBox)
	{
		m_pStoreBox = new CMemBlock(2*iMsgBlockSize+16);	// 加 16 是为了防止边界溢出
	}
}


// 设置一些常用的 SOCKET 参数
void CServerHandle::set_sock_opt(SOCKET s)
{
	#if 0
		// 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历	TIME_WAIT 的过程：
		BOOL bDontLinger = FALSE;
		setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));
	#endif

	#if 1
		// 接收缓冲区
		int nRecvBuf = SEND_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

		// 发送缓冲，系统默认的状态发送和接收一次为8688字节(约为8.5K)；
		// 在实际的过程中发送数据和接收数据量比较大，可以设置socket缓冲区，而避免了send(),recv()不断的循环收发：
		int nSendBuf = RECV_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	#else
		/*
			1、一个应用程序通过设定SO_SNDBUF为0把缓冲区关闭，然后发出一个阻塞send()调用。在这样的情况下，系统内核会把应用程序的缓冲区锁定，直到接收方确认收到了整个缓冲区后send()调用才返回。
				似乎这是一种判定你的数据是否已经为对方全部收到的简洁的方法，实际上却并非如此。想想看，即使远端TCP通知数据已经收到，其实也根本不代表数据已经成功送给客户端应用程序，
				比如对方可能发生资源不足的情况，导致AFD.SYS不能把数据拷贝给应用程序。另一个更要紧的问题是，在每个线程中每次只能进行一次发送调用，效率极其低下。

			2、把SO_RCVBUF设为0，关闭AFD.SYS的接收缓冲区也不能让性能得到提升，这只会迫使接收到的数据在比Winsock更低的层次进行缓冲，当你发出receive调用时，
				同样要进行缓冲区拷贝，因此你本来想避免缓冲区拷贝的阴谋不会得逞。

			3、现在我们应该清楚了，关闭缓冲区对于多数应用程序而言并不是什么好主意。只要要应用程序注意随时在某个连接上保持几个WSARecvs重叠调用，那么通常没有必要关闭接收缓冲区。
				如果AFD.SYS总是有由应用程序提供的缓冲区可用，那么它将没有必要使用内部缓冲区。高性能的服务器应用程序可以关闭发送缓冲区，同时不会损失性能。
				不过，这样的应用程序必须十分小心，保证它总是发出多个重叠发送调用，而不是等待某个重叠发送结束了才发出下一个。
				如果应用程序是按一个发完再发下一个的顺序来操作，那浪费掉两次发送中间的空档时间，总之是要保证传输驱动程序在发送完一个缓冲区后，立刻可以转向另一个缓冲区。
			4、看来设置为0是没有什么好处的 。
		*/

		int nZero=0;

		// 如果在发送数据的时，希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能：
		::setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(nZero));

		// 同上在recv()完成上述功能(默认情况是将socket缓冲区的内容拷贝到系统缓冲区)：
		::setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&nZero, sizeof(nZero));
	#endif
};

// 设置关闭类型
void CServerHandle::set_close_type(CLOSE_TYPE iCloseType)
{
	m_iCloseType = iCloseType;
}

// 获得关闭类型
CLOSE_TYPE CServerHandle::get_close_type()
{
	return m_iCloseType;
}

int CServerHandle::new_handle()
{
	int			nZero = 0;

	if(INVALID_SOCKET != m_hSocket)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
	
	m_hSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	if(INVALID_SOCKET==m_hSocket)
		return 10;

	set_close_type(CLOSE_TYPE_FLASH_CLOSE);	 // 暂时默认成闪断，例如手工禁用【本地连接】的方式模拟路由信号不稳定

	set_sock_opt(m_hSocket);

	return 0;
}

// 新到一个连接时初始化一些值
void CServerHandle::init_when_open()
{
	m_iCloseType = CLOSE_TYPE_FLASH_CLOSE;	// 关闭方式，参考 CLOSE_TYPE 宏
	m_pStoreBox->reset();

	m_iVerifyFailCount = 0;	// 包效验失败的次数
}

int CServerHandle::open(sockaddr_in& saLocalAddr, sockaddr_in& saRemoteAddr)
{
	assert(m_pCommTcpServer);

	m_saLocalAddr = saLocalAddr;
	m_saRemoteAddr = saRemoteAddr;

	// 写入日志 
	/*printf("通道号:%d LADDR:%d.%d.%d.%d:%d RADDR:%d.%d.%d.%d:%d \n", 
		m_lChannelNo, 
		saLocalAddr.sin_addr.S_un.S_un_b.s_b1, saLocalAddr.sin_addr.S_un.S_un_b.s_b2,
		saLocalAddr.sin_addr.S_un.S_un_b.s_b3, saLocalAddr.sin_addr.S_un.S_un_b.s_b4,
		ntohs(saLocalAddr.sin_port), 
		saRemoteAddr.sin_addr.S_un.S_un_b.s_b1, saRemoteAddr.sin_addr.S_un.S_un_b.s_b2, 
		saRemoteAddr.sin_addr.S_un.S_un_b.s_b3, saRemoteAddr.sin_addr.S_un.S_un_b.s_b4,
		ntohs(saRemoteAddr.sin_port));*/

	char szBuf[128]={0};
	sprintf(szBuf,"连接通道号:%d RADDR:%d.%d.%d.%d:%d", 
		m_lChannelNo, 
		//saLocalAddr.sin_addr.S_un.S_un_b.s_b1, saLocalAddr.sin_addr.S_un.S_un_b.s_b2,
		//saLocalAddr.sin_addr.S_un.S_un_b.s_b3, saLocalAddr.sin_addr.S_un.S_un_b.s_b4,
		//ntohs(saLocalAddr.sin_port), 
		saRemoteAddr.sin_addr.S_un.S_un_b.s_b1, saRemoteAddr.sin_addr.S_un.S_un_b.s_b2, 
		saRemoteAddr.sin_addr.S_un.S_un_b.s_b3, saRemoteAddr.sin_addr.S_un.S_un_b.s_b4,
		ntohs(saRemoteAddr.sin_port));
	COften::OutputInfo(szBuf);

	int iResult = 0;
	HANDLE  hTmp = NULL;

	__try
	{
		hTmp = ::CreateIoCompletionPort((HANDLE)m_hSocket, m_pCommTcpServer->m_hCompletionPort, 0, 0);
		if(!hTmp)
		{
			
			iResult = 10;
			__leave;
		}

		if(0 == m_stRecvResult.recv_data())
		{
			::InterlockedIncrement((PLONG)&m_nPendingIo);
		}
		else
		{
			iResult = 20;
			__leave;
		}
	}
	__finally
	{
		if(0==iResult)
		{
			m_bIsOpen = TRUE;

			// 新到一个连接时初始化一些值
			init_when_open();

			// 回调，连接成功
			m_pCommTcpServer->OnConnect(m_lChannelNo, saLocalAddr, saRemoteAddr);
			::InterlockedExchange64(&m_lHeartbeatTime, GetTickCount64());
		}
		else
		{
			m_bIsOpen = FALSE;

			// 回调，连接失败
			m_pCommTcpServer->OnConnectFail(saLocalAddr, saRemoteAddr, iResult);
		}
	}

	return iResult;
}

// 关闭对端
BOOL CServerHandle::close(CLOSE_TYPE iCloseType)
{
	CThreadGuard guard(&m_lockClose);
	assert(m_pCommTcpServer);

	if(INVALID_SOCKET==m_hSocket)	// 无效的通道号
		return FALSE;

	m_bIsOpen = FALSE;

	SOCKET sockClose = m_hSocket;
	
	closesocket(m_hSocket);
	m_hSocket = INVALID_SOCKET;

	// 对端归池
	m_pCommTcpServer->m_pServerHandlePool->recycle(this);	

	m_nRecvBufNonius = 0;

	memset(&m_saLocalAddr, 0, sizeof(sockaddr_in));
	memset(&m_saRemoteAddr, 0, sizeof(sockaddr_in));

	m_pCommTcpServer->OnClose(m_lChannelNo, sockClose, iCloseType);

	return TRUE;
}

/* --------------------------------------------------------------------------
函数说明：接收完成
传入参数：
    iResult	结果值，见 COMPLETE_RESULT_OK 等
	pRecv	小包，pRecv 是不可以归池的
返回值：
    参考 COMPLETE_RESULT_OK、COMPLETE_RESULT_FAIL、COMPLETE_RESULT_SOCKCLOSE、COMPLETE_RESULT_EXIT 等
--------------------------------------------------------------------------*/
int CServerHandle::OnRecvComplete(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCommTcpServer);

	int		iMakeAtomRes = 0;
	int		iRecvDataRes = 0;
	LONG	nPendingIo = 0;

	#if 0	// 此段不能删除，是原理性的讲解与演示
			// 设置 recv_data 中的 wsabuf.len = m_pRecv->size() 的情况下，客户端批量发包，在服务端接收线程至少有两个，
			// 设置 recv_data 中的 wsabuf.len = 16; 的情况下，客户端的一个原子包，在服务端接收线程至少有两个，
			// 奇怪的现象：按照普通人对多线程的理解：当第一个线程被 Sleep 阻塞后，另外的空闲线程会处理收到的值，这种理解是错的。
			//             当第一个线程被 Sleep 阻塞住后，就出现等待 iWaitN ms，别的空闲线程会并不收到此 socket 发来的消息。
	        //             当 wsabuf.len = 16 时，客户端的一个原子包，在服务端的第一个线程里也是被 Sleep 阻塞，而且不会由另一个线程来接收此客户端剩下的包 。
			// 结论：同一个 Socket 在一个 IOCP 周期内收取内容（也许接收缓冲内有n个包的内容）一定是由同一个线程来完成的。
			//       但不保证下一下 IOCP 周期内收取内容还是由同一个线程来接收，实时表明在两个 IOCP 周期往往是由不同的线程来接收内容的。
			//       客户端发包的顺序在服务端也是严格按顺序接收的，不会后发的包先至。

	    
		int iWaitN = 15*1000;	// ms
		static long volatile uAccess=0;	// 目的是仅仅阻塞一个性程，而且仅仅阻塞一次
										// 0为不通过，1为通过
		if(0==uAccess)
		{
			InterlockedExchange(&uAccess, 1);
			Sleep(iWaitN );
		}
	#endif

	#if 0	// 此段不能删除，是原理性的讲解与演示
			// 设置 recv_data 中的 wsabuf.len = m_pRecv->size() 的情况下，客户端批量发包，在服务端接收线程至少有两个，
			// 设置 recv_data 中的 wsabuf.len = 16; 的情况下，客户端的一个原子包，在服务端接收线程至少有两个，
			// 结果：显示同一个客户端批量发送时接收线程至少有两个。
			// 结论：两个 IOCP 周期往往是由不同的线程来接收内容的，注意：同一个 Socket 在一个 IOCP 周期内收取内容（也许接收缓冲内有n个包的内容）一定是由同一个线程来完成的
		    //       客户端发包的顺序在服务端也是严格按顺序接收的，不会后发的包先至。     
			DWORD dwCurrent = GetCurrentThreadId();
			printf("OnRecvComplete %d ，包长：%d \n", dwCurrent, ((CMemBlock*)pRecv)->length());
	#endif

	//// 但从安全起见，还是画蛇舔足的加一个锁，心理上会感觉更安全。这也许这个锁是多余的 ???
	//CThreadGuardWrite guard(&m_lockRecvComplete);

	::InterlockedDecrement((PLONG)&m_nPendingIo);

	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		if(m_nPendingIo < MAX_PENDING_IO)
		{ 
			// 制做成原子包，将 n 多个小包合成一个完整的包
			iMakeAtomRes = make_atom_msg_block(iResult, pRecv);	
			if(0==iMakeAtomRes)
			{
				// 投递一个读
				iRecvDataRes = m_stRecvResult.recv_data();
				
				if(0!=iRecvDataRes)	// 读失败
				{
					// 读失败通常是指 Socket 已经被关闭啦，但关闭的原因不知。而且此处的关闭也不会被响应的，因为 socket 已经关闭啦。
					m_iCloseType = CLOSE_TYPE_NO;	// 
					close(m_iCloseType);	

					char szTmp[64] = {0};
					sprintf(szTmp, "OnRecvComplete 中 recv_data 失败, WSAGetLastError=%d  ", iRecvDataRes);
					COften::OutputInfo(szTmp);

					return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
				}
				else
				{
					::InterlockedIncrement((PLONG)&m_nPendingIo);
				}
			}
		}
		else	// 对端在短时间内发来太多的包，将此对端关闭
		{ 
			iMakeAtomRes = 220;
		}

		::InterlockedExchange64(&m_lHeartbeatTime, GetTickCount64());
	}
	else
	{
		//printf("需要删除打印:OnRecvComplete \n");
		set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
		close(get_close_type());
	}

	if(iMakeAtomRes>0)
	{
		switch(iMakeAtomRes)
		{
		case SHE_IS_POWER_CLOSED:	// 表示客户端主动关闭
			{
				m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;	// 表示客户端主动关闭
				close(m_iCloseType);	
				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}
		case SHE_SmallPackegIsZero:	// 收到包的长度是零
			{
				// 些样的包不需要处理，直接越过就好
				// 投递一个读
				m_stRecvResult.recv_data();
				::InterlockedIncrement((PLONG)&m_nPendingIo);

				return CCompleteResult::COMPLETE_RESULT_OK;
			}
		case SHE_Verify_Fail:	// 校验包失败
			{
				set_close_type(CLOSE_TYPE_PACKAGE_ERR);	// 通讯包出错
				close(get_close_type());				// 闪断（例如手工禁用【本地连接】的方式模拟路由信号不稳定）不经过这里
														// 服务端 close 关闭与 power_close 关闭都不经过这里
														// 客户端 close 关闭与 power_close 关闭都不经过这里

				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}
		default:
			{
				set_close_type(CLOSE_TYPE_PACKAGE_ERR);	// 通讯包出错
				close(get_close_type());				// 闪断（例如手工禁用【本地连接】的方式模拟路由信号不稳定）不经过这里
														// 服务端 close 关闭与 power_close 关闭都不经过这里
														// 客户端 close 关闭与 power_close 关闭都不经过这里

				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}
		}
	}

	return CCompleteResult::COMPLETE_RESULT_OK;
}

/* --------------------------------------------------------------------------
函数说明：发送
传入参数：
	pSendBlock		发送的内容
返回值：
    成功则返回 0，但如果出现IO错误，会回调 OnSendFailed 函数
	失败返回错误码如下：
		10  无效的通道号
		20  pSendBlock 为空
		30  pSendResult 出池失败
		80  WSASend 失败
--------------------------------------------------------------------------*/
int CServerHandle::send_data(CMemBlock*& pSendBlock)
{
	assert(m_pCommTcpServer);

	int		iResult = 0;
	int		iError = 0;
	WSABUF	wsabuf;

	CSendResult*	pSendResult = NULL;
	DWORD m_dwBytesReceived = 0;

	__try
	{
		if(!is_valid())
		{
			iResult = 10;	// 无效的通道号
			__leave;
		}

		if(!pSendBlock)
		{
			iResult = 20;
			__leave;
		}

		m_pCommTcpServer->m_pSendResultPool->retrieve(&pSendResult);	// 发送结果出池，记得归池
		if(!pSendResult)
		{
			iResult = 30;	// pSendResult 出池失败
			__leave;
		}

		pSendResult->set_service_handle((void*)this);
		pSendResult->set_mem_block(pSendBlock);

		wsabuf.buf = (char*)pSendBlock->base();
		wsabuf.len = pSendBlock->length();

		if(!is_valid())	// 在离 WSASend 最近的地方加一道保险
		{
			iResult = 10;	// 无效的通道号
			__leave;
		}

		iResult = WSASend(
							get_handle(),
							&wsabuf,
							1,
							&m_dwBytesReceived,
							0,
							pSendResult,
							NULL);

		if(iResult == 0)
		{
			iResult = 0;
			__leave;
		}
		else
		{
			iError = WSAGetLastError();
			if(WSA_IO_PENDING == iError)	// 在发送的途中
			{
				iResult = 0;
			}
			else
			{
				// 例如 WSAECONNRESET 10054 就是在大指量发给对端

				iResult = 80;	//WSASend 失败
			}
		}
	}
	__finally
	{
		if(iResult>0)	// 发送错误，资源归池
		{
			if(pSendResult)
				m_pCommTcpServer->m_pSendResultPool->recycle(pSendResult);	// 对端归池

			// 如果对端是无效的，向无效的对端发数据根本不会响应 OnSendComplete 些函数
			// 所以必须在此处归池
			if(m_pCommTcpServer && m_pCommTcpServer->m_pMsgPool)
				m_pCommTcpServer->m_pMsgPool->recycle(pSendBlock);	// 消息归池
		}
	}

	return iResult;
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
int CServerHandle::is_packeg_valid(const BYTE* pData, int iDataLen)
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
		char szBuf[256]={0};
		sprintf(szBuf,"错误包，m_iMsgBlockSize=%d; iDataLen=%d-----标志位=%d; 指令状态=%d; 整个消息的长度=%d; 通道号=%d; 主消息=%d;  子消息=%d", 
			m_iMsgBlockSize, iDataLen, pCoreHead->uFlag, pCoreHead->lCordState, pCoreHead->iTotalSize, pCoreHead->lChannelNo, pCoreHead->iMainCode, pCoreHead->iSubCode);
		COften::OutputError(szBuf);
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
    成功则返回 0，否则返回错误码参考 SERVER_HANDLE_ERR 枚举：
--------------------------------------------------------------------------*/
int CServerHandle::make_atom_msg_block(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCommTcpServer);
	if(!m_pCommTcpServer)
	{
		printf("m_pCommTcpServer 是空值 \n");
		return SHE_pCommTcpServerIsNull;	// m_pCommTcpServer 是空值
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

	do
	{
		pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

		// 判断包的有效性
		iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());
		if( 0 != iVerifyResult )
		{
			if(SHE_PackageNotOver==iVerifyResult)	// 包体还未发过来，就应该等到下一个包完整到达时才判断
				break;	// 退出循环

			m_iVerifyFailCount++;
			printf("错包次数%d，错包标识%d \n", m_iVerifyFailCount, iVerifyResult);

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
				#if ERROR_PACKAGER_CUT	// 错包断开对端
					m_pStoreBox->reset();	// 消息存储箱刷新
					return SHE_Verify_Fail;

				#else	// 错包宽容对端（不断开，等待下一个正确的包）
					if(m_iVerifyFailCount < ERROR_PACKAGER_UP_LIMIT)	// 还没到错包的上限值
					{
						continue;
					}
					else	// 到达了错包的上限值
					{
						printf("到达了错包的上限值，即将断开对端 \n");
						m_pStoreBox->reset();	// 消息存储箱刷新
						return SHE_Verify_Fail;
					}

				#endif
			}
		}

		// 将原子包发向宿主
		CMemBlock* pAtomMsg = NULL;

		#if 1
			m_pCommTcpServer->m_pMsgPool->retrieve(&pAtomMsg, __FUNCTION__);	// 出池一个原子消息块
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
				m_pCommTcpServer->m_pMsgPool->recycle(pAtomMsg);	// 很重要

			return SHE_IS_POWER_CLOSED; // 表示客户端主动关闭
		}

		if( pAtomMsg->length()>0)
		{
			pAtomMsgHead->lChannelNo = m_lChannelNo;	// 通道号赋值

			pAtomMsgHead->dwPeerIP = m_saRemoteAddr.sin_addr.S_un.S_addr;	// 获得数数值型的IP地址	;

			m_pCommTcpServer->OnRecv(m_lChannelNo, pAtomMsg);	// 响应收包消息
		}
		else
		{
			m_pCommTcpServer->m_pMsgPool->recycle(pAtomMsg);	// 归池
			m_pCommTcpServer->OnCommError(m_lChannelNo, "CServerHandle::make_atom_msg_block ，pAtomMsg->length() 的值是 0 \n");
		}

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

// 发送完成，注意：如果对端是无效的，向无效的对端发数据根本不会响应 OnSendComplete 些函数
void CServerHandle::OnSendComplete(CSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock)
{
	assert(m_pCommTcpServer);

	::InterlockedDecrement((PLONG)&m_nPendingIo); 
	
	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		::InterlockedExchange64(&m_lHeartbeatTime, GetTickCount64());

		// 回调，发送成功
		m_pCommTcpServer->OnSend(m_lChannelNo, pSendBlock);	
	}
	else
	{
		// 发关失败
		m_pCommTcpServer->OnSendFailed(m_lChannelNo, pSendBlock);
	}

	// 无论发送成功或失败，消息块都要归池
	m_pCommTcpServer->m_pMsgPool->recycle(pSendBlock);	

	// 无论发送成功或失败，都需要归池
	m_pCommTcpServer->m_pSendResultPool->recycle(pSendResult);	// 发送结果归池
}

void CServerHandle::test()
{

}

/* --------------------------------------------------------------------------
函数说明：检查心跳
返回值：
     0  正常
	10  心跳超时，对端死了
--------------------------------------------------------------------------*/
int CServerHandle::check_heartbeat()
{
	assert(m_pCommTcpServer);

	int iResult = 0;

	LONGLONG lCurrent = (LONGLONG)GetTickCount64();

	if(lCurrent - m_lHeartbeatTime <= m_pCommTcpServer->m_iNoHeartbeatDieTime)	// 正常
		iResult = 0;
	else	// 心跳超时，对端死了
		iResult = 10;
	
	return iResult;
}
#include "./PublicHead.h"
#include "./AcceptResult.h"

#include "./ServerHandle.h"
#include "./CommTcpServer.h"

CAcceptResult::CAcceptResult(void)
{
	m_pCommTcpServer = NULL;

	memset(m_szOutputBuf, 0, sizeof(m_szOutputBuf));
	m_dwBytesReceived = 0;

	set_class_name_flag("CAcceptResult");

}

CAcceptResult::~CAcceptResult(void)
{
}

// 设置 CCommTcpServer 指针
void CAcceptResult::set_comm_tcp_server(CCommTcpServer*	pCommTcpServer)
{
	m_pCommTcpServer = pCommTcpServer;
}

BYTE* CAcceptResult::get_out_buf()
{
	return m_szOutputBuf;
}

DWORD CAcceptResult::get_out_buf_len()
{
	return sizeof(m_szOutputBuf);
}

int CAcceptResult::OnIoComplete(DWORD dwBytesTransfered)
{
	//CThreadGuard  guard(&m_lockComplete);

	assert(m_pCommTcpServer);

	#if 0
		// 测试用，检验能否从多个 IOCP 线程中来到此函数
		// 结果：会从不同的 IOCP 线程中来到此函数
		DWORD dwID = GetCurrentThreadId();
		static int iFlag = 0;
		if(0==iFlag)
		{
			iFlag = 1;
			Sleep(20000);
		}

	#endif

	DWORD		dwResult = CCompleteResult::COMPLETE_RESULT_FAIL;
	sockaddr*	pLocalAddr = NULL;
	sockaddr*	pRemoteAddr = NULL;
	DWORD		dwAddrSize = sizeof(sockaddr_in) + 16;	
	int			dwLocalSize = 0, dwRemoteSize = 0;
	int			iSeconds;
	int			iBytes = sizeof(iSeconds);
	int			iError = 0;

	int iResult = 0;

	iError = getsockopt(m_pServerHandle->get_handle(), SOL_SOCKET, SO_CONNECT_TIME, (char*)&iSeconds, (int*)&iBytes);
	if((iError == NO_ERROR) && (iSeconds != -1)) 
	{
		// GetAcceptExSockaddrs 是专门为 AcceptEx 函数准备的，它将 AcceptEx 接受的第一块数据中的本地和远程机器的地址返回给用户。
		GetAcceptExSockaddrs(	m_szOutputBuf,			// 指向传递给AcceptEx函数接收客户第一块数据的缓冲区
								m_dwBytesReceived,		// 缓冲区的大小，必须和传递给AccpetEx函数的一致
								dwAddrSize,				// 为本地地址预留的空间大小，必须和传递给AccpetEx函数一致
								dwAddrSize,				// 为远程地址预留的空间大小，必须和传递给AccpetEx函数一致
								&pLocalAddr,			// 用来返回连接的本地地址
								&dwLocalSize,			// 用来返回本地地址的长度
								&pRemoteAddr,			// 用来返回远程地址
								&dwRemoteSize);			// 用来返回远程地址的长度
			
		#if _DEBUG
			char* szIP = NULL;
			sockaddr_in* pLocal = (sockaddr_in*)pLocalAddr;		// 本地地址
			sockaddr_in* pRemote = (sockaddr_in*)pRemoteAddr;	// 对端地址

			int iPort = ntohs(pLocal->sin_port);			// 获得端口值

			DWORD dwIP =  pLocal->sin_addr.S_un.S_addr;	// 获得数数值型的IP地址	

			szIP = inet_ntoa((in_addr)pLocal->sin_addr);	// 获得字串型的IP地址

			//delete szIP;	// 不能释放，否则会崩溃
		#endif
			
		iResult = m_pServerHandle->open(*(sockaddr_in*)pLocalAddr, *(sockaddr_in*)pRemoteAddr);

		if(iResult>0)	// 找开失败
		{
			printf("m_pServerHandle->Open 失败，错误码：%d \n", iResult);

			if(m_pServerHandle)
			{
				m_pCommTcpServer->m_pServerHandlePool->recycle(m_pServerHandle);	// 对端服务归池
			}
		}
		
		// 打开成功了，再次投递一个【连接】
		m_pCommTcpServer->request_accept();

		dwResult = CCompleteResult::COMPLETE_RESULT_OK;
	}
	else 
	{
		dwResult = CCompleteResult::COMPLETE_RESULT_FAIL;

		if(!m_pCommTcpServer->m_bIsExit)
		{
			//printf("CAcceptResult::OnIoComplete 失败，socket=%d, iSeconds=%d, 错误码：%d \n", 
			//			m_pServerHandle->get_handle(), iSeconds, WSAGetLastError());

			printf("socket=%d 已关闭, iSeconds=%d, 错误码：%d \n", 
						m_pServerHandle->get_handle(), iSeconds, WSAGetLastError());
		}
	}

	m_pCommTcpServer->m_pAcceptResultPool->recycle(this);	// 连接结果归池

	//printf("CAcceptResult 实例正常归池，this=%d \n", (DWORD)this);

	return dwResult;
}
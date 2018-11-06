
#include "./PublicHead.h"
#include "./CommTcpServer.h"
#include "./CoreServer.h"

#include <process.h>

CCommTcpServer::CCommTcpServer(void)
{
	m_pCoreServer = NULL;

	SYSTEM_INFO			sysinfo = { 0 };
	GetSystemInfo(&sysinfo);
	m_nThreadCount = (int)sysinfo.dwNumberOfProcessors + 2;

	m_hCompletionPort = NULL;

	m_saListenAddr.sin_family = AF_INET;
	m_saListenAddr.sin_addr.S_un.S_addr = 0;
	m_saListenAddr.sin_port = 0;
	m_sListenSocket = INVALID_SOCKET;

	memset(m_hThread, 0, sizeof(m_hThread));
	memset(m_uThreadId, 0, sizeof(m_uThreadId));
	m_iThreadCount = 0;		// 线程数量
	
	m_hThreadShrinkPool = NULL;
	m_uThreadShrinkPoolId = 0;

	m_pMsgPool = NULL;				// 消息池
	m_bMsgPoolFromExternal = FALSE;	// TRUE 表示消息池是从外部传进来的

	m_pServerHandlePool = NULL;	// 对端服务池
	m_pAcceptResultPool = NULL;		// 连接结果池
	m_pSendResultPool = NULL;		// 发送结果池

	m_bIsExit = FALSE;

	m_iMsgBlockSize = 2048;		// 消息块的长度
	m_iMsgPoolInitCount = 256;	// 消息池的最初元素数量

	m_iSendResultPoolInitCount = 256;		// 发送结果池的最初元素数量，默认值是 256
	m_iAcceptResultPoolInitCount = 256;		// 连接结果池的最初元素数量，默认值是 128

	m_iServerHandlePoolInitCount = 512;	// 对端服务池的最初元素数量，默认值是 512
	
	m_iPulseCount = 0;	// 脉冲计数器

	set_check_power_close_peer(20*1000);	// 设置检查主动关闭对端的时间，以 ms 为单位
	set_shrink_pools_time(5*60*1000);		// 收缩各种池的时间，默认是 5分钟
	set_heartbeat_check_time(1*60*1000);	// 心跳检查的时间，默认是 1分钟
	m_iNoHeartbeatDieTime = 2*60*1000;		// 无心跳至死的时间，以 ms 为单位，即 N ms 之内客户端没有任何消息发过来就认为该客户端死掉了end

	::InterlockedExchange64(&m_lAtomMsgCount, 0);	// 原子包的数量
	m_lStartStatisticTime = 0;		// 开始统计的时间
	m_bStatisticRecvRate = FALSE;	// 接收速率
	m_iStatistInterval = 30*10;		// 统计间隔，以 PULSE_TIME 为基本单们

	
}

CCommTcpServer::~CCommTcpServer(void)
{
	//m_pCoreServer = NULL;	// 宿主的指针
}

// 设置宿主的指针
void CCommTcpServer::set_core_server(CCoreServer* pCoreServer)
{
	m_pCoreServer = pCoreServer;
}


// 设置 IOCP 工作线程的数量
void CCommTcpServer::set_work_thread_count(int iCount)
{
	m_nThreadCount = iCount;
}

// 从外部传入消息池
int CCommTcpServer::set_msg_pool(CMemBlockPool* pMsgPool)
{
	if(!pMsgPool)
		return 10;

	m_pMsgPool = pMsgPool;
	m_bMsgPoolFromExternal = TRUE;						// 消息池是从外部传进来的
	m_iMsgBlockSize = m_pMsgPool->get_mem_block_size();	// 获得池里内存块的尺寸

	return 0;
}

// 设置消息块的长度
void CCommTcpServer::set_msg_block_size(int iMsgBlockSize)
{
	if(m_bMsgPoolFromExternal)	// 消息池是从外部传进来的
	{
		assert(m_pMsgPool);
		m_iMsgBlockSize = m_pMsgPool->get_mem_block_size();	// 获得池里内存块的尺寸
	}
	else	// 消息池是内建的
	{
		m_iMsgBlockSize = iMsgBlockSize;
	}
}

// 设置发送结果池的最初元素数量
void CCommTcpServer::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	if(iSendResultPoolInitCount<2)
		m_iSendResultPoolInitCount = 2;
	else
		m_iSendResultPoolInitCount = iSendResultPoolInitCount;	
}

// 设置对端服务池的最初元素数量
void CCommTcpServer::set_service_handle_pool_init_count(int iServerHandlePoolInitCount)
{
	if(iServerHandlePoolInitCount<2)
		m_iServerHandlePoolInitCount = 2;
	else
		m_iServerHandlePoolInitCount = iServerHandlePoolInitCount;	
}

// 设置连接结果池的最初元素数量
void CCommTcpServer::set_accept_result_pool_init_count(int iAcceptResultPoolInitCount)
{
	if(iAcceptResultPoolInitCount<2)
		m_iAcceptResultPoolInitCount = 2;
	else
		m_iAcceptResultPoolInitCount = iAcceptResultPoolInitCount;
}

// 设置消息池的最初元素数量
void CCommTcpServer::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_iMsgPoolInitCount = iMsgPoolInitCount;	
}

// 设置检查主动关闭对端的时间，以 ms 为单位
void CCommTcpServer::set_check_power_close_peer(LONGLONG iTime)
{
	LONGLONG iPulseCount = iTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iCheckInitiativeClosePeerPulseCount = iPulseCount;
}

// 设置收缩各种池的时间，以 ms 为单位
void CCommTcpServer::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	LONGLONG iPulseCount = iShrinkPoolsTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iShrinkPoolsiPulseCount = iPulseCount;
}

// 设置心跳检查的时间，以 ms 为单位
void CCommTcpServer::set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime)
{
	LONGLONG iPulseCount = iHeartbeatCheckTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iHeartbeatCheckPulseCount = iPulseCount;
}

// 设置无心跳至死的时间，以 ms 为单位，即 N ms 之内客户端没有任何消息发过来就认为该客户端死掉了
void CCommTcpServer::set_no_heartbeat_die_time(int iNoHeartbeatDieTime)
{
	m_iNoHeartbeatDieTime = iNoHeartbeatDieTime;
}

// 是否心跳包
BOOL CCommTcpServer::is_heartbeat(CORE_MSG_HEAD* pMsgHead)
{
	if(pMsgHead->lCordState && 0x00000001 > 0)	// 是心跳包
		return TRUE;
	else										// 非心跳包
		return FALSE;
}

// 是否主动关闭指定对端的指令
BOOL CCommTcpServer::is_power_close_peer(CORE_MSG_HEAD* pMsgHead)
{
	if(pMsgHead->lCordState && 0x00000002 > 0)	// 是主动关闭指定对端的指令
		return TRUE;
	else										// 非主动关闭指定对端的指令
		return FALSE;
}

// 统计接收的速率，是个反复的开关
void CCommTcpServer::statistic_recv_rate()
{
	m_bStatisticRecvRate = !m_bStatisticRecvRate;

	if(m_bStatisticRecvRate)
	{
		::InterlockedExchange64(&m_lAtomMsgCount, 0);	// 原子包的数量
		m_lStartStatisticTime = GetTickCount64();

		printf("开启【统计接收的速率】 \n");
	}
	else
	{
		printf("关闭【统计接收的速率】 \n");
	}
}

// 初始化
int CCommTcpServer::init()
{
	int iResult = 0;

	SYSTEM_INFO			sysinfo = { 0 };
	int					i, nCount = 0;
	int					iErr = 0;

	// 消息池
	if(!m_pMsgPool)
	{
		m_pMsgPool = new CMemBlockPool(m_iMsgBlockSize, m_iMsgPoolInitCount, 20*m_iMsgPoolInitCount);		
		if(m_pMsgPool)
			m_pMsgPool->init();
		else
			return 10;	// 建立消息池失败
	}

	// 对端服务池
	m_pServerHandlePool = new CLightweightPool<CServerHandle>("对端服务池", m_iServerHandlePoolInitCount, 20*m_iServerHandlePoolInitCount);	
	if(m_pServerHandlePool)
		m_pServerHandlePool->init();
	else
		return 20;	// 建立对端服务池失败

	// 连接结果池
	m_pAcceptResultPool = new CLightweightPool<CAcceptResult>("连接结果池", m_iAcceptResultPoolInitCount, 20*m_iAcceptResultPoolInitCount);	
	if(m_pAcceptResultPool)
		m_pAcceptResultPool->init();
	else
		return 30;	// 建立连接结果池失败

	// 发送结果池
	m_pSendResultPool = new CLightweightPool<CSendResult>("发送结果池", m_iSendResultPoolInitCount, 20*m_iSendResultPoolInitCount);		
	if(m_pSendResultPool)
		m_pSendResultPool->init();
	else
		return 40;	// 建立发送结果池失败

	// 建立 IOCP 
	m_hCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if(!m_hCompletionPort)
		return 70;			// CreateIoCompletionPort 失败

	GetSystemInfo(&sysinfo);
	if(m_nThreadCount == 0)
	{
		m_nThreadCount = (int)sysinfo.dwNumberOfProcessors;
	}

	// 建立 IOCP 的工作线程
	for(i = 0; i < m_nThreadCount; i++)
	{
		m_hThread[i] = (HANDLE)_beginthreadex(NULL, 0, &thread_work, (void*)this,  CREATE_SUSPENDED, &m_uThreadId[i]); 
		if(!m_hThread[i])
			return 80;	// 建立工作线程失败

		m_iThreadCount++ ;
	}

	// 建立定时检查的线程
	m_hThreadShrinkPool = (HANDLE)_beginthreadex(NULL, 0, &thread_check, (void*)this,  CREATE_SUSPENDED, &m_uThreadShrinkPoolId); 
	if(!m_hThreadShrinkPool)
		return 90;	// 建立定时检查的线程失败

	return iResult;
}

// 定时检查的线程
unsigned __stdcall CCommTcpServer::thread_check(LPVOID lpParameter)
{
	CCommTcpServer* pThis = (CCommTcpServer*)lpParameter;
	int iInterval = 0;

	while(!pThis->m_bIsExit)
	{
		pThis->m_iPulseCount++ ;
		
		// 检查主动关闭对端
		if(0 == pThis->m_iPulseCount % pThis->m_iCheckInitiativeClosePeerPulseCount)
		{
			pThis->check_power_close_peer();	// 检查主动关闭对端超时
		}

		// 收缩一次
		// 以 ms 为单位
		if(0 == pThis->m_iPulseCount % pThis->m_iShrinkPoolsiPulseCount)
		{
			iInterval = pThis->m_pMsgPool->get_current_element_count() - pThis->m_iMsgPoolInitCount;
			if(iInterval > pThis->m_iMsgPoolInitCount)	// 间距大于初值才有收缩的意义
			{
				pThis->m_pMsgPool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pServerHandlePool->get_current_element_count() - pThis->m_iServerHandlePoolInitCount;
			if(iInterval > pThis->m_iServerHandlePoolInitCount)	// 间距大于初值才有收缩的意义
			{
				pThis->m_pServerHandlePool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pAcceptResultPool->get_current_element_count() - pThis->m_iAcceptResultPoolInitCount;
			if(iInterval > pThis->m_iAcceptResultPoolInitCount)	// 间距大于初值才有收缩的意义
			{
				pThis->m_pAcceptResultPool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pSendResultPool->get_current_element_count() - pThis->m_iSendResultPoolInitCount;
			if(iInterval > pThis->m_iSendResultPoolInitCount)	// 间距大于初值才有收缩的意义
			{
				pThis->m_pSendResultPool->shrink_pool(iInterval, 0.25);
			}

			//printf("各种池收缩一次 \n");
		}
		
		if(0 == pThis->m_iPulseCount % pThis->m_iHeartbeatCheckPulseCount)	// 心跳检查
		{
			// 检查所有对端的心跳
			pThis->check_all_peer_heartbeat();
			//printf("心跳检查 \n");
		}

		if(pThis->m_bStatisticRecvRate)	// 是否统计接收速率
		{
			if(0 == pThis->m_iPulseCount % pThis->m_iStatistInterval)		// 统计间隔
			{
				LONGLONG lSpace = GetTickCount64() - pThis->m_lStartStatisticTime;
				LONGLONG lRate = pThis->m_lAtomMsgCount/lSpace;
				if(lSpace)
				{
					if(lRate>0)
						printf("接收速率 %d/ms  \n", lRate);
					else
						printf("接收速率 %d/秒  \n", 1000*pThis->m_lAtomMsgCount/lSpace);
				}
			}
		}

		Sleep(PULSE_TIME);
	}

	return 0;
}

unsigned __stdcall CCommTcpServer::thread_work(LPVOID lpParameter)
{
	CCommTcpServer* pThis = (CCommTcpServer*)lpParameter;

	int		iResult = CCompleteResult::COMPLETE_RESULT_FAIL;
	BOOL	bResult = FALSE;
	DWORD	dwBytesTransfered = 0;	// 传输的实际字节数

	CCompleteResult*	pResult = NULL;
	CServerHandle*		pServerHandle = NULL;
	OVERLAPPED*			pOverlap = NULL;
	
	while(iResult != CCompleteResult::COMPLETE_RESULT_EXIT)
	{
		//dwResult = pThis->WorkProc();

		// 这个IOCP 响应 m_sListenSocket 对端连接、接收对端消息、向对端发消息、关闭对端
		// 对端连接是由 CAcceptResult 的实例负责
		// 接收对端消息是由 CRecvResult 的实例负责
		// 向对端发消息是由 CSendResult 的实例负责
		// 关闭对端是由 CTerminateResult 的实例负责
		bResult = ::GetQueuedCompletionStatus(	pThis->m_hCompletionPort,
												&dwBytesTransfered,
												(PULONG_PTR)&pServerHandle,
												(LPOVERLAPPED*)&pOverlap,
												INFINITE);

		if(pOverlap)
		{
			pResult = (CCompleteResult*)pOverlap;
			if(pResult)
			{
				#if 0	// 此段不能删除，是原理性的讲解与演示， 
						// 细节讲解见 CServerHandle::OnRecvComplete 函数内

					DWORD dwCurrent = GetCurrentThreadId();
					printf("%s %d \n", pResult->get_class_name_flag(),dwCurrent);
				#endif

				iResult = pResult->OnIoComplete(dwBytesTransfered);
			}
		}
	}

	return 0;
}

// 设置监听地址
void CCommTcpServer::set_listen_addr(const char* szListenAddr)
{
	m_saListenAddr.sin_addr.s_addr = inet_addr(szListenAddr);
}

// 设置监听端口
void CCommTcpServer::set_listen_port(unsigned int nPort)
{
	m_saListenAddr.sin_port = htons((unsigned short)nPort);
}

/* --------------------------------------------------------------------------

函数说明：初始化
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/

int CCommTcpServer::start_listen()
{
	int	iRes = 0;
	int	iErr = 0;

	WSADATA WsaData;

	iRes = WSAStartup(MAKEWORD(2,2),&WsaData);
	iErr = WSAGetLastError();
	if (0!=iRes)
	{
		printf("WSAStartup Failed ，WSAGetLastError()=%d \n", iErr);
		return 10;
	}

	m_sListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED); 
	iErr = WSAGetLastError();
	if(INVALID_SOCKET==m_sListenSocket)
	{
		printf("WSASocket Failed ，WSAGetLastError()=%d \n", iErr);
		return 20;
	}

	iRes = bind(m_sListenSocket, (sockaddr*)&m_saListenAddr, sizeof(m_saListenAddr));
	iErr = WSAGetLastError();
	if(0!=iRes)
	{
		printf("bind Failed ，WSAGetLastError()=%d \n", iErr);
		return 30;
	}
	else
	{
		iErr = listen(m_sListenSocket, 200);	// 第二个参数若改得很大，需要改WINDOWS系统的默认值???
		if(iErr != 0)
		{
			iErr = WSAGetLastError();
			return 40;
		}
		else
		{
			// 这个 m_sListenSocket 可以接收新对端连接、接收对端消息、向对端发消息、关闭对端
			// 接收新对端连接是由 CAcceptResult 的实例负责
			// 接收对端消息是由 CRecvResult 的实例负责
			// 向对端发消息是由 CSendResult 的实例负责
			// 关闭对端是由 CTerminateResult 的实例负责
			HANDLE hTmp = CreateIoCompletionPort((HANDLE)m_sListenSocket, m_hCompletionPort, 0, 0);
			iErr = GetLastError();
			if(!hTmp)
			{
				printf("bind Failed ，GetLastError()=%d \n", iErr);
				return 50;
			}
		}
	}

	return 0;
}

int CCommTcpServer::stop_listen()
{
	int iResult = 0;
	int iErr;

	if(m_sListenSocket != INVALID_SOCKET)
	{
		iErr = closesocket(m_sListenSocket);
		if(SOCKET_ERROR == iErr)
		{
			iErr = WSAGetLastError();
			iResult = 10;
		}
		else
		{
			m_sListenSocket = INVALID_SOCKET;
		}

	}

	return iResult;
}

/* --------------------------------------------------------------------------
函数说明：启动服务
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CCommTcpServer::start()
{
	int		iResult = 0;

	__try
	{
		// 启动定时检查的线程
		ResumeThread(m_hThreadShrinkPool);

		// 启动工作线程
		start_work_threads();


		iResult = start_listen();
		if(iResult>0)
			return 20;

		iResult = request_accept();
		if(iResult>0)
			return 30;
	}

	__finally
	{
		if(iResult>0)
		{
			int iResult = stop();
			assert(0==iResult);
		}
	}

	return iResult;
}

// 请求连接
int CCommTcpServer::request_accept()
{
	int iResult = 0;;
	int	iErr = 0;
	CAcceptResult* pAcceptResult = NULL;	// 连接结果
	CServerHandle* pServerHandle = NULL;	// 对端服务

	__try
	{
		m_pAcceptResultPool->retrieve(&pAcceptResult);	// 连接结果出池
		assert(pAcceptResult);
		if(!pAcceptResult)
		{
			iResult = 10;
			__leave;
		}
		pAcceptResult->set_comm_tcp_server(this);	// 很重要

		m_pServerHandlePool->retrieve(&pServerHandle);	// 对端服务出池
		assert(pServerHandle);

		if(!pServerHandle)
		{
			iResult = 20;
			__leave;
		}

		LONGLONG lChannelNo = m_stServerHandleMgr.add(pServerHandle);	// 产生通道号

		pServerHandle->set_comm_tcp_server(this);	// 很重要
		pServerHandle->set_channel_id(lChannelNo);	// 设置通道号
		pServerHandle->set_msg_block_size(m_iMsgBlockSize);	// 设置消息块的长度

		//BOOL bFlag = pServerHandle->is_valid();	// 测试用，此时应该是无效的

		iResult = pServerHandle->new_handle();	
		if(iResult>0)
		{
			iResult = 30;
			__leave;
		}

		pAcceptResult->set_service_handle(pServerHandle);

		//bFlag = pServerHandle->is_valid();	// 测试用，此时应该是效的，因为经过了 new_handle()

		/*
			BOOL AcceptEx(
			__in          SOCKET sListenSocket,
			__in          SOCKET sAcceptSocket,
			__in          PVOID lpOutputBuffer,
			__in          DWORD dwReceiveDataLength,
			__in          DWORD dwLocalAddressLength,
			__in          DWORD dwRemoteAddressLength,
			__out         LPDWORD lpdwBytesReceived,
			__in          LPOVERLAPPED lpOverlapped
			);
		*/

		#if 1
			// 等于 0，则当接收到一个连接后立即返回；
			DWORD dwReceiveDataLength = 0, // dwReceiveDataLength
		#else
			// dwReceiveDataLength 不等于0，则在接收到连接后，必须等到客户端发来第一包数据才返回。可根据实际需要设定此参数。
			// 这就是有人说明明我已经建立连接，为何服务端收不到 ACCEPT 事件的原因。
			// 这个功能的目的之一估计是用于客户端连成功时马上要发送密文，服务端根据密文来判断是否合法的客户端，从而踢掉恶意连接的客户端
			DWORD dwReceiveDataLength = m_pAcceptResult->get_out_buf_len() - ((sizeof(SOCKADDR_IN)+16)*2),
		#endif

		// 向完端口投递一个异步连接
		bResult = ::AcceptEx(	m_sListenSocket, 
								pServerHandle->get_handle(), 
								(void*)(pAcceptResult->get_out_buf()), 
								dwReceiveDataLength, 
								sizeof(sockaddr_in) + 16, 
								sizeof(sockaddr_in) + 16, 
								&pAcceptResult->m_dwBytesReceived, 
								pAcceptResult);
		
		if(bResult)
		{ 
			// immediately success and the overlapped still get queued
		}
		else
		{
			iErr = WSAGetLastError();
			if(WSA_IO_PENDING == iErr)
			{
				iResult = 0;
			}
			else
			{
				iResult = 80;
				__leave;
			}
		}
	}
	__finally
	{
		if(iResult>0)	
		{
			if(pAcceptResult)
			{
				//pAcceptResult->set_comm_tcp_server(NULL);		// 应该不需要吧
				m_pAcceptResultPool->recycle(pAcceptResult);	// 连接结果归池
			}

			if(pServerHandle)
			{
				//pServerHandle->set_comm_tcp_server(NULL);		// 应该不需要吧
				m_pServerHandlePool->recycle(pServerHandle);	// 对端服务归池
			}
		}
	}

	return iResult;
}

void CCommTcpServer::start_work_threads()
{
	for(int i=0; i<m_iThreadCount; i++)
	{
		ResumeThread(m_hThread[i]);
	}
}

// 停止服务
int CCommTcpServer::stop()
{
	m_bIsExit = TRUE;
	int iResult = 0;

	iResult = stop_listen();

	// 结束工作线程池
	iResult = stop_work_threads();

	// 等待定时检查的线程结束
	WaitForSingleObject(m_hThreadShrinkPool, WAIT_EXIT_TIME);

	// 关闭所有的对端
	close_all_peer();

	display_all_pool();

	if(!m_bMsgPoolFromExternal)	// TRUE 表示消息池是从外部传进来的
	{
		m_pMsgPool->uninit();
		delete m_pMsgPool;
	}


	m_pServerHandlePool->uninit();
	delete m_pServerHandlePool;

	m_pAcceptResultPool->uninit();
	delete m_pAcceptResultPool;

	m_pSendResultPool->uninit();
	delete m_pSendResultPool;

	//m_pCoreServer = NULL;	// 宿主的指针

	return iResult;
}

// 结束工作线程池
int CCommTcpServer::stop_work_threads()
{
	BOOL bResult = FALSE;

	for(int i=0; i < m_iThreadCount; i++)
	{
		bResult = ::PostQueuedCompletionStatus(m_hCompletionPort, 0, 0, &m_stTerminateResult);
		if(!bResult)
		{
			DWORD dwErr = GetLastError();
			return (int)dwErr;
		}
	}

	WaitForMultipleObjects(m_iThreadCount, m_hThread, TRUE, WAIT_EXIT_TIME);

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：发送
传入参数：
	lChannelNo	通道号
	pSendBlock	发送的消息块，注意：无论发送成功与失败框架系统都会将 pSendBlock 自动归池，
	                               
返回值：
    成功则返回 0，而且会回调 OnSend 函数。但如果出现IO错误，
	失败会回调 OnSendFailed 函数，返回错误码如下：
		10  无效的通道号
		20  pMemBlock 出池失败
		30  pSendResult 出池失败
		40  pMemBlock->copy 失败
		80  WSASend 失败
		90  CCommTcpServer::send_data 异常
--------------------------------------------------------------------------*/
int CCommTcpServer::send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock)
{
	CServerHandle* pServerHandle = m_stServerHandleMgr.find(lChannelNo);
	if(pServerHandle)
	{
		try
		{
			// 无论发送成功与失败框架系统都会将 pSendBlock 自动归池，
			int iRes = pServerHandle->send_data(pSendBlock);
			return 	iRes;
		}
		catch (...)
		{
			printf("CCommTcpServer::send_data 异常，pServerHandle=%d \n", pServerHandle);
			return 90;
		}
	}
	else	// 无效的通道号
	{
		// 响应发送失败
		OnSendFailed(lChannelNo, pSendBlock);

		// 如果对端是无效的，向无效的对端发数据根本不会响应 OnSendComplete 些函数
		m_pMsgPool->recycle(pSendBlock);	// 消息归池
	}

	return 10;	// 无效的通道号
}

/* --------------------------------------------------------------------------
函数说明：出池并发送，效率低，慎用。出池并发送，此函数效率低，慎用。通常用于向客户端一次性大批量发送数据（例如发送用户列表）的场合。
传入参数：
	lChannelNo	通道号
	iMainCode	消息主码
	iSubCode	消息辅助码
	pData		包体数据
	iDataLen	包体数据的长度                               
返回值：
    成功则返回 0，而且会回调 OnSend 函数。但如果出现IO错误，
	失败会回调 OnSendFailed 函数，返回错误码如下：
		10  无效的通道号
		20  pMemBlock 出池失败
		30  pSendResult 出池失败
		40  pMemBlock->copy 失败
		80  WSASend 失败
备注：
    因为本函数要消息出池，所以低效。
	高效的作法是用 OnRecv 的实参重新装填数据后直接回发。
--------------------------------------------------------------------------*/
int CCommTcpServer::retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData, int iDataLen, char* pszTextMark, BOOL bIsWait)
{
	if(!m_stServerHandleMgr.is_valid(lChannelNo))
		return 10;

	int iRes = 0;
	CMemBlock* pMemBlock = NULL;	// 消息块出池

	// 出池一个携带指定内容的消息块
	iRes = m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, pszTextMark, bIsWait);

	#if _DEBUG
		//printf("pMemBlock=%I64d \n", pMemBlock);	// 测试用
	#endif

	if(0==iRes && pMemBlock)
	{
		iRes = send_data(lChannelNo, pMemBlock);
	}

	return iRes;	// 无效的通道号
}

/* --------------------------------------------------------------------------
函数说明：TCP广播，即发送数据到所有的有效对端
传入参数：
	iMainCode	消息主码
	iSubCode	消息辅助码
	pData		包体数据
	iDataLen	包体数据的长度
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CCommTcpServer::tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData, int iDataLen, char* pszTextMark, BOOL bIsWait)
{
	int iRes = 0;

	CMemBlock* pMemBlock = NULL;	// 消息块出池

	// 出池一个携带指定内容的消息块
	iRes = m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, pszTextMark, bIsWait);

	if(0==iRes && pMemBlock)
		iRes = tcp_broadcase(pMemBlock, pszTextMark, bIsWait);
	else
		return 50;	// 消息块出池失败

	return iRes;	// 失败的对端数量 
}

/* --------------------------------------------------------------------------
函数说明：TCP广播，即发送数据到所有的有效对端
传入参数：
	pSendBlock  发送的消息块
返回值：
    成功则返回 0，失败返回错误码如下：
	    10 pSendBlock 值为空
		60 存在发送失败的对端
--------------------------------------------------------------------------*/
int CCommTcpServer::tcp_broadcase(CMemBlock*& pSendBlock, char* pszTextMark, BOOL bIsWait)
{
	if(!pSendBlock)
		return 10;

	int iFailCount = 0;	// 失败的对端数量
	int iRes = 0;

	vector<CServerHandle*> vecServerHandle;
	m_stServerHandleMgr.get_all_valid(vecServerHandle);
	size_t iSize = vecServerHandle.size();

	for(int i=0; i<vecServerHandle.size(); i++)
	{
		CMemBlock* pNewBlock = NULL;
		m_pMsgPool->retrieve(&pNewBlock, pszTextMark, bIsWait);
		pNewBlock->copy(pSendBlock->base(), pSendBlock->length());	// 消息块赋值

		if(pNewBlock)
		{
			CServerHandle* pServerHandle = vecServerHandle[i];

			// 无论发送成功与失败框架系统都会将 pSendBlock 自动归池，
			iRes = pServerHandle->send_data(pNewBlock);
			if(iRes>0)
			{
				iFailCount++;
			}
		}
	}

	m_pMsgPool->recycle(pSendBlock);	// 归池

	if(0 == iFailCount)
		return 0;	
	else
		return 60;	// 存在发送失败的对端

}

// 响应对端已关闭了
int CCommTcpServer::OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType)
{
	// 在客户端密集访发自消息而且服务端要回发消息的情况下，服务端占用过高时，客户端手工关闭但服务端偶尔无法响应关闭事件???
	// 这时只能靠心跳检测机制去踢掉那些已关闭但没能在服务端响应的对端了
	// 如果让客户端发出n个包后睡m毫秒，就可以降低服务端 CPU 的占用率，30%以下通常不会发生这样的事儿了。
	//printf("通道号=%d , socket=%d 已关闭 \n", lChannelNo, socketClose);

	if(!m_pCoreServer)
		return 10;

	m_pCoreServer->m_lCurrentChannel = INVALID_CHANNEL_NO;

	return m_pCoreServer->OnClose(lChannelNo, socketClose, iCloseType);
}

/* --------------------------------------------------------------------------
函数说明：响应发送成功
传入参数：
	lChannelNo	通道号
	pData			发送数据的内容
	iDataLen		发送数据的内容的长度
备注：
	消息块已经归池了，此处无需 delete 消息
--------------------------------------------------------------------------*/
void CCommTcpServer::OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->OnSend(lChannelNo, pSendBlock);
}

/* --------------------------------------------------------------------------
函数说明：响应发送失败
传入参数：
	lChannelNo	通道号
	pSendBlock	发送的消息，会由框架系统自动归池，应用层不许将 pSendBlock 归池
备注：
    应用层若想再次发送此消息，可以新出池一个消息块例如 pNewBlock ，
	再 pNewBlock->copy(pSendBlock->base, pSendBlock->length()) ，再发送 pNewBlock 
--------------------------------------------------------------------------*/
void CCommTcpServer::OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->OnSendFailed(lChannelNo, pSendBlock);
}

// 响应连接成功
void CCommTcpServer::OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->m_lCurrentChannel = lChannelNo;

	m_pCoreServer->OnConnect(lChannelNo, saLocalAddr, saRemoteAddr);
}

// 响应连接失败
void CCommTcpServer::OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->OnConnectFail(saLocalAddr, saRemoteAddr, iErrorCode);
}



// 响应收包消息，已经是原子包了。注意：此时并未归池，由 CCommTcpServer 之外的机制归池
void CCommTcpServer::OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv)
{
	CORE_MSG_HEAD*  pMsgHead = NULL;
	m_pMsgPool->get_core_msg_head(pRecv, pMsgHead);

	InterlockedIncrement64(&m_lAtomMsgCount);

	// 本段用于密集型测试
	// 结论：【用此段】与【不用此段】的区别微忽其微，说明速度变慢的问题不在于消息投递这一层
	#if 0	
		send_data(lChannelNo, pRecv);
		return ;
	#endif

	if(pMsgHead && is_heartbeat(pMsgHead))	// 是心跳包
	{
		if(m_pCoreServer)
			m_pCoreServer->OnIsHeartbeat(pMsgHead->lChannelNo);	// 心跳响应

		if(m_pMsgPool)
			m_pMsgPool->recycle(pRecv);	// 归池
	}
	else
	{
		if(m_pCoreServer)
			m_pCoreServer->OnRecv(lChannelNo, pRecv);	// 由应用层归池
	}

}

// 响应通讯错误的消息
void CCommTcpServer::OnCommError(LONGLONG lChannelNo, char* pszError)
{
	printf("lChannelNo=%d ,%s \n", pszError);
}

// 显示所有的池信息
void CCommTcpServer::display_all_pool()
{
	printf("池内情况：\n");
	printf(" MsgPool，       出池数=%I64d 归池数=%I64d 池内当前元素=%d \n",
		m_pMsgPool->get_retrieve_count(),
		m_pMsgPool->get_recycle_count(),
		m_pMsgPool->get_current_element_count()
		);

	printf(" SendResultPool，出池数=%I64d 归池数=%I64d 池内当前元素=%d \n",
		m_pSendResultPool->get_retrieve_count(),
		m_pSendResultPool->get_recycle_count(),
		m_pSendResultPool->get_current_element_count()
		);

	printf(" 收到原子包 %9d 个 \n", m_lAtomMsgCount);

	printf(" ServerHandlePool，出池数=%I64d 归池数=%I64d 池内当前元素=%d \n",
		m_pServerHandlePool->get_retrieve_count(),
		m_pServerHandlePool->get_recycle_count(),
		m_pServerHandlePool->get_current_element_count()
		);

	printf(" AcceptResultPool， 出池数=%I64d 归池数=%I64d 池内当前元素=%d \n",
		m_pAcceptResultPool->get_retrieve_count(),
		m_pAcceptResultPool->get_recycle_count(),
		m_pAcceptResultPool->get_current_element_count()
		);

	// 列印所有的有效对端信息
	display_all_valid_peer();
}

// 列印所有的有效对端信息
void CCommTcpServer::display_all_valid_peer()
{
	vector<CServerHandle*> vecServerHandle;

	int iCount = m_stServerHandleMgr.get_all_valid(vecServerHandle);
	printf(" 有效的对端数量=%d \n", vecServerHandle.size());

	for(int i=0; i<vecServerHandle.size(); i++)
	{
		CServerHandle* p = vecServerHandle[i];
		if(p && p->is_valid())
		{
			printf("  通道号=%d ， SOCKET=%d  \n", p->get_channel_id(), p->get_handle());
		}
	}
}

/* --------------------------------------------------------------------------
函数说明：关闭所有的对端
备注：
	在客户端收到消息后立即回发、服务端收到消息后也立即回发的情况下， 
	服务端发出 closesocket 指令强制关闭客户端，客户端却无法响应关闭事件??? 
--------------------------------------------------------------------------*/
void CCommTcpServer::close_all_peer()
{
	CThreadGuard guard(&m_lockClose);

#if 0	// 旧的
	vector<CServerHandle*> vecServerHandle;

	// 获得所有有效的对端服务
	int iCount = m_stServerHandleMgr.get_all_valid(vecServerHandle);

	size_t sizeTmp = vecServerHandle.size();
	if(iCount>0)
	{
		for(int i=0; i<vecServerHandle.size(); i++)
		{
			CServerHandle* p = vecServerHandle[i];
			if(p && p->is_valid())	// 对端有效
			{
				m_stServerHandleMgr.remove_one(p);

				p->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
				p->close(p->get_close_type());
			}
		}
	}
#else	// 新的
	vector<LONGLONG> vecChannelNo;

	// 获得所有有效对端的通道号
	int iCount = m_stServerHandleMgr.get_all_valid(vecChannelNo);

	size_t sizeTmp = vecChannelNo.size();
	if(iCount>0)
	{
		for(int i=0; i<vecChannelNo.size(); i++)
		{
			LONGLONG lChannelNo = vecChannelNo[i];
			if(INVALID_CHANNEL_NO!=lChannelNo)
			{
				power_close_peer(lChannelNo);
			}
		}
	}

#endif
}

/* --------------------------------------------------------------------------
函数说明：主动关闭指定的对端，客户端不会再执行断线重连
传入参数：
	lChannelNo	通道号
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CCommTcpServer::power_close_peer(LONGLONG lChannelNo)
{
	// 向客户端发主动关闭的消息

	CMemBlock* pPowerCloseBlock = NULL;

	if(m_pMsgPool)
	{
		// 出池一个主动关闭对端的消息块
		m_pMsgPool->retrieve_with_power_close(pPowerCloseBlock, __FUNCTION__);
		if(pPowerCloseBlock)
		{
			// 设置主动关闭的对端
			m_stServerHandleMgr.set_power_close_peer(lChannelNo);

			send_data(lChannelNo, pPowerCloseBlock);	// 向对端发送主动关闭的消息块
		}
	}

	return 0;
}

// 检查主动关闭对端超时
int CCommTcpServer::check_power_close_peer()
{
	CThreadGuard guard(&m_lockClose);

	m_stServerHandleMgr.check_power_close_peer();

	return 0;
}

/* --------------------------------------------------------------------------
函数说明：关闭指定的对端
传入参数：
	lChannelNo	通道号
返回值：
    成功则返回 0，失败返回错误码如下：
备注：
	在客户端收到消息后立即回发、服务端收到消息后也立即回发的情况下， 
	服务端发出 closesocket 指令强制关闭客户端，客户端却无法响应关闭事件??? 
--------------------------------------------------------------------------*/
int CCommTcpServer::close_peer(LONGLONG lChannelNo)
{
	CThreadGuard guard(&m_lockClose);

	int iResult = 10;	// 通道号无效

	if(m_stServerHandleMgr.is_valid(lChannelNo))
	{
		CServerHandle* pServerHandle = m_stServerHandleMgr.remove_one(lChannelNo);
		if(pServerHandle)
		{
			//printf("需要删除打印:close_peer端口号 %d \n",lChannelNo);
			pServerHandle->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
			pServerHandle->close(pServerHandle->get_close_type());
		}
		else
		{
			return 20;	// pServerHandle 无效
		}
	}

	return iResult;
}


// 检查所有对端的心跳
int CCommTcpServer::check_all_peer_heartbeat()
{
	CThreadGuard guard(&m_lockClose);

	vector<CServerHandle*> vecServerHandle;

	// 获得所有有效的对端服务
	int iCount = m_stServerHandleMgr.get_all_valid(vecServerHandle);

	size_t sizeTmp = vecServerHandle.size();
	if(iCount>0)
	{
		for(int i=0; i<vecServerHandle.size(); i++)
		{
			CServerHandle* p = vecServerHandle[i];
			if(p && p->is_valid())	// 对端有效
			{
				if(p->check_heartbeat()>0)	// 心跳超时，对端死了
				{
					LONGLONG lChannelNo = p->get_channel_id();
					m_stServerHandleMgr.remove_one(p);

					//printf("需要删除打印:check_all_peer_heartbeat端口号 %d \n",lChannelNo);
					p->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
					p->close(p->get_close_type());

					// 响应无心跳至死
					m_pCoreServer->OnNoHeartbeatDie(lChannelNo);
				}
			}
		}
	}

	return 0;
}
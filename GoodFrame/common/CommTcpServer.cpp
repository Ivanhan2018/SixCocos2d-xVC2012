
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
	m_iThreadCount = 0;		// �߳�����
	
	m_hThreadShrinkPool = NULL;
	m_uThreadShrinkPoolId = 0;

	m_pMsgPool = NULL;				// ��Ϣ��
	m_bMsgPoolFromExternal = FALSE;	// TRUE ��ʾ��Ϣ���Ǵ��ⲿ��������

	m_pServerHandlePool = NULL;	// �Զ˷����
	m_pAcceptResultPool = NULL;		// ���ӽ����
	m_pSendResultPool = NULL;		// ���ͽ����

	m_bIsExit = FALSE;

	m_iMsgBlockSize = 2048;		// ��Ϣ��ĳ���
	m_iMsgPoolInitCount = 256;	// ��Ϣ�ص����Ԫ������

	m_iSendResultPoolInitCount = 256;		// ���ͽ���ص����Ԫ��������Ĭ��ֵ�� 256
	m_iAcceptResultPoolInitCount = 256;		// ���ӽ���ص����Ԫ��������Ĭ��ֵ�� 128

	m_iServerHandlePoolInitCount = 512;	// �Զ˷���ص����Ԫ��������Ĭ��ֵ�� 512
	
	m_iPulseCount = 0;	// ���������

	set_check_power_close_peer(20*1000);	// ���ü�������رնԶ˵�ʱ�䣬�� ms Ϊ��λ
	set_shrink_pools_time(5*60*1000);		// �������ֳص�ʱ�䣬Ĭ���� 5����
	set_heartbeat_check_time(1*60*1000);	// ��������ʱ�䣬Ĭ���� 1����
	m_iNoHeartbeatDieTime = 2*60*1000;		// ������������ʱ�䣬�� ms Ϊ��λ���� N ms ֮�ڿͻ���û���κ���Ϣ����������Ϊ�ÿͻ���������end

	::InterlockedExchange64(&m_lAtomMsgCount, 0);	// ԭ�Ӱ�������
	m_lStartStatisticTime = 0;		// ��ʼͳ�Ƶ�ʱ��
	m_bStatisticRecvRate = FALSE;	// ��������
	m_iStatistInterval = 30*10;		// ͳ�Ƽ������ PULSE_TIME Ϊ��������

	
}

CCommTcpServer::~CCommTcpServer(void)
{
	//m_pCoreServer = NULL;	// ������ָ��
}

// ����������ָ��
void CCommTcpServer::set_core_server(CCoreServer* pCoreServer)
{
	m_pCoreServer = pCoreServer;
}


// ���� IOCP �����̵߳�����
void CCommTcpServer::set_work_thread_count(int iCount)
{
	m_nThreadCount = iCount;
}

// ���ⲿ������Ϣ��
int CCommTcpServer::set_msg_pool(CMemBlockPool* pMsgPool)
{
	if(!pMsgPool)
		return 10;

	m_pMsgPool = pMsgPool;
	m_bMsgPoolFromExternal = TRUE;						// ��Ϣ���Ǵ��ⲿ��������
	m_iMsgBlockSize = m_pMsgPool->get_mem_block_size();	// ��ó����ڴ��ĳߴ�

	return 0;
}

// ������Ϣ��ĳ���
void CCommTcpServer::set_msg_block_size(int iMsgBlockSize)
{
	if(m_bMsgPoolFromExternal)	// ��Ϣ���Ǵ��ⲿ��������
	{
		assert(m_pMsgPool);
		m_iMsgBlockSize = m_pMsgPool->get_mem_block_size();	// ��ó����ڴ��ĳߴ�
	}
	else	// ��Ϣ�����ڽ���
	{
		m_iMsgBlockSize = iMsgBlockSize;
	}
}

// ���÷��ͽ���ص����Ԫ������
void CCommTcpServer::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	if(iSendResultPoolInitCount<2)
		m_iSendResultPoolInitCount = 2;
	else
		m_iSendResultPoolInitCount = iSendResultPoolInitCount;	
}

// ���öԶ˷���ص����Ԫ������
void CCommTcpServer::set_service_handle_pool_init_count(int iServerHandlePoolInitCount)
{
	if(iServerHandlePoolInitCount<2)
		m_iServerHandlePoolInitCount = 2;
	else
		m_iServerHandlePoolInitCount = iServerHandlePoolInitCount;	
}

// �������ӽ���ص����Ԫ������
void CCommTcpServer::set_accept_result_pool_init_count(int iAcceptResultPoolInitCount)
{
	if(iAcceptResultPoolInitCount<2)
		m_iAcceptResultPoolInitCount = 2;
	else
		m_iAcceptResultPoolInitCount = iAcceptResultPoolInitCount;
}

// ������Ϣ�ص����Ԫ������
void CCommTcpServer::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_iMsgPoolInitCount = iMsgPoolInitCount;	
}

// ���ü�������رնԶ˵�ʱ�䣬�� ms Ϊ��λ
void CCommTcpServer::set_check_power_close_peer(LONGLONG iTime)
{
	LONGLONG iPulseCount = iTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iCheckInitiativeClosePeerPulseCount = iPulseCount;
}

// �����������ֳص�ʱ�䣬�� ms Ϊ��λ
void CCommTcpServer::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	LONGLONG iPulseCount = iShrinkPoolsTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iShrinkPoolsiPulseCount = iPulseCount;
}

// ������������ʱ�䣬�� ms Ϊ��λ
void CCommTcpServer::set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime)
{
	LONGLONG iPulseCount = iHeartbeatCheckTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iHeartbeatCheckPulseCount = iPulseCount;
}

// ����������������ʱ�䣬�� ms Ϊ��λ���� N ms ֮�ڿͻ���û���κ���Ϣ����������Ϊ�ÿͻ���������
void CCommTcpServer::set_no_heartbeat_die_time(int iNoHeartbeatDieTime)
{
	m_iNoHeartbeatDieTime = iNoHeartbeatDieTime;
}

// �Ƿ�������
BOOL CCommTcpServer::is_heartbeat(CORE_MSG_HEAD* pMsgHead)
{
	if(pMsgHead->lCordState && 0x00000001 > 0)	// ��������
		return TRUE;
	else										// ��������
		return FALSE;
}

// �Ƿ������ر�ָ���Զ˵�ָ��
BOOL CCommTcpServer::is_power_close_peer(CORE_MSG_HEAD* pMsgHead)
{
	if(pMsgHead->lCordState && 0x00000002 > 0)	// �������ر�ָ���Զ˵�ָ��
		return TRUE;
	else										// �������ر�ָ���Զ˵�ָ��
		return FALSE;
}

// ͳ�ƽ��յ����ʣ��Ǹ������Ŀ���
void CCommTcpServer::statistic_recv_rate()
{
	m_bStatisticRecvRate = !m_bStatisticRecvRate;

	if(m_bStatisticRecvRate)
	{
		::InterlockedExchange64(&m_lAtomMsgCount, 0);	// ԭ�Ӱ�������
		m_lStartStatisticTime = GetTickCount64();

		printf("������ͳ�ƽ��յ����ʡ� \n");
	}
	else
	{
		printf("�رա�ͳ�ƽ��յ����ʡ� \n");
	}
}

// ��ʼ��
int CCommTcpServer::init()
{
	int iResult = 0;

	SYSTEM_INFO			sysinfo = { 0 };
	int					i, nCount = 0;
	int					iErr = 0;

	// ��Ϣ��
	if(!m_pMsgPool)
	{
		m_pMsgPool = new CMemBlockPool(m_iMsgBlockSize, m_iMsgPoolInitCount, 20*m_iMsgPoolInitCount);		
		if(m_pMsgPool)
			m_pMsgPool->init();
		else
			return 10;	// ������Ϣ��ʧ��
	}

	// �Զ˷����
	m_pServerHandlePool = new CLightweightPool<CServerHandle>("�Զ˷����", m_iServerHandlePoolInitCount, 20*m_iServerHandlePoolInitCount);	
	if(m_pServerHandlePool)
		m_pServerHandlePool->init();
	else
		return 20;	// �����Զ˷����ʧ��

	// ���ӽ����
	m_pAcceptResultPool = new CLightweightPool<CAcceptResult>("���ӽ����", m_iAcceptResultPoolInitCount, 20*m_iAcceptResultPoolInitCount);	
	if(m_pAcceptResultPool)
		m_pAcceptResultPool->init();
	else
		return 30;	// �������ӽ����ʧ��

	// ���ͽ����
	m_pSendResultPool = new CLightweightPool<CSendResult>("���ͽ����", m_iSendResultPoolInitCount, 20*m_iSendResultPoolInitCount);		
	if(m_pSendResultPool)
		m_pSendResultPool->init();
	else
		return 40;	// �������ͽ����ʧ��

	// ���� IOCP 
	m_hCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if(!m_hCompletionPort)
		return 70;			// CreateIoCompletionPort ʧ��

	GetSystemInfo(&sysinfo);
	if(m_nThreadCount == 0)
	{
		m_nThreadCount = (int)sysinfo.dwNumberOfProcessors;
	}

	// ���� IOCP �Ĺ����߳�
	for(i = 0; i < m_nThreadCount; i++)
	{
		m_hThread[i] = (HANDLE)_beginthreadex(NULL, 0, &thread_work, (void*)this,  CREATE_SUSPENDED, &m_uThreadId[i]); 
		if(!m_hThread[i])
			return 80;	// ���������߳�ʧ��

		m_iThreadCount++ ;
	}

	// ������ʱ�����߳�
	m_hThreadShrinkPool = (HANDLE)_beginthreadex(NULL, 0, &thread_check, (void*)this,  CREATE_SUSPENDED, &m_uThreadShrinkPoolId); 
	if(!m_hThreadShrinkPool)
		return 90;	// ������ʱ�����߳�ʧ��

	return iResult;
}

// ��ʱ�����߳�
unsigned __stdcall CCommTcpServer::thread_check(LPVOID lpParameter)
{
	CCommTcpServer* pThis = (CCommTcpServer*)lpParameter;
	int iInterval = 0;

	while(!pThis->m_bIsExit)
	{
		pThis->m_iPulseCount++ ;
		
		// ��������رնԶ�
		if(0 == pThis->m_iPulseCount % pThis->m_iCheckInitiativeClosePeerPulseCount)
		{
			pThis->check_power_close_peer();	// ��������رնԶ˳�ʱ
		}

		// ����һ��
		// �� ms Ϊ��λ
		if(0 == pThis->m_iPulseCount % pThis->m_iShrinkPoolsiPulseCount)
		{
			iInterval = pThis->m_pMsgPool->get_current_element_count() - pThis->m_iMsgPoolInitCount;
			if(iInterval > pThis->m_iMsgPoolInitCount)	// �����ڳ�ֵ��������������
			{
				pThis->m_pMsgPool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pServerHandlePool->get_current_element_count() - pThis->m_iServerHandlePoolInitCount;
			if(iInterval > pThis->m_iServerHandlePoolInitCount)	// �����ڳ�ֵ��������������
			{
				pThis->m_pServerHandlePool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pAcceptResultPool->get_current_element_count() - pThis->m_iAcceptResultPoolInitCount;
			if(iInterval > pThis->m_iAcceptResultPoolInitCount)	// �����ڳ�ֵ��������������
			{
				pThis->m_pAcceptResultPool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pSendResultPool->get_current_element_count() - pThis->m_iSendResultPoolInitCount;
			if(iInterval > pThis->m_iSendResultPoolInitCount)	// �����ڳ�ֵ��������������
			{
				pThis->m_pSendResultPool->shrink_pool(iInterval, 0.25);
			}

			//printf("���ֳ�����һ�� \n");
		}
		
		if(0 == pThis->m_iPulseCount % pThis->m_iHeartbeatCheckPulseCount)	// �������
		{
			// ������жԶ˵�����
			pThis->check_all_peer_heartbeat();
			//printf("������� \n");
		}

		if(pThis->m_bStatisticRecvRate)	// �Ƿ�ͳ�ƽ�������
		{
			if(0 == pThis->m_iPulseCount % pThis->m_iStatistInterval)		// ͳ�Ƽ��
			{
				LONGLONG lSpace = GetTickCount64() - pThis->m_lStartStatisticTime;
				LONGLONG lRate = pThis->m_lAtomMsgCount/lSpace;
				if(lSpace)
				{
					if(lRate>0)
						printf("�������� %d/ms  \n", lRate);
					else
						printf("�������� %d/��  \n", 1000*pThis->m_lAtomMsgCount/lSpace);
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
	DWORD	dwBytesTransfered = 0;	// �����ʵ���ֽ���

	CCompleteResult*	pResult = NULL;
	CServerHandle*		pServerHandle = NULL;
	OVERLAPPED*			pOverlap = NULL;
	
	while(iResult != CCompleteResult::COMPLETE_RESULT_EXIT)
	{
		//dwResult = pThis->WorkProc();

		// ���IOCP ��Ӧ m_sListenSocket �Զ����ӡ����նԶ���Ϣ����Զ˷���Ϣ���رնԶ�
		// �Զ��������� CAcceptResult ��ʵ������
		// ���նԶ���Ϣ���� CRecvResult ��ʵ������
		// ��Զ˷���Ϣ���� CSendResult ��ʵ������
		// �رնԶ����� CTerminateResult ��ʵ������
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
				#if 0	// �˶β���ɾ������ԭ���ԵĽ�������ʾ�� 
						// ϸ�ڽ���� CServerHandle::OnRecvComplete ������

					DWORD dwCurrent = GetCurrentThreadId();
					printf("%s %d \n", pResult->get_class_name_flag(),dwCurrent);
				#endif

				iResult = pResult->OnIoComplete(dwBytesTransfered);
			}
		}
	}

	return 0;
}

// ���ü�����ַ
void CCommTcpServer::set_listen_addr(const char* szListenAddr)
{
	m_saListenAddr.sin_addr.s_addr = inet_addr(szListenAddr);
}

// ���ü����˿�
void CCommTcpServer::set_listen_port(unsigned int nPort)
{
	m_saListenAddr.sin_port = htons((unsigned short)nPort);
}

/* --------------------------------------------------------------------------

����˵������ʼ��
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
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
		printf("WSAStartup Failed ��WSAGetLastError()=%d \n", iErr);
		return 10;
	}

	m_sListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED); 
	iErr = WSAGetLastError();
	if(INVALID_SOCKET==m_sListenSocket)
	{
		printf("WSASocket Failed ��WSAGetLastError()=%d \n", iErr);
		return 20;
	}

	iRes = bind(m_sListenSocket, (sockaddr*)&m_saListenAddr, sizeof(m_saListenAddr));
	iErr = WSAGetLastError();
	if(0!=iRes)
	{
		printf("bind Failed ��WSAGetLastError()=%d \n", iErr);
		return 30;
	}
	else
	{
		iErr = listen(m_sListenSocket, 200);	// �ڶ����������ĵúܴ���Ҫ��WINDOWSϵͳ��Ĭ��ֵ???
		if(iErr != 0)
		{
			iErr = WSAGetLastError();
			return 40;
		}
		else
		{
			// ��� m_sListenSocket ���Խ����¶Զ����ӡ����նԶ���Ϣ����Զ˷���Ϣ���رնԶ�
			// �����¶Զ��������� CAcceptResult ��ʵ������
			// ���նԶ���Ϣ���� CRecvResult ��ʵ������
			// ��Զ˷���Ϣ���� CSendResult ��ʵ������
			// �رնԶ����� CTerminateResult ��ʵ������
			HANDLE hTmp = CreateIoCompletionPort((HANDLE)m_sListenSocket, m_hCompletionPort, 0, 0);
			iErr = GetLastError();
			if(!hTmp)
			{
				printf("bind Failed ��GetLastError()=%d \n", iErr);
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
����˵������������
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CCommTcpServer::start()
{
	int		iResult = 0;

	__try
	{
		// ������ʱ�����߳�
		ResumeThread(m_hThreadShrinkPool);

		// ���������߳�
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

// ��������
int CCommTcpServer::request_accept()
{
	int iResult = 0;;
	int	iErr = 0;
	CAcceptResult* pAcceptResult = NULL;	// ���ӽ��
	CServerHandle* pServerHandle = NULL;	// �Զ˷���

	__try
	{
		m_pAcceptResultPool->retrieve(&pAcceptResult);	// ���ӽ������
		assert(pAcceptResult);
		if(!pAcceptResult)
		{
			iResult = 10;
			__leave;
		}
		pAcceptResult->set_comm_tcp_server(this);	// ����Ҫ

		m_pServerHandlePool->retrieve(&pServerHandle);	// �Զ˷������
		assert(pServerHandle);

		if(!pServerHandle)
		{
			iResult = 20;
			__leave;
		}

		LONGLONG lChannelNo = m_stServerHandleMgr.add(pServerHandle);	// ����ͨ����

		pServerHandle->set_comm_tcp_server(this);	// ����Ҫ
		pServerHandle->set_channel_id(lChannelNo);	// ����ͨ����
		pServerHandle->set_msg_block_size(m_iMsgBlockSize);	// ������Ϣ��ĳ���

		//BOOL bFlag = pServerHandle->is_valid();	// �����ã���ʱӦ������Ч��

		iResult = pServerHandle->new_handle();	
		if(iResult>0)
		{
			iResult = 30;
			__leave;
		}

		pAcceptResult->set_service_handle(pServerHandle);

		//bFlag = pServerHandle->is_valid();	// �����ã���ʱӦ����Ч�ģ���Ϊ������ new_handle()

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
			// ���� 0���򵱽��յ�һ�����Ӻ��������أ�
			DWORD dwReceiveDataLength = 0, // dwReceiveDataLength
		#else
			// dwReceiveDataLength ������0�����ڽ��յ����Ӻ󣬱���ȵ��ͻ��˷�����һ�����ݲŷ��ء��ɸ���ʵ����Ҫ�趨�˲�����
			// ���������˵�������Ѿ��������ӣ�Ϊ�η�����ղ��� ACCEPT �¼���ԭ��
			// ������ܵ�Ŀ��֮һ���������ڿͻ������ɹ�ʱ����Ҫ�������ģ�����˸����������ж��Ƿ�Ϸ��Ŀͻ��ˣ��Ӷ��ߵ��������ӵĿͻ���
			DWORD dwReceiveDataLength = m_pAcceptResult->get_out_buf_len() - ((sizeof(SOCKADDR_IN)+16)*2),
		#endif

		// ����˿�Ͷ��һ���첽����
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
				//pAcceptResult->set_comm_tcp_server(NULL);		// Ӧ�ò���Ҫ��
				m_pAcceptResultPool->recycle(pAcceptResult);	// ���ӽ�����
			}

			if(pServerHandle)
			{
				//pServerHandle->set_comm_tcp_server(NULL);		// Ӧ�ò���Ҫ��
				m_pServerHandlePool->recycle(pServerHandle);	// �Զ˷�����
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

// ֹͣ����
int CCommTcpServer::stop()
{
	m_bIsExit = TRUE;
	int iResult = 0;

	iResult = stop_listen();

	// ���������̳߳�
	iResult = stop_work_threads();

	// �ȴ���ʱ�����߳̽���
	WaitForSingleObject(m_hThreadShrinkPool, WAIT_EXIT_TIME);

	// �ر����еĶԶ�
	close_all_peer();

	display_all_pool();

	if(!m_bMsgPoolFromExternal)	// TRUE ��ʾ��Ϣ���Ǵ��ⲿ��������
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

	//m_pCoreServer = NULL;	// ������ָ��

	return iResult;
}

// ���������̳߳�
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
����˵��������
���������
	lChannelNo	ͨ����
	pSendBlock	���͵���Ϣ�飬ע�⣺���۷��ͳɹ���ʧ�ܿ��ϵͳ���Ὣ pSendBlock �Զ���أ�
	                               
����ֵ��
    �ɹ��򷵻� 0�����һ�ص� OnSend ���������������IO����
	ʧ�ܻ�ص� OnSendFailed ���������ش��������£�
		10  ��Ч��ͨ����
		20  pMemBlock ����ʧ��
		30  pSendResult ����ʧ��
		40  pMemBlock->copy ʧ��
		80  WSASend ʧ��
		90  CCommTcpServer::send_data �쳣
--------------------------------------------------------------------------*/
int CCommTcpServer::send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock)
{
	CServerHandle* pServerHandle = m_stServerHandleMgr.find(lChannelNo);
	if(pServerHandle)
	{
		try
		{
			// ���۷��ͳɹ���ʧ�ܿ��ϵͳ���Ὣ pSendBlock �Զ���أ�
			int iRes = pServerHandle->send_data(pSendBlock);
			return 	iRes;
		}
		catch (...)
		{
			printf("CCommTcpServer::send_data �쳣��pServerHandle=%d \n", pServerHandle);
			return 90;
		}
	}
	else	// ��Ч��ͨ����
	{
		// ��Ӧ����ʧ��
		OnSendFailed(lChannelNo, pSendBlock);

		// ����Զ�����Ч�ģ�����Ч�ĶԶ˷����ݸ���������Ӧ OnSendComplete Щ����
		m_pMsgPool->recycle(pSendBlock);	// ��Ϣ���
	}

	return 10;	// ��Ч��ͨ����
}

/* --------------------------------------------------------------------------
����˵�������ز����ͣ�Ч�ʵͣ����á����ز����ͣ��˺���Ч�ʵͣ����á�ͨ��������ͻ���һ���Դ������������ݣ����緢���û��б��ĳ��ϡ�
���������
	lChannelNo	ͨ����
	iMainCode	��Ϣ����
	iSubCode	��Ϣ������
	pData		��������
	iDataLen	�������ݵĳ���                               
����ֵ��
    �ɹ��򷵻� 0�����һ�ص� OnSend ���������������IO����
	ʧ�ܻ�ص� OnSendFailed ���������ش��������£�
		10  ��Ч��ͨ����
		20  pMemBlock ����ʧ��
		30  pSendResult ����ʧ��
		40  pMemBlock->copy ʧ��
		80  WSASend ʧ��
��ע��
    ��Ϊ������Ҫ��Ϣ���أ����Ե�Ч��
	��Ч���������� OnRecv ��ʵ������װ�����ݺ�ֱ�ӻط���
--------------------------------------------------------------------------*/
int CCommTcpServer::retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData, int iDataLen, char* pszTextMark, BOOL bIsWait)
{
	if(!m_stServerHandleMgr.is_valid(lChannelNo))
		return 10;

	int iRes = 0;
	CMemBlock* pMemBlock = NULL;	// ��Ϣ�����

	// ����һ��Я��ָ�����ݵ���Ϣ��
	iRes = m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, pszTextMark, bIsWait);

	#if _DEBUG
		//printf("pMemBlock=%I64d \n", pMemBlock);	// ������
	#endif

	if(0==iRes && pMemBlock)
	{
		iRes = send_data(lChannelNo, pMemBlock);
	}

	return iRes;	// ��Ч��ͨ����
}

/* --------------------------------------------------------------------------
����˵����TCP�㲥�����������ݵ����е���Ч�Զ�
���������
	iMainCode	��Ϣ����
	iSubCode	��Ϣ������
	pData		��������
	iDataLen	�������ݵĳ���
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CCommTcpServer::tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData, int iDataLen, char* pszTextMark, BOOL bIsWait)
{
	int iRes = 0;

	CMemBlock* pMemBlock = NULL;	// ��Ϣ�����

	// ����һ��Я��ָ�����ݵ���Ϣ��
	iRes = m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, pszTextMark, bIsWait);

	if(0==iRes && pMemBlock)
		iRes = tcp_broadcase(pMemBlock, pszTextMark, bIsWait);
	else
		return 50;	// ��Ϣ�����ʧ��

	return iRes;	// ʧ�ܵĶԶ����� 
}

/* --------------------------------------------------------------------------
����˵����TCP�㲥�����������ݵ����е���Ч�Զ�
���������
	pSendBlock  ���͵���Ϣ��
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
	    10 pSendBlock ֵΪ��
		60 ���ڷ���ʧ�ܵĶԶ�
--------------------------------------------------------------------------*/
int CCommTcpServer::tcp_broadcase(CMemBlock*& pSendBlock, char* pszTextMark, BOOL bIsWait)
{
	if(!pSendBlock)
		return 10;

	int iFailCount = 0;	// ʧ�ܵĶԶ�����
	int iRes = 0;

	vector<CServerHandle*> vecServerHandle;
	m_stServerHandleMgr.get_all_valid(vecServerHandle);
	size_t iSize = vecServerHandle.size();

	for(int i=0; i<vecServerHandle.size(); i++)
	{
		CMemBlock* pNewBlock = NULL;
		m_pMsgPool->retrieve(&pNewBlock, pszTextMark, bIsWait);
		pNewBlock->copy(pSendBlock->base(), pSendBlock->length());	// ��Ϣ�鸳ֵ

		if(pNewBlock)
		{
			CServerHandle* pServerHandle = vecServerHandle[i];

			// ���۷��ͳɹ���ʧ�ܿ��ϵͳ���Ὣ pSendBlock �Զ���أ�
			iRes = pServerHandle->send_data(pNewBlock);
			if(iRes>0)
			{
				iFailCount++;
			}
		}
	}

	m_pMsgPool->recycle(pSendBlock);	// ���

	if(0 == iFailCount)
		return 0;	
	else
		return 60;	// ���ڷ���ʧ�ܵĶԶ�

}

// ��Ӧ�Զ��ѹر���
int CCommTcpServer::OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType)
{
	// �ڿͻ����ܼ��÷�����Ϣ���ҷ����Ҫ�ط���Ϣ������£������ռ�ù���ʱ���ͻ����ֹ��رյ������ż���޷���Ӧ�ر��¼�???
	// ��ʱֻ�ܿ�����������ȥ�ߵ���Щ�ѹرյ�û���ڷ������Ӧ�ĶԶ���
	// ����ÿͻ��˷���n������˯m���룬�Ϳ��Խ��ͷ���� CPU ��ռ���ʣ�30%����ͨ�����ᷢ���������¶��ˡ�
	//printf("ͨ����=%d , socket=%d �ѹر� \n", lChannelNo, socketClose);

	if(!m_pCoreServer)
		return 10;

	m_pCoreServer->m_lCurrentChannel = INVALID_CHANNEL_NO;

	return m_pCoreServer->OnClose(lChannelNo, socketClose, iCloseType);
}

/* --------------------------------------------------------------------------
����˵������Ӧ���ͳɹ�
���������
	lChannelNo	ͨ����
	pData			�������ݵ�����
	iDataLen		�������ݵ����ݵĳ���
��ע��
	��Ϣ���Ѿ�����ˣ��˴����� delete ��Ϣ
--------------------------------------------------------------------------*/
void CCommTcpServer::OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->OnSend(lChannelNo, pSendBlock);
}

/* --------------------------------------------------------------------------
����˵������Ӧ����ʧ��
���������
	lChannelNo	ͨ����
	pSendBlock	���͵���Ϣ�����ɿ��ϵͳ�Զ���أ�Ӧ�ò㲻�� pSendBlock ���
��ע��
    Ӧ�ò������ٴη��ʹ���Ϣ�������³���һ����Ϣ������ pNewBlock ��
	�� pNewBlock->copy(pSendBlock->base, pSendBlock->length()) ���ٷ��� pNewBlock 
--------------------------------------------------------------------------*/
void CCommTcpServer::OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->OnSendFailed(lChannelNo, pSendBlock);
}

// ��Ӧ���ӳɹ�
void CCommTcpServer::OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->m_lCurrentChannel = lChannelNo;

	m_pCoreServer->OnConnect(lChannelNo, saLocalAddr, saRemoteAddr);
}

// ��Ӧ����ʧ��
void CCommTcpServer::OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode)
{
	if(!m_pCoreServer)
		return;

	m_pCoreServer->OnConnectFail(saLocalAddr, saRemoteAddr, iErrorCode);
}



// ��Ӧ�հ���Ϣ���Ѿ���ԭ�Ӱ��ˡ�ע�⣺��ʱ��δ��أ��� CCommTcpServer ֮��Ļ��ƹ��
void CCommTcpServer::OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv)
{
	CORE_MSG_HEAD*  pMsgHead = NULL;
	m_pMsgPool->get_core_msg_head(pRecv, pMsgHead);

	InterlockedIncrement64(&m_lAtomMsgCount);

	// ���������ܼ��Ͳ���
	// ���ۣ����ô˶Ρ��롾���ô˶Ρ�������΢����΢��˵���ٶȱ��������ⲻ������ϢͶ����һ��
	#if 0	
		send_data(lChannelNo, pRecv);
		return ;
	#endif

	if(pMsgHead && is_heartbeat(pMsgHead))	// ��������
	{
		if(m_pCoreServer)
			m_pCoreServer->OnIsHeartbeat(pMsgHead->lChannelNo);	// ������Ӧ

		if(m_pMsgPool)
			m_pMsgPool->recycle(pRecv);	// ���
	}
	else
	{
		if(m_pCoreServer)
			m_pCoreServer->OnRecv(lChannelNo, pRecv);	// ��Ӧ�ò���
	}

}

// ��ӦͨѶ�������Ϣ
void CCommTcpServer::OnCommError(LONGLONG lChannelNo, char* pszError)
{
	printf("lChannelNo=%d ,%s \n", pszError);
}

// ��ʾ���еĳ���Ϣ
void CCommTcpServer::display_all_pool()
{
	printf("���������\n");
	printf(" MsgPool��       ������=%I64d �����=%I64d ���ڵ�ǰԪ��=%d \n",
		m_pMsgPool->get_retrieve_count(),
		m_pMsgPool->get_recycle_count(),
		m_pMsgPool->get_current_element_count()
		);

	printf(" SendResultPool��������=%I64d �����=%I64d ���ڵ�ǰԪ��=%d \n",
		m_pSendResultPool->get_retrieve_count(),
		m_pSendResultPool->get_recycle_count(),
		m_pSendResultPool->get_current_element_count()
		);

	printf(" �յ�ԭ�Ӱ� %9d �� \n", m_lAtomMsgCount);

	printf(" ServerHandlePool��������=%I64d �����=%I64d ���ڵ�ǰԪ��=%d \n",
		m_pServerHandlePool->get_retrieve_count(),
		m_pServerHandlePool->get_recycle_count(),
		m_pServerHandlePool->get_current_element_count()
		);

	printf(" AcceptResultPool�� ������=%I64d �����=%I64d ���ڵ�ǰԪ��=%d \n",
		m_pAcceptResultPool->get_retrieve_count(),
		m_pAcceptResultPool->get_recycle_count(),
		m_pAcceptResultPool->get_current_element_count()
		);

	// ��ӡ���е���Ч�Զ���Ϣ
	display_all_valid_peer();
}

// ��ӡ���е���Ч�Զ���Ϣ
void CCommTcpServer::display_all_valid_peer()
{
	vector<CServerHandle*> vecServerHandle;

	int iCount = m_stServerHandleMgr.get_all_valid(vecServerHandle);
	printf(" ��Ч�ĶԶ�����=%d \n", vecServerHandle.size());

	for(int i=0; i<vecServerHandle.size(); i++)
	{
		CServerHandle* p = vecServerHandle[i];
		if(p && p->is_valid())
		{
			printf("  ͨ����=%d �� SOCKET=%d  \n", p->get_channel_id(), p->get_handle());
		}
	}
}

/* --------------------------------------------------------------------------
����˵�����ر����еĶԶ�
��ע��
	�ڿͻ����յ���Ϣ�������ط���������յ���Ϣ��Ҳ�����ط�������£� 
	����˷��� closesocket ָ��ǿ�ƹرտͻ��ˣ��ͻ���ȴ�޷���Ӧ�ر��¼�??? 
--------------------------------------------------------------------------*/
void CCommTcpServer::close_all_peer()
{
	CThreadGuard guard(&m_lockClose);

#if 0	// �ɵ�
	vector<CServerHandle*> vecServerHandle;

	// ���������Ч�ĶԶ˷���
	int iCount = m_stServerHandleMgr.get_all_valid(vecServerHandle);

	size_t sizeTmp = vecServerHandle.size();
	if(iCount>0)
	{
		for(int i=0; i<vecServerHandle.size(); i++)
		{
			CServerHandle* p = vecServerHandle[i];
			if(p && p->is_valid())	// �Զ���Ч
			{
				m_stServerHandleMgr.remove_one(p);

				p->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
				p->close(p->get_close_type());
			}
		}
	}
#else	// �µ�
	vector<LONGLONG> vecChannelNo;

	// ���������Ч�Զ˵�ͨ����
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
����˵���������ر�ָ���ĶԶˣ��ͻ��˲�����ִ�ж�������
���������
	lChannelNo	ͨ����
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CCommTcpServer::power_close_peer(LONGLONG lChannelNo)
{
	// ��ͻ��˷������رյ���Ϣ

	CMemBlock* pPowerCloseBlock = NULL;

	if(m_pMsgPool)
	{
		// ����һ�������رնԶ˵���Ϣ��
		m_pMsgPool->retrieve_with_power_close(pPowerCloseBlock, __FUNCTION__);
		if(pPowerCloseBlock)
		{
			// ���������رյĶԶ�
			m_stServerHandleMgr.set_power_close_peer(lChannelNo);

			send_data(lChannelNo, pPowerCloseBlock);	// ��Զ˷��������رյ���Ϣ��
		}
	}

	return 0;
}

// ��������رնԶ˳�ʱ
int CCommTcpServer::check_power_close_peer()
{
	CThreadGuard guard(&m_lockClose);

	m_stServerHandleMgr.check_power_close_peer();

	return 0;
}

/* --------------------------------------------------------------------------
����˵�����ر�ָ���ĶԶ�
���������
	lChannelNo	ͨ����
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
��ע��
	�ڿͻ����յ���Ϣ�������ط���������յ���Ϣ��Ҳ�����ط�������£� 
	����˷��� closesocket ָ��ǿ�ƹرտͻ��ˣ��ͻ���ȴ�޷���Ӧ�ر��¼�??? 
--------------------------------------------------------------------------*/
int CCommTcpServer::close_peer(LONGLONG lChannelNo)
{
	CThreadGuard guard(&m_lockClose);

	int iResult = 10;	// ͨ������Ч

	if(m_stServerHandleMgr.is_valid(lChannelNo))
	{
		CServerHandle* pServerHandle = m_stServerHandleMgr.remove_one(lChannelNo);
		if(pServerHandle)
		{
			//printf("��Ҫɾ����ӡ:close_peer�˿ں� %d \n",lChannelNo);
			pServerHandle->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
			pServerHandle->close(pServerHandle->get_close_type());
		}
		else
		{
			return 20;	// pServerHandle ��Ч
		}
	}

	return iResult;
}


// ������жԶ˵�����
int CCommTcpServer::check_all_peer_heartbeat()
{
	CThreadGuard guard(&m_lockClose);

	vector<CServerHandle*> vecServerHandle;

	// ���������Ч�ĶԶ˷���
	int iCount = m_stServerHandleMgr.get_all_valid(vecServerHandle);

	size_t sizeTmp = vecServerHandle.size();
	if(iCount>0)
	{
		for(int i=0; i<vecServerHandle.size(); i++)
		{
			CServerHandle* p = vecServerHandle[i];
			if(p && p->is_valid())	// �Զ���Ч
			{
				if(p->check_heartbeat()>0)	// ������ʱ���Զ�����
				{
					LONGLONG lChannelNo = p->get_channel_id();
					m_stServerHandleMgr.remove_one(p);

					//printf("��Ҫɾ����ӡ:check_all_peer_heartbeat�˿ں� %d \n",lChannelNo);
					p->set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
					p->close(p->get_close_type());

					// ��Ӧ����������
					m_pCoreServer->OnNoHeartbeatDie(lChannelNo);
				}
			}
		}
	}

	return 0;
}
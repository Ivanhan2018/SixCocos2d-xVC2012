
#include "./PublicHead.h"
#include "./CommTcpClient.h"


#include "./CoreClient.h"

#include <process.h>

CCommTcpClient::CCommTcpClient(void)
{
	m_pCoreClient = NULL;	// ������ָ��

	m_hCompletionPort = NULL;

	m_hConnection = INVALID_SOCKET;

	m_pMsgPool = NULL;

	m_addrConnect.sin_family = AF_INET;
	m_addrConnect.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_addrConnect.sin_port = htons((unsigned short)5150);

	m_pStoreBox = NULL;
	m_iMsgBlockSize = 2048;

	m_iMsgPoolInitCount = 256;			// ��Ϣ�ص����Ԫ������
	m_iSendResultPoolInitCount = 256;	// ���ͽ���ص����Ԫ������

	m_bAutoReConnect = true;		// ���ߺ��Զ�����
	m_iAutoReConnectTime = 2000;	// ���ߺ��Զ������ļ��ʱ�䣬��λms�������ߺ����ms�����ٴ�����
	m_lConnectSuccedCount = 0;		// ���ӳɹ��Ĵ����������ж��Ƿ��������

	m_hThreadShrinkPool = NULL;
	m_uThreadShrinkPoolId = 0;

	m_iPulseCount = 0;	// ���������

	set_shrink_pools_time(5*60*1000);	// �������ֳص�ʱ�䣬Ĭ���� 5����
	set_send_heartbeat_time(30*1000);	// ������������ʱ�䣬Ĭ������

	m_iCloseType = CLOSE_TYPE_NO;	// �رշ�ʽ���ο� CLOSE_TYPE ��

	InterlockedExchange(&m_iIsConnect, 0);	// 1��ʾ�����У�0��ʾ����
}

CCommTcpClient::~CCommTcpClient(void)
{
	// �ͷ���Դ
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

// ����������ָ��
void CCommTcpClient::set_core_client(CCoreClient* pCoreClient)
{
	m_pCoreClient = pCoreClient;
}

// ������Ϣ��ĳ���
void CCommTcpClient::set_msg_block_size(int iMsgBlockSize)
{
	assert(iMsgBlockSize>0);
	m_iMsgBlockSize = iMsgBlockSize;

	// ������Ϣ��ĳ��ȣ���һ��һ��Ҫ�ӣ�������� ntdll.dll �ı���
	m_stRecvResult.set_msg_block_size(iMsgBlockSize);

	if(!m_pStoreBox)
	{
		m_pStoreBox = new CMemBlock(2*iMsgBlockSize+16);	// �� 16 ��Ϊ�˷�ֹ�߽����
	}
}

// ���÷��ͽ���ص����Ԫ������
void CCommTcpClient::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	m_iSendResultPoolInitCount = iSendResultPoolInitCount;	
}

// ������Ϣ�ص����Ԫ������
void CCommTcpClient::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_iMsgPoolInitCount = iMsgPoolInitCount;	
}

// ���ö��������ļ��ʱ�䣬��λms
void CCommTcpClient::set_reconnect_interval_time(int iAutoReConnectTime)
{
	m_iAutoReConnectTime = iAutoReConnectTime;
}

// ��ö�������
bool CCommTcpClient::get_reconnect()
{
	return m_bAutoReConnect;
}

// ���ö�������
void CCommTcpClient::set_reconnect(bool bAutoReConnect)
{
	m_bAutoReConnect = bAutoReConnect;
}

// ��ùرշ�ʽ
CLOSE_TYPE CCommTcpClient::get_close_type() 
{
	return m_iCloseType;
}

// ���ùرշ�ʽ
void CCommTcpClient::set_close_type(CLOSE_TYPE iCloseType) 
{
	m_iCloseType = iCloseType;
}

// �����������ֳص�ʱ�䣬iShrinkPoolsTime �� ms Ϊ��λ
void CCommTcpClient::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	//m_iShrinkPoolsTime = iShrinkPoolsTime;	

	LONGLONG iPulseCount = iShrinkPoolsTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iShrinkPoolsiPulseCount = iPulseCount;
}

// ���÷�����������ʱ��
void CCommTcpClient::set_send_heartbeat_time(LONGLONG iSendHeartbeatTime)
{
	LONGLONG iPulseCount = iSendHeartbeatTime/PULSE_TIME;
	if(0==iPulseCount)
		iPulseCount = 1;

	m_iSendHeartbeatPulseCount = iPulseCount;
}

// ����һЩ���õ� SOCKET ����
void CCommTcpClient::set_sock_opt(SOCKET s)
{
	// ���Ҫ�Ѿ���������״̬��soket�ڵ���closesocket��ǿ�ƹرգ�������	TIME_WAIT �Ĺ��̣�
	bool bDontLinger = false;
	setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(bool));

	#if 1
		// ���ջ�����
		int nRecvBuf = SEND_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

		// ���ͻ��壬ϵͳĬ�ϵ�״̬���ͺͽ���һ��Ϊ8688�ֽ�(ԼΪ8.5K)��
		// ��ʵ�ʵĹ����з������ݺͽ����������Ƚϴ󣬿�������socket����������������send(),recv()���ϵ�ѭ���շ���
		int nSendBuf = RECV_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	#else
		int nZero=0;

		// ����ڷ������ݵ�ʱ��ϣ����������ϵͳ��������socket�������Ŀ�����Ӱ���������ܣ�
		::setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(nZero));

		// ͬ����recv()�����������(Ĭ������ǽ�socket�����������ݿ�����ϵͳ������)��
		::setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&nZero, sizeof(nZero));
	#endif
};

// ��ʼ��
int CCommTcpClient::init()
{
	int iResult = 0;

	int			iError;
	WSADATA		WsaData = {0};
	iError = WSAStartup(MAKEWORD(2,2),&WsaData);
	if (SOCKET_ERROR == iError)
	{
		return 10;	// ִ�� WSAStartup ʧ��
	}

	m_stRecvResult.set_comm_tcp_client(this);

	// ��Ϣ��
	m_pMsgPool = new CMemBlockPool(m_iMsgBlockSize, m_iMsgPoolInitCount, 20*m_iMsgPoolInitCount);		
	if(m_pMsgPool)
		m_pMsgPool->init();
	else
		return 20;	// ������Ϣ��ʧ��

	// ���ͽ����
	m_pSendResultPool = new CLightweightPool<CClientSendResult>("���ͽ����", m_iSendResultPoolInitCount, 20*m_iSendResultPoolInitCount);		
	if(m_pSendResultPool)
		m_pSendResultPool->init();
	else
		return 40;	// �������ͽ����ʧ��

	if(is_valid())
	{
		m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;
		close(m_iCloseType);	 // �ͻ��������ر�
	}

	m_hConnection = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
   	iError = WSAGetLastError();
	if(!m_hConnection)
		return 50;	// m_hConnection ִ�� WSASocket ʧ��

	set_sock_opt(m_hConnection);

	// ���ջ�����
	int nRecvBuf = SEND_BUF_SIZE;
	setsockopt(m_hConnection, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	//���ͻ�����
	int nSendBuf = RECV_BUF_SIZE;
	setsockopt(m_hConnection, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));

	if(m_hCompletionPort)
	{
		CloseHandle(m_hCompletionPort);
		m_hCompletionPort = NULL;
	}
	m_hCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if(!m_hCompletionPort)
		return 60;	// CreateIoCompletionPort ʧ��

	// ���� IOCP �Ĺ����߳�
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &thread_work, (void*)this,  CREATE_SUSPENDED, &m_dwThreadId); 
	if(!m_hThread)
		return 70;	// ���� IOCP �Ĺ����߳�ʧ��

	// ������ʱ�����߳�
	m_hThreadShrinkPool = (HANDLE)_beginthreadex(NULL, 0, &thread_check, (void*)this,  CREATE_SUSPENDED, &m_uThreadShrinkPoolId); 
	if(!m_hThreadShrinkPool)
		return 90;	// ������ʱ�����߳�ʧ��

	return iResult;
}

int CCommTcpClient::start()
{
	int iResult = 0;
	m_bStop = false;

	// ������ʱ�����߳�
	ResumeThread(m_hThreadShrinkPool);

	// ���������߳�
	ResumeThread(m_hThread);

	return iResult;
}

int CCommTcpClient::stop()
{
	int iResult = 0;

	m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;

	power_close();		// �ͻ��������ر�

	m_bStop = true;

	// Ͷ����ֹ��ɶ˿ڵ�����
	::PostQueuedCompletionStatus(m_hCompletionPort, 0, 0, &m_stTerminateResult);

	// �ȴ� thread_work �̰߳�ȫ����
	WaitForSingleObject(m_hThread, INFINITE);

	// �ȴ���ʱ�����߳̽���
	WaitForSingleObject(m_hThreadShrinkPool, INFINITE);

	return iResult;
}

// IOCP �Ĺ����߳�
unsigned __stdcall CCommTcpClient::thread_work(LPVOID lpParameter)
{
	CCommTcpClient*	pThis = (CCommTcpClient*)lpParameter;
	DWORD			dwResult = 0;// while dwResult isn't same as 0 the thread exit

	do
	{
		dwResult = pThis->connect_to_server();
		while((dwResult != CCompleteResult::COMPLETE_RESULT_EXIT) && (dwResult != CCompleteResult::COMPLETE_RESULT_SOCKCLOSE))
		{
			InterlockedExchange(&pThis->m_iIsConnect, 1);	// 1��ʾ�����У�0��ʾ����
			dwResult = pThis->server_operate();
		}

		// �ǽ��������Ƕ�������״̬
		if(!pThis->m_bStop && pThis->m_bAutoReConnect)
		{
			InterlockedExchange(&pThis->m_iIsConnect, 0);	// 1��ʾ�����У�0��ʾ����
			Sleep(pThis->m_iAutoReConnectTime);	// ˯һ���������
		}
	}while(!pThis->m_bStop && pThis->m_bAutoReConnect);	// �ǽ��������Ƕ�������״̬


	return dwResult;
}

// �������ӵ�ַ
void CCommTcpClient::set_connect_addr(const char* szListenAddr)
{
	m_addrConnect.sin_addr.s_addr = inet_addr(szListenAddr);
}

// �������Ӷ˿�
void CCommTcpClient::set_connect_port(unsigned int nPort)
{
	m_addrConnect.sin_port = htons((unsigned short)nPort);
}

/* --------------------------------------------------------------------------
����˵�������ӳɹ��Ļص�
���������
	iResult	
	bIsReconnect	TRUE ��ʾ��������
	addrConnect		Ҫ���ӵķ����
--------------------------------------------------------------------------*/
void CCommTcpClient::OnConnect(bool bIsReconnect, sockaddr_in addrConnect)
{
	#if 0	// ������
		char szPrompt[64];
		memset(szPrompt, 0, sizeof(szPrompt));

		char* pszIP = inet_ntoa((in_addr)addrConnect.sin_addr); // ���IP��ַ 
		int	  iPort = ntohs(addrConnect.sin_port);				// ��ö˿�ֵ 

		if(bIsReconnect)
			_snprintf(szPrompt, sizeof(szPrompt)-1, "���������ɹ� %s ��%d \n", pszIP, iPort);
		else
			_snprintf(szPrompt, sizeof(szPrompt)-1, "��һ�����ӳɹ� %s ��%d \n", pszIP, iPort);

		printf(szPrompt);
	#endif

	AFTER_CONN_SUCC* pAfterConnSucc = new AFTER_CONN_SUCC;	// ���ӳɹ���
	pAfterConnSucc->bIsReconnect = bIsReconnect;
	pAfterConnSucc->addrConnect = addrConnect;
	pAfterConnSucc->pThis = this;

	#if 1
		// �ȴ��������յ����Ӻ��ʼ��������ϡ�
		// ��Ϊһ���ӳɹ������������Ϸ������ݣ����������ڳ�ʼ������Զ˵����ݣ�����Ҫ��һ���������Ӧ���ӳɹ�������ȴ���ֻ�����߳�����
		m_hThreadAfterConn = (HANDLE)_beginthreadex( NULL, 0, &thread_wait_server_init, (void*)pAfterConnSucc, 0, &m_dwThreadAfterConn );
		if(!m_hThreadAfterConn)
		{
			printf("�����߳� thread_wait_server_init ʧ�� \n");
		}
	#endif

}

// �ȴ��������յ����Ӻ��ʼ��������ϣ�
// ��Ϊһ���ӳɹ������������Ϸ������ݣ����������ڳ�ʼ������Զ˵����ݣ�����Ҫ��һ���������Ӧ���ӳɹ�������ȴ���ֻ�����߳�����
unsigned __stdcall  CCommTcpClient::thread_wait_server_init(void* pParam) 	
{
	if(pParam)
	{
		AFTER_CONN_SUCC* pAfterConnSucc = (AFTER_CONN_SUCC*)pParam;

		Sleep(300);	// ��Ϊһ���ӳɹ������������Ϸ������ݣ����������ڳ�ʼ������Զ˵����ݣ�����Ҫ��һ���������Ӧ���ӳɹ�

		pAfterConnSucc->pThis->m_pCoreClient->OnConnect(pAfterConnSucc->bIsReconnect, pAfterConnSucc->addrConnect);

		delete pAfterConnSucc;
	}

	return 0;
}

/* --------------------------------------------------------------------------
����˵��������ʧ�ܵĻص�
���������
	bIsReconnect	TRUE ��ʾ��������
	iError			WSAGetLastError() �����Ĵ�����	
	addrConnect		Ҫ���ӵķ����
--------------------------------------------------------------------------*/
void CCommTcpClient::OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect)
{
#if 0
	char szPrompt[64];
	memset(szPrompt, 0, sizeof(szPrompt));

	char* pszIP = inet_ntoa((in_addr)addrConnect.sin_addr); // ���IP��ַ 
	int	  iPort = ntohs(addrConnect.sin_port);				// ��ö˿�ֵ 

	if(bIsReconnect)
		_snprintf(szPrompt, sizeof(szPrompt)-1, "��������ʧ�� %s ��%d \n", pszIP, iPort);
	else
		_snprintf(szPrompt, sizeof(szPrompt)-1, "��һ������ʧ�� %s ��%d \n", pszIP, iPort);

	printf(szPrompt);
#endif

	m_pCoreClient->OnConnectFail(bIsReconnect, iError, addrConnect);
}

// ��Ӧ�رշ����
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

	// ���ӳɹ��Ĵ����������ж��Ƿ��������
	bool bIsReconnect = (m_lConnectSuccedCount>0)? true:false;

	if(0 == iResult)
	{
		::CreateIoCompletionPort((HANDLE)m_hConnection, m_hCompletionPort, 0, 0);
		if(0 == m_stRecvResult.recv_data())	// ����Ͷ��һ����
		{
			dwResult = CCompleteResult::COMPLETE_RESULT_OK;
		}

		m_lConnectSuccedCount++ ; 

		// ��Ӧ���ӳɹ�
		OnConnect(bIsReconnect, m_addrConnect);
	}
	else
	{
		// ��Ӧ����ʧ��
		OnConnectFail(bIsReconnect, iError, m_addrConnect);
	}

	return dwResult;
}

// �����������Ҫ��Ӧ����Ϣ������Ϣ��Terminate
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
		// �ڿͻ����յ���Ϣ�������ط���������յ���Ϣ��Ҳ�����ط�������£� 
		// ����˷��� closesocket ָ��ǿ�ƹرտͻ��ˣ��ͻ���ȴ�޷���Ӧ�ر��¼�??? ��������������˶κ�������
		printf("�յ� 0 ���� \n");
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

// �����رշ���ˣ�Ŀ�����÷������������ͻ��������ر�������
int CCommTcpClient::power_close()
{
	if(!is_valid())
		return 10;

	CMemBlock* pPowerCloseBlock = NULL;

	if(m_pMsgPool)
	{
		// ����һ�������رնԶ˵���Ϣ��
		m_pMsgPool->retrieve_with_power_close(pPowerCloseBlock, __FUNCTION__);

		if(pPowerCloseBlock)
		{
			send_data(pPowerCloseBlock);	// ��Զ˷��������رյ���Ϣ��
		}
	}

	close(CLOSE_TYPE_CLIENT_CLOSE);	// �ͻ��������ر�

	return 0;
}

/* --------------------------------------------------------------------------
����˵�����رշ����
���������
	bClientClose	TRUE��ʾ�ͻ��������رգ�FALSE��ʾ������˹رյ�
����ֵ��
    �ɹ��򷵻� TRUE�����򷵻� FALSE ��
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
		OnClose(m_iCloseType);	// �ͻ��������ر�

		// û��ֹͣ�������˶���������������˹ر�
		//if(!m_bStop && m_bAutoReConnect && !bClientClose)	// û��ֹͣ���ҿ����˶�������
		if(!m_bStop && m_bAutoReConnect && CLOSE_TYPE_FLASH_CLOSE==m_iCloseType)	// û��ֹͣ�������˶�������������
		{
			m_hConnection = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
	}

	if(CLOSE_TYPE_CLIENT_CLOSE==m_iCloseType || CLOSE_TYPE_NO)	// �ͻ��������رջ���δ֪ԭ��
	{
		m_bStop = true;
	}

	return bResult;
}

/* --------------------------------------------------------------------------
����˵�����жϰ�����Ч��
���������
	pData				Ҫ�жϵ��ֽ�������һ�����϶�λ���ֽ�������ǰ�ˡ�ע�⣺�ֽ���ͨ��������ܶ������
	iDataLen			�ֽ����ĳ���
	iEveryMsgBlockLen	ÿ����Ϣ���Ĺ̶����ȣ���ֵͨ��Ϊ 512��1024��2048��4096 �Ⱥ������ֵ
����ֵ��
	������Ч���򷵻� 0 ��
	������Ч���򷵻ش����룬�������б����£�
		10	��־λ�ж�ʧ��
		20	���ĳ����ж�ʧ��
--------------------------------------------------------------------------*/
int CCommTcpClient::is_packeg_valid(const BYTE* pData, int iDataLen)
{
	if( 0 == pData || 0 == iDataLen)
		return false;

	const CORE_MSG_HEAD* pCoreHead = (CORE_MSG_HEAD*)pData;

	if(0xaaaaaaaaaaaaaaaa != pCoreHead->uFlag)	// ��־λ�ж�
	{
		return SHE_CoreHeadFlagFail;	// ��־λ�ж�ʧ��
	}

	// ��ͷ�������ˣ������廹δ����������Ӧ�õȵ���һ������������ʱ���ж�
	if(pCoreHead->iTotalSize > iDataLen)
		return SHE_PackageNotOver;

	//--- �����ж� -----------------
	if (pCoreHead->iTotalSize > 0 && pCoreHead->iTotalSize <= m_iMsgBlockSize)
	{
	}
	else
	{
		return SHE_PackageLenFail;	// ���ĳ����ж�ʧ��
	}

	// ���ܲ��жϣ����� ???

	return 0;
};

/* --------------------------------------------------------------------------
����˵����������ԭ�Ӱ����� n ���С���ϳ�һ�������İ�
���������
    iResult	���ֵ���� COMPLETE_RESULT_OK �ȡ�
	pRecv	С����pRecv �ǲ����Թ�صġ�
����ֵ��
    �ɹ��򷵻� 0�����򷵻ش��������£�
	     5  ��ʾ���Զ������ر�
		20  �յ����ĳ�������
	    40	У���ʧ�ܣ�������Ч��
		50  У���ʧ�ܣ���һ����֮�������Ч��
--------------------------------------------------------------------------*/
int CCommTcpClient::make_atom_msg_block_Old(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCoreClient);
	if(!m_pCoreClient)
		return SHE_m_pCoreClientIsNull;

	CMemBlock* pSmallPackeg = (CMemBlock*)pRecv;	// С��

	if(pSmallPackeg->length()<=0)
	{
		printf("pSmallPackeg->length()=%d \n", pSmallPackeg->length());
		return SHE_SmallPackegIsZero;	// �յ����ĳ�������
	}

	int	iRecvDataSize = 0;
	int	iMsgSize = 0;
	int	iFlag = 0;


	//--- �ϲ���һ��ԭ�Ӱ��󣬾Ϳ��Գ���һ����Ϣ�����Ŵ�ԭ�Ӱ�������Ϣ��Ϳ��Ե����� ------------
	//int iTotalSize = 0;

	int iPackegLen = pSmallPackeg->length();			
	int iTempStoreBoxLen = m_pStoreBox->length();	// �����ã��洢���дͷ��ֵ����

	m_pStoreBox->copy(pSmallPackeg->base(), pSmallPackeg->length());	// ��Ϣ����洢��

	CORE_MSG_HEAD* pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

	// �жϰ�����Ч��
	int iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());

	if( 0 != iVerifyResult )	// У���ʧ�ܣ�������Ч�ģ�Ҳ����д����д
	{
		printf("iVerifyResult=%d \n", iVerifyResult);
		m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;
		close(m_iCloseType);	// �ͻ��������ر�

		return SHE_Verify_First_Fail;	// У���ʧ�ܣ���һ��������Ч��
	}

	bool bFirstHead = true;	// ��һ��ͷ

	BYTE* pBody = NULL;	// ����ĳ���
	int   iBodyLen = 0;	// ����

	while(pHead->iTotalSize > 0 && pHead->iTotalSize <= m_iMsgBlockSize  && m_pStoreBox->length() >= pHead->iTotalSize) 
	{
		if(bFirstHead)	// ��һ��ͷ����Ϊ�Ѿ��жϹ�����Ч���ˣ��˴�������һ���ж�
		{
			bFirstHead = false;	// ���óɲ��ǵ�һ��ͷ
		}
		else
		{
			pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

			// �жϰ�����Ч��
			iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());

			if( 0 != iVerifyResult )
			{
				printf("iVerifyResult=%d \n", iVerifyResult);
				
				#if 1	// ������
				    
				    iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());

					int iMainCode = 0;
					int iSubCode = 0;
					BYTE* pData = NULL;
					int iDataLen = 0;

					// ����ں���Ϣ����ʵ����
					m_pMsgPool->get_core_msg_data(m_pStoreBox, &iMainCode, &iSubCode, pData, &iDataLen);

					TEST_USER_INFO* p = (TEST_USER_INFO*)pData;
				#endif
				
				m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;
				close(m_iCloseType);	// �ͻ��������ر�

				return SHE_Verify_Other_Fail;	// У���ʧ�ܣ���һ����֮�������Ч��
			}
		}
		
		// ��ԭ�Ӱ���������
		CMemBlock* pAtomMsg = NULL;

		#if 1
			m_pMsgPool->retrieve(&pAtomMsg, __FUNCTION__);	// ����һ��ԭ����Ϣ��
			assert(pAtomMsg);
			if(!pAtomMsg)
				return SHE_pAtomMsg_retrieve_Fail;	// ԭ�Ӱ�����ʧ��
		#else
			// ��ʱ���ڲ�а���
			
		#endif

		pAtomMsg->copy(m_pStoreBox->rd_ptr(), pHead->iTotalSize);	

		CORE_MSG_HEAD* pAtomMsgHead = (CORE_MSG_HEAD*)(pAtomMsg->base());	// ԭ�Ӱ���ͷ

		// �Ƿ������ر�ָ���Զ˵�ָ�����true��ʾ�ǣ�����false��ʾ��
		if(pAtomMsgHead->is_power_close_peer())
		{
			return SHE_IS_POWER_CLOSED; // ��ʾ���Զ������ر�
		}

		if( pAtomMsg->length()>0)
		{
			int iMainCode = 0;
			int iSubCode = 0;
			BYTE* pData = NULL;
			int iDataLen = 0;

			m_pMsgPool->get_core_msg_data(pAtomMsg, &iMainCode, &iSubCode, pData, &iDataLen);

			const BYTE* cpData = pData;
			m_pCoreClient->OnRecv(iMainCode, iSubCode, cpData, iDataLen);	// ��Ӧ�հ���Ϣ
		}
		else
		{
			m_pCoreClient->OnCommError("CServerHandle::make_atom_msg_block ��pAtomMsg->length() ��ֵ�� 0 \n");
		}

		// ���ܽ��ճɹ���ʧ�ܣ��ͻ��˵�ԭ�Ӱ���Ҫ���
		// ��Ϊ�ͻ��˵�Ӧ�ò�ֻ���� pData������ֱ�Ӳ���ԭ�Ӱ�
		m_pMsgPool->recycle(pAtomMsg);	// ���

		m_pStoreBox->rd_ptr(pHead->iTotalSize);

		pHead = (CORE_MSG_HEAD*)(m_pStoreBox->rd_ptr());
	}

	if( m_pStoreBox->length() > 0 )	// pRecv ���в������İ��������а�
	{
		// ������������Ƶ�ͷ
		m_pStoreBox->remains_move_to_head();
	}
	else	// pRecv �ڶ��������İ����Ҷ����Ѿ�������
	{
		//m_pStoreBox->reset();
		m_pStoreBox->clear();
	}

	return 0;
}

/* --------------------------------------------------------------------------
����˵����������ԭ�Ӱ����� n ���С���ϳ�һ�������İ�
���������
    iResult	���ֵ���� COMPLETE_RESULT_OK �ȡ�
	pRecv	С����pRecv �ǲ����Թ�صġ�
����ֵ��
    �ɹ��򷵻� 0�����򷵻ش�����ο� SERVER_HANDLE_ERR ö�٣�
--------------------------------------------------------------------------*/
int CCommTcpClient::make_atom_msg_block(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCoreClient);
	if(!m_pCoreClient)
	{
		printf("m_pCoreClient �ǿ�ֵ \n");
		return SHE_m_pCoreClientIsNull;	// m_pCoreClient �ǿ�ֵ
	}

	CMemBlock* pSmallPackeg = (CMemBlock*)pRecv;	// С��

	if(pSmallPackeg->length()<=0)
	{
		printf("pSmallPackeg->length()=%d \n", pSmallPackeg->length());
		return SHE_SmallPackegIsZero;	// �յ����ĳ�������
	}

	int	iRecvDataSize = 0;
	int	iMsgSize = 0;
	int	iFlag = 0;

	//--- �ϲ���һ��ԭ�Ӱ��󣬾Ϳ��Գ���һ����Ϣ�����Ŵ�ԭ�Ӱ�������Ϣ��Ϳ��Ե����� ------------

	int iPackegLen = pSmallPackeg->length();			
	int iTempStoreBoxLen = m_pStoreBox->length();	// �����ã��洢���дͷ��ֵ����

	m_pStoreBox->copy(pSmallPackeg->base(), pSmallPackeg->length());	// ��Ϣ����洢��

	CORE_MSG_HEAD* pHead = NULL;
	int iVerifyResult = 0;	// �жϰ�����Ч��
	int iCount = 0;

	bool bFirstHead = true;	// ��һ��ͷ

	BYTE* pBody = NULL;	// ����ĳ���
	int   iBodyLen = 0;	// ����
	int   iVerifyFailCount = 0;	// ��Ч��ʧ�ܵĴ���

	do
	{
		pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

		// �жϰ�����Ч��
		iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());
		if( 0 != iVerifyResult )
		{
			if(SHE_PackageNotOver==iVerifyResult)	// ���廹δ����������Ӧ�õȵ���һ������������ʱ���ж�
				break;	// �˳�ѭ��

			iVerifyFailCount++;
			printf("iVerifyResult=%d iCount=%d \n", iVerifyResult,iCount);

			// �ҵ���һ����ͷ�ı�־λ
			bool bFind = false;
			while(m_pStoreBox->length()>0)
			{
				m_pStoreBox->rd_ptr(1);	// ��Ϣ�洢��ġ�����λ������һ���ֽ�
				pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();
				if(0xaaaaaaaaaaaaaaaa == pHead->uFlag)	// �ҵ���ͷ��
				{
					bFind = true;
					break;
				}
			}

			if(bFind)	// �ҵ���ͷ��
			{
				continue;
			}
			else	// ��Ϣ�洢�������û�а�ͷ
			{
				m_pStoreBox->reset();	// ��Ϣ�洢��ˢ��
				return SHE_Verify_Fail;
			}
		}

		// ��ԭ�Ӱ���������
		CMemBlock* pAtomMsg = NULL;

		#if 1
			m_pMsgPool->retrieve(&pAtomMsg, __FUNCTION__);	// ����һ��ԭ����Ϣ��
			assert(pAtomMsg);
			if(!pAtomMsg)
				return SHE_pAtomMsg_retrieve_Fail;	// ԭ�Ӱ�����ʧ��
		#else
			// ��ʱ���ڲ�а���
			
		#endif

		pAtomMsg->copy(m_pStoreBox->rd_ptr(), pHead->iTotalSize);	

		CORE_MSG_HEAD* pAtomMsgHead = (CORE_MSG_HEAD*)(pAtomMsg->base());	// ԭ�Ӱ���ͷ

		// �Ƿ������ر�ָ���Զ˵�ָ�����true��ʾ�ǣ�����false��ʾ��
		if(pAtomMsgHead->is_power_close_peer())
		{
			if(pAtomMsg)
				m_pMsgPool->recycle(pAtomMsg);	// ����Ҫ

			return SHE_IS_POWER_CLOSED; // ��ʾ���Զ������ر�
		}

		if( pAtomMsg->length()>0)
		{
			int iMainCode = 0;
			int iSubCode = 0;
			BYTE* pData = NULL;
			int iDataLen = 0;

			m_pMsgPool->get_core_msg_data(pAtomMsg, &iMainCode, &iSubCode, pData, &iDataLen);

			const BYTE* byData = pData;
			m_pCoreClient->OnRecv(iMainCode, iSubCode, byData, iDataLen);	// ��Ӧ�հ���Ϣ
		}
		else
		{
			m_pCoreClient->OnCommError("CServerHandle::make_atom_msg_block ��pAtomMsg->length() ��ֵ�� 0 \n");
		}

		// ���ܽ��ճɹ���ʧ�ܣ��ͻ��˵�ԭ�Ӱ���Ҫ���
		// ��Ϊ�ͻ��˵�Ӧ�ò�ֻ���� pData������ֱ�Ӳ���ԭ�Ӱ�
		m_pMsgPool->recycle(pAtomMsg);	// ���

		m_pStoreBox->rd_ptr(pHead->iTotalSize);

	} while(pHead->iTotalSize > 0 && pHead->iTotalSize <= m_iMsgBlockSize  && m_pStoreBox->length() >= pHead->iTotalSize) ;

	if( m_pStoreBox->length() > 0 )	// pRecv ���в������İ��������а�
	{
		// ������������Ƶ�ͷ
		m_pStoreBox->remains_move_to_head();
	}
	else	// pRecv �ڶ��������İ����Ҷ����Ѿ�������
	{
		m_pStoreBox->reset();
	}

	return 0;
}

/* --------------------------------------------------------------------------
����˵��������С�������
���������
    iResult	���ֵ���� COMPLETE_RESULT_OK �ȡ�
	pRecv	С����pRecv �ǲ����Թ�صġ�
����ֵ��
    �ο� COMPLETE_RESULT_OK��COMPLETE_RESULT_FAIL��COMPLETE_RESULT_SOCKCLOSE��COMPLETE_RESULT_EXIT ��
--------------------------------------------------------------------------*/
int CCommTcpClient::OnRecvComplete(int iResult, const CMemBlock* pRecv)
{
	// ���Ӱ�ȫ��������ǻ�������ļ�һ�����������ϻ�о�����ȫ����Ҳ��������Ƕ���� ???
	CThreadGuardWrite guard(&m_lockRecvComplete);

	//int iMakeAtomRes = 0;
	int iMakeAtomRes = 0;
	int iRecvDataRes = 0;

	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		// ������ԭ�Ӱ����� n ���С���ϳ�һ�������İ�
		iMakeAtomRes = make_atom_msg_block(iResult, pRecv);	
		if(0==iMakeAtomRes)
		{
			// ���� recv_data() λ�ã���������ǰ��,����make_whole_packeg()�������close()��closesocket���޷�����OnClose��Ϊ����������ô��close֮ǰ��recv
			// Ҫע��������Ǹô��Ƿ�����������,�����Ҫͬ���Ա�֤ʱ��
			iRecvDataRes = m_stRecvResult.recv_data();

			if(0!=iRecvDataRes)	// ��ʧ��
			{
				// ��ʧ��ͨ����ָ Socket �Ѿ����ر��������رյ�ԭ��֪�����Ҵ˴��Ĺر�Ҳ���ᱻ��Ӧ�ģ���Ϊ socket �Ѿ��ر�����
				m_iCloseType = CLOSE_TYPE_NO;	// 
				close(m_iCloseType);	

				printf("��ʼ�ǵ���Чֵ����δ֪ԭ�� \n");

				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}

			#if 0	// �˶�û��̫������壬��ʧ��ͨ����ָ Socket �Ѿ����ر��������رյ�ԭ��֪
				if(0!=iRecvDataRes)	// ��ʧ��
				{
					int iMaxCount = 20;
					int iSleepTime = 500;
					for(int i=0; i<iMaxCount; i++)	// �����Ķ� iMaxCount ��
					{
						Sleep(iSleepTime);

						printf("�����Ķ�ȡ�� %d �� \n", i);

						iRecvDataRes = m_stRecvResult.recv_data();
						if(0==iRecvDataRes)
							break;
					}
				}

				if(0!=iRecvDataRes)	// ������ȡʧ��
				{
					m_iCloseType = CLOSE_TYPE_WSARECV_ERR;	// ͨѶ������
					close(m_iCloseType);	

					printf("�����Ķ�ȡ��ʧ�����������رնԶ� \n");

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
			if(SHE_IS_POWER_CLOSED==iMakeAtomRes)	// ��ʾ��ʾ���Զ������ر�
			{
				set_reconnect(false);	// ��Ϊ�Ǳ�ʾ���Զ������رգ����Խ�ֹ��������

				//printf("��Ҫɾ����ӡ:OnRecvComplete \n");
				m_iCloseType = CLOSE_TYPE_SERVER_POWER_CLOSE;	// ��ʾ���Զ������ر�
				close(m_iCloseType);	
				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}

			m_iCloseType = CLOSE_TYPE_PACKAGE_ERR;	// ͨѶ������
			close(m_iCloseType);	// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�������������
									// ����� close �ر��� power_close �رն�����������
									// �ͻ��� close �ر��� power_close �رն�����������

			return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;

		#else
			switch(iMakeAtomRes)
			{
			case SHE_IS_POWER_CLOSED:	// ��ʾ��ʾ���Զ������ر�
				{
					set_reconnect(false);	// ��Ϊ�Ǳ�ʾ���Զ������رգ����Խ�ֹ��������

					m_iCloseType = CLOSE_TYPE_SERVER_POWER_CLOSE;	// ��ʾ���Զ������ر�
					close(m_iCloseType);	
					return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
				}
			case SHE_SmallPackegIsZero:	// �յ����ĳ�������
				{
					// Щ���İ�����Ҫ����ֱ��Խ���ͺ�
					// Ͷ��һ����
					m_stRecvResult.recv_data();

					return CCompleteResult::COMPLETE_RESULT_OK;;
				}
			case SHE_Verify_Fail:	// У���ʧ��
				{
					m_iCloseType = CLOSE_TYPE_PACKAGE_ERR;	// ͨѶ������
					close(m_iCloseType);	

					return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
				}
			}
			
		#endif
	}

	return CCompleteResult::COMPLETE_RESULT_OK;
}

/* ------------------------------------------------------------------------
����˵������Ӧ���ͳɹ�
���������
	pSendBlock	������Ϣ�飬���۷��ͳɹ���ʧ�ܣ���Ϣ�鶼���ɿ��ϵͳ�Զ���أ�Ӧ�ò㲻�� pSendBlock ���
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
����˵������Ӧ����ʧ��
���������
	lChannelNo	ͨ����
	pSendBlock	������Ϣ�飬���۷��ͳɹ���ʧ�ܣ���Ϣ�鶼���ɿ��ϵͳ�Զ���أ�Ӧ�ò㲻�� pSendBlock ���
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

// ������ɣ����۷��ͳɹ���ʧ�ܣ���Ϣ�鶼���ɿ��ϵͳ�Զ����
void CCommTcpClient::OnSendComplete(CClientSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock)
{
	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		// �ص������ͳɹ�
		OnSend(pSendBlock);	
	}
	else
	{
		// ����ʧ��
		OnSendFailed(pSendBlock);
	}

	// ���۷��ͳɹ���ʧ�ܣ���Ϣ�鶼Ҫ���
	m_pMsgPool->recycle(pSendBlock);	

	// ���۷��ͳɹ���ʧ�ܣ�����Ҫ���
	m_pSendResultPool->recycle(pSendResult);	// ���ͽ�����
}

/* --------------------------------------------------------------------------
����˵������������
���������
	lChannelNo	ͨ����
	pSendBlock	���͵���Ϣ�飬ע�⣺���۷��ͳɹ���ʧ�ܿ��ϵͳ���Ὣ pSendBlock �Զ���أ�
	                               
����ֵ��
    �ɹ��򷵻� 0�����һ�ص� OnSend ������
	ʧ�ܻ�ص� OnSendFailed ���������ش��������£�
		10  ��Ч��ͨ����
		20  ��Ч�� pSendBlock
		30  ���ͽ������ʧ��
		80  WSASend ʧ��
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
			iResult = 10;	// ��Ч��ͨ����
			__leave;
		}

		if(!pSendBlock)
		{
			iResult = 20;	// ��Ч�� pSendBlock
			__leave;
		}
		
		m_pSendResultPool->retrieve(&pSendResult);	// ���ͽ�����أ��ǵù��
		if(!pSendResult)
		{
			iResult = 30;	// ���ͽ������ʧ��
			__leave;
		}

		pSendResult->set_comm_tcp_client(this);
		pSendResult->set_mem_block(pSendBlock);

		DWORD m_dwBytesReceived = 0;

		wsabuf.buf = (char*)pSendBlock->base();
		wsabuf.len = pSendBlock->length();

		#if 1	// ������
			CORE_MSG_HEAD*  pMsgHead = NULL;
			m_pMsgPool->get_core_msg_head(pSendBlock, pMsgHead);
		#endif

		if(!is_valid())	// ���� WSASend ����ĵط���һ������
		{
			iResult = 10;	// ��Ч��ͨ����
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
				iResult = 80;	//WSASend ʧ��
			}
		}
	}
	__finally
	{
		if(iResult>0)	// ���ʹ�����Դ���
		{
			if(pSendResult)
				m_pSendResultPool->recycle(pSendResult);

			// ����Զ�����Ч�ģ�����Ч�ĶԶ˷����ݸ���������Ӧ OnSendComplete Щ����
			// ���Ա����ڴ˴����
			if(m_pMsgPool)
				m_pMsgPool->recycle(pSendBlock);	// ��Ϣ���
		}
	}

	return iResult;
}

/* --------------------------------------------------------------------------
����˵������������
���������
	pSendBlock	���͵���Ϣ�飬ע�⣺���۷��ͳɹ���ʧ�ܿ��ϵͳ���Ὣ pSendBlock �Զ���أ�                             
����ֵ��
    �ɹ��򷵻� 0�����һ�ص� OnSend ������
	ʧ�ܻ�ص� OnSendFailed ���������ش��������£�
	     5  ����ʧ��
		10  ��Ч��ͨ����
		20  ��Ч�� pSendBlock
		30  ���ͽ������ʧ��
		80  WSASend ʧ��
--------------------------------------------------------------------------*/
int CCommTcpClient::send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	if(!is_valid())
		return 10;

	CMemBlock* pMemBlock = NULL;	// ��Ϣ����أ��ǵù��
	m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, __FUNCTION__);

	if(!pMemBlock)
		return 5;

	return send_data(pMemBlock);
}


/* --------------------------------------------------------------------------
����˵�������ʹ������ݣ����ڲ���
���������	pSendBlock	���͵���Ϣ�飬ע�⣺���۷��ͳɹ���ʧ�ܿ��ϵͳ���Ὣ pSendBlock �Զ���أ�
	                               
����ֵ��
    �ɹ��򷵻� 0�����һ�ص� OnSend ������
	ʧ�ܻ�ص� OnSendFailed ���������ش��������£�
	     5  ����ʧ��
		10  ��Ч��ͨ����
		20  ��Ч�� pSendBlock
		30  ���ͽ������ʧ��
		80  WSASend ʧ��
--------------------------------------------------------------------------*/
int CCommTcpClient::send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	if(!is_valid())
		return 10;

	int iRes = 0;
	const int iErrCount = 5;	// ����Ĵ���

	CMemBlock* pMemBlockErr[iErrCount];	// �������Ϣ����أ��ǵù��
	memset(pMemBlockErr, 0, sizeof(pMemBlockErr));

	for(int i=0; i<iErrCount; i++)
	{
		m_pMsgPool->retrieve_with_error_content(pMemBlockErr[i], iMainCode, iSubCode, pData, iDataLen, __FUNCTION__);
	}

	CMemBlock* pMemBlock = NULL;	// ��ȷ����Ϣ����أ��ǵù��
	m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, pData, iDataLen, __FUNCTION__);

	if(!pMemBlock)
		return 5;

	for(int i=0; i<iErrCount; i++)	// �ȷ����
	{
		iRes = send_data(pMemBlockErr[i]);	
	}

	iRes = send_data(pMemBlock);		// �����ȷ�İ�

	return iRes;
}

// ��ʾ���еĳ���Ϣ
void CCommTcpClient::display_all_pool()
{
	long long iRetrieveCount = m_pMsgPool->get_retrieve_count();
	long long iRecycleCount = m_pMsgPool->get_recycle_count();
	int iCurCount = m_pMsgPool->get_current_element_count();


	printf("���������\n");
	printf("  m_pMsgPool��       ������=%I64d �����=%I64d�����ڵ�ǰԪ��=%d \n",
		iRetrieveCount, iRecycleCount, iCurCount);

	iRetrieveCount = m_pSendResultPool->get_retrieve_count();
	iRecycleCount = m_pSendResultPool->get_recycle_count();
	iCurCount = m_pSendResultPool->get_current_element_count();

	printf("  m_pSendResultPool��������=%I64d �����=%I64d�����ڵ�ǰԪ��=%d \n", 
		   iRetrieveCount, iRecycleCount, iCurCount);
}

// ����������
int CCommTcpClient::send_heartbeat_packeg()
{
	if(!is_valid())
		return 10;

	int iMainCode = 0;
	int iSubCode = 0;
	CMemBlock* pMemBlock = NULL;	// ��Ϣ����أ��ǵù��

	// ����һ��Я��ָ�����ݵ���Ϣ��
	int iRes = m_pMsgPool->retrieve_with_content_no_channel(pMemBlock, iMainCode, iSubCode, NULL, 0, __FUNCTION__);
	
	CORE_MSG_HEAD* pMsgHead = NULL;
	m_pMsgPool->get_core_msg_head(pMemBlock, pMsgHead);
	if(!pMsgHead)
		return 10;  // ��Ϣͷ������

	pMsgHead->set_heartbeat();	// ���ó�������

	if(0==iRes && pMemBlock)
		send_data(pMemBlock);

	return 0;
}

// ��ʱ�����߳�
unsigned __stdcall CCommTcpClient::thread_check(LPVOID lpParameter)
{
	CCommTcpClient* pThis = (CCommTcpClient*)lpParameter;

	int iInterval = 0;

	while(!pThis->m_bStop)
	{
		pThis->m_iPulseCount++;

		// ����һ�Σ��� PULSE_TIME ����Ϊ������λ���� N �� PULSE_TIME ����һ��
		if(0 == pThis->m_iPulseCount % pThis->m_iShrinkPoolsiPulseCount)
		{
			iInterval = pThis->m_pMsgPool->get_current_element_count() - pThis->m_iMsgPoolInitCount;
			if(iInterval > pThis->m_iMsgPoolInitCount)	// �����ڳ�ֵ��������������
			{
				pThis->m_pMsgPool->shrink_pool(iInterval, 0.25);
			}

			iInterval = pThis->m_pSendResultPool->get_current_element_count() - pThis->m_iSendResultPoolInitCount;
			if(iInterval > pThis->m_iSendResultPoolInitCount)	// �����ڳ�ֵ��������������
			{
				pThis->m_pSendResultPool->shrink_pool(iInterval, 0.25);
			}

			//printf("���ֳ�����һ�� \n");
		}

		// ����һ��������
		if(pThis->is_valid() && 0 == pThis->m_iPulseCount % pThis->m_iSendHeartbeatPulseCount)
		{
			//DWORD dwThreadId = GetCurrentThreadId();

			//char szTmp[128] = {0};
			//sprintf(szTmp, "����������,�߳�ID=%d ���������=%I64d ", dwThreadId, pThis->m_iPulseCount);
			//COften::OutputInfo(szTmp);

			// ����������
			pThis->send_heartbeat_packeg();
		}

		Sleep(PULSE_TIME);
	}

	return 0;
}
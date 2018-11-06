

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

	m_iPowerClosePeerTime = 0;	// �����رնԶ˵�ʱ��

	m_iCloseType = CLOSE_TYPE_FLASH_CLOSE;	// �رշ�ʽ���ο� CLOSE_TYPE ��
											// Ĭ��������

	m_iVerifyFailCount = 0;	// ��Ч��ʧ�ܵĴ���
}

CServerHandle::~CServerHandle(void)
{
	// �ͷ���Դ
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

// ���� CCommTcpServer ָ��
void CServerHandle::set_comm_tcp_server(CCommTcpServer*	pCommTcpServer)
{
	m_pCommTcpServer = pCommTcpServer;
}

// ������Ϣ��ĳ���
void CServerHandle::set_msg_block_size(int iMsgBlockSize)
{
	assert(iMsgBlockSize>0);
	m_iMsgBlockSize = iMsgBlockSize;

	m_stRecvResult.set_msg_block_size(iMsgBlockSize);

	if(!m_pStoreBox)
	{
		m_pStoreBox = new CMemBlock(2*iMsgBlockSize+16);	// �� 16 ��Ϊ�˷�ֹ�߽����
	}
}


// ����һЩ���õ� SOCKET ����
void CServerHandle::set_sock_opt(SOCKET s)
{
	#if 0
		// ���Ҫ�Ѿ���������״̬��soket�ڵ���closesocket��ǿ�ƹرգ�������	TIME_WAIT �Ĺ��̣�
		BOOL bDontLinger = FALSE;
		setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));
	#endif

	#if 1
		// ���ջ�����
		int nRecvBuf = SEND_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));

		// ���ͻ��壬ϵͳĬ�ϵ�״̬���ͺͽ���һ��Ϊ8688�ֽ�(ԼΪ8.5K)��
		// ��ʵ�ʵĹ����з������ݺͽ����������Ƚϴ󣬿�������socket����������������send(),recv()���ϵ�ѭ���շ���
		int nSendBuf = RECV_BUF_SIZE;
		setsockopt(s, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	#else
		/*
			1��һ��Ӧ�ó���ͨ���趨SO_SNDBUFΪ0�ѻ������رգ�Ȼ�󷢳�һ������send()���á�������������£�ϵͳ�ں˻��Ӧ�ó���Ļ�����������ֱ�����շ�ȷ���յ���������������send()���òŷ��ء�
				�ƺ�����һ���ж���������Ƿ��Ѿ�Ϊ�Է�ȫ���յ��ļ��ķ�����ʵ����ȴ������ˡ����뿴����ʹԶ��TCP֪ͨ�����Ѿ��յ�����ʵҲ���������������Ѿ��ɹ��͸��ͻ���Ӧ�ó���
				����Է����ܷ�����Դ��������������AFD.SYS���ܰ����ݿ�����Ӧ�ó�����һ����Ҫ���������ǣ���ÿ���߳���ÿ��ֻ�ܽ���һ�η��͵��ã�Ч�ʼ�����¡�

			2����SO_RCVBUF��Ϊ0���ر�AFD.SYS�Ľ��ջ�����Ҳ���������ܵõ���������ֻ����ʹ���յ��������ڱ�Winsock���͵Ĳ�ν��л��壬���㷢��receive����ʱ��
				ͬ��Ҫ���л���������������㱾������⻺������������ı����óѡ�

			3����������Ӧ������ˣ��رջ��������ڶ���Ӧ�ó�����Բ�����ʲô�����⡣ֻҪҪӦ�ó���ע����ʱ��ĳ�������ϱ��ּ���WSARecvs�ص����ã���ôͨ��û�б�Ҫ�رս��ջ�������
				���AFD.SYS��������Ӧ�ó����ṩ�Ļ��������ã���ô����û�б�Ҫʹ���ڲ��������������ܵķ�����Ӧ�ó�����Թرշ��ͻ�������ͬʱ������ʧ���ܡ�
				������������Ӧ�ó������ʮ��С�ģ���֤�����Ƿ�������ص����͵��ã������ǵȴ�ĳ���ص����ͽ����˲ŷ�����һ����
				���Ӧ�ó����ǰ�һ�������ٷ���һ����˳�������������˷ѵ����η����м�Ŀյ�ʱ�䣬��֮��Ҫ��֤�������������ڷ�����һ�������������̿���ת����һ����������
			4����������Ϊ0��û��ʲô�ô��� ��
		*/

		int nZero=0;

		// ����ڷ������ݵ�ʱ��ϣ����������ϵͳ��������socket�������Ŀ�����Ӱ���������ܣ�
		::setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(nZero));

		// ͬ����recv()�����������(Ĭ������ǽ�socket�����������ݿ�����ϵͳ������)��
		::setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&nZero, sizeof(nZero));
	#endif
};

// ���ùر�����
void CServerHandle::set_close_type(CLOSE_TYPE iCloseType)
{
	m_iCloseType = iCloseType;
}

// ��ùر�����
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

	set_close_type(CLOSE_TYPE_FLASH_CLOSE);	 // ��ʱĬ�ϳ����ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�

	set_sock_opt(m_hSocket);

	return 0;
}

// �µ�һ������ʱ��ʼ��һЩֵ
void CServerHandle::init_when_open()
{
	m_iCloseType = CLOSE_TYPE_FLASH_CLOSE;	// �رշ�ʽ���ο� CLOSE_TYPE ��
	m_pStoreBox->reset();

	m_iVerifyFailCount = 0;	// ��Ч��ʧ�ܵĴ���
}

int CServerHandle::open(sockaddr_in& saLocalAddr, sockaddr_in& saRemoteAddr)
{
	assert(m_pCommTcpServer);

	m_saLocalAddr = saLocalAddr;
	m_saRemoteAddr = saRemoteAddr;

	// д����־ 
	/*printf("ͨ����:%d LADDR:%d.%d.%d.%d:%d RADDR:%d.%d.%d.%d:%d \n", 
		m_lChannelNo, 
		saLocalAddr.sin_addr.S_un.S_un_b.s_b1, saLocalAddr.sin_addr.S_un.S_un_b.s_b2,
		saLocalAddr.sin_addr.S_un.S_un_b.s_b3, saLocalAddr.sin_addr.S_un.S_un_b.s_b4,
		ntohs(saLocalAddr.sin_port), 
		saRemoteAddr.sin_addr.S_un.S_un_b.s_b1, saRemoteAddr.sin_addr.S_un.S_un_b.s_b2, 
		saRemoteAddr.sin_addr.S_un.S_un_b.s_b3, saRemoteAddr.sin_addr.S_un.S_un_b.s_b4,
		ntohs(saRemoteAddr.sin_port));*/

	char szBuf[128]={0};
	sprintf(szBuf,"����ͨ����:%d RADDR:%d.%d.%d.%d:%d", 
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

			// �µ�һ������ʱ��ʼ��һЩֵ
			init_when_open();

			// �ص������ӳɹ�
			m_pCommTcpServer->OnConnect(m_lChannelNo, saLocalAddr, saRemoteAddr);
			::InterlockedExchange64(&m_lHeartbeatTime, GetTickCount64());
		}
		else
		{
			m_bIsOpen = FALSE;

			// �ص�������ʧ��
			m_pCommTcpServer->OnConnectFail(saLocalAddr, saRemoteAddr, iResult);
		}
	}

	return iResult;
}

// �رնԶ�
BOOL CServerHandle::close(CLOSE_TYPE iCloseType)
{
	CThreadGuard guard(&m_lockClose);
	assert(m_pCommTcpServer);

	if(INVALID_SOCKET==m_hSocket)	// ��Ч��ͨ����
		return FALSE;

	m_bIsOpen = FALSE;

	SOCKET sockClose = m_hSocket;
	
	closesocket(m_hSocket);
	m_hSocket = INVALID_SOCKET;

	// �Զ˹��
	m_pCommTcpServer->m_pServerHandlePool->recycle(this);	

	m_nRecvBufNonius = 0;

	memset(&m_saLocalAddr, 0, sizeof(sockaddr_in));
	memset(&m_saRemoteAddr, 0, sizeof(sockaddr_in));

	m_pCommTcpServer->OnClose(m_lChannelNo, sockClose, iCloseType);

	return TRUE;
}

/* --------------------------------------------------------------------------
����˵�����������
���������
    iResult	���ֵ���� COMPLETE_RESULT_OK ��
	pRecv	С����pRecv �ǲ����Թ�ص�
����ֵ��
    �ο� COMPLETE_RESULT_OK��COMPLETE_RESULT_FAIL��COMPLETE_RESULT_SOCKCLOSE��COMPLETE_RESULT_EXIT ��
--------------------------------------------------------------------------*/
int CServerHandle::OnRecvComplete(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCommTcpServer);

	int		iMakeAtomRes = 0;
	int		iRecvDataRes = 0;
	LONG	nPendingIo = 0;

	#if 0	// �˶β���ɾ������ԭ���ԵĽ�������ʾ
			// ���� recv_data �е� wsabuf.len = m_pRecv->size() ������£��ͻ��������������ڷ���˽����߳�������������
			// ���� recv_data �е� wsabuf.len = 16; ������£��ͻ��˵�һ��ԭ�Ӱ����ڷ���˽����߳�������������
			// ��ֵ����󣺰�����ͨ�˶Զ��̵߳���⣺����һ���̱߳� Sleep ����������Ŀ����̻߳ᴦ���յ���ֵ����������Ǵ�ġ�
			//             ����һ���̱߳� Sleep ����ס�󣬾ͳ��ֵȴ� iWaitN ms����Ŀ����̻߳Ტ���յ��� socket ��������Ϣ��
	        //             �� wsabuf.len = 16 ʱ���ͻ��˵�һ��ԭ�Ӱ����ڷ���˵ĵ�һ���߳���Ҳ�Ǳ� Sleep ���������Ҳ�������һ���߳������մ˿ͻ���ʣ�µİ� ��
			// ���ۣ�ͬһ�� Socket ��һ�� IOCP ��������ȡ���ݣ�Ҳ����ջ�������n���������ݣ�һ������ͬһ���߳�����ɵġ�
			//       ������֤��һ�� IOCP ��������ȡ���ݻ�����ͬһ���߳������գ�ʵʱ���������� IOCP �����������ɲ�ͬ���߳����������ݵġ�
			//       �ͻ��˷�����˳���ڷ����Ҳ���ϸ�˳����յģ�����󷢵İ�������

	    
		int iWaitN = 15*1000;	// ms
		static long volatile uAccess=0;	// Ŀ���ǽ�������һ���Գ̣����ҽ�������һ��
										// 0Ϊ��ͨ����1Ϊͨ��
		if(0==uAccess)
		{
			InterlockedExchange(&uAccess, 1);
			Sleep(iWaitN );
		}
	#endif

	#if 0	// �˶β���ɾ������ԭ���ԵĽ�������ʾ
			// ���� recv_data �е� wsabuf.len = m_pRecv->size() ������£��ͻ��������������ڷ���˽����߳�������������
			// ���� recv_data �е� wsabuf.len = 16; ������£��ͻ��˵�һ��ԭ�Ӱ����ڷ���˽����߳�������������
			// �������ʾͬһ���ͻ�����������ʱ�����߳�������������
			// ���ۣ����� IOCP �����������ɲ�ͬ���߳����������ݵģ�ע�⣺ͬһ�� Socket ��һ�� IOCP ��������ȡ���ݣ�Ҳ����ջ�������n���������ݣ�һ������ͬһ���߳�����ɵ�
		    //       �ͻ��˷�����˳���ڷ����Ҳ���ϸ�˳����յģ�����󷢵İ�������     
			DWORD dwCurrent = GetCurrentThreadId();
			printf("OnRecvComplete %d ��������%d \n", dwCurrent, ((CMemBlock*)pRecv)->length());
	#endif

	//// ���Ӱ�ȫ��������ǻ�������ļ�һ�����������ϻ�о�����ȫ����Ҳ��������Ƕ���� ???
	//CThreadGuardWrite guard(&m_lockRecvComplete);

	::InterlockedDecrement((PLONG)&m_nPendingIo);

	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		if(m_nPendingIo < MAX_PENDING_IO)
		{ 
			// ������ԭ�Ӱ����� n ���С���ϳ�һ�������İ�
			iMakeAtomRes = make_atom_msg_block(iResult, pRecv);	
			if(0==iMakeAtomRes)
			{
				// Ͷ��һ����
				iRecvDataRes = m_stRecvResult.recv_data();
				
				if(0!=iRecvDataRes)	// ��ʧ��
				{
					// ��ʧ��ͨ����ָ Socket �Ѿ����ر��������رյ�ԭ��֪�����Ҵ˴��Ĺر�Ҳ���ᱻ��Ӧ�ģ���Ϊ socket �Ѿ��ر�����
					m_iCloseType = CLOSE_TYPE_NO;	// 
					close(m_iCloseType);	

					char szTmp[64] = {0};
					sprintf(szTmp, "OnRecvComplete �� recv_data ʧ��, WSAGetLastError=%d  ", iRecvDataRes);
					COften::OutputInfo(szTmp);

					return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
				}
				else
				{
					::InterlockedIncrement((PLONG)&m_nPendingIo);
				}
			}
		}
		else	// �Զ��ڶ�ʱ���ڷ���̫��İ������˶Զ˹ر�
		{ 
			iMakeAtomRes = 220;
		}

		::InterlockedExchange64(&m_lHeartbeatTime, GetTickCount64());
	}
	else
	{
		//printf("��Ҫɾ����ӡ:OnRecvComplete \n");
		set_close_type(CLOSE_TYPE_SERVER_POWER_CLOSE);
		close(get_close_type());
	}

	if(iMakeAtomRes>0)
	{
		switch(iMakeAtomRes)
		{
		case SHE_IS_POWER_CLOSED:	// ��ʾ�ͻ��������ر�
			{
				m_iCloseType = CLOSE_TYPE_CLIENT_CLOSE;	// ��ʾ�ͻ��������ر�
				close(m_iCloseType);	
				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}
		case SHE_SmallPackegIsZero:	// �յ����ĳ�������
			{
				// Щ���İ�����Ҫ����ֱ��Խ���ͺ�
				// Ͷ��һ����
				m_stRecvResult.recv_data();
				::InterlockedIncrement((PLONG)&m_nPendingIo);

				return CCompleteResult::COMPLETE_RESULT_OK;
			}
		case SHE_Verify_Fail:	// У���ʧ��
			{
				set_close_type(CLOSE_TYPE_PACKAGE_ERR);	// ͨѶ������
				close(get_close_type());				// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�������������
														// ����� close �ر��� power_close �رն�����������
														// �ͻ��� close �ر��� power_close �رն�����������

				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}
		default:
			{
				set_close_type(CLOSE_TYPE_PACKAGE_ERR);	// ͨѶ������
				close(get_close_type());				// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�������������
														// ����� close �ر��� power_close �رն�����������
														// �ͻ��� close �ر��� power_close �رն�����������

				return CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;
			}
		}
	}

	return CCompleteResult::COMPLETE_RESULT_OK;
}

/* --------------------------------------------------------------------------
����˵��������
���������
	pSendBlock		���͵�����
����ֵ��
    �ɹ��򷵻� 0�����������IO���󣬻�ص� OnSendFailed ����
	ʧ�ܷ��ش��������£�
		10  ��Ч��ͨ����
		20  pSendBlock Ϊ��
		30  pSendResult ����ʧ��
		80  WSASend ʧ��
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
			iResult = 10;	// ��Ч��ͨ����
			__leave;
		}

		if(!pSendBlock)
		{
			iResult = 20;
			__leave;
		}

		m_pCommTcpServer->m_pSendResultPool->retrieve(&pSendResult);	// ���ͽ�����أ��ǵù��
		if(!pSendResult)
		{
			iResult = 30;	// pSendResult ����ʧ��
			__leave;
		}

		pSendResult->set_service_handle((void*)this);
		pSendResult->set_mem_block(pSendBlock);

		wsabuf.buf = (char*)pSendBlock->base();
		wsabuf.len = pSendBlock->length();

		if(!is_valid())	// ���� WSASend ����ĵط���һ������
		{
			iResult = 10;	// ��Ч��ͨ����
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
			if(WSA_IO_PENDING == iError)	// �ڷ��͵�;��
			{
				iResult = 0;
			}
			else
			{
				// ���� WSAECONNRESET 10054 �����ڴ�ָ�������Զ�

				iResult = 80;	//WSASend ʧ��
			}
		}
	}
	__finally
	{
		if(iResult>0)	// ���ʹ�����Դ���
		{
			if(pSendResult)
				m_pCommTcpServer->m_pSendResultPool->recycle(pSendResult);	// �Զ˹��

			// ����Զ�����Ч�ģ�����Ч�ĶԶ˷����ݸ���������Ӧ OnSendComplete Щ����
			// ���Ա����ڴ˴����
			if(m_pCommTcpServer && m_pCommTcpServer->m_pMsgPool)
				m_pCommTcpServer->m_pMsgPool->recycle(pSendBlock);	// ��Ϣ���
		}
	}

	return iResult;
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
int CServerHandle::is_packeg_valid(const BYTE* pData, int iDataLen)
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
		char szBuf[256]={0};
		sprintf(szBuf,"�������m_iMsgBlockSize=%d; iDataLen=%d-----��־λ=%d; ָ��״̬=%d; ������Ϣ�ĳ���=%d; ͨ����=%d; ����Ϣ=%d;  ����Ϣ=%d", 
			m_iMsgBlockSize, iDataLen, pCoreHead->uFlag, pCoreHead->lCordState, pCoreHead->iTotalSize, pCoreHead->lChannelNo, pCoreHead->iMainCode, pCoreHead->iSubCode);
		COften::OutputError(szBuf);
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
    �ɹ��򷵻� 0�����򷵻ش�����ο� SERVER_HANDLE_ERR ö�٣�
--------------------------------------------------------------------------*/
int CServerHandle::make_atom_msg_block(int iResult, const CMemBlock* pRecv)
{
	assert(m_pCommTcpServer);
	if(!m_pCommTcpServer)
	{
		printf("m_pCommTcpServer �ǿ�ֵ \n");
		return SHE_pCommTcpServerIsNull;	// m_pCommTcpServer �ǿ�ֵ
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

	do
	{
		pHead = (CORE_MSG_HEAD*)m_pStoreBox->rd_ptr();

		// �жϰ�����Ч��
		iVerifyResult = is_packeg_valid(m_pStoreBox->rd_ptr(), m_pStoreBox->length());
		if( 0 != iVerifyResult )
		{
			if(SHE_PackageNotOver==iVerifyResult)	// ���廹δ����������Ӧ�õȵ���һ������������ʱ���ж�
				break;	// �˳�ѭ��

			m_iVerifyFailCount++;
			printf("�������%d�������ʶ%d \n", m_iVerifyFailCount, iVerifyResult);

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
				#if ERROR_PACKAGER_CUT	// ����Ͽ��Զ�
					m_pStoreBox->reset();	// ��Ϣ�洢��ˢ��
					return SHE_Verify_Fail;

				#else	// ������ݶԶˣ����Ͽ����ȴ���һ����ȷ�İ���
					if(m_iVerifyFailCount < ERROR_PACKAGER_UP_LIMIT)	// ��û�����������ֵ
					{
						continue;
					}
					else	// �����˴��������ֵ
					{
						printf("�����˴��������ֵ�������Ͽ��Զ� \n");
						m_pStoreBox->reset();	// ��Ϣ�洢��ˢ��
						return SHE_Verify_Fail;
					}

				#endif
			}
		}

		// ��ԭ�Ӱ���������
		CMemBlock* pAtomMsg = NULL;

		#if 1
			m_pCommTcpServer->m_pMsgPool->retrieve(&pAtomMsg, __FUNCTION__);	// ����һ��ԭ����Ϣ��
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
				m_pCommTcpServer->m_pMsgPool->recycle(pAtomMsg);	// ����Ҫ

			return SHE_IS_POWER_CLOSED; // ��ʾ�ͻ��������ر�
		}

		if( pAtomMsg->length()>0)
		{
			pAtomMsgHead->lChannelNo = m_lChannelNo;	// ͨ���Ÿ�ֵ

			pAtomMsgHead->dwPeerIP = m_saRemoteAddr.sin_addr.S_un.S_addr;	// �������ֵ�͵�IP��ַ	;

			m_pCommTcpServer->OnRecv(m_lChannelNo, pAtomMsg);	// ��Ӧ�հ���Ϣ
		}
		else
		{
			m_pCommTcpServer->m_pMsgPool->recycle(pAtomMsg);	// ���
			m_pCommTcpServer->OnCommError(m_lChannelNo, "CServerHandle::make_atom_msg_block ��pAtomMsg->length() ��ֵ�� 0 \n");
		}

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

// ������ɣ�ע�⣺����Զ�����Ч�ģ�����Ч�ĶԶ˷����ݸ���������Ӧ OnSendComplete Щ����
void CServerHandle::OnSendComplete(CSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock)
{
	assert(m_pCommTcpServer);

	::InterlockedDecrement((PLONG)&m_nPendingIo); 
	
	if(iResult == CCompleteResult::COMPLETE_RESULT_OK)
	{
		::InterlockedExchange64(&m_lHeartbeatTime, GetTickCount64());

		// �ص������ͳɹ�
		m_pCommTcpServer->OnSend(m_lChannelNo, pSendBlock);	
	}
	else
	{
		// ����ʧ��
		m_pCommTcpServer->OnSendFailed(m_lChannelNo, pSendBlock);
	}

	// ���۷��ͳɹ���ʧ�ܣ���Ϣ�鶼Ҫ���
	m_pCommTcpServer->m_pMsgPool->recycle(pSendBlock);	

	// ���۷��ͳɹ���ʧ�ܣ�����Ҫ���
	m_pCommTcpServer->m_pSendResultPool->recycle(pSendResult);	// ���ͽ�����
}

void CServerHandle::test()
{

}

/* --------------------------------------------------------------------------
����˵�����������
����ֵ��
     0  ����
	10  ������ʱ���Զ�����
--------------------------------------------------------------------------*/
int CServerHandle::check_heartbeat()
{
	assert(m_pCommTcpServer);

	int iResult = 0;

	LONGLONG lCurrent = (LONGLONG)GetTickCount64();

	if(lCurrent - m_lHeartbeatTime <= m_pCommTcpServer->m_iNoHeartbeatDieTime)	// ����
		iResult = 0;
	else	// ������ʱ���Զ�����
		iResult = 10;
	
	return iResult;
}
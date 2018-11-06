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

// ���� CCommTcpServer ָ��
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
		// �����ã������ܷ�Ӷ�� IOCP �߳��������˺���
		// �������Ӳ�ͬ�� IOCP �߳��������˺���
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
		// GetAcceptExSockaddrs ��ר��Ϊ AcceptEx ����׼���ģ����� AcceptEx ���ܵĵ�һ�������еı��غ�Զ�̻����ĵ�ַ���ظ��û���
		GetAcceptExSockaddrs(	m_szOutputBuf,			// ָ�򴫵ݸ�AcceptEx�������տͻ���һ�����ݵĻ�����
								m_dwBytesReceived,		// �������Ĵ�С������ʹ��ݸ�AccpetEx������һ��
								dwAddrSize,				// Ϊ���ص�ַԤ���Ŀռ��С������ʹ��ݸ�AccpetEx����һ��
								dwAddrSize,				// ΪԶ�̵�ַԤ���Ŀռ��С������ʹ��ݸ�AccpetEx����һ��
								&pLocalAddr,			// �����������ӵı��ص�ַ
								&dwLocalSize,			// �������ر��ص�ַ�ĳ���
								&pRemoteAddr,			// ��������Զ�̵�ַ
								&dwRemoteSize);			// ��������Զ�̵�ַ�ĳ���
			
		#if _DEBUG
			char* szIP = NULL;
			sockaddr_in* pLocal = (sockaddr_in*)pLocalAddr;		// ���ص�ַ
			sockaddr_in* pRemote = (sockaddr_in*)pRemoteAddr;	// �Զ˵�ַ

			int iPort = ntohs(pLocal->sin_port);			// ��ö˿�ֵ

			DWORD dwIP =  pLocal->sin_addr.S_un.S_addr;	// �������ֵ�͵�IP��ַ	

			szIP = inet_ntoa((in_addr)pLocal->sin_addr);	// ����ִ��͵�IP��ַ

			//delete szIP;	// �����ͷţ���������
		#endif
			
		iResult = m_pServerHandle->open(*(sockaddr_in*)pLocalAddr, *(sockaddr_in*)pRemoteAddr);

		if(iResult>0)	// �ҿ�ʧ��
		{
			printf("m_pServerHandle->Open ʧ�ܣ������룺%d \n", iResult);

			if(m_pServerHandle)
			{
				m_pCommTcpServer->m_pServerHandlePool->recycle(m_pServerHandle);	// �Զ˷�����
			}
		}
		
		// �򿪳ɹ��ˣ��ٴ�Ͷ��һ�������ӡ�
		m_pCommTcpServer->request_accept();

		dwResult = CCompleteResult::COMPLETE_RESULT_OK;
	}
	else 
	{
		dwResult = CCompleteResult::COMPLETE_RESULT_FAIL;

		if(!m_pCommTcpServer->m_bIsExit)
		{
			//printf("CAcceptResult::OnIoComplete ʧ�ܣ�socket=%d, iSeconds=%d, �����룺%d \n", 
			//			m_pServerHandle->get_handle(), iSeconds, WSAGetLastError());

			printf("socket=%d �ѹر�, iSeconds=%d, �����룺%d \n", 
						m_pServerHandle->get_handle(), iSeconds, WSAGetLastError());
		}
	}

	m_pCommTcpServer->m_pAcceptResultPool->recycle(this);	// ���ӽ�����

	//printf("CAcceptResult ʵ��������أ�this=%d \n", (DWORD)this);

	return dwResult;
}
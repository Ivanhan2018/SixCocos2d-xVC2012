#include "./PublicHead.h"
#include "./ClientRecvResult.h"

#include "CommTcpClient.h"

CClientRecvResult::CClientRecvResult(void)
{
	m_iMsgBlockSize = 2048;
	m_pRecv = NULL;
	m_pCommTcpClient = NULL;
}

CClientRecvResult::~CClientRecvResult(void)
{
	if(m_pRecv)
	{
		delete m_pRecv;
	}
}

// ��������ָ��
void CClientRecvResult::set_comm_tcp_client(CCommTcpClient* pCommTcpClient)
{
	m_pCommTcpClient = pCommTcpClient;
}

// ������Ϣ��ĳ���
void CClientRecvResult::set_msg_block_size(int iMsgBlockSize)
{
	m_iMsgBlockSize = iMsgBlockSize;

	if(!m_pRecv)
	{
		m_pRecv = new CMemBlock(iMsgBlockSize);
	}
}

/* --------------------------------------------------------------------------
����˵����Ͷ��һ����
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CClientRecvResult::recv_data()
{
	assert(m_pCommTcpClient);
	if(!m_pCommTcpClient)
		return 10;

	int		iResult = CTC_ERR_recv_data;
	int		nError = 0;
	WSABUF	wsabuf = { 0 };
	DWORD	dwFlag = 0;

	m_dwBytesReceived = 0;
	m_pRecv->reset();

	wsabuf.buf = (char*)m_pRecv->base();

	#if 1	// ����ʹ��
		wsabuf.len = m_pRecv->size();
	#else	// �����ã����Զ��С�����ϳ�������
		wsabuf.len = 3;		
	#endif

	int iRecvFlag = WSARecv(
						m_pCommTcpClient->m_hConnection,
						&wsabuf,
						1,
						&m_dwBytesReceived,
						&dwFlag,
						this,
						0);
	if(iRecvFlag == 0)
	{
		iResult = 0;
	}
	else
	{
		/*
		WSANOTINITIALISED����ʹ�ô�API֮ǰӦ���ȳɹ��ص���WSAStartup()��
		WSAENETDOWN��WINDOWS�׽ӿ�ʵ�ּ�⵽������ϵͳʧЧ��
		WSAEFAULT��fromlen�����Ƿ���from��������С�޷�װ��˵�ַ��
		WSAEINTR���������̱�WSACancelBlockingCall()ȡ����
		WSAEINPROGRESS��һ��������WINDOWS�׽ӿڵ������������С�
		WSAEINVAL���׽ӿ�δ��bind()��������
		WSAENOTCONN���׽ӿ�δ���ӣ���������SOCK_STREAM���ͣ���
		WSAENOTSOCK�������ֲ���һ���׽ӿڡ�
		WSAEOPNOTSUPP��ָ����MSG_OOB�����׽ӿڲ���SOCK_STREAM���͵ġ�
		WSAESHUTDOWN���׽ӿ��ѱ��رա���һ���׽ӿ���0��2��how��������shutdown()�رպ��޷�����recv()�������ݡ�
		WSAEWOULDBLOCK���׽ӿڱ�ʶΪ������ģʽ�������ղ��������������
		WSAEMSGSIZE�����ݱ�̫���޷�ȫ��װ�뻺�������ʱ����С�
		WSAECONNABORTED�����ڳ�ʱ������ԭ�����·ʧЧ��
		WSAECONNRESET��Զ��ǿ����ֹ�����·��
		*/

		nError = WSAGetLastError();
		if(nError == WSA_IO_PENDING)
		{
			iResult = 0;
		}
	}
	
	return iResult;
}

int CClientRecvResult::OnRecvComplete(DWORD dwBytesTransfered)
{
	int	iResult = CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;

	assert(m_pCommTcpClient);
	if(!m_pCommTcpClient)
		return iResult;
	
	// ����Ҫ����Ϊ��ֱ����� m_pRecv->base() ��ֵ�ģ�û�о��� m_pRecv->copy ������Ҫ�ֹ� write ���ƶ�дָ��
	m_pRecv->write(dwBytesTransfered);	

	if(dwBytesTransfered > 0)	// �յ���������
	{
		// �ٴ�Ͷ��һ����
		iResult = m_pCommTcpClient->OnRecvComplete(CCompleteResult::COMPLETE_RESULT_OK, m_pRecv);
	}
	else	// �رնԶ�
			// ����������رնԶ�ʱ���������˶�
			// ���ǿͻ�������ر��ˣ����ʱ�� m_hSocket �Ѿ��类 close() �����ر���
			// ���Ƿ���˹ر��˿ͻ��ˣ����ʱ�� m_hSocket Ӧ�û���ֵ
	{
		CCommTcpClient* p = m_pCommTcpClient;

		switch(p->m_iCloseType)
		{
		case CLOSE_TYPE_CLIENT_CLOSE:	// �ͻ��������ر�
			{
				p->close(p->m_iCloseType);
				break;
			}
		case CLOSE_TYPE_NO:		// ��ʼ�ǵ���Чֵ����δ֪ԭ��
			{
				p->close(p->m_iCloseType);
				break;
			}
		default:	// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�����������
			{
				p->m_iCloseType = CLOSE_TYPE_FLASH_CLOSE;	// ���ϣ������ֹ����á��������ӡ��ķ�ʽģ��·���źŲ��ȶ�
				p->close(p->m_iCloseType);

				break;
			}
		}																
	}

	return iResult;
}

int CClientRecvResult::OnIoComplete(DWORD dwBytesTransfered)
{
	return (DWORD)OnRecvComplete(dwBytesTransfered);
}


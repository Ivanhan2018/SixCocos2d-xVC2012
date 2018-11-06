#include "./PublicHead.h"
#include "./RecvResult.h"

#include "./ServerHandle.h"

CRecvResult::CRecvResult(void)
{
	m_pServerHandle = NULL;
	m_iMsgBlockSize = 2048;
	m_pRecv = NULL;

	set_class_name_flag("CRecvResult");
}

CRecvResult::~CRecvResult(void)
{
	if(m_pRecv)
	{
		delete m_pRecv;
	}
}

void CRecvResult::set_service_handle(void* pServerHandlep)
{
	m_pServerHandle = pServerHandlep;
}

// ������Ϣ��ĳ���
void CRecvResult::set_msg_block_size(int iMsgBlockSize)
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
int CRecvResult::recv_data()
{
	CServerHandle* pServerHandle = (CServerHandle*)m_pServerHandle;

	int		iResult = 20;
	int		nError = 0;
	WSABUF	wsabuf = { 0 };
	DWORD	dwFlag = 0;

	m_dwBytesReceived = 0;
	m_pRecv->reset();

	wsabuf.buf = (char*)m_pRecv->base();

	#if _DEBUG
		#if 1	// ����ʹ��
			wsabuf.len = m_pRecv->size();
		#else	// �����ã����Զ��С�����ϳ�ԭ�Ӱ���ע��Ļ���??????
			wsabuf.len = 16;		// ���ܵ��ڱ�־λ uFlag �� ULONGLONG ��ռ�İ˸��ֽڣ����� is_packeg_valid Ч��������Ǵ��
									
		#endif
	#else
		wsabuf.len = m_pRecv->size();	// ����ʹ��
	#endif

	int iRecvFlag = WSARecv(
							pServerHandle->m_hSocket,
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
		nError = WSAGetLastError();
		if(nError == WSA_IO_PENDING)
		{
			return 0;
		}

		iResult = nError;
	}
	
	return iResult;
}

int CRecvResult::OnRecvComplete(DWORD dwBytesTransfered)
{
#if 0
	DWORD dwCurrent = GetCurrentThreadId();
	printf("OnRecvComplete %d \n", dwCurrent);
#endif

	int	iResult = CCompleteResult::COMPLETE_RESULT_SOCKCLOSE;

	m_pRecv->write(dwBytesTransfered);	// ����Ҫ����Ϊ��ֱ����� m_pRecv->base() ��ֵ�ģ�û�о��� m_pRecv->copy ������Ҫ�ֹ� write ���ƶ�дָ��

	if(dwBytesTransfered > 0)	// �յ���������
	{
		// �ٴ�Ͷ��һ����
		if(m_pServerHandle)
		{
			iResult = ((CServerHandle*)m_pServerHandle)->OnRecvComplete(CCompleteResult::COMPLETE_RESULT_OK, m_pRecv);
		}
	}
	else if(0 == dwBytesTransfered)	// �رնԶˣ�
									// ���Ƿ���˹رնԶˣ����ʱ�� m_pServerHandle->m_hSocket �Ѿ��类 CServerHandle::close() �ر���
									// ���ǿͻ��عر��ˣ����ʱ�� m_pServerHandle->m_hSocket Ӧ�û���ֵ
	{
		//// �ڿͻ����ܼ��÷�����Ϣ���ҷ����Ҫ�ط���Ϣ������£������ռ�ù���ʱ���ͻ����ֹ��رյ������ż���޷���Ӧ�ر��¼�???
		//// ��ʱֻ�ܿ�����������ȥ�ߵ���Щ�ѹرյ�û���ڷ������Ӧ�ĶԶ���
		//// ����ÿͻ��˷���n������˯m���룬�Ϳ��Խ��ͷ���� CPU ��ռ���ʣ�30%����ͨ�����ᷢ���������¶��ˡ�
		//printf(("�Զ˹ر��� \n");	// ������

		if(m_pServerHandle)
		{
			CServerHandle* p = (CServerHandle*)m_pServerHandle;

			CLOSE_TYPE iType = p->get_close_type();
			p->close(iType);
		}
	}

	return iResult;
}

int CRecvResult::OnIoComplete(DWORD dwBytesTransfered)
{
	return (DWORD)OnRecvComplete(dwBytesTransfered);
}
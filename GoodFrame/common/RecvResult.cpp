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

// 设置消息块的长度
void CRecvResult::set_msg_block_size(int iMsgBlockSize)
{
	m_iMsgBlockSize = iMsgBlockSize;

	if(!m_pRecv)
	{
		m_pRecv = new CMemBlock(iMsgBlockSize);
	}
}

/* --------------------------------------------------------------------------
函数说明：投递一个读
返回值：
    成功则返回 0，失败返回错误码如下：
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
		#if 1	// 正规使用
			wsabuf.len = m_pRecv->size();
		#else	// 测试用，测试多个小包整合成原子包，注意改回来??????
			wsabuf.len = 16;		// 不能低于标志位 uFlag 的 ULONGLONG 所占的八个字节，否则 is_packeg_valid 效验横竖都是错的
									
		#endif
	#else
		wsabuf.len = m_pRecv->size();	// 正规使用
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

	m_pRecv->write(dwBytesTransfered);	// 很重要，因为是直接针对 m_pRecv->base() 赋值的，没有经过 m_pRecv->copy ，所以要手工 write 来移动写指针

	if(dwBytesTransfered > 0)	// 收到正常数据
	{
		// 再次投递一个读
		if(m_pServerHandle)
		{
			iResult = ((CServerHandle*)m_pServerHandle)->OnRecvComplete(CCompleteResult::COMPLETE_RESULT_OK, m_pRecv);
		}
	}
	else if(0 == dwBytesTransfered)	// 关闭对端，
									// 若是服务端关闭对端，则此时的 m_pServerHandle->m_hSocket 已经早被 CServerHandle::close() 关闭了
									// 若是客户关关闭了，则此时的 m_pServerHandle->m_hSocket 应该还有值
	{
		//// 在客户端密集访发自消息而且服务端要回发消息的情况下，服务端占用过高时，客户端手工关闭但服务端偶尔无法响应关闭事件???
		//// 这时只能靠心跳检测机制去踢掉那些已关闭但没能在服务端响应的对端了
		//// 如果让客户端发出n个包后睡m毫秒，就可以降低服务端 CPU 的占用率，30%以下通常不会发生这样的事儿了。
		//printf(("对端关闭了 \n");	// 测试用

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
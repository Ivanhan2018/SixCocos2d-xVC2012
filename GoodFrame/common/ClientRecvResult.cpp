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

// 设置宿主指针
void CClientRecvResult::set_comm_tcp_client(CCommTcpClient* pCommTcpClient)
{
	m_pCommTcpClient = pCommTcpClient;
}

// 设置消息块的长度
void CClientRecvResult::set_msg_block_size(int iMsgBlockSize)
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

	#if 1	// 正规使用
		wsabuf.len = m_pRecv->size();
	#else	// 测试用，测试多个小包整合成完整包
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
		WSANOTINITIALISED：在使用此API之前应首先成功地调用WSAStartup()。
		WSAENETDOWN：WINDOWS套接口实现检测到网络子系统失效。
		WSAEFAULT：fromlen参数非法；from缓冲区大小无法装入端地址。
		WSAEINTR：阻塞进程被WSACancelBlockingCall()取消。
		WSAEINPROGRESS：一个阻塞的WINDOWS套接口调用正在运行中。
		WSAEINVAL：套接口未用bind()进行捆绑。
		WSAENOTCONN：套接口未连接（仅适用于SOCK_STREAM类型）。
		WSAENOTSOCK：描述字不是一个套接口。
		WSAEOPNOTSUPP：指定了MSG_OOB，但套接口不是SOCK_STREAM类型的。
		WSAESHUTDOWN：套接口已被关闭。当一个套接口以0或2的how参数调用shutdown()关闭后，无法再用recv()接收数据。
		WSAEWOULDBLOCK：套接口标识为非阻塞模式，但接收操作会产生阻塞。
		WSAEMSGSIZE：数据报太大无法全部装入缓冲区，故被剪切。
		WSAECONNABORTED：由于超时或其他原因，虚电路失效。
		WSAECONNRESET：远端强制中止了虚电路。
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
	
	// 很重要，因为是直接针对 m_pRecv->base() 赋值的，没有经过 m_pRecv->copy ，所以要手工 write 来移动写指针
	m_pRecv->write(dwBytesTransfered);	

	if(dwBytesTransfered > 0)	// 收到正常数据
	{
		// 再次投递一个读
		iResult = m_pCommTcpClient->OnRecvComplete(CCompleteResult::COMPLETE_RESULT_OK, m_pRecv);
	}
	else	// 关闭对端
			// 服务端主动关闭对端时，不会进入此段
			// 若是客户端自身关闭了，则此时的 m_hSocket 已经早被 close() 函数关闭了
			// 若是服务端关闭了客户端，则此时的 m_hSocket 应该还有值
	{
		CCommTcpClient* p = m_pCommTcpClient;

		switch(p->m_iCloseType)
		{
		case CLOSE_TYPE_CLIENT_CLOSE:	// 客户端主动关闭
			{
				p->close(p->m_iCloseType);
				break;
			}
		case CLOSE_TYPE_NO:		// 初始是的无效值或者未知原因
			{
				p->close(p->m_iCloseType);
				break;
			}
		default:	// 闪断，例如手工禁用【本地连接】的方式模拟路由信号不稳定，经过这里
			{
				p->m_iCloseType = CLOSE_TYPE_FLASH_CLOSE;	// 闪断，例如手工禁用【本地连接】的方式模拟路由信号不稳定
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


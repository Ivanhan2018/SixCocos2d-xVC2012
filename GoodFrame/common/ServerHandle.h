/********************************************************************
	created:	2013/01/24
	created:	20:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		侯国江
	
	purpose:	
*********************************************************************/

#ifndef SERVICE_HANDLE_H
#define SERVICE_HANDLE_H

#include "./PublicHead.h"

#include "./CoreHead.h"

#include "./RecvResult.h"
#include "./SendResult.h"

#include "./ThreadGuard.h"
#include "./ThreadGuardEx.h"

#include "./MemBlockPool.h"
#include "./CloseType.h"

class CCommTcpServer;

#define CORE_RETRIVE_MSG_TEXT 1 // 1 表示内核出池加入 __FUNCTION__ 字串，利于监测未归池的消息块。刚运营时最好用1值。
								// 0 表示内核不监测未归池的消息块，这样速度会快很多。在运营一段时间感觉稳定后，可以改成0值。

#define ERROR_PACKAGER_CUT 0	// 1 表示错包立即断开对端，优点：若对端发很大的错误包进行攻击，立即会被服务端断开，防攻击的能力强一些
								// 0 表示错包宽容对端（不断开，等待下一个正确的包），缺点：若对端发很大的错误包进行攻击，会使服务端的压力瞬间增得很大。


// 一个对端服务
class __declspec(dllexport) CServerHandle
{
public:
	

	friend class CChennelNoMgr;
	friend class CCommTcpServer;
	friend class CRecvResult;

	enum{	ERROR_PACKAGER_UP_LIMIT = 5,	};	// 错包的上限值，到达上限次数就断开

	enum { MAX_PENDING_IO = 500,
		 };

	// 发送缓冲，系统默认的状态发送和接收一次为8688字节(约为8.5K)；
	// 在实际的过程中发送数据和接收数据量比较大，可以设置socket缓冲区，而避免了send(),recv()不断的循环收发：
	enum{	SEND_BUF_SIZE=128*1024 };

	// 接收缓冲
	enum{	RECV_BUF_SIZE=128*1024 };

	
	//enum{	IS_CLIENT_POWER_CLOSE = 5,	// 表示客户端主动关闭
	//};

public:
	CServerHandle(void);
	~CServerHandle(void);

	void test();

	// 设置 CCommTcpServer 指针
	void set_comm_tcp_server(CCommTcpServer*	pCommTcpServer);

	// 设置消息块的长度
	void set_msg_block_size(int iMsgBlockSize);

	// 设置关闭类型
	inline void set_close_type(CLOSE_TYPE iCloseType);

	// 获得关闭类型
	inline CLOSE_TYPE get_close_type();

	// 新到一个连接时初始化一些值
	void init_when_open();

	int	open(sockaddr_in& saLocalAddr, sockaddr_in& saRemoteAddr);

	// 获得通道号
	inline LONGLONG get_channel_id();

	// 设置通道号
	inline void	 set_channel_id(LONGLONG lChannelNo);

	int				new_handle();
	inline SOCKET	get_handle();

	// 接收完成
	int OnRecvComplete(int iResult, const CMemBlock* pRecv);

	// 获得有效性
	inline BOOL is_valid();

	// 发送数据
	int send_data(CMemBlock*& pSendBlock);

	// 发送完成
	void OnSendComplete(CSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock);

	// 检查心跳
	int check_heartbeat();

public:		
	//--- 回调函数 ------------------------

	// 判断包的有效性
	int is_packeg_valid(const BYTE* pData, int iDataLen);

	// 制做成原子包，将 n 多个小包合成一个完整的包
	int make_atom_msg_block(int iResult, const CMemBlock* pRecv);



private:

	// 关闭对端
	BOOL close(CLOSE_TYPE iCloseType);

	// 设置一些常用的 SOCKET 参数
	void CServerHandle::set_sock_opt(SOCKET s);

public:
	volatile LONGLONG m_lHeartbeatTime;	// 心跳时间

	LONGLONG	m_lChannelNo;	// 通道与对端服务池有关，另外再考虑啦
	SOCKET		m_hSocket;	
	
	LONGLONG	m_iPowerClosePeerTime;	// 主动关闭对端的时间

private:
	sockaddr_in	m_saLocalAddr;
	sockaddr_in	m_saRemoteAddr;

	BOOL m_bIsOpen;	// 经过 open 函数并且成功

	volatile int	m_nPendingIo;

	int		m_nRecvBufNonius;

	CMemBlock*	m_pStoreBox;	// 消息存储箱，多个小包合成一个原子包，
								// 测试方法见 CRecvResult::recv_data() 函数中的 wsabuf.len = 16;	

	int		m_iMsgBlockSize;	// 消息块的长度

	CRecvResult	m_stRecvResult;	// 接收结果

	CSRWLock	m_lockRecvComplete;	// 锁 OnRecvComplete 的，不允许嵌套
	
	CCriticalSpection  m_lockClose;	// 锁 Close 的，为了安全（允许嵌套）

	CCommTcpServer*	m_pCommTcpServer;

	CLOSE_TYPE		m_iCloseType;	// 关闭方式，参考 CLOSE_TYPE 宏

	int				m_iVerifyFailCount;	// 包效验失败的次数
};

// 获得有效性
BOOL CServerHandle::is_valid()
{
	if(m_bIsOpen && INVALID_SOCKET!=m_hSocket)
		return TRUE;
	else
		return FALSE;
}

LONGLONG CServerHandle::get_channel_id()
{
	return m_lChannelNo;
}

// 设置通道号
void CServerHandle::set_channel_id(LONGLONG lChannelNo)
{
	m_lChannelNo = lChannelNo;
}

SOCKET CServerHandle::get_handle()
{
	return m_hSocket;
}

#endif
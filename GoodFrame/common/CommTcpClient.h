
#ifndef COMM_TCP_CLIENT_H
#define COMM_TCP_CLIENT_H

#include "./SelfModuleID.h"

#include "./MemBlockPool.h"
#include "./LightweightPool.h"

#include "./ClientRecvResult.h"
#include "./ClientSendResult.h"

#include "./TerminateResult.h"

#include "./ThreadGuard.h"
#include "./ThreadGuardEx.h"

#include "./CloseType.h"
#include "./CoreHead.h"

class CCoreClient;

class CCommTcpClient
{
public:
	friend class CCoreClient;

	struct AFTER_CONN_SUCC	// 连接成功后
	{
		AFTER_CONN_SUCC(){	memset(this, 0, sizeof(*this));	}

		bool bIsReconnect;
		sockaddr_in addrConnect;
		CCommTcpClient* pThis;
	};

	

	enum{	PULSE_TIME=100,		// 一个脉冲的时间，以ms为单位
		};

	// 发送缓冲，系统默认的状态发送和接收一次为8688字节(约为8.5K)；
	// 在实际的过程中发送数据和接收数据量比较大，可以设置socket缓冲区，而避免了send(),recv()不断的循环收发：
	enum{	SEND_BUF_SIZE=128*1024 };

	// 接收缓冲
	enum{	RECV_BUF_SIZE=128*1024 };

	
	friend class CClientSendResult;
	friend class CClientRecvResult;
public:
	CCommTcpClient(void);
	~CCommTcpClient(void);

public:

	// 等待服务器收到连接后初始化数据完毕
	static unsigned __stdcall  thread_wait_server_init(void* pParam);

	//--- 对外的接口 -------------------------------------------------

	// 设置宿主的指针
	void set_core_client(CCoreClient* pCoreClient);

	// 设置消息块的长度，这一句一定要加，否则出现 ntdll.dll 的崩溃
	void set_msg_block_size(int iMsgBlockSize=2048);

	// 设置发送结果池的最初元素数量
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// 设置消息池的最初元素数量
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	// 设置断线重连的间隔时间，单位ms
	void set_reconnect_interval_time(int iAutoReConnectTime);

	// 获得断线重连
	bool get_reconnect();

	// 设置断线重连
	void set_reconnect(bool bAutoReConnect);

	// 获得关闭方式
	CLOSE_TYPE get_close_type();

	// 设置关闭方式
	void set_close_type(CLOSE_TYPE iCloseType);

	// 设置收缩各种池的时间，iShrinkPoolsTime 以 ms 为单位
	void set_shrink_pools_time(long long iShrinkPoolsTime);

	// 设置发送心跳包的时间
	void set_send_heartbeat_time(long long iSendHeartbeatTime);

	/* --------------------------------------------------------------------------
	函数说明：初始化
	返回值：
		成功则返回 0，失败返回错误码如下：
		10  执行 WSAStartup 失败
		20  建立消息池失败
		40  建立发送发送结果池失败
		50  m_hConnection 执行 WSASocket 失败
		60  CreateIoCompletionPort 失败
		70  建立 IOCP 的工作线程失败
		90  建立定时检查的线程失败
	--------------------------------------------------------------------------*/
	int init();

	// 启动
	int start();

	// 停止
	int stop();

	// 发送数据
	int send_data(CMemBlock*& pSendBlock);

	// 发送数据
	int send_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// 发送错误数据，用于测试
	int send_error_data(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// 设置连接地址
	void set_connect_addr(const char* szListenAddr);

	// 设置连接端口
	void set_connect_port(unsigned int nPort);

	// 接收小包已完成
	int OnRecvComplete(int iResult, const CMemBlock* pRecv);

	// 主动关闭服务端，目的是让服务端能区别出客户端主动关闭与闪断
	int power_close();



	// 显示所有的池信息
	void display_all_pool();

	// 发送心跳包
	int send_heartbeat_packeg();

private:
	/* --------------------------------------------------------------------------
	函数说明：关闭服务端
	传入参数：
		bClientClose	TRUE 表示客户端主动关闭，FALSE 表示被服务端关闭的
	返回值：
		成功则返回 TRUE，否则返回 FALSE 。
	--------------------------------------------------------------------------*/
	bool close(CLOSE_TYPE iCloseType);

protected:		
	//--- 回调函数 ------------------------

	// 响应连接成功
	void OnConnect(bool bIsReconnect, sockaddr_in addrConnect);

	/* --------------------------------------------------------------------------
	函数说明：连接失败的回调
	传入参数：
		bIsReconnect	TRUE 表示断线重连
		iError			WSAGetLastError() 产生的错误码	
		addrConnect		要连接的服务端
	--------------------------------------------------------------------------*/
	void OnConnectFail(bool bIsReconnect, int iError, sockaddr_in addrConnect);

	// 响应发送成功
	void OnSend(const CMemBlock* pSendBlock);

	// 响应发送失败，
	void OnSendFailed(const CMemBlock* pSendBlock);

	// 响应关闭服务端
	void OnClose(CLOSE_TYPE iCloseType);

private:

	// 设置一些常用的 SOCKET 参数
	void set_sock_opt(SOCKET s);

	// 判断包的有效性
	int is_packeg_valid(const BYTE* pData, int iDataLen);

	// 制做成原子包，将 n 多个小包合成一个完整的包
	int make_atom_msg_block_Old(int iResult, const CMemBlock* pRecv);

	// 制做成原子包，将 n 多个小包合成一个完整的包
	int make_atom_msg_block(int iResult, const CMemBlock* pRecv);

	// 获得有效性
	inline bool is_valid();

	// 发送完成，无论发送成功或失败，消息块都会由框架系统自动归池
	void OnSendComplete(CClientSendResult*& pSendResult, int iResult, CMemBlock*& pSendBlock); 

	// IOCP 的工作线程
	static unsigned __stdcall thread_work(LPVOID lpParameter);

	// 连接服务器
	DWORD connect_to_server();

	// 服务操作，主要响应收消息、发消息、Terminate
	DWORD server_operate();

	// 定时检查的线程
	static unsigned __stdcall thread_check(LPVOID lpParameter);

public:
	CMemBlockPool*		m_pMsgPool;				// 池息池
	int					m_iMsgPoolInitCount;	// 消息池的最初元素数量

private:
	CCoreClient*	m_pCoreClient;	// 宿主的指针

	sockaddr_in		m_addrConnect;

	volatile SOCKET	m_hConnection;
	HANDLE			m_hCompletionPort;
	HANDLE			m_hThread;
	unsigned int	m_dwThreadId;

	HANDLE			m_hThreadAfterConn;		// 连接成功后的线程
	unsigned int	m_dwThreadAfterConn;	// 连接成功后的线程ID

	volatile LONG	m_iIsConnect;			// 1表示连接中，0表示断线
	volatile bool	m_bStop;
	CLOSE_TYPE		m_iCloseType;	// 关闭方式，参考 CLOSE_TYPE 宏

	bool			m_bAutoReConnect;		// 断线后自动重连
	int				m_iAutoReConnectTime;	// 断线后自动重连的间隔时间，单位ms，即断线后多少ms才能再次重连

	int				m_nRecvBufNonius;

	CMemBlock*	m_pStoreBox;	// 消息存储箱，多个小包合成一个原子包，
								// 测试方法见 CRecvResult::recv_data() 函数中的 wsabuf.len = 3;	

	int		m_iMsgBlockSize;	// 消息块的长度

	CLightweightPool<CClientSendResult>*	m_pSendResultPool;			// 发送结果池
	int										m_iSendResultPoolInitCount;	// 发送结果池的最初元素数量

	CClientRecvResult	m_stRecvResult;
	CTerminateResult	m_stTerminateResult;

	CSRWLock			m_lockRecvComplete;	// 锁 OnRecvComplete 的，不允许嵌套
	CCriticalSpection  m_lockClose;			// 锁 Close 的，为了安全（允许嵌套）

	LONGLONG	m_lConnectSuccedCount;	// 连接成功的次数，用来判断是否断线重连

	HANDLE			m_hThreadShrinkPool;		// 定时检查的线程
	unsigned int	m_uThreadShrinkPoolId;		// 定时检查的线程ID

	LONGLONG		m_iShrinkPoolsiPulseCount;	// 收缩各种池的脉冲次数
	LONGLONG		m_iSendHeartbeatPulseCount;	// 发送心跳包的脉冲次数

	long long	m_iPulseCount;	// 脉冲计数器

};

// 获得有效性
bool CCommTcpClient::is_valid()
{
	if(m_iIsConnect && INVALID_SOCKET!=m_hConnection)
		return true;
	else
		return false;	
}

#endif
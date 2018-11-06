/********************************************************************
	created:	2013/01/24
	created:	15:1:2013   10:40
	filename: 	E:\GoodFrame\common\AcceptResult.h
	file path:	E:\GoodFrame\common
	file base:	AcceptResult
	file ext:	h
	author:		侯国江
	
	purpose:	TCP 通讯模块
*********************************************************************/

#ifndef COMM_TCP_SERVICE_H
#define COMM_TCP_SERVICE_H

#include "./ChennelNoMgr.h"

#include "./ServerHandle.h"
#include "./TerminateResult.h"
#include "./AcceptResult.h"

#include "./LightweightPool.h"
#include "./CloseType.h"

class __declspec(dllexport) CCoreServer;

// 高效、稳定
class __declspec(dllexport) CCommTcpServer 
{
public:

	enum{	MAX_THREAD_COUNT = 20,	// 最大的 thread_work 线程数量
		};

	enum {	COMTIMEOUT_INFINITE				= -1,	// No time out
		 };

	enum{	PULSE_TIME=100,		// 一个脉冲的时间，以ms为单位
		};

	enum{
		INITIATIVE_CLOSE_PEER_OVER_TIME = 10 * 1000,	// 主动关闭对端的超时值，以ms为单位
		};
public:
	friend class CServerHandle;
	friend class CAcceptResult;
	friend class CRecvResult;
	friend class CCoreServer;

public:
	CCommTcpServer(void);
	~CCommTcpServer(void);

public:
	//--- 对外的接口 -------------------------------------------------

	// 设置宿主的指针
	void set_core_server(CCoreServer* pCoreServer);

	// 设置监听地址
	void set_listen_addr(const char* szListenAddr);

	// 设置监听端口
	void set_listen_port(unsigned int nPort);

	// 从外部传入消息池
	int set_msg_pool(CMemBlockPool* pMsgPool);

	// 设置消息块的长度
	void set_msg_block_size(int iMsgBlockSize=2048);

	// 设置消息池的最初元素数量
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	// 设置对端服务池的最初元素数量
	void set_service_handle_pool_init_count(int iServerHandlePoolInitCount);

	// 设置连接结果池的最初元素数量
	void set_accept_result_pool_init_count(int iAcceptResultPoolInitCount);

	// 设置发送结果池的最初元素数量
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// 设置检查主动关闭对端的时间，以 ms 为单位
	void set_check_power_close_peer(LONGLONG iTime);

	// 设置收缩各种池的时间，iShrinkPoolsTime 以 ms 为单位
	void set_shrink_pools_time(LONGLONG iShrinkPoolsTime);

	// 设置心跳检查的时间，以 PULSE_TIME 脉冲为基本单位，即 N 个 PULSE_TIME 检查一次
	void set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime);

	// 设置无心跳至死的时间，以 ms 为单位，即 N ms 之内客户端没有任何消息发过来就认为该客户端死掉了
	void set_no_heartbeat_die_time(int iNoHeartbeatDieTime);

	// 是否心跳包
	BOOL is_heartbeat(CORE_MSG_HEAD* pMsgHead);

	// 是否主动关闭指定对端的指令
	BOOL is_power_close_peer(CORE_MSG_HEAD* pMsgHead);

	/* --------------------------------------------------------------------------
	函数说明：初始化
	返回值：
		成功则返回 0，失败返回错误码如下：
		10    建立消息池失败
		20    建立对端服务池失败
		30    建立连接结果池失败
		40    建立发送结果池失败
		70    CreateIoCompletionPort 失败
		80    建立工作线程失败
		90    建立定时检查的线程失败
	--------------------------------------------------------------------------*/
	int init();

	// 启动服务
	int start();

	// 停止服务
	int stop();

	// 显示所有的池信息
	void display_all_pool();

	// 列印所有的有效对端信息
	void display_all_valid_peer();

	// 设置 IOCP 工作线程的数量
	void set_work_thread_count(int iCount);

	// 发送
	int send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock);

	// 出池并发送，效率低，慎用。出池并发送，此函数效率低，慎用。通常用于向客户端一次性大批量发送数据（例如发送用户列表）的场合。
	int retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	int tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// TCP广播，即发送数据到所有的有效对端
	int tcp_broadcase(CMemBlock*& pSendBlock, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// 检查所有对端的心跳
	int check_all_peer_heartbeat();

	// 主动关闭指定的对端，客户端不会再执行断线重连
	int power_close_peer(LONGLONG lChannelNo);

	// 关闭指定的对端
	int close_peer(LONGLONG lChannelNo);

	// 断开所有的对端
	void close_all_peer();

	// 统计接收的速率，是个反复的开关
	void statistic_recv_rate();

	// 检查主动关闭对端超时
	int check_power_close_peer();

protected:
	//--- 回调函数 -----------------------------------------------B--

	// 响应对端已关闭了
	int OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType);

	// 响应发送成功
	void OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// 响应发送失败
	void OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock);

	// 响应连接成功
	void OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr);	

	// 响应连接失败
	void OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode);

	/* --------------------------------------------------------------------------
	函数说明：响应收包消息，本函数是严格按照“先完后执”的原则来执行的，本质上说它就是IOCP里面的工作线程在调用本函数
	传入参数：
		lChannelNo
	传出参数：
		pRecv		消息块，已经是原子包了。注意：此时并未归池，由 CCommTcpServer 之外的机制归池
	--------------------------------------------------------------------------*/
	void OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv);

	// 响应通讯错误的消息
	void OnCommError(LONGLONG lChannelNo, char* pszError);


private:

	// IOCP 的工作线程
	static unsigned __stdcall thread_work(LPVOID lpParameter);

	// 定时检查的线程
	static unsigned __stdcall thread_check(LPVOID lpParameter);
	
	// 启动线程
	void start_work_threads();

	// 停止线程
	int	stop_work_threads();

	// 启动监听
	int	start_listen();

	// 停止监听
	int	stop_listen();

	// 请求连接
	int	request_accept();

private:

	BOOL volatile m_bIsExit;		// 退出状态

	HANDLE		m_hCompletionPort;
	DWORD		m_dwTmp;

	CChennelNoMgr m_stServerHandleMgr;	// 通道（对端服务）管理

	CMemBlockPool*	m_pMsgPool;				// 消息池，是可以从外部传入的
	BOOL			m_bMsgPoolFromExternal;	// TRUE 表示消息池是从外部传进来的
	int				m_iMsgPoolInitCount;	// 消息池的最初元素数量
	int				m_iMsgBlockSize;		// 消息块的长度

	CLightweightPool<CServerHandle>*	m_pServerHandlePool;			// 对端服务池
	int									m_iServerHandlePoolInitCount;	// 对端服务池的最初元素数量

	CLightweightPool<CAcceptResult>*	m_pAcceptResultPool;			// 连接结果池
	int									m_iAcceptResultPoolInitCount;	// 连接结果池的最初元素数量

	CLightweightPool<CSendResult>*	m_pSendResultPool;			// 发送结果池
	int								m_iSendResultPoolInitCount;	// 发送结果池的最初元素数量

	LONGLONG	m_iCheckInitiativeClosePeerPulseCount;	// 检查主动关闭对端的脉冲次数
	LONGLONG	m_iShrinkPoolsiPulseCount;		// 收缩各种池的脉冲次数
	LONGLONG	m_iHeartbeatCheckPulseCount;	// 心跳检查的脉冲次数
	LONGLONG	m_iNoHeartbeatDieTime;	// 无心跳至死的时间，以 ms 为单位，即 N ms 之内客户端没有任何消息发过来就认为该客户端死掉了

	
private:
	CCoreServer*	m_pCoreServer;	// 宿主的指针

	int			m_nThreadCount;
	sockaddr_in	m_saListenAddr;
	SOCKET		m_sListenSocket;

	CTerminateResult	m_stTerminateResult;

	HANDLE			m_hThread[MAX_THREAD_COUNT];	// 工作线程
	unsigned int	m_uThreadId[MAX_THREAD_COUNT];	// 工作线程ID
	int				m_iThreadCount;					// 工作线程数量

	long long	m_iPulseCount;	// 脉冲计数器

	HANDLE			m_hThreadShrinkPool;		// 定时检查的线程
	unsigned int	m_uThreadShrinkPoolId;		// 定时检查的线程ID

	CCriticalSpection  m_lockClose;	// 锁 Close 的，为了安全（允许嵌套）
	
	volatile LONGLONG m_lAtomMsgCount;	// 原子包的数量
	LONGLONG m_lStartStatisticTime;		// 开始统计的时间
	BOOL	 m_bStatisticRecvRate;		// 是否统计接收速率
	int		 m_iStatistInterval;		// 统计间隔，以 PULSE_TIME 为基本单们


		
};

#endif
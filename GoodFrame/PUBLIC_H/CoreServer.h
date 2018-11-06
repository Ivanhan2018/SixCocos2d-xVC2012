
#ifndef CORE_SERVER_H
#define CORE_SERVER_H

#include <WinSock2.h>

#include "./MemBlockPool.h"
#include "./CoreTimer.h"
#include "./Log.h"
#include "./CloseType.h"

class __declspec(dllexport)  CCommTcpServer;
class __declspec(dllexport) CGeneralWork;
class __declspec(dllexport) CGeneralDB;

#include <hash_map>
using std::hash_map;
using std::pair;

#define USE_NEW_WORKER 1	// 1 表示启用新型的 CGeneralWork ，通道号与工作线程绑定，严格遵守“先完后执”的顺序 
							// 0 表示用旧的 CBasicLogic ，通道号与工作线程不绑定，会出现“后发先完”的现象 

#define ALLOW_STRONG_CLOSE_PEER 1	// 1 表示允许强硬关闭对端，仅在测试时用此值
									// 0 表示禁止强硬关闭对端，正常时用此值 

class __declspec(dllexport) CCoreServer
{
public:
	CCoreServer(void);
	~CCoreServer(void);
public:
	enum{
		ERR_CS_exist_work_module = 10,		//  已存在任务模块ID啦，这是唯一的，不得重复

		};

public:

	//--- 纯虚函数 ------------------------------------------

	// 开始
	virtual int start() = 0;

	// 结束
	virtual int stop();

	// 设置消息块的长度
	void set_msg_block_size(int iMsgBlockSize=2048);

	// 设置消息池的最初元素数量
	void set_msg_pool_init_count(int iMsgPoolInitCount);

	//--- TCP 通讯层的设置函数 ------------------------------------------

	// 设置监听地址
	void set_listen_addr(const char* szListenAddr);

	// 设置监听端口
	void set_listen_port(unsigned int nPort);

	// 从外部传入消息池
	int set_msg_pool(CMemBlockPool* pMsgPool);

	// 设置对端服务池的最初元素数量
	void set_service_handle_pool_init_count(int iServerHandlePoolInitCount);

	// 设置连接结果池的最初元素数量
	void set_accept_result_pool_init_count(int iAcceptResultPoolInitCount);

	// 设置发送结果池的最初元素数量
	void set_send_result_pool_init_count(int iSendResultPoolInitCount);

	// 设置收缩各种池的时间，iShrinkPoolsTime 以 ms 为单位
	void set_shrink_pools_time(LONGLONG iShrinkPoolsTime);

	// 设置心跳检查的时间，以 PULSE_TIME 脉冲为基本单位，即 N 个 PULSE_TIME 检查一次
	void set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime);

	// 设置无心跳至死的时间，以 ms 为单位，即 N ms 之内客户端没有任何消息发过来就认为该客户端死掉了
	void set_no_heartbeat_die_time(int iNoHeartbeatDieTime);

	// 显示所有的池信息
	void display_all_pool();

	// 设置数据库心跳的时间
	void set_db_heartbeat_time(int iDbHeartbeatTime);

	// 设置 IOCP 工作线程的数量
	void set_work_thread_count(int iCount);

	// 设置日志的路径
	int set_log_path(TCHAR* pszPathName);

	/* --------------------------------------------------------------------------
	函数说明：发送，最推荐的
	传入参数：
		lChannelNo	通道号
		pSendBlock	发送的消息块，注意：无论发送成功与失败框架系统都会将 pSendBlock 自动归池，                              
	返回值：
		成功则返回 0，而且会回调 OnSend 函数。但如果出现IO错误，
		失败会回调 OnSendFailed 函数，返回错误码如下：
			10  无效的通道号
			20  pMemBlock 出池失败
			30  pSendResult 出池失败
			40  pMemBlock->copy 失败
			80  WSASend 失败
	--------------------------------------------------------------------------*/
	int send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock);

	/* --------------------------------------------------------------------------
	函数说明：出池并发送，效率低，慎用。出池并发送，此函数效率低，慎用。通常用于向客户端一次性大批量发送数据（例如发送用户列表）的场合。
	传入参数：
		lChannelNo	通道号
		iMainCode	消息主码
		iSubCode	消息辅助码
		pData		包体数据
		iDataLen	包体数据的长度                               
	返回值：
		成功则返回 0，而且会回调 OnSend 函数。但如果出现IO错误，
		失败会回调 OnSendFailed 函数，返回错误码如下：
			10  无效的通道号
			20  pMemBlock 出池失败
			30  pSendResult 出池失败
			40  pMemBlock->copy 失败
			80  WSASend 失败
	备注：
		因为本函数要消息出池，所以低效。
		高效的作法是用 OnRecv 的实参重新装填数据后直接回发。
	--------------------------------------------------------------------------*/
	int retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0, char* pszTextMark=NULL, BOOL bIsWait=TRUE);

	// TCP广播，即发送数据到所有的有效对端
	int tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData, int iDataLen);

	// TCP广播，即发送数据到所有的有效对端
	int tcp_broadcase(CMemBlock*& pSendBlock);

	// 检查所有对端的心跳
	int check_all_peer_heartbeat();

	#if ALLOW_STRONG_CLOSE_PEER
		// 关闭指定的对端，用 power_close_peer 代替
		int close_peer(LONGLONG lChannelNo);
	#endif

	/* --------------------------------------------------------------------------
	函数说明：主动关闭指定的对端，客户端不会再执行断线重连
	传入参数：
		lChannelNo	通道号
	返回值：
		成功则返回 0，失败返回错误码如下：
	备注：
		在客户端收到消息后立即回发、服务端收到消息后也立即回发的情况下， 
		服务端发出 closesocket 指令强制关闭客户端，客户端却无法响应关闭事件??? 
	--------------------------------------------------------------------------*/
	int power_close_peer(LONGLONG lChannelNo);

	// 关闭所有的对端
	void close_all_peer();

	// 统计接收的速率，是个反复的开关
	void statistic_recv_rate();

	//--- TCP 通讯层回调函数 ------------------------------------------

	// 心跳响应
	virtual int OnIsHeartbeat(LONGLONG lChannelNo) = 0;

	// 响应对端已关闭了
	virtual int OnClose(LONGLONG lChannelNo, SOCKET socketClose, CLOSE_TYPE iCloseType) = 0;

	// 响应发送成功
	virtual void OnSend(LONGLONG lChannelNo, const CMemBlock* pSendBlock) = 0;

	// 响应发送失败
	virtual void OnSendFailed(LONGLONG lChannelNo, const CMemBlock* pSendBlock) = 0;

	// 响应连接成功
	virtual void OnConnect(LONGLONG lChannelNo, const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr) = 0;	

	// 响应连接失败
	virtual void OnConnectFail(const sockaddr_in& saLocalAddr, const sockaddr_in& saRemoteAddr, int iErrorCode) = 0;

	// 定时器响应
	virtual int OnTimer(LONGLONG iIDEvent) = 0;

	/* --------------------------------------------------------------------------
	函数说明：响应无心跳至死
	传入参数：
		lChannelNo	被服务端断开的通道号
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	virtual int OnNoHeartbeatDie(LONGLONG lChannelNo) = 0;

	/* --------------------------------------------------------------------------
	函数说明：响应收包消息，本函数是严格按照“先完后执”的原则来执行的，本质上说它就是IOCP里面的工作线程在调用本函数
	传入参数：
		lChannelNo
	传出参数：
		pRecv		消息块，已经是原子包了。注意：要用底层框架的机制归池。
	--------------------------------------------------------------------------*/
	virtual void OnRecv(LONGLONG lChannelNo, CMemBlock*& pRecv) = 0;

	//--- 关键函数 ------------------------------------------

	/* --------------------------------------------------------------------------
	函数说明：初始化，必需在 start 函数之前执行本函数，形成 init() start() ... stop() uinit() 的顺序
	返回值：
		成功则返回 0，失败返回错误码如下：
			10  建立消息池失败
	--------------------------------------------------------------------------*/
	virtual int init();
	
	/* --------------------------------------------------------------------------
	函数说明：释放资源，必需在 stop 函数之后执行本函数，形成 init() start() ... stop() uinit() 的顺序
	返回值：
		成功则返回 0，失败返回错误码如下：
			10  建立消息池失败
	--------------------------------------------------------------------------*/
	virtual int uninit();

	// 列印消息池
	void display_msg_pool();

	// 注册工作模块，包括了数据库工作模块
	int regist_work_module(int iGeneralWorkID, CGeneralWork* pGeneralWork, CCoreServer* pCoreServer);

	// 投递任务消息，将消息投给指定的工作模块
	TASK_MSG_RESULT post_work_msg(int iGeneralWorkID, CMemBlock*& pMsgBlock);

	/* --------------------------------------------------------------------------
	函数说明：注册任务模块，包括了逻辑任务与数据库任务
	传入参数：
		iTaskModuleID	任务模块ID
		pTask			任务模块的指针
		bIsDB			是否数据库
	返回值：
		成功则返回 0，并且pTask 不是空值；
		失败返回错误码，并且 pTask 为空值，错误码如下：
			10  已存在任务模块ID啦，这是唯一的，不得重复
	--------------------------------------------------------------------------*/
	int regist_task_module(int iTaskModuleID, CBasicLogic* pTask, CCoreServer* pCoreServer);

	/* --------------------------------------------------------------------------
	函数说明：投递任务消息，将消息投给指定的任务模块
	传入参数：
		iTaskModuleID	任务模块ID
		bIsFront		TRUE 表示加到双向队列的头部，FALSE 表示加到双向队列的尾部
	传出参数：
		pMsgBlock		消息块
	返回值：
		返回参考 TASK_MSG_RESULT 枚举
	--------------------------------------------------------------------------*/
	TASK_MSG_RESULT post_task_msg(int iTaskModuleID, CMemBlock*& pMsgBlock, BOOL bIsFront=FALSE);

	/* --------------------------------------------------------------------------
	函数说明：设置定时器/修改定时器
	传入参数：
		iIDEvent	定时器ID，当框架不存在此定时器时就是设置定时器，当框架存在此定时器时就是修改此定时器的间隔
		iElapse		响应时间，以 ms 为单位，误差精度为 50 ms
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int set_timer(LONGLONG nIDEvent, int nElapse);

	/* --------------------------------------------------------------------------
	函数说明：结束定时器
	传入参数：
		iIDEvent	定时器ID
	返回值：
		成功则返回 0，失败返回错误码如下：
			10	不存在 iIDEvent
	--------------------------------------------------------------------------*/
	int kill_timer(LONGLONG iIDEvent);

	/* --------------------------------------------------------------------------
	函数说明：写入日志语句
	传入参数：
		bShowInScreen	显示于屏幕上
		iType	类型，参考 LOG_ERR_TYPE 枚举，
				LOG_TYPE_PROMPT = 0,	// 提示
				LOG_TYPE_WARING = 1,	// 警告
				LOG_TYPE_ERR = 2,		// 错误与异常
		pszSentence		日志语句
		iSentenceLen	日志语句的长度
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int write_log(BOOL bShowInScreen, int iType, char* pszSentence, int iSentenceLen);

	/* --------------------------------------------------------------------------
	函数说明：写入日志语句
	传入参数：
		iType	类型，参考 LOG_ERR_TYPE 枚举，
					LOG_TYPE_PROMPT = 0,	// 提示
					LOG_TYPE_WARING = 1,	// 警告
					LOG_TYPE_ERR = 2,		// 错误与异常

		pszSentence		日志语句
		iSentenceLen	日志语句的长度
	返回值：
		成功则返回 0，失败返回错误码如下：
	--------------------------------------------------------------------------*/
	int write_log(int iType, TCHAR* pszSentence, int iSentenceLen);

public:
	//--- 测试专用 ------------------------------------------

private:

	// 发送数据库心跳线程
	static unsigned __stdcall  thread_db_heartbeat(void* pParam);

public:
	CMemBlockPool*	m_pMsgPool;		// 消息池	

private:	

	CCommTcpServer* m_pTcpService;	// TCP 通讯层，无法被 CCoreServer 的子类直接使用，总是说“未定义的变量”
									// 只能通过 CCoreServer 的函数来封装 CCommTcpServer 中的功能

	CCoreTimer*		m_pCoreTimer;	// 内核定时器

	wstring		m_strPath;	// 日志的路径
	CLog*		m_pLogPrompt;	// 提示日志，
	CLog*		m_pLogWaring;	// 警告日志，
	CLog*		m_pLogErr;		// 错误与异常日志

private:
	int				m_iMsgPoolInitCount;	// 消息池的最初元素数量
	int				m_iMsgBlockSize;		// 消息块的长度

private:
	
	typedef hash_map<int, CGeneralWork*> MAP_GENERAL_WORK_TYPE;
	typedef pair <int, CGeneralWork*>	 PAIR_GENERAL_WORK_TYPE;	// 键值对
	MAP_GENERAL_WORK_TYPE	m_mapWork;	// 工作模块群

public:
	enum{ DbEventCount = 2,	};	// 事件的数量

	HANDLE			m_hDbHeartbeatStop;	// 结束发送数据库心跳的线程
	HANDLE			m_hDbThread;		// 数据库心跳的线程
	unsigned int	m_dwDbThreadID;		// 数据库心跳的线程ID

	int		m_iDbHeartbeatTime;	// 发送数据库心跳的时间

public:
	long long m_lCurrentChannel;	// 当前通道号
};

#endif
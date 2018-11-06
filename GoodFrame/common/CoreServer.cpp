
#include "./CoreServer.h"
#include "./PublicHead.h"

#include "process.h"

#include "./CommTcpServer.h"	// 这个文件不能放在 CoreServer.h 中，那样会导致 CCoreServer 的继承类无法享用 CSingleton 这个单件模式的通类
#include "./BasicDB.h"
#include "./GeneralDB.h"

CCoreServer::CCoreServer(void)
{
	m_pTcpService = NULL;	// TCP 通讯层
	m_pCoreTimer = NULL;	// 内核定时器

	m_lCurrentChannel = INVALID_CHANNEL_NO;

	// 消息池
	m_pMsgPool = NULL;
	m_iMsgBlockSize = 2048;		// 消息块的长度
	m_iMsgPoolInitCount = 256;	// 消息池的最初元素数量

	m_pTcpService = new CCommTcpServer;
	assert(m_pTcpService);

	m_pLogPrompt = NULL;	// 提示日志，
	m_pLogWaring = NULL;	// 警告日志，
	m_pLogErr = NULL;		// 错误与异常日志

	m_hDbHeartbeatStop = CreateEvent(NULL, FALSE, FALSE, NULL);	// 
	m_iDbHeartbeatTime = 30*1000;	// 发送数据库心跳的时间

	m_strPath = _T("Server_Log\\");

	
}

CCoreServer::~CCoreServer(void)
{
	// 清理资源

	
}

// 设置消息块的长度
void CCoreServer::set_msg_block_size(int iMsgBlockSize)
{
	m_iMsgBlockSize = iMsgBlockSize;
}

// 设置消息池的最初元素数量
void CCoreServer::set_msg_pool_init_count(int iMsgPoolInitCount)
{
	m_iMsgPoolInitCount = iMsgPoolInitCount;	
}

// 设置监听地址
void CCoreServer::set_listen_addr(const char* szListenAddr)
{
	assert(m_pTcpService);
	m_pTcpService->set_listen_addr(szListenAddr);
}

// 设置监听端口
void CCoreServer::set_listen_port(unsigned int nPort)
{
	assert(m_pTcpService);
	m_pTcpService->set_listen_port(nPort);
}

// 从外部传入消息池
int CCoreServer::set_msg_pool(CMemBlockPool* pMsgPool)
{
	assert(m_pTcpService);
	return m_pTcpService->set_msg_pool(pMsgPool);
}

// 设置对端服务池的最初元素数量
void CCoreServer::set_service_handle_pool_init_count(int iServerHandlePoolInitCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_service_handle_pool_init_count(iServerHandlePoolInitCount);
}

// 设置连接结果池的最初元素数量
void CCoreServer::set_accept_result_pool_init_count(int iAcceptResultPoolInitCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_accept_result_pool_init_count(iAcceptResultPoolInitCount);
}

// 设置发送结果池的最初元素数量
void CCoreServer::set_send_result_pool_init_count(int iSendResultPoolInitCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_send_result_pool_init_count(iSendResultPoolInitCount);
}

// 设置收缩各种池的时间，iShrinkPoolsTime 以 ms 为单位
void CCoreServer::set_shrink_pools_time(LONGLONG iShrinkPoolsTime)
{
	assert(m_pTcpService);
	m_pTcpService->set_shrink_pools_time(iShrinkPoolsTime);
}

// 设置心跳检查的时间，以 PULSE_TIME 脉冲为基本单位，即 N 个 PULSE_TIME 检查一次
void CCoreServer::set_heartbeat_check_time(LONGLONG iHeartbeatCheckTime)
{
	assert(m_pTcpService);
	m_pTcpService->set_heartbeat_check_time(iHeartbeatCheckTime);
}

// 设置无心跳至死的时间，以 ms 为单位，即 N ms 之内客户端没有任何消息发过来就认为该客户端死掉了
void CCoreServer::set_no_heartbeat_die_time(int iNoHeartbeatDieTime)
{
	assert(m_pTcpService);
	m_pTcpService->set_no_heartbeat_die_time(iNoHeartbeatDieTime);
}

// 设置数据库心跳的时间
void CCoreServer::set_db_heartbeat_time(int iDbHeartbeatTime)
{
	m_iDbHeartbeatTime = iDbHeartbeatTime;
}

// 设置 IOCP 工作线程的数量
void CCoreServer::set_work_thread_count(int iCount)
{
	assert(m_pTcpService);
	m_pTcpService->set_work_thread_count(iCount)  ;
}

// 设置日志的路径
int CCoreServer::set_log_path(TCHAR* pszPathName)
{
	if(!pszPathName)
		return 10;

	m_strPath = pszPathName;

	return 0;
}

// 发送
int CCoreServer::send_data(LONGLONG lChannelNo, CMemBlock*& pSendBlock)
{
	assert(m_pTcpService);
	return m_pTcpService->send_data(lChannelNo, pSendBlock)  ; 
}

// 出池并发送，效率低，慎用。出池并发送，此函数效率低，慎用。通常用于向客户端一次性大批量发送数据（例如发送用户列表）的场合。
int CCoreServer::retrieve_send_data(LONGLONG lChannelNo, int iMainCode, int iSubCode, BYTE* pData, int iDataLen, char* pszTextMark, BOOL bIsWait)
{
	assert(m_pTcpService);
	return m_pTcpService->retrieve_send_data(lChannelNo, iMainCode, iSubCode, pData, iDataLen, pszTextMark, bIsWait)  ; 
}

// TCP广播，即发送数据到所有的有效对端
int CCoreServer::tcp_broadcase(int iMainCode, int iSubCode, BYTE* pData, int iDataLen)
{
	assert(m_pTcpService);
	return m_pTcpService->tcp_broadcase(iMainCode, iSubCode, pData, iDataLen)  ;
}

// TCP广播，即发送数据到所有的有效对端
int CCoreServer::tcp_broadcase(CMemBlock*& pSendBlock)
{
	assert(m_pTcpService);
	return m_pTcpService->tcp_broadcase(pSendBlock)  ;
}

// 检查所有对端的心跳
int CCoreServer::check_all_peer_heartbeat()
{
	assert(m_pTcpService);
	return m_pTcpService->check_all_peer_heartbeat()  ;
}

#if ALLOW_STRONG_CLOSE_PEER
	// 关闭指定的对端，用 power_close_peer 代替
	int CCoreServer::close_peer(LONGLONG lChannelNo)
	{
		assert(m_pTcpService);
		return m_pTcpService->close_peer(lChannelNo)  ;
	}
#endif

// 主动关闭指定的对端，客户端不会再执行断线重连
int CCoreServer::power_close_peer(LONGLONG lChannelNo)
{
	assert(m_pTcpService);
	return m_pTcpService->power_close_peer(lChannelNo)  ;
}

// 关闭所有的对端
void CCoreServer::close_all_peer()
{
	assert(m_pTcpService);
	m_pTcpService->close_all_peer()  ;	
}

// 统计接收的速率，是个反复的开关
void CCoreServer::statistic_recv_rate()
{
	assert(m_pTcpService);
	m_pTcpService->statistic_recv_rate()  ;
}

// 初始化，必需在 start 函数之前执行本函数，形成 init() start() ... stop() uinit() 的顺序
int CCoreServer::init()
{
	int iResult = 0;

	// 消息池
	{
		m_pMsgPool = new CMemBlockPool(m_iMsgBlockSize, m_iMsgPoolInitCount, 20*m_iMsgPoolInitCount);		
		if(m_pMsgPool)
			m_pMsgPool->init();
		else
			return 10;	// 建立消息池失败
	}

	// TCP 通讯层
	{
		assert(m_pTcpService);

		// 设置宿主的指针
		m_pTcpService->set_core_server(this);

		// 从外部传入消息池
		m_pTcpService->set_msg_pool(m_pMsgPool);

		iResult = m_pTcpService->init();
		assert(0==iResult);

		iResult = m_pTcpService->start();
		assert(0==iResult);
	}

	// 内核定时器
	{
		m_pCoreTimer = new CCoreTimer;
		assert(m_pCoreTimer);

		// 设置宿主的指针
		m_pCoreTimer->set_core_server(this);

		m_pCoreTimer->set_msg_pool(m_pMsgPool);			
		
		m_pCoreTimer->start_timer();
	}

	// 提示日志
	{
		m_pLogPrompt = NULL;
		m_pLogPrompt = new CLog(_T("Prompt_"));
		assert(m_pLogPrompt);

		m_pLogPrompt->set_path(m_strPath);

		iResult = m_pLogPrompt->start_log();	// 启动任务模块，此句不能省略
		assert(0==iResult);
	}

	// 警告日志
	{
		m_pLogWaring = NULL;
		m_pLogWaring = new CLog(_T("Waring_"));
		assert(m_pLogWaring);

		m_pLogWaring->set_path(m_strPath);

		iResult = m_pLogWaring->start_log();	// 启动任务模块，此句不能省略
		assert(0==iResult);
	}

	// 错误与异常日志
	{
		m_pLogErr = NULL;
		m_pLogErr = new CLog(_T("ErrCatch_"));
		assert(m_pLogErr);

		m_pLogErr->set_path(m_strPath);

		iResult = m_pLogErr->start_log();	// 启动任务模块，此句不能省略
		assert(0==iResult);
	}

	// 建立单线程
	m_hDbThread = (HANDLE)_beginthreadex( NULL, 0, &thread_db_heartbeat, (void*)this, 0, &m_dwDbThreadID );

	return 0;
}

// 停止
int CCoreServer::stop()
{
	int iResult = 0;

	iResult = m_pTcpService->stop();
	assert(0==iResult);

	// 释放通讯层
	delete m_pTcpService;
	m_pTcpService = NULL;

	// 内核定时器
	iResult = m_pCoreTimer->stop_timer();
	assert(0==iResult);
	delete m_pCoreTimer;

	iResult = m_pLogPrompt->stop_log();
	assert(0==iResult);
	delete 	m_pLogPrompt;

	iResult = m_pLogWaring->stop_log();
	assert(0==iResult);
	delete 	m_pLogWaring;

	iResult = m_pLogErr->stop_log();
	assert(0==iResult);
	delete 	m_pLogErr;

	SetEvent(m_hDbHeartbeatStop);
	DWORD dwResult = WaitForSingleObject(m_hDbThread, 60*1000);	// 等待线程彻底的结束

	return iResult;
}

// 释放资源，必需在 stop 函数之后执行本函数，形成 init() start() ... stop() uinit() 的顺序
int CCoreServer::uninit()
{
	// 释放消息池
	if(m_pMsgPool)
	{
		m_pMsgPool->uninit();
		delete m_pMsgPool;
	}

	return 0;
}

// 发送数据库心跳线程
unsigned __stdcall  CCoreServer::thread_db_heartbeat(void* pParam) 	
{
	CCoreServer* pThis = (CCoreServer*)pParam;	// 当前线程的ID

	DWORD hThreadID = ::GetCurrentThreadId();	// 获得当前线程ID

	while(true)
	{
		DWORD dwResult = WaitForSingleObject(pThis->m_hDbHeartbeatStop, pThis->m_iDbHeartbeatTime);
		switch(dwResult)
		{
		case WAIT_TIMEOUT:	// 将超时作为发送数据库心跳的时间间隔
			{
				MAP_GENERAL_WORK_TYPE::iterator iter = pThis->m_mapWork.begin();

				for( ; iter!=pThis->m_mapWork.end(); iter++)	// 遍历所有的逻辑任务与数据库任务
				{
					CGeneralWork* pWork = (CGeneralWork*)(*iter).second;

					if(pWork->m_bIsDB)	// 数据库任务
					{
						CGeneralDB* pDb = (CGeneralDB*)pWork;

						// 向数据库发心跳包，因为数据库在长时间得不到访问就会自动断线
						pDb->db_heartbeat();
					}
				}
				
				break;
			}
		case WAIT_OBJECT_0:	// 收到结束的消息
			{
				return 0;
			}
		}
	}

	return 0;
}

// 列印消息池
void CCoreServer::display_msg_pool()
{
	printf(" MsgPool，       出池数=%9d 归池数=%9d 池内当前元素=%9d \n",
		m_pMsgPool->get_retrieve_count(),
		m_pMsgPool->get_recycle_count(),
		m_pMsgPool->get_current_element_count()
		);
}

// 显示所有的池信息
void CCoreServer::display_all_pool()
{
	m_pTcpService->display_all_pool();
}

// 注册工作模块，包括了数据库工作模块
int CCoreServer::regist_work_module(int iGeneralWorkID, CGeneralWork* pGeneralWork, CCoreServer* pCoreServer)
{
	assert(pCoreServer);
	assert(pGeneralWork);

	MAP_GENERAL_WORK_TYPE::iterator iter;

	iter = m_mapWork.find(iGeneralWorkID);

	if( iter != m_mapWork.end())	// 找到了
	{
		return ERR_CS_exist_work_module;	// 已存在任务模块ID啦，这是唯一的，不得重复
	}

	if(pGeneralWork)
	{
		pGeneralWork->set_core_server(pCoreServer);
		m_mapWork.insert(PAIR_GENERAL_WORK_TYPE(iGeneralWorkID, pGeneralWork));
	}

	return 0;
}

// 投递任务消息，将消息投给指定的工作模块
TASK_MSG_RESULT CCoreServer::post_work_msg(int iGeneralWorkID, CMemBlock*& pMsgBlock)
{
	// 因为在 regist_task_module 之后，不存在增加或移除任务模块的情况，所以不用加锁

	TASK_MSG_RESULT stRes = TMR_ERROR;

	if (NULL==pMsgBlock)
	{
		return stRes;
	}

	MAP_GENERAL_WORK_TYPE::iterator iter;

	iter = m_mapWork.find(iGeneralWorkID);

	if( iter != m_mapWork.end())	// 找到了
	{
		CGeneralWork* p = (CGeneralWork*)(*iter).second;
		if(0==p->handle_msg(pMsgBlock))
		{
			stRes = TMR_CONTINUE_PUT;
		}
		else
		{
			m_pMsgPool->recycle(pMsgBlock);
		}
	}

	return stRes;
}

// 设置定时器/修改定时器，当框架不存在此定时器时就是设置定时器，当框架存在此定时器时就是修改此定时器的间隔
int CCoreServer::set_timer(LONGLONG iIDEvent, int iElapse)
{
	assert(m_pCoreTimer);
	if(!m_pCoreTimer)
		return 10;

	m_pCoreTimer->set_timer(iIDEvent, iElapse);

	return 0;
}

int CCoreServer::kill_timer(LONGLONG iIDEvent)
{
	assert(m_pCoreTimer);
	if(!m_pCoreTimer)
		return 10;

	m_pCoreTimer->kill_timer(iIDEvent);

	return 0;
}

// 写入日志语句
int CCoreServer::write_log(BOOL bShowInScreen, int iType, char* pszSentence, int iSentenceLen)
{
	int iRes = 0;
	wstring wstrRes;

	// 多字节字串转成宽字节字串
	iRes = COften::EasyMultiByteToWideChar(pszSentence , iSentenceLen, wstrRes);
	if(0==iRes)
	{
		return write_log(iType, (TCHAR*)wstrRes.c_str(), (int)wstrRes.length());
	}

	return 0;
}

// 写入日志语句
int CCoreServer::write_log(int iType, TCHAR* pszSentence, int iSentenceLen)
{
	if(!pszSentence)
		return 10;

	if(0==iSentenceLen)
		return 20;

	if(0==iType)	// 提示
	{
		if(!m_pLogPrompt)
			return 60;

		return m_pLogPrompt->write_log(pszSentence, iSentenceLen);
	}
	else if(1==iType)	// 警告
	{
		if(!m_pLogWaring)
			return 70;

		return m_pLogWaring->write_log(pszSentence, iSentenceLen);
	}
	else if(2==iType)	// 错误与异常
	{
		if(!m_pLogErr)
			return 80;

		return m_pLogErr->write_log(pszSentence, iSentenceLen);
	}

	return  0;
}

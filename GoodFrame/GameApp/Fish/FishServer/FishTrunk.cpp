#include "FishTrunk.h"
#include "PublicHead.h"

#include "./EndlessLoopGuard.h"	// 死循环守护
#include "./TimeInterval.h"

// 加载内核服务端的 Lib
#if _DEBUG	
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreServerShell_d.lib") 
#else
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreServerShell.lib") 
#endif

// 加载游戏服务骨架 Lib
#if _DEBUG	
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/ServerSkeleton_d.lib") 
#else
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/ServerSkeleton.lib") 
#endif

CFishTrunk::CFishTrunk(void)
{
	m_bIsStart = false;
	m_pConnectCenter = NULL;
	// 建立
	CEndlessLoop::create();
}

CFishTrunk::~CFishTrunk(void)
{
	// 销毁连接中心服务器
	if (NULL!=m_pConnectCenter)
	{
		delete m_pConnectCenter;
	}
	m_pConnectCenter = NULL;
}

/* --------------------------------------------------------------------------
函数说明：孵化
传入参数：
传出参数：
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
int CFishTrunk::spawn(const char*roomConfig)
{
	//--- 服务端设置 -------------------------------------------------
	int iRes = 0;	
	CFishTrunk::create();
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
	assert(pTrunk);
	if(!pTrunk)
		return 10;

	{	// 客户端(连接房管服务器 RMS

		pTrunk->set_room_config(roomConfig);	// 设置房间配置文件的参数
		ROOM_CONFIG stRoomConfig = pTrunk->get_room_config();	// 获得房间配置

		CLIENT_TO_RMS_PARAM rms;	// 连接房管服务器 RMS（RoomMgrServer ）的参数
		_snprintf(rms.szIP, sizeof(rms.szIP)-1, "%s", stRoomConfig.szRoomMgrIp);	// 房间服的IP
		rms.iPort = stRoomConfig.RoomMgrPort;	// 房间服的端口

		iRes = pTrunk->create_client_to_rms(rms);	// 连接房管服务器 RMS（RoomMgrServer ）
		assert(0==iRes);
		if(0!=iRes)
		{
			CFishTrunk::destroy();
			return 50;
		}
	}

	return 0;
}

// 房管服的信息获取完毕，并且启动房间服务
int CFishTrunk::OnRoomMgrServerOk(SERVER_ROOM_INFO serverRoomInfo, ROOM_CONFIG roomConfig)
{
	int iRes = 0;

	// 中心服务器连接
	if(NULL==m_pConnectCenter)
	{
		m_pConnectCenter = new CConnectCenterServer();
		// 设置配置文件
		m_pConnectCenter->m_Config = serverRoomInfo;

		// 设置消息块的长度
		m_pConnectCenter->set_msg_block_size(2048);

		// 设置发送心跳包的时间
		m_pConnectCenter->set_send_heartbeat_time(30*1000);

		// 设置收缩各种池的时间
		m_pConnectCenter->set_shrink_pools_time(3*60*1000);

		// 设置断线重连
		m_pConnectCenter->set_reconnect(true);

		// 设置断线重连的间隔时间，单位ms
		m_pConnectCenter->set_reconnect_interval_time(2000);

		// 设置房间的日志的路径
		m_pConnectCenter->set_log_path(_T("LoginServerLog\\"));

		// 设置消息池的最初元素数量
		m_pConnectCenter->set_msg_pool_init_count(64);

		// 设置发送结果池的最初元素数量
		m_pConnectCenter->set_send_result_pool_init_count(16);	// 这个值可以小一些，因为一个客户端不可能发那么密集的

		// 连接IP
		m_pConnectCenter->set_connect_addr(roomConfig.szCenterIp);

		// 连接端口
		m_pConnectCenter->set_connect_port(roomConfig.iCenterPort);

		if(m_pConnectCenter->init())
		{
			COften::OutputError("连接中心服初始化失败");
			return 0;
		}
		if(m_pConnectCenter->start())
		{
			COften::OutputError("连接中心服启动失败");
			return 0;
		}
		Sleep(2000);
	}
	// ===========================================================================
	if (!m_bIsStart)
	{
		m_bIsStart = true;
		CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
		{

			// 设置对端服务池的最初元素数量
			pTrunk->set_service_handle_pool_init_count(SERVER_HANDLE_POOL_INIT_COUNT);

			// 设置连接结果池的最初元素数量
			pTrunk->set_accept_result_pool_init_count(SERVER_HANDLE_POOL_INIT_COUNT);

			// 设置发送结果池的最初元素数量
			pTrunk->set_send_result_pool_init_count(SERVER_HANDLE_POOL_INIT_COUNT);

			// 设置消息块的长度
			pTrunk->set_msg_block_size(2048);

			// 设置消息池的最初元素数量
			pTrunk->set_msg_pool_init_count(4096);

			pTrunk->set_listen_addr("0.0.0.0");	// 监听所有的IP，包括电信、联通、网通等
			pTrunk->set_listen_port(serverRoomInfo.iRoomPort);

			// 设置日志的路径，不用此句时会有框架的默认值 "CORE_LOG\\"
			pTrunk->set_log_path(_T("FishServerLog\\"));

			// 设置游戏开始的类型，iType 参考 GAME_BEGIN_TYPE_AUTO 、 GAME_BEGIN_TYPE_ONLY_ONE 、 GAME_BEGIN_TYPE_ALL_SIT 等
			//pTrunk->game_begin_type(GAME_BEGIN_TYPE_ONLY_ONE);
			pTrunk->game_begin_type(serverRoomInfo.iBeginMode);	// 开始模式(0:启动桌子就开始;1:一个人进桌就开始;2:坐满就开始;3:固定最少几个人准备就开始)	// add by cxf
		}

		{	// 初始化，必需在 start 函数之前执行本函数
			iRes = pTrunk->init();
			assert(0==iRes);
		}

		{	// 本段的这几句必需放在 pTrunk->start() 之前

			// 建立房间实例
			pTrunk->create_room_mgr(serverRoomInfo);	

			// 建立桌子群实例
			pTrunk->create_table();

			// 建立数据库实例
			pTrunk->create_db();		
		}

		{	// 开始，必需在 init  函数之后执行本函数
			iRes = pTrunk->start();
			assert(0==iRes);
		}

		{	// 必需在 pTrunk->start() 之后才能执行

			// 建立游戏骨架使用的定时器
			pTrunk->create_game_skeleton_timer();
		}
	}
	COften::OutputInfo("服务器启动完毕");

	return iRes;
}

/* --------------------------------------------------------------------------
函数说明：湮灭
传入参数：
传出参数：
返回值：
    成功则返回 0，失败返回错误码如下：
--------------------------------------------------------------------------*/
void CFishTrunk::annihilate()
{
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();

	// 销毁数据库实例
	pTrunk->destroy_db();	

	// 销毁桌子群实例
	pTrunk->destroy_table();

	// 销毁房间实例
	pTrunk->destroy_room_mgr();	

	CFishTrunk::destroy();
}

// 建立房间实例
IRoomMgr* CFishTrunk::create_room_mgr(SERVER_ROOM_INFO serverRoomInfo)
{
	m_pRoomMgr = new CRoomMgr;

	assert(m_pRoomMgr);
	if(m_pRoomMgr)
	{
		m_pRoomMgr->set_server_room_info(serverRoomInfo);	// 房间信息
		return m_pRoomMgr;
	}

	return NULL;
}

// 销毁房间实例
void CFishTrunk::destroy_room_mgr()
{
	delete (CRoomMgr*)m_pRoomMgr;
}

// 建立桌子群实例
int CFishTrunk::create_table()
{
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
	IRoomMgr* pRoomMgr = m_pRoomMgr;

	// new 出所有的桌子
	for(int i=0; i<pRoomMgr->get_server_room_info().iTables; i++)	
	{
		//CTimeInterval timeInterval(true, __FUNCTION__);	// 打印时间间隔

		IBaseTable* pTable = new CFishTable;	// 这一句非常非常的慢，每一个 new 都花了2秒钟??? 若60张桌子就要花 120秒???
												// 是不是在重复的读配置文件，若是的话，配置文件只需要读一次就好，不用每个 new 都去读一次配置文件
	//	#if 1	// 这一段不慢的，很快的
			if(pTable)
			{
				TABLE_INFO tableInfo;
				tableInfo.iTableNo = i;
				tableInfo.iSeatNum = pRoomMgr->get_server_room_info().iSeatNum;
			
				pTable->init(m_pRoomMgr, tableInfo, this->game_begin_type());

				pRoomMgr->m_vecTable.push_back(pTable);
			}
	//	#endif
	}

	return 0;
}

// 建立游戏骨架使用的定时器
int CFishTrunk::create_game_skeleton_timer()
{
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
	IRoomMgr* pRoomMgr = m_pRoomMgr;

	vector<IBaseTable*>* pVecTable = &(pRoomMgr->m_vecTable);
	vector<IBaseTable*>::iterator it = pVecTable->begin();

	for( ; it != pVecTable->end(); it++)
	{
		IBaseTable* pTable = *it;

		if(pTable)
		{
			pTable->create_game_skeleton_timer();
		}
	}

	return 0;
}

// 销毁桌子群实例
void CFishTrunk::destroy_table()
{
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
	IRoomMgr* pRoomMgr = m_pRoomMgr;

	vector<IBaseTable*>* pVecTable = &(pRoomMgr->m_vecTable);
	vector<IBaseTable*>::iterator it = pVecTable->begin();

	for( ; it != pVecTable->end(); it++)
	{
		IBaseTable* pTable = *it;

		if(pTable)
		{
			delete (CFishTable*)pTable;
		}

	}

	pVecTable->clear();
}

// 建立数据库实例
IDbAnyGame*	CFishTrunk::create_db()
{
	m_pDbAnyGame = new CDb_Fish;
	return m_pDbAnyGame;
}

// 销毁数据库实例
void CFishTrunk::destroy_db()
{
	delete (CDb_Fish*)m_pDbAnyGame;
}

#define TIMER_TYPE_TEST 1	// 0表示房间定时器，1表示桌子定时器

// 设置定时器
void CFishTrunk::test_05()
{
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
	IRoomMgr*	pRoomMgr = pTrunk->m_pRoomMgr;

	if(0==TIMER_TYPE_TEST)
	{
		pRoomMgr->set_room_timer(TIMER_ROOM_EVENT_ID, 2000);
	}
	else if(1==TIMER_TYPE_TEST)
	{
		pRoomMgr->set_table_timer(TIMER_TABLE_NO, TIMER_TABLE_EVENT_ID, 2000);
	}
}

// 杀掉定时器
void CFishTrunk::test_06()
{
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
	IRoomMgr*	pRoomMgr = pTrunk->m_pRoomMgr;

	if(0==TIMER_TYPE_TEST)
	{
		pRoomMgr->kill_room_timer(TIMER_ROOM_EVENT_ID);
	}
	else if(1==TIMER_TYPE_TEST)
	{
		pRoomMgr->kill_table_timer(TIMER_TABLE_NO, TIMER_TABLE_EVENT_ID);
	}
}

void CFishTrunk::test_07()
{
	CFishTrunk* pTrunk = CFishTrunk::get_singleton_ptr();
	IRoomMgr*	pRoomMgr = pTrunk->m_pRoomMgr;
}

// 列印所有的守护
int CFishTrunk::display_all_guard()
{
	bool bDiaplay = true;	// 在屏幕上显示

	vector<ENDLESS_LOOP_INFO> vecEndlessLoopInfo;
	CEndlessLoop::get_singleton_ptr()->display_all_guard(true, vecEndlessLoopInfo);

	return 0;
}
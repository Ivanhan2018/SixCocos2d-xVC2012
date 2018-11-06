#include "TrunkServer.h"
#include "PublicHead.h"

// �����ں˷���˵� Lib
#if _DEBUG	
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreServerShell_d.lib") 
#else
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/CoreServerShell.lib") 
#endif

// ������Ϸ����Ǽ� Lib
#if _DEBUG	
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/ServerSkeleton_d.lib") 
#else
	#pragma comment(lib, "../../../PUBLIC_LIB/x64/ServerSkeleton.lib") 
#endif

CTrunkServer::CTrunkServer(void)
{
	m_bIsStart = false;
	m_pConnectCenter = NULL;
}

CTrunkServer::~CTrunkServer(void)
{
	// �����������ķ�����
	if (NULL!=m_pConnectCenter)
	{
		delete m_pConnectCenter;
	}
	m_pConnectCenter = NULL;
}

/* --------------------------------------------------------------------------
����˵��������
���������
����������
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
int CTrunkServer::spawn(const char*roomConfig)
{
	//--- ��������� -------------------------------------------------
	int iRes = 0;	
	CTrunkServer::create();
	CTrunkServer* pTrunk = CTrunkServer::get_singleton_ptr();

	// ���÷��������ļ��Ĳ���
	if(roomConfig==NULL||strlen(roomConfig)==0)
		pTrunk->set_room_config("Config/RoomConfig_8000.ini");
	else
		pTrunk->set_room_config(roomConfig);

	ROOM_CONFIG stRoomConfig = pTrunk->get_room_config();	// ��÷�������

	CLIENT_TO_RMS_PARAM rms;	// ���ӷ��ܷ����� RMS��RoomMgrServer ���Ĳ���
	_snprintf(rms.szIP, sizeof(rms.szIP)-1, "%s", stRoomConfig.szRoomMgrIp);	// �������IP
	rms.iPort = stRoomConfig.RoomMgrPort;	// ������Ķ˿�

	iRes = pTrunk->create_client_to_rms(rms);	// ���ӷ��ܷ����� RMS��RoomMgrServer ��
	assert(0==iRes);
	if(0!=iRes)
	{
		CTrunkServer::destroy();
		return 50;
	}

	return 0;
}

// ���ܷ�����Ϣ��ȡ��ϣ����������������
int CTrunkServer::OnRoomMgrServerOk(SERVER_ROOM_INFO serverRoomInfo, ROOM_CONFIG roomConfig)
{
	int iRes = 0;

	// ���ķ���������
	if(NULL==m_pConnectCenter)
	{
		m_pConnectCenter = new CConnectCenterServer();
		// ���������ļ�
		m_pConnectCenter->m_Config = serverRoomInfo;

		// ������Ϣ��ĳ���
		m_pConnectCenter->set_msg_block_size(2048);

		// ���÷�����������ʱ��
		m_pConnectCenter->set_send_heartbeat_time(30*1000);

		// �����������ֳص�ʱ��
		m_pConnectCenter->set_shrink_pools_time(3*60*1000);

		// ���ö�������
		m_pConnectCenter->set_reconnect(true);

		// ���ö��������ļ��ʱ�䣬��λms
		m_pConnectCenter->set_reconnect_interval_time(2000);

		// ���÷������־��·��
		m_pConnectCenter->set_log_path(_T("SanGongConCenterLog\\"));

		// ������Ϣ�ص����Ԫ������
		m_pConnectCenter->set_msg_pool_init_count(64);

		// ���÷��ͽ���ص����Ԫ������
		m_pConnectCenter->set_send_result_pool_init_count(16);	// ���ֵ����СһЩ����Ϊһ���ͻ��˲����ܷ���ô�ܼ���

		// ����IP
		m_pConnectCenter->set_connect_addr(roomConfig.szCenterIp);

		// ���Ӷ˿�
		m_pConnectCenter->set_connect_port(roomConfig.iCenterPort);

		if(m_pConnectCenter->init())
		{
			COften::OutputError("�������ķ���ʼ��ʧ��");
			return 0;
		}
		if(m_pConnectCenter->start())
		{
			COften::OutputError("�������ķ�����ʧ��");
			return 0;
		}
		Sleep(2000);
	}
	// ===========================================================================

	if (!m_bIsStart)
	{
		m_bIsStart = true;
		CTrunkServer* pTrunk = CTrunkServer::get_singleton_ptr();

		// ���öԶ˷���ص����Ԫ������
		pTrunk->set_service_handle_pool_init_count(SERVER_HANDLE_POOL_INIT_COUNT);

		// �������ӽ���ص����Ԫ������
		pTrunk->set_accept_result_pool_init_count(SERVER_HANDLE_POOL_INIT_COUNT);

		// ���÷��ͽ���ص����Ԫ������
		pTrunk->set_send_result_pool_init_count(SERVER_HANDLE_POOL_INIT_COUNT);

		// ������Ϣ��ĳ���
		pTrunk->set_msg_block_size(2048);

		// ������Ϣ�ص����Ԫ������
		pTrunk->set_msg_pool_init_count(4096);

		pTrunk->set_listen_addr("0.0.0.0");	// �������е�IP���������š���ͨ����ͨ��
		pTrunk->set_listen_port(serverRoomInfo.iRoomPort);

		// ������־��·�������ô˾�ʱ���п�ܵ�Ĭ��ֵ "CORE_LOG\\"
		pTrunk->set_log_path(_T("SangongGameServerLog\\"));

		// ������Ϸ��ʼ�����ͣ�iType �ο� GAME_BEGIN_TYPE_AUTO �� GAME_BEGIN_TYPE_ONLY_ONE �� GAME_BEGIN_TYPE_ALL_SIT ��
		//pTrunk->game_begin_type(GAME_BEGIN_TYPE_ONLY_ONE);
		pTrunk->game_begin_type(serverRoomInfo.iBeginMode);	// ��ʼģʽ(0:�������ӾͿ�ʼ;1:һ���˽����Ϳ�ʼ;2:�����Ϳ�ʼ;3:�̶����ټ�����׼���Ϳ�ʼ)	// add by cxf
		// ��ʼ���������� start ����֮ǰִ�б�����
		iRes = pTrunk->init();
		assert(0==iRes);

		// ��������ʵ��
		pTrunk->create_room_mgr(serverRoomInfo);	

		// ��������Ⱥʵ��
		pTrunk->create_table();

		// �������ݿ�ʵ��
		pTrunk->create_db();		

		iRes = pTrunk->start();
		assert(0==iRes);

		// ������Ϸ�Ǽ�ʹ�õĶ�ʱ��
		pTrunk->create_game_skeleton_timer();

	}
	
	COften::OutputInfo("��������������");

	return iRes;
}

/* --------------------------------------------------------------------------
����˵��������
���������
����������
����ֵ��
    �ɹ��򷵻� 0��ʧ�ܷ��ش��������£�
--------------------------------------------------------------------------*/
void CTrunkServer::annihilate()
{
	CTrunkServer* pTrunk = CTrunkServer::get_singleton_ptr();

	// �������ݿ�ʵ��
	pTrunk->destroy_db();	

	// ��������Ⱥʵ��
	pTrunk->destroy_table();

	// ���ٷ���ʵ��
	pTrunk->destroy_room_mgr();	

	CTrunkServer::destroy();
}

// ��������ʵ��
IRoomMgr* CTrunkServer::create_room_mgr(SERVER_ROOM_INFO serverRoomInfo)
{
	m_pRoomMgr = new CGameRoom;

	assert(m_pRoomMgr);
	if(m_pRoomMgr)
	{
		m_pRoomMgr->set_server_room_info(serverRoomInfo);	// ������Ϣ
		return m_pRoomMgr;
	}

	return NULL;
}

// ���ٷ���ʵ��
void CTrunkServer::destroy_room_mgr()
{
	delete (CGameRoom*)m_pRoomMgr;
}

// ��������Ⱥʵ��
int CTrunkServer::create_table()
{
	CTrunkServer* pTrunk = CTrunkServer::get_singleton_ptr();
	IRoomMgr* pRoomMgr = m_pRoomMgr;

	// new �����е�����
	for(int i=0; i<pRoomMgr->get_server_room_info().iTables; i++)	
	{
		IBaseTable* pTable = new CGameTable;
		if(pTable)
		{
			TABLE_INFO tableInfo;
			tableInfo.iTableNo = i;
			tableInfo.iSeatNum = pRoomMgr->get_server_room_info().iSeatNum;
			pTable->init(m_pRoomMgr, tableInfo, this->game_begin_type());
			pRoomMgr->m_vecTable.push_back(pTable);
		}
	}

	return 0;
}

// ������Ϸ�Ǽ�ʹ�õĶ�ʱ��
int CTrunkServer::create_game_skeleton_timer()
{
	CTrunkServer* pTrunk = CTrunkServer::get_singleton_ptr();
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

// ��������Ⱥʵ��
void CTrunkServer::destroy_table()
{
	CTrunkServer* pTrunk = CTrunkServer::get_singleton_ptr();
	IRoomMgr* pRoomMgr = m_pRoomMgr;

	vector<IBaseTable*>* pVecTable = &(pRoomMgr->m_vecTable);
	vector<IBaseTable*>::iterator it = pVecTable->begin();

	for( ; it != pVecTable->end(); it++)
	{
		IBaseTable* pTable = *it;
		if(pTable)
		{
			delete (CGameTable*)pTable;
		}

	}

	pVecTable->clear();
}

// �������ݿ�ʵ��
IDbAnyGame*	CTrunkServer::create_db()
{
	m_pDbAnyGame = new CDBModule;
	return m_pDbAnyGame;
}

// �������ݿ�ʵ��
void CTrunkServer::destroy_db()
{
	delete (CDBModule*)m_pDbAnyGame;
}


#ifndef FISH_TRUCK_H
#define FISH_TRUCK_H

#include "./GameServerSkeleton.h"
#include "./RoomMgr.h"
#include "./Db_Fish.h"
#include "./FishTable.h"
#include "ConnectCenterServer.h"

class CFishTrunk : public CGameServerSkeleton
				 , public CSingleton<CFishTrunk>
{
public:
	enum{
		TIMER_ROOM_EVENT_ID = 5,	// ���䶨ʱ�����¼�ID

		TIMER_TABLE_NO = 1,			// ����
		TIMER_TABLE_EVENT_ID = 8,	// ���Ӷ�ʱ�����¼�ID
	};
	enum{	SERVER_HANDLE_POOL_INIT_COUNT = 2048, // �Զ˷���ص����Ԫ������	
	};
public:
	CFishTrunk(void);
	~CFishTrunk(void);

public:

	//--- �ؼ����� ----------------------------------

	// ����
	static int spawn(const char*roomConfig=NULL);

	// ����
	static void annihilate();

public:

	//--- �Ӹ���̳еĴ��麯�� ----------------------------------

	// ��������ʵ��
	virtual IRoomMgr* create_room_mgr(SERVER_ROOM_INFO serverRoomInfo);

	// ���ٷ���ʵ��
	virtual void destroy_room_mgr();

	// ��������Ⱥʵ��
	virtual int create_table();

	// ��������Ⱥʵ��
	virtual void destroy_table();

	// ������Ϸ�Ǽ�ʹ�õĶ�ʱ��
	virtual int create_game_skeleton_timer();

	// �������ݿ�ʵ��
	virtual IDbAnyGame*	create_db();

	// �������ݿ�ʵ��
	virtual void destroy_db();

	// ���ܷ�����Ϣ��ȡ��ϣ����������������
	virtual int OnRoomMgrServerOk(SERVER_ROOM_INFO serverRoomInfo, ROOM_CONFIG roomConfig);

public:

	// ��ӡ���е��ػ�
	int display_all_guard();

	//--- ���Բ��� ----------------------------------

	// ���ö�ʱ��
	void test_05();

	// ɱ����ʱ��
	void test_06();

	void test_07();

public:
	BOOL		m_bIsStart;

	CConnectCenterServer* m_pConnectCenter;

};

#endif
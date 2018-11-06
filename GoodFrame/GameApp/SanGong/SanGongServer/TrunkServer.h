
#ifndef TRUCK_SERVER_H
#define TRUCK_SERVER_H

#include "GameServerSkeleton.h"
#include "GameRoom.h"
#include "DBModule.h"
#include "GameTable.h"
#include "ConnectCenterServer.h"

class CTrunkServer : public CGameServerSkeleton
				 , public CSingleton<CTrunkServer>
{
	enum{	SERVER_HANDLE_POOL_INIT_COUNT = 2048, // �Զ˷���ص����Ԫ������	
		};
public:
	CTrunkServer(void);
	~CTrunkServer(void);

public:

	//--- �ؼ����� ----------------------------------

	// ����
	static int spawn(const char*roomConfig);

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
	BOOL		m_bIsStart;

	CConnectCenterServer* m_pConnectCenter;
};

#endif
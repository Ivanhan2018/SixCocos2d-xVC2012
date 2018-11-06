
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
	enum{	SERVER_HANDLE_POOL_INIT_COUNT = 2048, // 对端服务池的最初元素数量	
		};
public:
	CTrunkServer(void);
	~CTrunkServer(void);

public:

	//--- 关键函数 ----------------------------------

	// 孵化
	static int spawn(const char*roomConfig);

	// 湮灭
	static void annihilate();

public:

	//--- 从父类继承的纯虚函数 ----------------------------------

	// 建立房间实例
	virtual IRoomMgr* create_room_mgr(SERVER_ROOM_INFO serverRoomInfo);

	// 销毁房间实例
	virtual void destroy_room_mgr();

	// 建立桌子群实例
	virtual int create_table();

	// 销毁桌子群实例
	virtual void destroy_table();

	// 建立游戏骨架使用的定时器
	virtual int create_game_skeleton_timer();

	// 建立数据库实例
	virtual IDbAnyGame*	create_db();

	// 销毁数据库实例
	virtual void destroy_db();

	// 房管服的信息获取完毕，并且启动房间服务
	virtual int OnRoomMgrServerOk(SERVER_ROOM_INFO serverRoomInfo, ROOM_CONFIG roomConfig);

public:
	BOOL		m_bIsStart;

	CConnectCenterServer* m_pConnectCenter;
};

#endif
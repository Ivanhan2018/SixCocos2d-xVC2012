
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
		TIMER_ROOM_EVENT_ID = 5,	// 房间定时器的事件ID

		TIMER_TABLE_NO = 1,			// 桌号
		TIMER_TABLE_EVENT_ID = 8,	// 桌子定时器的事件ID
	};
	enum{	SERVER_HANDLE_POOL_INIT_COUNT = 2048, // 对端服务池的最初元素数量	
	};
public:
	CFishTrunk(void);
	~CFishTrunk(void);

public:

	//--- 关键函数 ----------------------------------

	// 孵化
	static int spawn(const char*roomConfig=NULL);

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

	// 列印所有的守护
	int display_all_guard();

	//--- 测试部分 ----------------------------------

	// 设置定时器
	void test_05();

	// 杀掉定时器
	void test_06();

	void test_07();

public:
	BOOL		m_bIsStart;

	CConnectCenterServer* m_pConnectCenter;

};

#endif
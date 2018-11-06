/*********************************************************
Name：SIX_RoomMgr
Desc：房间数据管理
Auth：Cool.Cat@2013-09-11
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include "SIX_Common.h"

typedef multimap<long long,CMD_SC_RoomList*> MMAP_ROOM;
typedef MMAP_ROOM::iterator ITER_ROOM;
typedef pair<ITER_ROOM,ITER_ROOM> RANGE_ROOM;

class SIX_RoomMgr:public TSingleton<SIX_RoomMgr>
{
public:
	SIX_RoomMgr();
	virtual ~SIX_RoomMgr();
	static SIX_RoomMgr *GetInstance() 
	{
		if (!m_gRoomMgr)
			m_gRoomMgr = new SIX_RoomMgr();
		return m_gRoomMgr;
	}
	void Release()
	{
		//if (!m_gRoomMgr)
		//	return;
		//CC_SAFE_DELETE(m_gRoomMgr);
	}

	void Add(CMD_SC_RoomList *pRoomItem);
	CMD_SC_RoomList *Get(int);
	void DelAll();
	MMAP_ROOM *getMap(){return &m_RoomMap;}

	void SetTablePlayerCount(int iTableIndex, int nCount, bool bTotalCount=false);
	int GetTablePlayerCount(int iTableIndex) const;
	int GetTableCount();

	void InitRoom();
	long long GetCurRoomID(){ return m_llCurSelectRoom; }
	void SetCurRoomID(long long llRoomID){	m_llCurSelectRoom = llRoomID; }
	CMD_SC_RoomList * GetCurRoom();
	const CMD_SC_RoomList *GetPlayerMaxRoom(long long llGold) const;
	
private:
	static SIX_RoomMgr *m_gRoomMgr;

	MMAP_ROOM m_RoomMap;
	map<int,int>	m_mTablePlayerCount;	// 每座的玩家人数
	long long			m_llCurSelectRoom;	// 当前选择的房间
};
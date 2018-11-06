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
private:
	static SIX_RoomMgr *m_gRoomMgr;
	MMAP_ROOM m_RoomMap;
};
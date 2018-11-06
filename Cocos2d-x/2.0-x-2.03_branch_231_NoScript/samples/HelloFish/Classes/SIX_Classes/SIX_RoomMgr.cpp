#include "SIX_RoomMgr.h"

SIX_RoomMgr *SIX_RoomMgr::m_gRoomMgr = 0;

SIX_RoomMgr::SIX_RoomMgr()
{
}

SIX_RoomMgr::~SIX_RoomMgr()
{
	this->Release();
}

void SIX_RoomMgr::Add(CMD_SC_RoomList *pRoomItem)
{
	if (!pRoomItem)
		return;
	m_RoomMap.insert(MMAP_ROOM::value_type(pRoomItem->lParentId,pRoomItem));
}

CMD_SC_RoomList *SIX_RoomMgr::Get(int roomIdx)
{
	for (ITER_ROOM iter=m_RoomMap.begin();iter!=m_RoomMap.end();iter++)
	{
		CMD_SC_RoomList *pRoomItem = iter->second;
		if (pRoomItem->iRoomId==roomIdx)
			return pRoomItem;
	}
	return 0;
}

void SIX_RoomMgr::DelAll()
{
	for (ITER_ROOM iter=m_RoomMap.begin();iter!=m_RoomMap.end();)
	{
		CMD_SC_RoomList *pRoomItem = iter->second;
		m_RoomMap.erase(iter++);
		CC_SAFE_DELETE(pRoomItem);
	}
#ifdef WIN32
	m_RoomMap.swap(MMAP_ROOM());
#endif
	m_RoomMap.clear();
}
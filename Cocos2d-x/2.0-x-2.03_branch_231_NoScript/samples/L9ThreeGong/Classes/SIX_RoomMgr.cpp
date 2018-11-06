#include "SIX_RoomMgr.h"

SIX_RoomMgr *SIX_RoomMgr::m_gRoomMgr = 0;

SIX_RoomMgr::SIX_RoomMgr()
{
	m_llCurSelectRoom = -1;
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

void SIX_RoomMgr::SetTablePlayerCount(int iTableIndex, int nCount, bool bTotalCount/*=false*/)
{
	if (-1 == iTableIndex)
		return;

	map<int,int>::iterator mPlayerCount = m_mTablePlayerCount.find(iTableIndex);
	if (m_mTablePlayerCount.end() != mPlayerCount)
	{
		mPlayerCount->second = bTotalCount?nCount:(mPlayerCount->second+nCount);
	}
	else
	{
		m_mTablePlayerCount.insert(make_pair(iTableIndex, nCount));
	}
}

int SIX_RoomMgr::GetTablePlayerCount(int iTableIndex) const
{
	map<int,int>::const_iterator cmPlayerCount = m_mTablePlayerCount.find(iTableIndex);
	if (m_mTablePlayerCount.end() != cmPlayerCount)
		return cmPlayerCount->second;
	else
		return 0;
}

int SIX_RoomMgr::GetTableCount()
{
	if (-1 == m_llCurSelectRoom)
		return 0;
	MMAP_ROOM::const_iterator mGameServer = getMap()->find(m_llCurSelectRoom);
	if (mGameServer != getMap()->end())
	{
		return mGameServer->second->iTables;
	}
	return 0;
}

void SIX_RoomMgr::InitRoom()
{
	m_mTablePlayerCount.clear();
}

CMD_SC_RoomList * SIX_RoomMgr::GetCurRoom()
{
	if (-1 != m_llCurSelectRoom)
	{
		MMAP_ROOM::const_iterator mGameServer = getMap()->find(m_llCurSelectRoom);
		if (mGameServer != getMap()->end())
		{
			return &(*(mGameServer->second));
		}
	}
	return NULL;
}

const CMD_SC_RoomList * SIX_RoomMgr::GetPlayerMaxRoom(long long llGold) const
{
	int iDoorsill = 0;		// 最小门槛
	int iMaxDoorsill = 0;	// 最大门槛
	CMD_SC_RoomList *pRoomResult = NULL;
	MMAP_ROOM::const_iterator cmRoomList = m_RoomMap.begin();
	// 找到携带金币能进入最高等级的房间类型
	for (; m_RoomMap.end() != cmRoomList; ++cmRoomList)
	{
		if (0!=pRoomResult && (llGold<cmRoomList->second->iDoorsill  ||  iMaxDoorsill>cmRoomList->second->iMaxDoorsill))
			continue;
		if (0==pRoomResult || (iDoorsill<cmRoomList->second->iDoorsill  &&  iMaxDoorsill<cmRoomList->second->iMaxDoorsill))
		{
			iDoorsill = cmRoomList->second->iDoorsill;
			iMaxDoorsill = cmRoomList->second->iMaxDoorsill;
			pRoomResult = cmRoomList->second;
		}
	}

	// 找到同类型房间中人数最多的房间
	if (0 != pRoomResult)
	{
		int iPlayerCount = -1;
		cmRoomList = m_RoomMap.begin();
		for (; m_RoomMap.end() != cmRoomList; ++cmRoomList)
		{
			if (pRoomResult->lParentId == cmRoomList->second->lParentId  &&  iPlayerCount < cmRoomList->second->iPlayerCount)
			{
				iPlayerCount = cmRoomList->second->iPlayerCount;
				pRoomResult = cmRoomList->second;
			}
		}
	}
	return pRoomResult;
}
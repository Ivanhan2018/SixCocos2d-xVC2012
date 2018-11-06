#include "SIX_PlayerMgr.h"

SIX_PlayerMgr *SIX_PlayerMgr::m_gPlayerMgr = 0;

SIX_PlayerMgr::SIX_PlayerMgr()
{
	m_MyUserIdx = 0;
	memset(m_MyName,0,sizeof(m_MyName));
	memset(m_MyPass,0,sizeof(m_MyPass));
	m_MyTableIdx = -1;
	m_MySeatIdx = -1;
}

SIX_PlayerMgr::~SIX_PlayerMgr()
{
	this->Release();
}

void SIX_PlayerMgr::OnDelegateDestory(PLAYER_LIST *pPlayer)
{
	if (!pPlayer)
		return;
}

PLAYER_LIST *SIX_PlayerMgr::getSelfPlayer()
{
	return this->Get(this->m_MyUserIdx);
}

void SIX_PlayerMgr::Enter(CCLayerColor *background)
{
	if (!g_pShipMgr)
		return;
	for (m_iter=m_map.begin();m_iter!=m_map.end();m_iter++)
	{
		PLAYER_LIST *pPlayer = m_iter->second;
		if (pPlayer->UserIdx!=this->getMyUserIdx() && pPlayer->iTableId==this->getMyTableIdx() && pPlayer->SeatId!=this->getMySeatIdx())
		{
			g_pShipMgr->Enter(background,pPlayer->UserIdx,pPlayer->SeatId,false);
		}
	}
}

void SIX_PlayerMgr::LeaveSeat(long long idx,int tableIdx,int seatIdx)
{
	if (!g_pShipMgr)
		return;
	for (m_iter=m_map.begin();m_iter!=m_map.end();m_iter++)
	{
		PLAYER_LIST *pPlayer = m_iter->second;
		if (pPlayer->UserIdx==idx && pPlayer->iTableId==tableIdx && pPlayer->SeatId==seatIdx)
		{
			g_pShipMgr->Leave(idx);
			break;
		}
	}
}
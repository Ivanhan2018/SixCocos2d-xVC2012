#include "SIX_PlayerMgr.h"

SIX_PlayerMgr *SIX_PlayerMgr::m_gPlayerMgr = 0;

SIX_PlayerMgr::SIX_PlayerMgr()
{
	m_MyUserIdx = 0;
	memset(m_MyName,0,sizeof(m_MyName));
	memset(m_MyPass,0,sizeof(m_MyPass));
	memset(m_MyNickName,0,sizeof(m_MyNickName));
	m_MyLevel=0;
	m_MyChip=0;
	m_MyTableIdx = -1;
	m_MySeatIdx = -1;
	m_MyUserIdentity=0;
	m_wBankerChairID=0;
	m_C3=m_C2=m_C1=0;
	m_bAllowChangeToHall = true;
}

SIX_PlayerMgr::~SIX_PlayerMgr()
{
	this->Release();
}


// 6个位置，左上角顺时针方向顺序 012345
// 逻辑ID<->视图ID互转函数
int SIX_PlayerMgr::getViewID(int CurLogicID, int MyLogicID)
{
	int CurViewID=(CurLogicID-MyLogicID+3+GAME_PLAYER_COUNT)%GAME_PLAYER_COUNT;
	return CurViewID;
}


int SIX_PlayerMgr::getLogicID(int CurViewID, int MyLogicID)
{
	int CurLogicID=(CurViewID-3+MyLogicID+GAME_PLAYER_COUNT)%GAME_PLAYER_COUNT;
	return CurLogicID;
}

int SIX_PlayerMgr::getBankerViewID()
{
	return this->getViewID(this->m_wBankerChairID,this->getMySeatIdx());
}

void SIX_PlayerMgr::clearPlayers()
{
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		memset(&m_Players[i],0,sizeof(m_Players[i]));
	}
}
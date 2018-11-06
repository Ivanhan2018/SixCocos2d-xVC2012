#include "EntityMgr.h"
#include "platform/CCPlatformMacros.h"


SINGLETON_DEFINE_INST(EntityMgr, CCObject);


EntityMgr::EntityMgr()
:m_pLogin(new Login())
,m_pRoomFrame(new RoomFrame())
,m_pDispatch(new MsgDispatch())
,macAddress("M123")
{
	for (int i = 0; i < 4; i ++)
	{
		m_nDownLoadPesent[i] = 0;
	}
	m_bIsShowRuker = false;
	m_pDispatch->init();
}

EntityMgr::~EntityMgr()
{
	CC_SAFE_DELETE(m_pDispatch);
	CC_SAFE_DELETE(m_pLogin);
	CC_SAFE_DELETE(m_pRoomFrame);
}

void EntityMgr::setMacAddress(const char* mac)
{
	macAddress = mac;
}

void EntityMgr::setDownLoadPesent(int pesent,int gameID)
{
	m_nDownLoadPesent[gameID] = pesent;
}

int EntityMgr::getPesent(int gameID)
{
	return m_nDownLoadPesent[gameID];
}

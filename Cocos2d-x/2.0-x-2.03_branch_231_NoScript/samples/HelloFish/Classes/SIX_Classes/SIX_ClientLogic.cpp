#include "SIX_ClientLogic.h"

SIX_ClientLogic::SIX_ClientLogic()
{
	pRoomInfo = 0;
}

SIX_ClientLogic::~SIX_ClientLogic()
{
	CC_SAFE_DELETE(pRoomInfo);
	SIXLog("~SIX_ClientLogic");
}

int SIX_ClientLogic::init(char *ip,int port,char *name,char *pass)
{
	CC_SAFE_DELETE(pRoomInfo);
	pRoomInfo = new CLIENT_ROOM_INFO(ip,port,name,pass);

	return SIX_ClientBase::init(ip,port,name,pass);
}
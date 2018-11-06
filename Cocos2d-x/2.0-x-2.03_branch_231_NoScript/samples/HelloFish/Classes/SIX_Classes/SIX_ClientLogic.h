/*********************************************************
Name：SIX_ClientLogic
Desc：SOCKET交互接口，所有网络消息丢到SIX_Proxy代理中，
      由UI线程处理。
Auth：Cool.Cat@2013-05-08
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_PackageMgr.h>
#include <SIX_Proxy.h>
#include <SIX_ClientBase.h>
#include "SIX_Common.h"

class SIX_Proxy;
class SIX_SocketBase;

class SIX_ClientLogic:public SIX_ClientBase
{
public:
	SIX_ClientLogic();
	virtual ~SIX_ClientLogic();
	virtual int init(char *ip,int port,char *name,char *pass);
	LOGIN_ROOM_SUCC &GetLoginInfo(){return m_stLoginSucc;}
	CLIENT_ROOM_INFO *GetRoomInfo(){return pRoomInfo;}
private:
	LOGIN_ROOM_SUCC	m_stLoginSucc;
	CLIENT_ROOM_INFO *pRoomInfo;
};
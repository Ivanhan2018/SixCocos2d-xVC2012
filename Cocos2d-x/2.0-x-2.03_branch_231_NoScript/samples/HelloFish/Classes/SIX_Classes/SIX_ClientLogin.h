/*********************************************************
Name：SIX_ClientLogin
Desc：登录服务器交互
Auth：Cool.Cat@2013-07-31
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_ClientLogic.h>
#include <SIX_PackageMgr.h>
#include <SIX_Proxy.h>
#include <SIX_SceneGate.h>
#include "SIX_Common.h"

class SIX_SceneGate;

/// 连接类型
typedef enum tagConnectionType
{
	CONNECTION_LOGIN,							// 登陆
	CONNECTION_EXPLOIT,						// 获得功勋排行数据
	CONNECTION_MATCH,						// 获取比赛 排行数据
	CONNECTION_MY_EXPLOIT,				// 领取我的功勋排名
	CONNECTION_MY_MATCH,				// 领取我的比赛排名
}ConnectionType;

class SIX_ClientLogin:public SIX_ClientLogic,public TSingleton<SIX_ClientLogin*>
{
public:
	SIX_ClientLogin();
	virtual ~SIX_ClientLogin();
	
	void SetConnectionType(ConnectionType ctType);
	ConnectionType GetConnectionType();
	void ShowMsgBox(const char *fmt,...);

	void Connect();
	void Disconnect();

	virtual void HandlePacketRaw(int,int,unsigned char*,unsigned int);

	static SIX_ClientLogin *GetInstance() 
	{
		if (!m_gClientLogin)
			m_gClientLogin = new SIX_ClientLogin();
		return m_gClientLogin;
	}

	void OnRelease()
	{
		CC_SAFE_DELETE(m_gClientLogin);
	}

	void setRoomListRequested(bool requested){m_bRoomListRequested=requested;}
	bool getRoomListRequested(){return m_bRoomListRequested;}
private:
	void HandlePacketLogin(int subCode,unsigned char *pData,int pDataLen);
	void HandlePacketRanking(int subCode,unsigned char *pData,int pDataLen);

private:
	static SIX_ClientLogin *m_Instance;
	static SIX_ClientLogin *m_gClientLogin;
	bool m_bRoomListRequested;

	ConnectionType m_ConnectionType;		// 连接类型，默认登陆
};
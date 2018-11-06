/*********************************************************
Name��SIX_ClientLogin
Desc����¼����������
Auth��Cool.Cat@2013-07-31
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_ClientLogic.h>
#include <SIX_PackageMgr.h>
#include <SIX_Proxy.h>
#include <SIX_SceneGate.h>
#include "SIX_Common.h"

class SIX_SceneGate;

/// ��������
typedef enum tagConnectionType
{
	CONNECTION_LOGIN,							// ��½
	CONNECTION_EXPLOIT,						// ��ù�ѫ��������
	CONNECTION_MATCH,						// ��ȡ���� ��������
	CONNECTION_MY_EXPLOIT,				// ��ȡ�ҵĹ�ѫ����
	CONNECTION_MY_MATCH,				// ��ȡ�ҵı�������
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

	ConnectionType m_ConnectionType;		// �������ͣ�Ĭ�ϵ�½
};
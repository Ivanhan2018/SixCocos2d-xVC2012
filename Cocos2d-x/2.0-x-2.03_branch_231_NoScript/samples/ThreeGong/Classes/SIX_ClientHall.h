/*********************************************************
Name：SIX_ClientHall
Desc：大厅服务器交互
Auth：团长@2013-10-09
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_ClientLogic.h>
#include <SIX_PackageMgr.h>
#include <SIX_Proxy.h>
#include "SIX_SceneHall.h"
#include "SIX_Common.h"


#include <queue>
using std::queue;

class SIX_SceneHall;

typedef struct tagSendData
{
	int nMainCode;
	int nSubCode;
	int nDataLen;
	int nStructLen;
	BYTE *pData;
}senddata;

class SIX_ClientHall:public SIX_ClientLogic,public TSingleton<SIX_ClientHall*>
{
public:
	SIX_ClientHall();
	virtual ~SIX_ClientHall();
	void OnRelease();

	static SIX_ClientHall *GetInstance() 
	{
		if (!m_gClientHall)
			m_gClientHall = new SIX_ClientHall();
		return m_gClientHall;
	}

	void SendData(int iMainCode, int iSubCode, BYTE* pData=NULL, int iDataLen=0);
	void Connect(bool bReconnected=true,int iReconnectDelay=MAX_RECONNECT_DELAY);
	void Disconnect();
	void AddServer(CMD_PlazaServerList *pServer);
	void ShowMsgBox(const char *fmt,...);

	virtual void HandlePacketRaw(int,int,unsigned char*,unsigned int);

private:
	void HandlePacketTask(int subCode,unsigned char *pData,int nDataLen);
	void HandlePacketActivity(int subCode,unsigned char *pData,int nDataLen);
	void HandlePacketTopList(int subCode,unsigned char *pData,int nDataLen);
	void HandlePacketShop(int subCode,unsigned char *pData,int nDataLen);
	void HandlePacketInitHall(int subCode,unsigned char *pData,int nDataLen);

private:
	static SIX_ClientHall *m_gClientHall;
	queue<senddata *>	m_QueueData;

	vector<CMD_PlazaServerList>::size_type m_nConnectServerIndex;
	vector<CMD_PlazaServerList> m_vPlazaServer;
};
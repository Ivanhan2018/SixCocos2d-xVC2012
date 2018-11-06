/*********************************************************
Name：SIX_ClientRoom
Desc：房间服务器交互
Auth：Ivan_han@2013-10-12
*********************************************************/
#pragma once
#include "SIX_Typedef.h"
#include "SIX_ClientLogic.h"
#include "SIX_PackageMgr.h"
#include "SIX_Proxy.h"
#include "SIX_Common.h"
#include "SIX_CardPlay.h"

class SIX_ClientRoom:public SIX_ClientLogic,public TSingleton<SIX_ClientRoom*>
{
public:
	SIX_ClientRoom();
	virtual ~SIX_ClientRoom();

	void Connect(const char *addr,int port,bool bReconnected=true,int iReconnectDelay=MAX_RECONNECT_DELAY, bool bAutoSitDown=true);
	void Disconnect();

	virtual void HandlePacketRaw(int,int,unsigned char*,unsigned int);

	static SIX_ClientRoom *GetInstance() 
	{
		if (!m_gClientRoom)
			m_gClientRoom = new SIX_ClientRoom();
		return m_gClientRoom;
	}

	void OnRelease()
	{
		CC_SAFE_DELETE(m_gClientRoom);
	}
	
	bool getLogicConnect(){ return m_bLogicConnect; }

	void login_room();
	void leave_room();
	void sit_down(int iTableNo, int iSeatNo);
	void raise_hand();
	void leave_seat();
	void query_table_list();
	void query_user_list();
	void write_score(const CMD_WRITE_SCORE& score);
	void tick_one_leave_seat(int iTableNo, int iSeatNo);
	void tick_table_leave_seat(int iTableNo);
	void tick_all_leave_seat();
	void tick_user_out_room(int iTableNo, int iSeatNo);
	void tick_user_out_room(int iTableNo);
	void tick_user_out_room();

	//测试用
	void auto_sit_down();
private:
	void HandlePacketRoom(int iSubCode,unsigned char *pData,int iDataLen);
	void HandlePacketTable(int iSubCode,unsigned char *pData,int iDataLen);
	void HandlePacketMatch(int iSubCode,unsigned char *pData,int iDataLen);

	void setSameTablePlayerData(long long lUserID);

private:
	static SIX_ClientRoom *m_gClientRoom;
	bool m_bAutoSitDown;
	bool m_bLogicConnect;
};
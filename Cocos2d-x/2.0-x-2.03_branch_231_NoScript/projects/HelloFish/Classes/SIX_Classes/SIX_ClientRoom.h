/*********************************************************
Name��SIX_ClientRoom
Desc���������������
Auth��Cool.Cat@2013-07-31
*********************************************************/
#pragma once

#include <SIX_Typedef.h>
#include <SIX_ClientLogic.h>
#include <SIX_PackageMgr.h>
#include <SIX_Proxy.h>
#include "FishManage.h"
#include "Ship.h"
#include <SIX_SceneGate.h>
#include <SIX_SceneRoom.h>
#include <SIX_SceneGame.h>

class SIX_ClientLogic;

class SIX_ClientRoom:public SIX_ClientLogic,public TSingleton<SIX_ClientRoom*>
{
public:
	SIX_ClientRoom();
	virtual ~SIX_ClientRoom();

	void Connect(const char *addr,int port);
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
private:
	void HandlePacketRoom(int subCode,unsigned char *pData,int pDataLen);
	void HandlePacketTable(int subCode,unsigned char *pData,int pDataLen);
	void HandlePacketMatch(int subCode,unsigned char *pData,int pDataLen);
public:
	void ShowMsgBox(const char *fmt,...);
	//add by Ivan_han
	void OnAddOneFish(Rsp_AddOneFish *pReal,float InitElapsed,TBuildTraceTime BuildTraceTime);
	void SetRaiseHandTime(unsigned long long tRaiseHandTime){m_tRaiseHandTime=tRaiseHandTime;}
	long long GetClientServerTimeInterval()const{return m_tClientServerTimeInterval;}
	//�ͻ����յ����������ʱ���ʱ��ֱ�ӵ���::GetTickCount64()��add by Ivan_han 20130614
	//static unsigned long long GetTickCount64();
	//���������ݵĽ��ա������add by Ivan_han 20130614
	bool IsNeedMalloc(TFishGroupID FishGroupID);
	FishListInfo *GetFishListInfo(TFishGroupID FishGroupID,bool isFirst);
	//������,BusyFishListCount()=0,1
	int BusyFishListCount()const;
	void SendNetGapTime(); // ����ʱ�䣨������ȡ�����ӳ���Ϣ�� add by cxf
private:
	unsigned long long m_tRaiseHandTime;	// ����������ʱ��c1��add by Ivan_han 20130628
	long long m_tClientServerTimeInterval;//��t=CK-SK+dT�������ɸ�����
	//vector<Rsp_AddOneFish> m_vecFish;//��켣��
	FishListInfo m_FishListInfos[20];//��켣��ָ������

	static SIX_ClientRoom *m_gClientRoom;
};
/***********************************************
Name��SIX_RoomList
Desc�������б����򣬰����Զ�ƥ��/�ֶ��������ܡ�
Auth��Cool.Cat@2013-07-31
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_EffectPopWnd.h>
#include "SIX_ListView.h"
#include "SIX_ListViewCell.h"
#include "SIX_ScrollBar.h"
#include "SIX_GlobalMgr.h"
#include "SIX_ClientRoom.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_ClientRoom;

class SIX_RoomList:public SIX_EffectPopWnd
{
public:
	SIX_RoomList();
	virtual ~SIX_RoomList();
	static SIX_RoomList *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);

	void setGateIdx(int idx);
	int getGateIdx();

	void setRoomIdx(int idx);
	int getRoomIdx();

	void setInited(bool bInited);
	bool getInited();

	void ShowListRoom(bool isShow=true);
	void ShowListTable(bool isShow=true);

	// ��ʾ/���ط���������Loading��ʾ
	void ShowTableLoading(bool isLoading=true);
	void RefreshTableList(int iRoomPeopleCount,int iTables,int iSeatNum);
	void MakeTableAll();
	void MakeRowTable(int rowStart,int rowCount,int tableCount);
	void SwitchSitDownOrLeaveSeat(long long lUserId,int iTableNo,int iSeatNo,bool IsSitDown);
	CCControlButton *FindControlFromData(int iTableNo,int iSeatNo);
	int getTableColumn();

	void setAutoSit(bool isAutoSit=false);
	bool getAutoSit();

	void ShowQucikStart(bool bShow=true);
private:
	void RefreshRoomList();
private:
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);
	virtual bool OnBtn(CCObject*,int tag);
private:
	// ����
	CCSprite *pTitle;
	// ���°�ť
	CCControlButton *pBtnUp;
	CCControlButton *pBtnDown;
	// ��෿���б�
	SIX_ListView *pListRoom;
	// �Ҳ������б�
	SIX_ListView *pListTable;
	// ���ٿ�ʼ��ť
	CCControlButton *pBtnQuick;
	// ���ٿ�ʼ������ʾ
	CCLabelTTF *pLabelQuick;

	// �ؿ�����
	int m_iGateIdx;
	// ��һ�ιؿ�����
	int m_iGateIdxLast;

	// ��������
	int m_iRoomIdx;
	// ��һ�εķ�������
	int m_iRoomIdxLast;

	// �Ƿ��ʼ��UI�ؼ�
	bool m_bInited;

	int m_RoomPeopleCount;
	int m_Tables;
	int m_SeatNum;

	// �Ƿ��Զ�����
	bool m_bAutoSit;
};

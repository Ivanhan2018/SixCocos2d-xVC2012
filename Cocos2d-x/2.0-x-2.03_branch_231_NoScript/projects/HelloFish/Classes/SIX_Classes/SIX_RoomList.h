/***********************************************
Name：SIX_RoomList
Desc：房间列表弹出框，包含自动匹配/手动入座功能。
Auth：Cool.Cat@2013-07-31
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

	// 显示/隐藏房间内桌子Loading提示
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
	// 标题
	CCSprite *pTitle;
	// 上下按钮
	CCControlButton *pBtnUp;
	CCControlButton *pBtnDown;
	// 左侧房间列表
	SIX_ListView *pListRoom;
	// 右侧座子列表
	SIX_ListView *pListTable;
	// 快速开始按钮
	CCControlButton *pBtnQuick;
	// 快速开始文字提示
	CCLabelTTF *pLabelQuick;

	// 关卡索引
	int m_iGateIdx;
	// 上一次关卡索引
	int m_iGateIdxLast;

	// 房间索引
	int m_iRoomIdx;
	// 上一次的房间索引
	int m_iRoomIdxLast;

	// 是否初始化UI控件
	bool m_bInited;

	int m_RoomPeopleCount;
	int m_Tables;
	int m_SeatNum;

	// 是否自动入座
	bool m_bAutoSit;
};

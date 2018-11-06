/***********************************************
Name：SIX_MatchList
Desc：比赛房间列表弹出框
Auth：团长@2013-08-12
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

class SIX_MatchList:public SIX_EffectPopWnd
{
public:
	SIX_MatchList();
	virtual ~SIX_MatchList();
	static SIX_MatchList *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);

	void setGateIdx(int idx);
	int getGateIdx();

	void setRoomIdx(int idx);
	int getRoomIdx();

	void setInited(bool bInited);
	bool getInited();

	void setLoginRoomSuccess(bool bLogin);
	bool getLoginRoomSuccess() const;

	void ShowListRoom(bool isShow=true);
	//void ShowListTable(bool isShow=true);
	void ShowWaitQueue(bool isShow=true);

	void AutoSqueue();

	// 显示/隐藏房间内桌子Loading提示
	//void ShowTableLoading(bool isLoading=true);
	//void RefreshTableList(int iRoomPeopleCount,int iTables,int iSeatNum);
	//void MakeTableAll();
	//void MakeRowTable(int rowStart,int rowCount,int tableCount);
	//void SwitchSitDownOrLeaveSeat(long long lUserId,int iTableNo,int iSeatNo,bool IsSitDown);
	//CCControlButton *FindControlFromData(int iTableNo,int iSeatNo);
	//int getTableColumn();
private:
	void RefreshRoomList();
	void UpdateWaitPoint(float dt);
private:
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);
	virtual bool OnBtn(CCObject*,int tag);
	virtual bool OnClose();
private:
	// 标题
	CCSprite *pTitle;
	// 左侧房间列表
	SIX_ListView *pListRoom;
	// 右侧座子列表
	//SIX_ListView *pListTable;
	// 玩家等待界面
	CCNode *m_pWaitQueue;
	// 提示信息
	std::string m_strRoomPrompt;

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
	// 登陆成功
	bool m_bLoginRoomSuccess;

	int m_RoomPeopleCount;
	int m_Tables;
	int m_SeatNum;
};

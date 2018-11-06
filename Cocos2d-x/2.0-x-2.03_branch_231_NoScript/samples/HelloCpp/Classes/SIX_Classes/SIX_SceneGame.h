#pragma once
#include <SIX_UIScene.h>
#include <SIX_Typedef.h>
#include <SIX_ClientRoom.h>
#include "SIX_PopWndSetting.h"
#include "SIX_PopWndBuyBullet.h"//add by Ivan_han 20130708
#include "SIX_PopWndSellFish.h"//add by Ivan_han 20130708
#include "FishManage.h"
#include "BulletAndNetMgr.h"
#include "Gold.h"
#include <SIX_ExpandLayer.h>
#include <SIX_CountDown.h>
#include <SIX_Cursor.h>
#include <SIX_Console.h>

class SIX_ClientRoom;

class SIX_SceneGame:public SIX_UIScene
{
public:
	SIX_SceneGame()
	{
		background = 0;
		m_pSysTip=0;
		g_FishMgr = CFishMgr::GetInstance();
		l_LoadImageCount = l_LoadImageCountTotal = 0;
		g_bInited = false;
		//l_lastCollideCheckTime = SIX_Utility::GetInstance()->GetTickCount();
		//l_CollideIntervalTime = 100;
		l_LoadImageCountTotal = 43;
		hbox_total = 31;
		//hbox_total = 21;
		res_total = l_LoadImageCountTotal + hbox_total;
	}

	virtual ~SIX_SceneGame();
public:
	static SIX_SceneGame* scene();
	virtual bool init();
	void update(float dt);
	void CheckHBoxLoadStatus();
	void RandomBubble();
	void UpdateResProgress(int);
	float convertPercentageToMaxPostionX(float m_fPercentage,CCPoint m_tBarChangeRate,CCPoint m_tMidpoint);
	void TransitionBGCallFun(CCNode* pSender);

    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType);

    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
    virtual void onExit();
	virtual void onCloseExit();
	virtual void OnNotifyCloseWndClicked(CCObject *pObj);

	void doExit();

#ifdef WIN32
	int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam);
	virtual void OnProcessCommand(const char *cmd);
	int shortcutKey(UINT message,WPARAM wParam,LPARAM lParam);
#endif
	void ShowConsole();
	//防沉迷提示信息，add by Ivan_han 20130828
	void SetSysTip(const char *szSysTip);
	void ClearSysTip(){SetSysTip("");}
	//add by Ivan_han 20130725
	SIX_PopWnd *getCurPopWnd()const{return m_pCurShowWnd;}
	//add by Ivan_han 20130724
	CCObject* getChildByObjName(const char *name);
	//add by Ivan_han 20130530
	bool IsInited()const{return g_bInited;}
	void SetInited(bool IsInited){g_bInited=IsInited;}
	bool IsWaitForChangeScene(){return m_WaitForChangeScene;}
	void SetWaitForChangeScene(bool IsWaitFor){m_WaitForChangeScene = IsWaitFor;}
	// 刷新场景
	void RefreshScenes(int nScenesID);
	void ReloadLittleThings();
	// 长时间不发射子弹出倒计时
	void ShowCountDown(int delay);
	void RemoveCountDownAndTips();
	void WriteScoreAndExit();
	void WriteScore();
	// 涨潮
	void RiseTide(int nScenesID, float fRiseTideTime, float fDelayTime, bool bFromRightToLeft);
	// 比赛倒计时
	void SetMatchCountdown(int nTime);

	void FishAndBulletCollide();
	bool GetKeyboardRepeatRoot() { return m_bRepeatShoot; }

	//CCSprite *m_WaveSprite;

	bool IsNoFire(){return m_bNoFire;}

private:
	void AddImageAsyncCallBack(CCObject *pObject);
	void DelayDoInit();
private:
	void MakeActionForShell(CCSprite *pShell,int type);
	void DoShellLoop(CCNode *);
	void OnTouchLogic(CCSet *pTouches,int pEvent);
	virtual void doEvents(CCObject* pSender, CCControlEvent event);

	void ClickUpDown(CCNode *pNode);
	void OnUpDownEffect(CCPoint pt);
	void onRepeatShootBullet(bool IsShoot);
	void onWaitRepeatShootBullet(float dt);
	void ResetGrid();

	// 显示出售获得鱼、购买子弹、帮助、设置等窗口
	void ShowSellFishWnd(bool bShow);
	void ShowBuyBulletWnd(bool bShow);
	void ShowHelpWnd(bool bShow);
	void ShowSetWnd(bool bShow);

	// 关闭按钮
	static bool OnExitBtn();

private:
	CCLayerColor *background;
	//add by Ivan_han 20130828
	CCLabelTTF *m_pSysTip;
	int l_LoadImageCount;
	int l_LoadImageCountTotal;
	bool g_bInited;
	//unsigned long l_lastCollideCheckTime;
	//int l_CollideIntervalTime;
	CCLayer *m_ResProgress;
	int res_total;
	int hbox_total;
	bool m_WaitForChangeScene;
	SIX_Console *pConsole;
	unsigned long long m_ulKeyBoardPushTime;
	bool m_NeedDrawBox;
	bool m_bRepeatShoot;
	int m_nKeyDownCount;

	int m_nSceneID;

	SIX_PopWndSellFish *pSellFish;
	SIX_PopWndBuyBullet *pBuyBullet;
	SIX_PopWnd *pHelp;
	SIX_PopWndSetting *pSetting;
	SIX_PopWnd *m_pCurShowWnd;

	unsigned long long m_uLastTick;

	SIX_ExpandLayer *pExpandLayer;
	SIX_CountDown *pCountDown;

	bool m_bNoFire;
};
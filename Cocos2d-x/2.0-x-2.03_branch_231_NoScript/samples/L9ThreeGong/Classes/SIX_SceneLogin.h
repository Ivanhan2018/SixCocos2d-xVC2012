/***********************************************
Name：SIX_SceneLogin
Desc：登录场景
Auth：Cool.Cat@2013-09-29
***********************************************/
#pragma once
#include <SIX_UIScene.h>
#include <SIX_Typedef.h>
#include <SIX_ExpandLayer.h>
#include "SIX_LoginPanel.h"

enum {
	BTN_LOGIN_AS_GUEST = 1,
	BTN_LOGIN_AS_MEMBER,
};

class SIX_SceneLogin:public SIX_UIScene
{
public:
	SIX_SceneLogin()
	{
	}

	virtual ~SIX_SceneLogin();
public:
	static SIX_SceneLogin* scene();
	virtual bool init();
	void update(float dt);

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
	// 关闭按钮 或 退出进程时触发
	// Cool.Cat
	virtual void onCloseExit();
	virtual void OnNotifyCloseWndClicked(CCObject *pObj);

#ifdef WIN32
	int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam);
#endif

	SIX_LoginPanel *getLoginPanel(){return m_pLoginPanel;}

	void DoChangeScene();
private:
	void doEvents(CCObject* pSender, CCControlEvent event);
	void ProgressDown(CCNode *pNode);
private:
	CCProgressTimer *pCountDown;
	SIX_LoginPanel *m_pLoginPanel;
};
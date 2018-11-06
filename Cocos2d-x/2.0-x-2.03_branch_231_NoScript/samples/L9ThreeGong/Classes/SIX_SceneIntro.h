/***********************************************
Name：SIX_SceneIntro
Desc：LOGO场景
Auth：Cool.Cat@2013-09-24
***********************************************/
#pragma once
#include <SIX_UIScene.h>
#include <SIX_Typedef.h>

class SIX_SceneIntro:public SIX_UIScene
{
public:
	SIX_SceneIntro()
	{
	}

	virtual ~SIX_SceneIntro();
public:
	static SIX_SceneIntro* scene();
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

	void ChangeNextScene(float);
private:
	void doEvents(CCObject* pSender, CCControlEvent event);
private:
};
/*********************************************************
Name：场景类
Desc：内部UI控件操作、CCLayer事件响应分发到Lua中处理
Auth：Cool.Cat@2013-03-29
*********************************************************/
#pragma once
#include <cocos2d.h>
#include <TSingleton.h>
#include <SIX_Interface.h>
#include <SIX_UILayer.h>
#include <SIX_UIMgr.h>
#include <SIX_DSTPL.h>
#include <SIX_DisconnectBox.h>
#include <SIX_ClientBase.h>

class SIX_DisconnectBox;
class SIX_ClientBase;
class SIX_UIMgr;

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_UIScene:public SIX_UILayer
{
public:
	friend class SIX_ClientBase;
	virtual ~SIX_UIScene();
public:
	virtual int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam){return 0;}
	virtual void keyMenuClicked();
	virtual void keyBackClicked();
public:
	void InitUIMgr();
	virtual void OnNotifyCloseWndClicked(CCObject *pObj){};
	virtual void doEvents(CCObject* pSender, CCControlEvent event){};
	// 关闭提示窗口
	void ShowCloseBox(bool bShow=true);
	// 闪断提示窗口
	void ShowFlashBox(SIX_ClientBase *pLogic,bool bShow=true);
	// 闪断超时后的回调
	void onDisconnectCallback();
public:
	SIX_UIMgr *GetUIMgr()				{return m_UIManager;}
	CCScene *GetScene()					{return m_Scene;}
	//SIX_ClientLogic *GetClientLogic();
public:
	SIX_UIMgr *m_UIManager;
	CCScene *m_Scene;
	SIX_DisconnectBox *m_pFlashBox;
	SIX_DisconnectBox *m_pCloseBox;
	SIX_ClientBase *m_pLogic;
};
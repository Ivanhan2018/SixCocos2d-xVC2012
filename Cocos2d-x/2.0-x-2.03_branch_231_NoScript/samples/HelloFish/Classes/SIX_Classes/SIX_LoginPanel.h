/***********************************************
Name：SIX_LoginPanel
Desc：用户登录面板
Auth：Cool.Cat@2013-09-09
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_EffectPopWnd.h>
#include <SIX_EditBox.h>
#include "SIX_ListView.h"
#include "SIX_ListViewCell.h"
#include "SIX_ScrollBar.h"
#include "SIX_GlobalMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_LoginPanel:public SIX_EffectPopWnd
{
public:
	SIX_LoginPanel();
	virtual ~SIX_LoginPanel();
	static SIX_LoginPanel *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);

	virtual bool onTextFieldAttachWithIME(SIX_EditBox * pSender);
	virtual bool onTextFieldDetachWithIME(SIX_EditBox * pSender);

	void showTips(const char *);
	bool DoLogin();
	void DoSwitchIMEFocus();
	void DoLockPanel(bool lock=true);
private:
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);
	virtual bool OnBtn(CCObject*,int tag);
	virtual bool OnSubmit();
	virtual bool OnClose();

	void DoEnter();
	virtual void OnInputDone(CCLayer *pLayer,const char *text);
private:
	// 用户名背景
	CCSprite *pSprBgName;
	// 密码背景
	CCSprite *pSprBgPass;
	// IP背景
	CCSprite *pSprBgIP;
	// 用户名输入框
	SIX_EditBox *pEditName;
	// 密码输入框
	SIX_EditBox *pEditPass;
	// IP输入框
	SIX_EditBox *pEditIP;
	// 错误提示
	CCLabelTTF *pLabelTips;
};

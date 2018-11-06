/***********************************************
Name：SIX_PopWndPointCard
Desc：点卡充值
Auth：团长@2013-10-16
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

class SIX_PopWndPointCard:public SIX_EffectPopWnd
{
public:
	SIX_PopWndPointCard();
	virtual ~SIX_PopWndPointCard();
	static SIX_PopWndPointCard *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);

	virtual bool onTextFieldAttachWithIME(SIX_EditBox * pSender);
	virtual bool onTextFieldDetachWithIME(SIX_EditBox * pSender);
	virtual void onHideFinished();

private:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);
	virtual bool OnBtn(CCObject*,int tag);
	virtual bool OnSubmit();
	virtual void OnInputDone(CCLayer *pLayer,const char *text);
	
public:
	bool DoOK();
	void DoLockPanel(bool lock=true);
	void DoSwitchIMEFocus();
	void EmptyCardAndPW();
	void showTips(const char *);

private:
	// 用户注册节点
	CCNode *pLabelReg;
	// 输入框背景
	CCSprite *pSprBgEdit;
	// 卡号输入框
	SIX_EditBox *pEditName;
	// 密码输入框
	SIX_EditBox *pEditPass;
	// 错误提示
	CCLabelTTF *pLabelTips;
	// 返回
	CCControlButton *pBtnBack;
	bool m_bOpenShopWnd;
	
	enum {
		BTN_GETPASS = 10,
		BTN_BACK,
	};

	enum {
		EDIT_NAME = 1,
		EDIT_PASS,
	};
};

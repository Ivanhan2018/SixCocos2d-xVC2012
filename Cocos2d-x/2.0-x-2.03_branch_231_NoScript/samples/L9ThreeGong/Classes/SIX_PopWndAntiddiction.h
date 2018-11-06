/***********************************************
Name：SIX_PopWndAntiddiction
Desc：防沉迷窗口
Auth：Cool.Cat@2013-10-08
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include <SIX_EffectPopWnd.h>

USING_NS_CC;
USING_NS_CC_EXT;

enum {
	EDIT_REALNAME = 1,
	EDIT_IDCARD,
};

class SIX_PopWndAntiddiction:public SIX_EffectPopWnd
{
public:
	virtual ~SIX_PopWndAntiddiction();
public:
	static SIX_PopWndAntiddiction *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);
public:
	virtual bool init();
	virtual bool OnSubmit();
	void showTips(const char*);
	void DoSwitchIMEFocus();
	void DoLockPanel(bool lock=true);
	bool DoAntiddiction();
private:
	virtual void onEnterTransitionDidFinish();
	virtual void OnInputDone(CCLayer *pLayer,const char *text);
private:
	// 真实姓名
	SIX_EditBox *pEditRealName;
	// 身份证号码
	SIX_EditBox *pEditIDCard;
	// 提示
	CCLabelTTF *pLabelTips;
};
/***********************************************
Name��SIX_LoginPanel
Desc���û���¼���
Auth��Cool.Cat@2013-09-09
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
	// �û�������
	CCSprite *pSprBgName;
	// ���뱳��
	CCSprite *pSprBgPass;
	// IP����
	CCSprite *pSprBgIP;
	// �û��������
	SIX_EditBox *pEditName;
	// ���������
	SIX_EditBox *pEditPass;
	// IP�����
	SIX_EditBox *pEditIP;
	// ������ʾ
	CCLabelTTF *pLabelTips;
};

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

enum {
	BTN_GETPASS = 10,
	BTN_GOTOREG,
	BTN_BACKLOGIN,
	BTN_REGISTER,
};

enum {
	EDIT_LOGIN_NAME = 1,
	EDIT_LOGIN_PASS,
	EDIT_REG_NAME,
	EDIT_REG_PASS,
};

class SIX_LoginPanelSG:public SIX_EffectPopWnd
{
public:
	SIX_LoginPanelSG();
	virtual ~SIX_LoginPanelSG();
	static SIX_LoginPanelSG *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);

	virtual bool onTextFieldAttachWithIME(SIX_EditBox * pSender);
	virtual bool onTextFieldDetachWithIME(SIX_EditBox * pSender);

	void showLoginTips(const char *);
	void showRegTips(const char *);
	bool DoLogin();
	bool DoRegister();
	void DoSwitchIMEFocus();
	void DoLockPanel(bool lock=true);

	void DoShowLogin(bool bShow=true);
	void DoShowReset(bool bShow=true);
	void DoShowReg(bool bShow=true);

	virtual void onHideFinished();

	int getCheckStatus(){return checkStatus;}
	void setCheckStatus(int status){checkStatus = status;}
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

	void DoShowEditBox(SIX_EditBox*,bool bShow=true);
private:
	// �һ�����ڵ�
	CCNode *pLabelReset;
	// ���ص�¼
	CCControlButton *pBtnResetBackLogin;

	// �û���¼�ڵ�
	CCNode *pLabelLogin;
	// ����򱳾�
	CCSprite *pSprBgLoginEdit;
	// �û��������
	SIX_EditBox *pEditLoginName;
	// ���������
	SIX_EditBox *pEditLoginPass;
	// ������ʾ
	CCLabelTTF *pLabelLoginTips;
	// �һ�����
	CCControlButton *pBtnGetPass;
	// ע���ʺ�
	CCControlButton *pBtnLoginReg;

	// �û�ע��ڵ�
	CCNode *pLabelReg;
	// ����򱳾�
	CCSprite *pSprBgRegEdit;
	// �û��������
	SIX_EditBox *pEditRegName;
	// ���������
	SIX_EditBox *pEditRegPass;
	// ������ʾ
	CCLabelTTF *pLabelRegTips;
	// ���ص�¼
	CCControlButton *pBtnRegBackLogin;
	// ע���ʺ�
	CCControlButton *pBtnRegReg;

	// �ϴε����ť״̬
	int checkStatus;
};

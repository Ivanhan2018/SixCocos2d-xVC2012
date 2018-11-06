/***********************************************
Name��SIX_PopWnd
Desc��ͨ�õ����򣬰���ȷ�ϡ�ȡ�����رհ�ť����ק
Auth��Cool.Cat@2013-04-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "SIX_UILayer.h"
#include "SIX_Cursor.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define PRIORITY_STEP		-10
#define ZORDER_STEP			10

enum BTN_TAG {
	BTN_SUBMIT = -10,
	BTN_CANCEL = -20,
	BTN_CLOSE = -30
};

class SIX_PopWnd:public SIX_UILayer
{
public:
	virtual ~SIX_PopWnd();
public:
	static SIX_PopWnd *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
	// ��ǰ�ɼ��ĵ���������Ŀ
	static int GetPopWndCount();
	static void setPopWndCount(int nCount);
public:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	// ��дSIX_PopWnd��Ϣ��Ӧ���ȼ����ԣ����ڶര�ڲ㼶��Ϣ������Ӧ��
	// Cool.Cat@2013-07-12
	virtual void onShow();
	virtual void onHide();
	virtual void onShowFinished(){};
	virtual void onHideFinished(){};

	// �����Ź���
	void backgroundWithSpriteFrameName(const char *pszSpriteFrameName);
	void backgroundWithFile(const char *file);
	
	// ��ť�Ź���
	// ��֡������
	void buttonSubmitWithSpriteFrameName(const char *pszSpriteFrameName);
	void buttonCancelWithSpriteFrameName(const char *pszSpriteFrameName);
	void buttonCloseWithSpriteFrameName(const char *pszSpriteFrameName);
	// ���ļ�����
	void buttonSubmitWithFile(const char *file,const char *text=0,const char *fontName="΢���ź�",int fontSize=12);
	void buttonCancelWithFile(const char *file,const char *text=0,const char *fontName="΢���ź�",int fontSize=12);
	void buttonCloseWithFile(const char *file,const char *text=0,const char *fontName="΢���ź�",int fontSize=12);
	// ���ļ����ز����֣�ʵ����̬��ť
	void buttonSubmitWithFileCell(const char *file,int cell,bool Hor=true);
	void buttonCancelWithFileCell(const char *file,int cell,bool Hor=true);
	void buttonCloseWithFileCell(const char *file,int cell,bool Hor=true);

	// ���ݸ���ļ������Զ�����ײ�Yes/No��ťλ��
	void AutoCaclBtnPosWidthYesOrNo(float offsetX,float offsetY);

	// ������ʾ״̬
	bool IsShow();

	// ���ֲ�
	virtual void InitMask(const ccColor4B& color,int nPriority=-129,bool bRedrawBorder=false);
	virtual void CreateMask();
	virtual void ReleaseMask();
	// ���õ������ڴ�С
	virtual void setContentSize(CCSize size);
	// ��ʾ/���ش���
	virtual void Show(bool IsShow=true);

	void ShowActionCallBack(CCNode *node);

	// ���ÿɷ���ק
	void setAllowDragged(bool bAllowDragged);
	bool getAllowDragged();

	// ��ȡ
	CCControlButton *GetBtnSubmit(){return pSubmit;}
	CCControlButton *GetBtnCancel(){return pCancel;}
	CCControlButton *GetBtnClose(){return pClose;}
public:
	virtual bool OnSubmit(){return true;};
	virtual bool OnCancel(){return true;};
	virtual bool OnClose(){return true;};
	virtual bool OnBtn(CCObject*,int tag){return true;}
public:
	CCControlButton *CreateButtonWithFrameName(const char *pszSpriteFrameName);
	CCControlButton *CreateButtonWithFile(const char *file,CCRect rc,const char *text=0,const char *fontName="΢���ź�",int fontSize=12);
	CCControlButton *CreateButtonWithFileCell(const char *file,int cell,bool Hor=true);
	void doEvents(CCObject* pSender, CCControlEvent event);
protected:
	void RedistributionAllChildren(CCNode *pRoot,bool IsHide=false);
	void Redistribution(CCLayer *pControl,bool IsHide=false);

	virtual void OnTouchLogic(CCTouch *pTouch,int pEvent);

    // default implements are used to call script callback if exist
	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccWindowMSG(CCTouch *pTouch, CCEvent *pEvent, int nType);
protected:
	// ����
	CCScale9Sprite *pBackground;
	// ȷ��
	CCControlButton *pSubmit;
	// ȡ��
	CCControlButton *pCancel;
	// �ر�
	CCControlButton *pClose;

	// ���ֲ�
	SIX_UILayer *pBlock;
	ccColor4B m_MaskColor;
	int m_MaskPriority;
	bool m_MaskRedrawBorder;

	bool m_IsShow;
	bool m_ActDone;

	// ��ק���
	bool m_bAllowDragged;
	bool m_IsDragged;
	CCPoint m_LastHitPos;

	// �Ƿ��ڹرյ�ʱ������UI�ӿؼ�
	bool m_bCloseThenCleanup;

	// ��һ�ε����ȼ�
	int m_LastPriority;
	// ����������Ŀ
	static int m_WndCount;

	static int GLOBAL_PRIORITY;
	static int GLOBAL_ZORDER;
};
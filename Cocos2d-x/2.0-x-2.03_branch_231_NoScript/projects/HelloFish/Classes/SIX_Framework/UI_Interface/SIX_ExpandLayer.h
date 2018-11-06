/***********************************************
Name��SIX_ExpandLayer
Desc��ʵ����������4�����򼰸���/�Ǹ����չ��/��£
Auth��Cool.Cat@2013-07-18
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "SIX_UILayer.h"
#include "SIX_Scissor.h"

#define EXPAND_DELAY	0.5f

USING_NS_CC;
USING_NS_CC_EXT;

enum EXPAND_TAG {
	BTN_EXPAND = -1,
};

enum STATUS_EXPAND {
	// �ﵽ��£̬
	STATUS_EXPAND_MIN	= 0,
	// ����չ��̬
	STATUS_EXPAND_INC	= 1,
	// ������£̬
	STATUS_EXPAND_DEC	= 2,
	// �ﵽչ��̬
	STATUS_EXPAND_MAX	= 3,
};

class SIX_ExpandLayer:public SIX_UILayer
{
public:
	virtual ~SIX_ExpandLayer();
public:
	static SIX_ExpandLayer *Create(float x,float y,const ccColor4B& color, float width, float height,int expand_offset=100,bool IsTouch=false,bool IsFollowForward=false,bool IsHor=true,bool bRedrawBorder=false,bool bScissor=false);

	bool AnimateInit(float width,float height);

	void buttonExpandWithSpriteFrameName(const char *pszSpriteFrameName);
	void buttonExpandWithFile(const char *file,CCRect rc,const char *text=0,const char *fontName="΢���ź�",int fontSize=12);
	void buttonExpandWithFileCell(const char *file,int cell,bool Hor=true);

	CCControlButton *CreateButtonWithFrameName(const char *pszSpriteFrameName);
	CCControlButton *CreateButtonWithFile(const char *file,CCRect,const char *text=0,const char *fontName="΢���ź�",int fontSize=12);
	CCControlButton *CreateButtonWithFileCell(const char *file,int cell,bool Hor=true);

	void resetZOrder();

	void setExpandButtonSprite(CCScale9Sprite *btnOn,CCScale9Sprite *btnOff,CCSize);

	virtual bool OnExpand(){return true;};

	CCControl *GetAnimate(){return pAnimate;}
	CCControlButton *GetBtnExpand(){return pBtnExpand;}
private:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void registerWithTouchDispatcher();
	virtual void ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType);

	void doEvents(CCObject* pSender, CCControlEvent event);
	void doExpandAnimation(bool IsExpand);
	void OnTouchLogic(CCSet *pTouch,int pEvent);
	void ExpandOn(CCNode *pNode);
	void ExpandOff(CCNode *pNode);
private:
	// ������
	SIX_Scissor *pAnimate;
	// ���ư�ť
	CCControlButton *pBtnExpand;
	// ���ư�ť����
	CCScale9Sprite *pBtnExpandSpriteOn;
	CCScale9Sprite *pBtnExpandSpriteOff;
	// ���ư�ť�Ƿ����չ��/��£
	bool m_bFollowForward;
	// չ��/��£״̬
	STATUS_EXPAND m_iStatusExpand;
	// չ��/��£����
	bool m_bHor;
	// չ��/��£ƫ��(����)
	// >0=��/��
	// <0=��/��
	int m_iOffset;
	// ����/���Hoverʱ��Ч
	bool m_bWhenTouch;
	// �Ƿ�ü���������
	bool m_bScissor;
};
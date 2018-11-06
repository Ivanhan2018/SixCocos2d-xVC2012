/***********************************************
Name：SIX_ExpandLayer
Desc：实现上下左右4个方向及跟随/非跟随的展开/收拢
Auth：Cool.Cat@2013-07-18
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
	// 达到收拢态
	STATUS_EXPAND_MIN	= 0,
	// 进行展开态
	STATUS_EXPAND_INC	= 1,
	// 进行收拢态
	STATUS_EXPAND_DEC	= 2,
	// 达到展开态
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
	void buttonExpandWithFile(const char *file,CCRect rc,const char *text=0,const char *fontName="微软雅黑",int fontSize=12);
	void buttonExpandWithFileCell(const char *file,int cell,bool Hor=true);

	CCControlButton *CreateButtonWithFrameName(const char *pszSpriteFrameName);
	CCControlButton *CreateButtonWithFile(const char *file,CCRect,const char *text=0,const char *fontName="微软雅黑",int fontSize=12);
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
	// 动画层
	SIX_Scissor *pAnimate;
	// 控制按钮
	CCControlButton *pBtnExpand;
	// 控制按钮纹理
	CCScale9Sprite *pBtnExpandSpriteOn;
	CCScale9Sprite *pBtnExpandSpriteOff;
	// 控制按钮是否跟随展开/收拢
	bool m_bFollowForward;
	// 展开/收拢状态
	STATUS_EXPAND m_iStatusExpand;
	// 展开/收拢方向
	bool m_bHor;
	// 展开/收拢偏移(非零)
	// >0=右/上
	// <0=左/下
	int m_iOffset;
	// 触碰/鼠标Hover时生效
	bool m_bWhenTouch;
	// 是否裁剪超出区域
	bool m_bScissor;
};
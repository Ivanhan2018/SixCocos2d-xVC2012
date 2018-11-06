/***********************************************
Name：SIX_ScrollBar
Desc：SIX_ScrollBar
Auth：Cool.Cat@2013-04-28
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_Slider.h>
#include "cocos-ext.h"
#include "SIX_UILayer.h"
#include "SIX_ListViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_Slider;

class SIX_ScrollBar:public CCControl
{
public:
	SIX_ScrollBar();
	virtual ~SIX_ScrollBar();
public:
	static SIX_ScrollBar* create(
		CCSpriteFrame *bgFrame,CCRect bgFileRect,CCSize bgSize,
		CCSpriteFrame *progressFrame,CCRect progressFileRect,
		CCSpriteFrame *thumbFrame,CCRect thumbFileRect,
		CCSpriteFrame *thumbFrameSelect,CCRect thumbSelectFileRect,
		CCSpriteFrame *btnLTFrame,CCRect btnLTRect,
		CCSpriteFrame *btnRBFrame,CCRect btnRBRect,
		CCSize btnSize,
		bool bHorizontal=true);

	static SIX_ScrollBar* create(
		const char *bgFile,CCRect bgFileRect,CCSize bgSize,
		const char *progressFile,CCRect progressFileRect,
		const char *thumbFile,CCRect thumbFileRect,
		const char *thumbSelectFile,CCRect thumbSelectFileRect,
		const char *btnLTFile,CCRect btnLTRect,
		const char *btnRBFile,CCRect btnRBRect,
		CCSize btnSize,
		bool bHorizontal=true);

	static SIX_ScrollBar* create(CCScale9Sprite *backgroundSprite,CCSize bg,CCSprite *progressSprite,CCScale9Sprite *thumbSprite,CCScale9Sprite *thumbSpriteSelect,CCScale9Sprite *btnLT,CCScale9Sprite *btnRB,CCSize btnSize,bool bHorizontal=true);

	virtual bool initWithSprites(CCScale9Sprite *backgroundSprite,CCSize bg,CCSprite *progressSprite,CCScale9Sprite *thumbSprite,CCScale9Sprite *thumbSpriteSelect,CCScale9Sprite *btnLT,CCScale9Sprite *btnRB,CCSize btnSize);
public:
	virtual void setSlider(SIX_Slider *slider);
	virtual SIX_Slider *getSlider(void) const;

	virtual void setBtnLT(CCControlButton *btnLT);
	virtual CCControlButton *getBtnLT(void) const;

	virtual void setBtnRB(CCControlButton *btnRB);
	virtual CCControlButton *getBtnRB(void) const;

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	// 滚动条回调
	virtual void ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent);
public:
	void setHorizontal(bool bHorizontal=true);
	bool getHorizontal();

	void setValue(float value);
	float getValue();
	
	void setMinimumValue(float minimumValue);
	float getMinimumValue();

	void setMaximumValue(float maximumValue);
	float getMaximumValue();

	void setMinimumAllowedValue(float minimumAllowedValue);
	float getMinimumAllowedValue();

	void setMaximumAllowedValue(float maximumAllowedValue);
	float getMaximumAllowedValue();

	void setScrollStep(float fScrollStep);
	float getScrollStep();
private:
	// 背景
	SIX_Slider *m_Slider;
	// 左/上按钮
	CCControlButton *m_BtnLT;
	// 右/下按钮
	CCControlButton *m_BtnRB;
	// 步进
	float m_fScrollStep;
	// 默认横向
	bool m_bHorizontal;
};
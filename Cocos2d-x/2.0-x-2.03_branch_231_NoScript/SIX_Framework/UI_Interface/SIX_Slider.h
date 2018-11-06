/***********************************************
Name：SIX_Slider
Desc：SIX_Slider
Auth：Cool.Cat@2013-04-28
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_Slider: public CCControlButton
{
public:
    SIX_Slider();
    virtual ~SIX_Slider();
    virtual bool initWithSprites(CCScale9Sprite * backgroundSprite, CCSize backgroundSize,CCSprite* progressSprite, CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSpriteSelect=0);
    static SIX_Slider* sliderWithFiles(const char* bgFile, CCSize backgroundSize,const char* progressFile, const char* thumbFile);
    static SIX_Slider* sliderWithSprites(CCScale9Sprite * backgroundSprite, CCSize backgroundSize,CCSprite* pogressSprite, CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSpriteSelect=0);
    static SIX_Slider* create(const char* bgFile, CCSize backgroundSize,const char* progressFile, const char* thumbFile);
    static SIX_Slider* create(CCScale9Sprite * backgroundSprite, CCSize backgroundSize,CCSprite* pogressSprite, CCScale9Sprite* thumbSprite,CCScale9Sprite *thumbSpriteSelect=0);

    virtual void needsLayout();
public:
    void sliderBegan(CCPoint location);
    void sliderMoved(CCPoint location);
    void sliderEnded(CCPoint location);

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    float valueForLocation(CCPoint location);

public:
    virtual void setEnabled(bool enabled);
    virtual bool isTouchInside(CCTouch * touch);
    CCPoint locationFromTouch(CCTouch* touch);

    void setValue(float Value,bool NeedNotify=true);
	float getValue();

	void setMinimumValue(float MinimumValue);
	float getMinimumValue();

	void setMaximumValue(float MaximumValue);
	float getMaximumValue();

	void setMinimumAllowedValue(float MinimumAllowedValue);
	float getMinimumAllowedValue();

	void setMaximumAllowedValue(float MaximumAllowedValue);
	float getMaximumAllowedValue();

	void setThumbSprite(CCScale9Sprite *ThumbSprite);
	CCScale9Sprite *getThumbSprite();

	void setThumbSpriteSelect(CCScale9Sprite *ThumbSpriteSelect);
	CCScale9Sprite *getThumbSpriteSelect();

	void setProgressSprite(CCSprite *ProgressSprite);
	CCSprite *getProgressSprite();

	void setBackgroundSprite(CCScale9Sprite *BackgroundSprite);
	CCScale9Sprite *getBackgroundSprite();

protected:
	float m_value;
	float m_valueLast;
    float m_minimumValue;
	float m_maximumValue;
	float m_minimumAllowedValue;
	float m_maximumAllowedValue;

private:
	CCScale9Sprite *m_backgroundSprite;
	CCSprite *m_progressSprite;
	CCScale9Sprite *m_thumbSprite;
	// 增加滑块选中态
	// Cool.Cat
	CCScale9Sprite *m_thumbSpriteSelect;
};
/***********************************************
Name��SIX_ScrollBar
Desc��SIX_ScrollBar
Auth��Cool.Cat@2013-04-28
***********************************************/
#pragma once
#include <cocos2d.h>
#include "SIX_Typedef.h"
#include "cocos-ext.h"
#include "SIX_UILayer.h"
#include "SIX_ListViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_ScrollBar:public CCControl
{
public:
	SIX_ScrollBar();
	virtual ~SIX_ScrollBar();
public:
	static SIX_ScrollBar* create(
		const char *backgroundFile,CCRect backgroundRect,CCRect backgroundDstRect,
		const char *btnLTFile,CCRect btnLTRect,
		const char *btnRBFile,CCRect btnRBRect,
		const char *thumbFile,CCRect thumbRect,
		bool bHorizontal=true);

	static SIX_ScrollBar* create(CCScale9Sprite *background,CCRect backgroundDstRect,CCSprite *btnLT,CCSprite *btnRB,CCScale9Sprite* thumb,bool bHorizontal=true);

	virtual bool initWithSprites(CCScale9Sprite * background,CCRect backgroundDstRect,CCSprite *btnLT, CCSprite *btnRB,CCScale9Sprite* thumb);

	virtual bool isTouchInside(CCTouch * touch);
	CCPoint locationFromTouch(CCTouch* touch);

	virtual void needsLayout();
public:
	virtual void setBackground(CCScale9Sprite *background);
	virtual CCScale9Sprite *getBackground(void) const;

	virtual void setBtnLT(CCSprite *btnLT);
	virtual CCSprite *getBtnLT(void) const;

	virtual void setBtnRB(CCSprite *btnRB);
	virtual CCSprite *getBtnRB(void) const;

	virtual void setThumb(CCScale9Sprite *thumb);
	virtual CCScale9Sprite *getThumb(void) const;
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

	void setThumbRect(CCRect rc);
	CCRect getThumbRect();
protected:
	void sliderBegan(CCPoint location);
	void sliderMoved(CCPoint location);
	void sliderEnded(CCPoint location);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	float valueForLocation(CCPoint location);
private:
	// ����
	CCScale9Sprite *m_Background;
	// ��/�ϰ�ť
	CCSprite *m_BtnLT;
	// ��/�°�ť
	CCSprite *m_BtnRB;
	// ����
	CCScale9Sprite *m_Thumb;

	// Ĭ�Ϻ���
	bool m_bHorizontal;
	// ��������
	CCRect m_ThumbRect;

	// ��ǰ����ֵ
	float m_value;
	// ���/��Сֵ
	float m_minimumValue;
	float m_maximumValue;
	// ��������/��Сֵ
	float m_minimumAllowedValue;
	float m_maximumAllowedValue;
};
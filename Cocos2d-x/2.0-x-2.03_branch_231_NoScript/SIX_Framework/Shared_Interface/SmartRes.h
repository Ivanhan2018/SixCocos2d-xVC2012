#ifndef __SMART_RES_H_
#define __SMART_RES_H_

#include "cocos2d.h"
NS_CC_BEGIN;

#define _center     SmartRes::sharedRes()->getCenter()
#define _top        SmartRes::sharedRes()->getTop()
#define _right      SmartRes::sharedRes()->getRight()
#define _bottom     SmartRes::sharedRes()->getBottom()
#define _left       SmartRes::sharedRes()->getLeft()
#define _scale      SmartRes::sharedRes()->getScale()
#define _xy(v)      SmartRes::sharedRes()->xy(v)
#define _ptRatio(x,y)      SmartRes::sharedRes()->ptRatio(x,y)

class SmartRes
{
public:
	static SmartRes* sharedRes(void);

	// 设定虚拟屏幕的宽度
	void setVirtualScreenWidth(float width, float height);

	const cocos2d::CCSize getScreenSize(void) {
		return m_screenSize;
	}

	float getScale(void) {
		return m_scale;
	}

	const cocos2d::CCPoint getCenter(void) {
		return m_center;
	}

	float getTop(void) {
		return m_top;
	}

	float getRight(void) {
		return m_right;
	}

	float getBottom(void) {
		return m_bottom;
	}

	float getLeft(void) {
		return m_left;
	}

	float xy(float v) {
		return m_scale * v;
	}

	CCPoint ptRatio(const float &fWidth, const float &fHeight)
	{
		if (0.0001 >= m_designSize.width  ||  0.0001 >= m_designSize.height)
		{
			CCLOG("Error 0.0001 >= m_designSize.width  ||  0.0001 >= m_designSize.height  (%f,%f)", m_designSize.width, m_designSize.height);
			return CCPoint(fWidth,fHeight);
		}
		return CCPoint(fWidth/m_designSize.width*m_screenSize.width, fHeight/m_designSize.height*m_screenSize.height);
	}

private:
	SmartRes(void)
		: m_scale(1.0f)
		, m_top(0)
		, m_right(0)
		, m_bottom(0)
		, m_left(0)
	{
	}
	bool init(void);

	static SmartRes* s_sharedRes;

	cocos2d::CCSize m_designSize;
	cocos2d::CCSize m_screenSize;
	cocos2d::CCPoint m_center;
	float m_scale;
	float m_top;
	float m_right;
	float m_bottom;
	float m_left;
};

NS_CC_END;
#endif
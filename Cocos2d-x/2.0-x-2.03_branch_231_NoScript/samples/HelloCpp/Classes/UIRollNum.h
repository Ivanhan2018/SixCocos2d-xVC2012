#ifndef __UIROLLNUM_H__
#define __UIROLLNUM_H__

#include "cocos2d.h"
#include "UINumber.h"

class UIRollNum : public cocos2d::CCSprite {
public:
	~UIRollNum();
	bool init();

	static UIRollNum* getOne();

	void rebuildEffect();
	void clearEffect();
	int getNumber();
	void setNumber(int num);

	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, numArray, NumArray);
	CC_SYNTHESIZE(cocos2d::CCPoint, m_point, Point);
	CC_SYNTHESIZE(NUM_STYLE, style, Style);

private:
	int m_nNumber;
	int m_maxCol;
	bool zeroFill;

};


#endif
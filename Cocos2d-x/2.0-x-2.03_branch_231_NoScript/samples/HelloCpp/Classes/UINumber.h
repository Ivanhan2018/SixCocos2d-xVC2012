#ifndef __UINUMBER_H__
#define __UINUMBER_H__

#include "cocos2d.h"
#include "SIX_Common.h"

#define NUM_HEIGHT 20
#define NUM_WIDTH  20

ENUM_BEGIN(NUM_STYLE)
	NumStyleNormal=0,
	NumStyleSameTime,
ENUM_END()

class UINumber : public cocos2d::CCSprite {
public:
	~UINumber();
	static UINumber* numberWithStyle(NUM_STYLE style);

	bool init();
	bool initWithStyle(NUM_STYLE style);

	void setNumber(int num);
	void onRollDown(float dt);
	void onRollUp(float dt);
	void setup();

	CC_SYNTHESIZE_RETAIN(cocos2d::CCTexture2D*, m_texture, M_Texture);

private:
	NUM_STYLE m_style;
	int m_num;
	int m_nPosCur;
	int m_nPosEnd;
	int m_nMoveLen;
};

#endif
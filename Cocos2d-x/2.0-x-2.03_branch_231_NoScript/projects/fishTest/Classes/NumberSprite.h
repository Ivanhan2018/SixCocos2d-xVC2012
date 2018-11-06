#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class NumberSprite :
	public cocos2d::CCSprite
{
public:
	NumberSprite(CCTexture2D *pTexture, CCSize size);
	~NumberSprite(void);
	void setValue(int v, bool isShow = true);

private:
	CCSize size;
	CCRect rect;
};

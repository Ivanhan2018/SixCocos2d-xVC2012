#ifndef __CCNET_H__
#define __CCNET_H__

#include "cocos2d.h"

class CCNet : public cocos2d::CCSprite 
{
public:
	static CCNet* spriteWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame)
	{
		CCNet *pobSprite = new CCNet();
		if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
		{
			pobSprite->autorelease();
			return pobSprite;
		}
		CC_SAFE_DELETE(pobSprite);
		return NULL;
	}

	static CCNet* spriteWithSpriteFrameName(const char *pszSpriteFrameName)
	{
		cocos2d::CCSpriteFrame *pFrame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

		char msg[256] = {0};
		sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
		CCAssert(pFrame != NULL, msg);
		return spriteWithSpriteFrame(pFrame);
	}

	CC_SYNTHESIZE(bool, isCatching, IsCatching);
};

#endif
#ifndef __CCFISH_H__
#define __CCFISH_H__

#include "cocos2d.h"

typedef enum 
{
	FishNoraml = 0,
	FishGold,
	FishShark
} FishType;

class CCFish : public cocos2d::CCSprite {
public:

	static CCFish* spriteWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame);
	static CCFish* spriteWithSpriteFrameName(const char *pszSpriteFrameName);

	bool randomCatch(int level);
	void addPath();
	void moveWithParabola(cocos2d::CCSprite* mSprite, cocos2d::CCPoint startP, cocos2d::CCPoint endP,
				float startAngle, float endAngle, float time);


	CC_SYNTHESIZE(bool, isCatch, IsCatch);

private:
	FishType type;
	cocos2d::CCAction* path;

	void removeSelf();

};

#endif
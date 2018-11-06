#include "CCFish.h"

using namespace cocos2d;

CCFish* CCFish::spriteWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame)
{
	CCFish *pobSprite = new CCFish();
	if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFish* CCFish::spriteWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
	return spriteWithSpriteFrame(pFrame);
}

bool CCFish::randomCatch(int level)
{
	if(rand() % 10 >= level){
		isCatch = true;
	}else{
		isCatch = false;
	}
	return isCatch;
}

void CCFish::addPath()
{
	switch(rand() % 7)
	{
		case 0:
			this->moveWithParabola(this, ccp(1200, 200), ccp(-500, 800), 0.0f, 20.0f, rand()%10+15);
			break;
		case 1:
			this->moveWithParabola(this, ccp(-200, 300), ccp(1300, 400), 180.0, 170.0, rand()%10+18);
			break;
		case 2:
			this->moveWithParabola(this, ccp(-200, 300), ccp(1000, -200), 190.0, 200.0, rand()%10+18);
			break;
		case 3:
			this->moveWithParabola(this, ccp(1300, 400), ccp(-200, 300), 10.0, 5.0, rand()%10+18);
			break;
		case 4:
			this->moveWithParabola(this, ccp(400, -1200), ccp(600, 1000), 90.0, 93.0, rand()%10+18);
			break;
		case 5:
			this->moveWithParabola(this, ccp(600, 1000), ccp(400, -200), -70.0, -80.0, rand()%10+18);
			break;
		case 6:
			this->moveWithParabola(this, ccp(1200, 2100), ccp(-200, 300), 30.0, -30.0, rand()%10+18);
			break;
	}
}

void CCFish::moveWithParabola(cocos2d::CCSprite* mSprite, cocos2d::CCPoint startP, cocos2d::CCPoint endP, float startAngle, float endAngle, float time)
{
	float sx = startP.x;
	float sy = startP.y; 
	float ex =endP.x+rand()%50;
	float ey =endP.y+rand()%150; 

	float h = mSprite->getContentSize().height * 0.5f;
	CCPoint pos = CCPointMake(sx - 200 + rand()%400, sy -200 + rand() %400);
	mSprite->setPosition(pos);
	mSprite->setRotation(startAngle);

	// 贝塞尔曲线
	ccBezierConfig bezier;
	// 控制点1(起点)
	bezier.controlPoint_1 = ccp(sx, sy);
	// 控制点2
	bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5+rand()%300);
	// 终点
	bezier.endPosition = ccp(endP.x-30, endP.y+h);

	CCBezierTo* actionMove = CCBezierTo::actionWithDuration(time, bezier);
	CCRotateTo* actionRotate = CCRotateTo::actionWithDuration(time, endAngle);
	CCFiniteTimeAction* action = CCSpawn::actions(actionMove, actionRotate, 0);
	CCFiniteTimeAction* sq = CCSequence::actions(action,CCCallFunc::actionWithTarget(this, callfunc_selector(CCFish::removeSelf)), 0);
	mSprite->runAction(sq);
}

void CCFish::removeSelf()
{
	this->removeFromParentAndCleanup(true);
}
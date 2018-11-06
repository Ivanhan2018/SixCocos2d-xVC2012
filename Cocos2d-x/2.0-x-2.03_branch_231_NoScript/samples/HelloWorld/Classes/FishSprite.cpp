#include "FishSprite.h"

using namespace cocos2d;

static int d_Fish_Plist_File_Count = 1;			// 鱼文件数目
static int d_Fish_Frame_Count = 10;				// 鱼游动帧
CCSpriteBatchNode * CFashManage::s_AllFish = NULL;

FishSprite* FishSprite::createWithSpriteFrame(cocos2d::CCSpriteFrame *pSpriteFrame)
{
	FishSprite *pobSprite = new FishSprite();
	if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

FishSprite* FishSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
	return createWithSpriteFrame(pFrame);
}

bool FishSprite::randomCatch(int level)
{
	if(rand() % 10 >= level){
		isCatching = true;
	}else{
		isCatching = false;
	}
	return isCatching;
}

void FishSprite::addPath()
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

void FishSprite::moveWithParabola(cocos2d::CCSprite* mSprite, cocos2d::CCPoint startP, cocos2d::CCPoint endP, float startAngle, float endAngle, float time)
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

	CCBezierTo* actionMove = CCBezierTo::create(time, bezier);
	CCRotateTo* actionRotate = CCRotateTo::create(time, endAngle);
	CCFiniteTimeAction* action = CCSpawn::create(actionMove, actionRotate, 0);
	CCFiniteTimeAction* sq = CCSequence::create(action,CCCallFunc::create(this, callfunc_selector(FishSprite::removeSelf)), 0);
	mSprite->runAction(sq);
}

void FishSprite::removeSelf()
{
	this->removeFromParentAndCleanup(true);
}

//////////////////////////////////////////////////////////////////////////
/// CFishManage

void CFashManage::Init(CCNode * pNode)
{
	if (NULL == s_AllFish)
	{
		for (int i=0; i<d_Fish_Plist_File_Count; i++)
		{
			CCString *pListName = CCString::createWithFormat("./play/fish%02d%s",i+1,".plist");
			CCString *pBatchName = CCString::createWithFormat("./play/fish%02d%s",i+1,".png");
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pListName->getCString());
			s_AllFish = CCSpriteBatchNode::create(pBatchName->getCString());
			pNode->addChild( s_AllFish );
		}
	}

	while(NULL != s_AllFish && sharedFish()->getChildren()->count() < d_Fish_Max_Count)
	{
		// 鱼种
		FishSprite::Fish_Type fishTytpe = (FishSprite::Fish_Type)(rand() % (FishSprite::Fish_Type_Count-1) + 1);
		addOneFish( fishTytpe );
	}
}

void CFashManage::Release()
{
	if (NULL != s_AllFish)
	{
		for (int i=0; i<d_Fish_Plist_File_Count; i++)
		{
			CCString *pListName = CCString::createWithFormat("./play/fish%02d%s",i+1,".plist");
			CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile( pListName->getCString() );
		}

		s_AllFish->removeAllChildrenWithCleanup(true);//removeAllChildren();
	}
}

void CFashManage::addOneFish(FishSprite::Fish_Type eType/*=Fish_1*/)
{
	if (NULL == s_AllFish)
		CCAssert(0, "请先调用 CFashManage::Init(...) 函数初始化");

	char charBuffer[256] = {0};
	CCArray* fish01 = CCArray::create();

	// 鱼帧
	for(int i = 1; i < d_Fish_Frame_Count; i++)
	{
		memset(charBuffer, 0, sizeof(charBuffer));
		_snprintf(charBuffer, sizeof(charBuffer), "fish0%d_0%d.png", eType, i);
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(charBuffer);
		fish01->addObject(spriteFrame);
	}

	// 由帧缓存生成action，帧延迟0.1f
	CCActionInterval * pFishAction = CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(fish01, 0.1f)));
	// 通过起始帧生成鱼实体
	FishSprite* fish = FishSprite::createWithSpriteFrameName(CCString::createWithFormat("fish0%d_0%d.png", eType, 1)->getCString());
	fish->setIsCatching( false );
	fish->setTag( eType );
	fish->runAction( pFishAction );
	fish->addPath();
	s_AllFish->addChild( fish );
}

CCSpriteBatchNode * CFashManage::sharedFish()
{
	if (NULL == s_AllFish)
		CCAssert(0, "请先调用 CFashManage::Init(...) 函数初始化");

	return s_AllFish;
}
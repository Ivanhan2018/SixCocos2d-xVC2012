#include "LoadingLayer.h"
#include "HallLayer.h"

static int sp_ProcessBar_Tag = 0;
static int sp_ProcessAnimation_Tag = 1;

LoadingLayer::LoadingLayer(void)
{
}


LoadingLayer::~LoadingLayer(void)
{
}

void LoadingLayer::setProcessBar(float time, float fPercentage)
{
	static float fSavePercentage = 0.0f;
	if (100 < fPercentage)
		fPercentage = 100;
	else if (0 > fPercentage)
		fPercentage = 0;
	if (fSavePercentage > fPercentage)
		fSavePercentage = 0.0f;

	CCNode * pProgress = getChildByTag( sp_ProcessBar_Tag );
	CCAction * pProgressAction = CCProgressFromTo::create(time, fSavePercentage, fPercentage);
	pProgress->runAction( (CCActionInterval *)pProgressAction );

	CCNode * spriteProcess = pProgress->getChildByTag( sp_ProcessAnimation_Tag );
	const CCSize sizeProgress = pProgress->getContentSize();
	// 根据百分比计算进度条实际滚动的距离
	int nX = sizeProgress.width/100*(fPercentage-fSavePercentage);
	if ( 100 == fPercentage)
		nX -= 15;
	CCMoveBy * move = CCMoveBy::create(time, ccp(nX, 0));
	spriteProcess->runAction( move );

	fSavePercentage = fPercentage;
}

void LoadingLayer::LoadComplete(float fTime)
{
	unschedule( schedule_selector(LoadingLayer::LoadComplete) );
	HallLayer::scene();
}

void LoadingLayer::onEnter()
{
	CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCSprite * bg = CCSprite::create("bg/bg.jpg");
	bg->setPosition(ccp(s.width/2, s.height/2));
	addChild(bg);

	CCLabelTTF * loadPrompt = CCLabelTTF::create("Loading. . .", "宋体", 40);
	loadPrompt->setPosition(ccp(s.width/2, s.height/4));
	addChild(loadPrompt);

	// 进度条
	CCSprite * pProgressbarBGFrame = CCSprite::create("progressbar1.png");
	pProgressbarBGFrame->setPosition(ccp(s.width/2, s.height/2));
	addChild(pProgressbarBGFrame);
	CCSprite * pProgressbarBG = CCSprite::create("progressbar2.png");
	pProgressbarBG->setPosition(ccp(s.width/2, s.height/2));
	addChild(pProgressbarBG);
	CCProgressTimer * pProgress = CCProgressTimer::create(CCSprite::create("progressbar3.png"));
	pProgress->setType(kCCProgressTimerTypeBar);
	pProgress->setPosition( ccp(s.width/2, s.height/2) );
	pProgress->setMidpoint(ccp(0, 0));
	pProgress->setBarChangeRate(ccp(1, 0));
	addChild( pProgress, 1, sp_ProcessBar_Tag );
	
	// 进度条动画
	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("progressAnimation.PNG");
	int nSpriteWidth = 352, nSpriteHeight = 288, nObject = 4;
	CCArray *animFrames = CCArray::createWithCapacity( nObject );
	CCSpriteFrame * spriteFrame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0,0,352,288));
	animFrames->addObject( spriteFrame );
	animFrames->addObject( CCSpriteFrame::createWithTexture(texture, CCRectMake(nSpriteWidth,0,352,288)) );
	animFrames->addObject( CCSpriteFrame::createWithTexture(texture, CCRectMake(nSpriteWidth*2,0,352,288)) );
	animFrames->addObject( CCSpriteFrame::createWithTexture(texture, CCRectMake(nSpriteWidth*3,0,352,288)) );
	CCAnimation * animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	CCAnimate * animate = CCAnimate::create( animation );
	CCSprite * spriteProcess = CCSprite::createWithSpriteFrame( spriteFrame );
	spriteProcess->setPosition( ccp(10, 25) );
	spriteProcess->runAction( CCRepeatForever::create( animate ) );
	pProgress->addChild( spriteProcess, 2, sp_ProcessAnimation_Tag );

	float fTime = 3.0f;
	setProcessBar(fTime, 100);//del
	schedule( schedule_selector(LoadingLayer::LoadComplete), fTime );
}

void LoadingLayer::onExit()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

//void LoadingLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)//del
//{
//	static int aa=0;
//	aa+=rand()%101;
//	if (aa > 100)
//		aa = 100;
//	setProcessBar(3.0f, aa);
//	return;
//}

void LoadingLayer::scene()
{
	CCScene * pScene = CCScene::create();
	LoadingLayer * pLoading = new LoadingLayer;
	pScene->addChild( pLoading );
	pLoading->release();

	CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.0f, pScene, ccBLACK) );
}
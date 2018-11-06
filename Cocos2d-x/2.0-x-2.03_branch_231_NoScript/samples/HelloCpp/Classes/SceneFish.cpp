#include "SceneFish.h"
#include <SIX_Common.h>
#include <SIX_GlobalMgr.h>

USING_NS_CC;
USING_GLOBALMGR;

CCScene* SceneFish::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SceneFish *layer = SceneFish::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneFish::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// 背景
    CCSprite* pSprite = CCSprite::create("./Scene/Scene01.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite);

	// 关闭
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("./CloseNormal.png","./CloseSelected.png",this,menu_selector(SceneFish::menuCallback));
	pCloseItem->setTag(ENUM_BTNIDX::BTN_CLOSE);
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width,origin.y + pCloseItem->getContentSize().height/2));
    CCMenu* pMenu = CCMenu::create(pCloseItem, 0);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

	// 音乐图标
    pMusicItem = CCMenuItemImage::create("./music_on.png","./music_on.png",this,menu_selector(SceneFish::menuCallback));
	pMusicItem->setTag(ENUM_BTNIDX::BTN_MUSIC_ON);
    pMusicItem->setPosition(ccp(origin.x + visibleSize.width - pMusicItem->getContentSize().width - pCloseItem->getContentSize().width,origin.y + pMusicItem->getContentSize().height/2));
    pMenu = CCMenu::create(pMusicItem, 0);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

	CCString text(UT->G2U("游戏场景01\n鱼群AI、场景切换、音效演示"));
	CCLabelTTF* pLabel = CCLabelTTF::create(text.getCString(), "微软雅黑", 24);
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,500));
	pLabel->setColor(ccc3(255,0,0));
    this->addChild(pLabel, 1);

    // enable standard touch
    this->setTouchEnabled(true);

    energy = 0;
	maxEnergy = 1000;
	m_LastShootTime = ::timeGetTime();

	// do sth
	this->InitUITab();
	this->LoadTexture();
	srand(time(NULL));

	while(fishSheet[0]->getChildren()->count() < MAX_ENEMY)
	{
		this->AddFish();
	}

	SIXLog("Fish.Count = %d/%d",fishSheet[0]->getChildrenCount(),fishSheet[0]->getChildren()->count());

	this->schedule(schedule_selector(SceneFish::Update), 0.05f);
    
    return true;
}

void SceneFish::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)(* pTouches->begin());
    CCPoint pos = touch->getLocation();
    
    SIXLog("touch, x = %f, y = %f", pos.x, pos.y);

	CCSetIterator iter = pTouches->begin();
	for(; iter != pTouches->end(); iter++)
	{
		CCTouch* pTouch = (CCTouch*)*iter;
		Shooting(pTouch);
	}
}

void SceneFish::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCSetIterator iter = pTouches->begin();
	for(; iter != pTouches->end(); iter++)
	{
		CCTouch *pTouch = (CCTouch*)*iter;
		//Shooting(pTouch);
	}
}

// 鼠标按住不放时一直发射子弹
// Cool.Cat
void SceneFish::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	Shooting(pTouch);
	//SIXLog("ccTouchesMoved.pos[%.2f/%.2f] , location[%.2f/%.2f]", pos.x, pos.y,location.x,location.y);
}

// 发射函数
void SceneFish::Shooting(CCTouch *pTouch)
{
	// 子弹间隔延迟控制
	DWORD now = ::timeGetTime();
	if (now<m_LastShootTime+MAX_SHOOT_DELAY)
		return;

	CCPoint pos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());

	if(pos.y < floor)
		return;

	m_LastShootTime = now;

	gun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_72.png"));

	// 设置炮台旋转
	float angle = (pos.y - gun->getPosition().y)/(pos.x - gun->getPosition().x);
	angle = atanf(angle)/M_PI*180;
	if(angle < 0)
	{
		SIXLog("A1.angle=%.2f",angle);
		gun->setRotation(-90-angle);
		SIXLog("A2.angle=%.2f",-90-angle);
	}
	else if(angle > 0)
	{
		SIXLog("B1.angle=%.2f",angle);
		gun->setRotation(90-angle);
		SIXLog("B2.angle=%.2f",90-angle);
	}

	gun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_71.png"));

	// 扣除子弹
	score1->setNumber(score1->getNumber()-1);
	
	CCNet* pBullet = CCNet::spriteWithSpriteFrameName("bullet_1_00000.png");

	// 子弹旋转
	pBullet->setRotation(gun->getRotation()+90.0);

	// 子弹起点
	pBullet->setPosition(ccp(530, 50));
	pBullet->setIsCatching(true);

	// 子弹帧缓存
	CCArray* bulletArray = CCArray::array();
	char charBuffer[MAX_PATH] = {0};
	for (int i=0;i<10;i++)
	{
		memset(charBuffer, 0, sizeof(charBuffer));
		sprintf(charBuffer, "bullet_1_%05d.png", i);
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(charBuffer);
		bulletArray->addObject(spriteFrame);
	}

	// 绑定子弹自身帧动画
	CCAnimate *pSelf = CCAnimate::actionWithAnimation(CCAnimation::animationWithSpriteFrames(bulletArray, 0.1f));

	// 自身动作
	CCRepeatForever* bullet_act = CCRepeatForever::actionWithAction(pSelf);
	pBullet->runAction(bullet_act);
	
	// 子弹移动到终点
	CCMoveTo* move = CCMoveTo::actionWithDuration(1.0f, pos);
	// 子弹到达终点时回调鱼网动作
	CCFiniteTimeAction* netSequence = CCSequence::actions(move,CCCallFuncO::actionWithTarget(this, callfuncO_selector(SceneFish::showNet), pBullet), 0);
	pBullet->runAction(netSequence);

	// 增加随机能量
	this->updateEnergry(rand() % 20);

	// 保存起来，在update中计算碰撞
	fishSheet[1]->addChild(pBullet);
}

void SceneFish::InitUITab()
{
	// 鱼
	for (int i=0;i<1;i++)
	{
		CCString *pListName = CCString::stringWithFormat("./action/fish%02d%s",i+1,".plist");
		CCString *pFrameName = CCString::stringWithFormat("./action/fish%02d%s",i+1,".png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pListName->getCString());
		fishSheet[i] = CCSpriteBatchNode::batchNodeWithFile(pFrameName->getCString());
		this->addChild(fishSheet[i]);
	}

	// 网
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./action/net/net.plist");
	netSheet = CCSpriteBatchNode::batchNodeWithFile("./action/net/net.png");
	this->addChild(netSheet);

	// 能量条外圈
	CCSprite* engryRing = CCSprite::create("energy_ring.png");
	engryRing->setPosition(ccp(520,30));
	this->addChild(engryRing);

	// 能量条指针
	energyPtr = CCSprite::create("energy_ptr.png");
	energyPtr->setPosition(ccp(520,30));
	this->addChild(energyPtr);

	//// 顶部UI
	//CCSprite* bgExp = CCSprite::create("top.png");
	//bgExp->setPosition(ccp(500, 564));
	//this->addChild(bgExp);

	// 底部UI
	CCSprite* bgNum = CCSprite::create("bottom.png");
	bgNum->setPosition(ccp(440,90));
	this->addChild(bgNum);

	// 金币
	score1 = UIRollNum::getOne();
    score1->setNumber(10000);
	score1->setPosition(ccp(365, 17));
	this->addChild(score1, 100);

	// 子弹
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./action/bullet/bullet.plist");
	fishSheet[1] = CCSpriteBatchNode::batchNodeWithFile("./action/bullet/bullet.png");
	this->addChild(fishSheet[1]);

	// 炮台
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("./action/cannon.plist");
	cannonSheet = CCSpriteBatchNode::batchNodeWithFile("./action/cannon.png");
	this->addChild(cannonSheet,1000);

	gun = CCSprite::spriteWithSpriteFrameName("actor_cannon1_71.png");
	gun->setPosition(ccp(520, 50));
	gun->setAnchorPoint(ccp(0.5,0.5));
	cannonSheet->addChild(gun);
	floor = gun->getPosition().y;
}

void SceneFish::LoadTexture()
{
}

void SceneFish::AddFish()
{
	// 鱼种
	int fishType = rand() % (MAX_FISH_TYPECOUNT-1) + 1;
	char charBuffer[256] = {0};
	CCArray* fish01 = CCArray::array();

	// 鱼帧
	for(int i = 1; i < MAX_FISH_FRAMECOUNT; i++)
	{
		memset(charBuffer, 0, sizeof(charBuffer));
		sprintf(charBuffer, "fish0%d_0%d.png", fishType, i);
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(charBuffer);
		fish01->addObject(spriteFrame);
	}

	// 由帧缓存生成action，帧延迟0.1f
	fish01_act = CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithSpriteFrames(fish01, 0.1f)));
	// 通过起始帧生成鱼实体
	CCFish* fish = CCFish::spriteWithSpriteFrameName(CCString::stringWithFormat("fish0%d_0%d.png", fishType, 1)->getCString());
	fish->setScale(1.0f);
	// 概率
	fish->setTag(fishType);
	fish->setIsCatch(false);
	fish->runAction(fish01_act);
	fish->addPath();
	fishSheet[0]->addChild(fish);
}

void SceneFish::Update(float dt)
{
	CCObject* sprite;
	CCObject* net;
	CCScaleTo* scale0 = CCScaleTo::actionWithDuration(0.3f, 1.1f);
	CCScaleTo* scale1 = CCScaleTo::actionWithDuration(0.3f, 0.9f);

	CCARRAY_FOREACH(fishSheet[0]->getChildren(), sprite)
	{
		CCFish* fish = (CCFish*)sprite;
		if(fish->getIsCatch())
			continue;

		CCARRAY_FOREACH(fishSheet[1]->getChildren(), net)
		{
			CCNet* netx = (CCNet*)net;
			if(CCRect::CCRectContainsPoint(fish->boundingBox(), netx->getPosition()))
			{
				// 概率控制
				if(!fish->randomCatch(fish->getTag()))
				{
					netx->setIsCatching(false);
					break;
				}
				else
				{
					// 鱼被捕获
					fish->setIsCatch(true);

					// 效果3帧
					CCArray* fish01 = CCArray::array();
					for(int i = 1; i < 3; i++)
					{
						fish01->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::stringWithFormat("fish0%d_catch_0%d.png",fish->getTag(),i)->getCString()));
					}
					CCRepeat* fish01_catch_act = CCRepeat::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithSpriteFrames(fish01, 0.2f)), 2);
					CCFiniteTimeAction* fishSequence = CCSequence::actions(fish01_catch_act, CCCallFuncO::actionWithTarget(this, callfuncO_selector(SceneFish::afterCatch), fish), 0);
					fish->stopAllActions();
					fish->runAction(fishSequence);

					PlayFishHit();

					// 金币效果
					CCSprite* gold = CCSprite::spriteWithFile("+5.png");
					gold->setPosition(fish->getPosition());

					CCFiniteTimeAction* goldSequence = CCSequence::actions(scale0, scale1, scale0, scale1, CCCallFuncO::actionWithTarget(this, callfuncO_selector(SceneFish::afterShow), gold), 0);
					gold->runAction(goldSequence);
					this->addChild(gold);
				}
			}
		}
	}

	CCARRAY_FOREACH(fishSheet[1]->getChildren(), net)
	{
		CCNet* netx = (CCNet*)net;
		if(netx->getIsCatching())
			continue;

		// 这个地方有问题BUG，remove不存在的子对象时会崩溃，已修正
		// Cool.Cat
		if (fishSheet[1]->getChildren()->containsObject(netx))
			fishSheet[1]->removeChild(netx, false);

		// 碰撞到鱼后，显示网的动态缩放效果
		//CCNet* tapnet = CCNet::spriteWithSpriteFrameName("net01.png");
		CCNet* tapnet = CCNet::spriteWithSpriteFrameName("1_00000.png");
		tapnet->setPosition(netx->getPosition());
		CCFiniteTimeAction* netSequence = CCSequence::actions(scale0, scale1, scale0, scale1, CCCallFuncO::actionWithTarget(this, callfuncO_selector(SceneFish::afterShowNet), tapnet), 0);
		tapnet->runAction(netSequence);
		netSheet->addChild(tapnet);

		score1->setNumber(score1->getNumber()+5);
	}

	while(fishSheet[0]->getChildren()->count()<MAX_ENEMY)
	{
		this->AddFish();
	}
}

void SceneFish::showNet(cocos2d::CCObject* pSender)
{
	CCNet* sp = (CCNet*)pSender;
	
	// 子弹到达终点后要停止所有动作，因为CCRepeatForever，否则会造成崩溃。。。
	// Cool.Cat
	sp->stopAllActions();

	fishSheet[1]->removeChild(sp, false);

	//sp->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("net01.png"));
	sp->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("1_00000.png"));

	CCScaleTo* scale0 = CCScaleTo::actionWithDuration(0.3f, 1.1f);
	CCScaleTo* scale1 = CCScaleTo::actionWithDuration(0.3f, 0.9f);

	CCFiniteTimeAction* netSequence = CCSequence::actions(scale0, scale1, scale0, scale1, CCCallFuncO::actionWithTarget(this, callfuncO_selector(SceneFish::afterShowNet), sp), 0);

	sp->runAction(netSequence);
	netSheet->addChild(sp);
}

void SceneFish::afterShowNet(cocos2d::CCObject* pSender)
{
	CCNet* sp = (CCNet*)pSender;
	netSheet->removeChild(sp, false);
}

void SceneFish::afterShow(cocos2d::CCObject* pSender)
{
	CCNet* sp = (CCNet*)pSender;
	this->removeChild(sp, false);
}

void SceneFish::afterCatch(cocos2d::CCObject* pSender)
{
	CCNet* sp = (CCNet*)pSender;
	fishSheet[0]->removeChild(sp, false);
}

void SceneFish::updateEnergry(int en)
{
	energy += en;
	if(energy > maxEnergy){
		energy = maxEnergy;
	}
	float rotation = 180.0f * energy / maxEnergy;
	energyPtr->setRotation(rotation);
}

void SceneFish::PlayFishHit()
{
	pGlobalMgr->GetMusicMgr()->stopAllEffects();
	pGlobalMgr->GetMusicMgr()->playEffect(UT->RNDNUM(8,24));
}

void SceneFish::menuCallback(CCObject* pSender)
{
	int tagId = ((CCNode*)pSender)->getTag();

	SIXLog("menuCallback.uID = %d",tagId);

	switch (tagId)
	{
	case ENUM_BTNIDX::BTN_CLOSE:
		{

			CCDirector::sharedDirector()->end();

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
		#endif
			break;
		}
	case ENUM_BTNIDX::BTN_MUSIC_ON:
		{
			CCSprite *off = CCSprite::create("./music_off.png");
			pMusicItem->setNormalImage(off);
			pMusicItem->setTag(ENUM_BTNIDX::BTN_MUSIC_OFF);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
			break;
		}
	case ENUM_BTNIDX::BTN_MUSIC_OFF:
		{
			CCSprite *on = CCSprite::create("./music_on.png");
			pMusicItem->setNormalImage(on);
			pMusicItem->setTag(ENUM_BTNIDX::BTN_MUSIC_ON);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			break;
		}
	}
}
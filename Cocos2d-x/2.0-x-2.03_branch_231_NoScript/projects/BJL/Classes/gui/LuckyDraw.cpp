//
//  LuckyDraw.cpp
//  Game
//
// Created by wangjun on 15-1-7.
//
//

#include "LuckyDraw.h"
#include "common/CocosUnits.h"
#include "ans/AnsString.h"
#include "ans/utf-8.h"
#include "configMgr/ConfigMgr.h"
#include "entity/EntityMgr.h"
#include "gui/RoomLayer.h"
#include "common/JsonHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

USING_NS_CC;

LuckyDraw::LuckyDraw()
{

}

LuckyDraw::~LuckyDraw()
{

}

bool LuckyDraw::init()
{
	canDraw = true;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor *base = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 800, 480);
	this->addChild(base);
	//±³¾°
	CCSprite *background = CCSprite::createWithSpriteFrame(spriteFrame("Bk_LuckyDraw1.png"));
	background->setPosition(ccp(winSize.width/2-98, winSize.height/2));
	this->addChild(background);	
	CCArray *animFrames = CCArray::create();
	animFrames->addObject(spriteFrame("Bk_LuckyDraw1.png"));
	animFrames->addObject(spriteFrame("Bk_LuckyDraw2.png"));
	animFrames->addObject(spriteFrame("Bk_LuckyDraw3.png"));
	animFrames->addObject(spriteFrame("Bk_LuckyDraw4.png"));
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2);
	CCFiniteTimeAction *forever = CCRepeatForever::create(CCAnimate::create(animation));
	background->runAction(forever);

	//Ö¸Õë
	pinSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_LuckDrawPin.png"));
	pinSprite->setAnchorPoint(ccp(0.5f, 0));
	pinSprite->setPosition(ccp(winSize.width/2, winSize.height/2+5));
	this->addChild(pinSprite);	
	//³é½±°´Å¥
	CCSprite *itemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_LuckDrawButton1.png"));
	CCSprite *itemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_LuckDrawButton2.png"));
	CCMenuItemSprite *menuItem = CCMenuItemSprite::create(itemNormalImage,itemSelectedImage,this,menu_selector(LuckyDraw::pressDraw));
	drawMenu = CCMenu::create(menuItem, NULL);
	drawMenu->setPosition(ccp(winSize.width/2, winSize.height/2+5));
	this->addChild(drawMenu,1);
	//·µ»Ø
	CCSprite* backNormal= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCSprite* backSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCMenuItemSprite* backItemSprite = CCMenuItemSprite::create(backNormal,backSelect,this,menu_selector(LuckyDraw::back));
	backSelect->setScale(0.9f);
	backSelect->setAnchorPoint(ccp(594,337));
	CCMenu* backMenu= CCMenu::create(backItemSprite,NULL);
	backMenu->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93));
	addChild(backMenu);
	return true;
}

void LuckyDraw::onEnter()
{
	CCLayer::onEnter();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1000,true);
}

void LuckyDraw::onExit()
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

void LuckyDraw::back(CCObject* obj)
{
	//playButtonSound();
	//CCScene *pScene = CCScene::create();
	//RoomLayer *pRoomLayer = RoomLayer::create();
	//pRoomLayer->automaticLogin(false);
	//pRoomLayer->closeLoginAward();
	//pScene->addChild(pRoomLayer);
	//CCDirector::sharedDirector()->replaceScene(pScene);

	playButtonSound();
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);
}

void LuckyDraw::keyBackClicked()
{
	back(NULL);
}

void LuckyDraw::pressDraw( CCObject* obj)
{
	if(canDraw == false)
	{
		return;
	}
	pinSprite->setRotation(0);
	canDraw = false;
	this->addRandSeed();
	int num = rand()%8;
	this->pinMove(num);
}

void LuckyDraw::pinMove(int tag)
{
	float anglePerUnit = 360/8;
	float finalAngle = anglePerUnit*tag;
	float circle = 4;
	this->addRandSeed();
	finalAngle+=rand()%43+1;
	finalAngle+=360*circle;
	CCRotateBy *rotateBy = CCRotateBy::create(10.0, finalAngle);
	CCEaseExponentialOut *easeAction = CCEaseExponentialOut::create(dynamic_cast<CCActionInterval *>(rotateBy));
	CCSequence *sequence = CCSequence::createWithTwoActions(easeAction, CCCallFuncN::create(this, callfuncN_selector(LuckyDraw::pinMoveEnd)));
	pinSprite->runAction(sequence);
}

void LuckyDraw::pinMoveEnd(CCNode *obj)
{
	canDraw = true;
}

void LuckyDraw::addRandSeed()
{
	cc_timeval psv;
	CCTime::gettimeofdayCocos2d(&psv, NULL);
	unsigned long int rand_seed = psv.tv_sec*1000+psv.tv_usec/1000;
	srand(rand_seed);
}
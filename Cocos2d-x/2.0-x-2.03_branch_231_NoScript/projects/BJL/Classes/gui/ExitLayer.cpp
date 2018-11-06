//
//  PesentCoins.cpp
//  Game
//
//  Created by ÂÞÃô on 13-7-10.
//
//

#include "ExitLayer.h"
#include "entity/EntityMgr.h"
#include "RoomLayer.h"
#include "GroupSprite.h"
#include "FreeLayer.h"
#include "OverRegistLayer.h"

bool ExitLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), winSize.width, winSize.height);
    addChild(layer,-1);

	//±³¾°
	CCSprite* exitBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer101.png"));
	exitBack->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
	addChild(exitBack);

	//tips
	CCSprite* spriteTips = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer0.png"));
	spriteTips->setPosition(ccp(winSize.width * 0.5,exitBack->getPositionY()+exitBack->getContentSize().height/2-spriteTips->getContentSize().height/2-5));
	addChild(spriteTips);

	CCSprite* closeNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCSprite* closeSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCMenuItemSprite* closeI = CCMenuItemSprite::create(closeNormal,closeSelect,this,menu_selector(ExitLayer::close));
	closeSelect->setScale(0.9f);
	closeSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* closeMenu = CCMenu::create(closeI,NULL);
	closeMenu->setPosition(ccp(exitBack->getContentSize().width - closeNormal->getContentSize().width * 0.5+10,exitBack->getContentSize().height - closeNormal->getContentSize().height * 0.5+10));
	exitBack->addChild(closeMenu);

	//ÍêÉÆ×¢²á£¬¼ÌÐøÓÎÏ·
	CCSprite* overRegistNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer100.png"));
	CCSprite* overRegistSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer100.png"));
	
	CCSprite* resumeNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer1.png"));
	CCSprite* resumeSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer1.png"));
	
	CCMenuItemSprite* overRegist = CCMenuItemSprite::create(overRegistNormal,overRegistSelect,this,menu_selector(ExitLayer::onOverRegist));
	CCMenuItemSprite* resumeItem = CCMenuItemSprite::create(resumeNormal,resumeSelect,this,menu_selector(ExitLayer::resumeGame));
	overRegistSelect->setScale(0.9f);
	overRegistSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	resumeSelect->setScale(0.9f);
	resumeSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* overRegistMenu = CCMenu::create(overRegist,NULL);
	CCMenu* resumeItemMenu = CCMenu::create(resumeItem,NULL);
	overRegistMenu->setPosition(ccp(winSize.width * 0.5 - exitBack->getContentSize().width * 0.25,winSize.height * 0.47+30));
	resumeItemMenu->setPosition(ccp(winSize.width * 0.5 - exitBack->getContentSize().width * 0.25,winSize.height * 0.47-40));
	addChild(overRegistMenu);
	addChild(resumeItemMenu);
	//Ãâ·Ñ»ñ½ð±Ò,Àë¿ªÓÎÏ·
	CCSprite* freeGetCoinsNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer2.png"));
	CCSprite* freeGetCoinsSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer2.png"));
	
	CCSprite* exitNormal =  CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer3.png"));
	CCSprite* exitSelect =  CCSprite::createWithSpriteFrame(spriteFrame("dt_exitlayer3.png"));
	CCMenuItemSprite* freeGetCoins = CCMenuItemSprite::create(freeGetCoinsNormal,freeGetCoinsSelect,this,menu_selector(ExitLayer::onFreeGetCoins));
	CCMenuItemSprite* exitItem = CCMenuItemSprite::create(exitNormal,exitSelect,this,menu_selector(ExitLayer::exitGame));
	freeGetCoinsSelect->setScale(0.9f);
	freeGetCoinsSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	exitSelect->setScale(0.9f);
	exitSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* freeGetCoinsMenu = CCMenu::create(freeGetCoins,NULL);
	CCMenu* exitItemMenu = CCMenu::create(exitItem,NULL);
	freeGetCoinsMenu->setPosition(ccp(winSize.width * 0.5 + exitBack->getContentSize().width * 0.25,winSize.height * 0.47+30));
	exitItemMenu->setPosition(ccp(winSize.width * 0.5 + exitBack->getContentSize().width * 0.25,winSize.height * 0.47-40));
	addChild(freeGetCoinsMenu);
	addChild(exitItemMenu);
	if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 0)
	{
		freeGetCoinsMenu->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.47+30));
		overRegistMenu->setVisible(false);
	}
    
    return true;
}

ExitLayer::ExitLayer()
{
    
}

ExitLayer::~ExitLayer()
{
    
}

void ExitLayer::onFreeGetCoins(CCObject* obj)
{
	playButtonSound();
	CCScene *scene = CCScene::create();
	FreeLayer *pFreelayer = FreeLayer::create();
	scene->addChild(pFreelayer);
	CCDirector::sharedDirector()->replaceScene(scene);   
}

void ExitLayer::onOverRegist(CCObject* obj)
{
	playButtonSound();
	CCScene* scene = CCScene::create();
	OverRegistLayer * pRegisterLayer = OverRegistLayer::create();
	pRegisterLayer->setRegistLayerFrom(1);
	scene->addChild(pRegisterLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void ExitLayer::resumeGame(CCObject* obj)
{
	playButtonSound();
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);
}

void ExitLayer::exitGame(CCObject* obj)
{
	playButtonSound();
	CCDirector::sharedDirector()->end();
}

void ExitLayer::close(CCObject* obj)
{
	playButtonSound();
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);
}


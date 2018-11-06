#include "MenuLayer.h"
#include "HelpLayer.h"
#include "PropLayer.h"
#include "RoomLayer.h"
#include "FreeLayer.h"
#include "LoginLayer.h"
#include "OverRegistLayer.h"


using namespace cocos2d;
MenuLayer::MenuLayer()
{

}
MenuLayer::~MenuLayer()
{

}
CCScene* MenuLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MenuLayer *layer = MenuLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool MenuLayer::init()
{
	bool bRet = false;
	do 
	{
		float posY = 368;
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *menuBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_SettingBk.png"));
		menuBk->setAnchorPoint(ccp(0,0.5));
		menuBk->setPosition(ccp(355,posY+2));
		addChild(menuBk);
		CCSprite *musicSprite =CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting5.png"));
		CCSprite *effectSprite =CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting6.png"));
		musicSprite->setPosition(ccp(426,posY));
		effectSprite->setPosition(ccp(633,posY));
		addChild(musicSprite);
		addChild(effectSprite);

		hasEffect = CCUserDefault::sharedUserDefault()->getBoolForKey("hasEffect", true);
		hasMusic = CCUserDefault::sharedUserDefault()->getBoolForKey("hasMusic", true);
		CCSprite *musicCheckbox;
		CCSprite *effectCheckbox;
		if(hasMusic)
		{
			musicCheckbox =CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting12.png"));
			if(!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
			{
				playBGM("music/roomback.mp3");
			}
		}else
		{
			musicCheckbox =CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting10.png"));
		}
		if(hasEffect)
		{
			effectCheckbox =CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting12.png"));
		}else
		{
			effectCheckbox =CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting10.png"));
		}
		musicItem = CCMenuItemSprite::create(musicCheckbox,musicCheckbox,this,menu_selector(MenuLayer::pressMusicItem));
		effectItem = CCMenuItemSprite::create(effectCheckbox,effectCheckbox,this,menu_selector(MenuLayer::pressEffectItem));
		CCMenu *musicMenu = CCMenu::create(musicItem, NULL);
		CCMenu *effectMenu = CCMenu::create(effectItem, NULL);
		musicMenu->setPosition(ccp(musicSprite->getPositionX()+70,posY));
		effectMenu->setPosition(ccp(effectSprite->getPositionX()+70,posY));
		addChild(musicMenu);
		addChild(effectMenu);
		CC_BREAK_IF(! CCLayer::init());
		setKeypadEnabled(true);
		bRet = true;
	} while (0);

	return bRet;

}

void MenuLayer::permitButtonClick()
{
	RoomLayer *pRoomLayer =  (RoomLayer *)this->getParent();
	pRoomLayer->permitButtonClick();
}		
void MenuLayer::forbidButtonClick()
{
	//pButtonMenu->setTouchEnabled(false);

}
void MenuLayer::keyBackClicked()
{
	RoomLayer * pRoomLayer = (RoomLayer * )this->getParent();
	pRoomLayer->permitButtonClick();
	playButtonSound();
	removeFromParentAndCleanup(true);
}

//ÓÎÏ·±³¾°ÒôÀÖ
void MenuLayer::pressMusicItem(CCObject* obj)
{
	bool bRet = false;
	if(hasMusic)
	{	
		musicItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting10.png")));
		musicItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting10.png")));
		bRet = false;
	}else
	{
		musicItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting12.png")));
		musicItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting12.png")));
		bRet = true;
	}
	hasMusic = bRet;
	CCUserDefault::sharedUserDefault()->setBoolForKey("hasMusic", bRet);
	CCUserDefault::sharedUserDefault()->flush();
	if(hasMusic)
	{
		if(!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			playBGM("music/roomback.mp3");
		}
	}else
	{
		if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			stopBGM();
		}
	}
}

//ÓÎÏ·±³¾°ÒôÀÖ
void MenuLayer::pressEffectItem(CCObject* obj)
{
	bool bRet = false;
	if(hasEffect)
	{	
		effectItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting10.png")));
		effectItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting10.png")));
		bRet = false;
	}else
	{
		effectItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting12.png")));
		effectItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Setting12.png")));
		bRet = true;
	}
	hasEffect = bRet;
	CCUserDefault::sharedUserDefault()->setBoolForKey("hasEffect", bRet);
	CCUserDefault::sharedUserDefault()->flush();
}
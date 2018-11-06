#include "CustomerServiceLayer.h"
#include "RoomLayer.h"
#include "GroupSprite.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif
using namespace cocos2d;
CustomerServiceLayer::CustomerServiceLayer()
{

}
CustomerServiceLayer::~CustomerServiceLayer()
{

}
CCScene* CustomerServiceLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		CustomerServiceLayer *layer = CustomerServiceLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool CustomerServiceLayer::init()
{
	bool bRet = false;
	do 
	{

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCLayerColor* layer = CCLayerColor::create( ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);
		/**添加背景图片**/
		CCSprite *pBGLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_10.png"));
		pBGLeft->setAnchorPoint(ccp(1.0f,0.5f));
		pBGLeft->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		addChild(pBGLeft);
		CCSprite *pBGRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_10.png"));
		pBGRight->setFlipX(true);
		pBGRight->setAnchorPoint(ccp(0.0f,0.5f));
		pBGRight->setPosition(CCPointMake(winSize.width*0.5 - 1,winSize.height*0.5));
		addChild(pBGRight);

		/**添加标题LOG**/
		CCSprite *pTitleLog =CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_3.png"));
		pTitleLog->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5+pBGRight->getContentSize().height/2-28));
		addChild(pTitleLog,2);

		/**添加关闭按钮**/
		CCSprite *pCloseNormalImage =CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
		CCSprite *pCloseSelectImage =CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
		CCMenuItemSprite *pCloseMenuItem= CCMenuItemSprite::create
			(pCloseNormalImage,pCloseSelectImage,this,menu_selector(CustomerServiceLayer::dismiss)); 
		pCloseSelectImage->setScale(0.9f);
		pCloseSelectImage->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseMenu = CCMenu::create(pCloseMenuItem,NULL);
		pCloseMenu->setPosition(winSize.width*0.5+pBGRight->getContentSize().width-25,winSize.height*0.5+pBGRight->getContentSize().height/2-25);
		addChild(pCloseMenu,2);

		CCSprite *pCustomerPhoto = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_6.png"));
		pCustomerPhoto->setPosition(CCPointMake(winSize.width*0.30f+40,winSize.height*0.45f));
		addChild(pCustomerPhoto,2);

		/**添加在线客服的按钮**/
		CCSprite *pNormalCSOnlineImage = (CCSprite *)GroupSprite::GroupSpriteWith
			("dt_warning_8.png","dt_kefu_1.png",GorupSpriteTypePhotoAndPhoto);
		CCSprite *pSelectCSOnlineImage = (CCSprite *)GroupSprite::GroupSpriteWith
			("dt_warning_8.png","dt_kefu_1.png",GorupSpriteTypePhotoAndPhoto);
		CCMenuItemSprite *pCSOnline = CCMenuItemSprite::create
			(pNormalCSOnlineImage,pSelectCSOnlineImage,this,menu_selector(CustomerServiceLayer::customerOnLine));
        pSelectCSOnlineImage->setScale(0.9f);
		pSelectCSOnlineImage->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		/**添加客服电话的按钮**/
		CCSprite *pNormalCSPhoneImage = (CCSprite *)GroupSprite::GroupSpriteWith
			("dt_warning_8.png","dt_kefu_4.png",GorupSpriteTypePhotoAndPhoto);
		CCSprite *pSelectCSPhoneImage = (CCSprite *)GroupSprite::GroupSpriteWith
			("dt_warning_8.png","dt_kefu_4.png",GorupSpriteTypePhotoAndPhoto);
		
		CCMenuItemSprite *pCSPhone = CCMenuItemSprite::create
			(pNormalCSPhoneImage,pSelectCSPhoneImage,this,menu_selector(CustomerServiceLayer::customerPhone));
        pSelectCSPhoneImage->setScale(0.9f);
		pSelectCSPhoneImage->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pMenu = CCMenu::create(pCSOnline,pCSPhone,NULL);
		pMenu->setPosition(CCPointMake(winSize.width*0.65,winSize.height*0.45));
		pMenu->alignItemsVerticallyWithPadding(50.0f);
		addChild(pMenu,2);
		CC_BREAK_IF(! CCLayer::init());
		setKeypadEnabled(true);
		bRet = true;
	} while (0);

	return bRet;

}

void CustomerServiceLayer::keyBackClicked()
{
	if(ConfigMgr::instance()->m_Config.m_bToAndroid)
	{
		ConfigMgr::instance()->m_Config.m_bToAndroid = false;
		return;
	}
	else
	{
		dismiss(NULL);
	}
}



void CustomerServiceLayer::dismiss(cocos2d::CCObject *obj)
{ 
	playButtonSound();
	//isGoingRoomLayer = false;
	RoomLayer *pRoomlayer = (RoomLayer *)this->getParent();
	pRoomlayer->permitButtonClick();
	this->removeFromParentAndCleanup(true);

}
void CustomerServiceLayer::customerOnLine(cocos2d::CCObject *obj){
	playButtonSound();
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->setGoingRoomLayer();
	ConfigMgr::instance()->m_Config.m_bToAndroid = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	showAndroidFeedBackLayer();
#endif
}
void CustomerServiceLayer::customerPhone(cocos2d::CCObject *obj){
	playButtonSound();
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->setGoingRoomLayer();
	ConfigMgr::instance()->m_Config.m_bToAndroid = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	toPhoneSever();
#endif
}
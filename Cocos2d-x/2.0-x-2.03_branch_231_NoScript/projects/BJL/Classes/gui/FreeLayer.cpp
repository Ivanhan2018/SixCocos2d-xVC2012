#include "FreeLayer.h"
#include "RoomLayer.h"
#include "FreeScrollLayer.h"
#include "MovingLabelLayer.h"
#include "RoomLayer.h"
#include "FreeCell.h"
using namespace cocos2d;
FreeLayer::FreeLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(FreeLayer::onGetDownData), MSG_UI_ANS_DOWNLOADDATA, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(FreeLayer::getDownAwardOver), MSG_UI_ANS_DOWNLOADAWARDOVER, NULL);
	
}
FreeLayer::~FreeLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_DOWNLOADDATA);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_DOWNLOADAWARDOVER);
}
CCScene* FreeLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		FreeLayer *layer = FreeLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

void FreeLayer::onGetDownData(CCObject* obj)
{
	SDownloadGamePrize_Returnn* data = (SDownloadGamePrize_Returnn*)obj;
	memcpy(&returnData, data, sizeof(SDownloadGamePrize_Returnn));
	CCLabelTTF* label = (CCLabelTTF*)this->getChildByTag(123);
	label->removeFromParentAndCleanup(true);
	//FreeScrollLayer *pFreeScroll = FreeScrollLayer::FreeScrollLayerWith(4,&returnData);
	//pFreeScroll->setPosition(CCPointMake(20.0f,3.0f));
	//addChild(pFreeScroll,2);
	FreeCell *sprite0 = FreeCell::FreeCellWith(0,data->dwDownloadGameInfo >> 0 & 1);
	sprite0->setAnchorPoint(CCPointZero);
	sprite0->setCellIdx(0,data->dwDownloadGameInfo >> 0 & 1);
	sprite0->setPosition(ccp(10, 310));
	addChild(sprite0,5);
	FreeCell *sprite1 = FreeCell::FreeCellWith(1,data->dwDownloadGameInfo >> 1 & 1);
	sprite1->setAnchorPoint(CCPointZero);
	sprite1->setCellIdx(1,data->dwDownloadGameInfo >> 1 & 1);
	sprite1->setPosition(ccp(10, 220));
	addChild(sprite1,5);
	FreeCell *sprite2 = FreeCell::FreeCellWith(2,data->dwDownloadGameInfo >> 2 & 1);
	sprite2->setAnchorPoint(CCPointZero);
	sprite2->setCellIdx(2,data->dwDownloadGameInfo >> 2 & 1);
	sprite2->setPosition(ccp(10, 130));
	addChild(sprite2,5);
	FreeCell *sprite3 = FreeCell::FreeCellWith(3,data->dwDownloadGameInfo >> 3 & 1);
	sprite3->setAnchorPoint(CCPointZero);
	sprite3->setCellIdx(3,data->dwDownloadGameInfo >> 3 & 1);
	sprite3->setPosition(ccp(10, 40));
	addChild(sprite3,5);




	CCSprite *m_bantouming_bj_left = CCSprite::createWithSpriteFrame(spriteFrame("dt_help_2.png"));

	m_bantouming_bj_left->setPosition(ccp(427.0f-164.0f,20.0f));
	addChild(m_bantouming_bj_left,4);

	CCSprite *m_bantouming_bj_right = CCSprite::createWithSpriteFrame(spriteFrame("dt_help_2.png"));
	//m_bantouming_bj_right->setRotationY(180.0f);
	m_bantouming_bj_right->setPosition(ccp(427.0f+164.0f,20.0f));
	addChild(m_bantouming_bj_right,4);

	CCLabelTTF* labelTips = CCLabelTTF::create(ConfigMgr::instance()->text("t474"),"",20);
	labelTips->setPosition(ccp(427,20));
	labelTips->setColor(ccc3(0,0,0));
	addChild(labelTips,5);
}

void FreeLayer::getDownAwardOver(CCObject* obj)
{
	MovingLabelLayer* moveingLabel = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t473"),ccp(427,240));
	addChild(moveingLabel,99);
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCTransitionFade *tScene = CCTransitionFade::create(2.0f, pScene, ccWHITE);
	CCDirector::sharedDirector()->replaceScene(tScene); 
}


bool FreeLayer::init()
{
	bool bRet = false;
	do 
	{

		EntityMgr::instance()->getDispatch()->connectLoginServer();
		EntityMgr::instance()->getDispatch()->getDownLoadAward(0,0);
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pPlayerInfoBJLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		CCSprite *pPlayerInfoBJRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		//pPlayerInfoBJRight->setRotationY(180);
		pPlayerInfoBJLeft->setPosition(ccp(winSize.width*0.25,winSize.height*0.5));
		pPlayerInfoBJRight->setPosition(ccp(winSize.width*0.75 - 1,winSize.height*0.5));
		addChild(pPlayerInfoBJLeft,0);
		addChild(pPlayerInfoBJRight,0);


		CCSprite *pPlayerInfoBJLeft1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		CCSprite *pPlayerInfoBJRight1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		//pPlayerInfoBJRight1->setRotationY(180);
		pPlayerInfoBJLeft1->setPosition(ccp(winSize.width*0.25+5,winSize.height*0.0-18));
		pPlayerInfoBJRight1->setPosition(ccp(winSize.width*0.75-5,winSize.height*0.0-18));
		pPlayerInfoBJLeft1->setScaleY(1.2f);
		pPlayerInfoBJRight1->setScaleY(1.2f);
		pPlayerInfoBJLeft1->setAnchorPoint(ccp(0.5,0));
		pPlayerInfoBJRight1->setAnchorPoint(ccp(0.5,0));
		addChild(pPlayerInfoBJLeft1,1);
		addChild(pPlayerInfoBJRight1,1);

		/*CCSprite *pMianFeiSprite = CCSprite::create("dt_playerinfo_0.png");
		pMianFeiSprite->setPosition(CCPointMake(winSize.width*0.054,winSize.height*0.885));
		addChild(pMianFeiSprite,2);*/

		CCLabelTTF* label = CCLabelTTF::create(ConfigMgr::instance()->text("t460"),"",30);
		label->setPosition(ccp(427,240));
		label->setColor(ccc3(0,0,0));
		addChild(label,5,123);


		CCSprite *pPlayerInfoLogo =  CCSprite::createWithSpriteFrame(spriteFrame("dt_register_14.png"));
		pPlayerInfoLogo->setPosition(ccp(winSize.width*0.5,winSize.height*0.923));
		addChild(pPlayerInfoLogo,2);

		CCSprite *pPlayerInfoLogoText = CCSprite::createWithSpriteFrame(spriteFrame("dt_free_3.png"));
		pPlayerInfoLogoText->setPosition(ccp(winSize.width*0.5,winSize.height*0.933));
		addChild(pPlayerInfoLogoText,3);



		CCSprite *pCloseNormalButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pCloseSelectButton =  CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pCloseItemSprite = CCMenuItemSprite::create
			(pCloseNormalButton,pCloseSelectButton,this,menu_selector(FreeLayer::dismiss));
		pCloseSelectButton->setScale(0.9f);
		pCloseSelectButton->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseButton = CCMenu::create(pCloseItemSprite,NULL);
		pCloseButton->setPosition(ccp(winSize.width*0.943,winSize.height*0.923));
		addChild(pCloseButton,1);
		
		setKeypadEnabled(true);

		bRet = true;
	} while (0);

	return bRet;

}

void FreeLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void FreeLayer::keyBackClicked()
{
	dismiss(NULL);
}
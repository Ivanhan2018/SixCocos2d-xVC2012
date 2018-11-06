#include "AgreementLayer.h"
#include "RoomLayer.h"
#include "AgreementScrollView.h"
#include "RegistLayer.h"
using namespace cocos2d;
AgreementLayer::AgreementLayer()
{

}
AgreementLayer::~AgreementLayer()
{

}
CCScene* AgreementLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		AgreementLayer *layer = AgreementLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool AgreementLayer::init()
{
	bool bRet = false;
	do 
	{
		
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pPlayerInfoBJLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		CCSprite *pPlayerInfoBJRight =CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		//pPlayerInfoBJRight->setRotationY(180);
		pPlayerInfoBJLeft->setPosition(ccp(winSize.width*0.25,winSize.height*0.5));
		pPlayerInfoBJRight->setPosition(ccp(winSize.width*0.75,winSize.height*0.5));
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


		CCSprite *pCloseNormalButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pCloseSelectButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pCloseItemSprite = CCMenuItemSprite::create
			(pCloseNormalButton,pCloseSelectButton,this,menu_selector(AgreementLayer::dismiss));
		pCloseSelectButton->setScale(0.9f);
		pCloseSelectButton->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseButton = CCMenu::create(pCloseItemSprite,NULL);
		pCloseButton->setPosition(ccp(winSize.width*0.943,winSize.height*0.923));
		addChild(pCloseButton,1);

		AgreementScrollView * pAgreementView = AgreementScrollView::create();
		addChild(pAgreementView,2);
		
		bRet = true;
		setKeypadEnabled(true);
	} while (0);

	return bRet;

}

void AgreementLayer::dismiss(cocos2d::CCObject *obj){
	CCScene *pScene = CCScene::create();
	RegistLayer *pRegistLayer = RegistLayer::create();
	//pRegistLayer->automaticLogin(false);
	//pRegistLayer->closeLoginAward();
	pScene->addChild(pRegistLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void AgreementLayer::keyBackClicked()
{
	dismiss(NULL);
}

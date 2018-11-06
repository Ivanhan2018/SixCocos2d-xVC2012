#include "RechargeLayer.h"
#include "RoomLayer.h"
#include "GroupSprite.h"
using namespace cocos2d;
RechargeLayer::RechargeLayer()
{

}
RechargeLayer::~RechargeLayer()
{

}
CCScene* RechargeLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		RechargeLayer *layer = RechargeLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool RechargeLayer::init()
{
	bool bRet = false;
	do 
	{

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);
		/**添加背景图片**/
		CCSprite *pBGLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_10.png")); 
		pBGLeft->setAnchorPoint(ccp(1.0f,0.5f));
		pBGLeft->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		addChild(pBGLeft);
		CCSprite *pBGRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_10.png")); 
		//pBGRight->setRotationY(180);
		pBGRight->setAnchorPoint(ccp(0.0f,0.5f));
		pBGRight->setPosition(CCPointMake(winSize.width*0.5+pBGRight->getContentSize().width,winSize.height*0.5));
		addChild(pBGRight);

		/**添加标题LOG**/
		CCSprite *pTitleLog = CCSprite::createWithSpriteFrame(spriteFrame("dt_recharge_2.png")); 
		pTitleLog->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5+pBGRight->getContentSize().height/2-28));
		addChild(pTitleLog,2);

		/**添加关闭按钮**/
		CCSprite *pCloseNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png")); 
		CCSprite *pCloseSelectImage =CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png")); 
		CCMenuItemSprite *pCloseMenuItem= CCMenuItemSprite::create
			(pCloseNormalImage,pCloseSelectImage,this,menu_selector(RechargeLayer::dismiss)); 
		pCloseSelectImage->setScale(0.9f);
		pCloseSelectImage->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseMenu = CCMenu::create(pCloseMenuItem,NULL);
		pCloseMenu->setPosition(winSize.width*0.5+pBGRight->getContentSize().width-25,winSize.height*0.5+pBGRight->getContentSize().height/2-25);
		addChild(pCloseMenu,2);

		/**添加确定按钮**/
		CCSprite *pSureNormalImage =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCSprite *pSureSelectImage =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		
		CCMenuItemSprite *pSureMenuItem= CCMenuItemSprite::create
			(pSureNormalImage,pSureSelectImage,this,menu_selector(RechargeLayer::makeSure)); 
		pSureSelectImage->setScale(0.9f);
		pSureSelectImage->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pSureMenu = CCMenu::create(pSureMenuItem,NULL);
		pSureMenu->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5-pBGRight->getContentSize().height/2+40));
		addChild(pSureMenu,2);


		/**添加文字提示**/
		//CCLabelTTF *pTextWaring0 =CCLabelTTF::create(ConfigMgr::instance()->text("t156"),"HelveticaNeue-Bold",18);
		//pTextWaring0->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.683));
		//addChild(pTextWaring0,3);

		//CCLabelTTF *pTextWaring1 =CCLabelTTF::create(ConfigMgr::instance()->text("t157"),"HelveticaNeue-Bold",18);
		//pTextWaring1->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.638));
		//addChild(pTextWaring1,4);

		///**添加图片提示**/
		//CCSprite *pImageWarning0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_recharge_0.png")); 
		//pImageWarning0->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.43));
		//addChild(pImageWarning0,4);
		//CCSprite *pImageWarning1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_recharge_1.png")); 
	 //   pImageWarning1->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.30));
		//addChild(pImageWarning1,4);

		CCSprite *pImageWarning0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_recharge_0.jpg")); 
		pImageWarning0->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		addChild(pImageWarning0,4);
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;
	} while (0);

	return bRet;

}


void RechargeLayer::dismiss(cocos2d::CCObject *obj){ 
	RoomLayer *pRoomlayer = (RoomLayer *)this->getParent();
	pRoomlayer->permitButtonClick();
	this->removeFromParentAndCleanup(true);

}
void RechargeLayer::makeSure(cocos2d::CCObject *obj){
	//快捷充值 2快 = 60W + 话费点

}
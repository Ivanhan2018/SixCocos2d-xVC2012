#include "VIPSystemLayer.h"
#include "RoomLayer.h"
#include "common/CocosUnits.h"
#include "ShopSystemLayer.h"

VIPSystemLayer::VIPSystemLayer()
{

}
VIPSystemLayer::~VIPSystemLayer()
{

}
CCScene* VIPSystemLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		VIPSystemLayer *layer = VIPSystemLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool VIPSystemLayer::init()
{
	bool bRet = false;
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		/**绘制半透明蒙板**/
		CCLayerColor* layer = CCLayerColor::create( ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);


		/**绘制背景图片**/
		CCSprite * pBJ = CCSprite::create("background/Bk_VIP.png");
		pBJ->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(pBJ,0);

		/**特卖按钮**/
		CCSprite *normalSprite1 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_VIP1.png"));
		CCSprite *selectSprite1 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_VIP2.png"));
		selectSprite1->setScale(0.9f);
		CCMenuItemSprite *menuSprite1 = CCMenuItemSprite::create
			(normalSprite1,selectSprite1,this,menu_selector(VIPSystemLayer::onDiscount));

		CCMenu *menu1= CCMenu::create(menuSprite1,NULL);
		menu1->setPosition(ccp(242, 76));  
		addChild(menu1);

		//成为VIP按钮
		CCSprite *normalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_VIP1.png"));
		CCSprite *selectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_VIP2.png"));
		CCMenuItemSprite *menuSprite = CCMenuItemSprite::create
			(normalSprite,selectSprite,this,menu_selector(VIPSystemLayer::onBecomeVIP));

		CCMenu *menu= CCMenu::create(menuSprite,NULL);
		menu->setPosition(ccp(579, menu1->getPositionY())); 
		addChild(menu);
		/**关闭按钮**/
		CCSprite *pbuttonNormalClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pbuttonSelectClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pButtonClose = CCMenuItemSprite::create
			(pbuttonNormalClose,pbuttonSelectClose,this,menu_selector(VIPSystemLayer::dismiss));
		pbuttonSelectClose->setScale(0.9f);
		pbuttonSelectClose->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pButton0 = CCMenu::create(pButtonClose,NULL);
		pButton0->setPosition(ccp(pBJ->getPositionX()+pBJ->getContentSize().width/2-pbuttonNormalClose->getContentSize().width/2+10,
			pBJ->getPositionY()+pBJ->getContentSize().height/2-pbuttonNormalClose->getContentSize().height/2+10));  
		addChild(pButton0,2);
		bRet = true;
		setKeypadEnabled(true);
	} while (0);

	return bRet;

}

void VIPSystemLayer::keyBackClicked()
{
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);
}

void VIPSystemLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);

}

void VIPSystemLayer::onDiscount(CCObject* obj)
{
	playButtonSound();
	ShopSystemLayer *tabLayer = ShopSystemLayer::create();
	CCScene *scene = CCScene::create();
	scene->addChild(tabLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void VIPSystemLayer::onBecomeVIP(CCObject* obj)
{
	playButtonSound();
	ShopSystemLayer *tabLayer = ShopSystemLayer::create();
	CCScene *scene = CCScene::create();
	scene->addChild(tabLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}
#include "TabLayer.h"
#include "RoomLayer.h"
#include "GroupSprite.h"
#include "TaskInfo.h"
#include "PromptBox.h"
#include "MovingLabelLayer.h"
#include "ddz/SceneControl.h"
#include "ddz/DDZRes.h"
#include "common/CocosUnits.h"


#define minInWarning(a,b) (((a) < (b)) ? (a) : (b))

using namespace cocos2d;
TabLayer::TabLayer()
{
	currentItem = 0;
	itemGap = 10;
	tabMenuWidth = 0;
	normalName = NULL;
	selectedName = NULL;
	tabMenuItem = NULL;
}

TabLayer::~TabLayer()
{
	if(normalName!=NULL)
	{
		normalName->release();
		normalName = NULL;
	}
	if(selectedName!=NULL)
	{
		selectedName->release();
		selectedName = NULL;
	}
}

TabLayer *TabLayer::createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName)
{
	TabLayer *tabLayer = new TabLayer();
	if (tabLayer && tabLayer->initWithTabItems(itemNormalName, itemSelectedName))
	{
		tabLayer->autorelease();
		return tabLayer;
	}
	else
	{
		CC_SAFE_DELETE(tabLayer);
		return NULL;
	}
}

bool TabLayer::initWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName)
{
	bool bRet = false;
	do 
	{
		if(itemNormalName==NULL||itemSelectedName==NULL)
		{
			return false;
		}
		if(itemNormalName->count()!=itemSelectedName->count())
		{
			return false;
		}
		normalName = CCArray::createWithArray(itemNormalName);
		selectedName = CCArray::createWithArray(itemSelectedName);
		normalName->retain();
		selectedName->retain();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		/**绘制半透明蒙板**/
		CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);

		/**绘制背景图片**/
		pBJ  = CCSprite::create("background/bg2.png");
		pBJ->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(pBJ,0);

		maskSprite = CCSprite::createWithSpriteFrame(spriteFrame("bg2_2.png"));
		maskSprite->setPosition(ccp(winSize.width/2,winSize.height-maskSprite->getContentSize().height/2));
		//this->addChild(maskSprite,2);

		//tab菜单 每日任务 新手任务 勋章
		tabNum = itemNormalName->count();
		tabMenuWidth = (tabNum+1)*itemGap;
		tabMenuItem = CCArray::create();
		for(int i = 0 ; i < tabNum; i++)
		{
			if(i == currentItem)
			{
				CCString *imageName = (CCString *)selectedName->objectAtIndex(i);
				string str = imageName->getCString();
				CCSprite *sprite = CCSprite::createWithSpriteFrame(spriteFrame(imageName->getCString()));
				tabMenuWidth+=sprite->getContentSize().width;
				CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite,sprite,this,menu_selector(TabLayer::pressTabButton));
				menuItem->setTag(i+TabLayerBaseTag);
				tabMenuItem->addObject(menuItem);
			}else{
				CCString *imageName = (CCString *)normalName->objectAtIndex(i);
				CCSprite *sprite = CCSprite::createWithSpriteFrame(spriteFrame(imageName->getCString()));
				tabMenuWidth+=sprite->getContentSize().width;
				CCMenuItemSprite *menuItem = CCMenuItemSprite::create(sprite,sprite,this,menu_selector(TabLayer::pressTabButton));
				menuItem->setTag(i+TabLayerBaseTag);
				tabMenuItem->addObject(menuItem);
			}
		}
		tabMenu = CCMenu::createWithArray(tabMenuItem);
		tabMenu->setAnchorPoint(ccp(0.5,0.5));
		tabMenu->setPosition(ccp(tabMenuWidth/2,winSize.height*0.9f-2));
		tabMenu->alignItemsHorizontallyWithPadding(itemGap);//设置排列方式，纵向间隔20
		addChild(tabMenu, 2);

		/**关闭按钮**/
		CCSprite *pbuttonNormalClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pbuttonSelectClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pButtonClose = CCMenuItemSprite::create
			(pbuttonNormalClose,pbuttonSelectClose,this,menu_selector(TabLayer::dismiss));
		pbuttonSelectClose->setScale(0.9f);
		pbuttonSelectClose->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pButton0 = CCMenu::create(pButtonClose,NULL);
		pButton0->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93)); 
		addChild(pButton0,2);

		bRet = true;
		setKeypadEnabled(true);
	} while (0);

	return bRet;

}

void TabLayer::keyBackClicked()
{
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);
}

void TabLayer::dismiss(cocos2d::CCObject *obj){
	//playButtonSound();
	//RoomLayer* layer = (RoomLayer*)this->getParent();
	//layer->permitButtonClick();
	//this->removeFromParentAndCleanup(true);
	doSomethingBeforeClosed();
	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void TabLayer::pressTabButton( CCObject* obj)
{
	int itemTag = ((CCNode *)obj)->getTag();
	if(currentItem == itemTag)
	{
		return;
	}
	currentItem = itemTag;
	for(int i = 0 ; i < tabNum; i++)
	{
		CCMenuItemSprite *menuItem = (CCMenuItemSprite *)tabMenu->getChildByTag(TabLayerBaseTag+i);
		if(TabLayerBaseTag+i == currentItem)
		{
			CCString *imageName = (CCString *)selectedName->objectAtIndex(i);
			menuItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame(imageName->getCString())));
			menuItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame(imageName->getCString())));
		}else{
			CCString *imageName = (CCString *)normalName->objectAtIndex(i);
			menuItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame(imageName->getCString())));
			menuItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame(imageName->getCString())));
		}
	}
	doSomething();
}

void TabLayer::doSomething()
{
	CCLog("TabLayer::doSomething");
}

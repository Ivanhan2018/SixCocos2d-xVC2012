#include "ExchangerLayer.h"
#include "gui/RoomLayer.h"
#include "common/CocosUnits.h"
#include "ddz/SceneControl.h"
#include "ddz/DDZRes.h"

ExchangerLayer::ExchangerLayer()
{
	exchangeTable = NULL;
}

ExchangerLayer::~ExchangerLayer()
{
	if(exchangeTable!=NULL)
		exchangeTable->release();
}

bool ExchangerLayer::init()
{
	bool bRet = false;
	do 
	{
		winSize = CCDirector::sharedDirector()->getWinSize();
		ccColor3B whiteColor = ccc3(255,255,255);
		ccColor3B blackColor = ccc3(0,0,0);
		CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);

		CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ExchangeTableBk1.png"));
		tableItemSize = tempSprite->getContentSize();
		tableGapX = (winSize.width-tableItemSize.width*3)/4;
		tableGapY = 4;
		itemNum = 5;

		CCSprite * pBJ  = CCSprite::create("background/Bk_Exchange1.png");
		pBJ->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		this->addChild(pBJ,0);

		CCSprite * exchangeSprite  = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Exchange3.png"));
		exchangeSprite->setAnchorPoint(ccp(0,0.5f));
		exchangeSprite->setPosition(ccp(0,390));
		this->addChild(exchangeSprite,2);

		/**关闭按钮**/
		CCSprite *pbuttonNormalClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pbuttonSelectClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pButtonClose = CCMenuItemSprite::create
			(pbuttonNormalClose,pbuttonSelectClose,this,menu_selector(ExchangerLayer::dismiss));
		pbuttonSelectClose->setScale(0.9f);
		pbuttonSelectClose->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pButton0 = CCMenu::create(pButtonClose,NULL);
		pButton0->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93)); 
		addChild(pButton0,2);

		//金币
		CCSize tableViewSize;
		tableViewSize.width = winSize.width;
		tableViewSize.height = 336;
		exchangeTable = CCTableView::create(this, tableViewSize);
		exchangeTable->setDelegate(this);
		exchangeTable->setAnchorPoint(ccp(0.5, 0.5));
		exchangeTable->setPosition(ccp(0, 0));
		exchangeTable->setVerticalFillOrder(kCCTableViewFillTopDown);
		exchangeTable->setDirection(kCCScrollViewDirectionVertical);
		exchangeTable->retain();
		this->addChild(exchangeTable, 1);

		//购买
		buyBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyBk.png"));
		buyBk->setAnchorPoint(ccp(0.5f,0));
		buyBk->setPosition(ccp(winSize.width/2,88));
		this->addChild(buyBk,1);

		buyText = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Exchange1.png"));
		buyText->setPosition(ccp(winSize.width/2,340));
		this->addChild(buyText,1);


		float textWidth = 100;
		float startY = 288;
		float gapY = 56;
		//类型标签
		buyArticleType1 = CCLabelTTF::create(ConfigMgr::instance()->text("t558"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		buyArticleType1->setColor(whiteColor);
		buyArticleType1->setPosition(CCPointMake(241,startY));
		addChild(buyArticleType1,1);
		//物品类型底框
		buyArticleTypeBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png"));
		buyArticleTypeBk->setAnchorPoint(ccp(0,0.5f));
		buyArticleTypeBk->setPosition(ccp(284,startY));
		buyArticleTypeBk->setAnchorPoint(ccp(0,0.5F));
		this->addChild(buyArticleTypeBk,1);
		//物品类型
		textWidth = 400;
		buyArticleType2 = CCLabelTTF::create(ConfigMgr::instance()->text("t558"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		buyArticleType2->setColor(blackColor);
		buyArticleType2->setAnchorPoint(ccp(0,0.5f));
		buyArticleType2->setPosition(CCPointMake(290,startY));
		addChild(buyArticleType2,1);

		startY -= gapY;
		//数量标签
		textWidth = 100;
		buyArticleNumLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t559"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		buyArticleNumLabel->setColor(whiteColor);
		buyArticleNumLabel->setPosition(CCPointMake(241,startY));
		addChild(buyArticleNumLabel,1);

		//购买数量输入框
		textWidth = 400;
		buyArticleNum = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
		buyArticleNum->setPosition(CCPoint(284, startY));
		buyArticleNum->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
		buyArticleNum->setReturnType(kKeyboardReturnTypeGo);
		buyArticleNum->setAnchorPoint(ccp(0,0.5f));
		buyArticleNum->setFontColor(blackColor);
		//buyArticleNum->setFontSize(20);
		addChild(buyArticleNum,1);
		
		startY -= gapY;
		//联系方式标签
		textWidth = 100;
		contactLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t1000"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		contactLabel->setColor(whiteColor);
		contactLabel->setPosition(CCPointMake(241,startY));
		addChild(contactLabel,1);

		//联系方式输入框
		textWidth = 400;
		contactInput = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
		contactInput->setPosition(CCPoint(284, startY));
		contactInput->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
		contactInput->setReturnType(kKeyboardReturnTypeGo);
		contactInput->setAnchorPoint(ccp(0,0.5f));
		contactInput->setFontColor(blackColor);
		//contactInput->setFontSize(20);
		addChild(contactInput,1);

		//购买确定取消菜单
		CCSprite * okNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk1.png"));
		CCSprite * okSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk2.png"));
		CCSprite * cancelNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel1.png"));
		CCSprite * cancelSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel2.png"));
		CCMenuItemSprite *okMenuItem = CCMenuItemSprite::create(okNormalSprite, 
			okSelectSprite, this, menu_selector(ExchangerLayer::pressOk));
		CCMenuItemSprite *canceldrawMenuItem = CCMenuItemSprite::create(cancelNormalSprite, 
			cancelSelectSprite, this, menu_selector(ExchangerLayer::pressCancel));
		buyMenu = CCMenu::create(okMenuItem,canceldrawMenuItem,NULL);
		buyMenu->setPosition(ccp(winSize.width * 0.5, 126));	
		buyMenu->alignItemsHorizontallyWithPadding(20);
		this->addChild(buyMenu,1);
		this->setBuyViewVisible(false);

		setKeypadEnabled(true);
		this->setTouchEnabled(true);
		bRet = true;
	}while(0);
	return bRet;
}

void ExchangerLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void ExchangerLayer::setBuyViewVisible(bool flag)
{
	buyViewVisible = flag;
	buyBk->setVisible(flag);
	buyText->setVisible(flag);
	buyArticleType1->setVisible(flag);
	buyArticleTypeBk->setVisible(flag);
	buyArticleType2->setVisible(flag);
	buyArticleNumLabel->setVisible(flag);
	buyArticleNum->setVisible(flag);
	contactLabel->setVisible(flag);
	contactInput->setVisible(flag);
	buyArticleNum->setText("");
	contactInput->setText("");
	buyMenu->setVisible(flag);
}

void ExchangerLayer::pressExchangeButton(cocos2d::CCObject *obj)
{
	if(buyViewVisible == true)
	{
		return;
	}
	currentType = ((CCNode *)obj)->getTag();
	for(int i = 0 ; i < itemNum ; i++){
		if(currentType == ExchangeButton_Start+i)
		{
			buyArticleType2->setString(ConfigMgr::instance()->text(CCString::createWithFormat("t%d", 589+i)->getCString()));
		}
		if(currentType<3){
			contactLabel->setString(ConfigMgr::instance()->text("t1000"));
		}else{
			contactLabel->setString(ConfigMgr::instance()->text("t1001"));
		}
	}
	this->setBuyViewVisible(true);
}

void ExchangerLayer::pressOk(cocos2d::CCObject *obj)
{
	this->setBuyViewVisible(false);
	for(int i = 0 ; i < itemNum ; i++){
		if(currentType == ExchangeButton_Start+i)
		{
			
		}
	}
}

void ExchangerLayer::pressCancel(cocos2d::CCObject *obj)
{
	this->setBuyViewVisible(false);
}

/**单元格大小
参数：table单元格所属的表格
*/
CCSize ExchangerLayer::cellSizeForTable(CCTableView *table)
{
	return CCSize(winSize.width, tableItemSize.height+tableGapY);
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int ExchangerLayer::numberOfCellsInTableView(CCTableView *table)
{
	int size;
	size = itemNum/3;
	if(itemNum%3!=0)
	{
		size++;
	}
	return size;
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *ExchangerLayer::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	char name[32];
	float startX = tableItemSize.width/2+tableGapX;
	float startY = tableItemSize.height/2+tableGapY;
	for(int i = 1 ; i < 4&&(((int)index*3+i)<=itemNum) ; i++)
	{
		sprintf(name, "%s%d.png", ExchangeTableFileName, (int)index*3+i);
		CCSprite *cellBk = CCSprite::createWithSpriteFrame(spriteFrame(name));
		cellBk->setPosition(ccp(startX, startY));
		cell->addChild(cellBk);

		memset(name, 0, sizeof(name));	
		CCSprite * buyNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ExchangeButton1.png"));
		CCSprite * buySelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ExchangeButton2.png"));
		CCMenuItemSprite *buyMenuItem = CCMenuItemSprite::create(buyNormalSprite, 
			buySelectSprite, this, menu_selector(ExchangerLayer::pressExchangeButton));
		buyMenuItem->setTag(ExchangeButton_Start+((int)index*3+i-1));
		CCMenu *buyMenu = CCMenu::create(buyMenuItem,NULL);
		buyMenu->setPosition(ccp(startX+tableItemSize.width/2-buyNormalSprite->getContentSize().width/2-8,
			startY-tableItemSize.height/2+buyNormalSprite->getContentSize().height/2+8));
		cell->addChild(buyMenu);
		startX+=tableItemSize.width+tableGapX;
	}
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void ExchangerLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	//CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(nameLabelTag);
	//const char *name = nameLabel->getString();
	//textField->setString(name);
	//this->removeChild(_tableView, true);
	//flag = 0;
}

void ExchangerLayer::scrollViewDidScroll(CCScrollView* view)
{

}
void ExchangerLayer::scrollViewDidZoom(CCScrollView* view)
{

}

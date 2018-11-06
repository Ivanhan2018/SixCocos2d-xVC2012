#include "ShopSystemLayer.h"
#include "entity/EntityMgr.h"
#include "common/DBHandler.h"

ShopSystemLayer::ShopSystemLayer()
{
	friendStatusData = NULL;
	myFriendList = NULL;
	coinsTable = NULL;
	articleTable = NULL;
	promptBox = NULL;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ShopSystemLayer::refreshView), "UserInsureInfo", NULL);
}

ShopSystemLayer::~ShopSystemLayer()
{
	if(friendStatusData!=NULL)
		friendStatusData->release();
	if(myFriendList!=NULL)
		myFriendList->release();
	if(coinsTable!=NULL)
		coinsTable->release();
	if(articleTable!=NULL)
		articleTable->release();
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "UserInsureInfo");
}

ShopSystemLayer *ShopSystemLayer::create()
{
	CCArray *normalName = CCArray::create();
	CCArray *selectedName = CCArray::create();
	normalName->addObject(CCString::create("Tab_Coins1.png"));
	selectedName->addObject(CCString::create("Tab_Coins2.png"));
	normalName->addObject(CCString::create("Tab_Bank1.png"));
	selectedName->addObject(CCString::create("Tab_Bank2.png"));
	//normalName->addObject(CCString::create("Tab_Article3.png"));
	//selectedName->addObject(CCString::create("Tab_Article4.png"));
	return ShopSystemLayer::createWithTabItems(normalName, selectedName);
}

ShopSystemLayer *ShopSystemLayer::createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName)
{
	ShopSystemLayer *tabLayer = new ShopSystemLayer();
	if (tabLayer && tabLayer->initWithTabItems(itemNormalName, itemSelectedName))
	{
		tabLayer->initView();
		tabLayer->autorelease();
		return tabLayer;
	}
	else
	{
		CC_SAFE_DELETE(tabLayer);
		return NULL;
	}
}

void ShopSystemLayer::initView()
{
	score = 0;
	bankScore = 0;
	winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopCoinTableBk1.png"));
	tableItemSize = tempSprite->getContentSize();
	tableGapX = (winSize.width-tableItemSize.width*3)/4;
	tableGapY = 4;
	coinsTableItemsNum = 7;
	this->setTabMenuPositionY(winSize.height*0.945f);
	pBJ->setDisplayFrame(spriteFrame("background/Bk_Shop.png"));
	maskSprite->setDisplayFrame(spriteFrame("Sprite_ShopMask1.png"));
	maskSprite2 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopMask2.png"));
	maskSprite2->setPosition(ccp(winSize.width/2,maskSprite2->getContentSize().height/2));
	this->addChild(maskSprite2,2);
	maskSprite3 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopMask3.png"));
	maskSprite3->setPosition(ccp(winSize.width/2,maskSprite2->getContentSize().height/2));
	this->addChild(maskSprite3,2);

	//金币
	CCSize tableViewSize;
	tableViewSize.width = winSize.width;
	tableViewSize.height = 310;
	coinsTable = CCTableView::create(this, tableViewSize);
	coinsTable->setDelegate(this);
	coinsTable->setAnchorPoint(ccp(0.5, 0.5));
	coinsTable->setPosition(ccp(0, 60));
	coinsTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	coinsTable->setDirection(kCCScrollViewDirectionVertical);
	coinsTable->retain();
	coinsTable->setTag(ShopTableTag_Coins);
	this->addChild(coinsTable, 1);
	//道具
	tableViewSize.width = winSize.width;
	tableViewSize.height = 310;
	articleTable = CCTableView::create(new ArticleTableHelper(this), tableViewSize);
	articleTable->setDelegate(this);
	articleTable->setAnchorPoint(ccp(0.5, 0.5));
	articleTable->setPosition(ccp(0, 60));
	articleTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	articleTable->setDirection(kCCScrollViewDirectionVertical);
	articleTable->retain();
	articleTable->setTag(ShopTableTag_Article);
	this->addChild(articleTable, 1);
	articleTable->setVisible(false);

	//保险柜
	bankBk = CCSprite::createWithSpriteFrame(spriteFrame("background/Bk_ShopBank.png"));
	bankBk->setAnchorPoint(ccp(0.5,0));
	bankBk->setPosition(ccp(winSize.width/2, 40));
	this->addChild(bankBk,1);	
	float textWidth = 500;
	char info[100]={0};
	sprintf(info, "%I64d", score);
	scoreLabel = CCLabelTTF::create(info,"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	scoreLabel->setColor(ccc3(255,255,255));
	scoreLabel->setAnchorPoint(ccp(0,0.5f));
	scoreLabel->setPosition(CCPointMake(465,228));
	addChild(scoreLabel,1);

	memset(info, 0, sizeof(info));
	sprintf(info, "%I64d", bankScore);
	bankScoreLabel = CCLabelTTF::create(info,"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	bankScoreLabel->setColor(ccc3(255,255,255));
	bankScoreLabel->setAnchorPoint(ccp(0,0.5f));
	bankScoreLabel->setPosition(CCPointMake(465,178));
	addChild(bankScoreLabel,1);
	//添加按钮
	CCSprite * depositNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_ShopBankDeposit1.png"));
	CCSprite * depositSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_ShopBankDeposit2.png"));
	CCSprite * withdrawNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_ShopBankWithdraw1.png"));
	CCSprite * withdrawSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_ShopBankWithdraw2.png"));
	CCSprite * sendNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_ShopBankSend1.png"));
	CCSprite * sendSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_ShopBankSend2.png"));
	CCMenuItemSprite *depositMenuItem = CCMenuItemSprite::create(depositNormalSprite, 
		depositSelectSprite, this, menu_selector(ShopSystemLayer::depositButton));
	CCMenuItemSprite *withdrawMenuItem = CCMenuItemSprite::create(withdrawNormalSprite, 
		withdrawSelectSprite, this, menu_selector(ShopSystemLayer::withdrawButton));
	CCMenuItemSprite *sendMenuItem = CCMenuItemSprite::create(sendNormalSprite, 
		sendSelectSprite, this, menu_selector(ShopSystemLayer::sendButton));
	bankMenu = CCMenu::create(depositMenuItem,withdrawMenuItem,sendMenuItem,NULL);
	bankMenu->setPosition(ccp(winSize.width * 0.5, 101));	
	bankMenu->alignItemsHorizontallyWithPadding(0.5);//设置排列方式，纵向间隔20
	this->addChild(bankMenu,1);
	bankBk->setVisible(false);
	scoreLabel->setVisible(false);
	bankScoreLabel->setVisible(false);
	bankMenu->setVisible(false);
	/************购买**********/
	buyBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyBk.png"));
	buyBk->setAnchorPoint(ccp(0.5f,0));
	buyBk->setPosition(ccp(winSize.width/2,88));
	this->addChild(buyBk,1);

	buyText = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyLabel.png"));
	buyText->setPosition(ccp(winSize.width/2,340));
	this->addChild(buyText,1);


	textWidth = 100;
	//类型标签
	buyArticleType1 = CCLabelTTF::create(ConfigMgr::instance()->text("t558"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	buyArticleType1->setColor(ccc3(255,255,255));
	buyArticleType1->setPosition(CCPointMake(241,261));
	addChild(buyArticleType1,1);
	//物品类型底框
	buyArticleTypeBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png"));
	buyArticleTypeBk->setAnchorPoint(ccp(0,0.5f));
	buyArticleTypeBk->setPosition(ccp(284,261));
	buyArticleTypeBk->setAnchorPoint(ccp(0,0.5f));
	this->addChild(buyArticleTypeBk,1);
	//物品类型
	buyArticleType2 = CCLabelTTF::create(ConfigMgr::instance()->text("t558"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	buyArticleType2->setColor(ccc3(138,99,64));
	buyArticleType2->setPosition(CCPointMake(winSize.width/2,261));
	addChild(buyArticleType2,1);

	//数量标签
	buyArticleNumLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t559"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	buyArticleNumLabel->setColor(ccc3(255,255,255));
	buyArticleNumLabel->setPosition(CCPointMake(241,202));
	addChild(buyArticleNumLabel,1);

	//购买数量输入框
	buyArticleNum = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	buyArticleNum->setPosition(CCPoint(284, 202));
	buyArticleNum->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	buyArticleNum->setReturnType(kKeyboardReturnTypeGo);
	buyArticleNum->setAnchorPoint(ccp(0,0.5f));
	buyArticleNum->setFontColor(ccc3(0,0,0));
	//buyArticleNum->setFontSize(20);
	addChild(buyArticleNum,1);

	//购买确定取消菜单
	CCSprite * okNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk1.png"));
	CCSprite * okSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk2.png"));
	CCSprite * cancelNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel1.png"));
	CCSprite * cancelSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel2.png"));
	CCMenuItemSprite *okMenuItem = CCMenuItemSprite::create(okNormalSprite, 
		okSelectSprite, this, menu_selector(ShopSystemLayer::pressOk));
	CCMenuItemSprite *canceldrawMenuItem = CCMenuItemSprite::create(cancelNormalSprite, 
		cancelSelectSprite, this, menu_selector(ShopSystemLayer::pressCancel));
	buyMenu = CCMenu::create(okMenuItem,canceldrawMenuItem,NULL);
	buyMenu->setPosition(ccp(winSize.width * 0.5, 136));	
	buyMenu->alignItemsHorizontallyWithPadding(20);
	this->addChild(buyMenu,1);
	this->setBuyViewVisible(false);
	/************取款**********/
	withdrawBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyBk.png"));
	withdrawBk->setAnchorPoint(ccp(0.5f,0));
	withdrawBk->setPosition(ccp(winSize.width/2,88));
	this->addChild(withdrawBk,1);

	withdrawText = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopWithdrawLabel.png"));
	withdrawText->setPosition(ccp(winSize.width/2,340));
	this->addChild(withdrawText,1);

	textWidth = 120;

	//数量标签
	withdrawNumLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t569"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	withdrawNumLabel->setColor(ccc3(255,255,255));
	withdrawNumLabel->setPosition(CCPointMake(241,261));
	addChild(withdrawNumLabel,1);

	//购买数量输入框
	withdrawNum = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	withdrawNum->setPosition(CCPoint(309, 261));
	withdrawNum->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	withdrawNum->setReturnType(kKeyboardReturnTypeGo);
	withdrawNum->setAnchorPoint(ccp(0,0.5f));
	withdrawNum->setFontColor(ccc3(0,0,0));
	//withdrawNum->setFontSize(20);
	addChild(withdrawNum,1);

	//密码标签
	withdrawPasswordLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t570"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	withdrawPasswordLabel->setColor(ccc3(255,255,255));
	withdrawPasswordLabel->setPosition(CCPointMake(241,202));
	addChild(withdrawPasswordLabel,1);

	//密码输入框
	withdrawPassword = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	withdrawPassword->setPosition(CCPoint(309, 202));
	withdrawPassword->setInputFlag(kEditBoxInputFlagPassword);
	withdrawPassword->setReturnType(kKeyboardReturnTypeGo);
	withdrawPassword->setAnchorPoint(ccp(0,0.5f));
	withdrawPassword->setFontColor(ccc3(0,0,0));
	//withdrawPassword->setFontSize(20);
	addChild(withdrawPassword,1);

	//购买确定取消菜单
	CCSprite * okNormalSprite2 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk1.png"));
	CCSprite * okSelectSprite2 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk2.png"));
	CCSprite * cancelNormalSprite2 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel1.png"));
	CCSprite * cancelSelectSprite2 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel2.png"));
	CCMenuItemSprite *okMenuItem2 = CCMenuItemSprite::create(okNormalSprite2, 
		okSelectSprite2, this, menu_selector(ShopSystemLayer::pressOk));
	CCMenuItemSprite *canceldrawMenuItem2 = CCMenuItemSprite::create(cancelNormalSprite2, 
		cancelSelectSprite2, this, menu_selector(ShopSystemLayer::pressCancel));
	withdrawMenu = CCMenu::create(okMenuItem2,canceldrawMenuItem2,NULL);
	withdrawMenu->setPosition(ccp(winSize.width * 0.5, 136));	
	withdrawMenu->alignItemsHorizontallyWithPadding(20);
	this->addChild(withdrawMenu,1);
	this->setWithdrawViewVisible(false);

	/************存款**********/
	depositBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyBk.png"));
	depositBk->setAnchorPoint(ccp(0.5f,0));
	depositBk->setPosition(ccp(winSize.width/2,88));
	this->addChild(depositBk,1);

	depositText = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopDepositLabel.png"));
	depositText->setPosition(ccp(winSize.width/2,340));
	this->addChild(depositText,1);

	textWidth = 120;

	//数量标签
	depositNumLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t571"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	depositNumLabel->setColor(ccc3(255,255,255));
	depositNumLabel->setPosition(CCPointMake(241,261));
	addChild(depositNumLabel,1);

	//购买数量输入框
	depositNum = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	depositNum->setPosition(CCPoint(309, 261));
	depositNum->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	depositNum->setReturnType(kKeyboardReturnTypeGo);
	depositNum->setAnchorPoint(ccp(0,0.5f));
	depositNum->setFontColor(ccc3(0,0,0));
	//depositNum->setFontSize(20);
	addChild(depositNum,1);

	//密码标签
	depositPasswordLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t570"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	depositPasswordLabel->setColor(ccc3(255,255,255));
	depositPasswordLabel->setPosition(CCPointMake(241,202));
	addChild(depositPasswordLabel,1);

	//密码输入框
	depositPassword = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	depositPassword->setPosition(CCPoint(309, 202));
	depositPassword->setInputFlag(kEditBoxInputFlagPassword);
	depositPassword->setReturnType(kKeyboardReturnTypeGo);
	depositPassword->setAnchorPoint(ccp(0,0.5f));
	depositPassword->setFontColor(ccc3(0,0,0));
	//depositPassword->setFontSize(20);
	addChild(depositPassword,1);

	//购买确定取消菜单
	CCSprite * okNormalSprite1 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk1.png"));
	CCSprite * okSelectSprite1 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk2.png"));
	CCSprite * cancelNormalSprite1 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel1.png"));
	CCSprite * cancelSelectSprite1 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel2.png"));
	CCMenuItemSprite *okMenuItem1 = CCMenuItemSprite::create(okNormalSprite1, 
		okSelectSprite1, this, menu_selector(ShopSystemLayer::pressOk));
	CCMenuItemSprite *canceldrawMenuItem1 = CCMenuItemSprite::create(cancelNormalSprite1, 
		cancelSelectSprite1, this, menu_selector(ShopSystemLayer::pressCancel));
	depositMenu = CCMenu::create(okMenuItem1,canceldrawMenuItem1,NULL);
	depositMenu->setPosition(ccp(winSize.width * 0.5, 136));	
	depositMenu->alignItemsHorizontallyWithPadding(20);
	this->addChild(depositMenu,1);
	this->setDepositViewVisible(false);

	/************转账**********/
	transferBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyBk.png"));
	transferBk->setAnchorPoint(ccp(0.5f,0));
	transferBk->setPosition(ccp(winSize.width/2,88));
	this->addChild(transferBk,1);

	transferText = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopSendLabel.png"));
	transferText->setPosition(ccp(winSize.width/2,340));
	this->addChild(transferText,1);

	textWidth = 120;

	//转账昵称标签
	transferNickname = CCLabelTTF::create(ConfigMgr::instance()->text("t573"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	transferNickname->setColor(ccc3(255,255,255));
	transferNickname->setPosition(CCPointMake(241,286));
	addChild(transferNickname,1);

	//昵称输入框
	nickname = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	nickname->setPosition(CCPoint(309, 286));
	nickname->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	nickname->setReturnType(kKeyboardReturnTypeGo);
	nickname->setAnchorPoint(ccp(0,0.5f));
	nickname->setFontColor(ccc3(0,0,0));
	//nickname->setFontSize(20);
	addChild(nickname,1);

	//数量标签
	transferNumLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t574"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	transferNumLabel->setColor(ccc3(255,255,255));
	transferNumLabel->setPosition(CCPointMake(241,231));
	addChild(transferNumLabel,1);

	//购买数量输入框
	transferNum = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	transferNum->setPosition(CCPoint(309, 231));
	transferNum->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	transferNum->setReturnType(kKeyboardReturnTypeGo);
	transferNum->setAnchorPoint(ccp(0,0.5f));
	transferNum->setFontColor(ccc3(0,0,0));
	//transferNum->setFontSize(20);
	addChild(transferNum,1);

	//密码标签
	transferPasswordLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t570"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	transferPasswordLabel->setColor(ccc3(255,255,255));
	transferPasswordLabel->setPosition(CCPointMake(241,176));
	addChild(transferPasswordLabel,1);

	//密码输入框
	transferPassword = CCEditBox::create(CCSize(268, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
	transferPassword->setPosition(CCPoint(309, 176));
	transferPassword->setInputFlag(kEditBoxInputFlagPassword);
	transferPassword->setReturnType(kKeyboardReturnTypeGo);
	transferPassword->setAnchorPoint(ccp(0,0.5f));
	transferPassword->setFontColor(ccc3(0,0,0));
	//transferPassword->setFontSize(20);
	addChild(transferPassword,1);

	//购买确定取消菜单
	CCSprite * okNormalSprite3 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk1.png"));
	CCSprite * okSelectSprite3 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyOk2.png"));
	CCSprite * cancelNormalSprite3 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel1.png"));
	CCSprite * cancelSelectSprite3 = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyCancel2.png"));
	CCMenuItemSprite *okMenuItem3 = CCMenuItemSprite::create(okNormalSprite3, 
		okSelectSprite3, this, menu_selector(ShopSystemLayer::pressOk));
	CCMenuItemSprite *canceldrawMenuItem3 = CCMenuItemSprite::create(cancelNormalSprite3, 
		cancelSelectSprite3, this, menu_selector(ShopSystemLayer::pressCancel));
	transferMenu = CCMenu::create(okMenuItem3,canceldrawMenuItem3,NULL);
	transferMenu->setPosition(ccp(winSize.width * 0.5, 125));	
	transferMenu->alignItemsHorizontallyWithPadding(20);
	this->addChild(transferMenu,1);
	this->setSendViewVisible(false);

	this->queryBankInfo();

	setKeypadEnabled(true);
	this->setTouchEnabled(true);
}

void ShopSystemLayer::doSomething()
{
	if(buyViewVisible == true)
	{
		return;
	}
	CCLog("ShopSystemLayer::doSomething");
	if(currentItem == TabLayerBaseTag){
		maskSprite2->setVisible(true);
		maskSprite3->setVisible(true);
		coinsTable->setVisible(true);
		articleTable->setVisible(false);

		bankBk->setVisible(false);
		scoreLabel->setVisible(false);
		bankScoreLabel->setVisible(false);
		bankMenu->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+2){
		maskSprite2->setVisible(true);
		maskSprite3->setVisible(true);
		coinsTable->setVisible(false);
		articleTable->setVisible(true);

		bankBk->setVisible(false);
		scoreLabel->setVisible(false);
		bankScoreLabel->setVisible(false);
		bankMenu->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+1){
		maskSprite2->setVisible(false);
		maskSprite3->setVisible(false);
		coinsTable->setVisible(false);
		articleTable->setVisible(false);

		bankBk->setVisible(true);
		scoreLabel->setVisible(true);
		bankScoreLabel->setVisible(true);
		bankMenu->setVisible(true);
	}
}

void ShopSystemLayer::refreshView(CCObject *pObject)
{
	score = EntityMgr::instance()->getDispatch()->m_dwlUserScore;
	bankScore = EntityMgr::instance()->getDispatch()->m_dwlUserInsure;
	char str[100];
	sprintf(str, "%I64d", score);
	scoreLabel->setString(str);
	sprintf(str, "%I64d", bankScore);
	bankScoreLabel->setString(str);
	if(promptBox!=NULL)
	{
		promptBox->setPromptText(EntityMgr::instance()->getDispatch()->szDescribeString);

		char message[1024];
		time_t tt = time(NULL);//这句返回的只是一个时间cuo
		tm* t= localtime(&tt);
		sprintf(message, "insert into PersonalMsg(msg) values(\'%s     %d-%02d-%02d %02d:%02d:%02d\')", EntityMgr::instance()->getDispatch()->szDescribeString,
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		DBHandler::sharedDBHandler()->execute(message);
	}
}

void ShopSystemLayer::queryBankInfo()
{
	EntityMgr::instance()->getDispatch()->SendPacketWithQueryBankInfo();
}

void ShopSystemLayer::setBuyViewVisible(bool flag)
{
	buyViewVisible = flag;
	buyBk->setVisible(flag);
	buyText->setVisible(flag);
	buyArticleType1->setVisible(flag);
	buyArticleTypeBk->setVisible(flag);
	buyArticleType2->setVisible(flag);
	buyArticleNumLabel->setVisible(flag);
	buyArticleNum->setVisible(flag);
	buyMenu->setVisible(flag);
}

void ShopSystemLayer::setDepositViewVisible(bool flag)
{
	depositViewVisible = flag;
	depositBk->setVisible(flag);
	depositText->setVisible(flag);
	depositNumLabel->setVisible(flag);
	depositNum->setVisible(flag);
	depositPasswordLabel->setVisible(flag);
	depositPassword->setVisible(flag);
	depositMenu->setVisible(flag);
}

void ShopSystemLayer::setWithdrawViewVisible(bool flag)
{
	withdrawViewVisible = flag;
	withdrawBk->setVisible(flag);
	withdrawText->setVisible(flag);
	withdrawNumLabel->setVisible(flag);
	withdrawNum->setVisible(flag);
	withdrawPasswordLabel->setVisible(flag);
	withdrawPassword->setVisible(flag);
	withdrawMenu->setVisible(flag);
}

void ShopSystemLayer::setSendViewVisible(bool flag)
{
	sendViewVisible = flag;
	transferBk->setVisible(flag);
	transferText->setVisible(flag);
	transferNickname->setVisible(flag);
	nickname->setVisible(flag);
	transferNumLabel->setVisible(flag);
	transferNum->setVisible(flag);
	transferPasswordLabel->setVisible(flag);
	transferPassword->setVisible(flag);
	transferMenu->setVisible(flag);
}

void ShopSystemLayer::buyButton(cocos2d::CCObject *obj)
{
	if(buyViewVisible == true)
	{
		return;
	}
	int objTag = ((CCNode *)obj)->getTag();
	if(objTag == BuyButton_Coins)
	{

	}
	if(objTag == BuyButton_Article)
	{

	}
	this->setBuyViewVisible(true);
}

void ShopSystemLayer::depositButton(cocos2d::CCObject *obj)
{
	if(depositViewVisible == false)
	{
		setDepositViewVisible(true);
	}
}

void ShopSystemLayer::withdrawButton(cocos2d::CCObject *obj)
{
	if(withdrawViewVisible == false)
	{
		setWithdrawViewVisible(true);
	}
}

void ShopSystemLayer::sendButton(cocos2d::CCObject *obj)
{
	if(sendViewVisible == false)
	{
		setSendViewVisible(true);
	}
}

void ShopSystemLayer::pressOk(cocos2d::CCObject *obj)
{
	if(buyViewVisible == true){
		this->setBuyViewVisible(false);
	}else if(depositViewVisible == true){
		int inputScore = atoi(depositNum->getText());
		if(inputScore<=score)
		{
			EntityMgr::instance()->getDispatch()->SendPacketWithDeposit(inputScore);
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t556"));
			addChild(promptBox,1);
		}else{
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t577"));
			addChild(promptBox,1);
		}
		this->setDepositViewVisible(false);
	}else if(withdrawViewVisible == true){
		int inputScore = atoi(withdrawNum->getText());
		if(inputScore<=bankScore)
		{
			string passStr = withdrawPassword->getText();
			EntityMgr::instance()->getDispatch()->SendPacketWithWithdraw(inputScore, passStr);
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t556"));
			addChild(promptBox,1);
		}else{
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t577"));
			addChild(promptBox,1);
		}
		this->setWithdrawViewVisible(false);
	}else if(sendViewVisible == true){
		int inputScore = atoi(transferNum->getText());
		if(inputScore<=bankScore)
		{
			string nicknameStr = nickname->getText();
			string passStr = transferPassword->getText();
			EntityMgr::instance()->getDispatch()->SendPacketWithSendScore(nicknameStr, inputScore, passStr, 1);
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t556"));
			addChild(promptBox,1);
		}else{
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t577"));
			addChild(promptBox,1);
		}
		this->setSendViewVisible(false);
	}
}

void ShopSystemLayer::pressCancel(cocos2d::CCObject *obj)
{
	if(buyViewVisible == true){
		this->setBuyViewVisible(false);
	}else if(depositViewVisible == true){
		this->setDepositViewVisible(false);
	}else if(withdrawViewVisible == true){
		this->setWithdrawViewVisible(false);
	}else if(sendViewVisible == true){
		this->setSendViewVisible(false);
	}
}

/**单元格大小
参数：table单元格所属的表格
*/
CCSize ShopSystemLayer::cellSizeForTable(CCTableView *table)
{
	return CCSize(winSize.width, tableItemSize.height+tableGapY);
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int ShopSystemLayer::numberOfCellsInTableView(CCTableView *table)
{
	int size;
	size = coinsTableItemsNum/3;
	if(coinsTableItemsNum%3!=0)
	{
		size++;
	}
	return size;
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *ShopSystemLayer::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	char name[32];
	float startX = tableItemSize.width/2+tableGapX;
	float startY = tableItemSize.height/2+tableGapY;
	for(int i = 1 ; i < 4&&(((int)index*3+i)<=coinsTableItemsNum) ; i++)
	{
		sprintf(name, "%s%d.png", ShopCoinTableFileName, (int)index*3+i);
		CCSprite *cellBk = CCSprite::createWithSpriteFrame(spriteFrame(name));
		cellBk->setPosition(ccp(startX, startY));
		cell->addChild(cellBk);

		memset(name, 0, sizeof(name));
		sprintf(name, "%s%d_1.png", BuyCoinButtonFileName, (int)index*3+i);
		CCSprite * buyNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame(name));
		memset(name, 0, sizeof(name));
		sprintf(name, "%s%d_2.png", BuyCoinButtonFileName, (int)index*3+i);
		CCSprite * buySelectSprite = CCSprite::createWithSpriteFrame(spriteFrame(name));
		CCMenuItemSprite *buyMenuItem = CCMenuItemSprite::create(buyNormalSprite, 
			buySelectSprite, this, menu_selector(ShopSystemLayer::buyButton));
		buyMenuItem->setTag(BuyButton_Coins+index);
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
void ShopSystemLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	//CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(nameLabelTag);
	//const char *name = nameLabel->getString();
	//textField->setString(name);
	//this->removeChild(_tableView, true);
	//flag = 0;
}

void ShopSystemLayer::scrollViewDidScroll(CCScrollView* view)
{

}
void ShopSystemLayer::scrollViewDidZoom(CCScrollView* view)
{

}

/**单元格大小
参数：table单元格所属的表格
*/
ArticleTableHelper::ArticleTableHelper(CCObject *fath)
{
	father = fath;
	winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopCoinTableBk1.png"));
	tableItemSize = tempSprite->getContentSize();
	tableGapX = (winSize.width-tableItemSize.width*3)/4;
	tableGapY = 4;
	articleTableItemsNum = 7;
}

ArticleTableHelper::~ArticleTableHelper()
{

}


void ArticleTableHelper::buyButton(cocos2d::CCObject *obj)
{

}

CCSize ArticleTableHelper::cellSizeForTable(CCTableView *table)
{
	return CCSize(winSize.width, tableItemSize.height+tableGapY);
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int ArticleTableHelper::numberOfCellsInTableView(CCTableView *table)
{
	int size;
	size = articleTableItemsNum/3;
	if(articleTableItemsNum%3!=0)
	{
		size++;
	}
	return size;
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *ArticleTableHelper::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	char name[32];
	float startX = tableItemSize.width/2+tableGapX;
	float startY = tableItemSize.height/2+tableGapY;
	for(int i = 1 ; i < 4&&(((int)index*3+i)<=articleTableItemsNum) ; i++)
	{
		sprintf(name, "%s%d.png", ShopArticleTableFileName, (int)index*3+i);
		CCSprite *cellBk = CCSprite::createWithSpriteFrame(spriteFrame(name));
		cellBk->setPosition(ccp(startX, startY));
		cell->addChild(cellBk);

		memset(name, 0, sizeof(name));	
		CCSprite * buyNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyArticle1.png"));
		CCSprite * buySelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyArticle2.png"));
		CCMenuItemSprite *buyMenuItem = CCMenuItemSprite::create(buyNormalSprite, 
			buySelectSprite, father, menu_selector(ShopSystemLayer::buyButton));
		buyMenuItem->setTag(BuyButton_Article+index);
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
void ArticleTableHelper::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	//CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(nameLabelTag);
	//const char *name = nameLabel->getString();
	//textField->setString(name);
	//this->removeChild(_tableView, true);
	//flag = 0;
}

void ArticleTableHelper::scrollViewDidScroll(CCScrollView* view)
{

}
void ArticleTableHelper::scrollViewDidZoom(CCScrollView* view)
{

}

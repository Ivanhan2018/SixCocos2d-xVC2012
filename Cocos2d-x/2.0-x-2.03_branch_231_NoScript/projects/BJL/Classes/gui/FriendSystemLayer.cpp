#include "FriendSystemLayer.h"
#include "common/DBHandler.h"
#include "gui/PromptBox.h"
#include "common/GlobalDef.h"
#include "entity/EntityMgr.h"

FriendSystemLayer::FriendSystemLayer()
{
	friendStatusTable = NULL;
	myFriendTable = NULL;
	friendData = NULL;
	friendIndex = -1;
	currentFriendBk = NULL;
}

FriendSystemLayer::~FriendSystemLayer()
{
	if(friendStatusTable!=NULL)
		friendStatusTable->release();
	if(myFriendTable!=NULL)
		myFriendTable->release();
	if(friendData != NULL){
		friendData->release();
	}
}

FriendSystemLayer *FriendSystemLayer::create()
{
	CCArray *normalName = CCArray::create();
	CCArray *selectedName = CCArray::create();
	normalName->addObject(CCString::create("Tab_FriendStatus1.png"));
	selectedName->addObject(CCString::create("Tab_FriendStatus2.png"));
	normalName->addObject(CCString::create("Tab_MyFriend1.png"));
	selectedName->addObject(CCString::create("Tab_MyFriend2.png"));
	normalName->addObject(CCString::create("Tab_AddFriend1.png"));
	selectedName->addObject(CCString::create("Tab_AddFriend2.png"));
	FriendSystemLayer *tabLayer = FriendSystemLayer::createWithTabItems(normalName,selectedName);
	return tabLayer;
}

FriendSystemLayer *FriendSystemLayer::createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName)
{
	FriendSystemLayer *tabLayer = new FriendSystemLayer();
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

void FriendSystemLayer::initView()
{
	currentIndex = 0;
	winSize = CCDirector::sharedDirector()->getWinSize();
	//获取我的好友数据
	this->getMyFriendData();
	CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend1.png"));
	tableViewCellSize = tempSprite->getContentSize();
	//好友动态页面
	CCSize tableViewSize;
	tableViewSize.width = tempSprite->getContentSize().width;
	tableViewSize.height = 370;
	FriendTableHelper *helper = new FriendTableHelper();
	friendStatusTable = CCTableView::create(helper, tableViewSize);
	friendStatusTable->setDelegate(helper);
	friendStatusTable->setAnchorPoint(ccp(0.5, 0.5));
	friendStatusTable->setPosition(ccp(15, 10));
	friendStatusTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	friendStatusTable->setDirection(kCCScrollViewDirectionVertical);
	friendStatusTable->retain();
	friendStatusTable->setTag(TableTag_FriendStatus);
	this->addChild(friendStatusTable, 1);
	this->setTouchEnabled(true);
	//我的好友页面

	//用户名字
	float startX = 345;
	float startY = 350.0f;
	float gapY = 50;
	ccColor3B textColor = ccc3(255, 192, 0);
	string pTextUserName="";
	m_pUserName = CCLabelTTF::create(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t82"),pTextUserName.c_str())->getCString(),"",22);
	m_pUserName->setColor(textColor);
	m_pUserName->setAnchorPoint(CCPointMake(0,0));
	m_pUserName->setPosition(CCPointMake(startX,startY));
	addChild(m_pUserName,2);

	//用户性别
	CCSprite *pButtonBJ = CCSprite::create("dt_warning_8.png");
	const char *pTextUserSex;
	//if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
	//{
	//	pTextUserSex = CCString::createWithFormat
	//		("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t150"))->getCString();
	//}
	//else
	//{
	//	pTextUserSex = CCString::createWithFormat
	//		("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t151"))->getCString();
	//}
	pTextUserSex = CCString::createWithFormat("%s",ConfigMgr::instance()->text("t83"))->getCString();
	m_pUserSex = CCLabelTTF::create(pTextUserSex,"HelveticaNeue-Bold", 22);
	m_pUserSex->setColor(textColor);
	m_pUserSex->setAnchorPoint(CCPointMake(0,0));
	m_pUserSex->setPosition(CCPointMake(startX,startY-gapY));
	addChild(m_pUserSex,2);

	//用户金币
	//const char *pTextUserGold = CCString::createWithFormat
	//	("%s%d",ConfigMgr::instance()->text("t85"),g_GlobalUnits.getGolbalUserData()->lScore)->getCString();
	const char *pTextUserGold = CCString::createWithFormat
		("%s",ConfigMgr::instance()->text("t85"))->getCString();
	pUserGold = CCLabelTTF::create(pTextUserGold,"HelveticaNeue-Bold", 22);
	pUserGold->setColor(textColor);
	pUserGold->setAnchorPoint(CCPointMake(0,0));
	pUserGold->setPosition(CCPointMake(startX,startY-2*gapY));
	addChild(pUserGold,2);

	//用户战绩
	//const char *pTextUserRecord = CCString::createWithFormat
	//	("%s%d%s/%d%s",ConfigMgr::instance()->text("t88"),g_GlobalUnits.getGolbalUserData()->lWinCount,ConfigMgr::instance()->text("t165"),g_GlobalUnits.getGolbalUserData()->lLostCount,ConfigMgr::instance()->text("t166"))->getCString();
	const char *pTextUserRecord = CCString::createWithFormat
		("%s%s%s/%s%s",ConfigMgr::instance()->text("t88")," ",ConfigMgr::instance()->text("t165")," ",ConfigMgr::instance()->text("t166"))->getCString();
	pUserRecord = CCLabelTTF::create(pTextUserRecord,"HelveticaNeue-Bold", 22);
	pUserRecord->setColor(textColor);
	pUserRecord->setAnchorPoint(CCPointMake(0,0));
	pUserRecord->setPosition(CCPointMake(startX,startY-3*gapY));
	addChild(pUserRecord,2);

	//用户胜率
	const char *pTextUserWinning;
	//if(g_GlobalUnits.getGolbalUserData()->lTotalCount == 0)
	//{
	//	pTextUserWinning = CCString::createWithFormat
	//		("%s%d%%",ConfigMgr::instance()->text("t89"),0)->getCString();
	//}
	//else
	//{
	//	pTextUserWinning = CCString::createWithFormat
	//		("%s%.2f%%",ConfigMgr::instance()->text("t89"),((float)g_GlobalUnits.getGolbalUserData()->lWinCount/(float)g_GlobalUnits.getGolbalUserData()->lTotalCount)*100)->getCString();
	//}
	//pTextUserWinning = CCString::createWithFormat
	//	("%s%d%%",ConfigMgr::instance()->text("t89"),0)->getCString();
	pTextUserWinning = CCString::createWithFormat
		("%s",ConfigMgr::instance()->text("t89"))->getCString();
	pUserWinning = CCLabelTTF::create(pTextUserWinning,"HelveticaNeue-Bold", 22);
	pUserWinning->setColor(textColor);
	pUserWinning->setAnchorPoint(CCPointMake(0,0));
	pUserWinning->setPosition(CCPointMake(startX,startY-4*gapY));
	addChild(pUserWinning,2);

	CCSprite *sendItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendSend1.png"));
	CCSprite *sendItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendSend2.png"));
	CCSprite *deleteItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendDelete1.png"));
	CCSprite *deleteItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendDelete2.png"));
	CCSprite *chatItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendChat1.png"));
	CCSprite *chatItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendChat2.png"));
	CCMenuItemSprite *sendItem = CCMenuItemSprite::create(sendItemNormalImage,sendItemSelectedImage,this,menu_selector(FriendSystemLayer::sendButton));
	CCMenuItemSprite *deleteItem = CCMenuItemSprite::create(deleteItemNormalImage,deleteItemSelectedImage,this,menu_selector(FriendSystemLayer::deleteButton));
	CCMenuItemSprite *chatItem = CCMenuItemSprite::create(chatItemNormalImage,chatItemSelectedImage,this,menu_selector(FriendSystemLayer::chatButton));
	myFriendOperaMenu = CCMenu::create(sendItem,deleteItem,chatItem,NULL);	
	myFriendOperaMenu->setPosition(ccp(555, 42));	
	myFriendOperaMenu->alignItemsHorizontallyWithPadding(4);//设置排列方式，纵向间隔20
	this->addChild(myFriendOperaMenu,2);

	tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend3.png"));
	tableViewSize.width = tempSprite->getContentSize().width;
	tableViewSize.height = 370;
	myFriendTable = CCTableView::create(this, tableViewSize);
	myFriendTable->setDelegate(this);
	myFriendTable->setAnchorPoint(ccp(0.5, 0.5));
	myFriendTable->setPosition(ccp(15, 10));
	myFriendTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	myFriendTable->setDirection(kCCScrollViewDirectionVertical);
	myFriendTable->retain();
	myFriendTable->setTag(TableTag_MyFriend);
	this->addChild(myFriendTable, 1);

	myFriendBk = CCSprite::create("background/Bk_Friend.png");
	myFriendBk->setAnchorPoint(ccp(1,0));
	myFriendBk->setPosition(ccp(800-3, 1));
	this->addChild(myFriendBk,1);	

	m_pUserName->setVisible(false);		
	m_pUserSex->setVisible(false);		
	pUserGold->setVisible(false);						
	pUserRecord->setVisible(false);				
	pUserWinning->setVisible(false);
	myFriendTable->setVisible(false);
	myFriendBk->setVisible(false);
	myFriendOperaMenu->setVisible(false);

	//添加好友
	//好友ID
	float textWidth = 500;
	addFriendID = CCLabelTTF::create(ConfigMgr::instance()->text("t557"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	addFriendID->setColor(ccc3(255,255,255));
	addFriendID->setAnchorPoint(ccp(0,0.5f));
	addFriendID->setPosition(CCPointMake(115,268));
	addChild(addFriendID, 1);
	//好友输入框
	friendAccount = CCEditBox::create(CCSize(389, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_Notice2.png")));
	friendAccount->setPosition(CCPoint(233, 268));
	friendAccount->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	friendAccount->setReturnType(kKeyboardReturnTypeGo);
	friendAccount->setAnchorPoint(ccp(0,0.5f));
	friendAccount->setFontColor(ccc3(0,0,0));
	//friendAccount->setFontSize(20);
	friendAccount->setPlaceHolder(ConfigMgr::instance()->text("t557"));
	addChild(friendAccount, 1);
	//添加按钮
	CCSprite * getCoinsNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendAdd1.png"));
	CCSprite * getCoinsSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendAdd2.png"));
	CCSprite * getCoinsDisSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_FriendAdd2.png"));
	getCoinsDisSprite->setColor(ccc3(100,100,100));
	CCMenuItemSprite *getCoinsMenuItem = CCMenuItemSprite::create(getCoinsNormalSprite, 
		getCoinsSelectSprite, this, menu_selector(FriendSystemLayer::pressAddButton));
	addButton = CCMenu::create(getCoinsMenuItem,NULL);
	addButton->setAnchorPoint(ccp(0,0));
	addButton->setPosition(ccp(368, 175));
	addChild(addButton, 1);

	addFriendID->setVisible(false);
	friendAccount->setVisible(false);
	addButton->setVisible(false);

	setKeypadEnabled(true);
	//setTouchEnabled(true);
}

void FriendSystemLayer::getMyFriendData()
{
	friendData = CCArray::create();
	friendData->retain();
	DBHandler *handler = new DBHandler();
	//char sql[800] = {0};
	sqlite3 *DB = handler->getDB();
	sqlite3_stmt *stmt;
	int rv = sqlite3_prepare(DB, "select * from FriendInfo", 100, &stmt, NULL);
	rv = sqlite3_step(stmt);
	while(rv == SQLITE_ROW)
	{
		DWORD dwUserID = sqlite3_column_int(stmt, 0);
		WORD wFaceID = sqlite3_column_int(stmt, 1);
		BYTE cbGender = sqlite3_column_int(stmt, 2);
		BYTE cbMemberOrder = sqlite3_column_int(stmt, 3);
		LONG lScore = sqlite3_column_int(stmt, 4);
		LONG lWinCount = sqlite3_column_int(stmt, 5);
		LONG lLostCount = sqlite3_column_int(stmt, 6);
		LONG lDrawCount = sqlite3_column_int(stmt, 7);
		LONG lFleeCount = sqlite3_column_int(stmt, 8);
		LONG lExperience = sqlite3_column_int(stmt, 9);
		char szNickName[NAME_LEN];
		memcpy(szNickName, sqlite3_column_text(stmt, 10), NAME_LEN);
		CCDictionary *dictionary = CCDictionary::create();
		dictionary->setObject(CCInteger::create(dwUserID), "dwUserID");
		dictionary->setObject(CCInteger::create(wFaceID), "wFaceID");
		dictionary->setObject(CCInteger::create(cbGender), "cbGender");
		dictionary->setObject(CCInteger::create(cbMemberOrder), "cbMemberOrder");
		dictionary->setObject(CCInteger::create(lScore), "lScore");
		dictionary->setObject(CCInteger::create(lWinCount), "lWinCount");
		dictionary->setObject(CCInteger::create(lLostCount), "lLostCount");
		dictionary->setObject(CCInteger::create(lDrawCount), "lDrawCount");
		dictionary->setObject(CCInteger::create(lFleeCount), "lFleeCount");
		dictionary->setObject(CCInteger::create(lWinCount+lLostCount+lDrawCount+lFleeCount), "lTotalCount");
		dictionary->setObject(CCInteger::create(lExperience), "lExperience");
		dictionary->setObject(CCString::create(szNickName), "szNickName");
		friendData->addObject(dictionary);
		rv = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	//if(friendData>0)
	//{
	//	friendIndex = 0;
	//}
}

void FriendSystemLayer::addMyFriendData(DWORD dwUserID)
{
	DBHandler *handler = new DBHandler();
	char sql[200] = {0};
	sqlite3 *DB = handler->getDB();
	sqlite3_stmt *stmt;
	sprintf(sql, "select * from FriendInfo where dwUserID=%lu", dwUserID);
	int rv = sqlite3_prepare(DB, sql, 200, &stmt, NULL);
	rv = sqlite3_step(stmt);
	if(rv == SQLITE_ROW)
	{
		DWORD dwUserID = sqlite3_column_int(stmt, 0);
		WORD wFaceID = sqlite3_column_int(stmt, 1);
		BYTE cbGender = sqlite3_column_int(stmt, 2);
		BYTE cbMemberOrder = sqlite3_column_int(stmt, 3);
		LONG lScore = sqlite3_column_int(stmt, 4);
		LONG lWinCount = sqlite3_column_int(stmt, 5);
		LONG lLostCount = sqlite3_column_int(stmt, 6);
		LONG lDrawCount = sqlite3_column_int(stmt, 7);
		LONG lFleeCount = sqlite3_column_int(stmt, 8);
		LONG lExperience = sqlite3_column_int(stmt, 9);
		char szNickName[NAME_LEN];
		memcpy(szNickName, sqlite3_column_text(stmt, 10), NAME_LEN);
		CCDictionary *dictionary = CCDictionary::create();
		dictionary->setObject(CCInteger::create(dwUserID), "dwUserID");
		dictionary->setObject(CCInteger::create(wFaceID), "wFaceID");
		dictionary->setObject(CCInteger::create(cbGender), "cbGender");
		dictionary->setObject(CCInteger::create(cbMemberOrder), "cbMemberOrder");
		dictionary->setObject(CCInteger::create(lScore), "lScore");
		dictionary->setObject(CCInteger::create(lWinCount), "lWinCount");
		dictionary->setObject(CCInteger::create(lLostCount), "lLostCount");
		dictionary->setObject(CCInteger::create(lDrawCount), "lDrawCount");
		dictionary->setObject(CCInteger::create(lFleeCount), "lFleeCount");
		dictionary->setObject(CCInteger::create(lWinCount+lLostCount+lDrawCount+lFleeCount), "lTotalCount");
		dictionary->setObject(CCInteger::create(lExperience), "lExperience");
		dictionary->setObject(CCString::create(szNickName), "szNickName");
		bool hasInsert = false;
		int i = 0;
		for(i = 0; i < friendData->count() ; i++)
		{
			CCDictionary *dic = (CCDictionary *)friendData->objectAtIndex(i);
			DWORD userID = ((CCInteger *)dic->objectForKey("dwUserID"))->getValue();
			if(dwUserID<userID)
			{
				friendData->insertObject(dictionary, i);
				hasInsert = true;
				break;
			}
		}
		if(hasInsert == false)
		{
			friendData->insertObject(dictionary, i);
		}
		rv = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	myFriendTable->reloadData();
}

void FriendSystemLayer::showFriendInfo(int index)
{
	friendIndex = index;
	CCDictionary *dic = (CCDictionary *)friendData->objectAtIndex(index);
	CCString *szNickName = (CCString *)dic->objectForKey("szNickName");
	CCInteger *cbGender = (CCInteger *)dic->objectForKey("cbGender");
	CCInteger *lScore = (CCInteger *)dic->objectForKey("lScore");
	CCInteger *lWinCount = (CCInteger *)dic->objectForKey("lWinCount");
	CCInteger *lLostCount = (CCInteger *)dic->objectForKey("lLostCount");
	CCInteger *lTotalCount = (CCInteger *)dic->objectForKey("lTotalCount");

	m_pUserName->setString(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t82"),szNickName->getCString())->getCString());		

	const char *pTextUserSex;
	if(cbGender->getValue() == 1)
	{
		pTextUserSex = CCString::createWithFormat
			("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t150"))->getCString();
	}
	else
	{
		pTextUserSex = CCString::createWithFormat
			("%s%s",ConfigMgr::instance()->text("t83"),ConfigMgr::instance()->text("t151"))->getCString();
	}
	m_pUserSex->setString(pTextUserSex);

	const char *pTextUserGold = CCString::createWithFormat
		("%s%d",ConfigMgr::instance()->text("t85"),lScore->getValue())->getCString();
	pUserGold->setString(pTextUserGold);

	const char *pTextUserRecord = CCString::createWithFormat
		("%s%d%s/%d%s",ConfigMgr::instance()->text("t88"),lWinCount->getValue(),ConfigMgr::instance()->text("t165"),lLostCount->getValue(),ConfigMgr::instance()->text("t166"))->getCString();
	pUserRecord->setString(pTextUserRecord);

	const char *pTextUserWinning;
	if(lTotalCount->getValue() == 0)
	{
		pTextUserWinning = CCString::createWithFormat
			("%s%d%%",ConfigMgr::instance()->text("t89"),0)->getCString();
	}
	else
	{
		pTextUserWinning = CCString::createWithFormat
			("%s%.2f%%",ConfigMgr::instance()->text("t89"),((float)lWinCount->getValue()/(float)lTotalCount->getValue())*100)->getCString();
	}
	pUserWinning->setString(pTextUserWinning);
}

void FriendSystemLayer::doSomething()
{
	CCLog("FriendSystemLayer::doSomething");
	if(currentItem == TabLayerBaseTag){
		friendStatusTable->setVisible(true);
		myFriendTable->setVisible(false);
		myFriendOperaMenu->setVisible(false);
		myFriendBk->setVisible(false);
		addFriendID->setVisible(false);
		friendAccount->setVisible(false);
		addButton->setVisible(false);

		m_pUserName->setVisible(false);		
		m_pUserSex->setVisible(false);		
		pUserGold->setVisible(false);						
		pUserRecord->setVisible(false);				
		pUserWinning->setVisible(false);				
	}else if(currentItem == TabLayerBaseTag+1){
		friendStatusTable->setVisible(false);
		myFriendTable->setVisible(true);
		myFriendOperaMenu->setVisible(true);
		myFriendBk->setVisible(true);

		m_pUserName->setVisible(true);		
		m_pUserSex->setVisible(true);		
		pUserGold->setVisible(true);						
		pUserRecord->setVisible(true);				
		pUserWinning->setVisible(true);

		addFriendID->setVisible(false);
		friendAccount->setVisible(false);
		addButton->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+2){
		friendStatusTable->setVisible(false);
		myFriendTable->setVisible(false);
		myFriendOperaMenu->setVisible(false);
		myFriendBk->setVisible(false);
		addFriendID->setVisible(true);
		friendAccount->setVisible(true);
		addButton->setVisible(true);

		m_pUserName->setVisible(false);		
		m_pUserSex->setVisible(false);		
		pUserGold->setVisible(false);						
		pUserRecord->setVisible(false);				
		pUserWinning->setVisible(false);
	}
}

void FriendSystemLayer::sendButton(cocos2d::CCObject *obj)
{
	CCDictionary *dictionary = (CCDictionary *)friendData->objectAtIndex(currentIndex);
	CCInteger *userID = (CCInteger *)dictionary->objectForKey("dwUserID");
	int id = userID->getValue();
	EntityMgr::instance()->getDispatch()->SendPacketWithSendScore(CCString::createWithFormat("%d", userID->getValue())->getCString(), 1000, EntityMgr::instance()->getDispatch()->m_szPassword, 0);
}

void FriendSystemLayer::deleteButton(cocos2d::CCObject *obj)
{

}

void FriendSystemLayer::chatButton(cocos2d::CCObject *obj)
{

}

void FriendSystemLayer::pressAddButton(cocos2d::CCObject *obj)
{
	DBHandler *handler = new DBHandler();
	string szNickName = friendAccount->getText();
	char sql[800] = {0};
	sqlite3 *DB = handler->getDB();
	sqlite3_stmt *stmt;
	sprintf(sql, "select * from UserInfo where nickname=\'%s\'", szNickName.c_str());
	int rv = sqlite3_prepare(DB, sql, 200, &stmt, NULL);
	rv = sqlite3_step(stmt);
	if(rv != SQLITE_ROW)
	{
		sqlite3_finalize(stmt);
		PromptBox *promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
		promptBox->setPromptText(ConfigMgr::instance()->text("t580"));
		addChild(promptBox,1);
		return;
	}

	DWORD userID = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	handler = new DBHandler();
	bool existBefore = handler->isRecordExisted("FriendInfo", userID);
	if(existBefore == false){
		sprintf(sql, "insert into FriendInfo(dwUserID,wFaceID,cbGender,cbMemberOrder,lScore,dwWinCount,dwLostCount,dwDrawCount,dwFleeCount,dwExperience,nickname) select %lu,0,0,0,0,0,0,0,0,0,'' where not exists(select * from FriendInfo where dwUserID=%lu)", userID, userID);
		handler->execute(sql);
	}
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "INSERT OR REPLACE INTO FriendInfo(dwUserID,wFaceID,cbGender,cbMemberOrder,lScore,dwWinCount,dwLostCount,dwDrawCount,dwFleeCount,dwExperience,nickname) SELECT UserInfo.dwUserID,UserInfo.wFaceID,UserInfo.cbGender,UserInfo.cbMemberOrder,UserInfo.lScore,UserInfo.dwWinCount,UserInfo.dwLostCount,UserInfo.dwDrawCount,UserInfo.dwFleeCount,UserInfo.dwExperience,UserInfo.nickname FROM UserInfo,FriendInfo WHERE UserInfo.dwUserID = FriendInfo.dwUserID and UserInfo.dwUserID=%lu", userID);
	handler->execute(sql);

	bool existAfter = handler->isRecordExisted("FriendInfo", userID);
	if(existAfter == true){
		if(existBefore == false)
		{
			this->addMyFriendData(userID);
			PromptBox *promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t579"));
			addChild(promptBox,1);
			bool bRet = handler->isRecordExisted("FriendStatus", userID);
			if(bRet == false)
			{
				memset(sql, 0, sizeof(sql));
				string str = ConfigMgr::instance()->text("t581");
				sprintf(sql, "insert into FriendStatus(dwUserID,status) values (%lu,\'%s %s\')", userID, szNickName.c_str(),str.c_str());
				handler->execute(sql);
			}
		}else
		{
		PromptBox *promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
		promptBox->setPromptText(ConfigMgr::instance()->text("t588"));
		addChild(promptBox,1);
		}
	}else{
		PromptBox *promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
		promptBox->setPromptText(ConfigMgr::instance()->text("t580"));
		addChild(promptBox,1);
	}
}

/**单元格大小
参数：table单元格所属的表格
*/
CCSize FriendSystemLayer::cellSizeForTable(CCTableView *table)
{
	CCSprite *tempSprite;
	tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend3.png"));
	CCSize size = tempSprite->getContentSize();
	size.width+=5;
	return size;
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int FriendSystemLayer::numberOfCellsInTableView(CCTableView *table)
{
	return friendData->count();
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *FriendSystemLayer::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = cell->getPosition();
	CCSprite *bk;
	bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend3.png"));

	bk->setAnchorPoint(ccp(0,0));
	bk->setPosition(ccp(0,2.5f));
	cell->addChild(bk);
	if(index == 0)
	{
		if(currentFriendBk!=NULL)
		{
			currentFriendBk->removeFromParentAndCleanup(true);
		}
		currentFriendBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend2.png"));
		currentFriendBk->setAnchorPoint(ccp(0,0));
		currentFriendBk->setPosition(bk->getPosition());
		cell->addChild(currentFriendBk);
		this->showFriendInfo(0);
	}

	CCDictionary *dic = (CCDictionary *)friendData->objectAtIndex(index);
	CCString *nameCCStr = (CCString *)dic->objectForKey("szNickName");
	int cbGender = ((CCInteger *)dic->objectForKey("cbGender"))->getValue();
	int wFaceID = ((CCInteger *)dic->objectForKey("wFaceID"))->getValue();

	const char* pSZPhonoName;
	if(cbGender == 1)
	{
		if(wFaceID > 1)
		{
			wFaceID = 0;
		}
		pSZPhonoName = CCString::createWithFormat("dt_register_10.png")->getCString();
	}
	else
	{
		if(wFaceID > 1)
		{
			wFaceID = 0;
		}
		pSZPhonoName = CCString::createWithFormat("dt_register_8.png")->getCString();
	}
	CCSprite *m_pPlayerPhoto;						//用户头像
	m_pPlayerPhoto = CCSprite::create(pSZPhonoName);
	m_pPlayerPhoto->setAnchorPoint(ccp(0,0.5));
	m_pPlayerPhoto->setPosition(CCPointMake(5,tableViewCellSize.height/2));
	cell->addChild(m_pPlayerPhoto,1);

	CCLabelTTF *nameLabel = CCLabelTTF::create(nameCCStr->getCString(), "Arial", 30);
	nameLabel->setColor(ccc3(255,0,0));
	nameLabel->setAnchorPoint(ccp(0,0.5));
	nameLabel->setPosition(ccp(80, tableViewCellSize.height/2));
	cell->addChild(nameLabel, 1);
	cell->setTag(index);
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void FriendSystemLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	if(currentFriendBk!=NULL)
	{
		currentFriendBk->removeFromParentAndCleanup(true);
	}
	currentFriendBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend2.png"));
	currentFriendBk->setAnchorPoint(ccp(0,0));
	currentFriendBk->setPosition(ccp(0,2.5f));
	cell->addChild(currentFriendBk);
	currentIndex = cell->getTag();
	this->showFriendInfo(cell->getTag());
}

void FriendSystemLayer::scrollViewDidScroll(CCScrollView* view)
{

}
void FriendSystemLayer::scrollViewDidZoom(CCScrollView* view)
{

}


FriendTableHelper::FriendTableHelper()
{
	friendStatusData = NULL;
	this->getFriendStatus();
}

FriendTableHelper::~FriendTableHelper()
{
	if(friendStatusData!=NULL)
		friendStatusData->release();
}

void FriendTableHelper::getFriendStatus()
{
	friendStatusData = CCArray::create();
	friendStatusData->retain();
	DBHandler *handler = new DBHandler();
	//char sql[800] = {0};
	sqlite3 *DB = handler->getDB();
	sqlite3_stmt *stmt;
	int rv = sqlite3_prepare(DB, "select * from FriendStatus", 100, &stmt, NULL);
	rv = sqlite3_step(stmt);
	while(rv == SQLITE_ROW)
	{
		char status[300] = {0};
		memcpy(status, sqlite3_column_text(stmt, 1), 300);
		friendStatusData->addObject(CCString::createWithFormat("%s", status));
		rv = sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
}

/**单元格大小
参数：table单元格所属的表格
*/
CCSize FriendTableHelper::cellSizeForTable(CCTableView *table)
{
	CCSprite *tempSprite;
	tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend1.png"));
	CCSize size = tempSprite->getContentSize();
	size.width+=5;
	return size;
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int FriendTableHelper::numberOfCellsInTableView(CCTableView *table)
{
	return friendStatusData->count();
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *FriendTableHelper::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	char name[32];
	sprintf(name, "%d line", index);
	CCSprite *bk;

	bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend1.png"));
	bk->setAnchorPoint(ccp(0,0));
	bk->setPosition(ccp(0,2.5f));
	cell->addChild(bk);

	CCString *status = (CCString *)friendStatusData->objectAtIndex(index);
	CCLabelTTF *nameLabel = CCLabelTTF::create(status->getCString(), "Arial", 30);
	nameLabel->setColor(ccc3(255,0,0));
	nameLabel->setAnchorPoint(ccp(0,0.5f));
	nameLabel->setPosition(ccp(10, bk->getContentSize().height/2+2.5f));
	CCPoint pos = cell->getPosition();
	cell->addChild(nameLabel);
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void FriendTableHelper::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{

}

void FriendTableHelper::scrollViewDidScroll(CCScrollView* view)
{

}
void FriendTableHelper::scrollViewDidZoom(CCScrollView* view)
{

}

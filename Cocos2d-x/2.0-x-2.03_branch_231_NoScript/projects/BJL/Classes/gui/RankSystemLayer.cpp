#include "RankSystemLayer.h"
#include "common/JsonHelper.h"
#include "entity/EntityMgr.h"

RankSystemLayer::RankSystemLayer()
{
	richTable = NULL;
	heroTable = NULL;
	luckTable = NULL;
	teacherTable = NULL;
	charmTable = NULL;
}

RankSystemLayer::~RankSystemLayer()
{

}

void RankSystemLayer::OnExit()
{
	if(richTable!=NULL)
		richTable->release();
	if(heroTable!=NULL)
		heroTable->release();
	if(luckTable!=NULL)
		luckTable->release();
	if(teacherTable!=NULL)
		teacherTable->release();
	if(charmTable!=NULL)
		charmTable->release();
}

RankSystemLayer *RankSystemLayer::create()
{
	CCArray *normalName = CCArray::create();
	CCArray *selectedName = CCArray::create();
	normalName->addObject(CCString::create("Tab_RichBoard1.png"));
	selectedName->addObject(CCString::create("Tab_RichBoard2.png"));
	normalName->addObject(CCString::create("Tab_HeroBoard1.png"));
	selectedName->addObject(CCString::create("Tab_HeroBoard2.png"));
	normalName->addObject(CCString::create("Tab_LuckBoard1.png"));
	selectedName->addObject(CCString::create("Tab_LuckBoard2.png"));
	normalName->addObject(CCString::create("Tab_TeacherBoard1.png"));
	selectedName->addObject(CCString::create("Tab_TeacherBoard2.png"));
	normalName->addObject(CCString::create("Tab_CharmBoard1.png"));
	selectedName->addObject(CCString::create("Tab_CharmBoard2.png"));
	return RankSystemLayer::createWithTabItems(normalName, selectedName);
}

RankSystemLayer *RankSystemLayer::createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName)
{
	RankSystemLayer *tabLayer = new RankSystemLayer();
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

void RankSystemLayer::initView()
{
	richRankText = ConfigMgr::instance()->text("t578");
	heroRankText = heroRankText;
	luckRankText = heroRankText;
	teacherRankText = heroRankText;
	charmRankText = heroRankText;

	float gapX = 11;
	float gapY = 10;
	winSize = CCDirector::sharedDirector()->getWinSize();
	winSize.width -= gapX*2;

	CCSize tableViewSize;
	tableViewSize.width = winSize.width;
	tableViewSize.height = 225;

	myRankBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board6.png"));
	tableItemSize.width = winSize.width;
	tableItemSize.height = myRankBk->getContentSize().height;
	//我的排行背景图
	myRankBk->setAnchorPoint(ccp(0.5,0.5));
	myRankBk->setScaleX(winSize.width/myRankBk->getContentSize().width);
	myRankBk->setScaleY(0.75f);
	myRankBk->setPosition(ccp(400, tableViewSize.height+gapY+tableItemSize.height*0.75f*0.5f));
	this->addChild(myRankBk,1);	

	float textWidth = 200;
	myRankLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t560"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentRight);
	myRankLabel1->setColor(ccc3(255,255,255));
	myRankLabel1->setAnchorPoint(ccp(1,0.5f));
	myRankLabel1->setPosition(ccp(myRankBk->getPositionX(), myRankBk->getPositionY()-1));
	this->addChild(myRankLabel1, 1);

	myRankLabel2 = CCLabelTTF::create(richRankText.c_str(),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	myRankLabel2->setColor(ccc3(255,255,255));
	myRankLabel2->setAnchorPoint(ccp(0,0.5f));
	myRankLabel2->setPosition(myRankLabel1->getPosition());
	this->addChild(myRankLabel2, 1);
	//排行上方图片
	rankBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board5.png"));
	rankBk->setAnchorPoint(ccp(0.5,0.5));
	rankBk->setPosition(ccp(400, tableViewSize.height+gapY+tableItemSize.height*0.75f+rankBk->getContentSize().height/2-30));
	this->addChild(rankBk,1);	
	float value = 21;
	myRankFieldLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t561"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	myRankFieldLabel1->setColor(ccc3(255,255,255));
	myRankFieldLabel1->setPosition(ccp(118, rankBk->getPositionY()-value));
	this->addChild(myRankFieldLabel1, 1);

	myRankFieldLabel2 = CCLabelTTF::create(ConfigMgr::instance()->text("t562"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	myRankFieldLabel2->setColor(ccc3(255,255,255));
	myRankFieldLabel2->setPosition(ccp(244, myRankFieldLabel1->getPositionY()));
	this->addChild(myRankFieldLabel2, 1);

	myRankFieldLabel3 = CCLabelTTF::create(ConfigMgr::instance()->text("t563"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	myRankFieldLabel3->setColor(ccc3(255,255,255));
	myRankFieldLabel3->setPosition(ccp(428, myRankFieldLabel1->getPositionY()));
	this->addChild(myRankFieldLabel3, 1);

	myRankFieldLabel4 = CCLabelTTF::create(ConfigMgr::instance()->text("t564"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	myRankFieldLabel4->setColor(ccc3(255,255,255));
	myRankFieldLabel4->setPosition(ccp(624, myRankFieldLabel1->getPositionY()));
	this->addChild(myRankFieldLabel4, 1);
	
	RankTableHelper *richTableHelper;
	RankTableHelper *heroTableHelper;
	RankTableHelper *luckTableHelper;
	RankTableHelper *teacherTableHelper;
	RankTableHelper *charmTableHelper;
	//财富榜
	richTableHelper = new RankTableHelper(this, 8, RankTableTag_Rich);
	richTable = CCTableView::create(richTableHelper, tableViewSize);
	richTable->setDelegate(richTableHelper);
	richTable->setAnchorPoint(ccp(0.5, 0.5));
	richTable->setPosition(ccp(gapX, gapY));
	richTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	richTable->setDirection(kCCScrollViewDirectionVertical);
	richTable->retain();
	this->addChild(richTable, 1);
	//英雄榜
	heroTableHelper = new RankTableHelper(this, 8, RankTableTag_Hero);
	heroTable = CCTableView::create(heroTableHelper, tableViewSize);
	heroTable->setDelegate(heroTableHelper);
	heroTable->setAnchorPoint(ccp(0.5, 0.5));
	heroTable->setPosition(ccp(gapX, gapY));
	heroTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	heroTable->setDirection(kCCScrollViewDirectionVertical);
	heroTable->retain();
	this->addChild(heroTable, 1);
	heroTable->setVisible(false);
	//鸿运榜
	luckTableHelper = new RankTableHelper(this, 10, RankTableTag_Luck);
	luckTable = CCTableView::create(luckTableHelper, tableViewSize);
	luckTable->setDelegate(luckTableHelper);
	luckTable->setAnchorPoint(ccp(0.5, 0.5));
	luckTable->setPosition(ccp(gapX, gapY));
	luckTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	luckTable->setDirection(kCCScrollViewDirectionVertical);
	luckTable->retain();
	this->addChild(luckTable, 1);
	luckTable->setVisible(false);
	//名师榜
	teacherTableHelper = new RankTableHelper(this, 12, RankTableTag_Teacher);
	teacherTable = CCTableView::create(teacherTableHelper, tableViewSize);
	teacherTable->setDelegate(teacherTableHelper);
	teacherTable->setAnchorPoint(ccp(0.5, 0.5));
	teacherTable->setPosition(ccp(gapX, gapY));
	teacherTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	teacherTable->setDirection(kCCScrollViewDirectionVertical);
	teacherTable->retain();
	this->addChild(teacherTable, 1);
	teacherTable->setVisible(false);
	//魅力榜
	charmTableHelper = new RankTableHelper(this, 14, RankTableTag_Charm);
	charmTable = CCTableView::create(charmTableHelper, tableViewSize);
	charmTable->setDelegate(charmTableHelper);
	charmTable->setAnchorPoint(ccp(0.5, 0.5));
	charmTable->setPosition(ccp(gapX, gapY));
	charmTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	charmTable->setDirection(kCCScrollViewDirectionVertical);
	charmTable->retain();
	this->addChild(charmTable, 1);
	charmTable->setVisible(false);


	richTable->reloadData();
	heroTable->reloadData();
	luckTable->reloadData();
	teacherTable->reloadData();
	charmTable->reloadData();

	setKeypadEnabled(true);
	this->setTouchEnabled(true);
	//setTouchEnabled(true);
	flag = false;
}

void RankSystemLayer::doSomethingBeforeClosed()
{
	flag = true;
}

void RankSystemLayer::doSomething()
{
	CCLog("RankSystemLayer::doSomething");
	if(currentItem == TabLayerBaseTag){
		myRankFieldLabel4->setString(ConfigMgr::instance()->text("t564"));
		richTable->setVisible(true);
		heroTable->setVisible(false);
		luckTable->setVisible(false);
		teacherTable->setVisible(false);
		charmTable->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+1){
		myRankFieldLabel4->setString(ConfigMgr::instance()->text("t565"));
		richTable->setVisible(false);
		heroTable->setVisible(true);
		luckTable->setVisible(false);
		teacherTable->setVisible(false);
		charmTable->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+2){
		myRankFieldLabel4->setString(ConfigMgr::instance()->text("t566"));
		richTable->setVisible(false);
		heroTable->setVisible(false);
		luckTable->setVisible(true);
		teacherTable->setVisible(false);
		charmTable->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+3){
		myRankFieldLabel4->setString(ConfigMgr::instance()->text("t567"));
		richTable->setVisible(false);
		heroTable->setVisible(false);
		luckTable->setVisible(false);
		teacherTable->setVisible(true);
		charmTable->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+4){
		myRankFieldLabel4->setString(ConfigMgr::instance()->text("t568"));
		richTable->setVisible(false);
		heroTable->setVisible(false);
		luckTable->setVisible(false);
		teacherTable->setVisible(false);
		charmTable->setVisible(true);
	}
	if(currentItem == TabLayerBaseTag){
		myRankLabel2->setString(richRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+1){
		myRankLabel2->setString(heroRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+2){
		myRankLabel2->setString(luckRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+3){
		myRankLabel2->setString(teacherRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+4){
		myRankLabel2->setString(charmRankText.c_str());
	}
}

void RankSystemLayer::setMyRankText(string text, RankTableTag tag)
{
	if(flag == true){
		return;
	}
	if(tag == RankTableTag_Rich)
	{
		richRankText = text;
	}else if(tag == RankTableTag_Hero)
	{
		heroRankText = text;
	}else if(tag == RankTableTag_Luck)
	{
		luckRankText = text;
	}else if(tag == RankTableTag_Teacher)
	{
		teacherRankText = text;
	}else if(tag == RankTableTag_Charm)
	{
		charmRankText = text;
	}
	if(currentItem == TabLayerBaseTag){
		myRankLabel2->setString(richRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+1){
		myRankLabel2->setString(heroRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+2){
		myRankLabel2->setString(luckRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+3){
		myRankLabel2->setString(teacherRankText.c_str());
	}else if(currentItem == TabLayerBaseTag+4){
		myRankLabel2->setString(charmRankText.c_str());
	}
}

void RankSystemLayer::reloadData(RankTableTag tag)
{
	if(flag == true){
		return;
	}
	if(tag == RankTableTag_Rich)
	{
		richTable->reloadData();
	}else if(tag == RankTableTag_Hero)
	{
		heroTable->reloadData();
	}else if(tag == RankTableTag_Luck)
	{
		luckTable->reloadData();
	}else if(tag == RankTableTag_Teacher)
	{
		teacherTable->reloadData();
	}else if(tag == RankTableTag_Charm)
	{
		charmTable->reloadData();
	}
}

void RankSystemLayer::sendButton(cocos2d::CCObject *obj)
{

}

void RankSystemLayer::deleteButton(cocos2d::CCObject *obj)
{

}

void RankSystemLayer::chatButton(cocos2d::CCObject *obj)
{

}

void RankSystemLayer::pressAddButton(cocos2d::CCObject *obj)
{

}
/**单元格大小
参数：table单元格所属的表格
*/
CCSize RankSystemLayer::cellSizeForTable(CCTableView *table)
{
	return tableItemSize;
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int RankSystemLayer::numberOfCellsInTableView(CCTableView *table)
{
	int size;
	size = 20;
	return size;
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *RankSystemLayer::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	//背景图
	CCSprite *bk;
	if(index%2 == 1){
		bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board6.png"));
	}else{
		bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board7.png"));
	}
	bk->setScaleX(winSize.width/bk->getContentSize().width);
	bk->setAnchorPoint(ccp(0,0));
	bk->setPosition(ccp(0,0));
	cell->addChild(bk);
	//奖杯
	CCSprite *awardSprite;
	if(index == 0){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board1.png"));
	}else if(index == 1){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board2.png"));
	}else if(index == 2){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board3.png"));
	}else{
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board4.png"));
	}
	awardSprite->setAnchorPoint(ccp(0,0.5f));
	awardSprite->setPosition(ccp(17,tableItemSize.height/2));
	cell->addChild(awardSprite);

	char str[5];
	sprintf(str, "%d", index+1);
	float textWidth = 100;
	CCLabelTTF *rankLabel = CCLabelTTF::create(str,"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	rankLabel->setColor(ccc3(255,255,255));
	rankLabel->setAnchorPoint(ccp(0,0.5f));
	rankLabel->setPosition(ccp(95, tableItemSize.height/2));
	cell->addChild(rankLabel);

	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void RankSystemLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	//CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(nameLabelTag);
	//const char *name = nameLabel->getString();
	//textField->setString(name);
	//this->removeChild(_tableView, true);
	//flag = 0;
}

void RankSystemLayer::scrollViewDidScroll(CCScrollView* view)
{

}

void RankSystemLayer::scrollViewDidZoom(CCScrollView* view)
{

}

/**单元格大小
参数：table单元格所属的表格
*/

void RankTableHelper::cancelHttpRequest(CCObject *obj)
{
	cancelOrNot = true;
}

RankTableHelper::RankTableHelper(RankSystemLayer *fath, int num, RankTableTag tag)
{
	cancelOrNot = false;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RankTableHelper::cancelHttpRequest),"CancelHttpRequest", NULL);
	
	nicknameArray = CCArray::create();
	nicknameArray->retain();
	field4ValueArray = CCArray::create();
	field4ValueArray->retain();
	float gapX = 11;
	float gapY = 10;
	father = fath;
	winSize = CCDirector::sharedDirector()->getWinSize();
	winSize.width -= gapX*2;
	CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board6.png"));
	tableItemSize.height = tempSprite->getContentSize().height;
	tableItemSize.width = winSize.width;
	itemsNum = num;
	tableTag = tag;
	url = "http://117.18.5.229:999/mobile/GetWealthRank.aspx?uid=";
	string urlExtra = "&tid=";
	char str[33];
	sprintf(str, "%lu", EntityMgr::instance()->getDispatch()->m_dwUserID);
	string userId = string(str);
	if(tag == RankTableTag_Rich)
	{
		string id = "1";
		url = url + userId + urlExtra + id;
	}else if(tag == RankTableTag_Hero)
	{
		string id = "4";
		url = url + userId + urlExtra + id;
	}else if(tag == RankTableTag_Luck)
	{
		string id = "2";
		url = url + userId + urlExtra + id;
	}else if(tag == RankTableTag_Teacher)
	{
		string id = "5";
		url = url + userId + urlExtra + id;
	}else if(tag == RankTableTag_Charm)
	{
		string id = "3";
		url = url + userId + urlExtra + id;
	}
	CCHttpRequest* request = new CCHttpRequest();//创建request对象,这里new出来的对象不能使用autorelease()，原因后述  
	request->setUrl(url.c_str());//设置url  
	request->setRequestType(CCHttpRequest::kHttpGet);//设置请求方式  
	request->setResponseCallback(this, callfuncND_selector(RankTableHelper::onHttpRequestCompleted));//这是回调对象和回调函数  
	request->setTag("GET test1");//设置用户标识，可以通过response获取  
	httpClient = CCHttpClient::getInstance();
	httpClient->send(request);//使用CCHttpClient共享实例来发送request  
	request->release();//调用release() 

}

RankTableHelper::~RankTableHelper()
{
	if(nicknameArray!=NULL)
		nicknameArray->release();
	if(field4ValueArray!=NULL)
		field4ValueArray->release();
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "CancelHttpRequest");
}


void RankTableHelper::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)  
{  
	if(cancelOrNot)
	{
		return;
	}
	CCHttpResponse *response = (CCHttpResponse*)data;  

	if (!response)  
	{  
		return;  
	}  

	// 获取对应request的字符串标识  
	if (0 != strlen(response->getHttpRequest()->getTag()))   
	{  
		CCLog("%s completed", response->getHttpRequest()->getTag());  
	}  
	//获取返回代码，比如200、404等  
	int statusCode = response->getResponseCode();  
	char statusString[64] = {};  
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());  
	//m_labelStatusCode->setString(statusString);  
	CCLog("response code: %d", statusCode);  

	if (!response->isSucceed())   
	{  
		CCLog("response failed");  
		CCLog("error buffer: %s", response->getErrorBuffer());//可以调用getErrorBuffer()来获取错误原因  
		return;  
	}  

	// dump data  
	std::vector<char> *buffer = response->getResponseData();//用来获取接收到的数据  
	char dataBuffer[32768]; 
	int dataSize = buffer->size();

	if(dataSize<=0)
	{
		return;
	}

	for (unsigned int i = 0; i < dataSize; i++)  
	{  
		dataBuffer[i] = (*buffer)[i];  
	}   
	int index = 0;
	Json::Value rootValue = JsonHelper::getJsonFromData(dataBuffer, dataSize);
	int tempSize = rootValue.size();
	Json::Value rootValue1 = rootValue["Table"];
	tempSize = rootValue1.size();
	Json::Value value;
	value = rootValue1["GemeInfoTable"];

	int size = value.size();
	for(Json::ValueIterator it = value.begin() ; it!=value.end() ; it++)
	{
		Json::Value childValue = *it;
		string nicknameStr = childValue["NickName"].asString();
		if(nicknameStr == "")
		{
			nicknameStr = childValue["nickname"].asString();
		}
		string field4Str;
		if(tableTag == RankTableTag_Rich)
		{
			field4Str = childValue["score"].asString();
		}else if(tableTag == RankTableTag_Hero)
		{
			field4Str = childValue["WinCount"].asString();
		}else if(tableTag == RankTableTag_Luck)
		{
			field4Str = childValue["money"].asString();
		}else if(tableTag == RankTableTag_Teacher)
		{
			field4Str = childValue["Spreadercount"].asString();
		}else if(tableTag == RankTableTag_Charm)
		{
			field4Str = childValue["LoveLiness"].asString();
		}
		this->addTableData(nicknameStr, field4Str);
	}
	index = 0;
	rootValue1 = rootValue["Table1"];
	value = rootValue1["GemeInfoTable1"];

	size = value.size();
	Json::Value childValue = value[index];
	string rankText = childValue["rows"].asString();

	if(rankText == "")
	{
		father->setMyRankText(ConfigMgr::instance()->text("t578"), tableTag);
	}
	else
	{
		father->setMyRankText(childValue["rows"].asString().c_str(), tableTag);
	}
	father->reloadData(tableTag);
} 

void RankTableHelper::addTableData(string nickname, string field4)
{
	if(nicknameArray == NULL){
		nicknameArray = CCArray::create();
	}
	if(field4ValueArray == NULL){
		field4ValueArray = CCArray::create();
	}
	CCString *nickCCStr = CCString::create(nickname);
	CCString *field4CCStr = CCString::create(field4);
	nicknameArray->addObject(nickCCStr);
	field4ValueArray->addObject(field4CCStr);
}

CCSize RankTableHelper::cellSizeForTable(CCTableView *table)
{
	CCSprite *tempSprite;
	tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board6.png"));
	CCSize size;
	size.width = winSize.width;
	size.height = tempSprite->getContentSize().height;
	return size;
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int RankTableHelper::numberOfCellsInTableView(CCTableView *table)
{
	return nicknameArray->count();
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *RankTableHelper::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	//背景图
	CCSprite *bk;
	if(index%2 == 1){
		bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board6.png"));
	}else{
		bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board7.png"));
	}
	bk->setScaleX(winSize.width/bk->getContentSize().width);
	bk->setAnchorPoint(ccp(0,0));
	bk->setPosition(ccp(0,0));
	cell->addChild(bk);
	//奖杯
	CCSprite *awardSprite;
	if(index == 0){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board1.png"));
	}else if(index == 1){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board2.png"));
	}else if(index == 2){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board3.png"));
	}else{
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board4.png"));
	}
	awardSprite->setAnchorPoint(ccp(0,0.5f));
	awardSprite->setPosition(ccp(17,tableItemSize.height/2));
	cell->addChild(awardSprite);

	char str[5];
	sprintf(str, "%d", index+1);
	float textWidth = 100;
	CCLabelTTF *rankLabel = CCLabelTTF::create(str,"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	rankLabel->setColor(ccc3(255,255,255));
	rankLabel->setAnchorPoint(ccp(0,0.5f));
	rankLabel->setPosition(ccp(95, tableItemSize.height/2));
	cell->addChild(rankLabel);

	textWidth = 180;
	CCLabelTTF *nicknameLabel;

	if(index > nicknameArray->count()){
		nicknameLabel =  CCLabelTTF::create("","",20,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	}else{
		CCString *nicknameCCStr = (CCString *)nicknameArray->objectAtIndex(index);
		nicknameLabel = CCLabelTTF::create(nicknameCCStr->getCString(),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	}
	nicknameLabel->setColor(ccc3(255,255,255));
	nicknameLabel->setAnchorPoint(ccp(0.5f,0.5f));
	nicknameLabel->setPosition(ccp(244, tableItemSize.height/2));
	cell->addChild(nicknameLabel);

	CCLabelTTF *field4Label;
	if(index > field4ValueArray->count()){
		field4Label =  CCLabelTTF::create("","",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	}else{
		CCString *field4CCStr = (CCString *)field4ValueArray->objectAtIndex(index);
		field4Label = CCLabelTTF::create(field4CCStr->getCString(),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	}
	field4Label->setColor(ccc3(255,255,255));
	field4Label->setAnchorPoint(ccp(0,0.5f));
	field4Label->setPosition(ccp(600, tableItemSize.height/2));
	cell->addChild(field4Label);

	CCLabelTTF *chengHaoLabel;
	if(index > field4ValueArray->count()){
		chengHaoLabel =  CCLabelTTF::create("","",20,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	}else{
		chengHaoLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t10"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentCenter);
	}
	chengHaoLabel->setColor(ccc3(255,255,255));
	chengHaoLabel->setAnchorPoint(ccp(0.5f,0.5f));
	chengHaoLabel->setPosition(ccp(428, tableItemSize.height/2));
	cell->addChild(chengHaoLabel);
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void RankTableHelper::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	//CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(nameLabelTag);
	//const char *name = nameLabel->getString();
	//textField->setString(name);
	//this->removeChild(_tableView, true);
	//flag = 0;
}

void RankTableHelper::scrollViewDidScroll(CCScrollView* view)
{

}
void RankTableHelper::scrollViewDidZoom(CCScrollView* view)
{

}

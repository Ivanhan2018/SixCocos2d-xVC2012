#include "MissionLayer.h"
#include "RoomLayer.h"
#include "common/CocosUnits.h"
#include "common/JsonHelper.h"
#include "common/DBHandler.h"


#define minInWarning(a,b) (((a) < (b)) ? (a) : (b))

using namespace cocos2d;

void authResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *error)
{
	switch (state) {
	case C2DXResponseStateSuccess:
		CCLog("授权成功");
		break;
	case C2DXResponseStateFail:
		CCLog("授权失败");
		break;
	default:
		break;
	}
}

void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error)
{
	if (state == C2DXResponseStateSuccess)
	{
		//输出用户信息
		try
		{
			CCArray *allKeys = userInfo -> allKeys();
			allKeys->retain();
			for (int i = 0; i < allKeys -> count(); i++)
			{
				CCString *key = (CCString *)allKeys -> objectAtIndex(i);
				CCObject *obj = userInfo -> objectForKey(key -> getCString());

				CCLog("key = %s", key -> getCString());
				if (dynamic_cast<CCString *>(obj))
				{
					CCLog("value = %s", dynamic_cast<CCString *>(obj) -> getCString());
				}
				else if (dynamic_cast<CCInteger *>(obj))
				{
					CCLog("value = %d", dynamic_cast<CCInteger *>(obj) -> getValue());
				}
				//else if (dynamic_cast<CCDouble *>(obj))
				//{
				//	CCLog("value = %f", dynamic_cast<CCDouble *>(obj) -> getValue());
				//}
			}
			allKeys->release();
		}
		catch(...)
		{
			CCLog("==============error");
		}

	}
}

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
	switch (state) {
	case C2DXResponseStateSuccess:
		CCLog("分享成功");
		break;
	case C2DXResponseStateFail:
		CCLog("分享失败");
		break;
	default:
		break;
	}
}

MissionLayer::MissionLayer()
{

}
MissionLayer::~MissionLayer()
{

}
CCScene* MissionLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MissionLayer *layer = MissionLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


MissionLayer *MissionLayer::create()
{
	CCArray *normalName = CCArray::create();
	CCArray *selectedName = CCArray::create();
	normalName->addObject(CCString::create("Tab_EverydayMission1.png"));
	selectedName->addObject(CCString::create("Tab_EverydayMission2.png"));
	normalName->addObject(CCString::create("Tab_BegginerMission1.png"));
	selectedName->addObject(CCString::create("Tab_BegginerMission2.png"));
	//normalName->addObject(CCString::create("Tab_ScoreBoard1.png"));
	//selectedName->addObject(CCString::create("Tab_ScoreBoard2.png"));
	//normalName->addObject(CCString::create("Tab_ReferenceBoard1.png"));
	//selectedName->addObject(CCString::create("Tab_ReferenceBoard2.png"));
	return MissionLayer::createWithTabItems(normalName, selectedName);
}

MissionLayer *MissionLayer::createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName)
{
	MissionLayer *tabLayer = new MissionLayer();
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
//void MissionLayer::initView()
//{
//	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//	/**绘制半透明蒙板**/
//	CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
//	layer->ignoreAnchorPointForPosition(false);
//	layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
//	addChild(layer);
//
//	/**绘制背景图片**/
//	CCSprite * pBJ  = CCSprite::create("background/bg2.png");
//	pBJ->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
//	addChild(pBJ,0);
//
//	maskSprite = CCSprite::createWithSpriteFrame(spriteFrame("bg2_2.png"));
//	maskSprite->setPosition(ccp(winSize.width/2,winSize.height-maskSprite->getContentSize().height/2));
//	this->addChild(maskSprite,2);
//	//tab菜单 每日任务 新手任务 勋章
//	float itemGap = 10;
//	currentItem = MissionLayerTabEveryday;
//
//	CCSprite *everydayImage = CCSprite::createWithSpriteFrame(spriteFrame("Tab_EverydayMission2.png"));
//	CCSprite *beginnerImage = CCSprite::createWithSpriteFrame(spriteFrame("Tab_BegginerMission1.png"));
//	CCSprite *awardImage = CCSprite::createWithSpriteFrame(spriteFrame("Tab_Achievement1.png"));
//	everydayItem = CCMenuItemSprite::create(everydayImage,everydayImage,this,menu_selector(MissionLayer::pressEveryday));
//	beginnerItem = CCMenuItemSprite::create(beginnerImage,beginnerImage,this,menu_selector(MissionLayer::pressBeginner));
//	awardItem = CCMenuItemSprite::create(awardImage,awardImage,this,menu_selector(MissionLayer::pressAward));
//	CCMenu* menu = CCMenu::create(everydayItem,beginnerItem,awardItem,NULL);
//	menu->setAnchorPoint(ccp(0.5,0.5));
//	float menuWidth = 4*itemGap+everydayImage->getContentSize().width*3;
//	menu->setPosition(ccp(menuWidth/2,winSize.height*0.9f-2));
//	menu->alignItemsHorizontallyWithPadding(itemGap);//设置排列方式，纵向间隔20
//	addChild(menu, 2);
//	/**关闭按钮**/
//	CCSprite *pbuttonNormalClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
//	CCSprite *pbuttonSelectClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
//	CCMenuItemSprite *pButtonClose = CCMenuItemSprite::create
//		(pbuttonNormalClose,pbuttonSelectClose,this,menu_selector(MissionLayer::dismiss));
//	pbuttonSelectClose->setScale(0.9f);
//	pbuttonSelectClose->setAnchorPoint(ccp(-0.5/9,-0.5/9));
//	CCMenu *pButton0 = CCMenu::create(pButtonClose,NULL);
//	pButton0->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93)); 
//	addChild(pButton0,2);
//	this->initView();
//	setKeypadEnabled(true);
//}

void MissionLayer::initView()
{
	beMissionNum = 4;
	float gapX = 11;
	float gapY = 10;
	winSize = CCDirector::sharedDirector()->getWinSize();
	winSize.width -= gapX*2;

	CCSprite *tempSprite;
	tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend1.png"));
	tableItemSize = tempSprite->getContentSize();
	CCSize tableViewSize;
	tableViewSize.width = winSize.width;
	tableViewSize.height = 380;

	//每日任务
	MissionTableHelper *everydayHelper = new MissionTableHelper(this, 5, MissionLayerTabEveryday);
	everydayTable = CCTableView::create(everydayHelper, tableViewSize);
	everydayTable->setDelegate(everydayHelper);
	everydayTable->setAnchorPoint(ccp(0.5,0.5));
	everydayTable->setPosition(ccp(gapX, gapY));
	everydayTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	everydayTable->setDirection(kCCScrollViewDirectionVertical);
	everydayTable->retain();
	this->addChild(everydayTable, 1);

	//新手任务
	MissionTableHelper *beMissionHelper = new MissionTableHelper(this, 5, MissionLayerTabBeginner);
	beMissionTable = CCTableView::create(this, tableViewSize);
	beMissionTable->setDelegate(this);
	beMissionTable->setAnchorPoint(ccp(0.5,0.5));
	beMissionTable->setPosition(ccp(gapX+5, gapY));
	beMissionTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	beMissionTable->setDirection(kCCScrollViewDirectionVertical);
	beMissionTable->retain();
	this->addChild(beMissionTable, 1);
	beMissionTable->setVisible(false);

	setKeypadEnabled(true);
	this->setTouchEnabled(true);
}


void MissionLayer::doSomething()
{
	CCLog("RankSystemLayer::doSomething");
	if(currentItem == TabLayerBaseTag){
		everydayTable->setVisible(true);
		beMissionTable->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+1){
		everydayTable->setVisible(false);
		beMissionTable->setVisible(true);
	}else if(currentItem == TabLayerBaseTag+2){
		everydayTable->setVisible(false);
		beMissionTable->setVisible(false);
	}else if(currentItem == TabLayerBaseTag+3){
		everydayTable->setVisible(false);
		beMissionTable->setVisible(false);
	}
}


void MissionLayer::reloadData(MissionLayerTab tag)
{
	if(tag == MissionLayerTabEveryday)
	{
		everydayTable->reloadData();
	}else if(tag == MissionLayerTabBeginner)
	{
		beMissionTable->reloadData();
	}
}

void MissionLayer::keyBackClicked()
{
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);
}

void MissionLayer::dismiss(cocos2d::CCObject *obj){
	//playButtonSound();
	//RoomLayer* layer = (RoomLayer*)this->getParent();
	//layer->permitButtonClick();
	//this->removeFromParentAndCleanup(true);

	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

CCSize MissionLayer::cellSizeForTable(CCTableView *table)
{
	CCSize size;
	size.width = winSize.width;
	size.height = tableItemSize.height+10;
	return size;
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int MissionLayer::numberOfCellsInTableView(CCTableView *table)
{
	return beMissionNum = 2;
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *MissionLayer::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	//背景图
	CCSprite *bk;
	bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend1.png"));
	bk->setAnchorPoint(ccp(0,0));
	bk->setPosition(ccp(0,0.5f));
	cell->addChild(bk);

	CCSprite *awardSprite;
	if(index == 0){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board1.png"));
	}else if(index == 1){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board2.png"));
	}else if(index == 2){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board3.png"));
	}else if(index == 3){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board3.png"));
	}else{
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Board4.png"));
	}
	awardSprite->setAnchorPoint(ccp(0,0.5f));
	awardSprite->setPosition(ccp(17,tableItemSize.height/2+5));
	cell->addChild(awardSprite);

	ccColor3B redColor = ccc3(61,8,40);
	float textWidth = 600;
	CCLabelTTF *title = CCLabelTTF::create(ConfigMgr::instance()->text(CCString::createWithFormat("t%d", 594+index)->getCString()),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	title->setColor(redColor);
	title->setAnchorPoint(ccp(0,0.5f));
	title->setPosition(ccp(120, 52));
	cell->addChild(title, 1);

	CCLabelTTF *descibeLabel = CCLabelTTF::create(ConfigMgr::instance()->text(CCString::createWithFormat("t%d", 600+index)->getCString()),"",26,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	descibeLabel->setColor(redColor);
	descibeLabel->setAnchorPoint(ccp(0,0.5f));
	descibeLabel->setPosition(ccp(120, 22));
	cell->addChild(descibeLabel, 1);
	cell->setTag(index);
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void MissionLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	if(cell->getTag() == 0)
	{
    CCDictionary *content = CCDictionary::create();
    content -> setObject(CCString::create("这是一条测试内容"), "content");
    content -> setObject(CCString::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image");
    content -> setObject(CCString::create("测试标题"), "title");
    content -> setObject(CCString::create("测试描述"), "description");
    content -> setObject(CCString::create("http://sharesdk.cn"), "url");
    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
    content -> setObject(CCString::create("ShareSDK"), "site");
    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(CCString::create("extInfo"), "extInfo");
    
    C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
	}
}

void MissionLayer::scrollViewDidScroll(CCScrollView* view)
{

}
void MissionLayer::scrollViewDidZoom(CCScrollView* view)
{

}

void MissionTableHelper::cancelHttpRequest(CCObject *obj)
{
	cancelOrNot = true;
}

MissionTableHelper::MissionTableHelper(MissionLayer *fath, int num, MissionLayerTab tag)
{
	DBHandler *handler = DBHandler::sharedDBHandler();
	sqlite3 *DB = handler->getDB();
	sqlite3_stmt *stmt;
	char sql[200]={0};
	sprintf(sql, "select * from UserInfo where dwUserID=%ld",EntityMgr::instance()->getDispatch()->m_dwUserID);
	int rv = sqlite3_prepare(DB, sql, 100, &stmt, NULL);
	rv = sqlite3_step(stmt);
	if(rv == SQLITE_ROW)
	{
		cbMemberOrder = sqlite3_column_int(stmt, 3);
		lScore = sqlite3_column_int(stmt, 4);
		LONG lWinCount = sqlite3_column_int(stmt, 5);
		LONG lLostCount = sqlite3_column_int(stmt, 6);
		LONG lDrawCount = sqlite3_column_int(stmt, 7);
		LONG lFleeCount = sqlite3_column_int(stmt, 8);
		totalCount=lWinCount+lLostCount+lDrawCount+lFleeCount;
	}else
	{
		totalCount = 0;
	}
	sqlite3_finalize(stmt);
	cancelOrNot = false;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MissionTableHelper::cancelHttpRequest),"CancelHttpRequest", NULL);

	field4ValueArray = CCArray::create();
	field4ValueArray->retain();
	float gapX = 11;
	float gapY = 10;
	father = fath;
	winSize = CCDirector::sharedDirector()->getWinSize();
	winSize.width -= gapX*2;
	CCSprite *tempSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend1.png"));
	tableItemSize.height = tempSprite->getContentSize().height;
	tableItemSize.height+=10;
	tableItemSize.width = winSize.width;
	itemsNum = num;
	tableTag = tag;
	if(tag == MissionLayerTabEveryday)
	{
		url = "http://fl567.com/mobile/GetWealthJob.aspx?uid=100669&Rwid=1&Kid=200&Time=65466";
		//string id = "4";
		//url = url + id;
	}
	CCHttpRequest* request = new CCHttpRequest();//创建request对象,这里new出来的对象不能使用autorelease()，原因后述  
	request->setUrl(url.c_str());//设置url  
	request->setRequestType(CCHttpRequest::kHttpGet);//设置请求方式  
	request->setResponseCallback(this, callfuncND_selector(MissionTableHelper::onHttpRequestCompleted));//这是回调对象和回调函数  
	request->setTag("GET test1");//设置用户标识，可以通过response获取  
	CCHttpClient::getInstance()->send(request);//使用CCHttpClient共享实例来发送request  
	request->release();//调用release()  
}

MissionTableHelper::~MissionTableHelper()
{
	if(field4ValueArray!=NULL)
		field4ValueArray->release();
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "CancelHttpRequest");
}

void MissionTableHelper::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)  
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
	Json::Value value = JsonHelper::getJsonFromData(dataBuffer, dataSize);
	Json::Value taskArray = value["task"];
	int size = taskArray.size();
	for(Json::ValueIterator it = taskArray.begin() ; it!=taskArray.end() ; it++)
	{
		Json::Value childValue = *it;
		int field4Str = childValue["always"].asInt();
		this->addTableData(field4Str);
	}
	father->reloadData(tableTag);
} 

void MissionTableHelper::addTableData(int field4)
{
	if(field4ValueArray == NULL){
		field4ValueArray = CCArray::create();
	}
	CCInteger *field4CCStr = CCInteger::create(field4);
	field4ValueArray->addObject(field4CCStr);
}

CCSize MissionTableHelper::cellSizeForTable(CCTableView *table)
{
	CCSize size;
	size.width = winSize.width;
	size.height = tableItemSize.height;
	return size;
}

/**表格中单元格的个数
参数：table单元格所属的表格
*/
unsigned int MissionTableHelper::numberOfCellsInTableView(CCTableView *table)
{
	return field4ValueArray->count();
}

/**单元格初始化
参数：table单元格所属的表格
*/
CCTableViewCell *MissionTableHelper::tableCellAtIndex(CCTableView *table,unsigned int index)
{
	static const char * cellIdentifier = "cell-identifier";
	CCTableViewCell *cell = new CCTableViewCell();  
	cell->autorelease(); 
	//背景图
	CCSprite *bk;
	bk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Friend1.png"));
	bk->setAnchorPoint(ccp(0,0));
	bk->setPosition(ccp(0,5));
	cell->addChild(bk);
	//奖杯
	CCSprite *awardSprite;
	if(index == 0){
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Mission2.png"));
	}else{
		awardSprite = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Mission1.png"));
	}
	awardSprite->setAnchorPoint(ccp(0,0.5f));
	awardSprite->setPosition(ccp(17,tableItemSize.height/2));
	cell->addChild(awardSprite);

	ccColor3B redColor = ccc3(61,8,40);
	float textWidth = 600;
	float textSize1 = 30;
	float textSize2 = 25;
	CCLabelTTF *title = CCLabelTTF::create(ConfigMgr::instance()->text(CCString::createWithFormat("t%d", 700+index)->getCString()),"",textSize1,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	title->setColor(redColor);
	title->setAnchorPoint(ccp(0,0.5f));
	title->setPosition(ccp(110, 57));
	cell->addChild(title, 1);

	CCLabelTTF *descibeLabel = CCLabelTTF::create(ConfigMgr::instance()->text(CCString::createWithFormat("t%d", 706+index)->getCString()),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	descibeLabel->setColor(ccc3(45,137,187));
	descibeLabel->setAnchorPoint(ccp(0,0.5f));
	descibeLabel->setPosition(ccp(110, 27));
	cell->addChild(descibeLabel, 1);

	int always = ((CCInteger *)field4ValueArray->objectAtIndex(index))->getValue();
	CCLabelTTF *progress = CCLabelTTF::create(ConfigMgr::instance()->text("t712"),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	progress->setColor(redColor);
	progress->setAnchorPoint(ccp(0,0.5f));
	progress->setPosition(ccp(460, 57));
	cell->addChild(progress, 1);
	CCLabelTTF *progress1;
	if(index == 3)
	{
		progress1 = CCLabelTTF::create(CCString::createWithFormat("%d/50", totalCount)->getCString(),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	}else if(index == 4) 
	{
		progress1 = CCLabelTTF::create(CCString::createWithFormat("%d/100", totalCount)->getCString(),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	}else if(index == 5) 
	{
		progress1 = CCLabelTTF::create(CCString::createWithFormat("%d/500", totalCount)->getCString(),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	}else{
		if(index == 2)
		{
			if(always == 0){
				progress1 = CCLabelTTF::create("0/3","",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}else if(always == 1){
				progress1 = CCLabelTTF::create("1/3","",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}else if(always == 2){
				progress1 = CCLabelTTF::create("2/3","",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}else{
				progress1 = CCLabelTTF::create("3/3","",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}
		}else
		{
			if(always == 0){
				progress1 = CCLabelTTF::create("0/1","",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}else{
				progress1 = CCLabelTTF::create("1/1","",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}
		}
	}
	progress1->setColor(redColor);
	progress1->setAnchorPoint(ccp(0,0.5f));
	progress1->setPosition(ccp(530, 57));
	cell->addChild(progress1, 1);

	CCLabelTTF *descibeLabel1;
	if(index == 0)
	{
		if(cbMemberOrder<1){
			descibeLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t715"),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		}else
		{
			if(always < 1){
				descibeLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t716"),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}else
			{
				descibeLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t717"),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
			}
		}
	}else
	{
		if(always < 1){
			descibeLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t718"),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		}else if(always == 1){
			descibeLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t716"),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		}else{
			descibeLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t717"),"",textSize2,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
		}
	}
	descibeLabel1->setColor(ccc3(255, 0, 0));
	descibeLabel1->setAnchorPoint(ccp(0,0.5f));
	descibeLabel1->setPosition(ccp(460, 27));
	cell->addChild(descibeLabel1, 1);

	if((index == 0&&cbMemberOrder>1&&always == 1)||(index==1&&always>0&&always<4&&lScore<1000)||(index>1&&always == 1))
	{
		CCSprite *getItemImage1 = CCSprite::createWithSpriteFrame(spriteFrame("Button_MissonAchieve1.png"));
		CCSprite *getItemImage2 = CCSprite::createWithSpriteFrame(spriteFrame("Button_MissonAchieve2.png"));
		CCMenuItemSprite *menuItem = CCMenuItemSprite::create(getItemImage1,getItemImage2,this,menu_selector(MissionTableHelper::pressGet));
		CCMenu *menu = CCMenu::createWithItem(menuItem);
		menu->setPosition(ccp(tableItemSize.width-80,tableItemSize.height/2));
		cell->addChild(menu);
	}
	return cell;  
}

/**点击单元格
参数：table，单元格所属的表格
cell，单元格
*/
void MissionTableHelper::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
	//CCLabelTTF *nameLabel = (CCLabelTTF *)cell->getChildByTag(nameLabelTag);
	//const char *name = nameLabel->getString();
	//textField->setString(name);
	//this->removeChild(_tableView, true);
	//flag = 0;
}

void MissionTableHelper::scrollViewDidScroll(CCScrollView* view)
{

}
void MissionTableHelper::scrollViewDidZoom(CCScrollView* view)
{

}

void MissionTableHelper::pressGet(CCObject *obj)
{

}

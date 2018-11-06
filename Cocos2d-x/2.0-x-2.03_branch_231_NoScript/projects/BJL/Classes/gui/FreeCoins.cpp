//
//  FreeCoins.cpp
//  Game
//
// Created by wangjun on 15-1-7.
//
//

#include "FreeCoins.h"
#include "common/CocosUnits.h"
#include "cocos-ext.h"
#include "ans/AnsString.h"
#include "ans/utf-8.h"
#include "configMgr/ConfigMgr.h"
#include "entity/EntityMgr.h"
#include "RoomLayer.h"
#include "LoginLayer.h"
#include "MovingLabelLayer.h"
#include "FreeLayer.h"
#include "OverRegistLayer.h"
#include "common/JsonHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

USING_NS_CC;

FreeCoins::FreeCoins()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(FreeCoins::onCheckVersion), MSG_UI_ANS_VERSIONNEW, NULL);
	cancelOrNot = false;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FreeCoins::cancelHttpRequest),"CancelHttpRequest", NULL);
	
}

FreeCoins::~FreeCoins()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_VERSIONNEW);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "CancelHttpRequest");
}

void FreeCoins::cancelHttpRequest(CCObject *obj)
{
	cancelOrNot = true;
}

bool FreeCoins::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//背景
	CCSprite *background = CCSprite::create("background/bg2.png");
	background->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(background);	

	//返回
	CCSprite* backNormal= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCSprite* backSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCMenuItemSprite* backItemSprite = CCMenuItemSprite::create(backNormal,backSelect,this,menu_selector(FreeCoins::back));
	backSelect->setScale(0.9f);
	backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* backMenu= CCMenu::create(backItemSprite,NULL);
	backMenu->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93));
	addChild(backMenu);

	//救济金，推荐赚金币，我的推荐人
	float itemGap = 10;
	currentItem = FreeCoinsTabAlms;
	CCSprite *almsItemImage1 = CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms2.png"));
	CCSprite *almsItemImage2 = CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms2.png"));
	CCSprite *recommendItemImage1 = CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend1.png"));
	CCSprite *recommendItemImage2 = CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend1.png"));
	CCSprite *recommenderItemImage1 = CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender1.png"));
	CCSprite *recommenderItemImage2 = CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender1.png"));
	almsItem = CCMenuItemSprite::create(almsItemImage1,almsItemImage2,this,menu_selector(FreeCoins::getAlms));
	recommendItem = CCMenuItemSprite::create(recommendItemImage1,recommendItemImage2,this,menu_selector(FreeCoins::recommend));
	recommenderItem = CCMenuItemSprite::create(recommenderItemImage1,recommenderItemImage2,this,menu_selector(FreeCoins::myRecommender));
	CCMenu* menu = CCMenu::create(almsItem,recommendItem,recommenderItem,NULL);
	menu->setAnchorPoint(ccp(0.5,0.5));
	float menuWidth = 4*itemGap+almsItemImage1->getContentSize().width*3;
	menu->setPosition(ccp(menuWidth/2,winSize.height*0.9f-2));
	menu->alignItemsHorizontallyWithPadding(itemGap);//设置排列方式，纵向间隔20
	//menu->setTouchPriority(-1801);
	addChild(menu);

	CCSprite *girl = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_FreeCoinsGirl.png"));
	girl->setAnchorPoint(ccp(0,0.5f));
	girl->setPosition(ccp(15, winSize.height/2-20));
	this->addChild(girl);	

	float textWidth = 500;
	almsText = CCLabelTTF::create(ConfigMgr::instance()->text("t552"),"",18,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	almsText->setColor(ccc3(189,154,97));
	almsText->setAnchorPoint(ccp(0,1));
	almsText->setPosition(CCPointMake(266,363));
	addChild(almsText);

	recommendText = CCLabelTTF::create(ConfigMgr::instance()->text("t553"),"",18,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	recommendText->setColor(ccc3(189,154,97));
	recommendText->setAnchorPoint(ccp(0,1));
	recommendText->setPosition(CCPointMake(266,363));
	addChild(recommendText);

	recommenderText = CCLabelTTF::create(ConfigMgr::instance()->text("t554"),"",18,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	recommenderText->setColor(ccc3(189,154,97));
	recommenderText->setAnchorPoint(ccp(0,1));
	recommenderText->setPosition(CCPointMake(266,247));
	addChild(recommenderText);
	almsText->setVisible(true);
	recommendText->setVisible(false);
	recommenderText->setVisible(false);

	CCSprite * getCoinsNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_FreeCoinGet1.png"));
	CCSprite * getCoinsSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_FreeCoinGet2.png"));
	CCSprite * getCoinsDisSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_FreeCoinGet2.png"));
	getCoinsDisSprite->setColor(ccc3(100,100,100));
	CCMenuItemSprite *getCoinsMenuItem = CCMenuItemSprite::create(getCoinsNormalSprite, 
		getCoinsSelectSprite,getCoinsDisSprite, this, menu_selector(FreeCoins::pressGetCoins));
	getCoinsMenu = CCMenu::create(getCoinsMenuItem,NULL);
	getCoinsMenu->setAnchorPoint(ccp(0,0));
	getCoinsMenu->setPosition(ccp(446, 48));
	addChild(getCoinsMenu);

	//推荐人
	recommenderLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t555"),"",30,CCSizeMake(textWidth,0),kCCTextAlignmentLeft);
	recommenderLabel->setColor(ccc3(255,255,255));
	recommenderLabel->setAnchorPoint(ccp(0,0.5f));
	recommenderLabel->setPosition(CCPointMake(261,299));
	addChild(recommenderLabel);
	//推荐人输入框
	recommenderName = CCEditBox::create(CCSize(389, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_Notice2.png")));
	recommenderName->setPosition(CCPoint(363, 301));
	recommenderName->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	recommenderName->setReturnType(kKeyboardReturnTypeGo);
	recommenderName->setAnchorPoint(ccp(0,0.5f));
	recommenderName->setFontColor(ccc3(0,0,0));
	//recommenderName->setFontSize(20);
	recommenderName->setPlaceHolder(ConfigMgr::instance()->text(""));
	addChild(recommenderName);
	recommenderLabel->setVisible(false);
	recommenderName->setVisible(false);
	setKeypadEnabled(true);
	setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne);

	promptBox = NULL;
	return true;
}

void FreeCoins::onEnter()
{
	CCLayer::onEnter();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1000,true);
}

void FreeCoins::onExit()
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool FreeCoins::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	//if(m_pMusicControlSprite->boundingBox().containsPoint(touchPoint))
	//{
	//	m_nChangeVoice = 1;
	//	return true;
	//}
	return false;
}

void FreeCoins::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}

void FreeCoins::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}

void FreeCoins::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}

void FreeCoins::back(CCObject* obj)
{
	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void FreeCoins::keyBackClicked()
{
	back(NULL);
}

void FreeCoins::onCheckVersion(CCObject* obj)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptVersionNew);
	addChild(box,50);
}

void FreeCoins::getAlms( CCObject* obj)
{
	if(currentItem == FreeCoinsTabAlms)
	{
		return;
	}
	currentItem = FreeCoinsTabAlms;
	getCoinsMenu->setVisible(true);
	almsItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms2.png")));
	almsItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms2.png")));
	recommendItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend1.png")));
	recommendItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend1.png")));
	recommenderItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender1.png")));
	recommenderItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender1.png")));
	almsText->setVisible(true);
	recommendText->setVisible(false);
	recommenderText->setVisible(false);
	recommenderLabel->setVisible(false);
	recommenderName->setVisible(false);
}

void FreeCoins::recommend( CCObject* obj)
{
	if(currentItem == FreeCoinsTabRecommend)
	{
		return;
	}
	currentItem = FreeCoinsTabRecommend;
	getCoinsMenu->setVisible(false);
	almsItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms1.png")));
	almsItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms1.png")));
	recommendItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend2.png")));
	recommendItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend2.png")));
	recommenderItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender1.png")));
	recommenderItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender1.png")));
	almsText->setVisible(false);
	recommendText->setVisible(true);
	recommenderText->setVisible(false);
	recommenderLabel->setVisible(false);
	recommenderName->setVisible(false);
}

void FreeCoins::myRecommender( CCObject* obj)
{
	if(currentItem == FreeCoinsTabRecommender)
	{
		return;
	}
	currentItem = FreeCoinsTabRecommender;
	getCoinsMenu->setVisible(true);
	almsItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms1.png")));
	almsItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Alms1.png")));
	recommendItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend1.png")));
	recommendItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_Recommend1.png")));
	recommenderItem->setNormalImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender2.png")));
	recommenderItem->setSelectedImage(CCSprite::createWithSpriteFrame(spriteFrame("Tab_MyRecommender2.png")));
	almsText->setVisible(false);
	recommendText->setVisible(false);
	recommenderText->setVisible(true);
	recommenderLabel->setVisible(true);
	recommenderName->setVisible(true);
}

void FreeCoins::pressGetCoins( CCObject* obj)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	char str[33];
	sprintf(str, "%lu", EntityMgr::instance()->getDispatch()->m_dwUserID);
	string userId = string(str);
	if(currentItem == FreeCoinsTabAlms)
	{
		promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
		promptBox->setPromptText(ConfigMgr::instance()->text("t556"));
		addChild(promptBox,1);
		string url = "http://117.18.5.229:999/mobile/GetWealthJob.aspx?uid=";
		url = url+userId;
		CCHttpRequest* request = new CCHttpRequest();//创建request对象,这里new出来的对象不能使用autorelease()，原因后述  
		request->setUrl(url.c_str());//设置url  
		request->setRequestType(CCHttpRequest::kHttpGet);//设置请求方式  
		request->setResponseCallback(this, callfuncND_selector(FreeCoins::onHttpRequestCompleted));//这是回调对象和回调函数  
		request->setTag("GET test1");//设置用户标识，可以通过response获取  
		CCHttpClient::getInstance()->send(request);//使用CCHttpClient共享实例来发送request  
		request->release();//调用release()  
	}else if(currentItem == FreeCoinsTabRecommender)
	{
		promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
		promptBox->setPromptText(ConfigMgr::instance()->text("t556"));
		addChild(promptBox,1);
		string url = "http://183.60.202.73:8011/mobile/GetWealthJob.aspx?uid=";
		url = url+userId;
		CCHttpRequest* request = new CCHttpRequest();//创建request对象,这里new出来的对象不能使用autorelease()，原因后述  
		request->setUrl(url.c_str());//设置url  
		request->setRequestType(CCHttpRequest::kHttpGet);//设置请求方式  
		request->setResponseCallback(this, callfuncND_selector(FreeCoins::onHttpRequestCompleted));//这是回调对象和回调函数  
		request->setTag("GET test1");//设置用户标识，可以通过response获取  
		CCHttpClient::getInstance()->send(request);//使用CCHttpClient共享实例来发送request  
		request->release();//调用release()  
	}
}

void FreeCoins::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)  
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
	char dataBuffer[255]; 
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
	
	for(Json::ValueIterator it = value.begin() ; it!=value.end() ; it++)
	{
		Json::Value value1 = *it;
	}


	int index = 0;
	Json::Value noticeValue = value[index];
	string noticeStr = noticeValue["mess"].asString();
	if(promptBox == NULL){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
		promptBox->setPromptText(noticeStr.c_str());
		addChild(promptBox,1);
	}else{
		promptBox->setPromptText(noticeStr.c_str());
	}
} 
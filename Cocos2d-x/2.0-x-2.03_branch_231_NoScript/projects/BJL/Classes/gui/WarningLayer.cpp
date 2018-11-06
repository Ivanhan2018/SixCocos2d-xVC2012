#include "WarningLayer.h"
#include "RoomLayer.h"
#include "GroupSprite.h"
#include "TaskInfo.h"
#include "PromptBox.h"
#include "MovingLabelLayer.h"
#include "ddz/SceneControl.h"
#include "ddz/DDZRes.h"
#include "common/CocosUnits.h"
#include "common/JsonHelper.h"
#include "common/DBHandler.h"
#include <string>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif


#define minInWarning(a,b) (((a) < (b)) ? (a) : (b))

using namespace cocos2d;

CCPoint signInImagePos = CCPoint(400,381);
CCPoint signInButtonPos = CCPoint(625, 135);
CCPoint awardImagePos[7] = {CCPoint(165,282), CCPoint(327,282),CCPoint(475,282),
	CCPoint(632,282),CCPoint(165,147),CCPoint(327,147),CCPoint(475,147)};
char awardImageName1[7][30]={"Sprite_SignIn1Day1.png", "Sprite_SignIn2Day1.png", "Sprite_SignIn3Day1.png","Sprite_SignIn4Day1.png",
	"Sprite_SignIn5Day1.png","Sprite_SignIn6Day1.png","Sprite_SignIn7Day1.png"};
char awardImageName2[7][30]={"Sprite_SignIn1Day2.png", "Sprite_SignIn2Day2.png", "Sprite_SignIn3Day2.png","Sprite_SignIn4Day2.png",
	"Sprite_SignIn5Day2.png","Sprite_SignIn6Day2.png","Sprite_SignIn7Day2.png"};

WarningLayer::WarningLayer()
{
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(
	//	this, callfuncO_selector(WarningLayer::onGetLoginAward), MSG_UI_ANS_GETAWARDRESULT, NULL);
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(
	//	this, callfuncO_selector(WarningLayer::onGetTaskAward), MSG_UI_ANS_TASKGETSUCC, NULL);
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(
	//	this, callfuncO_selector(WarningLayer::onGetTaskFailed), MSG_UI_ANS_TASKGETFAIL, NULL);
	signInDays = 0;
	cancelOrNot = false;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarningLayer::cancelHttpRequest),"CancelHttpRequest", NULL);

}
WarningLayer::~WarningLayer()
{
	if(awardImage != NULL)
	{
		CC_SAFE_DELETE(awardImage);
		awardImage = NULL;
	}

	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "CancelHttpRequest");
	//CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_GETAWARDRESULT);
	//CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_TASKGETSUCC);
	//CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_TASKGETFAIL);
}
CCScene* WarningLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		WarningLayer *layer = WarningLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool WarningLayer::init()
{
	bool bRet = false;
	do 
	{
		winSize = CCDirector::sharedDirector()->getWinSize();
		signInDays = 0;
		/**绘制半透明蒙板**/
		CCLayerColor* layer = CCLayerColor::create( ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);

		/**绘制背景图片**/
		//CCSprite * pBJ = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_1000.png"));
		CCSprite * pBJ = CCSprite::create("background/Bk_Notice.png");
		pBJ->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(pBJ,0);

		CCSprite *signInImage = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_SignIn1.png"));
		signInImage->setPosition(signInImagePos);
		this->addChild(signInImage);

		CCSprite *girl = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_Notice3.png"));
		girl->setPosition(CCPoint(111, 399));
		this->addChild(girl);
		//签到天数图片
		awardImage = CCArray::create();
		awardImage->retain();
		for(int i = 0 ; i < 7 ; i++)
		{
			CCSprite *sprite = CCSprite::createWithSpriteFrame(spriteFrame(awardImageName1[i]));
			sprite->setPosition(awardImagePos[i]);
			awardImage->addObject(sprite);
			this->addChild(sprite);
		}

		/**签到按钮**/
		CCSprite *normalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_SignIn1.png"));
		CCSprite *selectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_SignIn2.png"));
		CCMenuItemSprite *menuSprite = CCMenuItemSprite::create
			(normalSprite,selectSprite,this,menu_selector(WarningLayer::onGetTaskAward));

		signInMenu = CCMenu::create(menuSprite,NULL);
		signInMenu->setPosition(signInButtonPos);  
		addChild(signInMenu);
		/**关闭按钮**/
		CCSprite *pbuttonNormalClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pbuttonSelectClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pButtonClose = CCMenuItemSprite::create
			(pbuttonNormalClose,pbuttonSelectClose,this,menu_selector(WarningLayer::dismiss));
		pbuttonSelectClose->setScale(0.9f);
		pbuttonSelectClose->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pButton0 = CCMenu::create(pButtonClose,NULL);
		pButton0->setPosition(ccp(pBJ->getPositionX()+pBJ->getContentSize().width/2-pbuttonNormalClose->getContentSize().width/2+10,
			pBJ->getPositionY()+pBJ->getContentSize().height/2-pbuttonNormalClose->getContentSize().height/2+10));  
		addChild(pButton0,2);
		signInMenu->setVisible(false);
		promptBox = NULL;
		this->requestSignInDays();

		bRet = true;
		setKeypadEnabled(true);
	} while (0);

	return bRet;

}

void WarningLayer::setSignInDays(int days)
{
	for(int i = 0 ; i < days ; i++)
	{
		CCSprite *sprite = (CCSprite *)awardImage->objectAtIndex(i);
		sprite->setDisplayFrame(spriteFrame(awardImageName2[i]));
	}
}

void WarningLayer::requestSignInDays()
{
	char str[33];
	sprintf(str, "%lu", EntityMgr::instance()->getDispatch()->m_dwUserID);
	string userId;
	userId.assign(str, sizeof(str));
	string url = "http://117.18.5.229:999/phone/Registration.aspx?parama=0&paramb=";
	url = url+userId;
	CCHttpRequest* request = new CCHttpRequest();//创建request对象,这里new出来的对象不能使用autorelease()，原因后述  
	request->setUrl(url.c_str());//设置url  
	request->setRequestType(CCHttpRequest::kHttpGet);//设置请求方式  
	request->setResponseCallback(this, callfuncND_selector(WarningLayer::onHttpRequestCompleted));//这是回调对象和回调函数  
	request->setTag("GET test1");//设置用户标识，可以通过response获取  
	CCHttpClient::getInstance()->send(request);//使用CCHttpClient共享实例来发送request  
	request->release();//调用release()  
}

void WarningLayer::signIn()
{
	char str[33];
	sprintf(str, "%lu", EntityMgr::instance()->getDispatch()->m_dwUserID);
	string userId;
	userId.assign(str, sizeof(str));
	promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
	promptBox->setPromptText(ConfigMgr::instance()->text("t556"));
	addChild(promptBox,1);
	string url = "http://117.18.5.229:999/phone/Registration.aspx?parama=1&paramb=";
	url = url+userId;
	CCHttpRequest* request = new CCHttpRequest();//创建request对象,这里new出来的对象不能使用autorelease()，原因后述  
	request->setUrl(url.c_str());//设置url  
	request->setRequestType(CCHttpRequest::kHttpGet);//设置请求方式  
	request->setResponseCallback(this, callfuncND_selector(WarningLayer::onSignInCompleted));//这是回调对象和回调函数  
	request->setTag("GET test1");//设置用户标识，可以通过response获取  
	CCHttpClient::getInstance()->send(request);//使用CCHttpClient共享实例来发送request  
	request->release();//调用release()  
}

void WarningLayer::cancelHttpRequest(CCObject *obj)
{
	cancelOrNot = true;
}

void WarningLayer::onHttpRequestCompleted(cocos2d::CCNode *sender, void *data)
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
	char dataBuffer[4048]; 
	memset(dataBuffer, 0, sizeof(dataBuffer));
	int dataSize = buffer->size();
	if(dataSize<=0)
	{
		return;
	}
	for (unsigned int i = 0; i < dataSize; i++)  
	{  
		dataBuffer[i] = (*buffer)[i];  
	}   
	CCLog("%s", dataBuffer);
	char *slpitPointer;
	slpitPointer = strtok(dataBuffer, "|");
	char result = (char)*slpitPointer;
	int days = result - '0';
	if(days>7)
	{
		days = 0;
	}
	this->setSignInDays(days);
	if(slpitPointer!=NULL)
	{
		slpitPointer = strtok(NULL, "|");
	}
	result = 0;
	if(slpitPointer!=NULL){
		result = (char)*slpitPointer;
	}
	if(result == '1'){
		signInMenu->setVisible(true);
	}
}

void WarningLayer::onSignInCompleted(cocos2d::CCNode *sender, void *data)
{
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
	memset(dataBuffer, 0, sizeof(dataBuffer));
	int dataSize = buffer->size();
	for (unsigned int i = 0; i < dataSize; i++)  
	{  
		dataBuffer[i] = (*buffer)[i];  
	}   
	char *slpitPointer;
	slpitPointer = strtok(dataBuffer, "|");
	char result = (char)*slpitPointer;
	int days = result - '0';
	this->setSignInDays(days);
	if(slpitPointer!=NULL)
	{
		slpitPointer = strtok(NULL, "|");
	}
	result = (char)*slpitPointer;
	signInMenu->setVisible(false);
	if(result == '3'){
		if(promptBox == NULL){
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t575"));
			addChild(promptBox,1);
		}else{
			promptBox->setPromptText(ConfigMgr::instance()->text("t575"));
		}	
		char message[1024];
		time_t tt = time(NULL);//这句返回的只是一个时间cuo
		tm* t= localtime(&tt);
		sprintf(message, "insert into PersonalMsg(msg) values(\'%s     %d-%02d-%02d %02d:%02d:%02d\')", ConfigMgr::instance()->text("t575"),
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		DBHandler::sharedDBHandler()->execute(message);
	}else{
		if(promptBox == NULL){
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			promptBox = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeGetError);
			promptBox->setPromptText(ConfigMgr::instance()->text("t576"));
			addChild(promptBox,1);
		}else{
			promptBox->setPromptText(ConfigMgr::instance()->text("t576"));
		}
	}

}

void WarningLayer::keyBackClicked()
{
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);
}

void WarningLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	RoomLayer* layer = (RoomLayer*)this->getParent();
	layer->permitButtonClick();
	this->removeFromParentAndCleanup(true);

}

void WarningLayer::onGetTaskAward(CCObject* obj)
{
	//MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(CCString::createWithFormat("%s%d!",ConfigMgr::instance()->text("t128"), TaskInfo::ShareTaskInfo()->m_nTaskConfig[1])->getCString(),ccp(427,240));
	//addChild(layer,20);
	//TaskInfo::ShareTaskInfo()->m_nGetState[0] = 1;
	this->signIn();
}
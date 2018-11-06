#include "LoginLayer.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "entity/Login.h"
#include "RoomLayer.h"
#include "ans/AnsString.h"
#include "event/GBEvent.h"
#include "event/GBEventIDs.h"
#include "ans/utf-8.h"
#include "configMgr/ConfigMgr.h"
#include "GroupSprite.h"
#include "RegistLayer.h"
#include "ModifyPassWord.h"
#include "MovingLabelLayer.h"
#include "RegistLayer.h"
#include "RoomOption.h"
#include "PromptBox.h"
#include "FreeLayer.h"
#include "common/packet.h"
#include "common/DBHandler.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

CCScene* LoginLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LoginLayer *layer = LoginLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

LoginLayer::LoginLayer()
{
	//m_bLogin = true;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoginLayer::onAnsLoginFinish), MSG_UI_ANS_LOGINFINISH, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoginLayer::onLoginFaild), MSG_UI_ANS_LOGINFAIL, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LoginLayer::onFindPassword), MSG_UI_ANS_FINDPASS, NULL);
	//GBEVENT_ARG_REGISTER(GBEVENT_UI_FIMDPASSWORD, LoginLayer::onFindPassword);

	//GBEVENT_NOARG_REGISTER(GBEVENT_UI_LOGINFAILE, LoginLayer::onLoginFaild);
}
LoginLayer::~LoginLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_LOGINFINISH);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_LOGINFAIL);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_FINDPASS);

	//GBEVENT_NOARG_UNREGISTER(GBEVENT_UI_LOGINFAILE, LoginLayer::onLoginFaild);

	//GBEVENT_ARG_REGISTER(GBEVENT_UI_FIMDPASSWORD, LoginLayer::onFindPassword);
}

void LoginLayer::setLogin(bool loginBool)
{
	m_bLogin = loginBool;
}

// on "init" you need to initialize your instance
bool LoginLayer::init(bool bLogin)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	EntityMgr::instance();
	winSize = CCDirector::sharedDirector()->getWinSize();
	m_bLogin = true;
	m_from = false;
	//±³¾°
	CCSprite *bk = CCSprite::create("background/Bk_LoadView.png");
	bk->setPosition(CCPoint(FRAME_CENTER_X, FRAME_CENTER_Y));
	this->addChild(bk,0);

	CCSprite *m_pNoticeBk = CCSprite::create("background/Bk_Notice2.png");
	m_pNoticeBk->setPosition(CCPoint(NOTICE_CENTER_X, NOTICE_CENTER_Y));
	this->addChild(m_pNoticeBk,0);

	CCSprite *m_pLoginBk = CCSprite::create("background/Bk_Login.png");
	m_pLoginBk->setPosition(CCPoint(LOGIN_CENTER_X, LOGIN_CENTER_Y));
	this->addChild(m_pLoginBk,0);

	CCSprite *m_pAccountsBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_LoginAccountsBk.png"));
	m_pAccountsBk->setPosition(CCPoint(ACCOUNT_CENTER_X, ACCOUNT_CENTER_Y));
	m_pAccountsBk->setAnchorPoint(ccp(0,0.5f));
	this->addChild(m_pAccountsBk,0);

	CCSprite *m_pPassWordBk = CCSprite::createWithSpriteFrame(spriteFrame("Sprite_LoginPassWordBk.png"));
	m_pPassWordBk->setPosition(CCPoint(PASSWORD_CENTER_X, PASSWORD_CENTER_Y));
	m_pPassWordBk->setAnchorPoint(ccp(0,0.5f));
	this->addChild(m_pPassWordBk,0);
	//·µ»Ø
	//CCSprite* backNormal= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	//CCSprite* backSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	//CCMenuItemSprite* backItemSprite = CCMenuItemSprite::create(backNormal,backSelect,this,menu_selector(LoginLayer::back));
	//backSelect->setScale(0.9f);
	//backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	//CCMenu* backMenu= CCMenu::create(backItemSprite,NULL);
	//backMenu->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93));
	//addChild(backMenu);

	//±êÌâ
	//CCSprite* spriteTitleBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_14.png"));
	//CCSprite* spriteTitle = CCSprite::createWithSpriteFrame(spriteFrame("dt_login8.png"));
	//spriteTitleBack->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.92));
	//spriteTitle->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.93));
	//this->addChild(spriteTitleBack);
	//this->addChild(spriteTitle);

	//µ×¿ò
	//CCSprite* spriteBackBox0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg")); 
	//CCSprite* spriteBackBox1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
	//spriteBackBox0->setPosition(ccp(winSize.width * 0.5 - spriteBackBox0->getContentSize().width * 0.5,spriteBackBox0->getContentSize().height * 0.57));
	//spriteBackBox1->setPosition(ccp(winSize.width * 0.5 + spriteBackBox1->getContentSize().width * 0.5-2,spriteBackBox1->getContentSize().height * 0.57));
	//spriteBackBox0->setScaleY(1.12f);
	//spriteBackBox1->setScaleY(1.12f);
	//spriteBackBox1->setFlipX(true);
	//this->addChild(spriteBackBox0);
	//this->addChild(spriteBackBox1);

	//Ãâ·Ñ
	/*CCSprite *pMianFeiSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
	pMianFeiSprite->setPosition(CCPointMake(winSize.width*0.054,winSize.height*0.885));
	addChild(pMianFeiSprite);*/

	//CCSprite *pMianFeiSpriteNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
	//CCSprite *pMianFeiSpriteSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
	//CCMenuItemSprite* pMianfei = CCMenuItemSprite::create(pMianFeiSpriteNormal,pMianFeiSpriteSelect,this,menu_selector(LoginLayer::toFreeLayer));
	//pMianFeiSpriteSelect->setScale(0.9f);
	//pMianFeiSpriteSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	//CCMenu* mianfeiMenu = CCMenu::create(pMianfei,NULL);
	//mianfeiMenu->setPosition(CCPointMake(winSize.width*0.054,winSize.height*0.885));
	//addChild(mianfeiMenu);

	//µÇÂ½µ×¿ò
	//CCSprite* loginBackBox = CCSprite::createWithSpriteFrame(spriteFrame("dt_login2.png"));
	//loginBackBox->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.39));
	//addChild(loginBackBox);

	//logo
	//CCSprite* logoSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_login0.png"));
	//logoSprite->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.7));
	//addChild(logoSprite);


	//tips
	//CCSprite* spriteUserTips = CCSprite::createWithSpriteFrame(spriteFrame("dt_login4.png"));
	//CCSprite* spritePassTips = CCSprite::createWithSpriteFrame(spriteFrame("dt_login9.png"));
	//spriteUserTips->setPosition(ccp(winSize.width * 0.27,winSize.height * 0.46));
	//spritePassTips->setPosition(ccp(winSize.width * 0.27,winSize.height * 0.31));
	//addChild(spriteUserTips);
	//addChild(spritePassTips);


	//ÊäÈë¿ò
	passwordInput = CCEditBox::create(CCSize(270,40), CCScale9Sprite::create());
	passwordInput->setPosition(ccp(PASSWORD_TEXT_CENTER_X, PASSWORD_TEXT_CENTER_Y));
	passwordInput->setInputFlag(kEditBoxInputFlagPassword);
	passwordInput->setReturnType(kKeyboardReturnTypeGo);
	passwordInput->setMaxLength(20);
	passwordInput->setAnchorPoint(ccp(0,0.5f));
	passwordInput->setFontColor(ccc3(0,0,0));
	//passwordInput->setFontSize(20);
	passwordInput->setPlaceHolder(ConfigMgr::instance()->text("t4"));
	passwordInput->setZoomOnTouchDown(false);
	passwordInput->setDelegate(this);

	userInput = CCEditBox::create(CCSize(270, 40), CCScale9Sprite::create());
	userInput->setPosition(CCPoint(ACCOUNT_TEXT_CENTER_X, ACCOUNT_TEXT_CENTER_Y));
	//userInput->setTag(FLTAG_AccountsTex);
	userInput->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
	passwordInput->setReturnType(kKeyboardReturnTypeGo);
	userInput->setAnchorPoint(ccp(0,0.5f));
	userInput->setFontColor(ccc3(0,0,0));
	//userInput->setFontSize(20);
	userInput->setDelegate(this);

	userInput->setPlaceHolder(ConfigMgr::instance()->text("t3"));
	addChild(userInput);
	addChild(passwordInput);


	//µÇÂ½//°´Å¥	
	CCSprite * denglNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_Logon1.png"));
	CCSprite * denglSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_Logon2.png"));
	CCSprite * denglDisSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_Logon2.png"));
	denglDisSprite->setColor(ccc3(100,100,100));
	m_pDengluItemSprite = CCMenuItemSprite::create(denglNormalSprite, denglSelectSprite, this, menu_selector(LoginLayer::onLogin));
	m_pLoginMenu = CCMenu::create(m_pDengluItemSprite,NULL);
	//denglSelectSprite->setScale(0.9f);
	//denglSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pLoginMenu->setPosition(ccp(LOGON_CENTER_X, LOGON_CENTER_Y));
	addChild(m_pLoginMenu);

	//×¢²á ÓÎ¿ÍµÇÂ½
	CCSprite * registNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_LogonRegister1.png"));
	CCSprite * registSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_LogonRegister2.png"));
	CCSprite* guestNormal = CCSprite::createWithSpriteFrame(spriteFrame("Button_LogonGuest1.png"));
	CCSprite* guestSelect = CCSprite::createWithSpriteFrame(spriteFrame("Button_LogonGuest2.png"));
	CCMenuItemSprite* regist = CCMenuItemSprite::create(registNormalSprite,registSelectSprite, this, menu_selector(LoginLayer::onRegist));
	//CCMenuItemSprite* change = CCMenuItemSprite::create(changePassNormal,changePassSelect,this,menu_selector(LoginLayer::changePassWord));
	CCMenuItemSprite* guestLogon = CCMenuItemSprite::create(guestNormal, guestSelect,this,menu_selector(LoginLayer::GuestLogon));
	regist->setPosition(ccp(REGISTER_CENTER_X, REGISTER_CENTER_Y));
	guestLogon->setPosition(ccp(GUEST_CENTER_X, GUEST_CENTER_Y));
	m_pRegisterMenu = CCMenu::create(regist,guestLogon,NULL);
	m_pRegisterMenu->setPosition(CCPointZero);
	//m_pRegisterMenu->alignItemsHorizontallyWithPadding(10);
	//m_pRegisterMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.1));
	addChild(m_pRegisterMenu);

	std::string userAccount = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_ACCOUNT");
	std::string userPassword = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");
	//std::string userAccount = DEFAULT_ACCOUNT;
	//std::string userPassword = DEFAULT_PASSWORD;

	if(userAccount.length() > 1 &&userPassword.length() > 1)
	{
		userInput->setText(userAccount.c_str());
		passwordInput->setText(userPassword.c_str());
	}

	DBHandler *handler = new DBHandler();
	//char sql[800] = {0};
	sqlite3 *DB = handler->getDB();
	sqlite3_stmt *stmt;
	char sql[1024];
	int rv = sqlite3_prepare(DB, "select * from AccountDB", 100, &stmt, NULL);
	rv = sqlite3_step(stmt);
	if(rv == SQLITE_ROW)
	{
		userInput->setText(CCString::createWithFormat("%s",sqlite3_column_text(stmt, 1))->getCString());
		passwordInput->setText(CCString::createWithFormat("%s",sqlite3_column_text(stmt, 2))->getCString());
	}
	sqlite3_finalize(stmt);

	setKeypadEnabled(true);

	if (!bLogin)
	{
		return  true;
	}
	return true;
}

void LoginLayer::onEnter()
{
	CCLayer::onEnter();
}
void LoginLayer::onExit()
{
	CCLayer::onExit();
}
void LoginLayer::onLoginFaild(CCObject* obj)
{
	m_pDengluItemSprite->setEnabled(true);
	CCLOG("login faied");
	PromptBox* box = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeLoginFaild);
	addChild(box,100);
}
void LoginLayer::setIsfaildLogin(bool mIsFaildLogin)
{

}
void LoginLayer::onRegist(cocos2d::CCObject *obj)
{
	playButtonSound();
	CCScene* scene = CCScene::create();
	RegistLayer * pRegisterLayer = RegistLayer::create();
	pRegisterLayer->setRegistLayerFrom(1);
	scene->addChild(pRegisterLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void LoginLayer::onLogin(cocos2d::CCObject *obj)
{
	CCLog("onLogin");
	playButtonSound();
	m_pDengluItemSprite->setEnabled(true);
	char* user = const_cast<char*>( userInput->getText());
	char* password = const_cast<char*>(passwordInput->getText());

	if(strlen(user) == 0)
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t36"),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer);
		return;
	}


	//char buf[50];
	//memset(buf, 0, 50);
	//utf::utf_gb_convert("utf-8", "gb2312", buf,50, user, strlen(user));

	bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	if (!bRet)
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t26"),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer);
		return;
	}
	else
	{
		EntityMgr::instance()->login()->setUserLogin(user, password);
	}
}
void LoginLayer::GuestLogon(cocos2d::CCObject *obj)
{
	playButtonSound();
	bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	if (!bRet)
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t26"),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer);
		return;
	}
	else
	{
		EntityMgr::instance()->login()->setUserRegister(createAccount().c_str(), createPassword().c_str(),0,1,0);
	}
}

void LoginLayer::setBoolFrom(bool b){
	m_from = b;
}

void LoginLayer::back(cocos2d::CCObject *obj)
{
	playButtonSound();
	if(m_bLogin)
	{
		if(!m_from)
		{
			RoomOption* option = RoomOption::create();
			CCScene* pScene = CCScene::create();
			pScene->addChild(option);
			CCDirector::sharedDirector()->replaceScene(pScene);
		}else{
			RoomLayer *pRoomLayer = RoomLayer::create();
			pRoomLayer->automaticLogin(false);
			CCScene* pScene = CCScene::create();
			pScene->addChild(pRoomLayer);
			CCDirector::sharedDirector()->replaceScene(pScene);

		}
	}
	else
	{
		CCDirector::sharedDirector()->end();
	}
}

void LoginLayer::keyBackClicked()
{
	back(NULL);
}

//void LoginLayer::feedBack(cocos2d::CCObject *obj)
//{
//    id sth = [[UIApplication sharedApplication]delegate];
//        AppController *controller = (AppController*)sth;
//    controller.window = [[UIWindow alloc]initWithFrame:[[UIScreen mainScreen] bounds]];
//    UMFeedbackViewController* feedBack = [[UMFeedbackViewController alloc]initWithNibName:@"UMFeedbackViewController" bundle:nil];
//    feedBack.appkey = UMENG_APPKEY;
//    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:feedBack];
//    controller.window.rootViewController = navigationController;
//    [controller.window makeKeyAndVisible];    
//}

void LoginLayer::onAnsLoginFinish(CCObject* obj)
{
	m_pDengluItemSprite->setEnabled(true);
	RoomLayer* layer = RoomLayer::create();
	layer->automaticLogin(false);
	CCScene* scene = CCScene::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void LoginLayer::onFindPassword(CCObject* obj)
{
	playButtonSound();
	tagGetPassObj* pObj = (tagGetPassObj*)obj;
	CCLOG((const char*)pObj->szErrorDescribe);
	if(pObj->lErrCode == 0)  //³É¹¦
	{
		PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypePasswordFind);
		box->setPromptText(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t164"),pObj->szPassword)->getCString());
		addChild(box,30);
		cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("NEWZJD_PASSWORD",pObj->szPassword);
		passwordInput->cleanup();
		passwordInput->setText(pObj->szPassword);

	}else
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(CCString::createWithFormat("%s",(const char*)pObj->szErrorDescribe)->getCString(),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer);
	}

	userInput->setTouchEnabled(true);
	passwordInput->setTouchEnabled(true);
	m_pLoginMenu->setTouchEnabled(true);
	m_pRegisterMenu->setTouchEnabled(true);
}

void LoginLayer::changePassWord(CCObject* obj)
{
	playButtonSound();
	if(m_bLogin)
	{
		CCDirector::sharedDirector()->replaceScene(ModifyPassWord::scene());
	}
	else
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t455"),ccp(427,240));
		addChild(layer);
	}

}
void LoginLayer::toFreeLayer(CCObject* obj){
	playButtonSound();
	if(m_bLogin)
	{
		CCDirector::sharedDirector()->replaceScene(FreeLayer::scene());
	}
}

//void LoginLayer::onUserList(CCObject* obj)
//{
//    tagUserListObj* obj1 = (tagUserListObj*)obj;
//    
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    
//    //ÏÂÀ­²Ëµ¥
//    m_pListSprite = CCSprite::createWithSpriteFrame(spriteFrame("list_back.png"));
//    m_pListSprite->setPosition(CCPointMake(winSize.width * 0.565, winSize.height * 0.43));
//    m_pListSprite->setScaleY(1.1);
//    addChild(m_pListSprite,10);
//    
//    m_pListView = ListViewLayer::create();
//    //m_pListView->setCeLLText((const char*)obj1->szUserNameList);
//    m_pListView->init();
//    
//    if(winSize.width == IPHONE5SIZE)
//    {
//        m_pListView->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.28));
//    }
//    else
//    {
//        m_pListView->setPosition(CCPointMake(winSize.width * 0.44, winSize.height * 0.28));
//    }
//    addChild(m_pListView,10);
//    
//    userInput->setTouchEnabled(false);
//    passwordInput->setTouchEnabled(false);
//    m_pLoginMenu->setTouchEnabled(false);
//    m_pRegisterMenu->setTouchEnabled(false);
//}

//void LoginLayer::onUserInfo(CCObject* obj)
//{
//    tagUserObj* obj1 = (tagUserObj*)obj;
//    userInput->setText((const char*)obj1->szUserName);
//
//    bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
//    if (!bRet)
//    {
//        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//        PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeLoginConnectFaild);
//        addChild(promptBox);
//        return;
//    }
//    
//    removeChild(m_pListSprite);
//    removeChild(m_pListView);
//    
//    EntityMgr::instance()->getDispatch()->findPassword((const char*)obj1->szUserName);
//}


string LoginLayer::createAccount()
{
	string szAccount;
	int t = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 4; i++)
	{
		//t = rand() % 2 ? 65 : 97;
		t = 97;
		t += rand() % 26;
		szAccount += (char)t;

	}

	for (int i = 0; i < 4; i++)
	{
		t = rand() % 10;
		szAccount +=  ans::AnsString::int2String(t);

	}
	return  szAccount;
}

string LoginLayer::createPassword()
{
	string szPassword;
	int t = 0;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 6; i++)
	{
		t = rand() % 10;
		szPassword +=  ans::AnsString::int2String(t);
	}
	return  szPassword;
}

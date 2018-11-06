//
//  roomLayer.cpp
//  Game
//
//  Created by zhouwei on 13-6-17.
//
//

#include "roomLayer.h"
#include "event/GBEventIDs.h"
#include "controls/tableViewLayer.h"
#include "configMgr/ConfigMgr.h"
#include "ans/utf-8.h"
#include "event/GBEvent.h"
#include "PlayerInfoLayer.h"
#include "RoomOption.h"
#include "EmailLayer.h"
#include "ActivityLayer.h"
#include "ExitLayer.h"
#include "CustomerServiceLayer.h"
#include "MovingLabelLayer.h"
#include "PromptBox.h"
#include "ddz/SceneControl.h"
#include "ddz/DDZRes.h"
#include "GeTCHARge.h"
#include "GroupSprite.h"
#include "TaskInfo.h"
#include "RuningBar.h"
#include "CShaderSprite.h"
#include "FreeLayer.h"
#include "common/packet.h"
#include "common/CMD_GameServer.h"
#include "FreeCoins.h"
#include "gui/MissionLayer.h"
#include "gui/FriendSystemLayer.h"
#include "gui/HelpLayer.h"
#include "gui/ShopSystemLayer.h"
#include "gui/MissionLayer.h"
#include "gui/ExchangerLayer.h"
#include "gui/LuckyDraw.h"
#include "gui/LoginLayer.h"
#include "gui/VIPSystemLayer.h"
#include "gui/RankSystemLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

using namespace cocos2d;
CCScene* RoomLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	CCLayer *layer = RoomLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

RoomLayer::RoomLayer()
{
	pWarningLayer=NULL;
	isGoingRoomLayer = 0;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::onUpdateScoreAndGoldEgg),MSG_UI_ANS_UPDATESCOREANDGOLDEGG , NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::showDailyGetCoins),MSG_UI_ANS_CANNELRECHANGER , NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(RoomLayer::showDailyGetCoinsResult),MSG_UI_ANS_GETSAVECOINS,NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::onlandcardResult),MSG_UI_ANS_LANDCARDRESULT , NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::onPhoneCardResult),MSG_UI_ANS_PHONECARDRESULT , NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::onLinkResult),MSG_UI_ANS_GAMELINK , NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::onRefshTotalNum),MSG_UI_ANS_REFRESHTOTALNUM, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::onChange),MSG_UI_ANS_CHARGE, NULL);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("CancelHttpRequest");
}

RoomLayer::~RoomLayer()
{
	GBEVENT_NOARG_UNREGISTER(GBEVENT_UI_LOGINFINISH, RoomLayer::onLoginFinish);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_REGNFAIL);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_CANNELRECHANGER);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_GETSAVECOINS);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_UPDATESCOREANDGOLDEGG);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_LANDCARDRESULT);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_PHONECARDRESULT);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_LOGINFAIL);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_CHARGE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_REFRESHTOTALNUM);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_GAMELINK);
}


void RoomLayer::automaticLogin(bool automatic,bool overResgist /* = false */)
{
	if(automatic)
	{

		bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
		if(bRet)
		{
			if(EntityMgr::instance()->login()->getAccout().length() > 0 && !overResgist)
			{
				onLoginFinish();
			}
			else
			{
				std::string userAccount = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_ACCOUNT");
				std::string userPassword = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");
				userAccount = DEFAULT_ACCOUNT;
				userPassword = DEFAULT_PASSWORD;
				if(userAccount.length() > 1 &&userPassword.length() > 1)
				{
					CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RoomLayer::onLoginFaild), MSG_UI_ANS_LOGINFAIL, NULL);
					GBEVENT_NOARG_REGISTER(GBEVENT_UI_LOGINFINISH, RoomLayer::onLoginFinish);

					bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
					if(!bRet)
					{
						MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t26"),ccp(winSize.width * 0.5,winSize.height * 0.5));
						addChild(layer,100);
					}
					else
					{
						EntityMgr::instance()->login()->setUserLogin(userAccount.c_str(), userPassword);
					}	
				}
				else
				{
					CCNotificationCenter::sharedNotificationCenter()->addObserver(
						this, callfuncO_selector(RoomLayer::onRegisterFaild), MSG_UI_ANS_REGNFAIL, NULL);

					CCNotificationCenter::sharedNotificationCenter()->addObserver(
						this, callfuncO_selector(RoomLayer::onRegistSucc), MSG_UI_ANS_REGSUCC, NULL);
					//没有账号 注册游客账号
					int nGender = 0;
					int nFaceId = 0;
					string szAccount = createAccount();
					string szPassword = createPassword();

					bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
					if (!bRet)
					{
						PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeServerShut);
						addChild(box,100);
					}
					EntityMgr::instance()->login()->setUserRegister(szAccount.c_str(),szPassword.c_str(),nFaceId,nGender,1);

				}
			}
		}
		else
		{
			PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeServerShut);
			addChild(box,100);
		}
	}
	else
	{
		string szText0;
		if(strlen(g_GlobalUnits.getGolbalUserData()->szNickName)>0)
		{
			CCLOG("have nick name");
			szText0 = g_GlobalUnits.getGolbalUserData()->szNickName;
		}
		else
		{
			CCLOG("not have nick name");
			szText0 = EntityMgr::instance()->login()->getAccout();
		}
		long scoreNumber = g_GlobalUnits.getGolbalUserData()->lScore;
		string szText1 = CCString::createWithFormat("%d",scoreNumber)->getCString();//addCommaToNumber(scoreNumber);
		string szText2 = CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString();//addCommaToNumber(telephonePointNumber);
		szText0 = ConfigMgr::instance()->text("t1002")+szText0;
		szText1 = ConfigMgr::instance()->text("t1003")+szText1;
		szText2 = ConfigMgr::instance()->text("t1004")+szText2;

		CCLabelTTF* userNmae;
		if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 0)
		{
			userNmae = CCLabelTTF::create(szText0.c_str(),"",20);
		}
		else
		{
			userNmae = CCLabelTTF::create(CCString::createWithFormat("%s%s%s", ConfigMgr::instance()->text("t1002"),ConfigMgr::instance()->text("t161"),szText0.c_str())->getCString(),"",20);
		}
		m_pUserScore = CCLabelTTF::create(szText1.c_str(),"",20);
		m_pUserPhonePoint = CCLabelTTF::create(szText2.c_str(),"",20);
		userNmae->setColor(ccc3(0,0,0));
		m_pUserScore->setColor(ccc3(0,0,0));
		m_pUserPhonePoint->setColor(ccc3(0,0,0));
		userNmae->setPosition(ccp(winSize.width * 0.1f,winSize.height * 0.965f));
		m_pUserScore->setPosition(ccp(winSize.width * 0.1f,winSize.height * 0.92f));
		m_pUserPhonePoint->setPosition(ccp(winSize.width * 0.1f,winSize.height * 0.875f));
		userNmae->setAnchorPoint(ccp(0.0f,0.5f));
		m_pUserScore->setAnchorPoint(ccp(0.0f,0.5f));
		m_pUserPhonePoint->setAnchorPoint(ccp(0.0f,0.5f));
		addChild(userNmae);
		addChild(m_pUserScore);
		addChild(m_pUserPhonePoint,0,301);

		CCSprite *pPlayerNormalSprite;
		CCSprite *pPlayerSelectSprite;
		if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
		{
			pPlayerNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_10.png"));
			pPlayerSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_10.png"));
		}
		else
		{
			pPlayerNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
			pPlayerSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
		}

		pPlayerMenuSprite->setNormalImage(pPlayerNormalSprite);
		pPlayerMenuSprite->setSelectedImage(pPlayerSelectSprite);
		//showLoginAward();
		return;
	}
}

void RoomLayer::onLoginFinish()
{
	GBEVENT_NOARG_UNREGISTER(GBEVENT_UI_LOGINFINISH, RoomLayer::onLoginFinish);
	//登陆完成
	string szText0;
	if(strlen(g_GlobalUnits.getGolbalUserData()->szNickName)>0)
	{
		CCLOG("have nick name");
		szText0 = g_GlobalUnits.getGolbalUserData()->szNickName;
	}
	else
	{
		CCLOG("not have nick name");
		szText0 = EntityMgr::instance()->login()->getAccout();
	}
	long scoreNumber = g_GlobalUnits.getGolbalUserData()->lScore;
	string szText1 = CCString::createWithFormat("%d",scoreNumber)->getCString();//addCommaToNumber(scoreNumber);
	long telephonePointNumber = g_GlobalUnits.getGolbalUserData()->lGoldEggs;
	string szText2 = CCString::createWithFormat("%d",telephonePointNumber)->getCString();//addCommaToNumber(telephonePointNumber);

	CCLabelTTF* userNmae;
	if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 0)
	{
		userNmae = CCLabelTTF::create(szText0.c_str(),"",20);
	}
	else
	{
		userNmae = CCLabelTTF::create(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t161"),szText0.c_str())->getCString(),"",20);
	}
	m_pUserScore = CCLabelTTF::create(szText1.c_str(),"",17);
	m_pUserPhonePoint = CCLabelTTF::create(szText2.c_str(),"",17);
	userNmae->setColor(ccc3(0,0,0));
	m_pUserScore->setColor(ccc3(0,0,0));
	m_pUserPhonePoint->setColor(ccc3(0,0,0));
	userNmae->setPosition(ccp(winSize.width * 0.1f,winSize.height * 0.948f));
	m_pUserScore->setPosition(ccp(winSize.width * 0.265f,winSize.height * 0.925f));
	m_pUserPhonePoint->setPosition(ccp(winSize.width * 0.265f,winSize.height * 0.875f));
	userNmae->setAnchorPoint(ccp(0.0f,0.0f));
	m_pUserScore->setAnchorPoint(ccp(1.0f,0.5f));
	m_pUserPhonePoint->setAnchorPoint(ccp(1.0f,0.5f));
	addChild(userNmae);
	addChild(m_pUserScore);
	addChild(m_pUserPhonePoint,0,301);

	CCSprite *pPlayerNormalSprite;
	CCSprite *pPlayerSelectSprite;
	if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
	{
		pPlayerNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_10.png"));
		pPlayerSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_10.png"));
	}
	else
	{
		pPlayerNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
		pPlayerSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
	}

	pPlayerMenuSprite->setNormalImage(pPlayerNormalSprite);
	pPlayerMenuSprite->setSelectedImage(pPlayerSelectSprite);
	showLoginAward();
}

void RoomLayer::onUpdateScoreAndGoldEgg(CCObject* obj)
{
	long scoreNumber = g_GlobalUnits.getGolbalUserData()->lScore;
	string szText1 = CCString::createWithFormat("%d",scoreNumber)->getCString();//addCommaToNumber(scoreNumber);
	long telephonePointNumber = g_GlobalUnits.getGolbalUserData()->lGoldEggs;
	string szText2 = CCString::createWithFormat("%d",telephonePointNumber)->getCString();//addCommaToNumber(telephonePointNumber);
	m_pUserScore->setString(szText1.c_str());
	m_pUserPhonePoint->setString(szText2.c_str());
}

void RoomLayer::onLoginFaild(CCObject* obj)
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_LOGINFAIL);
	CCLOG("login faied");

	PromptBox* box = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeLoginFaild);
	addChild(box,100);
}

void RoomLayer::onEnter()
{
	if(!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		playBGM("music/roomback.mp3");
	}
	BaseLayer::onEnter();
}

void RoomLayer::onExit()
{
	BaseLayer::onExit();
}

//void RoomLayer::onHideLevel(float dt)
//{
//    if (m_pPopFrame)
//    {
//        m_pPopFrame->actionOut(NULL);
//    }
//    unschedule(schedule_selector(RoomLayer::onHideLevel));
//}
bool RoomLayer::init()
{
	// 1. super init first
	if ( !BaseLayer::init() )
	{
		return false;
	}
	roomLevel = ROOM_LAYER_LEVEL_HOBBY;
	mMenuCloseOrOpen = false;
	isGoingRoomLayer =0;
	//    getUserInfo();

	//背景
	winSize = CCDirector::sharedDirector()->getWinSize();
	//   m_nBGMID = playSound("oomback.mp3", true);
	CCSprite *background = CCSprite::create("background/bg.png");
	background->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(background);	

	CCSprite *sprite = CCSprite::createWithSpriteFrame(spriteFrame("box.png"));
	sprite->setPosition(ccp(winSize.width/2+2,winSize.height/2+138));
	sprite->setScaleX(0.72f);
	this->addChild(sprite);
	//CCShaderSprite* hollBack = CCShaderSprite::create("dt_back.jpg");
	//hollBack->setAnchorPoint(ccp(0,0.5f));
	//hollBack->setPosition(CCPointMake(0, winSize.height * 0.5f));
	//addChild(hollBack);
	CCSprite* hollTop = CCSprite::createWithSpriteFrame(spriteFrame("dt_topbox.png"));
	hollTop->setPosition(CCPointMake(winSize.width * 0.5f, winSize.height - hollTop->getContentSize().height * 0.5));
	//addChild(hollTop);

	CCSprite* hollDown = CCSprite::createWithSpriteFrame(spriteFrame("dt_hall.png"));
	hollDown->setPosition(CCPointMake(winSize.width * 0.5, hollDown->getContentSize().height * 0.5));
	//addChild(hollDown);

	/**人物图像信息的按钮**/
	CCSprite *pPlayerNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
	CCSprite *pPlayerSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
	pPlayerMenuSprite = CCMenuItemSprite::create
		(pPlayerNormalSprite,pPlayerSelectSprite,this,menu_selector(RoomLayer::showPlayerInformation));

	m_pPlayerMenu= CCMenu::create(pPlayerMenuSprite,NULL);
	m_pPlayerMenu->setPosition(CCPointMake(winSize.width * 0.045, winSize.height * 0.921));  
	addChild(m_pPlayerMenu);

	//跑马条
	RuningBar* bar = RuningBar::create();
	addChild(bar,2);

	//底下菜单
	CCSprite *friendItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomFriend1.png"));
	CCSprite *friendItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomFriend2.png"));
	CCSprite *shopItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomShop1.png"));
	CCSprite *shopItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomShop2.png"));
	CCSprite *startGameItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomStartGame1.png"));
	CCSprite *startGameItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomStartGame2.png"));
	CCSprite *missionItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomTask1.png"));
	CCSprite *missionItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomTask2.png"));
	CCSprite *rankItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomRank1.png"));
	CCSprite *rankItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomRank2.png"));
	CCMenuItemSprite *friendItem = CCMenuItemSprite::create(friendItemNormalImage,friendItemSelectedImage,this,menu_selector(RoomLayer::toFriend));
	CCMenuItemSprite *shopItem = CCMenuItemSprite::create(shopItemNormalImage,shopItemSelectedImage,this,menu_selector(RoomLayer::toShop));
	CCMenuItemSprite *startGameItem = CCMenuItemSprite::create(startGameItemNormalImage,startGameItemSelectedImage,this,menu_selector(RoomLayer::onQuickStart));
	CCMenuItemSprite *missionItem = CCMenuItemSprite::create(missionItemNormalImage,missionItemSelectedImage,this,menu_selector(RoomLayer::mission));
	CCMenuItemSprite *rankItem = CCMenuItemSprite::create(rankItemNormalImage,rankItemSelectedImage,this,menu_selector(RoomLayer::toRank));
	m_pButtonMenu = CCMenu::create(friendItem,shopItem,startGameItem,missionItem,rankItem,NULL);
	m_pButtonMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.07));	
	m_pButtonMenu->alignItemsHorizontallyWithPadding(0.5);//设置排列方式，纵向间隔20
	this->addChild(m_pButtonMenu);

	////菜单
	//CCSprite * menuNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_menu.png"));
	//CCSprite * menuSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_menu.png"));
	////活动
	//CCSprite * huodongNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_huodong.png"));
	//CCSprite * huodongSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_huodong.png"));
	////领话费
	//CCSprite * lingNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_linghf.png"));
	//CCSprite * lingSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_linghf.png"));
	////充金币
	//CCSprite * chongNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_chongcoins.png"));
	//CCSprite * chongSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_chongcoins.png"));
	//CCMenuItemSprite * menuS = CCMenuItemSprite::create(menuNormalSprite,menuSelectSprite, this, menu_selector(RoomLayer::toMenu));
	//menuSelectSprite->setScale(0.9f);
	//menuSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	//CCMenuItemSprite * huodongS = CCMenuItemSprite::create(huodongNormalSprite, huodongSelectSprite,this,menu_selector(RoomLayer::huodong));
	//huodongSelectSprite->setScale(0.9f);
	//huodongSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	//CCMenuItemSprite * lingS = CCMenuItemSprite::create(lingNormalSprite, lingSelectSprite,this,menu_selector(RoomLayer::geTCHARge));
	//lingSelectSprite->setScale(0.9f);
	//lingSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	//CCMenuItemSprite * chongS = CCMenuItemSprite::create(chongNormalSprite, chongSelectSprite,this,menu_selector(RoomLayer::rechange));
	//chongSelectSprite->setScale(0.9f);
	//chongSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	//m_pButtonMenu = CCMenu::create(menuS,huodongS,lingS,chongS,NULL);
	//m_pButtonMenu->alignItemsHorizontallyWithPadding(107);
	//m_pButtonMenu->setPosition(ccp(winSize.width * 0.41, winSize.height * 0.07));
	//addChild(m_pButtonMenu);

	//快速开始
	/*CCSprite * startNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_quickstart.png"));
	CCSprite * startSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_quickstart.png"));
	CCMenuItemSprite * startS = CCMenuItemSprite::create(startNormalSprite,startSelectSprite, this, menu_selector(RoomLayer::onQuickStart));
	startSelectSprite->setScale(0.9f);
	startSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pStartMenu = CCMenu::create(startS,NULL);
	m_pStartMenu->setPosition(ccp(winSize.width - startNormalSprite->getContentSize().width * 0.55,-4));

	addChild(m_pStartMenu);
	startS->setAnchorPoint(ccp(0.5,0.0));

	CCRotateBy* action1 = CCRotateBy::create(0.6f,10);
	CCRotateBy* action2 = CCRotateBy::create(0.6f,-10);
	startS->runAction(CCRepeatForever::create(CCSequence::create(action1,action2,NULL)));
	CCLog("11111111111111114444444");*/
	//充金币 小按钮
	/*CCSprite * schongNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_chong.png"));
	CCSprite * schongSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_chong.png"));
	CCMenuItemSprite * chongSS = CCMenuItemSprite::create(schongNormalSprite,schongSelectSprite, this, menu_selector(RoomLayer::rechangeLittleButton));
	schongSelectSprite->setScale(0.9f);
	schongSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pchongSMenu = CCMenu::create(chongSS,NULL);
	m_pchongSMenu->setPosition(ccp(winSize.width * 0.305f,winSize.height * 0.905f));
	addChild(m_pchongSMenu);*/
	m_pStartMenu = CCMenu::create();
	this->addChild(m_pStartMenu);
	//m_pchongSMenu = CCMenu::create();
	//this->addChild(m_pchongSMenu);

	//中间
	CCSprite *RabateItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomExchange1.png"));
	CCSprite *RabateItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomExchange2.png"));
	CCSprite *FackItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomLuck1.png"));
	CCSprite *FackItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomLuck2.png"));
	CCSprite *vipItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomVip1.png"));
	CCSprite *vipItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomVip2.png"));
	CCMenuItemSprite *RabateItem = CCMenuItemSprite::create(RabateItemNormalImage,RabateItemSelectedImage,this,menu_selector(RoomLayer::toExchange));
	CCMenuItemSprite *vipItem = CCMenuItemSprite::create(vipItemNormalImage,vipItemSelectedImage,this,menu_selector(RoomLayer::toVIP));
	CCMenuItemSprite *FackItem = CCMenuItemSprite::create(FackItemNormalImage,FackItemSelectedImage,this,menu_selector(RoomLayer::toLuckyDraw));
	RabateItem->setPosition(ccp(52, 104));
	vipItem->setPosition(ccp(626, RabateItem->getPositionY()));
	FackItem->setPosition(ccp(739, RabateItem->getPositionY()));
	m_pOtherMenu = CCMenu::create(RabateItem,FackItem, vipItem,NULL);
	m_pOtherMenu->setPosition(ccp(0,0));	
	//m_pOtherMenu->alignItemsHorizontallyWithPadding(winSize.width-winSize.width/4);
	background->addChild(m_pOtherMenu,0);

	//上面菜单
	CCSprite *FreeGoldItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomFreeGold1.png"));
	CCSprite *FreeGoldItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomFreeGold2.png"));
	CCSprite *TodayRewardItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomDailyBonus1.png"));
	CCSprite *TodayRewardItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomDailyBonus2.png"));
	CCSprite *SetupItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomSet1.png"));
	CCSprite *SetupItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomSet2.png"));
	CCSprite *HelpItemNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomHelp1.png"));
	CCSprite *HelpItemSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomHelp2.png"));
	CCSprite *messageSNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomInfo1.png"));
	CCSprite *messageSSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomInfo2.png"));
	CCSprite *backNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomBack1.png"));
	CCSprite *backSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomBack2.png"));
	CCMenuItemSprite *FreeGoldItem = CCMenuItemSprite::create(FreeGoldItemNormalImage,FreeGoldItemSelectedImage,this,menu_selector(RoomLayer::rechange));
	CCMenuItemSprite *TodayRewardItem = CCMenuItemSprite::create(TodayRewardItemNormalImage,TodayRewardItemSelectedImage,this,menu_selector(RoomLayer::signIn));
	CCMenuItemSprite *SetupItem = CCMenuItemSprite::create(SetupItemNormalImage,SetupItemSelectedImage,this,menu_selector(RoomLayer::setting));
	CCMenuItemSprite *HelpItem = CCMenuItemSprite::create(HelpItemNormalImage,HelpItemSelectedImage,this,menu_selector(RoomLayer::toHelp));
	CCMenuItemSprite *messageS = CCMenuItemSprite::create(messageSNormalImage,messageSSelectedImage,this,menu_selector(RoomLayer::message));
	CCMenuItemSprite *backItem = CCMenuItemSprite::create(backNormalImage,backSelectedImage,this,menu_selector(RoomLayer::pressBack));
	m_pTopMenu = CCMenu::create(FreeGoldItem,TodayRewardItem,SetupItem,HelpItem,messageS,backItem,NULL);
	m_pTopMenu->setPosition(ccp(winSize.width * 0.63, winSize.height * 0.93));
	m_pTopMenu->alignItemsHorizontallyWithPadding(30);//设置排列方式，纵向间隔20
	this->addChild(m_pTopMenu);
	/*//任务
	CCSprite * missionNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_mission.png"));
	CCSprite * missionSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_mission.png"));
	//消息
	CCSprite * messageNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_mail.png"));
	CCSprite * messageSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_mail.png"));
	//设置
	CCSprite * settingNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_setting.png"));
	CCSprite * settingSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_setting.png"));
	CCMenuItemSprite * missionS = CCMenuItemSprite::create(missionNormalSprite,missionSelectSprite, this, menu_selector(RoomLayer::mission));
	missionSelectSprite->setScale(0.9f);
	missionSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenuItemSprite * messageS = CCMenuItemSprite::create(messageNormalSprite, messageSelectSprite,this,menu_selector(RoomLayer::message));
	messageSelectSprite->setScale(0.9f);
	messageSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenuItemSprite * settingS = CCMenuItemSprite::create(settingNormalSprite, settingSelectSprite,this,menu_selector(RoomLayer::setting));
	settingSelectSprite->setScale(0.9f);
	settingSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pTopMenu  = CCMenu::create(missionS,messageS,settingS,NULL);
	m_pTopMenu->alignItemsHorizontallyWithPadding(10);
	m_pTopMenu->setPosition(ccp(winSize.width * 0.85, winSize.height * 0.93));
	addChild(m_pTopMenu);
	CCLog("11111111111111111555555");*/
	//消息数量
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("MESSAGESCAN",false))
	{
		m_MessageNumBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_messagepoint.png"));
		m_MessageNumBack->setPosition(ccp(winSize.width * 0.88,winSize.height * 0.97));
		addChild(m_MessageNumBack);
		m_MessageNum = CCLabelTTF::create("2","",12);
		m_MessageNum->setPosition(ccp(winSize.width * 0.88,winSize.height * 0.97));
		addChild(m_MessageNum);
	}

	//中间菜单
	CCSprite *BackLandlordNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemDDZ1.png"));
	CCSprite *BackLandlordSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemDDZ2.png"));
	CCSprite *ShakeNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemYYL1.png"));
	CCSprite *ShakeSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemYYL2.png"));
	CCSprite *Lucky28NormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemXY1.png"));
	CCSprite *Lucky28SelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemXY2.png"));
	CCSprite *NiuniuNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemNN1.png"));
	CCSprite *NiuniuSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemNN2.png"));
	CCSprite *ZajinHuaNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemZJH1.png"));
	CCSprite *ZajinHuaSelectedImage = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomGameItemZJH2.png"));
	CCMenuItemSprite *BackLandlord = CCMenuItemSprite::create(BackLandlordNormalImage, BackLandlordSelectedImage,this, menu_selector(RoomLayer::DDZItemCallback));
	CCMenuItemSprite *Shake = CCMenuItemSprite::create(ShakeNormalImage, ShakeSelectedImage,this, menu_selector(RoomLayer::onQuickStart));
	CCMenuItemSprite *Lucky28 = CCMenuItemSprite::create(Lucky28NormalImage, Lucky28SelectedImage,this, menu_selector(RoomLayer::Lucky28ItemCallback));
	CCMenuItemSprite *Niuniu = CCMenuItemSprite::create(NiuniuNormalImage, NiuniuSelectedImage,this, menu_selector(RoomLayer::NiuniuItemCallback));
	CCMenuItemSprite *ZajinHua = CCMenuItemSprite::create(ZajinHuaNormalImage, ZajinHuaSelectedImage,this, menu_selector(RoomLayer::ZajinHuaItemCallback));
	m_pMiddleHobbyMenu = GameItemLayer::create();
	m_pMiddleHobbyMenu->addMenuItem(BackLandlord);
	m_pMiddleHobbyMenu->addMenuItem(Shake);
	m_pMiddleHobbyMenu->addMenuItem(Lucky28);
	m_pMiddleHobbyMenu->addMenuItem(Niuniu);
	m_pMiddleHobbyMenu->addMenuItem(ZajinHua);
	//m_pMiddleHobbyMenu->setPosition(winSize/2);
	this->addChild(m_pMiddleHobbyMenu);


	//普通场
	CCSprite * normalNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomTypical.png"));
	CCSprite * normalSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomTypical.png"));
	normalSelectSprite->setScale(0.9f);
	//疯狂炸弹场
	CCSprite * otherNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomCrazy.png"));
	CCSprite * otherSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("Button_RoomCrazy.png"));
	otherSelectSprite->setScale(0.9f);
	CCMenuItemSprite * normalS = CCMenuItemSprite::create(normalNormalSprite,normalSelectSprite, this, menu_selector(RoomLayer::toNormalGame));
	normalS->setEnabled(true);
	CCMenuItemSprite * otherS = CCMenuItemSprite::create(otherNormalSprite, otherSelectSprite,this,menu_selector(RoomLayer::toOtherGame));
	otherS->setEnabled(true);
	m_pMiddleMenu = CCMenu::create(normalS,otherS,NULL);
	m_pMiddleMenu->alignItemsHorizontallyWithPadding(20);
	m_pMiddleMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	addChild(m_pMiddleMenu);
	m_pMiddleMenu->setVisible(false);

	//中间菜单
	//初级场
	GroupSprite * primaryNormalSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel1.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.44))->getCString(),GorupSpriteTypePhotoAndText1,3);
	GroupSprite * primarySelectSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel1.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.44))->getCString(),GorupSpriteTypePhotoAndText1,3);

	//中级场
	GroupSprite * middleNormalSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel2.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.3))->getCString(),GorupSpriteTypePhotoAndText1,2);
	GroupSprite * middleSelectSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel2.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.3))->getCString(),GorupSpriteTypePhotoAndText1,2);

	//高级场
	GroupSprite * seniyNormalSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel3.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.26))->getCString(),GorupSpriteTypePhotoAndText1,1);
	GroupSprite * seniySelectSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel3.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.26))->getCString(),GorupSpriteTypePhotoAndText1,1);

	//顶级场
	GroupSprite * superNormalSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel4.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.26))->getCString(),GorupSpriteTypePhotoAndText1,1);
	GroupSprite * superSelectSprite = GroupSprite::GroupSpriteWith("Button_RoomLevel4.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.26))->getCString(),GorupSpriteTypePhotoAndText1,1);
	m_pPrimaryS = CCMenuItemSprite::create(primaryNormalSprite,primarySelectSprite, this, menu_selector(RoomLayer::toPrimaryGame));
	primarySelectSprite->setScale(0.9f);
	primarySelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pMiddleS = CCMenuItemSprite::create(middleNormalSprite, middleSelectSprite,this,menu_selector(RoomLayer::toMiddleGame));
	middleSelectSprite->setScale(0.9f);
	middleSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pSeniyS = CCMenuItemSprite::create(seniyNormalSprite, seniySelectSprite,this,menu_selector(RoomLayer::toSeniyGame));
	seniySelectSprite->setScale(0.9f);
	seniySelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pSuperS = CCMenuItemSprite::create(superNormalSprite, superSelectSprite,this,menu_selector(RoomLayer::toSuperGame));
	superSelectSprite->setScale(0.9f);
	superSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	m_pMiddleMenu2 = CCMenu::create(m_pPrimaryS,m_pMiddleS,m_pSeniyS,m_pSuperS,NULL);
	m_pMiddleMenu2->alignItemsHorizontallyWithPadding(1);
	m_pMiddleMenu2->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
	addChild(m_pMiddleMenu2);

	this->setRoomLayerLevel(ROOM_LAYER_LEVEL_HOBBY);
	//CCParticleSystemQuad* particle1 = CCParticleSystemQuad::create("shanguang.plist");
	////particle1->setPosition(CCPointMake(100.0f,100.0f));
	//addChild(particle1,5);
	//particle1->setVisible(true);
	//particle1->setAutoRemoveOnFinish(true);

	if(TaskInfo::ShareTaskInfo()->m_nUMMessage > 0)
	{
		m_UMMessageNumBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_messagepoint.png"));
		m_UMMessageNumBack->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.79));
		addChild(m_UMMessageNumBack,10);
		m_UMMessageNum = CCLabelTTF::create(CCString::createWithFormat("%d",TaskInfo::ShareTaskInfo()->m_nUMMessage)->getCString(),"",12);
		m_UMMessageNum->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.79));
		addChild(m_UMMessageNum,10);
	}

	if(CCUserDefault::sharedUserDefault()->getBoolForKey("FIRSTRUN",true))
	{
		toNormalGame(NULL);
		CCUserDefault::sharedUserDefault()->setBoolForKey("FIRSTRUN",false);
	}

	gameToBankrupt(false);

	setKeypadEnabled(true);
	setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne);
	return  true;
}

void RoomLayer::showLoginAward()
{
	isGoingRoomLayer++;
	forbidButtonClick();
	if(pWarningLayer==NULL)
	{
		pWarningLayer = WarningLayer::create();
		addChild(pWarningLayer,10);
		pWarningLayer->setVisible(false);
	}
	pWarningLayer->setVisible(true);
}
void RoomLayer::closeLoginAward(){
	/*permitButtonClick();
	pWarningLayer->removeFromParentAndCleanup(true);*/
}

void RoomLayer::showSelectHead(CCObject* obj)
{
	CCLOG("select head");
}

void RoomLayer::onStart(ROOM_TYPE index)
{
	//   
	bool ret = EntityMgr::instance()->getDispatch()->connectGameServer((int)index);
	if (!ret)
	{
		PromptBox* box = PromptBox::PromptBoxWith(ccp(427,240),mPromptTypeServerShut);
		addChild(box,20);
		return;

	}

	EntityMgr::instance()->getDispatch()->SendPacketWithEnterRoomPageCount(6);
	EntityMgr::instance()->getDispatch()->setStartType(false);
}

//
//void RoomLayer::shangcheng(cocos2d::CCObject *obj)
//{
//    
//}
//

void RoomLayer::showPlayerInformation(CCObject *obj){
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	CCScene *pScene = CCScene::create();
	PlayerInfoLayer *pPlayInfoLayer = PlayerInfoLayer::create();
	pScene->addChild(pPlayInfoLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
	//addChild(pPlayInfomation);

}

/**底下菜单函数*/
void RoomLayer::toFriend(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	FriendSystemLayer *tabLayer = FriendSystemLayer::create();
	//addChild(tabLayer,10);

	CCScene *scene = CCScene::create();
	scene->addChild(tabLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void RoomLayer::toShop(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	ShopSystemLayer *tabLayer = ShopSystemLayer::create();
	//addChild(tabLayer,10);

	CCScene *scene = CCScene::create();
	scene->addChild(tabLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

//快速游戏          add by wangjun
void RoomLayer::onQuickStart(CCObject *pSender)
{
	bool ret = EntityMgr::instance()->getDispatch()->connectGameServer();
	if (!ret)
	{
		PromptBox* box = PromptBox::PromptBoxWith(ccp(427,240),mPromptTypeServerShut);
		addChild(box,20);
		return;

	}
	EntityMgr::instance()->getDispatch()->setBehaviorFlag(BEHAVIOR_LOGON_IMMEDIATELY|VIEW_MODE_PART);
	EntityMgr::instance()->getDispatch()->SendPacketWithEnterRoomPageCount(6);
	EntityMgr::instance()->getDispatch()->setBehaviorFlag(BEHAVIOR_LOGON_NORMAL);
	EntityMgr::instance()->getDispatch()->setStartType(true);
}

void RoomLayer::mission(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	MissionLayer *missionLayer = MissionLayer::create();
	//addChild(missionLayer,10);
	CCScene *scene = CCScene::create();
	scene->addChild(missionLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void RoomLayer::toRank(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	RankSystemLayer *tabLayer = RankSystemLayer::create();
	//addChild(tabLayer,10);

	CCScene *scene = CCScene::create();
	scene->addChild(tabLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

/**中间菜单*/
void RoomLayer::toExchange(CCObject* obj)	
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	ExchangerLayer *missionLayer = ExchangerLayer::create();
	//addChild(missionLayer,10);
	CCScene *scene = CCScene::create();
	scene->addChild(missionLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
}	

void RoomLayer::toLuckyDraw(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	LuckyDraw *layer = LuckyDraw::create();
	addChild(layer,10);
}

void RoomLayer::toVIP(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	pWarningLayer = VIPSystemLayer::create();
	addChild(pWarningLayer,10);
}

/**上面菜单函数*/

void RoomLayer::rechange(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	FreeCoins* freeCoins = FreeCoins::create();
	CCScene* pScene = CCScene::create();
	pScene->addChild(freeCoins);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void RoomLayer::signIn(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	pWarningLayer = WarningLayer::create();
	addChild(pWarningLayer,10);
}

void RoomLayer::setting(CCObject* obj)
{
	//playButtonSound();
	//RoomOption* option = RoomOption::create();
	//CCScene* pScene = CCScene::create();
	//pScene->addChild(option);
	//CCDirector::sharedDirector()->replaceScene(pScene);

	playButtonSound();
	//isGoingRoomLayer = true;
	if (!mMenuCloseOrOpen)
	{
		mMenuLayer = MenuLayer::create();
		//mMenuLayer->setVisible(true);
		addChild(mMenuLayer,2);
		mMenuCloseOrOpen = true;
	}else{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
	}
}

void RoomLayer::message(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	CCUserDefault::sharedUserDefault()->setBoolForKey("MESSAGESCAN",true);
	CCScene* scene = CCScene::create();
	EmailLayer* layer = EmailLayer::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void RoomLayer::toHelp(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	CCScene *scene = CCScene::create();
	HelpLayer *pHelplayer = HelpLayer::create();
	scene->addChild(pHelplayer);
	CCDirector::sharedDirector()->replaceScene(scene); 
}

void RoomLayer::pressBack(CCObject* obj)
{
	if(roomLevel == ROOM_LAYER_LEVEL_HOBBY)
	{
		LoginLayer *layer = LoginLayer::create();
		CCScene *scene = CCScene::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}else if(roomLevel == ROOM_LAYER_LEVEL_GAMETYPE)
	{
		this->gameBackButton(NULL);
	}else if(roomLevel == ROOM_LAYER_LEVEL_GAMEROOM)
	{
		this->matchBackButton(NULL);
	}
}

void RoomLayer::toMenu(CCObject* obj)
{
	playButtonSound();
	//isGoingRoomLayer = true;
	if (!mMenuCloseOrOpen)
	{
		mMenuLayer = MenuLayer::create();
		//mMenuLayer->setVisible(true);
		addChild(mMenuLayer);
		mMenuCloseOrOpen = true;
	}else{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
	}
}

void RoomLayer::rechangeLittleButton(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	if(mMenuCloseOrOpen){
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//低等级 = 1 中等级 = 2 高等级 = 3 有X = 1 没X = 2
	if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[(((1-1) % 3 ) << 1) + 1])
	{
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"1","5");
	}
	else if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[(((2-1) % 3 ) << 1) + 1])
	{
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"2","5");
	}
	else
	{
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"3","5");
	}

#endif
}

void RoomLayer::huodong(cocos2d::CCObject *obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	if(mMenuCloseOrOpen){
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
	}
	CCScene *scene = CCScene::create();
	ActivityLayer * pActivityLayer = ActivityLayer::create();
	scene->addChild(pActivityLayer);
	CCDirector::sharedDirector()->replaceScene(scene);
	//playButtonSound();
	//PesentCoinsLayer* layer = PesentCoinsLayer::PesentCoinsLayerWith(CCPointMake(CCDirector::sharedDirector()->getWinSize().width * 0.5,CCDirector::sharedDirector()->getWinSize().height * 0.5));
	//addChild(layer,50);
}

void RoomLayer::geTCHARge(cocos2d::CCObject *obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	if(mMenuCloseOrOpen){
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
	}

	GeTCHARge* getChangeLyaer = GeTCHARge::GeTCHARgeWith(ccp(winSize.width * 0.5,winSize.height * 0.5));
	addChild(getChangeLyaer,5);

}

void RoomLayer::DDZItemCallback( CCObject* pSender )
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMETYPE);
}

void RoomLayer::ShakeItemCallback( CCObject* pSender )
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	//this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMETYPE);
}

void RoomLayer::Lucky28ItemCallback( CCObject* pSender )
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	//this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMETYPE);
}

void RoomLayer::NiuniuItemCallback( CCObject* pSender )
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	//this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMETYPE);
}

void RoomLayer::ZajinHuaItemCallback( CCObject* pSender )
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	//this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMETYPE);
}

void RoomLayer::toNormalGame(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	m_nGameType = 0;
	this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMEROOM);
}

void RoomLayer::toOtherGame(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	m_nGameType = 1;
	this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMEROOM);
}

void RoomLayer::gameBackButton(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	this->setRoomLayerLevel(ROOM_LAYER_LEVEL_HOBBY);
}

void RoomLayer::matchBackButton(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	playButtonSound();
	this->setRoomLayerLevel(ROOM_LAYER_LEVEL_GAMETYPE);
}

void RoomLayer::setRoomLayerLevel(ROOM_LAYER_LEVEL level)
{
	if(level == ROOM_LAYER_LEVEL_HOBBY)
	{
		roomLevel = ROOM_LAYER_LEVEL_HOBBY;
		m_pMiddleMenu->setVisible(false);
		m_pMiddleMenu->setEnabled(false);

		m_pMiddleMenu2->setVisible(false);
		m_pMiddleMenu2->setEnabled(false);

		m_pMiddleHobbyMenu->setTouchEnabled(true);
		m_pMiddleHobbyMenu->setVisible(true);
		m_pMiddleHobbyMenu->setEnabled(true);
	}else if(level == ROOM_LAYER_LEVEL_GAMETYPE)
	{
		roomLevel = ROOM_LAYER_LEVEL_GAMETYPE;
		m_pMiddleMenu2->setVisible(false);
		m_pMiddleMenu2->setEnabled(false);
		m_pMiddleMenu->setVisible(true);
		m_pMiddleMenu->setEnabled(true);
		m_pMiddleHobbyMenu->setTouchEnabled(false);
		m_pMiddleHobbyMenu->setVisible(false);
		m_pMiddleHobbyMenu->setEnabled(false);
	}else if(level == ROOM_LAYER_LEVEL_GAMEROOM)
	{
		roomLevel = ROOM_LAYER_LEVEL_GAMEROOM;
		m_pMiddleMenu2->setVisible(true);
		m_pMiddleMenu2->setEnabled(true);
		m_pMiddleMenu->setVisible(false);
		m_pMiddleMenu->setEnabled(false);
		m_pMiddleHobbyMenu->setTouchEnabled(false);
		m_pMiddleHobbyMenu->setVisible(false);
		m_pMiddleHobbyMenu->setEnabled(false);
	}
}

void RoomLayer::toPrimaryGame(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	long lksdnb = ConfigMgr::instance()->m_Config.nServerEnter[3];
	if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[3])
	{
		PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptStartFaild);
		box->setPromptText(ConfigMgr::instance()->text("t451"));
		addChild(box,20);
		//MovingLabelLayer* moveingLayer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t450"),ccp(427,240));
		//addChild(moveingLayer,20);
		return;
	}
	//	if(g_GlobalUnits.getGolbalUserData()->lScore < 500)
	//	{
	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"1","4");
	//#endif
	//		return;
	//	}
	onStart(ROOM_TYPE_Primary);
}

void RoomLayer::toMiddleGame(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	long nefiugbv = ConfigMgr::instance()->m_Config.nServerEnter[2];
	//if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[2])
	//{
	//	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//	//		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"2","3");
	//	//#endif
	//	MovingLabelLayer* moveingLayer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t451"),ccp(427,240));
	//	addChild(moveingLayer,20);
	//	return;
	//}
	//if(g_GlobalUnits.getGolbalUserData()->lScore >= 80000)
	//{
	//	PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptStartFaild);
	//	box->setPromptText(ConfigMgr::instance()->text("t450"));
	//	addChild(box,20);
	//	return;
	//}
	onStart(ROOM_TYPE_Middle);
}

void RoomLayer::toSeniyGame(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[1])
	{
		//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"3","3");
		//#endif
		MovingLabelLayer* moveingLayer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t451"),ccp(427,240));
		addChild(moveingLayer,20);
		return;
	}
	onStart(ROOM_TYPE_Seniy);
}

void RoomLayer::toSuperGame(CCObject* obj)
{
	if (mMenuCloseOrOpen)
	{
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
		return;
	}
	if(g_GlobalUnits.getGolbalUserData()->lScore < ConfigMgr::instance()->m_Config.nServerEnter[0])
	{
		//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"3","3");
		//#endif
		MovingLabelLayer* moveingLayer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t451"),ccp(427,240));
		addChild(moveingLayer,20);
		return;
	}
	onStart(ROOM_TYPE_Super);
}

void RoomLayer::toPhoneKefu(CCObject* obj)
{
	playButtonSound();
	isGoingRoomLayer++;
	forbidButtonClick();
	if(mMenuCloseOrOpen){
		mMenuLayer->removeFromParentAndCleanup(true);
		mMenuCloseOrOpen=false;
	}
	pCustomerService = CustomerServiceLayer::create();
	addChild(pCustomerService,50);
	/*ExitLayer* layer = ExitLayer::create();
	addChild(layer);	*/		
}

void RoomLayer::permitButtonClick()
{
	m_pPlayerMenu->setTouchEnabled(true);			
	m_pButtonMenu->setTouchEnabled(true);			
	m_pStartMenu->setTouchEnabled(true);			
	m_pTopMenu->setTouchEnabled(true);				
	m_pMiddleMenu->setTouchEnabled(true);
	m_pMiddleMenu2->setTouchEnabled(true);
	//m_pKefuMenu->setTouchEnabled(true);
	m_pOtherMenu->setTouchEnabled(true);
	m_pMiddleHobbyMenu->setTouchEnabled(true);
}

void RoomLayer::forbidButtonClick()
{
	m_pPlayerMenu->setTouchEnabled(false);			
	m_pButtonMenu->setTouchEnabled(false);			
	m_pStartMenu->setTouchEnabled(false);			
	m_pTopMenu->setTouchEnabled(false);				
	m_pMiddleMenu->setTouchEnabled(false);
	m_pMiddleMenu2->setTouchEnabled(false);
	//m_pKefuMenu->setTouchEnabled(false);
	m_pOtherMenu->setTouchEnabled(false);
	m_pMiddleHobbyMenu->setTouchEnabled(false);
}

string RoomLayer::createAccount()
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

string RoomLayer::createPassword()
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

void RoomLayer::onRegistSucc(CCObject* obj)
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_REGSUCC);
	string szText0;
	if(strlen(g_GlobalUnits.getGolbalUserData()->szNickName)>0)
	{
		CCLOG("have nick name");
		szText0 = g_GlobalUnits.getGolbalUserData()->szNickName;
	}
	else
	{
		CCLOG("not have nick name");
		szText0 = EntityMgr::instance()->login()->getAccout();
	}
	long scoreNumber = g_GlobalUnits.getGolbalUserData()->lScore;
	string szText1 = CCString::createWithFormat("%d",scoreNumber)->getCString();//addCommaToNumber(scoreNumber);
	long telephonePointNumber = g_GlobalUnits.getGolbalUserData()->lGoldEggs;
	string szText2 = CCString::createWithFormat("%d",telephonePointNumber)->getCString();//addCommaToNumber(telephonePointNumber);


	CCLabelTTF* userNmae;
	if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 0)
	{
		userNmae = CCLabelTTF::create(szText0.c_str(),"",20);
	}
	else
	{
		userNmae = CCLabelTTF::create(CCString::createWithFormat("%s%s",ConfigMgr::instance()->text("t161"),szText0.c_str())->getCString(),"",20);
	}
	m_pUserScore = CCLabelTTF::create(szText1.c_str(),"",17);
	m_pUserPhonePoint = CCLabelTTF::create(szText2.c_str(),"",17);
	userNmae->setColor(ccc3(0,0,0));
	m_pUserScore->setColor(ccc3(0,0,0));
	m_pUserPhonePoint->setColor(ccc3(0,0,0));
	userNmae->setPosition(ccp(winSize.width * 0.1f,winSize.height * 0.948f));
	m_pUserScore->setPosition(ccp(winSize.width * 0.265f,winSize.height * 0.925f));
	m_pUserPhonePoint->setPosition(ccp(winSize.width * 0.265f,winSize.height * 0.875f));
	userNmae->setAnchorPoint(ccp(0.0f,0.0f));
	m_pUserScore->setAnchorPoint(ccp(1.0f,0.5f));
	m_pUserPhonePoint->setAnchorPoint(ccp(1.0f,0.5f));
	addChild(userNmae);
	addChild(m_pUserScore);
	addChild(m_pUserPhonePoint,0,301);

	CCSprite *pPlayerNormalSprite;
	CCSprite *pPlayerSelectSprite;
	if(g_GlobalUnits.getGolbalUserData()->cbGender == 1)
	{
		pPlayerNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_10.png"));
		pPlayerSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_10.png"));
	}
	else
	{
		pPlayerNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
		pPlayerSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
	}

	pPlayerMenuSprite->setNormalImage(pPlayerNormalSprite);
	pPlayerMenuSprite->setSelectedImage(pPlayerSelectSprite);
	showLoginAward();
}

void RoomLayer::onlandcardResult(CCObject* obj)
{
	CCString* str = (CCString*)obj;
	MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(str->getCString(),ccp(427,240));
	addChild(layer,20);
}

void RoomLayer::onPhoneCardResult(CCObject* obj)
{
	CCString* str = (CCString*)obj;
	MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(str->getCString(),ccp(427,240));
	addChild(layer,20);
}

void RoomLayer::onLinkResult(CCObject* obj)
{
	CCInteger* Interger = (CCInteger*)obj;

	switch (Interger->getValue())
	{
	case 0:			// 0为连接失败 
		break;

	case 1:			// 1为连接成功
		{
			//EntityMgr::instance()->getDispatch()->sendLoginPacket();
			SceneControl* pSceneControl = SceneControl::sharedSceneControl();
			CCScene* pScene = pSceneControl->getScene(SCENE_game,true);
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
		break;

	case 2:			// 2为没有服务器
		{
			PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeMakeSureModifyNickName);
			box->setPromptText(ConfigMgr::instance()->text("t475"));
			addChild(box,100);
		}
		break;
	case 3:
		{
			//破产弹框
			gameToBankrupt(true);
		}

	default:
		break;
	}
}
void RoomLayer::setGoingRoomLayer(){
	isGoingRoomLayer++;
}

void RoomLayer::keyBackClicked()
{
	CCLog("2222222222222222222now isGoingRoomLayer = %d",isGoingRoomLayer);
	if(isGoingRoomLayer>0){
		isGoingRoomLayer--;
	}else{
		forbidButtonClick();
		if(!this->getChildByTag(123))
		{
			ExitLayer* layer = ExitLayer::create();
			addChild(layer,100,123);
		}
	}
}

void RoomLayer::onRegisterFaild(CCObject* obj)
{
	//注册账号失败重新注册游客账号
	int nGender = 1;
	int nFaceId = 0;
	string szAccount = createAccount();
	string szPassword = createPassword();

	bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	if (!bRet)
	{
		//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeLoginConnectFaild);
		//addChild(promptBox);
		//return;
	}

	//char buf[50];
	//memset(buf, 0, 50);
	//utf::utf_gb_convert("utf-8", "gb2312", buf,50, const_cast<char*>(szAccount.c_str()), szAccount.length());

	///EntityMgr::instance()->getActor()->login()->setUserRegister(szAccount.c_str(),szPassword.c_str(),nFaceId,nGender);
	EntityMgr::instance()->login()->setUserRegister(szAccount.c_str(),szPassword.c_str(),nFaceId,nGender,1);
}

void RoomLayer::showMoveingLabelTips(const char* str)
{
	MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(str,ccp(winSize.width * 0.5,winSize.height * 0.5));
	addChild(layer,100);
}

//void RoomLayer::getUserInfo()
//{
//
//}
//void RoomLayer::checkUserCannelQueueUp(float dt)
//{
//    if(roomTimer->getIsClose())
//    {
//        unschedule(schedule_selector(RoomLayer::checkUserCannelQueueUp));
//        tishi->setVisible(true);
//        CCSprite * sprite1 = (CCSprite*)getChildByTag(MASKD_TAG);
//        CCMenu * menu = (CCMenu*)getChildByTag(MASKDMENU_TAG);
//        menu->setVisible(true);
//        sprite1->setVisible(true);
//        sprite1->resumeSchedulerAndActions();
//        CCSprite * sprite2 = (CCSprite*)getChildByTag(PAIDUI_TAG);
//        sprite2->setVisible(false);
//        roomTimer->setVisible(false);
//        
//        EntityMgr::instance()->getDispatch()->closeGameSocket();
//        ///EntityMgr::instance()->getActor()->roomFrame()->reset();
//		EntityMgr::instance()->roomFrame()->reset();
//	}
//}
//void RoomLayer::changeSoundState(cocos2d::CCObject *obj)
//{
//    if(soundState)
//    {
//        soundState = false;
//    }
//    else
//    {
//        soundState = true;
//    }
//    playButtonSound();
//    CCSprite * soundNormalSprite;
//    CCSprite * soundSelectSprite;
//    if(soundState)
//    {
//        soundNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("bt_shengyk1.png"));
//        soundSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("bt_shengyk2.png"));
//        resumeBGM("roomback.mp3");
//    }
//    else
//    {
//        soundNormalSprite = CCSprite::createWithSpriteFrame(spriteFrame("bt_shengyg1.png"));
//        soundSelectSprite = CCSprite::createWithSpriteFrame(spriteFrame("bt_shengyg2.png"));
//        pauseBGM();
//    }
//    soundMenuSprite->setNormalImage(soundNormalSprite);
//    soundMenuSprite->setSelectedImage(soundSelectSprite);
//    CCUserDefault::sharedUserDefault()->setBoolForKey("ZJD_SOUNDSTATE", soundState);
//}
//
//void RoomLayer::onLoingFinish()
//{
//    CCLOG("-----onLoingFinish------");
//    
//    if (EntityMgr::instance()->getDispatch()->isGameStatuc())
//    {
//        return;
//	}
//
//	stopSound(m_nBGMID);
//	//CCScene* pScene = DZPKLayer::scene();
//	//CCDirector::sharedDirector()->replaceScene(pScene);
//}
//
//void RoomLayer::showTable(float dt)
//{
//    int i1 = rand()%10;
//    int i3 = rand()%10;
//    int i4 = rand()%100;
//	for (int i = 0; i < 10; i ++)
//	{
//        if(i == i1 )
//        {
//            int i2 = rand()%3;
//            if(i2 == 0)
//            {
//                m_pTable[i]->resert(false, true, true,i4+i+1);
//            }
//            else if(i2 == 1)
//            {
//                m_pTable[i]->resert(true, false, true,i4+i+1);
//            }
//            else
//            {
//                m_pTable[i]->resert(true, true, false,i4+i+1);
//            }
//            
//        }
//        else if(i == i3)
//        {
//            int i2 = rand()%3;
//            if(i2 == 0)
//            {
//                m_pTable[i]->resert(false, true, true,i4+i+1);
//            }
//            else if(i2 == 1)
//            {
//                m_pTable[i]->resert(true, false, true,i4+i+1);
//            }
//            else
//            {
//                m_pTable[i]->resert(true, true, false,i4+i+1);
//            }
//        }
//        else
//        {
//            m_pTable[i]->resert(true, true, true,i4+i+1);
//        }
//    }
//}
//
//void RoomLayer::createTable()
//{
//	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//
//	//10个牌桌
//	srand(time(NULL));
//	int ret = rand()%100;
//	for (int i = 0; i < 10; i ++)
//	{
//		CCPoint pos;
//		switch (i) 
//		{
//		case 0:
//			pos = CCPointMake(winSize.width * 0.15, winSize.height * 0.61);
//			break;
//		case 1:
//			pos = CCPointMake(winSize.width * 0.85, winSize.height* 0.61);
//			break;
//		case 2:
//			pos = CCPointMake(winSize.width * 0.15, winSize.height * 0.39);
//			break;
//		case 3:
//			pos = CCPointMake(winSize.width * 0.38, winSize.height * 0.39);
//			break;
//		case 4:
//			pos = CCPointMake(winSize.width * 0.62, winSize.height * 0.39);
//			break;
//		case 5:
//			pos = CCPointMake(winSize.width * 0.85, winSize.height * 0.39);
//			break;
//		case 6:
//			pos = CCPointMake(winSize.width * 0.15, winSize.height * 0.17);
//			break;
//		case 7:
//			pos = CCPointMake(winSize.width * 0.38, winSize.height * 0.17);
//			break;
//		case 8:
//			pos = CCPointMake(winSize.width * 0.62, winSize.height * 0.17);
//			break;
//		case 9:
//			pos = CCPointMake(winSize.width * 0.85, winSize.height * 0.17);
//			break;
//		default:
//			break;
//		}
//
//		m_pTable[i] = RoomTable::RoomTableWith(pos, true, true, true,i+1+ret);
//		//showTable(0.0f);
//		m_pTable[i]->setVisible(false);
//		addChild(m_pTable[i]);
//	}
//
//	schedule(schedule_selector(RoomLayer::showTable),10.0);
//}
//
//void RoomLayer::onMatch(CCObject* obj)
//{
//    MatchError* match = MatchError::MatchErrorWith();
//    addChild(match);
//}
//
//void RoomLayer::showNotice()
//{
//    
//}
//
void RoomLayer::onPesent(CCObject* obj)
{
	tagScoreGifObj* obj1 = (tagScoreGifObj*)obj;

	//显示提示框
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypePasswordFind);
	addChild(promptBox,20);
	promptBox->setPromptText((const char*)obj1->szErrorDescribe);

	////赠送成功，刷新界面
	//if (obj1->lErrCode == 0)
	//{
	//    m_pUserInfo->setValue(g_GlobalUnits.getGolbalUserData()->lScore,g_GlobalUnits.getGolbalUserData()->lGoldEggs);
	//}
}

void RoomLayer::onRefshTotalNum(CCObject* obj)
{
	GroupSprite* m_pHappyNormalSprite = GroupSprite::GroupSpriteWith("dt_happygame.png",CCString::createWithFormat("%d",(int)((g_GlobalUnits.m_nOnlineCount + 5000)*1.8))->getCString(),GorupSpriteTypePhotoAndText0,5);
	GroupSprite* m_pHappySelectSprite = GroupSprite::GroupSpriteWith("dt_happygame.png",CCString::createWithFormat("%d",(int)((g_GlobalUnits.m_nOnlineCount + 5000)*1.8))->getCString(),GorupSpriteTypePhotoAndText0,5);
	/*m_pHappyS->setNormalImage(m_pHappyNormalSprite);
	m_pHappyS->setSelectedImage(m_pHappySelectSprite);*/

	//初级场
	GroupSprite * primaryNormalSprite = GroupSprite::GroupSpriteWith("dt_primarymatch.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.44))->getCString(),GorupSpriteTypePhotoAndText1,1);
	GroupSprite * primarySelectSprite = GroupSprite::GroupSpriteWith("dt_primarymatch.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.44))->getCString(),GorupSpriteTypePhotoAndText1,1);

	//中级场
	GroupSprite * middleNormalSprite = GroupSprite::GroupSpriteWith("dt_middlematch.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.3))->getCString(),GorupSpriteTypePhotoAndText1,2);
	GroupSprite * middleSelectSprite = GroupSprite::GroupSpriteWith("dt_middlematch.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.3))->getCString(),GorupSpriteTypePhotoAndText1,2);

	//高级场
	GroupSprite * seniyNormalSprite = GroupSprite::GroupSpriteWith("dt_seniymatch.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.26))->getCString(),GorupSpriteTypePhotoAndText1,3);
	GroupSprite * seniySelectSprite = GroupSprite::GroupSpriteWith("dt_seniymatch.png",CCString::createWithFormat("%d",(int)(((g_GlobalUnits.m_nOnlineCount + 5000)*1.8)*0.26))->getCString(),GorupSpriteTypePhotoAndText1,3);

	m_pPrimaryS->setNormalImage(primaryNormalSprite);
	m_pPrimaryS->setNormalImage(primarySelectSprite);
	m_pMiddleS->setNormalImage(middleNormalSprite);
	m_pMiddleS->setNormalImage(middleSelectSprite);
	m_pSeniyS->setNormalImage(seniyNormalSprite);
	m_pSeniyS->setNormalImage(seniySelectSprite);
}
//
void RoomLayer::onChange(CCObject* obj)
{
	tagChargeObj* obj1 = (tagChargeObj*)obj;

	//显示提示框
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypePasswordFind);
	addChild(promptBox,20);
	promptBox->setPromptText((const char*)obj1->szErrorDescribe);

	////赠送成功，刷新界面
	//if (obj1->lErrCode == 0)
	//{
	//    m_pUserInfo->setValue(g_GlobalUnits.getGolbalUserData()->lScore,g_GlobalUnits.getGolbalUserData()->lGoldEggs);
	//}
}

void RoomLayer::gameToBankrupt(bool isBankrupt)
{
	if(ConfigMgr::instance()->m_Config.m_isGameBankrupcy)
	{
		//小游戏破产 弹出破产框
		ConfigMgr::instance()->m_Config.m_isGameBankrupcy = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"1","4");
#endif
		return;
	}

	//自己弹出破产框
	if(isBankrupt)
	{
		//显示破产框
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),"1","4");
#endif
	}
}

void RoomLayer::showDailyGetCoins(CCObject* obj)
{
	if(g_GlobalUnits.getGolbalUserData()->nRelieveCount > 0)
	{
		bool ret = EntityMgr::instance()->getDispatch()->connectLoginServer();
		if (!ret)
		{
			PromptBox* box = PromptBox::PromptBoxWith(ccp(427,240),mPromptTypeServerShut);
			this->addChild(box,20);
			return;
		}
		EntityMgr::instance()->getDispatch()->getRelieve(g_GlobalUnits.getGolbalUserData()->dwUserID);
	}
	else
	{
		CCScene* scene = CCScene::create();
		FreeLayer* layer = FreeLayer::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}
}

void RoomLayer::showDailyGetCoinsResult(CCObject* obj)
{
	CCInteger* inter = (CCInteger*)obj;
	PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeLackCoins);
	box->setPromptText(CCString::createWithFormat("%s%d%s%d%s",ConfigMgr::instance()->text("t476"),inter->getValue(),ConfigMgr::instance()->text("t477"),g_GlobalUnits.getGolbalUserData()->nRelieveCount,ConfigMgr::instance()->text("t478"))->getCString());
	addChild(box,50);
}

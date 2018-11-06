#include "ActivityLayer.h"
#include "RoomLayer.h"
#include "ActivitySprite.h"
#include "FreeLayer.h"
#include "globalUnits/GlobalUnits.h"
#include "common/Encrypt.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

using namespace cocos2d;
ActivityLayer::ActivityLayer()
{

}
ActivityLayer::~ActivityLayer()
{
	m_ActivityContextArray->release();
	m_ActivitySpriteArray->release();
}
CCScene* ActivityLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		ActivityLayer *layer = ActivityLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool ActivityLayer::init()
{
	bool bRet = false;
	do 
	{
		winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pPlayerInfoBJLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		CCSprite *pPlayerInfoBJRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		//pPlayerInfoBJRight->setRotationY(180);
		pPlayerInfoBJLeft->setPosition(ccp(winSize.width*0.25,winSize.height*0.5));
		pPlayerInfoBJRight->setPosition(ccp(winSize.width*0.75 - 1,winSize.height*0.5));
		addChild(pPlayerInfoBJLeft,0);
		addChild(pPlayerInfoBJRight,0);


		CCSprite *pPlayerInfoBJLeft1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		CCSprite *pPlayerInfoBJRight1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		//pPlayerInfoBJRight1->setRotationY(180);
		pPlayerInfoBJLeft1->setPosition(ccp(winSize.width*0.25+5,winSize.height*0.0-18 - 195));
		pPlayerInfoBJRight1->setPosition(ccp(winSize.width*0.75-5,winSize.height*0.0-18 - 195));
		pPlayerInfoBJLeft1->setScaleY(1.2f);
		pPlayerInfoBJRight1->setScaleY(1.2f);
		pPlayerInfoBJLeft1->setAnchorPoint(ccp(0.5,0));
		pPlayerInfoBJRight1->setAnchorPoint(ccp(0.5,0));
		addChild(pPlayerInfoBJLeft1,1);
		addChild(pPlayerInfoBJRight1,1);

		//Ãâ·Ñ
		CCSprite *pMianFeiSpriteNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
		CCSprite *pMianFeiSpriteSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
		CCMenuItemSprite* pMianfei = CCMenuItemSprite::create(pMianFeiSpriteNormal,pMianFeiSpriteSelect,this,menu_selector(ActivityLayer::toFreeLayer));
		pMianFeiSpriteSelect->setScale(0.9f);
		pMianFeiSpriteSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu* mianfeiMenu = CCMenu::create(pMianfei,NULL);
		mianfeiMenu->setPosition(CCPointMake(winSize.width*0.054,winSize.height*0.885));
		addChild(mianfeiMenu);


		CCSprite *pPlayerInfoLogo = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_14.png"));
		pPlayerInfoLogo->setPosition(ccp(winSize.width*0.5,winSize.height*0.923));
		addChild(pPlayerInfoLogo,2);

		CCSprite *pPlayerInfoLogoText = CCSprite::createWithSpriteFrame(spriteFrame("dt_activity_1.png"));
		pPlayerInfoLogoText->setPosition(ccp(winSize.width*0.5,winSize.height*0.933));
		addChild(pPlayerInfoLogoText,3);

		m_nSelectActivity = 0;
		m_ActivitySpriteArray = CCArray::create();
		m_ActivitySpriteArray->retain();
		m_ActivityContextArray = CCArray::create();
		m_ActivityContextArray->retain();

		activityTips = CCLabelTTF::create(ConfigMgr::instance()->text(CCString::createWithFormat("t%d",500)->getCString()),"",26);
		activityTips->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.37));
		activityTips->setColor(ccc3(0,0,0));
		addChild(activityTips,3);

		//»î¶¯1
		for (int i = 0; i <5 ; i++)
		{
			ActivitySprite* sprite = ActivitySprite::ActivitySpriteWith(i);
			sprite->setPosition(ccp(sprite->getContentSize().width * 0.6 + i*sprite->getContentSize().width,winSize.height * 0.61));
			if(m_nSelectActivity == i)
			{
				sprite->setSelect(true);
				m_cDistanceSize = sprite->getContentSize().width;
			}
			else
			{
				sprite->setSelect(false);
			}
			m_ActivitySpriteArray->addObject(sprite);
			addChild(sprite,1);
			CCString* str1 ;
			str1 = CCString::createWithFormat(CCString::createWithFormat("t%d",550+i)->getCString());
			CCLabelTTF* label1;
			if(i <= 1)
			{
				label1 = CCLabelTTF::create(ConfigMgr::instance()->text(str1->getCString()),"",22,CCSizeMake(750,0),kCCTextAlignmentLeft);
			}
			else
			{
				label1 = CCLabelTTF::create("","",22,CCSizeMake(750,0),kCCTextAlignmentLeft);
			}
			label1->setPosition(ccp(winSize.width * 0.05,winSize.height * 0.25));
			label1->setAnchorPoint(ccp(0.0,0.5));
			label1->setColor(ccc3(0,0,0));
			addChild(label1,3);

			if(i!= 0)
			{
				label1->setVisible(false);
			}
			if(i == 0)
			{
				CCSprite* enterNormal = CCSprite::createWithSpriteFrame(spriteFrame("activityenter.png"));
				CCSprite* enterSelect = CCSprite::createWithSpriteFrame(spriteFrame("activityenter.png"));
				CCMenuItemSprite* enterItemSprite = CCMenuItemSprite::create(enterNormal,enterSelect,this,menu_selector(ActivityLayer::enterActivity));
				enterSelect->setScale(0.9f);
				enterSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
				m_EnterMenu = CCMenu::create(enterItemSprite,NULL);
				m_EnterMenu->setPosition(ccp(winSize.width * 0.8,winSize.height * 0.1));
				addChild(m_EnterMenu,10);
			}
			m_ActivityContextArray->addObject(label1);
		}



		//activityTips = CCLabelTTF::create(ConfigMgr::instance()->text(CCString::createWithFormat("t%d",199)->getCString()),"",26);
		//activityTips->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.37));
		//activityTips->setColor(ccc3(0,0,0));
		//addChild(activityTips,3);

		CCSprite* leftNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_activity_3.png"));
		leftNormal->setFlipX(true);
		CCSprite* leftSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_activity_3.png"));
		leftSelect->setFlipX(true);
		CCSprite* rightNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_activity_3.png"));
		CCSprite* rightSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_activity_3.png"));
		CCMenuItemSprite* leftItem = CCMenuItemSprite::create(leftNormal,leftSelect,this,menu_selector(ActivityLayer::leftActivity));
		CCMenuItemSprite* rightItem = CCMenuItemSprite::create(rightNormal,rightSelect,this,menu_selector(ActivityLayer::rightActivity));
		CCMenu* arrowMenu = CCMenu::create(leftItem,rightItem,NULL);
		arrowMenu->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.6));
		arrowMenu->alignItemsHorizontallyWithPadding(winSize.width * 0.9);
		addChild(arrowMenu,4);
		
		
			//sprite->setPosition(ccp(sprite1->getContentSize().width * 0.6,winSize.height * 0.61));
		//addChild(sprite,1);

		m_pWhiteBox = CCSprite::createWithSpriteFrame(spriteFrame("dt_activity_4.png"));
		m_pWhiteBox->setPosition(ccp(m_cDistanceSize * 0.6,winSize.height * 0.61));
		addChild(m_pWhiteBox);

		m_pUpArrow = CCSprite::createWithSpriteFrame(spriteFrame("dt_activity_0.png"));
		m_pUpArrow->setPosition(ccp(m_cDistanceSize * 0.6,winSize.height * 0.61 - 80));
		addChild(m_pUpArrow);
		

		CCSprite *pCloseNormalButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pCloseSelectButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pCloseItemSprite = CCMenuItemSprite::create
			(pCloseNormalButton,pCloseSelectButton,this,menu_selector(ActivityLayer::dismiss));
		CCMenu *pCloseButton = CCMenu::create(pCloseItemSprite,NULL);
		pCloseButton->setPosition(ccp(winSize.width*0.943,winSize.height*0.923));
		addChild(pCloseButton,1);
		setKeypadEnabled(true);
		bRet = true;
	} while (0);

	return bRet;

}

void ActivityLayer::enterActivity(CCObject* obj)
{

	playButtonSound();
	int gameID = g_GlobalUnits.getGolbalUserData()->dwUserID;
	std::string userPassword = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");

	char szMD5[33];
	CMD5Encrypt::EncryptData((unsigned char*)userPassword.c_str(), szMD5);
	CCString* str = CCString::createWithFormat("http://HD.91zjd.com/CheckValidUser.aspx?strUserID=%d&strPwd=%s",gameID,szMD5);
	CCLOG("%s",str->getCString());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	toAndridUserProtion(str->getCString());
#endif
}

void ActivityLayer::changeActivity(int type)
{
	playButtonSound();
	m_nSelectActivity = type;
	if(m_nSelectActivity == 0)
	{
		m_EnterMenu->setVisible(true);
	}
	else
	{
		m_EnterMenu->setVisible(false);
	}
	activityTips->setString(ConfigMgr::instance()->text(CCString::createWithFormat("t%d",500+m_nSelectActivity)->getCString()));

	for (unsigned int i = 0;i  < m_ActivitySpriteArray->count();i++)
	{
		ActivitySprite* sprite = (ActivitySprite*)m_ActivitySpriteArray->objectAtIndex(i);
		sprite->setSelect(false);
		if(i == type)
		{
			sprite->setSelect(true);
			m_pWhiteBox->setPosition(sprite->getPosition());
			m_pUpArrow->setPosition(ccp(sprite->getPositionX(),sprite->getPositionY() - 80));
		}
	}
	for (unsigned int i = 0;i<m_ActivityContextArray->count();i++)
	{
		CCLabelTTF* sprite = (CCLabelTTF*)m_ActivityContextArray->objectAtIndex(i);
		sprite->setVisible(false);
		if(i == type)
		{
			sprite->setVisible(true);
		}
	}
}

void ActivityLayer::leftActivity(CCObject* obj)
{
	playButtonSound();
	if(m_nSelectActivity == 0)
	{
		return;
	}
	m_nSelectActivity--;
	if(m_nSelectActivity == 0)
	{
		m_EnterMenu->setVisible(true);
	}
	else
	{
		m_EnterMenu->setVisible(false);
	}
	activityTips->setString(ConfigMgr::instance()->text(CCString::createWithFormat("t%d",500+m_nSelectActivity)->getCString()));
	for (int i = 0; i<5 ; i++)
	{
		ActivitySprite* sprite = (ActivitySprite*)m_ActivitySpriteArray->objectAtIndex(i);
		sprite->setPosition(ccp(sprite->getContentSize().width * 0.6 + i*sprite->getContentSize().width,winSize.height * 0.61));
		if(m_nSelectActivity == i)
		{
			sprite->setSelect(true);
			m_pWhiteBox->setPosition(sprite->getPosition());
			m_pUpArrow->setPosition(ccp(sprite->getPositionX(),sprite->getPositionY() - 80));
		}
		else
		{
			sprite->setSelect(false);
		}
	}
	for (unsigned int i = 0;i<m_ActivityContextArray->count();i++)
	{
		CCLabelTTF* sprite = (CCLabelTTF*)m_ActivityContextArray->objectAtIndex(i);
		sprite->setVisible(false);
		if(i == m_nSelectActivity)
		{
			sprite->setVisible(true);
		}
	}
}

void ActivityLayer::rightActivity(CCObject* obj)
{
	playButtonSound();
	if(m_nSelectActivity == 4)
	{
		return;
	}
	m_nSelectActivity++;
	if(m_nSelectActivity == 0)
	{
		m_EnterMenu->setVisible(true);
	}
	else
	{
		m_EnterMenu->setVisible(false);
	}
	activityTips->setString(ConfigMgr::instance()->text(CCString::createWithFormat("t%d",500+m_nSelectActivity)->getCString()));
	for (int i = 0; i<5 ; i++)
	{
		ActivitySprite* sprite = (ActivitySprite*)m_ActivitySpriteArray->objectAtIndex(i);
		sprite->setPosition(ccp(sprite->getContentSize().width * 0.6 + (i-1)*sprite->getContentSize().width,winSize.height * 0.61));
		if(m_nSelectActivity == i)
		{
			sprite->setSelect(true);
			m_pWhiteBox->setPosition(sprite->getPosition());
			m_pUpArrow->setPosition(ccp(sprite->getPositionX(),sprite->getPositionY() - 80));
		}
		else
		{
			sprite->setSelect(false);
		}
	}
	for (unsigned int i = 0; i<m_ActivityContextArray->count();i++)
	{
		CCLabelTTF* sprite = (CCLabelTTF*)m_ActivityContextArray->objectAtIndex(i);
		sprite->setVisible(false);
		if(i == m_nSelectActivity)
		{
			sprite->setVisible(true);
		}
	}
}

void ActivityLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);


}

void ActivityLayer::keyBackClicked()
{
	dismiss(NULL);
}


void ActivityLayer::toFreeLayer(CCObject* obj)
{
	playButtonSound();
	CCDirector::sharedDirector()->replaceScene(FreeLayer::scene());
}
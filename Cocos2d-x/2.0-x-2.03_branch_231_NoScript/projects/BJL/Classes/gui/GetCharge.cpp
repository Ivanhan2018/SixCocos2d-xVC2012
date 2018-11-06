//
//  GeTCHARge.cpp
//  Game
//
//  Created by 罗敏 on 13-8-6.
//
//

#include "GeTCHARge.h"
#include <limits.h>
#include "entity/EntityMgr.h"
#include "configMgr/ConfigMgr.h"
#include "GroupSprite.h"
#include "PromptBox.h"
#include "RoomLayer.h"
using namespace CocosDenshion;
using namespace cocos2d::extension;

GeTCHARge * GeTCHARge::GeTCHARgeWith(cocos2d::CCPoint pos)
{
    GeTCHARge * charge = new GeTCHARge();
    if(charge && charge->initGeTCHARge(pos))
    {
        charge->autorelease();
        return charge;
    }
    CC_SAFE_DELETE(charge);
    return charge;
}

bool GeTCHARge::initGeTCHARge(cocos2d::CCPoint pos)
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
	layer->ignoreAnchorPointForPosition(false);
	layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
	addChild(layer);

	CCSprite *pBackLeft =  CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_3.png"));
	CCSprite *pBackRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_3.png"));
	pBackLeft->setScaleY(1.1f);
	pBackRight->setScaleY(1.1f);
	//pBackRight->setRotationY(180);
	pBackLeft->setPosition(ccp(winSize.width*0.5 - pBackLeft->getContentSize().width * 0.5,winSize.height*0.5));
	pBackRight->setPosition(ccp(winSize.width*0.5 + pBackRight->getContentSize().width * 0.5 - 1,winSize.height*0.5));
	addChild(pBackLeft,0);
	addChild(pBackRight,0);




    CCSprite * backNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
    CCSprite * backSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
    CCMenuItemSprite * backItemSprite = CCMenuItemSprite::create(backNormal, backSelect, this, menu_selector(GeTCHARge::closeGeTCHARge));
	backSelect->setScale(0.9f);
	backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
    m_pBackMenu = CCMenu::create(backItemSprite,NULL);
	
    m_pBackMenu->setPosition(CCPointMake(winSize.width*0.928,winSize.height*0.868));
    addChild(m_pBackMenu);

	
    
    CCSprite* geTCHARgeNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_getchange10.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* geTCHARgeSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_getchange11.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* geTCHARgeDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_getchange11.png",GorupSpriteTypePhotoAndPhoto);
    
	CCSprite* getcoinsNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_getchange12.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* getcoinsSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_getchange13.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* getcoinsDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_getchange13.png",GorupSpriteTypePhotoAndPhoto);
   
	CCSprite* getQBNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_getchange8.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* getQBSelect =(CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_getchange9.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* getQBdis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_getchange9.png",GorupSpriteTypePhotoAndPhoto);
    
    geTCHARgeItemSprite = CCMenuItemSprite::create(geTCHARgeNormal, geTCHARgeSelect, geTCHARgeDis,this, menu_selector(GeTCHARge::geTCHARge));
    getcoinsItemSprite = CCMenuItemSprite::create(getcoinsNormal, getcoinsSelect, getcoinsDis,this, menu_selector(GeTCHARge::getCoins));
    getQBItemSprite = CCMenuItemSprite::create(getQBNormal, getQBSelect, getQBdis,this, menu_selector(GeTCHARge::getQB));
    m_pGetMenu = CCMenu::create(geTCHARgeItemSprite,getQBItemSprite,getcoinsItemSprite,NULL);
    m_pGetMenu->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.748));
    m_pGetMenu->alignItemsHorizontallyWithPadding(20);
    addChild(m_pGetMenu);


	/**添加内容背景**/
	CCSprite *pContentBGLeft =CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange2.png")); 
	pContentBGLeft->setScaleY(1.1f);
	CCSprite *pContentBGRight =CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange2.png")); 
	pContentBGRight->setScaleY(1.1f);
	//pContentBGRight->setRotationY(180);
	pContentBGLeft->setPosition(ccp(winSize.width*0.5 - pContentBGLeft->getContentSize().width * 0.5,winSize.height*0.425));
	pContentBGRight->setPosition(ccp(winSize.width*0.5 + pContentBGRight->getContentSize().width * 0.5,winSize.height*0.425));
	addChild(pContentBGLeft,0);
	addChild(pContentBGRight,0);

    
    CCSprite* dogetNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_getchange7.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* dogetSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_getchange7.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite* dogetdis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_getchange7.png",GorupSpriteTypePhotoAndPhoto);
    CCMenuItemSprite* dogetItemSprite = CCMenuItemSprite::create(dogetNormal, dogetSelect,dogetdis, this, menu_selector(GeTCHARge::doget));
    m_pDogetMenu = CCMenu::create(dogetItemSprite,NULL);
	dogetSelect->setScale(0.9f);
	dogetSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
    m_pDogetMenu->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.27));
    addChild(m_pDogetMenu);
    m_pDogetMenu->setVisible(false);

    currentSelct = 4;
    
    long lGold = g_GlobalUnits.getGolbalUserData()->lGoldEggs;
    

    long lTemp = 0;
    if (lGold >= 15000)
    {
        m_bEnoughGet = true;
    }else
    {
        m_bEnoughGet = false;
        lTemp = 15000 - lGold;
    }
	/**领话费**/
	const char* str1 = CCString::createWithFormat("%s%s%s",ConfigMgr::instance()->text("t67"),addCommaToNumber(lGold).c_str(),ConfigMgr::instance()->text("t74"))->getCString();
    m_pTips11 = CCLabelTTF::create(str1, "Helvetica-Bold", 24);
    m_pTips11->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.64));
    addChild(m_pTips11);
    m_pTips11->setVisible(false);

	m_pTips14 =CCLabelTTF::create(ConfigMgr::instance()->text("t169"), "Helvetica-Bold",14);
	m_pTips14->setColor(ccc3(215,119,19));
	m_pTips14->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.59));
	addChild(m_pTips14);
	m_pTips14->setVisible(false);

    m_pTips12 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange3.png"));
	m_pTips13 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange4.png"));
    m_pTips12->setAnchorPoint(CCPointMake(1.0, 0.5));
    m_pTips13->setAnchorPoint(CCPointMake(1.0, 0.5));
    m_pTips12->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.52));
    m_pTips13->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.4));
    addChild(m_pTips12);
    addChild(m_pTips13);
    m_pTips12->setVisible(false);
    m_pTips13->setVisible(false);
    
    m_pInputBox1 = CCEditBox::create(CCSize(230, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_login5.png")));
    m_pInputBox2 = CCEditBox::create(CCSize(230, 40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_login5.png")));
    m_pInputBox1->setPosition(ccp(winSize.width * 0.62, winSize.height * 0.52));
    m_pInputBox2->setPosition(ccp(winSize.width * 0.62, winSize.height * 0.4));
    addChild(m_pInputBox1);
    addChild(m_pInputBox2);
    m_pInputBox1->setVisible(false);
    m_pInputBox2->setVisible(false);
    
    //领QB
	const char* str2 = CCString::createWithFormat("%s%s%s",ConfigMgr::instance()->text("t67"),addCommaToNumber(lGold).c_str(),ConfigMgr::instance()->text("t75"))->getCString();
    m_pTips21 = CCLabelTTF::create(str2, "Helvetica-Bold", 24);
    m_pTips21->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.64));
    addChild(m_pTips21);
    m_pTips21->setVisible(false);


	m_pTips24 =CCLabelTTF::create(ConfigMgr::instance()->text("t169"), "Helvetica-Bold",14);
	m_pTips24->setColor(ccc3(215,119,19));
	m_pTips24->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.59));
	addChild(m_pTips24);
	m_pTips24->setVisible(false);
    
	m_pTips22 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange0.png"));
	m_pTips23 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange1.png"));
    m_pTips22->setAnchorPoint(CCPointMake(1.0, 0.5));
    m_pTips23->setAnchorPoint(CCPointMake(1.0, 0.5));
    m_pTips22->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.52));
    m_pTips23->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.4));
    addChild(m_pTips22);
    addChild(m_pTips23);
    m_pTips22->setVisible(false);
    m_pTips23->setVisible(false);
    
    //领金币
//    std::string str311 = "您拥有话费点";
//    str311.insert(str311.find("点"), addCommaToNumber(lGold).c_str());
    const char*  str333 = CCString::createWithFormat
		("%s%s%s%s%s%s",ConfigMgr::instance()->text("t78"),addCommaToNumber(lGold).c_str(),ConfigMgr::instance()->text("t68"),ConfigMgr::instance()->text("t76"),addCommaToNumber(((lGold - 200)>0?(lGold-200):0) * 10).c_str(),ConfigMgr::instance()->text("t77"))->getCString();
	m_pTips31 = CCLabelTTF::create(str333, "Helvetica-Bold", 24);	
	
    m_pTips31->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.54));
    addChild(m_pTips31);
    m_pTips31->setVisible(false);
	m_pTips34 =CCLabelTTF::create(ConfigMgr::instance()->text("t169"), "Helvetica-Bold",14);
	m_pTips34->setColor(ccc3(215,119,19));
	m_pTips34->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.47));
	addChild(m_pTips34);
	m_pTips34->setVisible(false);

	CCLabelTTF* m_ElseLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t480"),"",15);
	m_ElseLabel->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.18));
	m_ElseLabel->setColor(ccc3(215,119,19));
	addChild(m_ElseLabel);
    
    //白赚话费
    setTouchEnabled(true);
	setKeypadEnabled(true);
	showLingHuaFei();
    return true;
}

GeTCHARge::GeTCHARge()
{
   
}

GeTCHARge::~GeTCHARge()
{
    
}

void GeTCHARge::keyBackClicked()
{
	closeGeTCHARge(NULL);
}

void GeTCHARge::showLingHuaFei(){
	playButtonSound();
	geTCHARgeItemSprite->setEnabled(false);
	getcoinsItemSprite->setEnabled(true);
	getQBItemSprite->setEnabled(true);
	currentSelct = 0;


	m_pTips11->setVisible(true);

	m_pTips12->setVisible(true);
	m_pTips13->setVisible(true);

	m_pInputBox1->setVisible(true);
	m_pInputBox2->setVisible(true);
	m_pInputBox1->setPlaceHolder(ConfigMgr::instance()->text("t304"));
	m_pInputBox2->setPlaceHolder(ConfigMgr::instance()->text("t305"));


	m_pTips21->setVisible(false);

	m_pTips22->setVisible(false);
	m_pTips23->setVisible(false);


	m_pTips31->setVisible(false);
	// m_pTips32->setVisible(false);

	m_pDogetMenu->setVisible(true);

	m_pTips14->setVisible(true);
	m_pTips24->setVisible(false);
	m_pTips34->setVisible(false);
}


void GeTCHARge::geTCHARge(cocos2d::CCObject *obj)
{
	playButtonSound();
    playButtonSound();
    geTCHARgeItemSprite->setEnabled(false);
    getcoinsItemSprite->setEnabled(true);
    getQBItemSprite->setEnabled(true);
    currentSelct = 0;
    
    
    m_pTips11->setVisible(true);

    m_pTips12->setVisible(true);
    m_pTips13->setVisible(true);

    m_pInputBox1->setVisible(true);
    m_pInputBox2->setVisible(true);
	m_pInputBox1->setText("");
	m_pInputBox2->setText("");
    m_pInputBox1->setPlaceHolder(ConfigMgr::instance()->text("t304"));
    m_pInputBox2->setPlaceHolder(ConfigMgr::instance()->text("t305"));
    
    
    m_pTips21->setVisible(false);

    m_pTips22->setVisible(false);
    m_pTips23->setVisible(false);

    
    m_pTips31->setVisible(false);
   // m_pTips32->setVisible(false);

    m_pDogetMenu->setVisible(true);

	m_pTips14->setVisible(true);
	m_pTips24->setVisible(false);
	m_pTips34->setVisible(false);
}

void GeTCHARge::getCoins(cocos2d::CCObject *obj)
{
    playButtonSound();
    geTCHARgeItemSprite->setEnabled(true);
    getcoinsItemSprite->setEnabled(false);
    getQBItemSprite->setEnabled(true);
    currentSelct = 1;
    
    
    m_pTips11->setVisible(false);

    m_pTips12->setVisible(false);
    m_pTips13->setVisible(false);
    
    
    
    m_pTips21->setVisible(false);

    m_pTips22->setVisible(false);
    m_pTips23->setVisible(false);

    m_pInputBox1->setVisible(false);
    m_pInputBox2->setVisible(false);
    
    m_pTips31->setVisible(true);
   // m_pTips32->setVisible(true);

    m_pDogetMenu->setVisible(true);

	m_pTips14->setVisible(false);
	m_pTips24->setVisible(false);
	m_pTips34->setVisible(true);
}

void GeTCHARge::getQB(cocos2d::CCObject *obj)
{
    playButtonSound();
    geTCHARgeItemSprite->setEnabled(true);
    getcoinsItemSprite->setEnabled(true);
    getQBItemSprite->setEnabled(false);
    currentSelct = 2;
    
    
    m_pTips11->setVisible(false);

    m_pTips12->setVisible(false);
    m_pTips13->setVisible(false);

    
    m_pTips21->setVisible(true);

    m_pTips22->setVisible(true);
    m_pTips23->setVisible(true);

    m_pInputBox1->setVisible(true);
    m_pInputBox2->setVisible(true);
	m_pInputBox1->setText("");
	m_pInputBox2->setText("");
    m_pInputBox1->setPlaceHolder(ConfigMgr::instance()->text("t302"));
    m_pInputBox2->setPlaceHolder(ConfigMgr::instance()->text("t303"));
    
    m_pTips31->setVisible(false);
   // m_pTips32->setVisible(false);

    m_pDogetMenu->setVisible(true);

	m_pTips14->setVisible(false);
	m_pTips24->setVisible(true);
	m_pTips34->setVisible(false);
}

void GeTCHARge::registerWithTouchDispatcher()
{
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min)(),true);
    CCLayer::registerWithTouchDispatcher();
	 CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1000,false);
}

bool GeTCHARge::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bBackMenu = m_pBackMenu->ccTouchBegan(pTouch, pEvent);
    m_bGetMenu = m_pGetMenu->ccTouchBegan(pTouch, pEvent);
    if(currentSelct == 0 || currentSelct == 2)
    {
        m_bInputBox1 = m_pInputBox1->ccTouchBegan(pTouch, pEvent);
        m_bInputBox2 = m_pInputBox2->ccTouchBegan(pTouch, pEvent);
    }
    m_bDogetMenu = m_pDogetMenu->ccTouchBegan(pTouch, pEvent);
    return true;
}

void GeTCHARge::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_bBackMenu)
    {
        m_pBackMenu->ccTouchMoved(pTouch, pEvent);
    }
    if(m_bGetMenu)
    {
        m_pGetMenu->ccTouchMoved(pTouch, pEvent);
    }
    if(m_bInputBox1)
    {
        m_pInputBox1->ccTouchMoved(pTouch, pEvent);
    }
    if(m_bInputBox2)
    {
        m_pInputBox2->ccTouchMoved(pTouch, pEvent);
    }
    if(m_bDogetMenu)
    {
        m_pDogetMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void GeTCHARge::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_bBackMenu)
    {
        m_pBackMenu->ccTouchEnded(pTouch, pEvent);
    }
    if(m_bGetMenu)
    {
        m_pGetMenu->ccTouchEnded(pTouch, pEvent);
    }
    if(m_bInputBox1)
    {
        m_pInputBox1->ccTouchEnded(pTouch, pEvent);
    }
    if(m_bInputBox2)
    {
        m_pInputBox2->ccTouchEnded(pTouch, pEvent);
    }
    if(m_bDogetMenu)
    {
        m_pDogetMenu->ccTouchEnded(pTouch, pEvent);
    }
}

void GeTCHARge::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_bBackMenu)
    {
        m_pBackMenu->ccTouchCancelled(pTouch, pEvent);
    }
    if(m_bGetMenu)
    {
        m_pGetMenu->ccTouchCancelled(pTouch, pEvent);
    }
    if(m_bInputBox1)
    {
        m_pInputBox1->ccTouchCancelled(pTouch, pEvent);
    }
    if(m_bInputBox2)
    {
        m_pInputBox2->ccTouchCancelled(pTouch, pEvent);
    }
    if(m_bDogetMenu)
    {
        m_pDogetMenu->ccTouchCancelled(pTouch, pEvent);
    }
}

void GeTCHARge::closeGeTCHARge(cocos2d::CCObject *obj)
{
	playButtonSound();
	RoomLayer * pRoomLayer = (RoomLayer * )this->getParent();
    pRoomLayer->permitButtonClick();
    playButtonSound();
    removeFromParentAndCleanup(true);
	
}

void GeTCHARge::doget(CCObject* obj)
{
    playButtonSound();
    //建立连接
    bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (!bRet)
    {
		PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeServerShut);
		addChild(promptBox);
		CCLOG("login connect faild!");
        return;
    }


    if(currentSelct != 1)
	{
		const char* str = m_pInputBox1->getText();
		const char* str1 = m_pInputBox2->getText();
		int resultCmp = strcmp(str, str1);
		if(currentSelct == 0)
		{
			if(strlen(str) != 11 || !isLegal(str))
			{
				PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeErrorPhone);
				addChild(promptBox);
				CCLOG("erroe phone");
				return;
			}

			if(resultCmp != 0)
			{
				PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeTwoInputError);
				addChild(promptBox);
				CCLOG("input error");
				return;
			}
		}
		if(currentSelct == 2)
		{
			if(strlen(str) <= 3 || strlen(str) > 11 || !isLegal(str))
			{
				PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeErrorQQNumber);
				addChild(promptBox);
				CCLOG("error qq number");
				return;
			}
			if(resultCmp != 0)
			{
				PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeTwoInputError);
				addChild(promptBox);
				return;
			}
			}
		if(!m_bEnoughGet)
		{
			PromptBox* box = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeGeTCHARgeFaild);
			addChild(box);
			CCLOG("get charge faild!");
			long lGold = g_GlobalUnits.getGolbalUserData()->lGoldEggs;

			const char* str22 = CCString::createWithFormat("%s %s %s",ConfigMgr::instance()->text("t79"),addCommaToNumber(15000-lGold).c_str(),ConfigMgr::instance()->text("t80"))->getCString();
			const char* str33 = CCString::createWithFormat("%s %s %s",ConfigMgr::instance()->text("t79"),addCommaToNumber(15000-lGold).c_str(),ConfigMgr::instance()->text("t81"))->getCString();
			if(currentSelct == 0)
			{
				box->setPromptText(str22);
			}
			else if(currentSelct == 2)
			{
				box->setPromptText(str33);
			}
			return;
		}
		EntityMgr::instance()->getDispatch()->sendChargePacket(currentSelct,str);
		RoomLayer * pRoomLayer = (RoomLayer * )this->getParent();
		pRoomLayer->permitButtonClick();
		removeFromParentAndCleanup(true);
	}
	else
	{
		EntityMgr::instance()->getDispatch()->sendChargePacket(currentSelct,"000");
		RoomLayer * pRoomLayer = (RoomLayer * )this->getParent();
		pRoomLayer->permitButtonClick();
		removeFromParentAndCleanup(true);
	}
}

bool GeTCHARge::isLegal(string str)
{
    const char* s = str.c_str();
    int i = 0;
    while (i++ < str.length() - 1)
    {
        int a = s[i];
        if (s[i]>255)
        {
            //("中文");
            return false;
        }
        if (s[i] < 0)
        {
            //("中文");
            return false;
        }
        else if (s[i]>='0' && s[i]<='9')
        {
            //("数字");
        }
        else if (s[i]>='A' && s[i]<='Z' || s[i]>='a' && s[i]<='z')
        {
            //Memo1->Lines->Add("字母");
            return false;
        }
        else
        {
            //("其它");
            return  false;
        }
    }
    return  true;
}

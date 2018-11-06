//
//  GeTCHARge.cpp
//  Game
//
//  Created by 罗敏 on 13-8-6.
//
//

#include "ChongCoinsLayer.h"
#include <limits.h>
#include "entity/EntityMgr.h"
#include "configMgr/ConfigMgr.h"
#include "GroupSprite.h"
using namespace CocosDenshion;
using namespace cocos2d::extension;

ChongCoinsLayer * ChongCoinsLayer::ChongCoinsLayerWith(cocos2d::CCPoint pos)
{
    ChongCoinsLayer * charge = new ChongCoinsLayer();
    if(charge && charge->initChongCoinsLayer(pos))
    {
        charge->autorelease();
        return charge;
    }
    CC_SAFE_DELETE(charge);
    return charge;
}

bool ChongCoinsLayer::initChongCoinsLayer(cocos2d::CCPoint pos)
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* layer = CCLayerColor::create( ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
	layer->ignoreAnchorPointForPosition(false);
	layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
	addChild(layer);

	CCSprite *pBackLeft = CCSprite::create("dt_warning_3.png");
	CCSprite *pBackRight = CCSprite::create("dt_warning_3.png");
	//pBackRight->setRotationY(180);
	pBackLeft->setPosition(ccp(winSize.width*0.5 - pBackLeft->getContentSize().width * 0.5,winSize.height*0.5));
	pBackRight->setPosition(ccp(winSize.width*0.5 + pBackRight->getContentSize().width * 0.5,winSize.height*0.5));
	addChild(pBackLeft,0);
	addChild(pBackRight,0);




    CCSprite * backNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
    CCSprite * backSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
    CCMenuItemSprite * backItemSprite = CCMenuItemSprite::create(backNormal, backSelect, this, menu_selector(ChongCoinsLayer::closeChongCoinsLayer));
	backSelect->setScale(0.9f);
	backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
    CCMenu* pBackMenu = CCMenu::create(backItemSprite,NULL);
	
    pBackMenu->setPosition(CCPointMake(winSize.width*0.928,winSize.height*0.848));
    addChild(pBackMenu);

	


    
	CCSprite* zjdCardNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_rechange20.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* zjdCardSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange21.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* zjdCardDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange21.png",GorupSpriteTypePhotoAndPhoto);

	CCSprite* yidongSMSNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_rechange17.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* yidongSMSSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange18.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* yidongSMSDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange18.png",GorupSpriteTypePhotoAndPhoto);

	CCSprite* liantongSMSNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_rechange22.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* liantongSMSSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange23.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* liantongSMSDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange23.png",GorupSpriteTypePhotoAndPhoto);

	CCSprite* dianxingSMSNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_rechange12.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* dianxingSMSSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange13.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* dianxingSMSDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange13.png",GorupSpriteTypePhotoAndPhoto);

	CCSprite* phoneCardNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_rechange15.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* phoneCardSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange16.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* phoneCardDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange16.png",GorupSpriteTypePhotoAndPhoto);

	CCSprite* aliPayNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange5.png","dt_rechange7.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* aliPaySelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange8.png",GorupSpriteTypePhotoAndPhoto);
	CCSprite* aliPayDis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_getchange6.png","dt_rechange8.png",GorupSpriteTypePhotoAndPhoto);
    
	m_pZJDCardItemSprite = CCMenuItemSprite::create(zjdCardNormal, zjdCardSelect, zjdCardDis,this, menu_selector(ChongCoinsLayer::showZJDCard));
	m_pYidongMSMItemSprite = CCMenuItemSprite::create(yidongSMSNormal, yidongSMSSelect, yidongSMSDis,this, menu_selector(ChongCoinsLayer::showYidongSMS));
	m_pLiantongMSMItemSprite = CCMenuItemSprite::create(liantongSMSNormal, liantongSMSSelect, liantongSMSDis,this, menu_selector(ChongCoinsLayer::showLiantongSMS));
	m_pDianxingMSMItemSprite = CCMenuItemSprite::create(dianxingSMSNormal, dianxingSMSSelect, dianxingSMSDis,this, menu_selector(ChongCoinsLayer::showDianxingSMS));
	m_pPhoneCardItemSprite = CCMenuItemSprite::create(phoneCardNormal, phoneCardSelect, phoneCardDis,this, menu_selector(ChongCoinsLayer::showPhoneCard));
	m_pAlipayMSMItemSprite = CCMenuItemSprite::create(aliPayNormal, aliPaySelect, aliPayDis,this, menu_selector(ChongCoinsLayer::showAliPay));
	m_pZJDCardItemSprite->setScale(0.9f);
	m_pYidongMSMItemSprite->setScale(0.9f);
	m_pLiantongMSMItemSprite->setScale(0.9f);
	m_pDianxingMSMItemSprite->setScale(0.9f);
	m_pPhoneCardItemSprite->setScale(0.9f);
	m_pAlipayMSMItemSprite->setScale(0.9f);


	CCMenu* pTipsMenu = CCMenu::create(m_pZJDCardItemSprite,m_pYidongMSMItemSprite,m_pLiantongMSMItemSprite,m_pDianxingMSMItemSprite,m_pPhoneCardItemSprite,m_pAlipayMSMItemSprite,NULL);
	pTipsMenu->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.728));
	pTipsMenu->alignItemsHorizontallyWithPadding(1);
	addChild(pTipsMenu);

//	/**添加内容背景**/
//	CCSprite *pContentBGLeft = CCSprite::create("dt_getchange2.png");
//	CCSprite *pContentBGRight = CCSprite::create("dt_getchange2.png");
//	pContentBGRight->setRotationY(180);
//	pContentBGLeft->setPosition(ccp(winSize.width*0.5 - pContentBGLeft->getContentSize().width * 0.5,winSize.height*0.415));
//	pContentBGRight->setPosition(ccp(winSize.width*0.5 + pContentBGRight->getContentSize().width * 0.5,winSize.height*0.415));
//	addChild(pContentBGLeft,0);
//	addChild(pContentBGRight,0);
//
//    
//    CCSprite* dogetNormal = (CCSprite*)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_getchange7.png",GorupSpriteTypePhotoAndPhoto);
//    CCSprite* dogetSelect = (CCSprite*)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_getchange7.png",GorupSpriteTypePhotoAndPhoto);
//    CCSprite* dogetdis = (CCSprite*)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_getchange7.png",GorupSpriteTypePhotoAndPhoto);
//    CCMenuItemSprite* dogetItemSprite = CCMenuItemSprite::create(dogetNormal, dogetSelect,dogetdis, this, menu_selector(GeTCHARge::doget));
//    m_pDogetMenu = CCMenu::create(dogetItemSprite,NULL);
//    m_pDogetMenu->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.25));
//    addChild(m_pDogetMenu);
//    m_pDogetMenu->setVisible(false);
//
//    currentSelct = 4;
//    
//    long lGold = g_GlobalUnits.getGolbalUserData()->lGoldEggs;
//    
//
//    long lTemp = 0;
//    if (lGold >= 20000)
//    {
//        m_bEnoughGet = true;
//    }else
//    {
//        m_bEnoughGet = false;
//        lTemp = 20000 - lGold;
//    }
//	/**领话费**/
//	const char* str1 = CCString::createWithFormat("%s %s %s",ConfigMgr::instance()->text("t67"),addCommaToNumber(lGold).c_str(),ConfigMgr::instance()->text("t74"))->getCString();
//    m_pTips11 = CCLabelTTF::create(str1, "Helvetica-Bold", 24);
//    m_pTips11->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.62));
//    addChild(m_pTips11);
//    m_pTips11->setVisible(false);
//
//	m_pTips14 =CCLabelTTF::create(ConfigMgr::instance()->text("t169"), "Helvetica-Bold",14);
//	m_pTips14->setColor(ccc3(215,119,19));
//	m_pTips14->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.57));
//	addChild(m_pTips14);
//	m_pTips14->setVisible(false);
//
//    m_pTips12 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange3.png"));
//	m_pTips13 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange4.png"));
//    m_pTips12->setAnchorPoint(CCPointMake(1.0, 0.5));
//    m_pTips13->setAnchorPoint(CCPointMake(1.0, 0.5));
//    m_pTips12->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.50));
//    m_pTips13->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.38));
//    addChild(m_pTips12);
//    addChild(m_pTips13);
//    m_pTips12->setVisible(false);
//    m_pTips13->setVisible(false);
//    
//    m_pInputBox1 = CCEditBox::create(CCSize(260,48), CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_login5.png")));
//    m_pInputBox2 = CCEditBox::create(CCSize(260,48), CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_login5.png")));
//    m_pInputBox1->setPosition(ccp(winSize.width * 0.62, winSize.height * 0.50));
//    m_pInputBox2->setPosition(ccp(winSize.width * 0.62, winSize.height * 0.38));
//    this->addChild(m_pInputBox1);
//    this->addChild(m_pInputBox2);
//    m_pInputBox1->setVisible(false);
//    m_pInputBox2->setVisible(false);
//    
//    //领QB
//	const char* str2 = CCString::createWithFormat("%s %s %s",ConfigMgr::instance()->text("t67"),addCommaToNumber(lGold).c_str(),ConfigMgr::instance()->text("t75"))->getCString();
//    m_pTips21 = CCLabelTTF::create(str2, "Helvetica-Bold", 24);
//    m_pTips21->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.62));
//    addChild(m_pTips21);
//    m_pTips21->setVisible(false);
//
//
//	m_pTips24 =CCLabelTTF::create(ConfigMgr::instance()->text("t169"), "Helvetica-Bold",14);
//	m_pTips24->setColor(ccc3(215,119,19));
//	m_pTips24->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.57));
//	addChild(m_pTips24);
//	m_pTips24->setVisible(false);
//    
//	m_pTips22 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange0.png"));
//	m_pTips23 = CCSprite::createWithSpriteFrame(spriteFrame("dt_getchange1.png"));
//    m_pTips22->setAnchorPoint(CCPointMake(1.0, 0.5));
//    m_pTips23->setAnchorPoint(CCPointMake(1.0, 0.5));
//    m_pTips22->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.50));
//    m_pTips23->setPosition(CCPointMake(winSize.width * 0.45, winSize.height * 0.38));
//    addChild(m_pTips22);
//    addChild(m_pTips23);
//    m_pTips22->setVisible(false);
//    m_pTips23->setVisible(false);
//    
//    //领金币
////    std::string str311 = "您拥有话费点";
////    str311.insert(str311.find("点"), addCommaToNumber(lGold).c_str());
//    const char*  str333 = CCString::createWithFormat
//		("%s %s %s %s %s %s",ConfigMgr::instance()->text("t78"),addCommaToNumber(lGold).c_str(),ConfigMgr::instance()->text("t68"),ConfigMgr::instance()->text("t76"),addCommaToNumber(lGold * 12).c_str(),ConfigMgr::instance()->text("t77"))->getCString();
//	m_pTips31 = CCLabelTTF::create(str333, "Helvetica-Bold", 24);	
//	
//    m_pTips31->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.52));
//    addChild(m_pTips31);
//    m_pTips31->setVisible(false);
//	m_pTips34 =CCLabelTTF::create(ConfigMgr::instance()->text("t169"), "Helvetica-Bold",14);
//	m_pTips34->setColor(ccc3(215,119,19));
//	m_pTips34->setPosition(CCPointMake(winSize.width * 0.5, winSize.height * 0.45));
//	addChild(m_pTips34);
//	m_pTips34->setVisible(false);
//    
//    //白赚话费
//    setTouchEnabled(true);
//
//	showLingHuaFei();
    return true;
}

ChongCoinsLayer::ChongCoinsLayer()
{
   
}

ChongCoinsLayer::~ChongCoinsLayer()
{
    
}

void ChongCoinsLayer::registerWithTouchDispatcher()
{
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min)(),true);
    CCLayer::registerWithTouchDispatcher();
	 CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-100,true);
}

bool ChongCoinsLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void ChongCoinsLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void ChongCoinsLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void ChongCoinsLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void ChongCoinsLayer::closeChongCoinsLayer(cocos2d::CCObject *obj)
{
    removeFromParentAndCleanup(true);
}

void ChongCoinsLayer::showZJDCard(CCObject* obj)
{

}

void ChongCoinsLayer::showYidongSMS(CCObject* obj)
{

}

void ChongCoinsLayer::showLiantongSMS(CCObject* obj)
{

}

void ChongCoinsLayer::showDianxingSMS(CCObject* obj)
{

}

void ChongCoinsLayer::showPhoneCard(CCObject* obj)
{

}

void ChongCoinsLayer::showAliPay(CCObject* obj)
{

}

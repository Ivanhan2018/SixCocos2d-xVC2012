//
//  RegistScene.cpp
//  Game
//
//  Created by 兰 天乐 on 13-6-7.
//
//

#include "RoomOption.h"
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

USING_NS_CC;

RoomOption::RoomOption()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(RoomOption::onCheckVersion), MSG_UI_ANS_VERSIONNEW, NULL);
}

RoomOption::~RoomOption()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_VERSIONNEW);
}

bool RoomOption::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//背景
	CCSprite* spriteBack0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
	CCSprite* spriteBack1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
	spriteBack0->setPosition(ccp(spriteBack0->getContentSize().width * 0.5,winSize.height * 0.5));
	spriteBack1->setPosition(ccp(winSize.width - spriteBack1->getContentSize().width * 0.5-2,winSize.height * 0.5));
	spriteBack1->setFlipX(true);
	this->addChild(spriteBack0);
	this->addChild(spriteBack1);

	//免费
	CCSprite *pMianFeiSpriteNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
	CCSprite *pMianFeiSpriteSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
	CCMenuItemSprite* pMianfei = CCMenuItemSprite::create(pMianFeiSpriteNormal,pMianFeiSpriteSelect,this,menu_selector(RoomOption::toFreeLayer));
	pMianFeiSpriteSelect->setScale(0.9f);
	pMianFeiSpriteSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* mianfeiMenu = CCMenu::create(pMianfei,NULL);
	mianfeiMenu->setPosition(CCPointMake(winSize.width*0.054,winSize.height*0.885));
	addChild(mianfeiMenu,1);

	//返回
	CCSprite* backNormal= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCSprite* backSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCMenuItemSprite* backItemSprite = CCMenuItemSprite::create(backNormal,backSelect,this,menu_selector(RoomOption::back));
	backSelect->setScale(0.9f);
	backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* backMenu= CCMenu::create(backItemSprite,NULL);
	backMenu->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93));
	addChild(backMenu);

	//标题
	CCSprite* spriteTitleBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_14.png"));
	CCSprite* spriteTitle = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_0.png"));
	spriteTitleBack->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.92));
	spriteTitle->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.93));
	this->addChild(spriteTitleBack);
	this->addChild(spriteTitle);

	//底框
	CCSprite* spriteBackBox0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg")); 
	CCSprite* spriteBackBox1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
	spriteBackBox0->setPosition(ccp(winSize.width * 0.5 - spriteBackBox0->getContentSize().width * 0.5,spriteBackBox0->getContentSize().height * 0.57));
	spriteBackBox1->setPosition(ccp(winSize.width * 0.5 + spriteBackBox1->getContentSize().width * 0.5 - 2,spriteBackBox1->getContentSize().height * 0.57));
	spriteBackBox0->setScaleY(1.12f);
	spriteBackBox1->setScaleY(1.12f);
	spriteBackBox1->setFlipX(true);
	this->addChild(spriteBackBox0);
	this->addChild(spriteBackBox1);

	//游客账号栏
	CCSprite* spriteLableBack0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	CCSprite* spriteLableBack1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	spriteLableBack0->setPosition(ccp(winSize.width * 0.5 - spriteLableBack0->getContentSize().width * 0.5,winSize.height * 0.7));
	spriteLableBack1->setPosition(ccp(winSize.width * 0.5 + spriteLableBack1->getContentSize().width * 0.5-1,winSize.height * 0.7));
	spriteLableBack1->setFlipX(true);
	this->addChild(spriteLableBack0);
	this->addChild(spriteLableBack1);
	CCLabelTTF* pPlayerAccountTips;
	if(g_GlobalUnits.getGolbalUserData() && g_GlobalUnits.getGolbalUserData()->cbVisitor != 0)
	{
		pPlayerAccountTips = CCLabelTTF::create(ConfigMgr::instance()->text("t131"),"",22);
	}
	else
	{
		pPlayerAccountTips = CCLabelTTF::create(ConfigMgr::instance()->text("t309"),"",22);
	}
	pPlayerAccountTips->setPosition(ccp(winSize.width * 0.07,winSize.height * 0.7));
	pPlayerAccountTips->setAnchorPoint(ccp(0.0,0.5));
	pPlayerAccountTips->setColor(ccc3(106,57,6));
	this->addChild(pPlayerAccountTips);
	
	string szText0 = EntityMgr::instance()->login()->getAccout();
	CCLabelTTF* pPlayerAccountLabel = CCLabelTTF::create(szText0.c_str(),"",22);
	pPlayerAccountLabel->setColor(ccc3(106,57,6));
	pPlayerAccountLabel->setPosition(ccp(winSize.width * 0.07 + 64,winSize.height * 0.7));
	pPlayerAccountLabel->setAnchorPoint(ccp(0.0,0.5));
	this->addChild(pPlayerAccountLabel);
	//切换账号
	if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 0)
	{
		CCSprite* pChangeAccountNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_8.png"));
		CCSprite* pChangeAccountSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_option_8.png"));
		CCMenuItemSprite* pChangeMenuItemSprite = CCMenuItemSprite::create(pChangeAccountNormal,pChangeAccountSelect,this,menu_selector(RoomOption::changeAccount));
		pChangeAccountSelect->setScale(0.9f);
		pChangeAccountSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu* pChangeMenu= CCMenu::create(pChangeMenuItemSprite,NULL);
		pChangeMenu->setPosition(ccp(winSize.width * 0.85,winSize.height * 0.7));
		addChild(pChangeMenu);
	}
	else
	{
		CCSprite* pChangeAccountNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_overregist0.png"));
		CCSprite* pChangeAccountSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_overregist0.png"));
		CCMenuItemSprite* pChangeMenuItemSprite = CCMenuItemSprite::create(pChangeAccountNormal,pChangeAccountSelect,this,menu_selector(RoomOption::changeAccount));
		pChangeAccountSelect->setScale(0.9f);
		pChangeAccountSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu* pChangeMenu= CCMenu::create(pChangeMenuItemSprite,NULL);
		pChangeMenu->setPosition(ccp(winSize.width * 0.85,winSize.height * 0.7));
		addChild(pChangeMenu);
	}
	
	//声音
	CCLabelTTF* pVoiceTipsLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t132"),"",25);
	pVoiceTipsLabel->setPosition(ccp(winSize.width * 0.07,winSize.height * 0.61));
	pVoiceTipsLabel->setAnchorPoint(ccp(0.0,0.5));
	pVoiceTipsLabel->setColor(ccc3(106,57,6));
	this->addChild(pVoiceTipsLabel);
	//静音模式
	CCSprite* spriteLableBack2 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	CCSprite* spriteLableBack3 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	spriteLableBack2->setPosition(ccp(winSize.width * 0.5 - spriteLableBack2->getContentSize().width * 0.5,winSize.height * 0.52));
	spriteLableBack3->setPosition(ccp(winSize.width * 0.5 + spriteLableBack3->getContentSize().width * 0.5-1,winSize.height * 0.52));
	spriteLableBack3->setFlipX(true);
	this->addChild(spriteLableBack2);
	this->addChild(spriteLableBack3);
	CCLabelTTF* pSilentTipsLabel  = CCLabelTTF::create(ConfigMgr::instance()->text("t133"),"",22);
	pSilentTipsLabel->setPosition(ccp(winSize.width * 0.07,winSize.height * 0.52));
	pSilentTipsLabel->setAnchorPoint(ccp(0.0,0.5));
	pSilentTipsLabel->setColor(ccc3(106,57,6));
	this->addChild(pSilentTipsLabel);
	//静音开关
	//默认关闭
	m_bOpenSlientMode = CCUserDefault::sharedUserDefault()->getBoolForKey("ZJD_SOUNDSTATE");
	CCSprite* silentNormal;
	CCSprite* silentSelect;
	if(m_bOpenSlientMode)
	{
		silentNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_5.png"));
		silentSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_5.png"));
	}
	else
	{
		silentNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_4.png"));
		silentSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_4.png"));
	}
	
	m_pSilentItemSprite = CCMenuItemSprite::create(silentNormal,silentSelect,this,menu_selector(RoomOption::openSilentMode));
	CCMenu* slientMneu = CCMenu::create(m_pSilentItemSprite,NULL);
	slientMneu->setPosition(ccp(winSize.width * 0.85,winSize.height * 0.52));
	this->addChild(slientMneu);
	//音乐
	CCSprite* spriteLableBack4 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	CCSprite* spriteLableBack5 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	spriteLableBack4->setPosition(ccp(winSize.width * 0.5 - spriteLableBack4->getContentSize().width * 0.5,winSize.height * 0.41));
	spriteLableBack5->setPosition(ccp(winSize.width * 0.5 + spriteLableBack5->getContentSize().width * 0.5-1,winSize.height * 0.41));
	spriteLableBack5->setFlipX(true);
	this->addChild(spriteLableBack4);
	this->addChild(spriteLableBack5);
	CCLabelTTF* pMusicTipsLabel  = CCLabelTTF::create(ConfigMgr::instance()->text("t134"),"",22);
	pMusicTipsLabel->setPosition(ccp(winSize.width * 0.07,winSize.height * 0.41));
	pMusicTipsLabel->setAnchorPoint(ccp(0.0,0.5));
	pMusicTipsLabel->setColor(ccc3(106,57,6));
	this->addChild(pMusicTipsLabel);
	m_pMusicControlBlackBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_1.png"));
	CCSprite* m_pMusicControlWhiteBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_2.png"));
	m_pMusicControlSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_7.png"));
	m_pMusicControlBlackBack->setPosition(ccp(winSize.width * 0.55,winSize.height * 0.41));

	m_pMusicControlWhiteTimer = CCProgressTimer::create(m_pMusicControlWhiteBack);
	m_pMusicControlWhiteTimer->setMidpoint(ccp(0.0f,0.0f));
	m_pMusicControlWhiteTimer->setBarChangeRate(ccp(1.0f,0.0f));
	m_pMusicControlWhiteTimer->setType(kCCProgressTimerTypeBar);
	m_pMusicControlWhiteTimer->setPosition(ccp(winSize.width * 0.55,winSize.height * 0.41));
	float musicNum = CCUserDefault::sharedUserDefault()->getFloatForKey("ZJD_SOUNDNUM",1.0);
	m_pMusicControlSprite->setPosition(ccp(m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 + m_pMusicControlBlackBack->getContentSize().width*musicNum,winSize.height * 0.41));
	this->addChild(m_pMusicControlBlackBack);
	this->addChild(m_pMusicControlWhiteTimer);
	this->addChild(m_pMusicControlSprite);
	m_pMusicControlWhiteTimer->setPercentage(musicNum*100);



	//音效
	CCSprite* spriteLableBack6 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	CCSprite* spriteLableBack7 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	spriteLableBack6->setPosition(ccp(winSize.width * 0.5 - spriteLableBack6->getContentSize().width * 0.5,winSize.height * 0.3));
	spriteLableBack7->setPosition(ccp(winSize.width * 0.5 + spriteLableBack7->getContentSize().width * 0.5-1,winSize.height * 0.3));
	spriteLableBack7->setFlipX(true);
	this->addChild(spriteLableBack6);
	this->addChild(spriteLableBack7);
	CCLabelTTF* pSoundTipsLabel  = CCLabelTTF::create(ConfigMgr::instance()->text("t135"),"",22);
	pSoundTipsLabel->setPosition(ccp(winSize.width * 0.07,winSize.height * 0.3));
	pSoundTipsLabel->setAnchorPoint(ccp(0.0,0.5));
	pSoundTipsLabel->setColor(ccc3(106,57,6));
	this->addChild(pSoundTipsLabel);
	m_pSoundControlBlackBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_1.png"));
	CCSprite* m_pSoundControlWhiteBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_2.png"));
	m_pSoundControlSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_7.png"));
	m_pSoundControlBlackBack->setPosition(ccp(winSize.width * 0.55,winSize.height * 0.3));
	m_pSoundControlWhiteTimer = CCProgressTimer::create(m_pSoundControlWhiteBack);
	m_pSoundControlWhiteTimer->setMidpoint(ccp(0.0f,0.0f));
	m_pSoundControlWhiteTimer->setBarChangeRate(ccp(1.0f,0.0f));
	m_pSoundControlWhiteTimer->setType(kCCProgressTimerTypeBar);
	m_pSoundControlWhiteTimer->setPosition(ccp(winSize.width * 0.55,winSize.height * 0.3));
	m_pSoundControlWhiteBack->setPosition(ccp(winSize.width * 0.55,winSize.height * 0.3));

	float effNum = CCUserDefault::sharedUserDefault()->getFloatForKey("SOUNDEFFVOL",0.5f);
	m_pSoundControlSprite->setPosition(ccp(m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 + m_pMusicControlBlackBack->getContentSize().width*effNum,winSize.height * 0.3));

	this->addChild(m_pSoundControlBlackBack);
	this->addChild(m_pSoundControlWhiteTimer);
	this->addChild(m_pSoundControlSprite);
	m_pSoundControlWhiteTimer->setPercentage(effNum*100);

	//其他
	CCLabelTTF* pOtherTipsLabel = CCLabelTTF::create(ConfigMgr::instance()->text("t136"),"",25);
	pOtherTipsLabel->setPosition(ccp(winSize.width * 0.07,winSize.height * 0.2));
	pOtherTipsLabel->setAnchorPoint(ccp(0.0,0.5));
	pOtherTipsLabel->setColor(ccc3(106,57,6));
	this->addChild(pOtherTipsLabel);

	//版本检测
	CCSprite* spriteLableBack8 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	CCSprite* spriteLableBack9 = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_3.png"));
	spriteLableBack8->setPosition(ccp(winSize.width * 0.5 - spriteLableBack8->getContentSize().width * 0.5,winSize.height * 0.09));
	spriteLableBack9->setPosition(ccp(winSize.width * 0.5 + spriteLableBack9->getContentSize().width * 0.5-1,winSize.height * 0.09));
	spriteLableBack9->setFlipX(true);
	this->addChild(spriteLableBack8);
	this->addChild(spriteLableBack9);
	CCLabelTTF* pCheckTipsLabel  = CCLabelTTF::create(ConfigMgr::instance()->text("t137"),"",22);
	pCheckTipsLabel->setPosition(ccp(winSize.width * 0.07,winSize.height * 0.09));
	pCheckTipsLabel->setAnchorPoint(ccp(0.0,0.5));
	pCheckTipsLabel->setColor(ccc3(106,57,6));
	this->addChild(pCheckTipsLabel);
	const char* pVesion = CCString::createWithFormat("%d.%d.%d",ConfigMgr::instance()->m_VersionInfo.m_nHighVersion,ConfigMgr::instance()->m_VersionInfo.m_nMiddleVersion,ConfigMgr::instance()->m_VersionInfo.m_nLowVersion)->getCString();
	CCLabelTTF* pVesionLabel = CCLabelTTF::create(pVesion,"",18);
	pVesionLabel->setPosition(ccp(winSize.width * 0.07 + 108,winSize.height * 0.09));
	pVesionLabel->setAnchorPoint(ccp(0.0,0.5));
	pVesionLabel->setColor(ccc3(106,57,6));
	this->addChild(pVesionLabel);
	CCSprite* pCheckVesionNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_6.png"));
	CCSprite* pCheckVesionSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_option_6.png"));
	CCMenuItemSprite* pCheckVesionItemSprite = CCMenuItemSprite::create(pCheckVesionNormal,pCheckVesionSelect,this,menu_selector(RoomOption::checkVesion));
	pCheckVesionSelect->setScale(0.9f);
	pCheckVesionSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* pCheckMenu= CCMenu::create(pCheckVesionItemSprite,NULL);
	pCheckMenu->setPosition(ccp(winSize.width * 0.85,winSize.height * 0.09));
	addChild(pCheckMenu);

	setKeypadEnabled(true);
	setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne);
    return true;
}

void RoomOption::onEnter()
{
    CCLayer::onEnter();
	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1000,true);
}

void RoomOption::onExit()
{
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
   CCLayer::onExit();
}

bool RoomOption::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	if(m_pMusicControlSprite->boundingBox().containsPoint(touchPoint))
	{
		m_nChangeVoice = 1;
		return true;
	}
	if(m_pSoundControlSprite->boundingBox().containsPoint(touchPoint))
	{
		m_nChangeVoice = 2;
		return true;
	}
	return false;
}

void RoomOption::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	if(m_nChangeVoice == 1)
	{
		if(touchPoint.x >= m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 && touchPoint.x <= m_pMusicControlBlackBack->getPositionX() + m_pMusicControlBlackBack->getContentSize().width * 0.5)
		{
			m_pMusicControlSprite->setPosition(ccp(touchPoint.x,m_pMusicControlSprite->getPositionY()));
			m_pMusicControlWhiteTimer->setPercentage(((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width)*100);
			//此处改变音乐音量大小
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->setFloatForKey("ZJD_SOUNDNUM",(m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	if(m_nChangeVoice == 2)
	{
		if(touchPoint.x >= m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 && touchPoint.x <= m_pMusicControlBlackBack->getPositionX() + m_pMusicControlBlackBack->getContentSize().width * 0.5)
		{
			m_pSoundControlSprite->setPosition(ccp(touchPoint.x,m_pSoundControlSprite->getPositionY()));
			m_pSoundControlWhiteTimer->setPercentage(((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width)*100);
			CCUserDefault::sharedUserDefault()->setFloatForKey("SOUNDEFFVOL",(m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->flush();
		}
		//此处改变音效音量大小
	}
}

void RoomOption::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	if(m_nChangeVoice == 1)
	{
		if(touchPoint.x >= m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 && touchPoint.x <= m_pMusicControlBlackBack->getPositionX() + m_pMusicControlBlackBack->getContentSize().width * 0.5)
		{
			m_pMusicControlSprite->setPosition(ccp(touchPoint.x,m_pMusicControlSprite->getPositionY()));
			m_pMusicControlWhiteTimer->setPercentage(((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width)*100);
			//此处改变音乐音量大小
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->setFloatForKey("ZJD_SOUNDNUM",(m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->flush();
		}
	}
	if(m_nChangeVoice == 2)
	{
		if(touchPoint.x >= m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 && touchPoint.x <= m_pMusicControlBlackBack->getPositionX() + m_pMusicControlBlackBack->getContentSize().width * 0.5)
		{
			m_pSoundControlSprite->setPosition(ccp(touchPoint.x,m_pSoundControlSprite->getPositionY()));
			m_pSoundControlWhiteTimer->setPercentage(((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width)*100);
			CCUserDefault::sharedUserDefault()->setFloatForKey("SOUNDEFFVOL",(m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->flush();
		}
		//此处改变音效音量大小
	}
}

void RoomOption::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	if(m_nChangeVoice == 1)
	{
		if(touchPoint.x >= m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 && touchPoint.x <= m_pMusicControlBlackBack->getPositionX() + m_pMusicControlBlackBack->getContentSize().width * 0.5)
		{
			m_pMusicControlSprite->setPosition(ccp(touchPoint.x,m_pMusicControlSprite->getPositionY()));
			m_pMusicControlWhiteTimer->setPercentage(((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width)*100);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->setFloatForKey("ZJD_SOUNDNUM",(m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->flush();
			//此处改变音乐音量大小
		}
	}
	if(m_nChangeVoice == 2)
	{
		if(touchPoint.x >= m_pMusicControlBlackBack->getPositionX() - m_pMusicControlBlackBack->getContentSize().width * 0.5 && touchPoint.x <= m_pMusicControlBlackBack->getPositionX() + m_pMusicControlBlackBack->getContentSize().width * 0.5)
		{
			m_pSoundControlSprite->setPosition(ccp(touchPoint.x,m_pSoundControlSprite->getPositionY()));
			m_pSoundControlWhiteTimer->setPercentage(((m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width)*100);
			CCUserDefault::sharedUserDefault()->setFloatForKey("SOUNDEFFVOL",(m_pSoundControlBlackBack->getContentSize().width * 0.5 + touchPoint.x - m_pSoundControlBlackBack->getPositionX())/m_pSoundControlBlackBack->getContentSize().width);
			CCUserDefault::sharedUserDefault()->flush();
		}
		//此处改变音效音量大小
	}
}

void RoomOption::back(CCObject* obj)
{
	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void RoomOption::keyBackClicked()
{
	back(NULL);
}

void RoomOption::toFreeLayer(CCObject* obj)
{
	playButtonSound();
	CCDirector::sharedDirector()->replaceScene(FreeLayer::scene());
}

void RoomOption::changeAccount(CCObject* obj)
{
	playButtonSound();
	if(g_GlobalUnits.getGolbalUserData()->cbVisitor == 0)
	{
		CCDirector::sharedDirector()->replaceScene(LoginLayer::scene());
	}
	else
	{
		CCScene* scene = CCScene::create();
		OverRegistLayer* regist = OverRegistLayer::create();
		regist->setRegistLayerFrom(0);
		scene->addChild(regist);
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	
}

void RoomOption::openSilentMode(CCObject* obj)
{
	playButtonSound();
	if(m_bOpenSlientMode)
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("ZJD_SOUNDSTATE",false);
		m_bOpenSlientMode = false;
		playBGM("music/roomback.mp3");
	}
	else
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("ZJD_SOUNDSTATE",true);
		m_bOpenSlientMode = true;
		stopBGM();
	}
	CCSprite* silentNormal;
	CCSprite* silentSelect;
	if(m_bOpenSlientMode)
	{
		silentNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_5.png"));
		silentSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_5.png"));
	}
	else
	{
		silentNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_4.png"));
		silentSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_option_4.png"));
	}
	m_pSilentItemSprite->setNormalImage(silentNormal);
	m_pSilentItemSprite->setSelectedImage(silentSelect);
}

void RoomOption::checkVesion(CCObject* obj)
{
	playButtonSound();
	bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	if(bRet)
	{
		int version = ((ConfigMgr::instance()->m_VersionInfo.m_nHighVersion)<<24) + ((ConfigMgr::instance()->m_VersionInfo.m_nMiddleVersion)<<16) + (ConfigMgr::instance()->m_VersionInfo.m_nLowVersion);
		//给服务端发送版本
		EntityMgr::instance()->getDispatch()->sendGetConfigPacket(version);
	}
	else
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeServerShut);
		addChild(box,100);
	}
}

void RoomOption::onCheckVersion(CCObject* obj)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptVersionNew);
	addChild(box,50);
}
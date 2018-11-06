//
//  PromptBox.cpp
//  Game
//
//  Created by 罗敏 on 13-6-27.
//
//




#include "PromptBox.h"
#include <limits.h>
#include "common/GlobalDef.h"
#include "RoomLayer.h"
#include "configMgr/ConfigMgr.h"
#include "LoginLayer.h"
#include "GroupSprite.h"
#include "ddz/SceneControl.h"
#include "FreeLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

PromptBox* PromptBox::PromptBoxWith(cocos2d::CCPoint pos,mPromptType type)
{
	PromptBox * box = new PromptBox();
	if(box && box->initPromptBox(pos,type))
	{
		box->autorelease();
		return box;
	}
	CC_SAFE_DELETE(box);
	return NULL;
}
PromptBox::PromptBox()
{
	m_bIsLack = false;
}
PromptBox::~PromptBox()
{

}
bool PromptBox::initPromptBox(CCPoint pos , mPromptType type)
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	m_nTypes = type;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* colorLayer = CCLayerColor::create(ccc4(166, 166, 166, 100), winSize.width, winSize.height);
	addChild(colorLayer);

	//CCSprite * back = CCSprite::createWithSpriteFrame(spriteFrame("dt_prompt1.png"));
	CCSprite * back = CCSprite::create("dt_prompt1.png");
	back->setPosition(pos);
	back->setScale(1.2f);
	addChild(back);
	CCSprite* spriteTips = CCSprite::createWithSpriteFrame(spriteFrame("dt_prompt0.png"));
	spriteTips->setPosition(CCPointMake(winSize.width * 0.5 ,back->getContentSize().height * 0.45 + winSize.height * 0.5));
	addChild(spriteTips);


	CCSprite * backNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
	CCSprite * backSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png"));
	CCMenuItemSprite * backItemSprite = CCMenuItemSprite::create(backNormal, backSelect, this, menu_selector(PromptBox::closePromptBox));
	m_pBackMenu = CCMenu::create(backItemSprite,NULL);
	m_pBackMenu->setPosition(CCPointMake(back->getContentSize().width * 0.6 +  winSize.width * 0.5 - backSelect->getContentSize().width * 0.4,back->getContentSize().height * 0.6 + winSize.height * 0.5 - backSelect->getContentSize().height * 0.4));
	backSelect->setScale(0.9f);
	backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	addChild(m_pBackMenu);
	if(m_nTypes == mPromptTypePasswordFind)
	{
		m_pAlartWord = CCLabelTTF::create("111", "HelveticaNeue-Bold", 20, CCSizeMake(360, 150), kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		m_pAlartWord->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.51));
		addChild(m_pAlartWord);
	}
	else
	{
		m_pAlartWord = CCLabelTTF::create(getTheCharWithType(type), "HelveticaNeue-Bold", 20, CCSizeMake(360, 150), kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
		m_pAlartWord->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.51));
		addChild(m_pAlartWord);
	}
	if(m_nTypes == mPromptTypeMakeSureModifyNickName || m_nTypes == mPromptTypeNosever)
	{
		m_pAlartWord->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.51));
		CCSprite *okNormal =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCSprite *okSelect =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCMenuItemSprite * okItemSprite = CCMenuItemSprite::create(okNormal, okSelect, this, menu_selector(PromptBox::okButton));
		m_pOkMenu = CCMenu::create(okItemSprite,NULL);
		//m_pOkMenu->setScale(0.8f);
		m_pOkMenu->setPosition(CCPointMake(winSize.width * 0.5 ,winSize.height * 0.5 - back->getContentSize().height * 0.5 + okSelect->getContentSize().height * 0.5+5));
		okSelect->setScale(0.9f);
		okSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		addChild(m_pOkMenu);
	}
	if(m_nTypes == mPromptStartFaild || m_nTypes == mPromptTypeLackCoins)
	{
		CCSprite *okNormal =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCSprite *okSelect =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCMenuItemSprite * okItemSprite = CCMenuItemSprite::create(okNormal, okSelect, this, menu_selector(PromptBox::okButton));
		okSelect->setScale(0.9f);
		okSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite *cannelNormal = CCSprite::createWithSpriteFrame(spriteFrame("cannelbutton.png"));
		//CCSprite *cannelSelect = CCSprite::createWithSpriteFrame(spriteFrame("cannelbutton.png"));
		//CCMenuItemSprite * cannelItemSprite = CCMenuItemSprite::create(cannelNormal, cannelSelect, this, menu_selector(PromptBox::cannelButton));
		//cannelSelect->setScale(0.9f);
		//cannelSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		m_pOkMenu = CCMenu::create(okItemSprite,/*,cannelItemSprite,*/NULL);
		//m_pOkMenu->setScale(0.8f);
		//m_pOkMenu->alignItemsHorizontallyWithPadding(20);
		m_pOkMenu->setPosition(CCPointMake(winSize.width * 0.5 ,winSize.height * 0.5 - back->getContentSize().height * 0.5 + okSelect->getContentSize().height * 0.5+5));
		addChild(m_pOkMenu);
	}

	if(m_nTypes == mPromptTypeLackCoins)
	{
		m_pAlartWord->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.52));
	}


	setTouchEnabled(true);
	return true;
}

void PromptBox::setPromptText(const char* szDes)
{
	m_pAlartWord->setString(szDes);
}

void PromptBox::okButton(CCObject* obj)
{
	if(m_nTypes == mPromptTypeMakeSureModifyNickName)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_SUREMODYFINICKNAME,NULL);
		this->removeFromParentAndCleanup(true);
	}

	if(m_nTypes == mPromptTypeLackCoins || m_nTypes == mPromptTypeNosever)
	{
		//领取救济金
		this->removeFromParentAndCleanup(true);
	}

	if(m_nTypes == mPromptStartFaild)
	{
		if(m_bIsLack)
		{
			//少钱充值
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if(m_nTypes == mPromptStartFaild)
			{
				showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),CCString::createWithFormat("%d",m_nLevel)->getCString(),CCString::createWithFormat("%d",m_nXXX)->getCString());
			}
			else
			{
				showAndroidRechageLayer(CCString::createWithFormat("%d",g_GlobalUnits.getGolbalUserData()->dwUserID)->getCString(),CCString::createWithFormat("%d",1)->getCString(),CCString::createWithFormat("%d",2)->getCString());
			}
#endif
			this->removeFromParentAndCleanup(true);
		}
		else
		{
			bool ret = EntityMgr::instance()->getDispatch()->connectGameServer();
			if (!ret)
			{
				PromptBox* box = PromptBox::PromptBoxWith(ccp(427,240),mPromptTypeServerShut);
				this->getParent()->addChild(box,20);
				this->removeFromParentAndCleanup(true);
				return;
			}
			this->removeFromParentAndCleanup(true);
		}
	}
}

void PromptBox::cannelButton(CCObject* obj)
{
	if(m_nTypes == mPromptStartFaild)
	{
		this->removeFromParentAndCleanup(true);
	}
}

void PromptBox::setLevelAndX(int nLevel,int nXXX,bool isLack)
{
	m_nLevel = nLevel;
	m_nXXX = nXXX;
	m_bIsLack = isLack;
	if(isLack)
	{
		m_pAlartWord->setString(ConfigMgr::instance()->text("t451"));
	}
	else
	{
		m_pAlartWord->setString(ConfigMgr::instance()->text("t450"));
	}CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_pAlartWord->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.49));
}

void PromptBox::closePromptBox(cocos2d::CCObject *obj)
{
	//if (m_nTypes == mPromptTypeUpdateTips)
	//{
	//    tagUpdateObj tag;
	//    tag.bUpdate = false;
	//    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_VERUPDATE,&tag);
	//    return;
	//}
	//
	if (m_nTypes == mPromptTypeServerShut)
	{
		EntityMgr::instance()->getDispatch()->setLoginState(enLogin_Server);
		CCScene* scene = CCScene::create();
		LoginLayer* layer = LoginLayer::create(false);
		layer->setLogin(false);
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	if(m_nTypes == mPromptTypeLoginFaild)
	{
		LoginLayer* layer = LoginLayer::create();
		layer->setLogin(false);
		CCScene* scene = CCScene::create();
		scene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	this->removeFromParentAndCleanup(true);

	//
	//if(m_nTypes == mPromptTypeLoginConnectFaild)
	//{
	//    CCDirector::sharedDirector()->end();
	//    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//            exit(0);
	//    #endif
	//}
	//else
	//{
	//    playButtonSound();
	//    removeFromParentAndCleanup(true);
	//}
}

void PromptBox::registerWithTouchDispatcher()
{
	CCLayer::registerWithTouchDispatcher();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1000,true);
}
bool PromptBox::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_bBackMenu = m_pBackMenu->ccTouchBegan(pTouch, pEvent);
	if(m_nTypes == mPromptTypeMakeSureModifyNickName || m_nTypes == mPromptStartFaild || m_nTypes == mPromptTypeLackCoins)
	{
		m_bOkMenu = m_pOkMenu->ccTouchBegan(pTouch, pEvent);
	}
	return true;
}

void PromptBox::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(m_bBackMenu)
	{
		m_pBackMenu->ccTouchMoved(pTouch, pEvent);
	}
	if(m_nTypes == mPromptTypeMakeSureModifyNickName || m_nTypes == mPromptStartFaild || m_nTypes == mPromptTypeLackCoins)
	{
		if(m_bOkMenu)
		{
			m_pOkMenu->ccTouchMoved(pTouch, pEvent);
		}
	}
}

void PromptBox::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(m_bBackMenu)
	{
		m_pBackMenu->ccTouchEnded(pTouch, pEvent);
	}
	if(m_nTypes == mPromptTypeMakeSureModifyNickName || m_nTypes == mPromptStartFaild || m_nTypes == mPromptTypeLackCoins)
	{
		if(m_bOkMenu)
		{
			m_pOkMenu->ccTouchEnded(pTouch, pEvent);
		}
	}
}

void PromptBox::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(m_bBackMenu)
	{
		m_pBackMenu->ccTouchCancelled(pTouch, pEvent);
	}
	if(m_nTypes == mPromptTypeMakeSureModifyNickName || m_nTypes == mPromptStartFaild || m_nTypes == mPromptTypeLackCoins)
	{
		if(m_bOkMenu)
		{
			m_pOkMenu->ccTouchCancelled(pTouch, pEvent);
		}
	}
}

const char* PromptBox::getTheCharWithType(mPromptType type)
{
	const char * str = "";
	switch (type)
	{
	case mPromptTypeServerShut:
		str = ConfigMgr::instance()->text("t41");
		break;
	case mPromptTypeLoginFaild:
		str = ConfigMgr::instance()->text("t24");
		break;
	case mPromptTypeErrorQQNumber:
		str = ConfigMgr::instance()->text("t37");
		break;
	case mPromptTypeErrorPhone:
		str = ConfigMgr::instance()->text("t38");
		break;
	case mPromptTypeTwoInputError:
		str = ConfigMgr::instance()->text("t39");
		break;
	case mPromptTypeErrorNickName:
		str = ConfigMgr::instance()->text("t307");
		break;
	case mPromptTypeSeverPasswordFaild:
		str = ConfigMgr::instance()->text("t28");
		break;
	case mPromptTypeLoginLegal:
		str = ConfigMgr::instance()->text("t30");
		break;
	case mPromptTypeMakeSureModifyNickName:
		str = ConfigMgr::instance()->text("t308");
		break;
	case mPromptTypeGeTCHARgeFaild:
		str = ConfigMgr::instance()->text("t310");
		break;
	case mPromptTypeGetError:
		str = ConfigMgr::instance()->text("t454");
		break;
	case mPromptTypeLackCoins:
		str = ConfigMgr::instance()->text("t456");
		break;
	case  mPromptVersionNew:
		str = ConfigMgr::instance()->text("t479");
		break;
	case  mPromptNickNameError:
		str = ConfigMgr::instance()->text("t481");
		break;
	default:
		break;
	}
	return str;
}
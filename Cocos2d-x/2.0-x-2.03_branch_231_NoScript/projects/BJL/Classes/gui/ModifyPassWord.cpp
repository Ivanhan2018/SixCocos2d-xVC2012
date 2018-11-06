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
#include "ModifyPassWord.h"
#include "MovingLabelLayer.h"
#include "PromptBox.h"
#include "FreeLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

CCScene* ModifyPassWord::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ModifyPassWord *layer = ModifyPassWord::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

ModifyPassWord::ModifyPassWord()
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ModifyPassWord::onChangePassWordResult), MSG_UI_ANS_PASSWORDUPDATE, NULL);
}
ModifyPassWord::~ModifyPassWord()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_PASSWORDUPDATE);

}



bool ModifyPassWord::init(bool bLogin)
{
   
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

	//返回
	CCSprite* backNormal= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCSprite* backSelect= CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
	CCMenuItemSprite* backItemSprite = CCMenuItemSprite::create(backNormal,backSelect,this,menu_selector(ModifyPassWord::rBack));
	backSelect->setScale(0.9f);
	backSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* backMenu= CCMenu::create(backItemSprite,NULL);
	backMenu->setPosition(ccp(winSize.width * 0.93,winSize.height * 0.93));
	addChild(backMenu);

	//标题
	CCSprite* spriteTitleBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_14.png"));
	CCSprite* spriteTitle = CCSprite::createWithSpriteFrame(spriteFrame("dt_login6.png"));
	spriteTitleBack->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.92));
	spriteTitle->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.93));
	this->addChild(spriteTitleBack);
	this->addChild(spriteTitle);

	//底框
	CCSprite* spriteBackBox0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg")); 
	CCSprite* spriteBackBox1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
	spriteBackBox0->setPosition(ccp(winSize.width * 0.5 - spriteBackBox0->getContentSize().width * 0.5,spriteBackBox0->getContentSize().height * 0.57));
	spriteBackBox1->setPosition(ccp(winSize.width * 0.5 + spriteBackBox1->getContentSize().width * 0.5-2,spriteBackBox1->getContentSize().height * 0.57));
	spriteBackBox0->setScaleY(1.12f);
	spriteBackBox1->setScaleY(1.12f);
	spriteBackBox1->setFlipX(true);
	this->addChild(spriteBackBox0);
	this->addChild(spriteBackBox1);

	//免费
	CCSprite *pMianFeiSpriteNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
	CCSprite *pMianFeiSpriteSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
	CCMenuItemSprite* pMianfei = CCMenuItemSprite::create(pMianFeiSpriteNormal,pMianFeiSpriteSelect,this,menu_selector(ModifyPassWord::toFreeLayer));
	pMianFeiSpriteSelect->setScale(0.9f);
	pMianFeiSpriteSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
	CCMenu* mianfeiMenu = CCMenu::create(pMianfei,NULL);
	mianfeiMenu->setPosition(CCPointMake(winSize.width*0.054,winSize.height*0.885));
	addChild(mianfeiMenu);
	
	//登陆底框
	CCSprite* loginBackBox = CCSprite::createWithSpriteFrame(spriteFrame("dt_login2.png"));
	loginBackBox->setPosition(ccp(winSize.width * 0.5,winSize.height * 0.5));
	addChild(loginBackBox);
    
	//tips
	CCLabelTTF* tipsLabel0 = CCLabelTTF::create(ConfigMgr::instance()->text("t158"),"",24);
	CCLabelTTF* tipsLabel1 = CCLabelTTF::create(ConfigMgr::instance()->text("t159"),"",24);
	CCLabelTTF* tipsLabel2 = CCLabelTTF::create(ConfigMgr::instance()->text("t160"),"",24);
	tipsLabel0->setPosition(ccp(winSize.width * 0.35,winSize.height * 0.6));
	tipsLabel1->setPosition(ccp(winSize.width * 0.35,winSize.height * 0.5));
	tipsLabel2->setPosition(ccp(winSize.width * 0.35,winSize.height * 0.4));
	tipsLabel0->setColor(ccc3(0,0,0));
	tipsLabel1->setColor(ccc3(0,0,0));
	tipsLabel2->setColor(ccc3(0,0,0));
	addChild(tipsLabel0);
	addChild(tipsLabel1);
	addChild(tipsLabel2);


    //输入框
    orginPasswordInput = CCEditBox::create(CCSize(244,40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_login5.png")));
    modifyPasswordInput = CCEditBox::create(CCSize(244,40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_login5.png")));
	surePasswordInput = CCEditBox::create(CCSize(244,40), CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_login5.png")));
    orginPasswordInput->setPosition(ccp(winSize.width * 0.55, winSize.height * 0.6));
    modifyPasswordInput->setPosition(ccp(winSize.width * 0.55, winSize.height * 0.5));
	surePasswordInput->setPosition(ccp(winSize.width * 0.55, winSize.height * 0.4));
    orginPasswordInput->setPlaceHolder(ConfigMgr::instance()->text("t4"));
    modifyPasswordInput->setPlaceHolder(ConfigMgr::instance()->text("t4"));
	surePasswordInput->setPlaceHolder(ConfigMgr::instance()->text("t4"));
	//orginPasswordInput->setPlaceholderFont("",25);
	//modifyPasswordInput->setPlaceholderFont("",25);
	//surePasswordInput->setPlaceholderFont("",25);
    addChild(orginPasswordInput);
    addChild(modifyPasswordInput);
	addChild(surePasswordInput);
	if(g_GlobalUnits.getGolbalUserData()->cbVisitor != 0)
	{
		std::string userPassword = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_PASSWORD");
		orginPasswordInput->setText(userPassword.c_str());
	}

    
    //登陆//按钮
    CCSprite * modifyNormalSprite = (CCSprite*)GroupSprite::GroupSpriteWith("dt_login13.png","dt_login3.png",GorupSpriteTypePhotoAndPhoto);
    CCSprite * modifySelectSprite = (CCSprite*)GroupSprite::GroupSpriteWith("dt_login13.png","dt_login3.png",GorupSpriteTypePhotoAndPhoto);
    CCMenuItemSprite * modify = CCMenuItemSprite::create(modifyNormalSprite, modifySelectSprite, this, menu_selector(ModifyPassWord::clickButton));
    CCMenu* m_pmodifyMenu = CCMenu::create(modify,NULL);
	modifySelectSprite->setScale(0.9f);
	modifySelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
    m_pmodifyMenu->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.21));
    addChild(m_pmodifyMenu);
    
	setKeypadEnabled(true);

    return true;
}

void ModifyPassWord::clickButton(CCObject* obj)
{
	playButtonSound();
	const char* szNewPassword = modifyPasswordInput->getText();
	const char* szSurePassword = surePasswordInput->getText();
	const char* szOldPassword = orginPasswordInput->getText();
	if (strcmp(szNewPassword,szSurePassword))
	{
		//两次密码不一样
		PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(427, 240),mPromptTypeSeverPasswordFaild);
		addChild(promptBox);
		return;
	}

	if (!isLegal(szNewPassword))
	{
		//密码含有非法字符
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t457"),ccp(427,240));
		addChild(layer,20);
		return;
	}

	if(strlen(szNewPassword) > 12 || strlen(szNewPassword) < 6)
	{
		//密码长度不够
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t457"),ccp(427,240));
		addChild(layer,20);
		return;
	}

	bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	if(bRet)
	{
		EntityMgr::instance()->getDispatch()->modifyPassWord(szOldPassword,szNewPassword);
	}
}

void ModifyPassWord::rBack(CCObject* obj)
{
	playButtonSound();
	CCDirector::sharedDirector()->replaceScene(LoginLayer::scene());
}

void ModifyPassWord::keyBackClicked()
{
	rBack(NULL);
}

void ModifyPassWord::toFreeLayer(CCObject *obj){
	playButtonSound();
	CCDirector::sharedDirector()->replaceScene(FreeLayer::scene());
}

void ModifyPassWord::onChangePassWordResult(CCObject* obj)
{
	CCInteger* pNickNameResult = (CCInteger*)obj;
	int i = pNickNameResult->getValue();
	if(i == 0)
	{
		CCLOG("成功修改密码");
		std::string szNewPassword = modifyPasswordInput->getText();
		cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("NEWZJD_PASSWORD", szNewPassword);
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t167"),ccp(427,240));
		addChild(layer);
		CCScene *pScene = CCScene::create();
		RoomLayer *pRoomLayer = RoomLayer::create();
		pRoomLayer->automaticLogin(false);
		pRoomLayer->closeLoginAward();
		pScene->addChild(pRoomLayer);
		CCTransitionFade *tScene = CCTransitionFade::create(2.0f, pScene, ccWHITE);
		CCDirector::sharedDirector()->replaceScene(tScene); 
		//成功
	}
	else
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t168"),ccp(427,240));
		addChild(layer);
		//失败
	}
}

bool ModifyPassWord::isLegal(string str)
{
	const char* s = str.c_str();
	int i = 0;
	while (i++ < str.length() - 1)
	{
		int a = s[i];
		if (s[i]>255)
		{
			//("中文");
		}
		if (s[i] < 0)
		{
			//("中文");
		}
		else if (s[i]>='0' && s[i]<='9')
		{
			//("数字");
		}
		else if (s[i]>='A' && s[i]<='Z' || s[i]>='a' && s[i]<='z')
		{
			//Memo1->Lines->Add("字母");
		}
		else
		{
			//("其它");
			return  false;
		}
	}
	return  true;
}

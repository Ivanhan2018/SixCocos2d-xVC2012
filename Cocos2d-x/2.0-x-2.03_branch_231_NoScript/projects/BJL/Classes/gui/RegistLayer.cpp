#include "RegistLayer.h"
#include "RoomLayer.h"
#include "GroupSprite.h"
#include "MovingLabelLayer.h"
#include "LoginLayer.h"
#include "PromptBox.h"
#include "ans/utf-8.h"
#include "RoomLayer.h"
#include "AgreementLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

using namespace cocos2d;
RegistLayer::RegistLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(RegistLayer::onRegisterFaild), MSG_UI_ANS_REGNFAIL, NULL);

	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(RegistLayer::onRegistSucc), MSG_UI_ANS_REGSUCC, NULL);
}
RegistLayer::~RegistLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_REGNFAIL);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_REGSUCC);
}


bool RegistLayer::init()
{
	bool bRet = false;
	do 
	{
		nGenter = 1;
		nfaceID = 0;
		ccColor3B whiteColor = ccc3(255,255,255);
		ccColor3B blackColor = ccc3(0,0,0);
		winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pRegistBJLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		CCSprite *pRegistBJRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		//pRegistBJRight->setRotationY(180);
		pRegistBJLeft->setPosition(ccp(winSize.width*0.25,winSize.height*0.5));
		pRegistBJRight->setPosition(ccp(winSize.width*0.75-1,winSize.height*0.5));
		//addChild(pRegistBJLeft,0);
		//addChild(pRegistBJRight,0);

		CCSprite *pPlayerInfoBJLeft1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		CCSprite *pPlayerInfoBJRight1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		//pPlayerInfoBJRight1->setRotationY(180);
		pPlayerInfoBJLeft1->setPosition(ccp(winSize.width*0.25+5,winSize.height*0.0-18));
		pPlayerInfoBJRight1->setPosition(ccp(winSize.width*0.75-7,winSize.height*0.0-18));
		pPlayerInfoBJLeft1->setScaleY(1.2f);
		pPlayerInfoBJRight1->setScaleY(1.2f);
		pPlayerInfoBJLeft1->setAnchorPoint(ccp(0.5,0));
		pPlayerInfoBJRight1->setAnchorPoint(ccp(0.5,0));
		//addChild(pPlayerInfoBJLeft1,1);
		//addChild(pPlayerInfoBJRight1,1);


		CCScale9Sprite *pDituLeft1 = CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_5.png"));
		pDituLeft1->setContentSize(CCSizeMake(198.0f,149.0f));
		pDituLeft1->setPosition(ccp(340.0f,284.0f));
		//addChild(pDituLeft1,1);
		CCScale9Sprite *pDituRight1 = CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_5.png"));
		//pDituRight1->setRotationY(180);
		pDituRight1->setContentSize(CCSizeMake(198.0f,149.0f));
		pDituRight1->setPosition(ccp(340.0f+197.0f,284.0f));
		//addChild(pDituRight1,1);


		CCSprite *pRegistLogo = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_13.png"));
		pRegistLogo->setPosition(ccp(winSize.width*0.5,winSize.height*0.923));
		//addChild(pRegistLogo,1);

		
	CCSprite *bk = CCSprite::create("background/Bk_LoadView.png");
	bk->setPosition(CCPoint(FRAME_CENTER_X, FRAME_CENTER_Y));
	this->addChild(bk,0);

	CCSprite *titleSprite = CCSprite::create("dt_register_13.png");
	titleSprite->setPosition(CCPoint(FRAME_CENTER_X, 430));
	this->addChild(titleSprite,0);

	CCSprite *downSprite = CCSprite::create("dt_A1.png");
	downSprite->setPosition(CCPoint(FRAME_CENTER_X, downSprite->getContentSize().height/2));
	this->addChild(downSprite,0);

		//CCSprite *pCloseNormalButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		//CCSprite *pCloseSelectButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
			CCSprite *pCloseNormalButton = CCSprite::create("dt_guanbibig.png");
		CCSprite *pCloseSelectButton = CCSprite::create("dt_guanbibig.png");
		CCMenuItemSprite *pCloseItemSprite = CCMenuItemSprite::create
			(pCloseNormalButton,pCloseSelectButton,this,menu_selector(RegistLayer::dismiss));
		pCloseSelectButton->setScale(0.9f);
		pCloseSelectButton->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseButton = CCMenu::create(pCloseItemSprite,NULL);
		pCloseButton->setPosition(ccp(winSize.width*0.943,winSize.height*0.923));
		addChild(pCloseButton,1);

		CCSprite *pRegistPhotoTopBJNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_6.png"));
		CCSprite *pRegistPhotoTopBJSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_6.png"));
		CCMenuItemSprite* topItemSprite = CCMenuItemSprite::create(pRegistPhotoTopBJNormal,pRegistPhotoTopBJSelect,this,menu_selector(RegistLayer::selectWoman));
		CCMenu* menu0 = CCMenu::create(topItemSprite,NULL);
		menu0->setPosition(ccp(winSize.width*0.165,winSize.height*0.715));
		addChild(menu0,1);
		CCSprite *pRegistPhotoTopPlayer = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_8.png"));
		pRegistPhotoTopPlayer->setPosition(ccp(winSize.width*0.165,winSize.height*0.712));
		addChild(pRegistPhotoTopPlayer,2);
		CCSprite *pRegistPhotoTopSex = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_9.png"));
		pRegistPhotoTopSex->setPosition(ccp(winSize.width*0.197,winSize.height*0.658));
		addChild(pRegistPhotoTopSex,3);
		CCSprite *pRegistPhotoBottomBJNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_6.png"));
		CCSprite *pRegistPhotoBottomBJSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_6.png"));
		CCMenuItemSprite* buttomItemSprite = CCMenuItemSprite::create(pRegistPhotoBottomBJNormal,pRegistPhotoBottomBJSelect,this,menu_selector(RegistLayer::selectMan));
		CCMenu* menu1 = CCMenu::create(buttomItemSprite,NULL);
		menu1->setPosition(ccp(winSize.width*0.165,winSize.height*0.506));
		addChild(menu1,1);
		CCSprite *pRegistPhotoBottomPlayer = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_10.png"));
		pRegistPhotoBottomPlayer->setPosition(ccp(winSize.width*0.165,winSize.height*0.506));
		addChild(pRegistPhotoBottomPlayer,2);
		CCSprite *pRegistPhotoBottomSex = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_11.png"));
		pRegistPhotoBottomSex->setPosition(ccp(winSize.width*0.197,winSize.height*0.448));
		addChild(pRegistPhotoBottomSex,3);

		spriteSlectSex = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_0.png"));
		if(nGenter == 0)
		{
			spriteSlectSex->setPosition(ccp(winSize.width*0.195,winSize.height*0.615));
		}
		else
		{
			spriteSlectSex->setPosition(ccp(winSize.width*0.195,winSize.height*0.406));
		}
		addChild(spriteSlectSex,5);

		const char * pTextUserName = ConfigMgr::instance()->text("t94");
		CCLabelTTF* pTTFUserName = CCLabelTTF::create(pTextUserName, "HelveticaNeue-Bold", 22);
		pTTFUserName->setColor(whiteColor);
		pTTFUserName->setPosition(CCPointMake(winSize.width*0.360+25, winSize.height * 0.702)); 
		addChild(pTTFUserName,1);

		m_pUserNameKuang= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
		m_pUserNameKuang->setPosition(CCPointMake(winSize.width*0.600, winSize.height * 0.702));
		m_pUserNameKuang->setPlaceHolder(ConfigMgr::instance()->text("t163"));
		m_pUserNameKuang->setFontColor(blackColor);
		addChild(m_pUserNameKuang,1);

		const char * pTextUserPassword = ConfigMgr::instance()->text("t96");

		CCLabelTTF* pTTFUserPassword = CCLabelTTF::create(pTextUserPassword, "HelveticaNeue-Bold", 22);
		pTTFUserPassword->setColor(whiteColor);
		pTTFUserPassword->setPosition(CCPointMake(winSize.width*0.360+25, winSize.height * 0.598)); 
		addChild(pTTFUserPassword,1);

		m_pPassWordKuang= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
		m_pPassWordKuang->setPosition(CCPointMake(winSize.width*0.600, winSize.height * 0.598));
		m_pPassWordKuang->setPlaceHolder(ConfigMgr::instance()->text("t97"));
		m_pPassWordKuang->setFontColor(blackColor);
		m_pPassWordKuang->setInputFlag(kEditBoxInputFlagPassword);
		addChild(m_pPassWordKuang,1);

		const char * pTextUserPasswordOK = ConfigMgr::instance()->text("t98");

		CCLabelTTF* pTTFUserPasswordOK = CCLabelTTF::create(pTextUserPasswordOK, "HelveticaNeue-Bold", 22);
		pTTFUserPasswordOK->setColor(whiteColor);
		pTTFUserPasswordOK->setPosition(CCPointMake(winSize.width*0.360+25, winSize.height * 0.492)); 
		addChild(pTTFUserPasswordOK,1);

		m_pPassWordKuangOK= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("Sprite_ShopBuyInputBk.png")));
		m_pPassWordKuangOK->setPosition(CCPointMake(winSize.width*0.600, winSize.height * 0.492));
		m_pPassWordKuangOK->setPlaceHolder(ConfigMgr::instance()->text("t99"));
		m_pPassWordKuangOK->setFontColor(blackColor);
		m_pPassWordKuangOK->setInputFlag(kEditBoxInputFlagPassword);
		addChild(m_pPassWordKuangOK,1);

		const char * pPlayerXieYi = ConfigMgr::instance()->text("t100");
		CCMenuItemFont *pMenuXieYi = CCMenuItemFont::create(pPlayerXieYi,this,menu_selector(RegistLayer::showPlayerXieYi));
		pMenuXieYi->setFontSizeObj(18);
		pMenuXieYi->setColor(ccc3(248,185,16));
		CCMenu *pMenuButton = CCMenu::create(pMenuXieYi,NULL);
		pMenuButton->setPosition(CCPointMake(winSize.width*0.42, winSize.height * 0.361));
		addChild(pMenuButton,1);

		CCSprite *pPlayerXieYiLine = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_15.png"));
		pPlayerXieYiLine->setScaleX(0.90f);
		pPlayerXieYiLine->setPosition(CCPointMake(winSize.width*0.31, winSize.height * 0.361));
		addChild(pPlayerXieYiLine);

		/*CCSprite *pAgreePlayerXieYiButtonBJ = CCSprite::create("dt_warning_8.png");
		pAgreePlayerXieYiButtonBJ->setScaleX(1.6f);
		pAgreePlayerXieYiButtonBJ->setPosition(CCPointMake(winSize.width*0.506, winSize.height * 0.391));
		addChild(pAgreePlayerXieYiButtonBJ,1);
		const char * pAgreePlayerXieYi = ConfigMgr::instance()->text("t101");
		CCMenuItemFont *pMenuAgreeXieYi = CCMenuItemFont::create(pAgreePlayerXieYi,this,menu_selector(RegistLayer::showAgreePlayerXieYi));*/
		GroupSprite *pNormalSprite = GroupSprite::GroupSpriteWith
			("dt_warning_8.png",ConfigMgr::instance()->text("t101"),GorupSpriteTypePhotoAndWord);
		pNormalSprite->setTextSize(16);
		pNormalSprite->setTextColor(255,255,255);
		GroupSprite *pSelectSprite = GroupSprite::GroupSpriteWith
			("dt_warning_8.png",ConfigMgr::instance()->text("t101"),GorupSpriteTypePhotoAndWord);
		pSelectSprite->setTextSize(15);
		pSelectSprite->setTextColor(114,66,16);
		CCMenuItemSprite *pMenuAgreeXieYi = CCMenuItemSprite::create((CCSprite *)pNormalSprite,(CCSprite *)pSelectSprite,this,menu_selector(RegistLayer::showAgreePlayerXieYi));
		pSelectSprite->setScale(0.9f);
		pSelectSprite->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		/*pMenuAgreeXieYi->setFontSizeObj(22);
		pMenuAgreeXieYi->setColor(ccc3(114,66,16));*/
		CCMenu *pMenuAgreeButton = CCMenu::create(pMenuAgreeXieYi,NULL);
		pMenuAgreeButton->setPosition(CCPointMake(winSize.width*0.586, winSize.height * 0.361));
		addChild(pMenuAgreeButton,2);

		const char * pBangDingTXZ = ConfigMgr::instance()->text("t102");
		CCLabelTTF *pTTFBangDingTXZ=CCLabelTTF::create(pBangDingTXZ ,"HelveticaNeue-Bold",18);
		pTTFBangDingTXZ->setColor(whiteColor);
		pTTFBangDingTXZ->setPosition(CCPointMake(winSize.width*0.159+30, winSize.height * 0.317));
		addChild(pTTFBangDingTXZ,1);
		/*CCSprite *pBangDingTXZLine = CCSprite::create("dt_register_15.png");
		pBangDingTXZLine->setScaleX(5.85f);
		pBangDingTXZLine->setPosition(CCPointMake(winSize.width*0.50, winSize.height * 0.303));
		addChild(pBangDingTXZLine);*/

		/*	CCSprite *pDiKuang0 = CCSprite::create("dt_register_16.png");	
		pDiKuang0->setPosition(CCPointMake(winSize.width*0.254, winSize.height * 0.225)) ;
		addChild(pDiKuang0,1);*/


		CCScale9Sprite *pDituLeft2 = CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_5.png"));
		pDituLeft2->setContentSize(CCSizeMake(389.0f,125.0f));
		pDituLeft2->setPosition(ccp(427.0f-194.5f,72.0f));
		//addChild(pDituLeft2,2);
		CCScale9Sprite *pDituRight2 = CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_5.png"));
		//pDituRight2->setRotationY(180);
		pDituRight2->setContentSize(CCSizeMake(389.0f,125.0f));
		pDituRight2->setPosition(ccp(427.0f+193.5f,72.0f));
		//addChild(pDituRight2,1);


		CCSprite *pLog0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_5.png"));
		pLog0->setPosition(CCPointMake(winSize.width*0.25, winSize.height * 0.219));  
		//addChild(pLog0,2);



		/*CCSprite *pDiKuang1 = CCSprite::create("dt_register_16.png");	
		pDiKuang1->setPosition(CCPointMake(winSize.width*0.738, winSize.height * 0.225)) ; 
		addChild(pDiKuang1,1);*/
		CCSprite *pLog1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_4.png"));
		pLog1->setPosition(CCPointMake(winSize.width*0.75, winSize.height * 0.219));  
		//addChild(pLog1,2);




		/*CCSprite *pDiKuang2 = CCSprite::create("dt_register_16.png");	
		pDiKuang2->setPosition(CCPointMake(winSize.width*0.254, winSize.height * 0.079)) ; 
		addChild(pDiKuang2,1);*/
		CCSprite *pLog2 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_3.png"));
		pLog2->setPosition(CCPointMake(winSize.width*0.25, winSize.height * 0.085));  
		//addChild(pLog2,2);

		/*CCSprite *pDiKuang3 = CCSprite::create("dt_register_16.png");	
		pDiKuang3->setPosition(CCPointMake(winSize.width*0.738, winSize.height * 0.079)) ;  
		addChild(pDiKuang3,1);*/
		CCSprite *pLog3 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_222.png"));
		pLog3->setPosition(CCPointMake(winSize.width*0.775, winSize.height * 0.085));  
		//addChild(pLog3,2);

		/*CCLabelTTF *pTTF00=CCLabelTTF::create(ConfigMgr::instance()->text("t103") ,"HelveticaNeue-Bold",18);
		CCLabelTTF *pTTF01=CCLabelTTF::create(ConfigMgr::instance()->text("t104") ,"HelveticaNeue-Bold",12);
		CCLabelTTF *pTTF10=CCLabelTTF::create(ConfigMgr::instance()->text("t105") ,"HelveticaNeue-Bold",18);
		CCLabelTTF *pTTF11=CCLabelTTF::create(ConfigMgr::instance()->text("t106") ,"HelveticaNeue-Bold",12);
		CCLabelTTF *pTTF20=CCLabelTTF::create(ConfigMgr::instance()->text("t107") ,"HelveticaNeue-Bold",18);
		CCLabelTTF *pTTF21=CCLabelTTF::create(ConfigMgr::instance()->text("t108"), "HelveticaNeue-Bold",12);
		CCLabelTTF *pTTF30=CCLabelTTF::create(ConfigMgr::instance()->text("t109") ,"HelveticaNeue-Bold",18);
		CCLabelTTF *pTTF31=CCLabelTTF::create(ConfigMgr::instance()->text("t110") ,"HelveticaNeue-Bold",12);
		pTTF00->setAnchorPoint(ccp(0,0));
		pTTF00->setPosition(ccp(179.0f,106.0f));
		pTTF01->setAnchorPoint(ccp(0,0));
		pTTF01->setPosition(ccp(179.0f,85.0f));
		pTTF10->setAnchorPoint(ccp(0,0));
		pTTF10->setPosition(ccp(557.0f,106.0f));
		pTTF11->setAnchorPoint(ccp(0,0));
		pTTF11->setPosition(ccp(557.0f,85.0f));
		pTTF20->setAnchorPoint(ccp(0,0));
		pTTF20->setPosition(ccp(179.0f,40.0f));
		pTTF21->setAnchorPoint(ccp(0,0));
		pTTF21->setPosition(ccp(179.0f,19.0f));
		pTTF30->setAnchorPoint(ccp(0,0));
		pTTF30->setPosition(ccp(557.0f,40.0f));
		pTTF31->setAnchorPoint(ccp(0,0));
		pTTF31->setPosition(ccp(557.0f,19.0f));
		addChild(pTTF00,2);
		addChild(pTTF01,2);
		addChild(pTTF10,2);
		addChild(pTTF11,2);
		addChild(pTTF20,2);
		addChild(pTTF21,2);
		addChild(pTTF30,2);
		addChild(pTTF31,2);*/


		setKeypadEnabled(true);
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;
	} while (0);

	return bRet;

}

void RegistLayer::setRegistLayerFrom(int num)
{
	m_nRegistFrom = num;
}

void RegistLayer::selectMan(CCObject* obj)
{
	nGenter = 1;
	if(nGenter == 1)
	{
		spriteSlectSex->setPosition(ccp(winSize.width*0.195,winSize.height*0.406));
	}
	else
	{
		spriteSlectSex->setPosition(ccp(winSize.width*0.195,winSize.height*0.615));
	}
}

void RegistLayer::selectWoman(CCObject* obj)
{
	nGenter = 2;
	if(nGenter == 1)
	{
		spriteSlectSex->setPosition(ccp(winSize.width*0.195,winSize.height*0.406));
	}
	else
	{
		spriteSlectSex->setPosition(ccp(winSize.width*0.195,winSize.height*0.615));
	}
}

void RegistLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	if(m_nRegistFrom == 0)
	{
		CCScene* scene = CCScene::create();
		RoomLayer * pRoomLayer = RoomLayer::create();
		pRoomLayer->closeLoginAward();
		pRoomLayer->automaticLogin(false);
		scene->addChild(pRoomLayer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(LoginLayer::scene());
	}
}

void RegistLayer::keyBackClicked()
{
	if(ConfigMgr::instance()->m_Config.m_bToAndroid)
	{
		ConfigMgr::instance()->m_Config.m_bToAndroid = false;
		CCLog("222222222222222222now m_config.m_btoandroid is true  to false");
		return;
	}
	else
	{
		dismiss(NULL);
	}
}


void RegistLayer::showPlayerXieYi(cocos2d::CCObject *obj){
	playButtonSound();
	ConfigMgr::instance()->m_Config.m_bToAndroid = true;
	CCLog("222222222222222222222222now m_config.m_btoandroid is false  to true");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	toAndridUserProtion("http://www.91zjd.com/Agreement.html");
#endif

}

void RegistLayer::onRegistSucc(CCObject* obj)
{
	RoomLayer* layer = RoomLayer::create();
	layer->automaticLogin(false);
	layer->showLoginAward();
	layer->showMoveingLabelTips(ConfigMgr::instance()->text("t407"));
	CCScene* scene = CCScene::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(scene);
}

void RegistLayer::onRegisterFaild(CCObject* obj)
{
	CCString* str = (CCString*)obj;
	PromptBox* box = PromptBox::PromptBoxWith(ccp(427,240),mPromptTypePasswordFind);
	box->setPromptText(str->getCString());
	addChild(box,100);
}

void RegistLayer::showAgreePlayerXieYi(cocos2d::CCObject *obj){
	playButtonSound();
	winSize = CCDirector::sharedDirector()->getWinSize();
	string szAccount  = m_pUserNameKuang->getText();
	string szPassword = m_pPassWordKuang->getText();
	string szSPassword = m_pPassWordKuangOK->getText();

	int n = szAccount.length();

	if (szPassword != szSPassword)
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t28"),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer,10);
		return;
	}


	if(szAccount.length() < 6 || szAccount.length() > 12)
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t29"),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer,10);
		return;
	}

	if (szPassword.length() < 6 || szPassword.length() > 12)
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t457"),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer,10);
		return;
	}

	if ( !isLegal(szAccount) || !isLegal(szPassword))
	{
		MovingLabelLayer* layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t30"),ccp(winSize.width * 0.5,winSize.height * 0.5));
		addChild(layer,10);
		return;
	}
	bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	if (!bRet)
	{
		PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeServerShut);
		addChild(box,100);
	}else{
		EntityMgr::instance()->login()->setUserRegister(szAccount.c_str(),szPassword.c_str(),nfaceID,nGenter,0);
		//EntityMgr::instance()->login()->setUserLogin(szAccount.c_str(),szPassword.c_str());
	}
}

bool RegistLayer::isLegal(string str)
{
	//const char* s = str.c_str();
	char s[128] = {0};
	memcpy(s, str.c_str(), min(sizeof(s)-1, str.length()));
	CCLOG("get user accout str = %s, strlen(str)=%d",str.c_str(), strlen(str.c_str()));
	CCLOG("get user accout char = %s strlen(s)=%d", s, strlen(s));
	int i = 0;
	while (i++ < str.length() - 1)
	{
		if (s[i] < 0 || s[i] > 127)
		{
			//("中文");
			CCLOG("registLayer chinese");
		}
		else if (s[i]>='0' && s[i]<='9')
		{
			//("数字");
			CCLOG("registLayer number");
		}
		else if (s[i]>='A' && s[i]<='Z' || s[i]>='a' && s[i]<='z')
		{
			CCLOG("registLayer a b c");
		}
		else
		{
			//("其它");
			CCLOG("RegistLayer::isLegal false s[%d]:%d %s", i, s[i], &s[i]);
			return  false;
		}
	}
	return  true;
}


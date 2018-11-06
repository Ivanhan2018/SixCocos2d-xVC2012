#include "OverRegistLayer.h"
#include "RoomLayer.h"
#include "GroupSprite.h"
#include "MovingLabelLayer.h"
#include "LoginLayer.h"
#include "PromptBox.h"
#include "ans/utf-8.h"
#include "RoomOption.h"


using namespace cocos2d;
OverRegistLayer::OverRegistLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this, callfuncO_selector(OverRegistLayer::onOverRes), MSG_UI_ANS_OVERREGISTRES, NULL);
}
OverRegistLayer::~OverRegistLayer()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_OVERREGISTRES);
}


bool OverRegistLayer::init()
{
	bool bRet = false;
	do 
	{
		winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *pRegistBJLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		CCSprite *pRegistBJRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_12.jpg"));
		//pRegistBJRight->setRotationY(180);
		pRegistBJLeft->setPosition(ccp(winSize.width*0.25,winSize.height*0.5));
		pRegistBJRight->setPosition(ccp(winSize.width*0.75,winSize.height*0.5));
		addChild(pRegistBJLeft,0);
		addChild(pRegistBJRight,0);

		CCSprite *pPlayerInfoBJLeft1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		CCSprite *pPlayerInfoBJRight1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		//pPlayerInfoBJRight1->setRotationY(180);
		pPlayerInfoBJLeft1->setPosition(ccp(winSize.width*0.25+5,winSize.height*0.0-18));
		pPlayerInfoBJRight1->setPosition(ccp(winSize.width*0.75-7,winSize.height*0.0-18));
		pPlayerInfoBJLeft1->setScaleY(1.2f);
		pPlayerInfoBJRight1->setScaleY(1.2f);
		pPlayerInfoBJLeft1->setAnchorPoint(ccp(0.5,0));
		pPlayerInfoBJRight1->setAnchorPoint(ccp(0.5,0));
		addChild(pPlayerInfoBJLeft1,1);
		addChild(pPlayerInfoBJRight1,1);


		CCScale9Sprite *pDituLeft1 = CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_5.png"));
		pDituLeft1->setContentSize(CCSizeMake(198.0f,149.0f));
		pDituLeft1->setPosition(ccp(340.0f,284.0f));
		addChild(pDituLeft1,1);
		CCScale9Sprite *pDituRight1 = CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_5.png"));
		//pDituRight1->setRotationY(180);
		pDituRight1->setContentSize(CCSizeMake(198.0f,149.0f));
		pDituRight1->setPosition(ccp(340.0f+197.0f,284.0f));
		addChild(pDituRight1,1);


		CCSprite *pRegistLogoBack = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_14.png"));
		pRegistLogoBack->setPosition(ccp(winSize.width*0.5,winSize.height*0.923));
		addChild(pRegistLogoBack,1);
		CCSprite *pRegistLogo = CCSprite::createWithSpriteFrame(spriteFrame("dt_overregist2.png"));
		pRegistLogo->setPosition(ccp(winSize.width*0.5,winSize.height*0.927));
		addChild(pRegistLogo,1);
	

		CCSprite *pCloseNormalButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pCloseSelectButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pCloseItemSprite = CCMenuItemSprite::create
		(pCloseNormalButton,pCloseSelectButton,this,menu_selector(OverRegistLayer::dismiss));
		pCloseSelectButton->setScale(0.9f);
		pCloseSelectButton->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseButton = CCMenu::create(pCloseItemSprite,NULL);
		pCloseButton->setPosition(ccp(winSize.width*0.943,winSize.height*0.923));
		addChild(pCloseButton,1);


		const char * pTextTps = ConfigMgr::instance()->text("t463");

		CCLabelTTF* pTTFUserTps = CCLabelTTF::create(pTextTps, "HelveticaNeue-Bold", 17);
		pTTFUserTps->setColor(ccc3(115,78,17));
		pTTFUserTps->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.8)); 
		addChild(pTTFUserTps,1);

		const char * pTextUserName = ConfigMgr::instance()->text("t94");
		CCLabelTTF* pTTFUserName = CCLabelTTF::create(pTextUserName, "HelveticaNeue-Bold", 22);
		pTTFUserName->setColor(ccc3(115,78,17));
		pTTFUserName->setPosition(CCPointMake(winSize.width*0.360+25, winSize.height * 0.702)); 
		addChild(pTTFUserName,1);

		m_pUserNameKuang= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_register_19.png")));
		m_pUserNameKuang->setPosition(CCPointMake(winSize.width*0.600, winSize.height * 0.702));
		m_pUserNameKuang->setPlaceHolder(ConfigMgr::instance()->text("t163"));
		addChild(m_pUserNameKuang,1);
		std::string strUserName = CCUserDefault::sharedUserDefault()->getStringForKey("NEWZJD_ACCOUNT");
		m_pUserNameKuang->setText(strUserName.c_str());

		const char * pTextUserPassword = ConfigMgr::instance()->text("t461");

		CCLabelTTF* pTTFUserPassword = CCLabelTTF::create(pTextUserPassword, "HelveticaNeue-Bold", 22);
		pTTFUserPassword->setColor(ccc3(115,78,17));
		pTTFUserPassword->setPosition(CCPointMake(winSize.width*0.360+25, winSize.height * 0.598)); 
		addChild(pTTFUserPassword,1);

		m_pPassWordKuang= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_register_19.png")));
		m_pPassWordKuang->setPosition(CCPointMake(winSize.width*0.600, winSize.height * 0.598));
		m_pPassWordKuang->setPlaceHolder(ConfigMgr::instance()->text("t97"));
		m_pPassWordKuang->setInputFlag(kEditBoxInputFlagPassword);
		addChild(m_pPassWordKuang,1);

		const char * pTextUserPasswordOK = ConfigMgr::instance()->text("t462");

		CCLabelTTF* pTTFUserPasswordOK = CCLabelTTF::create(pTextUserPasswordOK, "HelveticaNeue-Bold", 22);
		pTTFUserPasswordOK->setColor(ccc3(115,78,17));
		pTTFUserPasswordOK->setPosition(CCPointMake(winSize.width*0.360+25, winSize.height * 0.492)); 
		addChild(pTTFUserPasswordOK,1);

		m_pPassWordKuangOK= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_register_19.png")));
		m_pPassWordKuangOK->setPosition(CCPointMake(winSize.width*0.600, winSize.height * 0.492));
		m_pPassWordKuangOK->setPlaceHolder(ConfigMgr::instance()->text("t99"));
		m_pPassWordKuangOK->setInputFlag(kEditBoxInputFlagPassword);
		addChild(m_pPassWordKuangOK,1);


		const char * pBangDingTXZ = ConfigMgr::instance()->text("t472");
		CCLabelTTF *pTTFBangDingTXZ=CCLabelTTF::create(pBangDingTXZ ,"HelveticaNeue-Bold",18);
		pTTFBangDingTXZ->setColor(ccc3(116,117,42));
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
		addChild(pDituLeft2,2);
		CCScale9Sprite *pDituRight2 = CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_5.png"));
		//pDituRight2->setRotationY(180);
		pDituRight2->setContentSize(CCSizeMake(389.0f,125.0f));
		pDituRight2->setPosition(ccp(427.0f+193.5f,72.0f));
		addChild(pDituRight2,1);


		CCSprite *pLog0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_overregist1.png"));
		pLog0->setPosition(CCPointMake(winSize.width*0.25, winSize.height * 0.219));  
		addChild(pLog0,2);
		

		CCSprite *okNormal =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCSprite *okSelect =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCMenuItemSprite * okItemSprite = CCMenuItemSprite::create(okNormal, okSelect, this, menu_selector(OverRegistLayer::showPlayerXieYi));
		CCMenu* m_pOkMenu = CCMenu::create(okItemSprite,NULL);
		//m_pOkMenu->setScale(0.8f);
		m_pOkMenu->setPosition(CCPointMake(winSize.width * 0.5 ,winSize.height * 0.36));
		okSelect->setScale(0.9f);
		okSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		addChild(m_pOkMenu,5);

		/*CCSprite *pDiKuang1 = CCSprite::create("dt_register_16.png");	
		pDiKuang1->setPosition(CCPointMake(winSize.width*0.738, winSize.height * 0.225)) ; 
		addChild(pDiKuang1,1);*/
		CCSprite *pLog1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_4.png"));
		pLog1->setPosition(CCPointMake(winSize.width*0.75, winSize.height * 0.219));  
		addChild(pLog1,2);
		
		


		/*CCSprite *pDiKuang2 = CCSprite::create("dt_register_16.png");	
		pDiKuang2->setPosition(CCPointMake(winSize.width*0.254, winSize.height * 0.079)) ; 
		addChild(pDiKuang2,1);*/
		CCSprite *pLog2 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_3.png"));
		pLog2->setPosition(CCPointMake(winSize.width*0.21, winSize.height * 0.085));  
		addChild(pLog2,2);

		/*CCSprite *pDiKuang3 = CCSprite::create("dt_register_16.png");	
		pDiKuang3->setPosition(CCPointMake(winSize.width*0.738, winSize.height * 0.079)) ;  
		addChild(pDiKuang3,1);*/
		CCSprite *pLog3 = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_222.png"));
		pLog3->setPosition(CCPointMake(winSize.width*0.775, winSize.height * 0.085));  
		addChild(pLog3,2);

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

void OverRegistLayer::setRegistLayerFrom(int num)
{
	m_nRegistFrom = num;
}


void OverRegistLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	if(m_nRegistFrom == 1)
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
		CCScene* scene = CCScene::create();
		RoomOption * pRoomLayer = RoomOption::create();
		scene->addChild(pRoomLayer);
		CCDirector::sharedDirector()->replaceScene(scene);
	}
}

void OverRegistLayer::keyBackClicked()
{
	dismiss(NULL);
}

void OverRegistLayer::onOverRes(CCObject* obj)
{
	CCInteger* inter = (CCInteger*)obj;
	MovingLabelLayer* layer;
	switch(inter->getValue())
	{
		case 0:
			{
				string szAccount  = m_pUserNameKuang->getText();
				string szPassword = m_pPassWordKuang->getText();
				cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("NEWZJD_ACCOUNT", szAccount);
				cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey("NEWZJD_PASSWORD", szPassword);

				layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t464"),ccp(427,240));
				CCScene* scene = CCScene::create();
				RoomLayer* layer = RoomLayer::create();
				layer->automaticLogin(true,true);
				scene->addChild(layer);
				layer->closeLoginAward();
				CCTransitionFade *tScene = CCTransitionFade::create(2.0f, scene, ccWHITE);
				CCDirector::sharedDirector()->replaceScene(tScene); 
				break;
			}
		case 1:
			{
				layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t468"),ccp(427,240));
				break;
			}
		case 2:
			{
				layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t465"),ccp(427,240));
				break;
			}
		case 3:
			{
				layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t466"),ccp(427,240));
				break;
			}
		case 4:
			{
				layer = MovingLabelLayer::MovingLabelLayerWith(ConfigMgr::instance()->text("t467"),ccp(427,240));
				break;
			}
		default:
			break;
	}
	addChild(layer,10);
}

//void OverRegistLayer::onRegistSucc(CCObject* obj)
//{
//	RoomLayer* layer = RoomLayer::create();
//	layer->automaticLogin(false);
//	layer->showLoginAward();
//	layer->showMoveingLabelTips(ConfigMgr::instance()->text("t407"));
//	CCScene* scene = CCScene::create();
//	scene->addChild(layer);
//	CCDirector::sharedDirector()->replaceScene(scene);
//}

//void OverRegistLayer::onRegisterFaild(CCObject* obj)
//{
//	CCString* str = (CCString*)obj;
//	PromptBox* box = PromptBox::PromptBoxWith(ccp(427,240),mPromptTypePasswordFind);
//	box->setPromptText(str->getCString());
//	addChild(box,100);
//}

void OverRegistLayer::showPlayerXieYi(cocos2d::CCObject *obj){
	playButtonSound();
	winSize = CCDirector::sharedDirector()->getWinSize();
	string szAccount  = m_pUserNameKuang->getText();
	string szPassword = m_pPassWordKuang->getText();
	string szSPassword = m_pPassWordKuangOK->getText();

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
	}

	//char buf[50];
	//memset(buf, 0, 50);
	//utf::utf_gb_convert("utf-8", "gb2312", buf,50, const_cast<char*>(szAccount.c_str()), szAccount.length());

	//EntityMgr::instance()->getActor()->login()->setUserRegister(szAccount.c_str(),szPassword.c_str(),nFaceId,nGender);
	EntityMgr::instance()->getDispatch()->overRegist(szAccount.c_str(),szSPassword);
}

bool OverRegistLayer::isLegal(string str)
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

 
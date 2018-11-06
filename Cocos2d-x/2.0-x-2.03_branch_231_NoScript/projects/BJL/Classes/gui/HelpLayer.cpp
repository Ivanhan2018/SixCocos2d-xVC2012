#include "HelpLayer.h"
#include "RoomLayer.h"
#include "HelpScrollView.h"
#include "FreeLayer.h"
using namespace cocos2d;
HelpLayer::HelpLayer()
{

}
HelpLayer::~HelpLayer()
{

}
CCScene* HelpLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelpLayer *layer = HelpLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool HelpLayer::init()
{
	bool bRet = false;
	do 
	{	
		
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		srand(unsigned(time(NULL)));
		
		CCLayerColor *m_layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 813.0f, 400.0f);
		m_layer->ignoreAnchorPointForPosition(false);
		m_layer->setPosition(ccp(winSize.width*0.5f,winSize.height*0.5f-50)); 
		addChild(m_layer,0);

		CCSprite *helpLayerBk = CCSprite::create("background/bg2.png");
		helpLayerBk->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(helpLayerBk,0);

		HelpScrollView *pHelpView = HelpScrollView::create();
		addChild(pHelpView,0);
	
		CCSprite *maskSprite = CCSprite::createWithSpriteFrame(spriteFrame("bg2_2.png"));
		maskSprite->setPosition(ccp(winSize.width/2,winSize.height-maskSprite->getContentSize().height/2));
		this->addChild(maskSprite,1);

		CCSprite *titleSprite = CCSprite::createWithSpriteFrame(spriteFrame("Tab_GameRule2.png"));
		titleSprite->setPosition(ccp(winSize.width/2,winSize.height*0.9f-2));
		this->addChild(titleSprite,1);

		//CCSprite *pPlayerInfoBJLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_email11.jpg"));
		//CCSprite *pPlayerInfoBJRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_email11.jpg"));
		//pPlayerInfoBJRight->setRotationY(180);
		//pPlayerInfoBJLeft->setPosition(ccp(winSize.width*0.25,winSize.height-52));
		//pPlayerInfoBJRight->setPosition(ccp(winSize.width*0.75 - 1,winSize.height-52));
		//addChild(pPlayerInfoBJLeft,0);
		//addChild(pPlayerInfoBJRight,0);

	


		//CCSprite *pPlayerInfoBJLeft1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email10.png"));
		//CCSprite *pPlayerInfoBJRight1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email10.png"));
		//pPlayerInfoBJRight1->setRotationY(180);
		//pPlayerInfoBJLeft1->setPosition(ccp(winSize.width*0.25+5,winSize.height*0.0-18));
		//pPlayerInfoBJRight1->setPosition(ccp(winSize.width*0.75-5,winSize.height*0.0-18));
		//pPlayerInfoBJLeft1->setScaleY(1.2f);
		//pPlayerInfoBJRight1->setScaleY(1.2f);
		//pPlayerInfoBJLeft1->setAnchorPoint(ccp(0.5,0));
		//pPlayerInfoBJRight1->setAnchorPoint(ccp(0.5,0));
		//addChild(pPlayerInfoBJLeft1,1);
		//addChild(pPlayerInfoBJRight1,1);

		//Ãâ·Ñ
		//CCSprite *pMianFeiSpriteNormal = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
		//CCSprite *pMianFeiSpriteSelect = CCSprite::createWithSpriteFrame(spriteFrame("dt_playerinfo_0.png"));
		//CCMenuItemSprite* pMianfei = CCMenuItemSprite::create(pMianFeiSpriteNormal,pMianFeiSpriteSelect,this,menu_selector(HelpLayer::toFreeLayer));
		//pMianFeiSpriteSelect->setScale(0.9f);
		//pMianFeiSpriteSelect->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		//CCMenu* mianfeiMenu = CCMenu::create(pMianfei,NULL);
		//mianfeiMenu->setPosition(CCPointMake(winSize.width*0.054,winSize.height*0.885));
		//addChild(mianfeiMenu,1);


		//CCSprite *pPlayerInfoLogo = CCSprite::createWithSpriteFrame(spriteFrame("dt_register_14.png"));
		//pPlayerInfoLogo->setPosition(ccp(winSize.width*0.5,winSize.height*0.923));
		//addChild(pPlayerInfoLogo,2);

		//CCSprite *pPlayerInfoLogoText = CCSprite::createWithSpriteFrame(spriteFrame("dt_help_1.png"));
		//pPlayerInfoLogoText->setPosition(ccp(winSize.width*0.5,winSize.height*0.933));
		//addChild(pPlayerInfoLogoText,3);



		CCSprite *pCloseNormalButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCSprite *pCloseSelectButton = CCSprite::createWithSpriteFrame(spriteFrame("dt_guanbibig.png"));
		CCMenuItemSprite *pCloseItemSprite = CCMenuItemSprite::create
			(pCloseNormalButton,pCloseSelectButton,this,menu_selector(HelpLayer::dismiss));
		pCloseSelectButton->setScale(0.9f);
		pCloseSelectButton->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseButton = CCMenu::create(pCloseItemSprite,NULL);
		pCloseButton->setPosition(ccp(winSize.width*0.943,winSize.height*0.923));
		addChild(pCloseButton,1);

		//CCSprite *m_bantouming_bj_left = CCSprite::createWithSpriteFrame(spriteFrame("dt_help_2.png"));
		//
		//m_bantouming_bj_left->setPosition(ccp(427.0f-164.0f,26.0f));
		//addChild(m_bantouming_bj_left,4);

		//CCSprite *m_bantouming_bj_right = CCSprite::createWithSpriteFrame(spriteFrame("dt_help_2.png"));
		//m_bantouming_bj_right->setRotationY(180.0f);
		//m_bantouming_bj_right->setPosition(ccp(427.0f+164.0f,26.0f));
		//addChild(m_bantouming_bj_right,4);

		pNode = CCNode::create();
		
		CCString* strTips = CCString::createWithFormat("t%d",rand()%9+420);

		m_pXiaoTiShi = CCLabelTTF::create(ConfigMgr::instance()->text(strTips->getCString()),"HelveticaNeue-Bold", 22);
		m_pXiaoTiShi->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.054));
		m_pXiaoTiShi->setColor(ccc3(255,255,0));
		addChild(m_pXiaoTiShi,5);

		CCLabelTTF *pWanFaShuoMing = CCLabelTTF::create(ConfigMgr::instance()->text("t140"),"",21);
		pWanFaShuoMing->setColor(ccc3(189,154,97));
		pWanFaShuoMing->setAnchorPoint(ccp(0,0.5));
		pWanFaShuoMing->setPosition(CCPointMake(41.0f,346.0f));
		//addChild(pWanFaShuoMing,5);
	   /* HelpScrollLayer *pHelpScroll = HelpScrollLayer::HelpScrollLayerWith(0,34);
		pHelpScroll->setPosition(CCPointMake(21.0f,45.0f));
		addChild(pHelpScroll,5);
*/
		/*HelpScrollView *pHelpView = HelpScrollView::create();
		addChild(pHelpView,5);*/
		schedule(schedule_selector(HelpLayer::changeTipsContent),5.0f);
		setKeypadEnabled(true);
		bRet = true;
	} while (0);

	return bRet;

}

void HelpLayer::changeTipsContent(float dt)
{
	CCString* strTips = CCString::createWithFormat("t%d",rand()%9+420);

	m_pXiaoTiShi->setString(ConfigMgr::instance()->text(strTips->getCString()));
}

void HelpLayer::dismiss(cocos2d::CCObject *obj){
	playButtonSound();
	CCScene *pScene = CCScene::create();
	RoomLayer *pRoomLayer = RoomLayer::create();
	pRoomLayer->automaticLogin(false);
	pRoomLayer->closeLoginAward();
	pScene->addChild(pRoomLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void HelpLayer::keyBackClicked()
{
	dismiss(NULL);
}

void HelpLayer::toFreeLayer(cocos2d::CCObject *obj){
	playButtonSound();
	CCDirector::sharedDirector()->replaceScene(FreeLayer::scene());

}


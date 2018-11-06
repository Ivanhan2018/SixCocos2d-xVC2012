#include "ChoosePlayerPhotoLayer.h"
#include "PlayerInfoLayer.h"
#include "ChoosePhotoScrollLayer.h"
using namespace cocos2d;
ChoosePlayerPhotoLayer::ChoosePlayerPhotoLayer()
{

}
ChoosePlayerPhotoLayer::~ChoosePlayerPhotoLayer()
{

}
CCScene* ChoosePlayerPhotoLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		ChoosePlayerPhotoLayer *layer = ChoosePlayerPhotoLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool ChoosePlayerPhotoLayer::init()
{
	bool bRet = false;
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
		CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);

		CCSprite *pWarningBJLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_3.png"));
		CCSprite *pWarningBJRight = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_3.png"));
		//pWarningBJRight->setRotationY(180);
		pWarningBJLeft->setPosition(ccp(winSize.width*0.28,winSize.height*0.5));
		pWarningBJRight->setPosition(ccp(winSize.width*0.28+380,winSize.height*0.5));
		addChild(pWarningBJLeft,0);
		addChild(pWarningBJRight,0);
		

		CCSprite *pbuttonNormalClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_11.png"));
		CCSprite *pbuttonSelectClose = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_11.png"));
		CCMenuItemSprite *pButtonClose = CCMenuItemSprite::create
			(pbuttonNormalClose,pbuttonSelectClose,this,menu_selector(ChoosePlayerPhotoLayer::dismiss));
		pbuttonSelectClose->setScale(0.9f);
		pbuttonSelectClose->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pButton0 = CCMenu::create(pButtonClose,NULL);
		pButton0->setPosition(ccp(winSize.width*0.920,winSize.height*0.850));  
		addChild(pButton0,2);
		CCLabelTTF *pChoosePhotoLog = CCLabelTTF::create(ConfigMgr::instance()->text("t138"),"HelveticaNeue-Bold", 22);
		pChoosePhotoLog->setPosition(ccp(winSize.width*0.5,winSize.height*0.845));
		pChoosePhotoLog->setColor(ccc3(166,117,42));
		addChild(pChoosePhotoLog,2);

		/**添加女生图像**/
		ChoosePhotoScrollLayer* m_pSystemScorllView = ChoosePhotoScrollLayer::PhotoScrollLayerWith(0,3);
		m_pSystemScorllView->setPosition(ccp(73,72));
		addChild(m_pSystemScorllView,0,101);
		/**添加男生图像**/
		ChoosePhotoScrollLayer* m_pSystemScorllView1 = ChoosePhotoScrollLayer::PhotoScrollLayerWith(1,3);
		m_pSystemScorllView1->setPosition(ccp(73,230));
		addChild(m_pSystemScorllView1,0,100);

		//CCSprite *pPhotoBJ1 = CCSprite::create("dt_register_6.png");
		//CCSprite *pPhotoBJ2 = CCSprite::create("dt_register_6.png");
		//CCSprite *pPhotoBJ3 = CCSprite::create("dt_register_6.png");
		//CCSprite *pPhotoBJ4 = CCSprite::create("dt_register_6.png");
		//CCSprite *pPhotoBJ5 = CCSprite::create("dt_register_6.png");
		//CCSprite *pPhotoBJ6 = CCSprite::create("dt_register_6.png");
		//CCSprite *pPhotoBJ7 = CCSprite::create("dt_register_6.png");
		//CCSprite *pPhotoBJ8 = CCSprite::create("dt_register_6.png");
		//pPhotoBJ1->setPosition(CCPointMake(winSize.width*0.210,winSize.height*0.604));
		//pPhotoBJ2->setPosition(CCPointMake(winSize.width*0.210+165,winSize.height*0.604));
		//pPhotoBJ3->setPosition(CCPointMake(winSize.width*0.210+2*165,winSize.height*0.604));
		//pPhotoBJ4->setPosition(CCPointMake(winSize.width*0.210+3*165,winSize.height*0.604));
		//pPhotoBJ5->setPosition(CCPointMake(winSize.width*0.210,winSize.height*0.323));
		//pPhotoBJ6->setPosition(CCPointMake(winSize.width*0.210+165,winSize.height*0.323));
		//pPhotoBJ7->setPosition(CCPointMake(winSize.width*0.210+2*165,winSize.height*0.323));
		//pPhotoBJ8->setPosition(CCPointMake(winSize.width*0.210+3*165,winSize.height*0.323));
		//addChild(pPhotoBJ1,2);
		//addChild(pPhotoBJ2,2);
		//addChild(pPhotoBJ3,2);
		//addChild(pPhotoBJ4,2);
		//addChild(pPhotoBJ5,2);
		//addChild(pPhotoBJ6,2);
		//addChild(pPhotoBJ7,2);
		//addChild(pPhotoBJ8,2);
		///*	CCSprite * pPhotoNormalImage1 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage1 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto1 = CCMenuItemSprite::create
		//(pPhotoNormalImage1,pPhotoSelectImage1,this,menu_selector(ChoosePlayerPhotoLayer::choose1));
		//pPhotoSelectImage1->setScale(0.9f);
		//pPhotoSelectImage1->setAnchorPoint(ccp(-0.5/9,-0.5/9));*/

		//CCSprite * pPhotoNormalImage1 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage1 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto1 = CCMenuItemSprite::create
		//	(pPhotoNormalImage1,pPhotoSelectImage1,this,menu_selector(ChoosePlayerPhotoLayer::choose1));
		//pPhotoSelectImage1->setScale(0.9f);
		//pPhotoSelectImage1->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite * pPhotoNormalImage2 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage2 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto2 = CCMenuItemSprite::create
		//	(pPhotoNormalImage2,pPhotoSelectImage2,this,menu_selector(ChoosePlayerPhotoLayer::choose2));
		//pPhotoSelectImage2->setScale(0.9f);
		//pPhotoSelectImage2->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite * pPhotoNormalImage3 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage3 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto3 = CCMenuItemSprite::create
		//	(pPhotoNormalImage3,pPhotoSelectImage3,this,menu_selector(ChoosePlayerPhotoLayer::choose3));
		//pPhotoSelectImage3->setScale(0.9f);
		//pPhotoSelectImage3->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite * pPhotoNormalImage4 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage4 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto4 = CCMenuItemSprite::create
		//	(pPhotoNormalImage4,pPhotoSelectImage4,this,menu_selector(ChoosePlayerPhotoLayer::choose4));
		//pPhotoSelectImage4->setScale(0.9f);
		//pPhotoSelectImage4->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite * pPhotoNormalImage5 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage5 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto5 = CCMenuItemSprite::create
		//	(pPhotoNormalImage5,pPhotoSelectImage5,this,menu_selector(ChoosePlayerPhotoLayer::choose5));
		//pPhotoSelectImage5->setScale(0.9f);
		//pPhotoSelectImage5->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite * pPhotoNormalImage6 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage6 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto6 = CCMenuItemSprite::create
		//	(pPhotoNormalImage6,pPhotoSelectImage6,this,menu_selector(ChoosePlayerPhotoLayer::choose6));
		//pPhotoSelectImage6->setScale(0.9f);
		//pPhotoSelectImage6->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite * pPhotoNormalImage7 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage7 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto7 = CCMenuItemSprite::create
		//	(pPhotoNormalImage7,pPhotoSelectImage7,this,menu_selector(ChoosePlayerPhotoLayer::choose7));
		//pPhotoSelectImage7->setScale(0.9f);
		//pPhotoSelectImage7->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCSprite * pPhotoNormalImage8 = CCSprite::create("dt_register_8.png");
		//CCSprite * pPhotoSelectImage8 = CCSprite::create("dt_register_8.png");
		//CCMenuItemSprite *pPhoto8 = CCMenuItemSprite::create
		//	(pPhotoNormalImage8,pPhotoSelectImage8,this,menu_selector(ChoosePlayerPhotoLayer::choose8));
		//pPhotoSelectImage8->setScale(0.9f);
		//pPhotoSelectImage8->setAnchorPoint(ccp(-0.5/9,-0.5/9));

		//CCMenu *pMenuTop = CCMenu::create(pPhoto1,pPhoto2,pPhoto3,pPhoto4,NULL);
		//pMenuTop->alignItemsHorizontallyWithPadding(98.0f);
		//CCMenu *pMenuBottom = CCMenu::create(pPhoto5,pPhoto6,pPhoto7,pPhoto8,NULL);
		//pMenuBottom->alignItemsHorizontallyWithPadding(98.0f);
		//pMenuTop->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.604));
		//pMenuBottom->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.323));
		//addChild(pMenuTop,3);
		//addChild(pMenuBottom,3);
		//m_choose_log =CCSprite::create("dt_warning_0.png");
		//m_choose_log->setPosition(ccp(206.0f,322.0f));
		//addChild(m_choose_log,4);
		bRet = true;
	} while (0);

	return bRet;

}

//void ChoosePlayerPhotoLayer::choose1(cocos2d::CCObject *obj)
//{
//	
//	m_choose_log->setPosition(ccp(206.0f,322.0f));
//	
//	
//}
//void ChoosePlayerPhotoLayer::choose2(cocos2d::CCObject *obj)
//{
//	m_choose_log->setPosition(ccp(206.0f+165,322.0f));
//	
//	
//}
//void ChoosePlayerPhotoLayer::choose3(cocos2d::CCObject *obj)
//{
//	m_choose_log->setPosition(ccp(206.0f+165*2,322.0f));
//	
//}
//void ChoosePlayerPhotoLayer::choose4(cocos2d::CCObject *obj)
//{
//	m_choose_log->setPosition(ccp(206.0f+165*3,322.0f));
//	
//}
//void ChoosePlayerPhotoLayer::choose5(cocos2d::CCObject *obj)
//{
//	m_choose_log->setPosition(ccp(206.0f,188.0f));
//	
//}
//void ChoosePlayerPhotoLayer::choose6(cocos2d::CCObject *obj)
//{
//	m_choose_log->setPosition(ccp(206.0f+165*1,188.0f));
//	
//}
//void ChoosePlayerPhotoLayer::choose7(cocos2d::CCObject *obj)
//{
//	m_choose_log->setPosition(ccp(206.0f+165*2,188.0f));
//	
//}
//void ChoosePlayerPhotoLayer::choose8(cocos2d::CCObject *obj)
//{
//	m_choose_log->setPosition(ccp(206.0f+165*3,188.0f));
//	
//}
void ChoosePlayerPhotoLayer::dismiss(cocos2d::CCObject *obj){
  PlayerInfoLayer* playInfo = (PlayerInfoLayer*)this->getParent();
  playInfo->permitButtom();
  this->removeFromParentAndCleanup(true);

}

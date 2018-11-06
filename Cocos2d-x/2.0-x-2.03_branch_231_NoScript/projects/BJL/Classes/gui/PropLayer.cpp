#include "PropLayer.h"
#include "MenuLayer.h"
#include "cocos-ext.h"
#include "GroupSprite.h"
#include "entity/EntityMgr.h"

using namespace cocos2d::extension;
using namespace cocos2d;
PropLayer::PropLayer()
{

}
PropLayer::~PropLayer()
{

}
CCScene* PropLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		PropLayer *layer = PropLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool PropLayer::init()
{
	bool bRet = false;
	do 
	{
		
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCLayerColor* layer = CCLayerColor::create(ccc4(0, 0, 0, 255*0.5f), 854.0f, 480.0f);
		layer->ignoreAnchorPointForPosition(false);
		layer->setPosition(ccp(winSize.width*0.5,winSize.height*0.5));
		addChild(layer);
		/**��ӱ���ͼƬ**/
		CCSprite *pBGLeft = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_12.png")); 
		pBGLeft->setAnchorPoint(ccp(0.5f,0.5f));
		pBGLeft->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		addChild(pBGLeft);

		/**��ӱ���LOG**/
		CCSprite *pTitleLog =CCSprite::createWithSpriteFrame(spriteFrame("dt_prop_1.png"));  
		pTitleLog->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5+pBGLeft->getTexture()->getPixelsHigh()/2-28));
		addChild(pTitleLog,2);

		/**��ӹرհ�ť**/
		CCSprite *pCloseNormalImage = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png")); 
		CCSprite *pCloseSelectImage = CCSprite::createWithSpriteFrame(spriteFrame("dt_kefu_0.png")); 
		CCMenuItemSprite *pCloseMenuItem= CCMenuItemSprite::create
			(pCloseNormalImage,pCloseSelectImage,this,menu_selector(PropLayer::dismiss)); 
		pCloseSelectImage->setScale(0.9f);
		pCloseSelectImage->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pCloseMenu = CCMenu::create(pCloseMenuItem,NULL);
		pCloseMenu->setPosition(winSize.width*0.5+pBGLeft->getTexture()->getPixelsWide()/2-25,winSize.height*0.5+pBGLeft->getTexture()->getPixelsHigh()/2-25);
		addChild(pCloseMenu,2);

		/**���ȷ����ť**/
		CCSprite *pSureNormalImage =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCSprite *pSureSelectImage =(CCSprite *)GroupSprite::GroupSpriteWith("dt_warning_8.png","dt_prop_0.png",GorupSpriteTypePhotoAndPhoto);
		CCMenuItemSprite *pSureMenuItem= CCMenuItemSprite::create
			(pSureNormalImage,pSureSelectImage,this,menu_selector(PropLayer::makeSure)); 
		pSureSelectImage->setScale(0.9f);
		pSureSelectImage->setAnchorPoint(ccp(-0.5/9,-0.5/9));
		CCMenu *pSureMenu = CCMenu::create(pSureMenuItem,NULL);
		pSureMenu->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5-pBGLeft->getTexture()->getPixelsHigh()/2+40));
		addChild(pSureMenu,2);

		/**���������ʾ**/
		CCLabelTTF *pTextWaring0 =CCLabelTTF::create(ConfigMgr::instance()->text("t152"),"HelveticaNeue-Bold",18);
		pTextWaring0->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.683));
		addChild(pTextWaring0,3);

		CCLabelTTF *pTextWaring1 =CCLabelTTF::create(ConfigMgr::instance()->text("t153"),"HelveticaNeue-Bold",18);
		pTextWaring1->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.608));
		addChild(pTextWaring1,4);

	

		/**��������**/
		m_pUserInput= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_register_1.png")));
		m_pUserInput->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.49));
		m_pUserInput->setPlaceHolder(ConfigMgr::instance()->text("t154"));
	

		m_pUserVerifyInput= CCEditBox::create(CCSize(225, 32),CCScale9Sprite::createWithSpriteFrame(spriteFrame("dt_register_1.png")));
		m_pUserVerifyInput->setPosition(CCPointMake(winSize.width*0.5, winSize.height * 0.39));
		m_pUserVerifyInput->setPlaceHolder(ConfigMgr::instance()->text("t155"));

		addChild(m_pUserInput,2);
		addChild(m_pUserVerifyInput,2);

		CC_BREAK_IF(! CCLayer::init());
		bRet = true;
	} while (0);

	return bRet;

}


void PropLayer::dismiss(cocos2d::CCObject *obj)
{ 
	playButtonSound();
	 MenuLayer *pMenulayer = (MenuLayer *)this->getParent();
     pMenulayer->permitButtonClick();
	 this->removeFromParentAndCleanup(true);
	
 }
 void PropLayer::makeSure(cocos2d::CCObject *obj){
	 playButtonSound();
	 const char* szAccount1 = m_pUserInput->getText();
	 if (strlen(szAccount1) < 1)
	 {
		 //�û�������
		 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		 /*		 PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeLenFaild);
		 addChild(promptBox,20)*/;
		 return;
	 }
	 const char* szAccount2 = m_pUserVerifyInput->getText();

	 if (strcmp(szAccount1, szAccount2))
	 {
		 ////���������������һ�£�����ʧ��
		 //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		 //PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypePesetFail);
		 //addChild(promptBox,20);
		 return;
	 }

	 //��������
	 bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	 if (!bRet)
	 {
		 //CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		 //PromptBox * promptBox = PromptBox::PromptBoxWith(CCPointMake(winSize.width * 0.5, winSize.height * 0.5),mPromptTypeLoginConnectFaild);
		 //addChild(promptBox);
		 return;
	 }

	 EntityMgr::instance()->getDispatch()->setLoginState(enLogin_Server);
	 EntityMgr::instance()->getDispatch()->sendScoreGiftPacket(szAccount1,2000000);
                                                               
 }
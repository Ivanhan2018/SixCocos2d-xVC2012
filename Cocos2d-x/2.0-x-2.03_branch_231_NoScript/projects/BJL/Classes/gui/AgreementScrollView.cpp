#include "AgreementLayer.h"
#include "RoomLayer.h"
#include "AgreementScrollView.h"

using namespace cocos2d;
AgreementScrollView::AgreementScrollView()
{

}
AgreementScrollView::~AgreementScrollView()
{
}
cocos2d::CCScene* AgreementScrollView::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		AgreementScrollView *layer = AgreementScrollView::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool AgreementScrollView::init()
{
	bool bRet = false;
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *pPlayerInfoBJLeft1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		CCSprite *pPlayerInfoBJRight1 =CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		//pPlayerInfoBJRight1->setRotationY(180);
		pPlayerInfoBJLeft1->setPosition(ccp(winSize.width*0.25+5,winSize.height*0.0-18));
		pPlayerInfoBJRight1->setPosition(ccp(winSize.width*0.75-5,winSize.height*0.0-18));
		pPlayerInfoBJLeft1->setScaleY(1.2f);
		pPlayerInfoBJRight1->setScaleY(1.2f);
		pPlayerInfoBJLeft1->setAnchorPoint(ccp(0.5,0));
		pPlayerInfoBJRight1->setAnchorPoint(ccp(0.5,0));
		addChild(pPlayerInfoBJLeft1,1);
		addChild(pPlayerInfoBJRight1,1);

		
		str1 = CCLabelTTF::create(ConfigMgr::instance()->text("t241"),"",18,CCSizeMake(770,0),kCCTextAlignmentLeft);
		str1->setColor(ccc3(189,154,97));
		str1->setAnchorPoint(ccp(0,1));
		str1->setPosition(CCPointMake(61.0f,378.0f));
		addChild(str1,2);
		

		bRet = true;
	} while (0);

	return bRet;
}

void AgreementScrollView::visit()
{
	glEnable(GL_SCISSOR_TEST);
	glScissor(22.0f,8.0f, 802.0f, 378.0f);//x, y, w, h
	CCLayer::visit();//调用自己的类方法
	glDisable(GL_SCISSOR_TEST);

}

void AgreementScrollView::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);	

}

void AgreementScrollView::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}
bool AgreementScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	m_start = touchPoint.y;
	return true;
}
void AgreementScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	m_end = touchPoint.y;
	if(str1->getPositionY()<378){
      str1->setPositionY(378);
	  
	}
	str1->setPosition(CCPointMake(str1->getPositionX(),str1->getPositionY()+m_end-m_start));

	m_start = m_end;
}
void AgreementScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}
void AgreementScrollView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}


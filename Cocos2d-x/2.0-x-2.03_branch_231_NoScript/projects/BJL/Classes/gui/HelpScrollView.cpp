#include "HelpLayer.h"
#include "RoomLayer.h"
#include "HelpScrollView.h"

using namespace cocos2d;
HelpScrollView::HelpScrollView()
{

}
HelpScrollView::~HelpScrollView()
{
}
cocos2d::CCScene* HelpScrollView::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelpScrollView *layer = HelpScrollView::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
bool HelpScrollView::init()
{
	bool bRet = false;
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		/*CCSprite *pPlayerInfoBJLeft1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		CCSprite *pPlayerInfoBJRight1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_email8.jpg"));
		pPlayerInfoBJRight1->setRotationY(180);
		pPlayerInfoBJLeft1->setPosition(ccp(winSize.width*0.25+5,winSize.height*0.0-18));
		pPlayerInfoBJRight1->setPosition(ccp(winSize.width*0.75-5,winSize.height*0.0-18));
		pPlayerInfoBJLeft1->setScaleY(1.2f);
		pPlayerInfoBJRight1->setScaleY(1.2f);
		pPlayerInfoBJLeft1->setAnchorPoint(ccp(0.5,0));
		pPlayerInfoBJRight1->setAnchorPoint(ccp(0.5,0));
		addChild(pPlayerInfoBJLeft1,1);
		addChild(pPlayerInfoBJRight1,1);*/

		m_node = CCNode::create();
		addChild(m_node,2);


// 		CCLabelTTF *str1 = CCLabelTTF::create(ConfigMgr::instance()->text("t214"),"",18,CCSizeMake(750,300),kCCTextAlignmentLeft);
// 		str1->setColor(ccc3(189,154,97));
// 		str1->setAnchorPoint(ccp(0,0.5));
// 		str1->setPosition(CCPointMake(50.0f,175.0f));
// 		m_node->addChild(str1,3);
		CCPoint pt=CCPointMake(50.0f,175.0f+150.f+40);
		for (int i=0;i<32;i++)
		{
			const char *str =CCString::createWithFormat("t%d",209+i)->getCString();

			CCRect rect=addString(pt,ConfigMgr::instance()->text(str),CCSizeMake(0,0));
			pt.y-=rect.size.height+20;
		}
		m_endPos=ccp(pt.x,-pt.y+50);

		bRet = true;
	} while (0);

	return bRet;
}



void HelpScrollView::onEnter()
{
	CCLayer::onEnter();
CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);	

}

void HelpScrollView::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}
bool HelpScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	m_start = touchPoint.y;
	return true;
}
void HelpScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	m_end = touchPoint.y;
	CCLOG("%d",m_node->getPositionY());
	if(m_node->getPositionY()<0){
		m_node->setPositionY(0);
	}
	if (m_node->getPositionY()>m_endPos.y)
	{
		m_node->setPositionY(m_endPos.y);
	}
	
	m_node->setPosition(CCPointMake(m_node->getPositionX(),m_node->getPositionY()+m_end-m_start));
	
	m_start = m_end;
}
void HelpScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}
void HelpScrollView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
}

cocos2d::CCRect HelpScrollView::addString( CCPoint pt,const char* buff,CCSize size )
{

	CCLabelTTF *str1 = CCLabelTTF::create(buff,"",18,CCSizeMake(750,0),kCCTextAlignmentLeft);
	str1->setColor(ccc3(189,154,97));
	str1->setAnchorPoint(ccp(0,1.0));
	str1->setPosition(pt);
	m_node->addChild(str1,3);
	return str1->boundingBox();
}

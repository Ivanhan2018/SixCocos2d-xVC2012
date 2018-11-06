//
//  SelectButton.cpp
//  Game
//
//  Created by À¼ ÌìÀÖ on 13-6-7.
//
//

#include "ActivitySprite.h"
#include "ActivityLayer.h"

ActivitySprite * ActivitySprite::ActivitySpriteWith(int type)
{
    ActivitySprite * button = new ActivitySprite();
	int actuvityNum = 100+type;
	if(actuvityNum > 101)
	{
		actuvityNum = 99;
	}
	CCString* str = CCString::createWithFormat("dt_activity_%d.jpg",actuvityNum);
    if(button && button->initWithSpriteFrame(spriteFrame(str->getCString())))
    {
		button->initActivitySprite(type);
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
}
bool ActivitySprite::initActivitySprite(int type)
{
	m_nType = type;
    return true;
}
ActivitySprite::ActivitySprite()
{

}
ActivitySprite::~ActivitySprite()
{
    
}

void ActivitySprite::setSelect(bool select)
{
	if(select)
	{
		this->setScale(1.0);
	}
	else
	{
		this->setScale(0.8);
	}
}

void ActivitySprite::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
void ActivitySprite::onExit()
{
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
bool ActivitySprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	if(this->boundingBox().containsPoint(touchPoint))
	{
		ActivityLayer* layer = (ActivityLayer*)this->getParent();
		layer->changeActivity(m_nType);
		return false;
	}
	return false;
}
void ActivitySprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}
void ActivitySprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}
void ActivitySprite::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}


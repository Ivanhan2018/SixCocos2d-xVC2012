//
//  MatchError.cpp
//  Game
//
//  Created by ÂÞÃô on 13-7-10.
//
//

#include "MovingLabelLayer.h"


MovingLabelLayer * MovingLabelLayer::MovingLabelLayerWith(const char* str,CCPoint pos)
{
    MovingLabelLayer * match = new MovingLabelLayer();
    if (match && match->initMovingLabelLayer(str,pos))
    {
        match->autorelease();
        return match;
    }
    CC_SAFE_DELETE(match);
    return match;
}

MovingLabelLayer::MovingLabelLayer()
{
    
}

MovingLabelLayer::~MovingLabelLayer()
{
    
}

bool MovingLabelLayer::initMovingLabelLayer(const char* str,CCPoint pos)
{
    //if(!CCNode::init())
    //{
    //    return false;
    //}
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* spriteBack0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_14.png"));
	CCSprite* spriteBack1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_warning_14.png"));
	spriteBack0->setPosition(ccp(pos.x - spriteBack0->getContentSize().width * 0.5,pos.y));
	spriteBack1->setPosition(ccp(pos.x + spriteBack1->getContentSize().width * 0.5,pos.y));
	spriteBack1->setFlipX(true);
	this->addChild(spriteBack0);
	this->addChild(spriteBack1);
	CCLabelTTF* label = CCLabelTTF::create(str,"",20);
	label->setColor(ccc3(255,255,0));
	label->setPosition(pos);
	addChild(label);

	CCMoveTo* moveto0 = CCMoveTo::create(0.2f,ccp(spriteBack0->getPositionX(),spriteBack0->getPositionY() + 10));
	CCMoveTo* moveto1 = CCMoveTo::create(0.2f,ccp(spriteBack1->getPositionX(),spriteBack1->getPositionY() + 10));
	CCMoveTo* moveto2 = CCMoveTo::create(0.2f,ccp(label->getPositionX(),label->getPositionY() + 10));
	CCDelayTime* delay0 = CCDelayTime::create(2.0f);
	CCDelayTime* delay1 = CCDelayTime::create(2.0f);
	CCDelayTime* delay2 = CCDelayTime::create(2.0f);
	CCCallFuncN* call0 = CCCallFuncN::create(this,callfuncN_selector(MovingLabelLayer::onActionDown));
	spriteBack0->runAction(CCSequence::create(moveto0,delay0,call0,NULL));
	spriteBack1->runAction(CCSequence::create(moveto1,delay1,NULL));
	label->runAction(CCSequence::create(moveto2,delay2,NULL));

    return true;
}

void MovingLabelLayer::onActionDown(CCNode* obj)
{
	this->removeFromParentAndCleanup(true);
}
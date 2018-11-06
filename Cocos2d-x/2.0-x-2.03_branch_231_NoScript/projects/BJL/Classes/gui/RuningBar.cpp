//
//  MatchError.cpp
//  Game
//
//  Created by ÂÞÃô on 13-7-10.
//
//

#include "RuningBar.h"
#include "configMgr/ConfigMgr.h"

RuningBar::RuningBar()
{
    
}

RuningBar::~RuningBar()
{
    
}

bool RuningBar::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->setContentSize(CCSizeMake(winSize.width * 0.53,20));
	this->setPosition(ccp(winSize.width * 0.24,winSize.height * 0.77 - 3));
	labelRunHole = CCLabelTTF::create(ConfigMgr::instance()->text("t404"),"",15);
	labelRunHole->setColor(ccc3(255,255,255));
	labelRunHole->setPosition(ccp(winSize.width * 1.3,10));
	addChild(labelRunHole);
	CCMoveTo* moveTo = CCMoveTo::create(20.0f,CCPoint(-winSize.width * 0.4,labelRunHole->getPositionY()));
	cocos2d::CCActionInterval * actionSeq = (cocos2d::CCActionInterval *)CCSequence::create(moveTo,CCCallFuncN::create(this,callfuncN_selector(RuningBar::reSertRunHolePosition)),NULL);
	CCRepeatForever* actionFor = CCRepeatForever::create(actionSeq);
	labelRunHole->runAction(actionFor);
    return true;
}

void RuningBar::reSertRunHolePosition(CCNode* node)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	labelRunHole->setPosition(ccp(winSize.width * 1.4,10));
}

void RuningBar::visit()
{
	CCPoint screenPos = this->convertToWorldSpace(CCPointZero);

	float scaleX = this->getScaleX();
	float scaleY = this->getScaleY();

	for (CCNode *p = m_pParent; p != NULL; p = p->getParent()) {
		scaleX *= p->getScaleX();
		scaleY *= p->getScaleY();
	}

	//CCRect frame =CCRectMake(screenPos.x, screenPos.y, m_obContentSize.width*scaleX, m_obContentSize.height*scaleY);

	//glEnable(GL_SCISSOR_TEST);
	//CCEGLView::sharedOpenGLView()->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
	//CCLayer::visit();
	//glDisable(GL_SCISSOR_TEST);
}

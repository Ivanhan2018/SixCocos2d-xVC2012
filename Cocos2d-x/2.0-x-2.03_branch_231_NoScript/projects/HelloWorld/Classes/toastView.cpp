//
//  toastView.cpp
//  XXDDZ
//
//  Created by Eldder on 14-1-23.
//
//

#include "toastView.h"


#include "toastView.h"

XYToast::XYToast()
{
}

XYToast::~XYToast()
{
}

bool XYToast::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)));//ccc4(0, 0, 0, 125)
        visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        origin = CCDirector::sharedDirector()->getVisibleOrigin();
        //====================================
        bg = CCScale9Sprite::create("toast_bg.png");
        bg->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+320*visibleSize.height/960));
        //============================
        bRet = true;
    } while (0);
    return bRet;
}


void XYToast::onExit()
{
    CCLayerColor::onExit();
}

void XYToast::initToast( string msg,float time )
{
    CCLabelTTF* pLabel = CCLabelTTF::create(msg.c_str(), "Arial", 21);
    pLabel->setColor(ccWHITE);
    bg->setContentSize(CCSizeMake(pLabel->getContentSize().width+10,pLabel->getContentSize().height+10));
    bg->addChild(pLabel, 1);
    this->addChild(bg,10);
    
     pLabel->setPosition(ccp(bg->getContentSize().width/2,bg->getContentSize().height/2));
    //pLabel->setPosition(ccp(bg->getContentSize().width/2,bg->getContentSize().height/2));
    pLabel->runAction(CCSequence::create(CCFadeIn::create(time/5),
                                         CCDelayTime::create(time/5*3),CCFadeOut::create(time/5),NULL));
    bg->runAction(CCSequence::create(CCFadeIn::create(time/5),
                                     CCDelayTime::create(time/5*3),CCFadeOut::create(time/5),
                                     CCCallFunc::create(this,callfunc_selector(XYToast::removeSelf)),NULL));
    //=========================
    //this->scheduleOnce(schedule_selector(XYToast::removeSelf),time);
}

void XYToast::removeSelf()
{
    this->removeFromParentAndCleanup(true);
}
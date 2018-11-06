//
//  DDDMessageBox.cpp
//  XXDZPK
//
//  Created by XXY on 13-11-23.
//
//



#include "DDDMessageBox.h"
#include "StaticProperty.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

void DDDLayer::DistoryMessageBox(float dt/*CCObject *pSender*/){
    if (!MsgBg) {
        return;
    }
    MsgBg->removeFromParentAndCleanup(true);
    MsgBg = NULL;
}

void DDDLayer::DistoryRollMessageBox(CCObject *pSender){
    CCSprite *sender = (CCSprite *)pSender;
    sender->removeFromParentAndCleanup(true);
}

void DDDLayer::ShowMessage(const wchar_t *tipMsg, float delay){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    if (MsgBg) {
        return;
    }
    MsgBg = CCSprite::create("square_new_tip.png");
    MsgBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(MsgBg,100);
    // 文字内容
    CCLabelTTF *lab = CCLabelTTF::create(WStrToUTF8(tipMsg).c_str(), "Arial", 30,CCSizeMake(250, 240), kCCTextAlignmentLeft);
    lab->setColor(ccBLACK);
    lab->setPosition(ccp(232, 110));
    MsgBg->addChild(lab);
    
    
    CCMenu *AlertMenu = CCMenu::create();
    CCMenuItemImage *itemCover = CCMenuItemImage::create("gameBack.png", "gameBack.png");
    itemCover->setTarget(this, menu_selector(DDDLayer::CoverButtonClicked));
    itemCover->setPosition(ccp(MsgBg->getContentSize().width/2, MsgBg->getContentSize().height/2));
    itemCover->setOpacity(0);
    AlertMenu->addChild(itemCover);
    
    AlertMenu->setPosition(CCPointZero);
    MsgBg->addChild(AlertMenu,1);
    
    this->scheduleOnce(schedule_selector(DDDLayer::DistoryMessageBox), delay);
}

#pragma mark 展示消息 消息 �?发送�?
//展示消息 消息 �?发送�?
void DDDLayer::ShowRollMessage(const wchar_t *tipSender, const wchar_t *tipMsg, DDDLayerRollMessageDirection eDirection/* = DDDRollDirectionNone*/){
    MessageOnRoll = true;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize MsgSize;
    
    CCSprite *rollTipbg = CCSprite::create("main_rolltip.png");
    rollTipbg->setPosition(ccp(size.width/2, -300));
    rollTipbg->setOpacity(0);
    
    CCSprite *rollTip = CCSprite::create("main_rolltip.png");
    rollTip->setPosition(ccp(200, 20));
    rollTipbg->addChild(rollTip);
    
    this->addChild(rollTipbg,100);
    
    // 文字内容
    CCLabelTTF *SenderLab = CCLabelTTF::create(WStrToUTF8(tipSender).c_str(), "Arial", 20);
    SenderLab->setColor(ccBLACK);
    SenderLab->setPosition(ccp(200, 20));
    rollTipbg->addChild(SenderLab);
    
    // 文字内容
    CCLabelTTF *TipLab = CCLabelTTF::create(WStrToUTF8(L"  �?�?").c_str(), "Arial", 20);
    TipLab->setColor(ccBLACK);
    TipLab->setPosition(ccp(200, 20));
    rollTipbg->addChild(TipLab);
    
    // 文字内容
    CCLabelTTF *lab = CCLabelTTF::create(WStrToUTF8(tipMsg).c_str(), "Arial", 20);
    lab->setColor(ccBLACK);
    lab->setPosition(ccp(200, 20));
    rollTipbg->addChild(lab);
    
     MsgSize = CCSizeMake(SenderLab->getContentSize().width + lab->getContentSize().width + TipLab->getContentSize().width, 40);
    
    SenderLab->setPosition(ccp(200 - MsgSize.width/2 + SenderLab->getContentSize().width/2, 20));
    
    TipLab->setPosition(ccp(200 - MsgSize.width/2 + SenderLab->getContentSize().width + TipLab->getContentSize().width/2, 20));
    
    lab->setPosition(ccp(200 - MsgSize.width/2 + SenderLab->getContentSize().width + TipLab->getContentSize().width + lab->getContentSize().width/2, 20));
    
    if (MsgSize.width + 40 > rollTip->getContentSize().width) {
        rollTip->setScaleX((MsgSize.width +40.0)/ rollTip->getContentSize().width);
    }
    
    this->DisplayRollMessage(rollTipbg, MsgSize, eDirection);
}

#pragma mark (未实�? 展示消息 聊天消息 发送�?接受�?消息内容
//展示消息 聊天消息 发送�?接受�?消息内容
void DDDLayer::ShowRollMessage(const wchar_t *tipSender, const wchar_t *tipTo, const wchar_t *tipMsg, DDDLayerRollMessageDirection eDirection/* = DDDRollDirectionNone*/){
    
}

#pragma mark  展示消息 消息内容 
//展示消息 消息内容 
void DDDLayer::ShowRollMessage(const wchar_t *tipMsg, DDDLayerRollMessageDirection eDirection/* = DDDRollDirectionNone*/){
    MessageOnRoll = true;
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize MsgSize;
    
    CCSprite *rollTipbg = CCSprite::create("main_rolltip.png");
     rollTipbg->setPosition(ccp(size.width/2, -300));
    rollTipbg->setOpacity(0);
    
    CCSprite *rollTip = CCSprite::create("main_rolltip.png");
    rollTip->setPosition(ccp(200, 20));
    rollTipbg->addChild(rollTip);
    
    this->addChild(rollTipbg,100);
    
    // 文字内容
    CCLabelTTF *lab = CCLabelTTF::create(WStrToUTF8(tipMsg).c_str(), "Arial", 20);
    lab->setColor(ccBLACK);
    lab->setPosition(ccp(200, 20));
    rollTipbg->addChild(lab);
    
    if (lab->getContentSize().width +40 > rollTip->getContentSize().width) {
        rollTip->setScaleX((lab->getContentSize().width +40.0)/ rollTip->getContentSize().width);
    }
    
    MsgSize = CCSizeMake(lab->getContentSize().width+40, 40);
    
    this->DisplayRollMessage(rollTipbg, MsgSize, eDirection);
}

//private
void DDDLayer::DisplayRollMessage(CCSprite *MsgLayer, CCSize MsgSize, DDDLayerRollMessageDirection eDirection){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    switch (eDirection) {
        case DDDRollDirectionNone:
        {//高度 555 水平 从右向左移动出界
            MsgLayer->setPosition(ccp(size.width/2+MsgSize.width, 555));
            MsgLayer->runAction(static_cast<CCSequence *>(CCSequence::create(CCMoveTo::create((size.width/2+MsgSize.width*2)/200.0, ccp(-MsgSize.width,555)), CCCallFuncO::create(this, callfuncO_selector(DDDLayer::DistoryRollMessage), MsgLayer), NULL)));
        }
            break;
        case DDDRollDirectionHorizontal://水平
        {
            
        }
            break;
        case DDDRollDirectionVertical://竖直
        {
            MsgLayer->setPosition(ccp(size.width/2, 455));
            MsgLayer->runAction(static_cast<CCSequence *>(CCSequence::create(CCMoveTo::create(1.2f, ccp(size.width/2,555)), CCCallFuncO::create(this, callfuncO_selector(DDDLayer::DistoryRollMessage), MsgLayer), NULL)));
        }
            break;
        default:
            break;
    }
    
}

//private
void DDDLayer::DistoryRollMessage(CCObject *pSender){
    MessageOnRoll = false;
    CCSprite *sender = (CCSprite *)pSender;
    sender->removeFromParentAndCleanup(true);
}

void DDDLayer::ShowAlert(const wchar_t *tipMsg){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    MsgBg = CCSprite::create("square_new_tip.png");
    MsgBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(MsgBg,100);
    // 文字内容
    CCLabelTTF *lab = CCLabelTTF::create(WStrToUTF8(tipMsg).c_str(), "Arial", 30,CCSizeMake(250, 240), kCCTextAlignmentCenter);
    lab->setColor(ccBLACK);
    lab->setPosition(ccp(232, 85));
    MsgBg->addChild(lab);
    
    CCMenu *AlertMenu = CCMenu::create();
    CCMenuItemFont *itemTest = CCMenuItemFont::create(WStrToUTF8(L"测试").c_str());
    itemTest->setFontSize(35);
    
    CCMenuItemSprite *itemOk = CCMenuItemSprite::create(CCSprite::create("square_new_tip_on.png"), CCSprite::create("square_new_tip_on.png"));
    itemOk->setTarget(this, menu_selector(DDDLayer::AlertViewOKButtonClicked));
    itemOk->setPosition(ccp(132, 55));
    AlertMenu->addChild(itemOk);
    
    CCMenuItemSprite *itemCancel = CCMenuItemSprite::create(CCSprite::create("square_new_tip_off.png"), CCSprite::create("square_new_tip_off.png"));
    itemCancel->setTarget(this, menu_selector(DDDLayer::AlertViewCancelButtonClicked));
    itemCancel->setPosition(ccp(332, 55));
    AlertMenu->addChild(itemCancel);
    
    CCMenuItemImage *itemCover = CCMenuItemImage::create("gameBack.png", "gameBack.png");
    itemCover->setTarget(this, menu_selector(DDDLayer::CoverButtonClicked));
    itemCover->setPosition(ccp(MsgBg->getContentSize().width/2, MsgBg->getContentSize().height/2));
    itemCover->setOpacity(0);
    AlertMenu->addChild(itemCover);
    
    AlertMenu->setPosition(CCPointZero);
    MsgBg->addChild(AlertMenu,1);
    
}

void DDDLayer::CoverButtonClicked(CCObject *pSender){
}

void DDDLayer::AlertViewCancelButtonClicked(CCObject *pSender){
    MsgBg->removeFromParentAndCleanup(true);
}

void DDDLayer::AlertViewOKButtonClicked(CCObject *pSender){
    MsgBg->removeFromParentAndCleanup(true);
}

void  DDDLayer::showMatchMessaghe(const wchar_t *tipMSG){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    MsgBg = CCSprite::create("showtipbg.png");
    MsgBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(MsgBg,100);
    // 文字内容
    
    CCLabelTTF *lab = CCLabelTTF::create(WStrToUTF8(tipMSG).c_str(), "Arial", 30,CCSizeMake(250, 240), kCCTextAlignmentCenter);
    lab->setColor(ccBLACK);
    lab->setPosition(ccp(142, 40));
    MsgBg->addChild(lab);
    
    CCMenu *AlertMenu = CCMenu::create();
    CCMenuItemFont *itemTest = CCMenuItemFont::create(WStrToUTF8(L"测试").c_str());
    itemTest->setFontSize(35);
    
    CCMenuItemFont *itemOk = CCMenuItemFont::create(WStrToUTF8(L"确定").c_str());
    itemOk->setTarget(this, menu_selector(DDDLayer::showMatchButtonOK));
    itemOk->setPosition(ccp(132, 45));
    itemOk->setColor(ccBLACK);
    itemOk->setFontSize(35);
    AlertMenu->addChild(itemOk);
    
    CCMenuItemImage *itemCover = CCMenuItemImage::create("gameBack.png", "gameBack.png");
    itemCover->setTarget(this, menu_selector(DDDLayer::CoverButtonClicked));
    itemCover->setPosition(ccp(MsgBg->getContentSize().width/2, MsgBg->getContentSize().height/2));
    itemCover->setOpacity(0);
    AlertMenu->addChild(itemCover);
    
    AlertMenu->setPosition(CCPointZero);
    MsgBg->addChild(AlertMenu,1);
    
}

//比赛回调
void DDDLayer::showMatchButtonOK(CCObject *pSender){
    
    MsgBg->removeFromParentAndCleanup(true);
}

#pragma mark WaittingOtherPlayer

void WaittingOtherPlayer::WaitOtherPlayerEnter(CCSprite *Layer){
    DotWaitLayer = CCSprite::create("gamebg.png");
    DotWaitLayer->setOpacity(0);
    DotWaitLayer->setPosition(ccp(Layer->getContentSize().width/2, Layer->getContentSize().height/2));
    Layer->addChild(DotWaitLayer,100);
    
    for (int i = 0; i < 9; i++) {
        char asd[20];sprintf(asd, "dot_wait_0%d.png",i+1);
        CCSprite *waitDot = CCSprite::create(asd);
        waitDot->setPosition(ccp(200+i*70, 150));
        DotWaitLayer->addChild(waitDot);
        waitDot->runAction(CCSpeed::create(CCRepeatForever::create(static_cast<CCSequence *>(CCSequence::create(CCScaleBy::create(i, 1),CCMoveBy::create(0.5, ccp(0, 20)), CCMoveBy::create(0.5, ccp(0, -20)),CCScaleBy::create(8-i, 1), NULL))), 5));
    }
}

void WaittingOtherPlayer::DistoryDotWaitLayer(){
    if (!DotWaitLayer) {
        return;
    }else{
    DotWaitLayer->stopAllActions();
    DotWaitLayer->removeFromParentAndCleanup(true);
        DotWaitLayer = NULL;
    }
}




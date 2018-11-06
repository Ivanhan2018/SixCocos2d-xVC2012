//
//  DDDPokerCardSprite.cpp
//  XXDDZ
//
//  Created by XXY on 13-12-17.
//
//

#include "DDDPokerCardSprite.h"

bool PokerCard::init(){
    
#pragma mark 牌的资源初始�?    
	CCTexture2D *textureCard = CCTextureCache::sharedTextureCache()->addImage("CardNew.png");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 14; j++) {
            CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(j*90, i*120, 90, 120));
            char a[50];snprintf(a,50, "CardBig%d%d",i,j+1);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
        }
    }
    {//小王
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(0, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",4,14);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    {//大王
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(90, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",4,15);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    {//背景
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(270, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",0,14);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    {//背景
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(180, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",0,0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    return true;
}

void PokerCard::createPokerCrad(CCSprite *gameLayer){
    if (!init()) {
        return;
    }
    m_Poker_Card_Manager = CCSpriteBatchNode::create("CardNew.png");
    
    for (int i = 0; i < 3; i++) {
        m_Poker_Sprite[i] = new Poker();
        m_Poker_Sprite[i]->position = -1;
        m_Crad_Dot.insert(std::pair<int, int>(i,-1));
    }
    
    for (int i = 0; i < 20; i++) {
        
        m_Poker_Sprite[0]->CardValue[i] = 0;
        m_Poker_Sprite[0]->Card[i] = CCSprite::create("CardNew.png");
        m_Poker_Sprite[0]->Card[i]->setDisplayFrame(CCSpriteFrame::create("CardNew.png", CCRectMake(90, 480, 90, 120)));
        m_Poker_Sprite[0]->Card[i]->setPosition(ccp(480,-320));
        m_Poker_Sprite[0]->Card[i]->setScale(0.6);
        m_Poker_Sprite[0]->Card[i]->setVisible(false);
        m_Poker_Card_Manager->addChild(m_Poker_Sprite[0]->Card[i],1, i+100);
        
        
        int idx = (i/9)*9+(8-i%9);
        if (i < 18) {
            idx = (i/9)*9+(8-i%9);
        }else{
            idx = (i/9)*9+(1-i%9);
        }
        
        int flg = i;
        if (i >17) {
            flg = i+7;
        }

        m_Poker_Sprite[1]->CardValue[idx] = 0;
        m_Poker_Sprite[1]->Card[idx] = CCSprite::create("CardNew.png");
        m_Poker_Sprite[1]->Card[idx]->setDisplayFrame(CCSpriteFrame::create("CardNew.png", CCRectMake(90, 480, 90, 120)));
        m_Poker_Sprite[1]->Card[idx]->setPosition(ccp((flg%9) * DotX + DotRight, DotHeight - (idx/9) * DotY));
        m_Poker_Sprite[1]->Card[idx]->setScale(0.6);
        m_Poker_Sprite[1]->Card[idx]->setVisible(false);
        m_Poker_Card_Manager->addChild(m_Poker_Sprite[1]->Card[idx],i+1,i+200);
        
        m_Poker_Sprite[2]->CardValue[i] = 0;
        m_Poker_Sprite[2]->Card[i] = CCSprite::create("CardNew.png");
        m_Poker_Sprite[2]->Card[i]->setDisplayFrame(CCSpriteFrame::create("CardNew.png", CCRectMake(90, 480, 90, 120)));
        
        m_Poker_Sprite[2]->Card[i]->setPosition(ccp((i%9) * DotX + DotLeft, DotHeight - (i/9) * DotY));
        m_Poker_Sprite[2]->Card[i]->setScale(0.6);
        m_Poker_Sprite[2]->Card[i]->setVisible(false);
        m_Poker_Card_Manager->addChild(m_Poker_Sprite[2]->Card[i],i+1,i+300);
    }
    gameLayer->addChild(m_Poker_Card_Manager,2);
}

void PokerCard::setUserSelfIndexForCurrentGame(int index){
    if (index <3 && index+1>0) {
        m_Crad_Dot[index] = 0;
        m_Crad_Dot[(index + 1)%3] = 1;
        m_Crad_Dot[(index + 2)%3] = 2;
    }
}

void PokerCard::ShowPlayerOutCard(bool isSelf, _WORD_ index, _BYTE_ outCardNum, _BYTE_ outCardData[20]){
    if (m_Crad_Dot[index] == 0) {
        
    }else{
         ShowPlayerOutCard(index, outCardNum, outCardData);
    }
}

void PokerCard::ShowGameOverCard(_BYTE_ cbCardCount[GAME_PLAYER], _BYTE_ cbHandCardData[FULL_COUNT]){
    
    int cardNum = 0;
    for (int i = 0; i < GAME_PLAYER; i++) {
        if (cbCardCount[i] == 0) {
            continue;
        }
        _BYTE_ outCardData[20] = {0};
        memcpy(outCardData, cbHandCardData+cardNum, sizeof(_BYTE_)*cbCardCount[i]);
        ShowPlayerOutCard(i, cbCardCount[i], outCardData);
        cardNum += cbCardCount[i];
    }
}

void PokerCard::MissPlayerOutCard(bool isClear, _WORD_ index, bool clearSelf){
    if (isClear) {
        for (int i = 0; i < MAX_COUNT; i++) {
            m_Poker_Sprite[0]->Card[i]->setVisible(false);
            m_Poker_Sprite[1]->Card[i]->setVisible(false);
            m_Poker_Sprite[2]->Card[i]->setVisible(false);
        }
        return;
    }
    
    if (clearSelf) {
        for (int i = 0; i < MAX_COUNT; i++) {
            m_Poker_Sprite[0]->Card[i]->setVisible(false);
        }
    }
    
    if (index+1 > 0 && index < 3) {
        int idx = m_Crad_Dot[idx];
        for (int i = 0; i < MAX_COUNT; i++) {
            m_Poker_Sprite[index]->Card[i]->setVisible(false);
        }
    }
}

void PokerCard::ShowPlayerOutCard(_WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]){
    int idx = m_Crad_Dot[index];
    switch (idx) {
        case 0:
        {
            ShowPlayerOutCard_Self(true, idx, outCardNum, outCardData);
        }
            break;
        case 1:
        {
            ShowPlayerOutCard_right(true, idx, outCardNum, outCardData);
        }
            break;
        case 2:
        {
            ShowPlayerOutCard_Left(true, idx, outCardNum, outCardData);
        }
            break;
        default:
        {
            //CCLog("无效的出排位�?);
        }
            break;
    }
}
    
bool PokerCard::ShowPlayerOutCard_Self(bool isSelf, _WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]){
#pragma mark 显示用户自己出的�?    
	for (int i = 0; i < outCardNum; i++) {
        //CCLog("绘制出牌到第 %d �?,i);
        char asd[50];snprintf(asd, 50, "CardBig%d%d",(outCardData[i]/16),(outCardData[i]%16));
        m_Poker_Sprite[0]->Card[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
        m_Poker_Sprite[0]->Card[i]->setPosition(ccp(i*25 +480 - outCardNum/2*25,225));
        CCLog("用户出牌 %d" ,i );
        m_Poker_Sprite[0]->Card[i]->setVisible(true);
    }
    for (int i = outCardNum; i < MAX_COUNT; i++) {
        m_Poker_Sprite[0]->Card[i]->setVisible(false);
    }
    return true;
}

bool PokerCard::ShowPlayerOutCard_Left(bool isSelf, _WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]){

    for (int i = 0; i < outCardNum; i++) {
        //CCLog("绘制出牌到第 %d �?,i);
        char asd[50];snprintf(asd, 50, "CardBig%d%d",(outCardData[i]/16),(outCardData[i]%16));
        m_Poker_Sprite[2]->Card[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
        m_Poker_Sprite[2]->Card[i]->setVisible(true);
    }
    for (int i = outCardNum; i < MAX_COUNT; i++) {
        m_Poker_Sprite[2]->Card[i]->setVisible(false);
    }
    return true;
}

bool PokerCard::ShowPlayerOutCard_right(bool isSelf, _WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]){

    for (int i = 0; i < outCardNum; i++) {
        //CCLog("绘制出牌到第 %d �?,i);
        char asd[50];snprintf(asd, 50, "CardBig%d%d",(outCardData[outCardNum-i-1]/16),(outCardData[outCardNum-i-1]%16));
        m_Poker_Sprite[1]->Card[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
        m_Poker_Sprite[1]->Card[i]->setVisible(true);
    }
    for (int i = outCardNum; i < MAX_COUNT; i++) {
        
        m_Poker_Sprite[1]->Card[i]->setVisible(false);
    }

    return true;
}

//
//  DDDNumberLable.cpp
//  XXDZPK
//
//  Created by XXY on 14-1-13.
//
//

#include "DDDNumberLable.h"

DDDNumberLab* DDDNumberLab::create()
{
    DDDNumberLab *pobSprite = new DDDNumberLab();
    
    if (pobSprite)
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void DDDNumberLab::initNumber(){
    if (!m_SpriteBatchNode) {
        m_SpriteBatchNode = CCSpriteBatchNode::create("numberTest3.png",10);
        this->addChild(m_SpriteBatchNode);
    }
    for (int i = 0; i < 6; i++) {
        m_NumArr[i] = CCSprite::create("numberTest3.png", CCRectMake(12*60, 0, 60, 90));
        m_NumArr[i]->setPosition(ccp(30+i*60, 45));
        m_NumArr[i]->setVisible(false);
        m_SpriteBatchNode->addChild(m_NumArr[i]);
    }
    
    m_NumArr[6] = CCSprite::create("numberTest3.png", CCRectMake(13*60, 0, 60, 90));
    m_NumArr[6]->setPosition(ccp(30+6*60, 45));
    m_NumArr[6]->setVisible(false);
    m_SpriteBatchNode->addChild(m_NumArr[6]);
}

void DDDNumberLab::setNumberSize(float size){
    m_NumberSize = size/60.0;
    this->setScale(m_NumberSize);
}

float DDDNumberLab::getNumberSize(){return 0;}

void DDDNumberLab::setMinus(bool flg){
    m_NumArr[6]->setVisible(false);
    m_Minus = flg;
}

bool DDDNumberLab::getMinus(){
    if (m_Minus) {
        for (int i = 0; i < 6; i++) {
            m_NumArr[i]->setPosition(ccp(90+i*60, 45));
        }
        
        m_NumArr[6]->setPosition(ccp(30, 45));
        m_NumArr[6]->setVisible(true);
    }
    
    return m_Minus = false;
}

void DDDNumberLab::setNumber(long long number){
    if (number < 0) {
        setMinus(true);
        number = -1*number;
    }else{
        setMinus(false);
    }
    
    CCLog("获取数字%lld",number);
    if (number <= MIN_NUM_FLAG) {
        Number_Length_Less(number);
    }else if (number/MAX_NUM_VALVE < MAX_NUM_VALVE) {
        int intgerPart = number/MAX_NUM_VALVE;
        int floatPart = number%MAX_NUM_VALVE;
        CCLog("获取数字 intgerPart %d",intgerPart);
        CCLog("获取数字 floatPart %d",floatPart);
        Number_For_TwoPart(intgerPart, floatPart, MARK_WAN);
    }else if (number/(MAX_NUM_VALVE*MAX_NUM_VALVE) < MAX_NUM_VALVE){
        number = number/MAX_NUM_VALVE;
        int intgerPart = number/MAX_NUM_VALVE;
        int floatPart = number%MAX_NUM_VALVE;
        CCLog("获取数字 intgerPart %d",intgerPart);
        CCLog("获取数字 floatPart %d",floatPart);
        Number_For_TwoPart(intgerPart, floatPart, MARK_YI);
    }else{
        Number_Length_Over();
    }
    
    getMinus();
}

void DDDNumberLab::Number_Length_Over(){
    for (int i = 0; i < 6; i++) {
        if (m_NumArr[i]) {
            m_NumArr[i]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(12*60, 0, 60, 90)));
            m_NumArr[i]->setPosition(ccp(30+i*60, 45));
        }else{
            m_NumArr[i] = CCSprite::create("numberTest3.png", CCRectMake(12*60, 0, 60, 90));
            m_NumArr[i]->setPosition(ccp(30+i*60, 45));
            m_SpriteBatchNode->addChild(m_NumArr[i]);
        }
    }
}
void DDDNumberLab::Number_Length_Less(long long num){
    int flg = 0;
    int p_NumArr[6] = {0};
    while(true){
        int numpot = num%10;
        p_NumArr[flg] = numpot;
        
        if (num/10 > 0) {
            num = num/10;
            flg++;
        }else{
            break;
        }
    }
    for (int i = 0; i <= flg; i++) {
        if (m_NumArr[i]) {
            m_NumArr[i]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(p_NumArr[flg-i]*60, 0, 60, 90)));
        }else{
            m_NumArr[flg] = CCSprite::create("numberTest3.png", CCRectMake(p_NumArr[flg-i]*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[flg]);
        }
        m_NumArr[i]->setPosition(ccp(30+i*60, 45));
        m_NumArr[i]->setVisible(true);
    }
    
    if (flg == 5) {
        return;
    }else{
        for (int i = flg+1; i < 6; i++) {
            if (m_NumArr[i]) {
                m_NumArr[i]->setVisible(false);
            }
        }
    }
}

//整数部分�?000�?999之间�?
void DDDNumberLab::Number_Intget_Max(long long num, int Mark){
    int flg = 1000;
    for (int i = 0; i < 4; i++) {
        if (m_NumArr[i]) {
            m_NumArr[i]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake((num/flg)*60, 0, 60, 90)));
        }else{
            m_NumArr[i] = CCSprite::create("numberTest3.png", CCRectMake((num/flg)*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[i]);
        }
        m_NumArr[i]->setPosition(ccp(30+i*60, 45));
        num = num%flg;
        flg = flg/10;
    }
    
    if (m_NumArr[4]) {
        m_NumArr[4]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(Mark*60, 0, 60, 90)));
    }else{
        m_NumArr[4] = CCSprite::create("numberTest3.png", CCRectMake(Mark*60, 0, 60, 90));
        m_SpriteBatchNode->addChild(m_NumArr[4]);
    }
    m_NumArr[4]->setPosition(ccp(30+4*60, 45));
    
    for (int i = 0; i < 5; i++) {
        if (m_NumArr[i]) {
            m_NumArr[i]->setVisible(true);
        }
    }
    if (m_NumArr[5]) {
        m_NumArr[5]->setVisible(false);
    }
}

//整数部分�?00�?99之间�?
int DDDNumberLab::Number_Intget_Less(long long num){
    if (num/100 > 0) {
        if (m_NumArr[0]) {
            m_NumArr[0]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake((num/100)*60, 0, 60, 90)));
        }else{
            m_NumArr[0] = CCSprite::create("numberTest3.png", CCRectMake((num/100)*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[0]);
        }
        m_NumArr[0]->setPosition(ccp(30+0*60, 45));
        m_NumArr[0]->setVisible(true);
        num = num%100;
        if (m_NumArr[1]) {
            m_NumArr[1]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake((num/10)*60, 0, 60, 90)));
        }else{
            m_NumArr[1] = CCSprite::create("numberTest3.png", CCRectMake((num/10)*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[1]);
        }
        m_NumArr[1]->setPosition(ccp(30+1*60, 45));
        m_NumArr[1]->setVisible(true);
        num = num%10;
        if (m_NumArr[2]) {
            m_NumArr[2]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(num*60, 0, 60, 90)));
        }else{
            m_NumArr[2] = CCSprite::create("numberTest3.png", CCRectMake(num*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[2]);
        }
        m_NumArr[2]->setPosition(ccp(30+2*60, 45));
        m_NumArr[2]->setVisible(true);
        return 3;
    }else if(num/10 > 0){
        if (m_NumArr[0]) {
            m_NumArr[0]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake((num/10)*60, 0, 60, 90)));
        }else{
            m_NumArr[0] = CCSprite::create("numberTest3.png", CCRectMake((num/10)*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[0]);
        }
        m_NumArr[0]->setPosition(ccp(30+0*60, 45));
        m_NumArr[0]->setVisible(true);
        num = num%10;
        if (m_NumArr[1]) {
            m_NumArr[1]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(num*60, 0, 60, 90)));
        }else{
            m_NumArr[1] = CCSprite::create("numberTest3.png", CCRectMake(num*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[1]);
        }
        m_NumArr[1]->setPosition(ccp(30+1*60, 45));
        m_NumArr[1]->setVisible(true);
        return 2;
    }else{
        if (m_NumArr[0]) {
            m_NumArr[0]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(num*60, 0, 60, 90)));
        }else{
            m_NumArr[0] = CCSprite::create("numberTest3.png", CCRectMake(num*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[0]);
        }
        m_NumArr[0]->setPosition(ccp(30+0*60, 45));
        m_NumArr[0]->setVisible(true);
        return 1;
    }
}

//小数部分
void DDDNumberLab::Number_Float_Less(long long num, int dotIdx, int Mark){
    
    if (m_NumArr[dotIdx]) {
        m_NumArr[dotIdx]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(MARK_Dot*60, 0, 60, 90)));
    }else{
        m_NumArr[dotIdx] = CCSprite::create("numberTest3.png", CCRectMake(MARK_Dot*60, 0, 60, 90));
        m_SpriteBatchNode->addChild(m_NumArr[dotIdx]);
    }
    m_NumArr[dotIdx]->setPosition(ccp(30+dotIdx*60, 45));
    
    int flg = 1000;
    for (int i = dotIdx+1; i<5; i++) {
        if (m_NumArr[i]) {
            m_NumArr[i]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake((num/flg)*60, 0, 60, 90)));
        }else{
            m_NumArr[i] = CCSprite::create("numberTest3.png", CCRectMake((num/flg)*60, 0, 60, 90));
            m_SpriteBatchNode->addChild(m_NumArr[i]);
        }
        m_NumArr[i]->setPosition(ccp(30+i*60, 45));
        num = num%flg;
        flg = flg/10;
    }
    
    if (m_NumArr[5]) {
        m_NumArr[5]->setDisplayFrame(CCSpriteFrame::create("numberTest3.png", CCRectMake(Mark*60, 0, 60, 90)));
    }else{
        m_NumArr[5] = CCSprite::create("numberTest3.png", CCRectMake(Mark*60, 0, 60, 90));
        m_SpriteBatchNode->addChild(m_NumArr[5]);
    }
    m_NumArr[5]->setPosition(ccp(30+5*60, 45));
    for (int i = 0; i < 6; i++) {
        if (m_NumArr[i]) {
            m_NumArr[i]->setVisible(true);
        }
    }
}

void DDDNumberLab::Number_For_TwoPart(int intgerPart, int floatPart, int Mark){
    
    CCLog("获取数字 intgerPart %d",intgerPart);
    CCLog("获取数字 floatPart %d",floatPart);
    
    if (intgerPart/MIN_NUM_CUT_FLG > 0) {
        Number_Intget_Max(intgerPart, Mark);
    }else{
        int flg = Number_Intget_Less(intgerPart);
        Number_Float_Less(floatPart, flg, Mark);
    }
}











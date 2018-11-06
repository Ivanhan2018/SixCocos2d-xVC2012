//
//  CardTouchLayer.cpp
//  TouchCardDemo
//
//  Created by ChengLin on 13-11-22.
//
//

#include "CardTouchLayer.h"
#include "StaticProperty.h"



CCPoint outcardPostion[20];

bool CardTouchLayer::init()
{
    if ( !CCLayer::init())
    {
        return false;
    }
    // 鑾峰彇鍦烘櫙澶у皬
    size = CCDirector::sharedDirector()->getWinSize();
    
#pragma mark 鐗岀殑璧勬簮鍒濆鍖?    
	CCTexture2D *textureCard = CCTextureCache::sharedTextureCache()->addImage("CardNew.png");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 14; j++) {
            CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(j*90, i*120, 90, 120));
            char a[50];snprintf(a,50, "CardBig%d%d",i,j+1);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
        }
    }
    {//灏忕帇
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(0, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",4,14);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    {//澶х帇
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(90, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",4,15);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    {//鑳屾櫙
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(180, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",0,0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    {//鑳屾櫙
        CCSpriteFrame *famBig = CCSpriteFrame::createWithTexture(textureCard, CCRectMake(270, 480, 90, 120));
        char a[50];snprintf(a,50, "CardBig%d%d",0,14);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(famBig, a);
    }
    
    
    // 璁板綍閫変腑鐨勭墝
    currentIndex = 20;
    // 鏃堕挓鏄惁寮€鍚?    
	timerIsOpen = true;
    
    // 鍒涘缓涓€涓儗鏅?    
	cardBg = CCSprite::create("userhandcardbg.png");
    cardBg->setPosition(ccp(size.width/2, selfCardMaginBottom));
    cardBg->setOpacity(0);
    this->addChild(cardBg);
    
    // 鍒涘缓婊戝姩閫夋嫨
    {
        slider = CCControlSlider::create("userhandcardbg.png", "userhandcardbg.png", "handCover.png");
        slider->setPosition(ccp(size.width/2+10, selfCardMaginBottom));
        slider->setOpacity(0);
        //璁剧疆婊戝姩鏉℃渶澶у€?        
		slider->setMaximumValue(21);
        //璁剧疆婊戝姩鏉℃渶灏忓€?        
		slider->setMinimumValue(0);
        //璁剧疆鐩戝惉锛屽綋婊戝姩鏉＄殑鍊煎彂鐢熷彉鍖栧悗锛屼細鍝嶅簲valueChanged鍑芥暟
        //slider->addTargetWithActionForControlEvents(this, cccontrol_selector(CardTouchLayer::valueChange), CCControlEventValueChanged);
        cardBg->addChild(slider);
    }
    
    // 鍒涘缓鐗岀殑绮剧伒
    for(int i=0;i < MAX_COUNT;i++){
        // 鍒濆鍖栨墜鐗屾暟鎹?        
		handCardsData[i] = CARD_NULL;
        // 鍒涘缓鐗岀殑绮剧伒
        cardSprites[i] = CCSprite::create();
        cardSprites[i]->setPosition(ccp(45 + i*selfCardSpacing , selfCardMaginBottom));
        char asd[50];snprintf(asd, 50, "CardBig%d%d",(handCardsData[i]/16),(handCardsData[i]%16));
        cardSprites[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
        cardSprites[i]->setVisible(false);
        cardBg->addChild(cardSprites[i]);
        // 鍒濆鍖栫墝鐨勯€変腑鏍囧織
        cardChosedState[i] = false;
    }
    
    return true;
}

// 閲嶆柊鍒濆鍖
void CardTouchLayer::reInit(){
    
    // 鏃堕挓鏄惁寮€鍚?    
	timerIsOpen = true;
    // 鐢ㄦ埛鎵嬬墝鏁伴噺
    handCardsCount = 0;
    // 鍒濆鍖栨墜鐗?    
	for(int i=0;i < MAX_COUNT;i++){
        // 鍒濆鍖栨墜鐗屾暟鎹?        
		handCardsData[i] = CARD_NULL;
        char asd[50];snprintf(asd, 50, "CardBig%d%d",(handCardsData[i]/16),(handCardsData[i]%16));
        cardSprites[i]->setPosition(ccp(45 + i*selfCardSpacing , selfCardMaginBottom));
        cardSprites[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
        
        cardSprites[i]->setVisible(false);
        // 鍒濆鍖栫墝鐨勯€変腑鏍囧織
        cardChosedState[i] = false;
    }
}

void CardTouchLayer::LoadCardData(BYTE cardData[MAX_COUNT],BYTE cardCount){
	if(cardCount >MAX_COUNT)
	{
		return;
	}
    memcpy(this->handCardsData, cardData, sizeof(BYTE) * cardCount);
    
    handCardsCount = cardCount;
    
    this->sortHandCards();
}

// 璁剧疆鐗岀殑鍒濆€?
void CardTouchLayer::initCardData(BYTE cardData[MAX_COUNT],BYTE cardCount){
	if(cardCount >MAX_COUNT)
	{
		return;
	}
    memcpy(this->handCardsData, cardData, sizeof(BYTE) * cardCount);
    // 閲嶇粯鐗岀殑鐣岄潰
    for(int i=0;i < MAX_COUNT;i++){
        char asd[50];snprintf(asd, 50, "CardBig%d%d",(handCardsData[i]/16),(handCardsData[i]%16));
        cardSprites[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
    }
}


// 鏄剧ず鎸囧畾鐨勪竴寮犳墜鐗?
void CardTouchLayer::showHandCardByIndex(int index){
    // 璁剧疆瀵瑰簲涓嬫爣鐨勭墝鏄剧ず
    cardSprites[index]->setVisible(true);
    // 绱姞鎵嬬墝鏁伴噺
    handCardsCount++;
    // 璁剧疆浣嶇疆鍋忕Щ
    cardBg->setPosition(ccp(size.width/2 + getOffsetX(),cardBg->getPositionY())) ;
}

// 寮硅捣鎸囧畾鐨勪竴寮犳墜鐗?
void CardTouchLayer::upHandCardByInfex(int index){
    // 鑾峰彇瀵瑰簲鐨勭簿鐏?    
	cardSprites[index]->setPosition(ccp(cardSprites[index]->getPositionX(), selfCardMaginBottomUp));
    // 鏀瑰彉閫変腑鐗岀殑鐘舵€?    
	cardChosedState[index] = true;
}

// 鑾峰彇閫変腑鐨勭墝鐨勬暟鎹?
void CardTouchLayer::getSelectedCardData(tagOutCardResult &outCardData){
    memset(&outCardData, 0, sizeof(tagOutCardResult));
    int j=0;
    for(int i=0;i<MAX_COUNT;i++){
        if(cardChosedState[i]){
            outCardData.cbResultCard[j++] = handCardsData[i];
            outCardData.cbCardCount++;
        }
    }
}

// 鍑虹墝
bool CardTouchLayer::outCards(tagOutCardResult &outCardData){
    memset(&outCardData, 0, sizeof(tagOutCardResult));
    for (int i = 0; i < 20; i++) {
        outcardPostion[i].x  = 0;
        outcardPostion[i].y = 0;
    }
    
    float BGofCrad = cardBg->getPositionX() - 480;
    
    
    int j=0;
    for(int i=0;i<MAX_COUNT;i++){
        if(cardChosedState[i]){
            
            
            outcardPostion[j].x = cardSprites[i]->getPositionX()+BGofCrad;
            outcardPostion[j].y = 130;
            outCardData.cbResultCard[j++] = handCardsData[i];
            outCardData.cbCardCount++;
            // 娓呴櫎鏁版嵁
            // 鍒囨崲鐗岀殑鐘舵€?            
			handCardsData[i] = CARD_NULL;
            this->changeCardState(i);
        }
    }
    
    //GameAnimationLayer::shareGameAnimation()->outCard_Animation(outCardData.cbCardCount, outCardData.cbResultCard, outcardPostion);
    
    
    // 鏇存柊鎵嬬墝鏁伴噺
    this->handCardsCount -= outCardData.cbCardCount;
    // 鎺掑簭
    this->sortHandCards();
    return true;
}

// 涓嶅嚭
void CardTouchLayer::notOutCards(){
    for(int i=0;i<MAX_COUNT;i++){
        if(cardChosedState[i]){
            // 鍒囨崲鐗岀殑鐘舵€?            
			this->changeCardState(i);
        }
    }
}

void CardTouchLayer::valueChange()
{
    int cardIndex = (int)slider->getValue();
    CCLog("楠岃瘉鏈夋晥鎬?%d", cardIndex);
    // 楠岃瘉鏈夋晥鎬?    
	if(cardIndex > handCardsCount){
        return;
    }else if(cardIndex == handCardsCount){
        cardIndex = handCardsCount-1;
        if (cardIndex < 0) {
            return;
        }
    }
    
    // 鍒ゆ柇閫夋嫨鐨勬槸鍚︽敼鍙?    
	if(currentIndex != cardIndex){
        // 璁板綍閫変腑鐨勪綅缃?        
		currentIndex = cardIndex;
        // 鏀瑰彉琚€変腑鐗岀殑鐘舵€?        
		this->changeCardState(cardIndex);
    }
    slider->setValue(21);
}

// 鏀瑰彉琚€変腑鐗岀殑鐘舵€?
void CardTouchLayer::changeCardState(int cardIndex){
    // 鍒ゆ柇褰撳墠鐗屾槸鍚﹂殣钘?    
	if(!cardSprites[cardIndex]->isVisible()) return;
    
    // 鍒ゆ柇褰撳墠琚€変腑鐗岀殑鐘舵€?    
	if(cardChosedState[cardIndex]){
        // 鑾峰彇瀵瑰簲鐨勭簿鐏?        
		cardSprites[cardIndex]->setPosition(ccp(cardSprites[cardIndex]->getPositionX(), selfCardMaginBottom));
        // 鏀瑰彉閫変腑鐗岀殑鐘舵€?        
		cardChosedState[cardIndex] = false;
    }else{
        // 鑾峰彇瀵瑰簲鐨勭簿鐏?        
		cardSprites[cardIndex]->setPosition(ccp(cardSprites[cardIndex]->getPositionX(), selfCardMaginBottomUp));
        // 鏀瑰彉閫変腑鐗岀殑鐘舵€?        
		cardChosedState[cardIndex] = true;
    }
    // 璁剧疆瀹氭椂鍣?    
	if(timerIsOpen){
        //this->scheduleOnce(schedule_selector(CardTouchLayer::timerCallBack), 0.5);
        timerIsOpen = false;
    }
}

// 鏃堕挓鍥炶皟
void CardTouchLayer::timerCallBack(){
    currentIndex = 21;
    timerIsOpen = true;
}

// 鎺掑簭鎵嬬墝
void CardTouchLayer::sortHandCards(){
    // 閬嶅巻姣忎竴涓暟鎹?    
	for (int i = 0; i < MAX_COUNT; i++) {
        // 鎺掑簭鏁版嵁
        for (int j = i; j < MAX_COUNT; j++) {
            CGameLogic gameLogic;
            BYTE firstCardLogicValue = handCardsData[i] == CARD_NULL ? 0 : gameLogic.GetCardLogicValue(handCardsData[i]);
            BYTE secondCardLogicValue = handCardsData[j] == CARD_NULL ? 0 : gameLogic.GetCardLogicValue(handCardsData[j]);
            if (firstCardLogicValue < secondCardLogicValue) {
                BYTE temp = handCardsData[i];
                handCardsData[i] = handCardsData[j];
                handCardsData[j] = temp;
            }
        }
        // 閲嶇粯鐗岄潰
        {
            char asd[50];snprintf(asd, 50, "CardBig%d%d",(handCardsData[i]/16),(handCardsData[i]%16));
            cardSprites[i]->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(asd));
            if(i<handCardsCount){
                cardSprites[i]->setVisible(true);
            }else{
                cardSprites[i]->setVisible(false);
                
            }
            // 鍒濆鍖栫墝鐨勯€変腑鏍囧織
            cardChosedState[i] = false;
        }
    }
    // 璁剧疆浣嶇疆鍋忕Щ
    cardBg->setPosition(ccp(size.width/2 + getOffsetX(),cardBg->getPositionY()));
}

// 璁＄畻鐜╁鎵嬬墝鐨刋杞村亸绉?
int CardTouchLayer::getOffsetX(){
    return (960 - ((selfCardSpacing * handCardsCount) + 90/2))/2 + selfCardOffsetX;
}




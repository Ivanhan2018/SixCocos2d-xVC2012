//
//  CardTouchLayer.h
//  TouchCardDemo
//
//  Created by ChengLin on 13-11-22.
//
//

#ifndef __TouchCardDemo__CardTouchLayer__
#define __TouchCardDemo__CardTouchLayer__

#include "Packet.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CMD_Game.h"
#include "GameLogic.h"
//#include "PlayerDataController.h"
//#include "GameAnimationLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;


#define     selfCardMaginBottom         100         // 鐜╁鎵嬬墝涓庡簳閮ㄧ殑闂磋窛
#define     selfCardMaginBottomUp       130         // 鐜╁瀹舵墜鐗屼笌搴曢儴鐨勯棿璺濓紙璺宠捣鏃讹級
#define     selfCardSpacing             45          // 鐜╁鎵嬬墝鐨勯棿璺?
#define     selfCardOffsetX             0           // 鐜╁鎵嬬墝X杞村亸绉?
class CardTouchLayer:public CCLayer{
    
public:
    
    virtual bool init();
    
    CREATE_FUNC(CardTouchLayer);
public:
    // 鎵嬬墝鐨勬暟鎹?    
	BYTE handCardsData[MAX_COUNT];
    // 鎵嬬墝鐨勫紶鏁?    
	BYTE handCardsCount;
private:
    // 鍦烘櫙澶у皬
    CCSize size;
    // 鐗岀殑绮剧伒鏁扮粍
    CCSprite *cardSprites[MAX_COUNT];
    // 鐗岄€変腑鏍囧織
    bool cardChosedState[MAX_COUNT];
    // 鑳屾櫙
    CCSprite *cardBg;
    // 婊戝姩閫夋嫨
    CCControlSlider *slider;
    // 璁板綍閫変腑鐨勭墝
    int currentIndex;
    // 鏃堕挓鏄惁寮€鍚?    
	bool timerIsOpen;
private:
    // 婊戝姩鐩戝惉
    void valueChange();
    // 鏀瑰彉琚€変腑鐗岀殑鐘舵€?    
	void changeCardState(int cardIndex);
    // 鏃堕挓鍥炶皟
    void timerCallBack();
    // 璁＄畻鐜╁鎵嬬墝鐨刋杞村亸绉?    
	int getOffsetX();
public:
    // 璁剧疆鐗岀殑鏁版嵁
    void initCardData(BYTE cardData[MAX_COUNT],BYTE cardCount);
    // 璁剧疆鐗岀殑鏁版嵁
    void LoadCardData(BYTE cardData[MAX_COUNT],BYTE cardCount);
    // 閲嶆柊鍒濆鍖?    
	void reInit();
    // 鏄剧ず鎸囧畾鐨勪竴寮犳墜鐗?    
	void showHandCardByIndex(int index);
    // 寮硅捣鎸囧畾鐨勪竴寮犳墜鐗?    
	void upHandCardByInfex(int index);
    // 鎺掑簭鎵嬬墝
    void sortHandCards();
    // 鑾峰彇閫変腑鐨勭墝鐨勬暟鎹?    
	void getSelectedCardData(tagOutCardResult &outCardData);
    // 鍑虹墝
    bool outCards(tagOutCardResult &outCardData);
    // 涓嶅嚭
    void notOutCards();
    // 鑾峰彇鍓╀綑鎵嬬墝鏁伴噺
    int getHanderCardCount(){return handCardsCount;};    
};

#endif /* defined(__TouchCardDemo__CardTouchLayer__) */

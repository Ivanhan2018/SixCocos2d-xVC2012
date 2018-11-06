//
//  DDDPokerCardSprite.h
//  XXDDZ
//
//  Created by XXY on 13-12-17.
//
//

#ifndef __XXDDZ__DDDPokerCardSprite__
#define __XXDDZ__DDDPokerCardSprite__

#include "cocos2d.h"
#include "CMD_Game.h"
#include "Packet.h" 

#define DotX 25
#define DotY         35          // 玩家出牌的上下间�?
#define DotHeight  450         // 左右侧用户出牌与屏幕底部的距�?
#define     DotLeft    230         // 左侧用户出牌与屏幕边的距�?
#define     DotRight   520         // 右侧用户出牌与屏幕边的距�?
USING_NS_CC;

struct POKER_ARRAY {
    CCSprite *Card[20];
    int CardValue[20];
    int position;
};

typedef POKER_ARRAY Poker;

class PokerCard:public CCNode{
    
private:
    
    bool init();
    
    Poker *m_Poker_Sprite[3];
    
public:
    
    void createPokerCrad(CCSprite *gameLayer);
    
    void setUserSelfIndexForCurrentGame(int index);
    
    void setPositionForIndex(int index);
    
    void ShowPlayerOutCard(bool isSelf, _WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]);
    
    void MissPlayerOutCard(bool isClear, _WORD_ index, bool clearSelf);
    
    void ShowGameOverCard(_BYTE_ cbCardCount[GAME_PLAYER], _BYTE_ cbHandCardData[FULL_COUNT]);
    
private:
    
    CCSpriteBatchNode *m_Poker_Card_Manager;
    
    std::map<int,int> m_Crad_Dot;
    
    void ShowPlayerOutCard(_WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]);
    
    bool ShowPlayerOutCard_Self(bool isSelf, _WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]);
    
    bool ShowPlayerOutCard_Left(bool isSelf, _WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]);
    
    bool ShowPlayerOutCard_right(bool isSelf, _WORD_ index, _BYTE_ outCardNum,_BYTE_ outCardData[20]);
    
};

#endif /* defined(__XXDDZ__DDDPokerCardSprite__) */

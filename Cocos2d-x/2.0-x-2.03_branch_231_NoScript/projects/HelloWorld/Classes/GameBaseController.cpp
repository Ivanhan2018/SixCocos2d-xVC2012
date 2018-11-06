//
//  GameBaseController.cpp
//  XXDDZ
//
//  Created by XXY on 13-11-29.
//
//

#include "GameBaseController.h"
#include "Packet.h"
#include "CardTouchLayer.h"

//设置游戏当前桌子
_BYTE_ myTableIndex;

//设置玩家的椅�?
_BYTE_ UserSelfIndex;

GAMEType myGameType;

bool isUserReady = false;

int playerHandCradCount[3];
_BYTE_ playerHandCardValue[3][MAX_COUNT];

// 第一个叫地主玩家
int FirstCallID = 0;

CCSprite *HandCardSprite[3][MAX_COUNT];

CCSprite *HandCardLayer[3];

// 当前用户手牌显示�?
CardTouchLayer *myHanderCardLayer;

CCSprite *CannotOutcardSprite;

void GameBaseController::setUserCurrentTableIndexAndChairIndex(_BYTE_ tabIdx, _BYTE_ ChairIdx){
    myTableIndex = tabIdx;
    UserSelfIndex = ChairIdx;
}
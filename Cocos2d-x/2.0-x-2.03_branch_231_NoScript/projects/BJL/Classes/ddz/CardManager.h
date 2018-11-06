#ifndef __GAME_CARDMANAGER_H__
#define __GAME_CARDMANAGER_H__
#pragma once

/***************************************
 牌管理类
 游戏界面

 ***************************************/

#include "cocos2d.h"
#include "CardSprite.h"
#include "ddz/CMD_DDZClient.h"
#include "ddz/Tools.h"
USING_NS_CC;
using namespace cocos2d;


struct PlayerCard
{
	//玩家手中的三张牌
	CardSprite* cards[3];
};

class CardManager : public cocos2d::CCLayer
{
public:
	//创建函数
	static CardManager *create();
	void showPlayerCardfive();
	//显示显示前两张牌
	void showPlayerCard(); 
	//显示第三张手牌
	void showPlayerCard1(BYTE m_cbTableCardArray[2][3],BYTE m_cbCardCount[2]);

	//游戏结束刷新手牌
	void updatePlayerCard(int chairID,unsigned char bHandCardData[2]);
	//设置手牌
	void SetHandCardData(unsigned char bHandCardData[]);
	//设置手牌
	void SetHandCardData1(unsigned char bHandCardData1[]);

	//发牌动画
	//(闲家第一张)
	void SetAnmionPlayOneCard();
	//(庄家第一张)
	void SetAnmionBankoneCard(CCObject* obj);
    //(闲家第二张)
	void SetAnmionPlayTwoCard(CCObject* obj);
	//庄家第二张
	void SetAnmionBankTwoCard(CCObject* obj);
	//闲家第三张
	void  SendCardToPlayerRuntion(float loat);
	//庄家第三张
	void  SendCardToBankThirdCard(float loat);

	//////////////////////////////////////////////////////
	//游戏结束重置方法
	void resetManager();
	//设置卡片翻滚
	void SetAnimation(CCSprite * Sprite,int Number);

	void afterCatchPalyerUsed(CCObject *obj);//闲家
	void afterCatchBankUsed(CCObject *obj);//庄家

	void  SetAnimationdoule(float loat);

public:

	//获取数值
	BYTE GetCardValue(BYTE cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//获取花色
	BYTE GetCardColor(BYTE cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//获取牌点
	BYTE GetCardPip(BYTE cbCardData);
	//获取牌点
	BYTE GetCardListPip(const BYTE cbCardData[], BYTE cbCardCount);

	CCSprite *GAMEoverSprite;                        //游戏结束

	CCLabelTTF* PlayhomeTTf[8];    //闲


	CCLabelTTF* ScoreGameover;   //平

	//设置游戏结束界面时间
	void showGameOver();
	void showGameOveAnmionTime(float dt);
	void remaggerDissGameOver();

	void SetScoreGameOver(LONGLONG lPlayScore,int Index, LONGLONG	lPlayAllScore);

private:
	//初始化函数
	bool initCardManager();
	//初始化所有玩家手牌
	void initPlayerCard();

	void SetPlayBankNumber(float flat);
public:
	CardSprite*       commonCards[5];	//五张公共牌
	PlayerCard        playerCard[8];  //玩家数组
	unsigned char     m_ucHandCardData[3];
	unsigned char     m_ucHandCardData1[3];

	unsigned short    m_bPlayerStatus[8]; 

	CCSprite *Player;  //闲家
	CCSprite *Banker;  // 庄家
	CCSprite *AndBureauSprite;  //和局
public:
	unsigned char     m_ucDeskCardData[5];
	bool FreehomeThirdCard;  //闲家是否发第三张牌 flase表示没有，true表示有
	CCSize Winsize;
	CCSprite *m_pUserPlaySprite;  //闲家点数
	CCSprite *m_pUserBankSprite;  //庄家点数

	BYTE cbBankerCount;	//闲家点数(两张牌的时候)
	BYTE cbPlayerTwoCardCount;	//庄家点数
	BYTE m_cbBankerCount;	//显示闲家第三张牌（三张牌的时候）

};

#endif  // __GAME_CARDMANAGER_H__
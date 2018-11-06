#ifndef __GAME_CARDMANAGER_H__
#define __GAME_CARDMANAGER_H__
#pragma once

/***************************************
 �ƹ�����
 ��Ϸ����

 ***************************************/

#include "cocos2d.h"
#include "CardSprite.h"
#include "ddz/CMD_DDZClient.h"
#include "ddz/Tools.h"
USING_NS_CC;
using namespace cocos2d;


struct PlayerCard
{
	//������е�������
	CardSprite* cards[3];
};

class CardManager : public cocos2d::CCLayer
{
public:
	//��������
	static CardManager *create();
	void showPlayerCardfive();
	//��ʾ��ʾǰ������
	void showPlayerCard(); 
	//��ʾ����������
	void showPlayerCard1(BYTE m_cbTableCardArray[2][3],BYTE m_cbCardCount[2]);

	//��Ϸ����ˢ������
	void updatePlayerCard(int chairID,unsigned char bHandCardData[2]);
	//��������
	void SetHandCardData(unsigned char bHandCardData[]);
	//��������
	void SetHandCardData1(unsigned char bHandCardData1[]);

	//���ƶ���
	//(�мҵ�һ��)
	void SetAnmionPlayOneCard();
	//(ׯ�ҵ�һ��)
	void SetAnmionBankoneCard(CCObject* obj);
    //(�мҵڶ���)
	void SetAnmionPlayTwoCard(CCObject* obj);
	//ׯ�ҵڶ���
	void SetAnmionBankTwoCard(CCObject* obj);
	//�мҵ�����
	void  SendCardToPlayerRuntion(float loat);
	//ׯ�ҵ�����
	void  SendCardToBankThirdCard(float loat);

	//////////////////////////////////////////////////////
	//��Ϸ�������÷���
	void resetManager();
	//���ÿ�Ƭ����
	void SetAnimation(CCSprite * Sprite,int Number);

	void afterCatchPalyerUsed(CCObject *obj);//�м�
	void afterCatchBankUsed(CCObject *obj);//ׯ��

	void  SetAnimationdoule(float loat);

public:

	//��ȡ��ֵ
	BYTE GetCardValue(BYTE cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//��ȡ��ɫ
	BYTE GetCardColor(BYTE cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//��ȡ�Ƶ�
	BYTE GetCardPip(BYTE cbCardData);
	//��ȡ�Ƶ�
	BYTE GetCardListPip(const BYTE cbCardData[], BYTE cbCardCount);

	CCSprite *GAMEoverSprite;                        //��Ϸ����

	CCLabelTTF* PlayhomeTTf[8];    //��


	CCLabelTTF* ScoreGameover;   //ƽ

	//������Ϸ��������ʱ��
	void showGameOver();
	void showGameOveAnmionTime(float dt);
	void remaggerDissGameOver();

	void SetScoreGameOver(LONGLONG lPlayScore,int Index, LONGLONG	lPlayAllScore);

private:
	//��ʼ������
	bool initCardManager();
	//��ʼ�������������
	void initPlayerCard();

	void SetPlayBankNumber(float flat);
public:
	CardSprite*       commonCards[5];	//���Ź�����
	PlayerCard        playerCard[8];  //�������
	unsigned char     m_ucHandCardData[3];
	unsigned char     m_ucHandCardData1[3];

	unsigned short    m_bPlayerStatus[8]; 

	CCSprite *Player;  //�м�
	CCSprite *Banker;  // ׯ��
	CCSprite *AndBureauSprite;  //�;�
public:
	unsigned char     m_ucDeskCardData[5];
	bool FreehomeThirdCard;  //�м��Ƿ񷢵������� flase��ʾû�У�true��ʾ��
	CCSize Winsize;
	CCSprite *m_pUserPlaySprite;  //�мҵ���
	CCSprite *m_pUserBankSprite;  //ׯ�ҵ���

	BYTE cbBankerCount;	//�мҵ���(�����Ƶ�ʱ��)
	BYTE cbPlayerTwoCardCount;	//ׯ�ҵ���
	BYTE m_cbBankerCount;	//��ʾ�мҵ������ƣ������Ƶ�ʱ��

};

#endif  // __GAME_CARDMANAGER_H__
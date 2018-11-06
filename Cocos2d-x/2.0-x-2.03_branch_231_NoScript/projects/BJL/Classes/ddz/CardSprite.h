#ifndef __GAME__CARDSPRITE__
#define __GAME__CARDSPRITE__
#pragma once

//�ƾ����� .h
//Created by xxxx on 14-1-6.

#include "cocos2d.h"
USING_NS_CC;

class CardSprite :public CCSprite
{
public:
	//��ʼ����
	static CardSprite * CardSpriteWith(unsigned char ucCardInfo);
	//��������
	void changeCardWith(unsigned char ucCardInfo);
private:
	//��ʼ������
	bool initCardSprite(unsigned char ucCardInfo);
	//�洢���������CCSprite
	CCSprite* tmp;
	//�洢���������CCTexture2D
	CCTexture2D* tmpTexture;
};
#endif

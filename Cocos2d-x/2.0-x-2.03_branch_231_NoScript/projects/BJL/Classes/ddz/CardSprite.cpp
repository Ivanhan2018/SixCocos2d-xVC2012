#include "CardSprite.h"
//ÅÆ¾«ÁéÀà .cpp
//Created by xxxx on 14-1-6.

CardSprite *CardSprite::CardSpriteWith(unsigned char ucCardInfo)
{

	CardSprite* sprite = new CardSprite();
	if(sprite && sprite->initCardSprite(ucCardInfo))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool CardSprite::initCardSprite(unsigned char ucCardInfo)
{
	tmp = CCSprite::create("ui_card/Card_All.png");
	tmpTexture = tmp->getTexture();
	if (ucCardInfo == 0x00)  
	{
		this->initWithTexture(tmpTexture, CCRectMake(0, 748, 140, 187));
	}
	else
	{
		int row = ucCardInfo%16;
		int col = ucCardInfo/16+1;
		this->initWithTexture(tmpTexture, CCRectMake((row-1) * 140 + 1, 187 * (col-1), 140,187));
	}
	return true;
}

void CardSprite::changeCardWith(unsigned char ucCardInfo)
{
	this->setTexture(tmpTexture);
	if (ucCardInfo == 0x00)  
	{
		this->setTextureRect(CCRectMake(0, 748, 140, 187));
	}
	else
	{
		int row = ucCardInfo%16;
		int col = ucCardInfo/16+1;
		this->setTextureRect(CCRectMake((row-1) * 140 + 1, 187 * (col-1), 140,187));
	}
}
#include "SIX_CardEntity.h"

SIX_CardEntity::SIX_CardEntity()
{
}

SIX_CardEntity::~SIX_CardEntity()
{
}

// 设置点数及花色
void SIX_CardEntity::setCardPointAndType(unsigned char point,CARD_TYPE type)
{
	m_CardInfo.wPoint=point;
	m_CardInfo.wType=type;
}

// 获取点数
unsigned char SIX_CardEntity::getCardPoint()
{
	return m_CardInfo.wPoint;
}

// 获取花色
CARD_TYPE SIX_CardEntity::getCardType()
{
	return m_CardInfo.wType;
}

// 是否花牌
bool SIX_CardEntity::isFaceCards(bool bCaclJoker)
{
	// 大小王也算花牌
	if (bCaclJoker && (m_CardInfo.wType==TYPE_BLACK_JOKER || m_CardInfo.wType==TYPE_RED_JOKER))
		return true;
	return (m_CardInfo.wPoint==1 || m_CardInfo.wPoint>10);
}

// 是否小王
bool SIX_CardEntity::isBlackJoker()
{
	return (m_CardInfo.wType==TYPE_BLACK_JOKER);
}

// 是否大王
bool SIX_CardEntity::isRedJoker()
{
	return (m_CardInfo.wType==TYPE_RED_JOKER);
}
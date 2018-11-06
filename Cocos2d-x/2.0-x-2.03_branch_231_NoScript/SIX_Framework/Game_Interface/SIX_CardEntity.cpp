#include "SIX_CardEntity.h"

SIX_CardEntity::SIX_CardEntity()
{
}

SIX_CardEntity::~SIX_CardEntity()
{
}

// ���õ�������ɫ
void SIX_CardEntity::setCardPointAndType(unsigned char point,CARD_TYPE type)
{
	m_CardInfo.wPoint=point;
	m_CardInfo.wType=type;
}

// ��ȡ����
unsigned char SIX_CardEntity::getCardPoint()
{
	return m_CardInfo.wPoint;
}

// ��ȡ��ɫ
CARD_TYPE SIX_CardEntity::getCardType()
{
	return m_CardInfo.wType;
}

// �Ƿ���
bool SIX_CardEntity::isFaceCards(bool bCaclJoker)
{
	// ��С��Ҳ�㻨��
	if (bCaclJoker && (m_CardInfo.wType==TYPE_BLACK_JOKER || m_CardInfo.wType==TYPE_RED_JOKER))
		return true;
	return (m_CardInfo.wPoint==1 || m_CardInfo.wPoint>10);
}

// �Ƿ�С��
bool SIX_CardEntity::isBlackJoker()
{
	return (m_CardInfo.wType==TYPE_BLACK_JOKER);
}

// �Ƿ����
bool SIX_CardEntity::isRedJoker()
{
	return (m_CardInfo.wType==TYPE_RED_JOKER);
}
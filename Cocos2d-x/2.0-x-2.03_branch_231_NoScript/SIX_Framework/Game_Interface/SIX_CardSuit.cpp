#include "SIX_CardSuit.h"

SIX_CardSuit::SIX_CardSuit()
{
	m_bIsPopAll = m_bIsActivedAll = m_bIsFrontShowAll = m_bIsReverseShowAll = false;
}

SIX_CardSuit::~SIX_CardSuit()
{
}

// ���õ�������ɫ
void SIX_CardSuit::setCardPointAndType(CCSpriteFrame *pPointFrame,CCSpriteFrame *pFaceSmallFrame,CCSpriteFrame *pFaceBigFrame,unsigned int idx,unsigned char point,CARD_TYPE type)
{
	if (idx>this->getChildrenCount())
		return;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return;

	pCard->setCardPointAndType(pPointFrame,pFaceSmallFrame,pFaceBigFrame,point,type);
}

// ��ȡ����
unsigned char SIX_CardSuit::getCardPoint(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return 0;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return 0;

	return pCard->getCardPoint();
}

// ��ȡ��ɫ
CARD_TYPE SIX_CardSuit::getCardType(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return TYPE_UNKNOWN;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return TYPE_UNKNOWN;

	return pCard->getCardType();
}

// �Ƿ���
bool SIX_CardSuit::isFaceCards(unsigned int idx,bool bCaclJoker)
{
	if (idx>this->getChildrenCount())
		return false;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->isFaceCards(bCaclJoker);
}

// �Ƿ�С��
bool SIX_CardSuit::isBlackJoker(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return false;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->isBlackJoker();
}

// �Ƿ����
bool SIX_CardSuit::isRedJoker(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return false;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->isRedJoker();
}

// �����Ƶ���
void SIX_CardSuit::setCardPop(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//���������ƶ�������.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardPop(bPop);
	}
}

// ��ȡ�Ƶ���
bool SIX_CardSuit::getCardPop(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardPop();
}

// �����Ƽ���
void SIX_CardSuit::setCardActived(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//���������ƶ�������.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardActived(bPop);
	}
}

// ��ȡ�Ƽ���
bool SIX_CardSuit::getCardActived(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardActived();
}

// ���������ӽǷ�ת
void SIX_CardSuit::setCardOrbitCamera(unsigned int startIdx,unsigned int endIdx,float t,float angleZ,float deltaAngleZ)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardOrbitCamera(t,angleZ,deltaAngleZ);
	}
}

// ����������ʾ
void SIX_CardSuit::setCardFrontShow(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//���������ƶ�������.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardFrontShow(bPop);
	}
}

// ��ȡ������ʾ
bool SIX_CardSuit::getCardFrontShow(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardFrontShow();
}

// �����Ƶ���ʾ
void SIX_CardSuit::setCardReverseShow(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//���������ƶ�������.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardReverseShow(bPop);
	}
}

// ��ȡ�Ƶ���ʾ
bool SIX_CardSuit::getCardReverseShow(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardReverseShow();
}

// �����������Ƿ���
void SIX_CardSuit::setCardPopAll(bool bIsPopAll)
{
	for (unsigned int i=0;i<this->getChildrenCount();i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (pCard)
			pCard->setCardPop(bIsPopAll);
	}
	m_bIsPopAll = bIsPopAll;
}

bool SIX_CardSuit::getCardPopAll()
{
	return m_bIsPopAll;
}

// �����������Ƿ񼤻�
void SIX_CardSuit::setCardActivedAll(bool bIsActived)
{
	for (unsigned int i=0;i<this->getChildrenCount();i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (pCard)
			pCard->setCardActived(bIsActived);
	}
	m_bIsActivedAll = bIsActived;
}

bool SIX_CardSuit::getCardActivedAll()
{
	return m_bIsActivedAll;
}

// �������������Ƿ���ʾ
void SIX_CardSuit::setCardFrontShowAll(bool bIsFrontShow)
{
	for (unsigned int i=0;i<this->getChildrenCount();i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (pCard)
			pCard->setCardFrontShow(bIsFrontShow);
	}
	m_bIsFrontShowAll = bIsFrontShow;
}

bool SIX_CardSuit::getCardFrontShowAll()
{
	return m_bIsFrontShowAll;
}

// ���������Ƶ��Ƿ���ʾ
void SIX_CardSuit::setCardReverseShowAll(bool bIsReverseShow)
{
	for (unsigned int i=0;i<this->getChildrenCount();i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (pCard)
			pCard->setCardReverseShow(bIsReverseShow);
	}
	m_bIsReverseShowAll = bIsReverseShow;
}

bool SIX_CardSuit::getCardReverseShowAll()
{
	return m_bIsReverseShowAll;
}

// ȡ�ƶ������Ļ�ľ���ƫ��
CCPoint SIX_CardSuit::getAbsOffset()
{
	CCPoint absOffset = this->getPosition();;
	CCNode *pFather = this->getParent();
	while(pFather)
	{
		absOffset.x += pFather->getPositionX();
		absOffset.y += pFather->getPositionY();
		pFather = pFather->getParent();
	}

	return absOffset;
}
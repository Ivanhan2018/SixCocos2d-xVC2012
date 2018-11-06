#include "SIX_CardSuit.h"

SIX_CardSuit::SIX_CardSuit()
{
	m_bIsPopAll = m_bIsActivedAll = m_bIsFrontShowAll = m_bIsReverseShowAll = false;
}

SIX_CardSuit::~SIX_CardSuit()
{
}

// 设置点数及花色
void SIX_CardSuit::setCardPointAndType(CCSpriteFrame *pPointFrame,CCSpriteFrame *pFaceSmallFrame,CCSpriteFrame *pFaceBigFrame,unsigned int idx,unsigned char point,CARD_TYPE type)
{
	if (idx>this->getChildrenCount())
		return;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return;

	pCard->setCardPointAndType(pPointFrame,pFaceSmallFrame,pFaceBigFrame,point,type);
}

// 获取点数
unsigned char SIX_CardSuit::getCardPoint(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return 0;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return 0;

	return pCard->getCardPoint();
}

// 获取花色
CARD_TYPE SIX_CardSuit::getCardType(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return TYPE_UNKNOWN;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return TYPE_UNKNOWN;

	return pCard->getCardType();
}

// 是否花牌
bool SIX_CardSuit::isFaceCards(unsigned int idx,bool bCaclJoker)
{
	if (idx>this->getChildrenCount())
		return false;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->isFaceCards(bCaclJoker);
}

// 是否小王
bool SIX_CardSuit::isBlackJoker(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return false;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->isBlackJoker();
}

// 是否大王
bool SIX_CardSuit::isRedJoker(unsigned int idx)
{
	if (idx>this->getChildrenCount())
		return false;

	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->isRedJoker();
}

// 设置牌弹起
void SIX_CardSuit::setCardPop(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//设置所有牌都不弹起.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardPop(bPop);
	}
}

// 获取牌弹起
bool SIX_CardSuit::getCardPop(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardPop();
}

// 设置牌激活
void SIX_CardSuit::setCardActived(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//设置所有牌都不弹起.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardActived(bPop);
	}
}

// 获取牌激活
bool SIX_CardSuit::getCardActived(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardActived();
}

// 设置牌面视角翻转
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

// 设置牌面显示
void SIX_CardSuit::setCardFrontShow(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//设置所有牌都不弹起.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardFrontShow(bPop);
	}
}

// 获取牌面显示
bool SIX_CardSuit::getCardFrontShow(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardFrontShow();
}

// 设置牌底显示
void SIX_CardSuit::setCardReverseShow(unsigned int startIdx,unsigned int endIdx,bool bPop)
{
	if (startIdx>this->getChildrenCount())
		return;

	if (endIdx<startIdx)
		endIdx = startIdx;

	//设置所有牌都不弹起.
	setCardPopAll(false);

	for (unsigned int i=startIdx;i<=endIdx;i++)
	{
		SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(i));
		if (!pCard)
			return;

		pCard->setCardReverseShow(bPop);
	}
}

// 获取牌底显示
bool SIX_CardSuit::getCardReverseShow(unsigned int idx)
{
	SIX_CardItem *pCard = dynamic_cast<SIX_CardItem*>(this->getChildren()->objectAtIndex(idx));
	if (!pCard)
		return false;

	return pCard->getCardReverseShow();
}

// 设置所有牌是否弹起
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

// 设置所有牌是否激活
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

// 设置所有牌面是否显示
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

// 设置所有牌底是否显示
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

// 取牌堆相对屏幕的绝对偏移
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
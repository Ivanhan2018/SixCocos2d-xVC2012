#include "SIX_CardItem.h"

SIX_CardItem::SIX_CardItem()
{
}

SIX_CardItem::~SIX_CardItem()
{
	DoRelease();
}

SIX_CardItem* SIX_CardItem::create(CCNode* label, CCScale9Sprite* backgroundSprite)
{
	SIX_CardItem *pCard = new SIX_CardItem();
	pCard->initWithLabelAndBackgroundSprite(label,backgroundSprite);
	pCard->init();
	pCard->autorelease();
	return pCard;
}

SIX_CardItem* SIX_CardItem::create(string title, const char * fontName, float fontSize)
{
    SIX_CardItem *pCard = new SIX_CardItem();
    pCard->initWithTitleAndFontNameAndFontSize(title, fontName, fontSize);
	pCard->init();
    pCard->autorelease();
    return pCard;
}

SIX_CardItem* SIX_CardItem::create(CCScale9Sprite* sprite)
{
    SIX_CardItem *pCard = new SIX_CardItem();
    pCard->initWithBackgroundSprite(sprite);
	pCard->init();
    pCard->autorelease();
    return pCard;
}

bool SIX_CardItem::init()
{
	m_pBatchNode = 0;
	m_pBackgroundFront = m_pBackgroundReverse = m_pPoint = m_pFaceS = m_pFaceB = 0;
	m_bPop = m_bActived = m_bFrontShow = m_bReverseShow = false;
	m_bShowPoint = m_bShowSmallFace = m_bShowBigFace = false;
	return true;
}

void SIX_CardItem::DoCardCombined()
{
	if (m_pBatchNode && !m_pBatchNode->getParent())
	{
		this->retain();
		this->addChild(m_pBatchNode);
	}
	if (m_pBackgroundFront && !m_pBackgroundFront->getParent())
	{
		if (m_pBatchNode)
			m_pBatchNode->addChild(m_pBackgroundFront);
		else
			this->addChild(m_pBackgroundFront);
	}
	if (m_pBackgroundReverse && !m_pBackgroundReverse->getParent())
	{
		if (m_pBatchNode)
			m_pBatchNode->addChild(m_pBackgroundReverse);
		else
			this->addChild(m_pBackgroundReverse);
	}
	if (m_pPoint && !m_pPoint->getParent())
	{
		if (m_pBatchNode)
			m_pBatchNode->addChild(m_pPoint);
		else
			this->addChild(m_pPoint);
	}
	if (m_pFaceS && !m_pFaceS->getParent())
	{
		if (m_pBatchNode)
			m_pBatchNode->addChild(m_pFaceS);
		else
			this->addChild(m_pFaceS);
	}
	if (m_pFaceB && !m_pFaceB->getParent())
	{
		if (m_pBatchNode)
			m_pBatchNode->addChild(m_pFaceB);
		else
			this->addChild(m_pFaceB);
	}
}

void SIX_CardItem::DoRelease()
{
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}

// ���õ�������ɫ
void SIX_CardItem::setCardPointAndType(CCSpriteFrame *pPointFrame,CCSpriteFrame *pFaceSmallFrame,CCSpriteFrame *pFaceBigFrame,unsigned char point,CARD_TYPE type)
{
	// ��������
	SIX_CardEntity::setCardPointAndType(point,type);
	// ˢ��UI
	if (m_pPoint)
	{
		m_pPoint->setVisible(pPointFrame?true:false);
		if (pPointFrame)
			m_pPoint->setDisplayFrame(pPointFrame);
		else
			m_pPoint->setTextureRect(CCRectZero);
	}
	if (m_pFaceS)
	{
		m_pFaceS->setVisible(pFaceSmallFrame?true:false);
		if (pFaceSmallFrame)
			m_pFaceS->setDisplayFrame(pFaceSmallFrame);
	}
	if (m_pFaceB)
	{
		m_pFaceB->setVisible(pFaceBigFrame?true:false);
		if (pFaceBigFrame)
			m_pFaceB->setDisplayFrame(pFaceBigFrame);
	}
}

// ������
void SIX_CardItem::resetCard(bool bPop,bool bActived,bool bFrontShow)
{
	this->setCardPop(bPop);
	this->setCardActived(bActived);
	this->setCardFrontShow(bFrontShow);
	this->setCardReverseShow(!bFrontShow);
}

// ����
void SIX_CardItem::setCardPop(bool bPop)
{
	if (m_bPop!=bPop)
	{
		m_bPop = bPop;
		this->setPositionY(bPop?this->getPositionY()+CARD_POP_OFFSET:this->getPositionY()-CARD_POP_OFFSET);
	}
}

bool SIX_CardItem::getCardPop()
{
	return m_bPop;
}

// ����(�Ƿ�ɲ���)
void SIX_CardItem::setCardActived(bool bActived)
{
	m_bActived = bActived;
	this->setEnabled(bActived);
	this->setTouchEnabled(bActived);
}

bool SIX_CardItem::getCardActived()
{
	return m_bActived;
}

// ��ʾ����
void SIX_CardItem::setCardFrontShow(bool bShow)
{
	m_bFrontShow = bShow;
	if (m_pBackgroundFront)
	{
		m_pBackgroundFront->setVisible(bShow);
	}
	if (m_pBackgroundReverse)
	{
		m_pBackgroundReverse->setVisible(!bShow);
	}
	this->setCardPointShow(bShow);
	this->setCardSmallFaceShow(bShow);
	this->setCardBigFaceShow(bShow);
}

bool SIX_CardItem::getCardFrontShow()
{
	return m_bFrontShow;
}

// ��ʾ�Ƶ�
void SIX_CardItem::setCardReverseShow(bool bShow)
{
	m_bReverseShow = bShow;
	if (m_pBackgroundFront)
	{
		m_pBackgroundFront->setVisible(!bShow);
	}
	if (m_pBackgroundReverse)
	{
		m_pBackgroundReverse->setVisible(bShow);
	}
	this->setCardPointShow(!bShow);
	this->setCardSmallFaceShow(!bShow);
	this->setCardBigFaceShow(!bShow);
}

bool SIX_CardItem::getCardReverseShow()
{
	return m_bReverseShow;
}

// ��ʾ����
void SIX_CardItem::setCardPointShow(bool bShow)
{
	m_bShowPoint = bShow;
	if (m_pPoint)
		m_pPoint->setVisible(bShow);
}

bool SIX_CardItem::getCardPointShow()
{
	return m_bShowPoint;
}

// ��ʾС��ɫ
void SIX_CardItem::setCardSmallFaceShow(bool bShow)
{
	m_bShowSmallFace = bShow;
	if (m_pFaceS)
		m_pFaceS->setVisible(bShow);
}

bool SIX_CardItem::getCardSmallFaceShow()
{
	return m_bShowSmallFace;
}

// ��ʾ��ɫ
void SIX_CardItem::setCardBigFaceShow(bool bShow)
{
	m_bShowBigFace = bShow;
	if (m_pFaceB)
		m_pFaceB->setVisible(bShow);
}

bool SIX_CardItem::getCardBigFaceShow()
{
	return m_bShowBigFace;
}

// ����ƫ��
void SIX_CardItem::setCardPointPosition(CCPoint pt)
{
	if (m_pPoint)
		m_pPoint->setPosition(pt);
}

void SIX_CardItem::setCardSmallFacePosition(CCPoint pt)
{
	if (m_pFaceS)
		m_pFaceS->setPosition(pt);
}

void SIX_CardItem::setCardBigFacePosition(CCPoint pt)
{
	if (m_pFaceB)
		m_pFaceB->setPosition(pt);
}

void SIX_CardItem::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	SIXLog("doEvents.event[%d].tag[%d]",event,tag);

	switch (event)
	{
		// ��ť���²���ק������������
	case CCControlEventTouchDragExit:
		{
			break;
		}
		// ��ť����δ����
	case CCControlEventTouchDown:
		{
			break;
		}
		// ��ť���µ���
	case CCControlEventTouchUpInside:
		{
			break;
		}
	}
}
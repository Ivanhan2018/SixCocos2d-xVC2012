#include "SIX_NumberBatchNode.h"

SIX_NumberBatchNode::SIX_NumberBatchNode()
{
	m_llNumberLast = m_llNumber = m_uCellNum = m_uPadding = m_uBitCount = m_uShowCount =0;
	m_CellAlignStyle = ALIGN_LEFT;
	pNumFile = 0;
}

SIX_NumberBatchNode::~SIX_NumberBatchNode()
{
	DoRelease();
}

SIX_NumberBatchNode *SIX_NumberBatchNode::Create(const char *file)
{
	if (!file)
		return 0;

	SIX_NumberBatchNode *pBatchNode = new SIX_NumberBatchNode();
	if (!pBatchNode || !pBatchNode->initWithFile(file,0))
	{
		CC_SAFE_DELETE(pBatchNode);
		return 0;
	}
	pBatchNode->pNumFile = CCString::create(file);
	//pBatchNode->pNumFile->retain();
	return pBatchNode;
}

SIX_NumberBatchNode *SIX_NumberBatchNode::Create(const char *file,unsigned int cell,float padding,unsigned int bitcount,CCPoint offset,EFFECT_TYPE effectType,float effectValue,float durtime)
{
	if (!file || !cell || !padding || !bitcount)
		return 0;

	SIX_NumberBatchNode *pBatchNode = new SIX_NumberBatchNode();
	if (!pBatchNode || !pBatchNode->initWithFile(file,0))
	{
		CC_SAFE_DELETE(pBatchNode);
		return 0;
	}
	
	// save it~
	if (durtime<=0.0f)
	{
		pBatchNode->setEffectType(EFFECT_NONE);
		pBatchNode->setEffectValue(EFFECT_VALUE);
		pBatchNode->setDurtime(EFFECT_DURTIME);
	}
	else
	{
		pBatchNode->setEffectType(effectType);
		pBatchNode->setEffectValue(effectValue);
		pBatchNode->setDurtime(durtime);
	}

	pBatchNode->pNumFile = CCString::create(file);
	//pBatchNode->pNumFile->retain();
	pBatchNode->setCellNum(cell);
	pBatchNode->setPadding(padding);
	pBatchNode->setBitCount(bitcount);
	pBatchNode->setPosition(offset);

	return pBatchNode;
}

void SIX_NumberBatchNode::DoRelease()
{
	stopAllActions();
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE(pNumFile);
}

void SIX_NumberBatchNode::setCellNum(unsigned int cellnum)
{
	m_uCellNum = cellnum;
}

unsigned int SIX_NumberBatchNode::getCellNum()
{
	return m_uCellNum;
}

void SIX_NumberBatchNode::setCellWidth(float cellwidth)
{
	m_fCellWidth = cellwidth;
}

float SIX_NumberBatchNode::getCellWidth()
{
	return m_fCellWidth;
}

void SIX_NumberBatchNode::setCellHeight(float cellheight)
{
	m_fCellHeight = cellheight;
}

float SIX_NumberBatchNode::getCellHeight()
{
	return m_fCellHeight;
}

void SIX_NumberBatchNode::setCellAlignStyle(ALIGN_STYLE style)
{
	m_CellAlignStyle = style;
}

ALIGN_STYLE SIX_NumberBatchNode::getCellAlignStyle()
{
	return m_CellAlignStyle;
}

void SIX_NumberBatchNode::setPadding(float padding)
{
	m_uPadding = padding;
}

float SIX_NumberBatchNode::getPadding()
{
	return m_uPadding;
}

void SIX_NumberBatchNode::setBitCount(unsigned int bitcount)
{
	m_uBitCount = bitcount;

	// ��������Ӿ�����~
	this->removeAllChildrenWithCleanup(true);

	// ����Ӻ��Ӿ��飬������ʱֻ��Ҫ�Ӿ����������ƫ�Ƽ���
	// Cool.Cat
	this->setCellWidth((float)(this->getTexture()->getContentSize().width/this->getCellNum()));
	this->setCellHeight(this->getTexture()->getContentSize().height);
	for (int i=0;i<m_uBitCount;i++)
	{
		// Ĭ��Ϊ����ĵ�һ��cell
		CCSprite *pSprNum = CCSprite::spriteWithFile(this->pNumFile->getCString(),CCRect(0.0f,0.0f,this->getCellWidth(),this->getCellHeight()));
		if (!pSprNum)
		{
			CCAssert(pSprNum,"pSprNum.nil!");
			continue;
		}
		if (i==0)
			pSprNum->setPosition(ccp(i*this->getCellWidth()-pSprNum->getContentSize().width/2,this->getCellHeight()-pSprNum->getContentSize().height/2));
		else
			pSprNum->setPosition(ccp(i*(this->getCellWidth()+this->getPadding())-pSprNum->getContentSize().width/2,this->getCellHeight()-pSprNum->getContentSize().height/2));
		this->addChild(pSprNum);
	}
}

unsigned int SIX_NumberBatchNode::getBitCount()
{
	return m_uBitCount;
}

void SIX_NumberBatchNode::setNumber(long long number,bool doAnimate)
{
	if (this->getBitCount()==0 || this->getBitCount()!=this->getChildrenCount())
		return;

	// ����Ҫ��ʾ���ֵĸ���
	int len = SIX_Utility::GetInstance()->GetNumberLength(number);
	if (0<getDigit() && len<getDigit())
		len = getDigit();
	if (this->getBitCount()<len)
		return;

	this->m_llNumberLast = this->m_llNumber;
	this->m_llNumber = number;

	// ת�ַ���
	CCString *pNumFormat = NULL;
	if (0 < getDigit())
		pNumFormat = CCString::createWithFormat("%%0%ulld", getDigit());
	else
		pNumFormat = CCString::create("%lld");
	CCString *pNumArray = CCString::createWithFormat(pNumFormat->getCString(),number);

	switch (this->getCellAlignStyle())
	{
		// �����
	case ALIGN_LEFT:
		{
			// ��ʼƫ��
			int pos = len;

			// �����Ч����
			for (int i=0;i<pos;i++)
			{
				CCSprite *pSprNum = dynamic_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
				if (!pSprNum)
				{
					CCAssert(0,"pSprNum.Nil");
					continue;
				}
				int value = SIX_Utility::GetInstance()->s2n(pNumArray->m_sString.at(i));
				pSprNum->setTextureRect(CCRect((float)(value*this->getCellWidth()),0.0f,this->getCellWidth(),this->getCellHeight()));
			}
			// ��Ч������ʾ������
			for (int i=pos;i<this->getBitCount();i++)
			{
				CCSprite *pSprNum = dynamic_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
				if (!pSprNum)
				{
					CCAssert(0,"pSprNum.Nil");
					continue;
				}
				pSprNum->setTextureRect(CCRect(0.0f,0.0f,0.0f,0.0f));
			}
			break;
		}
		// �Ҷ���
	case ALIGN_RIGHT:
		{
			// ��ʼƫ��
			int pos = this->getBitCount()-len;

			// ��Ч������ʾ������
			for (int i=0;i<pos;i++)
			{
				CCSprite *pSprNum = dynamic_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
				if (!pSprNum)
				{
					CCAssert(0,"pSprNum.Nil");
					continue;
				}
				pSprNum->setTextureRect(CCRect(0.0f,0.0f,0.0f,0.0f));
			}
			// �ұ���Ч����
			for (int i=pos;i<this->getBitCount();i++)
			{
				CCSprite *pSprNum = dynamic_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
				if (!pSprNum)
				{
					CCAssert(0,"pSprNum.Nil");
					continue;
				}
				int value = SIX_Utility::GetInstance()->s2n(pNumArray->m_sString.at(i-pos));
				pSprNum->setTextureRect(CCRect((float)(value*this->getCellWidth()),0.0f,this->getCellWidth(),this->getCellHeight()));
			}
			break;
		}
	}

	pNumArray->release();

	// ִ�ж���
	if (doAnimate)
	{
		this->DoEffectOnChildren(0.1f);
	}
	// ִ����Ч
	else
	{
		this->DoEffect(this);
		//this->DoEffectOnChildren(0.0f);
	}
}

long long SIX_NumberBatchNode::getNumber()
{
	return m_llNumber;
}

void SIX_NumberBatchNode::setDigit(unsigned int cCount)
{
	m_uShowCount = cCount;
}

unsigned int SIX_NumberBatchNode::getDigit()
{
	return m_uShowCount;
}
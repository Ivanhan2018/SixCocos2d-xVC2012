#include "SIX_EffectBatchNode.h"

SIX_EffectBatchNode::SIX_EffectBatchNode()
{
	m_tEffectType = EFFECT_NONE;
	m_fValue = EFFECT_VALUE;
	m_fDurtime = EFFECT_DURTIME;
}

SIX_EffectBatchNode::~SIX_EffectBatchNode()
{
}

SIX_EffectBatchNode *SIX_EffectBatchNode::Create(const char *file,EFFECT_TYPE effectType,float effectValue,float durtime)
{
	if (!file)
		return 0;

	SIX_EffectBatchNode *pBatchNode = new SIX_EffectBatchNode();
	if (!pBatchNode || !pBatchNode->initWithFile(file,0))
	{
		CC_SAFE_DELETE(pBatchNode);
		return 0;
	}
	
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
	return pBatchNode;
}

EFFECT_TYPE SIX_EffectBatchNode::getEffectType()
{
	return m_tEffectType;
}

void SIX_EffectBatchNode::setEffectType(EFFECT_TYPE effectType)
{
	m_tEffectType = effectType;
}

float SIX_EffectBatchNode::getEffectValue()
{
	return m_fValue;
}

void SIX_EffectBatchNode::setEffectValue(float value)
{
	m_fValue = value;
}

float SIX_EffectBatchNode::getDurtime()
{
	return m_fDurtime;
}

void SIX_EffectBatchNode::setDurtime(float durtime)
{
	m_fDurtime = durtime;
}

void SIX_EffectBatchNode::DoEffect(CCNode *pNode,float delay)
{
	if (m_tEffectType==EFFECT_NONE)
		return;

	CCArray *pActArr = CCArray::create();
	// 延迟执行
	if (delay>0.0f)
	{
		CCDelayTime *pTime = CCDelayTime::create(delay);
		pActArr->addObject(pTime);
	}
	switch (m_tEffectType)
	{
		// 渐入(子精灵调用时生效)
	case EFFECT_FADEIN:
		{
			// 持续时间
			CCFadeIn *pFadeIn = CCFadeIn::create(this->getDurtime());
			pActArr->addObject(pFadeIn);
			break;
		}
		// 渐出(子精灵调用时生效)
	case EFFECT_FADEOUT:
		{
			// 持续时间
			CCFadeOut *pFadeOut = CCFadeOut::create(this->getDurtime());
			pActArr->addObject(pFadeOut);
			break;
		}
		// 缩放(正常)
	case EFFECT_SCALE:
		{
			// 持续时间
			// 拉伸比例
			CCScaleTo *pScaleTo = CCScaleTo::create(this->getDurtime(),this->getEffectValue());
			pActArr->addObject(pScaleTo);
			pScaleTo = CCScaleTo::create(this->getDurtime(),1.0f);
			pActArr->addObject(pScaleTo);
			break;
		}
		// 旋转(正常)
	case EFFECT_ROTATION:
		{
			// 持续时间
			// 旋转角度
			CCRotateTo *pRotateTo = CCRotateTo::create(this->getDurtime(),this->getEffectValue());
			pActArr->addObject(pRotateTo);
			pRotateTo = CCRotateTo::create(this->getDurtime(),0.0f);
			pActArr->addObject(pRotateTo);
			break;
		}
	default:
		{
			CCAssert(0,"EffectType.Unknown!");
			return;
		}
	}

	//// let's do this~
	//// 顺序执行
	CCSequence *pAct = (CCSequence*)(CCSequence::create(pActArr));
	// 同步执行
	//CCSpawn *pAct = (CCSpawn*)(CCSpawn::create(pActArr));
	if (!pAct)
		return;
	pNode->runAction(pAct);
}

void SIX_EffectBatchNode::DoEffectOnChildren(float delay)
{
	for (unsigned int i=0;i<this->getChildrenCount();i++)
	{
		CCSprite *pSprite = dynamic_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
		if (!pSprite)
			continue;
		this->DoEffect(pSprite,delay*i);
	}
}
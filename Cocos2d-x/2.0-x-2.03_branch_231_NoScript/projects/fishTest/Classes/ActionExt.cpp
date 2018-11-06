
#include "ActionExt.h"


CCMoveByRound* CCMoveByRound::actionWithDuration(float duration, float r, float a, float b)
{
	CCMoveByRound *pMoveByRound  = new CCMoveByRound();
	pMoveByRound ->initWithDuration(duration, r, a, b);
	pMoveByRound ->autorelease();
	return pMoveByRound ;
}

bool CCMoveByRound::initWithDuration(float duration, float r, float a, float b)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		this->a = a;
		this->b = b;
		this->t = duration;
		this->r = r;
		return true;
	}

	return false;
}

void CCMoveByRound::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	CCPoint sp = pTarget->getPosition();
	float x = -a * cosf(r * 6.2831852f);
	float y = -b * sinf(r * 6.2831852f);
	sp = ccpAdd(sp, ccp(x, y));
	m_startPosition = sp;
	pTarget->setPosition(sp);
}

void CCMoveByRound::update(float time)
{
	if (m_pTarget)
	{
		float x = a * cosf((time + r) * 6.2831852f);
		float y = b * sinf((time + r) * 6.2831852f);
		m_pTarget->setPosition(ccp(m_startPosition.x + x, m_startPosition.y + y));
	}
}

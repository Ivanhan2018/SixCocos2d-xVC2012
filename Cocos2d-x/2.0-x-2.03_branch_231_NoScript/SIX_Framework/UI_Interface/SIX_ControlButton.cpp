#include "SIX_ControlButton.h"

SIX_ControlButton *SIX_ControlButton::m_LastOperatorButton = 0;

SIX_ControlButton* SIX_ControlButton::create(CCScale9Sprite* sprite)
{
	SIX_ControlButton *pRet = new SIX_ControlButton();
	pRet->initWithBackgroundSprite(sprite);
	pRet->autorelease();
	return pRet;
}

void SIX_ControlButton::setHighlighted(bool enabled)
{
	if (enabled)
	{
		if (this == m_LastOperatorButton)
			return;

		if (0 != m_LastOperatorButton)
		{
			m_LastOperatorButton->restoreNormalState();
			m_LastOperatorButton = 0;
		}

		CCControlButton::setHighlighted(enabled);
		m_LastOperatorButton = this;
	}
	else
	{
		return;
	}
}

void SIX_ControlButton::restoreNormalState()
{
	m_eState = CCControlStateNormal;
	m_isPushed = false;
	CCControlButton::setHighlighted(false);
}
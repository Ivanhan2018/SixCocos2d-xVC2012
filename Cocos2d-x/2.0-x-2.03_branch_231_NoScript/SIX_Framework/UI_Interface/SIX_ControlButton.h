/***********************************************
Name£∫SIX_ControlButton
Desc£∫SIX_ControlButton
Auth£∫Õ≈≥§@2013-10-28
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_UILayer.h>


USING_NS_CC;

class SIX_ControlButton : public CCControlButton
{
public:
	static SIX_ControlButton* create(CCScale9Sprite* sprite);
	virtual void setHighlighted(bool enabled);

private:
	void restoreNormalState();

private:
	static SIX_ControlButton *m_LastOperatorButton;
};
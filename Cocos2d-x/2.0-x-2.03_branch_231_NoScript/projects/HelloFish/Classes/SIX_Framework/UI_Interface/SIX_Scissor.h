/***********************************************
Name£ºSIX_Scissor
Desc£º¿É²Ã¼ô¿Ø¼þ
Auth£ºCool.Cat@2013-07-22
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "SIX_UILayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_Scissor:public CCControl
{
public:
	SIX_Scissor();
	virtual ~SIX_Scissor();
	static SIX_Scissor* create();
public:
	void setScissorEnabled(bool IsScissor);
	bool getScissorEnabled();
	void setScissorOffsetX(float offset);
	float getScissorOffsetX();
	void setScissorOffsetY(float offset);
	float getScissorOffsetY();
private:
	virtual void visit();
	void beforeDraw();
	void afterDraw();
private:
	bool m_bScissor;
	float m_fOffsetX;
	float m_fOffsetY;
};
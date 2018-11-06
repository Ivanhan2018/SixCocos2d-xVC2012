/***********************************************
Name：SIX_PopWndFirstBuy
Desc：首次购买礼包
Auth：团长@2013-10-29
***********************************************/
#pragma once
#include <cocos2d.h>
#include "cocos-ext.h"
#include "SIX_EffectPopWnd.h"

class SIX_PopWndFirstBuy :	public SIX_EffectPopWnd
{
public:
	static SIX_PopWndFirstBuy *Create(float x,float y,const ccColor4B& color, float width, float height);
	virtual ~SIX_PopWndFirstBuy(void);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();

private:
	void doEvents(CCObject* pSender, CCControlEvent controlEvent);
};


#pragma once
#ifndef ____HALL_H____
#define ____HALL_H____
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;

class CHall : public CCLayer
{
public:
	CHall(void);
	~CHall(void);
	
	virtual void onEnter();
	virtual void onExit();
	void Update(float);

	CCAnimate * CreateFrameAnimate(CCSpriteFrameCache * pCache, char * pSigleName, int iSize, float fTime);
	void OnHelp(CCObject* pSender);

	void setMenuItemEx(CCMenuItemImage * pItem, float &fX, float &fY);
	static void scene();
};

#endif
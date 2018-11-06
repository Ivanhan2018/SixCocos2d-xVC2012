/***********************************************
Name：SIX_PopWndBuyBullet
Desc：游戏场景购买子弹窗口
Auth：Cool.Cat@2013-07-06
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum BuyBullet_BTN_TAG {
	BTN_Bullet100 = 1,
	BTN_Bullet500 = 6,
	BTN_Bullet2000 = 8,
	BTN_BulletOn= 11,
	BTN_BulletOff = 12
};

class SIX_PopWndBuyBullet:public SIX_PopWnd
{
public:
	SIX_PopWndBuyBullet();
	virtual ~SIX_PopWndBuyBullet();
public:
	static SIX_PopWndBuyBullet *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
	bool IsAutoBuy()const;
public:
	virtual bool init();
private:
	virtual void onEnterTransitionDidFinish();
	//void callbackSwitch(CCObject *pSender,CCControlEvent controlEvent);
	bool OnBtn(CCObject*,int tag);
	bool OnBuyBtn(int iBulletNum);
public:
	CCLabelTTF *m_pGoldCoin[3];
	// 100发子弹
	CCControlButton *m_pBullet100;
	// 500发子弹
	CCControlButton *m_pBullet500;
	// 2000发子弹
	CCControlButton *m_pBullet2000;

	CCControlButton *m_pBulletOn;
	CCControlButton *m_pBulletOff;

	//CCControlSwitch *m_switchControl;
};
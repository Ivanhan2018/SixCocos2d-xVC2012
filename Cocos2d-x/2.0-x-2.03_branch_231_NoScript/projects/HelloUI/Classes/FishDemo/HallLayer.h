#ifndef ____HALL_H____
#define ____HALL_H____

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SIX_PopWndSetting.h"
#include "SIX_PopWndBuyBullet.h"
USING_NS_CC;

class HallLayer : public CCLayer
{
public:
	HallLayer(void);
	~HallLayer(void);
	
	virtual void onEnter();
	virtual void onExit();
	void Update(float);

	CCAnimate * CreateFrameAnimate(CCSpriteFrameCache * pCache, char * pSigleName, int iSize, float fTime);
	void OnHelp(CCObject* pSender);

	void setMenuItemEx(CCMenuItemImage * pItem,int tag, float &fX, float &fY);
	static void scene();

    void ShowSetWnd(bool bShow);
	void ShowBuyBulletWnd(bool bShow);
private:
	SIX_PopWndSetting *pSetting;
    SIX_PopWndBuyBullet *pBuyBullet;
};

#endif
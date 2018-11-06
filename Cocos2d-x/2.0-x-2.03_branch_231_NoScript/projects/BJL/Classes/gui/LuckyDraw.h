//
//  FreeCoins.h
//  Game
//
//  Created by wangjun on 15-1-13.
//
//

#ifndef __Game__LuckyDraw__
#define __Game__LuckyDraw__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "common/Define.h"
#include "event/GBEvent.h"
USING_NS_CC;
USING_NS_CC_EXT;

//enum FreeCoinsTab
//{
//	FreeCoinsTabAlms,
//	FreeCoinsTabRecommend,
//	FreeCoinsTabRecommender
//};

class LuckyDraw : public cocos2d::CCLayer
{
private:
	CCSprite *pinSprite;
	CCMenu *drawMenu;
	bool canDraw;
public:
	CREATE_FUNC(LuckyDraw);
	virtual bool init();

	LuckyDraw();
	~LuckyDraw();
	void back(CCObject* obj);
	void pressDraw( CCObject* obj);
	void onEnter();
	void onExit();
	void pinMove(int tag);
	void pinMoveEnd(CCNode *obj);
	void addRandSeed();
	virtual void keyBackClicked(void);					//手机返回按钮

};

#endif /* defined(__Game__RegistScene__) */

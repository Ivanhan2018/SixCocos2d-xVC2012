//
//  FreeCoins.h
//  Game
//
//  Created by wangjun on 15-1-7.
//
//

#ifndef __Game__FreeCoins__
#define __Game__FreeCoins__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "event/GBEvent.h"
#include "gui/PromptBox.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum FreeCoinsTab
{
	FreeCoinsTabAlms,
	FreeCoinsTabRecommend,
	FreeCoinsTabRecommender
};

class FreeCoins : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(FreeCoins);
	virtual bool init();

	FreeCoins();
	~FreeCoins();

	void getAlms( CCObject* obj);
	void recommend( CCObject* obj);
	void myRecommender( CCObject* obj);
	void pressGetCoins( CCObject* obj);
	void back(CCObject* obj);
	void onCheckVersion(CCObject* obj);
	void cancelHttpRequest(CCObject *obj);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
	void onEnter();
	void onExit();

	virtual void keyBackClicked(void);					//手机返回按钮

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	FreeCoinsTab currentItem;
	CCMenuItemSprite* almsItem;
	CCMenuItemSprite* recommendItem;
	CCMenuItemSprite* recommenderItem;
	CCLabelTTF* almsText;
	CCLabelTTF* recommendText;
	CCLabelTTF* recommenderText;
	CCMenu *getCoinsMenu;
	CCEditBox *recommenderName;
	CCLabelTTF* recommenderLabel;
	PromptBox* promptBox;
	bool cancelOrNot;
};

#endif /* defined(__Game__RegistScene__) */

#pragma once

#include "cocos2d.h"
#include "CCFish.h"
#include "CCNet.h"
#include "UIRollNum.h"

USING_NS_CC;

// 鱼最大实体数量
#define MAX_ENEMY			100
// 子弹间隔延迟(ms)
#define MAX_SHOOT_DELAY		500

class SceneFish : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    

    // touch callback
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    // implement the "static node()" method manually
    CREATE_FUNC(SceneFish);

	void menuCallback(CCObject* pSender);

	void LoadTexture();
	void InitUITab();
	void AddFish();
	void Update(float);
	void Shooting(CCTouch*);

	cocos2d::CCSpriteBatchNode* netSheet;
	cocos2d::CCSpriteBatchNode* fishSheet[2];
	cocos2d::CCSpriteBatchNode* cannonSheet;

	cocos2d::CCAction* fish01_act;
	UIRollNum *score1;
	cocos2d::CCSprite* gun;

	CCMenuItemImage *pMusicItem;

	int energy;
	int maxEnergy;
	cocos2d::CCSprite* energyPtr;
	float floor;
	float m_LastShootTime;

	void showNet(cocos2d::CCObject* pSender);
	void afterShowNet(cocos2d::CCObject* pSender);
	void afterCatch(cocos2d::CCObject* pSender);
	void afterShow(cocos2d::CCObject* pSender);

	void updateEnergry(int en);

	void PlayFishHit();
};
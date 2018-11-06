//
//  GeTCHARge.h
//  Game
//
//  Created by 罗敏 on 13-8-6.
//
//

#ifndef __Game__ChongCoinsLayer__
#define __Game__ChongCoinsLayer__

#include "cocos2d.h"
#include "common/CocosUnits.h"
#include "cocos-ext.h"
USING_NS_CC;

class ChongCoinsLayer : public CCLayer
{
public:
    static ChongCoinsLayer * ChongCoinsLayerWith(CCPoint pos);
    bool initChongCoinsLayer(CCPoint pos);
    ChongCoinsLayer();
    ~ChongCoinsLayer();
	void closeChongCoinsLayer(CCObject* obj);
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
public:
    
    int currentSelct;                    //点击领取时当前领取的类型
private:


private:
    CCMenuItemSprite* m_pZJDCardItemSprite;
    CCMenuItemSprite* m_pYidongMSMItemSprite;
    CCMenuItemSprite* m_pLiantongMSMItemSprite;
    CCMenuItemSprite* m_pDianxingMSMItemSprite;
	CCMenuItemSprite* m_pPhoneCardItemSprite;
	CCMenuItemSprite* m_pAlipayMSMItemSprite;
	CCNode* m_pZJDcARD;
	CCNode* m_pYidongMSM;
	CCNode* m_pLiantongMSM;
	CCNode* m_pDianxingMSM;
	CCNode* m_pPhoneCard;
	CCNode* m_pAlipayMSM;
private:
	void showZJDCard(CCObject* obj);
	void showYidongSMS(CCObject* obj);
	void showLiantongSMS(CCObject* obj);
	void showDianxingSMS(CCObject* obj);
	void showPhoneCard(CCObject* obj);
	void showAliPay(CCObject* obj);

};

#endif /* defined(__Game__GeTCHARge__) */

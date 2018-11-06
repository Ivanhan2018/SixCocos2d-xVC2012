//
//  GeTCHARge.h
//  Game
//
//  Created by ���� on 13-8-6.
//
//

#ifndef __Game__GeTCHARge__
#define __Game__GeTCHARge__

#include "cocos2d.h"
#include "common/CocosUnits.h"
#include "cocos-ext.h"
USING_NS_CC;

class GeTCHARge : public CCLayer
{
public:
    static GeTCHARge * GeTCHARgeWith(CCPoint pos);
    bool initGeTCHARge(CCPoint pos);
    GeTCHARge();
    ~GeTCHARge();
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void geTCHARge(CCObject* obj);
    void getCoins(CCObject* obj);
    void getQB(CCObject * obj);
    void getTips(CCObject* obj);
	bool isLegal(std::string str);
	void doget(CCObject* obj);
	void showLingHuaFei();
	virtual void keyBackClicked(void);					//�ֻ����ذ�ť
public:
    void closeGeTCHARge(CCObject * obj);
    int currentSelct;                    //�����ȡʱ��ǰ��ȡ������
    
    
    CCMenu* m_pBackMenu;            //����
    CCMenu* m_pGetMenu;             //��ȡ��ť
    CCMenu* m_pDogetMenu;           //������ȡ��ť
    CCMenu* m_pGetTips;             //��׬����
    
    cocos2d::extension::CCEditBox* m_pInputBox1;
    cocos2d::extension::CCEditBox* m_pInputBox2;
    bool m_bBackMenu;
    bool m_bGetMenu;
    bool m_bInputBox1;
    bool m_bInputBox2;
    bool m_bDogetMenu;
    bool m_bGetTips;
    
private:
    bool m_bEnoughGet;
    CCLabelTTF* m_pTips11;          //�컰��
    CCSprite* m_pTips12;
    CCSprite* m_pTips13;
	CCLabelTTF* m_pTips14;

    
    CCLabelTTF* m_pTips21;          //��QB
    CCSprite* m_pTips22;
    CCSprite* m_pTips23;
	CCLabelTTF* m_pTips24;
    
    CCLabelTTF* m_pTips31;          //����
    //CCLabelTTF* m_pTips32;
	CCLabelTTF* m_pTips34;

private:
    CCMenuItemSprite* geTCHARgeItemSprite;
    CCMenuItemSprite* getcoinsItemSprite;
    CCMenuItemSprite* getQBItemSprite;
    CCMenuItemSprite* getTipsItemSprite;
};

#endif /* defined(__Game__GeTCHARge__) */

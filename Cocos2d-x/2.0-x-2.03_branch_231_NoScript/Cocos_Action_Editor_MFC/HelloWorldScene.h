#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MFC_WND_Delegate
{
public:
	virtual void Set() = 0;
	virtual void Load() = 0;
	virtual void LoadFile() = 0;
};

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // touch callback
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccMousesMoved(CCSet *pTouches, CCEvent *pEvent);

	void OnTouchLogic(CCSet *pTouches,int pEvent);

	void onEnter();

	void draw();

	void DrawPoint(ccColor4B &color,CCPoint &pt);

	CCParticleSystem *MakeParticle(CCNode *pParent,const char *plist=0);

	CCSprite *m_SpriteDragged;
	CCPoint m_LastHitPos;
	unsigned long long m_LastRefreshTime;

	CCParticleSystem* part;
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

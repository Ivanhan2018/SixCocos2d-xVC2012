#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SceneFish.h"
#include <textures\CCTextureCache.h>
#include "moveLabel.h"
#include <GUI/CCControlExtension/CCControlExtensions.h>

USING_NS_CC;
USING_NS_CC_EXT;

class SceneLogin : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual void draw();

	CCControlButton *standardButtonWithTitle(const char * title);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // touch callback
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void menuCallback(CCObject* pSender);
	void loadingCallback(CCObject *pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(SceneLogin);

	//MoveLabel m_moveLabel;

	CCMenuItemImage *pMusicItem;
};

#endif // __HELLOWORLD_SCENE_H__

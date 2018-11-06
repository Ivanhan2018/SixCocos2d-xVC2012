#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

class CLogin : public cocos2d::CCLayer, cocos2d::extension::CCEditBoxDelegate
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
    
    void RegisterCallback(CCObject* pSender, cocos2d::extension::CCControlEvent controlEvent);
	void LogoinCallback(CCObject* pSender, cocos2d::extension::CCControlEvent controlEvent);

    CREATE_FUNC(CLogin);

	CCNode * m_pDefaultEdit;
	CCNode * m_pActionEdit;

	cocos2d::extension::CCEditBox									* m_peditAccount;
	cocos2d::extension::CCEditBox									* m_peditPW;
};

#endif  // __LOGIN_SCENE_H__
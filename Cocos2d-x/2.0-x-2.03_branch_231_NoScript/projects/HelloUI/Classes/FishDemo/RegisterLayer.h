#ifndef ____REGISTER_H____
#define ____REGISTER_H____

#include "cocos2d.h"
#include "cocos-ext.h"

class RegisterLayer : public cocos2d::CCLayer, cocos2d::extension::CCEditBoxDelegate
{
public:
	RegisterLayer(void);
	~RegisterLayer(void);

	virtual void onEnter();
	virtual void onExit();

	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);

// a selector callback
    void RegisterCallback(CCObject* pSender, cocos2d::extension::CCControlEvent controlEvent);
	void CancelCallback(CCObject* pSender, cocos2d::extension::CCControlEvent controlEvent);

	static cocos2d::CCScene * scene();

	cocos2d::extension::CCEditBox				* m_peditAccount;
	cocos2d::extension::CCEditBox				* m_peditPW;
	cocos2d::extension::CCEditBox				* m_peditAgainPW;
};

#endif
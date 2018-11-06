#ifndef __Game__MenuLayler__
#define __Game__MenuLayler__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"

#include "RegistLayer.h"
class MenuLayer : public cocos2d::CCLayer
{
private:
	CCMenuItemSprite *musicItem;
	CCMenuItemSprite *effectItem;
	bool hasEffect;
	bool hasMusic;
public:
	CCMenu *pButtonMenu;
public:
	MenuLayer();
	~MenuLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();

	CREATE_FUNC(MenuLayer);

public:
	void permitButtonClick();							//允许按钮按
	void forbidButtonClick();							//禁止按钮按
	virtual void keyBackClicked(void);					//手机返回按钮
	void pressMusicItem(CCObject* obj);					//游戏背景音乐
	void pressEffectItem(CCObject* obj);					//游戏背景音乐
};
#endif  //__Game__MenuLayler__
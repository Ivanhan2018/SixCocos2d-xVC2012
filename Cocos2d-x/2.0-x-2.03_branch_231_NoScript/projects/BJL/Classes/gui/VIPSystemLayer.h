#ifndef __Game__VIPSystemLayer__
#define __Game__VIPSystemLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"

class VIPSystemLayer : public cocos2d::CCLayer
{
private:

public:
	VIPSystemLayer();
	~VIPSystemLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(VIPSystemLayer);

	virtual void keyBackClicked(void);					//手机返回按钮
public:
	void dismiss(cocos2d::CCObject *obj);
	void onDiscount(CCObject* obj);
	void onBecomeVIP(CCObject* obj);
};
#endif  //__Game__WarningLayler__
#ifndef __Game__RechargeLayer__
#define __Game__RechargeLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class RechargeLayer : public cocos2d::CCLayer
{


public:
	RechargeLayer();
	~RechargeLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(RechargeLayer);

public:
	void dismiss(cocos2d::CCObject *obj);
	void makeSure(cocos2d::CCObject *obj);
};
#endif  //__Game__RechargeLayer__
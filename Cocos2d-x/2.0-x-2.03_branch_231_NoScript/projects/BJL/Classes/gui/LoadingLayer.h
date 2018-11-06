#ifndef __Game__LoadingLayer__
#define __Game__LoadingLayer__
#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class LoadingLayer : public cocos2d::CCLayer
{

public:
	LoadingLayer();
	~LoadingLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	void update(float dt);
	CREATE_FUNC(LoadingLayer);
	void onEnter();
private:
	CCProgressTimer *pJinDuTiao;
};
#endif  //__Game__LoadingLayer__
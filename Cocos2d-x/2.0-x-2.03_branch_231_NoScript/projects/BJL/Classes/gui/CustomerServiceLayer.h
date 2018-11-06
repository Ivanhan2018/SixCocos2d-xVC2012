#ifndef __Game__CustomerServiceLayer__
#define __Game__CustomerServiceLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class CustomerServiceLayer : public cocos2d::CCLayer
{


public:
	CustomerServiceLayer();
	~CustomerServiceLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(CustomerServiceLayer);

public:
	void dismiss(cocos2d::CCObject *obj);
	void customerOnLine(cocos2d::CCObject *obj);
	void customerPhone(cocos2d::CCObject *obj);
	virtual void keyBackClicked(void);					//手机返回按钮
	
	


};
#endif  //__Game__CustomerServiceLayer__
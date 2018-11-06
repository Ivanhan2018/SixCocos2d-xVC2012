#ifndef __Game__PropLayer__
#define __Game__PropLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"


class PropLayer : public cocos2d::CCLayer
{


public:
	PropLayer();
	~PropLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PropLayer);

public:
	void dismiss(cocos2d::CCObject *obj);
	void makeSure(cocos2d::CCObject *obj);
	
private:
	cocos2d::extension::CCEditBox *m_pUserInput;
	cocos2d::extension::CCEditBox *m_pUserVerifyInput;

};
#endif  //__Game__PropLayer__
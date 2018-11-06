#ifndef __Game__AgreementLayer__
#define __Game__AgreementLayer__
#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class AgreementLayer : public cocos2d::CCLayer
{

public:
	AgreementLayer();
	~AgreementLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();

	virtual void keyBackClicked(void);					//手机返回按钮

	CREATE_FUNC(AgreementLayer);
public:

	void dismiss(cocos2d::CCObject *obj);

};
#endif  //__Game__AgreementLayer__
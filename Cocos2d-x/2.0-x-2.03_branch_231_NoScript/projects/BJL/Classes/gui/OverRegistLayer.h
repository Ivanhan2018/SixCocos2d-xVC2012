#ifndef __Game__OverRegistLayer__
#define __Game__OverRegistLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d::extension;
class OverRegistLayer: public cocos2d::CCLayer
{
private:
	cocos2d::extension::CCEditBox * m_pUserNameKuang;
	cocos2d::extension::CCEditBox * m_pPassWordKuang;
	cocos2d::extension::CCEditBox * m_pPassWordKuangOK;
public:
	OverRegistLayer();
	~OverRegistLayer();
	virtual bool init();

	CREATE_FUNC(OverRegistLayer);

	void setRegistLayerFrom(int num);

public:
	void dismiss(cocos2d::CCObject *obj);
	void showPlayerXieYi(cocos2d::CCObject *obj);

	bool isLegal(string str);



	void onOverRes(CCObject* obj);

	virtual void keyBackClicked(void);					//手机返回按钮

private:
	CCSprite* spriteSlectSex;
	int m_nRegistFrom;
	CCSize winSize;
};
#endif  //__Game__RegistLayer__
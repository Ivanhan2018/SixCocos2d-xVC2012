#ifndef __Game__HelpLayer__
#define __Game__HelpLayer__
#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class HelpLayer : public cocos2d::CCLayer
{

public:
	HelpLayer();
	~HelpLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();

	
	CREATE_FUNC(HelpLayer);
public:
	
	void dismiss(cocos2d::CCObject *obj);
	void changeTipsContent(float dt);
	void toFreeLayer(cocos2d::CCObject *obj);

	virtual void keyBackClicked(void);					//手机返回按钮

private:
	CCNode *pNode;
	float m_start;
	float m_end;

	CCLabelTTF* m_pXiaoTiShi;

};
#endif  //__Game__HelpLayer__
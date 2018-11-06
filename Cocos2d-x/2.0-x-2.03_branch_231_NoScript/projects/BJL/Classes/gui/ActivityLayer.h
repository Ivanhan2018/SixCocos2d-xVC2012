#ifndef __Game__ActivityLayer__
#define __Game__ActivityLayer__
#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include "cocos2d.h"
class ActivityLayer : public cocos2d::CCLayer
{

public:
	ActivityLayer();
	~ActivityLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(ActivityLayer);

	void changeActivity(int type);

	void leftActivity(CCObject* obj);
	void rightActivity(CCObject* obj);

	void enterActivity(CCObject* obj);

public:
	
	void dismiss(cocos2d::CCObject *obj);
	void toFreeLayer(CCObject* obj);

	virtual void keyBackClicked(void);					//手机返回按钮

private:
	CCSprite* m_pUpArrow;			//指向上面的箭头
	CCSprite* m_pWhiteBox;			//白框
	CCArray* m_ActivitySpriteArray;	//活动图片
	float m_cDistanceSize;
	int m_nSelectActivity;
	CCSize winSize;
	CCArray* m_ActivityContextArray;//活动内容
	CCLabelTTF* activityTips;

	CCMenu* m_EnterMenu;
};
#endif  //__Game__HelpLayer__
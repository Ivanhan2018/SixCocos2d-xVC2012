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

	virtual void keyBackClicked(void);					//�ֻ����ذ�ť

private:
	CCSprite* m_pUpArrow;			//ָ������ļ�ͷ
	CCSprite* m_pWhiteBox;			//�׿�
	CCArray* m_ActivitySpriteArray;	//�ͼƬ
	float m_cDistanceSize;
	int m_nSelectActivity;
	CCSize winSize;
	CCArray* m_ActivityContextArray;//�����
	CCLabelTTF* activityTips;

	CCMenu* m_EnterMenu;
};
#endif  //__Game__HelpLayer__
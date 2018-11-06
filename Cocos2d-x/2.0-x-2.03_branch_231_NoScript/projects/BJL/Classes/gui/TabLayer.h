#ifndef __Game__TabLayer__
#define __Game__TabLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include <iostream>
#include <string>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

#define TabLayerBaseTag  1

class TabLayer : public cocos2d::CCLayer
{
protected:
	int currentItem;				//���ڱ��tab�ĵ�ǰҳ Ĭ��Ϊ��һҳ0
	CCSprite * pBJ;					//����ͼƬ
	CCSprite *maskSprite;			//����ͼƬ
private:
	float tabMenuWidth;				//tab��ǩ���
	CCMenu* tabMenu;				//��ǩ��ť
	int tabNum;						//��ǩ����
	float itemGap;
	CCArray *tabMenuItem;			//��ǩ�Ӳ˵�
	CCArray *normalName;			//��ǩ����
	CCArray *selectedName;
public:
	TabLayer();
	~TabLayer();
	static TabLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	bool initWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	void setTabMenuPositionY(float yPos){tabMenu->setPositionY(yPos);};
	virtual void keyBackClicked(void);					//�ֻ����ذ�ť
public:
	void dismiss(cocos2d::CCObject *obj);
	void pressTabButton(cocos2d::CCObject *obj);
	virtual void doSomething();
	virtual void doSomethingBeforeClosed(){};
};
#endif  //__Game__WarningLayler__
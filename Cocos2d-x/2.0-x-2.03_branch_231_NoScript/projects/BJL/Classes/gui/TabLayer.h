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
	int currentItem;				//用于标记tab的当前页 默认为第一页0
	CCSprite * pBJ;					//背景图片
	CCSprite *maskSprite;			//遮罩图片
private:
	float tabMenuWidth;				//tab标签宽度
	CCMenu* tabMenu;				//标签按钮
	int tabNum;						//标签数量
	float itemGap;
	CCArray *tabMenuItem;			//标签子菜单
	CCArray *normalName;			//标签名称
	CCArray *selectedName;
public:
	TabLayer();
	~TabLayer();
	static TabLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	bool initWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	void setTabMenuPositionY(float yPos){tabMenu->setPositionY(yPos);};
	virtual void keyBackClicked(void);					//手机返回按钮
public:
	void dismiss(cocos2d::CCObject *obj);
	void pressTabButton(cocos2d::CCObject *obj);
	virtual void doSomething();
	virtual void doSomethingBeforeClosed(){};
};
#endif  //__Game__WarningLayler__
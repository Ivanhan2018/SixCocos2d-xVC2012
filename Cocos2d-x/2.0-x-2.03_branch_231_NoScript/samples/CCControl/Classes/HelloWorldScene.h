#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "cocos-ext.h"

USING_NS_CC_EXT;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

//添加一个按钮
class CCControlButtonTest_Event : public cocos2d::CCLayer
{
public:
    bool init();
    void touchDownAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragInsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragOutsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragEnterAction(CCObject *sender, CCControlEvent controlEvent);
    void touchDragExitAction(CCObject *sender, CCControlEvent controlEvent);
    void touchUpInsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchUpOutsideAction(CCObject *sender, CCControlEvent controlEvent);
    void touchCancelAction(CCObject *sender, CCControlEvent controlEvent);

    CREATE_FUNC(CCControlButtonTest_Event)
};

//添加一个滑动条
class CCControlSliderTest : public cocos2d::CCLayer
{
public:
    bool init();
    void valueChanged(CCObject *sender, CCControlEvent controlEvent);

    cocos2d::CCLabelTTF* m_pDisplayValueLabel;
    CREATE_FUNC(CCControlSliderTest)
};

//添加一个开关按钮
class CCControlSwitchTest : public cocos2d::CCLayer
{
public:
    bool init();
    // Callback for the change value. 
    void valueChanged(CCObject* sender, CCControlEvent controlEvent);

    cocos2d::CCLabelTTF* m_pDisplayValueLabel;
    CREATE_FUNC(CCControlSwitchTest)
};

//步进器
class CCControlStepperTest : public cocos2d::CCLayer
{
public:
    bool init();
    // Creates and returns a new ControlStepper. 
	cocos2d::extension::CCControlStepper* makeControlStepper();
	virtual void onExit();
    // Callback for the change value. 
    void valueChanged(CCObject *sender, CCControlEvent controlEvent);
	protected:
	// 在setDisplayValueLabel的时候，调用原有m_pDisplayValueLabel的release，并且调用新值的的retain，专用于声明protected的变量
	//具体请进源码里参考对此宏的定义
    CC_SYNTHESIZE_RETAIN(cocos2d::CCLabelTTF*, m_pDisplayValueLabel, DisplayValueLabel)
    CREATE_FUNC(CCControlStepperTest)
};

#endif  // __HELLOWORLD_SCENE_H__
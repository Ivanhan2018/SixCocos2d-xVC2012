#include "HelloWorldScene.h"
USING_NS_CC_EXT;

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

		// 'layer' is an autorelease object
        CCControlButtonTest_Event *CCControlLayer = CCControlButtonTest_Event::create();
        CC_BREAK_IF(! CCControlLayer);
		// 'layer' is an autorelease object
        CCControlSliderTest *ControlSlider = CCControlSliderTest::create();
        CC_BREAK_IF(! ControlSlider);

		CCControlSwitchTest *ControlSwitch = CCControlSwitchTest::create();
        CC_BREAK_IF(! ControlSwitch);

		CCControlStepperTest *ControlStepper = CCControlStepperTest::create();
        CC_BREAK_IF(! ControlStepper);
		
        // add layer as a child to scene
        scene->addChild(layer);
		scene->addChild(CCControlLayer);
		scene->addChild(ControlSlider);
		scene->addChild(ControlSwitch);
		scene->addChild(ControlStepper);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        //CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        //this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        //CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        //CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        //pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
       // this->addChild(pSprite, 0);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

bool CCControlButtonTest_Event::init() {

	bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
	
		CCSize Size = CCDirector::sharedDirector()->getWinSize();
        // Add the button
        CCScale9Sprite *backgroundButton = CCScale9Sprite::create("button.png");
        CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("buttonHighlighted.png");
        
        CCLabelTTF *titleButton = CCLabelTTF::create("Touch Me!", "Marker Felt", 30);

        titleButton->setColor(ccc3(159, 168, 176));
        
        CCControlButton *controlButton = CCControlButton::create(titleButton, backgroundButton);
        controlButton->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
        controlButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
        
        controlButton->setAnchorPoint(ccp(0.5f, 2));
        controlButton->setPosition(ccp(Size.width / 2.0f,Size.height / 2.0f-50));
        addChild(controlButton, 1);

		// Sets up event handlers
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchDownAction), CCControlEventTouchDown);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchDragInsideAction), CCControlEventTouchDragInside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchDragOutsideAction), CCControlEventTouchDragOutside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchDragEnterAction), CCControlEventTouchDragEnter);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchDragExitAction), CCControlEventTouchDragExit);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchUpInsideAction), CCControlEventTouchUpInside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchUpOutsideAction), CCControlEventTouchUpOutside);
        controlButton->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlButtonTest_Event::touchCancelAction), CCControlEventTouchCancel);
		        bRet = true;
    } while (0);
return bRet;

}

//������ק�¼��������ԭ����label��ʾ���¼��ĳ�������־���
void CCControlButtonTest_Event::touchDownAction(CCObject *senderz, CCControlEvent controlEvent)
{
    //m_pDisplayValueLabel->setString(CCString::createWithFormat("Touch Down")->getCString());

	CCLog(CCString::createWithFormat("Touch Down")->getCString());

}

void CCControlButtonTest_Event::touchDragInsideAction(CCObject *sender, CCControlEvent controlEvent)
{
   // m_pDisplayValueLabel->setString(CCString::createWithFormat("Drag Inside")->getCString());
		CCLog(CCString::createWithFormat("Drag Inside")->getCString());
}

void CCControlButtonTest_Event::touchDragOutsideAction(CCObject *sender, CCControlEvent controlEvent)
{
    //m_pDisplayValueLabel->setString(CCString::createWithFormat("Drag Outside")->getCString());
CCLog(CCString::createWithFormat("Drag Outside")->getCString());
}

void CCControlButtonTest_Event::touchDragEnterAction(CCObject *sender, CCControlEvent controlEvent)
{
    //m_pDisplayValueLabel->setString(CCString::createWithFormat("Drag Enter")->getCString());
	CCLog(CCString::createWithFormat("Drag Enter")->getCString());
}

void CCControlButtonTest_Event::touchDragExitAction(CCObject *sender, CCControlEvent controlEvent)
{
    //m_pDisplayValueLabel->setString(CCString::createWithFormat("Drag Exit")->getCString());
	CCLog(CCString::createWithFormat("Drag Exit")->getCString());
}

void CCControlButtonTest_Event::touchUpInsideAction(CCObject *sender, CCControlEvent controlEvent)
{
    //m_pDisplayValueLabel->setString(CCString::createWithFormat("Touch Up Inside.")->getCString());
	CCLog(CCString::createWithFormat("Touch Up Inside.")->getCString());
}

void CCControlButtonTest_Event::touchUpOutsideAction(CCObject *sender, CCControlEvent controlEvent)
{
    //m_pDisplayValueLabel->setString(CCString::createWithFormat("Touch Up Outside.")->getCString());
	CCLog(CCString::createWithFormat("Touch Up Outside.")->getCString());
}

void CCControlButtonTest_Event::touchCancelAction(CCObject *sender, CCControlEvent controlEvent)
{
    //m_pDisplayValueLabel->setString(CCString::createWithFormat("Touch Cancel")->getCString());
	CCLog(CCString::createWithFormat("Touch Cancel")->getCString());
}

bool CCControlSliderTest::init()
{
	bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

        // Add a label in which the slider value will be displayed
        m_pDisplayValueLabel = CCLabelTTF::create("Move the slider thumb!\nThe lower slider is restricted." ,"Marker Felt", 18);
		//retain��ʾ���ֶ�������ã����ⱻcocos2d�ͷ�
        m_pDisplayValueLabel->retain();
        m_pDisplayValueLabel->setAnchorPoint(ccp(0.5f, -1.0f));
        m_pDisplayValueLabel->setPosition(ccp(screenSize.width / 1.7f, screenSize.height / 2.0f));
        addChild(m_pDisplayValueLabel);

        // Add the slider
        CCControlSlider *slider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
        slider->setAnchorPoint(ccp(0.5f, 1.0f));
        slider->setMinimumValue(0.0f); // Sets the min value of range
        slider->setMaximumValue(5.0f); // Sets the max value of range
        slider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f + 16));
		slider->setTag(1);

        // When the value of the slider will change, the given selector will be call
        slider->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlSliderTest::valueChanged), CCControlEventValueChanged);

		CCControlSlider *restrictSlider = CCControlSlider::create("sliderTrack.png","sliderProgress.png" ,"sliderThumb.png");
        restrictSlider->setAnchorPoint(ccp(0.5f, 1.0f));
        restrictSlider->setMinimumValue(0.0f); // Sets the min value of range
        restrictSlider->setMaximumValue(5.0f); // Sets the max value of range
		restrictSlider->setMaximumAllowedValue(4.0f);
		restrictSlider->setMinimumAllowedValue(1.5f);
		restrictSlider->setValue(3.0f);
        restrictSlider->setPosition(ccp(screenSize.width / 2.0f, screenSize.height / 2.0f - 24));
		restrictSlider->setTag(2);

	//same with restricted
		restrictSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlSliderTest::valueChanged), CCControlEventValueChanged);

        addChild(slider);    
		addChild(restrictSlider);

        bRet = true;
    } while (0);
return bRet;

}

void CCControlSliderTest::valueChanged(CCObject *sender, CCControlEvent controlEvent)
{
	//�õ���������	
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    // Change value of label.
	if(pSlider->getTag() == 1)
		m_pDisplayValueLabel->setString(CCString::createWithFormat("Upper slider value = %.02f", pSlider->getValue())->getCString());  
	if(pSlider->getTag() == 2)
		m_pDisplayValueLabel->setString(CCString::createWithFormat("Lower slider value = %.02f", pSlider->getValue())->getCString()); 
}

//���ذ�ť
bool CCControlSwitchTest::init()
{
	bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

        CCNode *layer = CCNode::create();
        layer->setPosition(ccp (screenSize.width / 2-120, screenSize.height / 2+100));
		//�����ֶ����һ���Ӳ�������ʾ���ذ�ť��״̬
        addChild(layer, 1);
        
        double layer_width = 0;
        
        // Add the black background for the text
        CCScale9Sprite *background = CCScale9Sprite::create("buttonBackground.png");
        background->setContentSize(CCSizeMake(80, 50));
        background->setPosition(ccp(layer_width + background->getContentSize().width / 2.0f, 0));
        layer->addChild(background);
        
        layer_width += background->getContentSize().width;
        
        m_pDisplayValueLabel  = CCLabelTTF::create("#color" ,"Marker Felt" ,30);
		
        m_pDisplayValueLabel->retain();

        m_pDisplayValueLabel->setPosition(background->getPosition());
        layer->addChild(m_pDisplayValueLabel);
        
        // Create the switch������Ҫ��ƽ��ͼƬ����ʾ�ؼ�������
		//������ʽ������һ�֣����ǲ��ӱ�ǩ��ʾ��ȥ�����������������
        CCControlSwitch *switchControl = CCControlSwitch::create
            (
                CCSprite::create("switch-mask.png"),
                CCSprite::create("switch-on.png"),
                CCSprite::create("switch-off.png"),
                CCSprite::create("switch-thumb.png"),
                CCLabelTTF::create("On", "Arial-BoldMT", 16),
                CCLabelTTF::create("Off", "Arial-BoldMT", 16)
            );
        switchControl->setPosition(ccp (layer_width + 10 + switchControl->getContentSize().width / 2, 0));
        layer->addChild(switchControl);
       //���¼�
        switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlSwitchTest::valueChanged), CCControlEventValueChanged);
        
        // Set the layer size
        layer->setContentSize(CCSizeMake(layer_width, 0));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));
        
        // Update the value label��buttonһ������Ҳ�кܶ�״̬�������������ָ����ֵ�����仯��ʱ��ִ��valueChanged�еĴ���
        valueChanged(switchControl, CCControlEventValueChanged);
        bRet = true;
    } while (0);
return bRet;
}

void CCControlSwitchTest::valueChanged(CCObject* sender, CCControlEvent controlEvent)
{
	//�õ���������
    CCControlSwitch* pSwitch = (CCControlSwitch*)sender;
	//���ݰ�ť��ǰ��״̬��ʾ��ǩ����
    if (pSwitch->isOn())
    {
        m_pDisplayValueLabel->setString("On");
    } 
    else
    {
        m_pDisplayValueLabel->setString("Off");
    }
}

//���һ��������
bool CCControlStepperTest::init()
{
	bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
		//��ʼ��
	    m_pDisplayValueLabel=NULL;

        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        
        CCNode *layer = CCNode::create();
        layer->setPosition(ccp (screenSize.width / 2+100, screenSize.height / 2+100));
        this->addChild(layer, 1);
        
        double layer_width          = 0;
        
        // Add the black background for the text
        CCScale9Sprite *background  = CCScale9Sprite::create("buttonBackground.png");
        background->setContentSize(CCSizeMake(100, 50));
        background->setPosition(ccp(layer_width + background->getContentSize().width / 2.0f, 0));
        layer->addChild(background);

        //ʹ��setter����һ��������ʾ��ǰֵ��label
        this->setDisplayValueLabel(CCLabelTTF::create("0", "HelveticaNeue-Bold", 30));
        m_pDisplayValueLabel->setPosition(background->getPosition());
        layer->addChild(m_pDisplayValueLabel);
        
        layer_width  += background->getContentSize().width;
        //���ô���
        CCControlStepper *stepper   = this->makeControlStepper();
        stepper->setPosition(ccp (layer_width + 10 + stepper->getContentSize().width / 2, 0));
        stepper->addTargetWithActionForControlEvents(this, cccontrol_selector(CCControlStepperTest::valueChanged), CCControlEventValueChanged);
        layer->addChild(stepper);
        
        layer_width                 += stepper->getContentSize().width;
        
        // Set the layer size
        layer->setContentSize(CCSizeMake(layer_width, 0));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));
        
        // Update the value label
        this->valueChanged(stepper, CCControlEventValueChanged);
		bRet = true;
    } while (0);
return bRet;
}
//����Ѵ����������Ĺ��̶���������
CCControlStepper *CCControlStepperTest::makeControlStepper()
{
    CCSprite *minusSprite       = CCSprite::create("stepper-minus.png");
    CCSprite *plusSprite        = CCSprite::create("stepper-plus.png");
    
    return CCControlStepper::create(minusSprite, plusSprite);
}

void CCControlStepperTest::valueChanged(CCObject *sender, CCControlEvent controlEvent)
{
    CCControlStepper* pControl = (CCControlStepper*)sender;
    // Change value of label.
    m_pDisplayValueLabel->setString(CCString::createWithFormat("%0.02f", (float)pControl->getValue())->getCString());	
}

void CCControlStepperTest::onExit(){
	CC_SAFE_RELEASE(m_pDisplayValueLabel);
}
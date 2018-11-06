#include "HelloWorldScene.h"
#include "cocos-ext.h"
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

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

//void HelloWorld::visit()
//{
//	glEnable(GL_SCISSOR_TEST);
//	glScissor(100, 100 , 300, 300 );//x, y, w, h
//	CCLayer::visit();//调用自己的类方法
//	glDisable(GL_SCISSOR_TEST);
//}

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

//         // Create a "close" menu item with close icon, it's an auto release object.
//         CCMenuItemSprite *pCloseItem = CCMenuItemSprite::create(
//             "CloseNormal.png",
//             "CloseSelected.png",
//             this,
//             menu_selector(HelloWorld::menuCloseCallback));
//         CC_BREAK_IF(! pCloseItem);
// 
//         // Place the menu item bottom-right conner.
//         pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
// 
//         // Create a menu with the "close" menu item, it's an auto release object.
//         CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//         pMenu->setPosition(CCPointZero);
//         CC_BREAK_IF(! pMenu);
// 
//         // Add the menu to HelloWorld layer as a child layer.
//         this->addChild(pMenu, 1);
// 
//         // 2. Add a label shows "Hello World".
// 
//         // Create a label and initialize with string "Hello World".
//         CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
//         CC_BREAK_IF(! pLabel);
// 
//         // Get window size and place the label upper. 
//         CCSize size = CCDirector::sharedDirector()->getWinSize();
//         pLabel->setPosition(ccp(size.width / 2, size.height - 50));
// 
//         // Add the label to HelloWorld layer as a child layer.
//         this->addChild(pLabel, 1);
// 
//         // 3. Add add a splash screen, show the cocos2d splash image.
//         CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//         CC_BREAK_IF(! pSprite);
// 
//         // Place the sprite on the center of the screen
//         pSprite->setPosition(ccp(size.width/2, size.height/2));
// 
//         // Add the sprite to HelloWorld layer as a child layer.
//         this->addChild(pSprite, 0);
		CCSprite* sprite = CCSprite::create("background.jpg");
		sprite->setPosition(ccp(427,240));
		addChild(sprite);

		//CCSize size=CCDirector::sharedDirector()->getWinSize();
		//CCSize winRect = CCSizeMake(size.width/2,size.height/2); //设置要拉伸后的的大小  
		//CCScale9Sprite *m_pNextBG   = CCScale9Sprite::create("a.png");  
		//m_pNextBG->setPreferredSize(winRect);                 //这个是关键  
		//m_pNextBG->setPosition(ccp(size.width/2,size.height/2));  
		//this->addChild(m_pNextBG,5);  

		//CCParticleSystemQuad *system=  CCParticleSystemQuad::create("hlddz_particle/cardtype/duizi.plist");
		//system->initWithFile("hlddz_particle/cardtype/duizi.plist");//plist文件可以通过
		//system->setAutoRemoveOnFinish(true);
		//system->setDuration(-1);
		//this->addChild(system);
        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


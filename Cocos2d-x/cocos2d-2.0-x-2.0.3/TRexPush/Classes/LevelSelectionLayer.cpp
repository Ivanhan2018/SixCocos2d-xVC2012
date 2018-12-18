#include "LevelSelectionLayer.h"

#include "GameLayer.h"

#include "CCDictionary.h"
#include "Constants.h"
using namespace cocos2d;

CCScene* LevelSelectionLayer::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        LevelSelectionLayer *layer = LevelSelectionLayer::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelSelectionLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCLayer::init());
        
        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                              "CloseNormal.png",
                                                              "CloseSelected.png",
                                                              this,
                                                              menu_selector(LevelSelectionLayer::menuCloseCallback));
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
        CCLabelTTF* pLabel = CCLabelTTF::create("Level Selection", "Arial", 24);
        CC_BREAK_IF(! pLabel);
        
        // Get window size and place the label upper.
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));
        
        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);
        
        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(! pSprite);
        
        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        
        // Add the sprite to HelloWorld layer as a child layer.
        //this->addChild(pSprite, 0);
        
        //add all of the level stuff
        CCDictionary* plistDictionary = CCDictionary::createWithContentsOfFile("LevelData.plist");
        
        CCArray* stagesArray = (CCArray*)plistDictionary->objectForKey("STAGES");
        
        CCDictionary* stageData = (CCDictionary*)stagesArray->objectAtIndex(0);
        
        CCArray* levelArray = (CCArray*) stageData->objectForKey("LEVELS");
        int numLevels = levelArray->count();
        
        //how far to space the buttons
        CCSize stageButtonSize = CCSizeMake(30, 30);
        
        CCMenu* menu = CCMenu::create();
        
        for(int levelIndex = 0; levelIndex < numLevels;levelIndex++)
        {
            CCString* test = CCString::createWithFormat("%d",levelIndex);
            
            CCLabelTTF* stageLabel1 = CCLabelTTF::create(test->getCString(), FONT_NAME, STAGE_FONTSIZE);
            CCLabelTTF* stageLabel2 = CCLabelTTF::create("OH HAI DER", FONT_NAME, STAGE_FONTSIZE);
            CCMenuItemSprite* stageLabel = CCMenuItemSprite::create(stageLabel1, stageLabel2, this, menu_selector(LevelSelectionLayer::levelClickCallback));
            
            float posX = (stageButtonSize.width*1.05*(-0.5 + 1*levelIndex%2));
            float posY = (stageButtonSize.height*1.05*( 0.5-levelIndex/2));
            stageLabel->setPosition(ccp(posX, posY));
            //set the tag to be the stage index
            menu->addChild(stageLabel, 0, levelIndex);
        }
        
        this->addChild(menu);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void LevelSelectionLayer::levelClickCallback(CCObject * pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}


void LevelSelectionLayer::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


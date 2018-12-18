#include "StageSelectionLayer.h"

#include "CCDictionary.h"
#include "Constants.h"
#include <string>

#include "LevelSelectionLayer.h"

using std::string;

using namespace cocos2d;

CCScene* StageSelectionLayer::scene()
{
    CCScene * scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        StageSelectionLayer *layer = StageSelectionLayer::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageSelectionLayer::init()
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
                                                              menu_selector(StageSelectionLayer::menuCloseCallback));
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
        CCLabelTTF* pLabel = CCLabelTTF::create("Stage Selection", "Arial", 24);
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
        
        //add all of the stage buttons
        CCDictionary* plistDictionary = CCDictionary::createWithContentsOfFile("LevelData.plist");
        
        CCArray* stagesArray = (CCArray*)plistDictionary->objectForKey("STAGES");
        
        int stageCount = stagesArray->count();
        
        CCMenu* menu = CCMenu::create();
        CCSize stageButtonSize = CCSizeMake(30, 30);
        for(int stageIndex = 0; stageIndex <stageCount;stageIndex++)
        {
            CCString* test = CCString::createWithFormat("%d",stageIndex);
            
            CCLabelTTF* stageLabel1 = CCLabelTTF::create(test->getCString(), FONT_NAME, STAGE_FONTSIZE);
            CCLabelTTF* stageLabel2 = CCLabelTTF::create("OH HAI DER", FONT_NAME, STAGE_FONTSIZE);
            CCMenuItemSprite* stageLabel = CCMenuItemSprite::create(stageLabel1, stageLabel2, this, menu_selector(StageSelectionLayer::stageClickCallback));
            
            float posX = (stageButtonSize.width*1.05*(-0.5 + 1*stageIndex%2));
            float posY = (stageButtonSize.height*1.05*( 0.5-stageIndex/2));
            stageLabel->setPosition(ccp(posX, posY));
            //set the tag to be the stage index
            menu->addChild(stageLabel, 0, stageIndex);
        }
        this->addChild(menu);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void StageSelectionLayer::stageClickCallback(CCObject * pSender)
{
    
    CCDirector::sharedDirector()->replaceScene(LevelSelectionLayer::scene());
}

/*-(void) playStage: (id) sender
{
    int stageNumber = ((CCNode*) sender).tag;
    
    
    CCScene* levelSelectLayer = [LevelSelectionLayer sceneWithIndex:stageNumber];
    
    
    bool isFreeVersion = false;
#ifdef LITEVERSION
    isFreeVersion = true;
#endif
    if (isFreeVersion && stageNumber > 0)
    {
        //Show popup for new version available.
        
        UIAlertView *alert = [[[UIAlertView alloc] initWithTitle:@"Download Full Version?"
                                                         message:@"Would you like to download the full version of iQubes?"
                                                        delegate:self
                                               cancelButtonTitle:@"No"
                                               otherButtonTitles:@"YES!", nil] autorelease];
        alert.tag = 10;
        [alert show];
    }
    else {
        [[CCDirector sharedDirector] replaceScene:levelSelectLayer];
        [[SimpleAudioEngine sharedEngine] playEffect:S_BUTTONCLICK];
    }
    
}*/



void StageSelectionLayer::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


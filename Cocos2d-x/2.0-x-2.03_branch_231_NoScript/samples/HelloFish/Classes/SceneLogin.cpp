#include "SceneLogin.h"
#include <SIX_Common.h>
#include <SIX_GlobalMgr.h>

USING_NS_CC;
USING_GLOBALMGR;

CCScene* SceneLogin::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SceneLogin *layer = SceneLogin::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneLogin::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();

	SIXLog("ContentSize=%.2f/%.2f",this->getContentSize().width,this->getContentSize().height);
	SIXLog("visibleSize=%.2f/%.2f",visibleSize.width,visibleSize.height);
	SIXLog("origin=%.2f/%.2f",origin.x,origin.y);
	SIXLog("winSize=%.2f/%.2f",winSize.width,winSize.height);

    // 背景
    CCSprite* pSprite = CCSprite::create("./Scene/Loading/Loading.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite);

	// 关闭
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("./CloseNormal.png","./CloseSelected.png",this,menu_selector(SceneLogin::menuCallback));
	pCloseItem->setTag(ENUM_BTNIDX::BTN_CLOSE);
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width ,origin.y + pCloseItem->getContentSize().height/2));
	
	// 音乐图标
    pMusicItem = CCMenuItemImage::create("./music_on.png","./music_on.png",this,menu_selector(SceneLogin::menuCallback));
	pMusicItem->setTag(ENUM_BTNIDX::BTN_MUSIC_ON);
    pMusicItem->setPosition(ccp(origin.x + visibleSize.width - pMusicItem->getContentSize().width - pCloseItem->getContentSize().width,origin.y + pMusicItem->getContentSize().height/2));

	// 开始
	//CCMenuItemImage *pStartMenu = CCMenuItemImage::create("./BtnNormal.png","./BtnNormal.png",this,menu_selector(SceneLogin::menuCallback));
	CCSprite *sprStart = CCSprite::create("./Scene/Loading/BtnNormal.png");
	sprStart->getTexture()->setAntiAliasTexParameters();
	CCMenuItemSprite *pStartMenu = CCMenuItemSprite::create(sprStart,sprStart,this,menu_selector(SceneLogin::menuCallback));

	pStartMenu->setTag(ENUM_BTNIDX::BTN_START);
	pStartMenu->setPosition(ccp(origin.x + visibleSize.width/2,(origin.y+visibleSize.height/2)*3/4));

	CCString text(UT->G2U("开始游戏").c_str());
	CCLabelTTF* pStartLabel = CCLabelTTF::create(text.getCString(), "", 12);
	pStartLabel->setPosition(ccp(pStartMenu->getContentSize().width/2,pStartMenu->getContentSize().height/2+3));
	// 抗锯齿
	pStartLabel->getTexture()->setAliasTexParameters();
	pStartLabel->setColor(ccc3(255,0,0));
    pStartMenu->addChild(pStartLabel,100);

	// 设置
	//CCMenuItemImage *pOptionMenu = CCMenuItemImage::create("./BtnNormal.png","./BtnNormal.png",this,menu_selector(SceneLogin::menuCallback));
	CCSprite *sprOption = CCSprite::create("./Scene/Loading/BtnNormal.png");
	sprOption->getTexture()->setAntiAliasTexParameters();
	CCMenuItemSprite *pOptionMenu = CCMenuItemSprite::create(sprOption,sprOption,this,menu_selector(SceneLogin::menuCallback));

	pOptionMenu->setTag(ENUM_BTNIDX::BTN_CONFIG);
	//pOptionMenu->setPosition(ccp(pStartMenu->getPositionX(),pStartMenu->getPositionY()-pStartMenu->getContentSize().height));
	pOptionMenu->setPosition(ccp(origin.x + visibleSize.width/2,(origin.y+visibleSize.height/2)*3/4-70));

	text = UT->G2U("设　置").c_str();
	CCLabelTTF *pOptionLabel = CCLabelTTF::create(text.getCString(), "", 12);
	pOptionLabel->setPosition(ccp(pOptionMenu->getContentSize().width/2,pOptionMenu->getContentSize().height/2+3));
	// 抗锯齿
	pOptionLabel->getTexture()->setAliasTexParameters();
	pOptionLabel->setColor(ccc3(0,0,255));
	pOptionMenu->addChild(pOptionLabel,100);

    CCMenu* pMenu = CCMenu::create(pCloseItem, pMusicItem, pStartMenu, pOptionMenu,0);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

	//char pText[MAX_PATH] = {0};
	//sprintf_s(pText,MAX_PATH-1,"%s",CCString(UT->G2U("中文换行效果有木有？\n有了！\n中文换行效果有木有？\n有了！\n中文换行效果有木有？\n有了！\n中文换行效果有木有？\n有了！\n中文换行效果有木有？\n有了！\n")).getCString());

	//m_moveLabel.init(200,200,200,200);
	//m_moveLabel.initStr(pText,"宋体",12);
	//this->addChild(&m_moveLabel,100);

	text = UT->G2U("大家好！Hello World!!!!!山上的朋友你们好吗？").c_str();
	CCControlButton *button = standardButtonWithTitle(text.getCString());
	button->setPosition(ccp(513,100));
	button->setPreferredSize(CCSize(205,75));
	button->setZoomFactor(3.1);
	this->addChild(button);
    
    // enable standard touch
    this->setTouchEnabled(true);

	CCTextureCache::sharedTextureCache()->addImageAsync("./Scene/Scene01.jpg", this, callfuncO_selector(SceneLogin::loadingCallback));
    
	// 改成2D，默认是3D的。。。
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);

    return true;
}

CCControlButton *SceneLogin::standardButtonWithTitle(const char * title)
{
    /** Creates and return a button with a default background and title color. */
    CCScale9Sprite *backgroundButton = CCScale9Sprite::create("./Scene/Loading/BtnNormal.png");
	backgroundButton->scale9Image->getTexture()->setAntiAliasTexParameters();
	//CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("./Scene/Loading/BtnNormal.png");
    
    CCLabelTTF *titleButton = CCLabelTTF::create(title, "微软雅黑", 30);
	titleButton->getTexture()->setAntiAliasTexParameters();
    
    CCControlButton *button = CCControlButton::create(titleButton, backgroundButton);
    //button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    //button->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
    
    return button;
}

void SceneLogin::draw()
{
	//m_moveLabel.run();
}

void SceneLogin::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)(* pTouches->begin());
    CCPoint pos = touch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
    //m_moveLabel.touchDown(location.x,location.y);
	//SIXLog("ccTouchesBegan.pos[%.2f/%.2f] , location[%.2f/%.2f]", pos.x, pos.y,location.x,location.y);
}

void SceneLogin::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
	//m_moveLabel.touchUp(location.x,location.y);
	//SIXLog("ccTouchesEnded.pos[%.2f/%.2f] , location[%.2f/%.2f]", pos.x, pos.y,location.x,location.y);
}

void SceneLogin::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
	//m_moveLabel.touchMove(location.x,location.y);
	//SIXLog("ccTouchesMoved.pos[%.2f/%.2f] , location[%.2f/%.2f]", pos.x, pos.y,location.x,location.y);
}

void SceneLogin::menuCallback(CCObject* pSender)
{
	int tagId = ((CCNode*)pSender)->getTag();

	SIXLog("menuCallback.uID = %d",tagId);

	switch (tagId)
	{
	case ENUM_BTNIDX::BTN_CLOSE:
		{

			CCDirector::sharedDirector()->end();

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
		#endif
			break;
		}
	case ENUM_BTNIDX::BTN_START:
	case ENUM_BTNIDX::BTN_CONFIG:
		{
			SIXLog("volume = %.2f",pGlobalMgr->GetMusicMgr()->getBackgroundMusicVolume());
			CCDirector *pDirector = CCDirector::sharedDirector();
			pDirector->replaceScene(CCTransitionFadeBL::create(TRANSITION_DURATION,SceneFish::scene()));
			//pDirector->replaceScene(SceneFish::scene());
			pGlobalMgr->GetMusicMgr()->playBackgroundMusic(7,true);
			break;
		}
	case ENUM_BTNIDX::BTN_MUSIC_ON:
		{
			CCSprite *off = CCSprite::create("./music_off.png");
			pMusicItem->setNormalImage(off);
			pMusicItem->setTag(ENUM_BTNIDX::BTN_MUSIC_OFF);
			pGlobalMgr->GetMusicMgr()->pauseBackgroundMusic();
			break;
		}
	case ENUM_BTNIDX::BTN_MUSIC_OFF:
		{
			CCSprite *on = CCSprite::create("./music_on.png");
			pMusicItem->setNormalImage(on);
			pMusicItem->setTag(ENUM_BTNIDX::BTN_MUSIC_ON);
			pGlobalMgr->GetMusicMgr()->resumeBackgroundMusic();
			break;
		}
	}
}

void SceneLogin::loadingCallback(CCObject *pSender)
{
	SIXLog("loadingCallback");
}
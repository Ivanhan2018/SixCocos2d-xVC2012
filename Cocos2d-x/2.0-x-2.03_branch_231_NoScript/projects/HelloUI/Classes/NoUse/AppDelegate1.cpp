#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    TargetPlatform target = getTargetPlatform();
    
    if (target == kTargetIpad)
    {
        // ipad
        
        CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        
        // don't enable retina because we don't have ipad hd resource
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionNoBorder);
    }
    else if (target == kTargetIphone)
    {        
        if (CCDirector::sharedDirector()->enableRetinaDisplay(true))
        {
            // well, it's a iPhone 4, iPhone 4S or iPhone 5
            CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        }
        else
        {
            // iPhone 3GS and before, with 480x320 resolution
            CCFileUtils::sharedFileUtils()->setResourceDirectory("sd");
        }
    }
    else 
    {
        // android, windows, blackberry, linux or mac
        // use 960*640 resources as design resolution size
        CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(/*480, 320*/1024, 650, kResolutionNoBorder);//getWinSize的值
    }

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	// 加载音效
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->SetSoundResourceFolder("Music");
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->LoadXMLFromFile("Music/SoundList.xml");
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->ReleaseXML();
	SIXLog("音效总数[%d] , 背景[%d] , 特效[%d]",
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetTotalSoundCount(),
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetBgSoundCount(),
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetEffectSoundCount()
	);

	// 随机背景音乐
	int soundID = SIX_Utility::RNDNUM(0,SIX_GlobalMgr::GetInstance()->GetMusicMgr()->GetBgSoundCount());
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playBackgroundMusic(soundID);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

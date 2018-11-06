#include "SIX_World.h"
#include "SmartRes.h"
#include "SIX_SceneIntro.h"
#include "SIX_SceneLogin.h"
#include "SIX_SceneHall.h"
#include "SIX_SceneGame.h"

SIX_SceneIntro *pSceneIntro = 0;
SIX_SceneLogin *pSceneLogin = 0;
SIX_SceneHall *pSceneHall = 0;
SIX_SceneGame *pSceneGame = 0;

bool SIX_World::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    TargetPlatform target = getTargetPlatform();
    
    if (target == kTargetIpad)
    {
        // ipad
        
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        
        // don't enable retina because we don't have ipad hd resource
        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionNoBorder);
    }
    else if (target == kTargetIphone)
    {
        // iphone
        
        // try to enable retina on device
        if (true == CCDirector::sharedDirector()->enableRetinaDisplay(true))
        {
            // iphone hd
            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
        }
        else
        {
            CCFileUtils::sharedFileUtils()->setResourceDirectory("iphone");
        }
    }
    else 
    {
        // android, windows, blackberry, linux or mac
        // use 960*640 resources as design resolution size
        CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
		//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(MAX_WIDTH,MAX_HEIGHT,kResolutionShowAll);
		SmartRes::sharedRes()->setVirtualScreenWidth(MAX_WIDTH, MAX_HEIGHT);
    }

#ifdef SHOW_FPS
    // turn on display FPS
    pDirector->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	// -- 改成2D，默认是3D的。。。
	//CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
	//CCDirector::sharedDirector()->setDepthTest(false);

#ifdef WIN32
	CCString *title = CCString::createWithFormat("%s%s - [%d.%d.%d.%04d]",PROJECT_NAME,PROJECT_ALIAS,VER_MAIN,VER_CHILD,VER_STAGE,VER_BUILD);
	CCEGLView::sharedOpenGLView()->setWindowTitle(title->getCString());
	CCEGLView::sharedOpenGLView()->setWindowIcon("./iphonehd/icon.ico");
	CCEGLView::sharedOpenGLView()->setFrameSize(MAX_WIDTH,MAX_HEIGHT);
#endif

	// 切换场景吧~
	pSceneIntro = SIX_SceneIntro::scene();
	if (!pSceneIntro)
	{
		//CCMessageBox("创建场景失败！",0);
		return true;
	}

	pGlobalMgr->LoadMusic(/*SoundList.xml*/XorStr<0x5A,14,0x5D4143E2>("\x09\x34\x29\x33\x3A\x13\x09\x12\x16\x4D\x1C\x08\x0A"+0x5D4143E2).s);
	CCScene * pScene = pSceneIntro->GetScene();
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void SIX_World::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
	pGlobalMgr->GetMusicMgr()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void SIX_World::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
	pGlobalMgr->GetMusicMgr()->resumeBackgroundMusic();
}
#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();

    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    TargetPlatform target = getTargetPlatform();
    
    CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
    //CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionNoBorder);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	// -- 改成2D，默认是3D的。。。
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);

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

void AppDelegate::UpdateParticalSystem(CCParticleSystem* pNewPreview)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	HelloWorld* ptr = (HelloWorld*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0);
	if(ptr)
	{
		ptr->removeChildByTag(2,true);
		pNewPreview->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/3 + origin.y));
		ptr->addChild(pNewPreview,1,2);
	}
	else
	{
		CCLOG("Can't find Main Layer");
		CC_SAFE_DELETE(pNewPreview);
	}
}
#include "LoadingLayer.h"
#include "RoomLayer.h"
#include "PromptBox.h"
#include "entity/EntityMgr.h"
#include "TaskInfo.h"
#include "gui/LoginLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../JniHelper.h"
#endif

using namespace cocos2d;
LoadingLayer::LoadingLayer()
{

}
LoadingLayer::~LoadingLayer()
{

}
CCScene* LoadingLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		LoadingLayer *layer = LoadingLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}


bool LoadingLayer::init()
{
	bool bRet = false;
	do 
	{
		TaskInfo::ShareTaskInfo();
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pic_dating.plist");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cardtable.plist","cardtable.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("myCardtable.plist","myCardtable.png");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cardtable1.plist","cardtable1.png");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cardtable2.plist","cardtable2.png");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cardtable3.plist","cardtable3.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("face.plist","face.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("normal_button.plist","normal_button.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("plaza.plist","plaza.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite1.plist","sprite1.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite2.plist","sprite2.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("tab_button.plist","tab_button.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shop.plist","shop.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("exchange.plist","exchange.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("luckyDraw1.plist","luckyDraw1.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("luckyDraw2.plist","luckyDraw2.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("player_info.plist","player_info.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("medal.plist","medal.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("DZPKImageAdd.plist","DZPKImageAdd.png");        //dzpk
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("BaiJiaoItem.plist","BaiJiaoItem.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gameNumber.plist","gameNumber.png");
		CCUserDefault::sharedUserDefault()->getBoolForKey("ZJD_SOUNDSTATE",true);
		if(!CCUserDefault::sharedUserDefault()->getFloatForKey("ZJD_SOUNDNUM"))
		{
			CCUserDefault::sharedUserDefault()->setFloatForKey("ZJD_SOUNDNUM",0.5);
			CCUserDefault::sharedUserDefault()->flush();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
		}
		else
		{
			float dt = CCUserDefault::sharedUserDefault()->getFloatForKey("ZJD_SOUNDNUM");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(dt);
		}
		
		/**添加背景**/
	    CCSprite *pLoadingBG = CCSprite::createWithSpriteFrame(spriteFrame("dt_loading_0.jpg"));
	    pLoadingBG->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));	
		addChild(pLoadingBG);
		/**添加进度条**/
		CCSprite *pJinDuTiao0 = CCSprite::createWithSpriteFrame(spriteFrame("dt_loading_4.png"));
		pJinDuTiao0->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.45));
		addChild(pJinDuTiao0,1);

		CCSprite *pJinDuTiao1 = CCSprite::createWithSpriteFrame(spriteFrame("dt_loading_5.png"));
		pJinDuTiao = CCProgressTimer::create(pJinDuTiao1);
		/**先设置进度条从左到右走**/
		pJinDuTiao->setMidpoint(ccp(0.0f,0.0f));
		pJinDuTiao->setBarChangeRate(ccp(1,0));
		pJinDuTiao->setType(kCCProgressTimerTypeBar);
		pJinDuTiao->setPercentage(0.0f);
		pJinDuTiao->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.45)); 
		addChild(pJinDuTiao,2);

		/**设置游戏动画**/
		CCSprite *pAniSprite = CCSprite::createWithSpriteFrame(spriteFrame("dt_loading_1.png"));
		pAniSprite->setPosition(CCPointMake(winSize.width *0.60,winSize.height*0.58));
		addChild(pAniSprite,1);
		CCAnimation* animation = CCAnimation::create();//创建一个动画
		for( int i=1;i<4;i++)
		{

			//总共有14帧，并将14帧放入szName这个数组里
			char szName[100] = {0};
			sprintf(szName, "dt_loading_%d.png", i);
			animation->addSpriteFrame(spriteFrame(szName));
		}
		animation->setDelayPerUnit(0.6f /3.0f);
		animation->setLoops(-1); 
		animation->setRestoreOriginalFrame(true);
		CCAnimate* action = CCAnimate::create(animation);
		pAniSprite->runAction(action);


		/**添加文字提示**/
		CCSprite *pTextWaring = CCSprite::create("dt_loading_6.png");
		pTextWaring->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.40));
		addChild(pTextWaring,1);
	    this->scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;

}

void LoadingLayer::onEnter()
{
	CCLayer::onEnter();
	bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
	if(bRet)
	{
		int version = ((ConfigMgr::instance()->m_VersionInfo.m_nHighVersion)<<24) + ((ConfigMgr::instance()->m_VersionInfo.m_nMiddleVersion)<<16) + (ConfigMgr::instance()->m_VersionInfo.m_nLowVersion);
		//给服务端发送版本
		//EntityMgr::instance()->getDispatch()->sendGetConfigPacket(version);
	}
	else
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeServerShut);
		addChild(box,100);
	}
}
void LoadingLayer::update(float dt)
{
	float percent = pJinDuTiao->getPercentage();
	percent = percent+1.0f;
	if(percent<100.0f)
	{
		pJinDuTiao->setPercentage(percent);
		if(percent == 50.0f)
		{
			//unscheduleUpdate();
			//得到android版本
		}
	}
	else{
		this->unscheduleUpdate();
		bool bRet = EntityMgr::instance()->getDispatch()->connectLoginServer();
		if(bRet)
		{
			//EntityMgr::instance()->getDispatch()->getVersion();
			//RoomLayer* layer = RoomLayer::create();
			//layer->automaticLogin(true);
			LoginLayer *layer = LoginLayer::create();
			CCScene* pScene = CCScene::create();
			pScene->addChild(layer);
			CCTransitionFade *tScene = CCTransitionFade::create(1, pScene, ccWHITE);
			CCDirector::sharedDirector()->replaceScene(tScene); 
		}
		else
		{
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			PromptBox* box = PromptBox::PromptBoxWith(ccp(winSize.width * 0.5,winSize.height * 0.5),mPromptTypeServerShut);
			addChild(box,100);
		}
	}
}
 
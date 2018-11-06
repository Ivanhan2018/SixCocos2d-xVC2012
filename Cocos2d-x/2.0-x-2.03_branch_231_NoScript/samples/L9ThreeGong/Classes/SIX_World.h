/***********************************************
Name：魅影入口类
Desc：beginning of the world~
Auth：Cool.Cat@2013-03-15
***********************************************/
#pragma once
#include <SIX_Common.h>
#include "SIX_GlobalMgr.h"
#include <../../SIX_Framework/JNI_Interface/SIX_CCJNIHelper.h>

USING_NS_CC;
//USING_GLOBALMGR;

class SIX_World:private cocos2d::CCApplication{
public:
    SIX_World()
	{
		pGlobalMgr = SIX_GlobalMgr::GetInstance();
		SIXLog("SIX_World.Begin");
	}
    virtual ~SIX_World()
	{
		SIXLog("SIX_World.End");
		CC_SAFE_DELETE(pGlobalMgr);
		// 卸载脚本引擎
		CCScriptEngineManager::purgeSharedManager();
		// 终结引擎主循环
		CCDirector::sharedDirector()->end();
		SIXLog("Application.Exit!");
	}
	void setPlayerInfo(CCString *Name,CCString *Pass)
	{
		if (!Name || !Pass)
			return;
	}
public:
    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
private:
	SIX_GlobalMgr *pGlobalMgr;
};
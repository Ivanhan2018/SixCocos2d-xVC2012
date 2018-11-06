/***********************************************
Name：全局管理器
Desc：封装资源管理器、场景管理器，由游戏世界调用
Auth：Cool.Cat@2013-03-15
***********************************************/
#pragma once
//#include "SIX_Common.h"
#include "SIX_SceneMgr.h"
#include "SIX_MusicMgr.h"
#include "SIX_Proxy.h"
#include "SIX_FileSystem.h"

USING_NS_CC;

class SIX_GlobalMgr:public TSingleton<SIX_GlobalMgr> {
	//CONSTRUCTOR(
	//	SIX_GlobalMgr,
	//	pSceneMgr = SIX_SceneMgr::GetInstance();
	//	pMusicMgr = SIX_MusicMgr::GetInstance();
	//	SIXLog("A.pSceneMgr[0x%08X].retainCount[%d]  , pMusicMgr[0x%08X].retainCount[%d]",
	//		pSceneMgr,
	//		pSceneMgr->retainCount(),
	//		pMusicMgr,
	//		pMusicMgr->retainCount());
	//);
	//DESTRUCTOR(
	//	SIX_GlobalMgr,
	//	SIXLog("B.pSceneMgr[0x%08X].retainCount[%d]  , pMusicMgr[0x%08X].retainCount[%d]",
	//		pSceneMgr,
	//		pSceneMgr->retainCount(),
	//		pMusicMgr,
	//		pMusicMgr->retainCount());
	//	CC_SAFE_DELETE(pSceneMgr);
	//	CC_SAFE_DELETE(pMusicMgr);
	//);
public:
	SIX_GlobalMgr()
	{
		pSceneMgr = SIX_SceneMgr::GetInstance();
		pMusicMgr = SIX_MusicMgr::GetInstance();
		pProxy = SIX_Proxy::GetInstance();
		pFS = SIX_FileSystem::GetInstance();

		SIXLog("A.pSceneMgr[0x%08X].retainCount[%d]  , pMusicMgr[0x%08X].retainCount[%d] , pProxy[0x%08X].retainCount[%d] , pFS[0x%08X].retainCount[%d]",
			pSceneMgr,
			pSceneMgr->retainCount(),
			pMusicMgr,
			pMusicMgr->retainCount(),
			pProxy,
			pProxy->retainCount(),
			pFS,
			pFS->retainCount());	
	}
	~SIX_GlobalMgr()
	{
		SIXLog("B.pSceneMgr[0x%08X].retainCount[%d]  , pMusicMgr[0x%08X].retainCount[%d] , pProxy[0x%08X].retainCount[%d] , pFS[0x%08X].retainCount[%d]",
			pSceneMgr,
			pSceneMgr->retainCount(),
			pMusicMgr,
			pMusicMgr->retainCount(),
			pProxy,
			pProxy->retainCount(),
			pFS,
			pFS->retainCount());
		CC_SAFE_DELETE(pSceneMgr);
		CC_SAFE_DELETE(pMusicMgr);
		CC_SAFE_DELETE(pProxy);
		CC_SAFE_DELETE(pFS);
	}
public:
	SIX_SceneMgr *GetSceneMgr() const {return &(*pSceneMgr);}
	SIX_MusicMgr *GetMusicMgr() const {return &(*pMusicMgr);}
	SIX_Proxy *GetProxy() const {return &(*pProxy);}
	SIX_FileSystem *GetFS() const {return &(*pFS);}
public:
	// 场景管理器
	SIX_SceneMgr *pSceneMgr;
	// 音效管理器
	SIX_MusicMgr *pMusicMgr;
	// 网络管理器
	SIX_Proxy *pProxy;
	// 文件管理器
	SIX_FileSystem *pFS;
};
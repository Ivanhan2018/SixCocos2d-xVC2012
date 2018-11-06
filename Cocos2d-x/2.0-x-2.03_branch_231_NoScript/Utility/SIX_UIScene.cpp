#include "SIX_UIScene.h"

//USING_NS_CC_EXT;

SIX_UIScene::~SIX_UIScene()
{
	SIXLog("~SIX_UIScene[0x%08X].m_Scene[0x%08X].retainCount[%d]",this,m_Scene,m_Scene->retainCount());
	CC_SAFE_DELETE(m_UIManager);
}

SIX_UIScene* SIX_UIScene::scene()
{
	SIX_UIScene *pScene = new SIX_UIScene();
	//SIX_UIScene *pScene = (SIX_UIScene*)CCLayerColor::create(ccc4(255,255,255,128));
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->autorelease();
		SIXLog("SIX_UIScene[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		//CCTransitionScene *ptr = dynamic_cast<CCTransitionScene*>(pScene->GetScene());
		pScene->InitUIMgr();
		pScene->initWithColor(ccc4(255,255,255,128));
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
    return pScene;
}

void SIX_UIScene::InitUIMgr()
{
	SIXLog("场景初始化...");
	m_UIManager = new SIX_UIMgr();
	m_UIManager->SetParent(this);
	SIXLog("场景初始化...OK!");
}

void *SIX_UIScene::GetInterface(const char *pstrName)
{
	//if(!STRCMP(pstrName,"UIScene")) 
	//	return static_cast<SIX_UIScene*>(this);
	//else if(!STRCMP(pstrName,"UILayer"))
	//	return static_cast<SIX_UILayer*>(this);
	return 0;
}
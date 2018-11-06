#include "SIX_SceneIntro.h"
#include "SIX_SceneLogin.h"
#include "SIX_GlobalMgr.h"

extern SIX_SceneLogin *pSceneLogin;
extern SIX_SceneIntro *pSceneIntro;

SIX_SceneIntro::~SIX_SceneIntro()
{
	pSceneIntro = 0;
	SIXLog("~SIX_SceneIntro");
}

SIX_SceneIntro* SIX_SceneIntro::scene()
{
	SIX_SceneIntro *pScene = new SIX_SceneIntro();
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->setObjName("SIX_SceneIntro");
		pScene->autorelease();
		SIXLog("SIX_SceneIntro[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
    return pScene;
}

bool SIX_SceneIntro::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

	this->InitUIMgr();
	this->initWithColor(ccc4(255,255,255,128));

	int retv = this->GetUIMgr()->LoadXMLFromFile("Intro.xml");
	this->GetUIMgr()->ReleaseXML();
	SIXLog("SIX_SceneIntro.init.retv[%d]",retv);

	if (retv!=0)
	{
		m_Scene->release();
		return false;
	}

	return true;
}

// default implements are used to call script callback if exist
void SIX_SceneIntro::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneIntro::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneIntro::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneIntro::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneIntro::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
{
	if (nType==CCNCMOUSEMOVE)
		return;
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);

	CCLayerColor *bg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	if (!bg)
		return;
	for (unsigned int i=0;i<bg->getChildrenCount();i++)
	{
		CCControl *pControl = dynamic_cast<CCControl*>(bg->getChildren()->objectAtIndex(i));
		if (!pControl)
			continue;

		int tag = pControl->getTag();
		if (tag>=1 && tag<=5)
		{
			CCSprite *pSpr = dynamic_cast<CCSprite*>(bg->getChildByTag(tag*10));
			if (!pSpr)
				continue;
			
			pSpr->setVisible(false);

			if (pControl->isTouchInside(pTouch))
			{
				pSpr->setVisible(true);
				pControl->setUserData((void*)1);
			}
		}
	}
}

void SIX_SceneIntro::onEnter()
{
	CCLayerColor::onEnter();
	SIX_PopWnd::setPopWndCount(0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
	//setAccelerometerEnabled(true);
}

void SIX_SceneIntro::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	//SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();

#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(this);
#endif

	schedule(schedule_selector(SIX_SceneIntro::update), 0.01f);

	// 2s后切换到大厅场景
	scheduleOnce(schedule_selector(SIX_SceneIntro::ChangeNextScene),1.0f);
}

void SIX_SceneIntro::onExitTransitionDidStart()
{
	CCLayerColor::onExitTransitionDidStart();
}

void SIX_SceneIntro::onExit()
{
#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(0);
#endif
	CCLayerColor::onExit();
}

void SIX_SceneIntro::onCloseExit()
{
	CCLayerColor::onCloseExit();
}

void SIX_SceneIntro::OnNotifyCloseWndClicked(CCObject *pObj)
{
	SIXLog("断线重连失败！");
}

void SIX_SceneIntro::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			break;
		}
	}
}

void SIX_SceneIntro::update(float dt)
{
	if (SIX_Proxy::GetInstance()->IsChangeScene())
	{
		SIX_Proxy::GetInstance()->SetChangeScene(false);
			
		if (!pSceneLogin)
		{
			pSceneLogin = SIX_SceneLogin::scene();
			if (!pSceneLogin)
			{
				//CCMessageBox("创建场景失败！",0);
				return;
			}
		}
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2f,pSceneLogin->GetScene(),ccc3(255, 255, 255)));
	}
}

void SIX_SceneIntro::ChangeNextScene(float dt)
{
	SIX_Proxy::GetInstance()->SetChangeScene(true);
}
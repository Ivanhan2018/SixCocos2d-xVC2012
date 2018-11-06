#include "SIX_SceneLogin.h"
#include "SIX_SceneHall.h"
#include "SIX_PlayerMgr.h"
#include "SIX_ClientLogin.h"
#include <SIX_GlobalMgr.h>

SCENE_IDX LAST_SCENE_IDX = SCENE_IDX_LOGIN;
extern SIX_SceneHall *pSceneHall;
extern SIX_SceneLogin *pSceneLogin;

SIX_SceneLogin::~SIX_SceneLogin()
{
	pSceneLogin = 0;
	SIXLog("~SIX_SceneLogin");
}

SIX_SceneLogin* SIX_SceneLogin::scene()
{
	SIX_SceneLogin *pScene = new SIX_SceneLogin();
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->setObjName("SIX_SceneLogin");
		pScene->autorelease();
		SIXLog("SIX_SceneLogin[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
    return pScene;
}

bool SIX_SceneLogin::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

	this->InitUIMgr();
	this->initWithColor(ccc4(255,255,255,128));

	int retv = this->GetUIMgr()->LoadXMLFromFile("Login.xml");
	this->GetUIMgr()->ReleaseXML();
	SIXLog("SIX_SceneLogin.init.retv[%d]",retv);

	if (retv!=0)
	{
		m_Scene->release();
		return false;
	}

	m_pLoginPanel = 0;
	return true;
}

// default implements are used to call script callback if exist
void SIX_SceneLogin::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneLogin::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneLogin::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneLogin::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneLogin::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
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

void SIX_SceneLogin::onEnter()
{
	CCLayerColor::onEnter();
	SIX_PopWnd::setPopWndCount(0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
	//setAccelerometerEnabled(true);
}

void SIX_SceneLogin::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();

#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(this);
#endif

	schedule(schedule_selector(SIX_SceneLogin::update), 0.01f);

	// 版本信息
	CCLayerColor *pBg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	if (pBg)
	{
		CCNode *pNode = pBg->getChildByTag(1);
		if (pNode)
		{
			CCLabelTTF *pName = dynamic_cast<CCLabelTTF*>(pNode->getChildByTag(11));
			if (pName)
			{
				pName->setString(SIX_Utility::GetInstance()->G2U(PROJECT_NAME).c_str());
				SIX_Utility::GetInstance()->FixedTexParameters(pName->getTexture(),true);
			}
			CCLabelTTF *pAlias = dynamic_cast<CCLabelTTF*>(pNode->getChildByTag(12));
			if (pAlias)
			{
				pAlias->setString(SIX_Utility::GetInstance()->G2U(PROJECT_ALIAS).c_str());
				SIX_Utility::GetInstance()->FixedTexParameters(pAlias->getTexture(),true);
			}
			CCLabelTTF *pVersion = dynamic_cast<CCLabelTTF*>(pNode->getChildByTag(13));
			if (pVersion)
			{
				pVersion->setString(CCString::createWithFormat(SIX_Utility::GetInstance()->G2U(/*v %d.%d.%d.%d*/XorStr<0xEA,14,0xF11BCE52>("\x9C\xCB\xC9\x89\xC0\xCA\x94\xDF\xD7\x97\xDA\xD0\x92"+0xF11BCE52).s).c_str(),VER_MAIN,VER_CHILD,VER_STAGE,VER_BUILD)->getCString());
				SIX_Utility::GetInstance()->FixedTexParameters(pVersion->getTexture(),true);
			}
		}
	}

	//// tile
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	//CCRect rc = CCRectMake(0,0,size.width,size.height);
	//CCSprite *pBG = CCSprite::create("function_bg.png",rc);
	//pBG->ignoreAnchorPointForPosition(true);
	//ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT,GL_REPEAT};
	//pBG->getTexture()->setTexParameters(&tp);
	//this->addChild(pBG);
}

void SIX_SceneLogin::onExitTransitionDidStart()
{
	CCLayerColor::onExitTransitionDidStart();
}

void SIX_SceneLogin::onExit()
{
	CC_SAFE_RELEASE(m_pLoginPanel);
#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(0);
#endif
	CCLayerColor::onExit();
}

void SIX_SceneLogin::onCloseExit()
{
	SIX_ClientLogin::GetInstance()->Disconnect();
	CCLayerColor::onCloseExit();
}

void SIX_SceneLogin::OnNotifyCloseWndClicked(CCObject *pObj)
{
	SIXLog("断线重连失败！");
}

#ifdef WIN32
int SIX_SceneLogin::OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam )
{
	//SIXLog("SIX_SceneLogin.OnAccelerometerKeyHook.MSG[%u].wParam[%u].lParam[%ul]",message,wParam,lParam);
	switch (message)
	{
	/*case WM_KEYDOWN:*/
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_TAB:
				{
					if (m_pLoginPanel && m_pLoginPanel->IsShow())
						m_pLoginPanel->DoSwitchIMEFocus();
					break;
				}
			case VK_RETURN:
				{
					if (m_pLoginPanel && m_pLoginPanel->IsShow())
					{
						m_pLoginPanel->setCheckStatus(BTN_SUBMIT);
						m_pLoginPanel->DoLogin();
						break;
					}
				}
				break;
			}
		}
        break;
	}
	return 0;
}
#endif

void SIX_SceneLogin::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControlButton *pBtn = (CCControlButton*)pSender;
	int tag = pBtn->getTag();

	// 按钮音效
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(100,false);

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
				// 游客身份登录
			case BTN_LOGIN_AS_GUEST:
				{
					// 请求登录服务器，获取房间列表
					SIX_ClientLogin::GetInstance()->Connect(false);
					break;
				}
				// 用户身份登录
			case BTN_LOGIN_AS_MEMBER:
				{
					// 用户登录面板
					if (!strlen(SIX_PlayerMgr::GetInstance()->getMyName()) || !strlen(SIX_PlayerMgr::GetInstance()->getMyPass()))
					{
						if (!m_pLoginPanel)
						{
							m_pLoginPanel = SIX_LoginPanel::Create(0.0f,0.0f,ccc4(0,0,0,0),623,423,50.0f,MOVABLE_TOP,MOVABLE_TOP,true);
							m_pLoginPanel->InitMask(ccc4(0,0,0,128));
							m_pLoginPanel->backgroundWithFile("box_bg.png");
							m_pLoginPanel->buttonSubmitWithFileCell("login_btn_login.png",2);
							m_pLoginPanel->GetBtnSubmit()->setPosition(ccp(122,85));
							m_pLoginPanel->buttonCloseWithFileCell("btn_close.png",2);
							m_pLoginPanel->GetBtnClose()->setPosition(ccp(590,392));
							m_pLoginPanel->setAllowDragged(false);
							//m_pLoginPanel->setRectDirty();
						}
						m_pLoginPanel->Show();
						m_pLoginPanel->DoShowLogin();
					}
					break;
				}
			}
			break;
		}
	}
}

void SIX_SceneLogin::update(float dt)
{
	if (SIX_Proxy::GetInstance()->IsChangeScene())
	{
		SIX_Proxy::GetInstance()->SetChangeScene(false);

		if (!pSceneHall)
		{
			pSceneHall = SIX_SceneHall::scene();
			if (!pSceneHall)
			{
				//CCMessageBox("创建场景失败！",0);
				return;
			}
		}
		LAST_SCENE_IDX = SCENE_IDX_LOGIN;
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2f,pSceneHall->GetScene(),ccc3(255, 255, 255)));
	}
}

void SIX_SceneLogin::DoChangeScene()
{
	// 隐藏登录面板
	if (this->getLoginPanel())
	{
		this->getLoginPanel()->DoShowLogin(false);
		this->getLoginPanel()->DoShowReg(false);
		this->getLoginPanel()->DoShowReset(false);
	}

	// 背景
	CCLayerColor *pBg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	if (pBg)
	{
		CCNode *pBtnArea = pBg->getChildByTag(4);
		if (pBtnArea)
		{
			// 隐藏底部按钮
			CCControlButton *pBtnGuest = dynamic_cast<CCControlButton*>(pBtnArea->getChildByTag(BTN_LOGIN_AS_GUEST));
			if (pBtnGuest)
			{
				pBtnGuest->setVisible(false);
				pBtnGuest->setTouchEnabled(false);
			}

			CCControlButton *pBtnMember = dynamic_cast<CCControlButton*>(pBtnArea->getChildByTag(BTN_LOGIN_AS_MEMBER));
			if (pBtnMember)
			{
				pBtnMember->setVisible(false);
				pBtnMember->setTouchEnabled(false);
			}
		}

		// Loading过度动画
		CCNode *pLoadingArea = CCNode::create();
		pLoadingArea->setVisible(true);
	}

	// 切换到大厅场景
	SIX_Proxy::GetInstance()->SetChangeScene(true);
}
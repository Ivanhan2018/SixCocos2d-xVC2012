#include "SIX_SceneGate.h"
//#include "SIX_SceneRoom.h"
#include "SIX_SceneGame.h"
#include <SIX_GlobalMgr.h>

SCENE_IDX LAST_SCENE_IDX = SCENE_IDX_GATE;

extern SIX_SceneGate *pSceneGate;
//extern SIX_SceneRoom *pSceneRoom;
extern SIX_SceneGame *pSceneGame;

SIX_SceneGate::~SIX_SceneGate()
{
	pSceneGate = 0;
	SIXLog("~SIX_SceneGate");
}

SIX_SceneGate* SIX_SceneGate::scene()
{
	SIX_SceneGate *pScene = new SIX_SceneGate();
	//SIX_UIScene *pScene = (SIX_UIScene*)CCLayerColor::create(ccc4(255,255,255,128));
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->setObjName("SIX_SceneGate");
		pScene->autorelease();
		SIXLog("SIX_SceneGate[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		//CCTransitionScene *ptr = dynamic_cast<CCTransitionScene*>(pScene->GetScene());
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
    return pScene;
}

bool SIX_SceneGate::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

	this->InitUIMgr();
	this->initWithColor(ccc4(255,255,255,128));

	int retv = this->GetUIMgr()->LoadXMLFromFile("Gate.xml");
	this->GetUIMgr()->ReleaseXML();
	SIXLog("SIX_SceneGate.init.retv[%d]",retv);

	if (retv!=0)
		return false;

	pConsole = 0;
	m_ref = 0;
	pSetting = 0;
	pRoomList = 0;
	m_pRank = 0;
	m_pLoginPanel = 0;

	// 全局的东西要初始化
	SIX_PlayerMgr::GetInstance()->setMyTableIdx(-1);
	SIX_PlayerMgr::GetInstance()->setMySeatIdx(-1);
	//SIX_PlayerMgr::GetInstance()->setMyUserIdx(-1);

	//CCControlButton *pBtn = CCControlButton::create("wtf","微软雅黑",24);
	//pBtn->setPosition(ccp(100,100));
	//pBtn->addTargetWithActionForControlEvents(pBtn,cccontrol_selector(SIX_SceneGate::doEvents),32);
	//this->addChild(pBtn);
	////pBtn->setVisible(false);

	return true;
}

void SIX_SceneGate::dropStone(int x, int y, int stoneSize, int stoneWeight)
{
	//CCLayerColor *bg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	//if (!bg)
	//	return;
	//CCSprite *pBackground = dynamic_cast<CCSprite*>(bg->getChildren()->objectAtIndex(0));
	//if (pBackground)
	//{
	//	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//	CCSprite *pDummy = dynamic_cast<CCSprite*>(bg->getChildByTag(0));
	//	if (!pDummy)
	//	{
	//		CCRect copy = CCRectZero;
	//		copy.size = CCSize(200,200);
	//		copy.origin = ccp(x,y);
	//		pDummy = CCSprite::createWithTexture(pBackground->getTexture(),copy);
	//		if (!pDummy)
	//			return;
	//		pDummy->setTag(0);
	//		pDummy->setAnchorPoint(ccp(0.5,0.5));
	//		pDummy->setRectDirty();
	//		bg->addChild(pDummy);
	//	}
	//	CCActionInterval *pAction = dynamic_cast<CCActionInterval*>(pDummy->getActionByTag(0));
	//	if (!pAction)
	//	{
	//		pDummy->setPosition(ccp(x,y));
	//		float t = 3.0f;
	//		pAction = CCRipple3D::create(CCPointMake(size.width/2,size.height/2), 240, 4, 160, ccg(32,32), t);
	//		//CCActionInterval *pAction = CCWaves::create(4, 20, true, true, ccg(16,12), t);
	//		//CCActionInterval *pAction = CCLens3D::create(CCPointMake(size.width/2,size.height/2), 240, ccg(15,10), t);
	//		pAction->setTag(0);
	//		pDummy->runAction(pAction);
	//	}
	//}
    pRipple->dropStone(x, y, stoneSize, stoneWeight);
}

// default implements are used to call script callback if exist
void SIX_SceneGate::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int xw = size.width/gridWidth;
    int yh = size.height/gridHeight;
    int x = pos.x/xw;
    int y = pos.y/yh;

	dropStone(x, y, 3, 64);
}

void SIX_SceneGate::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int xw = size.width/gridWidth;
    int yh = size.height/gridHeight;
    int x = pos.x/xw;
    int y = pos.y/yh;

    dropStone(x, y, 2, 32);
}

void SIX_SceneGate::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneGate::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneGate::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
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

	//if (m_ref%10==0)
	//{
	//	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//	int xw = size.width/gridWidth;
	//	int yh = size.height/gridHeight;
	//	int x = pos.x/xw;
	//	int y = pos.y/yh;

	//	dropStone(x, y, 2, 32);
	//	m_ref = 0;
	//}
	//m_ref++;
}

void SIX_SceneGate::onEnter()
{
	CCLayerColor::onEnter();
	SIX_PopWnd::setPopWndCount(0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
	//setAccelerometerEnabled(true);
}

void SIX_SceneGate::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();

	if (!pRoomList)
	{
		float width = 872.0f;
		float height = 605.0f;
		pRoomList = SIX_RoomList::Create(0.0f,0.0f,ccc4(0,0,0,0),width,height,50.0f,MOVABLE_LEFT,MOVABLE_RIGHT,true);
		pRoomList->InitMask(ccc4(0,0,0,128));
		pRoomList->backgroundWithFile("Scene/Room/bg.png");
		pRoomList->buttonCloseWithFileCell("Scene/Room/close.png",3);
		pRoomList->GetBtnClose()->setPosition(ccp(817,530));

		width = 868.0f;
		height = 517.0f;
		m_pMatchList = SIX_MatchList::Create(0.0f,0.0f,ccc4(0,0,0,0),width,height,50.0f,MOVABLE_LEFT,MOVABLE_RIGHT,true);
		m_pMatchList->InitMask(ccc4(0,0,0,128));
		m_pMatchList->backgroundWithFile("Scene/Room/matchlistBG.png");
		m_pMatchList->buttonCloseWithFileCell("Scene/Room/close.png",3);
		m_pMatchList->GetBtnClose()->setPosition(ccp(710+73,388+55));

		// 只请求一次房间列表
		if (!SIX_ClientLogin::GetInstance()->getRoomListRequested())
		{
			if (strlen(SIX_PlayerMgr::GetInstance()->getMyName()) &&
				strlen(SIX_PlayerMgr::GetInstance()->getMyPass()))
			{
				// 请求登录服务器，获取房间列表
				SIX_ClientLogin::GetInstance()->Connect();
			}
		}
	}

#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(this);
#endif

	CCLayerColor *bg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	if (bg)
	{
		for (unsigned int i=0;i<bg->getChildrenCount();i++)
		{
			CCControlButton *pButton = dynamic_cast<CCControlButton*>(bg->getChildren()->objectAtIndex(i));
			if (!pButton)
				continue;
			pButton->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_SceneGate::doEvents),CCControlEventTouchUpInside);
		}

		CCSprite *pBackground = dynamic_cast<CCSprite*>(bg->getChildren()->objectAtIndex(0));
		if (pBackground)
		{
			gridWidth = 60;
			gridHeight = 40;
			ccGridSize m_sGridSize = ccg(gridWidth,gridHeight);
			pRipple = SIX_RippleGrid3D::create(m_sGridSize);
			pRipple->setActive(true);
			pRipple->retain();
			pBackground->setGrid(pRipple);
		}
	}

	schedule(schedule_selector(SIX_SceneGate::update), 0.01f);

	// 用户登录面板
	if (!strlen(SIX_PlayerMgr::GetInstance()->getMyName()) || !strlen(SIX_PlayerMgr::GetInstance()->getMyPass()))
	{
		if (!m_pLoginPanel)
		{
			m_pLoginPanel = SIX_LoginPanel::Create(0.0f,0.0f,ccc4(0,0,0,0),426,292,50.0f,MOVABLE_TOP,MOVABLE_TOP,true);
			m_pLoginPanel->InitMask(ccc4(0,0,0,128));
			m_pLoginPanel->backgroundWithFile("Scene/Gate/loginBG.png");
			m_pLoginPanel->buttonSubmitWithFileCell("Scene/Gate/LoginBTN.png",4);
			m_pLoginPanel->GetBtnSubmit()->setPosition(ccp(280,10));
			m_pLoginPanel->buttonCloseWithFileCell("Scene/Room/close.png",3);
			m_pLoginPanel->GetBtnClose()->setPosition(ccp(375,240));
			m_pLoginPanel->setAllowDragged(false);
		}
		m_pLoginPanel->Show();
	}
}

void SIX_SceneGate::onExitTransitionDidStart()
{
	CCLayerColor::onExitTransitionDidStart();
}

void SIX_SceneGate::onExit()
{
	CC_SAFE_RELEASE(pSetting);
	CC_SAFE_RELEASE(pRoomList);
	CC_SAFE_RELEASE(m_pMatchList);
	CC_SAFE_RELEASE(pConsole);
	CC_SAFE_RELEASE(m_pLoginPanel);
#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(0);
#endif
	CCLayerColor::onExit();
}

void SIX_SceneGate::onCloseExit()
{
	SIX_ClientLogin::GetInstance()->Disconnect();
	SIX_ClientRoom::GetInstance()->Disconnect();
	CCLayerColor::onCloseExit();
}

void SIX_SceneGate::OnNotifyCloseWndClicked(CCObject *pObj)
{
	SIXLog("断线重连失败！");
}

#ifdef WIN32
int SIX_SceneGate::OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam )
{
	//SIXLog("SceneRoom.OnAccelerometerKeyHook.MSG[%u].wParam[%u].lParam[%ul]",message,wParam,lParam);
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
					if (pConsole && pConsole->IsShow())
					{
						pConsole->DoEnter();
						break;
					}
					if (m_pLoginPanel && m_pLoginPanel->IsShow())
					{
						m_pLoginPanel->DoLogin();
						break;
					}
				}
				break;
			case VK_F1:
				{
					ShowConsole();
					// hook
					return 1;
				}
			break;
			}
		}
        break;
	}
	return 0;
}

void SIX_SceneGate::OnProcessCommand(const char *cmd)
{
	if (!pConsole)
		return;

	string cmdCon(SIX_Utility::GetInstance()->U2G(cmd).c_str());
	std::transform(cmdCon.begin(),cmdCon.end(),cmdCon.begin(),::tolower);

	pConsole->setContent(/*>%s*/XorStr<0x45,4,0xFDA42D40>("\x7B\x63\x34"+0xFDA42D40).s,cmdCon.c_str());

	if (cmdCon==/*version*/XorStr<0x28,8,0x72481B50>("\x5E\x4C\x58\x58\x45\x42\x40"+0x72481B50).s || 
		cmdCon==/*ver*/XorStr<0xBC,4,0x028FBFDA>("\xCA\xD8\xCC"+0x028FBFDA).s)
	{
		pConsole->setContent(/*---------------------------------------*/XorStr<0x40,40,0x7140E047>("\x6D\x6C\x6F\x6E\x69\x68\x6B\x6A\x65\x64\x67\x66\x61\x60\x63\x62\x7D\x7C\x7F\x7E\x79\x78\x7B\x7A\x75\x74\x77\x76\x71\x70\x73\x72\x4D\x4C\x4F\x4E\x49\x48\x4B"+0x7140E047).s);
		pConsole->setContent(/*版本：%d.%d.%d.%04d*/XorStr<0xBC,20,0x0A511B50>("\x0C\x5B\x0F\x01\x63\x7B\xE7\xA7\xEA\xE0\xA2\xE9\xED\xAD\xE4\xEE\xFC\xF9\xAA"+0x0A511B50).s,VER_MAIN,VER_CHILD,VER_STAGE,VER_BUILD);
		pConsole->setContent(/*---------------------------------------*/XorStr<0x40,40,0x7140E047>("\x6D\x6C\x6F\x6E\x69\x68\x6B\x6A\x65\x64\x67\x66\x61\x60\x63\x62\x7D\x7C\x7F\x7E\x79\x78\x7B\x7A\x75\x74\x77\x76\x71\x70\x73\x72\x4D\x4C\x4F\x4E\x49\x48\x4B"+0x7140E047).s);
	}
	else if (cmdCon==/*exit*/XorStr<0x29,5,0x39578028>("\x4C\x52\x42\x58"+0x39578028).s)
	{
		SIXLog("Sayonara!");
		SIX_ClientLogin::GetInstance()->Disconnect();
		SIX_ClientRoom::GetInstance()->Disconnect();
		CCDirector::sharedDirector()->end();
	}
	// balabala
	// ...
	else
	{
		bool IsValid = false;
		MP *mp = new MP();
		int count = SIX_Utility::GetInstance()->Split(" ",(char *)(cmdCon.c_str()),mp);
		switch (count)
		{
		case 2:
			{
				const char *key = mp->at(0).c_str();
				if (!STRCMP(key,"dirty"))
				{
					int value = atoi(mp->at(1).c_str());
					this->getParent()->setRectDirty((value==0)?false:true);
					IsValid = true;
				}
				else if (!STRCMP(key,"bbox"))
				{
					int value = atoi(mp->at(1).c_str());
					this->getParent()->setBBoxDirty((value==0)?false:true);
					IsValid = true;
				}
				else if (!STRCMP(key,"box"))
				{
					CCLayerColor *bg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
					if (!bg)
						return;

					int value = atoi(mp->at(1).c_str());
					for (unsigned int i=0;i<bg->getChildrenCount();i++)
					{
						CCControlButton *pButton = dynamic_cast<CCControlButton*>(bg->getChildren()->objectAtIndex(i));
						if (!pButton)
							continue;
						if (value==0)
							pButton->setRectDirty(false);
						else
							pButton->setRectDirty(true);
					}
					IsValid = true;
				}
				break;
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
		if (!IsValid)
			pConsole->setContent(/*Unknown.Command!*/XorStr<0x4C,17,0x139B5D35>("\x19\x23\x25\x21\x3F\x26\x3C\x7D\x17\x3A\x3B\x3A\x39\x37\x3E\x7A"+0x139B5D35).s);
	}
}
#endif

void SIX_SceneGate::ShowConsole()
{
	if (!pConsole)
	{
		pConsole = SIX_ConsoleGM::Create(112.0,125.0,ccc4(0,0,0,128),800.0,400.0,true);
		pConsole->InitMask(ccc4(0,0,0,128));
	}
	pConsole->ShowConsole(this);
}

bool IsSet = false;
void SIX_SceneGate::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			//SIXLog("SIX_SceneGate.doEvents.pSender[0x%08X].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,event,tag);

			if (tag>=1 && tag<5)
			{
				//SIX_Proxy::GetInstance()->SetChangeScene(true);

				//SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();
				//return;

				pRoomList->setGateIdx(tag);
				pRoomList->Show();

				//if (!pSetting)
				//{
				//	pSetting = SIX_PopWndSetting::Create(0.0,0.0,ccc4(0,0,0,0),384,223,false);
				//	pSetting->InitMask(ccc4(0,0,0,128));
				//	pSetting->backgroundWithFile("Common/Setting/popwnd.png");
				//	pSetting->buttonSubmitWithFileCell("Common/Setting/btn_ok.png",3);
				//	pSetting->GetBtnSubmit()->setPosition(ccp(275,5));
				//	//pSetting->buttonCancelWithFileCell("Common/Setting/btn_cancel.png",4);
				//	//pSetting->AutoCaclBtnPosWidthYesOrNo(45,20);
				//}
				//pSetting->Show();
			}
			else if (5 == tag)
			{
				m_pMatchList->setGateIdx(tag);
				m_pMatchList->Show();
			}
			else if (6 == tag)
			{
				if (NULL == m_pRank)
				{
					m_pRank = SIX_PopWndRank::Create(0, 0, ccc4(0,0,0,0), 887, 597, false, false);
					m_pRank->InitMask(ccc4(0,0,0,128));
					m_pRank->backgroundWithFile("Common/Rank/BG.png");
					m_pRank->SetMyselfID( SIX_PlayerMgr::GetInstance()->getMyUserIdx() );
				}
				m_pRank->Show( true );
				break;
			}
		}
	}
}

void SIX_SceneGate::update(float dt)
{
	if (SIX_Proxy::GetInstance()->IsChangeScene())
	{
		SIX_Proxy::GetInstance()->SetChangeScene(false);
			
		// 切换到桌子场景
		LAST_SCENE_IDX = SCENE_IDX_GATE;

		if (!pSceneGame)
		{
			pSceneGame = SIX_SceneGame::scene();
			if (!pSceneGame)
			{
				//CCMessageBox("创建场景失败！",0);
				return;
			}
		}
		//CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2f,pSceneRoom->GetScene(),ccc3(255, 255, 255)));
		CCDirector::sharedDirector()->replaceScene( CCTransitionFadeBL::create(1.2f,pSceneGame->GetScene()));
	}
	else
		pRipple->update(dt);
}
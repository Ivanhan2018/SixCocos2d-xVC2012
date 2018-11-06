#include "SIX_Common.h"
#include "SIX_SceneGame.h"
#include "SIX_SceneHall.h"
#include <SIX_GlobalMgr.h>
#include <SIX_CardPlay.h>
#include "SIX_ClientRoom.h"
#include "SIX_PlayerMgr.h"

extern SCENE_IDX LAST_SCENE_IDX;
extern SIX_SceneHall *pSceneHall;
extern SIX_SceneGame *pSceneGame;

SIX_SceneGame::~SIX_SceneGame()
{
	pSceneGame = 0;
	SIXLog("~SIX_SceneGame");
}

SIX_SceneGame* SIX_SceneGame::scene()
{
	SIX_SceneGame *pScene = new SIX_SceneGame();
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->setObjName("SIX_SceneGame");
		pScene->autorelease();
		SIXLog("SIX_SceneGame[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
    return pScene;
}

bool SIX_SceneGame::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

	pCountDown = 0;
	pCountDownBatchNode = 0;
	pWndPlayerInfo = 0;
	pBackground = 0;
	pNodeTable = 0;
	pNodeShuffle = pNodeDice = 0;
	//pSpriteReady = 0;
	pBtnReady = pBtnRubCancel = pBtnRubSubmit = 0;
	pSpriteChip = 0;
	pBtnChipin1 = pBtnChipin2 = pBtnChipin3 = 0;
	pBtnKill=0;
	m_pWndMsg = 0;
	m_pTipsPopWnd = 0;
	m_pTipsShowCard = 0;
	m_ptCartTypeExplanation.setPoint(0.0f,0.0f);

	this->InitUIMgr();
	this->initWithColor(ccc4(255,255,255,128));

	int retv = this->GetUIMgr()->LoadXMLFromFile("Game.xml");
	this->GetUIMgr()->ReleaseXML();
	SIXLog("SIX_SceneGame.init.retv[%d]",retv);

	if (retv!=0)
	{
		m_Scene->release();
		return false;
	}

	return true;
}

// ����UI����Ϸ��ʼǰ״̬
void SIX_SceneGame::resetUI(bool bShow,bool bClearPlayerZone)
{
	this->showBtnChipin(bShow);
	this->showBtnReady(bShow);
	// ����ʱ
	this->showCountDown(bShow);
	this->showBtnRubBanker(bShow);
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		if (bClearPlayerZone)
			this->showPlayerZoneShow(i,bShow);
		this->showCardSuit(i,bShow);
		this->showStatsPanel(i,0,false,false,false);
		this->SetChipPanelNumber(i,0,bShow);
	}
	this->showNodeDice(bShow);
	this->showNodeShuffle(bShow);
	//this->showSprReady(false);
	this->showSprChip(bShow);
}

#ifdef WIN32
int SIX_SceneGame::OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_RETURN:
				{
					if (m_pWndMsg)
						m_pWndMsg->DoEnter();
					break;
				}
			}
			break;
		}
	}
	return 0;
}
#endif

// default implements are used to call script callback if exist
void SIX_SceneGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneGame::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneGame::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
{
	if (nType==CCNCMOUSEMOVE)
		return;
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);

	//CCLayerColor *bg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	//if (!bg)
	//	return;
	//for (unsigned int i=0;i<bg->getChildrenCount();i++)
	//{
	//	CCControl *pControl = dynamic_cast<CCControl*>(bg->getChildren()->objectAtIndex(i));
	//	if (!pControl)
	//		continue;

	//	int tag = pControl->getTag();
	//	if (tag>=1 && tag<=5)
	//	{
	//		CCSprite *pSpr = dynamic_cast<CCSprite*>(bg->getChildByTag(tag*10));
	//		if (!pSpr)
	//			continue;
	//		
	//		pSpr->setVisible(false);

	//		if (pControl->isTouchInside(pTouch))
	//		{
	//			pSpr->setVisible(true);
	//			pControl->setUserData((void*)1);
	//		}
	//	}
	//}
}

void SIX_SceneGame::onEnter()
{
	CCLayerColor::onEnter();
	SIX_PopWnd::setPopWndCount(0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
	//setAccelerometerEnabled(true);
	CCDirector::sharedDirector()->SetExitProxy(SIX_SceneGame::OnExitBtn);
}

void SIX_SceneGame::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	//SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();

#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(this);
#endif

	schedule(schedule_selector(SIX_SceneGame::update), 0.01f);

	// �����л�����������
	// Cool.Cat
	SIX_PlayerMgr::GetInstance()->setAllowChangeToHall(true);

	//// tile
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	//CCRect rc = CCRectMake(0,0,size.width,size.height);
	//CCSprite *pBG = CCSprite::create("function_bg.png",rc);
	//pBG->ignoreAnchorPointForPosition(true);
	//ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT,GL_REPEAT};
	//pBG->getTexture()->setTexParameters(&tp);
	//this->addChild(pBG);

	m_pWndMsg = SIX_PopWndMessage::Create(0.0f,0.0f,ccc4(0,0,0,0),0.0f,0.0f,50.0f,MOVABLE_TOP,MOVABLE_TOP, true);
	m_pWndMsg->setInformationDelegate(this);

	// ����ʱ
	FRAMECACHE_INFO *pFrameCacheInfo = new FRAMECACHE_INFO();
	pFrameCacheInfo->m_autorelease = false;
	pFrameCacheInfo->m_file.append("countdown.plist");
	SIX_CacheMgr::GetInstance()->Load(this,pFrameCacheInfo);

	// ����
	pFrameCacheInfo = new FRAMECACHE_INFO();
	pFrameCacheInfo->m_autorelease = false;
	pFrameCacheInfo->m_file.append("dice.plist");
	SIX_CacheMgr::GetInstance()->Load(this,pFrameCacheInfo);

	pBackground = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	if (!pBackground)
		return;

	// ����UI�����ƶѵ�SIX_CardPlay
	if (ParseAndBindUIToCardPlay()!=0)
	{
		SIXLog("��Ϸ������Ϣ����");
		return;
	}

	// UI��ʼ�������أ�����ͷ����Ϣ����
	this->resetUI(false);

	// ˢ�µ�ǰ���������û�UI��Ϣ
	// Cool.Cat
	SinglePlayer *pPlayer = 0;
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[i];
		SIXLog("pPlayer[%d].iTableId[%d].SeatId[%d].UserIdx[%lld].szName[%s].szNickname[%s]",
			i,
			pPlayer->iTableId,
			pPlayer->SeatId,
			pPlayer->UserIdx,
			pPlayer->szName,
			pPlayer->szNickname);

		if (pPlayer && pPlayer->UserIdx)
		{
			// ˢ����Ϸ����UI
			int ViewID=SIX_PlayerMgr::getViewID(pPlayer->SeatId,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
			// �û���Ϣ����ʾ
			this->showPlayerZoneShow(ViewID,true);
			// ������ʾ�û��ǳ�
			this->setPlayerZoneNickName(ViewID,pPlayer->szNickname);
			// ������ʾ�û�ͷ��
			this->setPlayerZoneFaceLogo(ViewID,pPlayer->lSysLogoID);
			// ������ʾ�û�����
			this->setPlayerZoneChip(ViewID,pPlayer->lGoldLogin);
			// �����û���Ϣ��͸����(��׼���û���͸����δ׼���û���͸��)
			this->setPlayerZoneOpacity(ViewID,pPlayer->bRaiseHand?255:128);
			// �ƶ�����
			this->showCardSuit(ViewID,false);
		}
	}
	SIXLog("+++++++++++++++++++++++++++++");

	//// ��ʾ׼����ʾ
	//this->showSprReady();
	// ��ʾ׼����ť
	this->showBtnReady();
	//// ����ʱ
	//unsigned long long time = SIX_PlayerMgr::GetInstance()->getLastRecvSitDownTime();
	//unsigned long long now = SIX_Utility::GetInstance()->GetTickCount();
	//int diff = 20-(int)((now-time)/1000);
	//SIXLog("time[%lld].now[%lld].diff[%d]",time,now,diff);
	//if (diff>0)
	//	this->showCountDown(true,diff);
	this->showCountDown(true,SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_READY"));
}

void SIX_SceneGame::onExitTransitionDidStart()
{
	CCLayerColor::onExitTransitionDidStart();
}

void SIX_SceneGame::onExit()
{
	SIX_ClientRoom::GetInstance()->leave_seat();
	SIX_ClientRoom::GetInstance()->Disconnect();
	// �������û���Ϣ
	SIX_PlayerMgr::GetInstance()->clearPlayers();
	// ����SIX_PlayerMgr
	SIX_PlayerMgr::GetInstance()->Destory();
	// ����SIX_CardPlay
	SIX_CardPlay::GetInstance()->Destory();
	//CC_SAFE_RELEASE(pCountDown);
	CC_SAFE_RELEASE(m_pTipsPopWnd);
	CC_SAFE_RELEASE(m_pTipsShowCard);
	CC_SAFE_DELETE(pCountDownBatchNode);
	CC_SAFE_RELEASE(pWndPlayerInfo);
#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(0);
#endif
	CCLayerColor::onExit();
}

void SIX_SceneGame::onCloseExit()
{
	CCLayerColor::onCloseExit();
}

bool SIX_SceneGame::OnExitBtn()
{
	if (!SIX_Utility::GetInstance()->IsSceneRunning(pSceneGame,"SIX_SceneGame"))
		return true;
	if (pSceneGame->showAllowChangeToHallTips())
		return false;
	return true;
}

void SIX_SceneGame::OnNotifyCloseWndClicked(CCObject *pObj)
{
	SIXLog("��������ʧ�ܣ�");
}

void SIX_SceneGame::OnShowInformation(CMD_ChatContent *pChat)
{
	if (0==pBackground)
		return;
	CCSprite * pShowChat = dynamic_cast<CCSprite *>(pBackground->getChildByTag(BTN_SHOW_CHAT));
	if (0==pShowChat)
		return;

	CCLabelTTF * pShowContent = dynamic_cast<CCLabelTTF *>(pShowChat->getChildByTag(BTN_SHOW_CHAT*10+1));
	if (pShowContent)
	{
		pShowChat->setVisible(true);
		CCString *pStr = CCString::createWithFormat("%s��%s", pChat->szSpeakNickName, pChat->szCentent);
		pShowContent->setString(SIX_Utility::GetInstance()->G2U(pStr->getCString()).c_str());

		CCDelayTime *pDelay = CCDelayTime::create(3.0f);
		CCCallFunc * pCall = CCCallFunc::create(this, callfunc_selector(SIX_SceneGame::checkHaveMsgNoShowFunc));
		CCFiniteTimeAction *pSequence = CCSequence::create(pDelay, pCall, NULL);
		pShowChat->runAction(pSequence);
	}
}

void SIX_SceneGame::setVisibleByBtnMask(bool bVisible)
{
	if (!pBackground)
		return;
	//CCNode *pBtn = pBackground->getChildByTag(BTN_MENU_CLOSE);
	//if (pBtn)
	//{
	//	CCNode *pMask = dynamic_cast<CCNode*>(pBtn->getChildByTag(BTN_MENU_CLOSE*10));
	//	if (pMask)
	//		pMask->setVisible(bVisible);
	//}
	//pBtn = pBackground->getChildByTag(BTN_MENU_RETURN);
	//if (pBtn)
	//{
	//	CCNode *pMask = dynamic_cast<CCNode*>(pBtn->getChildByTag(BTN_MENU_RETURN*10));
	//	if (pMask)
	//		pMask->setVisible(bVisible);
	//}
	//pBtn = pBackground->getChildByTag(BTN_MENU_CHANGETABLE);
	//if (pBtn)
	//{
	//	CCNode *pMask = dynamic_cast<CCNode*>(pBtn->getChildByTag(BTN_MENU_CHANGETABLE*10));
	//	if (pMask)
	//		pMask->setVisible(bVisible);
	//}
}

void SIX_SceneGame::setVisibleByCardType(bool bVisible/*=true*/)
{
	if (!pBackground)
		return;

	CCNode * pBtn = pBackground->getChildByTag(BTN_CARDTYPE_BT);
	if ( !pBtn )
		return;
	CCSprite *pCardTypeExplanation = dynamic_cast<CCSprite*>(pBtn->getChildByTag(BTN_CARDTYPE_BT*10));
	if ( !pCardTypeExplanation )
		return;

	if (0.000001>=m_ptCartTypeExplanation.x && 0.000001>=m_ptCartTypeExplanation.y)
		m_ptCartTypeExplanation.setPoint(pCardTypeExplanation->getPositionX(), pCardTypeExplanation->getPositionY());

	pCardTypeExplanation->setVisible(bVisible);
	//if (bVisible)
	//{
	//	pCardTypeExplanation->setPositionX(-pCardTypeExplanation->getContentSize().width);
	//	pCardTypeExplanation->setVisible(bVisible);

	//	CCMoveTo *pMoveTo = CCMoveTo::create(0.5f, CCPoint(m_ptCartTypeExplanation.x, m_ptCartTypeExplanation.y));
	//	CCEaseIn *pEaseIn = CCEaseIn::create(pMoveTo, 0.2f);
	//	pCardTypeExplanation->runAction(pEaseIn);
	//	CCFadeIn *pFadeIn = CCFadeIn::create(0.5f);
	//	pCardTypeExplanation->runAction(pFadeIn);
	//}
	//else
	//{
	//	CCMoveTo *pMoveTo = CCMoveTo::create(0.5f, CCPoint(-pCardTypeExplanation->getContentSize().width, m_ptCartTypeExplanation.y));
	//	CCEaseOut *pEaseOut = CCEaseOut::create(pMoveTo, 0.2f);
	//	CCHide *pHide = CCHide::create();
	//	CCFiniteTimeAction *pFiniteTimeAction = CCSequence::create(pEaseOut, pHide, NULL);
	//	pCardTypeExplanation->runAction(pFiniteTimeAction);
	//	CCFadeOut *pFadeOut = CCFadeOut::create(0.5f);
	//	pCardTypeExplanation->runAction(pFadeOut);
	//}
}

void SIX_SceneGame::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	// ��ť��Ч
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(100,false);

	SIXLog("doEvents.event[%d].tag[%d]",event,tag);

	switch (event)
	{
		// ��ť���²���ק������������
	case CCControlEventTouchDragExit:
		{
			if (BTN_CARDTYPE_BT == tag)
			{
				setVisibleByCardType(false);
				break;
			}
			else
			{
				// ����������ť����
				setVisibleByBtnMask(false);
			}
			break;
		}
		// ��ť����δ����
	case CCControlEventTouchDown:
		{
			switch (tag)
			{
			//case BTN_MENU_CLOSE:
			//case BTN_MENU_RETURN:
			//case BTN_MENU_CHANGETABLE:
			//	{
			//		// ����������ť����
			//		setVisibleByBtnMask(false);

			//		// ��ʾ����ť����
			//		CCNode *pMask = dynamic_cast<CCNode*>(pControl->getChildByTag(tag*10));
			//		if (pMask)
			//			pMask->setVisible(true);
			//		break;
			//	}
			case BTN_CARDTYPE_BT:
				{
					setVisibleByCardType(true);
					break;
				}
			}
			break;
		}
		// ��ť���µ���
	case CCControlEventTouchUpInside:
		{
			// anybtn test SceneGame
			//SIX_Proxy::GetInstance()->SetChangeScene(true);

			switch (tag)
			{
				// �˵�
			case BTN_MENU:
				{
					this->showAllowChangeToHallTips();
					//pControl->setVisible(false);
					//if (pBackground)
					//{
					//	CCNode *pBtn = pBackground->getChildByTag(BTN_MENU_CLOSE);
					//	if (pBtn)
					//	{
					//		pBtn->setVisible(true);
					//		SIX_Utility::GetInstance()->setVisibleAllChildren(pBtn,true);
					//	}
					//	pBtn = pBackground->getChildByTag(BTN_MENU_RETURN);
					//	if (pBtn)
					//	{
					//		pBtn->setVisible(true);
					//		SIX_Utility::GetInstance()->setVisibleAllChildren(pBtn,true);
					//	}
					//	pBtn = pBackground->getChildByTag(BTN_MENU_CHANGETABLE);
					//	if (pBtn)
					//	{
					//		pBtn->setVisible(true);
					//		SIX_Utility::GetInstance()->setVisibleAllChildren(pBtn,true);
					//	}
					//}
					//setVisibleByBtnMask(false);
					break;
				}
			//	// �رղ˵�
			//case BTN_MENU_CLOSE:
			//	// ��һ��
			//case BTN_MENU_CHANGETABLE:
			//	// ���ش���
			//case BTN_MENU_RETURN:
			//	{
			//		pControl->setVisible(false);
			//		if (pBackground)
			//		{
			//			CCNode *pBtn = pBackground->getChildByTag(BTN_MENU);
			//			if (pBtn)
			//			{
			//				pBtn->setVisible(true);
			//				SIX_Utility::GetInstance()->setVisibleAllChildren(pBtn,true);
			//			}
			//			pBtn = pBackground->getChildByTag(BTN_MENU_CLOSE);
			//			if (pBtn)
			//			{
			//				pBtn->setVisible(false);
			//				SIX_Utility::GetInstance()->setVisibleAllChildren(pBtn,false);
			//			}
			//			pBtn = pBackground->getChildByTag(BTN_MENU_RETURN);
			//			if (pBtn)
			//			{
			//				pBtn->setVisible(false);
			//				SIX_Utility::GetInstance()->setVisibleAllChildren(pBtn,false);
			//			}
			//			pBtn = pBackground->getChildByTag(BTN_MENU_CHANGETABLE);
			//			if (pBtn)
			//			{
			//				pBtn->setVisible(false);
			//				SIX_Utility::GetInstance()->setVisibleAllChildren(pBtn,false);
			//			}
			//		}
			//		setVisibleByBtnMask(false);

			//		switch (tag)
			//		{
			//			// ���ش���
			//		case BTN_MENU_RETURN:
			//			{
			//				this->showAllowChangeToHallTips();
			//				break;						
			//			}
			//		}

			//		//// ��һ������
			//		//if (tag==BTN_MENU_CHANGETABLE)
			//		//{
			//		//	SIX_CardPlay *pCardPlay = SIX_CardPlay::GetInstance();
			//		//	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(pCardPlay->Get(5));
			//		//	if (pPlayerZone && pPlayerZone->wCardSuit)
			//		//	{
			//		//		pPlayerZone->wCardSuit->setCardPopAll(!pPlayerZone->wCardSuit->getCardPopAll());
			//		//	}
			//		//}
			//		break;
			//	}
				// ������ͷ��
			case BTN_PLAYER1_LOGO:
			case BTN_PLAYER2_LOGO:
			case BTN_PLAYER3_LOGO:
			case BTN_PLAYER4_LOGO:
			case BTN_PLAYER5_LOGO:
			case BTN_PLAYER6_LOGO:
				{
					if (!pWndPlayerInfo)
					{
						pWndPlayerInfo = SIX_PopWndPlayerInfo::Create(0.0,0.0,ccc4(0,0,0,0),365,180,false);
						pWndPlayerInfo->InitMask(ccc4(0,0,0,128));
						pWndPlayerInfo->backgroundWithFile("game_bg_userinfo.png");
						// ��ֹ��ק
						pWndPlayerInfo->setAllowDragged(false);
					}
					pWndPlayerInfo->Show();
					// �����û���ͼID
					pWndPlayerInfo->setPlayerViewId(tag/100-1);
					break;
				}
				// ׼����ť
			case BTN_READY:
				{
					//// �ָ�������Ϣ����͸����
					//setPlayerZoneOpacity(4,255);

					// ����UI���ų��û���Ϣ����
					this->resetUI(false,false);

					//����
					SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_RAISE_HAND);

					break;
				}
				// ����ׯ
			case BTN_RUB_CANCEL:
				// ��ׯ
			case BTN_RUB_SUBMIT:
				{
					bool bCall=(tag==BTN_RUB_SUBMIT?true:false);
					Req_UserCallBanker req;
					req.llUserID=SIX_PlayerMgr::GetInstance()->getMyUserIdx();
					req.iSeatNo=SIX_PlayerMgr::GetInstance()->getMySeatIdx();
					req.bCall=bCall;
					SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN,REQ_USER_CALL_BANKER,(BYTE*)(&req), sizeof(req));

					//this->showCountDown(false);
					// ������ׯ��ť
					this->showBtnRubBanker(false);

					break;
				}
				// ��ע1
			case BTN_CHIPIN1:
				// ��ע2
			case BTN_CHIPIN2:
				// ��ע3
			case BTN_CHIPIN3:
				{
					Req_UserChipin req;
					req.llUserID=SIX_PlayerMgr::GetInstance()->getMyUserIdx();
					req.iSeatNo=SIX_PlayerMgr::GetInstance()->getMySeatIdx();
					req.lScore=(tag==BTN_CHIPIN2?SIX_PlayerMgr::GetInstance()->m_C2:(tag==BTN_CHIPIN3?SIX_PlayerMgr::GetInstance()->m_C3:SIX_PlayerMgr::GetInstance()->m_C1));
					SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN,REQ_USER_CHIPIN,(BYTE*)(&req), sizeof(req));

					//this->showCountDown(false);
					// ������ע��ť
					this->showBtnChipin(false);
					break;
				}
			case BTN_KILL_1:
				{
					Req_UserKill req;
					req.llUserID=SIX_PlayerMgr::GetInstance()->getMyUserIdx();
					req.iSeatNo=SIX_PlayerMgr::GetInstance()->getMySeatIdx();
					req.KillMode=1;
					SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN,REQ_USER_KILL,(BYTE*)(&req), sizeof(req));

					// ����ɢ��ɱ����С��ť
					this->showBtnKill(false);

					break;
				}
			case BTN_CARDTYPE_BT: // ���ʹ���
				{
					setVisibleByCardType(false);
					break;
				}
			case BTN_CHAT_BT: // ���촰��
				{
					m_pWndMsg->Show();
					break;
				}
			}

			//// test for progress turn circle effect
			//// Cool.Cat
			//if (!pCountDown)
			//{
			//	CCSprite* progressSprite = CCSprite::create("overlay.png");
			//	pCountDown = CCProgressTimer::create(progressSprite);
			//	pCountDown->ignoreAnchorPointForPosition(true);
			//	pCountDown->setType(kCCProgressTimerTypeRadial);
			//	addChild(pCountDown, 100);
			//}

			//if (pCountDown)
			//{
			//	pCountDown->stopAllActions();
			//	pCountDown->setPercentage(0.0f);

			//	CCPoint ptRoot = CCPoint(0.0f,0.0f);
			//	if (pControl->getParent())
			//		ptRoot = pControl->getParent()->getPosition();
			//	CCPoint pt = pControl->getPosition();
			//	pt.x += ptRoot.x;
			//	pt.y += ptRoot.y;
			//	pCountDown->setPosition(pt);

			//	pCountDown->setVisible(true);

			//	CCActionInterval* action_progress_to = CCProgressTo::create(5.0f,100);
			//	CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(SIX_SceneGame::ProgressDown));
			//	pCountDown->runAction(CCSequence::create(action_progress_to,action_callback,0));
			//}
			break;
		}
	}
}

bool SIX_SceneGame::showAllowChangeToHallTips()
{
	bool bAllowChangeToHall = SIX_PlayerMgr::GetInstance()->getAllowChangeToHall();
	if (!bAllowChangeToHall)
	{
		// ������ʾ����Ϸ������ſ��Է��ش�������
		// Cool.Cat
		if (!m_pTipsPopWnd)
		{
			m_pTipsPopWnd = SIX_TipsPopWnd::Create(0.0,0.0,ccc4(0,0,0,0),721.0,77.0);
			if (!m_pTipsPopWnd)
				return false;
			m_pTipsPopWnd->InitMask(ccc4(0,0,0,0));
			m_pTipsPopWnd->backgroundWithFile("tips_bg.png");
			m_pTipsPopWnd->setShowType(MOVABLE_TOP);
			m_pTipsPopWnd->setHideType(MOVABLE_NONE);
			m_pTipsPopWnd->setShakeOffset(0.0f);
			m_pTipsPopWnd->setSeqExec(true);
			m_pTipsPopWnd->setAllowDragged(false);
			m_pTipsPopWnd->setTips(/*��Ϸ������ſ��Է��ش�����*/XorStr<0x3D,27,0xB0B674F9>("\xEE\xF0\xF0\xF7\xFC\xA3\x89\xBC\xFF\xB5\xF5\x8D\xF6\x83\x99\x98\xFA\xFB\xF4\x88\xE5\xA1\x9F\xA8\xF6\xF7"+0xB0B674F9).s,"΢���ź�",22);
		}
		if (m_pTipsPopWnd->getActDone())
			m_pTipsPopWnd->Show();
		return true;
	}
	SIX_Proxy::GetInstance()->SetChangeScene(true);
	return false;
}

void SIX_SceneGame::ProgressDown(CCNode *pNode)
{
	if (!pCountDown)
		return;
	pCountDown->setVisible(false);
}

bool SIX_SceneGame::IsMySelf(unsigned int idx)
{
	return (idx==3);
}

void SIX_SceneGame::checkHaveMsgNoShowFunc()
{
	if (0==m_pWndMsg)
		return;

	if ( !m_pWndMsg->getNextMsg() )
	{
		if (0==pBackground)
			return;
		CCSprite * pShowChat = dynamic_cast<CCSprite *>(pBackground->getChildByTag(BTN_SHOW_CHAT));
		if (0==pShowChat)
			return;
		pShowChat->setVisible(false);
	}
}

void SIX_SceneGame::update(float dt)
{
	if (SIX_Proxy::GetInstance()->IsChangeScene())
	{
		SIX_Proxy::GetInstance()->SetChangeScene(false);

		if (!pSceneHall)
		{
			pSceneHall = SIX_SceneHall::scene();
			if (!pSceneHall)
			{
				//CCMessageBox("��������ʧ�ܣ�",0);
				return;
			}
		}
		LAST_SCENE_IDX = SCENE_IDX_GAME;
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2f,pSceneHall->GetScene(),ccc3(255, 255, 255)));
	}
}

// ����UI�����ƶѵ�SIX_CardPlay
int SIX_SceneGame::ParseAndBindUIToCardPlay()
{
	if (!pBackground)
		return -1;

	pNodeTable = dynamic_cast<CCSprite*>(pBackground->getChildByTag(SPRITE_TABLE));
	if (!pNodeTable)
		return -2;

	SIX_CardPlay *pCardPlay = SIX_CardPlay::GetInstance();

	// ��������ƶ��游�ڵ�
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		PLAYER_ZONE_INFO *pPlayerZone = new PLAYER_ZONE_INFO();
		pPlayerZone->wRoot = (CCNode*)(pNodeTable->getChildByTag((i+1)*100));
		if (!pPlayerZone->wRoot)
		{
			CC_SAFE_DELETE(pPlayerZone);
			continue;
		}

		// ��Ҹ�����Ϣ��
		pPlayerZone->wPlayerInfo = dynamic_cast<CCControlButton*>(pPlayerZone->wRoot->getChildByTag((i+1)*100));
		if (pPlayerZone->wPlayerInfo)
		{
			// �ǳ�
			pPlayerZone->wNickName = dynamic_cast<CCLabelTTF*>(pPlayerZone->wPlayerInfo->getChildByTag(1));
			// ͷ��
			pPlayerZone->wFaceLogo = dynamic_cast<CCSprite*>(pPlayerZone->wPlayerInfo->getChildByTag(2));
			// ���
			pPlayerZone->wMoney = dynamic_cast<CCLabelTTF*>(pPlayerZone->wPlayerInfo->getChildByTag(3));
			// ׯ��
			pPlayerZone->wBanker = dynamic_cast<CCSprite*>(pPlayerZone->wPlayerInfo->getChildByTag(4));
		}
		// ����
		CCNode *pNode = pPlayerZone->wRoot->getChildByTag(2);
		if (pNode)
		{
			// �ƶ�
			pPlayerZone->wCardSuit = dynamic_cast<SIX_CardSuit*>(pNode->getChildByTag(1));
			if (pPlayerZone->wCardSuit)
			{
				// ��1
				pPlayerZone->wCardItem1 = dynamic_cast<SIX_CardItem*>(pPlayerZone->wCardSuit->getChildByTag(1));
				// ��2
				pPlayerZone->wCardItem2 = dynamic_cast<SIX_CardItem*>(pPlayerZone->wCardSuit->getChildByTag(2));
				// ��3
				pPlayerZone->wCardItem3 = dynamic_cast<SIX_CardItem*>(pPlayerZone->wCardSuit->getChildByTag(3));
			}
			// ͳ�����
			pPlayerZone->wStatsPanel = dynamic_cast<CCNode*>(pNode->getChildByTag(2));
			if (pPlayerZone->wStatsPanel)
			{
				// �Ƶ�
				pPlayerZone->wStatsPoint = dynamic_cast<CCSprite*>(pPlayerZone->wStatsPanel->getChildByTag(1));
				pPlayerZone->wStatsDot = dynamic_cast<CCSprite*>(pPlayerZone->wStatsPanel->getChildByTag(2));
				// ����
				pPlayerZone->wStats3Gong = dynamic_cast<CCSprite*>(pPlayerZone->wStatsPanel->getChildByTag(3));
				// ը��
				pPlayerZone->wStatsBomb = dynamic_cast<CCSprite*>(pPlayerZone->wStatsPanel->getChildByTag(4));
			}
		}
		// ������
		pPlayerZone->wChipPanel = dynamic_cast<CCSprite*>(pPlayerZone->wRoot->getChildByTag(3));
		if (pPlayerZone->wChipPanel)
		{
			// ����
			pPlayerZone->wChipSprite = dynamic_cast<CCSprite*>(pPlayerZone->wChipPanel->getChildByTag(1));
			// ����
			pPlayerZone->wChipPoint = dynamic_cast<CCLabelTTF*>(pPlayerZone->wChipPanel->getChildByTag(2));
		}

		// save it~
		pCardPlay->Push(pPlayerZone);
	}

	return 0;
}

// ��ʾϴ����
void SIX_SceneGame::showNodeShuffle(bool bShow)
{
	if (!pBackground)
		return;

	if (!pNodeTable)
		return;

	if (!pNodeShuffle)
	{
		pNodeShuffle = pNodeTable->getChildByTag(NODE_SHUFFLE);
		if (!pNodeShuffle)
			return;
	}

	pNodeShuffle->setVisible(bShow);
}

// ��ʾ������
void SIX_SceneGame::showNodeDice(bool bShow)
{
	if (!pBackground)
		return;

	if (!pNodeTable)
		return;

	if (!pNodeDice)
	{
		pNodeDice = pNodeTable->getChildByTag(NODE_DICE);
		if (!pNodeDice)
			return;
	}

	pNodeDice->setVisible(bShow);
}

//// ��ʾ׼����ʾ
//void SIX_SceneGame::showSprReady(bool bShow)
//{
//	if (!pBackground)
//		return;
//
//	if (!pNodeTable)
//		return;
//
//	if (!pSpriteReady)
//	{
//		pSpriteReady = dynamic_cast<CCScale9Sprite*>(pNodeTable->getChildByTag(SPRITE_READY));
//		if (!pSpriteReady)
//			return;
//	}
//
//	pSpriteReady->setVisible(bShow);
//}

// ��ʾ׼����ť
void SIX_SceneGame::showBtnReady(bool bShow)
{
	if (!pBackground)
		return;

	if (!pBtnReady)
	{
		pBtnReady = dynamic_cast<CCControlButton*>(pBackground->getChildByTag(BTN_READY));
		if (!pBtnReady)
			return;
	}

	pBtnReady->setVisible(bShow);
}

// ��ʾ��ׯ��ť
void SIX_SceneGame::showBtnRubBanker(bool bShow)
{
	if (!pBackground)
		return;

	if (!pBtnRubCancel)
		pBtnRubCancel = dynamic_cast<CCControlButton*>(pBackground->getChildByTag(BTN_RUB_CANCEL));
	if (pBtnRubCancel)
		pBtnRubCancel->setVisible(bShow);

	if (!pBtnRubSubmit)
		pBtnRubSubmit = dynamic_cast<CCControlButton*>(pBackground->getChildByTag(BTN_RUB_SUBMIT));
	if (pBtnRubSubmit)
		pBtnRubSubmit->setVisible(bShow);
}

// ��ʾ��ע��ʾ
void SIX_SceneGame::showSprChip(bool bShow)
{
	if (!pBackground)
		return;

	if (!pNodeTable)
		return;

	if (!pSpriteChip)
	{
		pSpriteChip = dynamic_cast<CCScale9Sprite*>(pNodeTable->getChildByTag(SPRITE_CHIP));
		if (!pSpriteChip)
			return;
	}

	pSpriteChip->setVisible(bShow);
}

// ��ʾ��ע��ť
void SIX_SceneGame::showBtnChipin(bool bShow)
{
	if (!pBackground)
		return;

	if (!pBtnChipin1)
		pBtnChipin1 = dynamic_cast<CCControlButton*>(pBackground->getChildByTag(BTN_CHIPIN1));
	if (pBtnChipin1)
		pBtnChipin1->setVisible(bShow);

	if (!pBtnChipin2)
		pBtnChipin2 = dynamic_cast<CCControlButton*>(pBackground->getChildByTag(BTN_CHIPIN2));
	if (pBtnChipin2)
		pBtnChipin2->setVisible(bShow);

	if (!pBtnChipin3)
		pBtnChipin3 = dynamic_cast<CCControlButton*>(pBackground->getChildByTag(BTN_CHIPIN3));
	if (pBtnChipin3)
		pBtnChipin3->setVisible(bShow);
}

// ��ʾɢ��ɱ����С��ť
void SIX_SceneGame::showBtnKill(bool bShow)
{
	if (!pBackground)
		return;

	if (!pBtnKill)
		pBtnKill = dynamic_cast<CCControlButton*>(pBackground->getChildByTag(BTN_KILL_1));
	if (pBtnKill)
		pBtnKill->setVisible(bShow);
}

// ������ע��ť������ע��������
void SIX_SceneGame::SetBtnChipPoint(TChip chip1point,TChip chip2point,TChip chip3point)
{
	CCScale9Sprite *pNorSprite = 0;
	CCScale9Sprite *pSelSprite = 0;

	SIX_PlayerMgr::GetInstance()->m_C1=chip1point;
	SIX_PlayerMgr::GetInstance()->m_C2=chip2point;
	SIX_PlayerMgr::GetInstance()->m_C3=chip3point;

	if (pBtnChipin1)
	{
		CCLabelTTF *pTitle = dynamic_cast<CCLabelTTF*>(pBtnChipin1->getTitleLabel());
		if (pTitle)
		{
			pTitle->setString(CCString::createWithFormat("%lld",chip1point)->getCString());
			pTitle->setFontName("΢���ź�");
			pTitle->setFontSize(30);
			pTitle->setColor(ccc3(0,0,0));
			pTitle->setDimensions(CCSize(pBtnChipin1->getPreferredSize().width,pBtnChipin1->getPreferredSize().height));
			pTitle->setHorizontalAlignment(kCCTextAlignmentCenter);
			pTitle->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
			SIX_Utility::GetInstance()->FixedTexParameters(pTitle->getTexture(),true);
		}

		pBtnChipin1->setTitleColorForState(ccc3(0,0,0),CCControlStateNormal);
		pBtnChipin1->setTitleForState(CCString::createWithFormat("%lld",chip1point),CCControlStateNormal);
		pBtnChipin1->setTitleColorForState(ccc3(0,0,0),CCControlStateHighlighted);
		pBtnChipin1->setTitleForState(CCString::createWithFormat("%lld",chip1point),CCControlStateHighlighted);

		pBtnChipin1->setVisible(true);
	}

	if (pBtnChipin2)
	{
		CCLabelTTF *pTitle = dynamic_cast<CCLabelTTF*>(pBtnChipin2->getTitleLabel());
		if (pTitle)
		{
			pTitle->setString(CCString::createWithFormat("%lld",chip2point)->getCString());
			pTitle->setFontName("΢���ź�");
			pTitle->setFontSize(30);
			pTitle->setColor(ccc3(0,0,0));
			pTitle->setDimensions(CCSize(pBtnChipin2->getPreferredSize().width,pBtnChipin2->getPreferredSize().height));
			pTitle->setHorizontalAlignment(kCCTextAlignmentCenter);
			pTitle->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
			SIX_Utility::GetInstance()->FixedTexParameters(pTitle->getTexture(),true);
		}

		pBtnChipin2->setTitleColorForState(ccc3(0,0,0),CCControlStateNormal);
		pBtnChipin2->setTitleForState(CCString::createWithFormat("%lld",chip2point),CCControlStateNormal);
		pBtnChipin2->setTitleColorForState(ccc3(0,0,0),CCControlStateHighlighted);
		pBtnChipin2->setTitleForState(CCString::createWithFormat("%lld",chip2point),CCControlStateHighlighted);

		pBtnChipin2->setVisible(true);
	}

	if (pBtnChipin3)
	{
		CCLabelTTF *pTitle = dynamic_cast<CCLabelTTF*>(pBtnChipin3->getTitleLabel());
		if (pTitle)
		{
			pTitle->setString(CCString::createWithFormat("%lld",chip3point)->getCString());
			pTitle->setFontName("΢���ź�");
			pTitle->setFontSize(30);
			pTitle->setColor(ccc3(0,0,0));
			pTitle->setDimensions(CCSize(pBtnChipin3->getPreferredSize().width,pBtnChipin3->getPreferredSize().height));
			pTitle->setHorizontalAlignment(kCCTextAlignmentCenter);
			pTitle->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
			SIX_Utility::GetInstance()->FixedTexParameters(pTitle->getTexture(),true);
		}

		pBtnChipin3->setTitleColorForState(ccc3(0,0,0),CCControlStateNormal);
		pBtnChipin3->setTitleForState(CCString::createWithFormat("%lld",chip3point),CCControlStateNormal);
		pBtnChipin3->setTitleColorForState(ccc3(0,0,0),CCControlStateHighlighted);
		pBtnChipin3->setTitleForState(CCString::createWithFormat("%lld",chip3point),CCControlStateHighlighted);

		pBtnChipin3->setVisible(true);
	}
}

// ��ʾ��ׯ��ʾ
void SIX_SceneGame::showTipRubBanker(unsigned int playerIdx,bool isRub,bool isVisible)
{
	PLAYER_ZONE_INFO *pPlayerZone = this->getPlayerZone(playerIdx);
	if (!pPlayerZone)
		return;

	pPlayerZone->wNickName->removeAllChildrenWithCleanup(true);
	if (isVisible)
	{
		CCSprite *pRubTip = 0;
		if (isRub)
			pRubTip = CCSprite::create("game_tip_rub.png");
		else
			pRubTip = CCSprite::create("game_tip_norub.png");
		pRubTip->ignoreAnchorPointForPosition(true);
		pRubTip->setPosition(ccp(-5,-2));
		pPlayerZone->wNickName->addChild(pRubTip);
	}
}

// ��ʾʤ����ʾ
void SIX_SceneGame::showTipStats(unsigned int playerIdx,unsigned int point,bool isWin,bool bPointShow,bool b3GongShow,bool bBombShow)
{
	PLAYER_ZONE_INFO *pPlayerZone = this->getPlayerZone(playerIdx);
	if (!pPlayerZone)
		return;

	if (!bPointShow && !b3GongShow && !bBombShow)
	{
		pPlayerZone->wNickName->removeAllChildrenWithCleanup(true);
		return;
	}

	// ����
	CCSprite *pStatsTip = 0;
	if (isWin)
		pStatsTip = CCSprite::create("game_stats_win.png");
	else
		pStatsTip = CCSprite::create("game_stats_lose.png");
	pStatsTip->ignoreAnchorPointForPosition(true);
	pStatsTip->setPosition(ccp(-5,-2));
	pPlayerZone->wNickName->addChild(pStatsTip);

	// ͳ������
}

// ��ʾ/��������
void SIX_SceneGame::SetCardFrontShow(unsigned int playerIdx,unsigned int cardIdx,bool bShow)
{
	SIX_CardPlay *pCardPlay = SIX_CardPlay::GetInstance();
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(pCardPlay->Get(playerIdx));
	if (!pPlayerZone)
		return;

	switch (cardIdx)
	{
	case 0:
		{
			pPlayerZone->wCardItem1->setCardFrontShow(bShow);
			break;
		}
	case 1:
		{
			pPlayerZone->wCardItem2->setCardFrontShow(bShow);
			break;
		}
	case 2:
		{
			pPlayerZone->wCardItem3->setCardFrontShow(bShow);
			break;
		}
	}
}

void SIX_SceneGame::OnDiceSpinDone(CCNode *pNode)
{
	if (!pNode)
		return;

	CCSprite *pDice = dynamic_cast<CCSprite*>(pNode);
	if (!pDice)
		return;

	// Я������
	long long *pData = (long long*)(pNode->getUserData());
	// ����֡
	CCSpriteFrame *pDiceIdleFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("dice_%d.png",pNode->getTag())->getCString());
	if (!pDiceIdleFrame)
	{
		CC_SAFE_DELETE(pData);
		return;
	}

	// ���ӵ���
	pDice->setDisplayFrame(pDiceIdleFrame);
	// ���ýǶ�
	pDice->setRotation(0.0f);
	pDice->stopAllActions();

	// ��ʾׯ�ұ�־
	if (!pData)
		return;

	SIX_SceneGame *pThis = (SIX_SceneGame*)((int)pData[0]);
	if (!pThis)
	{
		CC_SAFE_DELETE(pData);
		return;
	}

	// ׯ�ұ�־�ع鵽ׯ������
	pThis->MoveBankerFlagToBankerArea(pData[2],pData[3],pData[4]);
	CC_SAFE_DELETE(pData);
}

// ��ע�ص�
void SIX_SceneGame::OnShowCanChipDone(CCNode *pNode,void *pData)
{
	TChip *pChipData = (TChip*)pData;

	// ����������
	this->showNodeDice(false);

	// �м���ʾ��ע��ť������Ӧ������
	if (SIX_PlayerMgr::GetInstance()->m_wBankerChairID!=SIX_PlayerMgr::GetInstance()->getMySeatIdx())
	{
		this->showCountDown(true,SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_CHIPIN_FIRST"));
		this->showBtnChipin(true);
		this->SetBtnChipPoint(pChipData[0],pChipData[1],pChipData[2]);
	}
	else
	{
		// �ȴ��м���ע
		this->showSprChip(true);
		//ɢ��ׯ����ʾɱ����С��ť
		if(SIX_PlayerMgr::GetInstance()->IsSanXianIdentity())
		{
			showBtnKill(true);
		}
	}
	CC_SAFE_DELETE(pChipData);
}

void SIX_SceneGame::OnDiceDropDone(CCNode *pNode)
{
	if (!pNode)
		return;

	// ���ɲ��ظ���������ӵ�������
	int pointArr[6];
	memset(&pointArr,0,sizeof(pointArr));
	int count = 0;
	while (count<6)
	{
		int point = SIX_Utility::GetInstance()->RNDNUM(1,6);
		bool gotch = true;
		for (int i=0;i<6;i++)
		{
			if (point==pointArr[i])
			{
				gotch = false;
				break;
			}
		}
		if (gotch)
		{
			pointArr[count] = point;
			count++;
		}
	}
	CCArray *pArraySpin = CCArray::create();
	for (int j=0;j<6;j++)
	{
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("dice_%d.png",pointArr[j])->getCString());
		if (pFrame)
			pArraySpin->addObject(pFrame);
		//SIXLog("pFrame[%d]=%s",j,CCString::createWithFormat("dice_%d.png",pointArr[j])->getCString());
	}

	if (!pArraySpin->count())
	{
		long long *pData = (long long*)(pNode->getUserData());
		CC_SAFE_DELETE(pData);
		return;
	}

	//// λ�ƣ��������һ�����������п��ܻ��ص�
	//float rndOffset[2] = {0.0f,0.0f};
	//rndOffset[1] = SIX_Utility::GetInstance()->RNDNUM(0,size.height);
	//// ��
	//if (i%2)
	//	rndOffset[0] = SIX_Utility::GetInstance()->RNDNUM(0,size.width/2-pDice->getContentSize().width/2);
	//// ��
	//else
	//	rndOffset[0] = SIX_Utility::GetInstance()->RNDNUM(size.width/2+pDice->getContentSize().width/2,size.width);
	////SIXLog("rndOffset[%d] = [%.2f/%.2f]",i,rndOffset[0],rndOffset[1]);

	// ��ת�ӳ�(0.05f��0.1f)
	//float rndDelay = float(SIX_Utility::GetInstance()->RNDNUM(50,100))/1000.0f;
	//CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pArraySpin,DELAY_DICE_FRAME);
	CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pArraySpin,SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_DICE_FRAME"));
	CCAnimate *pAnimate = CCAnimate::create(pAnimation);

	pNode->runAction(CCRepeatForever::create(pAnimate));

	CCArray *pArray = CCArray::create();
	//// λ��
	//CCMoveTo *pMove = CCMoveTo::create(0.5f,CCPoint(SIX_Utility::GetInstance()->RNDNUM(0,100),SIX_Utility::GetInstance()->RNDNUM(0,100)));
	//pArray->addObject(pMove);
	// ��ת
	//CCRotateTo *pRotate = CCRotateTo::create(DELAY_DICE_ANIMATION,0.0f);
	CCRotateTo *pRotate = CCRotateTo::create(SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_DICE_ANIMATION"),0.0f);
	pArray->addObject(pRotate);
	// �ص�
	pArray->addObject(CCCallFuncN::create(pNode,callfuncN_selector(SIX_SceneGame::OnDiceSpinDone)));
	CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
	pNode->runAction(pTimeAction);
}

// �������Ӷ���(����/��ת)
void SIX_SceneGame::showSingleDice(unsigned char point,CCPoint dropStart,CCPoint dropEnd,long long *pData,bool carryData)
{
	SIXLog("point[%d].dropStart[%.2f/%.2f].dropEnd[%.2f/%.2f].pThis[0x%08X/0x%08X].ViewID[%d].chip[%lld/%lld/%lld]",
		point,
		dropStart.x,
		dropStart.y,
		dropEnd.x,
		dropEnd.y,
		this,
		(int)pData[0],(TChairID)pData[1],pData[2],pData[3],pData[4]);
	if (!pNodeDice || point<=0 || point>6)
	{
		CC_SAFE_DELETE(pData);
		return;
	}

	CCSpriteBatchNode *pBatchNode = CCSpriteBatchNode::create(CCString::create("dice.png")->getCString());
	if (!pBatchNode)
	{
		CC_SAFE_DELETE(pData);
		return;
	}

	pNodeDice->addChild(pBatchNode);

	// ����֡
	CCSpriteFrame *pDiceDropFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("dice_%d.png",point)->getCString());
	if (!pDiceDropFrame)
	{
		CC_SAFE_DELETE(pData);
		return;
	}

	CCSprite *pDice = CCSprite::createWithSpriteFrame(pDiceDropFrame);
	if (!pDice)
	{
		CC_SAFE_DELETE(pData);
		return;
	}

	pDice->ignoreAnchorPointForPosition(false);
	pDice->setAnchorPoint(ccp(0.5,0.5));
	pDice->setPosition(dropStart);
	// ����
	pDice->setTag(point);
	if (carryData)
	{
		// Я��ׯ��/����ע��������
		pDice->setUserData((void*)pData);
	}
	pBatchNode->addChild(pDice);

	// ����
	//CCMoveTo *pMove = CCMoveTo::create(DELAY_DICE_FALLDOWN,dropEnd);
	CCMoveTo *pMove = CCMoveTo::create(SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_DICE_FALLDOWN"),dropEnd);
	CCArray *pArray = CCArray::create();
	pArray->addObject(pMove);
	// �ص�
	pArray->addObject(CCCallFuncN::create(pDice,callfuncN_selector(SIX_SceneGame::OnDiceDropDone)));
	CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
	pDice->runAction(pTimeAction);
}

// �ƶ�ׯ�����ӵ�ϴ����
void SIX_SceneGame::MoveBankerFlagToShuffleArea(TChairID wBankerID)
{
	int BankerViewID = SIX_PlayerMgr::getViewID(wBankerID,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
	PLAYER_ZONE_INFO *pPlayerZone = this->getPlayerZone(BankerViewID);
	if (!pPlayerZone)
		return;

	CCSize bankerSize = pPlayerZone->wBanker->getContentSize();
	CCPoint offsetStart = pPlayerZone->wBanker->getPosition();
	CCPoint offsetInfo = pPlayerZone->wPlayerInfo->getPosition();
	CCPoint offsetRoot = pPlayerZone->wRoot->getPosition();

	CCPoint offsetDice = this->pNodeDice->getPosition();
	CCSize diceSize = this->pNodeDice->getContentSize();

	// ����ƫ��
	CCPoint *pOffsetOgi = new CCPoint();
	pOffsetOgi->x = offsetDice.x + diceSize.width/2 - (offsetRoot.x + offsetInfo.x + offsetStart.x + bankerSize.width/2);
	pOffsetOgi->y = offsetDice.y + diceSize.height/2 - (offsetRoot.y + offsetInfo.y + offsetStart.y + bankerSize.height/2) + 50.0f;

	pPlayerZone->wBanker->setUserData((void*)pOffsetOgi);
	// �ƶ���������
	pPlayerZone->wBanker->setPosition(ccp(pOffsetOgi->x+pPlayerZone->wBanker->getPositionX(),pOffsetOgi->y+pPlayerZone->wBanker->getPositionY()));
	pPlayerZone->wBanker->setVisible(true);
}

// �ƶ�ׯ�����ӵ�ׯ������
void SIX_SceneGame::MoveBankerFlagToBankerArea(TChip c1,TChip c2,TChip c3)
{
	// �����ع鵽ׯ������
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		int ViewID = SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
		// �Ƴ���ׯ��ʾ
		this->showTipRubBanker(ViewID,false,false);
	}

	// ׯ�ұ�־��λ����
	int ViewID=SIX_PlayerMgr::getViewID(SIX_PlayerMgr::GetInstance()->m_wBankerChairID,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
	PLAYER_ZONE_INFO *pBankerZone = this->getPlayerZone(ViewID);
	if (pBankerZone)
	{
		CCPoint offsetEnd = CCPointZero;
		CCPoint *offsetData = (CCPoint*)pBankerZone->wBanker->getUserData();
		offsetEnd.x = -offsetData->x;
		offsetEnd.y = -offsetData->y;
		CC_SAFE_DELETE(offsetData);
		// λ��
		//CCMoveBy *pMove = CCMoveBy::create(DELAY_BANKER_FROM_DICE,offsetEnd);
		CCMoveBy *pMove = CCMoveBy::create(SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_BANKER_FROM_DICE"),offsetEnd);
		// �ص�
		TChip *chipData = new TChip[3];
		chipData[0] = c1;
		chipData[1] = c2;
		chipData[2] = c3;
		CCCallFunc* pCallback = CCCallFuncND::create(this,callfuncND_selector(SIX_SceneGame::OnShowCanChipDone),(void*)chipData);
		CCFiniteTimeAction *pAction = CCSequence::create(pMove,pCallback,0);
		pBankerZone->wBanker->runAction(pAction);
	}
}

// ��ʾ�����Ӷ���
void SIX_SceneGame::showAnimateThrowDice(unsigned int dice[],unsigned int count,long long *pData)
{
	SIXLog("pData[0x%08X/0x%08X].[%d].[%lld].[%lld].[%lld]",this,(int)pData[0],(TChairID)pData[1],pData[2],pData[3],pData[4]);

	// ������Ч
	// add by Ivan_han 20131101
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(700,false);

	showNodeDice(true);

	// ׯ�ұ�־���ƶ���������
	this->MoveBankerFlagToShuffleArea((int)pData[1]);

	pNodeDice->removeAllChildrenWithCleanup(true);

	CCSize size = pNodeDice->getContentSize();
	// ÿ��������Կ��
	float relaWidth = (float)(size.width/count);

	// ����+��ת����
	CCPoint dropStart = CCPointZero;
	CCPoint dropEnd = CCPointZero;
	for (unsigned int i=0;i<count;i++)
	{
		// �������ƫ��
		dropStart.x = (float)(relaWidth/2.0f + relaWidth*i);
		dropStart.y = size.height;
		// �����յ�ƫ��
		dropEnd.x = (float)(relaWidth/2.0f + relaWidth*i);
		dropEnd.y = size.height/2.0f;
		this->showSingleDice(dice[i],dropStart,dropEnd,pData,(i==count-1)?true:false);
	}
}

// ��ʾϴ�Ʒ��ƶ���
void SIX_SceneGame::showAnimateShuffleAndDealCard()
{
	// ����������
	showNodeDice(false);
	// ��ʾϴ����
	showNodeShuffle(true);
	// ������ע��ť��
	showBtnChipin(false);

	if (!pBackground)
		return;

	if (!pNodeTable)
		return;

	// ϴ���뷢�Ƶ��ӳټ��(s)
	//float totalDelay = MOUNT_SHUFFLE_CARD * DELAY_SHUFFLE_PER_CARD;
	float MountShuffleCard = SIX_GlobalMgr::GetInstance()->GetParamsIntValue("MOUNT_SHUFFLE_CARD");
	float DelayShufflePerCard = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_SHUFFLE_PER_CARD");
	float totalDelay = MountShuffleCard * DelayShufflePerCard;

	// ϴ��������
	for (int i=0;i<MountShuffleCard;i++)
	{
		// ϴ�Ƽ��
		CCDelayTime *pDelay = CCDelayTime::create(i*DelayShufflePerCard);
		// �ص�
		DELAY_INFO *pDelayInfo = new DELAY_INFO();
		pDelayInfo->idx = i;
		//pDelayInfo->offset = OFFSET_SHUFFLE_PER_CARD;
		pDelayInfo->offset = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("OFFSET_SHUFFLE_PER_CARD");
		CCCallFunc* pCallback = CCCallFuncND::create(this,callfuncND_selector(SIX_SceneGame::showSingleShuffleCard),(void*)pDelayInfo);
		CCFiniteTimeAction *pAction = CCSequence::create(pDelay,pCallback,0);
		this->runAction(pAction);
	}

	// �����ӳ�
	CCDelayTime *pDelay = CCDelayTime::create(totalDelay);
	// �ص�
	DELAY_INFO *pDealDelay = new DELAY_INFO();
	pDealDelay->delay = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_DEAL_PER_CARD");
	//pDealDelay->offset = OFFSET_SHUFFLE_PER_CARD;
	pDealDelay->offset = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("OFFSET_SHUFFLE_PER_CARD");
	CCCallFunc* pCallback = CCCallFuncND::create(this,callfuncND_selector(SIX_SceneGame::showAnimateDealCard),(void*)pDealDelay);
	CCFiniteTimeAction *pAction = CCSequence::create(pDelay,pCallback,0);
	this->runAction(pAction);
}

// ����ϴ�ƶ���
void SIX_SceneGame::showSingleShuffleCard(CCNode *pNode,void *pData)
{
	DELAY_INFO *pDelayInfo = static_cast<DELAY_INFO*>(pData);
	if (!pDelayInfo)
		return;
	int idx = pDelayInfo->idx;
	float offsetX = pDelayInfo->offset;
	CC_SAFE_DELETE(pDelayInfo);

	CCSpriteFrame *pCardFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S_card_reverse.png");
	if (!pCardFrame)
		return;

	SIX_CardItem *pCard = SIX_CardItem::create("","",12);
	if (!pCard)
		return;

	pCard->setCardPop(false);
	pCard->ignoreAnchorPointForPosition(true);
	//pCard->setAnchorPoint(ccp(0,0));
	pCard->setPreferredSize(pCardFrame->getOriginalSize());
	pCard->m_pBackgroundReverse = CCSprite::createWithSpriteFrame(pCardFrame);
	pCard->m_pBackgroundReverse->ignoreAnchorPointForPosition(true);
	pCard->m_pBatchNode = CCSpriteBatchNode::create("card.png");
	pCard->DoCardCombined();
	pCard->setTag(idx);
	// �Ƽ��
	pCard->setPosition(idx*offsetX,0.0f);
	pNodeShuffle->addChild(pCard);
}

// ��ʾ���ƶ���
void SIX_SceneGame::showAnimateDealCard(CCNode *pNode,void *pData)
{
	DELAY_INFO *pDelayInfo = static_cast<DELAY_INFO*>(pData);
	if (!pDelayInfo)
		return;

	float dealDelay = pDelayInfo->delay;
	float offsetX = pDelayInfo->offset;
	CC_SAFE_DELETE(pDelayInfo);

	// ��Ч���û���
	int validCount = 0;
	// �������ӳ�
	float percardTime = 0.0f;
	// �����ܺ�ʱ
	float validTime = 0.0f;

	// ����������
	//SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile("---------------------------------------------------------------------------");
	for (int j=0;j<3;j++)
	{
		for (int i=0;i<GAME_PLAYER_COUNT;i++)
		{
			// ����Ҫ�����û�״̬���жϣ��Ѿ���ʼ��Ϸ���û�����ʾ���ƶ�������������
			// Cool.Cat
			SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[i];
			if (!pSinglePlayer || (pSinglePlayer && pSinglePlayer->UserIdx<=0))
				continue;

			// ֻ���������û�
			if (!pSinglePlayer->bRaiseHand)
				continue;

			pDelayInfo = new DELAY_INFO();
			//pDelayInfo->idx = i;
			// idx=�û���ͼID*10+j
			int ViewID = SIX_PlayerMgr::GetInstance()->getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
			pDelayInfo->idx = ViewID*10+j;
			pDelayInfo->offset = offsetX;

			// ��ʾ�ƶ�
			this->showCardSuit(ViewID,true);
			// ����������ʵ��
			this->showCardItem(ViewID,j,false);

			// �ӳ�
			validCount++;
			percardTime = validCount * dealDelay;
			// ���Ƽ��
			CCDelayTime *pDelay = CCDelayTime::create(percardTime);
			// �ص�
			CCCallFunc* pCallback = CCCallFuncND::create(this,callfuncND_selector(SIX_SceneGame::showSingleDealCard),(void*)pDelayInfo);
			CCFiniteTimeAction *pAction = CCSequence::create(pDelay,pCallback,0);
			this->runAction(pAction);

			//SIXLog("showAnimateDealCard.i[%d].j[%d].validCount[%d].validTime[%.2f].idx[%d]",i,j,validCount,validTime,pDelayInfo->idx);
		}
	}
	//SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile("---------------------------------------------------------------------------");
	// �������һ����Ч�û����ƺ󣬻�Ҫ����ϴ����
	// Cool.Cat
	//validTime = percardTime + DELAY_DEAL_CARD_MOVE +1.0f;
	validTime = percardTime + SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_DEAL_CARD_MOVE") +1.0f;
	SIXLog("validCount[%d].validTime[%.2f]",validCount,validTime);
	// �ӳ�
	CCDelayTime *pDelay = CCDelayTime::create(validTime);
	// �ص�
	CCCallFunc* pCallback = CCCallFunc::create(this,callfunc_selector(SIX_SceneGame::hideNodeShuffleAndShowCardPoint));
	CCFiniteTimeAction *pAction = CCSequence::create(pDelay,pCallback,0);
	this->runAction(pAction);
}

// ����ϴ��������ʾ�Ƶ�(�ص�)
void SIX_SceneGame::hideNodeShuffleAndShowCardPoint()
{
	SIXLog("hideNodeShuffleAndShowCardPoint");
	pNodeShuffle->removeAllChildrenWithCleanup(true);
	this->showNodeShuffle(false);

	// ����������������
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN,REQ_SEND_FINISH);
}

// �����ƶ���
void SIX_SceneGame::showSingleDealCard(CCNode *pNode,void *pData)
{
	DELAY_INFO *pDelayInfo = static_cast<DELAY_INFO*>(pData);
	if (!pDelayInfo)
		return;

	// ������Ч
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(600,false);

	int ViewID = (int)(pDelayInfo->idx/10);
	int cardIdx = (pDelayInfo->idx-ViewID*10)%3;
	float offsetX = pDelayInfo->offset;

	//SIXLog("ViewID[%d].cardIdx[%d]",ViewID,cardIdx);

	PLAYER_ZONE_INFO *pPlayZone = this->getPlayerZone(ViewID);
	if (!pPlayZone || !pPlayZone->wCardSuit)
	{
		CC_SAFE_DELETE(pDelayInfo);
		return;
	}

	CCSpriteFrame *pCardFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("S_card_reverse.png");
	if (!pCardFrame)
	{
		CC_SAFE_DELETE(pDelayInfo);
		return;
	}

	SIX_CardItem *pCard = SIX_CardItem::create("","",12);
	if (!pCard)
	{
		CC_SAFE_DELETE(pDelayInfo);
		return;
	}

	pCard->ignoreAnchorPointForPosition(true);
	//pCard->setAnchorPoint(ccp(0,0));
	pCard->setPreferredSize(pCardFrame->getOriginalSize());
	pCard->m_pBackgroundReverse = CCSprite::createWithSpriteFrame(pCardFrame);
	pCard->m_pBackgroundReverse->ignoreAnchorPointForPosition(true);
	pCard->m_pBatchNode = CCSpriteBatchNode::create("card.png");
	pCard->DoCardCombined();
	pCard->setTag(pDelayInfo->idx);
	// �Ƽ��
	//pCard->setPosition(idx*offsetX,0.0f);
	// ���÷�����ʼƫ��Ϊϴ�������һ����ƫ��
	int MountShuffleCard = SIX_GlobalMgr::GetInstance()->GetParamsIntValue("MOUNT_SHUFFLE_CARD");
	pCard->setPosition((MountShuffleCard-1)*offsetX,0.0f);
	pNodeShuffle->addChild(pCard);

	// ϴ��������
	CCPoint nodeOffset = pNodeShuffle->getPosition();
	// Ҫ�������ӵ�ƫ��
	nodeOffset.x += pNodeTable->getPositionX();
	// ��ƫ��
	CCPoint cardOffset = CCPoint(nodeOffset.x+ViewID*offsetX,nodeOffset.y);

	// Ŀ��Ƕ�
	float angle = 0.0f;
	// ȡ�ƶ������Ļ�ľ���ƫ��
	CCPoint absOffset = pPlayZone->wCardSuit->getAbsOffset();
	switch (cardIdx)
	{
	case 0:
		{
			absOffset.x += pPlayZone->wCardItem1->getPositionX();
			absOffset.y += pPlayZone->wCardItem1->getPositionY();
			angle = pPlayZone->wCardItem1->getRotation();
			break;
		}
	case 1:
		{
			absOffset.x += pPlayZone->wCardItem2->getPositionX();
			absOffset.y += pPlayZone->wCardItem2->getPositionY();
			angle = pPlayZone->wCardItem2->getRotation();
			break;
		}
	case 2:
		{
			absOffset.x += pPlayZone->wCardItem3->getPositionX();
			absOffset.y += pPlayZone->wCardItem3->getPositionY();
			angle = pPlayZone->wCardItem3->getRotation();
			break;
		}
	}
	// �Ƶ��ƶѵ����ƫ��
	CCPoint relOffset = CCPoint(absOffset.x-cardOffset.x+ViewID*offsetX,absOffset.y-cardOffset.y);
	//SIXLog("relOffset[%d] = { %.2f , %.2f }",idx,relOffset.x,relOffset.y);

	// ��������㵽�յ�Ƕ�
	float h = sqrt(pow(relOffset.x,2.0f)+pow(relOffset.y,2.0f));
	// ����
	float arc = acos(relOffset.y/h);
	// �Ƕ�
	float arcAngle = (arc*360.0f)/(2*M_PI);
	// Ҫ���½Ƕ�
	if (relOffset.x<0)
		arcAngle = -arcAngle;
	// ����Ϊ0��
	pCard->setRotation(0.0f);
	// ��ת�Ƕ�����
	angle -= arcAngle;
	//CCRotateTo *pRotate = CCRotateTo::create(DELAY_DEAL_CARD_SPIN,angle);
	CCRotateTo *pRotate = CCRotateTo::create(SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_DEAL_CARD_SPIN"),angle);
	pCard->runAction(pRotate);
	//SIXLog("idx[%d].x/y/h[%.2f/%.2f/%.2f].arc[%.2f].angle[%.2f]",idx,relOffset.x,relOffset.y,h,arc,angle);

	// λ��
	//CCMoveTo *pMove = CCMoveTo::create(DELAY_DEAL_CARD_MOVE,relOffset);
	CCMoveTo *pMove = CCMoveTo::create(SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_DEAL_CARD_MOVE"),relOffset);
	CCArray *pArray = CCArray::create();
	pArray->addObject(pMove);
	// �ص�
	pArray->addObject(CCCallFuncN::create(this,callfuncN_selector(SIX_SceneGame::OnDealCardDone)));
	pCard->runAction(CCSequence::create(pArray));
	CC_SAFE_DELETE(pDelayInfo);
}

// ��������ɻص�
void SIX_SceneGame::OnDealCardDone(CCNode *pNode)
{
	int ViewID = (int)(pNode->getTag()/10);
	int cardIdx = (pNode->getTag()-ViewID)%3;
	//SIXLog("OnDealCardDone.ViewID[%d].cardIdx[%d]",ViewID,cardIdx);

	// ���Ƴ���ת��������������ڵĻ�
	// Cool.Cat
	pNode->stopAllActions();

	// ���Ƴ�����
	pNode->removeAllChildrenWithCleanup(true);
	pNode->removeFromParentAndCleanup(true);

	// ���ƶ���
	// Cool.Cat
	SinglePlayer *pSinglePlayer = 0;
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[i];
		if (pSinglePlayer && pSinglePlayer->UserIdx>0 && pSinglePlayer->bRaiseHand)
		{
			// ��ͼIDһ��
			if (ViewID==SIX_PlayerMgr::getViewID(pSinglePlayer->SeatId,SIX_PlayerMgr::GetInstance()->getMySeatIdx()))
				break;
		}
	}

	if (!pSinglePlayer)
		return;

	//// �����Ƶ�
	//SIX_GlobalMgr::GetInstance()->GetLogger()->WriteToFile("OnDealCardDone.ViewID[%d].cardIdx[%d].point[%d].type[%d]",
	//	ViewID,
	//	cardIdx,
	//	CARD_VALUE(pSinglePlayer->UserCardData[cardIdx]),
	//	CARD_COLOR_C(pSinglePlayer->UserCardData[cardIdx]));
	this->SetCardPointAndType(ViewID,cardIdx,CARD_VALUE(pSinglePlayer->UserCardData[cardIdx]),CARD_COLOR_C(pSinglePlayer->UserCardData[cardIdx]));
	if (cardIdx==2)
	{
		// ��ʾ��3���Ƶ�
		this->SetCardFrontShow(ViewID,2,false);
	}
	else
	{
		// ��ʾ����
		this->SetCardFrontShow(ViewID,cardIdx,true);
	}
	// ��ʾ��ʵ��
	this->showCardItem(ViewID,cardIdx,true);
	//SIXLog("OnDealCardDone.ViewID[%d].cardIdx[%d]",ViewID,cardIdx);
}

// ��ʾ��ע����
void SIX_SceneGame::showAnimateChip(unsigned int playerIdx,unsigned int chipPoint)
{
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(playerIdx));
	if (!pPlayerZone || !pPlayerZone->wChipPanel)
		return;

	// ��ע��Ч
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(300,false);

	pPlayerZone->wChipPanel->setVisible(true);

	// ������û���Ϣ���������ע������ƫ��
	if (pPlayerZone->wMoney)
	{
		// �û���Ϣͷ�����������������ƫ��
		CCSize size = pPlayerZone->wFaceLogo->getContentSize();
		CCPoint offsetStart = pPlayerZone->wFaceLogo->getPosition();
		CCPoint offsetInfo = pPlayerZone->wPlayerInfo->getPosition();

		offsetStart.x += (offsetInfo.x + size.width)/2.0f;
		offsetStart.y += (offsetInfo.y + size.height)/2.0f;

		// ��ע�������������������ƫ��
		CCPoint offsetEnd = pPlayerZone->wChipSprite->getPosition();
		CCPoint offsetPanel = pPlayerZone->wChipPanel->getPosition();

		offsetEnd.x += offsetPanel.x;
		offsetEnd.y += offsetPanel.y;

		// ���ƫ��У��
		offsetStart.x -= offsetEnd.x;
		offsetStart.y -= offsetEnd.y;

		// ��ע����
		// Cool.Cat
		// 1W����=1�����붯��
		int count = (int)(chipPoint/10000.0f)+1;
		// ���붯���������5��
		count = (count>5)?5:count;
		for (int i=0;i<count;i++)
		{
			CCSprite *pChipSprite = CCSprite::create("game_chip.png");
			if (!pChipSprite)
			{
				SetChipPanelNumber(playerIdx,0,true);
				return;
			}

			// ����ѵ�ƫ��
			offsetEnd.x = pPlayerZone->wChipSprite->getPositionX();
			offsetEnd.y = pPlayerZone->wChipSprite->getPositionY() + (i+1) * 2.0f;

			// ��һ�����붯����Я������
			if (i==0)
			{
				// �����ͼID
				pPlayerZone->wChipPanel->setUserData((void*)playerIdx);
				// ��ע������
				pChipSprite->setUserData((void*)chipPoint);
			}
			pChipSprite->setTag(100+i);
			pPlayerZone->wChipPanel->addChild(pChipSprite);

			// ���ö�����ʼƫ��
			pChipSprite->setPosition(offsetStart);
			//SIXLog("offsetStart[%.2f/%.2f].offsetEnd[%.2f/%.2f]",offsetStart.x,offsetStart.y,offsetEnd.x,offsetEnd.y);

			// ����
			CCArray *pArray = CCArray::create();
			// �ӳ�
			CCDelayTime *pDelay = CCDelayTime::create(i*0.1f);
			pArray->addObject(pDelay);
			// �����յ�ƫ��
			CCMoveTo *pMove = CCMoveTo::create(0.3f,offsetEnd);
			pArray->addObject(pMove);
			// �ص�
			pArray->addObject(CCCallFuncN::create(pChipSprite,callfuncN_selector(SIX_SceneGame::OnChipDone)));
			CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
			pChipSprite->runAction(pTimeAction);
		}
	}
}

void SIX_SceneGame::OnChipDone(CCNode *pNode)
{
	int beFirst = pNode->getTag();

	// ֻ�е�һ�����붯����Я������
	// Cool.Cat
	if (beFirst==100)
	{
		unsigned int playerIdx = (unsigned int)(pNode->getParent()->getUserData());
		unsigned int chipPoint = (unsigned int)(pNode->getUserData());
		//SIXLog("RemoveMotion.playerIdx[%u].chipPoint[%u]",playerIdx,chipPoint);
		this->SetChipPanelNumber(playerIdx,chipPoint);
	}
}

// �����м�����(Ĭ��˳ʱ��)
void SIX_SceneGame::doSortCustomInfo(SIX_TVector<CUSTOM_INFO*> *customVec,bool bClockwise)
{
	unsigned int count = 0;
	// ׯ����ͼID
	int BankerViewID = SIX_PlayerMgr::GetInstance()->getBankerViewID();
	// �����м���ͼID
	int customViewID = (BankerViewID==4)?0:bClockwise?BankerViewID+1:BankerViewID-1;
	// �����м�����ָ��
	CUSTOM_INFO *pTmpCustomInfo = 0;
	while (customVec->GetCount()>count)
	{
		for (unsigned int i=0;i<customVec->GetCount();i++)
		{
			pTmpCustomInfo = customVec->Get(i);
			if (!pTmpCustomInfo)
				continue;
			if (pTmpCustomInfo->ViewID!=customViewID)
				continue;
			CUSTOM_INFO *pCustomInfo = new CUSTOM_INFO();
			pCustomInfo->ViewID = pTmpCustomInfo->ViewID;
			pCustomInfo->bBanker = pTmpCustomInfo->bBanker;
			pCustomInfo->ChipCount = pTmpCustomInfo->ChipCount;
			pCustomInfo->UserID = pTmpCustomInfo->UserID;
			pCustomInfo->lGameTax = pTmpCustomInfo->lGameTax;
			pCustomInfo->CardType = pTmpCustomInfo->CardType;
			pCustomInfo->CardPoint = pTmpCustomInfo->CardPoint;
			SIX_PlayerMgr::GetInstance()->mCustomWin.Push(pCustomInfo);
			count++;
			break;
		}
		// ˳ʱ��
		if (bClockwise)
		{
			if (customViewID==4)
				customViewID = 0;
			else
				customViewID++;
		}
		// ��ʱ��
		else
		{
			if (customViewID==0)
				customViewID = 4;
			else
				customViewID--;
		}
	}

	// clear tmp vec
	customVec->Destory();

	// debug print
	for (unsigned int i=0;i<SIX_PlayerMgr::GetInstance()->mCustomWin.GetCount();i++)
	{
		CUSTOM_INFO *pCustomInfo = SIX_PlayerMgr::GetInstance()->mCustomWin.Get(i);
		if (!pCustomInfo)
			continue;
		SIXLog("pCustomInfo[%d].ViewID[%d/%d].UserID[%lld].ChipCount[%lld]",i,pCustomInfo->ViewID,BankerViewID,pCustomInfo->UserID,pCustomInfo->ChipCount);
	}
	SIXLog("----------------------------------");
}

// ��ʾ���㶯��(���հ�)
void SIX_SceneGame::showAnimateSettleAccountsFinal()
{
	float delayShowCardMove = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_SHOWCARD_MOVE");
	// ��ʾ������ʾ����ʼ�������ơ�
	if (!m_pTipsShowCard)
	{
		m_pTipsShowCard = SIX_TipsPopWnd::Create(0.0,0.0,ccc4(0,0,0,0),721.0,77.0);
		if (!m_pTipsShowCard)
			return;
		m_pTipsShowCard->InitMask(ccc4(0,0,0,0));
		m_pTipsShowCard->backgroundWithFile("tips_bg.png");
		m_pTipsShowCard->setShowType(MOVABLE_TOP);
		m_pTipsShowCard->setHideType(MOVABLE_NONE);
		m_pTipsShowCard->setShakeOffset(0.0f);
		m_pTipsShowCard->setSeqExec(true);
		m_pTipsShowCard->setAllowDragged(false);
		// ȡ�����ô���������
		m_pTipsShowCard->setHideWhenTouched(false);
		// ������ʾ/����λ�Ʋ���
		m_pTipsShowCard->setParamsShowMovable(delayShowCardMove/4.0f,delayShowCardMove/4.0f,delayShowCardMove/4.0f,delayShowCardMove/4.0f);
		m_pTipsShowCard->setTips(/*��ʼ��������*/XorStr<0xBF,13,0x4F6E91D5>("\x00\x6A\x0B\x7E\x11\x04\x71\x08\x06\x09\x0C\x0C"+0x4F6E91D5).s,"΢���ź�",22);	
	}
	m_pTipsShowCard->Show();

	// ͣ���ص�������
	float delayShowCardHoldOn = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_SHOWCARD_HOLDON");
	CCDelayTime *pDelay = CCDelayTime::create(delayShowCardMove+delayShowCardHoldOn);
	CCCallFunc* pCallback = CCCallFunc::create(this,callfunc_selector(SIX_SceneGame::onBankerShowCard));
	CCFiniteTimeAction *pAction = CCSequence::create(pDelay,pCallback,0);
	this->runAction(pAction);

	// �ӳٺ�ֱ�����������мұ���
	float delayShowCardBanker = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_SHOWCARD_BANKER");
	pDelay = CCDelayTime::create(delayShowCardMove + delayShowCardHoldOn + delayShowCardBanker);
	pCallback = CCCallFunc::create(this,callfunc_selector(SIX_SceneGame::showAnimateSettleAccounts));
	pAction = CCSequence::create(pDelay,pCallback,0);
	this->runAction(pAction);
}

// ׯ������/����
void SIX_SceneGame::onBankerShowCard()
{
	SIXLog("ׯ������");
	if (m_pTipsShowCard)
		m_pTipsShowCard->Show(false);

	CUSTOM_INFO *pCustomInfo = SIX_PlayerMgr::GetInstance()->getBankerInfo();
	if (!pCustomInfo)
		return;

	// ������Ч
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(200,false);

	// ׯ������3����
	this->SetCardFrontShow(SIX_PlayerMgr::GetInstance()->getBankerViewID(),2,true);
	// ׯ������
	this->showStatsPanel(SIX_PlayerMgr::GetInstance()->getBankerViewID(),pCustomInfo->CardPoint,pCustomInfo->ChipCount>0?true:false,pCustomInfo->CardType==1,pCustomInfo->CardType==2,pCustomInfo->CardType==4);
}

// �м�����/����
void SIX_SceneGame::onCustomShowCard(CCNode *pNode)
{
	CUSTOM_INFO *pCustomInfo = (CUSTOM_INFO*)pNode->getUserData();
	if (!pCustomInfo)
		return;

	SIXLog("�м�[%d]����",pCustomInfo->ViewID);

	// ������Ч
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(200,false);

	// �м�����3����
	pSceneGame->SetCardFrontShow(pCustomInfo->ViewID,2,true);
	// �м�����
	pSceneGame->showStatsPanel(pCustomInfo->ViewID,pCustomInfo->CardPoint,pCustomInfo->ChipCount>0?true:false,pCustomInfo->CardType==1,pCustomInfo->CardType==2,pCustomInfo->CardType==4);
}

// ��ʾ���㶯��
void SIX_SceneGame::showAnimateSettleAccounts()
{
	float delayShowCardCustom = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_SHOWCARD_CUSTOM");
	float delayChipExchange = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_CHIP_EXCHANGE");
	float delayChipMove = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_CHIP_MOVE");
	SIXLog("��ʼ����.delayShowCardCustom[%.2f].delayChipExchange[%.2f].delayChipMove[%.2f]",delayShowCardCustom,delayChipExchange,delayChipMove);

	int loseCount = 0;
	int winCount = 0;

	// �Լ���Ӯ״̬
	bool bMySelfWin = false;

	// ��ǰ�����м�����ָ��
	CUSTOM_INFO *pCustomInfo = 0;
	for (unsigned int i=0;i<SIX_PlayerMgr::GetInstance()->mCustomWin.GetCount();i++)
	{
		pCustomInfo = SIX_PlayerMgr::GetInstance()->mCustomWin.Get(i);
		// ����λ������û������
		if (!pCustomInfo)
			continue;

		// ����ׯ��
		if (pCustomInfo->bBanker)
			continue;

		// ����
		PLAYER_ZONE_INFO *pPlayerZone = this->getPlayerZone(pCustomInfo->ViewID);
		if (!pPlayerZone)
			continue;

		// Ӯ������Ч
		// add by Ivan_han 20131102
		SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(1200,false);

		// �Լ���Ӯ״̬
		if (pCustomInfo->ViewID==3)
		{
			if (pCustomInfo->ChipCount>0)
				bMySelfWin = true;
		}

		//pPlayerZone->wChipPanel->setTag(pCustomInfo->ViewID);
		pPlayerZone->wChipPanel->setUserData((void*)pCustomInfo);

		// ��ǰ�м��ӳ�����3����/����
		CCDelayTime *pDelay = CCDelayTime::create((delayShowCardCustom+delayChipExchange+delayChipMove)*i);
		CCCallFunc* pCallback = CCCallFuncN::create(pPlayerZone->wChipPanel,callfuncN_selector(SIX_SceneGame::onCustomShowCard));
		CCFiniteTimeAction *pAction = CCSequence::create(pDelay,pCallback,0);
		pPlayerZone->wChipPanel->runAction(pAction);

		// ��ǰ�мҳ�����㶯��
		CCArray *pArray = CCArray::create();
		pDelay = CCDelayTime::create((delayShowCardCustom+delayChipExchange+delayChipMove)*i+delayShowCardCustom);
		pArray->addObject(pDelay);
		// �м���(ׯ��Ӯ)
		if (pCustomInfo->ChipCount<0)
		{
			loseCount++;
			pArray->addObject(CCCallFuncN::create(pPlayerZone->wChipPanel,callfuncN_selector(SIX_SceneGame::OnCustomLoseSettleAccounts)));
			WLOG("showAnimateSettleAccounts[%lld].ViewID[%d].UserID[%lld].chipCount[%lld].A",SIX_PlayerMgr::GetInstance()->getMyUserIdx(),pCustomInfo->ViewID,pCustomInfo->UserID,pCustomInfo->ChipCount);
		}
		// �м�Ӯ(ׯ����)
		else if (pCustomInfo->ChipCount>0)
		{
			winCount++;
			pArray->addObject(CCCallFuncN::create(pPlayerZone->wChipPanel,callfuncN_selector(SIX_SceneGame::OnCustomWinSettleAccounts)));
			WLOG("showAnimateSettleAccounts[%lld].ViewID[%d].UserID[%lld].chipCount[%lld].B",SIX_PlayerMgr::GetInstance()->getMyUserIdx(),pCustomInfo->ViewID,pCustomInfo->UserID,pCustomInfo->ChipCount);
		}
		else
		{
			WLOG(/*��ӮΪ�㣡*/XorStr<0x9F,11,0xFF79ECE2>("\x55\x44\x72\x0C\x6D\x0E\x64\x45\x04\x09"+0xFF79ECE2).s);
		}
		CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
		pPlayerZone->wChipPanel->runAction(pTimeAction);
	}

	float totalDelay = (delayShowCardCustom+delayChipExchange+delayChipMove)*(winCount+loseCount);
	SIXLog("totalDelay=%.2f",totalDelay);

	// �����˱�����ɺ���ʾ�Լ����ֵ���Ӯͳ��
	this->showStatsMySelfWinOrLose(totalDelay,bMySelfWin);

	// ��������
	CCArray *pArray = CCArray::create();
	CCDelayTime *pDelay = CCDelayTime::create(totalDelay);
	pArray->addObject(pDelay);
	// �ص�
	pArray->addObject(CCCallFunc::create(this,callfunc_selector(SIX_SceneGame::OnClearData)));
	CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
	this->runAction(pTimeAction);
}

// ��������
void SIX_SceneGame::OnClearData()
{
	SIX_PlayerMgr::GetInstance()->mCustomWin.Destory();
	// ��������������л�����������
	// Cool.Cat
	SIX_PlayerMgr::GetInstance()->setAllowChangeToHall(true);
}

// �мҽ���ص�(��)
void SIX_SceneGame::OnCustomLoseSettleAccounts(CCNode *pNode)
{
	CCSprite *pChipPanel = dynamic_cast<CCSprite*>(pNode);
	if (!pChipPanel)
		return;
	CUSTOM_INFO *pCustomInfo = (CUSTOM_INFO*)pNode->getUserData();
	int ViewID = pCustomInfo->ViewID;
	TChip chipCount = pCustomInfo->ChipCount;

	//WLOG("OnCustomLoseSettleAccounts[%lld].ViewID[%d].chipCount[%lld].A",SIX_PlayerMgr::GetInstance()->getMyUserIdx(),ViewID,chipCount);

	// ��ǰ�м�
	PLAYER_ZONE_INFO *pPlayerZone = pSceneGame->getPlayerZone((unsigned int)ViewID);
	if (!pPlayerZone)
	{
		WLOG(/*OnCustomLoseSettleAccounts[%lld].ViewID[%d].chipCount[%lld].B*/XorStr<0x21,62,0x47ABE921>("\x6E\x4C\x60\x51\x56\x52\x48\x45\x65\x45\x58\x49\x7E\x4B\x5B\x44\x5D\x57\x72\x57\x56\x59\x42\x56\x4D\x49\x60\x19\x51\x52\x5B\x1D\x6F\x14\x2A\x21\x32\x0F\x03\x13\x6C\x2E\x16\x62\x2E\x26\x26\x20\x12\x3D\x26\x3A\x21\x0D\x72\x34\x35\x3E\x06\x72\x1F"+0x47ABE921).s,
			SIX_PlayerMgr::GetInstance()->getMyUserIdx(),ViewID,chipCount);
		return;
	}

	// ׯ��
	int BankerViewID = SIX_PlayerMgr::getViewID(SIX_PlayerMgr::GetInstance()->m_wBankerChairID,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
	PLAYER_ZONE_INFO *pBankerZone = pSceneGame->getPlayerZone(BankerViewID);
	if (!pBankerZone)
	{
		WLOG(/*OnCustomLoseSettleAccounts[%lld].ViewID[%d].chipCount[%lld].C*/XorStr<0x0D,62,0x26CC3947>("\x42\x60\x4C\x65\x62\x66\x7C\x79\x59\x79\x64\x7D\x4A\x7F\x6F\x68\x71\x7B\x5E\x43\x42\x4D\x56\x4A\x51\x55\x7C\x0D\x45\x46\x4F\x71\x03\x78\x46\x55\x46\x7B\x77\x6F\x10\x52\x6A\x16\x5A\x52\x52\x4C\x7E\x51\x4A\x2E\x35\x19\x66\x28\x29\x22\x1A\x66\x0A"+0x26CC3947).s,
			SIX_PlayerMgr::GetInstance()->getMyUserIdx(),ViewID,chipCount);
		return;
	}

	//WLOG("OnCustomLoseSettleAccounts[%lld].ViewID[%d].chipCount[%lld].D",SIX_PlayerMgr::GetInstance()->getMyUserIdx(),ViewID,chipCount);

	// ��������ӳ�
	float delayChipExchange = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_CHIP_EXCHANGE");
	// �����ƶ��ӳ�
	float delayChipMove = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_CHIP_MOVE");

	// ���浱ǰ��ƫ��
	CCPoint *offsetNow = new CCPoint();
	offsetNow->x = pChipPanel->getPositionX();
	offsetNow->y = pChipPanel->getPositionY();
	pChipPanel->setUserData((void*)offsetNow);

	// ׯ����Ϣͷ�����������������ƫ��
	CCSize size = CCSize(pBankerZone->wFaceLogo->getTextureRect().size.width,pPlayerZone->wFaceLogo->getTextureRect().size.height);
	CCPoint offsetEnd = pBankerZone->wFaceLogo->getPosition();
	CCPoint offsetInfo = pBankerZone->wPlayerInfo->getPosition();
	CCPoint offsetRoot = pBankerZone->wRoot->getPosition();

	offsetEnd.x = offsetRoot.x + offsetInfo.x + (offsetEnd.x + size.width)/2.0f;
	offsetEnd.y = offsetRoot.y + offsetInfo.y + (offsetEnd.y + size.height)/2.0f;

	//SIXLog("offsetEnd[%.2f/%.2f].offsetInfo[%.2f/%.2f].offsetRoot[%.2f/%.2f]",offsetEnd.x,offsetEnd.y,offsetInfo.x,offsetInfo.y,offsetRoot.x,offsetRoot.y);

	// �м���ע�������������������ƫ��
	CCPoint offsetStart = pPlayerZone->wChipPanel->getPosition();
	CCPoint offsetRoot2 = pPlayerZone->wRoot->getPosition();

	offsetStart.x += offsetRoot2.x;
	offsetStart.y += offsetRoot2.y;

	//SIXLog("offsetStart[%.2f/%.2f].offsetRoot2[%.2f/%.2f]",offsetStart.x,offsetStart.y,offsetRoot2.x,offsetRoot2.y);

	// �յ�ƫ��У��
	offsetEnd.x = offsetEnd.x - offsetStart.x;
	offsetEnd.y = offsetEnd.y - offsetStart.y;

	//SIXLog("offsetEnd[%.2f/%.2f]",offsetEnd.x,offsetEnd.y);

	// ����
	CCArray *pArray = CCArray::create();
	// �����յ�ƫ��
	CCMoveBy *pMove = CCMoveBy::create(delayChipMove,offsetEnd);
	pArray->addObject(pMove);
	// �ص�
	pArray->addObject(CCCallFuncN::create(pChipPanel,callfuncN_selector(SIX_SceneGame::OnCustomSettleAccountsChipMoveDone)));
	CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
	pChipPanel->runAction(pTimeAction);
}

// �мҽ���ص�(Ӯ)
void SIX_SceneGame::OnCustomWinSettleAccounts(CCNode *pNode)
{
	CCSprite *pChipPanel = dynamic_cast<CCSprite*>(pNode);
	if (!pChipPanel)
		return;
	CUSTOM_INFO *pCustomInfo = (CUSTOM_INFO*)pNode->getUserData();
	int ViewID = pCustomInfo->ViewID;
	TChip chipCount = pCustomInfo->ChipCount;

	//WLOG("OnCustomWinSettleAccounts[%lld].ViewID[%d].chipCount[%lld].A",SIX_PlayerMgr::GetInstance()->getMyUserIdx(),ViewID,chipCount);

	// ��ǰ�м�
	PLAYER_ZONE_INFO *pPlayerZone = pSceneGame->getPlayerZone((unsigned int)ViewID);
	if (!pPlayerZone)
	{
		WLOG(/*OnCustomWinSettleAccounts[%lld].ViewID[%d].chipCount[%lld].B*/XorStr<0xC0,61,0x2B9D9D4A>("\x8F\xAF\x81\xB6\xB7\xB1\xA9\xAA\x9F\xA0\xA4\x98\xA9\xB9\xBA\xA3\xB5\x90\xB1\xB0\xBB\xA0\xB8\xA3\xAB\x82\xFF\xB7\xB0\xB9\x83\xF1\xB6\x88\x87\x94\xAD\xA1\xBD\xC2\x8C\xB4\xC4\x88\x84\x84\x9E\xAC\x9F\x84\x9C\x87\xAF\xD0\x9A\x9B\x9C\xA4\xD4\xB9"+0x2B9D9D4A).s,
			SIX_PlayerMgr::GetInstance()->getMyUserIdx(),ViewID,chipCount);
		return;
	}

	//WLOG("OnCustomWinSettleAccounts[%lld].ViewID[%d].chipCount[%lld].C",SIX_PlayerMgr::GetInstance()->getMyUserIdx(),ViewID,chipCount);

	// ��������ӳ�
	float delayChipExchange = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_CHIP_EXCHANGE");
	// �����ƶ��ӳ�
	float delayChipMove = SIX_GlobalMgr::GetInstance()->GetParamsFloatValue("DELAY_CHIP_MOVE");

	// ���浱ǰ��ƫ��
	CCPoint *offsetNow = new CCPoint();
	offsetNow->x = pPlayerZone->wChipPanel->getPositionX();
	offsetNow->y = pPlayerZone->wChipPanel->getPositionY();
	pPlayerZone->wChipPanel->setUserData((void*)offsetNow);

	// �û���Ϣͷ�����������������ƫ��
	CCSize size = CCSize(pPlayerZone->wFaceLogo->getTextureRect().size.width,pPlayerZone->wFaceLogo->getTextureRect().size.height);
	CCPoint offsetEnd = pPlayerZone->wFaceLogo->getPosition();
	CCPoint offsetInfo = pPlayerZone->wPlayerInfo->getPosition();

	offsetEnd.x = offsetInfo.x + size.width/2.0f;
	offsetEnd.y = offsetInfo.y + size.height/2.0f;

	// ��ע�������������������ƫ��
	CCPoint offsetStart = pPlayerZone->wChipSprite->getPosition();
	CCPoint offsetPanel = pPlayerZone->wChipPanel->getPosition();

	offsetStart.x += offsetPanel.x;
	offsetStart.y += offsetPanel.y;

	// ���ƫ��У��
	offsetEnd.x -= offsetStart.x;
	offsetEnd.y -= offsetStart.y;

	//SIXLog("offsetEnd[%.2f/%.2f]",offsetEnd.x,offsetEnd.y);

	// ����
	CCArray *pArray = CCArray::create();
	// �����յ�ƫ��
	CCMoveBy *pMove = CCMoveBy::create(delayChipMove,offsetEnd);
	pArray->addObject(pMove);
	// �ص�
	pArray->addObject(CCCallFuncN::create(pChipPanel,callfuncN_selector(SIX_SceneGame::OnCustomSettleAccountsChipMoveDone)));
	CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
	pChipPanel->runAction(pTimeAction);
}

// �мҽ��㶯���ص�
void SIX_SceneGame::OnCustomSettleAccountsChipMoveDone(CCNode *pNode)
{
	CCSprite *pChipPanel = dynamic_cast<CCSprite*>(pNode);
	if (!pChipPanel)
		return;

	CCPoint *offsetOgi = (CCPoint*)(pNode->getUserData());
	// ����
	pChipPanel->setVisible(false);
	// ƫ��������
	pChipPanel->setPosition(*offsetOgi);
	// �Ƴ��Ѿ���ע�ĳ���
	for (unsigned int i=0;i<pChipPanel->getChildrenCount();i++)
	{
		CCNode *pChild = dynamic_cast<CCNode*>(pChipPanel->getChildren()->objectAtIndex(i));
		if (pChild && pChild->getTag()>=100)
		{
			//SIXLog("OnCustomSettleAccountsChipMoveDone.tag[%d]",pChild->getTag());
			// �ӳ��Ƴ�
			CCDelayTime *pDelay = CCDelayTime::create(0.1f);
			CCArray *pArray = CCArray::create();
			pArray->addObject(pDelay);
			pArray->addObject(CCCallFuncN::create(pChild,callfuncN_selector(SIX_SceneGame::OnChipRemove)));
			CCFiniteTimeAction *pTimeAction = CCSequence::create(pArray);
			pChild->runAction(pTimeAction);
		}
	}
	CC_SAFE_DELETE(offsetOgi);
}

// �Ƴ���̬����
void SIX_SceneGame::OnChipRemove(CCNode* pNode)
{
	pNode->removeAllChildrenWithCleanup(true);
	pNode->removeFromParentAndCleanup(true);
}

// ���ó�����������ʾ
void SIX_SceneGame::SetChipPanelNumber(unsigned int playerIdx,unsigned chipPoint,bool bShow)
{
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(playerIdx));
	if (!pPlayerZone || !pPlayerZone->wChipPanel)
		return;

	// ��������
	if (pPlayerZone->wChipPoint)
	{
		pPlayerZone->wChipPoint->setString(CCString::createWithFormat("%u",chipPoint)->getCString());
		SIX_Utility::GetInstance()->FixedTexParameters(pPlayerZone->wChipPoint->getTexture(),true);
	}
	pPlayerZone->wChipPanel->setVisible(bShow);
	// ��������
	pPlayerZone->wChipSprite->setVisible(false);
}

// ��ʾ�û���Ϣ��
void SIX_SceneGame::showPlayerZoneShow(unsigned int playerIdx,bool bShow)
{
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(playerIdx));
	if (!pPlayerZone || !pPlayerZone->wChipPanel)
		return;

	if (pPlayerZone->wPlayerInfo)
		pPlayerZone->wPlayerInfo->setVisible(bShow);
}

// �����û���Ϣ���ǳ�
void SIX_SceneGame::setPlayerZoneNickName(unsigned int playerIdx,const char *name)
{
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(playerIdx));
	if (!pPlayerZone || !pPlayerZone->wNickName)
		return;

	pPlayerZone->wNickName->setString(SIX_Utility::GetInstance()->G2U(name).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pPlayerZone->wNickName->getTexture(),true);
}

// �����û���Ϣ��ͷ��
void SIX_SceneGame::setPlayerZoneFaceLogo(unsigned int playerIdx, long long llSysLogoID)
{
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(playerIdx));
	if (!pPlayerZone || !pPlayerZone->wFaceLogo)
		return;

	CCString *pstrPath = CCString::createWithFormat("face_%lld.jpg", llSysLogoID);
	CCTexture2D *pLogo = CCTextureCache::sharedTextureCache()->addImage(pstrPath->getCString());
	if (pLogo)
	{
		pPlayerZone->wFaceLogo->setTexture(pLogo);
		pPlayerZone->wFaceLogo->setContentSize(CCSize(85,85));
	}
}

// �����û���Ϣ������
void SIX_SceneGame::setPlayerZoneChip(unsigned int playerIdx,unsigned int chip)
{
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(playerIdx));
	if (!pPlayerZone || !pPlayerZone->wMoney)
		return;

	pPlayerZone->wMoney->setString(SIX_Utility::GetInstance()->G2U(CCString::createWithFormat("%u",chip)->getCString()).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pPlayerZone->wMoney->getTexture(),true);
}

// �����û�Ϊׯ��
void SIX_SceneGame::showPlayerRubBanker(unsigned int playerIdx,bool bShow)
{
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(playerIdx));
	if (!pPlayerZone || !pPlayerZone->wBanker)
		return;

	pPlayerZone->wBanker->setVisible(bShow);
}

// ����ָ����Ҹ�����Ϣ����͸����
void SIX_SceneGame::setPlayerZoneOpacity(unsigned int idx,unsigned char opacity)
{
	if (!pBackground)
		return;

	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(idx));
	if (!pPlayerZone)
		return;

	if (pPlayerZone->wPlayerInfo)
		pPlayerZone->wPlayerInfo->setOpacity(opacity);
	if (pPlayerZone->wNickName)
		pPlayerZone->wNickName->setOpacity(opacity);
	if (pPlayerZone->wFaceLogo)
		pPlayerZone->wFaceLogo->setOpacity(opacity);
	if (pPlayerZone->wMoney)
		pPlayerZone->wMoney->setOpacity(opacity);
}

PLAYER_ZONE_INFO *SIX_SceneGame::getPlayerZone(unsigned int idx)
{
	if (!pBackground)
		return NULL;

	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(SIX_CardPlay::GetInstance()->Get(idx));
	return pPlayerZone;
}

// ��ʾ����
void SIX_SceneGame::showCardSuit(unsigned int playerIdx,bool bShow)
{
	SIX_CardPlay *pCardPlay = SIX_CardPlay::GetInstance();
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(pCardPlay->Get(playerIdx));
	if (!pPlayerZone)
		return;

	if (pPlayerZone->wCardSuit)
	{
		pPlayerZone->wCardSuit->setVisible(bShow);
		//pPlayerZone->wCardSuit->setCardFrontShowAll(bShow);
	}
}

// ��ʾ�ڼ�����
void SIX_SceneGame::showCardItem(unsigned int playerIdx,unsigned int cardIdx,bool bShow)
{
	SIX_CardPlay *pCardPlay = SIX_CardPlay::GetInstance();
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(pCardPlay->Get(playerIdx));
	if (!pPlayerZone)
		return;

	if (pPlayerZone->wCardSuit)
	{
		switch (cardIdx)
		{
		case 0:pPlayerZone->wCardItem1->setVisible(bShow);break;
		case 1:pPlayerZone->wCardItem2->setVisible(bShow);break;
		case 2:pPlayerZone->wCardItem3->setVisible(bShow);break;
		}
	}
}

// ��ʾͳ�ƽ��
void SIX_SceneGame::showStatsPanel(unsigned int playerIdx,unsigned int point,bool isWin,bool bPointShow,bool b3GongShow,bool bBombShow)
{
	SIX_CardPlay *pCardPlay = SIX_CardPlay::GetInstance();
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(pCardPlay->Get(playerIdx));
	if (!pPlayerZone)
		return;

	if (bPointShow || b3GongShow || bBombShow)
	{
		pPlayerZone->wStatsPanel->setVisible(true);
	}
	else
	{
		pPlayerZone->wStatsPanel->setVisible(false);
	}
	//// ��ʾ/�Ƴ�����ͳ��
	//this->showTipStats(playerIdx,point,isWin,bPointShow,b3GongShow,bBombShow);

	// ��ʾ�Ƶ�
	if (pPlayerZone->wStatsPoint)
	{
		if (bPointShow)
		{
			CCString *pPoint = 0;
			// �Լ���ʾ������
			if (this->IsMySelf(playerIdx))
				pPoint = CCString::createWithFormat("b_%u.png",point);
			// ������ʾС����
			else
				pPoint = CCString::createWithFormat("s_%u.png",point);

			// ��������
			CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pPoint->getCString());
			if (pFrame)
			{
				//pPlayerZone->wStatsPoint->setTexture(pFrame->getTexture());
				pPlayerZone->wStatsPoint->setDisplayFrame(pFrame);
			}
		}
		pPlayerZone->wStatsPoint->setVisible(bPointShow);
	}

	// ��ʾ����
	if (pPlayerZone->wStats3Gong)
		pPlayerZone->wStats3Gong->setVisible(b3GongShow);
	// ��ʾը��
	if (pPlayerZone->wStatsBomb)
		pPlayerZone->wStatsBomb->setVisible(bBombShow);
	// ����
	if (pPlayerZone->wStatsDot)
	{
		CCString *pDot = 0;
		// �Լ���ʾ������
		if (this->IsMySelf(playerIdx))
		{
			// 0123456
			if (point<7)
			{
				pDot = CCString::create("b_sdot.png");
			}
			// 789
			else
			{
				pDot = CCString::create("b_bdot.png");
			}
		}
		else
		{
			// 0123456
			if (point<7)
			{
				pDot = CCString::create("s_sdot.png");
			}
			// 789
			else
			{
				pDot = CCString::create("s_bdot.png");
			}
		}
		// ��������
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pDot->getCString());
		if (pFrame)
		{
			//pPlayerZone->wStatsDot->setTexture(pFrame->getTexture());
			pPlayerZone->wStatsDot->setDisplayFrame(pFrame);
		}
		pPlayerZone->wStatsDot->setVisible(bPointShow);
	}
}

// ��ʾʤ��
void SIX_SceneGame::showStatsMySelfWinOrLose(float delay,bool bWin)
{
	SIXLog("��Ӯͳ��[%.2f].bWin[%d]",delay,bWin);

	// ��Ӯ��Ч
	// add by Ivan_han 20131102
	unsigned int nSoundId=bWin?1100:800;
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(nSoundId,false);


	this->showNodeDice(true);
	
	pNodeDice->removeAllChildrenWithCleanup(true);

	//CCSpriteBatchNode *pBatchNode = CCSpriteBatchNode::create(CCString::create("dot.png")->getCString());
	//if (!pBatchNode)
	//	return;

	//pNodeDice->addChild(pBatchNode);

	//// ʤ��֡
	//CCSpriteFrame *pDiceDropFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("b_%s.png",bWin?"win":"lose")->getCString());
	//if (!pDiceDropFrame)
	//	return;

	//CCSprite *pResult = CCSprite::createWithSpriteFrame(pDiceDropFrame);
	//if (!pResult)
	//	return;

	//pResult->ignoreAnchorPointForPosition(true);
	//pResult->setAnchorPoint(ccp(0,0));
	//CCSize nodeSize = pNodeDice->getContentSize();
	//CCSize resultSize = pResult->getContentSize();
	//CCPoint offset = CCPointZero;
	//offset.x = (nodeSize.width-resultSize.width)/2;
	//offset.y = (nodeSize.height-resultSize.height)/2;
	//pResult->setPosition(offset);
	//pBatchNode->addChild(pResult);

	// ���
	CCDelayTime *pDelay = CCDelayTime::create(delay);
	CCCallFunc* pCallback = CCCallFunc::create(this,callfunc_selector(SIX_SceneGame::OnWinOrLoseDone));
	CCFiniteTimeAction *pAction = CCSequence::create(pDelay,pCallback,0);
	this->runAction(pAction);
}

// ʤ�������ص�
void SIX_SceneGame::OnWinOrLoseDone()
{
	pNodeDice->removeAllChildrenWithCleanup(true);
	pNodeDice->setVisible(false);

	// ������ӮTips����
	// Cool.Cat

	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		int ViewID = SIX_PlayerMgr::getViewID(i,SIX_PlayerMgr::GetInstance()->getMySeatIdx());
		PLAYER_ZONE_INFO *pPlayerZone = this->getPlayerZone(ViewID);
		if (!pPlayerZone)
			continue;
		
		SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[i];

		// ��ׯ���û�Ҫ����ׯ��ͼ��
		if (pPlayerZone->wBanker)
		{
			if (pPlayer && pPlayer->SeatId!=SIX_PlayerMgr::GetInstance()->m_wBankerChairID)
				pPlayerZone->wBanker->setVisible(false);
		}

		// ������ͷ��ָ�����͸��(δ׼��״̬)
		if (pPlayerZone->wPlayerInfo)
			pPlayerZone->wPlayerInfo->setOpacity(128);
		if (pPlayerZone->wNickName)
			pPlayerZone->wNickName->setOpacity(128);
		if (pPlayerZone->wFaceLogo)
			pPlayerZone->wFaceLogo->setOpacity(128);
		if (pPlayerZone->wMoney)
			pPlayerZone->wMoney->setOpacity(128);
	}
	//// ��ʾ׼����ʾ
	//showSprReady();
	// ��ʾ׼����ť
	showBtnReady();
	// ��һ�ֿ�ʼ׼��ʱ��
	//showCountDown(true,DELAY_READY);
	showCountDown(true,SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_READY"));
}

// �����Լ�/�Է�������(����/��С��ɫ)ƫ��
CCPoint SIX_SceneGame::caclCardFrontOffset(unsigned int point,CARD_TYPE type,bool isFaceBig,bool isMySelf)
{
	CCPoint cp = CCPointZero;
	switch (type)
	{
	case TYPE_SPADE:
	case TYPE_HEART:
	case TYPE_CLUB:
	case TYPE_DIAMOND:
		{
			// �Լ�
			if (isMySelf)
			{
				// ��ɫ
				if (isFaceBig)
				{
					if (point>10)
					{
						cp.x = 10.0f;
						cp.y = 5.0f;
					}
					else
					{
						cp.x = 25.0f;
						cp.y = 10.0f;
					}
				}
				// С��ɫ
				else
				{
					cp.x = 5.0f;
					cp.y = 50.0f;
				}
			}
			// ����
			else
			{
				// ��ɫ
				if (isFaceBig)
				{
					if (point>10)
					{
						cp.x = 3.0f;
						cp.y = 3.0f;
					}
					else
					{
						cp.x = 15.0f;
						cp.y = 5.0f;
					}
				}
				// С��ɫ
				else
				{
					cp.x = 5.0f;
					cp.y = 25.0f;
				}
			}
			break;
		}
	case TYPE_BLACK_JOKER:
	case TYPE_RED_JOKER:
		{
			// �Լ�
			if (isMySelf)
			{
				// ��ɫ
				if (isFaceBig)
				{
					cp.x = 10.0f;
					cp.y = 5.0f;
				}
				// С��ɫ
				else
				{
					cp.x = 5.0f;
					cp.y = 35.0f;
				}
			}
			else
			{
				// ��ɫ
				if (isFaceBig)
				{
					cp.x = 3.0f;
					cp.y = 3.0f;
				}
				// С��ɫ
				else
				{
					cp.x = 2.0f;
					cp.y = 15.0f;
				}
			}
			break;
		}
	}
	return cp;
}

// �����Ƶ㼰����
void SIX_SceneGame::SetCardPointAndType(unsigned int playerIdx,unsigned int cardIdx,unsigned char point,CARD_TYPE type)
{
	// �������
	if (playerIdx>6 || cardIdx>2 || point>15 || type<=TYPE_UNKNOWN || type>TYPE_RED_JOKER)
	{
		SIXLog("OnSetCardPointAndType.Overflow.playerIdx[%u].cardIdx[%u].point[%u].type[%d]",
			playerIdx,cardIdx,point,type);
		return;
	}

	//SIXLog("OnSetCardPointAndType.playerIdx[%u].cardIdx[%u].point[%u].type[%d]",playerIdx,cardIdx,point,type);

	// �����Ƶ�
	SIX_CardPlay *pCardPlay = SIX_CardPlay::GetInstance();
	PLAYER_ZONE_INFO *pPlayerZone = (PLAYER_ZONE_INFO*)(pCardPlay->Get(playerIdx));
	if (!pPlayerZone)
		return;

	if (cardIdx==0 && !pPlayerZone->wCardItem1 ||
		cardIdx==1 && !pPlayerZone->wCardItem2 ||
		cardIdx==2 && !pPlayerZone->wCardItem3)
		return;

	unsigned char pPrefixFormat = 0;
	CCString *pPrefixFaceB = 0;
	if (point==11)
		pPrefixFaceB = CCString::create("Jack");
	else if (point==12)
		pPrefixFaceB = CCString::create("Queen");
	else if (point==13)
		pPrefixFaceB = CCString::create("King");

	// �Լ���ʾ������(B)
	if (this->IsMySelf(playerIdx))
		pPrefixFormat = 0x42;
	// ������ʾС����(S)
	else
		pPrefixFormat = 0x53;

	// ����
	CCString *pPoint = 0;
	CCString *pFaceS = 0;
	CCString *pFaceB = 0;
	switch (type)
	{
		// ��(S)
	case TYPE_SPADE:
		{
			pPoint = CCString::createWithFormat("%c_B%u.png",pPrefixFormat,point);
			pFaceS = CCString::createWithFormat("%c_SS.png",pPrefixFormat);
			if (pPrefixFaceB)
				pFaceB = CCString::createWithFormat("%c_%s.png",pPrefixFormat,pPrefixFaceB->getCString());
			else
				pFaceB = CCString::createWithFormat("%c_SB.png",pPrefixFormat);
			break;
		}
		// ��(H)
	case TYPE_HEART:
		{
			pPoint = CCString::createWithFormat("%c_R%u.png",pPrefixFormat,point);
			pFaceS = CCString::createWithFormat("%c_HS.png",pPrefixFormat);
			if (pPrefixFaceB)
				pFaceB = CCString::createWithFormat("%c_%s.png",pPrefixFormat,pPrefixFaceB->getCString());
			else
				pFaceB = CCString::createWithFormat("%c_HB.png",pPrefixFormat);
			break;
		}
		// ÷(C)
	case TYPE_CLUB:
		{
			pPoint = CCString::createWithFormat("%c_B%u.png",pPrefixFormat,point);
			pFaceS = CCString::createWithFormat("%c_CS.png",pPrefixFormat);
			if (pPrefixFaceB)
				pFaceB = CCString::createWithFormat("%c_%s.png",pPrefixFormat,pPrefixFaceB->getCString());
			else
				pFaceB = CCString::createWithFormat("%c_CB.png",pPrefixFormat);
			break;
		}
		// ��(D)
	case TYPE_DIAMOND:
		{
			pPoint = CCString::createWithFormat("%c_R%u.png",pPrefixFormat,point);
			pFaceS = CCString::createWithFormat("%c_DS.png",pPrefixFormat);
			if (pPrefixFaceB)
				pFaceB = CCString::createWithFormat("%c_%s.png",pPrefixFormat,pPrefixFaceB->getCString());
			else
				pFaceB = CCString::createWithFormat("%c_DB.png",pPrefixFormat);
			break;
		}
		// С��
	case TYPE_BLACK_JOKER:
		{
			pPoint = CCString::create("");
			pFaceS = CCString::createWithFormat("%c_BJ.png",pPrefixFormat);
			pFaceB = CCString::createWithFormat("%c_BlackJoker.png",pPrefixFormat);
			break;
		}
		// ����
	case TYPE_RED_JOKER:
		{
			pPoint = CCString::create("");
			pFaceS = CCString::createWithFormat("%c_RJ.png",pPrefixFormat);
			pFaceB = CCString::createWithFormat("%c_RedJoker.png",pPrefixFormat);
			break;
		}
	default:
		{
			SIXLog("type.Unknown[%d]!",type);
			return;
		}
	}

	//SIXLog("pPoint[%s].pFaceS[%s].pFaceB[%s]",pPoint->getCString(),pFaceS->getCString(),pFaceB->getCString());

	// �Ƶ�����
	CCSpriteFrame *pPointFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pPoint->getCString());
	// С��ɫ����
	CCSpriteFrame *pFaceSFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFaceS->getCString());
	// ��ɫ����
	CCSpriteFrame *pFaceBFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFaceB->getCString());

	// �����Լ�/�Է�������(����/��С��ɫ)ƫ��
	CCPoint cpP = CCPointZero;
	if (this->IsMySelf(playerIdx))
	{
		cpP.x = 5.0f;
		cpP.y = 80.0f;
	}
	else
	{
		cpP.x = 5.0f;
		cpP.y = 40.0f;
	}

	CCPoint cpS = this->caclCardFrontOffset(point,type,false,this->IsMySelf(playerIdx));
	CCPoint cpB = this->caclCardFrontOffset(point,type,true,this->IsMySelf(playerIdx));

	switch (cardIdx)
	{
		// ��1
	case 0:
		{
			pPlayerZone->wCardItem1->setCardPointPosition(cpP);
			pPlayerZone->wCardItem1->setCardSmallFacePosition(cpS);
			pPlayerZone->wCardItem1->setCardBigFacePosition(cpB);
			pPlayerZone->wCardItem1->setCardPointAndType(pPointFrame,pFaceSFrame,pFaceBFrame,point,type);
			break;
		}
		// ��2
	case 1:
		{
			pPlayerZone->wCardItem2->setCardPointPosition(cpP);
			pPlayerZone->wCardItem2->setCardSmallFacePosition(cpS);
			pPlayerZone->wCardItem2->setCardBigFacePosition(cpB);
			pPlayerZone->wCardItem2->setCardPointAndType(pPointFrame,pFaceSFrame,pFaceBFrame,point,type);
			break;
		}
		// ��3
	case 2:
		{
			pPlayerZone->wCardItem3->setCardPointPosition(cpP);
			pPlayerZone->wCardItem3->setCardSmallFacePosition(cpS);
			pPlayerZone->wCardItem3->setCardBigFacePosition(cpB);
			pPlayerZone->wCardItem3->setCardPointAndType(pPointFrame,pFaceSFrame,pFaceBFrame,point,type);
			break;
		}
	default:
		{
			SIXLog("cardIdx.Unknown[%d]!",cardIdx);
			return;
		}
	}
}

// ����ʱ
void SIX_SceneGame::showCountDown(bool bShow,int delay)
{
	SIXLog("showCountDonw.bShow[%d].delay[%d]",bShow,delay);

	if (!bShow)
	{
		CC_SAFE_DELETE(pCountDownBatchNode);
		return;
	}

	if (delay<=0)
		return;

	// �ȸɵ��ϵĵ���ʱ
	CC_SAFE_DELETE(pCountDownBatchNode);

	CCSize size = CCEGLView::sharedOpenGLView()->getVisibleSize();

	pCountDownBatchNode = SIX_CountDownBatchNode::Create("countdown.png","countdown_bg.png",delay,2.0f,2,CCSize(143,63),CCPoint(24,11),"countdown_");
	if (pCountDownBatchNode)
	{
		CCCallFuncND* pCallbackND = CCCallFuncND::create(this,callfuncND_selector(SIX_SceneGame::doTimeIsUp),(void*)delay);
		pCountDownBatchNode->SetCallFuncND(pCallbackND);
		pCountDownBatchNode->ignoreAnchorPointForPosition(true);
		pCountDownBatchNode->setAnchorPoint(ccp(0.5,0.5));
		pCountDownBatchNode->setPosition(ccp((size.width-pCountDownBatchNode->getContentSize().width)/2,(size.height-pCountDownBatchNode->getContentSize().height)*0.55));
		pCountDownBatchNode->setUserData((void*)delay);
		//SIXLog("pCountDownBatchNode.postion[%.2f/%.2f]",
		//	(size.width-pCountDownBatchNode->getContentSize().width)/2,
		//	(size.height-pCountDownBatchNode->getContentSize().height)/2);
		this->addChild(pCountDownBatchNode);
	}
}

// CCCallFuncND��m_targetӦΪ����Ķ������󣬵�������
// SetCallFuncND�������ɶ���ִ�еĻص�������pNodeΪ��
// Cool.Cat
void SIX_SceneGame::doTimeIsUp(CCNode *pNode,void *params)
{
	int delay = (int)params;
	SIXLog("doTimeIsUp.delay[%d]",delay);
	int DELAY_READY = SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_READY");
	int DELAY_RUBBANKER = SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_RUBBANKER");
	int DELAY_CHIPIN_FIRST = SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_CHIPIN_FIRST");
	int DELAY_CHIPIN = SIX_GlobalMgr::GetInstance()->GetParamsIntValue("DELAY_CHIPIN");

	// ��ׯ�ȴ�ʱ�� -> ������ׯ����
	if (delay==DELAY_RUBBANKER)
	{
		// ����Լ��Ѿ�����ׯ�ˣ�����������
		SinglePlayer *pPlayer = &SIX_PlayerMgr::GetInstance()->m_Players[SIX_PlayerMgr::GetInstance()->getMySeatIdx()];
		if (pPlayer && pPlayer->byCallBanker==1)
			return;

		Req_UserCallBanker req;
		req.llUserID=SIX_PlayerMgr::GetInstance()->getMyUserIdx();
		req.iSeatNo=SIX_PlayerMgr::GetInstance()->getMySeatIdx();
		req.bCall=false;
		SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN,REQ_USER_CALL_BANKER,(BYTE*)(&req), sizeof(req));

		// ������ׯ��ť
		this->showBtnRubBanker(false);
	}
	// ��һ����ע�ȴ�ʱ�� -> ����Ͷ����ע
	// ��ע�ȴ�ʱ�� -> ����Ͷ����ע
	else if (delay==DELAY_CHIPIN_FIRST || delay==DELAY_CHIPIN)
	{
		Req_UserChipin req;
		req.llUserID=SIX_PlayerMgr::GetInstance()->getMyUserIdx();
		req.iSeatNo=SIX_PlayerMgr::GetInstance()->getMySeatIdx();
		req.lScore=SIX_PlayerMgr::GetInstance()->m_C1;
		SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN,REQ_USER_CHIPIN,(BYTE*)(&req), sizeof(req));

		// ������ע��ť
		this->showBtnChipin(false);
	}
	// ׼���ȴ�ʱ�� -> �˳���Ϸ�������л�����������
	else if (delay==DELAY_READY)
	{
		SIX_Proxy::GetInstance()->SetChangeScene(true);
	}
	else
	{
		SIXLog("[%d]what do u think about?",delay);
	}
}
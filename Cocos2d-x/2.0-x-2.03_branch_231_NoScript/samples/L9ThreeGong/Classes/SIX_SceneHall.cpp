#include "SIX_Common.h"
#include "SIX_SceneHall.h"
#include "SIX_SceneGame.h"
#include "SIX_PlayerMgr.h"
#include "SIX_RoomMgr.h"
#include "SIX_ClientHall.h"
#include "SIX_ClientRoom.h"
#include <SIX_GlobalMgr.h>
#include "SIX_PopWndFirstBuy.h"
#include "SIX_PopWndHelp.h"

extern SCENE_IDX LAST_SCENE_IDX;
extern SIX_SceneGame *pSceneGame;
extern SIX_SceneHall *pSceneHall;

SIX_SceneHall::~SIX_SceneHall()
{
	CC_SAFE_DELETE(m_pWndTask);
	CC_SAFE_DELETE(m_pWndActivity);
	CC_SAFE_DELETE(m_pWndTopList);
	CC_SAFE_DELETE(m_pWndSetting);
	CC_SAFE_DELETE(m_pWndAward);
	CC_SAFE_DELETE(m_pWndShop);
	CC_SAFE_DELETE(m_pWndRoomList);
	CC_SAFE_DELETE(m_pWndPersionalInformation);
	pSceneHall = 0;
	SIXLog("~SIX_SceneHall");
}

SIX_SceneHall* SIX_SceneHall::scene()
{
	SIX_SceneHall *pScene = new SIX_SceneHall();
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->setObjName("SIX_SceneHall");
		pScene->autorelease();
		SIXLog("SIX_SceneHall[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
    return pScene;
}

bool SIX_SceneHall::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

	this->InitUIMgr();
	this->initWithColor(ccc4(255,255,255,128));

	int retv = this->GetUIMgr()->LoadXMLFromFile("Hall.xml");
	this->GetUIMgr()->ReleaseXML();
	SIXLog("SIX_SceneHall.init.retv[%d]",retv);

	m_pWndTask = NULL;
	m_pWndActivity = 0;
	m_pWndTopList = 0;
	m_pWndSetting = 0;
	m_pWndAward = 0;
	m_pWndShop = 0;
	m_pWndRoomList = 0;
	m_pWndPersionalInformation = 0;

	if (retv!=0)
	{
		m_Scene->release();
		return false;
	}

	return true;
}

// default implements are used to call script callback if exist
void SIX_SceneHall::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneHall::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneHall::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneHall::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneHall::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
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

void SIX_SceneHall::onEnter()
{
	CCLayerColor::onEnter();
	SIX_PopWnd::setPopWndCount(0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
	//setAccelerometerEnabled(true);
}

void SIX_SceneHall::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	//SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();

#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(this);
#endif

	schedule(schedule_selector(SIX_SceneHall::update), 0.01f);

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

	pBackground = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	if (!pBackground)
		return;

	CCNode *pUserZone = pBackground->getChildByTag(BTN_USER);
	if (!pUserZone)
		return;

	pSprFaceLogo = dynamic_cast<CCSprite*>(pUserZone->getChildByTag(SPRITE_FACELOGO));
	pTTFNickName = dynamic_cast<CCLabelTTF*>(pUserZone->getChildByTag(TTF_NICKNAME));
	pSprLv = dynamic_cast<CCSprite*>(pUserZone->getChildByTag(SPRITE_LEVEL));
	pTTFLv = dynamic_cast<CCLabelTTF*>(pUserZone->getChildByTag(TTF_LEVEL));
	pProgressExp = dynamic_cast<CCProgressTimer*>(pUserZone->getChildByTag(PROGRESS_EXP));

	CCNode *pChipZone = pBackground->getChildByTag(BTN_GETCHIP);
	if (!pChipZone)
		return;

	pTTFChip = dynamic_cast<CCLabelTTF*>(pChipZone->getChildByTag(TTF_CHIP));

	CCNode *pTaskZone = pBackground->getChildByTag(BTN_TASK);
	if (!pTaskZone)
		return;

	pSprReward = dynamic_cast<CCSprite*>(pTaskZone->getChildByTag(SPR_REWARD));
	if (!pSprReward)
		return;

	pTTFReward = dynamic_cast<CCLabelTTF*>(pSprReward->getChildByTag(TTF_REWARD));

	setNickName(SIX_PlayerMgr::GetInstance()->getMyNickName());
	setLevel(SIX_PlayerMgr::GetInstance()->getMyLevel());
	setChip(SIX_PlayerMgr::GetInstance()->getMyChip());
	setFaceLogo(SIX_PlayerMgr::GetInstance()->getMyLogoID());
	
	CMD_InitHall initHall;
	initHall.llUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	initHall.iGameID = GAME_ID;
	SIX_ClientHall::GetInstance()->Connect(true);
	SIX_ClientHall::GetInstance()->SendData(MAIN_MSG_HALL, SUB_CSG_INIT_HALL, (BYTE *)&initHall, sizeof(initHall));
}

void SIX_SceneHall::onExitTransitionDidStart()
{
	CCLayerColor::onExitTransitionDidStart();
}

void SIX_SceneHall::onExit()
{
#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(0);
#endif
	CCLayerColor::onExit();
}

void SIX_SceneHall::onCloseExit()
{
	CCLayerColor::onCloseExit();
}

void SIX_SceneHall::OnNotifyCloseWndClicked(CCObject *pObj)
{
	SIXLog("断线重连失败！");
}

#ifdef WIN32
int SIX_SceneHall::OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam )
{
	if (m_pWndSetting && m_pWndSetting->IsShow())
		m_pWndSetting->OnAccelerometerKeyHook(message,wParam,lParam);

	switch (message)
	{
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_TAB:
				{
					if (0!=m_pWndShop  && 0!=m_pWndShop->GetPointCardWnd() && m_pWndShop->GetPointCardWnd()->IsShow())
						m_pWndShop->GetPointCardWnd()->DoSwitchIMEFocus();
					if (0!=m_pWndPersionalInformation  && m_pWndPersionalInformation->IsShow())
						m_pWndPersionalInformation->setFocus();
					break;
				}
			case VK_RETURN:
				{
					if (0!=m_pWndShop  && 0!=m_pWndShop->GetPointCardWnd() && m_pWndShop->GetPointCardWnd()->IsShow())
						m_pWndShop->GetPointCardWnd()->DoOK();
					if (0!=m_pWndPersionalInformation  && m_pWndPersionalInformation->IsShow())
						m_pWndPersionalInformation->setEnter();
					break;
				}
			}
		}
	}
	return 0;
}
#endif

void SIX_SceneHall::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	// 按钮音效
	// add by Ivan_han 20131102
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(100,false);

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{			
			switch (tag)
			{
			case BTN_RANK:	// 排行榜
				{
					if (0==m_pWndTopList)
						m_pWndTopList = SIX_PopWndTopList::Create(0.0,0.0f,ccc4(0,0,0,0),705,438,false);
					m_pWndTopList->ShowWnd();

					for (int i=1; i<=20; i++)
					{
						CMD_SC_RankingList tt;tt.nRank = i;tt.nValue = 100*i;tt.lSyslogoid = 10*i;_snprintf(tt.szNickName, sizeof(tt.szNickName), "cNickName_%d", i);
						CMD_SC_RankingList *pTT = &tt;
						m_pWndTopList->SetData(pTT);
					}
					m_pWndTopList->SetReceiveDataComplete();
					break;
				}
			case BTN_HELP:	// 帮助
				{
					SIX_PopWndHelp * pHelp = SIX_PopWndHelp::Create(0, 0, ccc4(0,0,0,0), 705,438, false, true);
					if (pHelp)
					{
						pHelp->InitMask(ccc4(0,0,0,128));
						pHelp->Show();
					}
					break;
				}
			case BTN_SETTING:	// 游戏设置
				{
					if (!m_pWndSetting)
					{
						m_pWndSetting = SIX_PopWndSetting::Create(0.0,0.0,ccc4(0,0,0,0),627,423,50.0f,MOVABLE_TOP,MOVABLE_TOP,true);
						m_pWndSetting->InitMask(ccc4(0,0,0,0));
						m_pWndSetting->backgroundWithFile("box_bg.png");
						m_pWndSetting->buttonCloseWithFileCell("btn_close.png",2);
						m_pWndSetting->GetBtnClose()->setPosition(ccp(590,392));
						m_pWndSetting->setAllowDragged(false);
					}
					m_pWndSetting->Show();
					break;
				}
			case BTN_GIFT: // 首购礼包
				{
					SIX_PopWndFirstBuy * pFirstBuy = SIX_PopWndFirstBuy::Create(0, 0, ccc4(0,0,0,0), 627,423);
					if (pFirstBuy)
					{
						pFirstBuy->InitMask(ccc4(0,0,0,128));
						pFirstBuy->Show();
					}
					break;
				}
			case BTN_QUICKSTART: // 快速游戏
				{
					if (SIX_ClientRoom::GetInstance()->getLogicConnect())
						return;
					// 断开当前的房间连接
					SIX_ClientRoom::GetInstance()->Disconnect();
					// 登录房间
					const CMD_SC_RoomList *pRoom = SIX_RoomMgr::GetInstance()->GetPlayerMaxRoom(SIX_PlayerMgr::GetInstance()->getMyChip());
					CCAssert(0!=pRoom, "没有房间！");
					if (0 != pRoom)
					{
						string addr(SIX_Utility::GetInstance()->NTOA(pRoom->lRoomTeltComIp));
						SIX_ClientRoom::GetInstance()->Connect(addr.c_str(),pRoom->iRoomPort, false);
					}
					break;
				}
			case BTN_HALL:	// 房间列表
				{
					if (0==m_pWndRoomList)
					{
						m_pWndRoomList = SIX_PopWndRoomList::Create(0.0,0.0f,ccc4(0,0,0,0),705,438,false);
					}
					m_pWndRoomList->ShowWnd();
					break;
				}
				// 通比竞技
			case BTN_ARENA:
				{
					break;
				}
			case BTN_REWARD:	// 领取礼品
				{
					if (0==m_pWndAward)
						m_pWndAward = SIX_PopWndAward::Create(0.0,0.0f,ccc4(0,0,0,0),705,438,false);
					m_pWndAward->ShowWnd();

					for (int i=1; i<=10; i++)
					{
						CMD_SC_Award tt;tt.nAwardID = i;tt.nReward = 1000*i;tt.nCount = 100*(i%2);
						if (i!=2  && i!=8)
							sprintf(tt.szFileName, "CM10.png");
						sprintf(tt.szDescription, "移动100元充值卡");
						CMD_SC_Award *pTT = &tt;
						m_pWndAward->SetData(pTT);
					}
					m_pWndAward->SetReceiveDataComplete();
					break;
				}
			case BTN_GETCHIP:	// 商城
				{
					if (0==m_pWndShop)
						m_pWndShop = SIX_PopWndShop::Create(0.0,0.0f,ccc4(0,0,0,0),705,438,false);
					m_pWndShop->ShowWnd();

					for (int i=1; i<=10; i++)
					{
						CMD_SC_Shop tt;
						tt.nID = i;tt.nGold = 10000*i;tt.nRenminbi = 100*i;CMD_SC_Shop *pTT = &tt;
						m_pWndShop->SetData(pTT);
					}
					m_pWndShop->SetReceiveDataComplete();
					break;
				}
			case BTN_ACTIVITY:	// 活动
				{
					if (0==m_pWndActivity)
						m_pWndActivity = SIX_PopWndActivity::Create(0.0,0.0f,ccc4(0,0,0,0),705,438,false);
					m_pWndActivity->ShowWnd();

					for (int i=1; i<=4; i++)
					{
						CMD_SC_ActivityList tt;
						tt.nID =i;
						_snprintf(tt.szName, sizeof(tt.szName), "name_%d", i);_snprintf(tt.szTitle, sizeof(tt.szTitle), "title_%d", i);_snprintf(tt.szDescription, sizeof(tt.szDescription), "Description_%d", i);_snprintf(tt.szStartTime, sizeof(tt.szStartTime), "2013/9/30 13:00");_snprintf(tt.szEndTime, sizeof(tt.szEndTime), "2013/10/1 12:00");CMD_SC_ActivityList *pTT = &tt;
						m_pWndActivity->SetData(pTT);
					}
					m_pWndActivity->SetReceiveDataComplete();
					break;
				}
			case BTN_TASK:	// 任务
				{
					if (0 == m_pWndTask)
						m_pWndTask = SIX_PopWndTask::Create(0.0,0.0f,ccc4(0,0,0,0),705,438,false);
					m_pWndTask->ShowWnd();
					break;
				}
			case BTN_USER:	// 个人信息
				{
					if (!m_pWndPersionalInformation)
						m_pWndPersionalInformation = SIX_PopWndPersonalInfomation::Create(0.0f,0.0f,ccc4(0,0,0,0),0.0f,0.0f,50.0f,MOVABLE_TOP,MOVABLE_TOP,true);
					
					m_pWndPersionalInformation->Show();
					break;
				}
			default: 
				{
					SIXLog("SIX_SceneHall::doEvents 未知按钮事件,  tag=%d", tag);
					break;
				}
			}
			break;
		}
	}
}

void SIX_SceneHall::update(float dt)
{
	if (SIX_Proxy::GetInstance()->IsChangeScene())
	{
		SIX_Proxy::GetInstance()->SetChangeScene(false);

		if (!pSceneGame)
		{
			pSceneGame = SIX_SceneGame::scene();
			if (!pSceneGame)
			{
				//CCMessageBox("创建场景失败！",0);
				return;
			}
		}
		LAST_SCENE_IDX = SCENE_IDX_HALL;
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2f,pSceneGame->GetScene(),ccc3(255, 255, 255)));
	}
}

// 设置头像
void SIX_SceneHall::setFaceLogo(long long llSysLogoID)
{
	if(!pSprFaceLogo)
		return;

	CCString *pstrPath = CCString::createWithFormat("face_%lld.jpg", llSysLogoID);
	CCTexture2D *pLogo = CCTextureCache::sharedTextureCache()->addImage(pstrPath->getCString());
	if (pLogo)
	{
		pSprFaceLogo->setTexture(pLogo);
	}
}

void SIX_SceneHall::setNickName(const char*szNickName)
{
	if (!pTTFNickName)
		return;

	pTTFNickName->setString(SIX_Utility::GetInstance()->G2U(szNickName).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pTTFNickName->getTexture(),true);
}

void SIX_SceneHall::setLevel(int Lv)
{
	if (!pTTFLv)
		return;

	pTTFLv->setString(CCString::createWithFormat("%d",Lv)->getCString());
	SIX_Utility::GetInstance()->FixedTexParameters(pTTFLv->getTexture(),true);

	// 设置级别ico
	if (!pSprLv)
		return;
}

void SIX_SceneHall::setChip(TChip Chip)
{
	if (!pTTFChip)
		return;

	pTTFChip->setString(CCString::createWithFormat("%lld",Chip)->getCString());
	SIX_Utility::GetInstance()->FixedTexParameters(pTTFChip->getTexture(),true);
}

// 设置可领取奖励提示
void SIX_SceneHall::setReward(int count)
{
	if (!pTTFReward)
		return;

	pTTFReward->setString(CCString::createWithFormat("%02d",count)->getCString());
	SIX_Utility::GetInstance()->FixedTexParameters(pTTFReward->getTexture(),true);

	// 奖励ico
	if (!pSprReward)
		return;

	pSprReward->setVisible(count==0?false:true);
}
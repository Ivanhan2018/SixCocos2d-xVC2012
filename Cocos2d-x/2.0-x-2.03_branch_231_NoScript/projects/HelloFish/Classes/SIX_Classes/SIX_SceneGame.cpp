#include "SIX_SceneGame.h"
#include "SIX_SceneGate.h"
#include "Ship.h"
#include "polygon.h"
#include <iterator>
#include <algorithm>
#include <SIX_GlobalMgr.h>
#include "SIX_MatchEnd.h"


extern SCENE_IDX LAST_SCENE_IDX;
extern double *s_AllFishArg;
extern double *s_AllBombArg;

extern SIX_SceneGate *pSceneGate;
extern SIX_SceneGame *pSceneGame;

extern int ARR_FISH[];
extern int ARR_FISH_COUNT;
extern int ARR_BOMB[];
extern int ARR_BOMB_COUNT;

extern int ARR_STARFISH_COUNT;

struct UpDownUserData
{
	UpDownUserData()
	{ 
		//ZeroMemory( this, sizeof(*this) ); 
		memset(this,0,sizeof(*this));
	}
	char cType[8];
	bool bComplete;
};

SIX_SceneGame::~SIX_SceneGame()
{
	pSceneGame = 0;
	SIXLog("~SIX_SceneGame");
}

SIX_SceneGame* SIX_SceneGame::scene()
{
	SIX_SceneGame *pScene = new SIX_SceneGame();
	//SIX_UIScene *pScene = (SIX_UIScene*)CCLayerColor::create(ccc4(255,255,255,128));
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->setObjName("SIX_SceneGame");
		pScene->autorelease();
		SIXLog("SIX_SceneGame[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		//CCTransitionScene *ptr = dynamic_cast<CCTransitionScene*>(pScene->GetScene());
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

	this->InitUIMgr();
	this->initWithColor(ccc4(255,255,255,128));

	int retv = this->GetUIMgr()->LoadXMLFromFile("Game.xml");
	this->GetUIMgr()->ReleaseXML();
	SIXLog("SIX_SceneGame.init.retv[%d]",retv);

	if (retv!=0)
		return false;

	m_uLastTick = 0;
	pSellFish=0;
	pBuyBullet = 0;
	pHelp = 0;
	pSetting = 0;	
	pConsole = 0;
	m_NeedDrawBox = false;
	m_WaitForChangeScene = false;
	m_pCurShowWnd = NULL;
	pCountDown = 0;
	m_bRepeatShoot = false;
	m_bNoFire = false;
	m_nKeyDownCount = 0;

	// ȡ�����ؼ�
	if (NULL == background)
	{
		background = dynamic_cast<CCLayerColor*>(getChildren()->objectAtIndex(0));
	}

	//add by Ivan_han 20130828
	m_pSysTip = dynamic_cast<CCLabelTTF*>(background->getChildByTag(900));
	//SetSysTip("���ѽ��벻������Ϸʱ�䣬Ϊ�����Ľ�������������������Ϣ���粻���ߣ��������彫�ܵ��𺦣����������ѽ�Ϊ�㣬ֱ�������ۼ�����ʱ����5Сʱ�󣬲��ָܻ�������");
	//SIX_Utility::GetInstance()->performWithDelay(this,callfunc_selector(SIX_SceneGame::ClearSysTip),30);

	m_ResProgress = dynamic_cast<CCLayer*>(background->getChildByTag(0));
	//m_WaveSprite = dynamic_cast<CCSprite*>(background->getChildByTag(998));

	// �����ײ���ť����
	// Cool.Cat
	CCSize size = CCEGLView::sharedOpenGLView()->getVisibleSize();
	CCLayer *pBottomButton = dynamic_cast<CCLayer*>(getChildByTag(1));
	if (pBottomButton)
	{
		CCControlButton *pBtn = dynamic_cast<CCControlButton*>(pBottomButton->getChildByTag(1));
		if (pBtn)
			pBtn->setPositionX(size.width/2-10-pBtn->getPreferredSize().width);

		pBtn = dynamic_cast<CCControlButton*>(pBottomButton->getChildByTag(2));
		if (pBtn)
			pBtn->setPositionX(size.width/2+10);
	}
	return true;
}

void SIX_SceneGame::OnTouchLogic(CCSet *pTouches,int pEvent)
{
	SIX_Cursor::GetInstance()->OnTouchLogic(pTouches,pEvent);
	
	if (!g_bInited)
		return;

	bool PushMouseLeftButton = false;
	bool bWhirlGun = false;
	bool bShootBullet = false;

	//CCTouch *pTouch = (CCTouch *)pTouches->anyObject();

	CCSetIterator it;
	for( it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCTouch *pTouch = (CCTouch *)(*it);
		// ���GL����ϵ
		CCPoint pos = pTouch->getLocation();
		//// �����Ļ����ϵ
		//CCPoint posInView = pTouch->getLocationInView();
		//// ת����location==pos
		//CCPoint location = CCDirector::sharedDirector()->convertToGL(posInView);

		//add by Ivan_han 20130529
		CCPoint SP=g_pShipMgr->CP2SP(pos);
		CCPoint CP=g_pShipMgr->SP2CP(SP);
	
		g_pShipMgr->onUpdateMousePT(pos);

		//SIXLog("OnTouchLogic.pTouches[0x%08X].pEvent[%d]",pTouches,pEvent);

		switch (pEvent)
		{
		case CCTOUCHBEGAN:
			{
				PushMouseLeftButton = true;
				m_ulKeyBoardPushTime = SIX_Utility::GetInstance()->GetTickCount();
				break;
			}
		case CCTOUCHMOVED:
			{
				bWhirlGun = true;
				break;
			}
		case CCTOUCHENDED:
			{
				// ���ǰ���ǵ����� ulTime �����ڵ�����꣬�����ڵ�������һ���ӵ���
				// �������ʱ�����������������ӵ���Ϊ�˸���ʵ�����������ӵ������󲻻��ٶ���෢��һ���ӵ�
				// ��Ϊ�������ﴦ�����Բż�����ж�
				unsigned long long ulDelayTime = BULLET_REPEATSHOOT_DELAY; 
				unsigned long long curTime = SIX_Utility::GetInstance()->GetTickCount();
				if ( m_ulKeyBoardPushTime + ulDelayTime > curTime )
					bShootBullet = true;

				PushMouseLeftButton = false;
				onRepeatShootBullet( false );
				break;
			}
		case CCTOUCHCANCELLED:
			{
				break;
			}
		case CCMOUSEMOVE:
			{
				//OnUpDownEffect( pos );
				bWhirlGun = true;

				// �ж��Ƿ��ƶ����Ӽ����ʵİ�ť����
				// Cool.Cat
				if (NULL != g_pShipMgr  &&  NULL != g_pShipMgr->getMySelfShip())
				{
					CCControlButton *pBtnInc = dynamic_cast<CCControlButton*>(g_pShipMgr->getMySelfShip()->m_shipSprite->getChildByTag(BTN_INC));
					CCControlButton *pBtnDec = dynamic_cast<CCControlButton*>(g_pShipMgr->getMySelfShip()->m_shipSprite->getChildByTag(BTN_DEC));
					if ((pBtnInc && pBtnInc->isTouchInside(pTouch)) || 
						(pBtnDec && pBtnDec->isTouchInside(pTouch)))
					{
						SIX_Cursor::GetInstance()->setShowOurCursor(FALSE);
						SIX_Cursor::GetInstance()->setShowSysCursor(TRUE);
					}
				}

				// �ж��Ƿ��ƶ������������˵�����
				if (pExpandLayer)
				{
					if (pExpandLayer->GetBtnExpand()->isTouchInside(pTouch) ||
						pExpandLayer->GetAnimate()->isTouchInside(pTouch))
					{
						SIX_Cursor::GetInstance()->setShowOurCursor(FALSE);
						SIX_Cursor::GetInstance()->setShowSysCursor(TRUE);
					}
				}
				break;
			}
		case CCMOUSERBUTTONUP:
			{
				if (NULL != g_pShipMgr  &&  NULL != g_pShipMgr->getMySelfShip())
				{
					g_pShipMgr->getMySelfShip()->IncBet();
				}
				break;
			}
		}
		
		if (bWhirlGun)
		{
			// �˴��п���ȡ������Ҫ���ж�
			// Cool.Cat
			CShip *pMyShip = g_pShipMgr->getMySelfShip();
			if (!pMyShip)
				return;
			pMyShip->onWhirlGun( pos );
		}

		// ��ס��겻�Ų��ƶ�������ǲ�������յ���Ϣ���������ߵ���δ���, ���Ե����ӵ������ж��ɿ����ʱ��ʱ������
		// С��BULLET_REPEATSHOOT_DELAYΪ���ŷ���
		// �����������ǰ���ʱ����һ���ȴ����������ʱ��ʱ���� BULLET_REPEATSHOOT_DELAY,
		// ���ʱ����û���ɿ����Ͳ���ɱ����ʱ�����������俪ʼ����
		if (bShootBullet)
		{
			// �˴��п���ȡ������Ҫ���ж�
			// Cool.Cat
			CShip *pMyShip = g_pShipMgr->getMySelfShip();
			if (!pMyShip)
				return;
			g_pShipMgr->onShootBullet(pMyShip->m_UserID, 0l, pos, false,false);
		}
		else if (PushMouseLeftButton)
		{
			if (!m_bRepeatShoot)
				onRepeatShootBullet( true );
		}
	}
}

// default implements are used to call script callback if exist
void SIX_SceneGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCTOUCHBEGAN);
}

void SIX_SceneGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCTOUCHMOVED);
}

void SIX_SceneGame::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCTOUCHENDED);
}

void SIX_SceneGame::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	OnTouchLogic(pTouches,CCTOUCHCANCELLED);
}

void SIX_SceneGame::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
{
	OnTouchLogic(pTouches, nType);
}

void SIX_SceneGame::onEnter()
{
	CCLayerColor::onEnter();
	SIX_PopWnd::setPopWndCount(0);

	setTouchEnabled(true);
	setKeypadEnabled(true);

	CCDirector::sharedDirector()->SetExitProxy( SIX_SceneGame::OnExitBtn );
	//setAccelerometerEnabled(true);
}

void SIX_SceneGame::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();

#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(this);
#endif

	if (SIX_Cursor::GetInstance()->LoadCursorFromFile("Scene/Game/aim.png"))
	{
		this->addChild(SIX_Cursor::GetInstance()->getCursor(),65535);
		SIX_Cursor::GetInstance()->setShowSysCursor(FALSE);
	}

	g_pGold = CGold::GetInstance();
	g_pShipMgr = CShipMgr::GetInstance();
	g_pBulletMgr = CBulletAndNetMgr::GetInstance();
	g_FishMgr = CFishMgr::GetInstance();

	schedule(schedule_selector(SIX_SceneGame::update), 0.01f);

	//ShowPopWndLoading(true)
	
	// -- �첽���� .plist �ļ�
	//SIX_Utility::addSpriteFramesWithPlistAsync(CCString::stringWithString("Scene/Game/FishAndBomb/DeadBomb.plist"), this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));
	
	SIX_Utility::addSpriteFramesWithPlistAsync(CCString::stringWithString("Scene/Game/GunBulletGold.plist"), this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));
	//���ת��
	SIX_Utility::addSpriteFramesWithPlistAsync(CCString::create("Scene/Game/GoldDisc.plist"),this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));
	
	s_AllFishArg = new double[ARR_FISH_COUNT];
	for (int i=0;i<ARR_FISH_COUNT;i++)
	{
		s_AllFishArg[i] = M_PI;
		int fishType=ARR_FISH[i];
		//SIXLog("fishType[%d]=%d",i,fishType);
		SIX_Utility::addSpriteFramesWithPlistAsync(CCString::createWithFormat("Scene/Game/FishAndBomb/Fish_%02d.plist",fishType),this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));
	}
	
	s_AllBombArg = new double[ARR_BOMB_COUNT];
	for (int i=0;i<ARR_BOMB_COUNT;i++)
	{
		s_AllBombArg[i] = M_PI;
		int BombType=ARR_BOMB[i];
		if(BombType==13)
			s_AllBombArg[i] = 0;
		//SIXLog("BombType[%d]=%d",i,BombType);
		SIX_Utility::addSpriteFramesWithPlistAsync(CCString::createWithFormat("Scene/Game/FishAndBomb/Bomb_%02d.plist",BombType),this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));
	}

	// ����
	for (int i=0;i<ARR_STARFISH_COUNT;i++)
	{
		SIX_Utility::addSpriteFramesWithPlistAsync(CCString::createWithFormat("Common/Effect/StarFish/StarFish%02d.plist",i+1),this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));		
	}

	// ����
	SIX_Utility::addSpriteFramesWithPlistAsync(CCString::create("Common/Effect/Shell/Shell.plist"),this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));

	// ����
	SIX_Utility::addSpriteFramesWithPlistAsync(CCString::create("Common/Effect/seagrass/seagrass.plist"),this,callfuncO_selector(SIX_SceneGame::AddImageAsyncCallBack));
}

void SIX_SceneGame::onExitTransitionDidStart()
{
	CCLayerColor::onExitTransitionDidStart();
}

void SIX_SceneGame::doExit()
{
	// δ��ʼ����֮ǰ�������˳�����ֹ����UIʱ����
	// Cool.Cat
	if (!this->IsInited())
		return;
	// ��ʱ�䵱�³����˳���־λ��~
	// Cool.Cat
	g_bInited = false;
	SIX_ClientRoom::GetInstance()->leave_seat();
	SIX_ClientRoom::GetInstance()->Disconnect();
	g_FishMgr->Release();
	g_pShipMgr->Release();
	g_pBulletMgr->Release();

	SIX_Utility::GetInstance()->ReleaseHitBox();
	CC_SAFE_RELEASE(pSellFish);
	CC_SAFE_RELEASE(pBuyBullet);
	CC_SAFE_RELEASE(pHelp);
	CC_SAFE_RELEASE(pSetting);

	CC_SAFE_RELEASE(pExpandLayer);
	//CC_SAFE_RELEASE(pCountDown);
	CC_SAFE_RELEASE(pConsole);

	CC_SAFE_DELETE(g_pGold);
	CC_SAFE_DELETE(g_pShipMgr);
	CC_SAFE_DELETE(g_pBulletMgr);
	CC_SAFE_DELETE(g_FishMgr);
}

void SIX_SceneGame::onExit()
{
	doExit();
#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(0);
#endif

	CC_SAFE_DELETE_ARRAY( s_AllFishArg );
	CC_SAFE_DELETE_ARRAY( s_AllBombArg );

	CCLayerColor::onExit();
	PlayerTreasureInfo::Instance().ResetFishKindNums();

	SIX_Cursor::GetInstance()->setInited(false);
	SIX_Cursor::GetInstance()->setShowSysCursor(TRUE);
	CCDirector::sharedDirector()->SetExitProxy( NULL );
}

void SIX_SceneGame::onCloseExit()
{
	SIX_ClientRoom::GetInstance()->Disconnect();
	CCLayerColor::onCloseExit();
}

void SIX_SceneGame::OnNotifyCloseWndClicked(CCObject *pObj)
{
	SIXLog("��������ʧ�ܣ�");
	SIXLog("�л����ؿ�����...");
	// ��������ʧ�ܺ��л����ؿ�������~
	// Cool.Cat
	SIX_Proxy::GetInstance()->SetChangeScene(true);
}

#ifdef WIN32
int SIX_SceneGame::OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam )
{
	//CCLOG("message %d=%x, wParam %d=%x\n", message, wParam);
	//SIXLog("SIX_SceneGame.OnAccelerometerKeyHook.MSG[%u==0x%x].wParam[%u].lParam[%ul]",message,message,wParam,lParam);

	shortcutKey(message, wParam, lParam);

	switch (message)
	{
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_RETURN:
				{
					if (pConsole)
						pConsole->DoEnter();
					break;
				}
			}
			break;
		}
	case WM_CHAR:
		{
			switch (wParam)
			{
			case VK_NUMPAD0:
				{
					ShowConsole();
					// hook
					return 1;
				}
			}
			break;
		}
	}
	return 0;
}

void SIX_SceneGame::OnProcessCommand(const char *cmd)
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
		pConsole->setContent(/*�汾��%d.%d.%d.%04d*/XorStr<0xBC,20,0x0A511B50>("\x0C\x5B\x0F\x01\x63\x7B\xE7\xA7\xEA\xE0\xA2\xE9\xED\xAD\xE4\xEE\xFC\xF9\xAA"+0x0A511B50).s,VER_MAIN,VER_CHILD,VER_STAGE,VER_BUILD);
		pConsole->setContent(/*---------------------------------------*/XorStr<0x40,40,0x7140E047>("\x6D\x6C\x6F\x6E\x69\x68\x6B\x6A\x65\x64\x67\x66\x61\x60\x63\x62\x7D\x7C\x7F\x7E\x79\x78\x7B\x7A\x75\x74\x77\x76\x71\x70\x73\x72\x4D\x4C\x4F\x4E\x49\x48\x4B"+0x7140E047).s);
	}
	else if (cmdCon==/*exit*/XorStr<0x29,5,0x39578028>("\x4C\x52\x42\x58"+0x39578028).s)
	{
		SIXLog("Sayonara!");
		SIX_ClientRoom::GetInstance()->Disconnect();
		CCDirector::sharedDirector()->end();
	}
	else if (cmdCon==/*stats*/XorStr<0x40,6,0x64B72E65>("\x33\x35\x23\x37\x37"+0x64B72E65).s)
	{
		int bulletCount = g_pBulletMgr->mMyBullet.size();
		int fishCount = g_FishMgr->mFishData.size();
		int bulletSpriteCount = g_pBulletMgr->sharedBullet()->getChildrenCount();

		int fishSpriteCount = 0;
		CCSpriteBatchNode **pArr = 0;
		pArr = g_FishMgr->sharedFish();
		for (int i=0;i<ARR_FISH_COUNT;i++)
			fishSpriteCount += pArr[i]->getChildrenCount();

		int bombSpriteCount = 0;
		pArr = g_FishMgr->sharedBomb();
		for (int i=0;i<ARR_BOMB_COUNT;i++)
			bombSpriteCount += pArr[i]->getChildrenCount();
		
		pConsole->setContent(/*�ӵ�ʵ�壺%d*/XorStr<0x7D,13,0x1708E767>("\xAA\xAD\xCA\x2F\x4B\x37\x4F\x61\x26\x3C\xA2\xEC"+0x1708E767).s,bulletCount);
		pConsole->setContent(/*��Ⱥʵ�壺%d*/XorStr<0x95,13,0x23C760BB>("\x46\x75\x5F\x22\x53\x2F\x57\x79\x3E\x24\xBA\xC4"+0x23C760BB).s,fishCount);
		pConsole->setContent(/*�ӵ����飺%d*/XorStr<0x0F,13,0x132BA852>("\xD8\xC3\xA4\xBD\xAD\xBF\xD4\xFF\xB4\xA2\x3C\x7E"+0x132BA852).s,bulletSpriteCount);
		pConsole->setContent(/*��Ⱥ���飺%d*/XorStr<0x48,13,0x7F799B33>("\x9B\xAA\x82\xF1\xF2\xE6\x8F\xA6\xF3\xEB\x77\x37"+0x7F799B33).s,fishSpriteCount);
		pConsole->setContent(/*ը�����飺%d*/XorStr<0x73,13,0x72F6152A>("\xA6\xDC\xC0\xD9\xC9\xD3\xB8\x93\xD8\xC6\x58\x1A"+0x72F6152A).s,bombSpriteCount);
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
					int value = atoi(mp->at(1).c_str());
					(value==0)?m_NeedDrawBox=false:m_NeedDrawBox=true;
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

int SIX_SceneGame::shortcutKey(UINT message,WPARAM wParam,LPARAM lParam)
{
	if (NULL != pConsole  &&  pConsole->IsShow())
		return 0;

	switch (message)
	{
	case WM_KEYUP:
		{
			if (0 < SIX_PopWnd::GetPopWndCount())
				return 0;
			switch (wParam)
			{
			case VK_LEFT:
			case VK_RIGHT:
				{
					if (!g_bInited)
						return 0;
					g_pShipMgr->getMySelfShip()->onWhirlGun(wParam==VK_LEFT ? true : false, false);
					break;
				}
			case VK_UP:
			case VK_SPACE:
				{
					unsigned long long ulDelayTime = BULLET_REPEATSHOOT_DELAY; 
					unsigned long long curTime = SIX_Utility::GetInstance()->GetTickCount();
					if (1 == m_nKeyDownCount  ||  m_ulKeyBoardPushTime + ulDelayTime > curTime)
					{
						CCPoint ptGunPos = g_pShipMgr->getMySelfShip()->m_shipSprite->getPosition();
						float fAngle = g_pShipMgr->getMySelfShip()->m_gunSprite->getRotation();
						// �ڹ����Ϸ�Ϊ0�ȣ���ת�����ҷ�Ϊ90����ת������Ϊ-90��
						// ��ʽ��Ҫ�����Ƕȣ����������ҷ�Ϊ0�ȣ�����Ϊ180�ȡ�
						fAngle = 90.0 - fAngle;
						g_pShipMgr->mTouchPT = SIX_Utility::GetInstance()->getAnotherCoordinate(ptGunPos, fAngle, 50);
						g_pShipMgr->onShootBullet(g_pShipMgr->getMySelfShip()->m_UserID, 0, g_pShipMgr->mTouchPT, false, true);
					}

					onRepeatShootBullet( false );
					m_nKeyDownCount = 0;
					break;
				}
			}
			break;
		}
	case WM_KEYDOWN:
		{
			if (0 < SIX_PopWnd::GetPopWndCount())
				return 0;
			switch (wParam)
			{
			case VK_LEFT:
			case VK_RIGHT:
				{
					if (!g_bInited)
						return 0;

					g_pShipMgr->getMySelfShip()->onWhirlGun(wParam==VK_LEFT ? true : false, true);
					break;
				}
			case VK_UP:
			case VK_SPACE:
				{
					++m_nKeyDownCount;
					// ����1ʱ���䵥���ӵ�����ס���Ż᲻���յ�WM_KEYDOWN��Ϣ
					if (1==m_nKeyDownCount  &&  !m_bRepeatShoot)
					{
						m_ulKeyBoardPushTime = SIX_Utility::GetInstance()->GetTickCount();
						onRepeatShootBullet( true );
					}
					break;
				}
			case VK_DOWN:
				{
					g_pShipMgr->getMySelfShip()->DecBet();
					break;
				}
			}
			break;
		}
	case WM_CHAR:
		{
			switch (wParam)
			{
			case 'Q':
			case 'q':
				{
					// �е���������ʾ��
					if (0 < SIX_PopWnd::GetPopWndCount()  &&  (pSellFish && !pSellFish->IsShow()  ||  NULL==pSellFish))
						return 0;
					ShowSellFishWnd((pSellFish && pSellFish->IsShow())?false:true);
					return 0;
				}
			case 'W':
			case 'w':
				{
					if (0 < SIX_PopWnd::GetPopWndCount()  &&  (pBuyBullet && !pBuyBullet->IsShow()  ||  NULL==pBuyBullet))
						return 0;
					ShowBuyBulletWnd((pBuyBullet && pBuyBullet->IsShow())?false:true);
					return 0;
				}
			case 'E':
			case 'e':
				{
					if (0 < SIX_PopWnd::GetPopWndCount()  &&  (pHelp && !pHelp->IsShow()  ||  NULL==pHelp))
						return 0;
					ShowHelpWnd((pHelp && pHelp->IsShow())?false:true);
					return 0;
				}
			case 'R':
			case 'r':
				{
					if (0 < SIX_PopWnd::GetPopWndCount()  &&  (pSetting && !pSetting->IsShow()  ||  NULL==pSetting))
						return 0;
					ShowSetWnd((pSetting && pSetting->IsShow())?false:true);
					return 0;
				}
			case 'a':
			case 'A': // ���Դ��룬����ʵ�ֺ󣬿�ɾ��
				{
					// �ǳ����Դ���
					//if (0 < SIX_PopWnd::GetPopWndCount())
					//	return 0;
					//int nID = SIX_Utility::GetInstance()->RNDNUM(1,4);//del
					//int nDirection = SIX_Utility::GetInstance()->RNDNUM(0,1);//del
					//pSceneGame->RiseTide(nID, 4.0f, 0.1f, 1==nDirection?true:false);//del

					//// ������������Դ���
					//SIX_MatchEnd *pMatchEnd = SIX_MatchEnd::Create(0, 0, ccc4(0,0,0,0), 674, 447, false, true); //del start
					//pMatchEnd->InitMask(ccc4(0,0,0,128));
					//pMatchEnd->backgroundWithFile("Scene/Game/matchEndBG.png");
					//CMD_MatchEnd ff;
					//for (int i=0; i<4; i++)
					//{
					//	ff.lUserID[i]=i;
					//	sprintf(ff.szName[i], "player %d", i+1);
					//	sprintf(ff.szNickname[i], "player nickname %d", i+1);
					//	ff.iRewardGold[i] = 1111 + i;
					//	ff.lGameCoin[i] = 2222 + i;
					//}
					//pMatchEnd->SetMatchData(&ff);
					//pMatchEnd->SetMyselfID( 2 );
					//pMatchEnd->Show( !pMatchEnd->IsShow() );//del end
				}
			}
			break;
		}
	}
	return 0;
}
#endif

void SIX_SceneGame::ShowConsole()
{
	if (!pConsole)
	{
		pConsole = SIX_Console::Create(112.0,125.0,ccc4(0,0,0,128),800.0,400.0,true);
		pConsole->InitMask(ccc4(0,0,0,128));
	}
	pConsole->ShowConsole(this);
}

void SIX_SceneGame::RefreshScenes(int nScenesID)
{
	//SIXLog("background[0x%08X].objName[%s]",background,background->getObjName());
	//background->setRectDirty(true);

	CCSprite *bgimage = dynamic_cast<CCSprite*>(background->getChildByTag(997));
	if (bgimage)
	{
		//int rnd = SIX_Utility::GetInstance()->RNDNUM(1,5);
		//CCString *rndImage = CCString::createWithFormat("Scene/Game/Scene%02d.jpg",rnd);
		CCString *rndImage = CCString::createWithFormat("Scene/Game/Scene%02d.jpg", nScenesID);
		//SIXLog("rndImage=%s",rndImage->getCString());
		CCTexture2D *tex2D = CCTextureCache::sharedTextureCache()->addImage(rndImage->getCString());
		if (tex2D)
		{
			m_nSceneID = nScenesID;
			bgimage->setTexture(tex2D);
			// ����������С��������С��һ�£���Ҫ���������������С
			// �����������С���Ǿ�����Ĵ�С������
			// Add by Cool.Cat
			CCSize newSize = tex2D->getContentSizeInPixels();
			bgimage->setTextureRect(CCRect(0,0,newSize.width,newSize.height));
		}
	}

	//m_WaveSprite->setVisible(true);

	ReloadLittleThings();
}

void SIX_SceneGame::ReloadLittleThings()
{
	if (g_FishMgr)
	{
		CCSize size = CCEGLView::sharedOpenGLView()->getVisibleSize();
		int offset = 50;
		int count = 0;
		int type = 0;

		// ����
		count = 1;
		type = SIX_Utility::GetInstance()->RNDNUM(0,100)%4+1;
		CCSprite *pShell = CCSprite::spriteWithSpriteFrameName(CCString::createWithFormat("Shell_%d_00000.png",type)->getCString());
		if (pShell)
		{
			// ��������
			pShell->setUserData((void*)type);
			// ��������
			MakeActionForShell(pShell,type);
			// �������
			int x = SIX_Utility::GetInstance()->RNDNUM(offset,size.width-offset);
			int y = SIX_Utility::GetInstance()->RNDNUM(offset,size.height-offset);
			pShell->setPosition(ccp(x,y));
			// �������0.5��1.0
			float scale = SIX_Utility::GetInstance()->RNDNUM(50,100)/100.0;
			pShell->setScale(scale);
			//// �����ת
			//(SIX_Utility::GetInstance()->RNDNUM(0,100)%2==0)?pShell->setFlipX(true):pShell->setFlipY(true);

			CCSpriteBatchNode *pArr = g_FishMgr->sharedShell();
			if (pArr)
			{
				// ���Ƴ���һ�������Ķ���
				pArr->removeAllChildrenWithCleanup(true);
				pArr->addChild(pShell);
			}
		}

		// ����
		CCSpriteBatchNode **pArr = g_FishMgr->sharedStarFish();
		if (pArr)
		{
			for (int i=0;i<ARR_STARFISH_COUNT;i++)
			{
				// ���Ƴ���һ�������Ķ���
				pArr[i]->removeAllChildrenWithCleanup(true);
			}
		}
		count = SIX_Utility::GetInstance()->RNDNUM(1,2);
		for (int i=0;i<count;i++)
		{
			type = SIX_Utility::GetInstance()->RNDNUM(0,100)%3+1;
			CCArray *pArray = CCArray::create();
			for (int j=0;j<15;j++)
			{
				CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%d_%05d.png",type,j)->getCString());
				if (!pSpriteFrame)
					break;
				pArray->addObject(pSpriteFrame);
			}
			CCAnimation *pAnimation =CCAnimation::createWithSpriteFrames(pArray,0.1f);
			CCRepeatForever *pAct = CCRepeatForever::create(CCAnimate::create(pAnimation));
			CCSprite *pStarFish = CCSprite::spriteWithSpriteFrameName(CCString::createWithFormat("%d_00000.png",type)->getCString());
			if (pStarFish)
			{
				pStarFish->runAction(pAct);
				// �������
				int x = SIX_Utility::GetInstance()->RNDNUM(offset,size.width-offset);
				int y = SIX_Utility::GetInstance()->RNDNUM(offset,size.height-offset);
				pStarFish->setPosition(ccp(x,y));
				// �������0.5��1.0
				float scale = SIX_Utility::GetInstance()->RNDNUM(50,100)/100.0;
				pStarFish->setScale(scale);
				// �����ת
				(SIX_Utility::GetInstance()->RNDNUM(0,100)%2==0)?pStarFish->setFlipX(true):pStarFish->setFlipY(true);

				//CCSpriteBatchNode **pArr = g_FishMgr->sharedStarFish();
				//if (pArr)
				//{
					pArr[type-1]->addChild(pStarFish);
				//}
			}
		}

		// ����
		count = SIX_Utility::GetInstance()->RNDNUM(1,2);
		type = SIX_Utility::GetInstance()->RNDNUM(0,100)%4+2;
		CCSprite *pSeaGrass = CCSprite::spriteWithSpriteFrameName(CCString::createWithFormat("seagrass_%d_00000.png",type)->getCString());
		if (pSeaGrass)
		{
			// ��������
			pSeaGrass->setUserData((void*)type);
			// ��������
			CCArray *pArray = CCArray::create();
			for (int j=0;j<15;j++)
			{
				CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("seagrass_%d_%05d.png",type,j)->getCString());
				if (!pSpriteFrame)
					break;
				pArray->addObject(pSpriteFrame);
			}
			CCAnimation *pAnimation =CCAnimation::createWithSpriteFrames(pArray,0.1f);
			CCRepeatForever *pAct = CCRepeatForever::create(CCAnimate::create(pAnimation));
			pSeaGrass->runAction(pAct);
			// �������
			int x = SIX_Utility::GetInstance()->RNDNUM(offset,size.width-offset);
			int y = SIX_Utility::GetInstance()->RNDNUM(offset,size.height-offset);
			pSeaGrass->setPosition(ccp(x,y));
			// �������0.5��1.0
			float scale = SIX_Utility::GetInstance()->RNDNUM(50,100)/100.0;
			pSeaGrass->setScale(scale);
			// �����ת
			(SIX_Utility::GetInstance()->RNDNUM(0,100)%2==0)?pSeaGrass->setFlipX(true):pSeaGrass->setFlipY(true);

			CCSpriteBatchNode *pArr = g_FishMgr->sharedSeaGrass();
			if (pArr)
			{
				// ���Ƴ���һ�������Ķ���
				pArr->removeAllChildrenWithCleanup(true);
				pArr->addChild(pSeaGrass);
			}
		}
	}
}

void SIX_SceneGame::RiseTide(int nScenesID, float fRiseTideTime, float fDelayTime, bool bFromRightToLeft)
{
	m_bNoFire = true;
	SIX_GlobalMgr::GetInstance()->PlayChangeSceneMusic();

	CCSprite *bgimage = dynamic_cast<CCSprite*>(background->getChildByTag(997));
	CCSprite *transitionBG = dynamic_cast<CCSprite*>(background->getChildByTag(999));
	CCSprite *TideSprite = CCSprite::create("Scene/Game/RiseTide.png");
	CCString *rndImage = CCString::createWithFormat("Scene/Game/Scene%02d.jpg", nScenesID);
	CCTexture2D *tex2D = CCTextureCache::sharedTextureCache()->addImage(rndImage->getCString());
	
	if (tex2D)
	{
		transitionBG->setTexture(tex2D);
		CCSize newSize = tex2D->getContentSizeInPixels();
		transitionBG->setTextureRect(CCRect(0,0,newSize.width,newSize.height));
	}

	CCProgressTimer *pTransitionProgressTime = CCProgressTimer::create(transitionBG);
	bgimage->addChild( pTransitionProgressTime );
	pTransitionProgressTime->setType(kCCProgressTimerTypeBar);
	pTransitionProgressTime->setMidpoint(ccp(bFromRightToLeft?1:0, 0));
	pTransitionProgressTime->setBarChangeRate(ccp(1, 0));
	pTransitionProgressTime->setUserData(bgimage);
	pTransitionProgressTime->setAnchorPoint(CCPoint(0,0));	
	pTransitionProgressTime->addChild( TideSprite );
	pTransitionProgressTime->setTag(990);
	
	// ������
	CCSize szSelf = TideSprite->getContentSize();
	CCSize szWin = CCDirector::sharedDirector()->getWinSize();
	float fStartX = szWin.width, fAnimationEndX = -szSelf.width, fSpeed = szWin.width/fRiseTideTime, fOnlyTideMoveDistance = -szSelf.width;
	float fOnlyTideMoveTime = szSelf.width/fSpeed; // ������Լ��ƶ�ʱ��
	if ( !bFromRightToLeft )
	{
		fStartX = -szSelf.width;
		fAnimationEndX = szWin.width;
		fOnlyTideMoveDistance = szSelf.width;
		TideSprite->setFlipX( true );
	}

	// Ϊ�˴ﵽͬ�����ȼ����ٶȣ����˱�������ȴ��˳����˳��Ǳ������ӽ�㣬�����������ñ��������ع��˱�����
	CCMoveTo *pTideMove = CCMoveTo::create(fRiseTideTime+fOnlyTideMoveTime, CCPoint(fAnimationEndX, 0.0));
	CCDelayTime *pTransitionDelayTime = CCDelayTime::create(fDelayTime);
	TideSprite->setAnchorPoint(ccp(0,0));
	TideSprite->setPositionX(fStartX);
	TideSprite->runAction(CCSequence::create((CCDelayTime *)pTransitionDelayTime->copy()->autorelease(), pTideMove, NULL));

	// ������������
	CCDelayTime *pWaitTideMove = CCDelayTime::create(fOnlyTideMoveTime);
	CCProgressTo *pTransitionProgressTo = CCProgressTo::create(fRiseTideTime, 100);
	//int *pScenesID = new int(nScenesID);
	m_nSceneID = nScenesID;
	//CCCallFuncND *pCallFunc = CCCallFuncND::create(pTransitionProgressTime, callfuncND_selector(SIX_SceneGame::TransitionBGCallFun), (void *)pScenesID);
	CCCallFuncN *pCallFunc = CCCallFuncN::create(this, callfuncN_selector(SIX_SceneGame::TransitionBGCallFun));
	CCFiniteTimeAction *pFiniteTime = CCSequence::create(pTransitionDelayTime, pTransitionProgressTo, pWaitTideMove, pCallFunc, NULL);
	pTransitionProgressTime->runAction( pFiniteTime );

	// �ǳ���Ч
	// Cool.Cat
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(22,false);
}

void SIX_SceneGame::SetMatchCountdown(int nTime)
{
	CCSprite *pDountdownBG = dynamic_cast<CCSprite *>(background->getChildByTag(200));
	if (NULL != pDountdownBG)
	{
		SIX_NumberBatchNode *pMinute = dynamic_cast<SIX_NumberBatchNode *>(pDountdownBG->getChildByTag(1));
		SIX_NumberBatchNode *pSecond = dynamic_cast<SIX_NumberBatchNode *>(pDountdownBG->getChildByTag(3));
		if (NULL != pMinute  &&  NULL != pSecond)
		{
			int nMinute = nTime/60;
			int nSeconde = nTime%60;
			// Ĭ����ʾ���֣��롿���������99���ӣ��ĳɡ�ʱ���֡�
			if (99 < nMinute)
			{
				nMinute = nTime/60/60;
				nSeconde = nTime/60%60;
			}
			pMinute->setNumber(nMinute);
			pSecond->setNumber(nSeconde);
		}
	}
}

void SIX_SceneGame::MakeActionForShell(CCSprite *pShell,int type)
{
	if (!pShell)
		return;

	CCArray *pArrayOpen = CCArray::create();
	CCArray *pArrayClose = CCArray::create();
	CCSpriteFrame *pFirstFrame = 0;
	// ǰ7֡��
	for (int i=0;i<7;i++)
	{
		CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Shell_%d_%05d.png",type,i)->getCString());
		if (!pSpriteFrame)
			break;
		pArrayOpen->addObject(pSpriteFrame);
		if (i==0)
			pFirstFrame = pSpriteFrame;
	}
	// ��3֡�ر�
	for (int i=7;i<10;i++)
	{
		CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("Shell_%d_%05d.png",type,i)->getCString());
		if (!pSpriteFrame)
			break;
		pArrayClose->addObject(pSpriteFrame);
	}
	// �رյ����һ֡���ڴ򿪵ĵ�һ֡
	pArrayClose->addObject(pFirstFrame);
	// ����(Ч�������ٴ򿪣����ٹر�)
	CCAnimation *pAnimationOpen =CCAnimation::createWithSpriteFrames(pArrayOpen,0.1f);
	CCAnimation *pAnimationClose =CCAnimation::createWithSpriteFrames(pArrayClose,0.05f);
	CCDelayTime *pTimeOpen = CCDelayTime::create(SIX_Utility::GetInstance()->RNDNUM(200,300)/100.0);
	CCDelayTime *pTimeClose = CCDelayTime::create(SIX_Utility::GetInstance()->RNDNUM(300,900)/10.0);
	CCCallFuncN *pCallfunN = CCCallFuncN::create(pShell,callfuncN_selector(SIX_SceneGame::DoShellLoop));
	CCFiniteTimeAction *pAct = CCSequence::create(CCAnimate::create(pAnimationOpen),pTimeOpen,CCAnimate::create(pAnimationClose),pTimeClose,pCallfunN,0);
	pShell->runAction(pAct);
}

void SIX_SceneGame::DoShellLoop(CCNode *pNode)
{
	CCSprite *pShell = dynamic_cast<CCSprite*>(pNode);
	if (!pShell)
		return;

	// ��������
	int type = (int)pShell->getUserData();

	MakeActionForShell(pShell,type);
}

void SIX_SceneGame::doEvents(CCObject* pSender, CCControlEvent event)
{
	if (!pSender)
		return;

	CCControl *pControl = dynamic_cast<CCControl*>(pSender);
	if (!pControl)
		return;

	CCString *name = CCString::create(pControl->getObjName());
	int tag = pControl->getTag();
	SIXLog("SIX_SceneGame.doEvents.pSender[0x%08X][%s].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,name->getCString(),event,tag);

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			// ������񴰿�
			if (!name->compareIgnoreCase("Settlement"))
			{
				ShowSellFishWnd((pSellFish && pSellFish->IsShow())?false:true);
				break;
			}

			// �����ӵ�����
			if (!name->compareIgnoreCase("Bullet"))
			{
				ShowBuyBulletWnd((pBuyBullet && pBuyBullet->IsShow())?false:true);
				break;
			}

			// ��������
			if (!name->compareIgnoreCase("Help"))
			{
				ShowHelpWnd((pHelp && pHelp->IsShow())?false:true);
				break;
			}

			// ���ô���
			if (!name->compareIgnoreCase("Setting"))
			{
				ShowSetWnd((pSetting && pSetting->IsShow())?false:true);
				break;
			}
		}
	}
}

void SIX_SceneGame::update(float dt)
{
	if (SIX_Proxy::GetInstance()->IsChangeScene())
	{
		SIX_Proxy::GetInstance()->SetChangeScene(false);

		// �л����ؿ�����
		LAST_SCENE_IDX = SCENE_IDX_GAME;
		
		if (!pSceneGate)
		{
			pSceneGate = SIX_SceneGate::scene();
			if (!pSceneGate)
			{
				//CCMessageBox("��������ʧ�ܣ�",0);
				return;
			}
		}
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2f,pSceneGate->GetScene(),ccc3(255, 255, 255)));
		return;
	}
	FishAndBulletCollide();

	//SIX_Lock lock(g_pBulletMgr->mutex);
	//{
	//	for (BULLET_MAP::iterator mItBullet = g_pBulletMgr->mMyBullet.begin();mItBullet!=g_pBulletMgr->mMyBullet.end();)
	//	{
	//		CBulletAndNet *pBullet = (CBulletAndNet*)mItBullet->second;
	//		// ɾ������pBullet->Data.RemoveStatusΪ2���ӵ�����(UI)
	//		if (pBullet && pBullet->Data.RemoveStatus==2)
	//		{
	//			g_pBulletMgr->mMyBullet.erase(mItBullet++);
	//			pBullet->DelBulletWithResource();
	//		}
	//		else
	//			mItBullet++;
	//	}
	//}

	ResetGrid();
	CheckHBoxLoadStatus();
	RandomBubble();
}

// �����������
// Cool.Cat
void SIX_SceneGame::RandomBubble()
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (pScene && !STRCMP(pScene->getChildren()->objectAtIndex(0)->getObjName(),"SIX_SceneGame"))
	{
		int rnd = SIX_Utility::GetInstance()->RNDNUM(1000,5000);
		unsigned long long tick = SIX_Utility::GetInstance()->GetTickCount();
		if (tick - m_uLastTick<(unsigned int)rnd)
			return;

		m_uLastTick = tick;

		CCParticleSystemQuad* part = CCParticleSystemQuad::create("Scene/Game/Particle/Bubble.plist");
		if(!part)
			return;

		// ����
		CCSize size = CCEGLView::sharedOpenGLView()->getVisibleSize();
		int offset = 100;
		float x = SIX_Utility::GetInstance()->RNDNUM(offset,size.width-offset);
		float y = SIX_Utility::GetInstance()->RNDNUM(offset,size.height-offset);
		part->setPosition(ccp(x,y));
		// ��ת
		float rota = (float)(SIX_Utility::GetInstance()->RNDNUM(0,360));
		part->setRotation(rota);
		// �Ƕȱ仯
		float angle = (float)(SIX_Utility::GetInstance()->RNDNUM(part->getAngleVar(),part->getAngleVar()+20));
		part->setAngleVar(angle);
		//// ����
		//unsigned int count = (unsigned int)(SIX_Utility::GetInstance()->RNDNUM(part->getTotalParticles(),part->getTotalParticles()+20));
		////unsigned int count = part->getTotalParticles();
		//part->setTotalParticles(count);
		//SIXLog("part.pos[%.2f/%.2f].count[%u].rota[%.2f].angle[%.2f]",x,y,count,rota,angle);
		part->setBlendAdditive(true);
		part->setAutoRemoveOnFinish(true);
		pScene->addChild(part);
	}
}

void SIX_SceneGame::UpdateResProgress(int value)
{
	if (!m_ResProgress || !m_ResProgress->isVisible())
		return;

	CCProgressTimer *pProgress = dynamic_cast<CCProgressTimer*>(m_ResProgress->getChildByTag(1));
	if (!pProgress)
		return;

	float v = value*100.0/res_total;
	if (v>=100.0)
		v = 100.0;
	pProgress->setPercentage(v);

	// ���
	CCSprite *curSpr = dynamic_cast<CCSprite*>(m_ResProgress->getChildByTag(2));
	if (!curSpr)
		return;

	CCPoint m_tBarChangeRate = pProgress->getBarChangeRate();
	CCPoint m_tMidpoint = pProgress->getMidpoint();
	float offset_x = convertPercentageToMaxPostionX(v,m_tBarChangeRate,m_tMidpoint) * 100;
	float offset_x_final = offset_x * pProgress->getContentSize().width / 100;

	// -- �ڷǹ�������Ҫ����
	if (offset_x_final<22.0)
	{
		curSpr->setScale(offset_x_final * (1/22));
	}
	else if (offset_x_final>596.0)
	{
		curSpr->setScale((22-(offset_x_final-596)) * (1/22));
	}
	// -- �ڹ�������ԭ
	else
	{
		curSpr->setScale(1.0);
	}
	curSpr->setPositionX(offset_x_final+pProgress->getPositionX());
}

//-- �ο�updateBar
//-- ������m_tBarChangeRate.x=1 && m_tMidpoint.x=0 ʱ��m_fPercentage������ʵ�Ĳ���ֵ����ʱ���Լ򻯵õ�m_fPercentage=getPercentage()
//-- ������Ҫ���ô˺�������һ�¡�����
//-- Ŀǰֻ�����˺��򲽽�ֵ�������������ʾ��ʽ�Ľ����������иı䷵��ֵ
//-- Cool.Cat@2013/4/9 14:00:18
float SIX_SceneGame::convertPercentageToMaxPostionX(float m_fPercentage,CCPoint m_tBarChangeRate,CCPoint m_tMidpoint)
{
	float alpha = m_fPercentage / 100.0;
	CCPoint alphaOffset = ccpMult(ccp(1.0 * (1.0 - m_tBarChangeRate.x) + alpha * m_tBarChangeRate.x, 1.0 * (1.0 - m_tBarChangeRate.y) + alpha * m_tBarChangeRate.y), 0.5);
	CCPoint min = ccpSub(m_tMidpoint, alphaOffset);
	CCPoint max = ccpAdd(m_tMidpoint, alphaOffset);

	if (min.x < 0)
	{
		max.x = max.x - min.x;
		min.x = 0;
	}

	if (max.x > 1)
	{
		min.x = min.x - (max.x - 1);
		max.x = 1;
	}

	if (min.y < 0)
	{
		max.y = max.y - min.y;
		min.y = 0;
	}

	if (max.y > 1)
	{
		min.y = min.y - (max.y - 1);
		max.y = 1;
	}
  
	// --CCLuaLog("min="..min.x.."/"..min.y.." , max="..max.x.."/"..max.y)
	return max.x;
}

void SIX_SceneGame::TransitionBGCallFun(CCNode* pSender)
{
	//int ScenesID = *((int *)data);
	//SAFE_DELETE(data);

	CCProgressTimer *pTransitionProgressTime = (CCProgressTimer *)pSender;
	CCSprite *bgimage = (CCSprite *)pTransitionProgressTime->getUserData();
	if (bgimage)
	{
		CCString *rndImage = CCString::createWithFormat("Scene/Game/Scene%02d.jpg", m_nSceneID);
		//SIXLog("rndImage=%s",rndImage->getCString());
		CCTexture2D *tex2D = CCTextureCache::sharedTextureCache()->addImage(rndImage->getCString());
		if (tex2D)
		{
			bgimage->setTexture(tex2D);
			// ����������С��������С��һ�£���Ҫ���������������С
			// �����������С���Ǿ�����Ĵ�С������
			// Add by Cool.Cat
			CCSize newSize = tex2D->getContentSizeInPixels();
			bgimage->setTextureRect(CCRect(0,0,newSize.width,newSize.height));
		}
	}
	pTransitionProgressTime->setVisible(false);
	
	this->ReloadLittleThings();
	this->m_bNoFire = false;
	SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();
}

void SIX_SceneGame::CheckHBoxLoadStatus()
{
	if (g_FishMgr->m_LoadHBoxProgress>=0 && g_FishMgr->m_LoadHBoxProgress<hbox_total)
	{
		if (!g_bInited)
			UpdateResProgress(l_LoadImageCountTotal+g_FishMgr->m_LoadHBoxProgress);
	}
	else if (g_FishMgr->m_LoadHBoxProgress==hbox_total)
	{
		UpdateResProgress(res_total);
		m_ResProgress->setVisible(false);
		g_FishMgr->m_LoadHBoxProgress = -1;
		SIXLog("TID[0x%08X].LoadHitBox.Inited",SIX_Utility::GetInstance()->GetCurrentThreadId());
		SIX_Utility::GetInstance()->AddHitBox();
		
		// �ӳٴ���
		// Cool.Cat
		SIX_Utility::GetInstance()->performWithDelay(this,callfunc_selector(SIX_SceneGame::DelayDoInit),0.1f);
	}
}

void SIX_SceneGame::SetSysTip(const char *szSysTip)
{
	if (!m_pSysTip)
		return;
	m_pSysTip->setString( SIX_Utility::GetInstance()->G2U(szSysTip).c_str() );
	SIX_Utility::GetInstance()->FixedTexParameters(m_pSysTip->getTexture());
}

CCObject* SIX_SceneGame::getChildByObjName(const char *name)
{
	CCControl *pCtl=pExpandLayer->GetAnimate();
	if(pCtl==NULL)
		return NULL;

	CCAssert( name != NULL, "Invalid name");
	CCString *cname = CCString::create(name);

	if(pCtl->getChildren() && pCtl->getChildren()->count() > 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(pCtl->getChildren(), child)
		{
			CCNode* pNode = (CCNode*)child;
			if(pNode && !cname->compareIgnoreCase(pNode->getObjName()))
				return pNode;
		}
	}

	return NULL;
}

void SIX_SceneGame::DelayDoInit()
{
	//// ����(etc:�����б�)
	//pExpandLayer = SIX_ExpandLayer::Create(100,300,ccc4(0,0,0,128),200,200,-200,false,false,true,true,true);
	//// ����(etc:���ð�ť)
	pExpandLayer = SIX_ExpandLayer::Create(MAX_WIDTH-65,MAX_HEIGHT-65,ccc4(0,0,0,0),70,268,-216,false,false,false,false,true);
	if (pExpandLayer)
	{
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("Common/Button/expand.png");
		CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTexture,CCRect(65,0,65,52));
		CCScale9Sprite *pBtnOn = CCScale9Sprite::createWithSpriteFrame(pFrame);
		pFrame = CCSpriteFrame::createWithTexture(pTexture,CCRect(0,0,65,52));
		CCScale9Sprite *pBtnOff = CCScale9Sprite::createWithSpriteFrame(pFrame);
		pExpandLayer->setExpandButtonSprite(pBtnOn,pBtnOff,CCSize(65,52));
		//pExpandLayer->buttonExpandWithFileCell("Common/Button/expand.png",2);
		pExpandLayer->GetBtnExpand()->setPosition(ccp(3,0));

		// �����ؼ�
		float width = pExpandLayer->GetBtnExpand()->getContentSize().width;
		//float height = pExpandLayer->GetBtnExpand()->getContentSize().height*4;
		float height = 54*4;
		pExpandLayer->AnimateInit(width,height);

		//// ����
		//CCScale9Sprite *pSpr = CCScale9Sprite::create("Common/Button/bg.png");
		//pSpr->setPreferredSize(CCSize(pExpandLayer->GetBtnExpand()->getPreferredSize().width,200));
		//pSpr->ignoreAnchorPointForPosition(true);
		//pExpandLayer->GetAnimate()->addChild(pSpr);

		// ����
		CCControlButton *pbtnSetting = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Button/setting.png",3);
		pbtnSetting->setObjName("Setting");
		pbtnSetting->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_SceneGame::doEvents),32);
		pExpandLayer->GetAnimate()->addChild(pbtnSetting);

		// ����
		CCControlButton *pBtnHelp = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Button/help.png",3);
		pBtnHelp->setPositionY(pbtnSetting->getPositionY()+pbtnSetting->getPreferredSize().height);
		pBtnHelp->setObjName("Help");
		pBtnHelp->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_SceneGame::doEvents),32);
		pExpandLayer->GetAnimate()->addChild(pBtnHelp);

		// �ӵ�
		CCControlButton *pBtnBullet = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Button/bullet.png",3);
		pBtnBullet->setPositionY(pBtnHelp->getPositionY()+pBtnHelp->getPreferredSize().height);
		pBtnBullet->setObjName("Bullet");
		pBtnBullet->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_SceneGame::doEvents),32);
		pExpandLayer->GetAnimate()->addChild(pBtnBullet);

		// ����
		CCControlButton *pBtnSettlement = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Button/settlement.png",3);
		pBtnSettlement->setPositionY(pBtnBullet->getPositionY()+pBtnBullet->getPreferredSize().height);
		pBtnSettlement->setObjName("Settlement");
		pBtnSettlement->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_SceneGame::doEvents),32);
		pExpandLayer->GetAnimate()->addChild(pBtnSettlement);

		pExpandLayer->resetZOrder();
		this->addChild(pExpandLayer);
	}

	// ��ҹ���
	g_pGold->Init( background );

	//vector<PLAYER_LIST*>::const_iterator it = g_pShipMgr->mPlayerList.begin();
	//for (; it != g_pShipMgr->mPlayerList.end(); ++it )
	//{
	//	PLAYER_LIST * pPlayer = *it;
	//	if ( pPlayer->iTableId == g_pShipMgr->mMyTableID && pPlayer->SeatId != g_pShipMgr->mMySeatId && pPlayer->UserIdx != SIX_PlayerMgr::GetInstance()->getMyUserIdx())
	//	{
	//		g_pShipMgr->Enter(background, pPlayer->UserIdx, pPlayer->SeatId, false);
	//	}
	//}

	SIX_PlayerMgr::GetInstance()->Enter(background);

	CCLayer *pBottomButton = dynamic_cast<CCLayer*>(getChildByTag(1));
	if (NULL != pBottomButton)
	{
		pBottomButton->setVisible(true);
	//	CCWaves *pWave = CCWaves::create(4, 20, true, true, ccg(1024,32), 1.5f);
	//	pBottomButton->runAction( pWave );
	//	CCMoveBy *pMove = CCMoveBy::create(1.5, CCPoint(0, -32));
	//	CCCallFuncN *pCall=CCCallFuncN::create(pBottomButton , callfuncN_selector(SIX_SceneGame::ClickUpDown) );
	//	UpDownUserData *pUserData = new UpDownUserData;
	//	pUserData->bComplete = false;
	//	pBottomButton->setUserData( pUserData );
	//	pBottomButton->runAction( CCSequence::create(pMove, pCall, NULL));
	}

	//ShowPopWndLoading(false);
	this->SetInited(true);
	g_pShipMgr->getMySelfShip()->setVisible( true );
	//add by Ivan_han 20130530
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_RAISE_HAND);
	//SIX_ClientRoom::GetInstance()->SetRaiseHandTime(SIX_ClientRoom::GetTickCount64());
	SIX_ClientRoom::GetInstance()->SetRaiseHandTime(SIX_Utility::GetInstance()->GetTickCount());
	//add by Ivan_han 20130724
	// �������䲻��Ҫ���������ӵ�
	if (m_UIManager  &&  3!=PlayerTreasureInfo::Instance().m_lGameType)
	{
		CCObject *pBtn=getChildByObjName("Bullet");
		if(pBtn)
		{
			m_UIManager->doEvents(pBtn,CCControlEventTouchUpInside);
		}
	}

	// ��������ʱ
	if (3==PlayerTreasureInfo::Instance().m_lGameType)
	{
		CCSprite *pDountdownBG = dynamic_cast<CCSprite *>(background->getChildByTag(200));
		pDountdownBG->setVisible(true);
	}
}

void SIX_SceneGame::AddImageAsyncCallBack(CCObject *pObject)
{
	CCTexture2D *pTexture = dynamic_cast<CCTexture2D*>(pObject);

	//SIXLog("SIX_SceneGame.AddImageAsyncCallBack.pObject[0x%08X].pTexture[0x%08X]",pObject,pTexture);

	if (pTexture)
	{
		CCString *pngPath = CCTextureCache::sharedTextureCache()->GetFileNameByTexture(pTexture);
		//SIXLog("SIX_SceneGame.AddImageAsyncCallBack.plist[%s]",pngPath->getCString());

		// png->plist
		string str(pngPath->getCString());
		// tolower/toupper��unix��Ϊ�궨�������vc�µĺ��������Ա���ʹ��::
		// ����gcc�±���ͨ�����ˡ�����
		// Cool.Cat
		std::transform(str.begin(),str.end(),str.begin(),::tolower);
		SIX_Utility::GetInstance()->replace(str,".png",".plist");
		CCString *plist = CCString::createWithFormat("%s",str.c_str());

		CCDictionary *dict = CCDictionary::createWithContentsOfFile(plist->getCString());
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithDictionary(dict,pTexture);
		CCSpriteFrameCache::sharedSpriteFrameCache()->insertPlist(plist->getCString());
		dict->release();

		l_LoadImageCount++;
		//SIXLog("[0x%08X]SIX_SceneGame.AddImageAsyncCallBack.l_LoadImageCount[%d].l_LoadImageCountTotal[%d]",
		//	SIX_Utility::GetInstance()->GetCurrentThreadId(),l_LoadImageCount,l_LoadImageCountTotal);

		//// -- ���½�����
		//if (pPopWnd~=nil)
		//	pPopWnd:updateProgress((l_LoadImageCount/l_LoadImageCountTotal)*100.0);

		UpdateResProgress(l_LoadImageCount);

		// -- �����Ƿ�ȫ���������
		if (l_LoadImageCount == l_LoadImageCountTotal)
		{
			SIXLog("SIX_SceneGame.AddImageAsyncCallBack.Done");

			//  ���
			g_pShipMgr->Enter(background, SIX_PlayerMgr::GetInstance()->getMyUserIdx(), SIX_PlayerMgr::GetInstance()->getMySeatIdx(), true);
			g_pShipMgr->getMySelfShip()->setVisible( false );
			g_pShipMgr->getMySelfShip()->ShowHereTips();

			// ��ʵ������ʼ��
			g_FishMgr->Init(this,background->getChildByTag(997));
			SIXLog("SIX_SceneGame.CFishMgr.Inited");

			// �ӵ������ʼ��
			g_pBulletMgr->Init(background);
			SIXLog("SIX_SceneGame.CBulletAndNetMgr.Inited");

			g_FishMgr->LoadHitBox();
		}
	}
}

typedef struct tagPPOINT_Info{
	FPOINT *pPoint;
	int nCount;
}PPOINT_INFO;

void SIX_SceneGame::FishAndBulletCollide()
{
	// û���ӵ��Ļ�������֮~
	if (!g_pBulletMgr || !g_pBulletMgr->mMyBullet.size())
		return;

	// û����Ļ�������֮~
	if (!g_FishMgr || !g_FishMgr->mFishData.size())
		return;

	// �ӵ�
	CBulletAndNet *pBullet = 0;
	bool bHaveCatchingFish = false;
	vector<unsigned int> vFishID;

	FISH_MAP mFishData;
	//SIX_Lock lock(g_FishMgr->mutex);
	//{
		std::copy(g_FishMgr->mFishData.begin(),g_FishMgr->mFishData.end(),std::inserter(mFishData,mFishData.begin()));
	//}

	// �ӵ�����֡BBox/HBox��ײ���
	SIX_Utility::GetInstance()->TimerStart();
	//SIX_Lock(g_pBulletMgr->mutex);
	//{
		BULLET_MAP::iterator mItBullet = g_pBulletMgr->mMyBullet.begin();
		for (; mItBullet != g_pBulletMgr->mMyBullet.end(); mItBullet++)
		{
			pBullet = (CBulletAndNet * )mItBullet->second;

			if (!pBullet)
				continue;

			if (pBullet->Data.IsCatching || !pBullet->isVisible())
				continue;

			int flag = (int)(pBullet->getUserData());
			if (flag==1)
				continue;

			bHaveCatchingFish = false;

			// ���BBox���ӵ��Ƿ�����ײ
			if (pBullet->Data.RemoveStatus==0 && pBullet->Data.iReflectionCount<=pBullet->Data.iReflectionMax && pBullet->Data.iReflectionMax>0)
			{
				// ��ǰ�ӵ�����
				FPOINT fp = FPOINT(pBullet->getPositionX(),pBullet->getPositionY());

				// ������ǰ�㾫��
				FISH_MAP::iterator fishIter = mFishData.begin();
				for (; fishIter!=mFishData.end(); fishIter++)
				{
					CFish *pFish = fishIter->first;
					if (!pFish->isVisible())
						continue;

					FISH_DATA * pData = fishIter->second;
					if (pData->isCatch)
						continue;

					// ģ����ײ��⣺�ȼ����ӵ������Ƿ�����ĸ���
					//CCPoint fishAR = pFish->getAnchorPoint();
					CCSize fishSize = pFish->getContentSize();
					// �뾶����󳤿����
					float radius = fishSize.height/2;
					if (fishSize.width>fishSize.height)
						radius = fishSize.width/2;
					// ��Χ�Ŵ�һ�㣬������ȷ~
					radius *= 1.5;
					CCPoint fishPos = pFish->getPosition();
					float minX = fishPos.x-radius;
					float minY = fishPos.y-radius;
					float maxX = fishPos.x+radius;
					float maxY = fishPos.y+radius;
					// ��Ļ��ߣ�
					if (maxX<=0 && maxY<=0)
						continue;
					if (fp.x>=minX && fp.x<=maxX && fp.y>=minY && fp.y<=maxY)
					{
						bool NeedCalcHBox = false;
						// ��ϸ��ײ��⣺�ټ����ӵ������Ƿ������BBox/HBox�ڲ�
						// ȡ��ǰ��֡
						CCSpriteFrame *pFrame = pFish->mDisplayFrame;
						if (!pFrame)
							NeedCalcHBox = true;
						else
						{
							if (pFrame->vertexCount==0)
								NeedCalcHBox = true;
							// ���������ײ���㣬�����HBox
							else if (pFrame->vertexCount>0)
							{
								// ���㾫��֡�ڵ�ǰʱ�̵�HBox
								pFish->CalcHitBox(pFrame->verticesBuffer,pFrame->verticesBufferCopy);

								FPOINT *pPoint = new FPOINT[pFrame->vertexCount];
								for (int i=0;i<pFrame->vertexCount;i++)
								{
									POINT_INFO point = pFrame->verticesBufferCopy[i];
									pPoint[i] = FPOINT(point.x,point.y);
								}
								// ����ӵ���������֡HBox������
								if (InsidePolygon(pFrame->vertexCount,pPoint,fp))
								{
									vFishID.push_back(pData->uld);
									bHaveCatchingFish = true;
									if (m_NeedDrawBox)
										pFish->setHBoxDirty();
								}
								delete [] pPoint;
								pPoint = 0;
							}
						}

						// ����BBox����
						if (NeedCalcHBox)
						{
							CCRect bboxRc = pFish->boundingBox();
							if (bboxRc.containsPoint(ccp(fp.x,fp.y)))
							{
								vFishID.push_back(pData->uld);
								bHaveCatchingFish = true;
								if (m_NeedDrawBox)
									pFish->setBBoxDirty();
							}
						}
					}
				}

				// ����ײ����
				if (bHaveCatchingFish)
				{
					// ��������/�ӵ��Ƴ�
					pBullet->setUserData((void*)1);
					pBullet->FinishAnimation(pBullet);

					// ������������
					CAPTURE_FISH Capture;
					Capture.llUserID = pBullet->Data.UserID;
					Capture.llBulletID = pBullet->Data.BulletId;
					int size = vFishID.size();
					Capture.nFishCount=min(size,12);
					for(unsigned int i=0;i<Capture.nFishCount;i++)
						Capture.FishIDs[i]=vFishID[i];
					SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_CAPTURE_FISH, &Capture, Capture.getLength());
				}
			}
		}
	//}   
	// �ӵ��߽���ײ���
	CBulletAndNetMgr::GetInstance()->UpdateBullet();
}

void SIX_SceneGame::ClickUpDown(CCNode *pNode)
{
	CCLayer *pLayer = dynamic_cast<CCLayer *>(pNode);
	if (NULL == pLayer)
		return;

	UpDownUserData *pUserData = static_cast<UpDownUserData *>(pLayer->getUserData());
	pUserData->bComplete = true;

	if (NULL==pUserData  ||  0>=strlen(pUserData->cType)  ||  0 == STRCMP(pUserData->cType, "down"))
	{
		sprintf(pUserData->cType, "up");
	}
	else
	{
		sprintf(pUserData->cType, "down");
	}
	//pLayer->setGrid(NULL);
}

void SIX_SceneGame::OnUpDownEffect(CCPoint pt)
{
	if (!g_bInited)
		return;

	CCLayer *pBottomButton = dynamic_cast<CCLayer*>(getChildByTag(1));
	if (NULL == pBottomButton)
		return;

	UpDownUserData *pcData = static_cast<UpDownUserData *>(pBottomButton->getUserData());
	if (NULL==pcData  || 0>=strlen(pcData->cType))
		return;

	if ( !pcData->bComplete )
	{
		return;
	}

	if (10 <= pt.y  &&  0 == STRCMP(pcData->cType, "up"))
		return;
	else if (32 > pt.y  &&  0 == STRCMP(pcData->cType, "down"))
		return;

	int nMove = (0 == STRCMP(pcData->cType, "up")) ? 32 : -32;
	pcData->bComplete = false;
	//CCWaves *pWave = CCWaves::create(4, 20, true, true, ccg(1024,32), 1.5f);
	//pLayer->runAction( pWave );
	CCMoveBy *pMove = CCMoveBy::create(1.5, CCPoint(0, nMove));
	CCCallFuncN *pCall=CCCallFuncN::create(pBottomButton , callfuncN_selector(SIX_SceneGame::ClickUpDown) );
	CCAction *pAction = CCSequence::create(pMove, pCall, NULL);
	pBottomButton->runAction( pAction );
}

void SIX_SceneGame::onRepeatShootBullet(bool IsShoot)
{
	if (!pSceneGame || !pSceneGame->getChildren() || !g_pShipMgr->getMySelfShip())
		return;

	CCLayerColor *bg = dynamic_cast<CCLayerColor*>(pSceneGame->getChildren()->objectAtIndex(0));
	if (!bg)
		return;
	if (m_bRepeatShoot == IsShoot  &&  true == m_bRepeatShoot)
		return;

	if ( IsShoot )
	{
		// �ǳ���ֹ����
		if (pSceneGame && pSceneGame->IsNoFire())
			return;
		schedule( schedule_selector(SIX_SceneGame::onWaitRepeatShootBullet), 1.0*BULLET_REPEATSHOOT_DELAY/1000);
	}
	else
	{
		unschedule( schedule_selector(SIX_SceneGame::onWaitRepeatShootBullet) );
		unsigned long long ulCutTime = SIX_Utility::GetInstance()->GetTickCount();
		// ΪʲôҪ������жϣ�������ǲ������߶�ʮһ��ȥֹͣ�ڹܶ��������Ӱ�췢�����ӵ����˺��� stopAllActions ��ֹͣ���ж���
		// �������������ӵ��ȴ�ʱ��(fDelay)��ô����ڹܶ�������Чʱ��
		// ��Ϊ���䵥���ڹܶ���û��ִ���꣬��ÿ���ɿ�����밴ť��������ر����������ʱ��
		// unschedule( schedule_selector(SIX_SceneGame::onWaitRepeatShootBullet) );
		if ( m_bRepeatShoot )
		{
			g_pShipMgr->getMySelfShip()->m_gunSprite->stopAllActions();
			CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( \
				CCString::createWithFormat("gun_%d_00000.png", g_pShipMgr->getMySelfShip()->GetGunType())->getCString() );
			g_pShipMgr->getMySelfShip()->m_gunSprite->setDisplayFrame( SpriteFrame );
			bg->stopAllActions();
		}
		m_bRepeatShoot = false;
	}
}

// -- �����ӵ�����ص�
void SIX_SceneGame::onWaitRepeatShootBullet(float dt)
{
	unschedule( schedule_selector(SIX_SceneGame::onWaitRepeatShootBullet) );

	m_bRepeatShoot = true;
	CCLayerColor *bg = dynamic_cast<CCLayerColor*>(pSceneGame->getChildren()->objectAtIndex(0));
	SIX_Utility::schedule(bg, callfunc_selector(CShip::onCallFucRepeatShootBullet), BULLET_SHOOT_DELAY/1000.0f);
}

void SIX_SceneGame::ResetGrid()
{
	CCScene *pScene = pSceneGame->GetScene();
    if (pScene->numberOfRunningActions()==0 && pScene->getGrid()!=0)
        pScene->setGrid(0);
}

// ��ʱ�䲻�����ӵ�������ʱ
void SIX_SceneGame::ShowCountDown(int delay)
{
	if (delay<=0)
		return;

	CCSize size = CCEGLView::sharedOpenGLView()->getVisibleSize();

	pCountDown = SIX_CountDown::Create("Common/Tips/bg.png","Common/Tips/msg.png","Common/Tips/num.png",10,-3.0f,2,delay,ccp(426.0f,0.0f));
	if (pCountDown)
	{
		pCountDown->SetCallFunc(callfunc_selector(SIX_SceneGame::WriteScoreAndExit));
		pCountDown->ignoreAnchorPointForPosition(true);
		pCountDown->setPosition(ccp((size.width-pCountDown->getPreferredSize().width)/2,(size.height-pCountDown->getPreferredSize().height)/2));
		this->addChild(pCountDown);
	}
}

void SIX_SceneGame::RemoveCountDownAndTips()
{
	g_pShipMgr->getMySelfShip()->ShowHereTips(false);

	CC_SAFE_DELETE(pCountDown);
}

void SIX_SceneGame::WriteScoreAndExit()
{
	SIXLog("SIX_SceneGame.WriteScoreAndExit");

	// �ȸ�����־λ�����յ�д����ɵ����ݰ������л�������
	// Cool.Cat
	//pSceneGame->SetInited(false);
	pSceneGame->SetWaitForChangeScene(true);

	this->WriteScore();	
}

void SIX_SceneGame::WriteScore()
{
	// ��������жϣ��л����ؿ�����
	// Cool.Cat
	if (!SIX_ClientRoom::GetInstance()->getReconnect() && !SIX_ClientRoom::GetInstance()->getConnected())
		SIX_Proxy::GetInstance()->SetChangeScene(true);
	else
		SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_WRITE_SCORE);
}

void SIX_SceneGame::ShowSellFishWnd(bool bShow)
{
	if (!pSellFish)
	{
		pSellFish = SIX_PopWndSellFish::Create(0.0,0.0,ccc4(0,0,0,0),627,552,false);
		pSellFish->InitMask(ccc4(0,0,0,128));
		pSellFish->backgroundWithFile("Common/SellFish/popwnd.png");
		//pSellFish->buttonSubmitWithFileCell("Common/Setting/btn_ok.png",3);
		pSellFish->buttonCancelWithFileCell("Common/Button/return.png",3);
		pSellFish->GetBtnCancel()->setPosition(375,10);
		pSellFish->Show(bShow);
	}
	else
	{
		pSellFish->Show(bShow);
	}
	m_pCurShowWnd = pSellFish;
}

void SIX_SceneGame::ShowBuyBulletWnd(bool bShow)
{
	// С�ڵ���0����δ������3Ϊ��������
	if (0 >= PlayerTreasureInfo::Instance().m_lGameType  ||  3==PlayerTreasureInfo::Instance().m_lGameType)
		return;

	if (!pBuyBullet)
	{
		pBuyBullet = SIX_PopWndBuyBullet::Create(0.0,0.0,ccc4(0,0,0,0),512,382,false);
		pBuyBullet->InitMask(ccc4(0,0,0,128));
		pBuyBullet->backgroundWithFile("Common/BuyBullet/popwnd.png");
		//pBuyBullet->buttonSubmitWithFileCell("Common/Setting/btn_ok.png",3);
		pBuyBullet->buttonCancelWithFileCell("Common/Button/return.png",3);
		pBuyBullet->GetBtnCancel()->setPosition(193,10);
		pBuyBullet->Show(bShow);
	}
	else
	{
		pBuyBullet->Show(bShow);
	}
	m_pCurShowWnd = pBuyBullet;
}

void SIX_SceneGame::ShowHelpWnd(bool bShow)
{
	if (!pHelp)
	{
		pHelp = SIX_PopWnd::Create(0.0f,0.0f,ccc4(0,0,0,0),746,666,false);
		pHelp->InitMask(ccc4(0,0,0,128));
		pHelp->backgroundWithFile("Common/Help/popwnd.png");
		//pBuyBullet->buttonSubmitWithFileCell("Common/Setting/btn_ok.png",3);
		pHelp->buttonSubmitWithFileCell("Common/Button/return.png",3);
		pHelp->GetBtnSubmit()->setPosition(ccp(310,10));
		pHelp->Show(bShow);
	}
	else
	{
		pHelp->Show(bShow);
	}
	m_pCurShowWnd = pHelp;
}

void SIX_SceneGame::ShowSetWnd(bool bShow)
{
	if (!pSetting)
	{
		pSetting = SIX_PopWndSetting::Create(0.0,0.0,ccc4(0,0,0,0),459,258,false);
		pSetting->InitMask(ccc4(0,0,0,128));
		pSetting->backgroundWithFile("Common/Setting/popwnd.png");
		pSetting->buttonSubmitWithFileCell("Common/Button/return.png",3);
		pSetting->GetBtnSubmit()->setPosition(ccp(167,10));
		//pSetting->buttonCancelWithFileCell("Common/Setting/btn_cancel.png",4);
		//pSetting->AutoCaclBtnPosWidthYesOrNo(45,20);
		pSetting->Show(bShow);
	}
	else
	{
		pSetting->Show(bShow);
	}
	m_pCurShowWnd = pSetting;
}

bool SIX_SceneGame::OnExitBtn()
{
	CShip *pShip=g_pShipMgr->getMySelfShip();
	if (NULL != pShip  &&  0l>=pShip->getBulletCount() &&  0l>=pShip->getFishCoin())
		return true;

	// �е���������ʾ
	if (0 < SIX_PopWnd::GetPopWndCount()  &&  NULL!=pSceneGame->m_pCurShowWnd)
	{
		if (pSceneGame->m_pCurShowWnd != pSceneGame->pSellFish)
			pSceneGame->m_pCurShowWnd->Show( false );
		else
			return false;
	}

	pSceneGame->ShowSellFishWnd( true );
	return false;
}
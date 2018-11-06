#include "Ship.h"
#include <SIX_SceneGame.h>

PlayerTreasureInfo::PlayerTreasureInfo()
{
	memset(this,0,sizeof(PlayerTreasureInfo));
}

PlayerTreasureInfo::PlayerTreasureInfo(PlayerTreasureInfo &p)
{
	memcpy(this,&p,sizeof(p));
}

PlayerTreasureInfo & PlayerTreasureInfo::Instance()
{
	static PlayerTreasureInfo g_PlayerTreasureInfo;
	return g_PlayerTreasureInfo;
}

TFishMulti PlayerTreasureInfo::getFishMulti(TFishKind fishType)
{
	int validIdx = SIX_PopWndSellFish::GetIndexFromArray(fishType);
	if (validIdx<0 ||validIdx>=StatFishCount)
	{
		return 0;
	}
	TFishMulti ARR_FISHMULTI[StatFishCount] = {1,2,3,4,5,6,7,8,9,10,15,18,20,25,30,80,120,300,500};
	TFishMulti ret=ARR_FISHMULTI[validIdx];
	return ret;
}

void PlayerTreasureInfo::UpdateFishKindNums(unsigned int FishCount[StatFishCount])
{
	for(int i=0;i<StatFishCount;i++)
	{
		m_FishCount[i]+=FishCount[i];
	}
}

void PlayerTreasureInfo::ResetFishKindNums()
{
	memset(m_FishCount,0,sizeof(m_FishCount));
}

const int c_ShipTag[]={100,101,102,103};				// xml�еĴ����飬tagֵ
extern SIX_SceneGame *pSceneGame;

CShipMgr * g_pShipMgr = NULL;

// ------------------------------------------
CShip::CShip()
{
	m_shipSprite = NULL;
	m_gunSprite = NULL;
	m_TreasureSprite=NULL;
	m_pGunGrade=NULL;
	m_gun = NULL;
	m_iNetGapTime = 0;		// ������ʱ��        // add by cxf
	m_lLastPingTime = 0;
	// ���´����ڲ�UI����Ϣ�������
	// Cool.Cat
	this->onEnter();
	this->onEnterTransitionDidFinish();
	this->schedule(schedule_selector(CShip::update), 1.0f);
}

CShip::~CShip()
{
	if (NULL != m_gun)
		CC_SAFE_DELETE(m_gun);
	this->removeAllChildrenWithCleanup( true );
	this->removeFromParentAndCleanup( true );
}

void CShip::Init()
{
	m_UserID = -1;
	m_seatIndex = 0;
	m_shipSprite = 0;
	m_gunSprite = 0;
	m_ullastShootTime = SIX_Utility::GetInstance()->GetTickCount();

	m_iNetGapTime = 0;		// ������ʱ��        // add by cxf

	m_gun = new GUN_DATA();
}

// -- ��ת�ڹܶ���
void CShip::onWhirlGunComplete(CCNode *gun)	
{
	//CShip *ship = dynamic_cast<CShip*>(gun->getUserData());
	CShip *ship = (CShip*)(gun->getUserData());
	ship->m_gun->m_completeWhirlGun = true;
	ship->onWhirlGun(CCP(ship->m_gun->m_unfinishedPT));
}

void CShip::setNetType(int NetType)
{
	mBulletType = NetType;
	CCString *pStrPath = CCString::createWithFormat("explode_00029.png", mBulletType);
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pStrPath->getCString() );
	CCSprite *SpriteNet = CCSprite::createWithSpriteFrame(pFrame);
	mNetSize = SpriteNet->getContentSize();
}

// -- ��ת�ڹ���ָ������
void CShip::onWhirlGun(CCPoint TouchPT, bool bAnimation/*=true*/)	
{
	CShip *pMySelf = g_pShipMgr->getMySelfShip();
	if (!pMySelf)
		return;

	m_gun->m_unfinishedPT = TPoint(TouchPT.x,TouchPT.y);
	if (!m_gun->m_completeWhirlGun)
		return;

	if (!m_shipSprite)
		return;

	// -- �� m_shipSprite �Ŀ�߷ֱ��� ��99,184)����ê��Ϊ(0.5,0.5) ��SceneGame.xml���ڹ��Ǵ����ӽ��
	// -- ����ȼ����������ʼ�㣬�ټ����ڹܵ�ƫ��λ�� �ó�����ϵ���ڹ�����
	float newGunX = m_shipSprite->getPositionX() - m_shipSprite->getContentSize().width/2 + m_gunSprite->getPositionX();
	float newGunY = m_shipSprite->getPositionY() - m_shipSprite->getContentSize().height/2 + m_gunSprite->getPositionY();
	
	// -- Y��̶������X��û�仯ֱ�ӷ���
	if (TouchPT.x == newGunX)
		return;
	
	float angle = (TouchPT.y - newGunY)/(TouchPT.x - newGunX);
	angle = atan(angle)/M_PI*180;
	
	// --CCLuaLog("onMultiTouch.x-----start["..TouchPT.x.."].y["..TouchPT.y.."] angle["..angle.."] newGunX="..newGunX.."newGunY="..newGunY)
	if (2==g_pShipMgr->getPlayerDirection(m_UserID))
	{
		if (0==angle && TouchPT.x<newGunX)
			angle = -(90+angle);
		else
			angle = (0>angle) ? -(90+angle) : 90-angle;
		
		// ������ˮƽ������(�������)�����ϣ�������ң�����ת90��-90
		if (TouchPT.y < newGunY)
		{
			angle = (TouchPT.x>= newGunX) ? 90 : -90;
			TouchPT.y = newGunY;
		}
	}	
	else
	{
		if (0==angle && TouchPT.x>newGunX)
			angle = -(90+angle);
		else
			angle = (0>angle) ? -(90+angle) : 90-angle;
		
		if (TouchPT.y > newGunY)
		{
			angle = (TouchPT.x>= newGunX) ? -90 : 90;
			TouchPT.y = newGunY;
		}
	}
		
	// --CCLuaLog( string.format("edit onMultiTouch pt(%d,%d) angle=%d", TouchPT.x,TouchPT.y, angle) )
	CCSprite *gun = m_gunSprite;
	float OldAngle = gun->getRotation();
	OldAngle = OldAngle-angle;
	// ��ת�ĽǶȴ��ڵ���90��ʱʹ�ö���ʵ�֣�������ֱ�����ýǶȣ�������������
	if (bAnimation  &&  (90 <= OldAngle || -90 >= OldAngle)  &&  m_UserID==pMySelf->m_UserID)
	{
		CCRotateTo *RotateAction = CCRotateTo::create(0.2f, angle);
		m_gun->m_completeWhirlGun = false;

		gun->runAction(CCSequence::createWithTwoActions(RotateAction, CCCallFuncN::create(this,callfuncN_selector(CShip::onWhirlGunComplete))));
	}
	else
		gun->setRotation( angle );
}

void CShip::onWhirlGun(bool bLeft, bool bContinuous)
{
	// ����ʱ����һ����ת�����ɿ�ʱ������ö���
	// window��Ϣ���и�ʱ������ʵ���˰��µ�����ת�ڹ�
	// window���Ϸ��Ͱ����¼���ͨ����̬����s_bLastContinuous���ӣ���ʵ�ֳ�����ת�ڹܶ���
	static bool s_bLastContinuous = false;
	CCSprite *gun = m_gunSprite;
	if (!bContinuous)
	{
		gun->stopAllActions();
		s_bLastContinuous = bContinuous;
		return;
	}
	else if (bContinuous  &&  s_bLastContinuous)
	{
		return;
	}

	float OldAngle = gun->getRotation();
	float fNewAngle = 180.0;
	float fRealAngle = 0.0;
	fNewAngle = OldAngle + (bLeft ? -fNewAngle : fNewAngle);

	if ( -90 > fNewAngle)
		fNewAngle = -90;
	else if (90 < fNewAngle)
		fNewAngle = 90;

	// ������ʵ��ת�ĽǶ�
	if (bLeft)
	{
		if (0 > OldAngle)
			fRealAngle = fabs(fNewAngle)-fabs(OldAngle);
		else
			fRealAngle = OldAngle + 90;
	}
	else
	{
		if (0 > OldAngle)
			fRealAngle = fabs(OldAngle) + 90;
		else
			fRealAngle = 90-OldAngle;
	}

	// ʹ����ʵ��ת�ĽǶ���������ת��Ҫ��ʱ��
	float fTime = 0.5; // ��תһ�����ʱ��
	float duration = fRealAngle/180.0*fTime;
	gun->runAction(CCSequence::create(CCRotateTo::create(duration, fNewAngle), NULL));
	s_bLastContinuous = bContinuous;
}

CCPoint CShip::getGunPos()
{
	CCPoint gunPosition = CCPoint(m_shipSprite->getPositionX(), m_shipSprite->getPositionY());
	gunPosition.y = 0==g_pShipMgr->getPlayerDirection(m_UserID) ? gunPosition.y-m_gun->m_gunOffestY : gunPosition.y+m_gun->m_gunOffestY;
	return gunPosition;
}

void CShip::setVisible(bool bVisible)
{
	if (NULL != m_shipSprite)
		m_shipSprite->setVisible( bVisible );
	if (NULL != m_gunSprite)
		m_gunSprite->setVisible( bVisible );
	if (NULL != m_TreasureSprite)
		m_TreasureSprite->setVisible( bVisible );
	// ֻ��ʾ�Լ���pingֵ��������Ҳ���ʾ
	// Cool.Cat
	if (bVisible && this->m_UserID!=SIX_PlayerMgr::GetInstance()->getMyUserIdx())
		this->m_ping->setVisible(false);
}

unsigned long long CShip::getFishCoin()const
{
	return getGoldCoin(1);
}

void CShip::setFishCoin(unsigned long long lFishCoin)
{
	setGoldCoin(lFishCoin,1,false);
}

unsigned long long CShip::getBulletCount()const
{
	return getGoldCoin(2);
}

void CShip::setBulletCount(unsigned long long lBulletCount)
{
	setGoldCoin(lBulletCount,2,false);
}

unsigned long long CShip::getGoldCoin(int tag/*=3*/)const
{
	if (!m_TreasureSprite)
		return 0;
	SIX_NumberBatchNode *pBatchNode = dynamic_cast<SIX_NumberBatchNode*>(m_TreasureSprite->getChildByTag(tag));
	if (!pBatchNode)
		return 0;
	//unsigned long long ret=_atoi64(pBatchNode->getString());
	unsigned long long ret = 0;
	ret = pBatchNode->getNumber();
	return ret;
}

void CShip::setGoldCoin(unsigned long long lGoldCoin,int tag/*=3*/,bool doAnimate)
{
	if (!m_TreasureSprite)
		return;
	SIX_NumberBatchNode *pBatchNode = dynamic_cast<SIX_NumberBatchNode*>(m_TreasureSprite->getChildByTag(tag));
	if (!pBatchNode)
		return;
	//char sz[100]={0};
	//_ui64toa(lGoldCoin,sz,10);
	//pBatchNode->setString(sz);
	pBatchNode->setNumber(lGoldCoin,doAnimate);
	SIX_Utility::GetInstance()->FixedTexParameters(pBatchNode->getTexture());
}

TGunGrade CShip::getGunGrade()const
{
	if (!m_gunSprite)
		return 1;
	TGunGrade ret=atoi(m_pGunGrade->getString());
	return ret;
}

void CShip::setGunGrade(TGunGrade GunGrade)
{
	if (!m_gunSprite)
		return;
	char sz[100]={0};
	// Ҫע�Ᵽ�ֶ�ƽ̨������
	// Cool.Cat
#ifdef WIN32
	_itoa(GunGrade,sz,10);
#else
	snprintf(sz,99,"%d",GunGrade);
#endif
	m_pGunGrade->setString(sz);
	SIX_Utility::GetInstance()->FixedTexParameters(m_pGunGrade->getTexture());

	if (NULL != m_gun)
	{
		m_gun->m_curGunType=GunGrade;
		SetGunImg();
	}
}

void CShip::SetName(const char *pName)
{
	if (!m_TreasureSprite)
		return;
	// tag 4���û��ǳ�
	CCLabelTTF *pBatchNode = dynamic_cast<CCLabelTTF*>(m_TreasureSprite->getChildByTag(4));
	if (!pBatchNode)
		return;
	pBatchNode->setString( SIX_Utility::GetInstance()->G2U(pName).c_str() );
	SIX_Utility::GetInstance()->FixedTexParameters(pBatchNode->getTexture());
}

// -- �л��ڹ�
#ifdef WIN32
void CShip::AccelerometerKeyHook(unsigned int MSG,unsigned int wParam,long long lParam)
{
	//if (WM_KEYUP != MSG  || GetKeyState(VK_LSHIFT) < 0 ||  GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_SHIFT) < 0)
	//	return;
	//
	//unsigned int Key = wParam;
	//if (49<=Key && 54>=Key)
	//{
	//	// -- ���ּ� 49��=��57��ASCII ʮ���ƣ���ʼ
	//	Key = Key - 49 + 1;
	//}
	//else if (VK_NUMPAD1<=Key && VK_NUMPAD6>=Key)
	//{
	//	 // -- С�������ּ� 97��=��105��ASCII ʮ���ƣ���ʼ
	//	Key = Key - 97 + 1;
	//}
	//else
	//	return;
	//
	//CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( CCString::createWithFormat("gun_%d_00000.png",Key)->getCString() );
	//CCObject *bg = pSceneGame->getChildren()->objectAtIndex(0);
	//// -- ��������ֹ�ڹ��޸�����
	//m_gunSprite->stopAllActions();
	//m_gunSprite->setDisplayFrame(SpriteFrame);
	//m_gun->m_curGunType = Key;
	//
	//CCActionInterval *ScaleToAction = dynamic_cast<CCActionInterval*>(CCScaleTo::create(0.2f, 1.1f));
	//CCScaleTo *ScaleToActionReverse = CCScaleTo::create(0.3f, 1);
	//m_gunSprite->runAction( CCSequence::createWithTwoActions(ScaleToAction, ScaleToActionReverse) );
}
#endif

// -- �����ӵ�����ص�
void CShip::onCallFucRepeatShootBullet()
{
	if (!g_pShipMgr || !g_pShipMgr->getMySelfShip())
		return;

	if (0 >= g_pShipMgr->getMySelfShip()->getBulletCount() )
		return;

	if (NULL != pSceneGame  &&  pSceneGame->GetKeyboardRepeatRoot())
	{
		CCPoint ptGunPos = g_pShipMgr->getMySelfShip()->m_shipSprite->getPosition();
		float fAngle = g_pShipMgr->getMySelfShip()->m_gunSprite->getRotation();
		// �ڹ����Ϸ�Ϊ0�ȣ���ת�����ҷ�Ϊ90����ת������Ϊ-90��
		// ��ʽ��Ҫ�����Ƕȣ����������ҷ�Ϊ0�ȣ�����Ϊ180�ȡ�
		fAngle = 90.0 - fAngle;
		g_pShipMgr->mTouchPT = SIX_Utility::GetInstance()->getAnotherCoordinate(ptGunPos, fAngle, 50);
	}

	//SIXLog("shoot pos (%f,%f)", g_pShipMgr->mTouchPT.x, g_pShipMgr->mTouchPT.y);
	g_pShipMgr->onShootBullet(g_pShipMgr->getMySelfShip()->m_UserID, 0l, g_pShipMgr->mTouchPT,true,false);
}

int CShip::GetGunType()
{
	if (NULL == m_gun)
		return 1;

	if (1<=m_gun->m_curGunType  &&  5>=m_gun->m_curGunType)
		return 1;
	else if (6<=m_gun->m_curGunType  &&  10>=m_gun->m_curGunType)
		return 2;
	else if (11<=m_gun->m_curGunType  &&  15>=m_gun->m_curGunType)
		return 3;
	else if (16<=m_gun->m_curGunType  &&  20>=m_gun->m_curGunType)
		return 4;
	else
		return 1;
}

void CShip::SetGunImg()
{
	CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(  \
		CCString::createWithFormat("gun_%d_00000.png", GetGunType())->getCString() );
	CCObject *bg = pSceneGame->getChildren()->objectAtIndex(0);
	// -- ��������ֹ�ڹ��޸�����
	m_gunSprite->stopAllActions();
	m_gunSprite->setDisplayFrame(SpriteFrame);
	
	CCActionInterval *ScaleToAction = dynamic_cast<CCActionInterval*>(CCScaleTo::create(0.2f, 1.1f));
	CCScaleTo *ScaleToActionReverse = CCScaleTo::create(0.3f, 1);
	m_gunSprite->runAction( CCSequence::createWithTwoActions(ScaleToAction, ScaleToActionReverse) );
}

// �ӱ���
void CShip::IncBet()
{
	TGunGrade curGunGrade=getGunGrade();
	TGunGrade GunGrade=1;
	if(curGunGrade==20)
		GunGrade=1;
	else
		GunGrade=curGunGrade+1;
	setGunGrade(GunGrade);

	// �л�������Ч
	// Cool.Cat
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(26,false);

	// ֪ͨ����˹㲥	
	Req_SetGunGrade req;
	req.llUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	req.GunGrade = GunGrade;
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, REQ_SET_GUNGRADE, &req,sizeof(req));
}

// ������
void CShip::DecBet()
{
	TGunGrade curGunGrade=getGunGrade();
	TGunGrade GunGrade=1;
	if(curGunGrade==1)
		GunGrade=20;
	else
		GunGrade=curGunGrade-1;
    setGunGrade(GunGrade);

	// �л�������Ч
	// Cool.Cat
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(26,false);

	// ֪ͨ����˹㲥
	Req_SetGunGrade req;
	req.llUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	req.GunGrade = GunGrade;
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, REQ_SET_GUNGRADE, &req,sizeof(req));
}

// �Ӽ�������Ҫ֪ͨ����˹㲥
// Cool.Cat
void CShip::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControlButton *pButton = (CCControlButton*)pSender;
	int tag = pButton->getTag();
	SIXLog("CShip.doEvents.pSender[0x%08X].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,event,tag);

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			if (tag==BTN_DEC)
				DecBet();
			else if (tag==BTN_INC)
				IncBet();
			break;
		}
	}
}

void CShip::update(float dt)
{
	// ֻˢ�������UI�ؼ�
	if (!g_pShipMgr || (g_pShipMgr && m_UserID!=SIX_PlayerMgr::GetInstance()->getMyUserIdx()))
		return;
	if (this->m_shipSprite && !this->m_shipSprite->isVisible())
		return;
	if (!this->m_TreasureSprite || !this->m_ping)
		return;

	// ˢ��pingֵUI
	// Cool.Cat
	//SIXLog("CShip.update.getNetGapTime[%d]",getNetGapTime());

	CCString *pFrameName = 0;
	long long delay = getNetGapTime();
	// good
	if (delay<60)
	{
		pFrameName = CCString::create("signal_01.png");
	}
	// no bad
	else if (delay<120)
	{
		pFrameName = CCString::create("signal_02.png");
	}
	// bad
	else
	{
		pFrameName = CCString::create("signal_03.png");
	}

	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pFrameName->getCString());
	if (!pFrame)
		return;
	m_ping->setTexture(pFrame->getTexture());
	m_ping->setTextureRect(pFrame->getRect());
}

// ���ڴδ���ʾ
void CShip::ShowHereTips(bool IsShow)
{
	CCSprite *pHere = dynamic_cast<CCSprite*>(this->m_shipSprite->getChildByTag(99));
	if (!pHere)
	{
		pHere = CCSprite::create("Common/Tips/here.png");
		if (!pHere)
			return;
		CCPoint pt = m_shipSprite->getPosition();
		if (g_pShipMgr->getPlayerDirection(this->m_UserID)==2)
			pHere->setPosition(ccp(this->m_shipSprite->getContentSize().width/2,this->m_shipSprite->getContentSize().height+50.0f));
		else
			pHere->setPosition(ccp(this->m_shipSprite->getContentSize().width/2,-this->m_shipSprite->getContentSize().height-50.0f));
		pHere->setTag(99);
		this->m_shipSprite->addChild(pHere);
	}
	pHere->setVisible(IsShow);
}

///////////////////////////////////////////////////////////////////////////////////
CShipMgr::CShipMgr()
{
	mIsNeedTransform = false;
	mTouchPT = CCPoint(0,0);
	//ZeroMemory(mShipData, sizeof(mShipData));
	memset(mShipData,0,sizeof(mShipData));
}

void CShipMgr::Enter(CCNode *Parent, long long UserID, int seatAbsoluteIndex, bool isMyself)
{
	int shipIndex = -1;
	if (isMyself)
	{
		ResetPlayer();
		//shipIndex = rand()%2+2;
		//add by Ivan_han 20130529
		shipIndex=getViewID(seatAbsoluteIndex,&mIsNeedTransform);
	}
	else if (NULL != getMySelfShip())
	{
		shipIndex = getViewID(seatAbsoluteIndex, getMySelfShip()->m_seatAbsoluteIndex, getMySelfShip()->m_seatIndex);
	}

	//// �Ҹ�����λ
	//for (int i=0;i<MAX_PLAYER;i++)
	//{
	//	if (!mShipData[i] && (isMyself && i>=MAX_PLAYER/2))
	//	{
	//		shipIndex = i;
	//		break;
	//	}
	//}

	if (0 > shipIndex || MAX_PLAYER <= shipIndex || NULL != mShipData[shipIndex])
	{
		SIXLog("error no seats! -- CShip:Enter(),UserID = %lld",UserID);
		return;
	}

	CShip *newShip = new CShip();
	newShip->Init();
	
	newShip->m_UserID = UserID;
	newShip->m_seatIndex = shipIndex;
	newShip->m_seatAbsoluteIndex = seatAbsoluteIndex;
	// ����
	newShip->m_shipSprite = dynamic_cast<CCSprite*>(Parent->getChildByTag( c_ShipTag[newShip->m_seatIndex] ));
	CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( CCString::createWithFormat("bg.png")->getCString() );
	newShip->m_shipSprite->setDisplayFrame(SpriteFrame);
	// ����
	newShip->m_gunSprite = dynamic_cast<CCSprite*>(newShip->m_shipSprite->getChildByTag(1));
	newShip->m_gunSprite->setUserData(newShip);
	SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( CCString::createWithFormat("gun_%d_00000.png", newShip->GetGunType())->getCString() );
	newShip->m_gunSprite->setDisplayFrame( SpriteFrame );
	// pingֵ
	newShip->m_ping = dynamic_cast<CCSprite*>(newShip->m_shipSprite->getChildByTag(2));
	// ��Ϣ����
	newShip->m_TreasureSprite= dynamic_cast<CCSprite*>(newShip->m_shipSprite->getChildByTag(3));
	newShip->m_TreasureSprite->setUserData(newShip);
	newShip->setVisible(true);

	newShip->mBulletSpeed = 500;
	newShip->mBulletType = 2;
	newShip->mNetSize.setSize(0,0);

	//add by Ivan_han 20130723
	if(!newShip->m_pGunGrade)
	{
		newShip->m_pGunGrade = CCLabelTTF::create("1", "΢���ź�", 18);
		newShip->m_pGunGrade->setPosition(ccp(110,50));
		newShip->m_pGunGrade->setColor(ccc3(238,199,16));
		newShip->m_shipSprite->addChild(newShip->m_pGunGrade);
	}

	// �Ӽ����ʰ�ť
	// Cool.Cat
	if (isMyself)
	{
		CCControlButton *pDec = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Game/dec.png",2);
		if (pDec)
		{
			pDec->setPosition(ccp(10,5));
			pDec->setTag(BTN_DEC);
			pDec->addTargetWithActionForControlEvents(newShip,cccontrol_selector(CShip::doEvents),32);
			newShip->m_shipSprite->addChild(pDec);
		}

		CCControlButton *pInc = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Game/inc.png",2);
		if (pInc)
		{
			pInc->setPosition(ccp(newShip->m_shipSprite->getContentSize().width-pInc->getContentSize().width-10,5));
			pInc->setTag(BTN_INC);
			pInc->addTargetWithActionForControlEvents(newShip,cccontrol_selector(CShip::doEvents),32);
			newShip->m_shipSprite->addChild(pInc);
		}
	}

	mShipData[shipIndex] = newShip;

	float fGunPosX = newShip->m_shipSprite->getPositionX();
	newShip->onWhirlGun( CCPoint(fGunPosX, 100) ); // ��ʼ���ڹ�λ��

	//add by Ivan_han 20130715
	//PLAYER_LIST *pPlayerList = NULL;
	//this->GetUserPlayer(UserID, &pPlayerList);
	PLAYER_LIST *pPlayerList = SIX_PlayerMgr::GetInstance()->Get(UserID);
	if (NULL != pPlayerList)
	{
		newShip->setGoldCoin(0,1,false);
		newShip->setGoldCoin(0,2,false);
		if(PlayerTreasureInfo::Instance().m_lGameType==2||pPlayerList->lGoldLogin>0)
			newShip->setGoldCoin(pPlayerList->lGoldLogin,3,false);
		else
			newShip->setGoldCoin(pPlayerList->lPointLogin,3,false);
		newShip->SetName(0>=strlen(pPlayerList->szNickname) ? pPlayerList->szName : pPlayerList->szNickname);
	}
	//unsigned long long lGoldCoin=newShip->getGoldCoin();
}

void CShipMgr::Leave( long long UserID )
{
	CShip * pPlayer = getShip( UserID );
	if (NULL != pPlayer)
	{
		pPlayer->m_shipSprite->setVisible( false );
		int nSeatIndex = pPlayer->m_seatIndex;
		if (NULL != mShipData[nSeatIndex])
		{
			mShipData[nSeatIndex]->unscheduleAllSelectors();
			CC_SAFE_RELEASE_NULL(mShipData[nSeatIndex]);
			//mShipData[nSeatIndex]->release();
			//mShipData[nSeatIndex] = NULL;
		}
	}

	/// ����˳��ӵ���Ҫ���
	if (g_pBulletMgr && g_pBulletMgr->sharedBullet())
	{
		CCArray *allBullet = g_pBulletMgr->sharedBullet()->getChildren();
		CBulletAndNet *pBullet = 0;
		BULLET_BIND_DATA *pBulletData = 0;
		for (int index=0; index<(int)(allBullet->count()); )
		{
			pBullet = dynamic_cast<CBulletAndNet*>( allBullet->objectAtIndex( index++ ) );
			if ( NULL != pBullet  && pBullet->Data.UserID ==  UserID )
			{
				index--;
				pBullet->setUserData((void*)1);
				pBullet->DelBullet( pBullet );
			}
		}
	}
}

void CShipMgr::Release()
{
	ResetPlayer();
}

CShip *CShipMgr::getShip(long long UserID)
{
	for (int i=0;i<MAX_PLAYER;i++)
	{
		CShip *pShip = mShipData[i];
		if (NULL != pShip  &&  pShip->m_UserID==UserID)
			return pShip;
	}
	return 0;
}

// ��ȡ�Լ�
CShip *CShipMgr::getMySelfShip()
{
	return getShip( SIX_PlayerMgr::GetInstance()->getMyUserIdx() );
}

/// �������λ��
void CShipMgr::onUpdateMousePT(CCPoint pt)
{
	mTouchPT = pt;
}

void CShipMgr::ResetPlayer()
{
	for (int i=0; i<4; i++)
	{
		if (NULL != mShipData[i])
		{
			//mShipData[i]->release();
			//mShipData[i] = NULL;
			this->Leave(mShipData[i]->m_UserID);
		}
	}
}

// �����ҷ���
int CShipMgr::getPlayerDirection(long long UserID)
{
	CShip *pShip = getShip( UserID );
	if (NULL == pShip)
		return 0;

	// ��������ֱ���0,1,2,3
	if (2==pShip->m_seatIndex || 3==pShip->m_seatIndex)
		return 2;
	return 0;
}

//��ȡ�������Լ��ͻ����е���ͼID
int CShipMgr::getViewID(int CurLogicID, int MyLogicID, int MyViewID)
{
	// 4 ��λ��
	// �߼�ID���Ͻ�˳ʱ�뷽��˳�� 0132
	// ��ͼID���Ͻ�˳ʱ�뷽��˳�� 0123

	//�߼�ID��������
	if (CurLogicID+MyLogicID==1)
		return 5-MyViewID;
	//�߼�ID��������
	if (CurLogicID+MyLogicID==5)
		return 5-MyViewID;

	//�߼�IDһ��һ�£���������
	if (CurLogicID+MyLogicID==2||CurLogicID+MyLogicID==4)
		return 3-MyViewID;

	//�߼�IDһ��һ�£���б����
	if (CurLogicID+MyLogicID==3)
	{
	    //�Լ����߼�ID������
		if(MyLogicID>1)
			return CurLogicID;
		//�Լ����߼�ID������
		if(MyLogicID<2)
			return MyViewID-2;
	}

	return -1;//����ֵ
}

void CShipMgr::AdjustmentPos(long long llUserID, CCPoint &pt)
{
	if (getMySelfShip()->m_UserID == llUserID )
		return;

	//if (getPlayerDirection( getMySelfShip()->m_UserID )  !=  getPlayerDirection( llUserID ))
	//{
	//	pt.y += 40;
	//}
}

void CShipMgr::AdjustmentPos(long long llUserID, qcPoint &pt)
{
	CCPoint ptPos(pt.x, pt.y);
	AdjustmentPos(llUserID, ptPos);
	pt.x = ptPos.x;
	pt.y = ptPos.y;
}

/*
	��Ӧ����/������Ϣ����Լ�����˵��ӵ�����
	llID----0��ʾ���Լ������ӵ���>0��ʾ������ص����ӵ�ID��comment by Ivan_han 20130815
	TouchPT----�ӵ�����Ŀ���
	RepeatShoot----�ظ�����
	bSetTouchPT----����ʹ�÷���Ŀ��㣬��Ϊ��ת�ڹ��и�ʱ�������Լ�������ӵ������ TouchPT ����
	bSetTouchPT----��������ǿ��ʹ�� TouchPT����Լ��̲��������ע�����û���ƶ���λ����û�и��µģ�
*/
void CShipMgr::onShootBullet(long long UserID, TBulletID llID, CCPoint TouchPT, bool RepeatShoot, bool bSetTouchPT/*=false*/ )
{
	// �ǳ���ֹ����
	if (pSceneGame && pSceneGame->IsNoFire())
		return;

	CCPoint ShootPT = TouchPT;
	CShip *pShip = getShip(UserID);
	if (NULL == pShip)
		return;

	if (pShip->m_UserID == SIX_PlayerMgr::GetInstance()->getMyUserIdx())
	{
		if (!pShip->m_gun->m_completeWhirlGun)
		{
			pShip->m_gun->m_completeWhirlGun = true;
			g_pShipMgr->getMySelfShip()->onWhirlGun( TouchPT, false );
			//return;
		}
		ShootPT = (bSetTouchPT ? ShootPT : mTouchPT);
	}

	// -- �ڹܵ����ĵ㣺���ĵ� x����ڴ������ĵ㣬y����ڴ����ĵ�ƫ�� m_gunOffestY ����
	// -- CCSprite�ӽ��������(0,0),�ڹ��봬���Ǿ���
	CCPoint gunPosition = CCPoint(pShip->m_shipSprite->getPositionX(), pShip->m_shipSprite->getPositionY());
	if (0 == getPlayerDirection(pShip->m_UserID))
	{
		gunPosition.y = gunPosition.y - pShip->m_gun->m_gunOffestY;
		if (ShootPT.y > gunPosition.y)
			ShootPT.y = gunPosition.y;
	}
	else
	{
		gunPosition.y = gunPosition.y + pShip->m_gun->m_gunOffestY;
		if (ShootPT.y < gunPosition.y)
			ShootPT.y = gunPosition.y;
	}

	if (pShip->m_UserID != SIX_PlayerMgr::GetInstance()->getMyUserIdx())
	{
		//AdjustmentPos(pShip->m_UserID, ShootPT);
		pShip->onWhirlGun( ShootPT );
	}

	//add by Ivan_han 20130724
	if (pShip->m_UserID == SIX_PlayerMgr::GetInstance()->getMyUserIdx() && getMySelfShip()->getBulletCount()<pShip->m_gun->m_curGunType)
	{
		if (pSceneGame && pSceneGame->IsInited() && pSceneGame->m_UIManager)
		{
			CCObject *pBtn=pSceneGame->getChildByObjName("Bullet");
			if(pBtn)
			{
				pSceneGame->m_UIManager->doEvents(pBtn,CCControlEventTouchUpInside);
			}
		}	
		return;
	}

	// ȡ������ʱ����еĻ�
	// Cool.Cat
	if (pShip->m_UserID == SIX_PlayerMgr::GetInstance()->getMyUserIdx())
	{
		pSceneGame->RemoveCountDownAndTips();
	}

	bool bSuccess = CBulletAndNetMgr::GetInstance()->addOneBullet(UserID, llID, ShootPT, gunPosition, pShip->m_gunSprite->getRotation(), RepeatShoot, pShip->m_gun->m_curGunType);
	if ( bSuccess )
	{
		CCArray *gunAction =CBulletAndNetMgr::createGunSpriteFrameArray(pShip->GetGunType());
		//pShip->m_gunSprite->stopAllActions();
		CCAnimation *pGunAnimation = CCAnimation::createWithSpriteFrames(gunAction, 0.04f);
		CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( \
			CCString::createWithFormat("gun_%d_00000.png", pShip->GetGunType())->getCString() );
		pShip->m_gunSprite->setDisplayFrame( SpriteFrame );
		pGunAnimation->setRestoreOriginalFrame( true );
		pShip->m_gunSprite->runAction(CCAnimate::create( pGunAnimation ));
	}
}

/// �����߼�ID��ȡ�ͻ��˵���ͼID�Լ������Ƿ��������任
int CShipMgr::getViewID(int LogicID,bool *IsNeedTransform)
{
	assert(LogicID>=0 && LogicID<=3);
	switch ( LogicID )
	{
	case 0:	// �߼�ID=���Ϸ�
		{
			*IsNeedTransform=true;
			return 2;//��ͼID=���·�����[0]=2
		}
	case 1:	// �߼�ID=���Ϸ�
		{
			*IsNeedTransform=true;
			return 3;//��ͼID=���·�����[1]=3
		}
	case 2:	// �߼�ID=���·�
		{
			*IsNeedTransform=false;
			return 3;//��ͼID=���·�����[2]=3
		}
	case 3:	//�߼�ID=���·�
		{
			*IsNeedTransform=false;
			return 2;//��ͼID=���·�����[3]=2
		}
	default: break;
	}
	return 0;
}

CCPoint CShipMgr::SP2CP(const CCPoint& SP)
{
	CCPoint ret=CShipMgr::ScaleTrans(1280,733,MAX_WIDTH,MAX_HEIGHT,SP);
	if(mIsNeedTransform)
	{
		ret=ccp(MAX_WIDTH-ret.x,MAX_HEIGHT-ret.y);
	}
	return ret;
}

CCPoint CShipMgr::CP2SP(const CCPoint& CP)
{

	CCPoint ret=CShipMgr::ScaleTrans(MAX_WIDTH,MAX_HEIGHT,1280,733,CP);
	if(mIsNeedTransform)
	{
		ret=ccp(1280-ret.x,733-ret.y);
	}
	return ret;
}

CCPoint CShipMgr::SD2CD(const CCPoint& SD)
{
	//CCPoint ret=SD;
	//if(mIsNeedTransform)
	//{
	//	ret=ccp(-SD.x,-SD.y);
	//}
	CCPoint ret=ccpSub(SP2CP(SD),SP2CP(ccp(0,0)));
	return ret;
}

CCPoint CShipMgr::CD2SD(const CCPoint& CD)
{
	//return SD2CD(CD);
	CCPoint ret=ccpSub(CP2SP(CD),CP2SP(ccp(0,0)));
	return ret;
}

float CShipMgr::SD2CD(float SD)
{
	//float ret=SD;
	//if(mIsNeedTransform)
	//{
	//	ret=SD+M_PI;
	//}
	//return ret;
	CCPoint cd=SD2CD(ccp(cos(SD),sin(SD)));
	float ret=atan2(cd.y,cd.x);
	return ret;
}

float CShipMgr::CD2SD(float CD)
{
	//return SD2CD(CD);
	CCPoint sd=CD2SD(ccp(cos(CD),sin(CD)));
	float ret=atan2(sd.y,sd.x);
	return ret;
}


float CShipMgr::ScaleXTrans(int W,int W1,float x)
{
	return x*W1/W;
}
float CShipMgr::ScaleXTrans(float ScaleX,float x)
{
	return x*ScaleX;
}
CCPoint CShipMgr::ScaleTrans(int W,int H,int W1,int H1,const CCPoint& p)
{
	CCPoint ret=CCPoint(ScaleXTrans(W,W1,p.x),ScaleXTrans(H,H1,p.y));
	return ret;
}
CCPoint CShipMgr::ScaleTrans(float ScaleX,float ScaleY,const CCPoint& p)
{
	CCPoint ret=CCPoint(ScaleXTrans(ScaleX,p.x),ScaleXTrans(ScaleY,p.y));
	return ret;
}

//// ����Ƿ�����û�
//bool CShipMgr::ExistUserPlayer(long long llUserID)
//{
//	bool bRet = false;
//	vector<PLAYER_LIST*>::const_iterator it = mPlayerList.begin();
//	for (; it != mPlayerList.end(); ++it )
//	{
//		PLAYER_LIST * pPlayer = *it;
//		if (llUserID == pPlayer->UserIdx)
//		{
//			bRet = true;
//			break;
//		}
//	}
//	return bRet;
//};
//
//// �����û�ָ��
//void CShipMgr::GetUserPlayer(long long llUserID, PLAYER_LIST **pPlayerUser)
//{
//	vector<PLAYER_LIST*>::const_iterator it = mPlayerList.begin();
//	for (; it != mPlayerList.end(); ++it )
//	{
//		PLAYER_LIST * pPlayer = *it;
//		if (llUserID == pPlayer->UserIdx)
//		{
//			*pPlayerUser=pPlayer;
//			break;
//		}
//	}
//};
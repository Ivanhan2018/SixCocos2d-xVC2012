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

const int c_ShipTag[]={100,101,102,103};				// xml中的船精灵，tag值
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
	m_iNetGapTime = 0;		// 网络间隔时间        // add by cxf
	m_lLastPingTime = 0;
	// 更新船体内部UI等信息放这里吧
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

	m_iNetGapTime = 0;		// 网络间隔时间        // add by cxf

	m_gun = new GUN_DATA();
}

// -- 旋转炮管动画
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

// -- 旋转炮管至指定坐标
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

	// -- 船 m_shipSprite 的宽高分别是 （99,184)，且锚点为(0.5,0.5) 见SceneGame.xml，炮管是船的子结点
	// -- 因此先计算出船的起始点，再加上炮管的偏移位置 得出坐标系内炮管坐标
	float newGunX = m_shipSprite->getPositionX() - m_shipSprite->getContentSize().width/2 + m_gunSprite->getPositionX();
	float newGunY = m_shipSprite->getPositionY() - m_shipSprite->getContentSize().height/2 + m_gunSprite->getPositionY();
	
	// -- Y轴固定，因此X轴没变化直接返回
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
		
		// 单击炮水平线以下(下排玩家)，以上（上排玩家），旋转90，-90
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
	// 旋转的角度大于等于90度时使用动画实现，而不是直接设置角度（这样更流畅）
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
	// 按下时创建一个旋转动画松开时便结束该动画
	// window消息间有个时间差，所以实现了按下单次旋转炮管
	// window不断放送按下事件，通过静态变量s_bLastContinuous忽视，来实现持续旋转炮管动画
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

	// 计算真实旋转的角度
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

	// 使用真实旋转的角度来计算旋转需要的时间
	float fTime = 0.5; // 旋转一次最大时间
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
	// 只显示自己的ping值，其他玩家不显示
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
	// 要注意保持多平台兼容性
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
	// tag 4是用户昵称
	CCLabelTTF *pBatchNode = dynamic_cast<CCLabelTTF*>(m_TreasureSprite->getChildByTag(4));
	if (!pBatchNode)
		return;
	pBatchNode->setString( SIX_Utility::GetInstance()->G2U(pName).c_str() );
	SIX_Utility::GetInstance()->FixedTexParameters(pBatchNode->getTexture());
}

// -- 切换炮管
#ifdef WIN32
void CShip::AccelerometerKeyHook(unsigned int MSG,unsigned int wParam,long long lParam)
{
	//if (WM_KEYUP != MSG  || GetKeyState(VK_LSHIFT) < 0 ||  GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_SHIFT) < 0)
	//	return;
	//
	//unsigned int Key = wParam;
	//if (49<=Key && 54>=Key)
	//{
	//	// -- 数字键 49《=》57（ASCII 十进制）开始
	//	Key = Key - 49 + 1;
	//}
	//else if (VK_NUMPAD1<=Key && VK_NUMPAD6>=Key)
	//{
	//	 // -- 小键盘数字键 97《=》105（ASCII 十进制）开始
	//	Key = Key - 97 + 1;
	//}
	//else
	//	return;
	//
	//CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( CCString::createWithFormat("gun_%d_00000.png",Key)->getCString() );
	//CCObject *bg = pSceneGame->getChildren()->objectAtIndex(0);
	//// -- 动画会阻止炮管修改属性
	//m_gunSprite->stopAllActions();
	//m_gunSprite->setDisplayFrame(SpriteFrame);
	//m_gun->m_curGunType = Key;
	//
	//CCActionInterval *ScaleToAction = dynamic_cast<CCActionInterval*>(CCScaleTo::create(0.2f, 1.1f));
	//CCScaleTo *ScaleToActionReverse = CCScaleTo::create(0.3f, 1);
	//m_gunSprite->runAction( CCSequence::createWithTwoActions(ScaleToAction, ScaleToActionReverse) );
}
#endif

// -- 连续子弹发射回调
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
		// 炮管正上方为0度，旋转到最右方为90，旋转到最左方为-90。
		// 公式需要修正角度，修正后最右方为0度，最左方为180度。
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
	// -- 动画会阻止炮管修改属性
	m_gunSprite->stopAllActions();
	m_gunSprite->setDisplayFrame(SpriteFrame);
	
	CCActionInterval *ScaleToAction = dynamic_cast<CCActionInterval*>(CCScaleTo::create(0.2f, 1.1f));
	CCScaleTo *ScaleToActionReverse = CCScaleTo::create(0.3f, 1);
	m_gunSprite->runAction( CCSequence::createWithTwoActions(ScaleToAction, ScaleToActionReverse) );
}

// 加倍率
void CShip::IncBet()
{
	TGunGrade curGunGrade=getGunGrade();
	TGunGrade GunGrade=1;
	if(curGunGrade==20)
		GunGrade=1;
	else
		GunGrade=curGunGrade+1;
	setGunGrade(GunGrade);

	// 切换倍率音效
	// Cool.Cat
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(26,false);

	// 通知服务端广播	
	Req_SetGunGrade req;
	req.llUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	req.GunGrade = GunGrade;
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, REQ_SET_GUNGRADE, &req,sizeof(req));
}

// 减倍率
void CShip::DecBet()
{
	TGunGrade curGunGrade=getGunGrade();
	TGunGrade GunGrade=1;
	if(curGunGrade==1)
		GunGrade=20;
	else
		GunGrade=curGunGrade-1;
    setGunGrade(GunGrade);

	// 切换倍率音效
	// Cool.Cat
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(26,false);

	// 通知服务端广播
	Req_SetGunGrade req;
	req.llUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	req.GunGrade = GunGrade;
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, REQ_SET_GUNGRADE, &req,sizeof(req));
}

// 加减倍率需要通知服务端广播
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
	// 只刷新自身的UI控件
	if (!g_pShipMgr || (g_pShipMgr && m_UserID!=SIX_PlayerMgr::GetInstance()->getMyUserIdx()))
		return;
	if (this->m_shipSprite && !this->m_shipSprite->isVisible())
		return;
	if (!this->m_TreasureSprite || !this->m_ping)
		return;

	// 刷新ping值UI
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

// 您在次处提示
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

	//// 找个空座位
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
	// 船体
	newShip->m_shipSprite = dynamic_cast<CCSprite*>(Parent->getChildByTag( c_ShipTag[newShip->m_seatIndex] ));
	CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( CCString::createWithFormat("bg.png")->getCString() );
	newShip->m_shipSprite->setDisplayFrame(SpriteFrame);
	// 炮塔
	newShip->m_gunSprite = dynamic_cast<CCSprite*>(newShip->m_shipSprite->getChildByTag(1));
	newShip->m_gunSprite->setUserData(newShip);
	SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( CCString::createWithFormat("gun_%d_00000.png", newShip->GetGunType())->getCString() );
	newShip->m_gunSprite->setDisplayFrame( SpriteFrame );
	// ping值
	newShip->m_ping = dynamic_cast<CCSprite*>(newShip->m_shipSprite->getChildByTag(2));
	// 信息区域
	newShip->m_TreasureSprite= dynamic_cast<CCSprite*>(newShip->m_shipSprite->getChildByTag(3));
	newShip->m_TreasureSprite->setUserData(newShip);
	newShip->setVisible(true);

	newShip->mBulletSpeed = 500;
	newShip->mBulletType = 2;
	newShip->mNetSize.setSize(0,0);

	//add by Ivan_han 20130723
	if(!newShip->m_pGunGrade)
	{
		newShip->m_pGunGrade = CCLabelTTF::create("1", "微软雅黑", 18);
		newShip->m_pGunGrade->setPosition(ccp(110,50));
		newShip->m_pGunGrade->setColor(ccc3(238,199,16));
		newShip->m_shipSprite->addChild(newShip->m_pGunGrade);
	}

	// 加减倍率按钮
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
	newShip->onWhirlGun( CCPoint(fGunPosX, 100) ); // 初始化炮管位置

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

	/// 玩家退出子弹需要清掉
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

// 获取自己
CShip *CShipMgr::getMySelfShip()
{
	return getShip( SIX_PlayerMgr::GetInstance()->getMyUserIdx() );
}

/// 更新鼠标位置
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

// 获得玩家方向
int CShipMgr::getPlayerDirection(long long UserID)
{
	CShip *pShip = getShip( UserID );
	if (NULL == pShip)
		return 0;

	// 上右下左分别是0,1,2,3
	if (2==pShip->m_seatIndex || 3==pShip->m_seatIndex)
		return 2;
	return 0;
}

//获取别人在自己客户端中的视图ID
int CShipMgr::getViewID(int CurLogicID, int MyLogicID, int MyViewID)
{
	// 4 个位置
	// 逻辑ID左上角顺时针方向顺序 0132
	// 视图ID左上角顺时针方向顺序 0123

	//逻辑ID都在上面
	if (CurLogicID+MyLogicID==1)
		return 5-MyViewID;
	//逻辑ID都在下面
	if (CurLogicID+MyLogicID==5)
		return 5-MyViewID;

	//逻辑ID一上一下，且正对面
	if (CurLogicID+MyLogicID==2||CurLogicID+MyLogicID==4)
		return 3-MyViewID;

	//逻辑ID一上一下，且斜对面
	if (CurLogicID+MyLogicID==3)
	{
	    //自己的逻辑ID在下面
		if(MyLogicID>1)
			return CurLogicID;
		//自己的逻辑ID在上面
		if(MyLogicID<2)
			return MyViewID-2;
	}

	return -1;//错误值
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
	响应网络/本地消息添加自己或别人的子弹精灵
	llID----0表示是自己发射子弹，>0表示是网络回调中子弹ID，comment by Ivan_han 20130815
	TouchPT----子弹发射目标点
	RepeatShoot----重复发射
	bSetTouchPT----设置使用发射目标点，因为旋转炮管有个时间差，所以自己发射的子弹会忽视 TouchPT 参数
	bSetTouchPT----参数则是强制使用 TouchPT，针对键盘操作情况（注：鼠标没有移动，位置是没有更新的）
*/
void CShipMgr::onShootBullet(long long UserID, TBulletID llID, CCPoint TouchPT, bool RepeatShoot, bool bSetTouchPT/*=false*/ )
{
	// 涨潮禁止开火
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

	// -- 炮管的中心点：中心点 x轴等于船的中心点，y轴等于船中心点偏移 m_gunOffestY 像素
	// -- CCSprite子结点的起点是(0,0),炮管与船都是精灵
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

	// 取消倒计时如果有的话
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

/// 根据逻辑ID获取客户端的视图ID以及决定是否进行坐标变换
int CShipMgr::getViewID(int LogicID,bool *IsNeedTransform)
{
	assert(LogicID>=0 && LogicID<=3);
	switch ( LogicID )
	{
	case 0:	// 逻辑ID=左上方
		{
			*IsNeedTransform=true;
			return 2;//视图ID=右下方，即[0]=2
		}
	case 1:	// 逻辑ID=右上方
		{
			*IsNeedTransform=true;
			return 3;//视图ID=左下方，即[1]=3
		}
	case 2:	// 逻辑ID=左下方
		{
			*IsNeedTransform=false;
			return 3;//视图ID=左下方，即[2]=3
		}
	case 3:	//逻辑ID=右下方
		{
			*IsNeedTransform=false;
			return 2;//视图ID=右下方，即[3]=2
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

//// 检查是否存在用户
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
//// 返回用户指针
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
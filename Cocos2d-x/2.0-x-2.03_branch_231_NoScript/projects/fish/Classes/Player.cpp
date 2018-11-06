#include "Player.h"

static int d_Gun_Count = 5;					// 炮数目
static int d_Gun_Frame_Count = 4;		// 炮帧数目

int PlayerManage::m_MySelfID = -1;							// 玩家自己ID
CCDictionary* PlayerManage::s_AllPlayer = NULL;	// 所有玩家

enum ZOrderLayer
{
	Z_BULLET,											// 子弹
	Z_SHIP,												// 船
	Z_GUN,											// 炮
};

enum T_tag
{
	t_NetworkSignal,								// 网络信号 tag
	t_Gun,												// 炮 tag
	t_Ship,												// 船 tag
};

#define FIX_POS(_pos, _min, _max) \
	if (_pos < _min)        \
	_pos = _min;        \
else if (_pos > _max)   \
	_pos = _max;        \

Player::Player(int iPosition, bool bMySelf/*=false*/) : m_PlayerPT( iPosition )
	, m_iGunType( 1 )
	, m_pGunAnimation( NULL )
	, m_MySelf( bMySelf )
{
	setTouchEnabled( bMySelf ? true : false );
}

Player::~Player(void)
{
}

void Player::onEnter()
{
	CCLayer::onEnter();

	setAccelerometerEnabled( m_MySelf ? true : false );

	CCSize sVisible = CCDirector::sharedDirector()->getVisibleSize();

	// 船
	CCSprite * pShip = CCSprite::create("play/ship.png");
	addChild( pShip, Z_SHIP,  t_Ship);
	if (PLAYER_COUNT/2 <= m_PlayerPT)
		pShip->setFlipY( true );
	CCPoint ShipPT[PLAYER_COUNT]={ccp(180, sVisible.height-15),  ccp(sVisible.width-200, sVisible.height-15),  ccp(sVisible.width-200, 55),  ccp(180, 55) };
	pShip->setPosition(ShipPT[m_PlayerPT]);
	
	// 炮
	CCSpriteFrameCache *pGunFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pGunFrameCache->addSpriteFramesWithFile("play/gun.plist");
	CCSprite * pGun = CCSprite::createWithSpriteFrame( pGunFrameCache->spriteFrameByName("gun_1_00000.png") );
	pShip->addChild( pGun, Z_GUN+10, t_Gun );
	if (PLAYER_COUNT/2 > m_PlayerPT)
		pGun->setFlipY( true );
	CCPoint GunPT[PLAYER_COUNT]={ccp(50, 20), ccp(50, 20), ccp(50, 110), ccp(50, 110)};
	pGun->setAnchorPoint(CCPoint(0.5f, 0.38f));
	pGun->setPosition(CCPoint(GunPT[m_PlayerPT].x, GunPT[m_PlayerPT].y));
	SetGunType( true );
	
	// 初始子弹
	m_BulletManage = CBulletManage::Init( this );
	m_BulletManage->sharedBullet()->_setZOrder/*setZOrder*/( Z_BULLET );
	CCAssert(m_BulletManage, "Bullet Init Failed!");

	//// 网络标记
	//CCSprite *pNetworkSignal = CCSprite::create("play/signal1.png");
	//addChild( pNetworkSignal,  t_NetworkSignal );
	//CCPoint fNetworkPT[PLAYER_COUNT]={ccp(-75, 0), ccp(75, 0), ccp(75, 0), ccp(-75, 0)};
	//pNetworkSignal->setPosition(CCPoint(pShip->getPositionX() + fNetworkPT[m_PlayerPT].x, pShip->getPositionY() + fNetworkPT[m_PlayerPT].y));

	//// 子弹标记
	//CCSprite *pBulletSign = CCSprite::create("play/BulletSign.png");
	//addChild( pBulletSign );
	//CCPoint fBulletSignPT[PLAYER_COUNT]={ccp(65, -20), ccp(-135, -20), ccp(-135, 55), ccp(65, 55)};
	//pBulletSign->setPosition(CCPoint(pShip->getPositionX() + fBulletSignPT[m_PlayerPT].x, pShip->getPositionY() + fBulletSignPT[m_PlayerPT].y));

	//// 金币标记
	//CCSprite * pGoldSign = CCSprite::create("play/GoldSign.png");
	//addChild( pGoldSign );
	//CCPoint fGoldSignPT[PLAYER_COUNT]={ccp(65, -40), ccp(-135, -40), ccp(-135, 35), ccp(65, 35)};
	//pGoldSign->setPosition(CCPoint(pShip->getPositionX() + fGoldSignPT[m_PlayerPT].x, pShip->getPositionY() + fGoldSignPT[m_PlayerPT].y));

	//// 玩家信息背景
	//CCSprite * pPlayerContentBG = CCSprite::create("play/PlayerInfoBG.png");
	//addChild( pPlayerContentBG );
	//CCPoint fPlayerContentBGPT[PLAYER_COUNT]={ccp(60, 40), ccp(-60, 40), ccp(45, -15), ccp(-60, -15)};
	//pPlayerContentBG->setPosition(CCPoint(pShip->getPositionX() + fPlayerContentBGPT[m_PlayerPT].x, pShip->getPositionY() + fPlayerContentBGPT[m_PlayerPT].y));


	// 玩家划船进入，未到达捕鱼现场，除了炮与船其他信息暂隐藏。
	CCSprite *pChild = NULL;
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(getChildren(), pObj)
	{
		pChild = (CCSprite*)pObj;
		pChild->setVisible( false );
	}
	schedule(schedule_selector(Player::OnRowingAnimation), 1.0f);
}

void Player::onExit()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("play/gun.plist");
	m_BulletManage->Release();
}

void Player::didAccelerate(CCAcceleration *pAccelerationValue)
{
	if ( !m_MySelf )
		return;

	CCSprite * pShip = (CCSprite *)getChildByTag( t_Ship );
	if (NULL != pShip)
	{
		float fNewX = pShip->getPositionX() + pAccelerationValue->x*3.5f ;
		float fMinX = CCDirector::sharedDirector()->getVisibleOrigin().x+pShip->getContentSize().width/2;
		float fMaxX = CCDirector::sharedDirector()->getVisibleSize().width-pShip->getContentSize().width/2;
		FIX_POS(fNewX, fMinX, fMaxX);
		pShip->setPosition(CCPoint(fNewX, pShip->getPositionY()));
	}
}

void Player::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	if ( !m_MySelf )
		return;

	CCSetIterator iter = touches->begin();
	for(; iter != touches->end(); iter++)
	{
		CCTouch* pTouch = (CCTouch*)*iter;
		EmitGun(CCDirector::sharedDirector()->convertToGL( pTouch->getLocationInView() ));
	}
}

void Player::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
}

void Player::ccMousesMoved(CCSet *touches, CCEvent *pEvent)
{
	CCSetIterator iter = touches->begin();
	for(; iter != touches->end(); iter++)
	{
		CCTouch* pTouch = (CCTouch*)*iter;
		whirlGun(CCDirector::sharedDirector()->convertToGL( pTouch->getLocationInView() ));
	}
}

void Player::SetGunType(bool bAdd)
{
	if ( bAdd )
	{
		m_iGunType = m_iGunType % d_Gun_Count+1;
	}
	else
	{
		m_iGunType = (m_iGunType-1) % d_Gun_Count;
		m_iGunType = (0 >= m_iGunType) ? d_Gun_Count : m_iGunType;
	}

	char cBuffer[64]="";
	_snprintf(cBuffer, sizeof(cBuffer), "gun_%d_00000.png", m_iGunType);
	CCSprite * pShip = (CCSprite *)getChildByTag( t_Ship );
	CCSprite * pGun = (CCSprite *)pShip->getChildByTag( t_Gun );
	pGun->setDisplayFrame( CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( cBuffer ) );

	// 创建发炮动画
	CCArray *pGunArray = CCArray::create();
	for (int i=0; i<d_Gun_Frame_Count; i++)
	{
		char cBuffer[64]="";
		_snprintf(cBuffer, sizeof(cBuffer), "gun_%d_0000%d.png", m_iGunType, i);
		CCSpriteFrame* pGunFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( cBuffer );
		pGunArray->addObject( pGunFrame );
	}

	if (NULL != m_pGunAnimation)
	{
		m_pGunAnimation->release();
		m_pGunAnimation = NULL;
	}	
	m_pGunAnimation = CCAnimation::createWithSpriteFrames( pGunArray, 0.05f );
	m_pGunAnimation->retain();
}

void Player::EmitGun(CCPoint pt)
{
	// 设置炮旋转
	CCSprite * pShip = (CCSprite *)getChildByTag( t_Ship );
	CCSprite * pGun = (CCSprite *)pShip->getChildByTag( t_Gun );

	float angle = whirlGun( pt );

	CCLog("xy:(%f,%f),(%f,%f), angle:%f\r", pt.x, pt.y, pGun->getPosition().x, pGun->getPosition().y, angle);
	pGun->runAction( CCAnimate::create(m_pGunAnimation) );
	CCPoint ptBullet[PLAYER_COUNT] = {ccp(0, 0), ccp(0, 0), ccp(0, 0), ccp(1, 17)};
	ptBullet[m_PlayerPT].x += pShip->getPositionX(); 
	ptBullet[m_PlayerPT].y += pShip->getPositionY();
	m_BulletManage->Shoot(getPlayerPT(), pt, ptBullet[m_PlayerPT], pGun->getRotation(), false);

	CCLog("ZOrder: Bullet=%d, pShip=%d, pGun=%d", m_BulletManage->sharedBullet()->getZOrder(), pShip->getZOrder(), pGun->getZOrder());
}

float Player::whirlGun(CCPoint & pt)
{
	// 设置炮旋转
	CCSprite * pShip = (CCSprite *)getChildByTag( t_Ship );
	CCSprite * pGun = (CCSprite *)pShip->getChildByTag( t_Gun );

	float angle = (pt.y - pShip->getPosition().y)/(pt.x - pShip->getPosition().x);
	angle = atanf(angle)/M_PI*180;
	angle = (0 > angle) ? -(90 + angle) : 90 - angle;

	// 单击炮水平线以下，旋转90，-90
	if (pt.y < pShip->getPositionY())
	{
		angle = (pt.x >= pShip->getPositionX()) ? 90 : -90;
		pt.y = pShip->getPositionY()+15;
	}

	pGun->setRotation( angle );
	return angle;
}

void Player::OnRowingAnimation(float fTime)
{
	unschedule( schedule_selector(Player::OnRowingAnimation) );

	float fOffset = 110.0f;
	if (PLAYER_COUNT/2 <= m_PlayerPT)
		fOffset = -110.0f;

	CCSprite * pShip = (CCSprite *)getChildByTag( t_Ship );
	pShip->setVisible( true );
	pShip->setPositionY( pShip->getPositionY()+fOffset );

	CCActionInterval * pMove = CCMoveBy::create(1.5f, ccp(0, -fOffset));
	CCActionInstant * pComplete = CCCallFunc::create(this, callfunc_selector(Player::OnRowingCompleteAnimation));
	CCFiniteTimeAction * pShipAnimation = CCSequence::create(pMove, pComplete, NULL);
	pShip->runAction( pShipAnimation );
}

void Player::OnRowingCompleteAnimation()
{
	// 玩家划船进入，未到达捕鱼现场，除了炮与船其他信息暂隐藏。
	CCSprite *pChild = NULL;
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(getChildren(), pObj)
	{
		pChild = (CCSprite*)pObj;
		pChild->setVisible( true );
	}
}

CBulletManage * Player::getBulletManage()
{
	return m_BulletManage;
}

//////////////////////////////////////////////////////////////////////////

Player *PlayerManage::create(CCNode* pNode, int iPT, bool bMySelf/*=false*/)
{
	if (NULL == s_AllPlayer)
	{
		s_AllPlayer = CCDictionary::create();
		s_AllPlayer->retain();
	}

	if ( bMySelf )
		m_MySelfID = iPT;

	Player * pPlayer = new Player( iPT, bMySelf );

	s_AllPlayer->setObject(pPlayer, iPT);
	pNode->addChild( pPlayer );

	return pPlayer;
}

void PlayerManage::PlayerLeave( int iPT )
{
	s_AllPlayer->removeObjectForKey( iPT );

	if (0 >= s_AllPlayer->count())
		s_AllPlayer->release();
}

int PlayerManage::GetMyPlayerID()
{
	return m_MySelfID;
}

Player* PlayerManage::GetMyPlayer()
{
	if (-1 == m_MySelfID  ||  NULL == s_AllPlayer)
		return NULL;

	return (Player*)s_AllPlayer->objectForKey( m_MySelfID );
}
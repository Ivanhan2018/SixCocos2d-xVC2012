#include "Common.h"
#include "BulletSprite.h"
#include <math.h>
#ifdef WIN32
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
#endif

USING_NS_CC;

static unsigned int d_Max_Shoot_Delay = 1;									// 子弹发射间隔
static float d_Bullet_Speed = 400.0f;												// 子弹速度
int CBulletManage::m_FrameCacheCount = 0;								// 缓冲纹理引用计数

struct tagCoordinate
{
	CCNode *pNode;
	CCPoint ptTouch;

	tagCoordinate()
	{
		pNode = NULL;
	}
};

BulletSprite * BulletSprite::create(const char *pszName)
{
	BulletSprite * pBullet = new BulletSprite();
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pszName );
	if ( pBullet   &&   pBullet->initWithSpriteFrame( pFrame ))
	{
		//pBullet->autorelease();
		return pBullet;
	}
	CC_SAFE_DELETE(pBullet);
	return NULL;
}

void BulletSprite::FinishAnimation(CCNode* pSender, void* data)
{
	stopAllActions();
	setVisible( false );

	CCPoint * pTouch = (CCPoint *)data;

	// 鱼网
	CCArray *pArray = CCArray::create();
	for (int i=0; i<10; i++)
	{
		CCString *pStrBuffer = CCString::createWithFormat("FishNet_01_%05d.png", i);
		CCSpriteFrame * pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pStrBuffer->getCString() );
		pArray->addObject( pFrame );
	}
	CCActionInterval * pAnimate = CCAnimate::create( CCAnimation::createWithSpriteFrames( pArray, 0.05f ) );

	setAnchorPoint(CCPoint(0.5,0.5));

	// 结束自己
	CCActionInstant *pCallBack = CCCallFunc::create(this, callfunc_selector( BulletSprite::Release ));
	runAction( CCSequence::create(CCShow::create(), pAnimate, pCallBack, NULL) );
}

void BulletSprite::Release()
{
	//removeAllChildren();
	//removeFromParent();
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}

//////////////////////////////////////////////////////////////////////////
/// CBulletManage

CBulletManage * CBulletManage::Init(CCNode * pNode)
{	
	m_FrameCacheCount++;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("play/bulletNet.plist");
	CCString *pBatchName = CCString::createWithFormat( "play/bulletNet.png" );

	CBulletManage *pManage = new CBulletManage();
	pManage->m_LastShootTime = time(0);
	pManage->s_AllBullet = CCSpriteBatchNode::create( pBatchName->getCString() );
	pManage->setParentNode( pNode );
	pNode->addChild( pManage->s_AllBullet );

	return pManage;
}

void CBulletManage::Release()
{
	--m_FrameCacheCount;

	if (0 >= m_FrameCacheCount)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("play/bullet.plist");
	}

	s_AllBullet->removeAllChildrenWithCleanup(true);//removeAllChildren();
}

void CBulletManage::Shoot(int iPlayerID, CCPoint ptTouch, CCPoint ptShip, float fRotation, bool bReBound)
{
	if (NULL == s_AllBullet)
		CCAssert(0, "请先调用 CBulletManage::Init(...) 函数！");

	// 子弹间隔延迟控制
	unsigned int dwNow = time(0);
	if (dwNow < m_LastShootTime+d_Max_Shoot_Delay)
		return;
	m_LastShootTime = dwNow;

	CCPoint ptMuzzle = CountTwoPointOneCoordinate(ptTouch, ptShip, 150);	// 计算枪口位置
	BulletSprite * pBullet = BulletSprite::create( CCString::createWithFormat("bullet_01_00000.png")->getCString() );
	pBullet->autorelease();
	pBullet->setRotation( fRotation );
	pBullet->setIsCatching( false );
	pBullet->setIsReBound( bReBound );
	pBullet->setAnchorPoint(CCPoint(0.5, 1.0));
	pBullet->setPosition( ptMuzzle );
	pBullet->setPlayerID( iPlayerID );
	
	float fDistance = sqrtf( pow(ptTouch.x - ptMuzzle.x,  2)  + pow(ptTouch.y - ptMuzzle.y,  2) ) ; // 两点间距离
	float fTime = fDistance / d_Bullet_Speed; // 子弹需要时间
	CCActionInterval *pMove = CCMoveTo::create( fTime, ccp(ptTouch.x,ptTouch.y) );
	
	CCActionInstant * pCallBack = CCCallFuncND::create(pBullet, callfuncND_selector( BulletSprite::FinishAnimation ), (void *)&ptTouch);
	CCFiniteTimeAction * pBulletRun = CCSequence::create(pMove, pCallBack, NULL);
	pBullet->runAction( pBulletRun );

	CCArray* pArray = CCArray::create();
	for (int i=0; i<10; i++)
	{
		CCString * pStrBuffer = CCString::createWithFormat( "bullet_01_%05d.png", i);
		CCSpriteFrame* pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pStrBuffer->getCString() );
		pArray->addObject( pSpriteFrame );
	}
	pBullet->runAction( CCRepeatForever::create( CCAnimate::create( CCAnimation::createWithSpriteFrames( pArray, 0.1f ) ) ) );
	s_AllBullet->addChild( pBullet );
}

CCSpriteBatchNode * CBulletManage::sharedBullet()
{
	if (NULL == s_AllBullet)
		CCAssert(0, "请先调用 CBulletManage::Init(...) 函数！");

	return s_AllBullet;
}

CCPoint CBulletManage::CountTwoPointOneCoordinate(cocos2d::CCPoint ptSrc, cocos2d::CCPoint ptDes, float fLenght)
{
	if (ptSrc.x == ptDes.x  &&  ptSrc.y == ptDes.y)
		return ptDes;

	float fDistance = sqrtf( pow(ptSrc.x - ptDes.x,  2)  + pow(ptSrc.y - ptDes.y,  2) ) ; // 两点间距离
	float fT = (fDistance - fLenght) / fDistance;
	CCPoint ptResult;
	ptResult.x =  (1-fT) * ptSrc.x + fT * ptDes.x;
	ptResult.y =  (1-fT) * ptSrc.y + fT * ptDes.y;

	return ptResult;
}
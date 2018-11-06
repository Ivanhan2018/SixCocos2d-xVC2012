#include "BulletAndNetMgr.h"
#include "Ship.h"
#include "TableInfo.h"
#include "GameSkeletonMsgCode.h"
#include "SIX_ClientRoom.h"
#include "collisionLib.h"
#include "Ship.h"
#include "SIX_GlobalMgr.h"

CBulletAndNetMgr *g_pBulletMgr = NULL;

// -- 获得两点外指定一个射程的坐标位置
CCPoint getRangePT(float range, CCPoint TouchPT, CCPoint GunPT)
{
	float LocusAngle = atan2(TouchPT.y-GunPT.y, TouchPT.x-GunPT.x);
	float ptX = range*cos(LocusAngle);
	float ptY = range*sin(LocusAngle);
	return CCPoint(GunPT.x + ptX, ptY + GunPT.y);
}

CCPoint getRangePTEx(CCPoint TouchPT, CCPoint GunPT)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//  -- 取得斜角长度
	float rangeLenght = sqrt(winSize.width*winSize.width + winSize.height * winSize.height);
		
	return getRangePT(rangeLenght,TouchPT, GunPT);
}

// ----------------------------------------------
CBulletAndNet::CBulletAndNet()
{
}

CBulletAndNet::~CBulletAndNet()
{
}

CBulletAndNet *CBulletAndNet::BulletAndNetWithTexture(const char *filename)
{
    if(!filename)
	{
        SIXLog("in BulletAndNetWithTexture file == nil");
		return 0;
	}
	CBulletAndNet *pBulletAndNet = new CBulletAndNet();
	if (!pBulletAndNet)
		return 0;

	if (!pBulletAndNet->initWithSpriteFrameName(filename))
	{
		CC_SAFE_DELETE(pBulletAndNet);
		return 0;
	}
	pBulletAndNet->autorelease();
	pBulletAndNet->retain();
	return pBulletAndNet;
}

// 多线程中移除UI对象，必须要post消息给主线程，让主线程去cleanup/release
// 否则UI渲染线程中会有可能造成m_pobTextureAtlas为空(弱引用WR)从而造成崩溃。
// Cool.Cat
void CBulletAndNet::DelBullet(CCNode *node)
{
	CBulletAndNet *pBullet = dynamic_cast<CBulletAndNet*>(node);
	//pBullet->removeAllChildrenWithCleanup( true );
	//pBullet->removeFromParentAndCleanup( true );
	pBullet->Data.RemoveStatus = 1; // 子弹置结束标示
	//SIXLog("BULLET---- DelBullet %lld", pBullet->Data.BulletId);
	int realDel = (int)(pBullet->getUserData());
	CCAssert(realDel==1,"DelBullet.Error!");
	if (realDel==1)
		this->DelBulletWithResource();
}

void CBulletAndNet::DelBulletWithResource()
{
	CCAssert(this->Data.RemoveStatus!=2,"RemoveStatus.Error!");
	if (this->Data.RemoveStatus!=2)
	{
		this->removeAllChildrenWithCleanup( true );
		this->removeFromParentAndCleanup( true );
		this->Data.RemoveStatus = 2;
		g_pBulletMgr->mMyBullet.erase(this->Data.BulletId);
		this->release();
	}
}

void CBulletAndNet::FinishAnimation(CCNode *node)
{
	if (NULL == node)
		return;

	CBulletAndNet *pNode = dynamic_cast<CBulletAndNet *>( node );
	pNode->stopAllActions();
	pNode->setVisible( false );
	CShip *pShip = g_pShipMgr->getShip( pNode->Data.UserID );
	if (NULL == pShip)
		return;

	// 鱼网
	CCArray *pArray=CBulletAndNetMgr::createNetSpriteFrameArray();

	CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames( pArray, 0.05f );
	CCAnimate *pAnimate = CCAnimate::create( pAnimation );
	node->setAnchorPoint(CCPoint(0.5,0.5));

	// -- 结束自己
	CCArray *BulletActionArray = CCArray::create();
	BulletActionArray->addObject(CCShow::create());
	BulletActionArray->addObject(pAnimate);
	BulletActionArray->addObject(CCCallFuncN::create(node,callfuncN_selector(CBulletAndNet::DelBullet)));
	node->runAction( CCSequence::create(BulletActionArray));
}

// ----------------------------------------------
CBulletAndNetMgr::CBulletAndNetMgr()
{
	m_Max_Shoot_Delay = BULLET_SHOOT_DELAY;
	s_AllBullet = 0;
	s_LastBulletID = 0l;
	m_uiMaxBulletCount = 0;

	//mutex = new SIX_Mutex();
}

CBulletAndNetMgr::~CBulletAndNetMgr()
{
	Release();
}

void CBulletAndNetMgr::Init(CCNode *pNode)
{
	s_AllBullet = CCSpriteBatchNode::create(CCString::create("Scene/Game/GunBulletGold.png")->getCString());
	pNode->addChild(s_AllBullet);
	g_pShipMgr->getMySelfShip()->setNetType( g_pShipMgr->getMySelfShip()->mBulletType );

	//////////////////////////////////////////////////
	////add tuan 2013/6/12 debug
	//CCFileUtils::sharedFileUtils()->setResourceDirectory("iphonehd");
	//const char *pPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath( "config.xml" );
	//TiXmlDocument *pXmlDocument = new TiXmlDocument();
	//pXmlDocument->LoadFile( pPath );
	//CC_SAFE_DELETE_ARRAY(pPath);
	//TiXmlElement *pRoot = pXmlDocument->RootElement();
	//if (NULL == pRoot)
	//{
	//	assert( 0 );
	//	return;
	//}

	//TiXmlNode *pAddress = pRoot->FirstChild( "debug_number" );
	//if (NULL == pAddress)
	//{
	//	assert( 0 && "FirstChild(\"debug\")");
	//	return;
	//}

	//TiXmlAttribute *pAttribute = pAddress->ToElement()->FirstAttribute();
	//while ( pAttribute )
	//{
	//	const char *pName = pAttribute->Name();
	//	const char *pVal = pAttribute->Value();
	//	if (0 == STRCMP(pName, "number1")  &&  0<strlen( pVal ))
	//	{	
	//		g_fNumber1 = atof( pVal );
	//	}
	//	else if (0 == STRCMP(pName, "number2")  &&  0<strlen( pVal ))
	//	{
	//		g_fNumber2 = atof( pVal );
	//	}
	//	pAttribute = pAttribute->Next();
	//}
	//pXmlDocument->Clear();
	//CC_SAFE_DELETE( pXmlDocument );
	////add tuan 2013/6/12 debug end
	//////////////////////////////////////////////////
}

void CBulletAndNetMgr::Release()
{
	if (s_AllBullet)
	{
		s_AllBullet->removeAllChildrenWithCleanup(true);
		s_AllBullet->removeFromParentAndCleanup( true );
		s_AllBullet = NULL;
	}

	//SIX_Lock(g_pBulletMgr->mutex);
	//{
		mMyBullet.clear();
	//}

	s_LastBulletID = 0;
	//CC_SAFE_DELETE(mutex);
}

bool CBulletAndNetMgr::addOneBullet(long long UserID, TBulletID BulletID, CCPoint ptTouch, CCPoint ptGun, float fRotation, bool RepeatShoot,TGunGrade GunType)
{
	if (!s_AllBullet)
	{
		SIXLog("请先调用 CBulletAndNetMgr:Init(...) 函数！");
		return false;
	}

	CShip *pShip = g_pShipMgr->getShip( UserID );
	if (NULL == pShip)
		return false;

	// -- 子弹间隔延迟控制
	unsigned long long dwNow = SIX_Utility::GetInstance()->GetTickCount();
	if (!RepeatShoot && dwNow < pShip->m_ullastShootTime+ m_Max_Shoot_Delay)
		return false;

	if (pShip->m_UserID == g_pShipMgr->getMySelfShip()->m_UserID)
	{
		// 子弹超过上限
		if (mMyBullet.size() >= m_uiMaxBulletCount)
		{
			return false;
		}

		BulletID = g_pBulletMgr->generateBulletID( UserID );
	}

	//SIXLog("RepeatShoot[%d].diffTime[%lld]",RepeatShoot,dwNow-pShip->m_ullastShootTime);

	CCPoint savePtTouch = ptTouch;
	pShip->m_ullastShootTime = dwNow;

	// -- 计算枪口位置(子弹轨迹动作起点)
	CCPoint ptMuzzle = CountTwoPointOneCoordinate(ptTouch, ptGun, 120.0);
	CBulletAndNet *pBullet = CBulletAndNet::BulletAndNetWithTexture( CCString::createWithFormat("bullet_%02d_00000.png", pShip->mBulletType)->getCString() );
	// -- 加上射程后的子弹目的地(子弹轨迹动作终点，假设没有反弹)
	CCPoint RangePT = getRangePTEx(ptTouch, ptGun);
	pBullet->setRotation( fRotation );
	pBullet->setAnchorPoint(CCPoint(0.5, 1.0));
	pBullet->setPosition( ptMuzzle );
	pBullet->Data.BulletId = BulletID;
	pBullet->Data.UserID = UserID;
	pBullet->Data.Direction = g_pShipMgr->getPlayerDirection( UserID );
	pBullet->Data.IsCatching = false;
	pBullet->Data.ptLastPos = TPoint(ptGun.x,ptGun.y);
	pBullet->Data.mBulletType = pShip->mBulletType;

	if (0 == g_pShipMgr->getPlayerDirection(UserID))
	{
		pBullet->setFlipY( true );
		pBullet->setAnchorPoint(CCPoint(0.5, 0.0));
	}
	
	// -- 无射程
	bool noRange = true;
	if (noRange)
		ptTouch = RangePT;
	
	// -- 两点间距离
	float fDistance = sqrt( pow(ptTouch.x - ptMuzzle.x,  2)  + pow(ptTouch.y - ptMuzzle.y,  2) );
	// -- 子弹需要时间
	float fTime = fDistance / pShip->mBulletSpeed;
	CCMoveTo *pMove = CCMoveTo::create(fTime, ptTouch);
	// --CCLuaLog("ptMuzzle="..ptMuzzle.x.."/"..ptMuzzle.y..",RangePT="..RangePT.x.."/"..RangePT.y);
	CCArray *BulletActionArray = CCArray::create();
	BulletActionArray->addObject(pMove);

	//if (noRange)
	//{
	//	SIXLog("BUllet data ----- myself  delete  UserID=%lld, BulletID=%lld", pBullet->Data.UserID, pBullet->Data.BulletId);
	//	BulletActionArray->addObject(CCCallFuncN::create(pBullet,callfuncN_selector(CBulletAndNet::FinishAnimation)));
	//}

	CCFiniteTimeAction *pBulletRun = CCSequence::create(BulletActionArray);
	pBullet->runAction( pBulletRun );
	switch (GunType)
	{
	case 1:pBullet->setScale(0.6f);break;
	case 2:pBullet->setScale(0.7f);break;
	case 3:pBullet->setScale(0.8f);break;
	case 4:pBullet->setScale(0.9f);break;
	case 5:pBullet->setScale(1.0f);break;
	default:pBullet->setScale(1.0f);
	}

	// 子弹自身动画
    CCArray *pArray = createBulletSpriteFrameArray(pShip->mBulletType);
	pBullet->runAction( CCRepeatForever::create( CCAnimate::create( CCAnimation::createWithSpriteFrames( pArray, 0.5f ) ) ) );

	s_AllBullet->addChild( pBullet );

	// 开火音效
	// Cool.Cat
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(23,false);
	
	// 发送到服务端
	if (UserID == g_pShipMgr->getMySelfShip()->m_UserID )
	{
		pBullet->Data.BulletId = BulletID;
		savePtTouch = g_pShipMgr->CP2SP( savePtTouch );

		//
		SHOT_FIRE shotData(pBullet->Data.BulletId,UserID,GunType,pShip->mBulletType,GunType,0,TPoint(savePtTouch.x,savePtTouch.y),TPoint(ptGun.x,ptGun.y),false);
		int retv = SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_FIRE, &shotData, sizeof(SHOT_FIRE));
		if (retv!=0)
		{
			SIXLog("addOneBullet.send_data.Error[%d]",retv);
			return false;
		}
		//SIX_Lock(g_pBulletMgr->mutex);
		//{
		pair<BULLET_MAP::iterator,bool> status = mMyBullet.insert(pair<long long, CBulletAndNet *>( pBullet->Data.BulletId, pBullet ) );
		if (!status.second)
		{
			SIXLog("mMyBullet.BulletId[%lld].Already.Exists!",pBullet->Data.BulletId);
			return false;
		}
		//mMyBulletBak.insert(pair<long long, CBulletAndNet *>( pBullet->Data.BulletId, pBullet ) );
		//}
	}

	return true;
}

CCSpriteBatchNode *CBulletAndNetMgr::sharedBullet()
{
	return s_AllBullet;
}

//add by Ivan_han 20130816
CCArray* CBulletAndNetMgr::createNetSpriteFrameArray()
{
	CCArray *pArray = CCArray::create();
	for (int i=0; i<9; i++)
	{
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( 
			CCString::createWithFormat("explode_%05d.png",(i+1)*4+1)->getCString() );
		if (!pFrame)
			break;
		pArray->addObject( pFrame );
	}
	return pArray;
}

//add by Ivan_han 20130816
CCArray* CBulletAndNetMgr::createBulletSpriteFrameArray(int BulletType/*=2*/)
{
	CCArray *pArray = CCArray::create();
	for (int i=0; i<8; i++)
	{
		CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( 
			CCString::createWithFormat("bullet_%02d_%05d.png",BulletType,i)->getCString() );
		if (!pSpriteFrame)
			break;
		pArray->addObject( pSpriteFrame );
	}
	return pArray;
}

//add by Ivan_han 20130816
CCArray* CBulletAndNetMgr::createGunSpriteFrameArray(int nGunType)
{
	CCArray *gunAction = CCArray::create();
	for (int i=0; i<LOAD_MAX; i++)
	{
		CCSpriteFrame *SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("gun_%d_%05d.png",nGunType, i)->getCString());
		if (!SpriteFrame)
			break;
		gunAction->addObject( SpriteFrame );
	}
	return gunAction;
}

void CBulletAndNetMgr::onReflectionBullect(long long UserID, TBulletID iID, TPoint fCurPos, float fCurRotation, TPoint fMovePos, float fMoveTime, int reflectionCount, int reflectionMax)
{
	if (sharedBullet() == NULL)
		return;
	//if (UserID == g_pShipMgr->mMyUserID)
	//	return;

	if (UserID==SIX_PlayerMgr::GetInstance()->getMyUserIdx())
		return;
	
	CCArray *allBullet = sharedBullet()->getChildren();
	CBulletAndNet *pBullet = 0;
	
	//g_pShipMgr->AdjustmentPos(UserID, fCurPos);
	//g_pShipMgr->AdjustmentPos(UserID, fMovePos);
	
	// 子弹墙壁反射检测
	for (int index=0;index<(int)(allBullet->count());)
	{
		pBullet = dynamic_cast<CBulletAndNet*>( allBullet->objectAtIndex( index ) );
		++index;

		if (NULL != pBullet  &&  pBullet->Data.BulletId == iID)
		{
			if (reflectionCount>=reflectionMax && reflectionMax>0)
			{
				pBullet->setUserData((void*)1);
				pBullet->DelBullet( pBullet );
			}
			else if ( !pBullet->Data.IsCatching )
			{
				pBullet->stopAllActions();
				pBullet->setPosition( CCPoint(fCurPos.x, fCurPos.y) );
				pBullet->setRotation( fCurRotation );

				// 子弹移动动画
				//CCMoveTo *pMove = CCMoveTo::create(fMoveTime, CCPoint(fMovePos.x,fMovePos.y));
				CCMoveBy *pMove = CCMoveBy::create(fMoveTime, CCPoint(fMovePos.x,fMovePos.y));
				CCArray *BulletActionArray = CCArray::create();
				BulletActionArray->addObject(pMove);
				CCFiniteTimeAction *pBulletRun = CCSequence::create( BulletActionArray );
				pBullet->runAction( pBulletRun );

				// 子弹自身动画
				CCArray* pArray=createBulletSpriteFrameArray(pBullet->Data.mBulletType);
				pBullet->runAction( CCRepeatForever::create( CCAnimate::create( CCAnimation::createWithSpriteFrames( pArray, 0.5f ) ) ) );
			}
			break;
		}
	}
}

CCPoint CBulletAndNetMgr::CountTwoPointOneCoordinate(CCPoint ptSrc, CCPoint ptDes, float fLenght)
{
	if (ptSrc.x == ptDes.x  &&  ptSrc.y == ptDes.y)
		return ptDes;

	//  -- 两点间距离
	float fDistance = sqrt( pow((float)(ptSrc.x - ptDes.x),  (float)2.0)  + pow((float)(ptSrc.y - ptDes.y),  (float)2.0) );
	float fT = (fDistance - fLenght) / fDistance;
	
	return CCPoint((1-fT) * ptSrc.x + fT * ptDes.x,  (1-fT) * ptSrc.y + fT * ptDes.y);
}

TBulletID CBulletAndNetMgr::generateBulletID(long long nUserID)
{
	s_LastBulletID = (s_LastBulletID + 1l) % 1000l + nUserID * 1000l;
	return s_LastBulletID;
}

//void CBulletAndNetMgr::BulletReflectionDel(long long iID, int reflectionCount, int reflectionMax)
//{
//	// 子弹反弹 reflectionMax 次后消失
//	CCArray *allBullet = g_pBulletMgr->sharedBullet()->getChildren();
//	CBulletAndNet *pBullet = 0;
//
//	if (reflectionCount > reflectionMax  &&  0 < reflectionMax)
//	{
//		for (int index=0; index<allBullet->count(); )
//		{
//			pBullet = dynamic_cast<CBulletAndNet*>( allBullet->objectAtIndex( index++ ) );
//			if (NULL != pBullet  &&  pBullet->Data.BulletId == iID)
//			{
//				mMyBullet.erase( pBullet->Data.BulletId );
//				pBullet->DelBullet( pBullet );				
//				return;
//			}
//		}
//	}
//}

#ifdef WIN32
void CBulletAndNetMgr::AccelerometerKeyHook(unsigned int MSG,unsigned long wParam,long long lParam)
{
	if (WM_KEYUP != MSG)
		return;

	unsigned int Key = wParam;
	
	if (GetKeyState(VK_LSHIFT) < 0 ||  GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_SHIFT) < 0)
	{
		if (49<=Key && 54>=Key)
			Key = Key-49+1;
		else if (VK_NUMPAD1<=Key && VK_NUMPAD6>=Key)
			Key = Key-VK_NUMPAD1+1;
		
		if (1==Key)
			g_pShipMgr->getMySelfShip()->setNetType( 1 );
		else
			g_pShipMgr->getMySelfShip()->setNetType( 2 );
	}
}
#endif

// 子弹与墙壁碰撞刷新检测
void CBulletAndNetMgr::UpdateBullet()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSpriteBatchNode *pShareBullet = sharedBullet();
	if (!pShareBullet)
		return;
	CCArray *pAllBullet = pShareBullet->getChildren();
	unsigned int index = 0;
	CCSprite *pObject = NULL;
	CBulletAndNet *pBullet = NULL;
	while (index < pAllBullet->count())
	{
		pBullet = dynamic_cast<CBulletAndNet *>( pAllBullet->objectAtIndex( index++ ) );
		// 如果子弹不存在，或者子弹正在移除/已经移除，则不处理！
		if (!pBullet || (pBullet &&pBullet->Data.RemoveStatus!=0))
		{
			// 如果子弹不存在，有问题咯~
			if (!pBullet)
				SIXLog("UpdateBullet.pBullet.Nil");
		}
		else
		//if (NULL != pBullet && pBullet->Data.RemoveStatus==0)
		{
			// 其他玩家的子弹不处理
			if (pBullet->Data.UserID != SIX_PlayerMgr::GetInstance()->getMyUserIdx())
				continue;

			// 通过子弹反向查找玩家
			CShip *pShip = g_pShipMgr->getShip(pBullet->Data.UserID);
			if (!pShip)
			{
				// 找不到有可能玩家退出？
				SIXLog("UpdateBullet.getShip[%lld].Nil",pBullet->Data.UserID);
				continue;
			}

			// 自己不存在？
			CShip *pMyShip = g_pShipMgr->getMySelfShip();
			if (!pMyShip)
			{
				SIXLog("UpdateBullet.pMyShip.Nil");
				continue;
			}

			// 反向查找的玩家又不是自己？
			if (pShip->m_UserID!=pMyShip->m_UserID)
			{
				SIXLog("UpdateBullet.getShip[%lld/%lld].Error",pShip->m_UserID,pMyShip->m_UserID);
				continue;
			}

			// 子弹偏移超出屏幕范围
			if (pBullet->getPositionX() < 0.0f  ||  pBullet->getPositionX() >  winSize.width  ||  pBullet->getPositionY() < 0.0f  ||  pBullet->getPositionY() > winSize.height)
			{
				// 放前面来判断，只要超过最大反射上限就移除掉
				// Cool.Cat
				if (pBullet->Data.iReflectionCount>=pBullet->Data.iReflectionMax && pBullet->Data.iReflectionMax>0)
				{
					//SIX_Lock(g_pBulletMgr->mutex);
					//{
					//	mMyBullet.erase( pBullet->Data.BulletId );
					//}

					//SIXLog("UpdateBullet.BulletId[%lld].retainCount[%d]",pBullet->Data.BulletId,pBullet->retainCount());

					//// 检测子弹ID是否存在先~
					//// Cool.Cat
					//if (!this->IsBulletExists(pBullet->Data.BulletId))
					//{
					//	SIXLog("UpdateBullet.BulletId[%lld].NoExists.A",pBullet->Data.BulletId);
					//	continue;
					//}

					BULLET_REFLECTION reflection;
					reflection.llUserID = pBullet->Data.UserID;
					reflection.llID = pBullet->Data.BulletId;
					reflection.iReflectionMax = pBullet->Data.iReflectionMax;
					reflection.iReflectionCount = pBullet->Data.iReflectionCount;
					SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_REFLECTION, &reflection, sizeof(BULLET_REFLECTION));

					pBullet->setUserData((void*)1);
					pBullet->DelBullet( pBullet );
					continue;
				}
				CShip *pShip = g_pShipMgr->getShip( pBullet->Data.UserID );
				// 先计算边界碰撞点
				CCPoint StartPT = CCP(pBullet->Data.ptLastPos);
				CCPoint collidePT = segment_cross_Rect(CCPoint(0,0), CCPoint(0,winSize.height), CCPoint(winSize.width,winSize.height),
					CCPoint(winSize.width,0), CCPoint(StartPT.x, StartPT.y), CCPoint(pBullet->getPositionX(),pBullet->getPositionY()), SIX_GlobalMgr::GetInstance()->GetConfig()->debug_number2);//add tuan 2013/6/12 debug
				// 计算法线向量
				CCPoint Direction=getReflex(CCPoint(0,0), CCPoint(0,winSize.height),CCPoint(winSize.width,winSize.height),
					CCPoint(winSize.width,0),   CCPoint(StartPT.x, StartPT.y), CCPoint(pBullet->getPositionX(),pBullet->getPositionY()), SIX_GlobalMgr::GetInstance()->GetConfig()->debug_number2);//add tuan 2013/6/12 debug
				//CCLog("UpdateBullet----------- into pt startPT =("..StartPT.x..","..StartPT.y..") pBullet =("..pBullet.x..","..pBullet.y..") collidePT =("..collidePT.x..","..collidePT.y..") Direction =("..Direction.x..","..Direction.y..")")

				// 再计算下一个反射方向(反射输出向量)
				CCPoint newMoveBy = CCPoint(0,0);
				//反射输出向量的辐角主值，add by Ivan_han 20130816
				float argMoveBy = 2 * atan2(Direction.y, Direction.x) - atan2(collidePT.y-StartPT.y,collidePT.x-StartPT.x);
				float Rotation = 0.0;
				float fTime = 0.0;
				
				if (0.0f == Direction.x && 0.0f == Direction.y)
				{
					//collidePT.x=pBullet->getPositionX();
					//collidePT.y=pBullet->getPositionY();
					//if (0 > pBullet->getPositionX())
					//	collidePT.x=0;
					//else if (pBullet->getPositionY() >  winSize.width)
					//	collidePT.x=winSize.width;

					//if (0 > pBullet->getPositionY())
					//	collidePT.y=0;
					//else if (pBullet->getPositionY() > winSize.height)
					//	collidePT.y=winSize.height;

					//v3 =atan2(collidePT.y-StartPT.y,collidePT.x-StartPT.x)+M_PI;

					// 反弹角度错误，设置反弹次数达到最大值，让子弹消失
					pBullet->Data.iReflectionCount = pBullet->Data.iReflectionMax + 1;
					SIXLog("UpdateBullet.BulletId[%lld].iReflectionMax[%d]",pBullet->Data.BulletId,pBullet->Data.iReflectionMax);
				}
				else
				{
					newMoveBy = CCPoint(10000*cos(argMoveBy), 10000*sin(argMoveBy));
					float fDistance =sqrt( pow(newMoveBy.x,  (float)2.0)  + pow(newMoveBy.y,  (float)2.0) );
					fTime = fDistance / pShip->mBulletSpeed;	// 子弹需要时间
					CCMoveBy *pMove = CCMoveBy::create(fTime, newMoveBy);
					// CCMoveBy::create()调用了autorelease()，so计数要自增下，
					// 否则多线程中会被自动释放掉从而导致堆栈崩溃。
					// Cool.Cat
					//pMove->retain();
					int PlayUpDown = pBullet->Data.Direction;
					Rotation = (M_PI*(0==PlayUpDown ? 3 : 1)/2-atan2(newMoveBy.y, newMoveBy.x))*180/M_PI;
					// CCLuaLog("UpdateBullet----------- into pt BulletID="..CBulletAndNetMgr.s_BulletData[pBullet]["BulletId"].."  newPT =("..newPT.x..","..newPT.y..") ; PlayUpDown = "..PlayUpDown)

					pBullet->Data.iReflectionCount++;
					pBullet->Data.ptLastPos = TPoint(collidePT.x,collidePT.y);
					pBullet->setPosition( collidePT );
					pBullet->setRotation( Rotation );
					pBullet->stopAllActions();
					pBullet->runAction( pMove );

					//// 检测子弹ID是否存在先~
					//// Cool.Cat
					//if (!this->IsBulletExists(pBullet->Data.BulletId))
					//{
					//	SIXLog("UpdateBullet.BulletId[%lld].NoExists.B",pBullet->Data.BulletId);
					//	continue;
					//}

					// 发送到服务端
					BULLET_REFLECTION reflection;
					reflection.llUserID = pBullet->Data.UserID;
					reflection.llID = pBullet->Data.BulletId;
					reflection.fCurRotation = Rotation;
					reflection.fMoveTime = fTime;
					reflection.iReflectionMax = pBullet->Data.iReflectionMax;
					reflection.iReflectionCount = pBullet->Data.iReflectionCount;

					collidePT = g_pShipMgr->CP2SP( collidePT );
					newMoveBy = g_pShipMgr->CD2SD( newMoveBy );
					reflection.fCurPos = TPoint(collidePT.x, collidePT.y);
					reflection.fMovePos = TPoint(newMoveBy.x, newMoveBy.y);

					SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_REFLECTION, &reflection, sizeof(BULLET_REFLECTION));
					//BulletReflectionDel(reflection.llID, pBullet->Data.iReflectionCount, pBullet->Data.iReflectionMax);
				}
			}
		}
	}	// end while
}

//bool CBulletAndNetMgr::IsBulletExists(TBulletID bulletId)
//{
//	BULLET_MAP::iterator iter = mMyBulletBak.find(bulletId);
//	if (iter!=mMyBulletBak.end())
//		return true;
//	return false;
//}
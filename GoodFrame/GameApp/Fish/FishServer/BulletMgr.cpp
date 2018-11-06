#include "BulletMgr.h"
#include "FishTable.h"
#include "GameSkeletonMsgCode.h"
#include "./EndlessLoopGuard.h"	// 死循环守护

const int g_nMaxBulletCount = 200;				// 子弹同时存在最大数目 50

#define USELOCK 1	// 1 表示子弹要加锁，0 表示子弹不加锁

CBulletMgr::CBulletMgr(void) : m_uiBulletMaxCount(40)
{
	m_pBulletPool = new CLightweightPool<BULLET_DATA>("BulletPool", g_nMaxBulletCount); 
}

CBulletMgr::~CBulletMgr(void)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	vector<BULLET_DATA *> vBullet;
	BULLET_DATA * pBulletData = NULL;
	int nRes = 0;

	{
		#if USELOCK
			CThreadGuardWrite guard(&m_lock);
		#endif

		MAP_BULLET::iterator mIt = m_mapBullet.begin();
		while ( mIt != m_mapBullet.end() )
		{
			if ( NULL != mIt->second)
			{
				vBullet.push_back( mIt->second );
				m_mapBullet.erase( mIt );
				mIt = m_mapBullet.begin();
				continue;
			}
			++mIt;
		}
	}

	vector<BULLET_DATA *>::iterator vIt = vBullet.begin();
	for (; vIt != vBullet.end(); ++vIt)
	{
		BULLET_DATA * pBulletData = (BULLET_DATA *)*vIt;
		if (NULL != pBulletData)
		{
			BOOL bResult = m_pBulletPool->recycle( pBulletData );
			assert(TRUE==bResult);
			if (FALSE == bResult)
				nRes = 20;
		}
	}
	vBullet.clear();
}

/// 增加子弹
int CBulletMgr::addBullet(SHOT_FIRE* pReal)
{
	BULLET_DATA *pBulletData = NULL;
	BOOL bResult = m_pBulletPool->retrieve( &pBulletData);
	assert(TRUE==bResult && pBulletData);
	if (FALSE == bResult  ||  NULL == pBulletData)
	{
		return 20;
	}
	memset(pBulletData, 0, sizeof(BULLET_DATA));

	pBulletData->SetFire( pReal );
	pBulletData->nCurrTime = (unsigned int) time(NULL);

	#if USELOCK
		CThreadGuardWrite guard(&m_lock);
	#endif
	m_mapBullet.insert( pair<long long, BULLET_DATA*>(pReal->iID, pBulletData) );
	return 0;
}

/// 删除子弹
int CBulletMgr::RemoveBullet(long long llID)
{
	BULLET_DATA *pBulletData = NULL;
	
	{
		#if USELOCK
			CThreadGuardWrite guard(&m_lock);
		#endif

		MAP_BULLET::iterator mIt = m_mapBullet.find( llID );
		if ( mIt != m_mapBullet.end() )
		{
			pBulletData = (BULLET_DATA *)mIt->second;
			m_mapBullet.erase( llID );
		}
	}
	if (NULL != pBulletData)
	{
		BOOL bResult = m_pBulletPool->recycle( pBulletData );
		assert(TRUE==bResult && pBulletData);
		if (FALSE == bResult  ||  NULL == pBulletData)
			return 20;
	}
	return 0;
}

/// 反射子弹
BOOL CBulletMgr::ReflectionBullet(BULLET_REFLECTION* pReal)
{
	BOOL bCanReflection = TRUE;
#if USELOCK
	CThreadGuardWrite guard(&m_lock);
#endif
	MAP_BULLET::iterator mIt = m_mapBullet.find( pReal->llID );
	if (m_mapBullet.end() != mIt)
	{
		mIt->second->SetReflection( pReal );
		if ( mIt->second->Reflection.iReflectionCount >= BULLET_REFLECTION_MAX)
		{
			bCanReflection = FALSE;
		}

		pReal->iReflectionCount = (++mIt->second->Reflection.iReflectionCount);
		pReal->iReflectionMax = BULLET_REFLECTION_MAX;
	}
	else
	{// 子弹不存在
		bCanReflection = FALSE;
	}
	return bCanReflection;
}

int CBulletMgr::GetBulletCount(long long llUserID)
{
	#if USELOCK
		CThreadGuardWrite guard(&m_lock);
	#endif

	int iCount=0;
	MAP_BULLET::iterator mIt = m_mapBullet.begin();
	for (; mIt != m_mapBullet.end(); ++mIt)
	{
		if (mIt->second->Fire.iUserID == llUserID)
		{
			++iCount;
		}
	}

	return iCount;
}

int CBulletMgr::GetBulletMaxCount()
{
	return m_uiBulletMaxCount;
}

/// 清空玩家子弹（退出时触发）
int CBulletMgr::ClearBullet(long long lUserID)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	vector<BULLET_DATA *> vBullet;
	BULLET_DATA * pBulletData = NULL;
	int nRes = 0;

	{
		#if USELOCK
			CThreadGuardWrite guard(&m_lock);
		#endif
		MAP_BULLET::iterator mIt = m_mapBullet.begin();
		while ( mIt != m_mapBullet.end() )
		{
			if ( NULL != mIt->second  &&  lUserID == mIt->second->Fire.iUserID)
			{
				vBullet.push_back( mIt->second );
				m_mapBullet.erase( mIt );
				mIt = m_mapBullet.begin();
				continue;
			}
			++mIt;
		}
	}

	vector<BULLET_DATA *>::iterator vIt = vBullet.begin();
	for (; vIt != vBullet.end(); ++vIt)
	{
		BULLET_DATA * pBulletData = (BULLET_DATA *)*vIt;
		if (NULL != pBulletData)
		{
			BOOL bResult = m_pBulletPool->recycle( pBulletData );
			assert(TRUE==bResult);
			if (FALSE == bResult)
				nRes = 20;
		}
	}
	vBullet.clear();
	return nRes;
}

/// 子弹群发（玩家进入时触发）
void CBulletMgr::ShootAllBullet(int iSeatNo)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	#if USELOCK
		CThreadGuardRead guard(&m_lock);
	#endif

	MAP_BULLET::iterator mIt = m_mapBullet.begin();
	for ( ; mIt != m_mapBullet.end(); ++mIt )
	{
		if (NULL == mIt->second)
			continue;
		((CFishTable *)m_pTable)->send_data(iSeatNo, TABLE_MAIN, TABLE_SUB_FIRE, (BYTE*)(&mIt->second->Fire), sizeof(mIt->second->Fire));
		((CFishTable *)m_pTable)->send_data(iSeatNo, TABLE_MAIN, TABLE_SUB_REFLECTION, (BYTE*)(&mIt->second->Reflection), sizeof(mIt->second->Reflection));
	}
}

TGunGrade CBulletMgr::IsExistBullet(long long llBulletID)
{
#if USELOCK
	CThreadGuardRead guard(&m_lock);
#endif
	TGunGrade GunGrade = 0;
	MAP_BULLET::iterator mIt = m_mapBullet.find(llBulletID);
	if (m_mapBullet.end() != mIt)
	{// 炮弹存在
		GunGrade = mIt->second->Fire.iGunType;
	}

	return GunGrade;
}
// 检查子弹超时
void CBulletMgr::CheckBulletOverTime()
{
	vector<TBulletID> vecBullet;
	unsigned int nTime=(unsigned int)time(NULL);
	MAP_BULLET::iterator mIt = m_mapBullet.begin();
	for (; mIt != m_mapBullet.end(); ++mIt)
	{
		unsigned int nSpaceTime = nTime-mIt->second->nCurrTime;
		if (nSpaceTime>FIER_BULLET_OVERTIME)
		{
			TBulletID lBulletID=mIt->second->Fire.iID;
			vecBullet.push_back(lBulletID);
		}
	}

	for (int i=0;i<vecBullet.size();++i)
	{
		TBulletID nlBulletId=vecBullet.at(i);
		RemoveBullet(nlBulletId);
	}
}
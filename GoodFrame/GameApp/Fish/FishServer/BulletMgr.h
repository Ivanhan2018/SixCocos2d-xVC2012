#ifndef __BULLET_MGR_H__
#define __BULLET_MGR_H__
#pragma once

#include "PartMgr.h"
#include "LightweightPool.h"
#include "../GameMsg/ProFish.h"

// 子弹管理
class CBulletMgr : public CPartMgr
{
public:
	CBulletMgr(void);
	~CBulletMgr(void);

	/// 增加子弹
	int addBullet(SHOT_FIRE* pReal);
	/// 删除子弹
	int RemoveBullet(long long llID);
	/// 反射子弹
	BOOL ReflectionBullet(BULLET_REFLECTION* pReal);
	/// 已发射子弹
	int GetBulletCount(long long llUserID);
	int GetBulletMaxCount();

	/// 清空某个玩家子弹（退出时触发）
	int ClearBullet(long long lUserID);

	/// 子弹群发（玩家进入时触发）
	void ShootAllBullet(int iSeatNo);

	// 检查炮弹是否存在<0表示炮弹不存在，非0表示炮的等级>
	TGunGrade IsExistBullet(long long llBulletID); // add  by Ivan_han 20130723
	//检查子弹超时
	void CheckBulletOverTime();

private:
	CLightweightPool<BULLET_DATA> *m_pBulletPool;			///< 子弹池
	MAP_BULLET			m_mapBullet;						///< 子弹数据
	const unsigned int	m_uiBulletMaxCount;					///< 单个玩家子弹允许最大数目
};

#endif


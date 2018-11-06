#ifndef __BULLET_MGR_H__
#define __BULLET_MGR_H__
#pragma once

#include "PartMgr.h"
#include "LightweightPool.h"
#include "../GameMsg/ProFish.h"

// �ӵ�����
class CBulletMgr : public CPartMgr
{
public:
	CBulletMgr(void);
	~CBulletMgr(void);

	/// �����ӵ�
	int addBullet(SHOT_FIRE* pReal);
	/// ɾ���ӵ�
	int RemoveBullet(long long llID);
	/// �����ӵ�
	BOOL ReflectionBullet(BULLET_REFLECTION* pReal);
	/// �ѷ����ӵ�
	int GetBulletCount(long long llUserID);
	int GetBulletMaxCount();

	/// ���ĳ������ӵ����˳�ʱ������
	int ClearBullet(long long lUserID);

	/// �ӵ�Ⱥ������ҽ���ʱ������
	void ShootAllBullet(int iSeatNo);

	// ����ڵ��Ƿ����<0��ʾ�ڵ������ڣ���0��ʾ�ڵĵȼ�>
	TGunGrade IsExistBullet(long long llBulletID); // add  by Ivan_han 20130723
	//����ӵ���ʱ
	void CheckBulletOverTime();

private:
	CLightweightPool<BULLET_DATA> *m_pBulletPool;			///< �ӵ���
	MAP_BULLET			m_mapBullet;						///< �ӵ�����
	const unsigned int	m_uiBulletMaxCount;					///< ��������ӵ����������Ŀ
};

#endif


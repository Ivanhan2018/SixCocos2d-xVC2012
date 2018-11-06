/*********************************************************
Name：BulletAndNetManage
Desc：子弹与网格管理器
Auth：lijianming
*********************************************************/
#pragma once
#include "cocos2d.h"
#include <SIX_Typedef.h>
#include "TableInfo.h"
#include "ProFish.h"
#include <SIX_Lock.h>

USING_NS_CC;

#define DELETE_BULLET_TASK	"delete_bullet_task"

/// 子弹数据结构
typedef struct tagBulletDataInfo
{
	tagBulletDataInfo()
	{
		//ZeroMemory(this, sizeof(*this));
		memset(this,0,sizeof(*this));
		iReflectionMax = BULLET_REFLECTION_MAX;
	}
	bool IsCatching;				///< 是否捕获
	int RemoveStatus;				///< 子弹是否已经移除(0=未移除，1=正在移除，2=已经移除)
	int Direction;						///< 子弹所属玩家方向（0上，2下）
	int mBulletType;				///< 子弹类型
	int iReflectionCount;			///< 反射次数
	int iReflectionMax;			///< 反射最大次数
	TBulletID BulletId;			///< 子弹ID
	long long UserID;				///< 玩家 ID
	TPoint ptLastPos;			///< 子弹起始位置（反射后会更新），反射前是枪口的位置（子弹运动轨迹的起点）
}BULLET_BIND_DATA;

class CBulletAndNet;
typedef map<TBulletID, CBulletAndNet *> BULLET_MAP;

/// 子弹与鱼网类
class CBulletAndNet:public CCSprite
{
public:
	CBulletAndNet();
	~CBulletAndNet();
public:
	//内部使用精灵框帧创建子弹精灵
	static CBulletAndNet *BulletAndNetWithTexture(const char *filename);
	void DelBullet(CCNode *node);
	void DelBulletWithResource();
	void FinishAnimation(CCNode *node);

	BULLET_BIND_DATA	Data;			/// < 子弹数据
};

// 子弹与鱼网管理类
class CBulletAndNetMgr : public TSingleton<CBulletAndNetMgr>
{
public:
	CBulletAndNetMgr();
	~CBulletAndNetMgr();

public:
	void Init(CCNode *pNode);
	void Release();
	bool addOneBullet(long long UserID, TBulletID BulletID, CCPoint ptTouch, CCPoint ptGun, float fRotation, bool RepeatShoot,TGunGrade GunType);
	void UpdateBullet();
	CCSpriteBatchNode *sharedBullet();
	void onReflectionBullect(long long UserID, TBulletID iID, TPoint fCurPos, float fCurRotation, TPoint fMovePos, float fMoveTime, int reflectionCount, int reflectionMax);
	//add by Ivan_han 20130816
	static CCArray* createNetSpriteFrameArray();
	static CCArray* createBulletSpriteFrameArray(int BulletType=2);
	static CCArray* createGunSpriteFrameArray(int nGunType);
#ifdef WIN32
	void AccelerometerKeyHook(unsigned int MSG,unsigned long wParam,long long lParam);
#endif
	//bool IsBulletExists(TBulletID);
protected:
	CCPoint CountTwoPointOneCoordinate(CCPoint ptSrc, CCPoint ptDes, float fLenght);
	TBulletID generateBulletID( long long nUserID );
	//void BulletReflectionDel(long long iID, int reflectionCount, int reflectionMax);
public:
	unsigned int m_uiMaxBulletCount;		///< 子弹允许最大数目
	int m_Max_Shoot_Delay;						///< 子弹发射间隔
	TBulletID s_LastBulletID;				///< 上次发射子弹ID

	CCSpriteBatchNode *s_AllBullet;
	BULLET_MAP mMyBullet;
	//SIX_Mutex *mutex;
};

extern CBulletAndNetMgr *g_pBulletMgr;
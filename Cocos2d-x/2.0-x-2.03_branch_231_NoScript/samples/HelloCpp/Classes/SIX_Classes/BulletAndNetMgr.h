/*********************************************************
Name��BulletAndNetManage
Desc���ӵ������������
Auth��lijianming
*********************************************************/
#pragma once
#include "cocos2d.h"
#include <SIX_Typedef.h>
#include "TableInfo.h"
#include "ProFish.h"
#include <SIX_Lock.h>

USING_NS_CC;

#define DELETE_BULLET_TASK	"delete_bullet_task"

/// �ӵ����ݽṹ
typedef struct tagBulletDataInfo
{
	tagBulletDataInfo()
	{
		//ZeroMemory(this, sizeof(*this));
		memset(this,0,sizeof(*this));
		iReflectionMax = BULLET_REFLECTION_MAX;
	}
	bool IsCatching;				///< �Ƿ񲶻�
	int RemoveStatus;				///< �ӵ��Ƿ��Ѿ��Ƴ�(0=δ�Ƴ���1=�����Ƴ���2=�Ѿ��Ƴ�)
	int Direction;						///< �ӵ�������ҷ���0�ϣ�2�£�
	int mBulletType;				///< �ӵ�����
	int iReflectionCount;			///< �������
	int iReflectionMax;			///< ����������
	TBulletID BulletId;			///< �ӵ�ID
	long long UserID;				///< ��� ID
	TPoint ptLastPos;			///< �ӵ���ʼλ�ã���������£�������ǰ��ǹ�ڵ�λ�ã��ӵ��˶��켣����㣩
}BULLET_BIND_DATA;

class CBulletAndNet;
typedef map<TBulletID, CBulletAndNet *> BULLET_MAP;

/// �ӵ���������
class CBulletAndNet:public CCSprite
{
public:
	CBulletAndNet();
	~CBulletAndNet();
public:
	//�ڲ�ʹ�þ����֡�����ӵ�����
	static CBulletAndNet *BulletAndNetWithTexture(const char *filename);
	void DelBullet(CCNode *node);
	void DelBulletWithResource();
	void FinishAnimation(CCNode *node);

	BULLET_BIND_DATA	Data;			/// < �ӵ�����
};

// �ӵ�������������
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
	unsigned int m_uiMaxBulletCount;		///< �ӵ����������Ŀ
	int m_Max_Shoot_Delay;						///< �ӵ�������
	TBulletID s_LastBulletID;				///< �ϴη����ӵ�ID

	CCSpriteBatchNode *s_AllBullet;
	BULLET_MAP mMyBullet;
	//SIX_Mutex *mutex;
};

extern CBulletAndNetMgr *g_pBulletMgr;
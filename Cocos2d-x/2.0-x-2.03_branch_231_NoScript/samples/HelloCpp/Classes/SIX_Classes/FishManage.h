/*********************************************************
Name��CFishMgr
Desc���㾫������õ��ľ���֡�Ĺ���
Auth��Ivan_han@2013/4/20 14:15:17
*********************************************************/
#pragma once
#include "cocos2d.h"
#include <SIX_Typedef.h>
#include <math.h>
#include "ProFish.h"
#include <SIX_Thread.h>
#include <SIX_Lock.h>
#include <SIX_TList.h>
#include <SIX_Common.h>

USING_NS_CC;

class SIX_SceneGame;
class CFishMgr;
class CFish;

//���������ݵĽ��ա����Ҫ�õ���add by Ivan_han 20130614
struct FishListInfo
{
	FishListInfo(){memset(this, 0, sizeof(*this));}
	Rsp_AddOneFish_List *pReal;
	TFishGroupID FishGroupID;
	unsigned RecvCount;
};

typedef struct tagFishDataInfo{
	CFishMgr *pFishMgr;
#ifdef USING_FISH_SHADOW
	CFish *pShadow;
#endif
	bool isCatch;
	TFishID uld;
	TFishMoveStatus FishMoveStatus;
	TBuildTraceTime BuildTraceTime;
	// <100=��
	// >100=ը��
	TFishKind fishKind;
	GLubyte Opacity;				///< ���ʼ��ɫ

	tagFishDataInfo()
	{
		isCatch = false;
		fishKind = 0;
	}
} FISH_DATA;
typedef map<CFish*,FISH_DATA*> FISH_MAP;

class CFish : public CCSprite
{
public:
	CFish();
	~CFish();
public:
	static CFish *spriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
	static CFish *spriteWithSpriteFrameName(const char *pszSpriteFrameName);
	bool randomCatch(int level);
	void SpriteRemoveCallBack(CCNode *node);
	void moveWithParabola(CCPoint startP,CCPoint endP,float startAngle,float endAngle,float time,TFishID uld=0);
	void moveWithBezier3(float duration,float InitElapsed,CCPoint p1,CCPoint p2,CCPoint p3,TFishID uld=0);
	void addPath(int pathType,float duration,float InitElapsed,CCPoint arg1,CCPoint arg2,CCPoint arg3,TFishID uld=0);
	void DieAnimation(const FISH_DATA * pFishData);
};

class CFishMgr : public TSingleton<CFishMgr>
{
public:
	CFishMgr();
	~CFishMgr();
public:
	void Init(SIX_SceneGame *,CCNode *pNode,int poolStep=500);
	void FishPoolExpansion();
	void LoadSeaGrass();
	void LoadShell();
	void LoadStarFish();
	void LoadBatchFish();
	void LoadBatchBoom();
	void LoadHitBox();
	CCSpriteBatchNode *sharedSeaGrass();
	CCSpriteBatchNode *sharedShell();
	CCSpriteBatchNode **sharedStarFish();
	CCSpriteBatchNode **sharedFish();
	CCSpriteBatchNode **sharedBomb();
	static int LoadHitBoxCallBack(void *);
	static int CheckThreading(void *);
	void WaitForCheckThread();
	void Release();
	// ��ӵ���
	void addOneFish(TFishID uld,TFishKind fishType,TFishPathType pathType,float duration,TFishMoveStatus FishMoveStatus,float InitElapsed,TBuildTraceTime BuildTraceTime,CCPoint startP,CCPoint arg1,CCPoint arg2,CCPoint arg3);
	// ������/ը��ID���Ҷ�Ӧ����������
	static int GetIndexFromArray(int idx,bool IsFish);
	// ������Ҳ������ը��,vHitFishID��������������ID,vDeadFishID�������񵽵���ID
	void CaptureFish(long long llUserID, long long llBulletID,const vector<TFishID> &vHitFishID,vector<TFishID> &vDeadFishID,TFallIntegral FallIntegral,TGunGrade GunGrade,TFishID DeadFullScreenBombFishID);
	/*
		��켣���٣�add by Ivan_han 20130621
		��켣״̬<0����״̬��1��켣�����Ҳ��ɲ���״̬��2��켣�����䲻ͬ�����ɲ���״̬>�����㳡��->���󳡾�ʱ�õ���
		�ͻ�����CCSpeedʵ����켣����Ч������ʱ�ͻ��˵�����V>1�ı������У��ͻ�����켣�������ڷ����������٣��Ҳ�ͬ�ͻ��˿��ܿ�����ͬ���ļ�����켣
		Rsp_AddOneFish::FishMoveStatus=1�������������ã���������켣�����·��󣬺�����ӵ���Ҳ��ܲ�����ٵ���켣��
		Rsp_AddOneFish::FishMoveStatus=2���ͻ������ã���������켣�����·����Ƚ����ӵ�����յ���ִ�м��������в�ͬ���ӳ�ֵ��û�б�Ҫ������Щ�ӳ٣���Щ��ҿ��Բ�����ٵ���켣��
	*/
	void SpeedUpOneFish(TFishID uld);
	void SpeedUpAllFish();
	//���ڻָ�ʱͬ�������λ�ã�add by Ivan_han 20130701
	void CheckAllFish();

	CFish *GetFishFromMap(TFishID fishId,FISH_DATA**pFishDataDst);

protected:
	void RestoreFish(CCNode *node);
	SIX_Thread *mCheckThread;
	bool m_NeedExitCheckThread;
	SIX_SceneGame *mScene;
public:
	CCNode *__pNode;
	// -- ��Я������
	FISH_MAP mFishData;
	/*
	--1-10��ը����Ӧ1-10���㣬11��ը����ȫ��ը����12��ը������Ϻը��
	13��ը���ǽ���ը����34,35,37��ը���Ǵ���Ԫը����40,46,48��ը���Ǵ���ϲը��
	*/
	CCSpriteBatchNode *s_AllFish[17];
	CCSpriteBatchNode *s_AllBomb[19];
	//CCSpriteBatchNode *s_DeadBomb;
	CCSpriteBatchNode *s_AllStarFish[3];
	CCSpriteBatchNode *s_AllShell;
	CCSpriteBatchNode *s_AllSeaGrass;
	bool m_WaitForHBoxThread;
	int m_LoadHBoxProgress;
	//SIX_Mutex *mutex;
	bool m_WaitForCheckThread;

	SIX_TList<CFish*> *m_FishPool;
	int m_poolStep;
};

extern CFishMgr *g_FishMgr;
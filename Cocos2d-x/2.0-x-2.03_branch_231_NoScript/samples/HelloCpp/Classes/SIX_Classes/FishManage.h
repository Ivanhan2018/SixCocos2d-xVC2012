/*********************************************************
Name：CFishMgr
Desc：鱼精灵对象用到的精灵帧的管理
Auth：Ivan_han@2013/4/20 14:15:17
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

//鱼阵大包数据的接收、组包要用到，add by Ivan_han 20130614
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
	// <100=鱼
	// >100=炸弹
	TFishKind fishKind;
	GLubyte Opacity;				///< 鱼初始颜色

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
	// 添加单鱼
	void addOneFish(TFishID uld,TFishKind fishType,TFishPathType pathType,float duration,TFishMoveStatus FishMoveStatus,float InitElapsed,TBuildTraceTime BuildTraceTime,CCPoint startP,CCPoint arg1,CCPoint arg2,CCPoint arg3);
	// 根据鱼/炸弹ID查找对应的数组索引
	static int GetIndexFromArray(int idx,bool IsFish);
	// 其他玩家捕获鱼或炸弹,vHitFishID解析网碰到的鱼ID,vDeadFishID解析捕获到的鱼ID
	void CaptureFish(long long llUserID, long long llBulletID,const vector<TFishID> &vHitFishID,vector<TFishID> &vDeadFishID,TFallIntegral FallIntegral,TGunGrade GunGrade,TFishID DeadFullScreenBombFishID);
	/*
		鱼轨迹加速，add by Ivan_han 20130621
		鱼轨迹状态<0正常状态，1鱼轨迹加速且不可捕获状态，2鱼轨迹加速虽不同步但可捕获状态>，单鱼场景->鱼阵场景时用到，
		客户端用CCSpeed实现鱼轨迹加速效果，此时客户端的鱼以V>1的倍速运行，客户端鱼轨迹对象先于服务器端销毁，且不同客户端可能看到不同步的加速鱼轨迹
		Rsp_AddOneFish::FishMoveStatus=1（服务器端设置）：加速鱼轨迹命令下发后，后进桌子的玩家不能捕获加速的鱼轨迹。
		Rsp_AddOneFish::FishMoveStatus=2（客户端设置）：加速鱼轨迹命令下发后，先进桌子的玩家收到并执行加速命令有不同的延迟值，没有必要处理这些延迟，这些玩家可以捕获加速的鱼轨迹。
	*/
	void SpeedUpOneFish(TFishID uld);
	void SpeedUpAllFish();
	//窗口恢复时同步旧鱼的位置，add by Ivan_han 20130701
	void CheckAllFish();

	CFish *GetFishFromMap(TFishID fishId,FISH_DATA**pFishDataDst);

protected:
	void RestoreFish(CCNode *node);
	SIX_Thread *mCheckThread;
	bool m_NeedExitCheckThread;
	SIX_SceneGame *mScene;
public:
	CCNode *__pNode;
	// -- 鱼携带数据
	FISH_MAP mFishData;
	/*
	--1-10号炸弹对应1-10号鱼，11号炸弹是全屏炸弹，12号炸弹是龙虾炸弹
	13号炸弹是金龙炸弹，34,35,37号炸弹是大三元炸弹，40,46,48号炸弹是大四喜炸弹
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
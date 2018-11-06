#pragma once
#include"../GameMsg/ProFish.h"
#include<stack>
using namespace std;

class CFishTraceMgr;
class CFishTable;
class FishStateMgr;

//发鱼状态
enum enFishState
{
	enFishState_Capture,//捕渔期(非剧情模式)
	enFishState_OffFish,//休渔期(剧情模式)
	enFishState_Max,
};

//////////////////////////////////////////////////////////////////////////
//发鱼状态
struct IFishState
{
	virtual ~IFishState(){}
	virtual bool Enter()=0;
	virtual bool Leave()=0;
	virtual enFishState GetState()=0;
	// 桌子定时器响应
	virtual int OnTableTimer(int iTableNo, int iIDEvent)=0;
};


//捕渔期(非剧情模式)
class CaptureFishState : public IFishState
{
public:
	CaptureFishState(FishStateMgr *pFishStateMgr=NULL);
	~CaptureFishState();
	bool Enter();
	bool Leave();
	enFishState GetState();
	//捕渔期最后6秒不发鱼
	bool IsFish()const;
	//add by Ivan_han 20130828
	/*
		分为三种情况：
		返回值为0：产生单鱼/鱼群
		返回值为1，不产生单鱼/鱼群,但捕渔期不结束
		返回值为2，不产生单鱼/鱼群,且捕渔期结束
    */
	int IsFishEx()const;
	/*
		暂时只发TFishPathType=5的单鱼/鱼群轨迹
		type表示单鱼/鱼群类型：1小鱼/2大鱼/3炸弹鱼/4列阵鱼群/5列队鱼群
	*/
	TFishKind AddFish(int type);
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	FishStateMgr *m_pFishStateMgr;
	unsigned long long m_EnterTime;
};


//休渔期(剧情模式)
class OffFishState : public IFishState
{
public:
	//add by Ivan_han 20130823
	//鱼阵序列中的一个鱼阵
	struct TFishGroupTypeSeqElem
	{
		TFishGroupType FishGroupType;
		long long RelativeBuildTime;
	};
	OffFishState(FishStateMgr *pFishStateMgr=NULL);
	~OffFishState();
	bool Enter();
	bool Leave();
	enFishState GetState();
	//随机一个鱼阵类型，取{1,2,3,4,5,6,7,11,12,13,14,15,16,17}之间的随机整数
	static TFishGroupType GetRandFishGroupType(bool bLeftToRight);
	//随机一个鱼阵序列，add by Ivan_han 20130823
	static stack<OffFishState::TFishGroupTypeSeqElem> GetRandFishGroupTypeSeq();
	//休渔期最后20秒不发鱼
	bool IsFish()const;
	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	FishStateMgr *m_pFishStateMgr;
	unsigned long long m_EnterTime;
	//当前鱼阵序列
	stack<TFishGroupTypeSeqElem> m_CurFishGroupTypeSeq;
	//最后一个鱼阵出现时刻+该鱼阵的轨迹时长
	unsigned long long m_OffEndTime;
};

//发鱼状态管理
class FishStateMgr
{
public:
	FishStateMgr(CFishTraceMgr * pFishTraceMgr=NULL);
	//获得当前发鱼状态
	enFishState GetFishState();
	//切换发鱼状态
	void SwitchFishState();
	//切换场景
	bool SwitchScene();
	int SwitchSceneTime();
public:
	CFishTraceMgr * m_pFishTraceMgr;
	TSeaSceneKind m_CureSeaSceneKind;//当前场景
	bool m_bWaveLToR;//改变方向
	//发鱼状态
	IFishState *      m_pCurFishState;//当前发鱼状态
	CaptureFishState  m_CaptureFishState;//捕渔期(非剧情模式)
	OffFishState      m_OffFishState;//休渔期(剧情模式)
};
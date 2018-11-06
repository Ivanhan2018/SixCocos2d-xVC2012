#pragma once
#include "PartMgr.h"
//#include "FishTable.h"
#include "GameFactorsMgr.h"

typedef double TAwardPoolValue;

//奖池类
class CAwardPool:public CPartMgr
{
public:
	CAwardPool(void);
	~CAwardPool(void);

	//初始化奖池
	bool Init(TAwardPoolValue V,TAwardPoolValue Vh,TAwardPoolValue Vl,TAwardPoolValue SV);

	//奖金进池，玩家射击量=奖池+收益池
	bool Put(TAwardPoolValue nEnterPoolValue);
	bool PutToP(TAwardPoolValue nEnterPoolValue);
	bool PutToSP(TAwardPoolValue nEnterPoolValue);

	//奖金出池
	bool Pop(TAwardPoolValue nLeavePoolValue);

	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);

	//游戏开始
	int OnGameBegin();

	//游戏结束
	int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	//一个能反映奖池条件击毙概率C的量，取值范围为(-1,0],[0,1000),{1000},(-1000,-1)
	float curLambda()const;

	//调整普通池上水位标，0表示不调整，1表示调高，-1表示调低
	int AdjustPoolHighFlag();

	//调整奖池下水位标，0表示不调整，1表示调高，-1表示调低
	int AdjustPoolLowFlag();

public:
	//奖池P
	TAwardPoolValue   m_V;  //水平面值
	TAwardPoolValue   m_Vh;  //上水位标
	TAwardPoolValue   m_Vl;  //下水位标

	//收益池SP
	TAwardPoolValue   m_SV;

	//玩家射击量的抽水比例deductRate=Y/(X+Y)
	int m_X,m_Y;//X+Y=100

	//奖池算法
	GameFactorsMgr m_GameFactorsMgr;
};

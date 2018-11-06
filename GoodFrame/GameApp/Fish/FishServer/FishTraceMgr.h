
#ifndef FISH_TRACE_MGR
#define FISH_TRACE_MGR

#include "PartMgr.h"
#include "../GameMsg/ProFish.h"//add by Ivan_han
#include "Bezier3Trace.h"
#include "FishStateMgr.h"
#include<vector>
#include<string>
using namespace std;

#define M_PI       3.14159265358979323846

struct TPos
{
	float x;
	float y;
};

struct TFishPos
{
	float x;
	float y;
	TFishKind FishKind;
};

struct TFishPosArg
{
	float x;
	float y;
	TFishKind FishKind;
	float Arg;
};

struct tagFishGroupType5
{
	TFishMoveSecs FishMoveSecs;
	TPoint arg1;     
	vector<TFishPos> Arr_Pos;
};

struct tagFishGroupType104
{
	TFishKind FishKind;
	vector<TPos> Arr_Pos;
};

struct tagFishGroupType105
{
	TFishKind FishKind;
	vector<long long> Arr_Pos;
};

// 鱼轨迹管理类
class CFishTraceMgr : public CPartMgr
{
public:
	CFishTraceMgr(void);
	~CFishTraceMgr(void);
public:
	TFishID getNewFishID();
	TFishGroupID getNewFishGroupID();

	//产生一条鱼轨迹，add by Ivan_han
    int AddOneFish(Rsp_AddOneFish &rsp);
	//llInitElapsed<0表示服务器端建立轨迹对象时，该轨迹动作已消逝的时间(ms)，实现列队鱼群时用到
    int AddOneFish(TFishKind fishType,TFishPathType pathType,TFishGroupType FishGroupType,TPoint startP,TPoint arg1,TPoint arg2,TPoint arg3,TFishMoveSecs FishMoveSecs,float EntryTime,float DepartureTime,long long llInitElapsed);

	//产生一个鱼阵，add by Ivan_han
	int AddOneGroupFish(Rsp_AddOneFish_List *pRsp,int iSubCode=RSP_ADD_ONE_FISH_LIST);
	int AddOneGroupFish(Rsp_AddOneFish_Arr &rsp);

	//随机产生一条三阶贝塞尔曲线轨迹的鱼
	void RandAddOneFishWithBezier3(int PathLibType,TFishKind fishType=0);
	bool RandBezier3(int PathLibType,TPoint &p0,TPoint &p1,TPoint &p2,TPoint &p3,float &EntryTime,float &DepartureTime);

	//产生一条任意曲线轨迹的鱼
	void AddOneFishWithCurve(int CurveLibIndex,int CurveIndex);

	//产生一个指定类型的鱼阵、鱼群
	void AddRegularFish(TFishGroupType FishGroupType,TFishKind fishType=0);
	
	//得到一条鱼轨迹，鱼号为0表示服务器端无此轨迹，add by Ivan_han 20130716
	Rsp_AddOneFish GetFishTrace(TFishID FishID);

	//得到鱼轨迹的鱼号，鱼号为0表示服务器端无此轨迹，add by Ivan_han 20130716
	vector<TFishKind> GetFishKinds(const vector<TFishID> &vFishID,std::vector<TFishNumOfAck> &vecOut);

	//屏幕内轨迹检测，返回屏幕内轨迹的渔币总量，鱼号为0表示检查屏幕内所有轨迹，add by Ivan_han 20130717
	int CheckFishTrace(TFishKind FishKind,std::vector<TFishID> &vecOut);

	//销毁一条轨迹
	bool DestroyFishTrace(TFishID FishID);

	//销毁轨迹检测，返回销毁轨迹的条数
	int DestroyFishTrace(std::vector<TFishID> &vecOut);

	//销毁多条轨迹，DeadFullScreenBombFishID=0表示vDeadFishID里面没有全屏炸弹
	std::vector<TFishID> DestroySomeFishTrace(const std::vector<TFishID> &vDeadFishID,std::vector<TFishKind> &vDeadFishKind,TFishID &DeadFullScreenBombFishID);

	//更新未死鱼的攻击次数，add by Ivan_han 20130801
	std::vector<TFishID> UpdateSomeFishTrace(const std::vector<TFishID> &vHitFishID,const std::vector<TFishID> &vDeadFishID);

	//销毁所有的轨迹
	void clearFishTrace();

	// 举手
	int OnRaiseHand(int iSeatNo);

	// 桌子定时器响应
	int OnTableTimer(int iTableNo, int iIDEvent);

	//游戏开始
	int OnGameBegin();

	//游戏结束
	int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	//非公有成员函数
protected:
	//产生一个直线轨迹鱼阵(约定：FishGroupType<100表示逻辑上是鱼阵，FishGroupType>100表示逻辑上是鱼群)
	int AddRegularFish101(TFishKind fishType=0);
	int AddRegularFish102(TFishKind fishType=0);
	int AddOneGroupFish1_List(vector<TFishPos> arr,TPoint arg1,TPoint arg2,TPoint arg3);
	//产生一个摆线轨迹鱼阵(FishGroupType>100表示逻辑上是鱼群)
	int AddRegularFish103(TFishKind fishType=0);
	//贝塞尔曲线轨迹列阵鱼群
	int AddRegularFish104(TFishKind fishType=0);
	//贝塞尔曲线轨迹列队鱼群
	int AddRegularFish105(TFishKind fishType=0);

	bool RandRegularFish104(TFishKind FishKind,vector<TPos> &Arr_Pos);
	bool RandRegularFish105(TFishKind FishKind,vector<long long> &Arr_Pos);
private:
	//鱼轨迹数据
	typedef std::vector<Rsp_AddOneFish> TVECT_FISH_TRACE;
	TVECT_FISH_TRACE m_ServerFishTrace;

	////三阶贝塞尔曲线轨迹库数据
	//CBezier3TraceCache m_Bezier3TraceCache[3];

	//发鱼策略
	FishStateMgr m_FishStateMgr;
};

#endif
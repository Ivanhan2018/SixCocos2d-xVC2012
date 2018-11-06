
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

// ��켣������
class CFishTraceMgr : public CPartMgr
{
public:
	CFishTraceMgr(void);
	~CFishTraceMgr(void);
public:
	TFishID getNewFishID();
	TFishGroupID getNewFishGroupID();

	//����һ����켣��add by Ivan_han
    int AddOneFish(Rsp_AddOneFish &rsp);
	//llInitElapsed<0��ʾ�������˽����켣����ʱ���ù켣���������ŵ�ʱ��(ms)��ʵ���ж���Ⱥʱ�õ�
    int AddOneFish(TFishKind fishType,TFishPathType pathType,TFishGroupType FishGroupType,TPoint startP,TPoint arg1,TPoint arg2,TPoint arg3,TFishMoveSecs FishMoveSecs,float EntryTime,float DepartureTime,long long llInitElapsed);

	//����һ������add by Ivan_han
	int AddOneGroupFish(Rsp_AddOneFish_List *pRsp,int iSubCode=RSP_ADD_ONE_FISH_LIST);
	int AddOneGroupFish(Rsp_AddOneFish_Arr &rsp);

	//�������һ�����ױ��������߹켣����
	void RandAddOneFishWithBezier3(int PathLibType,TFishKind fishType=0);
	bool RandBezier3(int PathLibType,TPoint &p0,TPoint &p1,TPoint &p2,TPoint &p3,float &EntryTime,float &DepartureTime);

	//����һ���������߹켣����
	void AddOneFishWithCurve(int CurveLibIndex,int CurveIndex);

	//����һ��ָ�����͵�������Ⱥ
	void AddRegularFish(TFishGroupType FishGroupType,TFishKind fishType=0);
	
	//�õ�һ����켣�����Ϊ0��ʾ���������޴˹켣��add by Ivan_han 20130716
	Rsp_AddOneFish GetFishTrace(TFishID FishID);

	//�õ���켣����ţ����Ϊ0��ʾ���������޴˹켣��add by Ivan_han 20130716
	vector<TFishKind> GetFishKinds(const vector<TFishID> &vFishID,std::vector<TFishNumOfAck> &vecOut);

	//��Ļ�ڹ켣��⣬������Ļ�ڹ켣��������������Ϊ0��ʾ�����Ļ�����й켣��add by Ivan_han 20130717
	int CheckFishTrace(TFishKind FishKind,std::vector<TFishID> &vecOut);

	//����һ���켣
	bool DestroyFishTrace(TFishID FishID);

	//���ٹ켣��⣬�������ٹ켣������
	int DestroyFishTrace(std::vector<TFishID> &vecOut);

	//���ٶ����켣��DeadFullScreenBombFishID=0��ʾvDeadFishID����û��ȫ��ը��
	std::vector<TFishID> DestroySomeFishTrace(const std::vector<TFishID> &vDeadFishID,std::vector<TFishKind> &vDeadFishKind,TFishID &DeadFullScreenBombFishID);

	//����δ����Ĺ���������add by Ivan_han 20130801
	std::vector<TFishID> UpdateSomeFishTrace(const std::vector<TFishID> &vHitFishID,const std::vector<TFishID> &vDeadFishID);

	//�������еĹ켣
	void clearFishTrace();

	// ����
	int OnRaiseHand(int iSeatNo);

	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);

	//��Ϸ��ʼ
	int OnGameBegin();

	//��Ϸ����
	int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	//�ǹ��г�Ա����
protected:
	//����һ��ֱ�߹켣����(Լ����FishGroupType<100��ʾ�߼���������FishGroupType>100��ʾ�߼�������Ⱥ)
	int AddRegularFish101(TFishKind fishType=0);
	int AddRegularFish102(TFishKind fishType=0);
	int AddOneGroupFish1_List(vector<TFishPos> arr,TPoint arg1,TPoint arg2,TPoint arg3);
	//����һ�����߹켣����(FishGroupType>100��ʾ�߼�������Ⱥ)
	int AddRegularFish103(TFishKind fishType=0);
	//���������߹켣������Ⱥ
	int AddRegularFish104(TFishKind fishType=0);
	//���������߹켣�ж���Ⱥ
	int AddRegularFish105(TFishKind fishType=0);

	bool RandRegularFish104(TFishKind FishKind,vector<TPos> &Arr_Pos);
	bool RandRegularFish105(TFishKind FishKind,vector<long long> &Arr_Pos);
private:
	//��켣����
	typedef std::vector<Rsp_AddOneFish> TVECT_FISH_TRACE;
	TVECT_FISH_TRACE m_ServerFishTrace;

	////���ױ��������߹켣������
	//CBezier3TraceCache m_Bezier3TraceCache[3];

	//�������
	FishStateMgr m_FishStateMgr;
};

#endif
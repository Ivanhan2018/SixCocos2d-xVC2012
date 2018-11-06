#include "FishTraceMgr.h"
#include "GameSkeletonMsgCode.h"
#include "FishTable.h"
#include "Bezier3Trace.h"
#include "ServerCurve.h"//add by Ivan_han 20130805
#include "./EndlessLoopGuard.h"	// 死循环守护

TFishPos ARR_FISHPOS[]={{-600,359,1},{-593,297,1},{-574,237,1},{-542,183,1},{-500,137,1},{-449,100,1},{-392,74,1},{-331,61,1},{-268,61,1},{-207,74,1},{-150,100,1},{-99,137,1},{-57,183,1},{-25,237,1},{-6,297,1},{0,360,1},{-6,422,1},{-25,482,1},{-57,536,1},{-99,582,1},{-150,619,1},{-207,645,1},{-268,658,1},{-331,658,1},{-392,645,1},{-450,619,1},{-500,582,1},{-542,536,1},{-574,482,1},{-593,422,1},{-550,359,2},{-542,297,2},{-519,239,2},{-482,188,2},{-433,148,2},{-377,122,2},{-315,110,2},{-253,114,2},{-193,133,2},{-140,167,2},{-97,213,2},{-67,267,2},{-51,328,2},{-51,391,2},{-67,452,2},{-97,506,2},{-140,552,2},{-193,586,2},{-253,605,2},{-315,609,2},{-377,597,2},{-433,571,2},{-482,531,2},{-519,480,2},{-542,422,2},{-500,359,3},{-490,298,3},{-461,242,3},{-417,198,3},{-361,169,3},{-299,160,3},{-238,169,3},{-182,198,3},{-138,242,3},{-109,298,3},{-100,360,3},{-109,421,3},{-138,477,3},{-182,521,3},{-238,550,3},{-300,560,3},{-361,550,3},{-417,521,3},{-461,477,3},{-490,421,3},{-300,360,40}};
int ARR_FISHPOS_COUNT = sizeof(ARR_FISHPOS)/sizeof(TFishPos);

//5列网狐队形0
TFishPos ARR_FISHPOS_WH0[]={{-420,360,1},{-420,420,1},{-420,480,1},{-420,540,1},{-420,600,1},{-420,300,1},{-420,240,1},{-420,180,1},{-420,120,1},{-340,360,2},{-340,420,2},{-340,480,2},{-340,540,2},{-340,600,2},{-340,300,2},{-340,240,2},{-340,180,2},{-340,120,2},{-260,360,3},{-260,420,3},{-260,480,3},{-260,540,3},{-260,600,3},{-260,300,3},{-260,240,3},{-260,180,3},{-260,120,3},{-180,360,4},{-180,420,4},{-180,480,4},{-180,540,4},{-180,600,4},{-180,300,4},{-180,240,4},{-180,180,4},{-180,120,4},{-100,360,5},{-100,420,5},{-100,480,5},{-100,540,5},{-100,600,5},{-100,300,5},{-100,240,5},{-100,180,5},{-100,120,5}};
int ARR_FISHPOS_WH0_COUNT = sizeof(ARR_FISHPOS_WH0)/sizeof(TFishPos);

//5列网狐队形1，2
TFishPos ARR_FISHPOS_WH1[]={{-420,360,1},{-416,420,1},{-405,480,1},{-387,540,1},{-362,600,1},{-416,300,1},{-405,240,1},{-387,180,1},{-362,120,1},{-340,360,2},{-336,420,2},{-325,480,2},{-307,540,2},{-282,600,2},{-336,300,2},{-325,240,2},{-307,180,2},{-282,120,2},{-260,360,3},{-256,420,3},{-245,480,3},{-227,540,3},{-202,600,3},{-256,300,3},{-245,240,3},{-227,180,3},{-202,120,3},{-180,360,4},{-176,420,4},{-165,480,4},{-147,540,4},{-122,600,4},{-176,300,4},{-165,240,4},{-147,180,4},{-122,120,4},{-100,360,5},{-96,420,5},{-85,480,5},{-67,540,5},{-42,600,5},{-96,300,5},{-85,240,5},{-67,180,5},{-42,120,5}};
int ARR_FISHPOS_WH1_COUNT = sizeof(ARR_FISHPOS_WH1)/sizeof(TFishPos);
TFishPos ARR_FISHPOS_WH2[]={{-420,360,1},{-423,420,1},{-434,480,1},{-452,540,1},{-477,600,1},{-423,300,1},{-434,240,1},{-452,180,1},{-477,120,1},{-340,360,2},{-343,420,2},{-354,480,2},{-372,540,2},{-397,600,2},{-343,300,2},{-354,240,2},{-372,180,2},{-397,120,2},{-260,360,3},{-263,420,3},{-274,480,3},{-292,540,3},{-317,600,3},{-263,300,3},{-274,240,3},{-292,180,3},{-317,120,3},{-180,360,4},{-183,420,4},{-194,480,4},{-212,540,4},{-237,600,4},{-183,300,4},{-194,240,4},{-212,180,4},{-237,120,4},{-100,360,5},{-103,420,5},{-114,480,5},{-132,540,5},{-157,600,5},{-103,300,5},{-114,240,5},{-132,180,5},{-157,120,5}};
int ARR_FISHPOS_WH2_COUNT = sizeof(ARR_FISHPOS_WH2)/sizeof(TFishPos);

vector<TFishPos> g_vec(ARR_FISHPOS,ARR_FISHPOS+ARR_FISHPOS_COUNT);
vector<TFishPos> g_vecWH0(ARR_FISHPOS_WH0,ARR_FISHPOS_WH0+ARR_FISHPOS_WH0_COUNT);
vector<TFishPos> g_vecWH1(ARR_FISHPOS_WH1,ARR_FISHPOS_WH1+ARR_FISHPOS_WH1_COUNT);
vector<TFishPos> g_vecWH2(ARR_FISHPOS_WH2,ARR_FISHPOS_WH2+ARR_FISHPOS_WH2_COUNT);

//起点数组关于x=640的对称数组
vector<TFishPos> g_vecRToL;
vector<TFishPos> g_vecWH0RToL;
vector<TFishPos> g_vecWH1RToL;
vector<TFishPos> g_vecWH2RToL;

CFishTraceMgr::CFishTraceMgr(void)
{
	//m_Bezier3TraceCache[0].LoadData("FishTrace/fish_one.xml");
	//m_Bezier3TraceCache[1].LoadData("FishTrace/fish_S.xml");
	//m_Bezier3TraceCache[2].LoadData("FishTrace/fish_U.xml");

	//m_FishStateMgr.m_pFishTable=this->get_fish_table();
	m_FishStateMgr.m_pFishTraceMgr=this;
}


CFishTraceMgr::~CFishTraceMgr(void)
{
}

TFishID CFishTraceMgr::getNewFishID()
{
	static TFishID FishID=0;
	FishID++;
	if(FishID==0)
		FishID++;
	return FishID;
}

TFishGroupID CFishTraceMgr::getNewFishGroupID()
{
	static TFishGroupID FishGroupID=0;
	FishGroupID++;
	if(FishGroupID==0)
		FishGroupID++;
	return FishGroupID;
}

//产生一条鱼轨迹，add by Ivan_han
int CFishTraceMgr::AddOneFish(Rsp_AddOneFish &rsp)
{
	if(get_fish_table()==NULL)
		return 0;

	int iRes = 0;

	// 桌子内广播
	get_fish_table()->send_table_data(TABLE_MAIN, RSP_ADD_ONE_FISH, (BYTE*)(&rsp), sizeof(rsp));

	return iRes;
}

int CFishTraceMgr::AddOneFish(TFishKind fishType,TFishPathType pathType,TFishGroupType FishGroupType,TPoint startP,TPoint arg1,TPoint arg2,TPoint arg3,TFishMoveSecs FishMoveSecs,float EntryTime/*=0.1*/,float DepartureTime/*=0.9*/,long long llInitElapsed/*=0*/)
{
	if(get_fish_table()==NULL)
		return 0;

	Rsp_AddOneFish rsp;
	rsp.TableID=get_fish_table()->m_stTableInfo.iTableNo;
	rsp.FishID=getNewFishID();
	rsp.FishMoveSecs=FishMoveSecs;
	rsp.FishEntryTime=FishMoveSecs*EntryTime;
	rsp.FishDepartureTime=FishMoveSecs*DepartureTime;
	rsp.FishKind=fishType;
	rsp.FishPathType=pathType;
	rsp.FishGroupType=FishGroupType;
	rsp.startP=startP;
	rsp.arg1=arg1;
	rsp.arg2=arg2;
	rsp.arg3=arg3;
	rsp.BuildTraceTime=CFishTable::GetTickCount64()+llInitElapsed;

	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
		m_ServerFishTrace.push_back(rsp);
	}
#if USESLEEP
	srand(time(0));
	Sleep(rand()%5000+2000);
#endif
	int iRes = AddOneFish(rsp);

	return iRes;
}

int CFishTraceMgr::AddOneGroupFish(Rsp_AddOneFish_List *pRsp,int iSubCode/*=RSP_ADD_ONE_FISH_LIST*/)
{
	if(get_fish_table()==NULL)
		return 0;

	int iRes = 0;

	// 桌子内广播
	get_fish_table()->send_table_data(TABLE_MAIN, iSubCode, (BYTE*)(pRsp), pRsp->getLength());

	return iRes;
}

//产生一个鱼阵，add by Ivan_han
int CFishTraceMgr::AddOneGroupFish(Rsp_AddOneFish_Arr &rsp)
{
	if(get_fish_table()==NULL)
		return 0;

	int iRes = 0;

	// 桌子内广播
	get_fish_table()->send_table_data(TABLE_MAIN, RSP_ADD_ONE_FISH_ARR, (BYTE*)(&rsp), sizeof(rsp));

	return iRes;
}

//产生一个直线轨迹鱼阵
int CFishTraceMgr::AddRegularFish101(TFishKind fishType/*=0*/)
{
	if(get_fish_table()==NULL)
		return 0;
	Rsp_AddOneFish_Arr rsp;
	rsp.TableID=get_fish_table()->m_stTableInfo.iTableNo;
	rsp.nFishCount=4;
	TFishKind FishKind=GameFactorsMgr::GetRand(1,3);
	TBuildTraceTime lPutFishTime=CFishTable::GetTickCount64();
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
		for(int i=0;i<rsp.nFishCount;i++)
		{
			rsp.Arr[i].TableID=get_fish_table()->m_stTableInfo.iTableNo;
			rsp.Arr[i].FishID=getNewFishID();
			rsp.Arr[i].FishMoveSecs=20;
			rsp.Arr[i].FishEntryTime=2;
			rsp.Arr[i].FishDepartureTime=18;
			rsp.Arr[i].reserved=0;
			rsp.Arr[i].FishMoveStatus=0;
			rsp.Arr[i].FishNumOfAck=0;
			rsp.Arr[i].FishKind=10;
			rsp.Arr[i].FishPathType=1;
			rsp.Arr[i].FishGroupType=101;
			rsp.Arr[i].startP=TPoint(-25*i,500);
			rsp.Arr[i].arg1=TPoint(1500,1500);
			rsp.Arr[i].arg2=TPoint();
			rsp.Arr[i].arg3=TPoint();
			rsp.Arr[i].BuildTraceTime=lPutFishTime;
			m_ServerFishTrace.push_back(rsp.Arr[i]);
		}
	}
	int iRes = AddOneGroupFish(rsp);

	return iRes;
}

int CFishTraceMgr::AddRegularFish102(TFishKind fishType/*=0*/)
{
	if(get_fish_table()==NULL)
		return 0;
	Rsp_AddOneFish_List *pRsp=NULL;
	pRsp=(Rsp_AddOneFish_List *)malloc(sizeof(Rsp_AddOneFish_List)+sizeof(Rsp_AddOneFish)*4);
	pRsp->nFishCount=4;
	pRsp->FishGroupID=getNewFishGroupID();
	TFishKind FishKind=GameFactorsMgr::GetFishKindByProb();
	TBuildTraceTime lPutFishTime=CFishTable::GetTickCount64();
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
		for(int i=0;i<pRsp->nFishCount;i++)
		{
			(*pRsp)[i].TableID=get_fish_table()->m_stTableInfo.iTableNo;
			(*pRsp)[i].FishID=getNewFishID();
			(*pRsp)[i].FishMoveSecs=20;
			(*pRsp)[i].FishEntryTime=2;
			(*pRsp)[i].FishDepartureTime=18;
			(*pRsp)[i].reserved=0;
			(*pRsp)[i].FishMoveStatus=0;
			(*pRsp)[i].FishNumOfAck=0;
			(*pRsp)[i].FishKind=FishKind;
			(*pRsp)[i].FishPathType=1;
			(*pRsp)[i].FishGroupType=102;
			(*pRsp)[i].startP=TPoint(-25*i,1500);
			(*pRsp)[i].arg1=TPoint(1500,1500);
			(*pRsp)[i].arg2=TPoint();
			(*pRsp)[i].arg3=TPoint();
			(*pRsp)[i].BuildTraceTime=lPutFishTime;
			m_ServerFishTrace.push_back((*pRsp)[i]);
		}
	}
	int iRes = AddOneGroupFish(pRsp);
	free(pRsp);
	return iRes;
}

/*
根据轨迹阵起点数组生成直线轨迹阵
参数说明：
arr----轨迹阵起点数组，轨迹阵起点数组的元素个数
arg1----直线轨迹阵的位移向量
arg2----轨迹阵起点数组的位移向量，根据arr和arg2可生成一个新的轨迹阵起点数组
arg3.x----TFishGroupType
arg3.y----TFishMoveSecs
*/
int CFishTraceMgr::AddOneGroupFish1_List(vector<TFishPos> arr,TPoint arg1,TPoint arg2,TPoint arg3)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	if(get_fish_table()==NULL)
		return 0;
	int n=arr.size();
	if(n<=0)
		return 0;
	TBuildTraceTime lPutFishTime=CFishTable::GetTickCount64();
	// 此锁仅在本括号内生效，出了括号就自动解锁啦
	CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
	TFishGroupID FishGroupID=getNewFishGroupID();
	int NoSendCount=n;
	int SendCount=0;
	TFishMoveSecs FishMoveSecs=PoolAndFish::Instance().GetFishMoveSecs((int)(arg3.x)%10);
	if((int)(arg3.x)%10==5)
		FishMoveSecs=arg3.y;
	while(NoSendCount>0)
	{
		if(NoSendCount>=30)
		{
			Rsp_AddOneFish_List *pRsp=NULL;
			pRsp=(Rsp_AddOneFish_List *)malloc(sizeof(Rsp_AddOneFish_List)+sizeof(Rsp_AddOneFish)*30);
			pRsp->nFishCount=30;
			pRsp->nTotalFishCount=n;
			pRsp->FishGroupID=FishGroupID;
			for(int i=SendCount;i<SendCount+30;i++)
			{
				(*pRsp)[i-SendCount].TableID=get_fish_table()->m_stTableInfo.iTableNo;
				(*pRsp)[i-SendCount].FishID=getNewFishID();
				(*pRsp)[i-SendCount].FishMoveSecs=FishMoveSecs;
				(*pRsp)[i-SendCount].FishEntryTime=FishMoveSecs*0.1;
				(*pRsp)[i-SendCount].FishDepartureTime=FishMoveSecs*0.9;
				(*pRsp)[i-SendCount].reserved=0;
				(*pRsp)[i-SendCount].FishMoveStatus=0;
				(*pRsp)[i-SendCount].FishNumOfAck=0;
				(*pRsp)[i-SendCount].FishKind=arr[i].FishKind;
				(*pRsp)[i-SendCount].FishPathType=1;
				(*pRsp)[i-SendCount].FishGroupType=arg3.x;
				(*pRsp)[i-SendCount].startP=TPoint(arr[i].x+arg2.x,arr[i].y+arg2.y);
				(*pRsp)[i-SendCount].arg1=arg1;
				(*pRsp)[i-SendCount].arg2=TPoint();
				(*pRsp)[i-SendCount].arg3=TPoint();
				(*pRsp)[i-SendCount].BuildTraceTime=lPutFishTime;
				m_ServerFishTrace.push_back((*pRsp)[i-SendCount]);
			}
			NoSendCount-=30;
			SendCount+=30;
			int iRes=AddOneGroupFish(pRsp/*,RSP_ADD_ONE_FISH_LIST_UNFINISH*/);
			free(pRsp);
		}
		else
		{
			Rsp_AddOneFish_List *pRsp=NULL;
			pRsp=(Rsp_AddOneFish_List *)malloc(sizeof(Rsp_AddOneFish_List)+sizeof(Rsp_AddOneFish)*(n-SendCount));
			pRsp->nFishCount=n-SendCount;
			pRsp->nTotalFishCount=n;
			pRsp->FishGroupID=FishGroupID;
			for(int i=SendCount;i<n;i++)
			{
				(*pRsp)[i-SendCount].TableID=get_fish_table()->m_stTableInfo.iTableNo;
				(*pRsp)[i-SendCount].FishID=getNewFishID();
				(*pRsp)[i-SendCount].FishMoveSecs=FishMoveSecs;
				(*pRsp)[i-SendCount].FishEntryTime=FishMoveSecs*0.1;
				(*pRsp)[i-SendCount].FishDepartureTime=FishMoveSecs*0.9;
				(*pRsp)[i-SendCount].reserved=0;
				(*pRsp)[i-SendCount].FishMoveStatus=0;
				(*pRsp)[i-SendCount].FishNumOfAck=0;
				(*pRsp)[i-SendCount].FishKind=arr[i].FishKind;
				(*pRsp)[i-SendCount].FishPathType=1;
				(*pRsp)[i-SendCount].FishGroupType=arg3.x;
				(*pRsp)[i-SendCount].startP=TPoint(arr[i].x+arg2.x,arr[i].y+arg2.y);
				(*pRsp)[i-SendCount].arg1=arg1;
				(*pRsp)[i-SendCount].arg2=TPoint();
				(*pRsp)[i-SendCount].arg3=TPoint();
				(*pRsp)[i-SendCount].BuildTraceTime=lPutFishTime;
				m_ServerFishTrace.push_back((*pRsp)[i-SendCount]);
			}
			NoSendCount=0;
			SendCount+=NoSendCount;
			int iRes=AddOneGroupFish(pRsp/*,RSP_ADD_ONE_FISH_LIST_FINISH*/);
			free(pRsp);
		}
	}
	return 0;
}

//产生一个摆线轨迹鱼阵
int CFishTraceMgr::AddRegularFish103(TFishKind fishType/*=0*/)
{
	if(get_fish_table()==NULL)
		return 0;
	Rsp_AddOneFish_Arr rsp;
	rsp.TableID=get_fish_table()->m_stTableInfo.iTableNo;
	rsp.nFishCount=10;
	TFishKind FishKind=GameFactorsMgr::GetRand(1,2);
	TBuildTraceTime lPutFishTime=CFishTable::GetTickCount64();
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
		for(int i=0;i<rsp.nFishCount;i++)
		{
			rsp.Arr[i].TableID=get_fish_table()->m_stTableInfo.iTableNo;
			rsp.Arr[i].FishID=getNewFishID();
			rsp.Arr[i].FishMoveSecs=20;
			rsp.Arr[i].FishMoveStatus=0;
			rsp.Arr[i].FishNumOfAck=0;
			rsp.Arr[i].FishKind=FishKind;
			rsp.Arr[i].FishPathType=3;
			rsp.Arr[i].FishGroupType=103;
			rsp.Arr[i].startP=TPoint(200,300);
			rsp.Arr[i].arg1=TPoint(90,10+M_PI*2*i/rsp.nFishCount);
			rsp.Arr[i].arg2=TPoint(0,M_PI);
			rsp.Arr[i].arg3=TPoint();
			rsp.Arr[i].BuildTraceTime=lPutFishTime;
			m_ServerFishTrace.push_back(rsp.Arr[i]);
		}
	}
	int iRes = AddOneGroupFish(rsp);

	return iRes;
}


//随机产生一条三阶贝塞尔曲线轨迹的鱼
void CFishTraceMgr::RandAddOneFishWithBezier3(int PathLibType,TFishKind fishType/*=0*/)
{
	TPoint p0(1180,1114);
	TPoint p1(1042,605);
	TPoint p2(124,-75);
	TPoint p3(-367,-151);
	float EntryTime=0.1;
	float DepartureTime=0.9;
	bool ret=RandBezier3(PathLibType,p0,p1,p2,p3,EntryTime,DepartureTime);
	TFishKind FishKind=fishType;
	if(fishType==0)
		FishKind=GameFactorsMgr::GetFishKindByProb();
	TFishMoveSecs FishMoveSecs=CTabFishCache::getFishMoveSecs(FishKind);
	AddOneFish(FishKind,5,0,p0,p1,p2,p3,FishMoveSecs,EntryTime,DepartureTime,0);
}

bool CFishTraceMgr::RandBezier3(int PathLibType,TPoint &p0,TPoint &p1,TPoint &p2,TPoint &p3,float &EntryTime,float &DepartureTime)
{
	int index=0;
	if(PathLibType>1)
	{
		//index=GameFactorsMgr::GetRand(0,2);
		static int ARR_TRACELIB[]={0,1,2};
		static int ARR_TRACELIB_PROB[]={417,76,8};
		static int ARR_TRACELIB_COUNT = sizeof(ARR_TRACELIB)/sizeof(int);
		index=GameFactorsMgr::SelectByProb(ARR_TRACELIB,ARR_TRACELIB_PROB,ARR_TRACELIB_COUNT,501);
	}
	CBezier3TraceCache *pCache=&m_Bezier3TraceCache[index];
	int nSize=pCache->m_vecBezier3TraceCache.size();
	if(nSize>0)
	{
		const CBezier3TraceNode *pNode=pCache->getBezier3Trace(GameFactorsMgr::GetRand(0,nSize-1));
		if(pNode!=NULL)
		{
			p0=pNode->m_pos0;
			p1=pNode->m_pos1;
			p2=pNode->m_pos2;
			p3=pNode->m_pos3;
			EntryTime=pNode->m_EntryTime;
			DepartureTime=pNode->m_DepartureTime;
			return true;
		}
	}
	return false;
}

//贝塞尔曲线轨迹列阵鱼群
int CFishTraceMgr::AddRegularFish104(TFishKind fishType/*=0*/)
{
	TPoint p0(1180,1114);
	TPoint p1(1042,605);
	TPoint p2(124,-75);
	TPoint p3(-367,-151);
	float EntryTime=0.1;
	float DepartureTime=0.9;
	bool ret=RandBezier3(3,p0,p1,p2,p3,EntryTime,DepartureTime);

	TPos Arr_Pos[]={{0,0},{-60,0},{-50,30},{0,50},{30,40},{30,-40}};
	int Arr_Pos_Count= sizeof(Arr_Pos)/sizeof(TPos);

	TFishKind FishKind=fishType;
	if(fishType==0)
		FishKind=GameFactorsMgr::GetRand(1,3);
	vector<TPos> vec_TPos(Arr_Pos,Arr_Pos+Arr_Pos_Count);
	bool bret=RandRegularFish104(FishKind,vec_TPos);

	TFishMoveSecs FishMoveSecs=CTabFishCache::getFishMoveSecs(FishKind);
	for(int i=0;i<vec_TPos.size();i++)
		AddOneFish(FishKind,5,0,TPoint(p0.x+vec_TPos[i].x,p0.y+vec_TPos[i].y),TPoint(p1.x+vec_TPos[i].x,p1.y+vec_TPos[i].y),TPoint(p2.x+vec_TPos[i].x,p2.y+vec_TPos[i].y),TPoint(p3.x+vec_TPos[i].x,p3.y+vec_TPos[i].y),FishMoveSecs,EntryTime,DepartureTime,0);

	return 0;
}

//贝塞尔曲线轨迹列队鱼群
int CFishTraceMgr::AddRegularFish105(TFishKind fishType/*=0*/)
{
	TPoint p0(-112,-333);
	TPoint p1(158,1110);
	TPoint p2(1152,-333);
	TPoint p3(1563,1055);
	float EntryTime=0.1;
	float DepartureTime=0.9;
	bool ret=RandBezier3(3,p0,p1,p2,p3,EntryTime,DepartureTime);

	long long Arr_Pos[]={-3500,-3000,-2500,-2000,-1000,0};
	int Arr_Pos_Count= sizeof(Arr_Pos)/sizeof(TPos);

	TFishKind FishKind=fishType;
	if(fishType==0)
		//FishKind=GameFactorsMgr::GetRand(1,10);
		FishKind=GameFactorsMgr::GetFishKindByProbEx(1);
	vector<long long> vec_TPos(Arr_Pos,Arr_Pos+Arr_Pos_Count);
	bool bret=RandRegularFish105(FishKind,vec_TPos);

	TFishMoveSecs FishMoveSecs=CTabFishCache::getFishMoveSecs(FishKind);
	for(int i=0;i<vec_TPos.size();i++)
		AddOneFish(FishKind,5,0,p0,p1,p2,p3,FishMoveSecs,EntryTime,DepartureTime,vec_TPos[i]);

	return 0;
}

bool CFishTraceMgr::RandRegularFish104(TFishKind FishKind,vector<TPos> &Arr_Pos)
{
	if(FishKind>=1 && FishKind<=3)
	{
		int nSize=PoolAndFish::Instance().m_vecAll104[FishKind-1].size();
		if(nSize>0)
		{
			int index=GameFactorsMgr::GetRand(0,nSize-1);
			Arr_Pos.clear();
			Arr_Pos=PoolAndFish::Instance().m_vecAll104[FishKind-1][index].Arr_Pos;
			return true;
		}
	}
	return false;
}

bool CFishTraceMgr::RandRegularFish105(TFishKind FishKind,vector<long long> &Arr_Pos)
{
	if(FishKind>=1 && FishKind<=10)
	{
		int nSize=PoolAndFish::Instance().m_vecAll105[FishKind-1].size();
		if(nSize>0)
		{
			int index=GameFactorsMgr::GetRand(0,nSize-1);
			Arr_Pos.clear();
			Arr_Pos=PoolAndFish::Instance().m_vecAll105[FishKind-1][index].Arr_Pos;
			return true;
		}
	}
	return false;
}

//产生一条任意曲线轨迹的鱼
void CFishTraceMgr::AddOneFishWithCurve(int CurveLibIndex,int CurveIndex)
{
	AddOneFish(GameFactorsMgr::GetFishKindByProb(),4,0,TPoint(0,0),TPoint(CurveLibIndex,CurveIndex),TPoint(0,0),TPoint(0,0),20,0.1,0.9,0);
}

//产生一个指定类型的鱼阵、鱼群
void CFishTraceMgr::AddRegularFish(TFishGroupType FishGroupType,TFishKind fishType/*=0*/)
{
	switch ( FishGroupType )
	{
	case 101: 	AddRegularFish101(fishType); break;
	case 102: 	AddRegularFish102(fishType); break;
	case 103: 	AddRegularFish103(fishType); break;
	case 104: 	AddRegularFish104(fishType); break;
	case 105: 	AddRegularFish105(fishType); break;
	case 1: 
		{
			//圆直线阵LToR
			AddOneGroupFish1_List(g_vec,TPoint(2000,0),TPoint(0,0),TPoint(1,0));
		}
		break;
	case 11: 
		{
			//圆直线阵RToL
			//AddOneGroupFish1_List(g_vec,TPoint(-2000,0),TPoint(1780,0),TPoint(1,0));
			AddOneGroupFish1_List(g_vecRToL,TPoint(-2000,0),TPoint(0,0),TPoint(1,0));
		}
		break;
	case 2: 
		{
			//垂直线队形直线阵LToR
			AddOneGroupFish1_List(g_vecWH0,TPoint(2000,0),TPoint(0,0),TPoint(2,0));
		}
		break;
	case 12: 
		{
			//垂直线队形直线阵RToL
			//AddOneGroupFish1_List(g_vecWH0,TPoint(-2000,0),TPoint(1780,0),TPoint(2,0));
			AddOneGroupFish1_List(g_vecWH0RToL,TPoint(-2000,0),TPoint(0,0),TPoint(2,0));
		}
		break;
	case 3: 
		{
			//顶点在焦点前面的抛物线队形直线阵LToR
			AddOneGroupFish1_List(g_vecWH2,TPoint(2000,0),TPoint(0,0),TPoint(4,0));
		}
		break;
	case 13: 
		{
			//顶点在焦点前面的抛物线队形直线阵RToL
			//AddOneGroupFish1_List(g_vecWH1,TPoint(-2000,0),TPoint(1780,0),TPoint(4,0));
			AddOneGroupFish1_List(g_vecWH2RToL,TPoint(-2000,0),TPoint(0,0),TPoint(4,0));
		}
		break;
	case 4: 
		{
			//顶点在焦点后面的抛物线队形直线阵LToR
			AddOneGroupFish1_List(g_vecWH1,TPoint(2000,0),TPoint(0,0),TPoint(3,0));
		}
		break;
	case 14: 
		{
			//顶点在焦点后面的抛物线队形直线阵RToL
			//AddOneGroupFish1_List(g_vecWH2,TPoint(-2000,0),TPoint(1780,0),TPoint(3,0));
			AddOneGroupFish1_List(g_vecWH1RToL,TPoint(-2000,0),TPoint(0,0),TPoint(3,0));
		}
		break;
	case 5: 
	case 6: 
	case 7: 
		{
			int nSize=PoolAndFish::Instance().m_vecFishGroupType5LToR.size();
			if(nSize>0)
			{
				int index=FishGroupType-5;
				if(index>=nSize)
					index=GameFactorsMgr::GetRand(0,nSize-1);  
				tagFishGroupType5 vFishs=PoolAndFish::Instance().m_vecFishGroupType5LToR[index];
				AddOneGroupFish1_List(vFishs.Arr_Pos,vFishs.arg1,TPoint(0,0),TPoint(5,vFishs.FishMoveSecs));
			}
		}
		break;
	case 15:
	case 16:
	case 17:
		{
			int nSize=PoolAndFish::Instance().m_vecFishGroupType5.size();
			if(nSize>0)
			{
				int index=FishGroupType-15;
				if(index>=nSize)
					index=GameFactorsMgr::GetRand(0,nSize-1);  
				tagFishGroupType5 vFishs=PoolAndFish::Instance().m_vecFishGroupType5[index];
				AddOneGroupFish1_List(vFishs.Arr_Pos,vFishs.arg1,TPoint(0,0),TPoint(5,vFishs.FishMoveSecs));
			}
		}
		break;
	default:   break;
	}
}

//得到一条鱼轨迹，鱼号为0表示服务器端无此轨迹，add by Ivan_han 20130716
Rsp_AddOneFish CFishTraceMgr::GetFishTrace(TFishID FishID)
{
	Rsp_AddOneFish ret;
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardRead guard(&m_lock);	// 只读锁，用于锁目标的遍历、读取
		for (int i=0; i<m_ServerFishTrace.size();++i)
		{
			if(m_ServerFishTrace[i].FishID==FishID)
				return m_ServerFishTrace[i];
		}
	}

	return ret;
}

//得到鱼轨迹的鱼号，鱼号为0表示服务器端无此轨迹，add by Ivan_han 20130716
vector<TFishKind> CFishTraceMgr::GetFishKinds(const vector<TFishID> &vFishID,std::vector<TFishNumOfAck> &vecOut)
{
	vector<TFishKind> ret;
	vecOut.clear();
	for(int i=0;i<vFishID.size();i++)
	{
		Rsp_AddOneFish obj=GetFishTrace(vFishID[i]);
		ret.push_back(obj.FishKind);
		vecOut.push_back(obj.FishNumOfAck);
	}
	return ret;
}

//屏幕内轨迹检测，返回屏幕内轨迹的渔币总量，鱼号为0表示检查屏幕内所有轨迹，add by Ivan_han 20130717
int CFishTraceMgr::CheckFishTrace(TFishKind FishKind,std::vector<TFishID> &vecOut)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	TBuildTraceTime NowTime=CFishTable::GetTickCount64();	// 获得当前的 ms 时间
	int ret=0;

	vecOut.clear();
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardRead guard(&m_lock);	// 只读锁，用于锁目标的遍历、读取
		TVECT_FISH_TRACE::iterator it = m_ServerFishTrace.begin();
		while(it != m_ServerFishTrace.end())
		{
			//简化处理
			//全屏炸弹不能炸全屏炸弹，同类炸弹不能炸同类炸弹，全屏炸弹可以炸同类炸弹，add by Ivan_han 20130731
			//if (NowTime<=((*it).BuildTraceTime+(*it).FishMoveSecs*900) && NowTime>=((*it).BuildTraceTime+(*it).FishMoveSecs*100) && ((FishKind==0 && (*it).FishKind!=111)||(*it).FishKind==FishKind))
			//if (NowTime<=((*it).BuildTraceTime+(*it).FishDepartureTime) && NowTime>=((*it).BuildTraceTime+(*it).FishEntryTime) && ((FishKind==0 && (*it).FishKind!=111)||(*it).FishKind==FishKind))
			//add by Ivan_han 20130807
			bool bSatisfied=false;
			if((FishKind==0 && (*it).FishKind!=111)||(*it).FishKind==FishKind)
			{
				if((*it).FishPathType==1)
				{
					TPoint pt;
					bSatisfied=LinePtInScreenRect((*it).startP,(*it).arg1,(*it).FishMoveSecs,NowTime-(*it).BuildTraceTime,pt);
				}
				else
				{
					bSatisfied=(NowTime<=((*it).BuildTraceTime+(*it).FishDepartureTime*1000) && NowTime>=((*it).BuildTraceTime+(*it).FishEntryTime*1000));
				}
			}
			if(bSatisfied)
			{
				vecOut.push_back((*it).FishID);
				const CTabFishItem *pFishLocalInfo=CTabFishCache::Instance().Find((*it).FishKind);
				if(pFishLocalInfo)
				{
					ret+=pFishLocalInfo->m_nFishMulti;
				}
			}

			it++;
		}
	}
	return ret;
}

//销毁一条轨迹
bool CFishTraceMgr::DestroyFishTrace(TFishID FishID)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
		TVECT_FISH_TRACE::iterator it = m_ServerFishTrace.begin();
		TVECT_FISH_TRACE::iterator end = m_ServerFishTrace.end();
		while(it != end)
		{
			if ((*it).FishID == FishID)
			{
				m_ServerFishTrace.erase(it);
				return true;
			}
			++it;
		}
	}
	return false;
}

//销毁轨迹检测
int CFishTraceMgr::DestroyFishTrace(std::vector<TFishID> &vecOut)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	TBuildTraceTime NowTime=CFishTable::GetTickCount64();	// 获得当前的 ms 时间
	int ret=0;

	vecOut.clear();
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
		TVECT_FISH_TRACE::iterator it = m_ServerFishTrace.begin();
		while(it != m_ServerFishTrace.end())
		{
			//判断时间,FISH_ALIVE_TIME=(*it).FishMoveSecsv!≡20
			if (NowTime>=((*it).BuildTraceTime+(*it).FishMoveSecs*1000))
			{
				vecOut.push_back((*it).FishID);
				it=m_ServerFishTrace.erase(it);
				ret++;
			}
			else
				it++;
		}
	}
	return ret;
}

//销毁多条轨迹，DeadFullScreenBombFishID=0表示vDeadFishID里面没有全屏炸弹
std::vector<TFishID> CFishTraceMgr::DestroySomeFishTrace(const std::vector<TFishID> &vDeadFishID,std::vector<TFishKind> &vDeadFishKind,TFishID &DeadFullScreenBombFishID)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	std::vector<TFishID> vDeadFishID1;
	vDeadFishKind.clear();
	DeadFullScreenBombFishID=0;
	// 此锁仅在本括号内生效，出了括号就自动解锁啦
	CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
	for (int i=0; i<vDeadFishID.size();i++)
	{
		unsigned int unFishID = vDeadFishID[i];
		TVECT_FISH_TRACE::iterator vIt = m_ServerFishTrace.begin();
		for (; vIt != m_ServerFishTrace.end(); ++vIt)
		{
			if (vIt->FishID == unFishID)
			{
				if(vIt->FishKind==111)
					DeadFullScreenBombFishID=unFishID;
				vDeadFishKind.push_back(vIt->FishKind);
				m_ServerFishTrace.erase( vIt );
				vDeadFishID1.push_back(unFishID);
				break;
			}
		}
	}
	return vDeadFishID1;
}

std::vector<TFishID> CFishTraceMgr::UpdateSomeFishTrace(const std::vector<TFishID> &vHitFishID,const std::vector<TFishID> &vDeadFishID)
{
	// 死循环监测，必需放在第一行
	CEndlessLoopGuard stEndlessLoopGuard(CEndlessLoop::get_singleton_ptr(), __FUNCTION__);

	std::vector<TFishID> vUnDeadFishID=vHitFishID;

	for(int i=0;i<vDeadFishID.size();i++)
		vUnDeadFishID.erase(remove(vUnDeadFishID.begin(),vUnDeadFishID.end(),vDeadFishID[i]),vUnDeadFishID.end());

	// 此锁仅在本括号内生效，出了括号就自动解锁啦
	CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
	for (int i=0; i<vUnDeadFishID.size();i++)
	{
		unsigned int unFishID = vUnDeadFishID[i];
		TVECT_FISH_TRACE::iterator vIt = m_ServerFishTrace.begin();
		for (; vIt != m_ServerFishTrace.end(); ++vIt)
		{
			if (vIt->FishID == unFishID)
			{
				vIt->FishNumOfAck++;
				break;
			}
		}
	}
	return vUnDeadFishID;
}

//销毁所有的轨迹
void CFishTraceMgr::clearFishTrace()
{
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardWrite guard(&m_lock);	// 写锁，用于锁目标的增、删、改
		m_ServerFishTrace.clear();
	}
}
//举手
int CFishTraceMgr::OnRaiseHand(int iSeatNo)
{
	if(get_fish_table()==NULL)
		return 0;

	//char xmlFileName[200]="FishTrace/fish_one.xml";
	//CBezier3TraceCache m_Bezier3TraceCache1(xmlFileName);
	
	{
		// 此锁仅在本括号内生效，出了括号就自动解锁啦
		CThreadGuardRead guard(&m_lock);	// 只读锁，用于锁目标的遍历、读取
		//发鱼轨迹给举手的玩家
		for (int i=0; i<m_ServerFishTrace.size();++i)
		{
			//先前的鱼阵不发给后进桌子的玩家，20130702
			if(m_ServerFishTrace[i].FishGroupType>0 && m_ServerFishTrace[i].FishGroupType <100)
				continue;
			get_fish_table()->send_data(iSeatNo,TABLE_MAIN, RSP_ADD_ONE_FISH, (BYTE*)(&m_ServerFishTrace[i]), sizeof(Rsp_AddOneFish));
		}
	}

	return 0;
}

// 桌子定时器响应
int CFishTraceMgr::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(get_fish_table()==NULL)
		return 0;

	if (iTableNo !=  get_fish_table()->m_stTableInfo.iTableNo)
		return 0;

	//事件处理
	switch (iIDEvent)
	{
	case IDI_SYS_MESSAGE:				//系统消息
		{
			//return SendSysMessage();
			return 0;
		}
	case IDI_BONUS:	//递增彩金
		{
			//return GenerateBonus();
			return 0;
		}
	case IDI_CLEAR_TRACE://销毁轨迹定时器IDI_CLEAR_TRACE=2
		{
			std::vector<TFishID> vecOut;
			int ret=DestroyFishTrace(vecOut);
			//printf("销毁%d条轨迹\n",ret);
			return 0;
		}
	//case IDI_CHANGE_SCENE:			//切换场景
	//	{
	//		//add by Ivan_han 20130805
	//		m_FishStateMgr.SwitchScene();
	//		get_fish_table()->set_table_timer(IDI_CHANGE_SCENE,m_FishStateMgr.SwitchSceneTime());
	//		return 0;
	//	}
	default:
		if (m_FishStateMgr.m_pCurFishState)
		{
			return m_FishStateMgr.m_pCurFishState->OnTableTimer(iTableNo,iIDEvent);
		}
		break;

	}
	return 0;
}

//游戏开始
int CFishTraceMgr::OnGameBegin()
{
	if(get_fish_table()==NULL)
		return 0;

	clearFishTrace();
	//get_fish_table()->set_table_timer(IDI_CHANGE_SCENE,PoolAndFish::Instance().GetCaptureTime());
	get_fish_table()->set_table_timer(IDI_CLEAR_TRACE,TIME_CLEAR_TRACE);

	//利用这里的开关可以测试捕渔期或休渔期
#if 1
	m_FishStateMgr.m_pCurFishState = &(m_FishStateMgr.m_CaptureFishState);
#else
	m_FishStateMgr.m_pCurFishState = &(m_FishStateMgr.m_OffFishState);
#endif
	m_FishStateMgr.m_pCurFishState->Enter();

	return 0;
}

//游戏结束
int CFishTraceMgr::OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	if(get_fish_table()==NULL)
		return 0;

	//get_fish_table()->kill_table_timer(IDI_CHANGE_SCENE);
	get_fish_table()->kill_table_timer(IDI_CLEAR_TRACE);

	clearFishTrace();

	if (m_FishStateMgr.m_pCurFishState != NULL)
	{
		m_FishStateMgr.m_pCurFishState->Leave();
		m_FishStateMgr.m_pCurFishState = NULL;
	}

	return 0;
}
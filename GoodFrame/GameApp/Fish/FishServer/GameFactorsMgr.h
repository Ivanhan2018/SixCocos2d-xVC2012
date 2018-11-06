#pragma once
#include "GameFactor.h"
#include "FishTraceMgr.h"
#include "FishStateMgr.h"//add by Ivan_han 20130823
#include<vector>
using namespace std;

class CAwardPool;
class TiXmlElement;

typedef double TCollisionScoreValue;
typedef unsigned short int TFishGroupType;//鱼群鱼阵类型
typedef unsigned char TFishMoveSecs;//鱼轨迹时长，也就是鱼的最长存活时间

/*
	读取xml文件中的奖池抽放水、碰撞得分下、上限等配置参数,add by Ivan_han 20130619
	读取xml文件中的发鱼策略参数、鱼阵参数,add by Ivan_han 20130628
	读取xml文件中的鱼群参数,add by Ivan_han 20130701
*/
class PoolAndFish
{
public:
	PoolAndFish(const char *xmlFileName=NULL)
	{
		//m_FishMoveSecs_3=3;
		//m_FishMoveSecs_4=4;
		memset(this,0,(char *)&m_vecFishGroupType104-(char *)this);
		if(xmlFileName!=NULL)
			LoadData(xmlFileName);
	}
	static PoolAndFish & Instance();
	//根据所给字符对字符串进行分割
	static vector<string> split(const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0);
	static TPos GetCirclePos(TPos startP,TPos centerP,float deltArg);
	//起点数组关于x=640的对称数组
	static vector<TFishPos> GetAxisymmetricFishPos(const vector<TFishPos>& vFishs);
	static bool LoadFishGroupType234(TiXmlElement* Node,TFishGroupType FishGroupType,vector<TFishPos> &vec);
	int LoadData(const char *xmlFileName);
	TFishMoveSecs GetFishMoveSecs(TFishGroupType FishGroupType)const;
	//获取捕渔期持续时间
	int GetCaptureTime()const;
	//获取休渔期持续时间
	int GetOffTime()const;
	int GetCaptureBuildTraceTime()const;
	int GetOffBuildTraceTime()const;
	TProbValue GetIsFishProb()const;
	//获取某种鱼的所有列阵鱼群轨迹
	vector<tagFishGroupType104> GetAll104(TFishKind FishKind)const;
	//获取某种鱼的所有列队鱼群轨迹
	vector<tagFishGroupType105> GetAll105(TFishKind FishKind)const;
public:
	bool m_HasLoadOK;//是否加载成功过
	/*
		<PoolDrawAndDropWater Vh0="12000" Vl0="8000" V0="10000" loVh="11000" hiVh="20000" loVl="0" hiVl="9000" mul="0.80" muh="1.20" V="1500000.00" mu="1.10"/> 
		<CollisionScore pil="11.81" pih="116.76" /> 
	*/
	TAwardPoolValue m_Vh0;//初始上水位
	TAwardPoolValue m_Vl0;//初始下水位
	TAwardPoolValue m_V0;//初始水平面
	TAwardPoolValue m_V;//当前水平面
	TAwardPoolValue m_loVh;//上水位标区间下界
	TAwardPoolValue m_hiVh;//上水位标区间上界
	TAwardPoolValue m_loVl;//下水位标区间下界
	TAwardPoolValue m_hiVl;//下水位标区间上界
	TCollisionScoreValue m_mul;//mu下限倍数
	TCollisionScoreValue m_muh;//mu上限倍数
	TCollisionScoreValue m_mu;//当前mu
	TCollisionScoreValue m_pil;//pi下限
	TCollisionScoreValue m_pih;//pi上限

	//<GameDifficulty_x1 Difficulty="6" Score="50" Scorel="50" Scoreh="50" Weight="10" ProbValue="0.8" Remarks="[1,11]" /> 
	int   m_Difficulty_x1;  //L值∈[1,11]，游戏难度
	int   m_Score_x1;  //游戏因素得分，满分为100
	int   m_Weight_x1;  //游戏因素相对权重
	TProbValue m_ProbValue_x1;//游戏因素的条件击毙概率

	//<CannonGrade_x2 CannonGrade="20" Score="100" Scorel="43" Scoreh="100" Weight="10" ProbValue="0.8" Remarks="最大为20" /> 
    int   m_CannonGrade_x2;  //大炮倍率∈[1,20]，大炮等级
	int   m_Score_x2;
	int   m_Weight_x2;
	TProbValue m_ProbValue_x2;

	//<PoolWaterLevelRatio_x4 Score="25" Scorel="0" Scoreh="100" Weight="30" ProbValue="0.8" Remarks="可在PoolDrawAndDropWater结点中修改" /> 
	int   m_Score_x4;
	int   m_Weight_x4;
	TProbValue m_ProbValue_x4;

	//<PlayerLuck_x6 PlayerLuck="60" Score="60" Scorel="0" Scoreh="100" Weight="40" ProbValue="0.8" Remarks="按平均计算" /> 
	int   m_PlayerLuck_x6;  //x_6值∈[0,100]
	int   m_Score_x6;
	int   m_Weight_x6;
	TProbValue m_ProbValue_x6;

	//<PlayerProfit_x7 PlayerProfit="0" Score="50" Scorel="0" Scoreh="100" Weight="30" ProbValue="0.8" Remarks="[-20000,20000],T=1" /> 
    int   m_PlayerProfit_x7;  //W/T值，负数表示输了，正数表示赢了
	int   m_Score_x7;
	int   m_Weight_x7;
	TProbValue m_ProbValue_x7;

	//<PlayerNewFlag_x8 PlayerNewFlag="0" Score="0" Scorel="0" Scoreh="100" Weight="10" ProbValue="0.8" Remarks="新手为1" /> 
    bool   m_PlayerNewFlag_x8;  //玩家新手标志
	int   m_Score_x8;
	int   m_Weight_x8;
	TProbValue m_ProbValue_x8;

	//<PlayerGameTime_x9 PlayerGameTime="0" Score="0" Scorel="0" Scoreh="100" Weight="5" ProbValue="0.8" Remarks="最大为100分钟" /> 
	int   m_PlayerGameTime_x9;  //T值，玩家本次游戏时间(m)
	int   m_Score_x9;
	int   m_Weight_x9;
	TProbValue m_ProbValue_x9;

	//<FishGameFactor_x5 FishNumOfAck="2" Score="100" Scorel="0" Scoreh="100" Weight="30" ProbValue="0.8" Remarks="可在csv中修改" /> 
	int   m_FishNumOfAck_x5;//F_1值，鱼的被攻击次数
	int   m_Score_x5;
	int   m_Weight_x5;
	TProbValue m_ProbValue_x5;

	//<FishStateMgr SwitchSceneTime="60000" CaptureBuildTraceTime="300" OffBuildTraceTime="2000" IsFishProb="0.9"></FishStateMgr>
	int m_CaptureTime;//捕渔期持续时间
	int m_OffTime;//休渔期持续时间
	int m_CaptureBuildTraceTime;
	int m_OffBuildTraceTime;

	TProbValue m_IsFishProb;//捕渔期产生鱼或炸弹时，是鱼的概率

	//add by Ivan_han 20130829
	vector<int> m_vecTypeSeq;

	TFishMoveSecs m_FishMoveSecs_1;
	TFishMoveSecs m_FishMoveSecs_2;
	TFishMoveSecs m_FishMoveSecs_3;
	TFishMoveSecs m_FishMoveSecs_4;

	vector<tagFishGroupType104> m_vecFishGroupType104;
	vector<tagFishGroupType105> m_vecFishGroupType105;
    //由上面数据导出来的数据
	vector<tagFishGroupType104> m_vecAll104[3];
	vector<tagFishGroupType105> m_vecAll105[10];

	vector<vector<TFishPos>> m_vecAll1;
	vector<vector<TFishPos>> m_vecAll2;
	vector<vector<TFishPos>> m_vecAll3;
	vector<vector<TFishPos>> m_vecAll4;

	//add by Ivan_han 20130802
	vector<tagFishGroupType5> m_vecFishGroupType5;
	vector<tagFishGroupType5> m_vecFishGroupType5LToR;

	//add by Ivan_han 20130823
	vector<vector<OffFishState::TFishGroupTypeSeqElem>> m_vecAllFishGroupTypeSeq;
};

/*
	单个玩家的游戏因素信息，add by Ivan_han 20130812
*/
class PlayerFactorInfo
{
public:
   PlayerProfitInfo m_PlayerProfitInfo;
   PlayerNewFlagInfo m_PlayerNewFlagInfo;
   PlayerGameTimeInfo m_PlayerGameTimeInfo;
   PlayerCannonGradeInfo m_PlayerCannonGradeInfo;
};

//游戏因素对象管理类
class GameFactorsMgr
{
public:
	GameFactorsMgr(CAwardPool *pAwardPool=NULL);
	~GameFactorsMgr(void);

	/*
		m_PoolAlgorithmType=1
	*/
	void setMU(TCollisionScoreValue mu);
	void updateCollisionScore();
	TCollisionScoreValue getCollisionScore()const;

	/*
		m_PoolAlgorithmType=2,0
	*/
	//取[nMin,nMax]之间的随机整数
	static int GetRand(const int nMin,const int nMax);
	//取[lo,hi]之间的随机双精度实数
	static TAwardPoolValue GetRandEx(const TAwardPoolValue lo,const TAwardPoolValue hi);
	//根据概率选择，返回true的概率为p
	static bool SelectBoolByProb(TProbValue p);
	//根据概率选择
	static int SelectByProb(int arr[],int arrProb[],int count,int total=0);
	/*
	    根据概率生成鱼或炸弹，增加一个参数RandType用于减少调用rand的次数
		RandType=1表示生成鱼
		RandType=2表示生成炸弹
		RandType=0或其他表示生成鱼或炸弹
	*/
	static TFishKind GetFishKindByProb(int RandType=0);
	//根据概率生成小鱼、大鱼、炸弹,type={1小鱼,2大鱼,3炸弹}
	static TFishKind GetFishKindByProbEx(int type);

	//取出一个击中的鱼,计算击毙概率P，返回true表示该鱼被击毙,false表示该鱼不被击毙
	bool OnCalcProbValue(int iSeatNo,TFishID FishID,TFishKind nFishKind,TFishNumOfAck FishNumOfAck,unsigned int nHitFishCount,TFallIntegral *pG,vector<TFishID> &vOtherDeadFishID, int &iFeats);
	//攻击结算
	TFallIntegral OnAttackSettlement(int iSeatNo,const vector<TFishID> &vFishID,const vector<TFishKind> &vFishKind,const vector<TFishNumOfAck> &vFishNumOfAck,vector<TFishID> &vDeadFishID,TGunGrade GunGrade, int &iFeats);

	void updateProbValue();
	TProbValue getProbValue()const;

public:
	int m_PoolAlgorithmType;//0:基于击毙概率的奖池算法（简化版）;1:基于碰撞得分的奖池算法;2:基于击毙概率的奖池算法;
	TCollisionScoreValue  m_mu;//μ值∈[0,1.5]，奖池抽放水加成

	//游戏因素x_1到x_9
	GameDifficulty m_GameDifficulty;//x_1
	CannonGrade m_CannonGrade;//x_2
	//FishGrade m_FishGrade;//x_3
	PoolWaterLevelRatio m_PoolWaterLevelRatio;//x_4
	//FishNumOfAck m_FishNumOfAck;//x_5
		   
	//单个玩家的游戏因素
	PlayerLuck m_PlayerLuck;//x_6
	PlayerProfit m_PlayerProfit;//x_7
	PlayerNewFlag m_PlayerNewFlag;//x_8
	PlayerGameTime m_PlayerGameTime;//x_9

	FishGameFactor m_FishGameFactor;//综合了x_3和x_5,权重y_35=y_3+y_5,得分x_35=x_3*y_3+x_5*y_5

	vector<GameFactor *> m_GameFactors;//所有的游戏因素
	/*
	   m_PoolAlgorithmType=0
	*/
	TCollisionScoreValue m_CollisionScore;//计算出来的碰撞得分∈[0,150]

	/*
	   m_PoolAlgorithmType=2，P=D*F*C*N
	*/
	TProbValue m_ProbValue;//鱼被捕获后的击毙概率P

	//add by Ivan_han 20130812
	PlayerFactorInfo m_PlayerFactorInfo[GAME_PLAYER_COUNT];

	CAwardPool *m_pAwardPool;
};

#pragma once
#include<map>
using namespace std;

typedef double TAwardPoolValue;//奖池里放的是渔币，这样就与房间倍率无关
typedef long long TFallIntegral;//渔币增量或掉落积分(>=0),这里的G分不等同于当前策划文档中的G分
typedef long long TWinIntegral;//扣除炮弹成本后赢的积分
typedef unsigned int TFishID;
typedef unsigned short int TFishKind;
typedef unsigned int TFishMulti;
typedef unsigned char TFishMoveSecs;
typedef unsigned char TFishNumOfAck;
typedef float TProbValue;//[0,1]之间的值,>1按1处理，<0按0处理

//游戏因素基类
class GameFactor
{
public:
	GameFactor()
	{
		m_Score=0;
		m_Weight=0;
		m_ProbValue=0;
	}
	virtual ~GameFactor(){}
	virtual void updateScore(){}
	virtual void updateProbValue(){}
public:
	int   m_Score;  //游戏因素得分，满分为100
	int   m_Weight;  //游戏因素相对权重
	TProbValue m_ProbValue;//游戏因素的条件击毙概率
};

//游戏因素1,游戏难度
class GameDifficulty:public GameFactor
{
public:
	GameDifficulty();
	~GameDifficulty(){}
	void updateScore();
	//D-游戏难度击毙概率
	void updateProbValue();
public:
	int   m_Difficulty;  //L值∈[1,11]，游戏难度
};

/*
	单个玩家的玩家大炮等级信息，add by Ivan_han 20130819
*/
class PlayerCannonGradeInfo
{
public:
	PlayerCannonGradeInfo()
	{
		m_CannonGrade=1;
	}
public:
	int   m_CannonGrade;  //大炮倍率∈[1,20]，大炮等级
};

//游戏因素2,大炮等级
class CannonGrade:public GameFactor
{
public:
	CannonGrade(){}
	~CannonGrade(){}
	void updateScore();
public:
	PlayerCannonGradeInfo   m_PlayerCannonGradeInfo;
};

//游戏因素4,奖池水位比例
class PoolWaterLevelRatio:public GameFactor
{
public:
	PoolWaterLevelRatio()
	{
		m_V=0;
		m_Vh=0;
		m_Vl=0;
	}
	~PoolWaterLevelRatio(){}
	//取出一个击中的鱼
	void updatePoolWaterLevelRatio(TAwardPoolValue V,TAwardPoolValue Vh,TAwardPoolValue Vl);
	void updateScore();
	//C--奖池条件击毙概率
	void updateProbValue();
	//比较奖池和G分
	bool IsPaid(TFallIntegral G)const;
public:
	TAwardPoolValue   m_V;  //水平面值
	TAwardPoolValue   m_Vh;  //上水位标
	TAwardPoolValue   m_Vl;  //下水位标
};

//游戏因素6,玩家运气
class PlayerLuck:public GameFactor
{
public:
	PlayerLuck()
	{
		m_PlayerLuck=0;
	}
	~PlayerLuck(){}
	void updateScore();
public:
	int   m_PlayerLuck;  //x_6值∈[0,100]
};

/*
	单个玩家的玩家输赢状况信息，add by Ivan_han 20130812
*/
class PlayerProfitInfo
{
public:
	PlayerProfitInfo()
	{
		m_PlayerProfit=0;
		m_dT=60000;
		m_T=0;
	}
public:
	TWinIntegral   m_PlayerProfit;  //W/T值，负数表示输了，正数表示赢了
	unsigned long long m_dT;//更新W值的时间周期(ms)
	unsigned long long m_T;//更新W值的时刻(ms)
};

//游戏因素7,玩家输赢状况
class PlayerProfit:public GameFactor
{
public:
	PlayerProfit(){}
	~PlayerProfit(){}
	//取出一个击中的鱼
	void updatePlayerProfit(TWinIntegral nPlayerProfit);
	void updateScore();
	//N1-玩家输赢状况
	void updateProbValue();
public:
	PlayerProfitInfo m_PlayerProfitInfo;
};

/*
	单个玩家的玩家新手标志信息，add by Ivan_han 20130814
*/
class PlayerNewFlagInfo
{
public:
	PlayerNewFlagInfo()
	{
		m_PlayerRegisterTime=0;
		m_PlayerNewFlag=true;
	}
public:
	long long m_PlayerRegisterTime;//s,玩家的注册时间距离1970年的秒数
	bool   m_PlayerNewFlag;//玩家新手标志
};

//游戏因素8,玩家新手标志
class PlayerNewFlag:public GameFactor
{
public:
	PlayerNewFlag()
	{
		updateProbValue();
	}
	~PlayerNewFlag(){}
	//取出一个击中的鱼
	void updatePlayerNewFlag(bool bPlayerNewFlag);
	void updateScore();
	//N2-玩家新手标示
	void updateProbValue();
public:
	PlayerNewFlagInfo m_PlayerNewFlagInfo;
};

/*
	单个玩家的玩家本次游戏时间信息，add by Ivan_han 20130814
*/
class PlayerGameTimeInfo
{
public:
	PlayerGameTimeInfo()
	{
		m_PlayerBeginGameTime=0;
		m_PlayerGameTime=0;
	}
public:
	unsigned long long m_PlayerBeginGameTime;//ms,玩家本次游戏开始时间
	unsigned long long m_PlayerGameTime;//ms,T值，玩家本次游戏时间(m)
};

//游戏因素9,玩家本次游戏时间
class PlayerGameTime:public GameFactor
{
public:
	PlayerGameTime(){}
	~PlayerGameTime(){}
	//取出一个击中的鱼
	void updatePlayerGameTime(unsigned long long llPlayerGameTime);
	void updateScore();
	//N3-玩家本次游戏时间
	void updateProbValue();
public:
	PlayerGameTimeInfo   m_PlayerGameTimeInfo;
};

//“鱼的数值表”表节点
class CTabFishItem
{
public:
	CTabFishItem()
	{
		memset(this,0,sizeof(CTabFishItem));
	}
public:
	TFishKind m_nFishKind;//鱼的种类
	char m_szFishName[16];//鱼的名称
	TFishMulti m_nFishMulti;//鱼的结算倍率
	float m_fKilledScore;//击毙分数
	int m_nFishBasicNumOfAck;  //F_2值，鱼的基本被攻击次数
	int m_nGenProb;//生成几率
	int m_nFishGradeMin;//鱼的等级得分下限
	int m_nFishGradeMax;//鱼的等级得分上限
	int m_nSceneCapacity;//场景容载量
	int m_nCardsFallProb;//卡牌掉落概率
	int m_nMerit;//获得功勋数量
	//add by Ivan_han 20130731
	TProbValue m_IsGroupProb;//成群概率
	int m_GroupType;//成群形式
	int m_PathLibType;//轨迹库
	int m_nKilledDifficulty;//鱼的击毙难度
	TFishMoveSecs m_nFishMoveSecs;//鱼的轨迹时长
};


//-------------------------“鱼的数值表”缓冲-----------------------------------------------------------
class CTabFishCache
{
public:
	CTabFishCache(const char *pszFilePath="PoolConfig\\FishMultiAndKilledScore.csv");
	static CTabFishCache & Instance();
	int LoadData(const char *pszFilePath);
	const CTabFishItem * Find(TFishKind FishKind);
	//单鱼/鱼群的轨迹时长
	static TFishMoveSecs getFishMoveSecs(TFishKind FishKind);
protected:
	std::map<int,CTabFishItem> m_mapFishCache;
};

//鱼的游戏因素对象(综合了x_3和x_5,权重y_35=y_3+y_5,得分x_35=x_3*y_3+x_5*y_5)
class FishGameFactor:public GameFactor
{
public:
	FishGameFactor()
	{
		m_FishID=0;
		m_nFishKind=0;
		m_nKilledDifficulty=0;
		m_FishNumOfAck=0;
		m_nHitFishCount=1;
	}
	//取出一个击中的鱼
	void updateFishGameFactor(TFishID FishID,TFishKind nFishKind,TFishNumOfAck FishNumOfAck,unsigned int m_nHitFishCount=1);
	//获取鱼的击毙分数
	float getKilledScore()const;
	////增加该鱼的被攻击次数
	//void IncreNumOfAck();
	void updateScore();
	//F-鱼被捕获击毙概率
	void updateProbValue();
public:
	TFishID m_FishID;
	TFishKind m_nFishKind;
	unsigned int   m_nKilledDifficulty;
	TFishNumOfAck   m_FishNumOfAck;//F_1值/F_2值，鱼的被攻击次数
	unsigned int   m_nHitFishCount;//本次捕获鱼的数量F_3
};



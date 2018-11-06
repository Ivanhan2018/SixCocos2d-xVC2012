#pragma once
#include<map>
using namespace std;

typedef double TAwardPoolValue;//������ŵ�����ң��������뷿�䱶���޹�
typedef long long TFallIntegral;//���������������(>=0),�����G�ֲ���ͬ�ڵ�ǰ�߻��ĵ��е�G��
typedef long long TWinIntegral;//�۳��ڵ��ɱ���Ӯ�Ļ���
typedef unsigned int TFishID;
typedef unsigned short int TFishKind;
typedef unsigned int TFishMulti;
typedef unsigned char TFishMoveSecs;
typedef unsigned char TFishNumOfAck;
typedef float TProbValue;//[0,1]֮���ֵ,>1��1����<0��0����

//��Ϸ���ػ���
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
	int   m_Score;  //��Ϸ���ص÷֣�����Ϊ100
	int   m_Weight;  //��Ϸ�������Ȩ��
	TProbValue m_ProbValue;//��Ϸ���ص��������и���
};

//��Ϸ����1,��Ϸ�Ѷ�
class GameDifficulty:public GameFactor
{
public:
	GameDifficulty();
	~GameDifficulty(){}
	void updateScore();
	//D-��Ϸ�ѶȻ��и���
	void updateProbValue();
public:
	int   m_Difficulty;  //Lֵ��[1,11]����Ϸ�Ѷ�
};

/*
	������ҵ���Ҵ��ڵȼ���Ϣ��add by Ivan_han 20130819
*/
class PlayerCannonGradeInfo
{
public:
	PlayerCannonGradeInfo()
	{
		m_CannonGrade=1;
	}
public:
	int   m_CannonGrade;  //���ڱ��ʡ�[1,20]�����ڵȼ�
};

//��Ϸ����2,���ڵȼ�
class CannonGrade:public GameFactor
{
public:
	CannonGrade(){}
	~CannonGrade(){}
	void updateScore();
public:
	PlayerCannonGradeInfo   m_PlayerCannonGradeInfo;
};

//��Ϸ����4,����ˮλ����
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
	//ȡ��һ�����е���
	void updatePoolWaterLevelRatio(TAwardPoolValue V,TAwardPoolValue Vh,TAwardPoolValue Vl);
	void updateScore();
	//C--�����������и���
	void updateProbValue();
	//�ȽϽ��غ�G��
	bool IsPaid(TFallIntegral G)const;
public:
	TAwardPoolValue   m_V;  //ˮƽ��ֵ
	TAwardPoolValue   m_Vh;  //��ˮλ��
	TAwardPoolValue   m_Vl;  //��ˮλ��
};

//��Ϸ����6,�������
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
	int   m_PlayerLuck;  //x_6ֵ��[0,100]
};

/*
	������ҵ������Ӯ״����Ϣ��add by Ivan_han 20130812
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
	TWinIntegral   m_PlayerProfit;  //W/Tֵ��������ʾ���ˣ�������ʾӮ��
	unsigned long long m_dT;//����Wֵ��ʱ������(ms)
	unsigned long long m_T;//����Wֵ��ʱ��(ms)
};

//��Ϸ����7,�����Ӯ״��
class PlayerProfit:public GameFactor
{
public:
	PlayerProfit(){}
	~PlayerProfit(){}
	//ȡ��һ�����е���
	void updatePlayerProfit(TWinIntegral nPlayerProfit);
	void updateScore();
	//N1-�����Ӯ״��
	void updateProbValue();
public:
	PlayerProfitInfo m_PlayerProfitInfo;
};

/*
	������ҵ�������ֱ�־��Ϣ��add by Ivan_han 20130814
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
	long long m_PlayerRegisterTime;//s,��ҵ�ע��ʱ�����1970�������
	bool   m_PlayerNewFlag;//������ֱ�־
};

//��Ϸ����8,������ֱ�־
class PlayerNewFlag:public GameFactor
{
public:
	PlayerNewFlag()
	{
		updateProbValue();
	}
	~PlayerNewFlag(){}
	//ȡ��һ�����е���
	void updatePlayerNewFlag(bool bPlayerNewFlag);
	void updateScore();
	//N2-������ֱ�ʾ
	void updateProbValue();
public:
	PlayerNewFlagInfo m_PlayerNewFlagInfo;
};

/*
	������ҵ���ұ�����Ϸʱ����Ϣ��add by Ivan_han 20130814
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
	unsigned long long m_PlayerBeginGameTime;//ms,��ұ�����Ϸ��ʼʱ��
	unsigned long long m_PlayerGameTime;//ms,Tֵ����ұ�����Ϸʱ��(m)
};

//��Ϸ����9,��ұ�����Ϸʱ��
class PlayerGameTime:public GameFactor
{
public:
	PlayerGameTime(){}
	~PlayerGameTime(){}
	//ȡ��һ�����е���
	void updatePlayerGameTime(unsigned long long llPlayerGameTime);
	void updateScore();
	//N3-��ұ�����Ϸʱ��
	void updateProbValue();
public:
	PlayerGameTimeInfo   m_PlayerGameTimeInfo;
};

//�������ֵ����ڵ�
class CTabFishItem
{
public:
	CTabFishItem()
	{
		memset(this,0,sizeof(CTabFishItem));
	}
public:
	TFishKind m_nFishKind;//�������
	char m_szFishName[16];//�������
	TFishMulti m_nFishMulti;//��Ľ��㱶��
	float m_fKilledScore;//���з���
	int m_nFishBasicNumOfAck;  //F_2ֵ����Ļ�������������
	int m_nGenProb;//���ɼ���
	int m_nFishGradeMin;//��ĵȼ��÷�����
	int m_nFishGradeMax;//��ĵȼ��÷�����
	int m_nSceneCapacity;//����������
	int m_nCardsFallProb;//���Ƶ������
	int m_nMerit;//��ù�ѫ����
	//add by Ivan_han 20130731
	TProbValue m_IsGroupProb;//��Ⱥ����
	int m_GroupType;//��Ⱥ��ʽ
	int m_PathLibType;//�켣��
	int m_nKilledDifficulty;//��Ļ����Ѷ�
	TFishMoveSecs m_nFishMoveSecs;//��Ĺ켣ʱ��
};


//-------------------------�������ֵ������-----------------------------------------------------------
class CTabFishCache
{
public:
	CTabFishCache(const char *pszFilePath="PoolConfig\\FishMultiAndKilledScore.csv");
	static CTabFishCache & Instance();
	int LoadData(const char *pszFilePath);
	const CTabFishItem * Find(TFishKind FishKind);
	//����/��Ⱥ�Ĺ켣ʱ��
	static TFishMoveSecs getFishMoveSecs(TFishKind FishKind);
protected:
	std::map<int,CTabFishItem> m_mapFishCache;
};

//�����Ϸ���ض���(�ۺ���x_3��x_5,Ȩ��y_35=y_3+y_5,�÷�x_35=x_3*y_3+x_5*y_5)
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
	//ȡ��һ�����е���
	void updateFishGameFactor(TFishID FishID,TFishKind nFishKind,TFishNumOfAck FishNumOfAck,unsigned int m_nHitFishCount=1);
	//��ȡ��Ļ��з���
	float getKilledScore()const;
	////���Ӹ���ı���������
	//void IncreNumOfAck();
	void updateScore();
	//F-�㱻������и���
	void updateProbValue();
public:
	TFishID m_FishID;
	TFishKind m_nFishKind;
	unsigned int   m_nKilledDifficulty;
	TFishNumOfAck   m_FishNumOfAck;//F_1ֵ/F_2ֵ����ı���������
	unsigned int   m_nHitFishCount;//���β����������F_3
};



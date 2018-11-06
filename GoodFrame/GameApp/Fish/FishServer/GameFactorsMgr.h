#pragma once
#include "GameFactor.h"
#include "FishTraceMgr.h"
#include "FishStateMgr.h"//add by Ivan_han 20130823
#include<vector>
using namespace std;

class CAwardPool;
class TiXmlElement;

typedef double TCollisionScoreValue;
typedef unsigned short int TFishGroupType;//��Ⱥ��������
typedef unsigned char TFishMoveSecs;//��켣ʱ����Ҳ�����������ʱ��

/*
	��ȡxml�ļ��еĽ��س��ˮ����ײ�÷��¡����޵����ò���,add by Ivan_han 20130619
	��ȡxml�ļ��еķ�����Բ������������,add by Ivan_han 20130628
	��ȡxml�ļ��е���Ⱥ����,add by Ivan_han 20130701
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
	//���������ַ����ַ������зָ�
	static vector<string> split(const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0);
	static TPos GetCirclePos(TPos startP,TPos centerP,float deltArg);
	//����������x=640�ĶԳ�����
	static vector<TFishPos> GetAxisymmetricFishPos(const vector<TFishPos>& vFishs);
	static bool LoadFishGroupType234(TiXmlElement* Node,TFishGroupType FishGroupType,vector<TFishPos> &vec);
	int LoadData(const char *xmlFileName);
	TFishMoveSecs GetFishMoveSecs(TFishGroupType FishGroupType)const;
	//��ȡ�����ڳ���ʱ��
	int GetCaptureTime()const;
	//��ȡ�����ڳ���ʱ��
	int GetOffTime()const;
	int GetCaptureBuildTraceTime()const;
	int GetOffBuildTraceTime()const;
	TProbValue GetIsFishProb()const;
	//��ȡĳ���������������Ⱥ�켣
	vector<tagFishGroupType104> GetAll104(TFishKind FishKind)const;
	//��ȡĳ����������ж���Ⱥ�켣
	vector<tagFishGroupType105> GetAll105(TFishKind FishKind)const;
public:
	bool m_HasLoadOK;//�Ƿ���سɹ���
	/*
		<PoolDrawAndDropWater Vh0="12000" Vl0="8000" V0="10000" loVh="11000" hiVh="20000" loVl="0" hiVl="9000" mul="0.80" muh="1.20" V="1500000.00" mu="1.10"/> 
		<CollisionScore pil="11.81" pih="116.76" /> 
	*/
	TAwardPoolValue m_Vh0;//��ʼ��ˮλ
	TAwardPoolValue m_Vl0;//��ʼ��ˮλ
	TAwardPoolValue m_V0;//��ʼˮƽ��
	TAwardPoolValue m_V;//��ǰˮƽ��
	TAwardPoolValue m_loVh;//��ˮλ�������½�
	TAwardPoolValue m_hiVh;//��ˮλ�������Ͻ�
	TAwardPoolValue m_loVl;//��ˮλ�������½�
	TAwardPoolValue m_hiVl;//��ˮλ�������Ͻ�
	TCollisionScoreValue m_mul;//mu���ޱ���
	TCollisionScoreValue m_muh;//mu���ޱ���
	TCollisionScoreValue m_mu;//��ǰmu
	TCollisionScoreValue m_pil;//pi����
	TCollisionScoreValue m_pih;//pi����

	//<GameDifficulty_x1 Difficulty="6" Score="50" Scorel="50" Scoreh="50" Weight="10" ProbValue="0.8" Remarks="[1,11]" /> 
	int   m_Difficulty_x1;  //Lֵ��[1,11]����Ϸ�Ѷ�
	int   m_Score_x1;  //��Ϸ���ص÷֣�����Ϊ100
	int   m_Weight_x1;  //��Ϸ�������Ȩ��
	TProbValue m_ProbValue_x1;//��Ϸ���ص��������и���

	//<CannonGrade_x2 CannonGrade="20" Score="100" Scorel="43" Scoreh="100" Weight="10" ProbValue="0.8" Remarks="���Ϊ20" /> 
    int   m_CannonGrade_x2;  //���ڱ��ʡ�[1,20]�����ڵȼ�
	int   m_Score_x2;
	int   m_Weight_x2;
	TProbValue m_ProbValue_x2;

	//<PoolWaterLevelRatio_x4 Score="25" Scorel="0" Scoreh="100" Weight="30" ProbValue="0.8" Remarks="����PoolDrawAndDropWater������޸�" /> 
	int   m_Score_x4;
	int   m_Weight_x4;
	TProbValue m_ProbValue_x4;

	//<PlayerLuck_x6 PlayerLuck="60" Score="60" Scorel="0" Scoreh="100" Weight="40" ProbValue="0.8" Remarks="��ƽ������" /> 
	int   m_PlayerLuck_x6;  //x_6ֵ��[0,100]
	int   m_Score_x6;
	int   m_Weight_x6;
	TProbValue m_ProbValue_x6;

	//<PlayerProfit_x7 PlayerProfit="0" Score="50" Scorel="0" Scoreh="100" Weight="30" ProbValue="0.8" Remarks="[-20000,20000],T=1" /> 
    int   m_PlayerProfit_x7;  //W/Tֵ��������ʾ���ˣ�������ʾӮ��
	int   m_Score_x7;
	int   m_Weight_x7;
	TProbValue m_ProbValue_x7;

	//<PlayerNewFlag_x8 PlayerNewFlag="0" Score="0" Scorel="0" Scoreh="100" Weight="10" ProbValue="0.8" Remarks="����Ϊ1" /> 
    bool   m_PlayerNewFlag_x8;  //������ֱ�־
	int   m_Score_x8;
	int   m_Weight_x8;
	TProbValue m_ProbValue_x8;

	//<PlayerGameTime_x9 PlayerGameTime="0" Score="0" Scorel="0" Scoreh="100" Weight="5" ProbValue="0.8" Remarks="���Ϊ100����" /> 
	int   m_PlayerGameTime_x9;  //Tֵ����ұ�����Ϸʱ��(m)
	int   m_Score_x9;
	int   m_Weight_x9;
	TProbValue m_ProbValue_x9;

	//<FishGameFactor_x5 FishNumOfAck="2" Score="100" Scorel="0" Scoreh="100" Weight="30" ProbValue="0.8" Remarks="����csv���޸�" /> 
	int   m_FishNumOfAck_x5;//F_1ֵ����ı���������
	int   m_Score_x5;
	int   m_Weight_x5;
	TProbValue m_ProbValue_x5;

	//<FishStateMgr SwitchSceneTime="60000" CaptureBuildTraceTime="300" OffBuildTraceTime="2000" IsFishProb="0.9"></FishStateMgr>
	int m_CaptureTime;//�����ڳ���ʱ��
	int m_OffTime;//�����ڳ���ʱ��
	int m_CaptureBuildTraceTime;
	int m_OffBuildTraceTime;

	TProbValue m_IsFishProb;//�����ڲ������ը��ʱ������ĸ���

	//add by Ivan_han 20130829
	vector<int> m_vecTypeSeq;

	TFishMoveSecs m_FishMoveSecs_1;
	TFishMoveSecs m_FishMoveSecs_2;
	TFishMoveSecs m_FishMoveSecs_3;
	TFishMoveSecs m_FishMoveSecs_4;

	vector<tagFishGroupType104> m_vecFishGroupType104;
	vector<tagFishGroupType105> m_vecFishGroupType105;
    //���������ݵ�����������
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
	������ҵ���Ϸ������Ϣ��add by Ivan_han 20130812
*/
class PlayerFactorInfo
{
public:
   PlayerProfitInfo m_PlayerProfitInfo;
   PlayerNewFlagInfo m_PlayerNewFlagInfo;
   PlayerGameTimeInfo m_PlayerGameTimeInfo;
   PlayerCannonGradeInfo m_PlayerCannonGradeInfo;
};

//��Ϸ���ض��������
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
	//ȡ[nMin,nMax]֮����������
	static int GetRand(const int nMin,const int nMax);
	//ȡ[lo,hi]֮������˫����ʵ��
	static TAwardPoolValue GetRandEx(const TAwardPoolValue lo,const TAwardPoolValue hi);
	//���ݸ���ѡ�񣬷���true�ĸ���Ϊp
	static bool SelectBoolByProb(TProbValue p);
	//���ݸ���ѡ��
	static int SelectByProb(int arr[],int arrProb[],int count,int total=0);
	/*
	    ���ݸ����������ը��������һ������RandType���ڼ��ٵ���rand�Ĵ���
		RandType=1��ʾ������
		RandType=2��ʾ����ը��
		RandType=0��������ʾ�������ը��
	*/
	static TFishKind GetFishKindByProb(int RandType=0);
	//���ݸ�������С�㡢���㡢ը��,type={1С��,2����,3ը��}
	static TFishKind GetFishKindByProbEx(int type);

	//ȡ��һ�����е���,������и���P������true��ʾ���㱻����,false��ʾ���㲻������
	bool OnCalcProbValue(int iSeatNo,TFishID FishID,TFishKind nFishKind,TFishNumOfAck FishNumOfAck,unsigned int nHitFishCount,TFallIntegral *pG,vector<TFishID> &vOtherDeadFishID, int &iFeats);
	//��������
	TFallIntegral OnAttackSettlement(int iSeatNo,const vector<TFishID> &vFishID,const vector<TFishKind> &vFishKind,const vector<TFishNumOfAck> &vFishNumOfAck,vector<TFishID> &vDeadFishID,TGunGrade GunGrade, int &iFeats);

	void updateProbValue();
	TProbValue getProbValue()const;

public:
	int m_PoolAlgorithmType;//0:���ڻ��и��ʵĽ����㷨���򻯰棩;1:������ײ�÷ֵĽ����㷨;2:���ڻ��и��ʵĽ����㷨;
	TCollisionScoreValue  m_mu;//��ֵ��[0,1.5]�����س��ˮ�ӳ�

	//��Ϸ����x_1��x_9
	GameDifficulty m_GameDifficulty;//x_1
	CannonGrade m_CannonGrade;//x_2
	//FishGrade m_FishGrade;//x_3
	PoolWaterLevelRatio m_PoolWaterLevelRatio;//x_4
	//FishNumOfAck m_FishNumOfAck;//x_5
		   
	//������ҵ���Ϸ����
	PlayerLuck m_PlayerLuck;//x_6
	PlayerProfit m_PlayerProfit;//x_7
	PlayerNewFlag m_PlayerNewFlag;//x_8
	PlayerGameTime m_PlayerGameTime;//x_9

	FishGameFactor m_FishGameFactor;//�ۺ���x_3��x_5,Ȩ��y_35=y_3+y_5,�÷�x_35=x_3*y_3+x_5*y_5

	vector<GameFactor *> m_GameFactors;//���е���Ϸ����
	/*
	   m_PoolAlgorithmType=0
	*/
	TCollisionScoreValue m_CollisionScore;//�����������ײ�÷֡�[0,150]

	/*
	   m_PoolAlgorithmType=2��P=D*F*C*N
	*/
	TProbValue m_ProbValue;//�㱻�����Ļ��и���P

	//add by Ivan_han 20130812
	PlayerFactorInfo m_PlayerFactorInfo[GAME_PLAYER_COUNT];

	CAwardPool *m_pAwardPool;
};

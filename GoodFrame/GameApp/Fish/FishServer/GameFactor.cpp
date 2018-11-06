#include "GameFactor.h"
#include "GameFactorsMgr.h"
#include "./EndlessLoopGuard.h"	// 死循环守护

GameDifficulty::GameDifficulty()
{
	m_Difficulty=PoolAndFish::Instance().m_Difficulty_x1;
	if(m_Difficulty<1||m_Difficulty>11)
		m_Difficulty=5;
	updateProbValue();
}

void GameDifficulty::updateScore()
{
	static int Scores[11]={100,90,80,70,60,50,40,30,20,10,0};
	if(m_Difficulty<1||m_Difficulty>11)
	{
		return;
	}
	m_Score=Scores[m_Difficulty-1];
}

void GameDifficulty::updateProbValue()
{
	if(m_Difficulty<1||m_Difficulty>11)
	{
		return;
	}
	m_ProbValue=1.f+0.05*(6-m_Difficulty);
}

void CannonGrade::updateScore()
{
	if(m_PlayerCannonGradeInfo.m_CannonGrade<1||m_PlayerCannonGradeInfo.m_CannonGrade>20)
	{
		return;
	}
	m_Score=40+3*m_PlayerCannonGradeInfo.m_CannonGrade;
}

void PoolWaterLevelRatio::updatePoolWaterLevelRatio(TAwardPoolValue V,TAwardPoolValue Vh,TAwardPoolValue Vl)
{
	m_V=V;
	m_Vh=Vh;
	m_Vl=Vl;
}

void PoolWaterLevelRatio::updateScore()
{
	if(m_Vl>=m_Vh)
	{
		return;
	}
	if(m_V<m_Vl)
	{
		m_Score=0;
		return;
	}
	if(m_V>m_Vh)
	{
		m_Score=100;
		return;
	}
	m_Score=100*(m_V-m_Vl)/(m_Vh-m_Vl);
}

void PoolWaterLevelRatio::updateProbValue()
{
	TProbValue C=0;
	if(m_V<m_Vl)
	{
		C=0;
		m_ProbValue=C;
		return;
	}
	if(m_V>m_Vh)
	{
		C=10;
		m_ProbValue=C;
		return;
	}
	C=0.2*GameFactorsMgr::GetRand(8,12)*(m_V-m_Vl)/(m_Vh-m_Vl);
	m_ProbValue=C;
}

//比较奖池和G分
bool PoolWaterLevelRatio::IsPaid(TFallIntegral G)const
{
	return m_V-m_Vl-G>=0;
}

void PlayerLuck::updateScore()
{
	m_PlayerLuck=rand()%101;
	m_Score=m_PlayerLuck;
}

void PlayerProfit::updatePlayerProfit(TWinIntegral nPlayerProfit)
{
	m_PlayerProfitInfo.m_PlayerProfit=nPlayerProfit;
}

void PlayerProfit::updateScore()
{
	if(m_PlayerProfitInfo.m_PlayerProfit<-20000)
	{
		m_Score=100;
		return;
	}
	if(m_PlayerProfitInfo.m_PlayerProfit>20000)
	{
		m_Score=0;
		return;
	}
	m_Score=-0.0025*m_PlayerProfitInfo.m_PlayerProfit+50;
}

void PlayerProfit::updateProbValue()
{
	TWinIntegral n1=-0.001*m_PlayerProfitInfo.m_PlayerProfit;
	TProbValue N1=n1;
	if(m_PlayerProfitInfo.m_PlayerProfit<-200)
	{
		N1=0.2;
	}
	if(m_PlayerProfitInfo.m_PlayerProfit>200)
	{
		N1=-0.2;
	}
	m_ProbValue=N1;
}

void PlayerNewFlag::updatePlayerNewFlag(bool bPlayerNewFlag)
{
	m_PlayerNewFlagInfo.m_PlayerNewFlag=bPlayerNewFlag;
}

void PlayerNewFlag::updateScore()
{
	if(m_PlayerNewFlagInfo.m_PlayerNewFlag)
	{
		m_Score=100;
		return;
	}
	m_Score=0;
}

void PlayerNewFlag::updateProbValue()
{
	TProbValue N2=0;
	if(m_PlayerNewFlagInfo.m_PlayerNewFlag)
	{
		N2=0.1;
	}
	m_ProbValue=N2;
}

void PlayerGameTime::updatePlayerGameTime(unsigned long long llPlayerGameTime)
{
	m_PlayerGameTimeInfo.m_PlayerGameTime=llPlayerGameTime;
}

void PlayerGameTime::updateScore()
{
	int m_PlayerGameTime=m_PlayerGameTimeInfo.m_PlayerGameTime/1000;
	if(m_PlayerGameTime>100)
	{
		m_Score=100;
		return;
	}
	m_Score=0.0001f*m_PlayerGameTime*m_PlayerGameTime*m_PlayerGameTime;
}

void PlayerGameTime::updateProbValue()
{
	TProbValue N3=0.1;
	int m_PlayerGameTime=m_PlayerGameTimeInfo.m_PlayerGameTime/1000;
	if(m_PlayerGameTime<=100)
		N3=0.00001*m_PlayerGameTime*m_PlayerGameTime;
	m_ProbValue=N3;
}

//------------------------------------------------------------------------------------------------------
//“鱼的数值表”缓冲
//------------------------------------------------------------------------------------------------------
CTabFishCache::CTabFishCache(const char *pszFilePath/*=PoolConfig\\FishMultiAndKilledScore.csv*/)
{
	if(pszFilePath!=NULL)
		LoadData(pszFilePath);
}

CTabFishCache & CTabFishCache::Instance()
{
	static CTabFishCache g_TabFishCache;//“鱼的数值表”缓冲
	return g_TabFishCache;
}

//返回值
//	0			成功
//	1			打开文件失败
//	2			已经载入数据了
int CTabFishCache::LoadData(const char *pszFilePath)
{
	if( !m_mapFishCache.empty() )
		return 2;

	FILE * fp =fopen(pszFilePath,"r");
	if( fp == NULL )
		return 1;

	char sz0[1000] = {0};
	char sz1[4000] = {0};
	CTabFishItem item;
	int n = 0;
	n = fscanf(fp, "%s", sz1);
	while( n > 0 && !feof(fp) )
	{
		n = fscanf(fp, "%d,%[^','],%d,%f,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d,%d,%d\n", &item.m_nFishKind,item.m_szFishName, &item.m_nFishMulti,&item.m_fKilledScore,&item.m_nFishBasicNumOfAck, &item.m_nGenProb,&item.m_nFishGradeMin,&item.m_nFishGradeMax,&item.m_nSceneCapacity, &item.m_nCardsFallProb, &item.m_nMerit,&item.m_IsGroupProb,&item.m_GroupType,&item.m_PathLibType,&item.m_nKilledDifficulty,&item.m_nFishMoveSecs);
		if( n > 0 )
		{
			m_mapFishCache.insert( std::make_pair(item.m_nFishKind, item) );
		}
	}
	fclose(fp);
	return 0;
}

const CTabFishItem * CTabFishCache::Find(TFishKind FishKind)
{
	std::map<int, CTabFishItem>::const_iterator it;
	it = m_mapFishCache.find( FishKind );
	if( it != m_mapFishCache.end() )
		return &(it->second);
	return NULL;
}

TFishMoveSecs CTabFishCache::getFishMoveSecs(TFishKind FishKind)
{
	TFishMoveSecs FishMoveSecs=20;
	const CTabFishItem *pFishLocalInfo=CTabFishCache::Instance().Find(FishKind);
	if(pFishLocalInfo)
	{
		FishMoveSecs=pFishLocalInfo->m_nFishMoveSecs;
		if(FishMoveSecs<5)
			FishMoveSecs=5;
		if(FishMoveSecs>40)
			FishMoveSecs=40;
	}
	return FishMoveSecs;
}

//取出一个击中的鱼
void FishGameFactor::updateFishGameFactor(TFishID FishID,TFishKind nFishKind,TFishNumOfAck FishNumOfAck,unsigned int nHitFishCount)
{
	m_FishID=FishID;
	m_nFishKind=nFishKind;
	const CTabFishItem *pFishLocalInfo=CTabFishCache::Instance().Find(nFishKind);
	if(pFishLocalInfo)
	{
		m_nKilledDifficulty=pFishLocalInfo->m_nKilledDifficulty;
	}
	m_FishNumOfAck=FishNumOfAck;
	m_nHitFishCount=nHitFishCount;
}

//获取鱼的击毙分数
float FishGameFactor::getKilledScore()const
{
	//if(m_pFishLocalInfo==NULL)
	//	return 0;
	//return m_pFishLocalInfo->m_fKilledScore;
	return 0;
}

////增加该鱼的被攻击次数
//void FishGameFactor::IncreNumOfAck()
//{
//	m_FishNumOfAck++;
//}

void FishGameFactor::updateScore()
{
	//if(m_pFishLocalInfo==NULL)
	//	return;
	//if(m_pFishLocalInfo->m_nFishGradeMin>m_pFishLocalInfo->m_nFishGradeMax)
	//	return;
	float m_Score3=0,m_Score5=0,m_Weight3=30,m_Weight5=20;
	//m_Score3=rand()%(m_pFishLocalInfo->m_nFishGradeMax-m_pFishLocalInfo->m_nFishGradeMin+1)+m_pFishLocalInfo->m_nFishGradeMin;
	//if(m_FishNumOfAck<=m_pFishLocalInfo->m_nFishBasicNumOfAck)
	//{	
	//	m_Score5=100.f*m_FishNumOfAck/m_pFishLocalInfo->m_nFishBasicNumOfAck;
	//}
	//else
	//{
	//	m_Score5=100.f;
	//}
	m_Score=m_Score3*m_Weight3+m_Score5*m_Weight5;
}

void FishGameFactor::updateProbValue()
{
	if(m_nHitFishCount==0||m_nKilledDifficulty==0)
		return;
	TProbValue F1=1.f/m_nKilledDifficulty;

	m_ProbValue=F1*(1+0.05*m_FishNumOfAck)/m_nHitFishCount;
}



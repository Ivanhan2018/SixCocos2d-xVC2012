#include "AwardPool.h"
#include "FishTable.h"

CAwardPool::CAwardPool(void)
{
	m_V = 0;
	m_Vh=0;
	m_Vl=0;
	m_SV=0;
	m_X=90;
	m_Y=10;
	m_GameFactorsMgr.m_pAwardPool=this;
#if 1
	//Init(10000,12000,8000,0);
	TAwardPoolValue m_Vh0=PoolAndFish::Instance().m_Vh0;//��ʼ��ˮλ
	TAwardPoolValue m_Vl0=PoolAndFish::Instance().m_Vl0;//��ʼ��ˮλ
	TAwardPoolValue m_V0=PoolAndFish::Instance().m_V0;//��ʼˮƽ��
	if(m_Vh0>=120 && m_Vl0>=80 && m_V0>=100 && m_Vh0>m_Vl0)
		Init(m_V0,m_Vh0,m_Vl0,0);
	else
		Init(100,120,80,0);
#else
	Init(100,120,80,0);
#endif
}

CAwardPool::~CAwardPool(void)
{

}

//��ʼ������
bool CAwardPool::Init(TAwardPoolValue V,TAwardPoolValue Vh,TAwardPoolValue Vl,TAwardPoolValue SV)
{
	m_V = V;
	m_Vh=Vh;
	m_Vl=Vl;
	m_SV=SV;
	return true;     
}

//������أ���������=����+�����
bool CAwardPool::Put(TAwardPoolValue nEnterPoolValue)
{
	if (nEnterPoolValue<1)
	{
		return false;
	}
	TAwardPoolValue nEnterP=nEnterPoolValue*m_X/(m_X+m_Y);
	TAwardPoolValue nEnterSP=nEnterPoolValue-nEnterP;
	PutToP(nEnterP);
	PutToSP(nEnterSP);
	return true;
}

bool CAwardPool::PutToP(TAwardPoolValue nEnterPoolValue)
{
	m_V+=nEnterPoolValue;
	return true;
}

bool CAwardPool::PutToSP(TAwardPoolValue nEnterPoolValue)
{
	m_SV+=nEnterPoolValue;
	return true;
}

//�������
bool CAwardPool::Pop(TAwardPoolValue nLeavePoolValue)
{
	if (nLeavePoolValue>m_V)
		return false;
	m_V-=nLeavePoolValue;
	return true;
}

// ���Ӷ�ʱ����Ӧ
int CAwardPool::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(get_fish_table()==NULL)
		return 0;

	if (iTableNo !=  get_fish_table()->m_stTableInfo.iTableNo)
		return 0;

	//�¼�����
	switch (iIDEvent)
	{
	case IDI_Adjust_Vh:
		{
			int ret=AdjustPoolHighFlag();
			//get_fish_table()->set_table_timer(IDI_Adjust_Vh,GameFactorsMgr::GetRand(2000,10000));
			return 0;
		}
	case IDI_Adjust_Vl:
		{
			int ret=AdjustPoolLowFlag();
			//get_fish_table()->set_table_timer(IDI_Adjust_Vl,GameFactorsMgr::GetRand(2000,10000));			
			return 0;
		}
	default:
		break;

	}
	return 0;
}

//��Ϸ��ʼ
int CAwardPool::OnGameBegin()
{
	if(get_fish_table()==NULL)
		return 0;

	get_fish_table()->set_table_timer(IDI_Adjust_Vh,6000);
	get_fish_table()->set_table_timer(IDI_Adjust_Vl,6000);

	return 0;
}

//��Ϸ����
int CAwardPool::OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag)
{
	if(get_fish_table()==NULL)
		return 0;

	get_fish_table()->kill_table_timer(IDI_Adjust_Vh);
	get_fish_table()->kill_table_timer(IDI_Adjust_Vl);

	return 0;
}


float CAwardPool::curLambda()const
{
	float Lambda=1000;//1000����������󣬴�ʱm_V��P_2��������;-1000��������󣬴�ʱm_V��P_2��������
	if(m_V==m_Vh)
		Lambda=1000;
	else
	{
		//m_V�������߶�m_Vlm_Vh���ɵı�
		Lambda=(m_V-m_Vl)/(m_Vh-m_V);
		//m_V��m_Vh���������ȡֵ��Ϊһ���ȼ���
		if(Lambda<-1000||Lambda>1000)
			Lambda=1000;
	}
	//����m_V����������߶�m_Vlm_Vh���������ĸ�ȡֵ����[0,m_Vl],(m_Vl,m_Vh-��),[m_Vl-��,m_Vh+��],(m_Vh+��,+��),��Ӧ��ֵ��Ϊ(-1,0],[0,1000),{1000},(-1000,-1)
	return Lambda;
}


int CAwardPool::AdjustPoolHighFlag()
{
	//��ˮλ������
	TAwardPoolValue loVh=PoolAndFish::Instance().m_loVh;
	TAwardPoolValue hiVh=PoolAndFish::Instance().m_hiVh;
	float Lambda=curLambda();
	//�������Դ��ڳ�ˮ״̬
	if(Lambda<0.1 && Lambda>-1)
	{
		//����Vh�������ˮ
		m_Vh=GameFactorsMgr::GetRandEx(m_Vh,hiVh);
		return 1;
	}
	//�������Դ��ڷ�ˮ״̬
	if(Lambda<-1||Lambda==1000)
	{
		//����Vh�������ˮ
		m_Vh=GameFactorsMgr::GetRandEx(loVh,m_Vh);
		return -1;
	}
	//�������Vh
	TAwardPoolValue m_VhOld=m_Vh;
	m_Vh=GameFactorsMgr::GetRandEx(loVh,hiVh);
	if(m_Vh>m_VhOld)
		return 1;
	if(m_Vh<m_VhOld)
		return -1;
	return 0;
}

int CAwardPool::AdjustPoolLowFlag()
{
	//��ˮλ������
	TAwardPoolValue loVl=PoolAndFish::Instance().m_loVl;
	TAwardPoolValue hiVl=PoolAndFish::Instance().m_hiVl;
	float Lambda=curLambda();
	//�������Դ��ڳ�ˮ״̬
	if(Lambda<0.1 && Lambda>-1)
	{
		//����Vl�������ˮ
		m_Vl=GameFactorsMgr::GetRandEx(loVl,m_Vl);
		return -1;
	}
	//�������Դ��ڷ�ˮ״̬
	if(Lambda<-1||Lambda==1000)
	{
		//����Vl�������ˮ
		m_Vl=GameFactorsMgr::GetRandEx(m_Vl,hiVl);
		return 1;
	}
	//�������Vl
	TAwardPoolValue m_VlOld=m_Vl;
	m_Vl=GameFactorsMgr::GetRandEx(loVl,hiVl);
	if(m_Vl>m_VlOld)
		return 1;
	if(m_Vl<m_VlOld)
		return -1;
	return 0;
}


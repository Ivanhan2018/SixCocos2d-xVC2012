#pragma once
#include "PartMgr.h"
//#include "FishTable.h"
#include "GameFactorsMgr.h"

typedef double TAwardPoolValue;

//������
class CAwardPool:public CPartMgr
{
public:
	CAwardPool(void);
	~CAwardPool(void);

	//��ʼ������
	bool Init(TAwardPoolValue V,TAwardPoolValue Vh,TAwardPoolValue Vl,TAwardPoolValue SV);

	//������أ���������=����+�����
	bool Put(TAwardPoolValue nEnterPoolValue);
	bool PutToP(TAwardPoolValue nEnterPoolValue);
	bool PutToSP(TAwardPoolValue nEnterPoolValue);

	//�������
	bool Pop(TAwardPoolValue nLeavePoolValue);

	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);

	//��Ϸ��ʼ
	int OnGameBegin();

	//��Ϸ����
	int OnGameFinish(BYTE bDeskStation, BYTE bCloseFlag);

	//һ���ܷ�ӳ�����������и���C������ȡֵ��ΧΪ(-1,0],[0,1000),{1000},(-1000,-1)
	float curLambda()const;

	//������ͨ����ˮλ�꣬0��ʾ��������1��ʾ���ߣ�-1��ʾ����
	int AdjustPoolHighFlag();

	//����������ˮλ�꣬0��ʾ��������1��ʾ���ߣ�-1��ʾ����
	int AdjustPoolLowFlag();

public:
	//����P
	TAwardPoolValue   m_V;  //ˮƽ��ֵ
	TAwardPoolValue   m_Vh;  //��ˮλ��
	TAwardPoolValue   m_Vl;  //��ˮλ��

	//�����SP
	TAwardPoolValue   m_SV;

	//���������ĳ�ˮ����deductRate=Y/(X+Y)
	int m_X,m_Y;//X+Y=100

	//�����㷨
	GameFactorsMgr m_GameFactorsMgr;
};

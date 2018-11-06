#pragma once
#include"../GameMsg/ProFish.h"
#include<stack>
using namespace std;

class CFishTraceMgr;
class CFishTable;
class FishStateMgr;

//����״̬
enum enFishState
{
	enFishState_Capture,//������(�Ǿ���ģʽ)
	enFishState_OffFish,//������(����ģʽ)
	enFishState_Max,
};

//////////////////////////////////////////////////////////////////////////
//����״̬
struct IFishState
{
	virtual ~IFishState(){}
	virtual bool Enter()=0;
	virtual bool Leave()=0;
	virtual enFishState GetState()=0;
	// ���Ӷ�ʱ����Ӧ
	virtual int OnTableTimer(int iTableNo, int iIDEvent)=0;
};


//������(�Ǿ���ģʽ)
class CaptureFishState : public IFishState
{
public:
	CaptureFishState(FishStateMgr *pFishStateMgr=NULL);
	~CaptureFishState();
	bool Enter();
	bool Leave();
	enFishState GetState();
	//���������6�벻����
	bool IsFish()const;
	//add by Ivan_han 20130828
	/*
		��Ϊ���������
		����ֵΪ0����������/��Ⱥ
		����ֵΪ1������������/��Ⱥ,�������ڲ�����
		����ֵΪ2������������/��Ⱥ,�Ҳ����ڽ���
    */
	int IsFishEx()const;
	/*
		��ʱֻ��TFishPathType=5�ĵ���/��Ⱥ�켣
		type��ʾ����/��Ⱥ���ͣ�1С��/2����/3ը����/4������Ⱥ/5�ж���Ⱥ
	*/
	TFishKind AddFish(int type);
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	FishStateMgr *m_pFishStateMgr;
	unsigned long long m_EnterTime;
};


//������(����ģʽ)
class OffFishState : public IFishState
{
public:
	//add by Ivan_han 20130823
	//���������е�һ������
	struct TFishGroupTypeSeqElem
	{
		TFishGroupType FishGroupType;
		long long RelativeBuildTime;
	};
	OffFishState(FishStateMgr *pFishStateMgr=NULL);
	~OffFishState();
	bool Enter();
	bool Leave();
	enFishState GetState();
	//���һ���������ͣ�ȡ{1,2,3,4,5,6,7,11,12,13,14,15,16,17}֮����������
	static TFishGroupType GetRandFishGroupType(bool bLeftToRight);
	//���һ���������У�add by Ivan_han 20130823
	static stack<OffFishState::TFishGroupTypeSeqElem> GetRandFishGroupTypeSeq();
	//���������20�벻����
	bool IsFish()const;
	// ���Ӷ�ʱ����Ӧ
	int OnTableTimer(int iTableNo, int iIDEvent);
public:
	FishStateMgr *m_pFishStateMgr;
	unsigned long long m_EnterTime;
	//��ǰ��������
	stack<TFishGroupTypeSeqElem> m_CurFishGroupTypeSeq;
	//���һ���������ʱ��+������Ĺ켣ʱ��
	unsigned long long m_OffEndTime;
};

//����״̬����
class FishStateMgr
{
public:
	FishStateMgr(CFishTraceMgr * pFishTraceMgr=NULL);
	//��õ�ǰ����״̬
	enFishState GetFishState();
	//�л�����״̬
	void SwitchFishState();
	//�л�����
	bool SwitchScene();
	int SwitchSceneTime();
public:
	CFishTraceMgr * m_pFishTraceMgr;
	TSeaSceneKind m_CureSeaSceneKind;//��ǰ����
	bool m_bWaveLToR;//�ı䷽��
	//����״̬
	IFishState *      m_pCurFishState;//��ǰ����״̬
	CaptureFishState  m_CaptureFishState;//������(�Ǿ���ģʽ)
	OffFishState      m_OffFishState;//������(����ģʽ)
};
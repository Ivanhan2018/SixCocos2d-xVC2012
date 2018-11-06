#include "stdafx.h"
#include "FishStateMgr.h"
#include "FishTable.h"
#include "GameSkeletonMsgCode.h"//add by Ivan_han 20130806
#include "PublicHead.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CaptureFishState::CaptureFishState(FishStateMgr *pFishStateMgr): m_pFishStateMgr(pFishStateMgr)
{
	m_EnterTime=0;
}
CaptureFishState::~CaptureFishState()
{

}

bool CaptureFishState::Enter()
{
	if(m_pFishStateMgr==NULL)
		return false;
	if(m_pFishStateMgr->m_pFishTraceMgr==NULL)
		return false;
	if(m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()==NULL)
		return false;
	m_EnterTime=CFishTable::GetTickCount64();
	m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()->set_table_timer(IDI_BUILD_TRACE,PoolAndFish::Instance().GetCaptureBuildTraceTime());
	return true;
}

bool CaptureFishState::Leave()
{
	if(m_pFishStateMgr==NULL)
		return false;
	if(m_pFishStateMgr->m_pFishTraceMgr==NULL)
		return false;
	if(m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()==NULL)
		return false;
	m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()->kill_table_timer(IDI_BUILD_TRACE);
	m_EnterTime=0;
	return true;
}

enFishState CaptureFishState::GetState()
{
	return enFishState_Capture;
}

bool CaptureFishState::IsFish()const
{
	unsigned long long NowTime=CFishTable::GetTickCount64();
	if(m_EnterTime>0 && NowTime-m_EnterTime+6000>PoolAndFish::Instance().GetCaptureTime())
		return false;
	return true;
}

int CaptureFishState::IsFishEx()const
{
	unsigned long long NowTime=CFishTable::GetTickCount64();
	if(m_EnterTime>0 && NowTime-m_EnterTime>=PoolAndFish::Instance().GetCaptureTime())
		return 2;
	if(m_EnterTime>0 && NowTime-m_EnterTime+6000>=PoolAndFish::Instance().GetCaptureTime())
		return 1;
	return 0;
}

TFishKind CaptureFishState::AddFish(int type)
{
	if(type==1||type==2||type==3)
	{
		TFishKind FishKind=GameFactorsMgr::GetFishKindByProbEx(type);
		m_pFishStateMgr->m_pFishTraceMgr->RandAddOneFishWithBezier3(3,FishKind);
		return FishKind;
	}
	if(type==4)
	{
		m_pFishStateMgr->m_pFishTraceMgr->AddRegularFish(104,0);
		return 0;
	}
	if(type==5)
	{
		m_pFishStateMgr->m_pFishTraceMgr->AddRegularFish(105,0);
		return 0;
	}
	return 0;
}

int CaptureFishState::OnTableTimer(int iTableNo, int iIDEvent)
{
	if(m_pFishStateMgr==NULL)
		return 0;
	if(m_pFishStateMgr->m_pFishTraceMgr==NULL)
		return 0;

	 if (IDI_BUILD_TRACE == iIDEvent)//�����켣��ʱ��IDI_BUILD_TRACE=1
	 {
#if 1
		 //if(IsFish())
			// return 0;
		 int ret=IsFishEx();
		 if(ret==1)
			 return 0;
		 if(ret==2)
		 {
			 m_pFishStateMgr->SwitchScene();
			 return 0;
		 }
		 //�����ڱ��ⷢ�ص��ĵ���/��Ⱥ�켣�Ĳ��ԣ�add by Ivan_han 20130829
		 //ģ��nMod=8
		 static int nCount=0;
		 int nMod=PoolAndFish::Instance().m_vecTypeSeq.size();
		 if(nMod==0)
		 {
			 return 0;
		 }
		 int type=PoolAndFish::Instance().m_vecTypeSeq[nCount%nMod];
		 TFishKind FishKind=AddFish(type);
		 //switch ( nCount%8 )
		 //{
		 //case 0:    AddFish(1);break;
		 //case 1: 	AddFish(2);break;
		 //case 2: 	AddFish(3);break;
		 //case 3:    AddFish(1);break;
		 //case 4:    AddFish(2);break;
		 //case 5:    AddFish(4);break;
		 //case 6:    AddFish(1);break;
		 //case 7:    AddFish(5);break;
		 //default:    break;
		 //}
		 nCount++;
#else
		 //��ʱֻ��TFishPathType=5�ĵ���/��Ⱥ�켣��add by Ivan_han 20130731
		 TFishKind FishKind=GameFactorsMgr::GetFishKindByProb();
		 const CTabFishItem *pFishLocalInfo=CTabFishCache::Instance().Find(FishKind);
		 if(pFishLocalInfo)
		 { 
			 bool IsGroup=false;
			 if(FishKind<12/*||pFishLocalInfo->m_IsGroupProb>0||pFishLocalInfo->m_GroupType>0*/)//<=10�ŵ�����ܳ�Ⱥ
			 {
				 IsGroup=GameFactorsMgr::SelectBoolByProb(pFishLocalInfo->m_IsGroupProb);
			 }
			 if(IsGroup)
			 {
				 //ֻ�����ж���Ⱥ
				 if(pFishLocalInfo->m_GroupType==1)
					 m_pFishStateMgr->m_pFishTraceMgr->AddRegularFish(105,FishKind);
				 else
				 {
					 //�Ƿ���������Ⱥ
					 bool IsGroup104=GameFactorsMgr::SelectBoolByProb(0.5);
					 if(IsGroup104)
						 m_pFishStateMgr->m_pFishTraceMgr->AddRegularFish(104,FishKind);
					 else
						 m_pFishStateMgr->m_pFishTraceMgr->AddRegularFish(105,FishKind);
				 }
			 }
			 else//>10�ŵ����ը��һ�����ܳ�Ⱥ��<=10�ŵ�����ܲ���Ⱥ
			 {
				 m_pFishStateMgr->m_pFishTraceMgr->RandAddOneFishWithBezier3(pFishLocalInfo->m_PathLibType,FishKind);
			 }
		 }
#endif
#if 0
		 m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()->set_table_timer(IDI_BUILD_TRACE,GameFactorsMgr::GetRand(1000,3000));
#endif
	 }
	 return 0;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 OffFishState::OffFishState(FishStateMgr *pFishStateMgr): m_pFishStateMgr(pFishStateMgr)
 {
	 m_EnterTime=0;
	 m_OffEndTime=0;
 }
 OffFishState::~OffFishState()
 {

 }

 bool OffFishState::Enter()
 {
	 if(m_pFishStateMgr==NULL)
		 return false;
	 if(m_pFishStateMgr->m_pFishTraceMgr==NULL)
		 return false;
	 if(m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()==NULL)
		 return false;

	 //add by Ivan_han 20130823
	 m_CurFishGroupTypeSeq=GetRandFishGroupTypeSeq();

	 int OffCheckBuildTraceTime=PoolAndFish::Instance().GetOffBuildTraceTime();
	 //2���Ӽ��һ����������
	 if(m_CurFishGroupTypeSeq.size()>0)
		 OffCheckBuildTraceTime=2000;

	 //����
	 m_EnterTime=CFishTable::GetTickCount64();
	 m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()->set_table_timer(IDI_REGULAR_FISH,OffCheckBuildTraceTime);
	 return true;
 }

 bool OffFishState::Leave()
 {
	 if(m_pFishStateMgr==NULL)
		 return false;
	 if(m_pFishStateMgr->m_pFishTraceMgr==NULL)
		 return false;
	 if(m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()==NULL)
		 return false;
	 
	 //����
	 m_pFishStateMgr->m_pFishTraceMgr->get_fish_table()->kill_table_timer(IDI_REGULAR_FISH);
	 while(!m_CurFishGroupTypeSeq.empty())
		 m_CurFishGroupTypeSeq.pop();
	 m_OffEndTime=0;
	 m_EnterTime=0;
	 return true;
 }

TFishGroupType OffFishState::GetRandFishGroupType(bool bLeftToRight)
{
	TFishGroupType FishGroupType=GameFactorsMgr::GetRand(1,7);
    if(!bLeftToRight)
		FishGroupType+=10;
	return FishGroupType;
}

stack<OffFishState::TFishGroupTypeSeqElem> OffFishState::GetRandFishGroupTypeSeq()
{
	stack<OffFishState::TFishGroupTypeSeqElem> sSeq;
	int nSize=PoolAndFish::Instance().m_vecAllFishGroupTypeSeq.size();
	if(nSize>0)
	{
		int index=GameFactorsMgr::GetRand(0,nSize-1);
		vector<OffFishState::TFishGroupTypeSeqElem> vSeq=PoolAndFish::Instance().m_vecAllFishGroupTypeSeq[index];
	    int nSize1=vSeq.size();
		for(int i=nSize1-1;i>=0;i--)
		{
            sSeq.push(vSeq[i]);
		}
	}
	if(sSeq.size()==0)
	{
		OffFishState::TFishGroupTypeSeqElem Seq[3]={{1,0},{2,35000},{11,70000}};
		for(int i=2;i>=0;i--)
		{
			sSeq.push(Seq[i]);
		}
	}
	return sSeq;
}

enFishState OffFishState::GetState()
{
	  return enFishState_OffFish;
}

bool OffFishState::IsFish()const
{
	unsigned long long NowTime=CFishTable::GetTickCount64();
	if(m_EnterTime>0 && NowTime-m_EnterTime+20000>PoolAndFish::Instance().GetOffTime())
		return false;
	return true;
}


int OffFishState::OnTableTimer(int iTableNo, int iIDEvent)
{
	 if(m_pFishStateMgr==NULL)
		 return 0;
	 if(m_pFishStateMgr->m_pFishTraceMgr==NULL)
		 return 0;

	 switch(iIDEvent)
	 {
	 case IDI_REGULAR_FISH:
		 {
//�����ڼ���������У������Ƿ��������켣��add by Ivan_han 20130823
#if 1
			 unsigned long long NowTime=CFishTable::GetTickCount64();
			 int SeqSize=m_CurFishGroupTypeSeq.size();
			 if(SeqSize>0 && NowTime-m_EnterTime>=4000)
			 {
				 TFishGroupTypeSeqElem SeqElem=m_CurFishGroupTypeSeq.top();
				 //���1������һ������
				 if(NowTime>m_EnterTime+SeqElem.RelativeBuildTime)
				 {
					 m_CurFishGroupTypeSeq.pop();
					 if(SeqSize==1)
					 {
						 m_OffEndTime=NowTime+1000*PoolAndFish::Instance().GetFishMoveSecs(SeqElem.FishGroupType);
					 }
					 m_pFishStateMgr->m_pFishTraceMgr->AddRegularFish(SeqElem.FishGroupType,0);

					 char szBuf[64]={0};
					 sprintf(szBuf,"FishGroupType=%d",SeqElem.FishGroupType);
					 COften::OutputInfo(szBuf);
					 return 0;
				 }
				 //���2��������һ������,�������ڲ�����
				 return 0;
			 }
			 else
			 {
				 //���3��������һ������,�������ڽ���
				 if(m_EnterTime>0 && m_OffEndTime>0 && NowTime>=m_OffEndTime)
				 {
					 m_pFishStateMgr->SwitchFishState();
					 return 0;
				 }
				  //���2��������һ������,�������ڲ�����
				 return 0;
			 }
#else
			 if(!IsFish())
				 return 0;
			 bool bLeftToRight=(rand()%2)?true:false;
			 TFishGroupType FishGroupType=OffFishState::GetRandFishGroupType(bLeftToRight);
			 m_pFishStateMgr->m_pFishTraceMgr->AddRegularFish(FishGroupType,0);
			 printf("bLeftToRight=%d,FishGroupType=%d\n",bLeftToRight,FishGroupType);
#endif
		 }
		 break;
	 default:
		 return 0;
		 break;
	 }

	 return 0;
 }

 FishStateMgr::FishStateMgr(CFishTraceMgr * pFishTraceMgr):m_pFishTraceMgr(pFishTraceMgr)
 {
	 m_pCurFishState = NULL;
	 m_CaptureFishState.m_pFishStateMgr=this;
	 m_OffFishState.m_pFishStateMgr=this;
 }

 //��õ�ǰ����״̬
 enFishState FishStateMgr::GetFishState()
 {
	 if (m_pCurFishState)
	 {
		 return m_pCurFishState->GetState();
	 }

	 return enFishState_Max;
 }

 //�л�����״̬
 void FishStateMgr::SwitchFishState()
 {
	 if (m_pCurFishState == NULL)
	 {
		 m_pCurFishState = &m_CaptureFishState;
	 }
	 else 
	 {
		 m_pCurFishState->Leave();
		 if (m_pCurFishState == &m_CaptureFishState)
		 {
			 m_pCurFishState = &m_OffFishState;
		 }
		 else
		 {
			 m_pCurFishState = &m_CaptureFishState;
		 }
		 m_pCurFishState->Enter();
	 }
 }

 bool FishStateMgr::SwitchScene()
 {
	 //�л��������ǳ�
	 if(GetFishState()==enFishState_Capture)
	 {
		 Rsp_ChangeScene rsp;
		 rsp.SeaSceneKind=GameFactorsMgr::GetRand(1,4);
		 rsp.bRToL=true;
		 // �����ڹ㲥
		 m_pFishTraceMgr->get_fish_table()->send_table_data(TABLE_MAIN,RSP_CHANGE_SCENE,(BYTE*)(&rsp),sizeof(rsp));
	 }
	 SwitchFishState();//ע�͵������Բ��Բ����ڻ�������

	 return true;

 }

 int FishStateMgr::SwitchSceneTime()
 {
	 if(GetFishState()==enFishState_Capture)
		 return PoolAndFish::Instance().GetCaptureTime();
	 else
	     return PoolAndFish::Instance().GetOffTime();
 }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
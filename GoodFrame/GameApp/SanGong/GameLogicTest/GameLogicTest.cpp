#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

#include "../SanGongServer/GameLogic.h"


int main()
{
	CGameLogic m_GameLogic;
	//�����������С��Win32��Ϊ4��x64��Ϊ8
	cout<<sizeof(m_GameLogic)<<endl;

#if 0
	TCardData cbCardData[MAX_COUNT]={0x0A,0x13,0x2D};
	//m_GameLogic.SortCardList(cbCardData,MAX_COUNT);
	TCardType CardType=m_GameLogic.GetCardType(cbCardData,MAX_COUNT);
	for(int j=0;j<MAX_COUNT;j++)
	{
		cout<<(int)cbCardData[j]<<"("<<CGameLogic::GetCardName(cbCardData[j])<<")"<<" ";
	}
	cout<<endl;
	cout<<"CardType="<<(int)CardType<<endl;
#endif

#if 1
	//[ׯ��7��]��[�м�7��]
	//TCardData cbCardData[2][MAX_COUNT]={{42,49,6},{58,28,55}};
	//[ׯ��9��]��[�м�9��]
	//TCardData cbCardData[2][MAX_COUNT]={{0x26,0x02,0x21},{0x16,0x14,0x29}};
	//[ׯ��7��]��[�м�7��]
	//TCardData cbCardData[2][MAX_COUNT]={{0x3C,0x37,0x3A},{0x04,0x1D,0x33}};
	//[ׯ��5��]Ӯ[�м�5��]
	//TCardData cbCardData[2][MAX_COUNT]={{0x0D,0x38,0x07},{0x1C,0x0C,0x25}};
	TCardData cbCardData[2][MAX_COUNT]={{0x04,0x3D,0x06},{0x1C,0x0C,0x25}};
	//m_GameLogic.SortCardList(cbCardData[0],MAX_COUNT);
	//m_GameLogic.SortCardList(cbCardData[1],MAX_COUNT);
	const char * szDes[2]={"ׯ��","�м�"};
	for(int i=0;i<2;i++)
	{
		cout<<szDes[i]<<endl;
		TCardType CardType=m_GameLogic.GetCardType(cbCardData[i],MAX_COUNT);
		TCardPoint CardPoint=m_GameLogic.GetCardPoint(cbCardData[i],MAX_COUNT);
		for(int j=0;j<MAX_COUNT;j++)
		{
			cout<<(int)cbCardData[i][j]<<"("<<CGameLogic::GetCardName(cbCardData[i][j])<<")"<<" ";
		}
		cout<<endl;
		cout<<"CardType="<<(int)CardType<<endl;
		cout<<"CardPoint="<<(int)CardPoint<<endl;
		cout<<endl;
	}
	if (m_GameLogic.CompareCard(cbCardData[0],cbCardData[1],MAX_COUNT)==true) 
	    cout<<"[0]ʤ[1]"<<endl;
	else
		cout<<"[0]��[1]"<<endl;
#endif

#if 0
	TCardData g_cbCardListData[FULL_COUNT]=
	{
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//���� A - K
		0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//÷�� A - K
		0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//���� A - K
		0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//���� A - K
		0x4E,0x4F,
	};
	int g_Value[65]={0};
	memset(g_Value,-1,sizeof(g_Value));
	for(int j=0;j<FULL_COUNT;j++)
	{
		g_Value[(int)CGameLogic::GetCardLogicValue(g_cbCardListData[j])]=(int)g_cbCardListData[j];
		//cout<<(int)g_cbCardListData[j]<<"("<<CGameLogic::GetCardName(g_cbCardListData[j])<<")���߼�ֵ="<<(int)CGameLogic::GetCardLogicValue(g_cbCardListData[j])<<endl;
	}
	for(int i=0;i<65;i++)
	{
		if(g_Value[i]==-1)
			continue;
		cout<<(int)g_Value[i]<<"("<<CGameLogic::GetCardName(g_Value[i])<<")���߼�ֵ="<<(int)i<<",��ɫ="<<(int)CGameLogic::GetCardColor(g_Value[i])<<endl;
	}
#endif

#if 0
	//CGameLogic��ֻ��������������ʹ�ã������ͻ���ֻ������ʾ
	//�����ͻ����õ�CGameLogic��ĵط�
	cout<<"GetCardType��������ֵ:0,1��ֵ(ɢ��),2������4ը��"<<endl;
	TCardData cbCardData[][MAX_COUNT]={{0x01,0x11,0x21},{0x01,0x11,0x22}};
	int n=sizeof(cbCardData)/(sizeof(TCardData)*MAX_COUNT);
	int index=m_GameLogic.GetRand(0,n-1);
	for(int i=0;i<n;i++)
	{
		TCardType cbCardType=m_GameLogic.GetCardType(cbCardData[i],MAX_COUNT);
		cout<<"cbCardType="<<(int)cbCardType<<endl;

		if(cbCardType==1)
		{
			//��ȡ�Ƶ�
			unsigned char cbValueList=0;
			unsigned char cbValueCard=0;
			for (unsigned char j=0;j<MAX_COUNT;j++)
			{
				//cbValueCard=m_GameLogic.GetCardValue(cbCardData[i][j]);
				cbValueCard=CARD_VALUE(cbCardData[i][j]);
				if (cbValueCard<10) cbValueList=(cbValueList+cbValueCard)%10;
			}
			cout<<"cbValueList="<<(int)cbValueList<<endl;
		}

	}
#endif

#if 0
	//�������������õ�CGameLogic��ĵط�
	//��Ϸһ�ֿ�ʼʱ���ַ��˿�
	TCardData	m_cbUserCardData[GAME_PLAYER_COUNT][MAX_COUNT]={0};		//�û��˿�
	srand(time(0));
	m_GameLogic.RandCardList(m_cbUserCardData[0],sizeof(m_cbUserCardData)/sizeof(m_cbUserCardData[0][0]));
	for(int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		cout<<"�û�"<<i<<":";
		for(int j=0;j<MAX_COUNT;j++)
		{
			cout<<(int)m_cbUserCardData[i][j]<<"("<<CGameLogic::GetCardName(m_cbUserCardData[i][j])<<")"<<" ";
		}
		cout<<endl;
	}

	//��Ϸһ�ֽ���ʱ������������û��˳�
	//��������
	TCardTypeMulti cbCardTimes[GAME_PLAYER_COUNT];
	memset(cbCardTimes,0,sizeof(cbCardTimes));

	//״̬����
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		m_GameLogic.SortCardList(m_cbUserCardData[i],MAX_COUNT);
		cbCardTimes[i]=m_GameLogic.GetCardTimes(m_cbUserCardData[i],MAX_COUNT);
		cout<<"�û�"<<i<<":";
		cout<<"cbCardTimes="<<(int)cbCardTimes[i]<<endl;
	}

	TChip	m_lGameScore[GAME_PLAYER_COUNT]={0};				//������Ϣ
	TChip	m_lUserChipIn[GAME_PLAYER_COUNT]={1,1,1,1,1,1};				//��ע��Ϣ
	TChairID m_wBankerUser=0;
	//�Ա��˿�
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		//�û�����
		if (i==m_wBankerUser) continue;

		//�Ա��˿�
		if (m_GameLogic.CompareCard(m_cbUserCardData[i],m_cbUserCardData[m_wBankerUser],MAX_COUNT)==true) 
		{
			m_lGameScore[i]+=cbCardTimes[i]*m_lUserChipIn[i];
			m_lGameScore[m_wBankerUser]-=cbCardTimes[i]*m_lUserChipIn[i];
		}
		else
		{
			m_lGameScore[i]-=cbCardTimes[m_wBankerUser]*m_lUserChipIn[i];
			m_lGameScore[m_wBankerUser]+=cbCardTimes[m_wBankerUser]*m_lUserChipIn[i];
		}
	}

	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		cout<<"�û�"<<i<<":";
		cout<<"m_lGameScore="<<(int)m_lGameScore[i]<<endl;
	}
#endif

	system("pause");
	return 0;
}

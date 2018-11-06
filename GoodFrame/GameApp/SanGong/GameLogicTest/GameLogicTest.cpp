#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

#include "../SanGongServer/GameLogic.h"


int main()
{
	CGameLogic m_GameLogic;
	//虚析构空类大小：Win32下为4，x64下为8
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
	//[庄家7点]输[闲家7点]
	//TCardData cbCardData[2][MAX_COUNT]={{42,49,6},{58,28,55}};
	//[庄家9点]输[闲家9点]
	//TCardData cbCardData[2][MAX_COUNT]={{0x26,0x02,0x21},{0x16,0x14,0x29}};
	//[庄家7点]输[闲家7点]
	//TCardData cbCardData[2][MAX_COUNT]={{0x3C,0x37,0x3A},{0x04,0x1D,0x33}};
	//[庄家5点]赢[闲家5点]
	//TCardData cbCardData[2][MAX_COUNT]={{0x0D,0x38,0x07},{0x1C,0x0C,0x25}};
	TCardData cbCardData[2][MAX_COUNT]={{0x04,0x3D,0x06},{0x1C,0x0C,0x25}};
	//m_GameLogic.SortCardList(cbCardData[0],MAX_COUNT);
	//m_GameLogic.SortCardList(cbCardData[1],MAX_COUNT);
	const char * szDes[2]={"庄家","闲家"};
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
	    cout<<"[0]胜[1]"<<endl;
	else
		cout<<"[0]输[1]"<<endl;
#endif

#if 0
	TCardData g_cbCardListData[FULL_COUNT]=
	{
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//方块 A - K
		0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//梅花 A - K
		0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//红桃 A - K
		0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//黑桃 A - K
		0x4E,0x4F,
	};
	int g_Value[65]={0};
	memset(g_Value,-1,sizeof(g_Value));
	for(int j=0;j<FULL_COUNT;j++)
	{
		g_Value[(int)CGameLogic::GetCardLogicValue(g_cbCardListData[j])]=(int)g_cbCardListData[j];
		//cout<<(int)g_cbCardListData[j]<<"("<<CGameLogic::GetCardName(g_cbCardListData[j])<<")的逻辑值="<<(int)CGameLogic::GetCardLogicValue(g_cbCardListData[j])<<endl;
	}
	for(int i=0;i<65;i++)
	{
		if(g_Value[i]==-1)
			continue;
		cout<<(int)g_Value[i]<<"("<<CGameLogic::GetCardName(g_Value[i])<<")的逻辑值="<<(int)i<<",花色="<<(int)CGameLogic::GetCardColor(g_Value[i])<<endl;
	}
#endif

#if 0
	//CGameLogic类只在三公服务器端使用，三公客户端只负责显示
	//三公客户端用到CGameLogic类的地方
	cout<<"GetCardType函数返回值:0,1点值(散牌),2三公，4炸弹"<<endl;
	TCardData cbCardData[][MAX_COUNT]={{0x01,0x11,0x21},{0x01,0x11,0x22}};
	int n=sizeof(cbCardData)/(sizeof(TCardData)*MAX_COUNT);
	int index=m_GameLogic.GetRand(0,n-1);
	for(int i=0;i<n;i++)
	{
		TCardType cbCardType=m_GameLogic.GetCardType(cbCardData[i],MAX_COUNT);
		cout<<"cbCardType="<<(int)cbCardType<<endl;

		if(cbCardType==1)
		{
			//获取牌点
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
	//三公服务器端用到CGameLogic类的地方
	//游戏一局开始时，分发扑克
	TCardData	m_cbUserCardData[GAME_PLAYER_COUNT][MAX_COUNT]={0};		//用户扑克
	srand(time(0));
	m_GameLogic.RandCardList(m_cbUserCardData[0],sizeof(m_cbUserCardData)/sizeof(m_cbUserCardData[0][0]));
	for(int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		cout<<"用户"<<i<<":";
		for(int j=0;j<MAX_COUNT;j++)
		{
			cout<<(int)m_cbUserCardData[i][j]<<"("<<CGameLogic::GetCardName(m_cbUserCardData[i][j])<<")"<<" ";
		}
		cout<<endl;
	}

	//游戏一局结束时，常规结束或用户退出
	//变量定义
	TCardTypeMulti cbCardTimes[GAME_PLAYER_COUNT];
	memset(cbCardTimes,0,sizeof(cbCardTimes));

	//状态设置
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		m_GameLogic.SortCardList(m_cbUserCardData[i],MAX_COUNT);
		cbCardTimes[i]=m_GameLogic.GetCardTimes(m_cbUserCardData[i],MAX_COUNT);
		cout<<"用户"<<i<<":";
		cout<<"cbCardTimes="<<(int)cbCardTimes[i]<<endl;
	}

	TChip	m_lGameScore[GAME_PLAYER_COUNT]={0};				//积分信息
	TChip	m_lUserChipIn[GAME_PLAYER_COUNT]={1,1,1,1,1,1};				//下注信息
	TChairID m_wBankerUser=0;
	//对比扑克
	for (int i=0;i<GAME_PLAYER_COUNT;i++)
	{
		//用户过滤
		if (i==m_wBankerUser) continue;

		//对比扑克
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
		cout<<"用户"<<i<<":";
		cout<<"m_lGameScore="<<(int)m_lGameScore[i]<<endl;
	}
#endif

	system("pause");
	return 0;
}

/*
	��ȡxml�ļ��е����ױ��������߹켣����,add by Ivan_han 20130610  
*/
#pragma once

#include "../GameMsg/ProFish.h"
#include<vector>
using namespace std;

//���ױ��������߹켣�ڵ�
class CBezier3TraceNode
{
public:
	CBezier3TraceNode()
	{
		memset(this,0,sizeof(CBezier3TraceNode));
		m_EntryTime=0;
		m_DepartureTime=1;
	}
public:
	//comment="��10��1.ini" Count="3" pos0="(1180,1114)" pos1="(1042,605)" pos2="(124,-75)" pos3="(-367,-151)"
	char m_szComment[16];//�켣������ò�Ҫ���������ַ�
	int m_nCount;//Ӧ����3
	TPoint m_pos0;//�켣���
	TPoint m_pos1;//��һ�����Ƶ�
	TPoint m_pos2;//�ڶ������Ƶ�
	TPoint m_pos3;//�켣�յ�
	//add by Ivan_han 20130803
	float m_EntryTime;
	float m_DepartureTime;
};

//-------------------------���ױ��������߹켣����-----------------------------------------------------------
class CBezier3TraceCache
{
public:
	CBezier3TraceCache(const char *xmlFileName=NULL);
	~CBezier3TraceCache();
	int LoadData(const char *xmlFileName);
	const CBezier3TraceNode * getBezier3Trace(int index);
public:
	std::vector<CBezier3TraceNode> m_vecBezier3TraceCache;
};

//���ױ��������߹켣������
extern	CBezier3TraceCache m_Bezier3TraceCache[3];
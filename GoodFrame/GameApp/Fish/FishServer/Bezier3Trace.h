/*
	读取xml文件中的三阶贝塞尔曲线轨迹数据,add by Ivan_han 20130610  
*/
#pragma once

#include "../GameMsg/ProFish.h"
#include<vector>
using namespace std;

//三阶贝塞尔曲线轨迹节点
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
	//comment="上10下1.ini" Count="3" pos0="(1180,1114)" pos1="(1042,605)" pos2="(124,-75)" pos3="(-367,-151)"
	char m_szComment[16];//轨迹名，最好不要出现中文字符
	int m_nCount;//应该是3
	TPoint m_pos0;//轨迹起点
	TPoint m_pos1;//第一个控制点
	TPoint m_pos2;//第二个控制点
	TPoint m_pos3;//轨迹终点
	//add by Ivan_han 20130803
	float m_EntryTime;
	float m_DepartureTime;
};

//-------------------------三阶贝塞尔曲线轨迹缓冲-----------------------------------------------------------
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

//三阶贝塞尔曲线轨迹库数据
extern	CBezier3TraceCache m_Bezier3TraceCache[3];
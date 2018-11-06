/*
���������ж����Ƿ��ڷ���������Ļ�����ڵĽ���취1��
t=��켣������ʱ��/��켣ʱ��
����t����켣���̿��Լ�����㵱ǰ��λ�ã�Ȼ�����жϸõ��Ƿ�����Ļ�����ڡ�
����������Ҫ֪����켣���̡�
 
����취2��----�Կռ任ʱ��
Ԥ�ȼ����ÿ����켣���ν��γ���Ļ���ε�ʱ��t1,t2��[0,1]��
t=��켣������ʱ��/��켣ʱ��
����t����t1,t2�Ϳ����ж����Ƿ�����Ļ�����ڣ�������Ҫ������㵱ǰ��λ�á�
ȱ�㣺����Ҫʵ�����ߺ�ֱ�ߡ����ߺ;��ε����㷨��Ŀǰ��δʵ�֣�
�ŵ㣺�����ϣ���Ϊ�Ƿ�ʵʱ���㣬����Ҫ�Ƚ���취1��ʵʱ�����㷨Ч��Ҫ��Щ��
��
1�� ֱ�ߺ����ױ��������ߣ�����֪�ĸ������ȷ������ͬ���Ľ����㷨��
2�� ���ױ��������ߵ�ֵ���㷨��X��Y��ȡֵ���ֵ����Сֵ����

����취3��
��ֱ�߹켣�����ý���취1��
�����ױ��������߹켣���������߹켣�����߹켣�����ý���취2��

*/
#pragma once
#include "../GameMsg/ProFish.h"


//��������
typedef void(*pFuncVoid)(void);
typedef TPoint(*pFuncTrace0)(float t);
typedef TPoint(*pFuncTrace1)(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);
typedef TPoint(*pFuncTrace2)(float t,TPoint a,TPoint b,TPoint c,TPoint d);//���ױ��������߷���

// Bezier cubic formula:
//    ((1 - t) + t)3 = 1 
// Expands to�� 
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1
/*
 ���ױ���������B(t)=P_0(1-t)^3+3P_1t(1-t)^2+3P_2t^2(1-t)+P_3t^3,t��[0,1]
 a������ʼ�㣬b�����һ���Ƶ㣬c����ڶ����Ƶ㣬d�����յ�
*/
static inline float bezierat( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a + 
            3*t*(powf(1-t,2))*b + 
            3*powf(t,2)*(1-t)*c +
            powf(t,3)*d );
}

//�жϵ�p�Ƿ��ڷ���������Ļ������
static inline bool PtInScreenRect(const TPoint &p)
{
	if(p.x<0||p.x>1280||p.y<0||p.y>733)
		return false;
	else
		return true;
}

//�������ױ��������߹켣�ν��γ���Ļ���ε�ʱ��t1,t2��[0,1]�Ľ����㷨
static inline float getBezier3EntryTime(TPoint p0,TPoint p1,TPoint p2,TPoint p3)
{
	//static float dt=0.01;
	//for(int i=0;i<50;i++)
	static float dt=0.05;
	for(int i=0;i<10;i++)
	{
	    TPoint pi=TPoint(bezierat(p0.x,p1.x,p2.x,p3.x,dt*i),bezierat(p0.y,p1.y,p2.y,p3.y,dt*i));
		if(PtInScreenRect(pi))
		{
			return dt*i;    
		}
	}
	return 0.5f;
}

static inline float getBezier3DepartureTime(TPoint p0,TPoint p1,TPoint p2,TPoint p3)
{
	//static float dt=0.01;
	//for(int i=0;i<50;i++)
	static float dt=0.05;
	for(int i=0;i<10;i++)
	{
		TPoint pi=TPoint(bezierat(p0.x,p1.x,p2.x,p3.x,1-dt*i),bezierat(p0.y,p1.y,p2.y,p3.y,1-dt*i));
		if(PtInScreenRect(pi))
		{
			return 1-dt*i;    
		}
	}
	return 0.5f;
}

//ʵʱ����ֱ�߹켣�ĵ�ǰ��,���ж��Ƿ��ڷ���������Ļ������
static inline bool LinePtInScreenRect(TPoint startP,TPoint arg1,TFishMoveSecs FishMoveSecs,TBuildTraceTime ElapsedTraceTime,TPoint &Pt)
{
	float dt=ElapsedTraceTime*0.001/FishMoveSecs;
	Pt=TPoint(startP.x+arg1.x*dt,startP.y+arg1.y*dt);
	return PtInScreenRect(Pt);
}

/*
//����ֱ�߹켣�ν��γ���Ļ���ε�ʱ��t1,t2��[0,1]�Ľ����㷨
static inline float getLineEntryTime(TPoint	startP,TPoint arg1)
{
	static float dt=0.05;
	for(int i=0;i<10;i++)
	{
		TPoint pi=TPoint(startP.x+arg1.x*dt*i,startP.y+arg1.y*dt*i);
		if(PtInScreenRect(pi))
		{
			return dt*i;    
		}
	}
	return 0.5f;
}

static inline float getLineDepartureTime(TPoint	startP,TPoint arg1)
{
	static float dt=0.05;
	for(int i=0;i<10;i++)
	{
		TPoint pi=TPoint(startP.x+arg1.x*(1-dt*i),startP.y+arg1.y*(1-dt*i));
		if(PtInScreenRect(pi))
		{
			return 1-dt*i;    
		}
	}
	return 0.5f;
}
*/


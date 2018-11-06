/*
服务器端判断鱼是否在服务器端屏幕矩形内的解决办法1：
t=鱼轨迹已运行时间/鱼轨迹时长
根据t和与轨迹方程可以计算出鱼当前的位置，然后再判断该点是否在屏幕矩形内。
服务器端需要知道鱼轨迹方程。
 
解决办法2：----以空间换时间
预先计算出每条鱼轨迹鱼游进游出屏幕矩形的时刻t1,t2∈[0,1]，
t=鱼轨迹已运行时间/鱼轨迹时长
根据t和与t1,t2就可以判断鱼是否在屏幕矩形内，而不需要计算出鱼当前的位置。
缺点：这需要实现曲线和直线、曲线和矩形的求交算法，目前尚未实现；
优点：理论上，因为是非实时计算，所以要比解决办法1的实时计算算法效率要高些。
求：
1、 直线和三阶贝塞尔曲线（由已知四个坐标点确定，下同）的交点算法；
2、 三阶贝塞尔曲线的值域算法（X，Y的取值最大值和最小值）；

解决办法3：
对直线轨迹，利用解决办法1；
对三阶贝塞尔曲线轨迹、任意曲线轨迹等曲线轨迹，利用解决办法2；

*/
#pragma once
#include "../GameMsg/ProFish.h"


//服务器端
typedef void(*pFuncVoid)(void);
typedef TPoint(*pFuncTrace0)(float t);
typedef TPoint(*pFuncTrace1)(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);
typedef TPoint(*pFuncTrace2)(float t,TPoint a,TPoint b,TPoint c,TPoint d);//三阶贝塞尔曲线方程

// Bezier cubic formula:
//    ((1 - t) + t)3 = 1 
// Expands to… 
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1
/*
 三阶贝塞尔曲线B(t)=P_0(1-t)^3+3P_1t(1-t)^2+3P_2t^2(1-t)+P_3t^3,t∈[0,1]
 a代表起始点，b代表第一控制点，c代表第二控制点，d代表终点
*/
static inline float bezierat( float a, float b, float c, float d, float t )
{
    return (powf(1-t,3) * a + 
            3*t*(powf(1-t,2))*b + 
            3*powf(t,2)*(1-t)*c +
            powf(t,3)*d );
}

//判断点p是否在服务器端屏幕矩形内
static inline bool PtInScreenRect(const TPoint &p)
{
	if(p.x<0||p.x>1280||p.y<0||p.y>733)
		return false;
	else
		return true;
}

//计算三阶贝塞尔曲线轨迹游进游出屏幕矩形的时刻t1,t2∈[0,1]的近视算法
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

//实时计算直线轨迹的当前点,并判断是否在服务器端屏幕矩形内
static inline bool LinePtInScreenRect(TPoint startP,TPoint arg1,TFishMoveSecs FishMoveSecs,TBuildTraceTime ElapsedTraceTime,TPoint &Pt)
{
	float dt=ElapsedTraceTime*0.001/FishMoveSecs;
	Pt=TPoint(startP.x+arg1.x*dt,startP.y+arg1.y*dt);
	return PtInScreenRect(Pt);
}

/*
//计算直线轨迹游进游出屏幕矩形的时刻t1,t2∈[0,1]的近视算法
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


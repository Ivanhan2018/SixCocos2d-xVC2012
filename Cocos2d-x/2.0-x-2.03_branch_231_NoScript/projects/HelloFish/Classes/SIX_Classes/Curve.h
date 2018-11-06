/*********************************************************
Name：Curve
Desc：平面曲线轨迹库
Auth：Ivan_han@2013/5/20 16:37:17
*********************************************************/
#pragma once
#include <math.h>
#include <map>
using  namespace std;
#include "cocos2d.h"

USING_NS_CC;

class Curve{
public:
	static CCPoint Trace_1_8_1(float t);
	static CCPoint Trace_1_8_2(float t);
	static CCPoint Trace_1_8_3(float t);
	static CCPoint Trace_1_9_1(float t);
	static CCPoint Trace_1_9_2(float t);
	static CCPoint Trace_1_9_3(float t);
	static CCPoint Trace_1_9_4(float t);
	static CCPoint Trace_9_1_1(float t);
	static CCPoint Trace_9_1_2(float t);
	static CCPoint Trace_9_1_3(float t);
	static CCPoint Trace_9_1_4(float t);
	static CCPoint Trace_9_16_1(float t);
	static CCPoint Trace_9_16_2(float t);
	static CCPoint Trace_9_16_3(float t);
	static CCPoint Trace_9_16_4(float t);
	static CCPoint Trace_1_12_1(float t);
	static CCPoint Trace_1_12_2(float t);
	static CCPoint Trace_1_12_3(float t);
	static CCPoint Trace_1_12_4(float t);
	static CCPoint Ellipse0Trace(float t);
	static CCPoint CosTrace(float t);
	static CCPoint CircleTrace(float t);
	static CCPoint EllipseTrace(float t);
	static CCPoint SinTrace(float t);
	static CCPoint GetCirclePos(CCPoint startP,CCPoint centerP,float deltArg);
	static CCPoint CircleTraceFunc(float t,float startPx,float startPy,float centerPx,float centerPy,float direction);
	static CCPoint CycloidTrace(float t);
	static CCPoint CycloidTraceFunc(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);
	static CCPoint CycloidTraceFunc1(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);
	static CCPoint ArchimedesSpiralTrace(float t);
	static CCPoint ArchimedesSpiralTraceFunc(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);
	static CCPoint ArchimedesSpiralTraceFunc1(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);
	static CCPoint GoStopGoLineTrace(float t);
	static CCPoint GoStopGoLineTrace(float t,float Ax,float Ay,float Cx,float Cy,float Lambda,float tA,float tC);
};

//add by Ivan_han 20130528
typedef void(*pFuncVoid)(void);
typedef CCPoint(*pFuncTrace0)(float t);
typedef CCPoint(*pFuncTrace1)(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);

//任意曲线轨迹库管理、辅助类
class CurveHelper
{
public:
	CurveHelper();
	~CurveHelper();
public:
	static long long MakeLongLong(int LO32,int HI32);
	static CurveHelper & Instance();
	pFuncTrace0 GetCurve(long long Index)const;
	pFuncTrace0 GetCurve(int CurveLibIndex,int CurveIndex)const;
	pFuncTrace0 GetCurve(CCPoint arg1)const;
private:
	map<long long,pFuncTrace0> m_CurveLib;
};


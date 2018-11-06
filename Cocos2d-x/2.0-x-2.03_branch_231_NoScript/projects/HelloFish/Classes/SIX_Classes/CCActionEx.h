#pragma once

#include "..\..\..\cocos2dx\actions\CCActionInterval.h"//包含系统延时类动作头文件
using namespace cocos2d;

//add by Ivan_han 20130528
typedef void(*pFuncVoid)(void);
typedef CCPoint(*pFuncTrace0)(float t);
typedef CCPoint(*pFuncTrace1)(float t,float startPx,float startPy,float r,float deltArg,float direction,float reservedx,float reservedy);

/***********************************************
Name：CircleAction
Desc：圆运动轨迹
Auth：Ivan_han@2013-04-23
***********************************************/
/*
   LUA中使用方法：
   --轨迹起点
   self:setPosition(CCPoint(200,300));
   --圆逆时针运动轨迹，参数一为动画时长，参数二为当前圆上位置的对径点坐标，参数三为轨迹方向
   self:runAction(CircleAction:create(3.0, ccp(500,300),1));

    --轨迹起点
    self:setPosition(CCPoint(200,300));
    --圆顺时针运动轨迹，参数一为动画时长，参数二为当前圆上位置的对径点坐标，参数三为轨迹方向
    self:runAction(CircleAction:create(3.0, ccp(500,300),-1));
*/
class  CircleAction : public CCActionInterval 
{ 
public: 
    /** initializes the action */ 
    bool initWithDuration(float duration, const CCPoint& position,int direction); 
 
    virtual void startWithTarget(CCNode *pTarget); 
    virtual void update(float time); 
 
public: 
    /** creates the action */
    static CircleAction* create(float duration, const CCPoint& position,int direction); 
 
protected:  
    CCPoint m_startPosition;//轨迹起点
    CCPoint m_endPosition;//轨迹终点
	int m_direction;//1表示逆时针Anti-clockwise，-1表示顺时针Clockwise
};

/***********************************************
Name：myAction
Desc：任意运动轨迹,轨迹的参数方程写在LUA脚本中
Auth：Ivan_han@2013-04-23
***********************************************/
/*
   LUA中使用方法：
   --自定义运动轨迹，参数一为动画时长，参数二为表示轨迹参数方程的LUA函数名
   self:runAction(myAction:create(3.0,"CircleTrace"));

   --圆中心为(350,300)，半径为150，轨迹起点为(500,300)的逆时针圆轨迹
   --圆运动轨迹，参数一为动画时长，参数二为表示圆轨迹参数方程的LUA函数名，参数三为轨迹起点坐标，参数四为圆心坐标，参数五为正负圈数
   self:runAction(myAction:createCircle(3.0,"CircleTraceFunc",ccp(500,300),ccp(350,300),1));
*/
class  myAction : public CCActionInterval 
{ 
public: 
	myAction(){memset(m_TraceFunc,0,sizeof(m_TraceFunc));m_TraceType=0;m_Func=0;m_Func1=0;m_t=0;}

    /** initializes the action */ 
    bool initWithDuration(float duration,float InitElapsed,const char *func); 
 
    virtual void startWithTarget(CCNode *pTarget); 
    virtual void update(float time); 
 
public: 
    /** creates the action */
	//相当于CC**To
    static myAction* create(float duration,float InitElapsed,const char *func);
	/*
	   带有控制参数的createXXX函数，相当于CC**By
	   参数说明：
	   centerP/rdeltArg----对于圆轨迹、摆线轨迹，分别代表圆心坐标、圆的半径和辐角主值增量
	   reserved----作为保留参数进一步刻画摆线轨迹，reserved.y=0时为水平向右的摆线轨迹
	*/
	static myAction* createCircle(float duration,float InitElapsed,const char *func,const CCPoint& startP,const CCPoint& centerP,float direction);
	static myAction* createCycloid(float duration,float InitElapsed,const char *func,const CCPoint& startP,const CCPoint& rdeltArg,float direction,const CCPoint& reserved);

	//add by Ivan_han 20130528
    bool initWithDuration(float duration,float InitElapsed,pFuncVoid fun); 
	static myAction* createTrace0(float duration,float InitElapsed,pFuncTrace0 fun);
	static myAction* createTrace1(float duration,float InitElapsed,pFuncTrace1 fun,const CCPoint& startP,const CCPoint& rdeltArg,float direction,const CCPoint& reserved);
    
	//add by Ivan_han 20130531
	void setFunc1(pFuncVoid Func1){m_Func1=Func1;}

	//利用定义求一元实函的一阶导数，add by Ivan_han 20130608
	static float dif1fx(float(*fx)(float),float x);
	static CCPoint dif1fx(pFuncTrace0 Func,float t);
	//add by Ivan_han 20130617
	static CCPoint dif1fx(pFuncTrace0 Func,float t,int W,int H,int W1,int H1);
protected: 
	char m_TraceFunc[20];//LUA函数名,定义了轨迹的参数方程
	int m_TraceType;//-2表示create，-1表示createCircle和createCycloid,0表示createTrace0,1表示createTrace1
	//针对圆轨迹、摆线轨迹的成员变量
    CCPoint m_startP;//轨迹起点
    CCPoint m_centerP;//轨迹中心点，保存参数centerP/rdeltArg
	float m_direction;//1表示逆时针Anti-clockwise，-1表示顺时针Clockwise
	//针对移动的圆轨迹（摆线轨迹）额外的成员变量
	CCPoint m_reserved;//进一步刻画摆线轨迹

	//轨迹的方程，add by Ivan_han 20130528
	pFuncVoid  m_Func;

	//轨迹的切向量方程，add by Ivan_han 20130531
	pFuncVoid  m_Func1;

	//上一次设置切向的时刻，m_t∈[0,1]
	float m_t;
};


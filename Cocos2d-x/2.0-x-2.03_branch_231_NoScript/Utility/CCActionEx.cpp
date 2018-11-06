#include "CCActionEx.h" 
#include "..\..\..\cocos2dx\support\CCPointExtension.h" 
#include "..\..\..\scripting\lua\cocos2dx_support\CCLuaEngine.h"
#include "..\..\..\scripting\lua\tolua\tolua++.h"

void CircleAction::startWithTarget(CCNode *pTarget){ 
    CCActionInterval::startWithTarget(pTarget); 
    m_startPosition = pTarget->getPosition();//轨迹起点 
} 
 
CircleAction* CircleAction::create(float duration, const CCPoint& position,int direction){ 
    CircleAction * pmyAction=new CircleAction(); 
    pmyAction->initWithDuration(duration, position,direction); 
    pmyAction->autorelease(); 
 
    return pmyAction; 
} 
//这个函数得到初始化数据 
bool CircleAction::initWithDuration(float duration, const CCPoint& position,int direction){ 
    if (CCActionInterval::initWithDuration(duration)) 
    { 
        m_endPosition = position; //轨迹终点，对于圆轨迹，是半圆弧轨迹的终点
		m_direction =direction;
        return true; 
    } 
 
    return false; 
} 
void CircleAction::update(float time){ 
    if (m_pTarget) 
    { 
        //这里的time就相当于当前时间占总的需要运行时间的百分比 
        /*
			这里轨迹就用一个圆
			x=cos(t),y=sin(t),当时间走完就是一圈360°
			对于圆轨迹，圆心坐标C=(m_startPosition+m_endPosition)/2 
        */ 
		    CCPoint C=ccp((m_startPosition.x+m_endPosition.x)*0.5,(m_startPosition.y+m_endPosition.y)*0.5);//圆心
			float startarg=atan2(m_startPosition.y-C.y,m_startPosition.x-C.x);//轨迹起点相对于圆心的辐角主值∈(-pi,pi]
		    float tempx=(m_startPosition.x-m_endPosition.x)*(m_startPosition.x-m_endPosition.x); 
			float tempy=(m_startPosition.y-m_endPosition.y)*(m_startPosition.y-m_endPosition.y); 
			float r=sqrt(tempx+tempy)*0.5;//圆的半径 
			float x=r*cos(startarg+2*M_PI*time*m_direction);//圆上点相对于圆心的X坐标偏移 
			float y=r*sin(startarg+2*M_PI*time*m_direction);//圆上点相对于圆心的Y坐标偏移 
			m_pTarget->setPosition(ccpAdd(C,ccp(x,y))); 
    } 
}

void myAction::startWithTarget(CCNode *pTarget){ 
    CCActionInterval::startWithTarget(pTarget); 
} 
 
myAction* myAction::create(float duration,const char *func){ 
    myAction * pmyAction=new myAction(); 
    pmyAction->initWithDuration(duration,func); 
    pmyAction->autorelease(); 
 
    return pmyAction; 
}
//这个函数得到初始化数据 
bool myAction::initWithDuration(float duration,const char *func){ 
    if (CCActionInterval::initWithDuration(duration)) 
    { 
		strcpy(m_TraceFunc,func);
        return true; 
    } 
    return false; 
}

//带有控制参数的createXXX函数
myAction* myAction::createCircle(float duration,const char *func,const CCPoint& startP,const CCPoint& centerP,float direction)
{
    return myAction::createCycloid(duration,func,startP,centerP,direction,CCPoint(0,0)); 
}

//带有控制参数的createXXX函数
myAction* myAction::createCycloid(float duration,const char *func,const CCPoint& startP,const CCPoint& rdeltArg,float direction,const CCPoint& reserved)
{
    myAction * pmyAction=new myAction(); 
    if(pmyAction==NULL) 
    { 
        return NULL; 
    }
	if(pmyAction->CCActionInterval::initWithDuration(duration)==false) 
    { 
        return NULL; 
    }
	strcpy(pmyAction->m_TraceFunc,func);
	pmyAction->m_TraceType=1;
	pmyAction->m_startP=startP;
	pmyAction->m_centerP=rdeltArg;
	pmyAction->m_direction=direction;
	pmyAction->m_reserved=reserved;
    pmyAction->autorelease(); 
 
    return pmyAction; 
}

void myAction::update(float time){ 
    if (m_pTarget && m_TraceFunc) 
    { 
		if(m_TraceType==0)
		{
				//这里的time就相当于当前时间占总的需要运行时间的百分比
				CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
				lua_State* m_state = pEngine->getLuaState();
				//int recv=pEngine->executeGlobalFunction(m_TraceFunc,1);
				//函数名
				lua_getglobal(m_state,m_TraceFunc);
				//第一个参数压栈
				lua_pushnumber(m_state, time);
				//调用函数
				lua_call(m_state, 1, 1);
				//得到返回值
				CCPoint retP=*(CCPoint*)(tolua_tousertype(m_state,2,0));
				lua_pop(m_state, 1);

				m_pTarget->setPosition(retP); 
				return;
		}
		if(m_TraceType==1)
		{
				//这里的time就相当于当前时间占总的需要运行时间的百分比
				CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
				lua_State* m_state = pEngine->getLuaState();
				//函数名
				lua_getglobal(m_state,m_TraceFunc);
				//第一个参数压栈
				lua_pushnumber(m_state, time);
				//第二三个参数压栈
				//lua_pushlightuserdata(m_state, &m_startP);
				//void *lp=lua_newuserdata(m_state,sizeof(CCPoint));
				//memcpy(lp,&m_startP,sizeof(CCPoint));
				lua_pushnumber(m_state,m_startP.x);
				lua_pushnumber(m_state,m_startP.y);
				//第四五个参数压栈
				//lua_pushlightuserdata(m_state, &m_centerP);
				//void *lp1=lua_newuserdata(m_state,sizeof(CCPoint));
				//memcpy(lp1,&m_centerP,sizeof(CCPoint));
				lua_pushnumber(m_state,m_centerP.x);
				lua_pushnumber(m_state,m_centerP.y);
				//第六个参数压栈
				lua_pushnumber(m_state,m_direction);
				//第七八个参数压栈
				lua_pushnumber(m_state,m_reserved.x);
				lua_pushnumber(m_state,m_reserved.y);
				//调用函数
				lua_call(m_state,8, 1);
				//得到返回值
				CCPoint retP=*(CCPoint*)(tolua_tousertype(m_state,2,0));
				lua_pop(m_state, 1);

				//m_pTarget->setPosition(CCPoint(m_startP.x+retP.x,m_startP.y+retP.y));//改为相对位置以支持CCRepeatForever无限次重复动画
				m_pTarget->setPosition(retP);
				return;
		}


    } 
}


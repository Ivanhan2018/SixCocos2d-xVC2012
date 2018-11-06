#include "CCActionEx.h" 
#include "..\..\..\cocos2dx\support\CCPointExtension.h" 
#include "Ship.h"//add by Ivan_han 20130608

void CircleAction::startWithTarget(CCNode *pTarget){ 
    CCActionInterval::startWithTarget(pTarget); 
    m_startPosition = pTarget->getPosition();//�켣��� 
} 
 
CircleAction* CircleAction::create(float duration, const CCPoint& position,int direction){ 
    CircleAction * pmyAction=new CircleAction(); 
    pmyAction->initWithDuration(duration, position,direction); 
    pmyAction->autorelease(); 
 
    return pmyAction; 
} 
//��������õ���ʼ������ 
bool CircleAction::initWithDuration(float duration, const CCPoint& position,int direction){ 
    if (CCActionInterval::initWithDuration(duration)) 
    { 
        m_endPosition = position; //�켣�յ㣬����Բ�켣���ǰ�Բ���켣���յ�
		m_direction =direction;
        return true; 
    } 
 
    return false; 
} 
void CircleAction::update(float time){ 
    if (m_pTarget) 
    { 
        //�����time���൱�ڵ�ǰʱ��ռ�ܵ���Ҫ����ʱ��İٷֱ� 
        /*
			����켣����һ��Բ
			x=cos(t),y=sin(t),��ʱ���������һȦ360��
			����Բ�켣��Բ������C=(m_startPosition+m_endPosition)/2 
        */ 
		    CCPoint C=ccp((m_startPosition.x+m_endPosition.x)*0.5,(m_startPosition.y+m_endPosition.y)*0.5);//Բ��
			float startarg=atan2(m_startPosition.y-C.y,m_startPosition.x-C.x);//�켣��������Բ�ĵķ�����ֵ��(-pi,pi]
		    float tempx=(m_startPosition.x-m_endPosition.x)*(m_startPosition.x-m_endPosition.x); 
			float tempy=(m_startPosition.y-m_endPosition.y)*(m_startPosition.y-m_endPosition.y); 
			float r=sqrt(tempx+tempy)*0.5;//Բ�İ뾶 
			float x=r*cos(startarg+2*M_PI*time*m_direction);//Բ�ϵ������Բ�ĵ�X����ƫ�� 
			float y=r*sin(startarg+2*M_PI*time*m_direction);//Բ�ϵ������Բ�ĵ�Y����ƫ�� 
			m_pTarget->setPosition(ccpAdd(C,ccp(x,y))); 
    } 
}

void myAction::startWithTarget(CCNode *pTarget){ 
    CCActionInterval::startWithTarget(pTarget); 
}

//add by Ivan_han 20130528
bool myAction::initWithDuration(float duration,float InitElapsed,pFuncVoid fun)
{
	if (CCActionInterval::initWithDuration(duration,InitElapsed)) 
	{ 
		m_Func=fun;
		return true; 
	} 
	return false; 
}

myAction* myAction::createTrace0(float duration,float InitElapsed,pFuncTrace0 fun)
{
	myAction * pmyAction=new myAction(); 
	pmyAction->initWithDuration(duration,InitElapsed,(pFuncVoid)fun);
	pmyAction->m_TraceType=0;
	pmyAction->autorelease(); 

	return pmyAction; 
}

myAction* myAction::createTrace1(float duration,float InitElapsed,pFuncTrace1 fun,const CCPoint& startP,const CCPoint& rdeltArg,float direction,const CCPoint& reserved)
{
	myAction * pmyAction=new myAction(); 
	if(pmyAction==NULL) 
	{ 
		return NULL; 
	}
	if(pmyAction->CCActionInterval::initWithDuration(duration,InitElapsed)==false) 
	{ 
		return NULL; 
	}
	pmyAction->m_Func=(pFuncVoid)fun;
	pmyAction->m_TraceType=1;
	pmyAction->m_startP=startP;
	pmyAction->m_centerP=rdeltArg;
	pmyAction->m_direction=direction;
	pmyAction->m_reserved=reserved;
	pmyAction->autorelease(); 

	return pmyAction; 
}
 
myAction* myAction::create(float duration,float InitElapsed,const char *func){ 
    myAction * pmyAction=new myAction(); 
    pmyAction->initWithDuration(duration,InitElapsed,func);
	pmyAction->m_TraceType=-2;
    pmyAction->autorelease();

    return pmyAction; 
}
//��������õ���ʼ������ 
bool myAction::initWithDuration(float duration,float InitElapsed,const char *func){ 
    if (CCActionInterval::initWithDuration(duration,InitElapsed)) 
    { 
		strcpy(m_TraceFunc,func);
        return true; 
    } 
    return false; 
}

//���п��Ʋ�����createXXX����
myAction* myAction::createCircle(float duration,float InitElapsed,const char *func,const CCPoint& startP,const CCPoint& centerP,float direction)
{
    return myAction::createCycloid(duration,InitElapsed,func,startP,centerP,direction,CCPoint(0,0)); 
}

//���п��Ʋ�����createXXX����
myAction* myAction::createCycloid(float duration,float InitElapsed,const char *func,const CCPoint& startP,const CCPoint& rdeltArg,float direction,const CCPoint& reserved)
{
    myAction * pmyAction=new myAction(); 
    if(pmyAction==NULL) 
    { 
        return NULL; 
    }
	if(pmyAction->CCActionInterval::initWithDuration(duration,InitElapsed)==false) 
    { 
        return NULL; 
    }
	strcpy(pmyAction->m_TraceFunc,func);
	pmyAction->m_TraceType=-1;
	pmyAction->m_startP=startP;
	pmyAction->m_centerP=rdeltArg;
	pmyAction->m_direction=direction;
	pmyAction->m_reserved=reserved;
    pmyAction->autorelease(); 
 
    return pmyAction; 
}

//���ö�����һԪʵ����һ�׵�����add by Ivan_han 20130608
float myAction::dif1fx(float(*fx)(float),float x)
{
	return (fx(x+0.0000001)-fx(x))/0.0000001;
}

CCPoint myAction::dif1fx(pFuncTrace0 Func,float t)
{
	float dx=(Func(t+0.001).x-Func(t).x);
	float dy=(Func(t+0.001).y-Func(t).y);
	return CCPoint(dx,dy);
}

CCPoint myAction::dif1fx(pFuncTrace0 Func,float t,int W,int H,int W1,int H1)
{
	CCPoint pt=CShipMgr::ScaleTrans(W,H,W1,H1,Func(t));
	CCPoint pt1=CShipMgr::ScaleTrans(W,H,W1,H1,Func(t+0.001));
	float dx=(pt1.x-pt.x);
	float dy=(pt1.y-pt.y);
	return CCPoint(dx,dy);
}

void myAction::update(float time){ 
    if (m_pTarget && (m_TraceFunc||m_Func)) 
    { 
		if(m_TraceType==0)
		{
			CCPoint retP=((pFuncTrace0)m_Func)(time);
			//add by Ivan_han 20130617
			retP=CShipMgr::ScaleTrans(1024,650,MAX_WIDTH,MAX_HEIGHT,retP);
			//add by Ivan_han 20130608
			if(g_pShipMgr!=NULL)
				retP=g_pShipMgr->SP2CP(retP);//�����
			m_pTarget->setPosition(retP);
			////���ĳЩ�������߹켣����˸���
			//if(time-m_t<0.05 && m_t>getInitElapsed())
			//	return;
			//���ݽ��켣�����߷�����½���CWֵ
			//CCPoint arg1=dif1fx(((pFuncTrace0)m_Func),time);
			CCPoint arg1=dif1fx(((pFuncTrace0)m_Func),time,1024,650,MAX_WIDTH,MAX_HEIGHT);
			if(g_pShipMgr!=NULL)
				arg1=g_pShipMgr->SD2CD(arg1);//������
			float m_fArg=m_pTarget->getArg();
			float angle=(m_fArg-atan2(arg1.y,arg1.x))*180/M_PI;
			m_pTarget->setRotation(angle);
			m_t=time;
			return;
		}
		if(m_TraceType==1)
		{
			CCPoint retP=((pFuncTrace1)m_Func)(time,m_startP.x,m_startP.y,m_centerP.x,m_centerP.y,m_direction,m_reserved.x,m_reserved.y);
			m_pTarget->setPosition(retP);
			if(m_Func1)
			{
				//���ݽ��켣�����߷�����½���CWֵ��add by Ivan_han 20130531
				CCPoint arg1=((pFuncTrace1)m_Func1)(time,m_startP.x,m_startP.y,m_centerP.x,m_centerP.y,m_direction,m_reserved.x,m_reserved.y);
				float m_fArg=m_pTarget->getArg();//M_PI;
				float angle=(m_fArg-atan2(arg1.y,arg1.x))*180/M_PI;
				m_pTarget->setRotation(angle);
			}
			return;
		}
		if(m_TraceType==-2)
		{
				////�����time���൱�ڵ�ǰʱ��ռ�ܵ���Ҫ����ʱ��İٷֱ�
				//CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
				//lua_State* m_state = pEngine->getLuaState();
				////int recv=pEngine->executeGlobalFunction(m_TraceFunc,1);
				////������
				//lua_getglobal(m_state,m_TraceFunc);
				////��һ������ѹջ
				//lua_pushnumber(m_state, time);
				////���ú���
				//lua_call(m_state, 1, 1);
				////�õ�����ֵ
				//CCPoint retP=*(CCPoint*)(tolua_tousertype(m_state,2,0));
				//lua_pop(m_state, 1);

				//m_pTarget->setPosition(retP); 
				return;
		}
		if(m_TraceType==-1)
		{
				////�����time���൱�ڵ�ǰʱ��ռ�ܵ���Ҫ����ʱ��İٷֱ�
				//CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
				//lua_State* m_state = pEngine->getLuaState();
				////������
				//lua_getglobal(m_state,m_TraceFunc);
				////��һ������ѹջ
				//lua_pushnumber(m_state, time);
				////�ڶ���������ѹջ
				////lua_pushlightuserdata(m_state, &m_startP);
				////void *lp=lua_newuserdata(m_state,sizeof(CCPoint));
				////memcpy(lp,&m_startP,sizeof(CCPoint));
				//lua_pushnumber(m_state,m_startP.x);
				//lua_pushnumber(m_state,m_startP.y);
				////�����������ѹջ
				////lua_pushlightuserdata(m_state, &m_centerP);
				////void *lp1=lua_newuserdata(m_state,sizeof(CCPoint));
				////memcpy(lp1,&m_centerP,sizeof(CCPoint));
				//lua_pushnumber(m_state,m_centerP.x);
				//lua_pushnumber(m_state,m_centerP.y);
				////����������ѹջ
				//lua_pushnumber(m_state,m_direction);
				////���߰˸�����ѹջ
				//lua_pushnumber(m_state,m_reserved.x);
				//lua_pushnumber(m_state,m_reserved.y);
				////���ú���
				//lua_call(m_state,8, 1);
				////�õ�����ֵ
				//CCPoint retP=*(CCPoint*)(tolua_tousertype(m_state,2,0));
				//lua_pop(m_state, 1);

				////m_pTarget->setPosition(CCPoint(m_startP.x+retP.x,m_startP.y+retP.y));//��Ϊ���λ����֧��CCRepeatForever���޴��ظ�����
				//m_pTarget->setPosition(retP);
				return;
		}


    } 
}


#pragma once

#include "..\..\..\cocos2dx\actions\CCActionInterval.h"//����ϵͳ��ʱ�ද��ͷ�ļ�
using namespace cocos2d;

/***********************************************
Name��CircleAction
Desc��Բ�˶��켣
Auth��Ivan_han@2013-04-23
***********************************************/
/*
   LUA��ʹ�÷�����
   --�켣���
   self:setPosition(CCPoint(200,300));
   --Բ��ʱ���˶��켣������һΪ����ʱ����������Ϊ��ǰԲ��λ�õĶԾ������꣬������Ϊ�켣����
   self:runAction(CircleAction:create(3.0, ccp(500,300),1));

    --�켣���
    self:setPosition(CCPoint(200,300));
    --Բ˳ʱ���˶��켣������һΪ����ʱ����������Ϊ��ǰԲ��λ�õĶԾ������꣬������Ϊ�켣����
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
    CCPoint m_startPosition;//�켣���
    CCPoint m_endPosition;//�켣�յ�
	int m_direction;//1��ʾ��ʱ��Anti-clockwise��-1��ʾ˳ʱ��Clockwise
};

/***********************************************
Name��myAction
Desc�������˶��켣,�켣�Ĳ�������д��LUA�ű���
Auth��Ivan_han@2013-04-23
***********************************************/
/*
   LUA��ʹ�÷�����
   --�Զ����˶��켣������һΪ����ʱ����������Ϊ��ʾ�켣�������̵�LUA������
   self:runAction(myAction:create(3.0,"CircleTrace"));

   --Բ����Ϊ(350,300)���뾶Ϊ150���켣���Ϊ(500,300)����ʱ��Բ�켣
   --Բ�˶��켣������һΪ����ʱ����������Ϊ��ʾԲ�켣�������̵�LUA��������������Ϊ�켣������꣬������ΪԲ�����꣬������Ϊ����Ȧ��
   self:runAction(myAction:createCircle(3.0,"CircleTraceFunc",ccp(500,300),ccp(350,300),1));
*/
class  myAction : public CCActionInterval 
{ 
public: 
	myAction(){memset(m_TraceFunc,0,sizeof(m_TraceFunc));m_TraceType=0;}

    /** initializes the action */ 
    bool initWithDuration(float duration,const char *func); 
 
    virtual void startWithTarget(CCNode *pTarget); 
    virtual void update(float time); 
 
public: 
    /** creates the action */
	//�൱��CC**To
    static myAction* create(float duration,const char *func);
	/*
	   ���п��Ʋ�����createXXX�������൱��CC**By
	   ����˵����
	   centerP/rdeltArg----����Բ�켣�����߹켣���ֱ����Բ�����ꡢԲ�İ뾶�ͷ�����ֵ����
	   reserved----��Ϊ����������һ���̻����߹켣��reserved.y=0ʱΪˮƽ���ҵİ��߹켣
	*/
	static myAction* createCircle(float duration,const char *func,const CCPoint& startP,const CCPoint& centerP,float direction);
	static myAction* createCycloid(float duration,const char *func,const CCPoint& startP,const CCPoint& rdeltArg,float direction,const CCPoint& reserved);
 
protected: 
	char m_TraceFunc[20];//LUA������,�����˹켣�Ĳ�������
	int m_TraceType;//0��ʾcreate��1��ʾcreateCircle��createMoveCircle
	//���Բ�켣�����߹켣�ĳ�Ա����
    CCPoint m_startP;//�켣���
    CCPoint m_centerP;//�켣���ĵ㣬�������centerP/rdeltArg
	float m_direction;//1��ʾ��ʱ��Anti-clockwise��-1��ʾ˳ʱ��Clockwise
	//����ƶ���Բ�켣�����߹켣������ĳ�Ա����
	CCPoint m_reserved;//��һ���̻����߹켣
};


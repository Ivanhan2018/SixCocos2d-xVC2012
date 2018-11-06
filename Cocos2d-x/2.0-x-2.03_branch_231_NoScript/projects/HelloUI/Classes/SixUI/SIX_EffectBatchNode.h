/***********************************************
Name��SIX_EffectBatchNode
Desc����Ч������
Auth��Cool.Cat@2013-07-25
***********************************************/
#pragma once
#include <cocos2d.h>
#include "SIX_Typedef.h"
//#include <EasyDataTime.h>

//USING_NS_CC;
//USING_NS_CC_EXT;

// ��Ч����
typedef enum {
	// ��
	EFFECT_NONE	= 0,
	// ����
	EFFECT_FADEIN,
	// ����
	EFFECT_FADEOUT,
	// ����
	EFFECT_SCALE,
	// ��ת
	EFFECT_ROTATION,
} EFFECT_TYPE;

#define EFFECT_VALUE	1.5f

// ����ʱ��(Ĭ��)
#define EFFECT_DURTIME	0.5f

class SIX_EffectBatchNode:public CCSpriteBatchNode
{
public:
	SIX_EffectBatchNode();
	virtual ~SIX_EffectBatchNode();
	static SIX_EffectBatchNode *Create(const char *file,EFFECT_TYPE effectType=EFFECT_NONE,float value=EFFECT_VALUE,float durtime=EFFECT_DURTIME);
public:
	EFFECT_TYPE getEffectType();
	void setEffectType(EFFECT_TYPE animateType);

	float getEffectValue();
	void setEffectValue(float value);

	float getDurtime();
	void setDurtime(float durtime);

	virtual void DoEffect(CCNode *,float delay=0.0f);
	virtual void DoEffectOnChildren(float delay=0.0f);
protected:
	// ��������(��ʱֻ֧�ֵ���������������ʵ�־ۺ϶���)
	EFFECT_TYPE m_tEffectType;
	// Ч��ֵ
	float m_fValue;
	// ����ִ��ʱ��
	float m_fDurtime;
};
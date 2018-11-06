/***********************************************
Name：SIX_EffectBatchNode
Desc：特效批处理
Auth：Cool.Cat@2013-07-25
***********************************************/
#pragma once
#include <cocos2d.h>
#include "SIX_Typedef.h"
//#include <EasyDataTime.h>

//USING_NS_CC;
//USING_NS_CC_EXT;

// 特效类型
typedef enum {
	// 无
	EFFECT_NONE	= 0,
	// 渐入
	EFFECT_FADEIN,
	// 渐出
	EFFECT_FADEOUT,
	// 缩放
	EFFECT_SCALE,
	// 旋转
	EFFECT_ROTATION,
} EFFECT_TYPE;

#define EFFECT_VALUE	1.5f

// 持续时间(默认)
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
	// 动画类型(暂时只支持单个动画，后期再实现聚合动画)
	EFFECT_TYPE m_tEffectType;
	// 效果值
	float m_fValue;
	// 动画执行时间
	float m_fDurtime;
};
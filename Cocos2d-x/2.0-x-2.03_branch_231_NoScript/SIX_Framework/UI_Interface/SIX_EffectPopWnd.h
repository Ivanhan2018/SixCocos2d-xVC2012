/***********************************************
Name：SIX_EffectPopWnd
Desc：特效弹出框，在PopWnd特效基础上增加了上下左右
	  4个方向的正反移动特效，以及视角控制（旋转）
Auth：Cool.Cat@2013-07-29
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_PopWnd.h>

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
	MOVABLE_NONE	=	-1,
	MOVABLE_LEFT	=	1,
	MOVABLE_RIGHT,
	MOVABLE_TOP,
	MOVABLE_BOTTOM,
} MOVABLE_TYPE;

#define	DEFAULT_SHAKEOFFSET	20.0f

class SIX_EffectPopWnd:public SIX_PopWnd
{
public:
	SIX_EffectPopWnd();
	virtual ~SIX_EffectPopWnd();
public:
	static SIX_EffectPopWnd *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	// 显示/隐藏窗口
	virtual void Show(bool IsShow=true);
	virtual void onShowFinished();
	virtual void onHideFinished();

	void setShowType(MOVABLE_TYPE type);
	MOVABLE_TYPE getShowType();

	void setHideType(MOVABLE_TYPE type);
	MOVABLE_TYPE getHideType();

	void setShakeOffset(float shakeOffset);
	float getShakeOffset();

	void setSeqExec(bool bSeqExec=true);
	bool getSeqExec();

	// 设置显示/隐藏位移参数
	void setParamsShowMovable(float delayBegin,float delayMax,float delayMin,float delayEnd);
	void setParamsHideMovable(float delayEnd);
	// 设置显示/隐藏非位移参数
	void setParamsShowUnMovable(float delayScaleMax,float ratioScaleMax,float delayScaleOrigin,float ratioScaleOrigin);
	void setParamsHideUnMovable(float delayScaleMax,float ratioScaleMax,float delayScaleMin,float ratioScaleMin);
private:
	MOVABLE_TYPE m_tShowType;
	MOVABLE_TYPE m_tHideType;
	// 振幅
	float m_fShakeOffset;
	// 是否序列执行(false=同步执行)
	bool m_bSeqExec;

	// 以下为位移动作参数
	// Cool.Cat
	// 开始偏移延迟(显示)=0.1f
	float m_fShowDelayBeginOffset;
	// 最大偏移延迟(显示)=0.1f
	float m_fShowDelayMaxOffset;
	// 最小偏移延迟(显示)=0.1f
	float m_fShowDelayMinOffset;
	// 结束偏移延迟(显示)=0.1f
	float m_fShowDelayEndOffset;

	// 结束偏移延迟(隐藏)=0.3f
	float m_fHideDelayEndOffset;

	// 以下为非位移动作(MOVABLE_NONE)参数
	// 最大拉伸延迟(显示)=0.2f
	float m_fShowDelayScaleMax;
	// 原始拉伸延迟(显示)=0.1f
	float m_fShowDelayScaleOrigin;
	// 最大拉伸比率(显示)=1.05f
	float m_fShowRatioScaleMax;
	// 原始拉伸比率(显示)=1.0f
	float m_fShowRatioScaleOrigin;

	// 最大拉伸延迟(隐藏)=0.1f
	float m_fHideDelayScaleMax;
	// 最小拉伸延迟(隐藏)=0.2f
	float m_fHideDelayScaleMin;
	// 最大拉伸比率(隐藏)=1.05f
	float m_fHideRatioScaleMax;
	// 最小拉伸比率(隐藏)=0.0f
	float m_fHideRatioScaleMin;
};
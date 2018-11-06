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
private:
	MOVABLE_TYPE m_tShowType;
	MOVABLE_TYPE m_tHideType;
	// 振幅
	float m_fShakeOffset;
	// 是否序列执行(false=同步执行)
	bool m_bSeqExec;
};
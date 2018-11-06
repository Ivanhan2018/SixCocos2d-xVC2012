/***********************************************
Name��SIX_EffectPopWnd
Desc����Ч��������PopWnd��Ч��������������������
	  4������������ƶ���Ч���Լ��ӽǿ��ƣ���ת��
Auth��Cool.Cat@2013-07-29
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

	// ��ʾ/���ش���
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

	// ������ʾ/����λ�Ʋ���
	void setParamsShowMovable(float delayBegin,float delayMax,float delayMin,float delayEnd);
	void setParamsHideMovable(float delayEnd);
	// ������ʾ/���ط�λ�Ʋ���
	void setParamsShowUnMovable(float delayScaleMax,float ratioScaleMax,float delayScaleOrigin,float ratioScaleOrigin);
	void setParamsHideUnMovable(float delayScaleMax,float ratioScaleMax,float delayScaleMin,float ratioScaleMin);
private:
	MOVABLE_TYPE m_tShowType;
	MOVABLE_TYPE m_tHideType;
	// ���
	float m_fShakeOffset;
	// �Ƿ�����ִ��(false=ͬ��ִ��)
	bool m_bSeqExec;

	// ����Ϊλ�ƶ�������
	// Cool.Cat
	// ��ʼƫ���ӳ�(��ʾ)=0.1f
	float m_fShowDelayBeginOffset;
	// ���ƫ���ӳ�(��ʾ)=0.1f
	float m_fShowDelayMaxOffset;
	// ��Сƫ���ӳ�(��ʾ)=0.1f
	float m_fShowDelayMinOffset;
	// ����ƫ���ӳ�(��ʾ)=0.1f
	float m_fShowDelayEndOffset;

	// ����ƫ���ӳ�(����)=0.3f
	float m_fHideDelayEndOffset;

	// ����Ϊ��λ�ƶ���(MOVABLE_NONE)����
	// ��������ӳ�(��ʾ)=0.2f
	float m_fShowDelayScaleMax;
	// ԭʼ�����ӳ�(��ʾ)=0.1f
	float m_fShowDelayScaleOrigin;
	// ����������(��ʾ)=1.05f
	float m_fShowRatioScaleMax;
	// ԭʼ�������(��ʾ)=1.0f
	float m_fShowRatioScaleOrigin;

	// ��������ӳ�(����)=0.1f
	float m_fHideDelayScaleMax;
	// ��С�����ӳ�(����)=0.2f
	float m_fHideDelayScaleMin;
	// ����������(����)=1.05f
	float m_fHideRatioScaleMax;
	// ��С�������(����)=0.0f
	float m_fHideRatioScaleMin;
};
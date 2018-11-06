/***********************************************
Name��SIX_PopWndSetting
Desc����Ϸ�������ô���
Auth��Cool.Cat@2013-07-06
***********************************************/
#pragma once
#include <cocos2d.h>
#include "SIX_Typedef.h"
#include "SIX_DSTPL.h"
#include "SIX_GlobalMgr.h"
#include "SIX_ScrollBar.h"
#include "cocos-ext.h"
#include "SIX_PopWnd.h"

USING_NS_CC;
USING_NS_CC_EXT;

typedef enum {
	AUDIO_MUTE = 1,
	EFFECT_MUTE = 2,
} BTN_MUTE;

class SIX_PopWndSetting:public SIX_PopWnd
{
public:
	virtual ~SIX_PopWndSetting();
public:
	static SIX_PopWndSetting *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual bool init();
private:
	virtual void onEnterTransitionDidFinish();
	// �������ص�
	virtual void ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent);
	virtual void doEvents(CCObject* pSender, CCControlEvent event);
	void setAudioMuteOrNot();
	void setEffectMuteOrNot();
public:
	// ����
	SIX_ScrollBar *pScrollBarAudio;
	// ��Ч
	SIX_ScrollBar *pScrollBarEffect;
	// ��������
	CCControlButton *pBtnAudioMute;
	// ��Ч����
	CCControlButton *pBtnEffectMute;
	// ��һ�������ٷֱ�
	float m_LastAudioRatio;
	// ��һ����Ч�ٷֱ�
	float m_LastEffectRatio;
};
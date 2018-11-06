/***********************************************
Name��SIX_PopWndSetting
Desc����Ϸ�������ô���
Auth��Cool.Cat@2013-07-06
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include <SIX_EffectPopWnd.h>
#include "SIX_PopWndResetPassWord.h"
#include "SIX_PopWndAntiddiction.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum {
	AUDIO_MUTE = 1,
	RUB_CARD,
	RESET_PASS,
	REAL_NAME,
	LOG_OFF,
};

class SIX_PopWndSetting:public SIX_EffectPopWnd
{
public:
	virtual ~SIX_PopWndSetting();
public:
	static SIX_PopWndSetting *Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset=DEFAULT_SHAKEOFFSET,MOVABLE_TYPE showType=MOVABLE_LEFT,MOVABLE_TYPE hideType=MOVABLE_RIGHT,bool bSeqExec=true);
public:
	virtual bool init();
#ifdef WIN32
	int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam);
#endif
private:
	virtual void onEnterTransitionDidFinish();
	// �������ص�
	virtual void ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent);
	virtual void doEvents(CCObject* pSender, CCControlEvent event);
	void setAudioMuteOrNot();
	void setRubCardYesOrNot();
public:
	// ����
	SIX_ScrollBar *pScrollBarAudio;
	// ��������
	CCControlButton *pBtnAudioMute;
	// ��һ�������ٷֱ�
	float m_LastAudioRatio;
	// ���ư�ť
	CCControlButton *pBtnRubCard;
	// �޸�����
	SIX_PopWndResetPassWord *pPopResetPassWord;
	// ������
	SIX_PopWndAntiddiction *pPopAntiddiction;
};
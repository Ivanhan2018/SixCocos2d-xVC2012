/***********************************************
Name：SIX_PopWndSetting
Desc：游戏场景设置窗口
Auth：Cool.Cat@2013-07-06
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
	// 滚动条回调
	virtual void ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent);
	virtual void doEvents(CCObject* pSender, CCControlEvent event);
	void setAudioMuteOrNot();
	void setEffectMuteOrNot();
public:
	// 音量
	SIX_ScrollBar *pScrollBarAudio;
	// 音效
	SIX_ScrollBar *pScrollBarEffect;
	// 音量禁音
	CCControlButton *pBtnAudioMute;
	// 音效禁音
	CCControlButton *pBtnEffectMute;
	// 上一次音量百分比
	float m_LastAudioRatio;
	// 上一次音效百分比
	float m_LastEffectRatio;
};
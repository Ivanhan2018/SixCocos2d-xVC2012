/***********************************************
Name��SIX_TipsPopWnd
Desc����ʾ����
Auth��Cool.Cat@2013-10-30
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include "SIX_EffectPopWnd.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_TipsPopWnd:public SIX_EffectPopWnd
{
public:
	virtual ~SIX_TipsPopWnd();
public:
	static SIX_TipsPopWnd *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
	// ����������ʾ
	void setTips(const char *text,const char *fontName,int fontSize);
	// �����Ƿ���������
	void setHideWhenTouched(bool bHideWhenTouched=true){m_bHideWhenTouched=bHideWhenTouched;}
	bool getHideWhenTouched(){return m_bHideWhenTouched;}
private:
	// ������ʾ
	CCLabelTTF *m_pText;
	// �Ƿ���������
	bool m_bHideWhenTouched;
};
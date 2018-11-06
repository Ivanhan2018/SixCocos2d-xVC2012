/***********************************************
Name：SIX_MsgBox
Desc：SIX_MsgBox
Auth：Cool.Cat@2013-04-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_MsgBox:public SIX_PopWnd
{
public:
	virtual ~SIX_MsgBox();
public:
	static SIX_MsgBox *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual bool init();

	// 正文
	void setTextAttribute(float x,float y,float w,float h,const char *fontName="微软雅黑",int fontSize=12,CCTextAlignment hAlignment=kCCTextAlignmentLeft);
	void setString(const char *text);
private:
	virtual void onEnterTransitionDidFinish();
public:
	// 正文
	CCLabelTTF *pText;
};
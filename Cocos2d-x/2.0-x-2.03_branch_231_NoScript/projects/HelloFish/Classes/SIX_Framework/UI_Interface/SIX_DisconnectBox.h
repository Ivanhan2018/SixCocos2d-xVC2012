/***********************************************
Name：SIX_DisconnectBox
Desc：SIX_DisconnectBox
Auth：Cool.Cat@2013-08-22
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"
#include "SIX_UIScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_UIScene;

class SIX_DisconnectBox:public SIX_PopWnd
{
public:
	virtual ~SIX_DisconnectBox();
public:
	static SIX_DisconnectBox *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual bool init();

	// 正文
	void setTextAttribute(float x,float y,float w,float h,const char *fontName="微软雅黑",int fontSize=12,CCTextAlignment hAlignment=kCCTextAlignmentLeft);
	void setString(const char *text);
	// Loading
	void setLoadingAttribute(float x,float y,float dely,SIX_UIScene *pScene=0,SEL_CallFunc pfn=0);
	void UnExec();
private:
	virtual void onEnterTransitionDidFinish();
	bool OnSubmit();
	void Hide(CCNode *node);
public:
	// 正文
	CCLabelTTF *pText;
	SIX_UIScene *pfnScene;
	SEL_CallFunc pfnCallBack;
};
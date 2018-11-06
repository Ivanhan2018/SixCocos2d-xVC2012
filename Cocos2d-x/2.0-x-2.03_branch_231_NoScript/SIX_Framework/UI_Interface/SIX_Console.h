/***********************************************
Name£ºSIX_Console
Desc£ºSIX_Console
Auth£ºCool.Cat@2013-04-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"
#include "SIX_ListView.h"
#include "SIX_ListViewCell.h"
#include "SIX_ScrollBar.h"
#include "SIX_EditBox.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_Console:public SIX_PopWnd{
public:
	virtual ~SIX_Console();
public:
	static SIX_Console *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void update(float t);
	void ShowConsole(CCLayer *pThis);

	void InitTitle(const char *text);
	void InitRuntime(const char *text);
	void InitEditBox();
	void InitListView();

	void DoEnter();
	virtual void OnInputDone(CCLayer *pLayer,const char *text);

	void setRuntime(const char *text);
	void setContent(const char *fmt,...);
	const char *GetFormatRuntime();
public:
	CCLayer *pFather;
	SIX_ListView *pListView;
	SIX_EditBox *pEditBox;
	CCLabelTTF *pTitleTTF;
	CCLabelTTF *pRuntimeTTF;
	double m_LastShowTime;
	int __EditBoxH;
	int __PaddingLR;
	int __PaddingT;
	int __HeaderH;
	int __SubmitW;
};
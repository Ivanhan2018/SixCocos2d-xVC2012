/***********************************************
Name£º½ø¶ÈÌõ
Desc£º
Auth£ºCool.Cat@2013-04-03
***********************************************/
#pragma once
#include <SIX_UIControl.h>
#include <misc_nodes\CCProgressTimer.h>

USING_NS_CC;

class SIX_UIProgress:public SIX_UIControl,public CCProgressTimer
{
public:
	SIX_UIProgress(){}
	virtual ~SIX_UIProgress(){}
public:
	void *GetInterface(const char *pstrName);
	CCString GetClass() const;
public:
	virtual void draw();
public:

};
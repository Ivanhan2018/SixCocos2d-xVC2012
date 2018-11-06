/*********************************************************
Name：场景类
Desc：内部UI控件操作、CCLayer事件响应分发到Lua中处理
Auth：Cool.Cat@2013-03-29
*********************************************************/
#pragma once
#include <cocos2d.h>
#include "SIX_Interface.h"
#include "SIX_UILayer.h"
#include "SIX_UIMgr.h"
#include "SIX_DSTPL.h"

class SIX_UIMgr;

USING_NS_CC;
//USING_NS_CC_EXT;

class SIX_UIScene:public SIX_UILayer
{
public:
	virtual ~SIX_UIScene();
public:
	static SIX_UIScene *scene();

	void InitUIMgr();
public:
	void *GetInterface(const char *pstrName);
public:
	SIX_UIMgr *GetUIMgr()				{return m_UIManager;}
	CCScene *GetScene()					{return m_Scene;}
public:
	SIX_UIMgr *m_UIManager;
	CCScene *m_Scene;
};
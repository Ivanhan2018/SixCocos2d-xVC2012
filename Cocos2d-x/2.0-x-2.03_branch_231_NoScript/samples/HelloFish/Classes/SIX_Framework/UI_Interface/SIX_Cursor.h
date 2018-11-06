/***********************************************
Name：SIX_Cursor
Desc：自定义鼠标(Win32)
Auth：Cool.Cat@2013-07-27
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_EffectBatchNode.h>

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_Cursor:public TSingleton<SIX_Cursor>
{
public:
	SIX_Cursor();
	virtual ~SIX_Cursor();
	bool LoadCursorFromFile(const char *file);
	void DoRelease();
public:
	void setShowSysCursor(BOOL bShowSysCursor=FALSE);
	BOOL getShowSysCursor();

	void setShowOurCursor(bool bShowOurCursor=false);
	bool getShowOurCursor();

	void setIngore(bool bIngore=true);
	bool getIngore();

	void setInited(bool bInited=true);
	bool getInited();

	CCSprite *getCursor();
	void setCursor(CCSprite *cursor);

	void OnTouchLogic(CCSet *pTouches,int pEvent);
protected:
	CCSprite *m_pCursor;
	bool m_bInited;
	bool m_bIngore;
};
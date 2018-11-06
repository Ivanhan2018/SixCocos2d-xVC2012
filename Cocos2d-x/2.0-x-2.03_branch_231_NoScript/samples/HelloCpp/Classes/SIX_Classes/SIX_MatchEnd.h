/***********************************************
Name：SIX_MatchEnd
Desc：比赛结算框
Auth：团长@2013-08-12
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"
#include "SIX_Common.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_MatchEnd:public SIX_PopWnd
{
public:
	virtual ~SIX_MatchEnd();

public:
	static SIX_MatchEnd *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
	// 设置比赛数据
	void SetMatchData(CMD_MatchEnd *pData);
	// 设置自己
	void SetMyselfID(long long nUserID);

public:
	bool init();

private:
	virtual void onEnterTransitionDidFinish();
	virtual void doEvents(CCObject* pSender, CCControlEvent event);

private:
	CMD_MatchEnd m_MatchData;
	long long	m_llUserID;
};
/***********************************************
Name：SIX_PopWndPlayerInfo
Desc：玩家资料窗口
Auth：Cool.Cat@2013-10-09
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_PopWndPlayerInfo:public SIX_PopWnd
{
public:
	virtual ~SIX_PopWndPlayerInfo();
public:
	static SIX_PopWndPlayerInfo *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);

	void setPlayerLogo(long long llSysLogoID);
	void setPlayerNickName(const char *name);
	void setPlayerMoney(int money);
	void setPlayerLevel(int level);
	void setPlayerWinRound(int round);
	void setPlayerTotalRound(int round);

	void setPlayerViewId(int idx);
	int getPlayerViewId();
private:
	virtual void onEnterTransitionDidFinish();
	void RefreshUI();
private:
	// 玩家头像
	CCSprite *m_pBgLogo;
	// 玩家昵称
	CCLabelTTF *m_pNickName;
	// 当前资产
	CCLabelTTF *m_pMoney;
	// 游戏等级
	CCLabelTTF *m_pLevel;
	// 等级图标
	CCSprite *m_pLevelIco;
	// 等级描述
	CCLabelTTF *m_pLevelDesc;
	// 已赢牌局
	CCLabelTTF *m_pWinRound;
	// 已玩牌局
	CCLabelTTF *m_pTotalRound;

	// 用户视图ID
	int m_PlayerViewId;
};
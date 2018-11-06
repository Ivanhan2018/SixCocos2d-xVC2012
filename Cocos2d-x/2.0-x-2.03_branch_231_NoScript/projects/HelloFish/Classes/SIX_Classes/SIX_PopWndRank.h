/***********************************************
Name：SIX_PopWndRank
Desc：排行榜
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

/// 当前界面显示内容
typedef enum tagCurrentShow
{
	CS_Exploit,			//	功勋排名
	CS_Match				// 比赛排名
}CS;

class SIX_PopWndRank:public SIX_PopWnd
{
public:
	virtual ~SIX_PopWndRank();

public:
	static SIX_PopWndRank *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);

	void SetExploitData(unsigned char *pData,int pDataLen);
	void SetMatchData(unsigned char *pData,int pDataLen);
	void SetShowData();
	void SetItemData(CCNode * pNode, int nIndex, int nCurPage, long long lUserID, const char *pcharNickName, int nScore, int nRewardGold);

	// 设置自己
	void SetMyselfID(long long nUserID);
	// 设置是否连接获取数据
	void SetLinkGetExploit(){ m_bGetExploitRanking = true; }
	void SetLinkGetMatch(){ m_bGetMatchRanking = true; }
	void SetLinkGetMyExpoit(){m_bGetMyExploitRanking = true; }
	void SetLinkGetMyMatch(){m_bGetMyMatchRanking = true; }

	// 取我的排名数据
	void GetMyRankingData(CMD_CS_UPD_FEATS_RANKING_REWARD & RankingData);
	void GetMyRankingData(CMD_CS_UPD_MATCH_RANKING_REWARD & RankingData);

protected:
	bool init();
	void SetPage(int nPage);
	unsigned int GetMyRanking();

private:
	virtual void onEnterTransitionDidFinish();
	virtual void doEvents(CCObject* pSender, CCControlEvent event);

private:
	CMD_MatchEnd m_MatchData;
	long long	m_llUserID;

	unsigned int	m_uCurExploitPage;		// 当前显示功勋页
	unsigned int	m_uCurMatchPage;			// 当前显示比赛页

	CS	m_ShowContent;					// 当前显示的内容，功勋或比赛排名
	vector< CMD_SC_FEATS_LIST *> m_vExploitRanking;		// 功勋排名
	vector<CMD_SC_MATCH_LIST *> m_vMatchRanking;		// 比赛排名

	bool m_bGetExploitRanking;		// 是否获取了功勋排名
	bool m_bGetMatchRanking;		// 是否获取了比赛排名
	bool m_bGetMyExploitRanking;	// 是否领取了我的功勋奖励
	bool m_bGetMyMatchRanking;	// 是否领取了我的比赛奖励
};
/***********************************************
Name��SIX_PopWndRank
Desc�����а�
Auth���ų�@2013-08-12
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

/// ��ǰ������ʾ����
typedef enum tagCurrentShow
{
	CS_Exploit,			//	��ѫ����
	CS_Match				// ��������
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

	// �����Լ�
	void SetMyselfID(long long nUserID);
	// �����Ƿ����ӻ�ȡ����
	void SetLinkGetExploit(){ m_bGetExploitRanking = true; }
	void SetLinkGetMatch(){ m_bGetMatchRanking = true; }
	void SetLinkGetMyExpoit(){m_bGetMyExploitRanking = true; }
	void SetLinkGetMyMatch(){m_bGetMyMatchRanking = true; }

	// ȡ�ҵ���������
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

	unsigned int	m_uCurExploitPage;		// ��ǰ��ʾ��ѫҳ
	unsigned int	m_uCurMatchPage;			// ��ǰ��ʾ����ҳ

	CS	m_ShowContent;					// ��ǰ��ʾ�����ݣ���ѫ���������
	vector< CMD_SC_FEATS_LIST *> m_vExploitRanking;		// ��ѫ����
	vector<CMD_SC_MATCH_LIST *> m_vMatchRanking;		// ��������

	bool m_bGetExploitRanking;		// �Ƿ��ȡ�˹�ѫ����
	bool m_bGetMatchRanking;		// �Ƿ��ȡ�˱�������
	bool m_bGetMyExploitRanking;	// �Ƿ���ȡ���ҵĹ�ѫ����
	bool m_bGetMyMatchRanking;	// �Ƿ���ȡ���ҵı�������
};
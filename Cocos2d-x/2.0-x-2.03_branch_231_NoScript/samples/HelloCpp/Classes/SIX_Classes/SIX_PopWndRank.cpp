#include "SIX_PopWndRank.h"
#include <SIX_NumberBatchNode.h>
#include "SIX_ClientLogin.h"
#include "SIX_Utility.h"

const int g_Tag = 100;
const unsigned int c_ShowCount = 7;				// 每页显示的数目

/// 按钮索引
enum
{
	BTN_1 = 1,					// 每周功勋排行按钮
	BTN_2,						// 每周比赛排行按钮
	BTN_EXIT,					// 退出按钮
	LAST_PAGE,				// 上一页按钮
	NEXT_PAGE,				// 下一页按钮
	RECEIVE_REWARD,	// 领取排行奖励按钮
	VIEW_MY_RANK,		// 查看我的排行按钮
	ITEM_DATA,				// 第一行数据 (用了7个枚举，所以占用了8~14)
	CUR_PAGE = 15,		// 当前页
	MY_RANKING,			// 我的排名
};

SIX_PopWndRank::~SIX_PopWndRank()
{
	vector< CMD_SC_FEATS_LIST *>::iterator vFeatsData = m_vExploitRanking.begin();
	for (; vFeatsData != m_vExploitRanking.end(); ++vFeatsData)
	{
		CMD_SC_FEATS_LIST *pData =*vFeatsData;
		CC_SAFE_DELETE(pData);
		vFeatsData = m_vExploitRanking.erase(vFeatsData);
		if (vFeatsData == m_vExploitRanking.end())
			break;
	}

	vector< CMD_SC_MATCH_LIST *>::iterator vMatchData = m_vMatchRanking.begin();
	for (; vMatchData != m_vMatchRanking.end(); ++vMatchData)
	{
		CMD_SC_MATCH_LIST *pData = *vMatchData;
		CC_SAFE_DELETE(pData);
		vMatchData = m_vMatchRanking.erase(vMatchData);
		if (vMatchData == m_vMatchRanking.end())
			break;
	}
}

SIX_PopWndRank *SIX_PopWndRank::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	if (0.0001 > x && 0.0001 > y)
	{
		CCSize szWind = CCDirector::sharedDirector()->getWinSize();
		x = (szWind.width - width) / 2;
		y = (szWind.height - height) / 2;
	}

	SIX_PopWndRank *pMatchEnd = new SIX_PopWndRank();
	if (pMatchEnd && pMatchEnd->init())
	{
		pMatchEnd->initWithColor(color,width,height);
		pMatchEnd->setPosition(x,y);
		pMatchEnd->setRedrawBorder(bRedrawBorder);
		pMatchEnd->setTouchEnabled(true);
		pMatchEnd->m_ForbiddenTouch = true;
		pMatchEnd->m_bCloseThenCleanup = bCloseThenCleanup;
		pMatchEnd->setObjName("SIX_PopWndRank");
	}
	return pMatchEnd;
}

void SIX_PopWndRank::SetExploitData(unsigned char *pData,int pDataLen)
{
	if (NULL == pData  ||  sizeof(CMD_SC_FEATS_LIST) != pDataLen)
		return;
	CMD_SC_FEATS_LIST *pFeatsList = (CMD_SC_FEATS_LIST *)pData;
	CMD_SC_FEATS_LIST * pNewData = new CMD_SC_FEATS_LIST;
	memcpy(pNewData, pFeatsList, sizeof(CMD_SC_FEATS_LIST));
	m_vExploitRanking.push_back(pNewData);
}

void SIX_PopWndRank::SetMatchData(unsigned char *pData,int pDataLen)
{
	if (NULL == pData  ||  sizeof(CMD_SC_MATCH_LIST) != pDataLen)
		return;

	CMD_SC_MATCH_LIST *pMatchList = (CMD_SC_MATCH_LIST *)pData;
	CMD_SC_MATCH_LIST * pNewData = new CMD_SC_MATCH_LIST;
	memcpy(pNewData, pMatchList, sizeof(CMD_SC_MATCH_LIST));
	m_vMatchRanking.push_back(pNewData);
}

void SIX_PopWndRank::SetMyselfID(long long nUserID)
{
	m_llUserID = nUserID;
}

void SIX_PopWndRank::GetMyRankingData(CMD_CS_UPD_FEATS_RANKING_REWARD & RankingData)
{
	memset(&RankingData, 0, sizeof(RankingData));
	vector< CMD_SC_FEATS_LIST *>::const_iterator vData = m_vExploitRanking.begin();
	for (; vData != m_vExploitRanking.end(); ++vData)
	{
		if ((*vData)->lUserID == m_llUserID)
		{
			RankingData.iID = (*vData)->iID;
			RankingData.iRankingNo = (*vData)->iRankingNo;
			RankingData.iSortId = (*vData)->iSortId;
			RankingData.lUserID = (*vData)->lUserID;
			break;
		}
	}
}

void SIX_PopWndRank::GetMyRankingData(CMD_CS_UPD_MATCH_RANKING_REWARD & RankingData)
{
	memset(&RankingData, 0, sizeof(RankingData));
	vector< CMD_SC_MATCH_LIST *>::const_iterator vData = m_vMatchRanking.begin();
	for (; vData != m_vMatchRanking.end(); ++vData)
	{
		if ((*vData)->lUserID == m_llUserID)
		{
			RankingData.iID = (*vData)->iID;
			RankingData.iRankingNo = (*vData)->iRankingNo;
			RankingData.iSortId = (*vData)->iSortId;
			RankingData.lUserID = (*vData)->lUserID;
			break;
		}
	}
}

bool SIX_PopWndRank::init()
{
	if (!SIX_PopWnd::init())
		return false;

	m_llUserID = 0l;
	m_uCurExploitPage = 0;
	m_uCurMatchPage = 0;
	m_ShowContent = CS_Exploit;
	m_bGetExploitRanking = false;
	m_bGetMatchRanking = false;
	m_bGetMyExploitRanking = false;
	m_bGetMyMatchRanking = false;

	if (!m_bGetExploitRanking)
	{
		SIX_ClientLogin::GetInstance()->SetConnectionType(CONNECTION_EXPLOIT);
		SIX_ClientLogin::GetInstance()->Connect();
	}
	return true;
}

void SIX_PopWndRank::SetPage(int nPage)
{
	unsigned int &nCurPage = (CS_Exploit == m_ShowContent) ? m_uCurExploitPage : m_uCurMatchPage;
	nPage += (CS_Exploit==m_ShowContent) ? m_uCurExploitPage : m_uCurMatchPage;

	if (nPage == nCurPage)
		return;
	int nAllCount = (CS_Exploit == m_ShowContent) ? m_vExploitRanking.size() : m_vMatchRanking.size();
	if (0 == nAllCount)
		return;
	int nNewPage = nAllCount/c_ShowCount + (0 < (nAllCount%c_ShowCount) ? 1 : 0);
	if (0>nPage  ||  nNewPage<=nPage)
		return;
	nCurPage = nPage;
}

unsigned int SIX_PopWndRank::GetMyRanking()
{
	if (CS_Exploit == m_ShowContent)
	{
		unsigned int nRank = 0;
		vector< CMD_SC_FEATS_LIST *>::const_iterator vData = m_vExploitRanking.begin();
		for (; vData != m_vExploitRanking.end(); ++vData)
		{
			nRank++;
			if ((*vData)->lUserID == m_llUserID)
			{
				return nRank;
			}
		}
	}
	else if (CS_Match == m_ShowContent)
	{
		unsigned int nRank = 0;
		vector< CMD_SC_FEATS_LIST *>::const_iterator vData = m_vExploitRanking.begin();
		for (; vData != m_vExploitRanking.end(); ++vData)
		{
			nRank++;
			if ((*vData)->lUserID == m_llUserID)
			{
				return nRank;
			}
		}
	}
	return 0;
}

void SIX_PopWndRank::SetShowData()
{
	// 未创建窗口
	if (NULL == pBackground)
		return;

	for (int i=0; i<7; i++)
	{
		CCNode * pNode = pBackground->getChildByTag(ITEM_DATA+i);
		if (NULL != pNode)
		{
			pNode->setVisible(false);
		}
	}

	if (CS_Exploit == m_ShowContent)
	{
		vector< CMD_SC_FEATS_LIST *>::size_type sIndex = c_ShowCount*m_uCurExploitPage;
		for (int i=0; sIndex<m_vExploitRanking.size() &&  i<7; ++sIndex,++i)
		{
			CMD_SC_FEATS_LIST *pFeatsList = m_vExploitRanking.at(sIndex);
			CCNode * pNode = pBackground->getChildByTag(ITEM_DATA+i);
			if (NULL != pNode)
			{
				SetItemData(pNode,i,m_uCurExploitPage,pFeatsList->lUserID, pFeatsList->szNickName, pFeatsList->iFeats, pFeatsList->iRewardGold);
			}
		}
	}
	else if (CS_Match == m_ShowContent)
	{
		vector< CMD_SC_MATCH_LIST *>::size_type sIndex = c_ShowCount*m_uCurMatchPage;
		for (int i=0; sIndex<m_vMatchRanking.size() &&  i<7; ++sIndex,++i)
		{
			CMD_SC_MATCH_LIST *pMatchList = m_vMatchRanking.at(sIndex);
			CCNode * pNode = pBackground->getChildByTag(ITEM_DATA+i);
			{
				SetItemData(pNode,i,m_uCurMatchPage,pMatchList->lUserID,pMatchList->szNickName,pMatchList->iGameCoin,pMatchList->iRewardGold);
			}
		}
	}

	// 设置我的排名
	CCLabelTTF *pMyRank = dynamic_cast<CCLabelTTF *>(pBackground->getChildByTag(MY_RANKING));
	if (NULL != pMyRank)
	{
		pMyRank->setString(CCString::createWithFormat("%u", GetMyRanking())->getCString());
	}

	// 当前页
	CCLabelTTF * pCurPage = dynamic_cast<CCLabelTTF *>(pBackground->getChildByTag(CUR_PAGE));
	if (NULL != pCurPage)
	{
		int nAllCount = (CS_Exploit==m_ShowContent) ? m_vExploitRanking.size() : m_vMatchRanking.size();
		int nShowCurPage = (CS_Exploit==m_ShowContent) ? m_uCurExploitPage : m_uCurMatchPage;
		int nAllPgae = nAllCount/c_ShowCount;
		if (0 < nAllCount)
			nShowCurPage++;
		if (0 < nAllCount%c_ShowCount)
			nAllPgae++;
		pCurPage->setString(CCString::createWithFormat("%d/%d", nShowCurPage, nAllPgae)->getCString());
	}
}

void SIX_PopWndRank::SetItemData(CCNode * pNode, int nIndex, int nCurPage, long long lUserID, const char *pcharNickName, int nScore, int nRewardGold)
{
	if (NULL != pNode)
	{
		pNode->setVisible(true);
		// 名次
		CCString *pRankPath = CCString::createWithFormat("Common/Rank/%s.png", m_llUserID==lUserID?"rankNumberMyself":"rankNumberOther");
		SIX_NumberBatchNode * pRank = dynamic_cast<SIX_NumberBatchNode *>(pNode->getChildren()->objectAtIndex(0));
		// 姓名
		CCLabelTTF *pNickName = dynamic_cast<CCLabelTTF *>(pNode->getChildren()->objectAtIndex(1));
		wstring wNickName = SIX_Utility::GetInstance()->AnsiToUnicode(pcharNickName);
		string sNickName = SIX_Utility::GetInstance()->UnicodeToUtf8(wNickName.c_str());
		// 功勋&比赛总积分
		SIX_NumberBatchNode * pScore = dynamic_cast<SIX_NumberBatchNode *>(pNode->getChildren()->objectAtIndex(2));
		// 最终排名奖励
		SIX_NumberBatchNode * pReward = dynamic_cast<SIX_NumberBatchNode *>(pNode->getChildren()->objectAtIndex(3));
		// 金币
		CCSprite *pGoldSign = dynamic_cast<CCSprite *>(pNode->getChildren()->objectAtIndex(4));

		if (m_llUserID==lUserID)
		{
			CCTexture2D *pRankTexture2D = CCTextureCache::sharedTextureCache()->addImage("Common/Rank/rankNumberMyself.png");
			pRank->setTexture(pRankTexture2D);
			CCTexture2D *pScoreTexture2D = CCTextureCache::sharedTextureCache()->addImage("Common/Rank/scoreGoldMyself.png");
			pScore->setTexture(pScoreTexture2D);
			CCTexture2D *pRewardTexture2D = CCTextureCache::sharedTextureCache()->addImage("Common/Rank/scoreGoldMyself.png");
			pReward->setTexture(pRewardTexture2D);
			CCRect rcMyselfGoldSign(pGoldSign->getTexture()->getContentSize().width/2,0,pGoldSign->getTexture()->getContentSize().width/2, \
				pGoldSign->getTexture()->getContentSize().height);
			pGoldSign->setTextureRect(rcMyselfGoldSign);
		}
		else
		{
			CCTexture2D *pRankTexture2D = CCTextureCache::sharedTextureCache()->addImage("Common/Rank/rankNumberOther.png");
			pRank->setTexture(pRankTexture2D);
			CCTexture2D *pScoreTexture2D = CCTextureCache::sharedTextureCache()->addImage("Common/Rank/scoreGoldOther.png");
			pScore->setTexture(pScoreTexture2D);
			CCTexture2D *pRewardTexture2D = CCTextureCache::sharedTextureCache()->addImage("Common/Rank/scoreGoldOther.png");
			pReward->setTexture(pRewardTexture2D);
			CCRect rcOtherGoldSign(0,0,pGoldSign->getTexture()->getContentSize().width/2,pGoldSign->getTexture()->getContentSize().height);
			pGoldSign->setTextureRect(rcOtherGoldSign);
		}

		pRank->setNumber(nIndex+c_ShowCount*nCurPage+1);
		pNickName->setString(sNickName.c_str());
		pNickName->setColor(m_llUserID==lUserID ? ccc3(72,228,4) : ccc3(255,255,255));
		pScore->setNumber(nScore);
		pReward->setNumber(nRewardGold);
	}
}

void SIX_PopWndRank::onEnterTransitionDidFinish()
{
	// 本窗口控件在此函数创建，在SetShowData设置数据
	// 每周功勋排行
	CCControlButton *pBtn1 = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Rank/rankBT1.png",2);
	if ( pBtn1 )
	{
		pBtn1->setTag(BTN_1);
		pBtn1->setZoomOnTouchDown(false);
		pBtn1->setDefaultTouchPriority(this->m_nPriority-1);
		pBtn1->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRank::doEvents), 32);
		pBtn1->setPosition(ccp(55, 470));
		pBackground->addChild(pBtn1);
	}
	// 每周比赛排行
	CCControlButton *pBtn2 = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Rank/rankBT2.png",2);
	if ( pBtn2 )
	{
		pBtn2->setTag(BTN_2);
		pBtn2->setZoomOnTouchDown(false);
		pBtn2->setDefaultTouchPriority(this->m_nPriority-1);
		pBtn2->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRank::doEvents), 32);
		pBtn2->setPosition(ccp(295, 470));
		pBackground->addChild(pBtn2);
	}
	// 退出
	CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Rank/ExitBTN.png",4);
	if ( pBtn )
	{
		pBtn->setTag(BTN_EXIT);
		pBtn->setZoomOnTouchDown(false);
		pBtn->setDefaultTouchPriority(this->m_nPriority-1);
		pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRank::doEvents),32);
		pBtn->setPosition(ccp(802, 487));
		pBackground->addChild(pBtn);
	}

	// 我的排行标识
	CCSprite *pMyRankSign = CCSprite::create("Common/Rank/MyRankSign.png");
	pMyRankSign->ignoreAnchorPointForPosition(true);
	pMyRankSign->setPosition(ccp(630,490));
	pBackground->addChild(pMyRankSign);
	// 我的排名
	CCLabelTTF *pMyRank = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(" ").c_str(),"微软雅黑",22, \
		CCSize(50,25),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	pMyRank->ignoreAnchorPointForPosition(true);
	pMyRank->setPosition(ccp(735,488));
	pMyRank->setString( "888" );
	pMyRank->setColor(ccc3(0,255,0));
	pMyRank->setTag(MY_RANKING);
	SIX_Utility::GetInstance()->FixedTexParameters(pMyRank->getTexture());
	pBackground->addChild( pMyRank );

	// 本周获得功勋 ， 本周获得比赛积分
	CCSprite *pGongXunHeadBG = CCSprite::create("Common/Rank/GongXunHeadBG.png");
	pGongXunHeadBG->setPosition(ccp(470,440));
	pBackground->addChild(pGongXunHeadBG);

	for (int i=0; i<7; i++)
	{
		// 行背景
		CCSprite *pItemBG = CCSprite::create("Common/Rank/ItemBG.png");
		pItemBG->ignoreAnchorPointForPosition(true);
		pItemBG->setPosition(ccp(50,365-i*50));
		pItemBG->setTag(ITEM_DATA+i);
		pBackground->addChild(pItemBG);
		// 名次
		CCString *pRankPath = CCString::createWithFormat("Common/Rank/%s.png", m_llUserID==m_MatchData.lUserID[i]?"rankNumberMyself":"rankNumberOther");
		SIX_NumberBatchNode * pRank = SIX_NumberBatchNode::Create(pRankPath ->getCString());
		pRank->setCellNum(10);
		pRank->setPadding(-28);
		pRank->setBitCount(3);
		pRank->setCellAlignStyle(ALIGN_RIGHT);
		pRank->setNumber(i);
		pRank->setPosition(ccp(35,-2));
		pRank->setObjName("rank");
		pItemBG->addChild(pRank);
		// 昵称
		CCLabelTTF *pNickName = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(" ").c_str(),"微软雅黑",22, \
			CCSize(160,30),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		pNickName->ignoreAnchorPointForPosition(true);
		pNickName->setPosition(ccp(113,8));
		pNickName->setObjName("NickName");
		char *pNameData = 0 >= strlen(m_MatchData.szName[i]) ? m_MatchData.szNickname[i] : m_MatchData.szName[i];
		pNickName->setString( pNameData );
		SIX_Utility::GetInstance()->FixedTexParameters(pNickName->getTexture());
		pItemBG->addChild( pNickName );
		// 功勋&比赛总积分
		CCString *pScorePath = CCString::createWithFormat("Common/Rank/%s.png", m_llUserID==m_MatchData.lUserID[i]?"scoreGoldMyself":"scoreGoldOther");
		SIX_NumberBatchNode * pScore = SIX_NumberBatchNode::Create(pScorePath ->getCString());
		pScore->setCellNum(10);
		pScore->setPadding(-10);
		pScore->setBitCount(8);
		pScore->setCellAlignStyle(ALIGN_LEFT);
		pScore->setNumber(m_MatchData.lGameCoin[i]);
		pScore->setPosition(ccp(365,13));
		pScore->setObjName("Score");
		pItemBG->addChild(pScore);
		// 最终排名奖励
		SIX_NumberBatchNode * pReward = SIX_NumberBatchNode::Create(pScorePath ->getCString());
		pReward->setCellNum(10);
		pReward->setPadding(-10);
		pReward->setBitCount(8);
		pReward->setCellAlignStyle(ALIGN_RIGHT);
		pReward->setNumber(m_MatchData.iRewardGold[i]);
		pReward->setPosition(ccp(610,10));
		pReward->setObjName("Reward");
		pItemBG->addChild(pReward);
		// 金币标识
		CCSprite *pGoldSign = CCSprite::create("Common/Rank/GoldSign.png");
		CCRect rcOtherGoldSign(0,0,pGoldSign->getContentSize().width/2,pGoldSign->getContentSize().height);
		pGoldSign->setTextureRect(rcOtherGoldSign);
		pGoldSign->ignoreAnchorPointForPosition(true);
		pGoldSign->setPosition(ccp(720,7));
		pGoldSign->setObjName("GoldSign");
		pItemBG->addChild(pGoldSign);
	}

	// 上一页
	CCControlButton *pLastPage = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Rank/LastPage.png",2);
	if ( pBtn2 )
	{
		pLastPage->setTag(LAST_PAGE);
		pLastPage->setZoomOnTouchDown(false);
		pLastPage->setDefaultTouchPriority(this->m_nPriority-1);
		pLastPage->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRank::doEvents), 32);
		pLastPage->setPosition(ccp(193, 23));
		pBackground->addChild(pLastPage);
	}
	// 下一页
	CCControlButton *pNextPage = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Rank/NextPage.png",2);
	if ( pBtn2 )
	{
		pNextPage->setTag(NEXT_PAGE);
		pNextPage->setZoomOnTouchDown(false);
		pNextPage->setDefaultTouchPriority(this->m_nPriority-1);
		pNextPage->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRank::doEvents), 32);
		pNextPage->setPosition(ccp(325, 23));
		pBackground->addChild(pNextPage);
	}
	// 显示页
	CCLabelTTF *pNickName = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(" ").c_str(),"微软雅黑",20, \
		CCSize(80,25),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	pNickName->ignoreAnchorPointForPosition(true);
	pNickName->setPosition(ccp(228,28));
	pNickName->setString( "1/1" );
	pNickName->setColor(ccc3(0,0,0));
	pNickName->setTag(CUR_PAGE);
	SIX_Utility::GetInstance()->FixedTexParameters(pNickName->getTexture());
	pBackground->addChild( pNickName );

	// 领取排行奖励
	CCControlButton *pReceiveReward = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Rank/ReceiveReward.png",2);
	if ( pBtn2 )
	{
		pReceiveReward->setTag(RECEIVE_REWARD);
		pReceiveReward->setZoomOnTouchDown(false);
		pReceiveReward->setDefaultTouchPriority(this->m_nPriority-1);
		pReceiveReward->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRank::doEvents), 32);
		pReceiveReward->setPosition(ccp(380, 20));
		pBackground->addChild(pReceiveReward);
	}
	// 查看我的排行
	CCControlButton *pViewMyRank = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/Rank/viewMyRank.png",2);
	if ( pBtn2 )
	{
		pViewMyRank->setTag(VIEW_MY_RANK);
		pViewMyRank->setZoomOnTouchDown(false);
		pViewMyRank->setDefaultTouchPriority(this->m_nPriority-1);
		pViewMyRank->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRank::doEvents), 32);
		pViewMyRank->setPosition(ccp(543, 20));
		pBackground->addChild(pViewMyRank);
	}
}

void SIX_PopWndRank::doEvents(CCObject* pSender, CCControlEvent event)
{
	if (!pSender)
		return;

	CCControl *pControl = dynamic_cast<CCControl*>(pSender);
	if (!pControl)
		return;

	CCString *name = CCString::create(pControl->getObjName());
	int tag = pControl->getTag();
	SIXLog("SIX_PopWndRank.doEvents.pSender[0x%08X][%s].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,name->getCString(),event,tag);

	switch (tag)
	{
	case BTN_1:	// 每周功勋排行按钮
		{
			if (CS_Exploit == m_ShowContent)
				return;
			m_ShowContent = CS_Exploit;
			SetShowData();
			break;
		}
	case BTN_2:	// 每周比赛排行按钮
		{
			if (CS_Match == m_ShowContent)
				return;
			m_ShowContent = CS_Match;
			SetShowData();

			if (!m_bGetMatchRanking)
			{
				SIX_ClientLogin::GetInstance()->SetConnectionType(CONNECTION_MATCH);
				SIX_ClientLogin::GetInstance()->Connect();
				return;
			}
			break;
		}
	case BTN_EXIT:	// 退出按钮
		{
			Show(false);
			break;
		}
	case LAST_PAGE:	// 上一页按钮
		{
			SetPage(-1);
			SetShowData();
			break;
		}
	case NEXT_PAGE:	// 下一页按钮
		{
			SetPage(1);
			SetShowData();
			break;
		}
	case RECEIVE_REWARD:	// 领取排行奖励按钮
		{
			if (!m_bGetMyExploitRanking  &&  CS_Exploit==m_ShowContent)
			{
				SIX_ClientLogin::GetInstance()->SetConnectionType(CONNECTION_MY_EXPLOIT);
				SIX_ClientLogin::GetInstance()->Connect();
				return;
			}
			else if (!m_bGetMyMatchRanking  &&  CS_Match==m_ShowContent)
			{
				SIX_ClientLogin::GetInstance()->SetConnectionType(CONNECTION_MY_MATCH);
				SIX_ClientLogin::GetInstance()->Connect();
				return;
			}
			break;
		}
	case VIEW_MY_RANK:	// 查看我的排行按钮
		{
			break;
		}
	default:
		{
			CCAssert(1, "未处理的按钮响应事件!" );
			break;
		}
	}
}
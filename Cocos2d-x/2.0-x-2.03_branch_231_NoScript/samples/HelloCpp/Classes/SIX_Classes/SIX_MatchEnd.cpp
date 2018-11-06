#include "SIX_MatchEnd.h"
#include <SIX_NumberBatchNode.h>

const int g_Tag = 100;

SIX_MatchEnd::~SIX_MatchEnd()
{
}

SIX_MatchEnd *SIX_MatchEnd::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
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

	SIX_MatchEnd *pMatchEnd = new SIX_MatchEnd();
	if (pMatchEnd && pMatchEnd->init())
	{
		pMatchEnd->initWithColor(color,width,height);
		pMatchEnd->setPosition(x,y);
		pMatchEnd->setRedrawBorder(bRedrawBorder);
		pMatchEnd->setTouchEnabled(true);
		pMatchEnd->m_ForbiddenTouch = true;
		pMatchEnd->m_bCloseThenCleanup = bCloseThenCleanup;
		pMatchEnd->setObjName("SIX_MatchEnd");
	}
	return pMatchEnd;
}

void SIX_MatchEnd::SetMatchData(CMD_MatchEnd *pData)
{
	memcpy(&m_MatchData, pData, sizeof(m_MatchData));
}

void SIX_MatchEnd::SetMyselfID(long long nUserID)
{
	m_llUserID = nUserID;
}

bool SIX_MatchEnd::init()
{
	if (!SIX_PopWnd::init())
		return false;

	m_llUserID = 0l;
	return true;
}

void SIX_MatchEnd::onEnterTransitionDidFinish()
{
	for (int i=0; i<4; i++)
	{
		// 名次
		CCSprite * pRank = NULL;
		CCRepeatForever * pRepeatForever = NULL;
		if (0==i)
		{
			CCString *pRankPath = NULL;
			CCAnimation* pAnimation = NULL;
			if ( m_llUserID == m_MatchData.lUserID[i] )
			{
				pAnimation = CCAnimation::create();
				for( int i=1;i<10;i++)
				{
					char szName[100] = {0};
					sprintf(szName, "Common/MatchEnd/1_%05d.png", i);
					pAnimation->addSpriteFrameWithFileName(szName);
				}
				pAnimation->setDelayPerUnit(0.15);
				CCAnimate * pAnimate = CCAnimate::create( pAnimation );
				pRepeatForever = CCRepeatForever::create(pAnimate);
				pRankPath = CCString::create("Common/MatchEnd/1_00000.png");
			}
			else
			{
				pRankPath = CCString::create("Common/MatchEnd/1.png");
			}

			pRank = CCSprite::create(pRankPath->getCString());

			CCSprite *pWin = CCSprite::create(m_llUserID==m_MatchData.lUserID[i] ? "Common/MatchEnd/win.png" : "Common/MatchEnd/lose.png");
			pWin->setPosition(ccp(291,366));
			pBackground->addChild(pWin);
		}
		else if (m_llUserID == m_MatchData.lUserID[i])
		{
			CCString *pRankPath = CCString::createWithFormat("Common/MatchEnd/%d.png", i+1);
			pRank = CCSprite::create(pRankPath->getCString());
			pRank->setTextureRect(CCRect(pRank->getContentSize().width/2, 0.0, pRank->getContentSize().width/2, pRank->getContentSize().height));
		}
		else
		{
			CCString *pRankPath = CCString::createWithFormat("Common/MatchEnd/%d.png",i+1);
			pRank = CCSprite::create(pRankPath->getCString());
			pRank->setTextureRect(CCRect(0.0, 0.0, pRank->getContentSize().width/2, pRank->getContentSize().height));
		}
		pRank->setTag(g_Tag+i);
		pRank->setPosition(ccp(70,260 - i*50));
		pBackground->addChild( pRank );
		pRank->setVisible( false );

		if (NULL != pRepeatForever)
			pRank->runAction( pRepeatForever );

		float fDelayShow = 1.0; // 延时显示，再放大
		if (m_llUserID == m_MatchData.lUserID[i])
		{
			pRank->setScale(5.0);			
			CCDelayTime * pDelayTime = CCDelayTime::create(fDelayShow);
			CCShow * pShow = CCShow::create();
			CCScaleTo * pScaleTo = CCScaleTo::create(0.2, 1.0);
			CCFiniteTimeAction * pSequence = CCSequence::create(pDelayTime, pShow, pScaleTo, NULL);
			pRank->runAction(pSequence);
		}
		else
		{
			CCDelayTime * pDelayTime = CCDelayTime::create(fDelayShow+0.5*i);
			CCShow * pShow = CCShow::create();
			CCFiniteTimeAction * pSequence = CCSequence::create(pDelayTime, pShow, NULL);
			pRank->runAction(pSequence);
		}

		// 标识自己
		CCString *pPath = CCString::create(m_llUserID == m_MatchData.lUserID[i] ? "Common/MatchEnd/matchEndMyselfBG.png" : "Common/MatchEnd/OthersBG.png");
		CCSprite *pItemBG = CCSprite::create( pPath->getCString() );
		pItemBG->ignoreAnchorPointForPosition(true);
		pItemBG->setPosition(ccp(100,240 - i*50));
		pBackground->addChild( pItemBG );

		// 昵称
		CCLabelTTF *pNickName = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(" ").c_str(),"微软雅黑",22, \
			CCSize(160,50),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		pNickName->ignoreAnchorPointForPosition(true);
		pNickName->setPosition(ccp(-7,3));
		char *pNameData = 0 >= strlen(m_MatchData.szName[i]) ? m_MatchData.szNickname[i] : m_MatchData.szName[i];
		pNickName->setString( pNameData );
		SIX_Utility::GetInstance()->FixedTexParameters(pNickName->getTexture());
		pItemBG->addChild( pNickName );

		// 积分
		SIX_NumberBatchNode * pScore = SIX_NumberBatchNode::Create("Common/MatchEnd/number.png");
		pScore->setCellNum(10);
		pScore->setPadding(-5);
		pScore->setBitCount(6);
		pScore->setCellAlignStyle(ALIGN_LEFT);
		pScore->setNumber(m_MatchData.lGameCoin[i]);
		pScore->setPosition(ccp(180,13));
		pItemBG->addChild(pScore);

		// 奖励
		SIX_NumberBatchNode * pReward = SIX_NumberBatchNode::Create("Common/MatchEnd/number.png");
		pReward->setCellNum(10);
		pReward->setPadding(-5);
		pReward->setBitCount(6);
		pReward->setCellAlignStyle(ALIGN_RIGHT);
		pReward->setNumber(m_MatchData.iRewardGold[i]);
		pReward->setPosition(ccp(290,13));		
		pItemBG->addChild(pReward);
	}

	// 退出
	CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Common/MatchEnd/matchEndExitBTN.png",3);
	if ( pBtn )
	{
		pBtn->setTag(1);
		pBtn->setZoomOnTouchDown(false);
		pBtn->setDefaultTouchPriority(this->m_nPriority-1);
		pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_MatchEnd::doEvents),32);
		pBtn->setPosition(ccp(235, 19));
		pBackground->addChild(pBtn);
	}
}

void SIX_MatchEnd::doEvents(CCObject* pSender, CCControlEvent event)
{
	if (!pSender)
		return;

	CCControl *pControl = dynamic_cast<CCControl*>(pSender);
	if (!pControl)
		return;

	CCString *name = CCString::create(pControl->getObjName());
	int tag = pControl->getTag();
	SIXLog("SIX_MatchEnd.doEvents.pSender[0x%08X][%s].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,name->getCString(),event,tag);

	if (1 == tag)
	{
		SIX_Proxy::GetInstance()->SetChangeScene(true);
	}
}
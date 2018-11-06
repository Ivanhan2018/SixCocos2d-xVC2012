#include "SIX_PopWndAward.h"

SIX_PopWndAward::~SIX_PopWndAward(void)
{
}

SIX_PopWndAward *SIX_PopWndAward::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndAward *pPopWnd = new SIX_PopWndAward();
	SIX_PopWndHaveListView::Create(pPopWnd, ccp(x,y), color, CCSize(width,height), bRedrawBorder, bCloseThenCleanup);
	
	pPopWnd->SetListViewCellSize(CCSize(width-c_smallWndBorderX*2-10, 73));
	pPopWnd->SetListViewRect(CCRect(c_smallWndBorderX+7, c_smallWndBorderY+10, width-c_smallWndBorderX*2-10, height-c_titleHeight-c_smallWndBorderY));
	return pPopWnd;
}

bool SIX_PopWndAward::init()
{
	if (!SIX_PopWndHaveListView::init())
		return false;

	SetTitlePath("award_titleBG.png");
	return true;
}

void SIX_PopWndAward::setCellContent()
{
	if (0 == GetListView())
		return;

	GetListView()->RemoveCellAll();
	map<int, CMD_SC_Award>::iterator mAward = m_mapAward.begin();
	for (int nIndex = 0; mAward != m_mapAward.end(); ++mAward, ++nIndex)
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		GetListView()->AppendCell(pCell);
		CCSize cellSize = GetListView()->getContentSize();

		// Ïî±³¾°
		CCSprite *pItemBG = CCSprite::create("ItemBG.jpg");
		if (0 != pItemBG)
		{
			pItemBG->ignoreAnchorPointForPosition(true);
			pItemBG->setPosition(ccp(0,0));
			pCell->addChild(pItemBG);
		}
		// ¿¨ÀàÐÍ
		if (0 < strlen(mAward->second.szFileName))
		{
			CCString *pStrCardTypePath = CCString::createWithFormat("award_%s",mAward->second.szFileName);
			CCSprite *pCardType = CCSprite::create(pStrCardTypePath->getCString());
			if (0 != pCardType  &&  0!=pItemBG)
			{
				pCardType->ignoreAnchorPointForPosition(true);
				pCardType->setPosition(ccp(5,(pItemBG->getContentSize().height-pCardType->getContentSize().height)/2));
				pCell->addChild(pCardType);
			}
		}
		else
		{
			// ¿¨ÃèÊö
			CCLabelTTF *pDescription = CCLabelTTF::create();
			pDescription->setString(SIX_Utility::GetInstance()->G2U(mAward->second.szDescription).c_str());
			pDescription->setColor(ccc3(138,202,18));
			pDescription->setFontSize(18.0f);
			pDescription->setFontName("Î¢ÈíÑÅºÚ");
			pDescription->setOpacity(255);
			pDescription->ignoreAnchorPointForPosition(true);
			pDescription->setPosition(ccp(10,(pItemBG->getContentSize().height-pDescription->getContentSize().height)/2));
			SIX_Utility::GetInstance()->FixedTexParameters(pDescription->getTexture(),true);
			pCell->addChild(pDescription);
		}
		// ½±È¯
		CCLabelTTF *pTextReward = CCLabelTTF::create();
		char cReward[128]="";
		sprintf(cReward, "½±È¯£º%d", mAward->second.nReward);
		pTextReward->setString(SIX_Utility::GetInstance()->G2U(cReward).c_str());
		pTextReward->setColor(ccc3(253,255,8));
		pTextReward->setFontSize(18.0f);
		pTextReward->setFontName("Î¢ÈíÑÅºÚ");
		pTextReward->setOpacity(255);
		pTextReward->ignoreAnchorPointForPosition(true);
		pTextReward->setPosition(ccp(pItemBG->getContentSize().width*0.272,(pItemBG->getContentSize().height-pTextReward->getContentSize().height)/2));
		SIX_Utility::GetInstance()->FixedTexParameters(pTextReward->getTexture(),true);
		pCell->addChild(pTextReward);
		// ÊýÁ¿
		CCLabelTTF *pTxtCount = CCLabelTTF::create();
		CCString *pStrSchedule = CCString::createWithFormat("ÊýÁ¿£º%d", mAward->second.nCount);
		pTxtCount->setString(SIX_Utility::GetInstance()->G2U(pStrSchedule->getCString()).c_str());
		pTxtCount->setColor(ccc3(255,255,255));
		pTxtCount->setFontSize(20.0f);
		pTxtCount->setFontName("Î¢ÈíÑÅºÚ");
		pTxtCount->ignoreAnchorPointForPosition(true);
		pTxtCount->setPosition(ccp(pItemBG->getContentSize().width*0.545,(pItemBG->getContentSize().height-pTxtCount->getContentSize().height)/2));
		SIX_Utility::GetInstance()->FixedTexParameters(pTxtCount->getTexture(),true);
		pCell->addChild(pTxtCount);
		// Áì½±°´Å¥
		CCControlButton * pRewardButton = SIX_Utility::GetInstance()->CreateButtonWithFileCell("ReceiveRewardBT.png", 2);
		if (0 == pRewardButton)
			return;
		pRewardButton->setTag(nIndex+1);
		pRewardButton->setObjName("Setting");
		pRewardButton->setZoomOnTouchDown(false);
		pRewardButton->setDefaultTouchPriority(m_nPriority-1);
		pRewardButton->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndAward::doEvents),32);
		pRewardButton->setPosition(ccp(cellSize.width-pRewardButton->getContentSize().width-30,(pItemBG->getContentSize().height-pRewardButton->getContentSize().height)/2-3));
		pCell->addChild(pRewardButton);
	}

	GetListView()->refresh();
}

void SIX_PopWndAward::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			case 1:
				{
					break;
				}
			default:
				SIXLog("SIX_SceneHall::doEvents Î´Öª°´Å¥ÊÂ¼þ,  tag=%d", tag);
				break;
			}
		}
	}
	return;
}

void SIX_PopWndAward::SetData(CMD_SC_Award *& pAward)
{
	CMD_SC_Award award;
	memcpy(&award, pAward, sizeof(award));
	m_mapAward.insert(make_pair(award.nAwardID, award));
}
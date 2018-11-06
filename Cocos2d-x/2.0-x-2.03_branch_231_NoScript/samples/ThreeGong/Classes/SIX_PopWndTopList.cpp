#include "SIX_PopWndTopList.h"
#include "SIX_PlayerMgr.h"

enum NodeTag
{	
	ITEM_TEXT = 1,								// 项文字
	TOP_LIST_TAG,								// 排行榜列表
};

SIX_PopWndTopList::~SIX_PopWndTopList(void)
{
}

SIX_PopWndTopList *SIX_PopWndTopList::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndTopList *pPopWnd = new SIX_PopWndTopList();
	SIX_PopWndHaveListView::Create(pPopWnd, ccp(x,y), color, CCSize(width,height), bRedrawBorder, bCloseThenCleanup);
	
	pPopWnd->SetListViewCellSize(CCSize(200,61));
	pPopWnd->SetListViewRect(CCRect(c_smallWndBorderX+2,c_smallWndBorderY,200,height-c_titleHeight-c_smallWndBorderY-26));
	return pPopWnd;
}

bool SIX_PopWndTopList::init()
{
	if (!SIX_PopWndHaveListView::init())
		return false;
	
	SetTitlePath("top_titleBG.png");
	return true;
}

void SIX_PopWndTopList::onEnterTransitionDidFinish()
{
	SIX_PopWndHaveListView::onEnterTransitionDidFinish();
	
	CCScale9Sprite *pSmallWnd = dynamic_cast<CCScale9Sprite *>(getChildByTag(SMALL_BG));
	if (0 != GetListView()  &&  0 != pSmallWnd)
	{
		reorderChild(pSmallWnd, getZOrder()+100);
		reorderChild(GetListView(), getZOrder()+200);

		int nX = GetListView()->getContentSize().width-c_smallWndBorderX*2-3;
		pSmallWnd->setPosition(ccp(nX+c_smallWndBorderX, c_smallWndBorderY+30));
		pSmallWnd->setPreferredSize(CCSize(getContentSize().width-nX-32, getContentSize().height-c_titleHeight-c_smallWndBorderY-20));
	}

	InitTopList();

	if (0 != GetListView())
	{
		GetListView()->RemoveCellAll();
		char cType[4][32]={"筹码总榜","筹码周榜","经验总榜","经验周榜"};

		for (int nIndex = 0; nIndex <4; ++nIndex)
		{
			SIX_ListViewCell *pCell = new SIX_ListViewCell();
			GetListView()->AppendCell(pCell);
			// 项背景
			CCSprite *pItemBG = CCSprite::create("ItemBG.png");
			if (0 != pItemBG && 0!=pItemBG)
			{
				pItemBG->ignoreAnchorPointForPosition(true);
				pCell->addChild(pItemBG);
			}
			// 选择标识
			CCSprite *pSelectItemMark = CCSprite::create("selectItemBG.png");
			if (0 != pSelectItemMark)
			{
				pSelectItemMark->setObjName("SelectItemBG");
				pSelectItemMark->setAnchorPoint(ccp(0,0));
				pSelectItemMark->setVisible(0==nIndex ? true : false);
				pCell->addChild(pSelectItemMark);
			}
			// 名字
			CCLabelTTF *pDescription = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(cType[nIndex]).c_str(),"微软雅黑",20, \
				pSelectItemMark->getContentSize(),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
			if (0 != pDescription)
			{
				pDescription->setColor(ccc3(255,255,255));
				pDescription->setOpacity(255);
				pDescription->setTag(ITEM_TEXT+nIndex*10);
				pDescription->ignoreAnchorPointForPosition(true);
				SIX_Utility::GetInstance()->FixedTexParameters(pDescription->getTexture(),true);
				pCell->addChild(pDescription);
			}
		}
		GetListView()->refresh();
	}

	// 设置自己的排名
	if (0 != pSmallWnd)
	{
		// 项背景
		CCSprite *pMyItemBG = CCSprite::create("MyTopListBG.png");
		if (0 != pMyItemBG)
		{
			pMyItemBG->ignoreAnchorPointForPosition(true);
			pMyItemBG->setPosition(ccp(GetListView()->getPositionX()-9, GetListView()->getPositionY()+GetListView()->getContentSize().height-pMyItemBG->getContentSize().height-10));
			pSmallWnd->addChild(pMyItemBG, 300);
			InitItem(pMyItemBG, m_MyTopList.nMyRank, SIX_PlayerMgr::GetInstance()->getMyName(), SIX_PlayerMgr::GetInstance()->getMyChip(), true, 4.0f, 10.0f);
		}

		// 提示
		CCLabelTTF *pTxtPrompt = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("注：此排行榜每24小时更新一次").c_str(),"微软雅黑",14, \
			CCSize(300,30),kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		if (0 != pTxtPrompt)
		{
			pTxtPrompt->setColor(ccc3(205,159,97));
			pTxtPrompt->ignoreAnchorPointForPosition(true);
			pTxtPrompt->setPosition(ccp(pSmallWnd->getPositionX()+5, 15.0f));
			SIX_Utility::GetInstance()->FixedTexParameters(pTxtPrompt->getTexture(),true);
			addChild(pTxtPrompt, 300);
		}
	}
}

void SIX_PopWndTopList::setCellContent()
{
	SIX_ListView *pTopListView = dynamic_cast<SIX_ListView *>(getChildByTag(TOP_LIST_TAG));
	if (0 == pTopListView)
		return;
	pTopListView->RemoveCellAll();

	map<int, CMD_SC_RankingList>::iterator mTopList = m_mapTopList.begin();
	for (int nIndex = 1; mTopList != m_mapTopList.end(); ++mTopList, ++nIndex)
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		pTopListView->AppendCell(pCell);
		InitItem(pCell, nIndex, mTopList->second.szNickName, mTopList->second.nValue, false, 0.0f, 0.0f);
	}
	pTopListView->refresh();
}

CCSize SIX_PopWndTopList::cellSizeForTable(CCTableView *table)
{
	return CCSize(0,0); 
}

CCTableViewCell* SIX_PopWndTopList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	return 0;
}

unsigned int SIX_PopWndTopList::numberOfCellsInTableView(CCTableView *table)
{
	return 0;
}

void SIX_PopWndTopList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	for (unsigned int i=0; i<GetListView()->GetCellCount(); ++i)
	{
		SIX_ListViewCell * pListVewCell = GetListView()->GetCell(i);
		CCSprite *pSelectItemMark = dynamic_cast<CCSprite *>(pListVewCell->getChildren()->objectAtIndex(1));
		if (0 != pSelectItemMark)
		{
			pSelectItemMark->setVisible(false);
		}
	}

	CCSprite *pSelectItemMark = dynamic_cast<CCSprite *>(cell->getChildren()->objectAtIndex(1));
	if (0 != pSelectItemMark)
	{
		pSelectItemMark->setVisible(true);
	}
}

void SIX_PopWndTopList::scrollViewDidScroll(CCScrollView* view)
{}

void SIX_PopWndTopList::scrollViewDidZoom(CCScrollView* view)
{}

void SIX_PopWndTopList::InitItem(CCNode *pCell, const int &nIndex, const char *pcNickName, long long llValue, bool bSetMyData, float fOffsetX, float fOffsetY)
{
	// 名次
	CCString *pStrPath = CCString::createWithFormat("top_%d.png", 3>=nIndex ? nIndex : 0);
	CCSprite *pRanking = CCSprite::create(pStrPath->getCString());
	if (0 != pRanking  &&  !bSetMyData)
	{
		pRanking->setAnchorPoint(ccp(0,0));
		pCell->addChild(pRanking);
	}
	
	if ((0 >= nIndex  ||  100 < nIndex)  &&  bSetMyData)
	{
		CCSprite *pNoTopList = CCSprite::create("NoTopList.png");
		if (0 != pNoTopList)
		{
			pNoTopList->ignoreAnchorPointForPosition(true);
			pNoTopList->setPosition(ccp(10.0f, 26.0f));
			pCell->addChild(pNoTopList);
		}
	}
	else if (3 < nIndex && pRanking)
	{
		CCString *pStrRanking = CCString::createWithFormat("%d", nIndex);
		CCLabelTTF *pOtherRanking = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(pStrRanking->getCString()).c_str(),"微软雅黑",36, \
			pRanking->getContentSize(),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		if (0 != pOtherRanking)
		{
			pOtherRanking->setColor(bSetMyData ? ccc3(0,0,0) : ccc3(255,255,255));
			pOtherRanking->ignoreAnchorPointForPosition(true);
			SIX_Utility::GetInstance()->FixedTexParameters(pOtherRanking->getTexture(),true);
			pCell->addChild(pOtherRanking);
		}
	}
	// 项背景
	CCSprite *pItemBG = CCSprite::create("top_ItemBG.png");
	if (0 != pItemBG  &&  0!=pRanking  &&  !bSetMyData)
	{
		pItemBG->setAnchorPoint(ccp(0,0));
		pItemBG->setPositionX(pRanking->getPositionX()+pRanking->getContentSize().width);
		pCell->addChild(pItemBG);
	}
	// 头像
	CCSprite *pTmpPicture = CCSprite::create("face_small.jpg");
	CCSprite *pPicture = CCSprite::create("face_small.jpg", CCRect(0,0,pItemBG->getContentSize().height,pItemBG->getContentSize().height));
	if (0 != pPicture)
	{
		pPicture->setAnchorPoint(ccp(0,0));
		pPicture->setPosition(ccp(75.0f+fOffsetX, (pItemBG->getContentSize().height-pPicture->getContentSize().height)/2+fOffsetY));
		pCell->addChild(pPicture);
	}
	// 昵称
	CCLabelTTF *pNickName = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(pcNickName).c_str(),"微软雅黑",18, \
		pItemBG->getContentSize(),kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
	if (0 != pNickName)
	{
		pNickName->setColor(bSetMyData ? ccc3(0,0,0) : ccc3(255,255,255));
		pNickName->setOpacity(255);
		pNickName->ignoreAnchorPointForPosition(true);
		pNickName->setPosition(ccp(140.0f+fOffsetX, (pItemBG->getContentSize().height-pNickName->getContentSize().height)/2+fOffsetY));
		SIX_Utility::GetInstance()->FixedTexParameters(pNickName->getTexture(),true);
		pCell->addChild(pNickName);
	}
	// 筹码
	CCString *pStrMoney = CCString::createWithFormat("筹码：%lld",llValue);
	CCLabelTTF *pMoney = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(pStrMoney->getCString()).c_str(),"微软雅黑",18, \
		pItemBG->getContentSize(),kCCTextAlignmentRight, kCCVerticalTextAlignmentCenter);
	if (0 != pMoney)
	{
		pMoney->setColor(bSetMyData ? ccc3(0,0,0) : ccc3(255,255,255));
		pMoney->setOpacity(255);
		pMoney->ignoreAnchorPointForPosition(true);
		pMoney->setPosition(ccp(fOffsetX+50, (pItemBG->getContentSize().height-pMoney->getContentSize().height)/2+fOffsetY));
		SIX_Utility::GetInstance()->FixedTexParameters(pMoney->getTexture(),true);
		pCell->addChild(pMoney);
	}
}

void SIX_PopWndTopList::SetData(CMD_SC_RankingList *& pTopList)
{
	CMD_SC_RankingList topList;
	memcpy(&topList, pTopList, sizeof(topList));
	m_mapTopList.insert(make_pair(topList.nRank, topList));
}

void SIX_PopWndTopList::SetMyData(CMD_CSG_Ranking *& pMyTopList)
{
	memcpy(&m_MyTopList, pMyTopList, sizeof(CMD_CSG_Ranking));
}

void SIX_PopWndTopList::doEvents(CCObject* pSender, CCControlEvent controlEvent)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (controlEvent)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			default:
				SIXLog("SIX_SceneHall::doEvents 未知按钮事件,  tag=%d", tag);
				break;
			}
		}
	}
	return;
}

void SIX_PopWndTopList::InitTopList()
{
	CCScale9Sprite *pSmallWnd = dynamic_cast<CCScale9Sprite *>(getChildByTag(SMALL_BG));
	if (0 == pSmallWnd)
		return;

	CCRect listViewRect = CCRect(pSmallWnd->getPosition().x+12,pSmallWnd->getPosition().y+10,pSmallWnd->getContentSize().width,pSmallWnd->getContentSize().height-70);
	CCSize listViewCell = CCSize(pSmallWnd->getContentSize().width,51);

	SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
	pContainer->setContentSize(CCSize(listViewRect.size.width, listViewRect.size.height));
	pContainer->setPosition(ccp(listViewRect.getMinX(), listViewRect.getMinY()));

	//SIX_ScrollBar *pScrollBar = SIX_ScrollBar::create(
	//	"scrollbar.png",CCRect(0,51,17,17),CCSize(listViewRect.size.height-17*2,17),
	//	"scrollbar.png",CCRect(0,51,17,17),
	//	"scrollbar.png",CCRect(0,34,17,17),
	//	"scrollbar.png",CCRect(0,34,17,17),
	//	"scrollbar.png",CCRect(0,0,17,17),
	//	"scrollbar.png",CCRect(0,17,17,17),
	//	CCSize(17,17),
	//	false
	//	);
	//pScrollBar->setAnchorPoint(ccp(0,0));
	//pScrollBar->setMinimumValue(0);
	//pScrollBar->setMaximumValue(100);
	//pScrollBar->setValue(0);
	//pScrollBar->setDefaultTouchPriority(m_nPriority-1);

	SIX_ListView *pListView = SIX_ListView::create(ccc4(0,0,0,0),
		ccp(listViewRect.getMinX(),listViewRect.getMinY()),
		CCSize(listViewRect.size.width, listViewRect.size.height),
		CCSize(listViewCell.width, listViewCell.height),
		kCCScrollViewDirectionVertical,
		pContainer,
		0//pScrollBar
		);

	pListView->setObjName("PopWndList_TopList");
	pListView->setTag(TOP_LIST_TAG);

	// -- 设置响应touch事件(create的时候已经设置好了，这里只是演示而已)
	pListView->setTouchEnabled(true);	
	// -- 设置裁剪超出区域(create的时候默认设置为true，这里只是演示而已~)
	pListView->getTableView()->setClippingToBounds(true);
	// -- 设置横竖方向(create的时候已经设置好了，这里只是演示而已~)
	pListView->getTableView()->setDirection(kCCScrollViewDirectionVertical);
	// -- 设置自上而下滚动(create的时候已经设置好了，这里只是演示而已~)
	pListView->getTableView()->setVerticalFillOrder(kCCTableViewFillTopDown);
	// -- 设置滑动效果
	pListView->getTableView()->setBounceable(true);
	addChild(pListView, pSmallWnd->getZOrder()-1);
}
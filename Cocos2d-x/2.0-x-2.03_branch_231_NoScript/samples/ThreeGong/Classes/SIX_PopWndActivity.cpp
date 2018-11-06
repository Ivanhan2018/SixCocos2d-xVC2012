#include "SIX_PopWndActivity.h"

enum NodeTag
{
	SELECT_ITEM_TAG = 2,					// 选择项背景
	ITEM_TEXT = 3,									// 项文字
};

SIX_PopWndActivity::~SIX_PopWndActivity(void)
{
}

SIX_PopWndActivity *SIX_PopWndActivity::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndActivity *pPopWnd = new SIX_PopWndActivity();
	SIX_PopWndHaveListView::Create(pPopWnd, ccp(x,y), color, CCSize(width,height), bRedrawBorder, bCloseThenCleanup);
	pPopWnd->SetListViewCellSize(CCSize(200,61));
	pPopWnd->SetListViewRect(CCRect(c_smallWndBorderX+4,c_smallWndBorderY,200,height-c_titleHeight-c_smallWndBorderY));
	return pPopWnd;
}

bool SIX_PopWndActivity::init()
{
	if (!SIX_PopWndHaveListView::init())
		return false;
	
	SetTitlePath("activity_titleBG.png");
	return true;
}

void SIX_PopWndActivity::setCellContent()
{
	if (0 != GetListView())
	{
		GetListView()->RemoveCellAll();
		map<int, CMD_SC_ActivityList>::iterator mActivityList = m_mapActivityList.begin();
		for (int nIndex = 0; mActivityList != m_mapActivityList.end(); ++mActivityList, ++nIndex)
		{
			SIX_ListViewCell *pCell = new SIX_ListViewCell();
			GetListView()->AppendCell(pCell);
			CCSize cellSize = GetListView()->getContentSize();
			// 项背景
			CCSprite *pItemBG = CCSprite::create("ItemBG.png");
			if (0 != pItemBG)
			{
				pItemBG->ignoreAnchorPointForPosition(true);
				pItemBG->setPosition(ccp(0,(GetListView()->cellSizeForTable(0).height-pItemBG->getContentSize().height)/2));
				pCell->addChild(pItemBG);
			}
			// 选择标识
			CCSprite *pSelectItemMark = CCSprite::create("selectItemBG.png");
			if (0 != pSelectItemMark)
			{
				pSelectItemMark->setObjName("SelectItemBG");
				pSelectItemMark->setTag(SELECT_ITEM_TAG+nIndex*10);
				pSelectItemMark->setAnchorPoint(ccp(0,0));
				pSelectItemMark->setVisible(0==nIndex ? true : false);
				pCell->addChild(pSelectItemMark);
			}
			// 活动名字
			CCLabelTTF *pDescription = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(mActivityList->second.szName).c_str(),"微软雅黑",22, \
				pItemBG->getContentSize(),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
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

	CCScale9Sprite *pBlueBG = CCScale9Sprite::create("blueBG.png");
	if (0 != pBlueBG  &&  0 != GetListView())
	{
		CCSize sizelistView = GetListView()->getContentSize();
		CCSize sizeWnd = getContentSize();
		pBlueBG->ignoreAnchorPointForPosition(true);
		pBlueBG->setPreferredSize(CCSize(sizeWnd.width-sizelistView.width-c_smallWndBorderX*2+17, sizeWnd.height-c_smallWndBorderY-c_titleHeight-10));
		pBlueBG->setPosition(c_smallWndBorderX+sizelistView.width-27, c_smallWndBorderY+15);
		addChild(pBlueBG, GetListView()->getZOrder()-1);
	}

	if (0 != pBlueBG)
	{
		// 活动标题
		CCLabelTTF *pTitleText = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("中华人民共和国").c_str(),"微软雅黑",26, CCSize(pBlueBG->getContentSize().width, 100), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		if (0 != pTitleText)
		{
			pTitleText->ignoreAnchorPointForPosition(true);
			pTitleText->setColor(ccc3(255,184,12));
			pTitleText->setPosition(ccp(0,pBlueBG->getContentSize().height-80));
			SIX_Utility::GetInstance()->FixedTexParameters(pTitleText->getTexture(),true);
			pBlueBG->addChild(pTitleText);
		}
		// 分界线
		CCSprite *pDividingLine = CCSprite::create("dividingLine.jpg");
		if (0 != pDividingLine)
		{
			pDividingLine->ignoreAnchorPointForPosition(true);
			pDividingLine->setPosition(ccp((pBlueBG->getContentSize().width-pDividingLine->getContentSize().width)/2, pBlueBG->getContentSize().height-60));
			pBlueBG->addChild(pDividingLine);
		}
		// 活动时间
		CCLabelTTF *pTextTime = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("2012/9/1-2013/12/29").c_str(),"微软雅黑",20, CCSize(pBlueBG->getContentSize().width, 100), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		if (0 != pTextTime)
		{
			pTextTime->ignoreAnchorPointForPosition(true);
			pTextTime->setColor(ccc3(255,255,0));
			pTextTime->setPosition(ccp(40,pBlueBG->getContentSize().height-140));
			SIX_Utility::GetInstance()->FixedTexParameters(pTextTime->getTexture(),true);
			pBlueBG->addChild(pTextTime);
		}
		// 活动详细说明
		CCLabelTTF *pTextContent = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("    活动期间，完成比赛100局。活动期间，完成比赛100局。活动期间，完成比赛100局。活动期间，完成比赛100局。活动期间，完成比赛100局。将。。。！").c_str(),"微软雅黑",14, CCSize(pBlueBG->getContentSize().width-80, 100), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		if (0 != pTextContent)
		{
			pTextContent->ignoreAnchorPointForPosition(true);
			pTextContent->setColor(ccc3(240,240,240));
			pTextContent->setPosition(ccp(40,pBlueBG->getContentSize().height-190));
			SIX_Utility::GetInstance()->FixedTexParameters(pTextContent->getTexture(),true);
			pBlueBG->addChild(pTextContent);
		}
	}
}

CCSize SIX_PopWndActivity::cellSizeForTable(CCTableView *table)
{
	return CCSize(0,0); 
}

CCTableViewCell* SIX_PopWndActivity::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	return 0;
}

unsigned int SIX_PopWndActivity::numberOfCellsInTableView(CCTableView *table)
{
	return 0;
}

void SIX_PopWndActivity::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
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

void SIX_PopWndActivity::scrollViewDidScroll(CCScrollView* view)
{}

void SIX_PopWndActivity::scrollViewDidZoom(CCScrollView* view)
{}

void SIX_PopWndActivity::SetData(CMD_SC_ActivityList *& pActivity)
{
	CMD_SC_ActivityList Activity;
	memcpy(&Activity, pActivity, sizeof(Activity));
	m_mapActivityList.insert(make_pair(Activity.nID, Activity));
}

void SIX_PopWndActivity::doEvents(CCObject* pSender, CCControlEvent controlEvent)
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
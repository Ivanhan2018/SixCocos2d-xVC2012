#include "SIX_PopWndHelp.h"

enum NodeTag
{
	BUTTION_START_ID =1000,
	BUTTON_END_ID = 1001,
	SELECT_BUTTON_ID = 10,
};

SIX_PopWndHelp::~SIX_PopWndHelp(void)
{
}

SIX_PopWndHelp *SIX_PopWndHelp::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndHelp *pPopWnd = new SIX_PopWndHelp();
	SIX_PopWndHaveListView::Create(pPopWnd, ccp(x,y), color, CCSize(width,height), bRedrawBorder, bCloseThenCleanup);
	pPopWnd->SetListViewCellSize(CCSize(width-170-c_smallWndBorderX*2-10, (height-c_titleHeight-c_smallWndBorderY)/10));
	pPopWnd->SetListViewRect(CCRect(c_smallWndBorderX+175,c_smallWndBorderY+10,width-170-c_smallWndBorderX*2-10, height-c_titleHeight-c_smallWndBorderY));
	return pPopWnd;
}

bool SIX_PopWndHelp::init()
{
	if (!SIX_PopWndHaveListView::init())
		return false;
	
	m_pLastButton = 0;
	SetTitlePath("help_titleBG.png");
	return true;
}

void SIX_PopWndHelp::onEnterTransitionDidFinish()
{
	SIX_PopWndHaveListView::onEnterTransitionDidFinish();

	float fOffsetY = getContentSize().height-120;
	char szName[][32]={"游戏规则", "经验等级"};
	int iArrayCount = sizeof(szName)/sizeof(szName[0]);

	CCControlButton *pTypeBT = SIX_Utility::GetInstance()->CreateButtonWithFile("ItemBG.png", CCRect(0,0,170,61));
	CCScale9Sprite *pSmallWnd = dynamic_cast<CCScale9Sprite *>(getChildByTag(SMALL_BG));
	CCScale9Sprite *pBlueBG = CCScale9Sprite::create("blueBG.png");
	if (pBlueBG && pSmallWnd && pTypeBT)
	{
		CCSize sizeWnd = getContentSize();
		pBlueBG->ignoreAnchorPointForPosition(true);
		pBlueBG->setPosition(c_smallWndBorderX+4+pTypeBT->getContentSize().width, pSmallWnd->getPositionY()+10);
		pBlueBG->setPreferredSize(CCSize(getContentSize().width-pBlueBG->getPositionX()-20, pSmallWnd->getContentSize().height-10));
		addChild(pBlueBG);
	}

	for (int i=0; i<iArrayCount; ++i)
	{
		CCControlButton *pType = SIX_Utility::GetInstance()->CreateButtonWithFile("ItemBG.png", CCRect(0,0,170,61), szName[i], "微软雅黑", 22);
		if (pType)
		{
			pType->setTag(BUTTION_START_ID+i);
			pType->setZoomOnTouchDown(false);
			pType->setDefaultTouchPriority(m_nPriority-1);
			pType->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndHelp::doEvents),32);
			pType->setPosition(ccp(c_smallWndBorderX+4, fOffsetY));
			addChild(pType);
			fOffsetY -= pType->getContentSize().height;

			CCSprite *pSelectItemMark = CCSprite::create("selectItemBG.png");
			if (pSelectItemMark)
			{
				pSelectItemMark->setTag(SELECT_BUTTON_ID);
				pSelectItemMark->ignoreAnchorPointForPosition(true);
				pSelectItemMark->setVisible(false);
				pType->addChild(pSelectItemMark);
			}

			if (0 == i)
			{
				OnClickBtn(pType);
			}
		}
	}
	SetReceiveDataComplete(true, true);
}

void SIX_PopWndHelp::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControlButton *pButton = dynamic_cast<CCControlButton *>(pSender);
	int tag = pButton->getTag();
	if (event != CCControlEventTouchUpInside)
		return;

	if (BUTTION_START_ID <= tag  &&  BUTTON_END_ID >= tag)
	{
		OnClickBtn(pButton);
	}
	else
	{
		SIXLog("SIX_PopWndHaveListView::doEvents 未知按钮事件,  tag=%d", tag);
	}
}

void SIX_PopWndHelp::OnClickBtn(CCControlButton *pButton)
{
	if ( !GetListView() )
		return;
	if (m_pLastButton)
	{
		CCSprite *pSelect = dynamic_cast<CCSprite *>(m_pLastButton->getChildByTag(SELECT_BUTTON_ID));
		if (pSelect)
			pSelect->setVisible(false);
	}
	m_pLastButton = pButton;
	CCSprite *pSelect = dynamic_cast<CCSprite *>(pButton->getChildByTag(SELECT_BUTTON_ID));
	if (pSelect)
	{
		pSelect->setVisible(true);
	}

	int iIndex = pButton->getTag()-BUTTION_START_ID;
	if (0>iIndex  || iIndex>BUTTON_END_ID-BUTTION_START_ID)
		return;

	char szFileName[][32]={"help_GameRule.png", "help_experienceRank.png"};
	CCSprite *pTmpContent = CCSprite::create(szFileName[iIndex]);
	CCSize cellSize = GetListView()->cellSizeForTable(0);
	int iNum = pTmpContent->getContentSize().height/cellSize.height;
	iNum += (0==(int)pTmpContent->getContentSize().height%(int)cellSize.height) ? 0 : 1;

	GetListView()->RemoveCellAll();
	for (int i=0; i<iNum; i++)
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		GetListView()->AppendCell(pCell);

		CCSprite *pContent = CCSprite::create(szFileName[iIndex], CCRect(0,cellSize.height*i,cellSize.width,cellSize.height));
		if (pContent)
		{
			pContent->ignoreAnchorPointForPosition(true);
			pCell->addChild(pContent);
		}
	}
}
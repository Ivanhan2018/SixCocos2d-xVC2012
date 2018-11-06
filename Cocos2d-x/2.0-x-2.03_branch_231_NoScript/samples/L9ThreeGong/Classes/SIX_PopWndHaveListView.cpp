#include "SIX_PopWndHaveListView.h"

const int c_PaddingLR = 5;
const int c_PaddingT = 5;
const int c_HeaderH = 15;

SIX_PopWndHaveListView::~SIX_PopWndHaveListView()
{
}

SIX_PopWndHaveListView *SIX_PopWndHaveListView::Create(SIX_PopWndHaveListView *pPopWnd, CCPoint pt,const ccColor4B& color, CCSize size,bool bRedrawBorder/*=false*/,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	if (0.0001 > pt.x && 0.0001 > pt.y)
	{
		CCSize szWind = CCDirector::sharedDirector()->getWinSize();
		pt.x = (szWind.width - size.width) / 2;
		pt.y = (szWind.height - size.height) / 2;
	}

	//SIX_PopWndHaveListView *pPopWnd = new SIX_PopWndHaveListView();
	if (pPopWnd && pPopWnd->init())
	{
		pPopWnd->initWithColor(color,size.width,size.height);
		pPopWnd->setPosition(pt.x,pt.y);
		pPopWnd->setRedrawBorder(bRedrawBorder);
		pPopWnd->setTouchEnabled(true);
		pPopWnd->m_ForbiddenTouch = true;
		pPopWnd->m_bCloseThenCleanup = bCloseThenCleanup;
		pPopWnd->setObjName("SIX_PopWndHaveListView");
		pPopWnd->backgroundWithFile("box_bg.png");
	}
	return pPopWnd;
}

bool SIX_PopWndHaveListView::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;

	m_pListView = 0;
	m_LastShowTime = 0.0;
	m_pLoadSign = 0;
	m_bReceiveDataComplete = true;
	
	setShowType(MOVABLE_TOP);
	setHideType(MOVABLE_TOP);

	InitMask(ccc4(0,0,0,128));
	// 设置弹出窗口不可拖拽
	// Cool.Cat
	setAllowDragged(false);
	
	SetListViewCellSize(CCSize(183,73));
	SetListViewRect(CCRect(17,35,200,330));
	SetListViewDirection(kCCScrollViewDirectionVertical);
	SetHaveScrollBar(true);
	return true;
}

void SIX_PopWndHaveListView::onEnterTransitionDidFinish()
{
	CCSize sizeWnd = getContentSize();

	// 关闭按钮
	CCControlButton *pCloseBT = SIX_Utility::GetInstance()->CreateButtonWithFileCell("btn_close.png", 2);
	if (0 != pCloseBT)
	{
		pCloseBT->setTag(RETURN_ID);
		pCloseBT->setObjName("PopWnd_Close");
		pCloseBT->setZoomOnTouchDown(false);
		pCloseBT->setDefaultTouchPriority(m_nPriority-1);
		pCloseBT->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndHaveListView::doEvents),32);
		pCloseBT->setPosition(ccp(sizeWnd.width-pCloseBT->getContentSize().width/2-15, getContentSize().height-pCloseBT->getContentSize().height/2-15));
		addChild(pCloseBT);
	}

	// 标题
	if ( !m_strTitleImgPath.empty() )
	{
		CCSprite * pTitle = CCSprite::create(m_strTitleImgPath.c_str());
		if (0 != pTitle)
		{
			pTitle->ignoreAnchorPointForPosition(true);
			pTitle->setPosition(ccp((sizeWnd.width-pTitle->getContentSize().width)/2, sizeWnd.height-pTitle->getContentSize().height-(c_titleHeight-pTitle->getContentSize().height)/2));
			addChild(pTitle);
		}
	}

	InitListView();

	// 小窗口背景中
	CCScale9Sprite *pSmallWnd = CCScale9Sprite::create("SmallWndInWnd.png");
	if (0 != pSmallWnd)
	{
		pSmallWnd->ignoreAnchorPointForPosition(true);
		pSmallWnd->setPreferredSize(CCSize(sizeWnd.width-c_smallWndBorderX*2, sizeWnd.height-c_titleHeight));
		pSmallWnd->setPosition(c_smallWndBorderX, c_smallWndBorderY);
		pSmallWnd->setTag(SMALL_BG);
		addChild(pSmallWnd, getZOrder()+200);
	}

	// 加载
	if (0 == m_pLoadSign)
	{
		m_pLoadSign = CCSprite::create("loading.png");
		if (0 != m_pLoadSign)
		{
			CCRotateBy *pRotateBy = CCRotateBy::create(0.02f, 10.0f);
			m_pLoadSign->runAction(CCRepeatForever::create(pRotateBy));
			m_pLoadSign->setAnchorPoint(ccp(0.5,0.5));
			m_pLoadSign->ignoreAnchorPointForPosition(true);
			CCSize sizeLoad = m_pLoadSign->getContentSize();
			m_pLoadSign->setPosition(CCPoint((sizeWnd.width-sizeLoad.width)/2,(sizeWnd.height-sizeLoad.height)/2));
			m_pLoadSign->setTag(LOAD_ID);
			addChild(m_pLoadSign, getZOrder()+200);
		}
	}
}

void SIX_PopWndHaveListView::SetListViewRect(CCRect rc)
{
	m_listViewRect = rc;
}

void SIX_PopWndHaveListView::SetListViewCellSize(CCSize size)
{
	m_listViewCell = size;
}

void SIX_PopWndHaveListView::SetListViewDirection(CCScrollViewDirection direction)
{
	m_ScrollViewDirection = direction;
}

void SIX_PopWndHaveListView::SetHaveScrollBar(bool bHave)
{
	m_bHaveScrollBar = bHave;
}

SIX_ListView * SIX_PopWndHaveListView::GetListView()
{
	return m_pListView;
}

void SIX_PopWndHaveListView::ShowWnd()
{
	double now = SIX_Utility::GetInstance()->GetGlobalSecond();
	//SIXLog("m_LastShowTime[%.2f/%.2f].m_IsShow[%d]",m_LastShowTime,now,m_IsShow);
	if (now-m_LastShowTime<0.05)
		return;

	m_LastShowTime = now;
	
	Show(!m_IsShow);
}

void SIX_PopWndHaveListView::SetReceiveDataComplete(bool bComplete/*=true*/, bool bOnlyStopAnimation/*=false*/)
{
	if ( bComplete )
	{
		if ( !bOnlyStopAnimation )
			setCellContent();

		if (0 != m_pLoadSign)
		{
			m_pLoadSign->setVisible(false);
			m_pLoadSign->pauseSchedulerAndActions();
		}
	}
	else
	{
		if (0 != m_pLoadSign)
		{
			m_pLoadSign->setVisible(true);
			m_pLoadSign->resumeSchedulerAndActions();
		}
	}
	m_bReceiveDataComplete = bComplete;
}

void SIX_PopWndHaveListView::SetTitlePath(const char *pTitleName)
{
	m_strTitleImgPath = pTitleName;
}

void SIX_PopWndHaveListView::InitListView()
{
	if (m_pListView)
		return;

	SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
	pContainer->setContentSize(CCSize(m_listViewRect.size.width, m_listViewRect.size.height));
	pContainer->setPosition(ccp(m_listViewRect.getMinX(), m_listViewRect.getMinY()));

	//SIX_ScrollBar *pScrollBar = NULL;	
	//if (m_bHaveScrollBar)
	//{
	//	pScrollBar = SIX_ScrollBar::create(
	//		"scrollbar.png",CCRect(0,51,17,17),CCSize(m_listViewRect.size.height-17*2,17),
	//		"scrollbar.png",CCRect(0,51,17,17),
	//		"scrollbar.png",CCRect(0,34,17,17),
	//		"scrollbar.png",CCRect(0,34,17,17),
	//		"scrollbar.png",CCRect(0,0,17,17),
	//		"scrollbar.png",CCRect(0,17,17,17),
	//		CCSize(17,17),
	//		false
	//		);
	//	pScrollBar->setAnchorPoint(ccp(0,0));
	//	pScrollBar->setMinimumValue(0);
	//	pScrollBar->setMaximumValue(100);
	//	pScrollBar->setValue(0);
	//	pScrollBar->setDefaultTouchPriority(m_nPriority-1);
	//}

	m_pListView = SIX_ListView::create(ccc4(0,0,0,0),
				ccp(m_listViewRect.getMinX(),m_listViewRect.getMinY()),
				CCSize(m_listViewRect.size.width, m_listViewRect.size.height),
				CCSize(m_listViewCell.width, m_listViewCell.height),
				m_ScrollViewDirection,
				pContainer,
				NULL//pScrollBar
			);

	m_pListView->getTableView()->setDelegate(this);
	m_pListView->getTableView()->setObjName("PopWndList");
	
	// -- 设置响应touch事件(create的时候已经设置好了，这里只是演示而已)
	m_pListView->setTouchEnabled(true);	
	// -- 设置裁剪超出区域(create的时候默认设置为true，这里只是演示而已~)
	m_pListView->getTableView()->setClippingToBounds(true);
	// -- 设置横竖方向(create的时候已经设置好了，这里只是演示而已~)
	m_pListView->getTableView()->setDirection(m_ScrollViewDirection);
	// -- 设置自上而下滚动(create的时候已经设置好了，这里只是演示而已~)
	m_pListView->getTableView()->setVerticalFillOrder(kCCTableViewFillTopDown);
	// -- 设置滑动效果
	m_pListView->getTableView()->setBounceable(true);
	addChild(m_pListView, getZOrder()+100);
}

void SIX_PopWndHaveListView::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			case RETURN_ID:
				{
					ShowWnd();
					break;
				}
			default: 
				{
					SIXLog("SIX_PopWndHaveListView::doEvents 未知按钮事件,  tag=%d", tag);
					break;
				}
			}
			break;
		}
	}
}
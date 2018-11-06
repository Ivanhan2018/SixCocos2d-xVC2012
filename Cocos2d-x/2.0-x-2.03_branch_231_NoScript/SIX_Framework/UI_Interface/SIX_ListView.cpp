#include "SIX_ListView.h"

// ----------------------------
// 基类(CCLayerColor)属性：
// color=背景颜色
// ----------------------------
// 自身(SIX_ListView)属性
// offset=控件偏移大小
// size=控件可视区域大小
// cellSize=节点可视区域大小
// pViewDirection=滚动方向
// pContainer=内部容器
// pScrollBar=内部滚动条
// ----------------------------
SIX_ListView *SIX_ListView::create(const ccColor4B& color,CCPoint offset,CCSize size,CCSize cellSize,int pViewDirection,SIX_UILayer *pContainer,SIX_ScrollBar *pScrollBar)
{
	SIX_ListView *pRet = new SIX_ListView(offset,size,cellSize,pViewDirection,pContainer,pScrollBar);
	if (pRet && pRet->initWithColor(color,size.width,size.height))
	{
		// 作为一个CCLayerColor感到深深的压力
		pRet->setPosition(offset.x,offset.y);
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SIX_ListView::initWithColor(const ccColor4B& color, float w, float h)
{
    if( SIX_ListView::init() ) {

        // default blend function
        m_tBlendFunc.src = GL_SRC_ALPHA;
        m_tBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;

        m_tColor.r = color.r;
        m_tColor.g = color.g;
        m_tColor.b = color.b;
        m_cOpacity = color.a;

        for (int i = 0; i<sizeof(m_pSquareVertices) / sizeof( m_pSquareVertices[0]); i++ ) {
            m_pSquareVertices[i].x = 0.0f;
            m_pSquareVertices[i].y = 0.0f;
        }

        updateColor();
        setContentSize(CCSizeMake(w, h));

        setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    }
    return true;
}

bool SIX_ListView::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	setTouchEnabled(true);
    m_tableView = SIX_TableView::create(this,m_size,m_container);
    m_tableView->setDirection(CCScrollViewDirection(m_pViewDirection));
	m_tableView->setAnchorPoint(ccp(0,0));
    m_tableView->setDelegate(this);
	// 自上而下
	m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	// 裁剪超出区域(隐藏)
	m_tableView->setClippingToBounds(true);
	// 设置动态滚动
	m_tableView->setBounceable(true);
    this->addChild(m_tableView);
    m_tableView->reloadData();

	// 重新设置下滚动条的偏移
	if (m_scrollbar)
	{
		// 设置回调
		m_scrollbar->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_ListView::ScrollBarChanged),CCControlEventValueChanged);

		// 先加进来
		this->addChild(m_scrollbar);

		// 如果是横向的
		if (m_scrollbar->getHorizontal())
		{
			m_scrollbar->setPosition(ccp(0,0));
		}
		// 否则如果纵向的
		else
		{
			m_scrollbar->setPosition(ccp(m_size.width,m_size.height));
		}

		// 默认隐藏
		//m_scrollbar->setVisible(false);
	}

	return true;
}

SIX_ListView::SIX_ListView(CCPoint offset,CCSize size,CCSize cellSize,int pViewDirection,SIX_UILayer *pContainer,SIX_ScrollBar *pScrollBar)
{
	m_Cells = new SIX_DSTPL<SIX_ListViewCell>;

	m_container = pContainer;

	m_offset.x = offset.x;
	m_offset.y = offset.y;

	m_size.width = size.width;
	m_size.height = size.height;

	m_cellSize.width = cellSize.width;
	m_cellSize.height = cellSize.height;

	// 如果传入了滚动条，还要微调下
	if (pScrollBar)
	{
		// 稍微挤一挤，沟总是有的~
		CCSize scrollSize = pScrollBar->getContentSize();

		// 如果是横向滚动条的话
		if (pScrollBar->getHorizontal())
		{
			m_size.height = size.height - scrollSize.height;
		}
		// 否则纵向的话
		else
		{
			m_size.width = size.width - scrollSize.height;

			m_cellSize.width = m_size.width;
		}
		
		pScrollBar->setVisible(false);

		//SIXLog("m_size = %.2f/%.2f , scrollSize = %.2f/%.2f",
		//	m_size.width,m_size.height,
		//	scrollSize.width,scrollSize.height);
	}

	m_pViewDirection = pViewDirection;

	m_scrollbar = pScrollBar;
}

SIX_ListView::~SIX_ListView()
{
	RemoveCellAll();
	SIXLog("~SIX_ListView");
}

/* Implement CCTableViewDataSource */
CCSize SIX_ListView::cellSizeForTable(CCTableView *table)
{
	return m_cellSize;
}

CCTableViewCell* SIX_ListView::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	if (!m_Cells || !m_Cells->GetChildrenCount())
		return 0;
	return m_Cells->Get(idx);
}

unsigned int SIX_ListView::numberOfCellsInTableView(CCTableView *table)
{
	if (!m_Cells || !m_Cells->GetChildrenCount())
		return 0;
	return m_Cells->GetChildrenCount();
}

/* Implement CCTableViewDelegate */
void SIX_ListView::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("SIX_ListView.tableCellTouched.cell[%u]", cell->getIdx());
}

bool SIX_ListView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	bool retv = true;

	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();

	CCTouchHandler *pBaseHandler = 0;
	CCTouchHandler *pHandler = 0;
	CCTouchDelegate *pDelegate = 0;
	CCNode *pChild = 0;

	CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
	{
		if (!pChild)
			continue;

		pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
		if (!pDelegate)
			continue;

		pBaseHandler = pDispatcher->findHandler(pDelegate);

		pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
		if (!pHandler)
			pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

		if (pHandler)
			pHandler->getDelegate()->ccTouchBegan(pTouch, pEvent);
	}

	return retv;
}

void SIX_ListView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
	CCTouchHandler *pBaseHandler = 0;
	CCTouchHandler *pHandler = 0;
	CCTouchDelegate *pDelegate = 0;
	CCNode *pChild = 0;

	CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
	{
		if (!pChild)
			continue;

		pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
		if (!pDelegate)
			continue;

		pBaseHandler = pDispatcher->findHandler(pDelegate);

		pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
		if (!pHandler)
			pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

		if (pHandler)
			pHandler->getDelegate()->ccTouchMoved(pTouch, pEvent);
	}
	CCLayerColor::ccTouchMoved(pTouch,pEvent);
}

void SIX_ListView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
	CCTouchHandler *pBaseHandler = 0;
	CCTouchHandler *pHandler = 0;
	CCTouchDelegate *pDelegate = 0;
	CCNode *pChild = 0;

	CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
	{
		if (!pChild)
			continue;

		pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
		if (!pDelegate)
			continue;

		pBaseHandler = pDispatcher->findHandler(pDelegate);

		pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
		if (!pHandler)
			pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

		if (pHandler)
		{
			//SIXLog("ccTouchEnded.pHandler[0x%08X]",pHandler);
			pHandler->getDelegate()->ccTouchEnded(pTouch, pEvent);
		}
	}
	CCLayerColor::ccTouchEnded(pTouch,pEvent);
}

void SIX_ListView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
		
	CCTouchHandler *pBaseHandler = 0;
	CCTouchHandler *pHandler = 0;
	CCTouchDelegate *pDelegate = 0;
	CCNode *pChild = 0;

	CCARRAY_FOREACH_T(this->getChildren(),pChild,CCNode*)
	{
		if (!pChild)
			continue;

		pDelegate = dynamic_cast<CCTouchDelegate*>(pChild);
		if (!pDelegate)
			continue;

		pBaseHandler = pDispatcher->findHandler(pDelegate);

		pHandler = dynamic_cast<CCTargetedTouchHandler*>(pBaseHandler);
		if (!pHandler)
			pHandler = dynamic_cast<CCStandardTouchHandler*>(pBaseHandler);

		if (pHandler)
			pHandler->getDelegate()->ccTouchCancelled(pTouch, pEvent);
	}
	CCLayerColor::ccTouchCancelled(pTouch,pEvent);
}

/* Implement CCScrollViewDelegate */
void SIX_ListView::scrollViewDidScroll(CCScrollView* view)
{
}

void SIX_ListView::scrollViewDidZoom(CCScrollView* view)
{
}

/* Implement Self Method */
// 获取子节点
SIX_ListViewCell *SIX_ListView::GetCell(unsigned int idx)
{
	if (!m_Cells || !m_tableView || (idx+1)>m_Cells->GetChildrenCount())
		return 0;

	return (SIX_ListViewCell*)(m_Cells->Get(idx));
}

// 增加子节点
void SIX_ListView::AppendCell(SIX_ListViewCell *pItem)
{
	if (!m_Cells || !m_tableView)
		return;

	m_Cells->Add(pItem,this->GetCellCount());
	// 我刷~
	this->refresh();
}

void SIX_ListView::AddCell(SIX_ListViewCell *pItem,unsigned int idx)
{
	if (!m_Cells || !m_tableView)
		return;

	m_Cells->Add(pItem,idx);
	// 我刷~
	this->refresh();
}

// 移除子节点
void SIX_ListView::RemoveCell(unsigned int idx,bool bRelease)
{
	if (!m_Cells)
		return;

	m_Cells->Del(idx,bRelease);
	// 我刷~
	this->refresh();
}

void SIX_ListView::RemoveCell(SIX_ListViewCell *pItem,bool bRelease)
{
	if (!m_Cells)
		return;

	m_Cells->Del(pItem,bRelease);
	// 我刷~
	this->refresh();
}

// 移除所有子节点
void SIX_ListView::RemoveCellAll()
{
	if (!m_Cells)
		return;
	
	m_Cells->DelAll();
	// 我刷刷刷~
	this->refresh();
}

// 子节点数量
unsigned int SIX_ListView::GetCellCount()
{
	if (!m_Cells)
		return 0;
	return m_Cells->GetChildrenCount();
}

// 增删子节点后需要刷新ListView
void SIX_ListView::refresh()
{
	if (m_tableView)
	{
		m_tableView->reloadData();
		if (!m_scrollbar)
			return;
		// 刷新滚动条
		// Cool.Cat
		CCSize fullSize = m_tableView->getContentSize();
		CCSize trimSize = this->getContentSize();

		//SIXLog("fullSize = %.2f/%.2f , trimSize = %.2f/%.2f",fullSize.width,fullSize.height,trimSize.width,trimSize.height);

		// 动态增加/删除cell，要影响滚动条的显示/隐藏及移动到头尾
		// Cool.Cat
		if (m_scrollbar->getHorizontal())
		{
			if (fullSize.width>trimSize.width)
			{
				m_scrollbar->getSlider()->setValue(m_scrollbar->getMaximumValue(),true);
				m_scrollbar->setVisible(true);
			}
			else if (fullSize.width==0)
			{
				m_scrollbar->getSlider()->setValue(m_scrollbar->getMinimumValue(),true);
				m_scrollbar->setVisible(false);
			}
			else
			{
				m_scrollbar->setVisible(false);
			}
		}
		else
		{
			if (fullSize.height>trimSize.height)
			{
				m_scrollbar->getSlider()->setValue(m_scrollbar->getMaximumValue(),true);
				m_scrollbar->setVisible(true);
			}
			else if (fullSize.height==0)
			{
				m_scrollbar->getSlider()->setValue(m_scrollbar->getMinimumValue(),true);
				m_scrollbar->setVisible(false);
			}
			else
			{
				m_scrollbar->setVisible(false);
			}
		}
	}
}

// 取TableView容器
CCTableView *SIX_ListView::getTableView()
{
	return m_tableView;
}

// 取背景层容器
SIX_UILayer *SIX_ListView::getLayer()
{
	return m_container;
}

// 取滚动条对象
SIX_ScrollBar *SIX_ListView::getScrollbar()
{
	return m_scrollbar;
}

// 滚动条回调
// Cool.Cat
void SIX_ListView::ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent)
{
	SIX_ScrollBar* pScrollbar = (SIX_ScrollBar*)pSender;
	if (!pScrollbar || !pScrollbar->isVisible())
		return;

	if (!m_tableView || !m_tableView->isVisible())
		return;

	// 滚动条当前值
	float value = pScrollbar->getValue();
	float max = pScrollbar->getMaximumValue();

	CCSize fullSize = m_tableView->getContentSize();
	CCSize trimSize = this->getContentSize();
	//CCPoint leftPoint = m_tableView->getContainer()->getPosition();

	// 滚动条当前百分比
	float ratio = 1.0f-value/max;

	// 计算cell偏移
	CCPoint offset_pt = CCPointZero;
	if (pScrollbar->getHorizontal())
		offset_pt.x = -ratio*(fullSize.width-trimSize.width);
	else
		offset_pt.y = -ratio*(fullSize.height-trimSize.height);

	//SIXLog("ScrollBarChanged.value[%.2f/%.2f].ratio[%.2f].fullSize[%.2f/%.2f].trimSize[%.2f/%.2f].offset_pt[%.2f/%.2f].leftPoint[%.2f/%.2f]",
	//	value,max,
	//	ratio,
	//	fullSize.width,fullSize.height,
	//	trimSize.width,trimSize.height,
	//	offset_pt.x,offset_pt.y,
	//	leftPoint.x,leftPoint.y
	//);

	// do it~
	m_tableView->setContentOffset(offset_pt);
}
#include "SIX_ListView.h"

// ----------------------------
// ����(CCLayerColor)���ԣ�
// color=������ɫ
// ----------------------------
// ����(SIX_ListView)����
// offset=�ؼ�ƫ�ƴ�С
// size=�ؼ����������С
// cellSize=�ڵ���������С
// pViewDirection=��������
// pContainer=�ڲ�����
// pScrollBar=�ڲ�������
// ----------------------------
SIX_ListView *SIX_ListView::create(const ccColor4B& color,CCPoint offset,CCSize size,CCSize cellSize,int pViewDirection,SIX_UILayer *pContainer,SIX_ScrollBar *pScrollBar)
{
	SIX_ListView *pRet = new SIX_ListView(offset,size,cellSize,pViewDirection,pContainer,pScrollBar);
	if (pRet && pRet->initWithColor(color,size.width,size.height))
	{
		// ��Ϊһ��CCLayerColor�е������ѹ��
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
    tableView = CCTableView::create(this,m_size,m_container);
    tableView->setDirection(CCScrollViewDirection(m_pViewDirection));
	tableView->setAnchorPoint(ccp(0,0));
    tableView->setDelegate(this);
	// ���϶���
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	// �ü���������(����)
	tableView->setClippingToBounds(true);
	// ���ö�̬����
	tableView->setBounceable(true);
    this->addChild(tableView);
    tableView->reloadData();

	// ���������¹�������ƫ��
	if (m_scrollbar)
	{
		// ���ûص�
		m_scrollbar->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_ListView::ScrollBarChanged),CCControlEventValueChanged);

		// �ȼӽ���
		this->addChild(m_scrollbar);

		// ����Ǻ����
		if (m_scrollbar->getHorizontal())
		{
			m_scrollbar->setPosition(ccp(0,0));
		}
		// ������������
		else
		{
			m_scrollbar->setPosition(ccp(m_size.width,m_size.height));
		}
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

	// ��������˹���������Ҫ΢����
	if (pScrollBar)
	{
		// ��΢��һ�����������е�~
		CCSize scrollSize = pScrollBar->getContentSize();

		// ����Ǻ���������Ļ�
		if (pScrollBar->getHorizontal())
		{
			m_size.height = size.height - scrollSize.height;
		}
		// ��������Ļ�
		else
		{
			m_size.width = size.width - scrollSize.height;

			m_cellSize.width = m_size.width;
		}

		SIXLog("m_size = %.2f/%.2f , scrollSize = %.2f/%.2f",
			m_size.width,m_size.height,
			scrollSize.width,scrollSize.height);
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
			pHandler->getDelegate()->ccTouchEnded(pTouch, pEvent);
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
// ��ȡ�ӽڵ�
SIX_ListViewCell *SIX_ListView::GetCell(unsigned int idx)
{
	if (!m_Cells || !tableView)
		return 0;

	return (SIX_ListViewCell*)(m_Cells->Get(idx));
}

// �����ӽڵ�
void SIX_ListView::AppendCell(SIX_ListViewCell *pItem)
{
	if (!m_Cells || !tableView)
		return;

	m_Cells->Add(pItem,this->GetCellCount());
	// ��ˢ~
	this->refresh();
}

void SIX_ListView::AddCell(SIX_ListViewCell *pItem,unsigned int idx)
{
	if (!m_Cells || !tableView)
		return;

	m_Cells->Add(pItem,idx);
	// ��ˢ~
	this->refresh();
}

// �Ƴ��ӽڵ�
void SIX_ListView::RemoveCell(unsigned int idx,bool bRelease)
{
	if (!m_Cells)
		return;

	m_Cells->Del(idx,bRelease);
	// ��ˢ~
	this->refresh();
}

void SIX_ListView::RemoveCell(SIX_ListViewCell *pItem,bool bRelease)
{
	if (!m_Cells)
		return;

	m_Cells->Del(pItem,bRelease);
	// ��ˢ~
	this->refresh();
}

// �Ƴ������ӽڵ�
void SIX_ListView::RemoveCellAll()
{
	if (!m_Cells)
		return;
	
	m_Cells->DelAll();
	// ��ˢˢˢ~
	this->refresh();
}

// �ӽڵ�����
unsigned int SIX_ListView::GetCellCount()
{
	if (!m_Cells)
		return 0;
	return m_Cells->GetChildrenCount();
}

// ��ɾ�ӽڵ����Ҫˢ��ListView
void SIX_ListView::refresh()
{
	if (tableView)
		tableView->reloadData();
}

// ȡTableView����
CCTableView *SIX_ListView::getContainer()
{
	return tableView;
}

// �������ص�
void SIX_ListView::ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent)
{
	SIX_ScrollBar* pScrollbar = (SIX_ScrollBar*)pSender;
	if (!pScrollbar)
		return;

	// ��������ǰֵ
	float value = pScrollbar->getValue();
	SIXLog("ScrollBarChanged.value=%.2f",value);
}
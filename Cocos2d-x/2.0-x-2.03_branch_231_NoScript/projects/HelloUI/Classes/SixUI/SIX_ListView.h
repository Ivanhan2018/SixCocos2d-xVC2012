/***********************************************
Name：SIX_ListView
Desc：SIX_ListView
Auth：Cool.Cat@2013-04-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include "SIX_Typedef.h"
#include "SIX_DSTPL.h"
#include "cocos-ext.h"
#include "SIX_UILayer.h"
#include "SIX_ListViewCell.h"
#include "SIX_ScrollBar.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_ListView:public CCLayerColor,public CCTableViewDataSource,public CCTableViewDelegate
{
public:
	virtual bool init();
	virtual bool initWithColor(const ccColor4B& color, float width, float height);

	static SIX_ListView* create(const ccColor4B& color,CCPoint offset,CCSize size,CCSize cellSize,int pViewDirection,SIX_UILayer *pContainer=0,SIX_ScrollBar *pScrollBar=0);

	SIX_ListView(CCPoint offset,CCSize size,CCSize cellSize,int pViewDirection,SIX_UILayer *pContainer=0,SIX_ScrollBar *pScrollBar=0);
	~SIX_ListView();

	/* CCTableViewDataSource */
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);

	/* CCTableViewDelegate */
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	/* CCScrollViewDelegate */
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
public:
	// 获取子节点
	SIX_ListViewCell *GetCell(unsigned int idx);
	// 增加子节点
	void AppendCell(SIX_ListViewCell *pItem);
	void AddCell(SIX_ListViewCell *pItem,unsigned int idx=0);
	// 移除子节点
	void RemoveCell(unsigned int idx,bool bRelease=true);
	void RemoveCell(SIX_ListViewCell *pItem,bool bRelease=true);
	// 移除所有子节点
	void RemoveCellAll();
	// 子节点数量
	unsigned int GetCellCount();
	// 增删子节点后需要刷新ListView
	void refresh();
	// 取TableView容器
	CCTableView *getContainer();
	// 滚动条回调
	void ScrollBarChanged(CCObject *pSender,CCControlEvent controlEvent);
private:
	CCTableView* tableView;
	// 滚动条
	// CCControlSlider *m_scrollbar;
	SIX_ScrollBar *m_scrollbar;
	// 背景层
	SIX_UILayer *m_container;
	// 偏移
	CCPoint m_offset;
	// 大小
	CCSize m_size;
	// 单元格大小
	CCSize m_cellSize;
	int m_pViewDirection;
	SIX_DSTPL<SIX_ListViewCell> *m_Cells;
};
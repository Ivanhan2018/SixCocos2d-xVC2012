/***********************************************
Name£∫SIX_PopWndActivity
Desc£∫SIX_PopWndActivity
Auth£∫Õ≈≥§@2013-09-27
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "CMD_Plaza.h"

class SIX_PopWndActivity :	public SIX_PopWndHaveListView
{
public:
	static SIX_PopWndActivity *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup=false);
	virtual ~SIX_PopWndActivity(void);

	virtual bool init();
	virtual void setCellContent();
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);

public:
	void SetData(CMD_SC_ActivityList *& pActivity);

private:
	void doEvents(CCObject* pSender, CCControlEvent controlEvent);

private:
	map<int, CMD_SC_ActivityList> m_mapActivityList;
};


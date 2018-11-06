/***********************************************
Name£∫SIX_PopWndRoomList
Desc£∫SIX_PopWndRoomList
Auth£∫Õ≈≥§@2013-10-11
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include <SIX_Typedef.h>
#include "SIX_Common.h"

class SIX_PopWndRoomList :	public SIX_PopWndHaveListView
{
public:
	static SIX_PopWndRoomList *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup=false);
	virtual ~SIX_PopWndRoomList(void);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void setCellContent();
	virtual void onShowFinished();
	virtual bool OnClose();

	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
	
public:
	void SetTablePeopleNumber(int iTableID, int iCount);

private:
	void doEvents(CCObject* pSender, CCControlEvent controlEvent);
	void InitTopList();
};


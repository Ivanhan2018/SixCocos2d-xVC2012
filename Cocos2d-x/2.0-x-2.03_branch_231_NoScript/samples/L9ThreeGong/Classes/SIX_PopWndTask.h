/***********************************************
Name£∫SIX_PopWndTask
Desc£∫SIX_PopWndTask
Auth£∫Õ≈≥§@2013-09-27
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "CMD_Plaza.h"

class SIX_PopWndTask :	public SIX_PopWndHaveListView
{
public:
	static SIX_PopWndTask *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup=false);
	virtual ~SIX_PopWndTask(void);

	virtual bool init();
	virtual void setCellContent();
	virtual void onShowFinished();
	virtual CCSize cellSizeForTable(CCTableView *table){ return CCSize(0,0); }
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx){ return 0;}
	virtual unsigned int numberOfCellsInTableView(CCTableView *table){ return 0;}
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){}
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	void SetData(CMD_SC_TaskList *& pTask);
	void SetNextData(CMD_SC_GET_NEXT_TASK *& pTask);

private:
	void doEvents(CCObject* pSender, CCControlEvent event);

private:
	map<int, CMD_SC_TaskList> m_mapTaskList;
};


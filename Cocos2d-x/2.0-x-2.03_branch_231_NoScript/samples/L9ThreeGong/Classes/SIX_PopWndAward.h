/***********************************************
Name£∫SIX_PopWndAward
Desc£∫SIX_PopWndAward
Auth£∫Õ≈≥§@2013-10-08
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "CMD_Plaza.h"

class SIX_PopWndAward :	public SIX_PopWndHaveListView
{
public:
	static SIX_PopWndAward *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup=false);
	virtual ~SIX_PopWndAward(void);

	virtual bool init();
	virtual void setCellContent();
	virtual CCSize cellSizeForTable(CCTableView *table){ return CCSize(0,0); }
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx){ return 0;}
	virtual unsigned int numberOfCellsInTableView(CCTableView *table){ return 0;}
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){}
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	void SetData(CMD_SC_Award *& pAward);

private:
	void doEvents(CCObject* pSender, CCControlEvent event);

private:
	map<int, CMD_SC_Award> m_mapAward;
};


/***********************************************
Name£∫SIX_PopWndTopList
Desc£∫SIX_PopWndTopList
Auth£∫Õ≈≥§@2013-10-07
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "CMD_Plaza.h"

class SIX_PopWndTopList :	public SIX_PopWndHaveListView
{
public:
	static SIX_PopWndTopList *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup=false);
	virtual ~SIX_PopWndTopList(void);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void setCellContent();
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);

public:
	void SetData(CMD_SC_RankingList *& pTopList);
	void SetMyData(CMD_CSG_Ranking *& pMyTopList);

private:
	void doEvents(CCObject* pSender, CCControlEvent controlEvent);
	void InitTopList();
	void InitItem(CCNode *pCell, const int &nIndex, const char *pcNickName, long long llValue, bool bSetMyData, float fOffsetX, float fOffsetY);

private:
	map<int, CMD_SC_RankingList> m_mapTopList;
	CMD_CSG_Ranking	m_MyTopList;
};


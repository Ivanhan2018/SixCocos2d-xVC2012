/***********************************************
Name£∫SIX_PopWndShop
Desc£∫SIX_PopWndShop
Auth£∫Õ≈≥§@2013-10-08
***********************************************/
#pragma once
#include "SIX_PopWndHaveListView.h"
#include "CMD_Plaza.h"
#include "SIX_PointCard.h"

class SIX_PopWndShop :	public SIX_PopWndHaveListView
{
public:
	static SIX_PopWndShop *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup=false);
	virtual ~SIX_PopWndShop(void);

	virtual bool init();
	virtual void onEnter();
	virtual void onHideFinished();
	virtual void setCellContent();
	virtual CCSize cellSizeForTable(CCTableView *table){ return CCSize(0,0); }
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx){ return 0;}
	virtual unsigned int numberOfCellsInTableView(CCTableView *table){ return 0;}
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){}
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

public:
	void SetData(CMD_SC_Shop *& pShop);
	SIX_PopWndPointCard *& GetPointCardWnd(){ return m_pPointCard; }

private:
	void doEvents(CCObject* pSender, CCControlEvent event);

private:
	map<int, CMD_SC_Shop> m_mapShop;
	SIX_PopWndPointCard * m_pPointCard;
	CCControlButton *m_pBtnPointCard;
	bool m_bOpenPointCardWnd;
};


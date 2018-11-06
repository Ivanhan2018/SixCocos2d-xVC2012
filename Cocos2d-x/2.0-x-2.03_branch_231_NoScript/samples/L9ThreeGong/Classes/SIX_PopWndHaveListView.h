/***********************************************
Name��SIX_PopWndTask
Desc��SIX_PopWndTask
Auth���ų�@2013-09-27
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include "cocos-ext.h"
#include "SIX_EffectPopWnd.h"
#include "SIX_ListView.h"
#include "SIX_ListViewCell.h"
//#include "SIX_ScrollBar.h"

enum BUTTON_ID
{
	RETURN_ID = 1000,		// ���ذ�ť
	LOAD_ID,						// ���ر�־
	SMALL_BG,					// С����
};

const int c_smallWndBorderX = 15;
const int c_smallWndBorderY = 12;
const int c_titleHeight = 60;

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_PopWndHaveListView:public SIX_EffectPopWnd, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	virtual ~SIX_PopWndHaveListView();
	static SIX_PopWndHaveListView *Create(SIX_PopWndHaveListView *pPopWnd, CCPoint pt,const ccColor4B& color, CCSize size,bool bRedrawBorder=false,bool bCloseThenCleanup=false);

public:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void setCellContent(){}
	virtual CCSize cellSizeForTable(CCTableView *table){ return CCSize(0,0); }
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx){ return 0;}
    virtual unsigned int numberOfCellsInTableView(CCTableView *table){ return 0;}
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell){}
	virtual void scrollViewDidScroll(CCScrollView* view){}
	virtual void scrollViewDidZoom(CCScrollView* view){}

	void SetListViewRect(CCRect rc);
	void SetListViewCellSize(CCSize size);
	void SetListViewDirection(CCScrollViewDirection direction);
	void SetHaveScrollBar(bool bHave);
	SIX_ListView * GetListView();

	void ShowWnd();
	void SetReceiveDataComplete(bool bComplete=true, bool bOnlyStopAnimation=false);
	bool GetReceiveDataComplete(){ return m_bReceiveDataComplete; }
	// ���ñ���·��
	void SetTitlePath(const char *pTitleName);

private:
	void InitListView();
	void doEvents(CCObject* pSender, CCControlEvent event);

private:
	CCSprite * m_pLoadSign;
	SIX_ListView * m_pListView;

	CCRect	m_listViewRect;
	CCSize	m_listViewCell;
	CCScrollViewDirection m_ScrollViewDirection;
	bool	m_bHaveScrollBar;

	double m_LastShowTime;
	bool m_bReceiveDataComplete;
	string m_strTitleImgPath;
};
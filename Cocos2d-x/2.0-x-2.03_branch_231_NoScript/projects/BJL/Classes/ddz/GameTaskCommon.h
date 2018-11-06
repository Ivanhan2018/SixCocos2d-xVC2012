//  [4/14/2014 wucan]
#ifndef		__COMMON_TASK__
#define		__COMMON_TASK__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <limits>
USING_NS_CC;
USING_NS_CC_EXT;

class GameTaskCommon:public CCLayer,public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	CREATE_FUNC(GameTaskCommon);
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();

	//--CCTableViewDataSource
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	//--CCTableViewDelegate
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) ;
	virtual void scrollViewDidScroll(CCScrollView* view){};
	virtual void scrollViewDidZoom(CCScrollView* view){};
	void runOutOrIn(bool isVisible=true);
private:
	CC_SYNTHESIZE(bool,m_isOut,IsOut);
	CCSprite*         m_taskBk;
	CCTableView*  m_tableView;
	static char      m_taskBUff[1024];
	int totalCount;
};

#endif
#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class EmailScorllLayer : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	bool intEmailScorllLayerWith(int type,int num);
	static EmailScorllLayer* EmailScorllLayerWith(int type,int num);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	EmailScorllLayer(void);
	~EmailScorllLayer(void);
private:
	int m_nType;
	int m_nMessageNum;
};

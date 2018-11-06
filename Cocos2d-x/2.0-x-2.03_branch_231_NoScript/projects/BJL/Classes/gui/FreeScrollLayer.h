#pragma once

#include "common/GlobalDef.h"
#include "common/CMD_Plaza.h"

#include "cocos2d.h"
#include "cocos-ext.h"



USING_NS_CC;
USING_NS_CC_EXT;

class FreeScrollLayer : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	bool intFreeScrollLayerWith(int num,SDownloadGamePrize_Returnn* data);
	static FreeScrollLayer* FreeScrollLayerWith(int num,SDownloadGamePrize_Returnn* data);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	FreeScrollLayer(void);
	~FreeScrollLayer(void);

	void onGetDownData(CCObject* obj);
private:
	int m_nType;
	int m_nMessageNum;

	SDownloadGamePrize_Returnn* m_Data;

};
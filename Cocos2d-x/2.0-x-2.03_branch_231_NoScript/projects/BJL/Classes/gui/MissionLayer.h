#ifndef __Game__MissionLayer__
#define __Game__MissionLayer__

#include "gui/TabLayer.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "C2DXShareSDK.h"
#include "common/Define.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cn::sharesdk;

enum MissionLayerTab
{
	MissionLayerTabEveryday,
	MissionLayerTabBeginner,
	MissionLayerTabScore,
	MissionLayerTabReference
};

class MissionLayer : public TabLayer, public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{
private:
	CCSize winSize;
	CCSize tableItemSize;
	float tableGapX;
	float tableGapY;
	CCMenuItemSprite* everydayItem;
	CCMenuItemSprite* beginnerItem;
	CCMenuItemSprite* awardItem;
	//每日任务
	CCTableView *everydayTable;
	//新手任务
	CCTableView *beMissionTable;
	int beMissionNum;
public:
	MissionLayer();
	~MissionLayer();
	static CCScene *scene();
	static MissionLayer *create();
	static MissionLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	void initView();
	virtual void doSomething();
	void reloadData(MissionLayerTab tag);
	virtual void keyBackClicked(void);					//手机返回按钮
	void dismiss(cocos2d::CCObject *obj);
	
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);

	//分享回调
	//void authResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *error);
	//void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *userInfo, CCDictionary *error);
	//void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error);
};

class MissionTableHelper: public CCObject, public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{ 
private:
	MissionLayer *father;
	CCSize winSize;
	CCSize tableItemSize;
	int itemsNum;
	MissionLayerTab tableTag;
	string url;
	CCArray *field4ValueArray;
	bool cancelOrNot;
	DWORD totalCount;
	BYTE cbMemberOrder;
	LONG lScore;
public:
	MissionTableHelper(MissionLayer *fath, int num, MissionLayerTab tag);
	~MissionTableHelper();
	void cancelHttpRequest(CCObject *obj);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
	void addTableData(int field4);
	void pressGet(CCObject *obj);
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
};
#endif  //__Game__WarningLayler__
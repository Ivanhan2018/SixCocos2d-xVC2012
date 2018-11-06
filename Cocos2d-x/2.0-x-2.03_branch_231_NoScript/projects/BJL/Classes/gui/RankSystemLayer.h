#ifndef __Game__RankSystemLayer__
#define __Game__RankSystemLayer__

#include "gui/TabLayer.h"
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum RankTableTag
{
	RankTableTag_Rich,
	RankTableTag_Hero,
	RankTableTag_Luck,
	RankTableTag_Teacher,
	RankTableTag_Charm
};

class RankSystemLayer : public TabLayer,public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{

private:
	bool flag;
	CCSize winSize;
	CCSize tableItemSize;
	CCSprite *myRankBk;							//我的排行背景图
	CCLabelTTF *myRankLabel1;					//我的排行字
	CCLabelTTF *myRankLabel2;					//我的排行值
	CCSprite *rankBk;							//排行上方图片

	CCLabelTTF *myRankFieldLabel1;					//排行字段1
	CCLabelTTF *myRankFieldLabel2;					//排行字段2
	CCLabelTTF *myRankFieldLabel3;					//排行字段3
	CCLabelTTF *myRankFieldLabel4;					//排行字段4
	
	//财富榜
	string richRankText;
	CCTableView *richTable;
	//英雄榜
	string heroRankText;
	CCTableView *heroTable;
	//鸿运榜
	string luckRankText;
	CCTableView *luckTable;
	//名师榜
	string teacherRankText;
	CCTableView *teacherTable;
	//魅力榜
	string charmRankText;
	CCTableView *charmTable;
private:
	void initView();
public:
	RankSystemLayer();
	~RankSystemLayer();
	void OnExit();
	static RankSystemLayer *create();
	static RankSystemLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);

	virtual void doSomethingBeforeClosed();
	virtual void doSomething();
	void setMyRankText(string text, RankTableTag tag);
	void reloadData(RankTableTag tag);
	void sendButton(cocos2d::CCObject *obj);
	void deleteButton(cocos2d::CCObject *obj);
	void chatButton(cocos2d::CCObject *obj);
	void pressAddButton(cocos2d::CCObject *obj);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);

};

class RankTableHelper: public CCObject, public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{ 
private:
	RankSystemLayer *father;
	CCSize winSize;
	CCSize tableItemSize;
	int itemsNum;
	RankTableTag tableTag;
	string url;
	CCArray *nicknameArray;
	CCArray *field4ValueArray;
	CCHttpClient*httpClient;
	bool cancelOrNot;
public:
	RankTableHelper(RankSystemLayer *fath, int num, RankTableTag tag);
	~RankTableHelper();
	void cancelHttpRequest(CCObject *obj);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
	void addTableData(string nickname, string field4);
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
};

#endif  //__Game__WarningLayler__
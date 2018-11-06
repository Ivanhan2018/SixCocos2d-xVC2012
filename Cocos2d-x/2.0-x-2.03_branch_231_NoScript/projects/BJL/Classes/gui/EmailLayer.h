//
//  PopFrame.h
//  Game
//
//  Created by ���� on 13-8-26.
//
//

#ifndef __Game__PopFrame__
#define __Game__PopFrame__

#include "gui/TabLayer.h"
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;


enum EmailTableTag
{
	EmailTableTag_Personal,
	EmailTableTag_System,
	EmailTableTag_Friend
};

class EmailLayer : public TabLayer 
{
private:
	CCSize winSize;
	CCSize tableItemSize;
	//�ҵ���Ϣ
	CCTableView *myMsgTable;

	//ϵͳ��Ϣ
	CCTableView *sysMsgTable;  

	//������Ϣ
	CCTableView *friendMsgTable;

public:
    EmailLayer();
    ~EmailLayer();
	static EmailLayer *create();
	static EmailLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
    void initView();
	virtual void doSomething();
	void back(CCObject* obj);
	virtual void keyBackClicked(void);					//�ֻ����ذ�ť
	void reloadData(EmailTableTag tag);
};

class EmailTableHelper: public CCObject, public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{ 
private:
	EmailLayer *father;
	CCSize winSize;
	CCSize tableItemSize;
	int itemsNum;
	EmailTableTag tableTag;
	CCArray *msgArray;
public:
	EmailTableHelper(EmailLayer *fath, int num, EmailTableTag tag);
	~EmailTableHelper();
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
};

#endif /* defined(__Game__PopFrame__) */

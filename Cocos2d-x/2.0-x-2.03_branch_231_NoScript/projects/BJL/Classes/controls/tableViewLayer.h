#ifndef __TABLE_VIEW_LAYER__
#define __TABLE_VIEW_LAYER__

#include "cocos2d.h"
#include "cocos-ext.h"

class tableViewLayer : public cocos2d::CCLayer,cocos2d::extension::CCTableViewDataSource,cocos2d::extension::CCTableViewDelegate 
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();
	static tableViewLayer* tableViewLayerWith1();

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);

	//�����¼� ������ǵ�������Ǹ���ҳ
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	//ÿһ��ĸ߶ȺͿ��
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	//�����б��ÿһ������
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	//һ��������
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	CREATE_FUNC(tableViewLayer);
protected:
private:
	void spriteClickCallBack(cocos2d::CCNode* pNode);
};

#endif //__TABLE_VIEW_LAYER__
#ifndef __Game__ExchangerLayer__
#define __Game__ExchangerLayer__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum ExchangeButtonTag
{
	ExchangeButton_Start = 1
};


#define ExchangeTableFileName "Sprite_ExchangeTableBk"
class ExchangerLayer :public CCLayer, public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{

private:
	CCSize winSize;
	CCSize tableItemSize;
	float tableGapX;
	float tableGapY;
	int itemNum;
	//兑换
	CCTableView *exchangeTable;
	//购买
	int currentType;
	bool buyViewVisible;
	CCSprite *buyBk;
	CCSprite *buyText;
	CCLabelTTF *buyArticleType1;						//类型标签
	CCSprite *buyArticleTypeBk;							//物品类型底框
	CCLabelTTF *buyArticleType2;						//物品类型
	CCLabelTTF *buyArticleNumLabel;						//数量标签
	CCEditBox *buyArticleNum;							//购买数量输入框
	CCLabelTTF *contactLabel;						//联系方式标签
	CCEditBox *contactInput;							//联系方式输入框
	CCMenu *buyMenu;									//购买确定取消菜单
private:
	void initView();
public:
	ExchangerLayer();
	~ExchangerLayer();
	CREATE_FUNC(ExchangerLayer);
	virtual bool init();
	void dismiss(cocos2d::CCObject *obj);
	void setBuyViewVisible(bool flag);
	void pressExchangeButton(cocos2d::CCObject *obj);
	void pressOk(cocos2d::CCObject *obj);
	void pressCancel(cocos2d::CCObject *obj);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);


public:
};
#endif  //__Game__WarningLayler__
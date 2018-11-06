#ifndef __Game__ShopSystemLayer__
#define __Game__ShopSystemLayer__

#include "gui/TabLayer.h"
#include "common/Define.h"
#include "gui/PromptBox.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

enum ShopSystemTableTag
{
	ShopTableTag_Coins = 1,
	ShopTableTag_Article
};

enum ShopSystemBuyButtonTag
{
	BuyButton_Coins = 100,
	BuyButton_Article = 200
};


#define ShopCoinTableFileName "Sprite_ShopCoinTableBk"
#define BuyCoinButtonFileName "Sprite_ShopBuyCoins"
#define ShopArticleTableFileName "Sprite_ShopArticleTableBk"

class ArticleTableHelper:public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource,public CCLayer
{ 
private:
	CCObject *father;
	CCSize winSize;
	CCSize tableItemSize;
	float tableGapX;
	float tableGapY;
	int articleTableItemsNum;
public:
	ArticleTableHelper(CCObject *fath);
	~ArticleTableHelper();
	void buyButton(cocos2d::CCObject *obj);
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
};

class ShopSystemLayer : public TabLayer,public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{

private:
	CCSize winSize;
	CCSize tableItemSize;
	float tableGapX;
	float tableGapY;
	int coinsTableItemsNum;
	CCArray *friendStatusData;
	CCArray *myFriendList;
	CCSprite *maskSprite2;
	CCSprite *maskSprite3;
	//金币
	CCTableView *coinsTable;
	//道具
	CCTableView *articleTable;
	//保险柜
	SCORE score;
	SCORE bankScore;
	CCSprite *bankBk;
	CCLabelTTF *scoreLabel;
	CCLabelTTF *bankScoreLabel;
	CCMenu *bankMenu;
	//购买
	bool buyViewVisible;
	bool depositViewVisible;
	bool withdrawViewVisible;
	bool sendViewVisible;
	CCSprite *buyBk;
	CCSprite *buyText;
	CCLabelTTF *buyArticleType1;						//类型标签
	CCSprite *buyArticleTypeBk;							//物品类型底框
	CCLabelTTF *buyArticleType2;						//物品类型
	CCLabelTTF *buyArticleNumLabel;						//数量标签
	CCEditBox *buyArticleNum;							//购买数量输入框
	CCMenu *buyMenu;									//购买确定取消菜单
	//存款
	CCSprite *depositBk;
	CCSprite *depositText;
	CCLabelTTF *depositNumLabel;						//数量标签
	CCEditBox *depositNum;								//购买数量输入框
	CCLabelTTF *depositPasswordLabel;					//密码标签
	CCEditBox *depositPassword;							//密码输入框
	CCMenu *depositMenu;								//确定取消菜单
	//取款
	CCSprite *withdrawBk;
	CCSprite *withdrawText;
	CCLabelTTF *withdrawNumLabel;						//数量标签
	CCEditBox *withdrawNum;								//购买数量输入框
	CCLabelTTF *withdrawPasswordLabel;					//密码标签
	CCEditBox *withdrawPassword;							//密码输入框
	CCMenu *withdrawMenu;								//确定取消菜单
	//转账
	CCSprite *transferBk;
	CCSprite *transferText;
	CCLabelTTF *transferNickname;						//昵称标签
	CCEditBox *nickname;								//昵称输入框
	CCLabelTTF *transferNumLabel;						//数量标签
	CCEditBox *transferNum;								//购买数量输入框
	CCLabelTTF *transferPasswordLabel;					//密码标签
	CCEditBox *transferPassword;							//密码输入框
	CCMenu *transferMenu;								//确定取消菜单

	//调试框
	PromptBox *promptBox;
private:
	void initView();
public:
	ShopSystemLayer();
	~ShopSystemLayer();
	static ShopSystemLayer *create();
	static ShopSystemLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	virtual void doSomething();
	void refreshView(CCObject *pObject);
	void queryBankInfo();

	void setBuyViewVisible(bool flag);
	void setDepositViewVisible(bool flag);
	void setWithdrawViewVisible(bool flag);
	void setSendViewVisible(bool flag);
	void buyButton(cocos2d::CCObject *obj);
	void depositButton(cocos2d::CCObject *obj);
	void withdrawButton(cocos2d::CCObject *obj);
	void sendButton(cocos2d::CCObject *obj);
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
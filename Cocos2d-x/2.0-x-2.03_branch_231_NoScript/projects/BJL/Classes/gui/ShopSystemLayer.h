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
	//���
	CCTableView *coinsTable;
	//����
	CCTableView *articleTable;
	//���չ�
	SCORE score;
	SCORE bankScore;
	CCSprite *bankBk;
	CCLabelTTF *scoreLabel;
	CCLabelTTF *bankScoreLabel;
	CCMenu *bankMenu;
	//����
	bool buyViewVisible;
	bool depositViewVisible;
	bool withdrawViewVisible;
	bool sendViewVisible;
	CCSprite *buyBk;
	CCSprite *buyText;
	CCLabelTTF *buyArticleType1;						//���ͱ�ǩ
	CCSprite *buyArticleTypeBk;							//��Ʒ���͵׿�
	CCLabelTTF *buyArticleType2;						//��Ʒ����
	CCLabelTTF *buyArticleNumLabel;						//������ǩ
	CCEditBox *buyArticleNum;							//�������������
	CCMenu *buyMenu;									//����ȷ��ȡ���˵�
	//���
	CCSprite *depositBk;
	CCSprite *depositText;
	CCLabelTTF *depositNumLabel;						//������ǩ
	CCEditBox *depositNum;								//�������������
	CCLabelTTF *depositPasswordLabel;					//�����ǩ
	CCEditBox *depositPassword;							//���������
	CCMenu *depositMenu;								//ȷ��ȡ���˵�
	//ȡ��
	CCSprite *withdrawBk;
	CCSprite *withdrawText;
	CCLabelTTF *withdrawNumLabel;						//������ǩ
	CCEditBox *withdrawNum;								//�������������
	CCLabelTTF *withdrawPasswordLabel;					//�����ǩ
	CCEditBox *withdrawPassword;							//���������
	CCMenu *withdrawMenu;								//ȷ��ȡ���˵�
	//ת��
	CCSprite *transferBk;
	CCSprite *transferText;
	CCLabelTTF *transferNickname;						//�ǳƱ�ǩ
	CCEditBox *nickname;								//�ǳ������
	CCLabelTTF *transferNumLabel;						//������ǩ
	CCEditBox *transferNum;								//�������������
	CCLabelTTF *transferPasswordLabel;					//�����ǩ
	CCEditBox *transferPassword;							//���������
	CCMenu *transferMenu;								//ȷ��ȡ���˵�

	//���Կ�
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
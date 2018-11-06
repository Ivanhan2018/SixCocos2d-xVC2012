#ifndef __Game__FriendSystemLayer__
#define __Game__FriendSystemLayer__

#include "gui/TabLayer.h"
#include "cocos-ext.h"
#include "common/Define.h"
USING_NS_CC_EXT;

enum FriendSystemTableTag
{
	TableTag_FriendStatus = 1,
	TableTag_MyFriend
};

class FriendTableHelper:public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{ 
private:
	CCArray *friendStatusData;
public:
	void getFriendStatus();
	FriendTableHelper();
	~FriendTableHelper();
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
};

class FriendSystemLayer : public TabLayer,public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{

private:
	CCSize winSize;
	//���Ѷ�̬
	CCTableView *friendStatusTable;
	//�ҵĺ���
	int currentIndex;
	CCArray *friendData;
	CCTableView *myFriendTable;
	CCSprite *myFriendBk;
	CCMenu *myFriendOperaMenu;
	CCSprite *currentFriendBk;
	//��Ӻ���
	CCLabelTTF *addFriendID;
	CCEditBox *friendAccount;
	CCMenu *addButton;

	//�û���Ϣ
	int friendIndex;
	int photoNum;
	CCSize tableViewCellSize;
	//CCSprite *m_pPlayerPhoto;						//�û�ͷ��
	//CCSprite *photoBk;								//ͷ�񱳾�
	CCLabelTTF *m_pUserName;						//�û�����
	CCLabelTTF *m_pUserSex;							//�û��Ա�
	CCLabelTTF *pUserGold;							//�û����
	CCLabelTTF *pUserRecord;						//�û�ս��
	CCLabelTTF *pUserWinning;						//�û�ʤ��
private:
	void initView();
	void getMyFriendData();
	void addMyFriendData(DWORD dwUserID);
public:
	FriendSystemLayer();
	~FriendSystemLayer();
	static FriendSystemLayer *create();
	static FriendSystemLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	virtual void doSomething();
	void sendButton(cocos2d::CCObject *obj);
	void deleteButton(cocos2d::CCObject *obj);
	void chatButton(cocos2d::CCObject *obj);
	void pressAddButton(cocos2d::CCObject *obj);
	void showFriendInfo(int index);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);


public:
};
#endif  //__Game__WarningLayler__
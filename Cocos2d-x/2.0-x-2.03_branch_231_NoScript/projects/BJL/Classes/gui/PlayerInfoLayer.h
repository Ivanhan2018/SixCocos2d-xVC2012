#ifndef __Game__PlayerInfoLayer__
#define __Game__PlayerInfoLayer__

#include "common/CocosUnits.h"
#include "ConfigMgr/ConfigMgr.h"
#include "ans/AnsString.h"
#include "cocos-ext.h"
#include "gui/TabLayer.h"
#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC_EXT;

#define PHOTO_TABLE_CELL_BUTTON 1
#define SPRITE_MEDAL_L "Sprite_MedalL"
#define SPRITE_MEDAL_A "Sprite_MedalA"
#define MEDAL_NUM 79
#define MEDAL_TABLE_COLUMN 4

class PlayerInfoLayer : public TabLayer,public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{
private:

	CCMenu *pCloseButton;
	CCMenu *pMenuPlayer;
	CCMenu *pMenu1;
	CCMenu *pMenu2;
	CCMenu* mianfeiMenu;
public:
	PlayerInfoLayer();
	~PlayerInfoLayer();
	virtual bool init();
	static cocos2d::CCScene* scene();
	virtual void onEnter();
	//CREATE_FUNC(PlayerInfoLayer);
	static PlayerInfoLayer *create();
	static PlayerInfoLayer *createWithTabItems(CCArray *itemNormalName, CCArray *itemSelectedName);
	virtual void doSomething();
	void pressChangePhoto(CCObject *pObject);

	void showMedalInfo(cocos2d::CCObject *obj, CCControlEvent event);
		 virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	 virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
public:
	void changeUserName(cocos2d::CCObject *obj);
	//void saveChange(cocos2d::CCObject *obj);
	void changeUserPhoto(cocos2d::CCObject *obj);
	void dismiss(cocos2d::CCObject *obj);
	/**��ֹ�ý�������а�ť����**/
	void forbidButtom();
	/**�򿪸ý�������а�ť����**/
	void permitButtom();

	void onSureModifyNickName(CCObject* obj);
	void onModifyNickNameResult(CCObject* obj);
	void onModifyTouxiangResult(CCObject* obj);
	void setTouxiangModifyResult(CCObject* obj);
	void removeTouxiangLayer(CCObject* obj);

	void toFreeLayer(CCObject* obj);

	void rechange(CCObject* obj);

	virtual void keyBackClicked(void);					//�ֻ����ذ�ť
	bool isLegal(string str);

private:
	char* m_szModifyNickName;
	cocos2d::extension::CCEditBox * m_pNickNameInput;
	bool m_bInputNickName;
	const char* m_szMidfyNickNameSave;

	int m_nGenterResult;
	int m_nHeadResult;
	//�û���Ϣ
	int photoNum;
	CCSize tableViewCellSize;
	CCSprite *m_pPlayerPhoto;						//�û�ͷ��
	CCSprite *photoBk;								//ͷ�񱳾�
	CCLabelTTF *m_pUserName;						//�û�����
	CCLabelTTF *m_pUserSex;							//�û��Ա�
	CCLabelTTF *pUserGold;							//�û����
	CCLabelTTF *pUserRecord;						//�û�ս��
	CCLabelTTF *pUserWinning;						//�û�ʤ��
	CCTableView *photoTable;						//ѡ��ͷ��
	//ѫ��
	CCTableView *medalTable;						//ѫ��
	CCLabelTTF *labelMedalInfo;
};

class MedalTableHelper:public cocos2d::extension::CCTableViewDelegate,
	public cocos2d::extension::CCTableViewDataSource
{ 
private:
	CCObject *father;
	CCSize winSize;
	CCSize tableItemSize;
	float tableGapX;
	float tableGapY;
	int articleTableItemsNum;
public:
	MedalTableHelper(CCObject *fath);
	~MedalTableHelper();
	//void showMedalInfo(cocos2d::CCObject *obj);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
};
#endif  //__Game__PlayerInfoLayer__
#ifndef _OperalayerBJL_H_
#define _OperalayerBJL_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "entity/EntityMgr.h"
#include "gui/RoomLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
enum MyEnumItem
{
	m_pCKPX_100EnumItem,
	m_pCKPX_1000EnumItem,
	m_pGRYZ_1WEnumItem,
	m_pGRYZ_10WEnumItem,
	m_pGRYZ_100WEnumItem,
	m_pGRYZ_500WEnumItem,
	m_pGRYZ_1000WEnumItem,
	m_pGRYZ_ChipSpriteWEnumItem,

};
class OperaLayer:public cocos2d::CCLayer
{
public:
	OperaLayer();
	~OperaLayer();
	//创建函数
	static OperaLayer *create();  
	//初始化函数
	bool initOperaLayer();

	void initOpenRaChipTTf();
	void registerWithTouchDispatcher();

	CCMenu *pCloseMenu_100;
	CCMenu *pCloseMenu_1000;
	CCMenu *pCloseMenu_1W;
	CCMenu *pCloseMenu_10W;
	CCMenu *pCloseMenu_100W;
	CCMenu *pCloseMenu_500W;
	CCMenu *pCloseMenu_1000W;

	//点击事件的监听
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); 
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); 
	void ccTouchCancelled(CCTouch* touch, CCEvent* event);

	//显示筹码下注按钮
	void showOperMenut();

	//隐藏
	void remaggerdisflase();
	void menuCloseCallbackboy(CCObject* obj);
	//可以点击Touch
	void initClickTouch();
	//不可以点击并且变色
	void dissUnclickTouch();
	//删除下注精灵筹码
	void resetManagerOper();
	//设置那些按钮可以按
	void update(float delta);
	//获取分数
	void PlacelinitUnClickTouch(CCObject *obl);
	CCSprite *m_pCKPX_100Sprite_1;
	CCSprite *m_pCKPX_100Sprite_2;
	CCSprite *m_pCKPX_1000Sprite_1;
	CCSprite *m_pCKPX_1000Sprite_2;
	CCSprite *m_pGRYZ_1WSprite_1;
	CCSprite *m_pGRYZ_1WSprite_2;
	CCSprite *m_pGRYZ_10WSprite_1;
	CCSprite *m_pGRYZ_10WSprite_2;
	CCSprite *m_pCKPX_100WSprite_1;
	CCSprite *m_pCKPX_100WSprite_2;
	CCSprite *m_pGRYZ_500WSprite_1;
	CCSprite *m_pGRYZ_500WSprite_2;
	CCSprite *m_pGRYZ_1000WSprite_1;
	CCSprite *m_pGRYZ_1000WSprite_2;
	int indexScore0;
	int indexScore1;
	int indexScore2;
	int indexScore3;
	int indexScore4;
	int indexScore5;
	int indexScore6;
	int indexScore7;
	bool IsXIazhuNumber;

	long ManNumberScore;
private:
	//界面大小
	CCSize winSize;
	CCNode * anode;
	CCArray *chipOfMine;
	CCSprite *currentChipSprite;
	CCLabelAtlas *m_pTotalChipValueTTf[8];
	CCSprite *m_pMySpriteNunber[8];

	bool isControl;
	int stasteat;             //判断是那个

	LONGLONG   XIazNumberScore;
	float nodeScale;

	//筹码按钮
	CCMenuItemSprite *m_pCKPX_100Image;
	CCMenuItemSprite *m_pCKPX_1000Image;
	CCMenuItemSprite *m_pGRYZ_1WImage;
	CCMenuItemSprite *m_pGRYZ_10WImage;
	CCMenuItemSprite *m_pGRYZ_100WImage;
	CCMenuItemSprite *m_pGRYZ_500WImage;
	CCMenuItemSprite *m_pGRYZ_1000WImage;

	//筹码显示
	CCSprite *pCKPX_100;
	CCSprite *pCKPX_1000;
	CCSprite *pCKPX_1W;
	CCSprite *pCKPX_10W;
	CCSprite *pCKPX_100W;
	CCSprite *pCKPX_500W;
	CCSprite *pCKPX_1000W;









};

#endif
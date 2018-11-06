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
	//��������
	static OperaLayer *create();  
	//��ʼ������
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

	//����¼��ļ���
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); 
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); 
	void ccTouchCancelled(CCTouch* touch, CCEvent* event);

	//��ʾ������ע��ť
	void showOperMenut();

	//����
	void remaggerdisflase();
	void menuCloseCallbackboy(CCObject* obj);
	//���Ե��Touch
	void initClickTouch();
	//�����Ե�����ұ�ɫ
	void dissUnclickTouch();
	//ɾ����ע�������
	void resetManagerOper();
	//������Щ��ť���԰�
	void update(float delta);
	//��ȡ����
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
	//�����С
	CCSize winSize;
	CCNode * anode;
	CCArray *chipOfMine;
	CCSprite *currentChipSprite;
	CCLabelAtlas *m_pTotalChipValueTTf[8];
	CCSprite *m_pMySpriteNunber[8];

	bool isControl;
	int stasteat;             //�ж����Ǹ�

	LONGLONG   XIazNumberScore;
	float nodeScale;

	//���밴ť
	CCMenuItemSprite *m_pCKPX_100Image;
	CCMenuItemSprite *m_pCKPX_1000Image;
	CCMenuItemSprite *m_pGRYZ_1WImage;
	CCMenuItemSprite *m_pGRYZ_10WImage;
	CCMenuItemSprite *m_pGRYZ_100WImage;
	CCMenuItemSprite *m_pGRYZ_500WImage;
	CCMenuItemSprite *m_pGRYZ_1000WImage;

	//������ʾ
	CCSprite *pCKPX_100;
	CCSprite *pCKPX_1000;
	CCSprite *pCKPX_1W;
	CCSprite *pCKPX_10W;
	CCSprite *pCKPX_100W;
	CCSprite *pCKPX_500W;
	CCSprite *pCKPX_1000W;









};

#endif
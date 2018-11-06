//
//  roomLayer.h
//  Game
//
//  Created by zhouwei on 13-6-17.
//
//

#ifndef __Game__roomLayer__
#define __Game__roomLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MenuLayer.h"
#include "WarningLayer.h"
#include "BaseLayer.h"
#include "GroupSprite.h"
#include "CustomerServiceLayer.h"
#include "PromptBox.h"
#include "gui/FMGameItemLayer.h"


#define MASKD_TAG 20          //���Ͽ���ť��TAG
#define MASKDMENU_TAG 21      //���Ͽ��򶯻�Ч��TAG
#define PAIDUI_TAG 22         //�ŶӾ���TAG

//class RoomUserInfo;
//class LevelInfo;
//class PopFrame;
//class tableViewLayer;

enum ROOM_TYPE
{
	ROOM_TYPE_Super = 0,
	ROOM_TYPE_Seniy,
	ROOM_TYPE_Middle,
	ROOM_TYPE_Primary
	
};

enum ROOM_LAYER_LEVEL
{
	ROOM_LAYER_LEVEL_HOBBY,
	ROOM_LAYER_LEVEL_GAMETYPE,
	ROOM_LAYER_LEVEL_GAMEROOM
};

class RoomLayer : public BaseLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(RoomLayer);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    RoomLayer();
    ~RoomLayer();
public:

	void toMenu(CCObject* obj);							//�˵�
	void rechangeLittleButton(CCObject* obj);			//����С��ť
	void huodong(CCObject * obj);						//�
	void geTCHARge(CCObject * obj);                     //�컰��
	void onStart(ROOM_TYPE index);               //���Ͽ���

	//���²˵�����
	void toFriend(CCObject* obj);						//����ϵͳ
	void toShop(CCObject* obj);							//��Ϸ�̳�
	void onQuickStart(CCObject *pSender);				//������Ϸ          add by wangjun
	void mission(CCObject* obj);						//����
	void toRank(CCObject* obj);							//����

	//�м�˵�
	void toExchange(CCObject* obj);							//�һ�
	void toLuckyDraw(CCObject* obj);						//���˳齱
	void toVIP(CCObject* obj);						//vip

	//����˵�����
	void rechange(CCObject* obj);						//����
	void signIn(CCObject* obj);						//ÿ��ǩ��
	void setting(CCObject* obj);						//����
	void toHelp(CCObject* obj);							//��Ϸ����
	void message(CCObject* obj);						//��Ϣ
	void pressBack(CCObject* obj);						//����

	void showPlayerInformation(CCObject *obj);          //������Ϣ

	//��Ϸ��ť
	void DDZItemCallback(CCObject* pSender);					//������
	void ShakeItemCallback(CCObject* pSender);					//ҡҡ��
	void Lucky28ItemCallback(CCObject* pSender);                //����28
	void NiuniuItemCallback(CCObject* pSender);                 //ţţ
	void ZajinHuaItemCallback(CCObject* pSender);               //ը�� 

	//�м�˵�����
	void toNormalGame(CCObject* obj);					//��ͨ��
	void toOtherGame(CCObject* obj);					//���ը����

	//�м�˵�����
	void toPrimaryGame(CCObject* obj);					//������
	void toMiddleGame(CCObject* obj);					//�м���
	void toSeniyGame(CCObject* obj);					//�߼���
	void toSuperGame(CCObject* obj);					//������

	void matchBackButton(CCObject* obj);				//��������
	void gameBackButton(CCObject* obj);				    //��������

	//��ϵ�ͷ�
	void toPhoneKefu(CCObject* obj);					//��ϵ�ͷ�

	void automaticLogin(bool automatic,bool overResgist = false);				//�Զ���¼,ע��

	void onLoginFinish();								//��½���
	void onLoginFaild(CCObject* obj);					//��½ʧ��

	string createAccount();								//�����˺�
	string createPassword();							//��������
	void onRegistSucc(CCObject* obj);					//ע��ɹ�
	void onRegisterFaild(CCObject* obj);				//ע��ʧ��

	//�Ͻ𿨳�ֵ���
	void onlandcardResult(CCObject* obj);
	//�绰����ֵ���
	void onPhoneCardResult(CCObject* obj);

	void onLinkResult(CCObject* obj);
    //void shangcheng(CCObject * obj);                      //�̳�
	
    //void changeSoundState(CCObject * obj);              //���ֿ���
    //void backPreScene(CCObject * obj);                  //�����ϸ�����
    
 //   void onLoingFinish();                               //����С��Ϸ
 //   void checkUserCannelQueueUp(float dt);              //����û��Ƿ�ȡ���Ŷ�
 //   void showTable(float dt);                                   //��ʾ10������
 //   void onMatch(CCObject* obj);                                     //��ʾƥ���
 //   void onUpdateScore(CCObject* obj);
 //   void onPesent(CCObject* obj);                       //���ͻص�
 //   void onCharge(CCObject* obj);                       //��ȡ���ѽ�һص�
 //   void showNotice();                                  //��ʾ����
 //   void onBankrupt(CCObject* obj);                     //�Ʋ��ص�
 //   void onHideLevel(float dt);                        //�ȼ���������
 //   void onChargeTips(CCObject* obj);                   //��ֵ��ʾ
	//void onChangeGame(CCObject* obj);					//�л���Ϸ

	void showLoginAward();								//��ʾ������½����
	void closeLoginAward();
	void showSelectHead(CCObject* obj);								//ѡ��ͷ��

	void permitButtonClick();							//����ť��
	void forbidButtonClick();							//��ֹ��ť��

	void showMoveingLabelTips(const char* str);			//��ʾƮ����ʾ	

	void onChange(CCObject* obj);						//���ͣ��ص�
	void onPesent(CCObject* obj);						//�컰�ѻص�

	void onUpdateScoreAndGoldEgg(CCObject* obj);		//ˢ�½�Һͻ��ѵ�

	void onRefshTotalNum(CCObject* obj);				//ˢ������

	virtual void keyBackClicked(void);					//�ֻ����ذ�ť

	void setGoingRoomLayer();

	void gameToBankrupt(bool isBankrupt);			//С��Ϸ���ش������Ƿ��Ʋ�

	void showDailyGetCoins(CCObject* obj);			//��ʾÿ������
	void showDailyGetCoinsResult(CCObject* obj);	//ÿ����ȡ�ȼý���
	void setRoomLayerLevel(ROOM_LAYER_LEVEL level);
private:
	//void getUserInfo();
	//void createTable();
private:
	MenuLayer  *mMenuLayer;
	CCLayer *pWarningLayer;
	CustomerServiceLayer *pCustomerService;
private:
	bool       mMenuCloseOrOpen;
	int       isGoingRoomLayer;
	
private:
	CCSize winSize;
	int roomLevel;
	CCMenu* m_pPlayerMenu;			//������Ϣ��ť
	CCMenu* m_pButtonMenu;			//���°�ť
	CCMenu* m_pStartMenu;			//���ٿ�ʼ��ť
	CCMenu* m_pOtherMenu;				//���水ť
	CCMenu* m_pTopMenu;				//���水ť
	GameItemLayer* m_pMiddleHobbyMenu;		//�м䰴ť��ѡ����Ϸ��
	CCMenu* m_pMiddleMenu;			//�м䰴ť����ͨ���
	CCMenu* m_pMiddleMenu2;			//�м䰴ť2�����иߣ�
	//CCMenu* m_pKefuMenu;			//��ϵ�ͷ���ť
	//CCMenu* m_pchongSMenu;			//С���Ұ�ť
	//CCMenu* m_pMatchBack;			//ѡ�񳡴�ʱ����
	//CCMenu* m_pGameBack;			//ѡ����Ϸʱ����

	CCMenuItemSprite* pPlayerMenuSprite;		//����ͷ��

	int m_nGameType;						//��Ϸ���� ����ʲô��

	CCLabelTTF* m_pUserScore;				//���
	CCLabelTTF* m_pUserPhonePoint;

	CCMenuItemSprite * m_pHappyS;

	CCMenuItemSprite * m_pPrimaryS;
	CCMenuItemSprite * m_pMiddleS;
	CCMenuItemSprite * m_pSeniyS;
	CCMenuItemSprite * m_pSuperS;

	CCSprite* m_MessageNumBack;
	CCLabelTTF* m_MessageNum;

	CCSprite* m_UMMessageNumBack;
	CCLabelTTF* m_UMMessageNum;

	PromptBox* m_pRuberBox;
//    tagGlobalUserData * userInfo;
//    //����״̬
//    bool soundState;
//    CCMenuItemSprite * soundMenuSprite;
//    CCLabelTTF * tishi;
//    RoomTimer * roomTimer;
//    
//    RoomUserInfo* m_pUserInfo;
////    LevelInfo*    m_pLevelInfo;
//    PopFrame*   m_pPopFrame;
//    CCSprite*   m_pLevelSprite;
//    int m_nBGMID;
//
//	GameSelectView* m_pViewLayer;
//	CCMenu*		   m_pBeginPlayCardMenu;			//���Ͽ���
//	CCSprite*	   m_pLightBack;					//�ƹⱳ��
//	RoomTable*	   m_pTable[10];					//����
//
//	int m_nGameKindId;								//��Ϸ����
};

#endif /* defined(__Game__roomLayer__) */

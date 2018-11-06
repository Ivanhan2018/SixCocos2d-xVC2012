/***********************************************
Name��SIX_SceneGame
Desc����Ϸ����
Auth��Cool.Cat@2013-09-28
***********************************************/
#pragma once
#include <SIX_UIScene.h>
#include <SIX_Typedef.h>
#include <SIX_ExpandLayer.h>
#include <SIX_CountDownBatchNode.h>
#include "SIX_PopWndPlayerInfo.h"
#include "SIX_PopWndMessage.h"
#include "SIX_TipsPopWnd.h"
#include "SIX_PlayerMgr.h"

enum {
	BTN_MENU			=	1,
	//BTN_MENU_CLOSE,
	//BTN_MENU_RETURN,
	//BTN_MENU_CHANGETABLE,
	BTN_CARDTYPE_BT		=	5,
	BTN_CHAT_BT			=	6,
	BTN_SHOW_CHAT		=	7,

	BTN_PLAYER1_LOGO	=	100,
	BTN_PLAYER2_LOGO	=	200,
	BTN_PLAYER3_LOGO	=	300,
	BTN_PLAYER4_LOGO	=	400,
	// �Լ�
	BTN_PLAYER5_LOGO	=	500,
	BTN_PLAYER6_LOGO	=	600,

	// ����
	SPRITE_TABLE		=	995,
	// ϴ��
	NODE_SHUFFLE		=	996,
	// ����
	NODE_DICE			=	997,
	//// ׼��
	//SPRITE_READY		=	998,
	// ��ע
	SPRITE_CHIP			=	999,

	// ׼��
	BTN_READY			=	1000,
	// ����ׯ
	BTN_RUB_CANCEL		=	2000,
	// ��ׯ
	BTN_RUB_SUBMIT		=	3000,
	// ��ע
	BTN_CHIPIN1			=	4000,
	BTN_CHIPIN2			=	5000,
	BTN_CHIPIN3			=	6000,

	// ɢ��ɱ����С
	BTN_KILL_1			=	7000,
};

// ���UI�ṹ
typedef struct tagPlayerZoneInfo{
	// ������Ϣ���ڵ�
	CCNode *wRoot;
	// ������Ϣ�ڵ�
	CCControlButton *wPlayerInfo;
	// �ǳ�
	CCLabelTTF *wNickName;
	// ͷ��
	CCSprite *wFaceLogo;
	// ���
	CCLabelTTF *wMoney;
	// ׯ��
	CCSprite *wBanker;

	// �ƶѽڵ�
	SIX_CardSuit *wCardSuit;
	// ��1
	SIX_CardItem *wCardItem1;
	// ��2
	SIX_CardItem *wCardItem2;
	// ��3
	SIX_CardItem *wCardItem3;

	// ͳ�����
	CCNode *wStatsPanel;
	// �Ƶ�
	CCSprite *wStatsPoint;
	CCSprite *wStatsDot;
	// ����
	CCSprite *wStats3Gong;
	// ը��
	CCSprite *wStatsBomb;

	// �������
	CCSprite *wChipPanel;
	// ����
	CCSprite *wChipSprite;
	// ����
	CCLabelTTF *wChipPoint;
} PLAYER_ZONE_INFO;

typedef struct tagDelayInfo {
	int idx;
	float delay;
	float offset;
	tagDelayInfo()
	{
		idx = 0;
		delay = 0.0f;
		offset = 0.0f;
	}
} DELAY_INFO;

class SIX_SceneGame : public SIX_UIScene, public SIX_InformationDelegate
{
public:
	SIX_SceneGame()
	{
	}

	virtual ~SIX_SceneGame();
public:
	static SIX_SceneGame* scene();
	virtual bool init();
	void update(float dt);

    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType);

    virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
    virtual void onExit();
	// �رհ�ť �� �˳�����ʱ����
	// Cool.Cat
	virtual void onCloseExit();
	virtual void OnNotifyCloseWndClicked(CCObject *pObj);
	virtual void OnShowInformation(CMD_ChatContent *pChat);
	static bool OnExitBtn();

	void resetUI(bool bShow=false,bool bClearPlayerZone=true);

#ifdef WIN32
	int OnAccelerometerKeyHook(UINT message,WPARAM wParam,LPARAM lParam);
#endif;
private:
	void setVisibleByBtnMask(bool bVisible=true);
	void setVisibleByCardType(bool bVisible=true);
	void doEvents(CCObject* pSender, CCControlEvent event);
	void ProgressDown(CCNode *pNode);

	bool IsMySelf(unsigned int idx);
	void checkHaveMsgNoShowFunc();

	// ����Ϊ�ƾ����UI����
	// -------------------------------
	// ����UI�����ƶѵ�SIX_CardPlay
	int ParseAndBindUIToCardPlay();
public:
	// ��ʾϴ����
	void showNodeShuffle(bool bShow=true);
	// ��ʾ������
	void showNodeDice(bool bShow=true);
	//// ��ʾ׼����ʾ
	//void showSprReady(bool bShow=true);
	// ��ʾ׼����ť
	void showBtnReady(bool bShow=true);
	// ��ʾ��ׯ��ť
	void showBtnRubBanker(bool bShow=true);
	// ��ʾ��ע��ʾ
	void showSprChip(bool bShow=true);
	// ��ʾ��ע��ť
	void showBtnChipin(bool bShow=true);
	// ��ʾɢ��ɱ����С��ť
	void showBtnKill(bool bShow=true);

	// ��ʾ��ׯ��ʾ
	void showTipRubBanker(unsigned int playerIdx,bool isRub,bool isVisible);
	// ��ʾʤ����ʾ
	void showTipStats(unsigned int playerIdx,unsigned int point=0,bool isWin=false,bool bPointShow=false,bool b3GongShow=false,bool bBombShow=false);

	// �ƶ�ׯ�����ӵ�ϴ����
	void MoveBankerFlagToShuffleArea(TChairID wBankerID);
	// �ƶ�ׯ�����ӵ�ׯ������
	void MoveBankerFlagToBankerArea(TChip c1,TChip c2,TChip c3);

	// ��ʾ�����Ӷ���
	void showAnimateThrowDice(unsigned int dice[],unsigned int count,long long *pDat);
	void OnDiceSpinDone(CCNode *pNode);
	void OnDiceDropDone(CCNode *pNode);
	void showSingleDice(unsigned char point,CCPoint dropStart,CCPoint dropEnd,long long *pData,bool carryData=false);

	// ��ע�ص�
	void OnShowCanChipDone(CCNode *pNode,void *pData);

	// ��ʾϴ�Ʒ��ƶ���
	void showAnimateShuffleAndDealCard();
	// ����ϴ�ƶ���
	void showSingleShuffleCard(CCNode *pNode,void *pData);
	// ��ʾ���ƶ���
	void showAnimateDealCard(CCNode *pNode,void *pData);
	// �����ƶ���
	void showSingleDealCard(CCNode *pNode,void *pData);
	// ��������ɻص�
	void OnDealCardDone(CCNode *pNode);
	// ����ϴ��������ʾ�Ƶ�(�ص�)
	void hideNodeShuffleAndShowCardPoint();

	// ��ʾ��ע����
	void showAnimateChip(unsigned int playerIdx,unsigned int chippoint);
	void OnChipDone(CCNode *pNode);

	// ��ʾ���㶯��
	void showAnimateSettleAccounts();

	// �����м�����(Ĭ��˳ʱ��)
	void doSortCustomInfo(SIX_TVector<CUSTOM_INFO*> *customVec,bool bClockwise=true);
	// ��ʾ���㶯��(���հ�)
	void showAnimateSettleAccountsFinal();
	// ׯ������/����
	void onBankerShowCard();
	// �м�����/����
	void onCustomShowCard(CCNode *pNode);

	// �мҽ���ص�(��)
	void OnCustomLoseSettleAccounts(CCNode *pNode);
	// �мҽ���ص�(Ӯ)
	void OnCustomWinSettleAccounts(CCNode *pNode);

	// �мҽ��㶯���ص�
	void OnCustomSettleAccountsChipMoveDone(CCNode *pNode);
	// �Ƴ���̬����(
	void OnChipRemove(CCNode* pNode);

	// ��������
	void OnClearData();

	// ��ʾ�û���Ϣ��
	void showPlayerZoneShow(unsigned int,bool bShow=true);
	// �����û���Ϣ���ǳ�
	void setPlayerZoneNickName(unsigned int,const char *name);
	// �����û���Ϣ��ͷ��
	void setPlayerZoneFaceLogo(unsigned int, long long llSysLogoID);
	// �����û���Ϣ������
	void setPlayerZoneChip(unsigned int,unsigned int);
	// �����û�Ϊׯ��
	void showPlayerRubBanker(unsigned int,bool bShow=true);

	// ����ָ����Ҹ�����Ϣ����͸����
	void setPlayerZoneOpacity(unsigned int,unsigned char);

	//add by Ivan_han 20131013
	PLAYER_ZONE_INFO *getPlayerZone(unsigned int idx);

	// ��ʾ����
	void showCardSuit(unsigned int,bool bShow=true);
	// ��ʾ��ʵ��
	void showCardItem(unsigned int playerIdx,unsigned int cardIdx,bool bShow=true);
	// ��ʾͳ�ƽ��
	void showStatsPanel(unsigned int playerIdx,unsigned int point,bool isWin,bool bPointShow=true,bool b3GongShow=false,bool bBombShow=false);
	// ��ʾ����ʤ��
	void showStatsMySelfWinOrLose(float delay,bool bWin=true);
	// ʤ�������ص�
	void OnWinOrLoseDone();

	// �����Լ�/�Է�������(����/��С��ɫ)ƫ��
	CCPoint caclCardFrontOffset(unsigned int point,CARD_TYPE type,bool isFaceBig=true,bool isMySelf=true);
	// �����Ƶ�/��С��ɫ
	void SetCardPointAndType(unsigned int playerIdx,unsigned int cardIdx,unsigned char point,CARD_TYPE type);
	// ������ע��ť������ע��������
	void SetBtnChipPoint(TChip chip1point=0,TChip chip2point=0,TChip chip3point=0);
	// ��ʾ/��������
	void SetCardFrontShow(unsigned int playerIdx,unsigned int cardIdx,bool bShow=true);
	// ���ó�����������ʾ
	void SetChipPanelNumber(unsigned int playerIdx,unsigned chipPoint,bool bShow=true);

	// ��ʾ����ʱ
	void showCountDown(bool bShow,int delay=0);
	void doTimeIsUp(CCNode *pNode,void *params);

	SIX_PopWndMessage * &getWndMessage() { return m_pWndMsg; }

	bool showAllowChangeToHallTips();
private:
	CCProgressTimer *pCountDown;
	SIX_PopWndPlayerInfo *pWndPlayerInfo;
	SIX_PopWndMessage *m_pWndMsg;
	CCLayerColor *pBackground;
	// ����
	CCSprite *pNodeTable;
	// ϴ����
	CCNode *pNodeShuffle;
	// ������
	CCNode *pNodeDice;
	//// ׼����ʾ
	//CCScale9Sprite *pSpriteReady;
	// ��ע��ʾ
	CCScale9Sprite *pSpriteChip;
	// ׼����ť
	CCControlButton *pBtnReady;
	// ��ׯ��ť
	CCControlButton *pBtnRubCancel;
	CCControlButton *pBtnRubSubmit;
	// ��ע��ť
	CCControlButton *pBtnChipin1;
	CCControlButton *pBtnChipin2;
	CCControlButton *pBtnChipin3;
	// ɢ��ɱ����С��ť
	CCControlButton *pBtnKill;
	// ����ʱ
	SIX_CountDownBatchNode *pCountDownBatchNode;
	CCPoint m_ptCartTypeExplanation;
	// ������ʾ����Ϸ������ſ��Է��ش�����
	SIX_TipsPopWnd *m_pTipsPopWnd;
	// ������ʾ����ʼ�������ơ�
	SIX_TipsPopWnd *m_pTipsShowCard;
};
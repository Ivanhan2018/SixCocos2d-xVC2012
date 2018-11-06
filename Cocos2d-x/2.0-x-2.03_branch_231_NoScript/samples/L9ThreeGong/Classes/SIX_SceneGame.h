/***********************************************
Name：SIX_SceneGame
Desc：游戏场景
Auth：Cool.Cat@2013-09-28
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
	// 自己
	BTN_PLAYER5_LOGO	=	500,
	BTN_PLAYER6_LOGO	=	600,

	// 桌子
	SPRITE_TABLE		=	995,
	// 洗牌
	NODE_SHUFFLE		=	996,
	// 骰子
	NODE_DICE			=	997,
	//// 准备
	//SPRITE_READY		=	998,
	// 下注
	SPRITE_CHIP			=	999,

	// 准备
	BTN_READY			=	1000,
	// 不抢庄
	BTN_RUB_CANCEL		=	2000,
	// 抢庄
	BTN_RUB_SUBMIT		=	3000,
	// 下注
	BTN_CHIPIN1			=	4000,
	BTN_CHIPIN2			=	5000,
	BTN_CHIPIN3			=	6000,

	// 散仙杀大赔小
	BTN_KILL_1			=	7000,
};

// 玩家UI结构
typedef struct tagPlayerZoneInfo{
	// 个人信息根节点
	CCNode *wRoot;
	// 个人信息节点
	CCControlButton *wPlayerInfo;
	// 昵称
	CCLabelTTF *wNickName;
	// 头像
	CCSprite *wFaceLogo;
	// 金币
	CCLabelTTF *wMoney;
	// 庄家
	CCSprite *wBanker;

	// 牌堆节点
	SIX_CardSuit *wCardSuit;
	// 牌1
	SIX_CardItem *wCardItem1;
	// 牌2
	SIX_CardItem *wCardItem2;
	// 牌3
	SIX_CardItem *wCardItem3;

	// 统计面板
	CCNode *wStatsPanel;
	// 牌点
	CCSprite *wStatsPoint;
	CCSprite *wStatsDot;
	// 三公
	CCSprite *wStats3Gong;
	// 炸弹
	CCSprite *wStatsBomb;

	// 筹码面板
	CCSprite *wChipPanel;
	// 筹码
	CCSprite *wChipSprite;
	// 点数
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
	// 关闭按钮 或 退出进程时触发
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

	// 以下为牌局相关UI操作
	// -------------------------------
	// 解析UI并绑定牌堆到SIX_CardPlay
	int ParseAndBindUIToCardPlay();
public:
	// 显示洗牌区
	void showNodeShuffle(bool bShow=true);
	// 显示骰子区
	void showNodeDice(bool bShow=true);
	//// 显示准备提示
	//void showSprReady(bool bShow=true);
	// 显示准备按钮
	void showBtnReady(bool bShow=true);
	// 显示抢庄按钮
	void showBtnRubBanker(bool bShow=true);
	// 显示下注提示
	void showSprChip(bool bShow=true);
	// 显示下注按钮
	void showBtnChipin(bool bShow=true);
	// 显示散仙杀大赔小按钮
	void showBtnKill(bool bShow=true);

	// 显示抢庄提示
	void showTipRubBanker(unsigned int playerIdx,bool isRub,bool isVisible);
	// 显示胜负提示
	void showTipStats(unsigned int playerIdx,unsigned int point=0,bool isWin=false,bool bPointShow=false,bool b3GongShow=false,bool bBombShow=false);

	// 移动庄家骰子到洗牌区
	void MoveBankerFlagToShuffleArea(TChairID wBankerID);
	// 移动庄家骰子到庄家区域
	void MoveBankerFlagToBankerArea(TChip c1,TChip c2,TChip c3);

	// 显示丢骰子动画
	void showAnimateThrowDice(unsigned int dice[],unsigned int count,long long *pDat);
	void OnDiceSpinDone(CCNode *pNode);
	void OnDiceDropDone(CCNode *pNode);
	void showSingleDice(unsigned char point,CCPoint dropStart,CCPoint dropEnd,long long *pData,bool carryData=false);

	// 下注回调
	void OnShowCanChipDone(CCNode *pNode,void *pData);

	// 显示洗牌发牌动画
	void showAnimateShuffleAndDealCard();
	// 单牌洗牌动画
	void showSingleShuffleCard(CCNode *pNode,void *pData);
	// 显示发牌动画
	void showAnimateDealCard(CCNode *pNode,void *pData);
	// 发单牌动画
	void showSingleDealCard(CCNode *pNode,void *pData);
	// 发单牌完成回调
	void OnDealCardDone(CCNode *pNode);
	// 隐藏洗牌区并显示牌点(回调)
	void hideNodeShuffleAndShowCardPoint();

	// 显示下注动画
	void showAnimateChip(unsigned int playerIdx,unsigned int chippoint);
	void OnChipDone(CCNode *pNode);

	// 显示结算动画
	void showAnimateSettleAccounts();

	// 结算闲家排序(默认顺时针)
	void doSortCustomInfo(SIX_TVector<CUSTOM_INFO*> *customVec,bool bClockwise=true);
	// 显示结算动画(最终版)
	void showAnimateSettleAccountsFinal();
	// 庄家亮牌/牌型
	void onBankerShowCard();
	// 闲家亮牌/牌型
	void onCustomShowCard(CCNode *pNode);

	// 闲家结算回调(输)
	void OnCustomLoseSettleAccounts(CCNode *pNode);
	// 闲家结算回调(赢)
	void OnCustomWinSettleAccounts(CCNode *pNode);

	// 闲家结算动画回调
	void OnCustomSettleAccountsChipMoveDone(CCNode *pNode);
	// 移除动态筹码(
	void OnChipRemove(CCNode* pNode);

	// 清理数据
	void OnClearData();

	// 显示用户信息区
	void showPlayerZoneShow(unsigned int,bool bShow=true);
	// 设置用户信息区昵称
	void setPlayerZoneNickName(unsigned int,const char *name);
	// 设置用户信息区头像
	void setPlayerZoneFaceLogo(unsigned int, long long llSysLogoID);
	// 设置用户信息区筹码
	void setPlayerZoneChip(unsigned int,unsigned int);
	// 设置用户为庄家
	void showPlayerRubBanker(unsigned int,bool bShow=true);

	// 设置指定玩家个人信息区域透明度
	void setPlayerZoneOpacity(unsigned int,unsigned char);

	//add by Ivan_han 20131013
	PLAYER_ZONE_INFO *getPlayerZone(unsigned int idx);

	// 显示牌区
	void showCardSuit(unsigned int,bool bShow=true);
	// 显示牌实体
	void showCardItem(unsigned int playerIdx,unsigned int cardIdx,bool bShow=true);
	// 显示统计结果
	void showStatsPanel(unsigned int playerIdx,unsigned int point,bool isWin,bool bPointShow=true,bool b3GongShow=false,bool bBombShow=false);
	// 显示自身胜负
	void showStatsMySelfWinOrLose(float delay,bool bWin=true);
	// 胜负结束回调
	void OnWinOrLoseDone();

	// 计算自己/对方的牌面(点数/大小花色)偏移
	CCPoint caclCardFrontOffset(unsigned int point,CARD_TYPE type,bool isFaceBig=true,bool isMySelf=true);
	// 设置牌点/大小花色
	void SetCardPointAndType(unsigned int playerIdx,unsigned int cardIdx,unsigned char point,CARD_TYPE type);
	// 设置下注按钮区可下注筹码数量
	void SetBtnChipPoint(TChip chip1point=0,TChip chip2point=0,TChip chip3point=0);
	// 显示/隐藏牌面
	void SetCardFrontShow(unsigned int playerIdx,unsigned int cardIdx,bool bShow=true);
	// 设置筹码数量及显示
	void SetChipPanelNumber(unsigned int playerIdx,unsigned chipPoint,bool bShow=true);

	// 显示倒计时
	void showCountDown(bool bShow,int delay=0);
	void doTimeIsUp(CCNode *pNode,void *params);

	SIX_PopWndMessage * &getWndMessage() { return m_pWndMsg; }

	bool showAllowChangeToHallTips();
private:
	CCProgressTimer *pCountDown;
	SIX_PopWndPlayerInfo *pWndPlayerInfo;
	SIX_PopWndMessage *m_pWndMsg;
	CCLayerColor *pBackground;
	// 桌子
	CCSprite *pNodeTable;
	// 洗牌区
	CCNode *pNodeShuffle;
	// 骰子区
	CCNode *pNodeDice;
	//// 准备提示
	//CCScale9Sprite *pSpriteReady;
	// 下注提示
	CCScale9Sprite *pSpriteChip;
	// 准备按钮
	CCControlButton *pBtnReady;
	// 抢庄按钮
	CCControlButton *pBtnRubCancel;
	CCControlButton *pBtnRubSubmit;
	// 下注按钮
	CCControlButton *pBtnChipin1;
	CCControlButton *pBtnChipin2;
	CCControlButton *pBtnChipin3;
	// 散仙杀大赔小按钮
	CCControlButton *pBtnKill;
	// 倒计时
	SIX_CountDownBatchNode *pCountDownBatchNode;
	CCPoint m_ptCartTypeExplanation;
	// 文字提示“游戏结束后才可以返回大厅”
	SIX_TipsPopWnd *m_pTipsPopWnd;
	// 文字提示“开始依次亮牌”
	SIX_TipsPopWnd *m_pTipsShowCard;
};
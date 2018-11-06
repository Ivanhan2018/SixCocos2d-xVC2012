//  [3/19/2014 wucan]
#ifndef  __CC_SCENEVIEW_WUCAN_
#define __CC_SCENEVIEW_WUCAN_
#include "cocos2d.h"
#include "SceneData.h"
#include "ViewHandCard.h"
#include "CardTableLayer.h"
#include "ViewMenuLayer.h"
#include "ViewCardEffect.h"
#include "Settlement.h"
#include "ViewTask.h"
#include "SetUpLayer.h"
#include "VoiceAndFace.h"
#include "DialogLayer.h"
#include "SoundControl.h"

#include "GameTaskCommon.h"

USING_NS_CC;

class SceneView:public CCNode
{
public:
	SceneView(void);
	~SceneView(void);
	CREATE_FUNC(SceneView);
	virtual bool init();
	void OnMessage(CCObject* obj);
	void receiveMenuClickCallfunc(CCObject * obj);	//--菜单按钮点击后的回调
	void onBankrupt(CCObject * obj);							//--游戏破产返回大厅
	void onLlinkOFF(float ft);							//--网络断开返回大厅
	void wangZha(CCObject *obj);
	void SetCloseCall( CCObject *obj );

	//--功能函数
	int  cAddScoreUseid;   //庄家id

	bool ScoreUseidbool;
private:
	void startGameDeal();
	void startGameViewDeal(CCInteger* _data);
	void onBackTaskDeal(CCInteger* _data);
	void addViewDeal(CCInteger* _data);
	void sendCardDeal(CCInteger* _data);
	void openCardDeal(CCInteger* _data);
	void landLordDeal(CCInteger* _data);
	void timeConreolDral(CCInteger* _data);
	void outCardDeal(CCInteger* _data);
	void passCardDeal(CCInteger* _data);
	void gameOverDeal(CCInteger* _data);
	void timeCallBackDeal(CCInteger* _data);
	void timeAgencyDeal(float ft);
	
	void Strameobjet(CCObject *obj);

	void StrameNumberbjet(CCObject *obj);

	int longNumberuserInforID;   //庄家Id
private:
	ViewCardEffect*    m_effectView;
	CC_SYNTHESIZE(ViewMenuLayer *,m_menuLayer,MenuLayer);
//	SceneLogic *logic;
	Settlement * m_settlementNode;
	VoiceAndFace*     m_face;
	GameTaskCommon* m_gameTask;
	CCLayer * m_dialogLayer;

	int						m_AgencyNum;				//--玩家没打轮数
	bool						m_isAgency;						//--机器人代打

	//--用于游戏托管
	Game_State			m_gameStae;					//--游戏状态
	int						m_timeKey;
	bool						m_isLandLord;					//--第一次叫地主
	unsigned int m_userOutCardState;				//用户出牌状态（//地主出牌且不能明牌，地主首轮出牌能明牌，上轮最大方，现在第一轮出牌）
	unsigned int g_tableConsume;					//牌桌消费

};
#endif

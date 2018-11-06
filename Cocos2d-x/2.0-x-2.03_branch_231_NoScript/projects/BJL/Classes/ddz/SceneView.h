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
	void receiveMenuClickCallfunc(CCObject * obj);	//--�˵���ť�����Ļص�
	void onBankrupt(CCObject * obj);							//--��Ϸ�Ʋ����ش���
	void onLlinkOFF(float ft);							//--����Ͽ����ش���
	void wangZha(CCObject *obj);
	void SetCloseCall( CCObject *obj );

	//--���ܺ���
	int  cAddScoreUseid;   //ׯ��id

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

	int longNumberuserInforID;   //ׯ��Id
private:
	ViewCardEffect*    m_effectView;
	CC_SYNTHESIZE(ViewMenuLayer *,m_menuLayer,MenuLayer);
//	SceneLogic *logic;
	Settlement * m_settlementNode;
	VoiceAndFace*     m_face;
	GameTaskCommon* m_gameTask;
	CCLayer * m_dialogLayer;

	int						m_AgencyNum;				//--���û������
	bool						m_isAgency;						//--�����˴���

	//--������Ϸ�й�
	Game_State			m_gameStae;					//--��Ϸ״̬
	int						m_timeKey;
	bool						m_isLandLord;					//--��һ�νе���
	unsigned int m_userOutCardState;				//�û�����״̬��//���������Ҳ������ƣ��������ֳ��������ƣ�������󷽣����ڵ�һ�ֳ��ƣ�
	unsigned int g_tableConsume;					//��������

};
#endif

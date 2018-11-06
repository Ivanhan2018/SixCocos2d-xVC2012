//  [3/19/2014 wucan]
#ifndef		__CC_SCENELOGIC_WUCAN__
#define		 __CC_SCENELOGIC_WUCAN__
#include "cocos2d.h"
#include "SceneData.h"
#include "EntityMgr.h"
#include "SceneView.h"
#include "CardManager.h"
#include "OperalayerBJL.h"
#include "ChipManager.h"
USING_NS_CC;

class SceneLogic:public CCNode
{
public:
	CREATE_FUNC(SceneLogic);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	//��Ϣ����
	void onMessageGame(CCObject* obj);			
	void onMessageScene(CCObject* obj);		
	void onUpdateTable(CCObject* obj);		
	void onUpdataMatch(CCObject* obj);		//this Messager is userd to change gear
	void onViewMessage(CCObject* obj);
	bool onSceneMessage(unsigned char cbStation,const void* pBuffer,WORD wDataSize);
	bool onGameMessage(WORD wSubCmdID, const void* pBuffer, WORD wDataSize);



	//ϵͳ����
	// ��ȡ��ֵ
	static int GetCardValue(int nCardData) {
		return nCardData & MASK_VALUE;
	}

	// ��ȡ��ɫ
	static int GetCardColor(int nCardData) {
		return nCardData & MASK_COLOR;
	}

	// �߼���ֵ
	static int GetCardLogicValue(int nCardData) {
		// ��ֵ��ɫ
		int nCardValue = SceneLogic::GetCardValue(nCardData);
		int nCardColor = SceneLogic::GetCardColor(nCardData);

		// ת��
		if (nCardColor == 0x40) {
			return nCardValue + 2;
		}
		return (nCardValue <= 2) ? (nCardValue + 13) : nCardValue;
	}
	SceneView *SceneViewlayer;
private:
	tagUserData* getMeUserDate() { return EntityMgr::instance()->roomFrame()->getMeUserItem()->getUserData(); }
	WORD getMeChairID(){return getMeUserDate()->wChairID;}
	WORD getMeChairID1(){
		WORD meChairID = EntityMgr::instance()->getDispatch()->m_wChairID;
		return meChairID;
	}
	int	switchViewChairID(unsigned int nChairID); 
	void setGameState(Game_State _state);
	void sendSeverData(WORD wSubCmdID);
	void sendSeverData(WORD wSubCmdID,void* pData,WORD wDataSize);
	void sendFrameData( WORD wSubCmdID,void* pData,WORD wDataSize);
	void checkNet(float ft);
	void onLinkResult(CCObject* obj);
	void onUpdateScoreAndGoldEgg(CCObject* obj);
	int getUserRealChairID(DWORD userID);
	//���ܺ���
private:
	void onUserStart(CCObject *pSender);
	bool onUserStartView(const void * pBuffer, WORD wDataSize);
	bool onUserBEeiLv(const void * pBuffer, WORD wDataSize);
	bool onUserAdd(const void * pBuffer, WORD wDataSize);
	bool onSubSendCard(const void * pBuffer, WORD wDataSize);
	bool onSubOpenCard(const void * pBuffer, WORD wDataSize);
	bool onSubLandScore(const void * pBuffer, WORD wDataSize);
	bool onSubGameStart(const void * pBuffer, WORD wDataSize);
	bool onSubOutCard(const void * pBuffer, WORD wDataSize);
	bool onSubPassCard(const void * pBuffer, WORD wDataSize);
		//��Ϸ����;
	bool onSubGameEnd(const void * pBuffer, WORD wDataSize);
	//���� ����
	bool onUserExpression(const void * pBuffer, WORD wDataSize);

	//��Ϸ��¼
	bool OnSubCheatCard(const void * pBuffer, WORD wDataSize);
	//ȡ����ׯ
	bool OnSubUserCancelBanker(const void * pBuffer, WORD wDataSize);
	//��Ϸ����
	bool OnSubGameFree(const void *pBuffer, WORD wDataSize);

	CCSize size;
	ViewMenuLayer *m_menuLayergic;
	CardManager*					m_pCardManager;									//�ƹ�����
	OperaLayer *                    m_OperaLayer;
	ChipManager*                    m_chipManager;                                   //���������
	CCSprite *SpriteGameStare;        //��Ϸ��ʼ��������ע��ǩ
	CCSprite *SpriteGameTime;          //ʱ���־
	OperaLayer *operlayer;

	CC_SYNTHESIZE(CardTableLayer*,m_cardTableLayer,CardTableLayer);
	void userInforDeal(CCInteger* _data);

private:
	//--����
	BYTE							m_handCardData[GAME_PLAYER][MAX_COUNT];			//�˿��б�
	WORD						m_handCardNum[GAME_PLAYER];
	//--����
	BYTE							m_BackCardData[GAME_PLAYER];								//����
	//--���������
	BYTE							m_outCardData[MAX_COUNT];
	WORD						m_outCardNum;
	WORD						m_beilv;
	BYTE						m_bLastCallScore;													
	WORD						m_wCurrentUser;															//��ǰ���
	WORD						m_wTempUser;																//�ϼ�
	WORD						m_nBankerUser;															//����
	bool							m_wOpenUser[GAME_PLAYER];									//�������
	Game_State				m_gameState;																//��Ϸ״̬
	WORD						m_baseScore;																//��Ϸ��������
	bool							m_isOut;
	//������Ϣ
protected:
	LONGLONG						m_lPlayBetScore;					//��������ע
	LONGLONG						m_lPlayFreeSocre;					//������ɻ���

	//��ע��
protected:
	LONGLONG						m_lAllBet[AREA_MAX];				//����ע
	LONGLONG						m_lPlayBet[AREA_MAX];				//�����ע
	LONGLONG						m_lPlayScore[AREA_MAX];				//�����Ӯ

	//ׯ����Ϣ
protected:
	WORD							m_wBankerUser;						//��ǰׯ��
	LONGLONG						m_lBankerScore;						//ׯ�һ���
	LONGLONG						m_lBankerWinScore;					//ׯ��Ӯ��
	WORD							m_wBankerTime;						//ׯ�Ҿ���
	bool							m_bEnableSysBanker;					//ϵͳ��ׯ

	//�û���ע
	LONGLONG m_lBetScore[8];							//��ע��Ŀ

	//��Ϸ����
protected:
	//�˿���Ϣ
	BYTE							m_cbCardCount[3];						//�˿���Ŀ
	BYTE							m_cbCardCount1[3];						//�˿���Ŀ

	BYTE							m_cbTableCardArray[2][3];				//�����˿�

	//ׯ����Ϣ
	LONGLONG						m_plBankerScore;						//ׯ�ҳɼ�
	LONGLONG						m_plBankerTotallScore;					//ׯ�ҳɼ�
	int								m_pnBankerTime;						//��ׯ����

	//��ҳɼ�
	LONGLONG						m_plPlayScore[AREA_MAX];				//��ҳɼ�
	LONGLONG						m_plPlayAllScore;						//��ҳɼ�

	//ȫ����Ϣ
	LONGLONG						m_plRevenue;							//��Ϸ˰��




};		
#endif

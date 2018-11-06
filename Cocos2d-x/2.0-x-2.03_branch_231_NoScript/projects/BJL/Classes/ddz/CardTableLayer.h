//  [3/26/2014 xieyi]
#ifndef __CARDTABLE_LAYER__
#define __CARDTABLE_LAYER__

#include "cocos2d.h"
#include "DDZRes.h"
#include "SceneData.h"
#include "Timer.h"
#include "User.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class CardTableLayer : public CCNode
{
public:

	CardTableLayer();
	~CardTableLayer();
	CREATE_FUNC(CardTableLayer);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void waitingMatching(bool isWaiting);			//�ȴ��Ŷ�
	void setUserIsOnline(WORD wBankerUser,LONGLONG lBankerScore,LONGLONG lBankerWinScore, WORD	wBankerTime);//�û���ׯ
	void setUserIcon(int userId,int gender,char* name,int gold,char* huafeidian );//����ׯ��ͷ����Ϣ
	void setNickName(const char * nikeName);				//�����ǳ�
	CCSize size;
	void upHaiou(float ft);
	void haiouCall(CCObject* _obj);
	//����ׯ�ҵĽ��
	void setBabnkUsedScore(LONGLONG Score);
	//����ׯ�ҵĳɼ��;���
	void setBankUsedChengjiORrJuNumber(LONGLONG Chengji,LONGLONG JuNumber);
	//������ҵķ����ɼ�
	void setPlayAllScoreORchengji(LONGLONG Chengji);

	//�û���ע���»���
	void SetPlaceLandScore(CCObject *obj);

	void initScrollView(BYTE m_cbPlayerCount ,BYTE m_cbBankerCount);

	void SetUpdate();
public:
	cocos2d::extension::CCScrollView      *m_pScrollView;
	LONG szText0;
private:
	CC_SYNTHESIZE(int,m_coinNumber,CoinNum); 	//�������
	CC_SYNTHESIZE(int,m_hhdNumber,HhdNumber);		//���ѵ�����
	CC_SYNTHESIZE(int,m_times,Times);			//����
	CCLabelTTF * m_coinNumberAtlas;				//�������
	CCSprite *SpriteMyUsed;                        //�û�ͷ��
	//	CCLabelAtlas * m_hhdAtlas;						//���ѵ���
	CCLabelTTF * m_nikeName;						//����ǳ�
	CCLabelTTF *m_Chengji;                          //�û��ɼ�
	CCSpriteBatchNode * m_cardTableBatchNode;		//����batchnode
	CCSpriteBatchNode * m_pdNode;						//�ŶӶ���
	CCString getDateNow();						//���ϵͳ��ǰʱ��

	CCSprite *SpriteGameRecord;             //��Ϸ��¼
public:
	CCSprite *FinUsedSprite;
	CCLabelTTF* laberName;   //����
	CCLabelTTF* goldname;        //���
	CCLabelTTF* ChengjiScore;  //��ַ
	CCLabelTTF *JiNumber;   //����


 //   CCLabelAtlas* lBankTTf;    //ׯ
	//CCLabelAtlas* PlayKingTTf;   //������
	//CCLabelAtlas* lBankKingTTf;    //ׯ���� 
	//CCLabelAtlas* DittoPingTTf;    //ͬ��ƽ
	//CCLabelAtlas* PlaySubTTf;    //�ж���
	//CCLabelAtlas* lBankSubTTf;    //ׯ����
	bool hnnnnnnn;
};

#endif

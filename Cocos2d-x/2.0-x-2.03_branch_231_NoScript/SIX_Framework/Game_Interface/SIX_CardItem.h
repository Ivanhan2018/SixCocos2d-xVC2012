/***********************************************
Name��SIX_CardItem
Desc���˿�UI��������Դ���أ���Ч��
Auth��Cool.Cat@2013-10-10
***********************************************/
#pragma once
#include "SIX_Typedef.h"
#include "SIX_CardEntity.h"

// �˿˵���ƫ��
#define CARD_POP_OFFSET		20.0f

class SIX_CardItem:public CCControlButton,public SIX_CardEntity
{
public:
	SIX_CardItem();
	virtual ~SIX_CardItem();
	static SIX_CardItem* create(CCNode* label, CCScale9Sprite* backgroundSprite);
	static SIX_CardItem* create(std::string title, const char * fontName, float fontSize);
	static SIX_CardItem* create(CCScale9Sprite* sprite);
	virtual bool init();
	void DoCardCombined();
	void DoRelease();
	void doEvents(CCObject* pSender, CCControlEvent event);
public:
	// ���õ�������ɫ
	virtual void setCardPointAndType(CCSpriteFrame *pPointFrame,CCSpriteFrame *pFaceSmallFrame,CCSpriteFrame *pFaceBigFrame,unsigned char point=0,CARD_TYPE type=TYPE_UNKNOWN);

	// ������UI
	void resetCard(bool bPop=false,bool bActived=false,bool bFrontShow=false);

	// ����
	void setCardPop(bool bPop=true);
	bool getCardPop();

	// ����(�Ƿ�ɲ���)
	void setCardActived(bool bActived=true);
	bool getCardActived();

	// �ӽǷ�ת
	void setCardOrbitCamera(float t,float angleZ,float deltaAngleZ);

	// ��ʾ����
	void setCardFrontShow(bool bShow=true);
	bool getCardFrontShow();

	// ��ʾ�Ƶ�
	void setCardReverseShow(bool bShow=true);
	bool getCardReverseShow();

	// ��ʾ����
	void setCardPointShow(bool bShow=true);
	bool getCardPointShow();

	// ��ʾС��ɫ
	void setCardSmallFaceShow(bool bShow=true);
	bool getCardSmallFaceShow();

	// ��ʾ��ɫ
	void setCardBigFaceShow(bool bShow=true);
	bool getCardBigFaceShow();

	// ����ƫ��
	void setCardPointPosition(CCPoint pt);
	void setCardSmallFacePosition(CCPoint pt);
	void setCardBigFacePosition(CCPoint pt);
public:
	// ������
	CCSpriteBatchNode *m_pBatchNode;
	// ���汳��
	CCSprite *m_pBackgroundFront;
	// ���汳��
	CCSprite *m_pBackgroundReverse;
	// ����
	CCSprite *m_pPoint;
	// С��ɫ
	CCSprite *m_pFaceS;
	// ��ɫ
	CCSprite *m_pFaceB;

	// �Ƿ���
	bool m_bPop;
	// �Ƿ񼤻�
	bool m_bActived;
	// �Ƿ���ʾ����
	bool m_bFrontShow;
	// �Ƿ���ʾ�Ƶ�
	bool m_bReverseShow;

	// �Ƿ���ʾ����
	bool m_bShowPoint;
	// �Ƿ���ʾС��ɫ
	bool m_bShowSmallFace;
	// �Ƿ���ʾ��ɫ
	bool m_bShowBigFace;
};
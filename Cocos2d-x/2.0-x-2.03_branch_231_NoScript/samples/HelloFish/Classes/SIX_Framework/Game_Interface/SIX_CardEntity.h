/***********************************************
Name��SIX_CardEntity
Desc���˿�ʵ������
Auth��Cool.Cat@2013-10-10
***********************************************/
#pragma once

// ����
enum CARD_TYPE {
	TYPE_UNKNOWN	= 0,
	// ��(S)
	TYPE_SPADE		= 1,
	// ��(H)
	TYPE_HEART,
	// ÷(C)
	TYPE_CLUB,
	// ��(D)
	TYPE_DIAMOND,
	// С��(BJ)
	TYPE_BLACK_JOKER,
	// ����(RJ)
	TYPE_RED_JOKER,
};

// �ƽṹ
typedef struct tagCardInfo {
	// ����(1��13)
	unsigned char wPoint;
	// ����
	CARD_TYPE wType;
	tagCardInfo()
	{
		wPoint = 0;
		wType = TYPE_UNKNOWN;
	}
} CARD_INFO;

class SIX_CardEntity
{
public:
	SIX_CardEntity();
	virtual ~SIX_CardEntity();
public:
	// ���õ�������ɫ
	virtual void setCardPointAndType(unsigned char point=0,CARD_TYPE type=TYPE_UNKNOWN);

	// ��ȡ����
	unsigned char getCardPoint();

	// ��ȡ��ɫ
	CARD_TYPE getCardType();

	// �Ƿ���
	bool isFaceCards(bool bCaclJoker=true);

	// �Ƿ�С��
	bool isBlackJoker();

	// �Ƿ����
	bool isRedJoker();
private:
	CARD_INFO m_CardInfo;
};
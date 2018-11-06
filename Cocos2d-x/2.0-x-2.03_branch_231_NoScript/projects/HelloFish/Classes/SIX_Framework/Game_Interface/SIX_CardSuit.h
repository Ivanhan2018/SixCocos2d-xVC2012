/*************************************************************************************
Name��SIX_CardSuit
Desc���˿��ƶ�
Auth��Cool.Cat@2013-09-22
*************************************************************************************
0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//���� A - K
0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//÷�� A - K
0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//���� A - K
0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//���� A - K
*************************************************************************************/
#pragma once
#include "SIX_Typedef.h"
#include "SIX_CardItem.h"

//// ��ɫ����
//#define	CARD_MASK_COLOR		0xF0
//// ��ֵ����
//#define	CARD_MASK_VALUE		0x0F
//// �˿�����
//#define CARD_TYPE(x)		(x&CARD_MASK_COLOR)>>4
//// �˿˵���
//#define CARD_POINT(x)		(x&CARD_MASK_VALUE)

class SIX_CardSuit:public CCControl
{
public:
	SIX_CardSuit();
	virtual ~SIX_CardSuit();
public:
	// ���õ�������ɫ
	void setCardPointAndType(CCSpriteFrame *pPointFrame,CCSpriteFrame *pFaceSmallFrame,CCSpriteFrame *pFaceBigFrame,unsigned int idx,unsigned char point=0,CARD_TYPE type=TYPE_UNKNOWN);
	// ��ȡ����
	unsigned char getCardPoint(unsigned int idx);
	// ��ȡ��ɫ
	CARD_TYPE getCardType(unsigned int idx);
	// �Ƿ���
	bool isFaceCards(unsigned int idx,bool bCaclJoker=true);
	// �Ƿ�С��
	bool isBlackJoker(unsigned int idx);
	// �Ƿ����
	bool isRedJoker(unsigned int idx);

	// �����Ƶ���
	void setCardPop(unsigned int startIdx,unsigned int endIdx,bool bPop=false);
	// ��ȡ�Ƶ���
	bool getCardPop(unsigned int idx);
	// �����Ƽ���
	void setCardActived(unsigned int startIdx,unsigned int endIdx,bool bActived=false);
	// ��ȡ�Ƽ���
	bool getCardActived(unsigned idx);
	// ����������ʾ
	void setCardFrontShow(unsigned int startIdx,unsigned int endIdx,bool bShow=false);
	// ��ȡ������ʾ
	bool getCardFrontShow(unsigned int idx);
	// �����Ƶ���ʾ
	void setCardReverseShow(unsigned int startIdx,unsigned int endIdx,bool bShow=false);
	// ��ȡ�Ƶ���ʾ
	bool getCardReverseShow(unsigned int idx);

	// �����������Ƿ���
	void setCardPopAll(bool bIsPopAll=true);
	bool getCardPopAll();
	// �����������Ƿ񼤻�
	void setCardActivedAll(bool bIsActived=true);
	bool getCardActivedAll();
	// �������������Ƿ���ʾ
	void setCardFrontShowAll(bool bIsFrontShow=true);
	bool getCardFrontShowAll();
	// ���������Ƶ��Ƿ���ʾ
	void setCardReverseShowAll(bool bIsReverseShow=true);
	bool getCardReverseShowAll();

	// ȡ�ƶ������Ļ�ľ���ƫ��
	CCPoint getAbsOffset();
private:
	// �Ƿ���������
	bool m_bIsPopAll;
	// �Ƿ񼤻�������
	bool m_bIsActivedAll;
	// �Ƿ���ʾ��������
	bool m_bIsFrontShowAll;
	// �Ƿ���ʾ�����Ƶ�
	bool m_bIsReverseShowAll;
};
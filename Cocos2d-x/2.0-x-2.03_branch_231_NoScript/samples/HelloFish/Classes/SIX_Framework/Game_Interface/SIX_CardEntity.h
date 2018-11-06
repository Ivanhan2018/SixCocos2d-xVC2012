/***********************************************
Name：SIX_CardEntity
Desc：扑克实体数据
Auth：Cool.Cat@2013-10-10
***********************************************/
#pragma once

// 类型
enum CARD_TYPE {
	TYPE_UNKNOWN	= 0,
	// 桃(S)
	TYPE_SPADE		= 1,
	// 心(H)
	TYPE_HEART,
	// 梅(C)
	TYPE_CLUB,
	// 方(D)
	TYPE_DIAMOND,
	// 小王(BJ)
	TYPE_BLACK_JOKER,
	// 大王(RJ)
	TYPE_RED_JOKER,
};

// 牌结构
typedef struct tagCardInfo {
	// 点数(1～13)
	unsigned char wPoint;
	// 类型
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
	// 设置点数及花色
	virtual void setCardPointAndType(unsigned char point=0,CARD_TYPE type=TYPE_UNKNOWN);

	// 获取点数
	unsigned char getCardPoint();

	// 获取花色
	CARD_TYPE getCardType();

	// 是否花牌
	bool isFaceCards(bool bCaclJoker=true);

	// 是否小王
	bool isBlackJoker();

	// 是否大王
	bool isRedJoker();
private:
	CARD_INFO m_CardInfo;
};
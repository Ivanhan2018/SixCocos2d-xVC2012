/*************************************************************************************
Name：SIX_CardSuit
Desc：扑克牌堆
Auth：Cool.Cat@2013-09-22
*************************************************************************************
0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//方块 A - K
0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//梅花 A - K
0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//红桃 A - K
0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//黑桃 A - K
*************************************************************************************/
#pragma once
#include "SIX_Typedef.h"
#include "SIX_CardItem.h"

//// 花色掩码
//#define	CARD_MASK_COLOR		0xF0
//// 数值掩码
//#define	CARD_MASK_VALUE		0x0F
//// 扑克类型
//#define CARD_TYPE(x)		(x&CARD_MASK_COLOR)>>4
//// 扑克点数
//#define CARD_POINT(x)		(x&CARD_MASK_VALUE)

class SIX_CardSuit:public CCControl
{
public:
	SIX_CardSuit();
	virtual ~SIX_CardSuit();
public:
	// 设置点数及花色
	void setCardPointAndType(CCSpriteFrame *pPointFrame,CCSpriteFrame *pFaceSmallFrame,CCSpriteFrame *pFaceBigFrame,unsigned int idx,unsigned char point=0,CARD_TYPE type=TYPE_UNKNOWN);
	// 获取点数
	unsigned char getCardPoint(unsigned int idx);
	// 获取花色
	CARD_TYPE getCardType(unsigned int idx);
	// 是否花牌
	bool isFaceCards(unsigned int idx,bool bCaclJoker=true);
	// 是否小王
	bool isBlackJoker(unsigned int idx);
	// 是否大王
	bool isRedJoker(unsigned int idx);

	// 设置牌弹起
	void setCardPop(unsigned int startIdx,unsigned int endIdx,bool bPop=false);
	// 获取牌弹起
	bool getCardPop(unsigned int idx);
	// 设置牌激活
	void setCardActived(unsigned int startIdx,unsigned int endIdx,bool bActived=false);
	// 获取牌激活
	bool getCardActived(unsigned idx);
	// 设置牌面显示
	void setCardFrontShow(unsigned int startIdx,unsigned int endIdx,bool bShow=false);
	// 获取牌面显示
	bool getCardFrontShow(unsigned int idx);
	// 设置牌底显示
	void setCardReverseShow(unsigned int startIdx,unsigned int endIdx,bool bShow=false);
	// 获取牌底显示
	bool getCardReverseShow(unsigned int idx);

	// 设置所有牌是否弹起
	void setCardPopAll(bool bIsPopAll=true);
	bool getCardPopAll();
	// 设置所有牌是否激活
	void setCardActivedAll(bool bIsActived=true);
	bool getCardActivedAll();
	// 设置所有牌面是否显示
	void setCardFrontShowAll(bool bIsFrontShow=true);
	bool getCardFrontShowAll();
	// 设置所有牌底是否显示
	void setCardReverseShowAll(bool bIsReverseShow=true);
	bool getCardReverseShowAll();

	// 取牌堆相对屏幕的绝对偏移
	CCPoint getAbsOffset();
private:
	// 是否弹起所有牌
	bool m_bIsPopAll;
	// 是否激活所有牌
	bool m_bIsActivedAll;
	// 是否显示所有牌面
	bool m_bIsFrontShowAll;
	// 是否显示所有牌底
	bool m_bIsReverseShowAll;
};
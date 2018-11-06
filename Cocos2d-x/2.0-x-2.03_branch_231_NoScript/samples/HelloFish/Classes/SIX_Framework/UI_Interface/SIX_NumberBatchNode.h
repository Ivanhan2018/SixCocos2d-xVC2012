/***********************************************
Name��SIX_NumberBatchNode
Desc����Ч���������Ż��Ӿ��鶯��Ч��
Auth��Cool.Cat@2013-07-25
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "SIX_EffectBatchNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

// cell���뷽ʽ
typedef enum tagAlignStyle{
	// �����
	ALIGN_LEFT = 1,
	// �ж���
	ALIGN_CENTER,
	// �Ҷ���
	ALIGN_RIGHT,
} ALIGN_STYLE;

class SIX_NumberBatchNode:public SIX_EffectBatchNode
{
public:
	SIX_NumberBatchNode();
	virtual ~SIX_NumberBatchNode();
	static SIX_NumberBatchNode *Create(const char *file);
	static SIX_NumberBatchNode *Create(const char *file,unsigned int cell,float padding,unsigned int bitcount,CCPoint offset,EFFECT_TYPE effectType=EFFECT_NONE,float effectValue=EFFECT_VALUE,float durtime=EFFECT_DURTIME);
	void DoRelease();
public:
	void setCellNum(unsigned int cell);
	unsigned int getCellNum();

	void setCellWidth(float width);
	float getCellWidth();

	void setCellHeight(float height);
	float getCellHeight();

	void setCellAlignStyle(ALIGN_STYLE style=ALIGN_LEFT);
	ALIGN_STYLE getCellAlignStyle();

	void setPadding(float padding);
	float getPadding();

	void setBitCount(unsigned int bitcount);
	unsigned int getBitCount();

	void setNumber(long long,bool doAnimate=true);
	long long getNumber();

	void setDigit(unsigned int cCount);
	unsigned int getDigit();
private:
	// �ϴε�����
	long long m_llNumberLast;
	// ���Ƶ�����
	long long m_llNumber;
	// �����ڲ�����
	unsigned int m_uCellNum;
	// ����cell���
	float m_fCellWidth;
	// ����cell�߶�
	float m_fCellHeight;
	// ���
	float m_uPadding;
	// �ܸ��������㲹0��
	unsigned int m_uBitCount;
	// cell���뷽ʽ
	ALIGN_STYLE m_CellAlignStyle;
	// ����·��
	CCString *pNumFile;
	// λ����������0����
	unsigned int m_uShowCount;
};

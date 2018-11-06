/***********************************************
Name：SIX_NumberBatchNode
Desc：特效批处理，已优化子精灵动画效率
Auth：Cool.Cat@2013-07-25
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "SIX_EffectBatchNode.h"

USING_NS_CC;
USING_NS_CC_EXT;

// cell对齐方式
typedef enum tagAlignStyle{
	// 左对齐
	ALIGN_LEFT = 1,
	// 中对齐
	ALIGN_CENTER,
	// 右对齐
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
	// 上次的数字
	long long m_llNumberLast;
	// 绘制的数字
	long long m_llNumber;
	// 纹理内部个数
	unsigned int m_uCellNum;
	// 纹理cell宽度
	float m_fCellWidth;
	// 纹理cell高度
	float m_fCellHeight;
	// 间距
	float m_uPadding;
	// 总个数（不足补0）
	unsigned int m_uBitCount;
	// cell对齐方式
	ALIGN_STYLE m_CellAlignStyle;
	// 纹理路径
	CCString *pNumFile;
	// 位数，少于用0代替
	unsigned int m_uShowCount;
};

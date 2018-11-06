#pragma once
#include "cocos2d.h"

USING_NS_CC;


class EmailCell : public CCSprite
{
public:
	static EmailCell* EmailCellWith(int type);
	bool initEmailCellWith(int type);
	void setCellIdx(int idx);
	EmailCell(void);
	~EmailCell(void);

	void DeleteMessage(CCObject* obj);

private:
	CCLabelTTF* messageContext;
	CCLabelTTF* messageTitle;
	int m_nType;
};


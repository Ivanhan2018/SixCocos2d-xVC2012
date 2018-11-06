#pragma once
#include "cocos2d.h"
#include "MovingLabelLayer.h"
USING_NS_CC;


class ChoosePhotoCell : public CCNode
{
public:
	static ChoosePhotoCell* PhotoCellWith(int type);
	bool initPhotoCellWith(int type);
	void setCellIdx(int idx);
	void choosePhoto(cocos2d::CCObject *obj);
	void callbackC();
	ChoosePhotoCell(void);
	~ChoosePhotoCell(void);
	

private:
	CCSize winSize;
	int m_nType;
	/**����ѡ���Ϊ�ڼ���ͼƬ**/
	int m_choose;
	CCSprite *pPhotoBJ1;
	CCSprite *pChoose;
	CCMenu *pMenu;
	MovingLabelLayer* layer;
};
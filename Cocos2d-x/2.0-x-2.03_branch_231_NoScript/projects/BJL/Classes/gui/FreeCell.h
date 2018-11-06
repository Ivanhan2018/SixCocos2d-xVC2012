#pragma once
#include "cocos2d.h"

USING_NS_CC;


class FreeCell : public CCNode
{
public:
	static FreeCell* FreeCellWith(int type,bool isGet);
	bool initFreeCellWith(int type,bool isGet);
	void setCellIdx(int idx,bool isGet);
	void chooseFree(cocos2d::CCObject *obj);
	void setPesent(CCObject* obj);
	FreeCell(void);
	~FreeCell(void);

	void setMenuEnable(CCObject* obj);

private:

	int m_nType;
	bool m_nIsget;
	/**代表选择的为第几号图片**/
	int m_choose;
	CCSprite *pSprite;
	CCSprite *pChoose;

	CCLabelTTF *m_titile;
	CCLabelTTF *m_text;

	/**进度条**/
	CCProgressTimer *pJinDuTiao;
	CCSprite *pJinDuTiao0;
	CCSprite *pJinDuTiao1;
	//领取字
	CCLabelTTF *pTextWaring;
	/**文字 显示下载进度**/
	CCLabelTTF *pTTF;

	/**csmj**/
	int m_csmj_per;
	/**pdk**/
	int m_pdk_per;
	/**phz**/
	int m_phz_per;
	/**sdh**/
	int m_sdh_per;

	CCMenuItemSprite *m_pMenuButton;
	
};
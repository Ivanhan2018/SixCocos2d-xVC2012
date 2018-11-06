/***********************************************
Name：SIX_PopWndSellFish
Desc：游戏场景出售渔获窗口
Auth：Cool.Cat@2013-07-06
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"
#include <SIX_NumberBatchNode.h>
#include "SIX_Common.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum SellFish_BTN_TAG {
	BTN_SellAndExit = 1,
	BTN_SellNoExit = 2
};

class SIX_PopWndSellFish:public SIX_PopWnd
{
public:
	enum emFishCount{StatFishCount=19};
	SIX_PopWndSellFish();
	virtual ~SIX_PopWndSellFish();
public:
	static SIX_PopWndSellFish *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
	//add by Ivan_han 20130713
	// 根据鱼号/龙虾炸弹号/金龙炸弹号查找对应的数组索引
	static int GetIndexFromArray(TFishKind fishType);
	unsigned int getFishCount(int validIdx)const;
	void setFishCount(int validIdx,unsigned int uFishCount);
	void doAnimation(CCNode *pNode);
public:
	virtual bool init();
	virtual void onShow();
private:
	virtual void onEnterTransitionDidFinish();
	bool OnBtn(CCObject*,int tag);
public:
	// 出售并退出
	CCControlButton *m_pSellAndExit;
	// 出售并继续
	CCControlButton *m_pSellNoExit;

	// 鱼数量
	SIX_NumberBatchNode *m_pFishCount[StatFishCount];
	// 获得渔币
	SIX_NumberBatchNode *m_pFishCoin;
	// 剩余子弹
	SIX_NumberBatchNode *m_pBulletCount;
	// 获得渔币换的金币
	SIX_NumberBatchNode *m_pGoldCoin1;
	// 剩余子弹换的金币
	SIX_NumberBatchNode *m_pGoldCoin2;
	// 合计金币
	SIX_NumberBatchNode *m_pGoldCoin;
};
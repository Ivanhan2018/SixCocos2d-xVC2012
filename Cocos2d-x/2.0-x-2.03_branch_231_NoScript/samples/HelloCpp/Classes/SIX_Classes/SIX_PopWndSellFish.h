/***********************************************
Name��SIX_PopWndSellFish
Desc����Ϸ����������񴰿�
Auth��Cool.Cat@2013-07-06
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
	// �������/��Ϻը����/����ը���Ų��Ҷ�Ӧ����������
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
	// ���۲��˳�
	CCControlButton *m_pSellAndExit;
	// ���۲�����
	CCControlButton *m_pSellNoExit;

	// ������
	SIX_NumberBatchNode *m_pFishCount[StatFishCount];
	// ������
	SIX_NumberBatchNode *m_pFishCoin;
	// ʣ���ӵ�
	SIX_NumberBatchNode *m_pBulletCount;
	// �����һ��Ľ��
	SIX_NumberBatchNode *m_pGoldCoin1;
	// ʣ���ӵ����Ľ��
	SIX_NumberBatchNode *m_pGoldCoin2;
	// �ϼƽ��
	SIX_NumberBatchNode *m_pGoldCoin;
};
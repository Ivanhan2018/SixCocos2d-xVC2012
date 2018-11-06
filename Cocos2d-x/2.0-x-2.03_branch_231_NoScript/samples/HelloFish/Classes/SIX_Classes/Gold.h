/*********************************************************
Name：Gold
Desc：金币管理器
Auth：lijianming
*********************************************************/
#pragma once
#include "cocos2d.h"
#include <SIX_Typedef.h>
#include <SIX_UIScene.h>
#include "BulletAndNetMgr.h"
#include "cocos2d.h"
//#include "Numbers.h"
#include <SIX_Lock.h>
#include <SIX_TList.h>
#include <SIX_GlobalMgr.h>

typedef enum {
	TYPE_GOLD	= 1,
	TYPE_SILVER = 2,
} MONEY_TYPE;

struct TNumPos
{
	float x;
	float y;
	int i;
};

USING_NS_CC;

class CGold : public TSingleton<CGold>
{
public:
	CGold();
	~CGold();

public:
	void Init(CCNode *pBG,int poolStep=500);
	void Release();
	void GoldPoolExpansion();
	void SilverPoolExpansion();
	void Del(CCNode *node);
	void CountGold(int goldValue,int *gold,int *silver);
	void createOneGold(CCNode *node, CCPoint fishPT, CCPoint PlayerPT, int goldType, int index, int total);
	void showGold(int goldValue, CCPoint fishPT, long long llUserID);
	//添加一个金币转盘，add by Ivan_han 20130720
	void AddOneGoldDisc(int goldValue, CCPoint fishPT, long long llUserID);
	//add by Ivan_han 20130720
	CCLayerColor *GetBG()const{return mBG;}
	//添加单个数字精灵，add by Ivan_han 20130723
	CCSprite *AddOneNumber(int i);
	static vector<TNumPos> GetNumPosArr(int goldValue,bool bShowMult);
private:
	// 金币移动速度
	float mfSpeed;
	CCLayerColor *mBG;

	SIX_TList<CCSprite*> *m_GoldPool;
	SIX_TList<CCSprite*> *m_SilverPool;
	int m_poolStep;
	CCSpriteBatchNode *pBatchNode;
	CCSpriteBatchNode *pGoldDiscBatchNode;//add by Ivan_han 20130727
	bool m_IsGold;
};

extern CGold *g_pGold;
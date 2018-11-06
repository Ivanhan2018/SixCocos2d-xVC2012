/***********************************************
Name��SIX_PopWndPlayerInfo
Desc��������ϴ���
Auth��Cool.Cat@2013-10-09
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include <SIX_DSTPL.h>
#include <SIX_GlobalMgr.h>
#include <SIX_ScrollBar.h>
#include "cocos-ext.h"
#include "SIX_PopWnd.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_PopWndPlayerInfo:public SIX_PopWnd
{
public:
	virtual ~SIX_PopWndPlayerInfo();
public:
	static SIX_PopWndPlayerInfo *Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder=false,bool bCloseThenCleanup=false);
public:
	virtual bool init();
	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);

	void setPlayerLogo(long long llSysLogoID);
	void setPlayerNickName(const char *name);
	void setPlayerMoney(int money);
	void setPlayerLevel(int level);
	void setPlayerWinRound(int round);
	void setPlayerTotalRound(int round);

	void setPlayerViewId(int idx);
	int getPlayerViewId();
private:
	virtual void onEnterTransitionDidFinish();
	void RefreshUI();
private:
	// ���ͷ��
	CCSprite *m_pBgLogo;
	// ����ǳ�
	CCLabelTTF *m_pNickName;
	// ��ǰ�ʲ�
	CCLabelTTF *m_pMoney;
	// ��Ϸ�ȼ�
	CCLabelTTF *m_pLevel;
	// �ȼ�ͼ��
	CCSprite *m_pLevelIco;
	// �ȼ�����
	CCLabelTTF *m_pLevelDesc;
	// ��Ӯ�ƾ�
	CCLabelTTF *m_pWinRound;
	// �����ƾ�
	CCLabelTTF *m_pTotalRound;

	// �û���ͼID
	int m_PlayerViewId;
};
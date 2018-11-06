/***********************************************
Name：SIX_CardItem
Desc：扑克UI，包含资源加载，特效等
Auth：Cool.Cat@2013-10-10
***********************************************/
#pragma once
#include "SIX_Typedef.h"
#include "SIX_CardEntity.h"

// 扑克弹起偏移
#define CARD_POP_OFFSET		20.0f

class SIX_CardItem:public CCControlButton,public SIX_CardEntity
{
public:
	SIX_CardItem();
	virtual ~SIX_CardItem();
	static SIX_CardItem* create(CCNode* label, CCScale9Sprite* backgroundSprite);
	static SIX_CardItem* create(std::string title, const char * fontName, float fontSize);
	static SIX_CardItem* create(CCScale9Sprite* sprite);
	virtual bool init();
	void DoCardCombined();
	void DoRelease();
	void doEvents(CCObject* pSender, CCControlEvent event);
public:
	// 设置点数及花色
	virtual void setCardPointAndType(CCSpriteFrame *pPointFrame,CCSpriteFrame *pFaceSmallFrame,CCSpriteFrame *pFaceBigFrame,unsigned char point=0,CARD_TYPE type=TYPE_UNKNOWN);

	// 重置牌UI
	void resetCard(bool bPop=false,bool bActived=false,bool bFrontShow=false);

	// 弹起
	void setCardPop(bool bPop=true);
	bool getCardPop();

	// 激活(是否可操作)
	void setCardActived(bool bActived=true);
	bool getCardActived();

	// 视角翻转
	void setCardOrbitCamera(float t,float angleZ,float deltaAngleZ);

	// 显示牌面
	void setCardFrontShow(bool bShow=true);
	bool getCardFrontShow();

	// 显示牌底
	void setCardReverseShow(bool bShow=true);
	bool getCardReverseShow();

	// 显示点数
	void setCardPointShow(bool bShow=true);
	bool getCardPointShow();

	// 显示小花色
	void setCardSmallFaceShow(bool bShow=true);
	bool getCardSmallFaceShow();

	// 显示大花色
	void setCardBigFaceShow(bool bShow=true);
	bool getCardBigFaceShow();

	// 设置偏移
	void setCardPointPosition(CCPoint pt);
	void setCardSmallFacePosition(CCPoint pt);
	void setCardBigFacePosition(CCPoint pt);
public:
	// 批处理
	CCSpriteBatchNode *m_pBatchNode;
	// 正面背景
	CCSprite *m_pBackgroundFront;
	// 反面背景
	CCSprite *m_pBackgroundReverse;
	// 点数
	CCSprite *m_pPoint;
	// 小花色
	CCSprite *m_pFaceS;
	// 大花色
	CCSprite *m_pFaceB;

	// 是否弹起
	bool m_bPop;
	// 是否激活
	bool m_bActived;
	// 是否显示牌面
	bool m_bFrontShow;
	// 是否显示牌底
	bool m_bReverseShow;

	// 是否显示点数
	bool m_bShowPoint;
	// 是否显示小花色
	bool m_bShowSmallFace;
	// 是否显示大花色
	bool m_bShowBigFace;
};
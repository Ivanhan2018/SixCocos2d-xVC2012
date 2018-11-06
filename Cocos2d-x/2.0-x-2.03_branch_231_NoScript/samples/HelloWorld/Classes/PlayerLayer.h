#pragma once
#ifndef ____PLAYER_H____
#define ____PLAYER_H____
#include "cocos2d.h"
#include "BulletSprite.h"

USING_NS_CC;
#define  PLAYER_COUNT		4				// 玩家数目

//////////////////////////////////////////////////////////////////////////
// 左上角位置为 0 号位，顺时针分别为 0, 1, 2, 3

/// 玩家
class PlayerLayer : public CCLayer
{	
public:
	PlayerLayer(int iPosition, bool bMySelf=false);
	~PlayerLayer(void);

	virtual void onEnter();
	virtual void onExit();
	virtual void didAccelerate(CCAcceleration *pAccelerationValue);

	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesMoved(CCSet* touches, CCEvent* event);
	void ccMousesMoved(CCSet *touches, CCEvent *pEvent);
	
	/// 设置炮类型
	void SetGunType(bool bAdd);
	/// 发炮动作
	void EmitGun(CCPoint pt);
	/// 旋转炮
	/// @return 返回旋转的角度值
	float whirlGun(CCPoint &pt);

	CCAnimation * m_pGunAnimation;
	CC_SYNTHESIZE_READONLY(int, m_iGunType, GunType);			///< 炮类型
	CC_SYNTHESIZE_READONLY(bool, m_MySelf, MySelf);				/// 设置自己
	CC_PROPERTY_READONLY(CBulletManage *, m_BulletManage, BulletManage); /// 当前玩家的子弹管理
	CC_SYNTHESIZE(int, m_PlayerPT, PlayerPT);								/// 玩家方位

	/// 划船动画
	void OnRowingAnimation(float fTime);
	void OnRowingCompleteAnimation();
};

class PlayerManage
{
public:
	static PlayerLayer* create(CCNode* pNode, int iPT, bool bMySelf=false);
	static void PlayerLeave( int iPT );												/// 玩家离开
	static int GetMyPlayerID();
	static PlayerLayer* GetMyPlayer();

	static int m_MySelfID;																///< 玩家ID
	static CCDictionary* s_AllPlayer;												///< 所有玩家
};

#endif
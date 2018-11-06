#pragma once
#ifndef ____PLAYER_H____
#define ____PLAYER_H____
#include "cocos2d.h"
#include "BulletSprite.h"

USING_NS_CC;
#define  PLAYER_COUNT		4				// �����Ŀ

//////////////////////////////////////////////////////////////////////////
// ���Ͻ�λ��Ϊ 0 ��λ��˳ʱ��ֱ�Ϊ 0, 1, 2, 3

/// ���
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
	
	/// ����������
	void SetGunType(bool bAdd);
	/// ���ڶ���
	void EmitGun(CCPoint pt);
	/// ��ת��
	/// @return ������ת�ĽǶ�ֵ
	float whirlGun(CCPoint &pt);

	CCAnimation * m_pGunAnimation;
	CC_SYNTHESIZE_READONLY(int, m_iGunType, GunType);			///< ������
	CC_SYNTHESIZE_READONLY(bool, m_MySelf, MySelf);				/// �����Լ�
	CC_PROPERTY_READONLY(CBulletManage *, m_BulletManage, BulletManage); /// ��ǰ��ҵ��ӵ�����
	CC_SYNTHESIZE(int, m_PlayerPT, PlayerPT);								/// ��ҷ�λ

	/// ��������
	void OnRowingAnimation(float fTime);
	void OnRowingCompleteAnimation();
};

class PlayerManage
{
public:
	static PlayerLayer* create(CCNode* pNode, int iPT, bool bMySelf=false);
	static void PlayerLeave( int iPT );												/// ����뿪
	static int GetMyPlayerID();
	static PlayerLayer* GetMyPlayer();

	static int m_MySelfID;																///< ���ID
	static CCDictionary* s_AllPlayer;												///< �������
};

#endif
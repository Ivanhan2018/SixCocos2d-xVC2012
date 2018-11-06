#pragma once
#ifndef ____CBULLET_H____
#define ____CBULLET_H____

#include "cocos2d.h"

// �ӵ�
class BulletSprite :	public cocos2d::CCSprite
{
public:
	static BulletSprite * create(const char *pszName);
	void FinishAnimation(CCNode* pSender, void* data);
	void Release();
	
	CC_SYNTHESIZE(bool, m_bIsReBound, IsReBound);
	CC_SYNTHESIZE(bool, m_bIsCatching, IsCatching);
	CC_SYNTHESIZE(int, m_iPlayerID, PlayerID);
};

class CBulletManage
{
public:
	static CBulletManage * Init(cocos2d::CCNode * pNode);
	void Release();

	void Shoot(int iPlayerID, cocos2d::CCPoint ptTouch, cocos2d::CCPoint ptShip, float fRotation, bool bReBound);					///< ����
	cocos2d::CCSpriteBatchNode * sharedBullet();																														///< �����ӵ�

protected:
	static cocos2d::CCPoint CountTwoPointOneCoordinate(cocos2d::CCPoint ptSrc, cocos2d::CCPoint ptDes, float fLenght);	///< ���������ָ��һ�����ȵ�����

private:
	static int m_FrameCacheCount;
	DWORD m_LastShootTime;
	cocos2d::CCSpriteBatchNode * s_AllBullet;
	CC_SYNTHESIZE(cocos2d::CCNode *, m_ParentNode, ParentNode);
};

#endif
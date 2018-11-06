/***********************************************
Name��SIX_CountDownBatchNode
Desc������ʱ��ʾ����������
Auth��Cool.Cat@2013-10-22
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_CountDownBatchNode:public CCSpriteBatchNode
{
public:
	SIX_CountDownBatchNode();
	virtual ~SIX_CountDownBatchNode();
	static SIX_CountDownBatchNode *Create(const char *batchNodeFile,const char *bgFrameName,unsigned int TimeCount,float padding,unsigned int bitcount,CCSize size,CCPoint offset,const char *numFramePrefix=0,float scaleFactor=1.0f);
	void SetCallFuncND(CCCallFuncND *pCallFunc);
	void DoRelease();
private:
	void DoCallBack(CCNode *pNode);
private:
	// ����ʱ
	unsigned int m_uCountdown;
	// ���
	float m_fPadding;
	// �ܸ��������㲹0��
	unsigned int m_uBitCount;
	// ����
	CCString *m_BackgroundName;
	// ǰ׺
	CCString *m_NumFramePrefix;
	// �ص�
	CCCallFuncND *m_pCallFuncND;
	// ��һ��Ԫ����ʼƫ��
	CCPoint m_offsetFirst;
	// ��������
	float m_fScaleFactor;
};
/***********************************************
Name��SIX_CountDown
Desc������ʱ��ʾ����
Auth��Cool.Cat@2013-07-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
//#include <EasyDataTime.h>

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_CountDown:public CCScale9Sprite
{
public:
	SIX_CountDown();
	virtual ~SIX_CountDown();
	static SIX_CountDown *Create(const char *bgFile,const char *msgFile,const char *numFile,unsigned int cell,float padding,unsigned int bitcount,unsigned int countdown,CCPoint offset);
	void SetCallFunc(SEL_CallFunc pCallFunc);
	void DoRelease();
private:
	void DoCallBack(CCNode *pNode);
private:
	CCScale9Sprite *pMsg;
	CCSpriteBatchNode* pBatchNode;
	// ����ʱ
	unsigned int m_uCountdown;
	// �����ڲ�����
	unsigned int m_uCell;
	// ���
	float m_uPadding;
	// �ܸ��������㲹0��
	unsigned int m_uBitCount;
	CCString *pNumFile;
	// �ص�
	SEL_CallFunc m_pCallFunc;
};
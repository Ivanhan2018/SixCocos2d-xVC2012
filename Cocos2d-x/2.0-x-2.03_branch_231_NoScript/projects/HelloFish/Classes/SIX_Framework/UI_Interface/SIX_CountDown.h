/***********************************************
Name：SIX_CountDown
Desc：倒计时提示控制
Auth：Cool.Cat@2013-07-24
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
	// 倒计时
	unsigned int m_uCountdown;
	// 纹理内部个数
	unsigned int m_uCell;
	// 间距
	float m_uPadding;
	// 总个数（不足补0）
	unsigned int m_uBitCount;
	CCString *pNumFile;
	// 回调
	SEL_CallFunc m_pCallFunc;
};
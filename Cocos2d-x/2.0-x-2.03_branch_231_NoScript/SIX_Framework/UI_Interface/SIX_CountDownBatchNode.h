/***********************************************
Name：SIX_CountDownBatchNode
Desc：倒计时提示控制批处理
Auth：Cool.Cat@2013-10-22
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
	// 倒计时
	unsigned int m_uCountdown;
	// 间距
	float m_fPadding;
	// 总个数（不足补0）
	unsigned int m_uBitCount;
	// 背景
	CCString *m_BackgroundName;
	// 前缀
	CCString *m_NumFramePrefix;
	// 回调
	CCCallFuncND *m_pCallFuncND;
	// 第一个元素起始偏移
	CCPoint m_offsetFirst;
	// 拉伸因子
	float m_fScaleFactor;
};
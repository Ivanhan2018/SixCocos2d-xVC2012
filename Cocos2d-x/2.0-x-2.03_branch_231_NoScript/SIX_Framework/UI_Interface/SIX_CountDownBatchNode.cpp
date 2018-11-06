#include "SIX_CountDownBatchNode.h"

SIX_CountDownBatchNode::SIX_CountDownBatchNode()
{
	m_uCountdown = 0;
	m_BackgroundName = 0;
	m_NumFramePrefix = 0;
	m_pCallFuncND = 0;
	m_offsetFirst = CCPointZero;
	m_fScaleFactor = 0.0f;
	m_fPadding = 0.0f;
}

SIX_CountDownBatchNode::~SIX_CountDownBatchNode()
{
	DoRelease();
}

SIX_CountDownBatchNode *SIX_CountDownBatchNode::Create(const char *batchNodeFile,const char *bgFrameName,unsigned int TimeCount,float padding,unsigned int bitcount,CCSize size,CCPoint offset,const char *numFramePrefix,float scaleFactor)
{
	SIX_CountDownBatchNode *pCountDown = new SIX_CountDownBatchNode();
	if (pCountDown && pCountDown->init())
	{
		pCountDown->initWithFile(batchNodeFile,0);
		pCountDown->ignoreAnchorPointForPosition(true);
		// 背景
		if (bgFrameName)
		{
			pCountDown->m_BackgroundName = CCString::create(bgFrameName);
			pCountDown->m_BackgroundName->retain();
		}
		// save it~
		if (numFramePrefix)
		{
			pCountDown->m_NumFramePrefix = CCString::create(numFramePrefix);
			pCountDown->m_NumFramePrefix->retain();
		}
		// 大小
		pCountDown->setContentSize(size);
		// 间距
		pCountDown->m_fPadding = padding;
		// 位数
		pCountDown->m_uBitCount = bitcount;
		// 第一个元素偏移
		pCountDown->m_offsetFirst.x = offset.x;
		pCountDown->m_offsetFirst.y = offset.y;
		// 拉伸
		pCountDown->m_fScaleFactor = scaleFactor;
		// 先执行第一次动作
		pCountDown->m_uCountdown = TimeCount;
		pCountDown->DoCallBack(pCountDown);
	}
	return pCountDown;
}

void SIX_CountDownBatchNode::SetCallFuncND(CCCallFuncND *pCallFunc)
{
	m_pCallFuncND = pCallFunc;
	m_pCallFuncND->retain();
}

void SIX_CountDownBatchNode::DoCallBack(CCNode *pNode)
{
	if (!pNode)
		return;

	SIX_CountDownBatchNode *pCountDown = dynamic_cast<SIX_CountDownBatchNode*>(pNode);
	if (!pCountDown)
		return;

	pCountDown->removeAllChildrenWithCleanup(true);

	if (pCountDown->m_uCountdown==0)
	{
		if (pCountDown->m_pCallFuncND)
		{
			pCountDown->m_pCallFuncND->execute();
		}
		//pCountDown->removeFromParentAndCleanup(true);
		//CC_SAFE_RELEASE(pCountDown);
		pCountDown->DoRelease();
		return;
	}

	pCountDown->m_uCountdown--;

	CCSize size = this->getContentSize();
	//SIXLog("size[%.2f/%.2f]",size.width,size.height);

	// 添加背景
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pCountDown->m_BackgroundName->getCString());
	if (pFrame)
	{
		CCSprite *pChild = CCSprite::createWithSpriteFrame(pFrame);
		if (pChild)
		{
			pChild->ignoreAnchorPointForPosition(true);
			pCountDown->addChild(pChild);
		}
	}

	CCString *pNumArr = CCString::createWithFormat("%u",pCountDown->m_uCountdown);
	string numStr(pNumArr->getCString());
	// 位数不足要补0
	int zerofill = pCountDown->m_uBitCount - numStr.length();
	if (zerofill>0)
		for (int i=0;i<zerofill;i++)
			numStr.insert(0,"0");

	// 添加子元素
	for (unsigned int i=0;i<numStr.length();i++)
	{
		int value = SIX_Utility::GetInstance()->s2n(numStr.at(i));

		if (pCountDown->m_NumFramePrefix)
			pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s%d.png",m_NumFramePrefix->getCString(),value)->getCString());
		else
			pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%d.png",value)->getCString());
		if (!pFrame)
			continue;

		// 位宽
		float cell_width = pFrame->getOriginalSize().width;
		float cell_height = pFrame->getOriginalSize().height;

		CCSprite *pChild = CCSprite::createWithSpriteFrame(pFrame);
		if (!pChild)
		{
			CCAssert(pChild,"pChild.Nil");
			continue;
		}

		pChild->setPosition(ccp(m_offsetFirst.x+i*(cell_width+pCountDown->m_fPadding),m_offsetFirst.y));
		//SIXLog("pChild[%d].cell_width[%.2f/%.2f].setPosition[%.2f/%.2f]",
		//	i,
		//	cell_width,
		//	cell_height,
		//	m_offsetFirst.x+i*(cell_width+pCountDown->m_fPadding),
		//	m_offsetFirst.y);

		pChild->ignoreAnchorPointForPosition(true);
		pCountDown->addChild(pChild);
	}

	// 先放大
	pCountDown->setScale(pCountDown->m_fScaleFactor);
	// 再恢复
	CCScaleTo *pScale = CCScaleTo::create(0.1f,1.0f);
	// 剩余执行时间
	CCDelayTime *pDelay = CCDelayTime::create(0.9f);
	// add array
	CCArray *ActionArray = CCArray::create();
	ActionArray->addObject(pScale);
	ActionArray->addObject(pDelay);
	ActionArray->addObject(CCCallFuncN::create(pCountDown,callfuncN_selector(SIX_CountDownBatchNode::DoCallBack)));
	CCSequence *pSeq = dynamic_cast<CCSequence*>(CCSequence::create(ActionArray));
	pCountDown->runAction(pSeq);
	SIXLog("SIX_CountDownBatchNode.DoCallBack.m_uCountdown[%u]",pCountDown->m_uCountdown);
}

void SIX_CountDownBatchNode::DoRelease()
{
	// 停止动作管理器和调度器先~
	this->cleanup();
	// 再置零
	m_uCountdown = 0;
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
	CC_SAFE_DELETE(m_pCallFuncND);
	CC_SAFE_DELETE(m_NumFramePrefix);
	CC_SAFE_DELETE(m_BackgroundName);
}
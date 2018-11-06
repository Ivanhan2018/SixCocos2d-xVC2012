#include "SIX_CountDown.h"

SIX_CountDown::SIX_CountDown()
{
	pMsg = 0;
	pBatchNode = 0;
	m_uCountdown = m_uCell = m_uBitCount = 0;
	m_uPadding = 0.0f;
	pNumFile = 0;
	m_pCallFunc = 0;
}

SIX_CountDown::~SIX_CountDown()
{
	DoRelease();
}

SIX_CountDown *SIX_CountDown::Create(const char *bgFile,const char *msgFile,const char *numFile,unsigned int cell,float padding,unsigned int bitcount,unsigned int countdown,CCPoint offset)
{
	if (!bgFile || !msgFile || !numFile || !cell || !bitcount || !countdown)
		return 0;

	SIX_CountDown *pCountDown = new SIX_CountDown();
	if (pCountDown && pCountDown->init())
	{
		pCountDown->initWithFile(bgFile);
		pCountDown->pMsg = CCScale9Sprite::create(msgFile);
		if (!pCountDown->pMsg)
		{
			CC_SAFE_DELETE(pCountDown);
			return 0;
		}
		pCountDown->pMsg->ignoreAnchorPointForPosition(true);
		pCountDown->pMsg->setPosition(ccp((pCountDown->getPreferredSize().width-pCountDown->pMsg->getPreferredSize().width)/2,(pCountDown->getPreferredSize().height-pCountDown->pMsg->getPreferredSize().height)/2));
		pCountDown->addChild(pCountDown->pMsg);

		pCountDown->pBatchNode = CCSpriteBatchNode::create(numFile);
		if (!pCountDown->pBatchNode)
		{
			CC_SAFE_DELETE(pCountDown);
			return 0;
		}

		pCountDown->pBatchNode->setPosition(offset);
		pCountDown->pBatchNode->ignoreAnchorPointForPosition(true);
		pCountDown->pMsg->addChild(pCountDown->pBatchNode);

		// save it~
		pCountDown->pNumFile = CCString::create(numFile);
		pCountDown->pNumFile->retain();
		// 先执行第一次动作
		pCountDown->m_uCountdown = countdown;
		pCountDown->m_uCell = cell;
		pCountDown->m_uPadding = padding;
		pCountDown->m_uBitCount = bitcount;
		pCountDown->DoCallBack(pCountDown->pBatchNode);
	}
	return pCountDown;
}

void SIX_CountDown::SetCallFunc(SEL_CallFunc pCallFunc)
{
	m_pCallFunc = pCallFunc;
}

void SIX_CountDown::DoCallBack(CCNode *pNode)
{
	if (!pNode)
		return;
	CCSpriteBatchNode *pBatchNode = dynamic_cast<CCSpriteBatchNode*>(pNode);
	if (!pBatchNode)
		return;
	CCScale9Sprite *pMsg = dynamic_cast<CCScale9Sprite*>(pBatchNode->getParent());
	if (!pMsg)
		return;
	SIX_CountDown *pCountDown = dynamic_cast<SIX_CountDown*>(pMsg->getParent());
	if (!pCountDown)
		return;

	pCountDown->pBatchNode->removeAllChildrenWithCleanup(true);

	if (pCountDown->m_uCountdown==0)
	{
		if (pCountDown->m_pCallFunc)
			(pCountDown->*pCountDown->m_pCallFunc)();
		pCountDown->removeFromParentAndCleanup(true);
		CC_SAFE_DELETE(pCountDown);
		return;
	}

	pCountDown->m_uCountdown--;

	if (!SIX_Utility::GetInstance()->AddSpriteBatchNodeByNumber(pCountDown->pBatchNode,pCountDown->pNumFile->getCString(),pCountDown->m_uCell,pCountDown->m_uPadding,pCountDown->m_uBitCount,pCountDown->m_uCountdown))
		return;

	// 先放大
	pCountDown->pBatchNode->setScale(5.0f);
	// 再恢复
	CCScaleTo *pScale = CCScaleTo::create(0.1f,1.0f);
	// 剩余执行时间
	CCDelayTime *pDelay = CCDelayTime::create(0.9f);
	// add array
	CCArray *ActionArray = CCArray::create();
	ActionArray->addObject(pScale);
	ActionArray->addObject(pDelay);
	ActionArray->addObject(CCCallFuncN::create(pCountDown->pBatchNode,callfuncN_selector(SIX_CountDown::DoCallBack)));
	CCSequence *pSeq = dynamic_cast<CCSequence*>(CCSequence::create(ActionArray));
	pCountDown->pBatchNode->runAction(pSeq);
	SIXLog("SIX_CountDown.DoCallBack.m_uCountdown[%u]",pCountDown->m_uCountdown);
}

void SIX_CountDown::DoRelease()
{
	stopAllActions();
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE(pNumFile);
}
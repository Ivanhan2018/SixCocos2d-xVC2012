#include "Gold.h"
#include "SIX_Common.h"
#include "Ship.h"
//#include <stack>
//using namespace std;

CGold *g_pGold = NULL;

CGold::CGold()
{
	mfSpeed = 400;
	pBatchNode = 0;
	pGoldDiscBatchNode=0;
	m_poolStep = 100;
	m_GoldPool = m_SilverPool = 0;
}

CGold::~CGold()
{
	Release();
}

// 池回收
void CGold::Release()
{
	// 先释放出池的对象
	int count = 0;
	if (pBatchNode)
	{
		count += pBatchNode->getChildrenCount();
		for (unsigned int j=0;j<pBatchNode->getChildrenCount();j++)
		{
			CCSprite *pSprite = dynamic_cast<CCSprite*>(pBatchNode->getChildren()->objectAtIndex(j));
			if (!pSprite)
				continue;
			pSprite->removeAllChildrenWithCleanup(true);
			pSprite->removeFromParentAndCleanup(true);
			pSprite->release();
		}
		pBatchNode->removeAllChildrenWithCleanup(true);
	}

	//add by Ivan_han 20130727
	if (pGoldDiscBatchNode)
	{
		for (unsigned int j=0;j<pGoldDiscBatchNode->getChildrenCount();j++)
		{
			CCSprite *pSprite = dynamic_cast<CCSprite*>(pGoldDiscBatchNode->getChildren()->objectAtIndex(j));
			if (!pSprite)
				continue;
			pSprite->removeAllChildrenWithCleanup(true);
			pSprite->removeFromParentAndCleanup(true);
			pSprite->release();
		}
		pGoldDiscBatchNode->removeAllChildrenWithCleanup(true);
	}

	// 再释放池里的对象
	if (m_GoldPool)
	{
		SIXLog("Release.Begin.m_GoldPool.count[%d].count[%d]",m_GoldPool->GetCount(),count);
		while (m_GoldPool->GetCount()>0)
		{
			CCSprite *pSprite = m_GoldPool->Pop();
			if (!pSprite)
				continue;
			pSprite->removeAllChildrenWithCleanup(true);
			pSprite->removeFromParentAndCleanup(true);
			pSprite->release();
		}
		SIXLog("Release.End.m_GoldPool.count[%d]",m_GoldPool->GetCount());
		CC_SAFE_DELETE(m_GoldPool);
	}

	if (m_SilverPool)
	{
		SIXLog("Release.Begin.m_SilverPool.count[%d].count[%d]",m_SilverPool->GetCount(),count);
		while (m_SilverPool->GetCount()>0)
		{
			CCSprite *pSprite = m_SilverPool->Pop();
			if (!pSprite)
				continue;
			pSprite->removeAllChildrenWithCleanup(true);
			pSprite->removeFromParentAndCleanup(true);
			pSprite->release();
		}
		SIXLog("Release.End.m_SilverPool.count[%d]",m_SilverPool->GetCount());
		CC_SAFE_DELETE(m_SilverPool);
	}
}

void CGold::Init(CCNode *pBG,int poolStep)
{
	mBG = dynamic_cast<CCLayerColor *>(pBG);

	m_poolStep = poolStep;
	
	m_GoldPool = new SIX_TList<CCSprite*>;
	GoldPoolExpansion();

	m_SilverPool = new SIX_TList<CCSprite*>;
	SilverPoolExpansion();

	if (!pBatchNode)
	{
		pBatchNode = CCSpriteBatchNode::create("Scene/Game/GunBulletGold.png");
		pBG->addChild(pBatchNode);
	}

	//add by Ivan_han 20130727
	if (!pGoldDiscBatchNode)
	{
		pGoldDiscBatchNode = CCSpriteBatchNode::create("Scene/Game/GoldDisc.png");
		pBG->addChild(pGoldDiscBatchNode);
	}
}

void CGold::GoldPoolExpansion()
{
	if (!m_GoldPool)
		return;

	if (m_poolStep<=0)
		m_poolStep = 100;

	// 金币
	unsigned int oldsize = m_GoldPool->GetCount();
	for (int i=0;i<m_poolStep;i++)
	{
		CCSprite *pSpr = CCSprite::createWithSpriteFrameName("gold_1.png");
		if (!pSpr)
			continue;
		pSpr->setVisible(false);
		pSpr->setTag(TYPE_GOLD);
		pSpr->autorelease();
		pSpr->retain();
		pSpr->retain();
		m_GoldPool->Push(pSpr);
	}
	SIXLog("GoldPoolExpansion.gold[%u->%d][%u].Done!",oldsize,oldsize+m_poolStep,m_GoldPool->GetCount());
}

void CGold::SilverPoolExpansion()
{
	if (!m_SilverPool)
		return;

	if (m_poolStep<=0)
		m_poolStep = 100;

	// 银币
	unsigned int oldsize = m_SilverPool->GetCount();
	for (int i=0;i<m_poolStep;i++)
	{
		CCSprite *pSpr = CCSprite::createWithSpriteFrameName("silver_1.png");
		if (!pSpr)
			continue;
		pSpr->setVisible(false);
		pSpr->setTag(TYPE_SILVER);
		pSpr->autorelease();
		pSpr->retain();
		pSpr->retain();
		m_SilverPool->Push(pSpr);
	}
	SIXLog("GoldPoolExpansion.silver[%u->%d][%u].Done!",oldsize,oldsize+m_poolStep,m_SilverPool->GetCount());
}

CCSprite *CGold::AddOneNumber(int i)
{
	//add by Ivan_han 20130720
	CCSprite *pNumber=NULL;
	if(i<0||i>10)
		return NULL;
	static CCRect s_RectNumber[11]={CCRect(0,0,38,37),CCRect(38,0,32,37),CCRect(70,0,38,37),CCRect(108,0,36,37),CCRect(144,0,38,37),CCRect(182,0,38,37),CCRect(220,0,38,37),CCRect(258,0,34,37),CCRect(292,0,38,37),CCRect(330,0,36,37),CCRect(366,0,32,37)};
	//static CCPoint s_PosNumber[11]={ccp(100,200),ccp(140,200),ccp(180,200),ccp(220,200),ccp(260,200),ccp(300,200),ccp(340,200),ccp(380,200),ccp(420,200),ccp(460,200),ccp(500,200)};
	CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GoldDisc_Number.png");
	if(pSpriteFrame)
	{
		CCTexture2D *pTexture=pSpriteFrame->getTexture();
		const CCPoint Offset=pSpriteFrame->getOffset();
		pNumber=CCSprite::spriteWithTexture(pTexture,CCRect(s_RectNumber[i].origin.x-Offset.x,s_RectNumber[i].origin.y-Offset.y,s_RectNumber[i].size.width,s_RectNumber[i].size.height));
		//pNumber->setPosition(s_PosNumber[i]);
	}
	return pNumber;
}

vector<TNumPos> CGold::GetNumPosArr(int goldValue,bool bShowMult)
{
	TNumPos NumPos[11]={0};
	int a[11]={0},i=0; 
	int num=goldValue;
	while(num) 
	{  
		a[i]=num%10;//a[i]存储第i位的数字
		NumPos[i].i=a[i];
		num/=10;
		i++; 
	}
	int length=i;
	if(goldValue==0)
	{
		a[0]=0;
		NumPos[0].i=0;
		length=1;
	}
	if(bShowMult)
	{
		a[length]=10;//10代表乘号
		NumPos[length].i=10;
		length+=1;
	}
	vector<TNumPos> ret(NumPos,NumPos+length);
	//求最高位数字精灵的位置x,y
	float xs[5]={0,77,66,46,32};
	float y=80;
	float x=xs[0];
	if(length<5)
		x=xs[length];
	int xk=x;
	static CCRect s_RectNumber[11]={CCRect(0,0,38,37),CCRect(38,0,32,37),CCRect(70,0,38,37),CCRect(108,0,36,37),CCRect(144,0,38,37),CCRect(182,0,38,37),CCRect(220,0,38,37),CCRect(258,0,34,37),CCRect(292,0,38,37),CCRect(330,0,36,37),CCRect(366,0,32,37)};
	if(bShowMult)
	{
		xk=20;
		y=-20;
	}	
	for(int k=length-1;k>=0;k--)
	{
		int Num=NumPos[k].i;
		ret[k].x=xk;
		ret[k].y=y;
		xk+=s_RectNumber[Num].size.width-4;
	}
	return ret;
}

void CGold::Del(CCNode *node)
{
	CCSprite *pSprite = dynamic_cast<CCSprite*>(node);
	if (!pSprite)
		return;

	// 改为归池
	// Cool.Cat
	int type = pSprite->getTag();
	if (type==TYPE_GOLD)
	{
		pSprite->setVisible(false);
		g_pGold->m_GoldPool->Push(pSprite);
	}
	else if (type==TYPE_SILVER)
	{
		pSprite->setVisible(false);
		g_pGold->m_SilverPool->Push(pSprite);
	}
	else
	{
		pSprite->removeAllChildrenWithCleanup( true );
	}
	pSprite->removeFromParentAndCleanup( true );
}

void CGold::CountGold(int goldValue,int *gold,int *silver)
{
	//*gold = goldValue/100;
	//*silver = (goldValue - *gold*100) / 10;
	*gold = goldValue>10?1:0;
	*silver =1-(*gold);
}

void CGold::createOneGold(CCNode *node, CCPoint fishPT, CCPoint PlayerPT, int goldType, int index, int total)
{
	// 出池
	// Cool.Cat
	CCSprite *pSprite = 0;
	if (goldType==1)
	{
		pSprite = m_GoldPool->Pop();
		if (!pSprite)
		{
			SIXLog("池里没金币啦，开始扩容 ...");
			GoldPoolExpansion();
			pSprite = m_GoldPool->Pop();
		}
	}
	else if (goldType==2)
	{
		pSprite = m_SilverPool->Pop();
		if (!pSprite)
		{
			SIXLog("池里没银币啦，开始扩容 ...");
			SilverPoolExpansion();
			pSprite = m_SilverPool->Pop();
		}
	}

	if (!pSprite)
		return;

	//CCSprite *pSprite = CCSprite::createWithSpriteFrameName( pStrPath->getCString() );
	CCSize rcSize = pSprite->getContentSize();
	CCPoint Postion = CCPoint(fishPT.x - (rcSize.width-1)*total/2 + (rcSize.width-1)*index, fishPT.y - rcSize.height/2);
	// -- 捕获鱼位置为中心点，横向排列，横向金币间距 -1
	pSprite->setPosition( Postion );
	
	CCArray *pArray = CCArray::create();
	char typeArr[][32] = {
		"gold_%d.png",
		"silver_%d.png"
	};

	CCString *pStrPath = 0;
	for (int i=1; i<15; i++)
	{
		pStrPath = CCString::createWithFormat(typeArr[goldType-1],i);
		CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pStrPath->getCString() );
		if (!pSpriteFrame)
			break;
		pArray->addObject( pSpriteFrame );
	}

	pSprite->setVisible(true);
	pSprite->runAction( CCRepeatForever::create( CCAnimate::create( CCAnimation::createWithSpriteFrames( pArray, 0.09f ) ) ) );
	
	CCJumpBy *JumpByAction = CCJumpBy::create(0.3f, CCPointMake(0,150), 50, 1);
	CCMoveTo *BounceOutMove = CCMoveTo::create( 0.9f, CCPoint(Postion.x, Postion.y) );
	CCEaseBounceOut *BounceOut = CCEaseBounceOut::create(BounceOutMove);
	// 两点间距离
	float fDistance = sqrt( pow(PlayerPT.x - fishPT.x,  2)  + pow(PlayerPT.y - fishPT.y,  2) );
	// 金币动画需要的时间
	float fTime = fDistance / mfSpeed;
	CCMoveTo *pMove = CCMoveTo::create( fTime, PlayerPT );
	CCArray *ActionArray = CCArray::create();
	ActionArray->addObject(JumpByAction);
	ActionArray->addObject(BounceOut);
	ActionArray->addObject(pMove);
	//ActionArray->addObject(CCCallFuncN::create(node,callfuncN_selector(CGold::Del)));
	ActionArray->addObject(CCCallFuncN::create(pSprite,callfuncN_selector(CGold::Del)));
	CCSequence *SequenceRun = dynamic_cast<CCSequence*>(CCSequence::create(ActionArray));
	pSprite->runAction( SequenceRun );
	if (pBatchNode)
		pBatchNode->addChild(pSprite);
	else
		node->addChild( pSprite );
}

void CGold::showGold(int goldValue, CCPoint fishPT, long long llUserID)
{
	if (NULL == mBG)
		return;

	CShip *pShip = g_pShipMgr->getShip( llUserID );
	CCPoint PlayerPT = pShip->getGunPos();
	int nDirection = g_pShipMgr->getPlayerDirection( llUserID );
	PlayerPT.y = (0 == nDirection) ? MAX_HEIGHT : 0;

	//add by Ivan_han 20130725
	vector<TNumPos> ret=CGold::GetNumPosArr(goldValue,true);
	for(unsigned int i=0;i<ret.size();i++)
	{
		CCSprite *pNumber=AddOneNumber(ret[i].i);
		if(pNumber)
		{
			pNumber->setPosition(ccpAdd(fishPT,ccp(ret[i].x,ret[i].y)));
			CCArray *ActionArray = CCArray::create();
			CCDelayTime *pDelayTime = CCDelayTime::create(0.8f);
			ActionArray->addObject(pDelayTime);
			ActionArray->addObject(CCCallFuncN::create(pNumber/*mBG*/,callfuncN_selector(CGold::Del)));
			CCSequence *SequenceRun = dynamic_cast<CCSequence*>(CCSequence::create(ActionArray));
			pNumber->runAction( SequenceRun );
			//mBG->addChild( pNumber );
			if (pGoldDiscBatchNode)
				pGoldDiscBatchNode->addChild(pNumber);
			else
				mBG->addChild(pNumber);
		}
	}

	int gold=0;
	int silver = 0;
	CountGold( goldValue ,&gold,&silver);
	
	for (int i=0;i<gold;i++)
		createOneGold(mBG, fishPT, PlayerPT, 1, i, gold);
	
	for (int i=0;i<silver;i++)
		createOneGold(mBG, fishPT, PlayerPT, 2, i, silver);

	// 掉币音效
	// Cool.Cat
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(24,false);
}

void CGold::AddOneGoldDisc(int goldValue, CCPoint fishPT, long long llUserID)
{
	if (NULL == mBG)
		return;

	CCString *pStrPath =CCString::create("GoldDisc_1.png");
	CCSprite *pSprite = CCSprite::createWithSpriteFrameName( pStrPath->getCString() );
	pSprite->setPosition( fishPT );

	vector<TNumPos> ret=CGold::GetNumPosArr(goldValue,false);
	for(unsigned int i=0;i<ret.size();i++)
	{
		CCSprite *pNumber=AddOneNumber(ret[i].i);
		if(pNumber)
		{
			pSprite->addChild(pNumber);
			pNumber->setPosition(ccp(ret[i].x,ret[i].y));
		}
	}


	CCArray *pArray = CCArray::create();

	for (int i=1; i<12; i++)
	{
		pStrPath = CCString::createWithFormat("GoldDisc_%d.png",i);
		CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( pStrPath->getCString() );
		if (!pSpriteFrame)
			break;
		pArray->addObject( pSpriteFrame );
	}

	pSprite->runAction( CCRepeatForever::create( CCAnimate::create( CCAnimation::createWithSpriteFrames( pArray, 0.09f ) ) ) );

	CCArray *ActionArray = CCArray::create();
	CCDelayTime *pDelayTime = CCDelayTime::create(2);
	ActionArray->addObject(pDelayTime);
	ActionArray->addObject(CCCallFuncN::create(pSprite/*mBG*/,callfuncN_selector(CGold::Del)));
	CCSequence *SequenceRun = dynamic_cast<CCSequence*>(CCSequence::create(ActionArray));
	pSprite->runAction( SequenceRun );
	//mBG->addChild( pSprite );
	if (pGoldDiscBatchNode)
		pGoldDiscBatchNode->addChild(pSprite);
	else
		mBG->addChild(pSprite);

	// 炸弹音效
	SIX_GlobalMgr::GetInstance()->GetMusicMgr()->playEffect(25,false);
}
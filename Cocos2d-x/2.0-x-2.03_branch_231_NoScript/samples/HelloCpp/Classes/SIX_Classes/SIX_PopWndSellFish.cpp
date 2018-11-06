#include "SIX_PopWndSellFish.h"
#include "Ship.h"
#include "SIX_SceneGame.h"

int ARR_FISHSAMPLE[] = {1,2,3,4,5,6,7,8,9,10,15,18,20,25,30,40,12,112,113};
int ARR_FISHSAMPLE_COUNT = sizeof(ARR_FISHSAMPLE)/sizeof(int);

extern SIX_SceneGame *pSceneGame;

SIX_PopWndSellFish::SIX_PopWndSellFish()
{

}

SIX_PopWndSellFish::~SIX_PopWndSellFish()
{

}

SIX_PopWndSellFish *SIX_PopWndSellFish::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	if (0.0001 > x && 0.0001 > y)
	{
		CCSize szWind = CCDirector::sharedDirector()->getWinSize();
		x = (szWind.width - width) / 2;
		y = (szWind.height - height) / 2;
	}

	SIX_PopWndSellFish *pSellFish = new SIX_PopWndSellFish();
	if (pSellFish && pSellFish->init())
	{
		pSellFish->initWithColor(color,width,height);
		pSellFish->setPosition(x,y);
		pSellFish->setRedrawBorder(bRedrawBorder);
		pSellFish->setTouchEnabled(true);
		pSellFish->m_ForbiddenTouch = true;
		pSellFish->m_bCloseThenCleanup = bCloseThenCleanup;


	}
	return pSellFish;
}

int SIX_PopWndSellFish::GetIndexFromArray(TFishKind fishType)
{
	for(int i=0;i<ARR_FISHSAMPLE_COUNT;i++)
	{
		if (fishType==ARR_FISHSAMPLE[i])
			return i;
	}
	return -1;
}

unsigned int SIX_PopWndSellFish::getFishCount(int validIdx)const
{
	if(validIdx<0||validIdx>=ARR_FISHSAMPLE_COUNT)
	{
		return 0;
	}
	SIX_NumberBatchNode *pNumber = m_pFishCount[validIdx];
	if (!pNumber)
		return 0;
	unsigned int ret = pNumber->getNumber();
	return ret;
}

void SIX_PopWndSellFish::setFishCount(int validIdx,unsigned int uFishCount)
{
	if(validIdx<0||validIdx>=ARR_FISHSAMPLE_COUNT)
	{
		return;
	}

	SIX_NumberBatchNode *pNumber = m_pFishCount[validIdx];
	if (!pNumber)
		return;
	// 延迟显示动画
	// Cool.Cat
	pNumber->setUserData((void*)uFishCount);
	SIX_Utility::GetInstance()->performWithDelay(pNumber,callfuncN_selector(SIX_PopWndSellFish::doAnimation),0.05f*validIdx);
}

void SIX_PopWndSellFish::doAnimation(CCNode *pNode)
{
	if (!pNode)
		return;
	SIX_NumberBatchNode *pNumber = dynamic_cast<SIX_NumberBatchNode*>(pNode);
	if (!pNumber)
		return;
	unsigned int num = (unsigned int)(pNumber->getUserData());
	pNumber->setNumber(num);
	SIX_Utility::GetInstance()->FixedTexParameters(pNumber->getTexture());
}

bool SIX_PopWndSellFish::init()
{
	if (!SIX_PopWnd::init())
		return false;
	m_pSellAndExit=0;
	m_pSellNoExit=0;
	memset(m_pFishCount,0,sizeof(m_pFishCount));
	m_pFishCoin=0;
	m_pBulletCount=0;
	m_pGoldCoin1=0;
	m_pGoldCoin2=0;
	m_pGoldCoin=0;
	return true;
}

void SIX_PopWndSellFish::onShow()
{
	SIX_PopWnd::onShow();
	CShip *pShip=g_pShipMgr->getMySelfShip();
	if(pShip)
	{
		// 延迟显示捕获每种鱼数量
		for(int i=0;i<StatFishCount;i++)
		{
			setFishCount(i,PlayerTreasureInfo::Instance().m_FishCount[i]);
		}
		// 获得渔币
		if(m_pFishCoin)
		{
			m_pFishCoin->setUserData((void*)pShip->getFishCoin());
			SIX_Utility::GetInstance()->performWithDelay(m_pFishCoin,callfuncN_selector(SIX_PopWndSellFish::doAnimation),0.05f*18);
		}
		// 获得渔币换的金币
		if(m_pGoldCoin1)
		{
			m_pGoldCoin1->setUserData((void*)(pShip->getFishCoin()*PlayerTreasureInfo::Instance().m_iBasePoint));
			SIX_Utility::GetInstance()->performWithDelay(m_pGoldCoin1,callfuncN_selector(SIX_PopWndSellFish::doAnimation),0.05f*19);
		}
		// 剩余子弹
		if(m_pBulletCount)
		{
			m_pBulletCount->setUserData((void*)pShip->getBulletCount());
			SIX_Utility::GetInstance()->performWithDelay(m_pBulletCount,callfuncN_selector(SIX_PopWndSellFish::doAnimation),0.05f*20);
		}
		// 剩余子弹换的金币
		if(m_pGoldCoin2)
		{
			m_pGoldCoin2->setUserData((void*)(pShip->getBulletCount()*PlayerTreasureInfo::Instance().m_iBasePoint));
			SIX_Utility::GetInstance()->performWithDelay(m_pGoldCoin2,callfuncN_selector(SIX_PopWndSellFish::doAnimation),0.05f*21);
		}
		// 合计金币
		if(m_pGoldCoin)
		{
			m_pGoldCoin->setUserData((void*)(pShip->getFishCoin()*PlayerTreasureInfo::Instance().m_iBasePoint+pShip->getBulletCount()*PlayerTreasureInfo::Instance().m_iBasePoint));
			SIX_Utility::GetInstance()->performWithDelay(m_pGoldCoin,callfuncN_selector(SIX_PopWndSellFish::doAnimation),0.05f*22);
		}
	}
}

void SIX_PopWndSellFish::onEnterTransitionDidFinish()
{
	if(!m_pSellAndExit)
	{
		m_pSellAndExit = CreateButtonWithFileCell("Common/SellFish/SellAndExit.png",3);
		if (m_pSellAndExit)
			m_pSellAndExit->setTag(BTN_SellAndExit);
		m_pSellAndExit->setPosition(ccp(115,10));
	}
	if(!m_pSellNoExit)
	{
		m_pSellNoExit = CreateButtonWithFileCell("Common/SellFish/SellNoExit.png",3);
		if (m_pSellNoExit)
			m_pSellNoExit->setTag(BTN_SellNoExit);
		m_pSellNoExit->setPosition(ccp(240,10));
	}
	CCSprite *pFishBg = CCSprite::create("Common/SellFish/FishSample.png");
	if (pFishBg)
	{
		pFishBg->ignoreAnchorPointForPosition(true);
		pFishBg->setPosition(ccp(56,208));
		this->addChild(pFishBg);

		// 每种鱼捕获的数量
		for(int i=0;i<StatFishCount;i++)
		{
			if(!m_pFishCount[i])
			{
				m_pFishCount[i] = SIX_NumberBatchNode::Create("Common/SellFish/num_color.png",10,1.0f,5,ccp(0,0),EFFECT_SCALE,1.5f,0.1f);
				if (!m_pFishCount[i])
					continue;
				// 设置偏移
				int row = i/6;
				int col = i%6;
				m_pFishCount[i]->setPosition(90.0f+col*85.0f,425.0f-row*75.0);
				m_pFishCount[i]->setCellAlignStyle(ALIGN_LEFT);
				m_pFishCount[i]->setNumber(0);
				this->addChild(m_pFishCount[i]);
			}
		}
	}
	// 获得渔币
	if(!m_pFishCoin)
	{
		m_pFishCoin = SIX_NumberBatchNode::Create("Common/SellFish/num_small.png",10,-2.0f,8,ccp(0,0),EFFECT_SCALE,2.0f,0.1f);
		if (m_pFishCoin)
		{
			m_pFishCoin->setCellAlignStyle(ALIGN_LEFT);
			m_pFishCoin->setPosition(177,156);
			m_pFishCoin->setNumber(0);
			this->addChild(m_pFishCoin);
		}
	}
	// 剩余子弹
	if(!m_pBulletCount)
	{
		m_pBulletCount = SIX_NumberBatchNode::Create("Common/SellFish/num_small.png",10,-2.0f,8,ccp(0,0),EFFECT_SCALE,2.0f,0.1f);
		if (m_pBulletCount)
		{
			m_pBulletCount->setCellAlignStyle(ALIGN_LEFT);
			m_pBulletCount->setPosition(ccp(177,127));
			m_pBulletCount->setNumber(0);
			this->addChild(m_pBulletCount);
		}
	}
	// 获得渔币换的金币
	if(!m_pGoldCoin1)
	{
		m_pGoldCoin1 = SIX_NumberBatchNode::Create("Common/SellFish/num_small.png",10,-2.0f,8,ccp(0,0),EFFECT_SCALE,2.0f,0.1f);
		if (m_pGoldCoin1)
		{
			m_pGoldCoin1->setCellAlignStyle(ALIGN_LEFT);
			m_pGoldCoin1->setPosition(ccp(437,156));
			m_pGoldCoin1->setNumber(0);
			this->addChild(m_pGoldCoin1);
		}
	}
	// 剩余子弹换的金币
	if(!m_pGoldCoin2)
	{
		m_pGoldCoin2 = SIX_NumberBatchNode::Create("Common/SellFish/num_small.png",10,-2.0f,8,ccp(0,0),EFFECT_SCALE,2.0f,0.1f);
		if (m_pGoldCoin2)
		{
			m_pGoldCoin2->setCellAlignStyle(ALIGN_LEFT);
			m_pGoldCoin2->setPosition(ccp(437,127));
			m_pGoldCoin2->setNumber(0);
			this->addChild(m_pGoldCoin2);
		}
	}
	// 合计金币
	if(!m_pGoldCoin)
	{
		m_pGoldCoin = SIX_NumberBatchNode::Create("Common/SellFish/num_big.png",10,-2.0f,8,ccp(0,0),EFFECT_SCALE,3.0f,0.1f);
		if (m_pGoldCoin)
		{
			m_pGoldCoin->setCellAlignStyle(ALIGN_LEFT);
			m_pGoldCoin->setPosition(ccp(320,80));
			m_pGoldCoin->setNumber(0);
			this->addChild(m_pGoldCoin);
		}
	}
}

bool SIX_PopWndSellFish::OnBtn(CCObject* pObject,int tag)
{
	if(tag==BTN_SellAndExit)
	{
		SIX_Proxy::GetInstance()->SetChangeScene(true);
		Show(false);
		return true;
	}
	if(tag==BTN_SellNoExit)
	{
		pSceneGame->WriteScore();
		Show(false);
		return true;
	}
	return true;
}


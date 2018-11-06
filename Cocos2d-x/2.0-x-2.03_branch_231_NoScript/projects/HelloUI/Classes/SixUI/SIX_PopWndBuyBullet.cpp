#include "SIX_PopWndBuyBullet.h"
//#include "Ship.h"
//#include "SIX_ClientRoom.h"

SIX_PopWndBuyBullet::SIX_PopWndBuyBullet()
{

}

SIX_PopWndBuyBullet::~SIX_PopWndBuyBullet()
{

}

SIX_PopWndBuyBullet *SIX_PopWndBuyBullet::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
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

	SIX_PopWndBuyBullet *pBuyBullet = new SIX_PopWndBuyBullet();
	if (pBuyBullet && pBuyBullet->init())
	{
		pBuyBullet->initWithColor(color,width,height);
		pBuyBullet->setPosition(x,y);
		pBuyBullet->setRedrawBorder(bRedrawBorder);
		pBuyBullet->setTouchEnabled(true);
		//pBuyBullet->m_ForbiddenTouch = true;
		pBuyBullet->m_bCloseThenCleanup = bCloseThenCleanup;


	}
	return pBuyBullet;
}

bool SIX_PopWndBuyBullet::IsAutoBuy()const
{
	if(m_pBulletOn)
		return m_pBulletOn->isVisible();
	return false;
}

bool SIX_PopWndBuyBullet::init()
{
	if (!SIX_PopWnd::init())
		return false;
	m_pGoldCoin[0]=0;
	m_pGoldCoin[1]=0;
	m_pGoldCoin[2]=0;
	m_pBullet100=0;
	m_pBullet500=0;
	m_pBullet2000=0;
	m_pBulletOn=0;
	m_pBulletOff=0;
	return true;
}

void SIX_PopWndBuyBullet::onEnterTransitionDidFinish()
{
	//if (pCancel)
	//{
	//	pCancel->setPosition(370,35);
	//}
	static CCPoint s_PosGoldCoin[3]={ccp(85,152),ccp(220,152),ccp(355,152)};
	static const char *s_GoldCoin[3]={"1000金币","5000金币","20000金币"};
	static int s_BulletNum[3]={100,500,2000};
	for(int i=0;i<3;i++)
	{
		if(!m_pGoldCoin[i])
		{
			m_pGoldCoin[i]=CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(s_GoldCoin[i]).c_str(), "微软雅黑", 18);
			m_pGoldCoin[i]->setPosition(s_PosGoldCoin[i]);
			m_pGoldCoin[i]->ignoreAnchorPointForPosition(true);
			m_pGoldCoin[i]->setColor(ccc3(238,199,16));
			this->addChild(m_pGoldCoin[i]);
		}
		//if(m_pGoldCoin[i] && PlayerTreasureInfo::Instance().m_iBasePoint>0)
		{
			  char sz[100]={0};
#ifdef WIN32
			  //_itoa(PlayerTreasureInfo::Instance().m_iBasePoint*s_BulletNum[i],sz,10);
#else
			  //snprintf(sz,99,"%d",PlayerTreasureInfo::Instance().m_iBasePoint*s_BulletNum[i]);
#endif
			  strcat(sz,SIX_Utility::GetInstance()->G2U("金币").c_str());
			  m_pGoldCoin[i]->setString(sz);
			  //SIX_Utility::GetInstance()->FixedTexParameters(m_pGoldCoin[i]->getTexture());
		}
	}
	if(!m_pBullet100)
	{
		m_pBullet100 = CreateButtonWithFileCell("Common/BuyBullet/buy.png",3);
		if (m_pBullet100)
		{
			m_pBullet100->setTag(BTN_Bullet100);
			m_pBullet100->setPosition(ccp(65,110));
		}
	}
	if(!m_pBullet500)
	{
		m_pBullet500 = CreateButtonWithFileCell("Common/BuyBullet/buy.png",3);
		if (m_pBullet500)
		{
			m_pBullet500->setTag(BTN_Bullet500);
			m_pBullet500->setPosition(ccp(200,110));
		}
	}
	if(!m_pBullet2000)
	{
		m_pBullet2000 = CreateButtonWithFileCell("Common/BuyBullet/buy.png",3);
		if (m_pBullet2000)
		{
			m_pBullet2000->setTag(BTN_Bullet2000);
			m_pBullet2000->setPosition(ccp(335,110));
		}
	}
	if(!m_pBulletOn)
	{
		//m_pBulletOn = CreateButtonWithFile("Common/BuyBullet/check.png");
		//m_pBulletOn = CreateButtonWithFileCell(m_pBulletOn,"Common/BuyBullet/On.png",2);
		m_pBulletOn = CreateButtonWithFile("Common/BuyBullet/check.png",CCRect(24,0,24,23));
		if (m_pBulletOn)
		{
			m_pBulletOn->setTag(BTN_BulletOn);
			m_pBulletOn->setPosition(ccp(70,65));
			m_pBulletOn->setVisible(false);
		}
	}
	if(!m_pBulletOff)
	{
		//m_pBulletOff = CreateButtonWithFile("Common/BuyBullet/check.png");
		//m_pBulletOff = CreateButtonWithFileCell(m_pBulletOff,"Common/BuyBullet/Off.png",2);
		m_pBulletOff = CreateButtonWithFile("Common/BuyBullet/check.png",CCRect(0,0,23,23));
		if (m_pBulletOff)
		{
			m_pBulletOff->setTag(BTN_BulletOff);
			m_pBulletOff->setPosition(ccp(70,65));
			m_pBulletOff->setVisible(true);
		}
	}
	//if(!m_switchControl)
	//{
	//	m_switchControl= CCControlSwitch::create(
	//		CCSprite::create("extensions/switch-mask.png"),
	//		CCSprite::create("Common/BuyBullet/CheckOnOff.png",CCRect(0,0,20,19)),
	//		CCSprite::create("Common/BuyBullet/CheckOnOff.png",CCRect(20,0,20,19)),
	//		CCSprite::create("extensions/switch-thumb.png")//,
	//		//CCLabelTTF::create("On", "Arial-BoldMT", 16),
	//		//CCLabelTTF::create("Off", "Arial-BoldMT", 16)
	//		);
	//	m_switchControl->setDefaultTouchPriority(this->m_nPriority-1);
	//	m_switchControl->setPosition(ccp(100,50)); 
	//	m_switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(SIX_PopWndBuyBullet::callbackSwitch), CCControlEventValueChanged);
	//	this->addChild(m_switchControl);
	//	callbackSwitch(m_switchControl,CCControlEventValueChanged);
	//}
}

bool SIX_PopWndBuyBullet::OnBtn(CCObject* pObject,int tag)
{
	if(tag==BTN_BulletOn)
	{
		m_pBulletOn->setVisible(false);
		m_pBulletOff->setVisible(true);
		m_pBulletOn->setTouchEnabled(false);
		m_pBulletOff->setTouchEnabled(true);
		//CCTouchHandler *pHandlerOn = CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(m_pBulletOn);
		//if (pHandlerOn)
		//	pHandlerOn->setTouchEventPause(true);
		//CCTouchHandler *pHandlerOff = CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(m_pBulletOff);
		//if (pHandlerOff)
		//	pHandlerOff->setTouchEventPause(false);
		//m_pBulletOff->setPosition(ccp(72,79));
		//m_pBulletOn->setPosition(ccp(172,79));
		//int PriorityOn=m_pBulletOn->getDefaultTouchPriority();
		//int PriorityOff=m_pBulletOff->getDefaultTouchPriority();
		//if(PriorityOff!=-1024)
		//	m_pBulletOff->setDefaultTouchPriority(-1024);
		//m_pBulletOn->setDefaultTouchPriority(-1023);
		return true;
	}
	if(tag==BTN_BulletOff)
	{
		m_pBulletOn->setVisible(true);
		m_pBulletOff->setVisible(false);
		m_pBulletOn->setTouchEnabled(true);
		m_pBulletOff->setTouchEnabled(false);
		//CCTouchHandler *pHandlerOn = CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(m_pBulletOn);
		//if (pHandlerOn)
		//	pHandlerOn->setTouchEventPause(false);
		//CCTouchHandler *pHandlerOff = CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(m_pBulletOff);
		//if (pHandlerOff)
		//	pHandlerOff->setTouchEventPause(true);
		//m_pBulletOff->setPosition(ccp(172,79));
		//m_pBulletOn->setPosition(ccp(72,79));
		//int PriorityOn=m_pBulletOn->getDefaultTouchPriority();
		//int PriorityOff=m_pBulletOff->getDefaultTouchPriority();
		//if(PriorityOn!=-1024)
		//	m_pBulletOn->setDefaultTouchPriority(-1024);
		//m_pBulletOff->setDefaultTouchPriority(-1023);
		return true;
	}
	if(tag==BTN_Bullet100)
	{
		return OnBuyBtn(100);
	}
	if(tag==BTN_Bullet500)
	{
		return OnBuyBtn(500);
	}
	if(tag==BTN_Bullet2000)
	{
		return OnBuyBtn(2000);
	}
	return true;
}

bool SIX_PopWndBuyBullet::OnBuyBtn(int iBulletNum)
{
	// 发包给服务器
	//int iBulletNum=100;
	/*USER_BUY_BULLET BuyBullet;
	BuyBullet.llUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	BuyBullet.iBulletNum = iBulletNum;
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_BUY_BULLET, &BuyBullet,sizeof(USER_BUY_BULLET));*/

	Show(false);
	return true;
}

#include "SIX_PopWndPlayerInfo.h"
#include "SIX_PlayerMgr.h"

SIX_PopWndPlayerInfo::~SIX_PopWndPlayerInfo()
{
}

SIX_PopWndPlayerInfo *SIX_PopWndPlayerInfo::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
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

	SIX_PopWndPlayerInfo *pWndPlayerInfo = new SIX_PopWndPlayerInfo();
	if (pWndPlayerInfo && pWndPlayerInfo->init())
	{
		pWndPlayerInfo->initWithColor(color,width,height);
		pWndPlayerInfo->setPosition(x,y);
		pWndPlayerInfo->setRedrawBorder(bRedrawBorder);
		pWndPlayerInfo->setTouchEnabled(true);
		pWndPlayerInfo->m_ForbiddenTouch = true;
		pWndPlayerInfo->m_bCloseThenCleanup = bCloseThenCleanup;
		pWndPlayerInfo->setObjName("SIX_PopWndSetting");
		//pWndPlayerInfo->setRectDirty();
	}
	return pWndPlayerInfo;
}

bool SIX_PopWndPlayerInfo::init()
{
	if (!SIX_PopWnd::init())
		return false;
	m_pBgLogo = 0;
	m_pNickName = m_pMoney = m_pLevel = m_pLevelDesc = m_pWinRound = m_pTotalRound = 0;
	m_pLevelIco = 0;
	m_PlayerViewId = 0;
	return true;
}

bool SIX_PopWndPlayerInfo::ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
	// 相对GL坐标系
	CCPoint pos = pTouch->getLocation();
	// 如果点击坐标不在自身区域，隐藏自身
	CCRect rcPopWnd = CCRect(this->getPositionX(),this->getPositionY(),this->getContentSize().width,this->getContentSize().height);
	if (!rcPopWnd.containsPoint(pos))
	{
		this->Show(false);
		return true;
	}
	return SIX_PopWnd::ccTouchBegan(pTouch,pEvent);
}

void SIX_PopWndPlayerInfo::setPlayerLogo(long long llSysLogoID)
{
	// 玩家头像
	if (!m_pBgLogo)
	{
		CCString *pstrPath = CCString::createWithFormat("face_%lld.jpg", llSysLogoID);
		m_pBgLogo = CCSprite::create(pstrPath->getCString());
		if (!m_pBgLogo)
			return;
		m_pBgLogo->ignoreAnchorPointForPosition(true);
		m_pBgLogo->setContentSize(CCSize(130,130));
		m_pBgLogo->setPosition(ccp(25,25));
		this->addChild(m_pBgLogo);
	}
	else
	{
		CCString *pstrPath = CCString::createWithFormat("face_%lld.jpg", llSysLogoID);
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pstrPath->getCString());
		m_pBgLogo->setTexture(pTexture);
	}
}

void SIX_PopWndPlayerInfo::setPlayerNickName(const char *name)
{
	// 玩家昵称
	if (!m_pNickName)
	{
		m_pNickName = CCLabelTTF::create();
		m_pNickName->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
		m_pNickName->setFontSize(30);
		m_pNickName->setColor(ccc3(228,178,91));
		m_pNickName->setOpacity(255);
		m_pNickName->ignoreAnchorPointForPosition(true);
		m_pNickName->setPosition(ccp(170,125));
		m_pNickName->setDimensions(CCSize(170,40));
		this->addChild(m_pNickName);
	}
	m_pNickName->setString(SIX_Utility::GetInstance()->G2U(name).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(m_pNickName->getTexture(),true);
}

void SIX_PopWndPlayerInfo::setPlayerMoney(int money)
{
	// 玩家资产
	if (!m_pMoney)
	{
		m_pMoney = CCLabelTTF::create();
		m_pMoney->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
		m_pMoney->setFontSize(16);
		m_pMoney->setColor(ccc3(255,255,255));
		m_pMoney->setOpacity(255);
		m_pMoney->ignoreAnchorPointForPosition(true);
		m_pMoney->setPosition(ccp(170,100));
		m_pMoney->setDimensions(CCSize(170,20));
		this->addChild(m_pMoney);
	}
	m_pMoney->setString(SIX_Utility::GetInstance()->G2U(CCString::createWithFormat(/*当前资产：%d*/XorStr<0xAA,13,0x42AA0F76>("\x1F\x1A\x6B\x1D\x79\x65\x02\x4B\x11\x09\x91\xD1"+0x42AA0F76).s,money)->getCString()).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(m_pMoney->getTexture(),true);
}

void SIX_PopWndPlayerInfo::setPlayerLevel(int level)
{
	// 游戏等级
	if (!m_pLevel)
	{
		m_pLevel = CCLabelTTF::create();
		m_pLevel->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
		m_pLevel->setFontSize(16);
		m_pLevel->setColor(ccc3(255,255,255));
		m_pLevel->setOpacity(255);
		m_pLevel->ignoreAnchorPointForPosition(true);
		m_pLevel->setPosition(ccp(170,75));
		m_pLevel->setDimensions(CCSize(120,20));
		this->addChild(m_pLevel);
	}
	m_pLevel->setString(SIX_Utility::GetInstance()->G2U(CCString::createWithFormat(/*游戏等级：Lv%d*/XorStr<0x68,15,0x2117853C>("\xBB\xA7\xA5\xDC\xD9\xA5\xD2\xD9\xD3\xCB\x3E\x05\x51\x11"+0x2117853C).s,level)->getCString()).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(m_pLevel->getTexture(),true);
}

void SIX_PopWndPlayerInfo::setPlayerWinRound(int round)
{
	// 已赢牌局
	if (!m_pWinRound)
	{
		m_pWinRound = CCLabelTTF::create();
		m_pWinRound->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
		m_pWinRound->setFontSize(16);
		m_pWinRound->setColor(ccc3(255,255,255));
		m_pWinRound->setOpacity(255);
		m_pWinRound->ignoreAnchorPointForPosition(true);
		m_pWinRound->setPosition(ccp(170,50));
		m_pWinRound->setDimensions(CCSize(170,20));
		this->addChild(m_pWinRound);
	}
	m_pWinRound->setString(SIX_Utility::GetInstance()->G2U(CCString::createWithFormat(/*已赢牌局：%d*/XorStr<0xAD,13,0x41EB6E54>("\x7F\x7F\x7C\x1E\x74\x74\x0D\x62\x16\x0C\x92\xDC"+0x41EB6E54).s,round)->getCString()).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(m_pWinRound->getTexture(),true);
}

void SIX_PopWndPlayerInfo::setPlayerTotalRound(int round)
{
	// 已玩牌局
	if (!m_pTotalRound)
	{
		m_pTotalRound = CCLabelTTF::create();
		m_pTotalRound->setFontName(/*微软雅黑*/XorStr<0x8D,9,0x252C9508>("\x43\x2C\x47\x7D\x40\x57\x29\x4E"+0x252C9508).s);
		m_pTotalRound->setFontSize(16);
		m_pTotalRound->setColor(ccc3(255,255,255));
		m_pTotalRound->setOpacity(255);
		m_pTotalRound->ignoreAnchorPointForPosition(true);
		m_pTotalRound->setPosition(ccp(170,25));
		m_pTotalRound->setDimensions(CCSize(170,20));
		this->addChild(m_pTotalRound);
	}
	m_pTotalRound->setString(SIX_Utility::GetInstance()->G2U(CCString::createWithFormat(/*已玩牌局：%d*/XorStr<0xF3,13,0xD9573F8C>("\x21\x25\x38\x10\x32\x3E\x47\x2C\x58\x46\xD8\x9A"+0xD9573F8C).s,round)->getCString()).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(m_pTotalRound->getTexture(),true);
}

void SIX_PopWndPlayerInfo::setPlayerViewId(int idx)
{
	m_PlayerViewId = idx;
	RefreshUI();
}

int SIX_PopWndPlayerInfo::getPlayerViewId()
{
	return m_PlayerViewId;
}

void SIX_PopWndPlayerInfo::RefreshUI()
{
	// 视图ID转逻辑ID
	int LogicID = SIX_PlayerMgr::getLogicID(m_PlayerViewId,SIX_PlayerMgr::GetInstance()->getMySeatIdx());

	SinglePlayer *pSinglePlayer = &SIX_PlayerMgr::GetInstance()->m_Players[LogicID];
	if (pSinglePlayer && pSinglePlayer->UserIdx>0)
	{
		this->setPlayerNickName(pSinglePlayer->szNickname);
		this->setPlayerMoney(pSinglePlayer->lGoldLogin);
		this->setPlayerLevel(0);
		this->setPlayerWinRound(0);
		this->setPlayerTotalRound(0);
		this->setPlayerLogo(pSinglePlayer->lSysLogoID);
	}
}

void SIX_PopWndPlayerInfo::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	// just for test!!!
	// Cool.Cat
	setPlayerLogo(0);
	setPlayerNickName(/*Player*/XorStr<0x1E,7,0x8D9E3C20>("\x4E\x73\x41\x58\x47\x51"+0x8D9E3C20).s);
	setPlayerMoney(0);
	setPlayerLevel(0);
	setPlayerWinRound(0);
	setPlayerTotalRound(0);
}
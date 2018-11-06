#include "OperalayerBJL.h"
#include "SimpleAudioEngine.h"
#include "ddz/CMD_DDZClient.h"
#include "msgDispatch/MsgDispatch.h"
#include "common/CocosUnits.h"
#include "DDZRes.h"
#define BTN_ANIM_TIME						0.25f								//按钮动画时间
#define BTN_PRESSED							  100								//按钮被按下
#define BTN_NOT_PRESSED						    0								//按钮没被按下

CCRect chipPosRect1[8] = {
	CCRect(0,180,212,116),
	CCRect(225,180,350,80),
	CCRect(586,180,212,116),
	CCRect(0,120,200,60),
	CCRect(590,120,200,60),
	CCRect(217,108,367,68),
	CCRect(0,298,224,70),
	CCRect(576,298,224,70)
};

float chipWidth1 = 83*0.8;
float chipHeight1 = 72*0.8;
int addRandSeedStaticPoint(CCPoint point)
{
	int  MaxAddRandSeed ;	
	for(int i = 0 ; i < 8 ; i++)
	{
		CCRect rect = chipPosRect1[i];
		rect.size.width-=chipWidth1;
		rect.size.height-=chipHeight1;
		if(rect.containsPoint(point))
		{
			MaxAddRandSeed = i;
		}
	}
	return MaxAddRandSeed;
}
OperaLayer::OperaLayer()
{
	currentChipSprite = NULL;
	chipOfMine = CCArray::create();
	chipOfMine->retain();
	indexScore0 = 0;
	indexScore1 = 0;
	indexScore2 = 0;
	indexScore3 = 0;
	indexScore4 = 0;
	indexScore5 = 0;
	indexScore6 = 0;
	indexScore7 = 0;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(OperaLayer::PlacelinitUnClickTouch), "UpdatePlacelinitUnClickTouch", NULL);

	
}

OperaLayer::~OperaLayer()
{
	if (chipOfMine != NULL)
	{
		CC_SAFE_DELETE(chipOfMine);
		chipOfMine = NULL;
	}
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "UpdatePlacelinitUnClickTouch");

}

OperaLayer * OperaLayer::create()
{
	OperaLayer *operaLayer = new OperaLayer();
	if (operaLayer&&operaLayer->initOperaLayer())
	{
		operaLayer->autorelease();
		return operaLayer;
	}	
	CC_SAFE_DELETE(operaLayer);
	return NULL;
}

bool OperaLayer::initOperaLayer()
{
	bool bRet = false;
	do 
	{
		isControl = false;
		IsXIazhuNumber = false;
		stasteat = 0;
		nodeScale = 1;
		winSize = CCDirector::sharedDirector()->getWinSize();

		anode = CCNode::create();	
		anode->setAnchorPoint(CCPointZero);
		anode->setPosition(ccp(0,0));
		this->addChild(anode, 3);
		m_pCKPX_100Sprite_1 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_1.png"));
		m_pCKPX_100Sprite_2 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_1.png"));
		m_pCKPX_1000Sprite_1 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_10.png"));
		m_pCKPX_1000Sprite_2 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_10.png"));
		m_pGRYZ_1WSprite_1 =CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_100.png"));
		m_pGRYZ_1WSprite_2 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_100.png"));
		m_pGRYZ_10WSprite_1 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_1000.png"));
		m_pGRYZ_10WSprite_2 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_1000.png"));
		m_pCKPX_100WSprite_1 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_10000.png"));
		m_pCKPX_100WSprite_2 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_10000.png"));
		m_pGRYZ_500WSprite_1 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_50000.png"));
		m_pGRYZ_500WSprite_2 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_50000.png"));
		m_pGRYZ_1000WSprite_1 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_100000.png"));
		m_pGRYZ_1000WSprite_2 = CCSprite::createWithSpriteFrame(spriteFrame("BJL_diss_100000.png"));
		m_pCKPX_100Image = CCMenuItemSprite::create(m_pCKPX_100Sprite_1,m_pCKPX_100Sprite_2,this,menu_selector(OperaLayer::menuCloseCallbackboy));
		m_pCKPX_100Image->setTag(m_pCKPX_100EnumItem);
		m_pCKPX_100Image->setScale(0.8);
	    m_pCKPX_1000Image = CCMenuItemSprite::create(m_pCKPX_1000Sprite_1,m_pCKPX_1000Sprite_2,this,menu_selector(OperaLayer::menuCloseCallbackboy));
		m_pCKPX_1000Image->setTag(m_pCKPX_1000EnumItem);
		m_pCKPX_1000Image->setScale(0.8);
		m_pGRYZ_1WImage = CCMenuItemSprite::create(m_pGRYZ_1WSprite_1,m_pGRYZ_1WSprite_2,this,menu_selector(OperaLayer::menuCloseCallbackboy));
		m_pGRYZ_1WImage->setTag(m_pGRYZ_1WEnumItem);  
		m_pGRYZ_1WImage->setScale(0.8);
		m_pGRYZ_10WImage = CCMenuItemSprite::create(m_pGRYZ_10WSprite_1,m_pGRYZ_10WSprite_2,this,menu_selector(OperaLayer::menuCloseCallbackboy));
		m_pGRYZ_10WImage->setTag(m_pGRYZ_10WEnumItem);
		m_pGRYZ_10WImage->setScale(0.8);
		m_pGRYZ_100WImage = CCMenuItemSprite::create(m_pCKPX_100WSprite_1,m_pCKPX_100WSprite_2,this,menu_selector(OperaLayer::menuCloseCallbackboy));
		m_pGRYZ_100WImage->setTag(m_pGRYZ_100WEnumItem);
		m_pGRYZ_100WImage->setScale(0.8);
		m_pGRYZ_500WImage = CCMenuItemSprite::create(m_pGRYZ_500WSprite_1,m_pGRYZ_500WSprite_2,this,menu_selector(OperaLayer::menuCloseCallbackboy));
		m_pGRYZ_500WImage->setTag(m_pGRYZ_500WEnumItem);
		m_pGRYZ_500WImage->setScale(0.8);
		m_pGRYZ_1000WImage = CCMenuItemSprite::create(m_pGRYZ_1000WSprite_1,m_pGRYZ_1000WSprite_2,this,menu_selector(OperaLayer::menuCloseCallbackboy));
		m_pGRYZ_1000WImage->setTag(m_pGRYZ_1000WEnumItem);
		m_pGRYZ_1000WImage->setScale(0.8);
		pCloseMenu_100 = CCMenu::create(m_pCKPX_100Image,NULL);
	    pCloseMenu_100->setAnchorPoint(ccp(0,0));
		pCloseMenu_100->setTouchEnabled(false);
		pCloseMenu_100->setPosition(ccp(winSize.width*0.45,winSize.height*0.1));
		this->addChild(pCloseMenu_100,3);
		pCloseMenu_1000 = CCMenu::create(m_pCKPX_1000Image,NULL);
		pCloseMenu_1000->setAnchorPoint(ccp(0,0));
		pCloseMenu_1000->setTouchEnabled(false);
		pCloseMenu_1000->setPosition(ccp(winSize.width*0.53,winSize.height*0.1));
		this->addChild(pCloseMenu_1000,3);	
		pCloseMenu_1W = CCMenu::create(m_pGRYZ_1WImage,NULL);
		pCloseMenu_1W->setAnchorPoint(ccp(0,0));
		pCloseMenu_1W->setTouchEnabled(false);
		pCloseMenu_1W->setPosition(ccp(winSize.width*0.61,winSize.height*0.1));
		this->addChild(pCloseMenu_1W,3);	
		pCloseMenu_10W = CCMenu::create(m_pGRYZ_10WImage,NULL);
		pCloseMenu_10W->setAnchorPoint(ccp(0,0));
		pCloseMenu_10W->setTouchEnabled(false);
		pCloseMenu_10W->setPosition(ccp(winSize.width*0.69,winSize.height*0.1));
		this->addChild(pCloseMenu_10W,3);	
		pCloseMenu_100W = CCMenu::create(m_pGRYZ_100WImage,NULL);
		pCloseMenu_100W->setAnchorPoint(ccp(0,0));
		pCloseMenu_100W->setTouchEnabled(false);
		pCloseMenu_100W->setPosition(ccp(winSize.width*0.77,winSize.height*0.1));
		this->addChild(pCloseMenu_100W,3);	
		pCloseMenu_500W= CCMenu::create(m_pGRYZ_500WImage,NULL);
		pCloseMenu_500W->setAnchorPoint(ccp(0,0));
		pCloseMenu_500W->setTouchEnabled(false);
		pCloseMenu_500W->setPosition(ccp(winSize.width*0.85,winSize.height*0.1));
		this->addChild(pCloseMenu_500W,3);		
		pCloseMenu_1000W= CCMenu::create(m_pGRYZ_1000WImage,NULL);
		pCloseMenu_1000W->setAnchorPoint(ccp(0,0));
		pCloseMenu_1000W->setTouchEnabled(false);
		pCloseMenu_1000W->setPosition(ccp(winSize.width*0.93,winSize.height*0.1));
		this->addChild(pCloseMenu_1000W,3);	
		initOpenRaChipTTf();
		setTouchEnabled(true);
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		bRet = true;
	}while (0);
	return bRet;
}
void OperaLayer::initOpenRaChipTTf()
{
	for (int i = 0;i<8;i++)
	{
		m_pTotalChipValueTTf[i] = CCLabelAtlas::create("",texture_name::s_ChipMagerNumber,12,17,'0');
		m_pTotalChipValueTTf[i]->setAnchorPoint(CCPointZero);
		m_pTotalChipValueTTf[i]->setColor(ccc3(255,204,0));
		m_pMySpriteNunber[i] = CCSprite::createWithSpriteFrame(spriteFrame("ME_SCORE_BACK.png"));
		m_pMySpriteNunber[i]->setAnchorPoint(CCPointZero);
		switch (i)
		{
		case 0:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.1+80,winSize.height*0.4));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.1,winSize.height*0.4));
			}break;
		case 1:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.5+80,winSize.height*0.4));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.5,winSize.height*0.4));

			}break;
		case 2:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.8+80,winSize.height*0.4));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.8,winSize.height*0.4));
			}break;
		case 3:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.1+80,winSize.height*0.25));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.1,winSize.height*0.25));

			}break;
		case 4:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.8+80,winSize.height*0.25));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.8,winSize.height*0.25));

			}break;

		case 5:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.5+80,winSize.height*0.25+10));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.5,winSize.height*0.25+10));

			}break;
		case 6:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.1+80,winSize.height*0.65));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.1,winSize.height*0.65));

			}break;
		case 7:
			{
				m_pTotalChipValueTTf[i]->setPosition(ccp(winSize.width *0.8+80,winSize.height*0.65));
				m_pMySpriteNunber[i]->setPosition(ccp(winSize.width*0.8,winSize.height*0.65));
			}break;	
		default:
			break;
		}
		m_pTotalChipValueTTf[i]->setVisible(false);
		m_pMySpriteNunber[i]->setVisible(false);
		addChild(m_pMySpriteNunber[i],1);
        addChild(m_pTotalChipValueTTf[i],2);
	}
}

void OperaLayer::showOperMenut()
{
	pCloseMenu_100->setVisible(true);
	pCloseMenu_1000->setVisible(true);
	pCloseMenu_1W->setVisible(true);
	pCloseMenu_10W->setVisible(true);
	pCloseMenu_100W->setVisible(true);
	pCloseMenu_500W->setVisible(true);
	pCloseMenu_1000W->setVisible(true);
}

void OperaLayer::remaggerdisflase()
{
//	pCloseMenu->setVisible(false);
}
void OperaLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	//单点触摸
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	//多点触摸
	pDirector->getTouchDispatcher()->addStandardDelegate(this, 0);
}
bool OperaLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{	
		//	CCPoint pSpritepis = pSprite->getPosition();
		//获得触摸点在屏幕坐标系下的坐标
		//CCPoint location = pTouch->getLocationInView();
		////将其转化为OpenGl坐标
		//location = CCDirector::sharedDirector()->convertToGL(location);
		////再对应到anode节点自己的坐标系
		//location = anode->convertTouchToNodeSpace(pTouch);
		//CCPoint heropos ;
		//CCRect heroRect;
		//if (stasteat == 1)
		//{	
		//	heropos = pCKPX_100->getPosition();
		//	//锚点似乎在中心哦
		//	heroRect = CCRectMake(heropos.x - (pCKPX_100->getContentSize().width/2),
		//		heropos.y - (pCKPX_100->getContentSize().height/2), 
		//		pCKPX_100->getContentSize().width, pCKPX_100->getContentSize().height);
		//	if (nodeScale != 1)
		//	{
		//		heroRect.setRect(heropos.x - ((pCKPX_100->getContentSize().width) * nodeScale / 2), heropos.y - ((pCKPX_100->getContentSize().height) * nodeScale / 2), (pCKPX_100->getContentSize().width) * nodeScale, (pCKPX_100->getContentSize().height) * nodeScale);
		//	}
		//}else if (stasteat == 2)
		//{
		//	heropos = pCKPX_1000->getPosition();
		//	//锚点似乎在中心哦
		//	heroRect = CCRectMake(heropos.x - (pCKPX_1000->getContentSize().width/2),
		//		heropos.y - (pCKPX_1000->getContentSize().height/2), 
		//		pCKPX_1000->getContentSize().width, pCKPX_1000->getContentSize().height);

		//	if (nodeScale != 1)
		//	{
		//		heroRect.setRect(heropos.x - ((pCKPX_1000->getContentSize().width) * nodeScale / 2),
		//			heropos.y - ((pCKPX_1000->getContentSize().height) * nodeScale / 2),
		//			(pCKPX_1000->getContentSize().width) * nodeScale, 
		//			(pCKPX_1000->getContentSize().height) * nodeScale);
		//	}
		//}else if (stasteat == 3)
		//{
		//	heropos = pCKPX_1W->getPosition();
		//	//锚点似乎在中心哦
		//	heroRect = CCRectMake(heropos.x - (pCKPX_1W->getContentSize().width/2),
		//		heropos.y - (pCKPX_1W->getContentSize().height/2), 
		//		pCKPX_1W->getContentSize().width, pCKPX_1W->getContentSize().height);

		//	if (nodeScale != 1)
		//	{
		//		heroRect.setRect(heropos.x - ((pCKPX_1W->getContentSize().width) * nodeScale / 2),
		//			heropos.y - ((pCKPX_1W->getContentSize().height) * nodeScale / 2),
		//			(pCKPX_1W->getContentSize().width) * nodeScale, 
		//			(pCKPX_1W->getContentSize().height) * nodeScale);
		//	}
		//}else if (stasteat == 4)
		//{
		//	heropos = pCKPX_10W->getPosition();
		//	//锚点似乎在中心哦
		//	heroRect = CCRectMake(heropos.x - (pCKPX_10W->getContentSize().width/2),
		//		heropos.y - (pCKPX_10W->getContentSize().height/2), 
		//		pCKPX_10W->getContentSize().width, pCKPX_10W->getContentSize().height);

		//	if (nodeScale != 1)
		//	{
		//		heroRect.setRect(heropos.x - ((pCKPX_10W->getContentSize().width) * nodeScale / 2),
		//			heropos.y - ((pCKPX_10W->getContentSize().height) * nodeScale / 2),
		//			(pCKPX_10W->getContentSize().width) * nodeScale, 
		//			(pCKPX_10W->getContentSize().height) * nodeScale);
		//	}
		//}else if (stasteat == 5)
		//{
		//	heropos = pCKPX_100W->getPosition();
		//	//锚点似乎在中心哦
		//	heroRect = CCRectMake(heropos.x - (pCKPX_100W->getContentSize().width/2),
		//		heropos.y - (pCKPX_100W->getContentSize().height/2), 
		//		pCKPX_100W->getContentSize().width, pCKPX_100W->getContentSize().height);

		//	if (nodeScale != 1)
		//	{
		//		heroRect.setRect(heropos.x - ((pCKPX_100W->getContentSize().width) * nodeScale / 2),
		//			heropos.y - ((pCKPX_100W->getContentSize().height) * nodeScale / 2),
		//			(pCKPX_100W->getContentSize().width) * nodeScale, 
		//			(pCKPX_100W->getContentSize().height) * nodeScale);
		//	}
		//}else if (stasteat == 6)
		//{
		//	heropos = pCKPX_500W->getPosition();
		//	//锚点似乎在中心哦
		//	heroRect = CCRectMake(heropos.x - (pCKPX_500W->getContentSize().width/2),
		//		heropos.y - (pCKPX_500W->getContentSize().height/2), 
		//		pCKPX_500W->getContentSize().width, pCKPX_500W->getContentSize().height);

		//	if (nodeScale != 1)
		//	{
		//		heroRect.setRect(heropos.x - ((pCKPX_500W->getContentSize().width) * nodeScale / 2),
		//			heropos.y - ((pCKPX_500W->getContentSize().height) * nodeScale / 2),
		//			(pCKPX_500W->getContentSize().width) * nodeScale, 
		//			(pCKPX_500W->getContentSize().height) * nodeScale);
		//	}
		//}else if (stasteat == 7)
		//{
		//	heropos = pCKPX_1000W->getPosition();
		//	//锚点似乎在中心哦
		//	heroRect = CCRectMake(heropos.x - (pCKPX_1000W->getContentSize().width/2),
		//		heropos.y - (pCKPX_1000W->getContentSize().height/2), 
		//		pCKPX_1000W->getContentSize().width, pCKPX_1000W->getContentSize().height);

		//	if (nodeScale != 1)
		//	{
		//		heroRect.setRect(heropos.x - ((pCKPX_1000W->getContentSize().width) * nodeScale / 2),
		//			heropos.y - ((pCKPX_1000W->getContentSize().height) * nodeScale / 2),
		//			(pCKPX_1000W->getContentSize().width) * nodeScale, 
		//			(pCKPX_1000W->getContentSize().height) * nodeScale);
		//	}
		//}
	return true;
}
void OperaLayer::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	//2.在ccTouchMoved中，若布尔型的全局变量为true，说明在ccTouchBegan中触点已经控制主角，并根据触摸点的横纵坐标设置主角位置
	if (isControl)
	{
		CCPoint location = touch->getLocationInView();
		location = CCDirector::sharedDirector()->convertToGL(location);
		location = anode->convertTouchToNodeSpace(touch);
		currentChipSprite->setPosition(location);
		return;
		if(stasteat == 1)
		{
			pCKPX_100->setPosition(ccp(location.x, location.y));
		}else if(stasteat == 2)
		{
			pCKPX_1000->setPosition(ccp(location.x, location.y));
		}else if(stasteat == 3)
		{
			pCKPX_1W->setPosition(ccp(location.x, location.y));
		}else if(stasteat == 4)
		{
			pCKPX_10W->setPosition(ccp(location.x, location.y));
		}else if(stasteat == 5)
		{
			pCKPX_100W->setPosition(ccp(location.x, location.y));
		}else if(stasteat == 6)
		{
			pCKPX_500W->setPosition(ccp(location.x, location.y));
		}
		else if (stasteat == 7)
		{
			pCKPX_1000W->setPosition(ccp(location.x, location.y));
		}
	}
}

void OperaLayer::ccTouchCancelled( CCTouch* touch, CCEvent* event )
{
	//isControl = false;
}

void OperaLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	//变量定义
	BYTE cbBuffer[sizeof(CMD_C_PlaceBet)];
	memset(cbBuffer, 0 , sizeof(CMD_C_PlaceBet));
	CMD_C_PlaceBet *PlaceBet = (CMD_C_PlaceBet *)cbBuffer;
	CCPoint location = pTouch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	bool bRet = false;
	for(int i = 0 ; i < 8 ; i++)
	{
		CCRect rect = chipPosRect1[i];
		rect.size.width-=chipWidth1;
		rect.size.height-=chipHeight1;
		//判断点击的点是否在精灵自身的范围内，也就是判断是否点击了精灵：
		if(rect.containsPoint(location))
		{
			bRet = true;
			//构造变量
			PlaceBet->cbBetArea = addRandSeedStaticPoint(location);
			if (isControl)
			{
				chipOfMine->addObject(currentChipSprite);
			}
			break;
		}
	}
	if (!bRet) //判断是否成功下注
	{
		if (currentChipSprite && isControl)
		{
			currentChipSprite->setVisible(false);
			chipOfMine->addObject(currentChipSprite);
		}

	}
	PlaceBet->lBetScore = 0;
	if (bRet == true&&isControl == true)
	{
		if (PlaceBet->cbBetArea == 0)
		{
			indexScore0+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore0)->getCString());
		}else if (PlaceBet->cbBetArea == 1)
		{
			indexScore1+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore1)->getCString());
		}else if (PlaceBet->cbBetArea == 2)
		{
			indexScore2+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore2)->getCString());
		}else if (PlaceBet->cbBetArea == 3)
		{
			indexScore3+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore3)->getCString());
		}else if (PlaceBet->cbBetArea == 4)
		{
			indexScore4+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore4)->getCString());
		}else if (PlaceBet->cbBetArea == 5)
		{
			indexScore5+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore5)->getCString());
		}else if (PlaceBet->cbBetArea == 6)
		{
			indexScore6+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore6)->getCString());
		}else if (PlaceBet->cbBetArea == 7)
		{
			indexScore7+=XIazNumberScore;
			PlaceBet->lBetScore = XIazNumberScore;
			m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setString(CCString::createWithFormat("%d",indexScore7)->getCString());
		}	

		m_pTotalChipValueTTf[PlaceBet->cbBetArea]->setVisible(true);
		m_pMySpriteNunber[PlaceBet->cbBetArea]->setVisible(true);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("UpdatePlacelBankScore", CCInteger::create(PlaceBet->lBetScore));

		EntityMgr::instance()->getDispatch()->sendSocketDate(SUB_C_PLACE_JETTON,PlaceBet,sizeof(CMD_C_PlaceBet));
	}
	isControl = false;
}
void OperaLayer::initClickTouch()
{
	ManNumberScore = g_GlobalUnits.getGolbalUserData()->lScore;
   schedule(schedule_selector(OperaLayer::update),0.1f);
}

void OperaLayer::dissUnclickTouch()
{
	pCloseMenu_100->setTouchEnabled(false);
	pCloseMenu_1000->setTouchEnabled(false);
	pCloseMenu_1W->setTouchEnabled(false);
	pCloseMenu_10W->setTouchEnabled(false);
	pCloseMenu_100W->setTouchEnabled(false);
	pCloseMenu_500W->setTouchEnabled(false);
	pCloseMenu_1000W->setTouchEnabled(false);
	m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_1.png"));
	m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10.png"));
	m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100.png"));
	m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_1000.png"));
	m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10000.png"));
	m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_50000.png"));
	m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
}

void OperaLayer::menuCloseCallbackboy( CCObject* obj )
{
	IsXIazhuNumber = true;
	int tag = dynamic_cast<CCNode*>(obj)->getTag();
	isControl = true;
	//触屏检测
	setTouchEnabled(true);
	switch (tag)
	{
		case m_pCKPX_100EnumItem:
		{
			stasteat = 1;
			XIazNumberScore = 100;
			currentChipSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_Cannger_1.png"));;
			currentChipSprite->setScale(0.8);
			currentChipSprite->setTag(m_pGRYZ_ChipSpriteWEnumItem);
			currentChipSprite->setAnchorPoint(ccp(0, 0));
			currentChipSprite->setPosition(ccp(winSize.width*0.45, winSize.height*0.1));
			chipOfMine->addObject(currentChipSprite);
			anode->addChild(currentChipSprite, 1);
			isControl = true;
			break;
		}
		case m_pCKPX_1000EnumItem:
		{
			stasteat = 2;
			XIazNumberScore = 1000;
			currentChipSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_Cannger_10.png"));
			CCRect rect = currentChipSprite->boundingBox();   //获取矩形区域
			currentChipSprite->setScale(0.8);
			currentChipSprite->setAnchorPoint(ccp(0, 0));
			currentChipSprite->setPosition(ccp(winSize.width*0.53, winSize.height*0.1));
			chipOfMine->addObject(currentChipSprite);
			currentChipSprite->setTag(m_pGRYZ_ChipSpriteWEnumItem);
			anode->addChild(currentChipSprite, 1);
			isControl = true;
			break;
		}
		case m_pGRYZ_1WEnumItem:
		{
			stasteat = 3;
			XIazNumberScore = 10000;
			currentChipSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_Cannger_100.png"));
			CCRect rect = currentChipSprite->boundingBox();   //获取矩形区域
			currentChipSprite->setScale(0.8);
			currentChipSprite->setAnchorPoint(ccp(0, 0));
			currentChipSprite->setPosition(ccp(winSize.width * 061, winSize.height*0.1));
			chipOfMine->addObject(currentChipSprite);
			currentChipSprite->setTag(m_pGRYZ_ChipSpriteWEnumItem);
			anode->addChild(currentChipSprite, 1);
			isControl = true;
			break;
		}
		case m_pGRYZ_10WEnumItem:
		{
			stasteat = 4;
			XIazNumberScore = 100000;
			currentChipSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_Cannger_1000.png"));
			CCRect rect = currentChipSprite->boundingBox();   //获取矩形区域
			currentChipSprite->setScale(0.8);
			currentChipSprite->setTag(m_pGRYZ_ChipSpriteWEnumItem);
			currentChipSprite->setAnchorPoint(ccp(0, 0));
			currentChipSprite->setPosition(ccp(winSize.width*0.69, winSize.height*0.1));
			chipOfMine->addObject(currentChipSprite);
			anode->addChild(currentChipSprite, 1);
			isControl = true;
			break;
		}
		case m_pGRYZ_100WEnumItem:
		{
			stasteat = 5;
			XIazNumberScore = 1000000;
			currentChipSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_Cannger_10000.png"));
			CCRect rect = currentChipSprite->boundingBox();   //获取矩形区域
			currentChipSprite->setScale(0.8);
			currentChipSprite->setTag(m_pGRYZ_ChipSpriteWEnumItem);
			currentChipSprite->setAnchorPoint(ccp(0, 0));
			currentChipSprite->setPosition(ccp(winSize.width*0.77, winSize.height*0.1));
			chipOfMine->addObject(currentChipSprite);
			anode->addChild(currentChipSprite, 1);
			isControl = true;
			break;
		}
		case m_pGRYZ_500WEnumItem:
		{
			stasteat = 6;
			XIazNumberScore = 5000000;
			currentChipSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_Cannger_50000.png"));
			CCRect rect = currentChipSprite->boundingBox();   //获取矩形区域
			currentChipSprite->setScale(0.8);
			currentChipSprite->setTag(m_pGRYZ_ChipSpriteWEnumItem);
			currentChipSprite->setAnchorPoint(ccp(0, 0));
			currentChipSprite->setPosition(ccp(winSize.width*0.85, winSize.height*0.1));
			chipOfMine->addObject(currentChipSprite);
			anode->addChild(currentChipSprite, 1);
			isControl = true;
			break;
		}
		case m_pGRYZ_1000WEnumItem:
		{
			stasteat = 7;
			XIazNumberScore = 10000000;
			currentChipSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_Cannger_100000.png"));
			CCRect rect = currentChipSprite->boundingBox();   //获取矩形区域
			currentChipSprite->setScale(0.8);
			currentChipSprite->setTag(m_pGRYZ_ChipSpriteWEnumItem);
			currentChipSprite->setAnchorPoint(ccp(0, 0));
			currentChipSprite->setPosition(ccp(winSize.width*0.93, winSize.height*0.1));
			chipOfMine->addObject(currentChipSprite);
			anode->addChild(currentChipSprite, 1);
			isControl = true;
			break;
		}
		default:
		{
			isControl = false;
			currentChipSprite = NULL;
			break;
		}
	}
}

void OperaLayer::resetManagerOper()
{
	for (int i = 0 ; i < chipOfMine->count() ; i++)
	{
		CCNode *node = (CCNode *)chipOfMine->objectAtIndex(i);
		node->removeFromParentAndCleanup(true);
	}
	CCLog("ChipManagerArray has %d element", chipOfMine->count());
	chipOfMine->removeAllObjects();
	for (int i = 0;i<8;i++)
	{
		m_pTotalChipValueTTf[i]->setVisible(false);
		m_pMySpriteNunber[i]->setVisible(false);
	}
	indexScore0 = 0;
	indexScore1 = 0;
	indexScore2 = 0;
	indexScore3 = 0;
	indexScore4 = 0;
	indexScore5 = 0;
	indexScore6 = 0;
	indexScore7 = 0;
	IsXIazhuNumber = false;
}

void OperaLayer::update( float delta )
{
	unschedule(schedule_selector(OperaLayer::update));
	LONGLONG Score = ManNumberScore;
	CCLOG("wwwwwwwwwwwww = %d",Score);
	if (Score>5000000 &&Score<10000000)
	{
		pCloseMenu_100->setTouchEnabled(true);
		pCloseMenu_1000->setTouchEnabled(true);
		pCloseMenu_1W->setTouchEnabled(true);
		pCloseMenu_10W->setTouchEnabled(true);
		pCloseMenu_100W->setTouchEnabled(true);
		pCloseMenu_500W->setTouchEnabled(true);
		pCloseMenu_1000W->setTouchEnabled(false);
		m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1.png"));
		m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10.png"));
		m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_100.png"));
		m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10000.png"));
		m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_50000.png"));
		m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
	}else if (Score>1000000 &&Score<5000000)
	{
		pCloseMenu_100->setTouchEnabled(true);
		pCloseMenu_1000->setTouchEnabled(true);
		pCloseMenu_1W->setTouchEnabled(true);
		pCloseMenu_10W->setTouchEnabled(true);
		pCloseMenu_100W->setTouchEnabled(true);
		pCloseMenu_500W->setTouchEnabled(false);
		pCloseMenu_1000W->setTouchEnabled(false);
		m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1.png"));
		m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10.png"));
		m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_100.png"));
		m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10000.png"));
		m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_50000.png"));
		m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
	}
	else if (Score>100000 &&Score<1000000)
	{
		pCloseMenu_100W->setTouchEnabled(false);
		pCloseMenu_500W->setTouchEnabled(false);
		pCloseMenu_1000W->setTouchEnabled(false);
		pCloseMenu_100->setTouchEnabled(true);
		pCloseMenu_1000->setTouchEnabled(true);
		pCloseMenu_1W->setTouchEnabled(true);
		pCloseMenu_10W->setTouchEnabled(true);
		m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1.png"));
		m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10.png"));
		m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_100.png"));
		m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10000.png"));
		m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_50000.png"));
		m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
	}
	else if (Score>10000 &&Score<100000)
	{
		pCloseMenu_100->setTouchEnabled(true);
		pCloseMenu_1000->setTouchEnabled(true);
		pCloseMenu_1W->setTouchEnabled(true);
		pCloseMenu_100W->setTouchEnabled(false);
		pCloseMenu_500W->setTouchEnabled(false);
		pCloseMenu_1000W->setTouchEnabled(false);
		pCloseMenu_10W->setTouchEnabled(false);
		m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1.png"));
		m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10.png"));
		m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_100.png"));
		m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_1000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10000.png"));
		m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_50000.png"));
		m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
	}
	else if (Score>1000 &&Score<10000)
	{
		pCloseMenu_100->setTouchEnabled(true);
		pCloseMenu_1000->setTouchEnabled(true);
		pCloseMenu_100W->setTouchEnabled(false);
		pCloseMenu_500W->setTouchEnabled(false);
		pCloseMenu_1000W->setTouchEnabled(false);
		pCloseMenu_10W->setTouchEnabled(false);
		pCloseMenu_1W->setTouchEnabled(false);
		m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1.png"));
		m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_10.png"));
		m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100.png"));
		m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_1000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10000.png"));
		m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_50000.png"));
		m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
	}else if (Score>100 &&Score<1000)
	{
		pCloseMenu_100->setTouchEnabled(true);
		pCloseMenu_1000->setTouchEnabled(false);
		pCloseMenu_1W->setTouchEnabled(false);
		pCloseMenu_10W->setTouchEnabled(false);
		pCloseMenu_100W->setTouchEnabled(false);
		pCloseMenu_500W->setTouchEnabled(false);
		pCloseMenu_1000W->setTouchEnabled(false);
		m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_Cannger_1.png"));
		m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10.png"));
		m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100.png"));
		m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_1000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10000.png"));
		m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_50000.png"));
		m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
	}
	else if (Score>0 &&Score<100)
	{
		pCloseMenu_100->setTouchEnabled(false);
		pCloseMenu_1000->setTouchEnabled(false);
		pCloseMenu_1W->setTouchEnabled(false);
		pCloseMenu_10W->setTouchEnabled(false);
		pCloseMenu_100W->setTouchEnabled(false);
		pCloseMenu_500W->setTouchEnabled(false);
		pCloseMenu_1000W->setTouchEnabled(false);
		m_pCKPX_100Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_1.png"));
		m_pCKPX_1000Sprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10.png"));
		m_pGRYZ_1WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100.png"));
		m_pGRYZ_10WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_1000.png"));
		m_pCKPX_100WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_10000.png"));
		m_pGRYZ_500WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_50000.png"));
		m_pGRYZ_1000WSprite_1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_diss_100000.png"));
	}
	CCLog("fccccc");

}

void OperaLayer::PlacelinitUnClickTouch( CCObject *obl )
{
	ManNumberScore = ((CCInteger *)obl)->getValue();
	schedule(schedule_selector(OperaLayer::update),0.1f);
}






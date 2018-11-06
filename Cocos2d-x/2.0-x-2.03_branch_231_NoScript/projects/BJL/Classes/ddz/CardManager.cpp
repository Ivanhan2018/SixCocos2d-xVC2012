/***************************************
 牌管理类
 游戏界面
 xxxx 2013.1.5
 ***************************************/

#include "CardManager.h"
#include "common/CocosUnits.h"
#include "globalUnits/GlobalUnits.h"
#include "ddz/DDZRes.h"
using namespace cocos2d;
    
//索引定义
#define INDEX_PLAYER				0									//闲家索引
#define INDEX_BANKER				1									//庄家索引
CardManager *CardManager::create()
{
	CardManager *cardManager = new CardManager();
	if (cardManager&&cardManager->initCardManager())
	{
		cardManager->autorelease();
		return cardManager;
	}	
	CC_SAFE_DELETE(cardManager);
	return NULL;
}

bool CardManager::initCardManager()
{
	bool bRet = false;
	do 
	{
		Winsize = CCDirector::sharedDirector()->getWinSize();
		m_pUserPlaySprite = CCSprite::createWithSpriteFrame(spriteFrame("GAME_POINT_0.png"));
		m_pUserPlaySprite->setPosition(ccp(Winsize.width/2-90,Winsize.height*0.7));
		m_pUserPlaySprite->setVisible(false);
		addChild(m_pUserPlaySprite);
		m_pUserBankSprite = CCSprite::createWithSpriteFrame(spriteFrame("GAME_POINT_0.png"));
		m_pUserBankSprite->setPosition(ccp(Winsize.width/2+90,Winsize.height*0.7));
		m_pUserBankSprite->setVisible(false);
		addChild(m_pUserBankSprite);

		Player = CCSprite::createWithSpriteFrame(spriteFrame("BJL_27_2.png"));
		Player->setPosition(ccp(Winsize.width/2-90,Winsize.height*0.7-50));
		Player->setVisible(false);
		addChild(Player);

		AndBureauSprite = CCSprite::createWithSpriteFrame(spriteFrame("BJL_27_3.png"));
		AndBureauSprite->setAnchorPoint(CCPointZero);
		AndBureauSprite->setPosition(ccp(Winsize.width/2-60,Winsize.height*0.7-70));
		AndBureauSprite->setVisible(false);
	    addChild(AndBureauSprite);

		Banker = CCSprite::createWithSpriteFrame(spriteFrame("BJL_27_1.png"));
		Banker->setPosition(ccp(Winsize.width/2+90,Winsize.height*0.7-50));
		Banker->setVisible(false);
		addChild(Banker);

		//结束动画
		GAMEoverSprite = CCSprite::create("background/GAME_END.png");
		GAMEoverSprite->setAnchorPoint(CCPointZero);
		GAMEoverSprite->setPosition(ccp(Winsize.width*0.25,Winsize.height));
		addChild(GAMEoverSprite,3);

		initPlayerCard();

		bRet = true;
	} while (0);

	return bRet;
}

void CardManager::initPlayerCard()
{
	for (int i = 0;i < 2;i++)
	{
		playerCard[i].cards[0] = CardSprite::CardSpriteWith(0);
		playerCard[i].cards[1] = CardSprite::CardSpriteWith(0);
		playerCard[i].cards[2] = CardSprite::CardSpriteWith(0);

		playerCard[i].cards[0]->setScale(0.5f);
		playerCard[i].cards[1]->setScale(0.5f);
		playerCard[i].cards[2]->setScale(0.5f);

		playerCard[i].cards[0]->setVisible(false);
		playerCard[i].cards[1]->setVisible(false);
		playerCard[i].cards[2]->setVisible(false);

		addChild(playerCard[i].cards[0],2-i);
		addChild(playerCard[i].cards[1],2-i);
		addChild(playerCard[i].cards[2],2-i);
	}

	playerCard[0].cards[0]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[0].cards[1]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[0].cards[2]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[1].cards[0]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[1].cards[1]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[1].cards[2]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	memset(m_ucHandCardData,0,sizeof(m_ucHandCardData));
	memset(m_bPlayerStatus,0,sizeof(m_bPlayerStatus));
	memset(m_ucDeskCardData,0,sizeof(m_ucDeskCardData));
	for (int i = 0; i < 8; i++)
	{
		PlayhomeTTf[i]  =  CCLabelTTF::create("0","",16);
		PlayhomeTTf[i]->setAnchorPoint(CCPointZero);
		PlayhomeTTf[i]->setColor(ccc3(173,118,0));
		switch (i)
		{
		case 0:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*0.3,Winsize.height*0.25*1.2));
			break;
		case 1:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*0.9,Winsize.height*0.25*1.2));
			break;	
		case 2:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*1.5,Winsize.height*0.25*1.2));
			break;		
		case 3:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*0.3,Winsize.height*0.25*0.8));	
			break;	
		case 4:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*1.5,Winsize.height*0.25*0.8));
			break;	
		case 5:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*0.9,Winsize.height*0.25*0.8));
			break;	
		case 6:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*0.3,Winsize.height*0.25*1.6));
			break;	
		case 7:
			PlayhomeTTf[i]->setPosition(ccp(GAMEoverSprite->getPositionX()*1.5,Winsize.height*0.25*1.6));
			break;		
		default:
			break;
		}
		GAMEoverSprite->addChild(PlayhomeTTf[i],3);
	}
	ScoreGameover  =  CCLabelTTF::create("0","",16);
	ScoreGameover->setPosition(ccp(GAMEoverSprite->getPositionX()*0.5,Winsize.height*0.14));
    ScoreGameover->setColor(ccc3(173,118,0));
	ScoreGameover->setAnchorPoint(CCPointZero);
	GAMEoverSprite->addChild(ScoreGameover,3);
}

void CardManager::showPlayerCardfive()
{
	for (int iChairID=0;iChairID<2;iChairID++)
	{
		playerCard[iChairID].cards[0]->changeCardWith(m_ucHandCardData[0]);
		playerCard[iChairID].cards[1]->changeCardWith(m_ucHandCardData[1]);
		playerCard[iChairID].cards[2]->changeCardWith(m_ucHandCardData[2]);
		playerCard[iChairID].cards[0]->setVisible(true);
		playerCard[iChairID].cards[1]->setVisible(true);
		playerCard[iChairID].cards[2]->setVisible(true);
	}
}
void CardManager::showPlayerCard()
{
	Player->setVisible(true);
	Banker->setVisible(true);
	m_pUserPlaySprite->setVisible(true);
	m_pUserBankSprite->setVisible(true);
	playerCard[0].cards[0]->changeCardWith(m_ucHandCardData[0]);
	playerCard[0].cards[1]->changeCardWith(m_ucHandCardData[1]);
	playerCard[1].cards[0]->changeCardWith(m_ucHandCardData1[0]);
	playerCard[1].cards[1]->changeCardWith(m_ucHandCardData1[1]);
	playerCard[1].cards[0]->setVisible(true);
	playerCard[1].cards[1]->setVisible(true);
	playerCard[0].cards[0]->setVisible(true);
	playerCard[0].cards[1]->setVisible(true);
	SetAnmionPlayOneCard();


}
void CardManager::showPlayerCard1( BYTE m_cbTableCardArray[2][3],BYTE m_cbCardCount[2])
{
	FreehomeThirdCard = false;
	cbBankerCount= GetCardListPip(m_cbTableCardArray[0],2);
	cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],2);	
	if (cbBankerCount<=5 && cbPlayerTwoCardCount<8)
	{
		playerCard[0].cards[2]->changeCardWith(m_ucHandCardData[2]);
		playerCard[0].cards[2]->setVisible(true);
		schedule(schedule_selector(CardManager::SendCardToPlayerRuntion),2.0f);
		FreehomeThirdCard = true;
		m_cbBankerCount= GetCardListPip(m_cbTableCardArray[0],3);//闲家

	}

	BYTE cbPlayerThirdCardValue = 0 ;	//第三张牌点数
	//计算点数
//	cbPlayerThirdCardValue =GetCardPip(m_cbTableCardArray[0][2]);
	cbPlayerThirdCardValue =GetCardListPip(m_cbTableCardArray[0],2);
	BYTE m_cbPlayerTwoCardCount= 0; 

	//闲一点 庄七点  闲拿了第三张牌  庄不拿牌出现问题
	if (cbBankerCount< 8 && cbPlayerTwoCardCount<8)
	{
		switch(cbBankerCount)
		{
		case 0:
			if (FreehomeThirdCard == true &&cbPlayerThirdCardValue !=7 && cbPlayerThirdCardValue !=6)
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			break;
		case 1:
			if (FreehomeThirdCard == true &&cbPlayerThirdCardValue !=7&&cbPlayerThirdCardValue !=4&&cbPlayerThirdCardValue !=6)
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			break;
		case 2:
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			break;
		case 3:
			if(FreehomeThirdCard == true && cbPlayerThirdCardValue != 8 && cbPlayerThirdCardValue != 4)
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);

			}
			else if (FreehomeThirdCard == false) 
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);

			}			
			break;
		case 4:
			if(FreehomeThirdCard == true && cbPlayerThirdCardValue != 1 && cbPlayerThirdCardValue != 8 && cbPlayerThirdCardValue != 9 && cbPlayerThirdCardValue != 0 &&cbPlayerThirdCardValue !=4)
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			else if ( FreehomeThirdCard == false) 
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			break;
		case 5:
			if(FreehomeThirdCard == true && cbPlayerThirdCardValue != 1 && cbPlayerThirdCardValue != 2 
				&& cbPlayerThirdCardValue != 3  && cbPlayerThirdCardValue != 8 &&
				cbPlayerThirdCardValue != 9 &&  cbPlayerThirdCardValue != 0 &&cbPlayerThirdCardValue !=6)
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			else if (FreehomeThirdCard == false) 
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			break;
		case 6:
			if( FreehomeThirdCard == true && ( cbPlayerThirdCardValue == 6 || cbPlayerThirdCardValue == 7 ))
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}else if (FreehomeThirdCard == false &&cbPlayerTwoCardCount !=7)
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.0f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			break;
		case 7:
			if( FreehomeThirdCard == true && ( cbPlayerThirdCardValue == 6 ))
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}else if (FreehomeThirdCard == false )
			{
				playerCard[1].cards[2]->changeCardWith(m_ucHandCardData1[2]);
				playerCard[1].cards[2]->setVisible(true);
				schedule(schedule_selector(CardManager::SendCardToBankThirdCard),2.50f);
				cbPlayerTwoCardCount =GetCardListPip(m_cbTableCardArray[1],3);
			}
			break;
			//不须补牌
		default:
			break;
		}
	}
	char buf1[50];
	char buf2[50];
	sprintf(buf1, "GAME_POINT_%d.png",cbPlayerTwoCardCount);
	m_pUserBankSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf1));
	if (FreehomeThirdCard)
	{
		sprintf(buf2, "GAME_POINT_%d.png",m_cbBankerCount);
		m_pUserPlaySprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf2));
	}else
	{	
		sprintf(buf2, "GAME_POINT_%d.png",cbBankerCount);
		m_pUserPlaySprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf2));
	}
	schedule(schedule_selector(CardManager::SetPlayBankNumber),4.0f);
}
void CardManager::SetPlayBankNumber( float flat )
{
	unschedule(schedule_selector(CardManager::SetPlayBankNumber));
	if (FreehomeThirdCard)
	{
		if (m_cbBankerCount>cbPlayerTwoCardCount){
			SetAnimation(Player,0);
		}else if (m_cbBankerCount<cbPlayerTwoCardCount){
			SetAnimation(Banker,1);
		}else
		{
			AndBureauSprite->setVisible(true);
			Banker->setVisible(false);
			Player->setVisible(false);
		}
	}else{
		if (cbBankerCount>cbPlayerTwoCardCount){
			SetAnimation(Player,0);
		}else if (cbBankerCount<cbPlayerTwoCardCount){
			SetAnimation(Banker,1);
		}else{
			AndBureauSprite->setVisible(true);
			Banker->setVisible(false);
			Player->setVisible(false);
		}
	}
}
void CardManager::updatePlayerCard(int chairID,unsigned char bHandCardData[3])
{
	playerCard[chairID].cards[0]->changeCardWith(bHandCardData[0]);
	playerCard[chairID].cards[1]->changeCardWith(bHandCardData[1]);
	playerCard[chairID].cards[2]->changeCardWith(bHandCardData[2]);
}
void CardManager::resetManager()
{
	Player->setVisible(false);
	Banker->setVisible(false);
	m_pUserPlaySprite->setVisible(false);
	m_pUserBankSprite->setVisible(false);
	AndBureauSprite->setVisible(false);
	playerCard[0].cards[0]->changeCardWith(0);
	playerCard[0].cards[1]->changeCardWith(0);
	playerCard[0].cards[2]->changeCardWith(0);
	playerCard[1].cards[0]->changeCardWith(0);
	playerCard[1].cards[1]->changeCardWith(0);
	playerCard[1].cards[2]->changeCardWith(0);
	playerCard[0].cards[0]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[0].cards[1]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[0].cards[2]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[1].cards[0]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[1].cards[1]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[1].cards[2]->setPosition(ccp(Winsize.width*0.8,Winsize.height));
	playerCard[0].cards[0]->setVisible(false);
	playerCard[0].cards[1]->setVisible(false);
	playerCard[0].cards[2]->setVisible(false);
	playerCard[1].cards[0]->setVisible(false);
	playerCard[1].cards[1]->setVisible(false);
	playerCard[1].cards[2]->setVisible(false);
	memset(m_ucHandCardData,0,sizeof(m_ucHandCardData));
	memset(m_ucHandCardData1,0,sizeof(m_ucHandCardData1));
	memset(m_bPlayerStatus,0,sizeof(m_bPlayerStatus));
	memset(m_ucDeskCardData,0,sizeof(m_ucDeskCardData));
	Player->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_27_2.png"));
	Banker->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_27_1.png"));
	ScoreGameover->setString(CCString::createWithFormat("%d",0)->getCString());
	for (int Index = 0; Index < 8; Index++){
		PlayhomeTTf[Index]->setString(CCString::createWithFormat("%d",0)->getCString());
	}
}

void CardManager::SetHandCardData( unsigned char bHandCardData[] )
{
	memcpy(m_ucHandCardData,bHandCardData,sizeof(m_ucHandCardData));
	m_ucHandCardData[0] = bHandCardData[0];
	m_ucHandCardData[1] = bHandCardData[1];
	m_ucHandCardData[2] = bHandCardData[2];
	return ;
}
void CardManager::SetHandCardData1( unsigned char bHandCardData1[] )
{
	memcpy(m_ucHandCardData1,bHandCardData1,sizeof(m_ucHandCardData1));
	m_ucHandCardData1[0] = bHandCardData1[0];
	m_ucHandCardData1[1] = bHandCardData1[1];
	m_ucHandCardData1[2] = bHandCardData1[2];
}
BYTE CardManager::GetCardPip( BYTE cbCardData )
{
	//计算牌点
	BYTE cbCardValue=GetCardValue(cbCardData);
	BYTE cbPipCount=(cbCardValue>=10)?0:cbCardValue;

	return cbPipCount;
}

BYTE CardManager::GetCardListPip( const BYTE cbCardData[], BYTE cbCardCount )
{
	//变量定义
	BYTE cbPipCount=0;

	//获取牌点
	for (BYTE i=0;i<cbCardCount;i++)
	{
		cbPipCount=(GetCardPip(cbCardData[i])+cbPipCount)%10;
	}
	return cbPipCount;
}

void CardManager::SetAnimation(CCSprite *Sprite,int Number)
{
	char charBuffer[256] = {0};
	CCArray* CardManagerSprite = CCArray::create();
	for(int i = 1; i < 7; i++)
	{
		memset(charBuffer, 0, sizeof(charBuffer));
		if (Number == 0)
		{
			sprintf(charBuffer,"WIN_XIAN_0%d.png",i);
		}else
		{
			sprintf(charBuffer,"WIN_ZHUANG_0%d.png",i);

		}
		CCSpriteFrame* spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(charBuffer);
		CardManagerSprite->addObject(spriteFrame);
	}
	//执行动画函数
	CCAnimation* fish01_catch_act= 
		CCAnimation::createWithSpriteFrames(CardManagerSprite,0.1f);
	fish01_catch_act->setRestoreOriginalFrame(true);
	CCAnimate* action = CCAnimate::create(fish01_catch_act);
	CCFiniteTimeAction*  mFly= NULL;
	//更新
	if (Number == 0)
	{	
		mFly = CCSequence::create(CCCallFuncO::create
			(this, callfuncO_selector(CardManager::afterCatchPalyerUsed),Sprite), NULL);
	}else
	{
		mFly = CCSequence::create(CCCallFuncO::create
			(this, callfuncO_selector(CardManager::afterCatchBankUsed),Sprite), NULL);

	}
	Sprite->stopAllActions();
	Sprite->runAction(CCSequence::create(action,mFly,NULL));
}
void CardManager::afterCatchPalyerUsed( CCObject *obj )
{
	Player->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_27_4.png"));
}

void CardManager::afterCatchBankUsed( CCObject *obj )
{
	Banker->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_27_5.png"));
}
void CardManager::SetAnmionPlayOneCard()
{
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.2f,ccp(Winsize.width*0.8,Winsize.height*0.7-150));
	CCFiniteTimeAction* actionMove2 =CCMoveTo::create( 0.2f,ccp(Winsize.width/2-108,Winsize.height*0.7-150));
	CCFiniteTimeAction*  pCallSendCardBk = CCSequence::create(CCCallFuncO::create
		(this, callfuncO_selector(CardManager::SetAnmionBankoneCard),playerCard[0].cards[0]), NULL);
	playerCard[0].cards[0]->runAction( CCSequence::create(actionMove,actionMove2,pCallSendCardBk, NULL) );

}
void CardManager::SetAnmionBankoneCard( CCObject* obj )
{
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.2f,ccp(Winsize.width*0.8,Winsize.height*0.7-150));
	CCFiniteTimeAction* actionMove2 =CCMoveTo::create( 0.2f,ccp(Winsize.width/2+72,Winsize.height*0.7-150));
	CCFiniteTimeAction* pCallSendCardBk = CCSequence::create(CCCallFuncO::create
		(this, callfuncO_selector(CardManager::SetAnmionPlayTwoCard),playerCard[1].cards[0]), NULL);
	playerCard[1].cards[0]->runAction( CCSequence::create(actionMove,actionMove2,pCallSendCardBk, NULL) );

}

void CardManager::SetAnmionPlayTwoCard( CCObject* obj )
{
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.25f,ccp(Winsize.width*0.8,Winsize.height*0.7-150));
	CCFiniteTimeAction* actionMove2 =CCMoveTo::create( 0.25f,ccp(Winsize.width/2-88,Winsize.height*0.7-150));
	CCFiniteTimeAction* pCallSendCardBk = CCSequence::create(CCCallFuncO::create
		(this, callfuncO_selector(CardManager::SetAnmionBankTwoCard),playerCard[0].cards[1]), NULL);
	playerCard[0].cards[1]->runAction( CCSequence::create(actionMove,actionMove2,pCallSendCardBk, NULL) );
}
void CardManager::SetAnmionBankTwoCard( CCObject* obj )
{
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.25f,ccp(Winsize.width*0.8,Winsize.height*0.7-150));
	CCFiniteTimeAction* actionMove2 =CCMoveTo::create( 0.25f,ccp(Winsize.width/2+92,Winsize.height*0.7-150));
	playerCard[1].cards[1]->runAction( CCSequence::create(actionMove,actionMove2, NULL) );

}
void CardManager::SendCardToPlayerRuntion(float loat)
{
	unschedule(schedule_selector(CardManager::SendCardToPlayerRuntion));
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.2f,ccp(Winsize.width*0.8,Winsize.height*0.7-150));
	CCFiniteTimeAction* actionMove2 =CCMoveTo::create( 0.2f,ccp(Winsize.width/2-68,Winsize.height*0.7-150));
	playerCard[0].cards[2]->runAction( CCSequence::create(actionMove,actionMove2, NULL) );

}
void CardManager::SendCardToBankThirdCard(float loat)
{
	unschedule(schedule_selector(CardManager::SendCardToBankThirdCard));
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.2f,ccp(Winsize.width*0.8,Winsize.height*0.7-150));
	CCFiniteTimeAction* actionMove2 =CCMoveTo::create( 0.2f,ccp(Winsize.width/2+112,Winsize.height*0.7-150));
	playerCard[1].cards[2]->runAction( CCSequence::create(actionMove,actionMove2,NULL));

}
void CardManager::showGameOver()
{
	schedule(schedule_selector(CardManager::showGameOveAnmionTime),7.0f);
}
void CardManager::showGameOveAnmionTime( float dt )
{
	unschedule(schedule_selector(CardManager::showGameOveAnmionTime));
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.2f,ccp(Winsize.width*0.25,Winsize.height*0.25));
	GAMEoverSprite->runAction( CCSequence::create(actionMove, NULL) );
}
void CardManager::remaggerDissGameOver()
{
	CCFiniteTimeAction* actionMove =CCMoveTo::create( 0.2f,ccp(Winsize.width*0.25,Winsize.height));
	GAMEoverSprite->runAction( CCSequence::create(actionMove, NULL) );
}

void CardManager::SetScoreGameOver( LONGLONG lPlayScore,int Index, LONGLONG	lPlayAllScore)
{
	if (lPlayScore !=0)
	{
		PlayhomeTTf[Index]->setString(CCString::createWithFormat("%d",lPlayScore)->getCString());
		ScoreGameover->setString(CCString::createWithFormat("%I64d",lPlayAllScore)->getCString());
	}
}



#include "ViewHandCard.h"
#include "DDZRes.h"
#include "SceneData.h"
#include "DDZLogic.h"
#include "SoundControl.h"

class CCcardDate:public CCInteger
{
public:
	CCcardDate(int v):CCInteger(v){};
	CREATE_FUNC_MSG(CCcardDate);
	bool m_isup;		//是否升起
	bool m_isfocus;		//是否获得焦点
	bool m_isfist;		//是不是选中的第一张牌
	bool m_isselect;	//是否被选中
};

ViewHandCard::ViewHandCard()
{
	memset(m_outCardData,0,sizeof(m_outCardData));
	m_outCardNum = 0;
	m_isOpenCard=false;
}

ViewHandCard::~ViewHandCard()
{
	
}

bool ViewHandCard::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	bool ret =false;
	do 
	{
		m_unallowToucn = false;
		m_distance = 0;
		m_maxDistance = 0;
		m_isRay = true;
		m_isSelect = false;

		for(int i=0;i<20;i++)
		{
			m_leftCardNum[i] = 5 - rand()%10;
			m_rightCardNum[i] = 5 - rand()%10;
		}

		//上家手牌
		m_leftCardNode = CCSpriteBatchNode::create(texture_name::s_card);
		this->addChild(m_leftCardNode);
		//下家手牌
		m_rightCardNode = CCSpriteBatchNode::create(texture_name::s_card);
		this->addChild(m_rightCardNode);

		//上家盖着的扑克牌
		m_hintLeftCardNode = CCSpriteBatchNode::create(texture_name::s_cardTable);
		this->addChild(m_hintLeftCardNode);
		//下家盖着的扑克牌
		m_hintRightCardNode = CCSpriteBatchNode::create(texture_name::s_cardTable);
		this->addChild(m_hintRightCardNode);
		//自己手中的牌
		m_handCardNode =CCNode::create();   
		this->addChild(m_handCardNode);

		m_outCardNodeM=CCNode::create();
		this->addChild(m_outCardNodeM);

		m_outCardNodeL=CCNode::create();
		this->addChild(m_outCardNodeL);

		m_outCardNodeR=CCNode::create();
		this->addChild(m_outCardNodeR);

		m_viewTask =ViewTask::create();									//底牌任务
		this->addChild(m_viewTask);
		
		//底牌（地主牌）
		m_diPaiNode = CCNode::create();
		this->addChild(m_diPaiNode);

// 		m_rightCardNumAtlas = CCLabelAtlas::create("0",texture_name::s_coinNumber,14,19,'0');
// 		m_rightCardNumAtlas->setPosition(size.width-145.f,size.height*0.37+15.0f);
// 		m_rightCardNumAtlas->setVisible(false);
// 		this->addChild(m_rightCardNumAtlas);
// 		m_leftCardNumAtlas = CCLabelAtlas::create("0",texture_name::s_coinNumber,14,19,'0');
// 		m_leftCardNumAtlas->setPosition(130.0f,size.height*0.37+15);
// 		m_leftCardNumAtlas->setVisible(false);
// 		this->addChild(m_leftCardNumAtlas);

		setTouchEnabled(true);
		//setTouchMode(kCCTouchesOneByOne);
		ret =true;
	} while (0);
	return ret;
}

bool ViewHandCard::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_unallowToucn)
	{
		return true;
	}
	m_origin = pTouch->getLocation().x;
	CCPoint pt= pTouch->getLocation();
	CCSize size= CCDirector::sharedDirector()->getWinSize();
	CCObject* pObj=NULL;
	//逆向
	CCARRAY_FOREACH_REVERSE(m_handCardNode->getChildren(),pObj)
	{
		CCSprite* pNode=(CCSprite*)pObj;
		if (pNode && pNode->boundingBox().containsPoint(pt))
		{
			CCcardDate* cardObj = (CCcardDate*)(pNode->getUserObject());
			cardObj->m_isselect = !cardObj->m_isselect;
			cardObj->m_isfist = true;
			cardObj->m_isfocus = true;
			m_isSelect = true;
			pNode->setColor(ccc3(220,220,220));
// 			float _h = (cardObj->m_isup)?0.20f:0.15f;
// 			pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
			break;
		}
	}
	return true;
}

void ViewHandCard::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if(!m_isSelect) return;
	m_distance = abs(pTouch->getLocation().x-m_origin);
	if (m_distance>=m_maxDistance)
	{
		m_isRay = true;
	}else{
		m_isRay = false;
	}
	m_maxDistance = m_distance;
	

	CCPoint pt= pTouch->getLocation();
	CCSize size= CCDirector::sharedDirector()->getWinSize();
	CCObject* pObj=NULL;
	//逆向
	int num = 0;
	CCARRAY_FOREACH_REVERSE(m_handCardNode->getChildren(),pObj)
	{
		CCSprite* pNode=(CCSprite*)pObj;
		if (pNode && pNode->boundingBox().containsPoint(pt))
		{
			num++;
			CCcardDate* cardObj = (CCcardDate*)(pNode->getUserObject());
			if(!cardObj->m_isfocus)
			{
				CCObject * pObj2 = NULL;
				CCARRAY_FOREACH_REVERSE(m_handCardNode->getChildren(),pObj2)
				{
					CCSprite * pNode2 = (CCSprite*)pObj2;
					CCcardDate * cardObj2 = (CCcardDate*)pNode2->getUserObject();
					//收缩状态失去焦点，取消选中扑克牌
					if (!m_isRay&&cardObj2->m_isfocus)
					{
						cardObj2->m_isselect = !cardObj2->m_isselect;
						if (!cardObj2->m_isselect)
						{
							pNode2->setColor(ccc3(255,255,255));
						}else{
							pNode2->setColor(ccc3(220,220,220));
						}
// 						float _h = (cardObj2->m_isup)?0.20f:0.15f;
// 						pNode2->runAction(CCMoveTo::create(0.1f,ccp(pNode2->getPositionX(),_h*size.height)));
					}
					cardObj2->m_isfocus = false;
					
				}
				cardObj->m_isfocus = true;
				if(!cardObj->m_isfist&&m_isRay)
				{
					cardObj->m_isselect = !cardObj->m_isselect;
					if (!cardObj->m_isselect)
					{
						pNode->setColor(ccc3(255,255,255));
					}else{
						pNode->setColor(ccc3(220,220,220));
					}
// 					float _h = (cardObj->m_isup)?0.20f:0.15f;
// 					pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
				}
				
			}
			break;
		}
	}
	if (0==num)
	{
		m_isSelect = false;
	}

}

void ViewHandCard::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_isSelect = false;
	bool isAllUp=true;
	//移除焦点
	CCObject * pObj2 = NULL;
	int MoveNum =0;
	BYTE  Card[20];
	memset(Card,0,sizeof(BYTE)*20);
	CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj2)
	{
		CCSprite * pNode2 = (CCSprite*)pObj2;
		CCcardDate * cardObj2 = (CCcardDate*)pNode2->getUserObject();
		pNode2->setColor(ccc3(255,255,255));
		if (cardObj2->m_isselect)
		{
			if(cardObj2->m_isup==false)isAllUp=false;
			cardObj2->m_isup=!cardObj2->m_isup;
			Card[MoveNum++]=cardObj2->getValue();
			float _h = (cardObj2->m_isup)?0.08f:0.05f;
			pNode2->stopAllActions();
			pNode2->runAction(CCMoveTo::create(0.1f,ccp(pNode2->getPositionX(),_h*size.height)));
		}
		cardObj2->m_isfocus = false;
		cardObj2->m_isfist = false;
		cardObj2->m_isselect = false;
	}

	if (isAllUp==true)return;
	if (MoveNum<=1)return;

	DDZLogic m_GameLogic;
	int MoveUpNum =0;
	BYTE  MoveUpCard[20];
	memset(MoveUpCard,0,sizeof(BYTE)*20);
	do 
	{
		if (m_outCardNum==0)
		{
			tagAnalyseResult  AnalyseResult;
			memset(&AnalyseResult,0,sizeof(AnalyseResult));
			m_GameLogic.analysebCardData(Card,MoveNum,AnalyseResult);

			//优先选择炸弹
			if (AnalyseResult.cbFourCount>=1)
			{
				MoveUpNum=0;
				for (int i=0;i<AnalyseResult.cbFourCount;i++)
				{
					MoveUpCard[MoveUpNum++]=AnalyseResult.cbFourCardData[i];
				}
				break;
			}

			//飞机
			int index=0;
			int key=0;
			BYTE  tempCard[20];
			memset(tempCard,0,20);
			MoveUpNum=0;
			if (AnalyseResult.cbThreeCount>=2)
			{
				for (int i=0;i<AnalyseResult.cbThreeCount-1;i++)
				{
					tempCard[key++]=AnalyseResult.cbThreeCardData[i*3];
					tempCard[key++]=AnalyseResult.cbThreeCardData[i*3+1];
					tempCard[key++]=AnalyseResult.cbThreeCardData[i*3+2];
					for (int j=i+1;j<AnalyseResult.cbThreeCount;j++)
					{

						if (m_GameLogic.getCardLogicValue(AnalyseResult.cbThreeCardData[(j-1)*3])-
							m_GameLogic.getCardLogicValue(AnalyseResult.cbThreeCardData[j*3])==1)
						{
							tempCard[key++]=AnalyseResult.cbThreeCardData[j*3];
							tempCard[key++]=AnalyseResult.cbThreeCardData[j*3+1];
							tempCard[key++]=AnalyseResult.cbThreeCardData[j*3+2];
							index++;
						}else{
							break;
						}
					}
					if (index>=1)
					{
						memcpy(MoveUpCard,tempCard,sizeof(BYTE)*20);
						MoveUpNum=key;
						break;
					}
				}
				if (MoveUpNum>=6)break;
			}

			//顺子
			if (AnalyseResult.cbSignedCount+AnalyseResult.cbDoubleCount+
				AnalyseResult.cbThreeCount+AnalyseResult.cbFourCount>=5||
				AnalyseResult.cbDoubleCount+AnalyseResult.cbThreeCount+AnalyseResult.cbFourCount>=3)
			{
				for (int i=0;i<MoveNum-2;i++)
				{
					for (int j=MoveNum-1;j>i;j--)
					{
						BYTE ItoJ[20];
						memset(ItoJ,0,20);
						memcpy(ItoJ,Card+i,j-i+1);
						if(true==OnLianduiWidom(ItoJ,j-i+1,MoveUpCard,MoveUpNum))return;
						if(true==OnShunziWidom(ItoJ,j-i+1,MoveUpCard,MoveUpNum))return;
					}
				}
			}

			//三张
			if (AnalyseResult.cbThreeCount>=1)
			{
				for (int i=0;i<AnalyseResult.cbThreeCount;i++)
				{
					MoveUpCard[MoveUpNum++]=AnalyseResult.cbThreeCardData[i];
				}
				break;
			}

		}else
		{
			tagOutCardResult outCardData;
			if(true==m_GameLogic.searchOutCard(Card,MoveNum,m_outCardData,m_outCardNum,outCardData))
			{
				MoveUpNum =outCardData.cbCardCount;
				memcpy(MoveUpCard,outCardData.cbResultCard,sizeof(BYTE)*MoveUpNum);
				break;
			}
		}
	} while (0);

	if (MoveUpNum>1)
			setCardUp(MoveUpCard,MoveUpNum);

}

void ViewHandCard::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void ViewHandCard::setHardCard(WORD _charID,BYTE* _data,int _num,bool _effect,bool _open)
{
	switch(_charID)
	{
	case 0:
		if (_open)
		{
			showLeftUserHardCard(_data,_num);
		}
		showLeftHintCard(_num);
		break;
	case 1:
		showMeUserHardCard(_data,_num,_open);
		if(_effect)
		{
			CCObject* pObj=NULL;
			CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
			{
				CCSprite* pNode=(CCSprite*)pObj;
				if (pNode)pNode->setVisible(false);
			}
			m_isOpenCard = _open;
			m_effectNum=0;
			unschedule(schedule_selector(ViewHandCard::showhardCardEffect));
			schedule(schedule_selector(ViewHandCard::showhardCardEffect),0.2f,17,0.0f);
		}
		break;
	case 2:
		if (_open)
		{
			showRightUserHardCard(_data,_num);
		}
		showRightHintCard(_num);
		break;
	}
}

void ViewHandCard::setOutCard( WORD _charID,BYTE* _data,int _num,WORD BankUserID)
{
	CCNode* node=NULL;
	CCSize size= CCDirector::sharedDirector()->getWinSize();
	int _baseL = (_num-1)*SMALLCARD_SPACE;
	CCPoint  pt;
	m_outCardNum =_num;
	memcpy(m_outCardData,_data,sizeof(BYTE)*_num);

	switch(_charID)
	{
	case 0:
		node=m_outCardNodeM;
		pt=ccp(size.width*0.3f, size.height*0.6f);
		break;
	case 1:
		node=m_outCardNodeM;
		pt=ccp(size.width*0.5f, size.height*0.4f+5);
		break;
	case 2:
		node=m_outCardNodeM;
		pt=ccp(size.width*0.7f, size.height*0.6f);
		break;
	default:
		m_outCardNodeL->removeAllChildrenWithCleanup(true);
		m_outCardNodeR->removeAllChildrenWithCleanup(true);
		m_outCardNodeM->removeAllChildrenWithCleanup(true);
		m_outCardNum =0;
		memset(m_outCardData,0,sizeof(BYTE)*20);
		return;
	}
	node->removeAllChildrenWithCleanup(true);
	for (int i=0;i<_num;i++)
	{
		CCSprite *spt =getCardSprite(_data[i],1,false);
		CC_BREAK_IF(!spt);
		CCcardDate* cardObj =CCcardDate::create(_data[i]);
		cardObj->m_isup = false;
		spt->setUserObject(cardObj);
		spt->setPosition(ccp(pt.x-_baseL*0.5+i*SMALLCARD_SPACE,pt.y));
		node->addChild(spt);
		if(i==_num-1 &&_charID==BankUserID)
		{
			CCSprite* bankWar=CCSprite::create(texture_name::s_card,CCRectMake(335,0,36,40));
			bankWar->setAnchorPoint(ccp(1.0f,1.0f));
			bankWar->setPosition(ccp(spt->getContentSize().width,spt->getContentSize().height));
			spt->addChild(bankWar);
		}
	}
}

CCSprite* ViewHandCard::getCardSprite( char _data,int _type, bool isBigCard)
{
	CCSprite* sptbk=NULL;			//白底
	CCSprite* sptColUP=NULL;			//花色
	CCSprite* sptNumUP=NULL;		//数字
	CCSprite* sptColDo=NULL;			//花色
	CCSprite* sptNumDo=NULL;		//数字

	CCSpriteFrame* sptFrame=NULL;
	if (_data == 0x4E)  //小王
	{
		sptbk=CCSprite::create(texture_name::s_card,isBigCard?CCRectMake(190,0,95,127):CCRectMake(421,0,50,56));
	}
	else if (_data == 0x4F)
	{
		sptbk=CCSprite::create(texture_name::s_card,isBigCard?CCRectMake(95,0,95,127):CCRectMake(371,0,50,56));
	}
	else
	{
		DDZLogic _logic;
		int color =_logic.getCardColor(_data);
		int value =_logic.getCardValue(_data);
		if (isBigCard)
			sptbk=CCSprite::create(texture_name::s_card,CCRectMake(0,0,95,127));				//底版
		else
			sptbk=CCSprite::create(texture_name::s_card,CCRectMake(285,0,50,56));

		sptNumUP=CCSprite::create(texture_name::s_card,(color/16)%2==1?CCRectMake(30*(value-1),140,30,29):CCRectMake(30*(value-1),169,30,30));
		sptNumUP->setAnchorPoint(ccp(0.0f,1.0f));
		sptNumUP->setPosition(ccp(sptbk->getContentSize().width*0.05,sptbk->getContentSize().height*0.95));

		sptColUP=CCSprite::create(texture_name::s_card,CCRectMake(285+20*(color/16),57,20,20));
		sptColUP->setAnchorPoint(ccp(0.0f,1.0f));
		sptColUP->setPosition(ccp(sptbk->getContentSize().width*0.1,sptbk->getContentSize().height*0.7));

		if (isBigCard)
		{
			sptNumDo=CCSprite::create(texture_name::s_card,(color/16)%2==1?CCRectMake(30*(value-1),140,30,29):CCRectMake(30*(value-1),169,30,30));
			//sptNumDo->setRotationX(180.0f);
			//sptNumDo->setRotationY(180.0f);
			sptNumDo->setAnchorPoint(ccp(0.0f,1.0f));
			sptNumDo->setPosition(ccp(sptbk->getContentSize().width*0.95,sptbk->getContentSize().height*0.05));

			sptColDo=CCSprite::create(texture_name::s_card,CCRectMake(285+20*(color/16),57,20,20));
			//sptColDo->setRotationX(180.0f);
			//sptColDo->setRotationY(180.0f);
			sptColDo->setAnchorPoint(ccp(0.0f,1.0f));
			sptColDo->setPosition(ccp(sptbk->getContentSize().width*0.9,sptbk->getContentSize().height*0.3));
		}
		else
		{
			sptNumUP->setScale(0.8f);
			sptColUP->setScale(0.8f);
			sptColUP->setPosition(ccp(sptbk->getContentSize().width*0.12,sptbk->getContentSize().height*0.50));
		}
		if(sptColUP)sptbk->addChild(sptColUP);
		if(sptNumUP)sptbk->addChild(sptNumUP);
		if(sptNumDo)sptbk->addChild(sptNumDo);
		if(sptColDo)sptbk->addChild(sptColDo);
	}
	return sptbk;
}

bool ViewHandCard::UserOutCard(bool isOut)
{
	//--不要
	if(isOut==false)
	{
		this->setCardRecover();//--复原扑克
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,CCInteger::create(msgToLogic_passCard));
		return true;
	}
	//--出牌
	BYTE			tempCardData[MAX_COUNT];
	WORD		tempCardNum=0;
	CCObject* pObj=NULL;
	//正向
	CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
	{
		CCSprite * pNode = (CCSprite*)pObj;
		CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
		if ( cardObj && cardObj->m_isup)
		{
			tempCardData[tempCardNum++] = cardObj->getValue();
		}
	}
	DDZLogic _logic;
	if (m_outCardNum==0)	//--一轮首出
	{
		if ( _logic.getCardType(tempCardData,tempCardNum) == CT_ERROR)	
			return false;
	}
	else
	{
		if (_logic.compareCard(m_outCardData,tempCardData,m_outCardNum,tempCardNum)==false)
			return false;
	}

	//出牌成功
	CCsendCard* _sendCard=CCsendCard::create(msgToLogic_outCard);
	_sendCard->m_handCardNum =tempCardNum;
	memcpy(_sendCard->m_handCardData,tempCardData,sizeof(BYTE)*tempCardNum);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,_sendCard);
	return true;
}

void ViewHandCard::UserAutoCard()
{
	//--出牌
	BYTE			tempCardData[MAX_COUNT];
	WORD		tempCardNum=0;
	CCObject* pObj=NULL;
	DDZLogic _logic;
	//逆向
	CCARRAY_FOREACH_REVERSE(m_handCardNode->getChildren(),pObj)
	{
		CCSprite * pNode = (CCSprite*)pObj;
		CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
		if ( tempCardNum ==0)
		{
			tempCardData[tempCardNum++]  = cardObj->getValue();
		}
		else if (_logic.getCardLogicValue(tempCardData[0]) ==_logic.getCardLogicValue(cardObj->getValue()))
		{
			tempCardData[tempCardNum++]  = cardObj->getValue();
		}
	}
	//出牌成功
	CCsendCard* _sendCard=CCsendCard::create(msgToLogic_outCard);
	_sendCard->m_handCardNum =tempCardNum;
	memcpy(_sendCard->m_handCardData,tempCardData,sizeof(BYTE)*tempCardNum);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,_sendCard);
}

bool ViewHandCard::setHintCard()
{
	bool ret= false;
	DDZLogic _logic;
	CCSize size =CCDirector::sharedDirector()->getWinSize();
	tagOutCardResult outCardData;
	CCObject* pObj=NULL;
	//--手牌
	BYTE			tempCardData[MAX_COUNT];
	WORD		tempCardNum=getCardData(tempCardData);
	//--已经起来的牌
	BYTE			tempCardDataUp[MAX_COUNT];
	WORD		tempCardNumUp=getCardUpData(tempCardDataUp);
	//--对手出的牌
	BYTE        tempOutCardData[MAX_COUNT];
	WORD		tempOutCardNum=m_outCardNum;
	memcpy(tempOutCardData,m_outCardData,sizeof(BYTE)*MAX_COUNT);

	if (_logic.compareCard(m_outCardData,tempCardDataUp,m_outCardNum,tempCardNumUp))
	{
		//--已经智能了
		tempOutCardNum=tempCardNumUp;
		memcpy(tempOutCardData,tempCardDataUp,sizeof(BYTE)*MAX_COUNT);
		ret=true;
	}

	if(_logic.searchOutCard(tempCardData,tempCardNum,tempOutCardData,tempOutCardNum,outCardData))
	{
		ret=true;

		CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
		{
			CCSprite * pNode = (CCSprite*)pObj;
			CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
			if (cardObj==NULL)continue;
			for (int i =0;i<outCardData.cbCardCount;i++)
			{
				if ( cardObj && cardObj->getValue()==outCardData.cbResultCard[i])
				{
					cardObj->m_isup =true;

					float _h = (cardObj->m_isup)?0.08f:0.05f;
					pNode->stopAllActions();
					pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
					break;
				}
				else
				{
					cardObj->m_isup =false;
					float _h = (cardObj->m_isup)?0.08f:0.05f;
					pNode->stopAllActions();
					pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
				}

			}
		}
	}
	else if (_logic.searchOutCard(tempCardData,tempCardNum,m_outCardData,m_outCardNum,outCardData))
	{
		ret=true;

		CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
		{
			CCSprite * pNode = (CCSprite*)pObj;
			CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
			if (cardObj==NULL)continue;
			for (int i =0;i<outCardData.cbCardCount;i++)
			{
				if ( cardObj && cardObj->getValue()==outCardData.cbResultCard[i])
				{
					cardObj->m_isup =true;

					float _h = (cardObj->m_isup)?0.08f:0.05f;
					pNode->stopAllActions();
					pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
					break;
				}
				else
				{
					cardObj->m_isup =false;
					float _h = (cardObj->m_isup)?0.08f:0.05f;
					pNode->stopAllActions();
					pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
				}

			}
		}
	}

	return ret;
}

bool ViewHandCard::isNoCardout()
{
	DDZLogic _logic;
	tagOutCardResult outCardData;
	//--手牌
	BYTE			tempCardData[MAX_COUNT];
	WORD		tempCardNum=getCardData(tempCardData);
	return _logic.searchOutCard(tempCardData,tempCardNum,m_outCardData,m_outCardNum,outCardData);

}

void ViewHandCard::showMeUserHardCard( BYTE* _data,int _num,bool _open )
{
	CCSize size= CCDirector::sharedDirector()->getWinSize();
	int _baseL = (_num-1)*CARD_SPACE;

	m_handCardNode->removeAllChildrenWithCleanup(true);

	for (int i=0;i<_num;i++)
	{
		CCSprite *spt =getCardSprite(_data[i],1,true);
		CC_BREAK_IF(!spt);
		CCcardDate* cardObj =CCcardDate::create(_data[i]);
		cardObj->m_isup = false;
		cardObj->m_isfocus = false;
		cardObj->m_isfist = false;
		cardObj->m_isselect = false;
		spt->setUserObject(cardObj);
		spt->setAnchorPoint(ccp(0.5f,0));
		spt->setPosition(ccp(size.width*0.5-_baseL*0.5+i*CARD_SPACE+25,size.height*0.05f));
		m_handCardNode->addChild(spt);
		if (i==_num-1 && _open)
		{
			CCSprite * sptOpen=CCSprite::create(texture_name::s_card,CCRectMake(325,77,55,63));
			sptOpen->setAnchorPoint(ccp(1.0f,1.0f));
			sptOpen->setPosition(ccp(spt->getContentSize().width,spt->getContentSize().height));
			spt->addChild(sptOpen);
		}
	}
}

void ViewHandCard::showhardCardEffect( float deley )
{
	SoundControl::sharedSoundControl()->playSoundEffect(sound_name::s_ct_fapai);
	m_effectNum++;
	CCObject* pObj=NULL;
	m_handCardNode->setVisible(true);
	int _num=0;
	CCPoint ptEnd;
	//正向
	CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
	{
		_num++;
		CCSprite* pNode=(CCSprite*)pObj;
		if (pNode )
			pNode->setVisible(_num<m_effectNum?true:false);
		if (_num==m_effectNum)
		{
			ptEnd=pNode->getPosition();
			pNode->setPosition(ccp(ptEnd.x-CARD_SPACE,ptEnd.y));
			pNode->setVisible(true);
			pNode->runAction(CCMoveTo::create(0.15f,ptEnd));
		}
	}
	if (((m_effectNum%4==0  )|| m_effectNum==1 ) && m_isOpenCard==false)
	{
		CCviewOpenCardNum* _num=CCviewOpenCardNum::create(msgToView_openCardNum);
		_num->m_num =5- m_effectNum/4;
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,_num);
	}
	if(m_effectNum>=17)
	{
		unschedule(schedule_selector(ViewHandCard::showhardCardEffect));
	}
}

void ViewHandCard::showLeftUserHardCard(BYTE* _data,int _num)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int _baseL = (_num-1)*SMALLCARD_SPACE;
	m_leftCardNode->removeAllChildrenWithCleanup(true);

	for (int i=0;i<_num;i++)
	{
		CCSprite *spt = getCardSprite(_data[i],1,false);
		CC_BREAK_IF(!spt);
		spt->setPosition(ccp(size.width*0.25-_baseL*0.5+i*SMALLCARD_SPACE,size.height*0.8));
		m_leftCardNode->addChild(spt);
	}
}

void ViewHandCard::showRightUserHardCard(BYTE* _data,int _num)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int _baseL = (_num-1)*SMALLCARD_SPACE;
	m_rightCardNode->removeAllChildrenWithCleanup(true);

	for (int i=0;i<_num;i++)
	{
		CCSprite *spt = getCardSprite(_data[i],1,false);
		CC_BREAK_IF(!spt);
		spt->setPosition(ccp(size.width*0.75-_baseL*0.5+i*SMALLCARD_SPACE,size.height*0.8));
		m_rightCardNode->addChild(spt);
	}
}

void ViewHandCard::showDiPai(BYTE * _data,int _num,int _lastTask,bool isNew)
{
	m_diPaiNode->removeAllChildrenWithCleanup(true);

	CCSize size=CCDirector::sharedDirector()->getWinSize();
	memcpy(m_BackData,_data,sizeof(BYTE)*3);
	m_lastTaskKey=_lastTask;
	if (isNew==false)
	{
		showDipaiEffect(this);
		return;
	}

	CCSprite *spt[3];
	CCArray * animFrames[3];
	CCAnimation * animation[3];
	CCPoint pt=ccp(size.width*0.5,size.height*0.5);

	for (int i=0;i<3;i++)
	{
		spt[i] = CCSprite::createWithSpriteFrameName(texture_name::s_paiBei0);
		spt[i]->setPosition(pt);
		spt[i]->setUserObject(CCInteger::create(_data[i]));
		m_diPaiNode->addChild(spt[i]);

		animFrames[i]=new CCArray(3);
		CCSpriteFrame * frame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_paiBei0);
		animFrames[i]->addObject(frame1);

		CCSpriteFrame * frame2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(texture_name::s_paiBei1);
		animFrames[i]->addObject(frame2);

		CCSpriteFrame * frame3 = getCardSprite(_data[i],1,true)->displayFrame();
		animFrames[i]->addObject(frame3);

		animation[i] = CCAnimation::createWithSpriteFrames(animFrames[i],0.2f);
		spt[i]->runAction(CCSequence::create(CCMoveTo::create(0.2f,ccp(pt.x+(i-1)*100,pt.y)),CCAnimate::create(animation[i]),CCCallFuncN::create(this,callfuncN_selector(ViewHandCard::showDipaiSpt)),CCDelayTime::create(1.0f),
			CCSpawn::create(CCScaleTo::create(0.4f,0.4f),CCMoveTo::create(0.4f,ccp(30,size.height-30)),NULL),i==2?CCCallFuncN::create(this,callfuncN_selector(ViewHandCard::showDipaiEffect)):NULL,NULL));
	}
}

void ViewHandCard::showDipaiSpt(CCNode* _node)
{
	CCSprite *spt=(CCSprite*)_node;
 	CCSprite * _sptcard=getCardSprite(((CCInteger*)(spt->getUserObject()))->getValue(),1,true);
 	_sptcard->setAnchorPoint(ccp(0.5f,0.5f));
 	_sptcard->setPosition(ccp(spt->getContentSize().width*0.5,spt->getContentSize().height*0.5));
	spt->addChild(_sptcard);
}

void ViewHandCard::showDipaiEffect(CCNode* _node)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_diPaiNode->removeAllChildrenWithCleanup(true);

	for (int i=0;i<3;i++)
	{
		CCSprite *spt = getCardSprite(m_BackData[i],1,false);
		CC_BREAK_IF(!spt);
		spt->setAnchorPoint(ccp(0,1.0f));
		spt->setPosition(ccp(10.0f+i*SMALLCARD_SPACE,size.height-10.0f));
		m_diPaiNode->addChild(spt);
	}
	m_viewTask->setBackTaskView(m_BackData,3);
	m_viewTask->setLastTaskView(m_lastTaskKey);
}

void ViewHandCard::showRightHintCard(int _num)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
// 	CCString cstr;
// 	cstr.initWithFormat("%d",_num);
// 	m_rightCardNumAtlas->setString(cstr.getCString());
// 	m_rightCardNumAtlas->setVisible(true);
// 	if (_num==0)
// 	{
// 		m_rightCardNumAtlas->setVisible(false);
// 	}
	int _baseL = (_num-1)*5;
	m_hintRightCardNode->removeAllChildrenWithCleanup(true);

	for (int i=0;i<_num;i++)
	{
		CCSprite * spt = CCSprite::createWithSpriteFrameName(texture_name::s_hintCard);
		CC_BREAK_IF(!spt);
		spt->setPosition(ccp(750.0f-i*4.5+m_rightCardNum[i],size.height*0.37+i*5));
		m_hintRightCardNode->addChild(spt,_num-i,0);
	}
}

void ViewHandCard::showLeftHintCard(int _num)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
// 	CCString cstr;
// 	cstr.initWithFormat("%d",_num);
// 	m_leftCardNumAtlas->setVisible(true);
// 	m_leftCardNumAtlas->setString(cstr.getCString());
// 	if (_num==0)
// 	{
// 		m_leftCardNumAtlas->setVisible(false);
// 	}

	int _baseL = (_num-1)*5;
	m_hintLeftCardNode->removeAllChildrenWithCleanup(true);

	for (int i=0;i<_num;i++)
	{
		CCSprite * spt = CCSprite::createWithSpriteFrameName(texture_name::s_hintCard);
		spt->setFlipX(true);
		CC_BREAK_IF(!spt);
		spt->setPosition(ccp(100.0f+i*4.5+m_leftCardNum[i],size.height*0.37+i*5));
		m_hintLeftCardNode->addChild(spt,_num-i,0);
	}
}

int ViewHandCard::getCardData( BYTE* _data )
{

	WORD		tempCardNum=0;
	CCObject* pObj=NULL;
	//正向
	CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
	{
		CCSprite * pNode = (CCSprite*)pObj;
		CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
		if ( cardObj )
		{
			_data[tempCardNum++] = cardObj->getValue();
		}
	}
	return tempCardNum;
}

int ViewHandCard::getCardUpData( BYTE* _data )
{
	WORD		tempCardNum=0;
	CCObject* pObj=NULL;
	//正向
	CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
	{
		CCSprite * pNode = (CCSprite*)pObj;
		CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
		if ( cardObj && cardObj->m_isup)
		{
			_data[tempCardNum++] = cardObj->getValue();
		}
	}
	return tempCardNum;
}

void ViewHandCard::setUnallowTouch()
{
	m_unallowToucn = true;
}

void ViewHandCard::removeHintCard()
{
	m_hintLeftCardNode->setVisible(false);
	m_hintRightCardNode->setVisible(false);
}

void ViewHandCard::setCardRecover()
{
	CCObject* pObj=NULL;
	//正向
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
	{
		CCSprite * pNode = (CCSprite*)pObj;
		CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
		if ( cardObj && cardObj->m_isup)
		{
			cardObj->m_isup=!cardObj->m_isup;
			float _h = (cardObj->m_isup)?0.08f:0.05f;
			pNode->stopAllActions();
			pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
		}
	}
}

void ViewHandCard::setCardUp( BYTE * _data,int _num )
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCObject* pObj=NULL;
	CCARRAY_FOREACH(m_handCardNode->getChildren(),pObj)
	{
		CCSprite * pNode = (CCSprite*)pObj;
		CCcardDate * cardObj = (CCcardDate*)pNode->getUserObject();
		if (cardObj==NULL)continue;
		for (int i =0;i<_num;i++)
		{
			if ( cardObj && cardObj->getValue()==_data[i])
			{
				cardObj->m_isup =true;

				float _h = (cardObj->m_isup)?0.08f:0.05f;
				pNode->stopAllActions();
				pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
				break;
			}
			else
			{
				cardObj->m_isup =false;
				float _h = (cardObj->m_isup)?0.08f:0.05f;
				pNode->stopAllActions();
				pNode->runAction(CCMoveTo::create(0.1f,ccp(pNode->getPositionX(),_h*size.height)));
			}
		}
	}
}


bool ViewHandCard::OnShunziWidom( BYTE cbCardData[], BYTE cbCardCount ,BYTE wisCard[], int& index )
{
	DDZLogic m_gameLogic;
	index=0;
	int twoIndex=0;
	bool  isWisdom=true;
	BYTE cbCompareValueMax = m_gameLogic.getCardLogicValue(cbCardData[0]);//最大牌
	BYTE cbCompareValueMin = m_gameLogic.getCardLogicValue(cbCardData[cbCardCount-1]);//最小牌
	//判断是否是顺子
	memset(wisCard,0,20);
	isWisdom=true;
	if((cbCompareValueMax-cbCompareValueMin)<4 || (cbCompareValueMax-cbCompareValueMin)>12)return false;
	if(cbCompareValueMax>14)return false;
	for(int k=cbCompareValueMin;k<=cbCompareValueMax;k++)
	{
		twoIndex=0;
		for(int i=0;i<cbCardCount;i++)
		{
			if(m_gameLogic.getCardLogicValue(cbCardData[i])==k)
			{
				twoIndex++;
				wisCard[index++]=cbCardData[i];
				break;
			}
		}
		if(twoIndex<1)				
		{
			isWisdom=false;
			break;
		}
	}
	if (isWisdom)
	{
		setCardUp(wisCard,index);
		return true;
	}
	return false;
}

bool ViewHandCard::OnLianduiWidom( BYTE cbCardData[], BYTE cbCardCount,BYTE wisCard[], int& index )
{
	DDZLogic m_gameLogic;
	index=0;
	int twoIndex=0;
	bool  isWisdom=true;
	BYTE cbCompareValueMax = m_gameLogic.getCardLogicValue(cbCardData[0]);//最大牌
	BYTE cbCompareValueMin = m_gameLogic.getCardLogicValue(cbCardData[cbCardCount-1]);//最小牌


	//判断选派是否为连对
	memset(wisCard,0,20);
	if(cbCompareValueMax>14)return false;
	if((cbCompareValueMax-cbCompareValueMin)<2)return false;
	for(int k=cbCompareValueMin;k<=cbCompareValueMax;k++){
		twoIndex=0;
		for (int i=0;i<cbCardCount;i++)
		{
			if(m_gameLogic.getCardLogicValue(cbCardData[i])==k){
				twoIndex++;
				wisCard[index++]=cbCardData[i];
			}
			if(twoIndex>=2)break;
		}
		if (twoIndex<2)
		{
			isWisdom=false;
			break;
		}
	}
	if (isWisdom)
	{
		setCardUp(wisCard,index);
		return true;
	}
	return false;
}

void ViewHandCard::newRound()
{
	m_outCardNum = 0;
}
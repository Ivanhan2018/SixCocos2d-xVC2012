#include "SceneLogic.h"
#include "RoomFrame.h"
#include "DDZRes.h"
#include "CMD_DDZ.h"
#include "DDZLogic.h"
#include "GlobalFrame.h"
#include "CMD_Game.h"
#include "CMD_GameServer.h"
#include "SceneControl.h"
#include "TaskInfo.h"
#include "utf-8.h"
#include "GameTaskCommon.h"
#include "GlobalUnits.h"
#include "ConfigMgr.h"
#include "CMD_DDZClient.h"
#include "MyNSString.h"

int compareCardValue(const void *a, const void *b)
{
	BYTE valuaA = *(BYTE *)a;
	BYTE valuaB = *(BYTE *)b;
	return SceneLogic::GetCardLogicValue(valuaB) - SceneLogic::GetCardLogicValue(valuaA);
}

bool SceneLogic::init()
{
	bool ret=false;
	do 
	{
		size = CCDirector::sharedDirector()->getWinSize();

		//--手牌
		for(int i=0 ;i<GAME_PLAYER;i++)
		{
			memset(m_handCardData[i],0,sizeof(BYTE)*MAX_COUNT);
			m_handCardNum[i]=0;
			m_BackCardData[i]=0;
			memset(m_outCardData,0,sizeof(BYTE)*MAX_COUNT);
			m_outCardNum=0;
			m_wOpenUser[i] =false;
		}
		m_gameState=Game_null;
		m_isOut =false;
		m_beilv = 1;
		m_baseScore=0;
		for(int i =0;i<8;i++)
		{
			m_lBetScore[i] = 0;  //游戏结束重新初始化为0
		}
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneLogic::onUserStart),"GameStart" , NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneLogic::onUpdateTable),MSG_UI_ANS_PLAYERUPDATE,NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneLogic::onMessageGame),GBEVENT_UI_GAMEMESSAGE,NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneLogic::onMessageScene),GBEVENT_UI_SCENEMESSAGE,NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneLogic::onUpdataMatch),MSG_UI_ANS_MATCH,NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneLogic::onViewMessage),MESSAGE_TOLOGIC,NULL);
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneLogic::onLinkResult),MSG_UI_ANS_GAMELINK , NULL);				//连接服务器
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneLogic::onUpdateScoreAndGoldEgg),MSG_UI_ANS_UPDATESCOREANDGOLDEGG , NULL);			//--充值刷新金币
		//this->schedule(schedule_selector(SceneLogic::checkNet), 8);

		m_chipManager = ChipManager::create();
		addChild(m_chipManager);



		m_cardTableLayer = CardTableLayer::create();  //头像  信息
		this->addChild(m_cardTableLayer,0);


		operlayer =  OperaLayer::create();
		this->addChild(operlayer,0);


		m_pCardManager = CardManager::create();
		addChild(m_pCardManager,1);

		SpriteGameStare = CCSprite::create("BJL/BJL_04.png");
		SpriteGameStare->setAnchorPoint(CCPointZero);
		SpriteGameStare->setPosition(ccp(size.width*0.35+10,size.height*0.9));
		SpriteGameStare->setVisible(false);
		addChild(SpriteGameStare);
		SpriteGameTime = CCSprite::createWithSpriteFrame(spriteFrame("BJL_23_1.png"));
		SpriteGameTime->setAnchorPoint(CCPointZero);
		SpriteGameTime->setPosition(ccp(size.width*0.4,size.height*0.78));
		SpriteGameTime->setVisible(false);
		addChild(SpriteGameTime);
		ret = true;

	} while (0);
	return ret;
}


void SceneLogic::onEnter()
{
	EntityMgr::instance()->getDispatch()->setGameStatus(true);
	CCNode::onEnter();
	//游戏场景消息
}

void SceneLogic::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_PLAYERUPDATE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,GBEVENT_UI_GAMEMESSAGE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,GBEVENT_UI_SCENEMESSAGE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_UI_ANS_MATCH);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MESSAGE_TOLOGIC);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_GAMELINK);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_UI_ANS_UPDATESCOREANDGOLDEGG);
	CCNode::onExit();
}

void SceneLogic::checkNet(float ft)
{
	static int NetData=0;
	if (EntityMgr::instance()->getDispatch()->isGameLinkOK()) 
	{
		NetData=0;
		unschedule(schedule_selector(SceneLogic::checkNet));
		schedule(schedule_selector(SceneLogic::checkNet), 8);
	}else{
		NetData++;
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,NetData>2?(NetData=0,CCInteger::create(msgToView_socketoff)):CCInteger::create(msgToView_socketoffConnect));
		unschedule(schedule_selector(SceneLogic::checkNet));
		schedule(schedule_selector(SceneLogic::checkNet), 4);
	}
}

int SceneLogic::switchViewChairID( unsigned int nChairID )
{
	tagUserData*    m_pMeUserDate=EntityMgr::instance()->roomFrame()->getMeUserItem()->getUserData();
	unsigned int nViewChairID = (nChairID + GAME_PLAYER - m_pMeUserDate->wChairID);
	switch (GAME_PLAYER)
	{
	case 2: { nViewChairID+=1; break; }
	case 3: { nViewChairID+=1; break; }
	case 4: { nViewChairID+=2; break; }
	case 5: { nViewChairID+=2; break; }
	case 6: { nViewChairID+=3; break; }
	case 7: { nViewChairID+=3; break; }
	case 8: { nViewChairID+=4; break; }
	}
	return nViewChairID % GAME_PLAYER;
}

void SceneLogic::sendSeverData( WORD wSubCmdID )
{
	if (EntityMgr::instance()->getDispatch()->isGameLinkOK()) {
		EntityMgr::instance()->getDispatch()->sendSocketDate(wSubCmdID);
	}else{
		//?????????????????????
		//sendViewMessage(LOGIC_SOCKET_OFF);
	}
}

void SceneLogic::sendSeverData( WORD wSubCmdID,void* pData,WORD wDataSize )
{
	if (EntityMgr::instance()->getDispatch()->isGameLinkOK()) {
		EntityMgr::instance()->getDispatch()->sendSocketDate(wSubCmdID,pData,wDataSize);
	}else{
		//?????????????????????
		//sendViewMessage(LOGIC_SOCKET_OFF);
	}
}

void SceneLogic::sendFrameData( WORD wSubCmdID,void* pData,WORD wDataSize )
{
	if (EntityMgr::instance()->getDispatch()->isGameLinkOK()) {
		EntityMgr::instance()->getDispatch()->sendFrameDate(wSubCmdID,pData,wDataSize);
	}else{

	}
}

void SceneLogic::setGameState( Game_State _state )
{
	m_gameState = _state;
}

//游戏消息
void SceneLogic::onMessageGame(CCObject* obj)
{
	tagGameBuffer* tag = (tagGameBuffer*)obj;
	onGameMessage(tag->wSubCmdID,tag->dateBuffer,tag->nDataSize);
}

//游戏场景消息
void SceneLogic::onMessageScene(CCObject* obj)
{
	tagSceneBuffer* tag = (tagSceneBuffer*)obj;
	onSceneMessage(tag->cbState,tag->dateBuffer,tag->nDataSize);
}

void SceneLogic::onUpdataMatch( CCObject* obj )
{
	//MatchError* match = MatchError::MatchErrorWith();
	//addChild(match,101);
}

//跟新桌子
void SceneLogic::onUpdateTable(CCObject* obj)
{
	tagUserBuffer* tag = (tagUserBuffer*)obj;
	DWORD dwUserID = tag->dwUserID;

	CUserItem* pUserItem = (CUserItem*)EntityMgr::instance()->roomFrame()->getUserItem(dwUserID);
	if (!pUserItem)
	{
		return;
	}

	tagUserData* pUserDate = pUserItem->getUserData();
	if (!pUserDate)
	{
		return;
	}
	unsigned int nChairID = switchViewChairID(pUserDate->wChairID);
	//if(pUserDate->cbUserStatus<=US_SIT)return;

	CCuserInfor* _userData =CCuserInfor::create(msgToView_UserInfor);
	_userData->m_userInforID = pUserDate->dwUserID;
	_userData->m_score =pUserDate->lScore;
	_userData->m_gender =pUserDate->cbGender;
	_userData->m_GoldEggs=pUserDate->lGoldEggs;
	memcpy(_userData->m_PosName,pUserDate->szDwellingPlace,sizeof(char)*32);

	if(pUserDate->dwUserID == 38395)
	{
		CCLOG("ccccccccccccccccccccccc");
	}
	if (strlen(pUserDate->szNickName)>2)
	{
		memcpy(_userData->m_name,pUserDate->szNickName,sizeof(char)*32);
	}
	else
	{
		memcpy(_userData->m_name,pUserDate->szName,sizeof(char)*32);
	}
//	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,_userData);
	userInforDeal(_userData);
	//string szUserID = CGlobalMath::getUserFace(pUserItem->m_UserData.wFaceID,pUserItem->m_UserData.cbGender);
	//m_SceneView->SetUserState(pUserDate->cbUserStatus,nChairID,szUserID, &pUserItem->m_UserData,dwUserID);
}

void SceneLogic::onViewMessage( CCObject* obj )
{
	CCInteger* _int=(CCInteger*)obj;
	switch(_int->getValue())
	{
	case msgToLogic_changeTable:
		{
			CCDirector::sharedDirector()->replaceScene(SceneControl::sharedSceneControl()->getScene(SCENE_game,true));
			EntityMgr::instance()->getDispatch()->SendPacketWithChangeTable();
		}
		break;
	case msgToLogic_openStart:
		{
			EntityMgr::instance()->getDispatch()->SendPacketWithUserStatus(US_READY);
		}
		break;
	case magToLogc_gameStart:
		{
			EntityMgr::instance()->getDispatch()->SendPacketWithUserStatus(US_READY);
		}
		break;
	case msgToLogic_outCard:
		{
			CCsendCard* _data=(CCsendCard* )_int;

			BYTE cbBuffer[sizeof(CMD_C_OutCard)];
			memset(cbBuffer, 0 , sizeof(CMD_C_OutCard));
			CMD_C_OutCard *OutCard = (CMD_C_OutCard *)cbBuffer;
			//OutCard.wOutCardUser =getMeUserDate()->wChairID;
			OutCard->cbCardCount =_data->m_handCardNum;
			memcpy(OutCard->cbCardData,_data->m_handCardData,sizeof(BYTE)*_data->m_handCardNum);
			sendSeverData(SUB_C_OUT_CARD, OutCard, sizeof(CMD_C_OutCard)-sizeof(OutCard->cbCardData)+OutCard->cbCardCount*sizeof(BYTE));

			//--自己的牌显示
			CCoutCard* _outCard =CCoutCard::create(msgToView_outCard);
			_outCard->m_outUser = 1;
			_outCard->m_numCard =_data->m_handCardNum;
			memcpy(_outCard->m_outkCard,_data->m_handCardData,_outCard->m_numCard);
			_outCard->m_bankUser=m_nBankerUser;
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,_outCard);
			//--减掉手牌
			DDZLogic _logic;
			BYTE		outCardData[MAX_COUNT];
			WORD	outCardNum=m_handCardNum[1];
			memcpy(outCardData,m_handCardData[1],MAX_COUNT);

			//if(_logic.removeCard(OutCard.bCardData,OutCard.bCardCount,outCardData,outCardNum))
			//{
			//	outCardNum-=OutCard.bCardCount;
			//}

			if(OutCard->cbCardCount == 2){
				const unsigned char num1 = OutCard->cbCardData[0];
				const unsigned char num2 = OutCard->cbCardData[1];
				if(num1 == 0x4F &&num2 == 0x4E)
				{
					CCNotificationCenter::sharedNotificationCenter()->postNotification("WANGZHA");
				}
			}
			//--手牌变化
			CCsendCard* msgdata=CCsendCard::create(msgToView_sendCard);
			memcpy(msgdata->m_handCardData,outCardData,sizeof(BYTE)*MAX_COUNT);
			msgdata->m_handCardNum = outCardNum;
			msgdata->m_bOpen =m_wOpenUser[1];
			msgdata->m_bEffect =false;
			msgdata->m_userID =1;
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,msgdata);

		}
		break;
	case msgToLogic_passCard:
		{
			sendSeverData(SUB_C_PASS_CARD);
		}
		break;
	case 	msgToLogc_openCard:
		{
			CCviewOpenCardNum* _cardNum=(CCviewOpenCardNum*)_int;
			BYTE cbBuffer[sizeof(CMD_C_OPENCARD)];
			memset(cbBuffer, 0 , sizeof(CMD_C_OPENCARD));
			CMD_C_OPENCARD *OpenCard = (CMD_C_OPENCARD *)cbBuffer;
			OpenCard->bOpenUser = getMeUserDate()->wChairID;
			OpenCard->bNum  =_cardNum->m_num;
			sendSeverData(REC_SUB_C_OPNE_CARD,OpenCard,sizeof(CMD_C_OPENCARD));
		}
		break;
	case msgToLogc_LandLord:
		{
			CClandLord*_data =(CClandLord*)_int;
			if(_data->m_isLand == true){
				CCviewOpenCardNum* _cardNum=(CCviewOpenCardNum*)_int;
				BYTE cbBuffer[sizeof(CMD_C_CallScore)];
				memset(cbBuffer, 0, sizeof(CMD_C_CallScore));
				CMD_C_CallScore *CallScore = (CMD_C_CallScore *)cbBuffer;
				CallScore->cbCallScore = (m_bLastCallScore==255?0:m_bLastCallScore)+1;
				EntityMgr::instance()->getDispatch()->sendSocketDate(SUB_C_CALL_SCORE,CallScore,sizeof(CMD_C_CallScore));
			}else{
				BYTE cbBuffer[sizeof(CMD_C_CallScore)];
				memset(cbBuffer, 0, sizeof(CMD_C_CallScore));
				CMD_C_CallScore *CallScore = (CMD_C_CallScore *)cbBuffer;
				CallScore->cbCallScore = 255;
				EntityMgr::instance()->getDispatch()->sendSocketDate(SUB_C_CALL_SCORE,CallScore,sizeof(CMD_C_CallScore));
			}
		}
		break;
	case msgToLogic_MoreGame:
		{
			if (EntityMgr::instance()->getDispatch()->isGameLinkOK())
			{
				CCDirector::sharedDirector()->replaceScene(SceneControl::sharedSceneControl()->getScene(SCENE_game,false));
				EntityMgr::instance()->getDispatch()->SendPacketWithUserStatus(US_READY);
			}
			else
			{
				CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,CCInteger::create(msgToView_socketoff));
			}
		}
		break;
	case magToLogc_jiabei:
		{
			CMD_C_DAOFAN _addData ;
			_addData.m_bUserDaofanID = getMeUserDate()->wChairID;
			sendSeverData(REC_SUB_C_DAOFAN,&_addData,sizeof(CMD_C_DAOFAN));
		}
		break;
	case msgToLogic_face:
		{
			CCfaceAndVioce * obj1=(CCfaceAndVioce*)obj;
			CMD_GF_EXPRESSION expression;
			expression.wType    = obj1->m_Type;
			expression.wIndex   = obj1->m_KeyID;
			expression.wChairID = getMeUserDate()->wChairID;
			//sendSeverData(SUB_GF_EXPRESSION, &expression, sizeof(expression));
			if(obj1->m_Type == 2)			//（1表情 2语音）
			{
				//此处不明
				BYTE cbBuffer[sizeof(CMD_GR_C_UserChat)];
				//memset(cbBuffer, 0, sizeof(CMD_GR_C_UserChat));
				//CMD_GR_C_UserChat *userChat = (CMD_GR_C_UserChat *)cbBuffer;
				//CCDictionary * strings = CCDictionary::createWithContentsOfFile("xml/strings.xml");
				//const char* buff=((CCString*)strings->objectForKey(CCString::createWithFormat("wav%d",obj1->m_KeyID)->getCString()))->getCString();
				//userChat->wChatLength = 128;
				//userChat->dwChatColor = 0XFF0000;
				//userChat->dwTargerUserID = EntityMgr::instance()->getDispatch()->m_dwUserID;
				//MyNSString::mbs2wc(buff, strlen(buff), userChat->szChatString);
				//sendFrameData(SUB_GF_USER_CHAT,userChat,sizeof(CMD_GR_C_UserChat));
			}else{
				BYTE cbBuffer[sizeof(CMD_GR_C_UserExpression)];
				memset(cbBuffer, 0, sizeof(CMD_GR_C_UserExpression));
				CMD_GR_C_UserExpression *userExpression = (CMD_GR_C_UserExpression *)cbBuffer;
				userExpression->dwTargetUserID = EntityMgr::instance()->getDispatch()->m_dwUserID;
				userExpression->wItemIndex = obj1->m_KeyID;
				sendFrameData(SUB_GF_USER_EXPRESSION,userExpression,sizeof(CMD_GR_C_UserExpression));
			}
		}
		break;
	}
}

bool SceneLogic::onSceneMessage( unsigned char cbStation,const void* pBuffer,WORD wDataSize )
{
	switch(cbStation)
	{
	case GAME_SCENE_FREE:               //空闲状态
		{
			CCLOG("%d",wDataSize);
			CCLOG("%d",sizeof(CMD_S_StatusFree));
			//效验大小 
			assert(wDataSize==sizeof(CMD_S_StatusFree));
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;
	

			CCLOG("－－－－小游戏－－－空闲状态－－－－－－－－");
			CMD_S_StatusFree* pStatusPlay=(CMD_S_StatusFree *)pBuffer;
			//空闲时间
			BYTE Tinme= pStatusPlay->cbTimeLeave -4;
			int zhuangjia = pStatusPlay->wBankerUser;
			CUserItem* pUserItem = (CUserItem*)EntityMgr::instance()->roomFrame()->getUserItem(pStatusPlay->wBankerUser);

			CCLOG("zhuangjiausd == %d",zhuangjia);
			SpriteGameTime->setVisible(true);
			SpriteGameTime->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_23_1.png"));
			CCNotificationCenter::sharedNotificationCenter()->postNotification("StrameNumber", CCInteger::create(zhuangjia));
			CCNotificationCenter::sharedNotificationCenter()->postNotification("Strameobjet", CCInteger::create(Tinme));
			CCNotificationCenter::sharedNotificationCenter()->postNotification("MI_setCCteefTag");
			m_cardTableLayer->waitingMatching(false);
			operlayer->dissUnclickTouch();
			if (!pStatusPlay->bEnableSysBanker)//不是系统坐庄
			{		
				m_cardTableLayer->setUserIsOnline(pStatusPlay->wBankerUser,pStatusPlay->lBankerScore,
				pStatusPlay->lBankerWinScore,pStatusPlay->wBankerTime);
			}
			break;
		}
	case GAME_SCENE_PLAY:			//游戏状态
		{
			CCLOG("－－－－小游戏－－－游戏状态－－－－－－－－");
			CCLOG("%d",wDataSize);
			CCLOG("%d",sizeof(CMD_S_StatusPlay));
			//效验数据
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;
			CMD_S_StatusPlay* pStatusPlay=(CMD_S_StatusPlay *)pBuffer;

			WORD appwBankerUser = pStatusPlay->wBankerUser;	//当前庄家
			CCLOG("%d",appwBankerUser);
			int hbvgkjsdnvg = 100;

		}
	default:
		{
			return true;
		}
	}
	return  true;
}
bool SceneLogic::onGameMessage( WORD wSubCmdID, const void* pBuffer, WORD wDataSize )
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_FREE:		//游戏空闲
		{
			return OnSubGameFree(pBuffer,wDataSize);
		}
	case SUB_S_GAME_START:		//游戏开始
		{
			return onSubSendCard(pBuffer,wDataSize);
		}
	case SUB_S_PLACE_JETTON:		//用户下注
		{
			CCLog("SUB_S_CALL_SCORE");
			return onSubLandScore(pBuffer,wDataSize);
		}
	case SUB_S_APPLY_BANKER:		//申请庄家
		{
			CCLog("SUB_S_OUT_CARD");
			return onSubOutCard(pBuffer,wDataSize);
		}
	case SUB_S_CANCEL_BANKER:	//取消做庄
		{
			return OnSubUserCancelBanker(pBuffer, wDataSize);
		}
	case SUB_S_CHANGE_BANKER:		//切换庄家
		{
			CCLog("SUB_S_PASS_CARD");
			return onSubPassCard(pBuffer,wDataSize);
		}
	case SUB_S_GAME_END:		//游戏结束
		{
			CCLog("SUB_S_BANKER_INFO");
			return onSubGameStart(pBuffer,wDataSize);
		}

	case SUB_S_PLACE_JETTON_FAIL:	//下注失败(忽略)
		{
			CCLog("SUB_S_GAME_CONCLUDE");
			return onSubGameEnd(pBuffer,wDataSize);
		}
	case SUB_S_CHANGE_USER_SCORE:	//更新积分
		{
			CCLog("SUB_S_SET_BASESCORE");
			return true;
		}
	case SUB_S_SEND_RECORD:		//游戏记录	
		{
			CCLog("SUB_S_CHEAT_CARD");
			return OnSubCheatCard(pBuffer,wDataSize);
		}
	case SUB_S_AMDIN_COMMAND:   //管理员命令申请 请求
		{
			CCLog("SUB_S_CHEAT_CARD");
			return onUserExpression(pBuffer,wDataSize);
		}
	}

	return true;
}
void SceneLogic::onUserStart(CCObject *pSender)
{
	//--游戏准备开始
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,CCInteger::create(msgToView_start));
}

bool SceneLogic::onUserStartView( const void * pBuffer, WORD wDataSize )
{
	if (wDataSize!= sizeof(CMD_S_READY))
	{
		CCLOG("发牌数据校验错误！");
		return false;
	}

	//--游戏开始表现
	CMD_S_READY* _ready=(CMD_S_READY*)pBuffer;
	CCopenStart* _start=CCopenStart::create(msgToView_startView);
	_start->m_bOpenCard =_ready->bOpenCard;
	_start->m_bCurrentUser = switchViewChairID(_ready->bCurrentUser);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,_start);
	return true;
}

bool SceneLogic::onUserBEeiLv( const void * pBuffer, WORD wDataSize )
{
	if (wDataSize!= sizeof(CMD_S_BEILV))
	{
		CCLOG("发牌数据校验错误！");
		return false;
	}
	CMD_S_BEILV *_beilv =(CMD_S_BEILV*)pBuffer;
	CCbeilv*_beidata =CCbeilv::create(msgToView_beiLv);
	_beidata->m_base =m_baseScore;
	_beidata->m_beilv = _beilv->beillu[getMeUserDate()->wChairID];
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,_beidata);
	return true;
}

bool SceneLogic::onUserAdd( const void * pBuffer, WORD wDataSize )
{
	if (wDataSize!= sizeof(CMD_S_CallScore))
	{
		CCLOG("发牌数据校验错误！");
		return false;
	}

	//变量定义
	//CMD_S_CallScore * pCallScore=(CMD_S_CallScore *)pBuffer;
	CMD_S_DAOFAN* _daofang =(CMD_S_DAOFAN *)pBuffer;
	CCaddView* _addView =CCaddView::create(msgToView_addView);
	_addView->m_addID = switchViewChairID(_daofang->m_bUserDaofanID);
	_addView->m_AddType =1;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,_addView);
	return true;
}

bool SceneLogic::onSubOpenCard( const void * pBuffer, WORD wDataSize )
{
	if (wDataSize!=sizeof(CMD_S_OPENCARD))
	{
		CCLOG("发牌数据校验错误！");
		return false;
	}
	CMD_S_OPENCARD* _data =(CMD_S_OPENCARD*)pBuffer;

	m_wOpenUser[switchViewChairID(_data->bOpenUser)]=true;

	//--明牌效果表现
	CCopenCard* openCard = CCopenCard::create(msgToView_openCard);
	openCard->m_openID = switchViewChairID(_data->bOpenUser);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,openCard);

	//--手牌表现
	if(openCard->m_openID == 1)return true;			//--自己明牌，不做变化
	CCsendCard* msgdata=CCsendCard::create(msgToView_sendCard);
	memcpy(msgdata->m_handCardData,m_handCardData[openCard->m_openID],sizeof(BYTE)*MAX_COUNT);
	msgdata->m_handCardNum = m_handCardNum[openCard->m_openID];
	msgdata->m_bOpen =m_wOpenUser[openCard->m_openID];
	msgdata->m_bEffect =false;
	msgdata->m_userID =openCard->m_openID;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,msgdata);

	return true;
}
//游戏空闲
bool SceneLogic::OnSubGameFree( const void *pBuffer, WORD wDataSize )
{
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_GameFree));
	//效验大小 
	assert(wDataSize==sizeof(CMD_S_GameFree));
	if (wDataSize!=sizeof(CMD_S_GameFree)) return false;
	CMD_S_GameFree* _data =(CMD_S_GameFree*)pBuffer;
	int bTimeFree =_data->cbTimeLeave-2;
	m_cardTableLayer->waitingMatching(false);
	m_pCardManager->remaggerDissGameOver();
	m_pCardManager->resetManager();
	m_chipManager->dissRemoveChuoValue();
	m_chipManager->initGetChipManager();
	SpriteGameTime->setVisible(true);
	operlayer->dissUnclickTouch();
	operlayer->resetManagerOper();
	SpriteGameTime->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_23_1.png"));
	CCNotificationCenter::sharedNotificationCenter()->postNotification("Strameobjet", CCInteger::create(bTimeFree));
	CCNotificationCenter::sharedNotificationCenter()->postNotification("MI_setCCteefTag");
	return true;
}
//游戏开始
bool SceneLogic::onSubSendCard( const void * pBuffer, WORD wDataSize )
{
	CCLOG("datasize = %d",wDataSize);
	CCLOG("sizeof(CMD_S_GameStart) = %d",sizeof(CMD_S_GameStart));

	assert(wDataSize==sizeof(CMD_S_GameStart));
	if (wDataSize!=sizeof(CMD_S_GameStart)) 
		return false;
	CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pBuffer;
	//玩家信息
	m_lPlayBetScore = pGameStart->lPlayBetScore;
	m_lPlayFreeSocre = pGameStart->lPlayFreeSocre;
	m_wBankerUser = pGameStart->wBankerUser;
	m_lBankerScore = pGameStart->lBankerScore;
	int rejsbvkfsd  = pGameStart->cbTimeLeave-2;
	//设置时间,标志
	CCNotificationCenter::sharedNotificationCenter()->postNotification("Strameobjet", CCInteger::create(rejsbvkfsd));
	CCNotificationCenter::sharedNotificationCenter()->postNotification("MI_setPlaceScore");
	SpriteGameTime->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_23_2.png"));
	m_cardTableLayer->setBabnkUsedScore(pGameStart->lBankerScore);

	return true;
}
//用户下注
bool SceneLogic::onSubLandScore( const void * pBuffer, WORD wDataSize )
{
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_PlaceBet));
	//效验大小 
	assert(wDataSize==sizeof(CMD_S_PlaceBet));
	if (wDataSize!=sizeof(CMD_S_PlaceBet)) return false;
	CMD_S_PlaceBet * pPlaceBet=(CMD_S_PlaceBet *)pBuffer;
	CMD_C_HumanArea sHumanAddArea;
	memset(&sHumanAddArea,0,sizeof(CMD_C_HumanArea)); 
	m_lBetScore[pPlaceBet->cbBetArea] += pPlaceBet->lBetScore;
	m_chipManager->showGetChipManager(pPlaceBet->cbBetArea,m_lBetScore[pPlaceBet->cbBetArea]);
	m_chipManager->showChipManagerSprite(pPlaceBet->cbBetArea,pPlaceBet->lBetScore);
    SpriteGameStare->setVisible(true);
	operlayer->initClickTouch();
	return true; 
}

//游戏结束
bool SceneLogic::onSubGameStart( const void * pBuffer, WORD wDataSize )
{
	////消息处理 
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_GameEnd));
	//效验大小 
	assert(wDataSize==sizeof(CMD_S_GameEnd));
	if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;
	CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pBuffer;

	BYTE cbTimeLeaveGame =pGameEnd->cbTimeLeave-1;
	CCNotificationCenter::sharedNotificationCenter()->postNotification("Strameobjet", CCInteger::create(cbTimeLeaveGame));
	CCNotificationCenter::sharedNotificationCenter()->postNotification("MI_setCardTalayer");
	SpriteGameTime->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("BJL_23_3.png"));

	//更新庄家 玩家信息
	LONGLONG lBankerScoregame = pGameEnd->lBankerScore;					//庄家成绩
	LONGLONG lBankerTotallScoregame= pGameEnd->lBankerTotallScore;		//庄家成绩
	int		nBankerTimeGame = pGameEnd->nBankerTime ;
	LONGLONG lPlayScoreGAMER[AREA_MAX]; //做庄次数
	LONGLONG lPlayAllScoreGame =pGameEnd->lPlayAllScore;						//玩家成绩
	m_cardTableLayer->setBankUsedChengjiORrJuNumber(pGameEnd->lBankerTotallScore,pGameEnd->nBankerTime);
	m_cardTableLayer->setPlayAllScoreORchengji(pGameEnd->lPlayAllScore);

	if (operlayer->IsXIazhuNumber){
		m_pCardManager->showGameOver();
		for (int i =0;i<AREA_MAX;i++){
		lPlayScoreGAMER[i] = pGameEnd->lPlayScore[i];
		if (pGameEnd->lPlayScore[i] != 0){
		m_pCardManager->SetScoreGameOver(pGameEnd->lPlayScore[i],i,pGameEnd->lPlayAllScore);}}
	}
	m_cbCardCount[0] = 	pGameEnd->cbTableCardArray[0][0];
	m_cbCardCount[1] = 	pGameEnd->cbTableCardArray[0][1];
	m_cbCardCount[2] = 	pGameEnd->cbTableCardArray[0][2];
	m_cbCardCount1[0] = pGameEnd->cbTableCardArray[1][0];
	m_cbCardCount1[1] = pGameEnd->cbTableCardArray[1][1];
	m_cbCardCount1[2] = pGameEnd->cbTableCardArray[1][2];

	//将手牌传入牌类
	m_pCardManager->SetHandCardData(m_cbCardCount); 
	m_pCardManager->SetHandCardData1(m_cbCardCount1); 
	m_pCardManager->showPlayerCard();
	m_pCardManager->showPlayerCard1(pGameEnd->cbTableCardArray,pGameEnd->cbCardCount);
	//全局信息
	LONGLONG lRevenueGame =pGameEnd->lRevenue;							//游戏税收
	m_OperaLayer->remaggerdisflase();
	operlayer->dissUnclickTouch();
	SpriteGameStare->setVisible(false);
	for(int i =0;i<8;i++)
	{
		m_lBetScore[i] = 0;  //游戏结束重新初始化为0
	}
	return true;
}
//申请庄家
bool SceneLogic::onSubOutCard( const void * pBuffer, WORD wDataSize )
{
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_ApplyBanker));
	//效验大小 
	assert(wDataSize==sizeof(CMD_S_ApplyBanker));
	if (wDataSize!=sizeof(CMD_S_ApplyBanker)) return false;
	CMD_S_ApplyBanker * pOutCard=(CMD_S_ApplyBanker *)pBuffer;

	return true;
}
//切换庄家
bool SceneLogic::onSubPassCard( const void * pBuffer, WORD wDataSize )
{
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_ChangeBanker));
	//效验大小 
	assert(wDataSize==sizeof(CMD_S_ChangeBanker));
	if (wDataSize!=sizeof(CMD_S_ChangeBanker)) return false;
	CMD_S_ChangeBanker* pPassCard=(CMD_S_ChangeBanker *)pBuffer;
	m_cardTableLayer->setBabnkUsedScore(pPassCard->lBankerScore);
	//切换庄家的时候需要重新将成绩和局数初始化
	m_cardTableLayer->setBankUsedChengjiORrJuNumber(0,0);
	return true;
}
//下注失败
bool SceneLogic::onSubGameEnd( const void * pBuffer, WORD wDataSize )
{
	////消息处理
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_PlaceBetFail));
	//效验大小 
	assert(wDataSize==sizeof(CMD_S_PlaceBetFail));
	if (wDataSize!=sizeof(CMD_S_PlaceBetFail)) return false;
	CMD_S_PlaceBetFail * pPlaceBetFail=(CMD_S_PlaceBetFail *)pBuffer;
	return true;
}
//申请 请求
bool SceneLogic::onUserExpression( const void * pBuffer, WORD wDataSize )
{
	//消息处理
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_CommandResult));
	//效验大小 
	//assert(wDataSize==sizeof(CMD_S_CommandResult));
	//if (wDataSize!=sizeof(CMD_S_CommandResult)) return false;
	CMD_S_CommandResult* _data =(CMD_S_CommandResult*)pBuffer;

	return true;
}

//取消做庄
bool SceneLogic::OnSubUserCancelBanker( const void * pBuffer, WORD wDataSize )
{
	//消息处理
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(CMD_S_CancelBanker));
	//效验大小 
	//assert(wDataSize==sizeof(CMD_S_CancelBanker));
	//if (wDataSize!=sizeof(CMD_S_CancelBanker)) return false;
	CMD_S_CancelBanker* _data =(CMD_S_CancelBanker*)pBuffer;
	return true;
}
//游戏记录
bool SceneLogic::OnSubCheatCard( const void * pBuffer, WORD wDataSize )
{
	//消息处理
	CCLOG("%d",wDataSize);
	CCLOG("%d",sizeof(tagServerGameRecord));
	//效验大小 
	//if (wDataSize%sizeof(tagServerGameRecord)!=0) return false;

	WORD temp  = wDataSize/sizeof(tagServerGameRecord);
	for (WORD wIndex= 0; wIndex<temp; wIndex++)
	{
		tagServerGameRecord * pServerGameRecord=(((tagServerGameRecord *)pBuffer)+wIndex);
		BYTE m_cbKingWinner = pServerGameRecord->cbKingWinner;						//天王赢家
		bool m_bPlayerTwoPair =pServerGameRecord->bPlayerTwoPair;						//对子标识
		bool m_bBankerTwoPair = pServerGameRecord->bBankerTwoPair;						//对子标识
		BYTE m_cbPlayerCount =pServerGameRecord->cbPlayerCount;						//闲家点数
		BYTE m_cbBankerCount = pServerGameRecord->cbBankerCount;						//庄家点数
		m_cardTableLayer->initScrollView(m_cbPlayerCount,m_cbBankerCount);
	}
	return true;
}
void SceneLogic::onLinkResult( CCObject* obj )
{
	CCInteger* Interger = (CCInteger*)obj;

	switch (Interger->getValue())
	{
	case 0:			// 0为连接失败 
		break;
	case 1:			// 1为连接成功
		{
			//EntityMgr::instance()->getDispatch()->sendLoginPacket();

			SceneControl* pSceneControl = SceneControl::sharedSceneControl();
			CCScene* pScene = pSceneControl->getScene(SCENE_game,true);
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
		break;
	case 2:			// 2为没有服务器
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOVIEW,CCInteger::create(msgToView_socketoff));
		}
		break;
	default:
		break;
	}
}

void SceneLogic::onUpdateScoreAndGoldEgg( CCObject* obj )
{
	sendSeverData(SUB_GF_ROOM_SCOREUPDATA, 0, 0);
}

int SceneLogic::getUserRealChairID(DWORD userID)
{
	CUserItem* pUserItem = (CUserItem*)EntityMgr::instance()->roomFrame()->getUserItem(userID);
	if (!pUserItem)
	{
		return 1;
	}

	tagUserData* pUserDate = pUserItem->getUserData();
	if (!pUserDate)
	{
		return 1;
	}
	int nChairID = switchViewChairID(pUserDate->wChairID);
	return nChairID;
}
//获取用户信息
void SceneLogic::userInforDeal( CCInteger* _data )
{
	CCuserInfor* _inforData=(CCuserInfor*)_data;
	CCLOG("ID == %d",_inforData->m_userInforID);
	CCLOG("Score == %d",_inforData->m_score);
	CCLOG("Gold == %d",_inforData->m_GoldEggs);
	if(_inforData->m_gender != 0 && _inforData->m_score !=0 &&_inforData->m_userInforID !=0
		&& _inforData->m_userInforID  != g_GlobalUnits.getGolbalUserData()->dwUserID)
	{
		CCLOG("ID == %d",_inforData->m_userInforID);
		CCLOG("Score == %d",_inforData->m_score);
		CCLOG("Gold == %d",_inforData->m_GoldEggs);
		CCLOG("Name == %s",_inforData->m_name);
		m_cardTableLayer->setUserIcon(_inforData->m_userInforID,_inforData->m_gender,_inforData->m_name,_inforData->m_score,_inforData->m_PosName);
		CCUserDefault::sharedUserDefault()->setStringForKey("shangJia", _inforData->m_name);
		Tag tag;
		tag.userId = 0;
		tag.gender = _inforData->m_gender;
		SoundEffect::sharedSoundEffect()->initLeftTag(tag);
	}
	CCLOG("grdggwegweg");
}







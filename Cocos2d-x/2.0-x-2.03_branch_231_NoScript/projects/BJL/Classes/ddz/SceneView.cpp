#include "SceneView.h"
#include "SceneLogic.h"
#include "DDZRes.h"
#include "../gui/RoomLayer.h"
#include "SceneControl.h"

SceneView::SceneView(void)
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneView::OnMessage),MESSAGE_TOVIEW,NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneView::receiveMenuClickCallfunc),MESSAGE_MENUCLICKED,NULL);//������ť�����Ϣ
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(SceneView::wangZha),"WANGZHA",NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneView::Strameobjet), "Strameobjet", NULL);

	m_userOutCardState = 3 ;//3Ϊ��ͨ����
	longNumberuserInforID = 0;
}


SceneView::~SceneView(void)
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MESSAGE_TOVIEW);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MESSAGE_MENUCLICKED);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"WANGZHA");
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "Strameobjet");

}

bool SceneView::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	bool ret =false;
	do 
	{
		ScoreUseidbool = false;
		CCSprite * background = CCSprite::create(texture_name::s_background);
		background->setAnchorPoint(CCPointZero);
		this->addChild(background);

		CCMenuItemImage * CloseCardlayerItem = CCMenuItemImage::create("BJL/BJL_08.png","BJL/BJL_08_2.png",this,
			menu_selector(SceneView::SetCloseCall));
		CCMenu *CloseMen = CCMenu::create(CloseCardlayerItem,NULL);
		CloseMen->setAnchorPoint(CCPointZero);
		CloseMen->setPosition(30,size.height*0.9);
		addChild(CloseMen);
	    SceneLogic *logic= SceneLogic::create();	//--�߼�����
		this->addChild(logic);

		m_menuLayer = ViewMenuLayer::create();							//--ʱ�� ��־
		this->addChild(m_menuLayer);

		m_gameTask=GameTaskCommon::create();					//�������
		this->addChild(m_gameTask);

		m_effectView =ViewCardEffect::create();						//--Ч��
		this->addChild(m_effectView);



		m_settlementNode = Settlement::create();					//����
		m_settlementNode->setPosition(ccp(size.width/2,size.height/2+50.0f));
		m_settlementNode->setVisible(false);
		this->addChild(m_settlementNode);

        m_face =VoiceAndFace::create();								//--����
		this->addChild(m_face);

		m_dialogLayer = CCLayer::create();
		this->addChild(m_dialogLayer);

		m_isAgency =false;												//--������
		m_isLandLord=true;												//--�е�����ť�ͱ���
		m_AgencyNum=0;

		m_gameStae =Game_null;
		m_timeKey=0;

		ret = true;
	} while (0);
	
	return ret;
}

void SceneView::SetCloseCall( CCObject *obj )
{
	DialogLayer * dialog = DialogLayer::create(dialog_back);
	addChild(dialog,10);
}
void SceneView::onBankrupt( CCObject * obj )
{
	/*
	tagBankruptObj* tag=(tagBankruptObj*)obj;
	if (tag->bBankrupt == false)	//��һ���Ʋ� ����5000�𷵻ش���
	{
	m_dialogLayer->removeAllChildren();
	DialogLayer * dialog = DialogLayer::create(dialog_poChanSongCoin);
	m_dialogLayer->addChild(dialog);

	}
	else //�Ʋ��Żش���
	{
	m_dialogLayer->removeAllChildren();
	DialogLayer * dialog = DialogLayer::create(dialog_poChan);
	m_dialogLayer->addChild(dialog);
	}
	*/
	CCDirector::sharedDirector()->replaceScene(SceneControl::sharedSceneControl()->getScene(SCENE_start,false));
}

void SceneView::OnMessage( CCObject* obj )
{
	CCInteger* _int=(CCInteger*)obj;
	switch(_int->getValue())
	{
	case msgToView_UserInfor:				//--�û�����Ϣ����
		//logic->userInforDeal(_int);
		CCLog("sfdgbfsdfbfd");
		break;
	case msgToView_addView:				//--��Ϸ�ӱ�����
		addViewDeal(_int);
		break;
	case msgToView_backCard:				//--���Ʊ仯
		onBackTaskDeal(_int);
		break;
	case msgToView_start:						//--׼�����ƿ�ʼ
		startGameDeal();
		break;
	case msgToView_startView:				//--���ƿ�ʼ����
		startGameViewDeal(_int);
		break;
	case msgToView_sendCard:				//--���Ʊ���
		sendCardDeal(_int);
		break;
	case msgToView_openCard:				//--���Ʊ���
		openCardDeal(_int);
		break;
	case msgToView_landLord:				//--����������
		landLordDeal(_int);
		break;
	case msgToView_time:						//--ʱ�ӱ仯
		timeConreolDral(_int);
		break;
	case 	msgToView_outCard:				//--���Ʊ���
		outCardDeal(_int);
		break;
	case 	msgToView_passCard:				//--���Ʊ���
		passCardDeal(_int);
		break;
	case msgToView_gameOver:				//--��Ϸ��������
		gameOverDeal(_int);
		break;
	case msgToView_openCardNum:		//--�������ư�ť�����仯
		{
		}
		break;
	case msgToView_beiLv:					//--���ʱ仯����
		{
			CCbeilv*_beiData=(CCbeilv*)_int;
		//	m_cardTableLayer->setMultiplyingPower(_beiData->m_base,_beiData->m_beilv);
		//	m_cardTableLayer->setDiFen(_beiData->m_base);
		}
		break;
	case msgToview_TimeCallBack:				//--ʱ�ӻص�
		timeCallBackDeal(_int);
		break;
	case msgToView_OnLine:						//--���߱���
		{
			CConline* _onLineData =(CConline*)_int;
		//	m_cardTableLayer->setUserIsOnline(_onLineData->m_userID,_onLineData->m_isOnline);
		}
		break;
	case msgToView_Reconnect:					//--��������
		{
			//m_cardTableLayer->waitingMatching(false);
		}
		break;
	case msgToView_socketoff:					//--����Ͽ�
		{
			if (m_dialogLayer->getChildrenCount()>0&&m_dialogLayer->getChildren()->objectAtIndex(0))
			{
				DialogLayer * dialog = (DialogLayer *)m_dialogLayer->getChildren()->objectAtIndex(0);
				if (dialog_dismissTable==dialog->m_type)
				{
					break;
				}
			}
			m_dialogLayer->removeAllChildrenWithCleanup(true);
			DialogLayer * dialog = DialogLayer::create(dialog_hints);
			m_dialogLayer->addChild(dialog);

		}
		break;
	case 	msgToView_socketoffConnect:				//--�Զ�����
		{
			m_effectView->runEffect(Effect_LlinkOFF,1);
			schedule(schedule_selector(SceneView::onLlinkOFF),2.0f,1,2.0f);
		}
		break;
	case 	msgToView_VoiceAndFace:			//--�����仯
		{
			CCfaceAndVioce* _face=(CCfaceAndVioce*)_int;
			if(_face->m_Type == 2 && _face->m_KeyID < 0)
			{
				string voiceString = _face->voice;
				m_effectView->runVoice(voiceString, _face->m_UserID);
			}else
			{
				m_effectView->runVoiceAndFace(_face->m_Type,_face->m_KeyID,_face->m_UserID);
			}
		}
		break;
	case msgToview_LordView:					//--��������
		{
			CClandView* _landView=(CClandView*)_int;
		//	m_cardTableLayer->setLordIcon(_landView->m_landUserID);
		}
		break;
	case msgToView_SettmentUser:			//�����������
		{
		//	m_settlementNode->setUserMessage(_int);
		//	m_effectView->runSettlementEffect(_int,g_tableConsume,m_cardTableLayer);

		}
		break;
	case msgToView_huafeidian:
		{
			CChuafeidian* _data=(CChuafeidian*)_int;
			m_effectView->runHfdEffect(_data);
		}
		break;
	case msgToView_Close:
		{
			m_dialogLayer->removeAllChildrenWithCleanup(true);
			DialogLayer * dialog = DialogLayer::create(dialog_dismissTable);
			m_dialogLayer->addChild(dialog);
		}
		break;
	case msgToView_RoomLimit:
		{
			CCRoomLimit* _data=(CCRoomLimit*)_int;
			m_dialogLayer->removeAllChildrenWithCleanup(true);
			dialog_type type=dialog_poChan;
			switch(_data->m_RoomLimitKey)
			{
			case 0:
				type=dialog_poChan;
				break;
			case 1:
				type=dialog_roomLimitMin;
				break;
			case 2:
				type=dialog_roomLimitMax;
				break;
			default:
				return;
			}
			DialogLayer * dialog = DialogLayer::create(type);
			m_dialogLayer->addChild(dialog);
		}
		break;
	}
}

void SceneView::startGameDeal()
{
//	operlayer->showDXGZJZBtns();
}

void SceneView::startGameViewDeal( CCInteger* _data )
{
	CCopenStart* _openStart =(CCopenStart*)_data;
	m_effectView->runEffect(_openStart->m_bOpenCard?Effect_OpenStart:Effect_gameStart,_openStart->m_bCurrentUser);
}

void SceneView::onBackTaskDeal( CCInteger* _data )
{
	CCbackData* _backData=(CCbackData*)_data;
}

void SceneView::addViewDeal( CCInteger* _data )
{
	CCaddView* _addData=(CCaddView*)_data;
	switch(_addData->m_AddType)
	{
	case 1:	//--����
		m_effectView->runEffect(Effect_jiaBei,_addData->m_addID);
		break;
	}
}

void SceneView::sendCardDeal( CCInteger* _data )
{
	//CCsendCard* _sendCardData=(CCsendCard*)_data;
	//if (_sendCardData->m_bEffect==true && _sendCardData->m_userID==1)		//--��һ�η���ȡ���й�
	//{
	//	m_isAgency =false;
	//	m_effectView->runRobot(false);
	//}
	//((ViewHandCard*)m_handCardView)->setHardCard(_sendCardData->m_userID,_sendCardData->m_handCardData,
	//	_sendCardData->m_handCardNum,_sendCardData->m_bEffect,_sendCardData->m_bOpen);
	//if (_sendCardData->m_handCardNum==2||_sendCardData->m_handCardNum==1)
	//{
	//	m_effectView->runEffect(Effect_alarm,_sendCardData->m_userID);
	//	//SoundEffect::sharedSoundEffect()->playEffect(sound_name::s_warning,_sendCardData->m_userID);
	//}
	//m_menuLayer->notificationMenuBarAutoHints();
}

void SceneView::openCardDeal( CCInteger* _data )
{
	CCopenCard*_openCardData=(CCopenCard*)_data;
	m_effectView->runEffect(Effect_openCard,_openCardData->m_openID);
}

void SceneView::landLordDeal( CCInteger* _data )
{
	CClandLord* _landLordData = (CClandLord*) _data;
	EffectType type ;
	if (_landLordData->m_LandKey==1)
	{
		if (m_isLandLord)
		{
			type =Effect_NoLandLord;
		}
		else
		{
			type =Effect_NoRobLord;
		}
	}
	else if (_landLordData->m_LandKey==2)
	{
		if (m_isLandLord)
		{
			type =Effect_LandLord;
			m_isLandLord=false;
		}
		else
		{
			type =Effect_RobLord;
		}
	}else if (_landLordData->m_LandKey==3)
	{
		type =Effect_NoRobLord;
	}
	else if (_landLordData->m_LandKey==4)
	{
		type =Effect_RobLord;
	}

	m_effectView->runEffect(type,_landLordData->m_landID);
}

void SceneView::timeConreolDral( CCInteger* _data )
{
}

void SceneView::outCardDeal( CCInteger* _data )
{
//	m_cardTableLayer->waitingMatching(false);//ȷ����Ϸ���ŶӶ������ص�
}

void SceneView::passCardDeal( CCInteger* _data )
{
	CCpassCard* _passCard =(CCpassCard* )_data;
	m_effectView->runEffect(Effect_PassCard,_passCard->m_passUser);
}

void SceneView::gameOverDeal( CCInteger* _data )
{
}

void SceneView::timeCallBackDeal( CCInteger* _data )
{
}

void SceneView::receiveMenuClickCallfunc(CCObject * obj)
{
	CCInteger * integer = (CCInteger*)obj;
	switch(integer->getValue())
	{
	case menu_changeTable:	
		{
		}
		break;
	case menu_visibleStartMenuItem:	//���ƿ�ʼ
		{
		}
		break;
	case menu_startMenuItem://��ͨ��ʼ
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,CCInteger::create(magToLogc_gameStart));
		}
		break;
	case menu_rechargemenuItem://���ٳ�ֵ
		CCLOG("SceneView recive menu_rechargemenuItem click");
		CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_JNICONTROL,CCInteger::create(MSG_JNI_Recharge));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		EntityMgr::instance()->getDispatch()->sendOrderInfo("tbf",2);
#endif
		break;
	case menu_outCardMenuItem://����
		CCLOG("SceneView recive menu_outCardMenuItem click");
		{
			CCLOG("ViewHandCard recive menu_outCardMenuItem click");
		}
		break;
	case menu_passOutCardMenuItem:	//��Ҫ
		{
		}
		break;
	case menu_hintMenuItem:	//��ʾ
		{
		}
		break;
	case menu_jiaoDiZhuItem:	//�е���
	case menu_qiangDiZhuItem://������
		{

			CClandLord* landord =CClandLord::create(msgToLogc_LandLord);
			landord->m_isLand = true;
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,landord);
		}
		break;
	case menu_buJiaoItem://���е���e
	case menu_passQiangDiZhuItem://��������
		{
			CCLOG("ViewHandCard recive menu_passQiangDiZhuItem click");
			CClandLord* landord =CClandLord::create(msgToLogc_LandLord);
			landord->m_isLand = false;
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,landord);
		}
		break;
	case menu_visibleCardItem://����
		{

		}
		break;
	case menu_doubleItem://�ӱ�
		{

		}
		break;
	case menu_unDoubleItem://���ӱ�

		break;
	case menu_settlementDetial://��������
		{
			if (m_settlementNode->isVisible())
			{
				m_settlementNode->setVisible(false);
			}
			else
			{
				m_settlementNode->setVisible(true);
			}
		}
		break;
	case menu_again://����һ��
		{
			m_settlementNode->setVisible(false);
			CCLOG("SceneView recive menu_again click");
			CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,CCInteger::create(msgToLogic_MoreGame));
		}
		break;
	case menu_MenuBarPullItem://�˵�����������
		CCLOG("SceneView recive menu_MenuBarPullItem click");
		break;
	case menu_menuBarRobotItem://�˵����йܰ�ť
		{
			CCLOG("SceneView recive menu_menuBarRobotItem click");
			//if(m_gameStae>=Game_Start)//�ﵽ��������״̬����ܿ�ʼ�����й�
			//{
			m_isAgency = true;
			m_AgencyNum=0;
			m_effectView->runRobot(true);
			//schedule(schedule_selector(SceneView::timeAgencyDeal),2.0f);//--�����˴���
			//}
		}
		break;
	case menu_menuBarTalkItem://�˵������찴ť
		{
			//if (m_gameStae>=Game_Start)
			//{
			m_face->runOutOrIn();
			//}
		}
		break;
	case menu_menuBarOptionsItem://�˵������ð�ť
		{
			CCLOG("SceneView recive menu_menuBarOptionsItem click");
			SetUpLayer * setUpLayer = SetUpLayer::create();	//����
			m_dialogLayer->addChild(setUpLayer);

		}
		break;
	case menu_menuBarTaskItem://�˵�������ť
		{
			m_gameTask->runOutOrIn();
			m_effectView->runEffect(Effect_task,1);
		}
		break;
	case menu_menuBarBackItem://�˵������ذ�ť
		CCLOG("SceneView recive menu_menuBarBackItem click");
		{
			if(m_dialogLayer->getChildrenCount()>0)
			{
				m_dialogLayer->removeAllChildrenWithCleanup(true);
			}else{
				DialogLayer * dialog = DialogLayer::create(dialog_back);
				m_dialogLayer->addChild(dialog);

			}
		}
		break;
	case menu_number:	//���ƿ�ʼ��ť�ϵ�����
		CCLOG("SceneView recive menu_number click");
		break;
	case menu_visibleCardStartItem:	//���ƹ����е����ƿ�ʼ��ť
		{
		}
		break;
	case menu_OutAgency:				//--ȡ���й�
		{
			m_isAgency =false;
		}
		break;
	}
}

void SceneView::timeAgencyDeal(float ft)
{
	unschedule(schedule_selector(SceneView::timeAgencyDeal));
	CCtimeCallBack* _timeCallBack=CCtimeCallBack::create(0);
	_timeCallBack->m_gameState =m_gameStae;
	_timeCallBack->m_timeKey =m_timeKey;
	timeCallBackDeal(_timeCallBack);  //--�����˴���
}

void SceneView::onLlinkOFF( float ft )
{
	unschedule(schedule_selector(SceneView::onLlinkOFF));
	SceneControl::sharedSceneControl()->getScene(SCENE_endAgain,false);
}

void SceneView::wangZha(CCObject *obj)
{
	//((ViewHandCard*)m_handCardView)->newRound();
}

void SceneView::Strameobjet( CCObject *obj )
{
	int numbers = ((CCInteger *)obj)->getValue();
	m_menuLayer->setTimer(1,Game_Start,numbers,true,0);
}

void SceneView::StrameNumberbjet( CCObject *obj )
{
	int NumberUsed = ((CCInteger *)obj)->getValue();
	longNumberuserInforID = NumberUsed;
}





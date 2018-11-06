#include "SIX_PopWndMessage.h"
#include "SIX_PlayerMgr.h"
#include "SIX_ClientRoom.h"

const char C_szContent[][128]={{"大家好~"}, {"动作快点呀！"}, {"不要抢！这盘我来坐庄！"}, {"我开始挂机了，有事再叫我~"}, 
{"不好意思，得离开了，下次再玩哦~"}, {"有本事再来一盘！"}};

enum
{
	CHAT_LIST_VIEW_ID, // 聊天列表
	DEFAULT_CHAT_LIST_VIEW_ID, // 默认聊天内容
	CLOSE_ID,	// 关闭按钮
	SEND_ID, // 发送按钮
	DEFAULT_CHAT_BTN_START = 1000, // 默认聊天内容
	DEFAULT_CHAT_BTN_END = 1500, // 默认聊天内容
};

SIX_PopWndMessage::~SIX_PopWndMessage(void)
{
	while (0 <= m_deChatContent.size())
	{
		CMD_ChatContent * pChat = m_deChatContent.front();
		CC_SAFE_DELETE(pChat);
		m_deChatContent.pop_front();
	}
}

SIX_PopWndMessage *SIX_PopWndMessage::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset/*=DEFAULT_SHAKEOFFSET*/,MOVABLE_TYPE showType/*=MOVABLE_LEFT*/,MOVABLE_TYPE hideType/*=MOVABLE_RIGHT*/,bool bSeqExec/*=true*/)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	CCSize szWind = CCDirector::sharedDirector()->getWinSize();
	if (0.0001 > x && 0.0001 > y)
	{
		x = (szWind.width - width) / 2;
		y = (szWind.height - height) / 2;
	}
	if (0.0001 > width &&  0.0001 > height)
	{
		width = szWind.width;
		height = szWind.height;
	}

	SIX_PopWndMessage *pMsg = new SIX_PopWndMessage();
	if (pMsg && pMsg->init())
	{
		pMsg->initWithColor(color,width,height);
		pMsg->setPosition(x,y);
		pMsg->setRedrawBorder(false);
		pMsg->setTouchEnabled(true);
		pMsg->setAllowDragged(false);
		pMsg->m_ForbiddenTouch = true;
		pMsg->m_bCloseThenCleanup = false;
		pMsg->setShakeOffset(shakeOffset);
		pMsg->setShowType(showType);
		pMsg->setHideType(hideType);
		pMsg->setSeqExec(bSeqExec);
		pMsg->setObjName("SIX_PopWndMessage");
		//pMsg->backgroundWithFile("Common/SmallWndInWnd.png");

		// 聊天列表
		CCRect listViewRect = CCRect(20, height-200-20, width-40, 200);
		CCSize listViewCell = CCSize(width-40,40);
		pMsg->createListView(pMsg->getInformationListview(), (int)CHAT_LIST_VIEW_ID, listViewRect, listViewCell);
		pMsg->addChild(pMsg->getInformationListview());
	}
	return pMsg;
}

bool SIX_PopWndMessage::init()
{
	if (!SIX_EffectPopWnd::init())
		return false;

	InitMask(ccc4(0,0,0,128));
	m_PannelShowStyle = NORMAL_SEND_AND_RECEIVE_PANEL;

	m_bIsHaveShow = false;
	m_InformationDelegate = 0;
	m_pSendPanel = 0;
	m_pChatContent = 0;
	return true;
}

void SIX_PopWndMessage::onEnterTransitionDidFinish()
{
	char cBuffer[128]="";
	CCSize sizeWnd = getContentSize();
	
	createSendPanel();
}

void SIX_PopWndMessage::onShowFinished()
{
	setChangePanel(NORMAL_SEND_AND_RECEIVE_PANEL);
}

bool SIX_PopWndMessage::OnClose()
{
	return true;
}

void SIX_PopWndMessage::OnTouchLogic(CCTouch *pTouch,int pEvent)
{
	SIX_EffectPopWnd::OnTouchLogic(pTouch,pEvent);

	switch (pEvent)
	{
	case CCTOUCHBEGAN:
		{
			if (m_pChatContent)
				m_pChatContent->ccTouchBegan(pTouch,0);
			break;
		}
	case CCTOUCHMOVED:
		{
			if (m_pChatContent)
				m_pChatContent->ccTouchMoved(pTouch,0);
			break;
		}
	case CCTOUCHENDED:
		{
			if (m_pChatContent)
				m_pChatContent->ccTouchEnded(pTouch,0);
			break;
		}
	case CCTOUCHCANCELLED:
		{
			if (m_pChatContent)
				m_pChatContent->ccTouchCancelled(pTouch,0);
			break;
		}
	}
}

void SIX_PopWndMessage::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
}

void SIX_PopWndMessage::ReceiInformation(CMD_ChatContent *pContent)
{
	CMD_ChatContent *pChatContent = new CMD_ChatContent;
	memcpy(pChatContent, pContent, sizeof(CMD_ChatContent));
#ifdef WIN32
	wstring wszContent = SIX_Utility::GetInstance()->Utf8ToUnicode(pChatContent->szCentent);
	string strContent = SIX_Utility::GetInstance()->UnicodeToAnsi(wszContent.c_str());
	wstring wszNickName = SIX_Utility::GetInstance()->Utf8ToUnicode(pChatContent->szSpeakNickName);
	string strNickName = SIX_Utility::GetInstance()->UnicodeToAnsi(wszNickName.c_str());
#else
	string strContent = SIX_Utility::GetInstance()->U2G(pChatContent->szCentent);
	string strNickName = SIX_Utility::GetInstance()->U2G(pChatContent->szSpeakNickName);
#endif
	memcpy(pChatContent->szCentent, strContent.c_str(), sizeof(pChatContent->szCentent));
	memcpy(pChatContent->szSpeakNickName, strNickName.c_str(), sizeof(pChatContent->szSpeakNickName));
	m_deChatContent.push_back(pChatContent);

	if ( !IsShow() )
	{
		setChangePanel(MIN_SHOW_RECEIVE_PANEL);
	}
	else
	{
		setReceiveMsgToListView(true);
	}
}

void SIX_PopWndMessage::setChangePanel(pannelshowstyle pannelStyle)
{
	m_PannelShowStyle = pannelStyle;

	if (MIN_SHOW_RECEIVE_PANEL == pannelStyle)
	{
		if ( !m_bIsHaveShow  &&  0 < m_deChatContent.size()  &&  m_InformationDelegate)
		{
			CMD_ChatContent *pChatContent = m_deChatContent.front();
			m_InformationDelegate->OnShowInformation(pChatContent);
			m_bIsHaveShow = true;
			setReceiveMsgToListView(false);
		}
	}
	else if (NORMAL_SEND_AND_RECEIVE_PANEL == pannelStyle)
	{
		m_bIsHaveShow = false;
		this->stopAllActions();
		setReceiveMsgToListView(true);
	}
}

void SIX_PopWndMessage::setInformationDelegate(SIX_InformationDelegate *pDelegate)
{
	m_InformationDelegate = pDelegate;
}

void SIX_PopWndMessage::DoEnter()
{
	if ( 0==m_pChatContent  ||  !IsShow())
		return;
	m_pChatContent->attachWithIME();
	
	if (0 >= strlen(m_pChatContent->getTTF()->getString()))
		return;

	CMD_ChatContent chatContent;
	chatContent.iChatType = 0;
	chatContent.lSpeakUserId = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	memcpy(chatContent.szCentent, m_pChatContent->getTTF()->getString(), sizeof(chatContent.szCentent));
	memcpy(chatContent.szSpeakNickName, SIX_PlayerMgr::GetInstance()->getMyNickName(), sizeof(chatContent.szSpeakNickName));
	SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_TABLE_SPEAK, &chatContent, sizeof(chatContent));
	m_pChatContent->getTTF()->setString("");
	m_pChatContent->attachWithIME();
	SIX_Utility::GetInstance()->FixedTexParameters(m_pChatContent->getTTF()->getTexture());
}

void SIX_PopWndMessage::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();
	if (CCControlEventTouchUpInside != event)
		return;
	if (DEFAULT_CHAT_BTN_START <= tag  &&  DEFAULT_CHAT_BTN_END >= tag)
	{
		CMD_ChatContent chatContent;
		chatContent.iChatType = 0;
		chatContent.lSpeakUserId = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
		memcpy(chatContent.szCentent, C_szContent[tag-DEFAULT_CHAT_BTN_START], sizeof(chatContent.szCentent));
		memcpy(chatContent.szSpeakNickName, SIX_PlayerMgr::GetInstance()->getMyNickName(), sizeof(chatContent.szSpeakNickName));
#ifdef WIN32
		wstring wszContent = SIX_Utility::GetInstance()->AnsiToUnicode(chatContent.szCentent);
		string strContent = SIX_Utility::GetInstance()->UnicodeToUtf8(wszContent.c_str());
		wstring wszNickName = SIX_Utility::GetInstance()->AnsiToUnicode(chatContent.szSpeakNickName);
		string strNickName = SIX_Utility::GetInstance()->UnicodeToUtf8(wszNickName.c_str());
#else
		string strContent = SIX_Utility::GetInstance()->G2U(chatContent.szCentent);
		string strNickName = SIX_Utility::GetInstance()->G2U(chatContent.szSpeakNickName);
#endif
		memcpy(chatContent.szCentent, strContent.c_str(), sizeof(chatContent.szCentent));
		memcpy(chatContent.szSpeakNickName, strNickName.c_str(), sizeof(chatContent.szSpeakNickName));
		SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_TABLE_SPEAK, &chatContent, sizeof(chatContent));
		Show(false);
		return;
	}

	switch (tag)
	{
	case CLOSE_ID:
		{
			Show(false);
			break;
		}
	case SEND_ID:
		{
			if ( 0==m_pChatContent || 0 >= strlen(m_pChatContent->getTTF()->getString()))
				return;

			CMD_ChatContent chatContent;
			chatContent.iChatType = 0;
			chatContent.lSpeakUserId = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
			memcpy(chatContent.szCentent, m_pChatContent->getTTF()->getString(), sizeof(chatContent.szCentent));
			memcpy(chatContent.szSpeakNickName, SIX_PlayerMgr::GetInstance()->getMyNickName(), sizeof(chatContent.szSpeakNickName));
			SIX_ClientRoom::GetInstance()->send_data(TABLE_MAIN, TABLE_SUB_TABLE_SPEAK, &chatContent, sizeof(chatContent));
			m_pChatContent->getTTF()->setString("");
			SIX_Utility::GetInstance()->FixedTexParameters(m_pChatContent->getTTF()->getTexture());
#ifdef WIN32
			m_pChatContent->attachWithIME();
#endif
			break;
		}
	default:
		{
			SIXLog("未处理的按钮事件 tag=%d", tag);
			break;
		}
	}
	return;
}

void SIX_PopWndMessage::createListView(SIX_ListView *&pListView, int iTag, const CCRect &listViewRect, const CCSize &listViewCell)
{
	SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
	pContainer->setContentSize(CCSize(listViewRect.size.width, listViewRect.size.height));
	pContainer->setPosition(ccp(listViewRect.getMinX(), listViewRect.getMinY()));

	SIX_ScrollBar *pScrollBar = SIX_ScrollBar::create(
		"scrollbar.png",CCRect(0,51,17,17),CCSize(listViewRect.size.height-17*2,17),
		"scrollbar.png",CCRect(0,51,17,17),
		"scrollbar.png",CCRect(0,34,17,17),
		"scrollbar.png",CCRect(0,34,17,17),
		"scrollbar.png",CCRect(0,0,17,17),
		"scrollbar.png",CCRect(0,17,17,17),
		CCSize(17,17),
		false
		);
	pScrollBar->setAnchorPoint(ccp(0,0));
	pScrollBar->setMinimumValue(0);
	pScrollBar->setMaximumValue(100);
	pScrollBar->setValue(0);
	pScrollBar->setDefaultTouchPriority(m_nPriority-1);

	pListView = SIX_ListView::create(ccc4(0,0,0,0),
		ccp(listViewRect.getMinX(),listViewRect.getMinY()),
		CCSize(listViewRect.size.width, listViewRect.size.height),
		CCSize(listViewCell.width, listViewCell.height),
		kCCScrollViewDirectionVertical,
		pContainer,
		pScrollBar
		);
	pListView->setObjName("ListView");
	pListView->setTag(iTag);
	pListView->setTouchEnabled(true);	
	pListView->getTableView()->setClippingToBounds(true);
	pListView->getTableView()->setDirection(kCCScrollViewDirectionVertical);
	pListView->getTableView()->setVerticalFillOrder(kCCTableViewFillTopDown);
	pListView->getTableView()->setBounceable(true);
	pListView->getTableView()->setDelegate(this);
	return;
}

void SIX_PopWndMessage::createSendPanel()
{
	m_pSendPanel = CCScale9Sprite::create("Chat_BG.png");
	if ( 0==m_pSendPanel  ||  0==m_pInformationListView)
		return;

	m_pSendPanel->ignoreAnchorPointForPosition(true);
	m_pSendPanel->setPreferredSize(CCSize(getContentSize().width-10, getContentSize().height-m_pInformationListView->getPositionY()+30));
	m_pSendPanel->setPosition(ccp((getContentSize().width-m_pSendPanel->getPreferredSize().width)/2, 5));
	addChild(m_pSendPanel);

	float fOffsetX = getContentSize().width - 25;
	float fOffsetY = m_pSendPanel->getPositionY()+m_pSendPanel->getContentSize().height;

	// 聊天类型
	CCLabelTTF *pType = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U("桌子").c_str(),"微软雅黑",28, \
		CCSize(110,70),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	if (0 != pType)
	{
		pType->setColor(ccc3(255,255,255));
		pType->setOpacity(255);
		pType->ignoreAnchorPointForPosition(true);
		pType->setPosition(ccp(0, fOffsetY-80));
		SIX_Utility::GetInstance()->FixedTexParameters(pType->getTexture(),true);
		m_pSendPanel->addChild(pType);
	}
	// 关闭
	CCControlButton * pCloseBT = SIX_Utility::GetInstance()->CreateButtonWithFileCell("chat_CloseBT.png", 2);
	if (pCloseBT)
	{
		fOffsetX -= pCloseBT->getContentSize().width;
		pCloseBT->setZoomOnTouchDown(false);
		pCloseBT->setDefaultTouchPriority(m_nPriority-1);
		pCloseBT->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndMessage::doEvents),32);
		pCloseBT->setPosition(ccp(fOffsetX,fOffsetY-pCloseBT->getContentSize().height-15));
		pCloseBT->setTag(CLOSE_ID);
		m_pSendPanel->addChild(pCloseBT);
	}
	// 发送
	CCControlButton * pSendBT = SIX_Utility::GetInstance()->CreateButtonWithFileCell("char_SendBT.png", 2);
	if (pSendBT)
	{
		fOffsetX = fOffsetX - pSendBT->getContentSize().width - 5;
		pSendBT->setZoomOnTouchDown(false);
		pSendBT->setDefaultTouchPriority(m_nPriority-1);
		pSendBT->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndMessage::doEvents),32);
		pSendBT->setPosition(ccp(fOffsetX,fOffsetY-pSendBT->getContentSize().height-15));
		pSendBT->setTag(SEND_ID);
		m_pSendPanel->addChild(pSendBT);
	}
	// 用户名输入框
	float fEditWidth = fOffsetX-(pType->getPositionX()+pType->getContentSize().width)-10;
	CCScale9Sprite *pEditBG = CCScale9Sprite::create("chat_EditBG.png");
	if ( pEditBG )
	{
		pEditBG->ignoreAnchorPointForPosition(true);
		pEditBG->setPreferredSize(CCSize(fEditWidth, 63));
		pEditBG->setPosition(ccp(pType->getPositionX()+pType->getContentSize().width, fOffsetY-pEditBG->getPreferredSize().height-10));
		m_pSendPanel->addChild(pEditBG);
	}
	m_pChatContent = new SIX_EditBox();
	if (m_pChatContent  &&  pEditBG)
	{
		m_pChatContent->setInputTextMaxCount(50);
		m_pChatContent->setContentSize(pEditBG->getContentSize());
		//m_pChatContent->setContentSize(CCSize(fEditWidth,));
		//m_pChatContent->setPosition(ccp(pType->getPositionX()+pType->getContentSize().width, fOffsetY-m_pChatContent->getContentSize().height-15));

		m_pChatContent->getTTF()->setPosition(ccp(5,10));
		m_pChatContent->getTTF()->setFontSize(40);
		m_pChatContent->getTTF()->setString("");
		m_pChatContent->getTTF()->setScissorSize(CCSize(pEditBG->getContentSize().width-10, pEditBG->getContentSize().height));
		m_pChatContent->getTTF()->setColor(ccc3(0,0,0));
		m_pChatContent->InitCursor(0xFF,1,40);
		pEditBG->addChild(m_pChatContent);
		SIX_Utility::GetInstance()->FixedTexParameters(m_pChatContent->getTTF()->getTexture());
	}
	// 默认聊天内容
	CCRect listViewRect = CCRect(10, 10, m_pSendPanel->getContentSize().width, pEditBG->getPositionY()-5);
	CCSize listViewCell = CCSize(m_pSendPanel->getContentSize().width,55);
	SIX_ListView *pDefaultChatContent = 0;
	createListView(pDefaultChatContent, (int)DEFAULT_CHAT_LIST_VIEW_ID, listViewRect, listViewCell);
	addChild(pDefaultChatContent);
	setDefaultChatContentToListView();
}

void SIX_PopWndMessage::setReceiveMsgToListView(bool bInsertAllData)
{
	while (0 < m_deChatContent.size())
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		m_pInformationListView->AppendCell(pCell);

		CCSprite *pChatType= CCSprite::create("Chat_Sign.png");
		if (0 == pChatType)
		{
			CCAssert(0, "SIX_PopWndMessage::setReceiveMsgToListView    Create Failed !");
			continue;
		}
		pChatType->ignoreAnchorPointForPosition(true);
		pChatType->setPosition(ccp(5, (m_pInformationListView->cellSizeForTable(0).height-pChatType->getContentSize().height)/2));
		pCell->addChild(pChatType);

		CMD_ChatContent * pChat = m_deChatContent.front();
		CCString *pStrMoney = CCString::createWithFormat("%s：%s",pChat->szSpeakNickName, pChat->szCentent);
		CCLabelTTF *pInformation = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(pStrMoney->getCString()).c_str(),"微软雅黑",18, \
			m_pInformationListView->cellSizeForTable(0),kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		if (0 != pInformation)
		{
			pInformation->setColor(pChat->lSpeakUserId==SIX_PlayerMgr::GetInstance()->getMyUserIdx() ? ccc3(128,128,128) : ccc3(255,255,255));
			pInformation->ignoreAnchorPointForPosition(true);
			pInformation->setPosition(ccp(pChatType->getContentSize().width+15, (m_pInformationListView->cellSizeForTable(0).height-pInformation->getContentSize().height)/2));
			SIX_Utility::GetInstance()->FixedTexParameters(pInformation->getTexture(),true);
			pCell->addChild(pInformation);
		}
		
		m_pInformationListView->refresh();
		CC_SAFE_DELETE(pChat);
		m_deChatContent.pop_front();

		if ( !bInsertAllData )
			break;
	}
}

void SIX_PopWndMessage::setDefaultChatContentToListView()
{
	SIX_ListView *pDefaultChatContent = dynamic_cast<SIX_ListView *>(getChildByTag(DEFAULT_CHAT_LIST_VIEW_ID));
	if (0==pDefaultChatContent)
		return;

	int iContentCount = sizeof(C_szContent)/sizeof(C_szContent[0]);
	SIX_ListViewCell *pCell = 0;
	for (int i=0; i<iContentCount/2; ++i)
	{
		pCell = new SIX_ListViewCell();
		pDefaultChatContent->AppendCell(pCell);
		if (0==pCell)
			continue;

		float fInterval = 5; // 间隔
		float fFastChatWidth = (pDefaultChatContent->cellSizeForTable(0).width-fInterval*3)/2;
		for (int j=0; j<2; ++j)
		{
			CCControlButton *pFastChatBT = SIX_Utility::GetInstance()->CreateButtonWithFile("chat_fastChat.png", CCRect(0,0,381,53));
			if ( pFastChatBT )
			{
				//pFastChatBT->ignoreAnchorPointForPosition(true);
				//pFastChatBT->setPreferredSize(CCSize(fFastChatWidth, 44));
				//pFastChatBT->setPosition(ccp(fInterval, (pDefaultChatContent->cellSizeForTable(0).height-pFastChatBT->getContentSize().height)/2));
				//pCell->addChild(pFastChatBT);

				pFastChatBT->ignoreAnchorPointForPosition(true);
				pFastChatBT->setPosition(ccp(fInterval, (pDefaultChatContent->cellSizeForTable(0).height-pFastChatBT->getContentSize().height)/2-5));
				pFastChatBT->setZoomOnTouchDown(false);
				pFastChatBT->setDefaultTouchPriority(m_nPriority-1);
				pFastChatBT->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndMessage::doEvents),32);
				pFastChatBT->setTag(DEFAULT_CHAT_BTN_START+i*2+j);
				pCell->addChild(pFastChatBT);
				fInterval = fInterval+pFastChatBT->getPositionX()+pFastChatBT->getContentSize().width;

				CCLabelTTF *pFastContent = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(C_szContent[i*2+j]).c_str(),"微软雅黑",20, \
					pFastChatBT->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
				if (0 != pFastContent)
				{
					pFastContent->setColor(ccc3(255,255,255));
					pFastContent->setOpacity(255);
					pFastContent->ignoreAnchorPointForPosition(true);
					SIX_Utility::GetInstance()->FixedTexParameters(pFastContent->getTexture(),true);
					pFastChatBT->addChild(pFastContent);
				}
			}
		}
	}
}

bool SIX_PopWndMessage::getNextMsg()
{
	if (MIN_SHOW_RECEIVE_PANEL == m_PannelShowStyle)
	{
		if (0 >= m_deChatContent.size())
		{
			m_bIsHaveShow = false;
			return false;
		}

		CMD_ChatContent *pChatContent = m_deChatContent.front();
		m_InformationDelegate->OnShowInformation(pChatContent);
		setReceiveMsgToListView(false);
	}
	else
	{
		return false;
	}
	return true;
}
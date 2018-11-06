#include "SIX_MatchList.h"

enum CONTROL_ID
{
	LABELTTF_WAIT_PROMPT,				// 等待提示内容
	BUTTON_CANCEL_QUEUE,				// 取消排队
	CELL_NODE,										// 结点
	BUTTON_SIGN_UP,							// 报名
};

SIX_MatchList::SIX_MatchList()
{
	m_iGateIdx = m_iGateIdxLast = 0;
	m_iRoomIdx = m_iRoomIdxLast = 0;
	m_RoomPeopleCount = m_Tables = m_SeatNum = 0;
	m_bLoginRoomSuccess = 0;
}

SIX_MatchList::~SIX_MatchList()
{
	unschedule(schedule_selector(SIX_MatchList::UpdateWaitPoint));
}

SIX_MatchList *SIX_MatchList::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_MatchList *pPopWnd = new SIX_MatchList();
	if (pPopWnd && pPopWnd->init())
	{
		pPopWnd->initWithColor(color,width,height);
		pPopWnd->setPosition(x,y);
		pPopWnd->setRedrawBorder(false);
		pPopWnd->m_ForbiddenTouch = true;
		pPopWnd->m_bCloseThenCleanup = false;
		pPopWnd->setShakeOffset(shakeOffset);
		pPopWnd->setShowType(showType);
		pPopWnd->setHideType(hideType);
		pPopWnd->setSeqExec(bSeqExec);
		pPopWnd->setObjName("SIX_SceneRoom");
	}
	return pPopWnd;
}

bool SIX_MatchList::init()
{
	if (!SIX_PopWnd::init())
		return false;
	pTitle = 0;
	pListRoom = 0;
	m_pWaitQueue = 0;
	//pListTable = 0;
	m_bInited = false;
	return true;
}

void SIX_MatchList::onEnter()
{
	CCLayerColor::onEnter();
	g_pShipMgr = CShipMgr::GetInstance();
}

void SIX_MatchList::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();
	this->setInited(true);
	ShowListRoom();
	//ShowListTable();
	//RefreshRoomList();
}

void SIX_MatchList::setGateIdx(int idx)
{
	m_iGateIdxLast = m_iGateIdx;
	m_iGateIdx = idx;

	this->setInited(true);

	if (m_iGateIdxLast != m_iGateIdx) // 比赛房间
	{
		if (NULL != pBackground)
		{
			pBackground->removeAllChildrenWithCleanup(true);
			pBackground->removeFromParentAndCleanup(true);
			pBackground = NULL;
		}

		CCString *pPath = CCString::createWithFormat("Scene/Room/%s.png", (5 == idx) ? "matchlistBG" : "bg");
		backgroundWithFile(pPath->getCString());
		this->reorderChild(pBackground, pClose->getZOrder()-1);
	}

	//CCTexture2D *text2D = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("Scene/Room/%d.png",idx)->getCString());
	//if (!text2D)
	//	return;
	//CCSize newSize = text2D->getContentSizeInPixels();
	//if (!pTitle)
	//{
	//	pTitle = CCSprite::createWithTexture(text2D);
	//	if (!pTitle)
	//		return;
	//	pTitle->ignoreAnchorPointForPosition(true);
	//	pTitle->setPosition(ccp(335+30,375+55));
	//	if (this->pBackground)
	//		pBackground->addChild(pTitle);
	//	else
	//		this->addChild(pTitle);
	//}
	//else
	//{
	//	pTitle->setTexture(text2D);
	//}
	//pTitle->setTextureRect(CCRect(0,0,newSize.width,newSize.height));

	ShowListRoom();
	RefreshRoomList();
}

int SIX_MatchList::getGateIdx()
{
	return m_iGateIdx;
}

void SIX_MatchList::setRoomIdx(int idx)
{
	m_iRoomIdx = idx;
}

int SIX_MatchList::getRoomIdx()
{
	return m_iRoomIdx;
}

void SIX_MatchList::setInited(bool bInited)
{
	m_bInited = bInited;
}

bool SIX_MatchList::getInited()
{
	return m_bInited;
}

void SIX_MatchList::setLoginRoomSuccess(bool bLogin)
{
	m_bLoginRoomSuccess = bLogin;
}

bool SIX_MatchList::getLoginRoomSuccess() const
{
	return m_bLoginRoomSuccess;
}

void SIX_MatchList::ShowListRoom(bool isShow)
{
	if (!pListRoom)
	{
		float list_width = 843.0;
		float list_height = 398.0;
		float cell_width = 276.0;
		float cell_height = list_height;
		float offset_x = 15.0;
		float offset_y = 30.0;

		SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
		pContainer->setContentSize(CCSize(list_width,list_height));
		pContainer->setPosition(ccp(offset_x,offset_y));

		pListRoom = SIX_ListView::create(ccc4(0,0,0,0),
					ccp(offset_x,offset_y),
					CCSize(list_width,list_height),
					CCSize(cell_width,cell_height),
					kCCScrollViewDirectionHorizontal,
					pContainer,
					0
				);
		pListRoom->setObjName("ListRoom");
		if (this->pBackground)
			pBackground->addChild(pListRoom);
		else
			this->addChild(pListRoom);
	}

	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	for (int i=0; i<pListRoom->GetCellCount(); i++)
	{
		CCNode *pNode = dynamic_cast<CCNode *>(pListRoom->GetCell(i)->getChildren()->objectAtIndex(0));
		CCControlButton *pButton = dynamic_cast<CCControlButton *>(pNode->getChildren()->objectAtIndex(1));
		CCTouchDelegate *pDelegate = dynamic_cast<CCTouchDelegate*>(pButton);
		CCTouchHandler *pHandler = pDispatcher->findHandler(pDelegate);
		pButton->setEnabled( isShow );
		if (NULL != pHandler)
		{
			pHandler->setTouchEventPause( !isShow );
		}
	}

	pListRoom->setVisible(isShow);
}

void SIX_MatchList::ShowWaitQueue(bool isShow/*=true*/)
{
	m_strRoomPrompt = "正在为您连接房间中，请稍后";

	if (NULL == m_pWaitQueue)
	{
		m_pWaitQueue = CCNode::create();

		CCSprite *pBG = CCSprite::create("Scene/Room/matchlistWaitPlayer.png");
		pBG->setPosition(ccp(430,231));
		m_pWaitQueue->addChild(pBG);

		CCLabelTTF *pWaitPrompt = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(m_strRoomPrompt.c_str()).c_str(),"微软雅黑",26, \
			CCSize(600,60),kCCTextAlignmentLeft);
		pWaitPrompt->setTag(LABELTTF_WAIT_PROMPT);
		pWaitPrompt->ignoreAnchorPointForPosition(true);
		pWaitPrompt->setPosition(ccp(235,236));
		SIX_Utility::GetInstance()->FixedTexParameters(pWaitPrompt->getTexture());	
		m_pWaitQueue->addChild( pWaitPrompt );

		// 取消排队
		CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Room/MatchListReturn.png",4);
		if (!pBtn)
			return;
		pBtn->setTag(BUTTON_CANCEL_QUEUE);
		pBtn->setZoomOnTouchDown(false);
		pBtn->setDefaultTouchPriority(this->m_nPriority-1);
		pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pBtn->setPosition(ccp(325, 90));
		m_pWaitQueue->addChild(pBtn);
		this->schedule(schedule_selector(SIX_MatchList::UpdateWaitPoint), 0.4f);
		this->pauseSchedulerAndActions();
		addChild( m_pWaitQueue );
	}

	if ( isShow )
	{
		CCControlButton *pButton = dynamic_cast<CCControlButton *>(m_pWaitQueue->getChildren()->objectAtIndex(2));
		pButton->setUserData((void*)m_iRoomIdx);
		this->resumeSchedulerAndActions();
	}
	else
	{
		this->pauseSchedulerAndActions();
	}

	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	CCControlButton *pButton = dynamic_cast<CCControlButton *>(m_pWaitQueue->getChildren()->objectAtIndex(2));
	CCTouchDelegate *pDelegate = dynamic_cast<CCTouchDelegate*>(pButton);
	CCTouchHandler *pHandler = pDispatcher->findHandler(pDelegate);
	if (NULL != pHandler)
	{
		pHandler->setTouchEventPause( !isShow );
	}
	m_pWaitQueue->setVisible( isShow );
}

void SIX_MatchList::AutoSqueue()
{
	if ( IsShow() )
	{
		m_strRoomPrompt = "正在努力为您匹配对手，请稍后";
		SIX_ClientRoom::GetInstance()->send_data(MATCH_MAIN, MATCH_SUB_CS_ARRANGE_QUEUE);
	}
}

void SIX_MatchList::RefreshRoomList()
{
	if (!this->getInited() || m_iGateIdx==m_iGateIdxLast)
		return;

	if (!pListRoom)
		return;

	// clean all first!
	// Cool.Cat
	pListRoom->RemoveCellAll();
	//pListTable->RemoveCellAll();

	// 行宽
	float LineWidth = pListRoom->cellSizeForTable(pListRoom->getTableView()).width;
	// 行高
	float LineHeight = pListRoom->cellSizeForTable(pListRoom->getTableView()).height;

	int count = 0;
	int nMatchCount = 0;
	RANGE_ROOM range = SIX_RoomMgr::GetInstance()->getMap()->equal_range(m_iGateIdx);
	for (ITER_ROOM iter=range.first;iter!=range.second;iter++)
	{
		CMD_SC_RoomList *pRoomList = iter->second;

		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		pListRoom->AddCell(pCell,count);
		count++;

		CCNode *pNode = CCNode::create();
		pNode->setTag(CELL_NODE);
		pNode->setObjName("node");
		pCell->addChild(pNode);

		if (3 == pRoomList->iRoomType)
		{
			CCString *pStrPath = NULL;
			switch (++nMatchCount)
			{
			case 1: pStrPath = CCString::create("Scene/Room/PrimaryBattlefield.png"); break;
			case 2: pStrPath = CCString::create("Scene/Room/MiddleBattlefield.png"); break;
			case 3: pStrPath = CCString::create("Scene/Room/HighBattlefield.png"); break;
			default: CCAssert(1,0); break;
			}
			CCSprite *pSprite = CCSprite::create(pStrPath->getCString());
			pSprite->ignoreAnchorPointForPosition(true);
			pNode->addChild(pSprite);
		
			// 报名费
			SIX_NumberBatchNode * pRegistrationFree = SIX_NumberBatchNode::Create("Scene/Room/matchNumber.png");
			pRegistrationFree->setCellNum(10);
			pRegistrationFree->setPadding(-3);
			pRegistrationFree->setBitCount(7);
			pRegistrationFree->setCellAlignStyle(ALIGN_RIGHT);
			pRegistrationFree->setNumber(pRoomList->iEnterTradeGold);
			pRegistrationFree->setPosition(ccp(45,263));
			pSprite->addChild(pRegistrationFree);
			// 头名奖
			SIX_NumberBatchNode * pFirstPrize = SIX_NumberBatchNode::Create("Scene/Room/matchNumber.png");
			pFirstPrize->setCellNum(10);
			pFirstPrize->setPadding(-3);
			pFirstPrize->setBitCount(7);
			pFirstPrize->setCellAlignStyle(ALIGN_RIGHT);
			pFirstPrize->setNumber(pRoomList->iRewardGold1);
			pFirstPrize->setPosition(ccp(45,193));
			pSprite->addChild(pFirstPrize);
			// 参与者
			SIX_NumberBatchNode * pPartner = SIX_NumberBatchNode::Create("Scene/Room/matchNumber.png");
			pPartner->setCellNum(10);
			pPartner->setPadding(-3);
			pPartner->setBitCount(7);
			pPartner->setCellAlignStyle(ALIGN_RIGHT);
			pPartner->setNumber(0);
			pPartner->setPosition(ccp(45,118));
			pSprite->addChild(pPartner);

			// 报名进入按钮
			CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Room/mathlist_intoBTN.png",4);
			if (!pBtn)
				continue;
			pBtn->setTag(BUTTON_SIGN_UP);
			pBtn->setUserData((void*)pRoomList->iRoomId);
			pBtn->setZoomOnTouchDown(false);
			pBtn->setDefaultTouchPriority(this->m_nPriority-1);
			pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
			pBtn->setPosition(ccp(65, 40));
			pBtn->setObjName("BaoMing");
			pNode->addChild(pBtn);
		}
	}
}

void SIX_MatchList::UpdateWaitPoint(float dt)
{
	CCLabelTTF *pWaitPrompt = dynamic_cast<CCLabelTTF*>(m_pWaitQueue->getChildren()->objectAtIndex(1));
	if (NULL != pWaitPrompt)
	{
		static int nPointCount=0;
		nPointCount = (3 <= nPointCount) ? 0 : nPointCount+1;
		string strTmpContent = m_strRoomPrompt;
		for (int i=1; i<=nPointCount; i++)
		{
			strTmpContent.append(".");
		}
		pWaitPrompt->setString( SIX_Utility::GetInstance()->G2U( strTmpContent.c_str() ).c_str() );
	}
}

bool SIX_MatchList::OnBtn(CCObject* pObject,int tag)
{
	CCControlButton *pButton = dynamic_cast<CCControlButton*>(pObject);
	if (!pButton)
		return true;

	int roomIdx = (int)(pButton->getUserData());
	if (0 >= roomIdx)
		return true;

	switch ( tag )
	{
	case BUTTON_SIGN_UP:	// 报名按钮
		{
			// 房间列表
			CMD_SC_RoomList *pRoomItem = SIX_RoomMgr::GetInstance()->Get(roomIdx);
			if (pRoomItem)
			{
				// 复原所有房间按钮
				for (unsigned int i=0;i<pListRoom->GetCellCount();i++)
				{
					SIX_ListViewCell *pCell = pListRoom->GetCell(i);
					//CCNode *pNode = pCell->getChildByTag(0);
					//if (!pNode)
					//	continue;
					CCControlButton *pBtn = dynamic_cast<CCControlButton*>(pCell->getChildren()->objectAtIndex(0));
					if (!pBtn)
						continue;
					pBtn->setEnabled(true);
				}

				m_iRoomIdx = pRoomItem->iRoomId;
				// 禁用当前房间按钮
				pButton->setEnabled(false);

				string addr(SIX_Utility::GetInstance()->NTOA(pRoomItem->lRoomTeltComIp));
				SIXLog("addr[%s:%d]",addr.c_str(),pRoomItem->iRoomPort);

				// 清空座位列表
				//pListTable->RemoveCellAll();

				// 断开当前的房间连接
				SIX_ClientRoom::GetInstance()->Disconnect();

				ShowListRoom(false);
				ShowWaitQueue(true);
				setLoginRoomSuccess( false );
				// 登录房间
				SIX_ClientRoom::GetInstance()->Connect(addr.c_str(),pRoomItem->iRoomPort, false);
			}
			break;
		}
	case BUTTON_CANCEL_QUEUE:	// 取消排队
		{
			if ( getLoginRoomSuccess() )
			{
				SIX_ClientRoom::GetInstance()->send_data(MATCH_MAIN, MATCH_SUB_CS_CANCEL_ARRANGE_QUEUE);
				SIX_ClientRoom::GetInstance()->Disconnect();
			}

			ShowWaitQueue( false );
			ShowListRoom();

			//// 断开当前的房间连接
			//SIX_ClientRoom::GetInstance()->Disconnect();
			break;
		}
	}
	return true;

	//// 右侧座位
	//if (tag>0)
	//{
	//	CCString *pString = CCString::createWithFormat("%d",tag);
	//	string str(pString->getCString());
	//	// -- 座位索引
	//	int SeatIdx = atoi(str.substr(str.length()-1,1).c_str());
	//	// -- 座子索引
	//	int TableIdx = atoi(str.substr(str.length()-2,1).c_str());
	//	// -- 第几行
	//	int CellRow = atoi(str.substr(0,1).c_str()) - 1;
	//	//SIXLog("SeatTag[%d] => CellRow[%d].TableIdx[%d].SeatIdx[%d]",tag,CellRow,TableIdx,SeatIdx);

	//	SIX_ClientRoom::GetInstance()->sit_down(TableIdx,SeatIdx);
	//	return true;
	//}
	return true;
}

bool SIX_MatchList::OnClose()
{
	// 取消排队
	if ( getLoginRoomSuccess() )
	{
		SIX_ClientRoom::GetInstance()->send_data(MATCH_MAIN, MATCH_SUB_CS_CANCEL_ARRANGE_QUEUE);
		SIX_ClientRoom::GetInstance()->Disconnect();
	}

	ShowWaitQueue( false );
	ShowListRoom();

	return SIX_EffectPopWnd::OnClose();
}

void SIX_MatchList::OnTouchLogic(CCTouch *pTouch,int pEvent)
{
	// 如果触点在list区域内，拦截之~
	// Cool.Cat
	if (pListRoom && pListRoom->getLayer())
	{
		CCPoint pt = pListRoom->getParent()->convertTouchToNodeSpace(pTouch);
		CCRect rc = pListRoom->boundingBox();
		if (rc.containsPoint(pt))
			return;
	}
	//if (pListTable && pListTable->getLayer())
	//{
	//	CCPoint pt = pListTable->getParent()->convertTouchToNodeSpace(pTouch);
	//	CCRect rc = pListTable->boundingBox();
	//	if (rc.containsPoint(pt))
	//		return;
	//}
	SIX_EffectPopWnd::OnTouchLogic(pTouch,pEvent);
}
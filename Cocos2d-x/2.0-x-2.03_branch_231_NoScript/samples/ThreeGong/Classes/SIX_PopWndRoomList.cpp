#include "SIX_PopWndRoomList.h"
#include "SIX_RoomMgr.h"
#include "SIX_ClientRoom.h"
#include "SIX_PlayerMgr.h"
#include "SIX_RoomMgr.h"

enum NodeTag
{
	BUTTTON_TAG = 1,					// ��ť
	SELECT_ITEM_TAG,					// ѡ�����
	ITEM_TEXT,								// ������
	TABLE_LIST_TAG,						// �����б�
	FAST_GAME_BT,						// ������Ϸ
	LIST_VIEW_HEAD,						// �б�ͷ
	STINT_TEXT,								// ��������
	CUR_PEOPLE_BG,						// ��ǰ������������
	CUR_PEOPLE_PROGRESS_BG,	// ��ǰ������������
	CUR_PEOPLE_COUNT,				// ��ǰ��������	
};

SIX_PopWndRoomList::~SIX_PopWndRoomList(void)
{
}

SIX_PopWndRoomList *SIX_PopWndRoomList::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndRoomList *pPopWnd = new SIX_PopWndRoomList();
	SIX_PopWndHaveListView::Create(pPopWnd, ccp(x,y), color, CCSize(width,height), bRedrawBorder, bCloseThenCleanup);
	
	pPopWnd->SetListViewCellSize(CCSize(168,61));
	pPopWnd->SetListViewRect(CCRect(c_smallWndBorderX+3,c_smallWndBorderY,width-c_smallWndBorderX*2-5,61));
	pPopWnd->SetListViewDirection(kCCScrollViewDirectionHorizontal);
	pPopWnd->SetHaveScrollBar(false);
	//pPopWnd->setRectDirty();
	return pPopWnd;
}

bool SIX_PopWndRoomList::init()
{
	if (!SIX_PopWndHaveListView::init())
		return false;
	
	SetTitlePath("room_titleBG.png");
	return true;
}

void SIX_PopWndRoomList::onEnterTransitionDidFinish()
{
	SIX_PopWndHaveListView::onEnterTransitionDidFinish();
	
	CCScale9Sprite *pSmallWnd = dynamic_cast<CCScale9Sprite *>(getChildByTag(SMALL_BG));
	if (0 != GetListView()  &&  0 != pSmallWnd)
	{
		reorderChild(pSmallWnd, getZOrder()+100);
		reorderChild(GetListView(), getZOrder()+200);

		pSmallWnd->setPosition(ccp(c_smallWndBorderX, c_smallWndBorderY+55));
		pSmallWnd->setPreferredSize(CCSize(getContentSize().width-c_smallWndBorderX*2, getContentSize().height-c_titleHeight-c_smallWndBorderY-55));
	}

	CCControlButton * pFastGame = SIX_Utility::GetInstance()->CreateButtonWithFileCell("fastGameBT.png", 2);
	if (0 != pFastGame)
	{
		CCSize sizeButton = pFastGame->getContentSize();
		pFastGame->setTag(FAST_GAME_BT);
		pFastGame->setPosition(ccp(28,getContentSize().height-pFastGame->getContentSize().height-20));
		pFastGame->setZoomOnTouchDown(false);
		pFastGame->setDefaultTouchPriority(m_nPriority-1);
		pFastGame->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndRoomList::doEvents),32);
		addChild(pFastGame);
	}

	const int ciCount = 4;
	char cType[ciCount][32]={"���ֳ�","��Ӣ��","��ʦ��","����"};
	int iParentID[ciCount] = {1,2,3,4};	// ���ڵ㣬��ӦCMD_GameServer_Register�е�lParentId��
	for (int nIndex = 0; nIndex <ciCount; ++nIndex)
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		GetListView()->AppendCell(pCell);

		ITER_ROOM mRoom = SIX_RoomMgr::GetInstance()->getMap()->find(iParentID[nIndex]);
		if (SIX_RoomMgr::GetInstance()->getMap()->end() != mRoom)
			pCell->setTag(mRoom->second->lParentId);
		else
			pCell->setTag(-1);

		// ���
		CCSprite *pItemBG = CCSprite::create("room_ItemBG.png");
		if (0 != pItemBG && 0!=pItemBG)
		{
			pItemBG->ignoreAnchorPointForPosition(true);
			pCell->addChild(pItemBG);
		}
		// ѡ���ʶ
		CCSprite *pSelectItemMark = CCSprite::create("room_selectItemBG.png");
		if (0 != pSelectItemMark)
		{
			pSelectItemMark->setObjName("SelectItemBG");
			pSelectItemMark->setTag(SELECT_ITEM_TAG+nIndex*10);
			pSelectItemMark->ignoreAnchorPointForPosition(true);
			pSelectItemMark->setVisible(0==nIndex ? true : false);
			pCell->addChild(pSelectItemMark);
		}
		// ����
		CCLabelTTF *pDescription = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(cType[nIndex]).c_str(),"΢���ź�",22, \
			pItemBG->getContentSize(),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		if (0 != pDescription)
		{
			pDescription->setColor(ccc3(255,255,255));
			pDescription->setOpacity(255);
			pDescription->setTag(ITEM_TEXT+nIndex*10);
			pDescription->ignoreAnchorPointForPosition(true);
			SIX_Utility::GetInstance()->FixedTexParameters(pDescription->getTexture(),true);
			pCell->addChild(pDescription);
		}
	}
	GetListView()->refresh();

	InitTopList();

	// �б�ͷ
	if (0 != pSmallWnd)
	{
		CCScale9Sprite *pListViewHead = CCScale9Sprite::create("ListViewHeadBG.png");
		if (0 != pListViewHead)
		{
			pListViewHead->ignoreAnchorPointForPosition(true);
			pListViewHead->setPreferredSize(pSmallWnd->getContentSize());
			pListViewHead->setPosition(pSmallWnd->getPositionX(), pSmallWnd->getPositionY());
			pListViewHead->setTag(LIST_VIEW_HEAD);
			addChild(pListViewHead, getZOrder()+200);

			CCString *pStrStint = CCString::createWithFormat("���ƣ�%d ~ %d ����", 0, 0);
			CCLabelTTF *pStintTxt = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(pStrStint->getCString()).c_str(),"΢���ź�",18, \
				CCSize(pListViewHead->getContentSize().width,45),kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
			if (0 != pStintTxt)
			{
				pStintTxt->setTag(STINT_TEXT);
				pStintTxt->setColor(ccc3(255,255,255));
				pStintTxt->ignoreAnchorPointForPosition(true);
				pStintTxt->setPosition(ccp(20, pListViewHead->getContentSize().height-45));
				SIX_Utility::GetInstance()->FixedTexParameters(pStintTxt->getTexture(),true);
				pListViewHead->addChild(pStintTxt);
			}
			//const int nHeadCount = 3;
			//char cHeadName[nHeadCount][32] = {"����", "��ע", "��������"};
			//for (int i=0; i<nHeadCount; i++)
			//{
			//	float fOffsetX = pListViewHead->getPositionX()+pListViewHead->getContentSize().width*i/3;
			//	CCLabelTTF *pHeadTxT = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(cHeadName[i]).c_str(),"΢���ź�",18, \
			//		CCSize(pListViewHead->getContentSize().width/3,45),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
			//	if (0 != pHeadTxT)
			//	{
			//		pHeadTxT->setColor(ccc3(255,255,255));
			//		pHeadTxT->ignoreAnchorPointForPosition(true);
			//		pHeadTxT->setPosition(ccp(fOffsetX, pListViewHead->getContentSize().height-45));
			//		SIX_Utility::GetInstance()->FixedTexParameters(pHeadTxT->getTexture(),true);
			//		pListViewHead->addChild(pHeadTxT);
			//	}
			//	if (i != 0)
			//	{
			//		CCSprite *pSplitterBar = CCSprite::create("SplitterBar.jpg");
			//		if (0 != pSplitterBar)
			//		{
			//			pSplitterBar->ignoreAnchorPointForPosition(true);
			//			pSplitterBar->setPosition(ccp(fOffsetX-pSplitterBar->getContentSize().width/2, pListViewHead->getContentSize().height-pSplitterBar->getContentSize().height-5));
			//			pListViewHead->addChild(pSplitterBar);
			//		}
			//	}
			//}
		}
	}
}

void SIX_PopWndRoomList::setCellContent()
{
	if (0 == GetListView())
		return;

	SIX_ListView *pTableListView = dynamic_cast<SIX_ListView *>(getChildByTag(TABLE_LIST_TAG));
	if (0 == pTableListView)
		return;

	pTableListView->RemoveCellAll();
	if (-1 == SIX_RoomMgr::GetInstance()->GetCurRoomID())
		return;

	CMD_SC_RoomList *pRoom = SIX_RoomMgr::GetInstance()->GetCurRoom();
	if (0==pRoom)
		return;

	// ���÷�������
	CCScale9Sprite *pListViewHead = dynamic_cast<CCScale9Sprite *>(getChildByTag(LIST_VIEW_HEAD));
	if (0 != pListViewHead)
	{
		CCLabelTTF *pStintTxt = dynamic_cast<CCLabelTTF *>(pListViewHead->getChildByTag(STINT_TEXT));
		if (0 != pStintTxt)
		{
			CCString *pStintStr = CCString::createWithFormat("���ƣ�%d ~ %d ����", pRoom->iDoorsill, pRoom->iMaxDoorsill);
			pStintTxt->setString(SIX_Utility::GetInstance()->G2U(pStintStr->getCString()).c_str());
			SIX_Utility::GetInstance()->FixedTexParameters(pStintTxt->getTexture(),true);
		}
	}

	for (int nIndex = 0; nIndex<pRoom->iTables; ++nIndex)
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		pTableListView->AppendCell(pCell);
		pCell->setTag(nIndex);
		
		// ���
		CCScale9Sprite *pItemBG = CCScale9Sprite::create("room_ItemBG.jpg");
		if (0 != pItemBG)
		{
			pItemBG->ignoreAnchorPointForPosition(true);
			pItemBG->setPreferredSize(CCSize(pTableListView->getContentSize().width-13, pItemBG->getContentSize().height));
			pCell->addChild(pItemBG);
		}
		// ����
		CCString *pStrTable = CCString::createWithFormat("%d ��",nIndex+1);
		CCLabelTTF *pTable = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(pStrTable->getCString()).c_str(),"΢���ź�",18, \
			CCSize(pItemBG->getContentSize().width/3,pItemBG->getContentSize().height),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		if (0 != pTable)
		{
			pTable->setColor(ccc3(255,255,0));
			pTable->ignoreAnchorPointForPosition(true);
			SIX_Utility::GetInstance()->FixedTexParameters(pTable->getTexture(),true);
			pCell->addChild(pTable);
		}
		// ����
		int nCurCount = SIX_RoomMgr::GetInstance()->GetTablePlayerCount(nIndex);
		int nTotalCount = pRoom->iSeatNum;
		nTotalCount = max(1,nTotalCount);
		CCSprite *pNumberBG = CCSprite::create("peopleNumberBG.png");
		if (0 != pNumberBG && 0!=pItemBG)
		{
			pNumberBG->ignoreAnchorPointForPosition(true);
			int nOffesetX = (pItemBG->getContentSize().width/3-pNumberBG->getContentSize().width)/2+8;
			pNumberBG->setPosition(ccp(pItemBG->getContentSize().width*2/3+nOffesetX, (pItemBG->getContentSize().height-pNumberBG->getContentSize().height)/2));
			pNumberBG->setTag(CUR_PEOPLE_BG);
			pCell->addChild(pNumberBG);
		}
		CCSprite *pCurNumberBG= CCSprite::create("peopleNumberSchedule.png", CCRect(0,0,pNumberBG->getContentSize().width*nCurCount/nTotalCount, pNumberBG->getContentSize().height));
		if (0 != pCurNumberBG)
		{
			pCurNumberBG->ignoreAnchorPointForPosition(true);
			pCurNumberBG->setPosition(pNumberBG->getPosition());
			pCurNumberBG->setTag(CUR_PEOPLE_PROGRESS_BG);
			pCell->addChild(pCurNumberBG);
		}
		CCString *pStrMoney = CCString::createWithFormat("%d / %d ��",nCurCount, nTotalCount);
		CCLabelTTF *pNumberTxT = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(pStrMoney->getCString()).c_str(),"΢���ź�",18, \
			pNumberBG->getContentSize(),kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		if (0 != pNumberTxT)
		{
			pNumberTxT->setColor(ccc3(255,255,255));
			pNumberTxT->ignoreAnchorPointForPosition(true);
			pNumberTxT->setPosition(pNumberBG->getPosition());
			pNumberTxT->setTag(CUR_PEOPLE_COUNT);
			SIX_Utility::GetInstance()->FixedTexParameters(pNumberTxT->getTexture(),true);
			pCell->addChild(pNumberTxT);
		}
	}
	pTableListView->refresh();
}

void SIX_PopWndRoomList::onShowFinished()
{
	const CMD_SC_RoomList *pRoom = SIX_RoomMgr::GetInstance()->GetPlayerMaxRoom(SIX_PlayerMgr::GetInstance()->getMyChip());
	if (0 != pRoom  &&  0<GetListView()->GetCellCount())
	{
		SIX_ListViewCell *pListviewCell = GetListView()->GetCell(0);
		for (int i=0; i<GetListView()->GetCellCount(); ++i)
		{
			if (0 !=GetListView()->GetCell(i)  &&  pRoom->lParentId==GetListView()->GetCell(i)->getTag())
			{
				pListviewCell = GetListView()->GetCell(i);
				break;
			}
		}
		tableCellTouched(GetListView()->getTableView(), pListviewCell);
	}
	else
	{
		tableCellTouched(GetListView()->getTableView(), GetListView()->GetCell(0));
	}
}

bool SIX_PopWndRoomList::OnClose()
{
	if (-1 != SIX_RoomMgr::GetInstance()->GetCurRoomID())
	{
		if (SIX_ClientRoom::GetInstance()->getConnected())
			SIX_ClientRoom::GetInstance()->leave_room();
		SIX_ClientRoom::GetInstance()->Disconnect();
	}
	return true;
}

CCSize SIX_PopWndRoomList::cellSizeForTable(CCTableView *table)
{
	return CCSize(0,0); 
}

CCTableViewCell* SIX_PopWndRoomList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	return 0;
}

unsigned int SIX_PopWndRoomList::numberOfCellsInTableView(CCTableView *table)
{
	return 0;
}

void SIX_PopWndRoomList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	//SIXLog("tableCellTouched");
	if (0==STRCMP("PopWndList_TopList", table->getObjName()))// �����б��¼�
	{
		int nTalbeID = cell->getTag();
		CCAssert(0<=nTalbeID  &&  nTalbeID<SIX_RoomMgr::GetInstance()->GetTableCount(), "��Ч���ţ�");
		if (0<=nTalbeID  && nTalbeID<SIX_RoomMgr::GetInstance()->GetTableCount())
		{
			SIX_ClientRoom::GetInstance()->sit_down(nTalbeID, -1);	
		}
	}
	else if (0==STRCMP("PopWndList", table->getObjName()))	// ��Ϸ�����б��¼�
	{
		if (-1 != SIX_RoomMgr::GetInstance()->GetCurRoomID()  &&  SIX_RoomMgr::GetInstance()->GetCurRoomID() == (long long)cell->getTag())
			return;

		bool bIsRoomExist = false;
		long long llOldSelectRoom = SIX_RoomMgr::GetInstance()->GetCurRoomID();
		SIX_RoomMgr::GetInstance()->SetCurRoomID((long long)cell->getTag());
		MMAP_ROOM *pMap = SIX_RoomMgr::GetInstance()->getMap();
		MMAP_ROOM::const_iterator cmRoom = pMap->find(cell->getTag());
		if (-1 != cell->getTag()  &&  pMap->end() != cmRoom)
			bIsRoomExist = true;

		for (unsigned int i=0; i<GetListView()->GetCellCount(); ++i)
		{
			SIX_ListViewCell * pListVewCell = GetListView()->GetCell(i);
			CCSprite *pSelectItemMark = dynamic_cast<CCSprite *>(pListVewCell->getChildren()->objectAtIndex(1));
			CCLabelTTF *pSelectTxt = dynamic_cast<CCLabelTTF *>(pListVewCell->getChildren()->objectAtIndex(2));
			if (0 == pSelectItemMark  ||  0 == pSelectTxt)
				continue;

			if ( pListVewCell == cell )
			{
				pSelectItemMark->setVisible(true);
				pSelectItemMark->setOpacity(bIsRoomExist?255:50);
				pSelectTxt->setColor(bIsRoomExist ? ccc3(255,255,255) : ccc3(128,128,128));
			}
			else
			{
				pSelectItemMark->setVisible(false);
				pSelectItemMark->setOpacity(255);
				pSelectTxt->setColor(ccc3(255,255,255));
			}
		}
		SIX_ListView *pTableListView = dynamic_cast<SIX_ListView *>(getChildByTag(TABLE_LIST_TAG));
		if (0 != pTableListView)
			pTableListView->RemoveCellAll();
		if ((long long)cell->getTag() != llOldSelectRoom  &&  -1 != llOldSelectRoom)
		{
			if (SIX_ClientRoom::GetInstance()->getConnected())
				SIX_ClientRoom::GetInstance()->leave_room();
			SIX_ClientRoom::GetInstance()->Disconnect();
		}
		// ���÷�������
		CCScale9Sprite *pListViewHead = dynamic_cast<CCScale9Sprite *>(getChildByTag(LIST_VIEW_HEAD));
		if (0 != pListViewHead)
		{
			CCLabelTTF *pStintTxt = dynamic_cast<CCLabelTTF *>(pListViewHead->getChildByTag(STINT_TEXT));
			if (0 != pStintTxt)
			{
				CCString *pStintStr = CCString::createWithFormat("���ƣ�%d ~ %d ����", 0, 0);
				pStintTxt->setString(SIX_Utility::GetInstance()->G2U(pStintStr->getCString()).c_str());
				SIX_Utility::GetInstance()->FixedTexParameters(pStintTxt->getTexture(),true);
			}
		}

		// ��½����
		if (bIsRoomExist)
		{
			if ( !SIX_ClientRoom::GetInstance()->getLogicConnect() )
			{
				SetReceiveDataComplete(false);
				string addr(SIX_Utility::GetInstance()->NTOA(cmRoom->second->lRoomUnicomIp));
				SIX_ClientRoom::GetInstance()->Disconnect();
				SIX_ClientRoom::GetInstance()->Connect(addr.c_str(),cmRoom->second->iRoomPort,false,300,false);
			}
		}
		else
		{
			SetReceiveDataComplete();
		}
	}
}

void SIX_PopWndRoomList::scrollViewDidScroll(CCScrollView* view)
{}

void SIX_PopWndRoomList::scrollViewDidZoom(CCScrollView* view)
{}

void SIX_PopWndRoomList::SetTablePeopleNumber(int iTableID, int iCount)
{
	CCAssert(0<=iCount, "����������Ч��");
	if (0==this  ||  -1==SIX_RoomMgr::GetInstance()->GetCurRoomID() || 0>iCount)
		return;
	SIX_ListView *pTableListView = dynamic_cast<SIX_ListView *>(getChildByTag(TABLE_LIST_TAG));
	if (0 == pTableListView)
		return;

	for (int i=0; i<pTableListView->GetCellCount(); ++i)
	{
		SIX_ListViewCell *pListViewCell = pTableListView->GetCell(i);
		if (0 != pListViewCell  &&  iTableID==pListViewCell->getTag())
		{
			CCSprite *pNumberBG = dynamic_cast<CCSprite *>(pListViewCell->getChildByTag(CUR_PEOPLE_BG));
			CCSprite *pCurNumberBG = dynamic_cast<CCSprite *>(pListViewCell->getChildByTag(CUR_PEOPLE_PROGRESS_BG));
			CCLabelTTF *pNumberTxT = dynamic_cast<CCLabelTTF *>(pListViewCell->getChildByTag(CUR_PEOPLE_COUNT));
			if (0 != pNumberTxT && 0!=pCurNumberBG && 0!=pNumberBG)
			{
				CMD_SC_RoomList *pRoom = SIX_RoomMgr::GetInstance()->GetCurRoom();
				if (0 != pRoom)
				{
					CCString *pStrMoney = CCString::createWithFormat("%d / %d ��",iCount, pRoom->iSeatNum);
					pNumberTxT->setString(SIX_Utility::GetInstance()->G2U(pStrMoney->getCString()).c_str());
					pCurNumberBG->setTextureRect(CCRect(0,0,pNumberBG->getContentSize().width*iCount/pRoom->iSeatNum, pNumberBG->getContentSize().height));
				}
			}
		}
	}
}

void SIX_PopWndRoomList::doEvents(CCObject* pSender, CCControlEvent controlEvent)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (controlEvent)
	{
	case CCControlEventTouchUpInside:
		{
			switch (tag)
			{
			case FAST_GAME_BT:	// ������Ϸ
				{
					if (-1 == SIX_RoomMgr::GetInstance()->GetCurRoomID()  ||  !SIX_ClientRoom::GetInstance()->getConnected())
						return;
					SIX_ClientRoom::GetInstance()->sit_down(-1, -1);
					break;
				}
			default:
				SIXLog("SIX_SceneHall::doEvents δ֪��ť�¼�,  tag=%d", tag);
				break;
			}
		}
	}
	return;
}

void SIX_PopWndRoomList::InitTopList()
{
	CCScale9Sprite *pSmallWnd = dynamic_cast<CCScale9Sprite *>(getChildByTag(SMALL_BG));
	if (0 == pSmallWnd)
		return;

	CCRect listViewRect = CCRect(pSmallWnd->getPosition().x+7,pSmallWnd->getPosition().y+10,pSmallWnd->getContentSize().width,pSmallWnd->getContentSize().height-55);
	CCSize listViewCell = CCSize(pSmallWnd->getContentSize().width,73);

	SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
	pContainer->setContentSize(CCSize(listViewRect.size.width, listViewRect.size.height));
	pContainer->setPosition(ccp(listViewRect.getMinX(), listViewRect.getMinY()));

	//SIX_ScrollBar *pScrollBar = SIX_ScrollBar::create(
	//	"scrollbar.png",CCRect(0,51,17,17),CCSize(listViewRect.size.height-17*2,17),
	//	"scrollbar.png",CCRect(0,51,17,17),
	//	"scrollbar.png",CCRect(0,34,17,17),
	//	"scrollbar.png",CCRect(0,34,17,17),
	//	"scrollbar.png",CCRect(0,0,17,17),
	//	"scrollbar.png",CCRect(0,17,17,17),
	//	CCSize(17,17),
	//	false
	//	);
	//pScrollBar->setAnchorPoint(ccp(0,0));
	//pScrollBar->setMinimumValue(0);
	//pScrollBar->setMaximumValue(100);
	//pScrollBar->setValue(0);
	//pScrollBar->setDefaultTouchPriority(m_nPriority-1);

	SIX_ListView *pListView = SIX_ListView::create(ccc4(0,0,0,0),
		ccp(listViewRect.getMinX(),listViewRect.getMinY()),
		CCSize(listViewRect.size.width, listViewRect.size.height),
		CCSize(listViewCell.width, listViewCell.height),
		kCCScrollViewDirectionVertical,
		pContainer,
		NULL//pScrollBar
		);
	pListView->setTag(TABLE_LIST_TAG);

	// -- ������Ӧtouch�¼�(create��ʱ���Ѿ����ú��ˣ�����ֻ����ʾ����)
	pListView->setTouchEnabled(true);	
	// -- ���òü���������(create��ʱ��Ĭ������Ϊtrue������ֻ����ʾ����~)
	pListView->getTableView()->setClippingToBounds(true);
	// -- ���ú�������(create��ʱ���Ѿ����ú��ˣ�����ֻ����ʾ����~)
	pListView->getTableView()->setDirection(kCCScrollViewDirectionVertical);
	// -- �������϶��¹���(create��ʱ���Ѿ����ú��ˣ�����ֻ����ʾ����~)
	pListView->getTableView()->setVerticalFillOrder(kCCTableViewFillTopDown);
	// -- ���û���Ч��
	pListView->getTableView()->setBounceable(true);
	pListView->getTableView()->setDelegate(this);
	pListView->getTableView()->setObjName("PopWndList_TopList");
	addChild(pListView, pSmallWnd->getZOrder()-1);
}
#include "SIX_RoomList.h"

SIX_RoomList::SIX_RoomList()
{
	m_iGateIdx = m_iGateIdxLast = 0;
	m_iRoomIdx = m_iRoomIdxLast = 0;
	m_RoomPeopleCount = m_Tables = m_SeatNum = 0;
	m_bAutoSit = false;
}

SIX_RoomList::~SIX_RoomList()
{
}

SIX_RoomList *SIX_RoomList::Create(float x,float y,const ccColor4B& color, float width, float height,float shakeOffset,MOVABLE_TYPE showType,MOVABLE_TYPE hideType,bool bSeqExec)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_RoomList *pPopWnd = new SIX_RoomList();
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

bool SIX_RoomList::init()
{
	if (!SIX_PopWnd::init())
		return false;
	pTitle = 0;
	pListRoom = 0;
	pListTable = 0;
	pBtnUp = pBtnDown = 0;
	pBtnQuick = 0;
	pLabelQuick = 0;
	m_bInited = false;
	return true;
}

void SIX_RoomList::onEnter()
{
	CCLayerColor::onEnter();
	g_pShipMgr = CShipMgr::GetInstance();
}

void SIX_RoomList::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();
	this->setInited(true);
	ShowListRoom();
	ShowListTable();
	RefreshRoomList();
}

void SIX_RoomList::ShowTableLoading(bool isLoading)
{

}

void SIX_RoomList::RefreshTableList(int iRoomPeopleCount,int iTables,int iSeatNum)
{
	m_RoomPeopleCount = iRoomPeopleCount;
	m_Tables = iTables;
	m_SeatNum = iSeatNum;

	ShowListTable();

	// clean all first!
	// Cool.Cat
	pListTable->RemoveCellAll();
	MakeTableAll();
	// 刷新滚动条
	pListTable->refresh();
	// 默认重定向到顶部
	pListTable->getScrollbar()->setValue(0.0f);
}

void SIX_RoomList::MakeTableAll()
{
	int m_rowHaveTableCount = this->getTableColumn();
	int rowCount = (int)(m_Tables / m_rowHaveTableCount);
	int leftCount = m_Tables - m_rowHaveTableCount * rowCount;
	//SIXLog("rowCount = %d , leftCount = %d",rowCount,leftCount);
	MakeRowTable(1, rowCount, m_rowHaveTableCount);
	MakeRowTable(rowCount+1,rowCount+1,leftCount);
}

void SIX_RoomList::MakeRowTable(int rowStart,int rowCount,int tableCount)
{
	if (tableCount<=0 || rowStart<=0 || !pListTable)
		return;

	// 行宽
	float LineWidth = pListTable->getContentSize().width;
	// 行高
	float LineHeight = pListTable->cellSizeForTable(pListTable->getTableView()).height;
	// 桌位与边缘间隔高度
	float offset_seat_y = 10.0;
	// 桌子列数
	int tableColumn = this->getTableColumn();

	for (int row=rowStart;row<=rowCount;row++)
	{
		// -- 动态创建第row行ListViewCell
		int CellRow = row;
		int CellTag = CellRow * 100;
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		pCell->setObjName(CCString::createWithFormat("TableCell-%02d",CellRow)->getCString());
		pCell->setTag(CellTag);
		pListTable->AddCell(pCell,CellRow-1);
		//SIXLog("row[%d].Cell[%s].CellTag[%d]",row,pCell->getObjName(),CellTag);
		
		// -- 动态创建第i列桌子
		for (int i=1;i<=tableCount;i++)
		{
			// --local TableTag = CellTag + i
			int TableTag = CellTag + (row-1)*tableCount + i-1;
			CCNode *pNode = CCNode::create();
			pNode->setObjName(CCString::createWithFormat("Table-%02d",TableTag)->getCString());
			pNode->setTag(TableTag);
			pCell->addChild(pNode);
			//SIXLog("row[%d].table[%s].TableTag[%d]",row,pNode->getObjName(),TableTag);
			
			// -- 桌子背景
			CCSpriteFrame *pTable = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("table_none.png");
			if (!pTable)
				return;

			CCSize tableFrameContentSize = pTable->getOriginalSizeInPixels();
			//int spaceWidth = (LineWidth - tableCount * tableFrameContentSize.width)/(tableCount+1);
			int spaceWidth = (LineWidth - tableColumn * tableFrameContentSize.width)/(tableColumn+1);
			int TablePosX = i * spaceWidth + (i-1) * tableFrameContentSize.width;
			int TablePosY = (LineHeight - tableFrameContentSize.height)/2;
			
			CCScale9Sprite *pScale9Sprite = CCScale9Sprite::createWithSpriteFrame(pTable);
			pScale9Sprite->setAnchorPoint(ccp(0,0));
			pScale9Sprite->setPreferredSize(CCSize(tableFrameContentSize.width,tableFrameContentSize.height));
			pScale9Sprite->setPosition(ccp(TablePosX,TablePosY));
			pNode->addChild(pScale9Sprite);
			
			// -- 桌子座位
			for (int k=1;k<=4;k++)
			{
				CCSpriteFrame *pSeat = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("seat.png");
				if (!pSeat)
					return;

				int SeatTag = TableTag * 10 + k - 1;

				CCSize seatFrameContentSize = pSeat->getOriginalSizeInPixels();
				
				int SeatPosX=0;
				if (k==1 || k==3)
					SeatPosX = pScale9Sprite->getPositionX() + seatFrameContentSize.width/2;
				else if (k==2 || k==4)
					SeatPosX = pScale9Sprite->getPositionX() + tableFrameContentSize.width - seatFrameContentSize.width/2;
	
				int SeatPosY=0;
				if (k==1 || k==2)
					SeatPosY = LineHeight - offset_seat_y - seatFrameContentSize.height/2;
				else if (k==3 || k==4)
					SeatPosY = offset_seat_y + seatFrameContentSize.height/2;

				//SIXLog("row[%d].table[%d].seat[%d].SeatTag[%d].SeatPos[%d/%d]",row,i,(k-1),SeatTag,SeatPosX,SeatPosY);
				
				CCScale9Sprite *pScale9SpriteSeat = CCScale9Sprite::createWithSpriteFrame(pSeat);
				CCControlButton *pBtnSeat = CCControlButton::create(pScale9SpriteSeat);
				pBtnSeat->setTag(SeatTag);
				pBtnSeat->setPreferredSize(CCSize(seatFrameContentSize.width,seatFrameContentSize.height));
				pBtnSeat->setPosition(ccp(SeatPosX,SeatPosY));
				if (k==3 || k==4)
				{
					CCScale9Sprite *pBg = pBtnSeat->getBackgroundSprite();
					pBg->setRotation(180.0f);
					//pBtnSeat->setRotation(180.0);
				}
				pBtnSeat->setDefaultTouchPriority(this->m_nPriority-1);
				pBtnSeat->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_RoomList::doEvents),32);
				pNode->addChild(pBtnSeat);
			}
		}
	}
}

void SIX_RoomList::SwitchSitDownOrLeaveSeat(long long lUserId,int iTableNo,int iSeatNo,bool IsSitDown)
{
	//SIXLog("SIX_SceneRoom:SitDown.lUserId[%lld].iTableNo[%d].iSeatNo[%d]",lUserId,iTableNo,iSeatNo);

	// -- 根据桌子ID和座位ID定位查找UI控件
	CCControlButton *pSeat = FindControlFromData(iTableNo,iSeatNo);
	if (!pSeat)
	{
		//SIXLog("SitDown.FindControlFromData[%d][%d].Nil",iTableNo,iSeatNo);
		return;
	}
	
	// -- 切换座位按钮的背景九宫格图片
	CCSpriteFrame *pSprite = 0;
	if (IsSitDown)
	{
		pSprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("female.png");
	}
	else
	{
		pSprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("seat.png");
	}
	
	if (!pSprite)
		return;
	
	CCScale9Sprite *pBg = pSeat->getBackgroundSprite();
	// -- 换图片前要先设置alpha
	pBg->setColor(ccc3(255,255,255));
	pBg->setOpacity(255);
	pBg->setSpriteFrame(pSprite);
	if (iSeatNo==2 || iSeatNo==3)
	{
		if (IsSitDown)
			pBg->setRotation(360.0f);
		else
			pBg->setRotation(180.0f);
	}
	//if (IsSitDown)
	//	CCLuaLog("SitDown.Done");
	//else
	//	CCLuaLog("LeaveSeat.Done");
}

CCControlButton *SIX_RoomList::FindControlFromData(int iTableNo,int iSeatNo)
{
	if (!pListTable)
		return 0;

	// 桌子背景
	CCSpriteFrame *pTableFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("table_none.png");
	if (!pTableFrame)
		return 0;

	// 桌子尺寸
	CCSize tableFrameContentSize = pTableFrame->getOriginalSizeInPixels();

	// 桌子间隔
	int table_offset = 20;

	// 桌子列数
	int m_rowHaveTableCount = getTableColumn();
	
	int cellTag = (int)(iTableNo / m_rowHaveTableCount);
	int tableIdx = iTableNo - m_rowHaveTableCount * cellTag;
	//SIXLog("SIX_SceneRoom:SitDown.cellTag[%d].tableIdx[%d]",cellTag,tableIdx);
	
	// -- 查找对应的cell
	SIX_ListViewCell *pCell = pListTable->GetCell(cellTag);
	if (!pCell)
	{
		//SIXLog("行标[%d]不存在！",cellTag);
		return 0;
	}
	
	// -- 查找对应的table
	int tableTag = (cellTag+1)*100 + iTableNo;
	CCNode *pTable = pCell->getChildByTag(tableTag);
	if (!pTable)
	{
		//SIXLog("桌标[%d]不存在！",tableTag);
		return 0;
	}
	
	// -- 查找对应的seat
	int seatTag = tableTag * 10 + iSeatNo;
	CCControlButton *pSeat = dynamic_cast<CCControlButton*>(pTable->getChildByTag(seatTag));
	if (!pSeat)
	{
		//SIXLog("位号[%d]不存在！",seatTag);
		return 0;
	}

	return pSeat;
}

int SIX_RoomList::getTableColumn()
{
	// 桌子背景
	CCSpriteFrame *pTableFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("table_none.png");
	if (!pTableFrame)
		return 0;

	// 桌子尺寸
	CCSize tableFrameContentSize = pTableFrame->getOriginalSizeInPixels();

	// 桌子间隔
	int table_offset = 20;

	// 桌子列数
	return (int)(pListTable->getContentSize().width / (table_offset + tableFrameContentSize.width));
}

void SIX_RoomList::setAutoSit(bool isAutoSit)
{
	m_bAutoSit = isAutoSit;
}

bool SIX_RoomList::getAutoSit()
{
	return m_bAutoSit;
}

void SIX_RoomList::ShowQucikStart(bool bShow)
{
	if (!pLabelQuick)
	{
		pLabelQuick = CCLabelTTF::create();
		if (!pLabelQuick)
			return;
		pLabelQuick->ignoreAnchorPointForPosition(true);
		pLabelQuick->setPosition(ccp(250,350));
		pLabelQuick->setString(SIX_Utility::GetInstance()->G2U("防作弊房间，点击快速开始系统自动进行配桌").c_str());
		pLabelQuick->setFontName("微软雅黑");
		pLabelQuick->setFontSize(24);
		pLabelQuick->setColor(ccc3(255,255,255));
		pLabelQuick->setOpacity(255);
		SIX_Utility::GetInstance()->FixedTexParameters(pLabelQuick->getTexture());
		this->addChild(pLabelQuick);
	}
	pLabelQuick->setVisible(bShow);

	if (!pBtnQuick)
	{
		pBtnQuick = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Room/quick.png",4);
		if (!pBtnQuick)
		{
			SIXLog("QuickStart.Error!");
			return;
		}
		pBtnQuick->setPosition(350,250);
		pBtnQuick->setTag(-3);
		pBtnQuick->setDefaultTouchPriority(this->m_nPriority-1);
		pBtnQuick->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_RoomList::doEvents),32);
		this->addChild(pBtnQuick);
	}
	pBtnQuick->setVisible(bShow);
}

void SIX_RoomList::setGateIdx(int idx)
{
	m_iGateIdxLast = m_iGateIdx;
	m_iGateIdx = idx;

	this->setInited(true);

	CCTexture2D *text2D = CCTextureCache::sharedTextureCache()->addImage(CCString::createWithFormat("Scene/Room/%d.png",idx)->getCString());
	if (!text2D)
		return;

	CCSize newSize = text2D->getContentSizeInPixels();
	if (!pTitle)
	{
		pTitle = CCSprite::createWithTexture(text2D);
		if (!pTitle)
			return;
		pTitle->ignoreAnchorPointForPosition(true);
		pTitle->setPosition(ccp(220,540));
		if (this->pBackground)
			pBackground->addChild(pTitle);
		else
			this->addChild(pTitle);
	}
	else
	{
		pTitle->setTexture(text2D);
	}
	pTitle->setTextureRect(CCRect(0,0,newSize.width,newSize.height));

	RefreshRoomList();
}

int SIX_RoomList::getGateIdx()
{
	return m_iGateIdx;
}

void SIX_RoomList::setRoomIdx(int idx)
{
	m_iRoomIdx = idx;
}

int SIX_RoomList::getRoomIdx()
{
	return m_iRoomIdx;
}

void SIX_RoomList::setInited(bool bInited)
{
	m_bInited = bInited;
}

bool SIX_RoomList::getInited()
{
	return m_bInited;
}

void SIX_RoomList::ShowListRoom(bool isShow)
{
	if (!pListRoom)
	{
		float list_width = 155.0f;
		float list_height = 440.0f;
		float cell_height = 50.0f;
		float offset_x = 10.0f;
		float offset_y = 45.0f;
		SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
		pContainer->setContentSize(CCSize(list_width,list_height));
		pContainer->setPosition(ccp(offset_x,offset_y));

		pListRoom = SIX_ListView::create(ccc4(0,0,0,0),
					ccp(offset_x,offset_y),
					CCSize(list_width,list_height),
					CCSize(list_width,cell_height),
					kCCScrollViewDirectionVertical,
					pContainer,
					0
				);
		pListRoom->setObjName("ListRoom");
		if (this->pBackground)
			pBackground->addChild(pListRoom);
		else
			this->addChild(pListRoom);

		// 向上按钮
		pBtnUp = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Room/btnup.png",2);
		pBtnUp->setPosition(45,490);
		pBtnUp->setTag(-1);
		pBtnUp->setUserData(0);
		pBtnUp->setDefaultTouchPriority(this->m_nPriority-1);
		pBtnUp->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		this->addChild(pBtnUp);

		// 向下按钮
		pBtnDown = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Room/btndown.png",2);
		pBtnDown->setPosition(45,15);
		pBtnDown->setTag(-2);
		pBtnDown->setUserData(0);
		pBtnDown->setDefaultTouchPriority(this->m_nPriority-1);
		pBtnDown->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		this->addChild(pBtnDown);
	}
	pListRoom->setVisible(isShow);
}

void SIX_RoomList::ShowListTable(bool isShow)
{
	if (!pListTable)
	{
		float list_width = 688.0f;
		float list_height = 509.0f;
		float cell_height = 300.0f;
		float offset_x = 172.0f;
		float offset_y = 10.0f;

		SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
		pContainer->setContentSize(CCSize(list_width,list_height));
		pContainer->setPosition(ccp(offset_x,offset_y));

		//SIX_ScrollBar *pScrollBar = SIX_ScrollBar::create(
		//	"Scene/Room/scrollbar_bg.png",CCRect(0,0,list_height,21),CCSize(pContainer->getContentSize().height-20*2,21),
		//	"Scene/Room/scrollbar_bg.png",CCRect(0,0,list_height,21),
		//	"Scene/Room/scrollbar_thumb.png",CCRect(0,0,121,20),
		//	"Scene/Room/scrollbar_thumb.png",CCRect(0,0,121,20),
		//	"Scene/Room/scrollbar_up.png",CCRect(0,0,20,20),
		//	"Scene/Room/scrollbar_down.png",CCRect(0,60,20,20),
		//	CCSize(20,20),
		//	false
		//	);
		SIX_ScrollBar *pScrollBar = SIX_ScrollBar::create(
			"Scene/Room/scrollbar_bg.png",CCRect(0,0,492,27),CCSize(492,27),
			"Scene/Room/scrollbar_bg.png",CCRect(0,0,492,27),
			"Scene/Room/scrollbar_thumb.png",CCRect(0,0,105,27),
			"Scene/Room/scrollbar_thumb.png",CCRect(0,27,105,27),
			0,CCRectZero,
			0,CCRectZero,
			CCSizeZero,
			false
			);
		pScrollBar->setAnchorPoint(ccp(0,0));
		pScrollBar->setMinimumValue(0);
		pScrollBar->setMaximumValue(100);
		pScrollBar->setValue(0);
		pScrollBar->setDefaultTouchPriority(m_nPriority-1);
		pScrollBar->getSlider()->getThumbSprite()->ignoreAnchorPointForPosition(true);
		pScrollBar->getSlider()->getThumbSprite()->setPositionY(0.0f);

		pListTable = SIX_ListView::create(ccc4(0,0,0,0),
					ccp(offset_x,offset_y),
					CCSize(list_width,list_height),
					CCSize(list_width,cell_height),
					kCCScrollViewDirectionVertical,
					pContainer,
					pScrollBar
				);
		pListTable->setObjName("ListTable");
		//pListTable->getTableView()->setDirection(kCCScrollViewDirectionVertical);
		//pListTable->getTableView()->setVerticalFillOrder(kCCTableViewFillTopDown);
		//pListTable->getTableView()->setBounceable(true);
		//pListTable->getTableView()->setClippingToBounds(true);
		//pListTable->setTouchEnabled(true);
		if (this->pBackground)
			pBackground->addChild(pListTable);
		else
			this->addChild(pListTable);
	}
	pListTable->setVisible(isShow);
}

void SIX_RoomList::RefreshRoomList()
{
	if (!this->getInited() || m_iGateIdx==m_iGateIdxLast)
		return;

	if (!pListRoom || !pListTable)
		return;

	// clean all first!
	// Cool.Cat
	pListRoom->RemoveCellAll();
	pListTable->RemoveCellAll();

	// 行宽
	float LineWidth = pListRoom->getContentSize().width;
	// 行高
	float LineHeight = pListRoom->cellSizeForTable(pListRoom->getTableView()).height;

	int count = 0;
	RANGE_ROOM range = SIX_RoomMgr::GetInstance()->getMap()->equal_range(m_iGateIdx);
	for (ITER_ROOM iter=range.first;iter!=range.second;iter++)
	{
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		//pCell->setObjName(CCString::createWithFormat("RoomCell-%lld-%d",iter->first,iter->second->iRoomId)->getCString());
		//pCell->setUserData((void*)iter->second->iRoomId);
		pListRoom->AddCell(pCell,count);
		count++;

		CCNode *pNode = CCNode::create();
		pNode->setTag(0);
		pCell->addChild(pNode);

		CCControlButton *pBtn = SIX_Utility::GetInstance()->CreateButtonWithFileCell("Scene/Room/cell.png",3);
		if (!pBtn)
			continue;
		pBtn->setTag(0);
		pBtn->setUserData((void*)iter->second->iRoomId);
		pBtn->setZoomOnTouchDown(false);
		pBtn->setDefaultTouchPriority(this->m_nPriority-1);
		pBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWnd::doEvents),32);
		pNode->addChild(pBtn);

		CCLabelTTF *pText = CCLabelTTF::create(SIX_Utility::GetInstance()->G2U(iter->second->szRoomName).c_str(),"微软雅黑",16);
		pText->ignoreAnchorPointForPosition(true);
		pText->setPosition(ccp(15,18));
		SIX_Utility::GetInstance()->FixedTexParameters(pText->getTexture());
		pBtn->addChild(pText);

		if (iter->second->bAutoSit)
		{
			CCSprite *pSprite = CCSprite::create("Scene/Room/defense.png");
			pSprite->ignoreAnchorPointForPosition(true);
			//pSprite->setPosition(ccp(pBtn->getPreferredSize().width-pSprite->getContentSize().width-7.0f,(pBtn->getPreferredSize().height-pSprite->getContentSize().height)/2));
			pSprite->setPosition(ccp(1,5));
			pBtn->addChild(pSprite);
		}
	}
}

bool SIX_RoomList::OnBtn(CCObject* pObject,int tag)
{
	CCControlButton *pButton = dynamic_cast<CCControlButton*>(pObject);
	if (!pButton)
		return true;

	int roomIdx = (int)(pButton->getUserData());
	if (roomIdx>0 && tag==0)
	{
		// 左侧房间列表
		CMD_SC_RoomList *pRoomItem = SIX_RoomMgr::GetInstance()->Get(roomIdx);
		if (pRoomItem)
		{
			// 复原所有房间按钮
			for (unsigned int i=0;i<pListRoom->GetCellCount();i++)
			{
				SIX_ListViewCell *pCell = pListRoom->GetCell(i);
				CCNode *pNode = pCell->getChildByTag(0);
				if (!pNode)
					continue;
				CCControlButton *pBtn = dynamic_cast<CCControlButton*>(pNode->getChildren()->objectAtIndex(0));
				if (!pBtn)
					continue;
				pBtn->setEnabled(true);
			}

			m_iRoomIdx = pRoomItem->iRoomId;
			// 禁用当前房间按钮
			pButton->setEnabled(false);

			string addr(SIX_Utility::GetInstance()->NTOA(pRoomItem->lRoomTeltComIp));//lRoomTeltComIp = 1913260554->10.10.10.114
			SIXLog("addr[%s:%d]",addr.c_str(),pRoomItem->iRoomPort);

			// 隐藏快速开始按钮
			this->ShowQucikStart(false);

			// 清空座位列表
			pListTable->RemoveCellAll();

			// 断开当前的房间连接
			SIX_ClientRoom::GetInstance()->Disconnect();

			// 设置房间是否为自动入座
			this->setAutoSit(pRoomItem->bAutoSit);

			// add by Ivan_han 20140915
	        addr=SIX_GlobalMgr::GetInstance()->GetConfig()->ip;
			// 登录房间
			SIX_ClientRoom::GetInstance()->Connect(addr.c_str(),pRoomItem->iRoomPort);
		}
		return true;
	}

	if (roomIdx==0)
	{
		// 右侧座位
		if (tag>0)
		{
			CCString *pString = CCString::createWithFormat("%d",tag);
			string str(pString->getCString());
			// -- 座位索引
			int SeatIdx = atoi(str.substr(str.length()-1,1).c_str());
			// -- 座子索引
			int TableIdx = atoi(str.substr(str.length()-2,1).c_str());
			// -- 第几行
			int CellRow = atoi(str.substr(0,1).c_str()) - 1;
			//SIXLog("SeatTag[%d] => CellRow[%d].TableIdx[%d].SeatIdx[%d]",tag,CellRow,TableIdx,SeatIdx);

			SIX_ClientRoom::GetInstance()->sit_down(TableIdx,SeatIdx);
			return true;
		}
		// 向上阿牛
		else if (tag==-1)
		{
			//CCMessageBox("上",0);
		}
		// 向下阿牛
		else if (tag==-2)
		{
			//CCMessageBox("下",0);
		}
		// 快速开始
		else if (tag==-3)
		{
			SIX_ClientRoom::GetInstance()->sit_down(-1,-1);
		}
	}
	return true;
}

void SIX_RoomList::OnTouchLogic(CCTouch *pTouch,int pEvent)
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
	if (pListTable && pListTable->getLayer())
	{
		CCPoint pt = pListTable->getParent()->convertTouchToNodeSpace(pTouch);
		CCRect rc = pListTable->boundingBox();
		if (rc.containsPoint(pt))
			return;
	}
	SIX_EffectPopWnd::OnTouchLogic(pTouch,pEvent);
}
#include "SIX_SceneRoom.h"
#include "SIX_SceneGame.h"
#include "Ship.h"
#include <SIX_GlobalMgr.h>

extern SCENE_IDX LAST_SCENE_IDX;

extern SIX_SceneRoom *pSceneRoom;
extern SIX_SceneGame *pSceneGame;

SIX_SceneRoom::~SIX_SceneRoom()
{
	pSceneRoom = 0;
	SIXLog("~SIX_SceneRoom");
}

SIX_SceneRoom* SIX_SceneRoom::scene()
{
	SIX_SceneRoom *pScene = new SIX_SceneRoom();
	//SIX_UIScene *pScene = (SIX_UIScene*)CCLayerColor::create(ccc4(255,255,255,128));
	if (pScene && pScene->init())
	{
		pScene->m_Scene = CCScene::create();
		pScene->m_Scene->addChild(pScene);
		pScene->setObjName("SIX_SceneRoom");
		pScene->autorelease();
		SIXLog("SIX_SceneRoom[0x%08X].m_Scene[0x%08X].retainCount[%d]",pScene,pScene->m_Scene,pScene->m_Scene->retainCount());
		//CCTransitionScene *ptr = dynamic_cast<CCTransitionScene*>(pScene->GetScene());
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
    return pScene;
}

bool SIX_SceneRoom::init()
{
    if ( !CCLayerColor::init() )
    {
        return false;
    }

	this->InitUIMgr();
	this->initWithColor(ccc4(255,255,255,128));

	int retv = this->GetUIMgr()->LoadXMLFromFile("Room.xml");
	this->GetUIMgr()->ReleaseXML();
	SIXLog("SIX_SceneRoom.init.retv[%d]",retv);

	if (retv!=0)
		return false;

	m_rowHaveTableCount = 5;
	pConsole = 0;

	return true;
}

// default implements are used to call script callback if exist
void SIX_SceneRoom::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneRoom::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneRoom::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneRoom::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneRoom::ccWindowMSG(CCSet *pTouches, CCEvent *pEvent, int nType)
{
	if (nType==CCNCMOUSEMOVE)
		return;
	CCTouch *pTouch = (CCTouch *)pTouches->anyObject();
	CCPoint pos = pTouch->getLocation();
	CCPoint location = CCDirector::sharedDirector()->convertToGL(pos);
}

void SIX_SceneRoom::onEnter()
{
	CCLayerColor::onEnter();
	SIX_PopWnd::setPopWndCount(0);

	setTouchEnabled(true);
	setKeypadEnabled(true);
	//setAccelerometerEnabled(true);

	g_pShipMgr = CShipMgr::GetInstance();
}

void SIX_SceneRoom::onEnterTransitionDidFinish()
{
	CCLayerColor::onEnterTransitionDidFinish();

	SIX_GlobalMgr::GetInstance()->PlayNextBackgroundMusic();

#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(this);
#endif

	schedule(schedule_selector(SIX_SceneRoom::update), 0.01f);

	CCLayerColor *bg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	
	// -- 桌子背景容器
	pListView = dynamic_cast<SIX_ListView*>(bg->getChildByTag(1));
	if (!pListView)
	{
		CCMessageBox("WTF",0);
		return;
	}

	// 从关卡场景进来
	if (LAST_SCENE_IDX==SCENE_IDX_GATE)
	{
		char *addr = new char[16];
		int port = 0;
		char *name = new char[32];
		char *pass = "202cb962ac59075b964b07152d234b70";
		SIX_GlobalMgr::GetInstance()->GetConfigFile(addr,port);

		pClientRoom = SIX_ClientRoom::GetInstance();
		pClientRoom->RandomUser(name);
		pClientRoom->init(addr,port,name,pass);
		pClientRoom->start();
	}
	// 从捕鱼场景返回到桌子场景
	else if (LAST_SCENE_IDX==SCENE_IDX_GAME)
	{
		//-- 取桌子列表
		SIX_ClientRoom::GetInstance()->query_table_list();
		
		// -- 取玩家列表
		SIX_ClientRoom::GetInstance()->query_user_list();
		
		// -- 发送离座消息
		SIX_ClientRoom::GetInstance()->leave_seat();
	}
}

void SIX_SceneRoom::onExitTransitionDidStart()
{
	CCLayerColor::onExitTransitionDidStart();
}

void SIX_SceneRoom::onExit()
{
#ifdef WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setKeyBoardDelegate(0);
#endif
	CCLayerColor::onExit();
}

#ifdef WIN32
int SIX_SceneRoom::OnAccelerometerKeyHook( UINT message,WPARAM wParam,LPARAM lParam )
{
	//SIXLog("SceneRoom.OnAccelerometerKeyHook.MSG[%u].wParam[%u].lParam[%ul]",message,wParam,lParam);
	switch (message)
	{
	case WM_KEYUP:
		{
			switch (wParam)
			{
			case VK_RETURN:
				{
					if (pConsole)
						pConsole->DoEnter();
					break;
				}
			}
			break;
		}
	case WM_CHAR:
		{
			switch (wParam)
			{
			case VK_NUMPAD0:
				{
					ShowConsole();
					// hook
					return 1;
				}
			}
			break;
		}
	}
	return 0;
}

void SIX_SceneRoom::OnProcessCommand(const char *cmd)
{
	if (!pConsole)
		return;

	string cmdCon(SIX_Utility::GetInstance()->U2G(cmd).c_str());
	std::transform(cmdCon.begin(),cmdCon.end(),cmdCon.begin(),::tolower);

	pConsole->setContent(/*>%s*/XorStr<0x45,4,0xFDA42D40>("\x7B\x63\x34"+0xFDA42D40).s,cmdCon.c_str());

	if (cmdCon==/*version*/XorStr<0x28,8,0x72481B50>("\x5E\x4C\x58\x58\x45\x42\x40"+0x72481B50).s || 
		cmdCon==/*ver*/XorStr<0xBC,4,0x028FBFDA>("\xCA\xD8\xCC"+0x028FBFDA).s)
	{
		pConsole->setContent(/*---------------------------------------*/XorStr<0x40,40,0x7140E047>("\x6D\x6C\x6F\x6E\x69\x68\x6B\x6A\x65\x64\x67\x66\x61\x60\x63\x62\x7D\x7C\x7F\x7E\x79\x78\x7B\x7A\x75\x74\x77\x76\x71\x70\x73\x72\x4D\x4C\x4F\x4E\x49\x48\x4B"+0x7140E047).s);
		pConsole->setContent(/*版本：%d.%d.%d.%04d*/XorStr<0xBC,20,0x0A511B50>("\x0C\x5B\x0F\x01\x63\x7B\xE7\xA7\xEA\xE0\xA2\xE9\xED\xAD\xE4\xEE\xFC\xF9\xAA"+0x0A511B50).s,VER_MAIN,VER_CHILD,VER_STAGE,VER_BUILD);
		pConsole->setContent(/*---------------------------------------*/XorStr<0x40,40,0x7140E047>("\x6D\x6C\x6F\x6E\x69\x68\x6B\x6A\x65\x64\x67\x66\x61\x60\x63\x62\x7D\x7C\x7F\x7E\x79\x78\x7B\x7A\x75\x74\x77\x76\x71\x70\x73\x72\x4D\x4C\x4F\x4E\x49\x48\x4B"+0x7140E047).s);
	}
	else if (cmdCon==/*exit*/XorStr<0x29,5,0x39578028>("\x4C\x52\x42\x58"+0x39578028).s)
	{
		SIXLog("Sayonara!");
		SIX_ClientRoom::GetInstance()->stop();
	}
	// balabala
	// ...
	else
	{
		bool IsValid = false;
		MP *mp = new MP();
		int count = SIX_Utility::GetInstance()->Split(" ",(char *)(cmdCon.c_str()),mp);
		switch (count)
		{
		case 2:
			{
				const char *key = mp->at(0).c_str();
				if (!STRCMP(key,"dirty"))
				{
					int value = atoi(mp->at(1).c_str());
					this->getParent()->setRectDirty((value==0)?false:true);
					IsValid = true;
				}
				else if (!STRCMP(key,"bbox"))
				{
					int value = atoi(mp->at(1).c_str());
					this->getParent()->setBBoxDirty((value==0)?false:true);
					IsValid = true;
				}
				break;
			}
		}
#ifdef WIN32
		mp->swap(MP());
#endif
		mp->clear();
		CC_SAFE_DELETE(mp);
		if (!IsValid)
			pConsole->setContent(/*Unknown.Command!*/XorStr<0x4C,17,0x139B5D35>("\x19\x23\x25\x21\x3F\x26\x3C\x7D\x17\x3A\x3B\x3A\x39\x37\x3E\x7A"+0x139B5D35).s);
	}
}
#endif

void SIX_SceneRoom::ShowConsole()
{
	if (!pConsole)
	{
		pConsole = SIX_Console::Create(112.0,125.0,ccc4(0,0,0,128),800.0,400.0,true);
		pConsole->InitMask(ccc4(0,0,0,128));
	}
	pConsole->ShowConsole(this);
}

void SIX_SceneRoom::RefreshTableList(int iRoomPeopleCount,int iTables,int iSeatNum)
{
	m_RoomPeopleCount = iRoomPeopleCount;
	m_Tables = iTables;
	m_SeatNum = iSeatNum;

	ShowTable();
}

void SIX_SceneRoom::ShowTable(bool IsShow)
{
	pListView->setVisible(IsShow);	
	pListView->RemoveCellAll();

	MakeTableAll();
}

void SIX_SceneRoom::MakeTableAll()
{
	int rowCount = (int)(m_Tables / m_rowHaveTableCount);
	int leftCount = m_Tables - m_rowHaveTableCount * rowCount;
	//SIXLog("rowCount = %d , leftCount = %d",rowCount,leftCount);
	MakeRowTable(1, rowCount, m_rowHaveTableCount);
	MakeRowTable(rowCount+1,rowCount+1,leftCount);
}

void SIX_SceneRoom::MakeRowTable(int rowStart,int rowCount,int tableCount)
{
	if (tableCount<=0 || rowStart<=0 || !pListView)
		return;

	// 行宽
	float LineWidth = pListView->getContentSize().width;
	// 行高
	float LineHeight = pListView->cellSizeForTable(pListView->getContainer()).height;
	// 桌位与边缘间隔高度
	float offset_seat_y = 10.0;

	for (int row=rowStart;row<=rowCount;row++)
	{
		// -- 动态创建第row行ListViewCell
		int CellRow = row;
		int CellTag = CellRow * 100;
		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		pCell->setObjName(CCString::createWithFormat("TableCell-%02d",CellRow)->getCString());
		pCell->setTag(CellTag);
		pListView->AddCell(pCell,CellRow-1);
		//SIXLog("row[%d].Cell[%s].CellTag[%d]",row,pCell->getObjName(),CellTag);
		
		// -- 动态创建第i行桌子
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
			int spaceWidth = (LineWidth - tableCount * tableFrameContentSize.width)/(tableCount+1);
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
				CCSpriteFrame *pSeat = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("empty.png");
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
					pBtnSeat->setRotation(180.0);
				//GetUIMgr()->addControlEvents(32,pBtnSeat);
				pBtnSeat->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_SceneRoom::doEvents),32);
				pNode->addChild(pBtnSeat);
			}
		}
	}
}

void SIX_SceneRoom::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControlButton *pButton = (CCControlButton*)pSender;
	int tag = pButton->getTag();
	//SIXLog("SIX_SceneRoom.doEvents.pSender[0x%08X].event[%d].tag[%d].onCCControlEventTouchUpInside",pSender,event,tag);

	switch (event)
	{
	case CCControlEventTouchUpInside:
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
			break;
		}
	}
}

CCControlButton *SIX_SceneRoom::FindControlFromData(int iTableNo,int iSeatNo)
{
	if (!pListView)
		return 0;
	
	int cellTag = (int)(iTableNo / m_rowHaveTableCount);
	int tableIdx = iTableNo - m_rowHaveTableCount * cellTag;
	//SIXLog("SIX_SceneRoom:SitDown.cellTag[%d].tableIdx[%d]",cellTag,tableIdx);
	
	// -- 查找对应的cell
	SIX_ListViewCell *pCell = pListView->GetCell(cellTag);
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

void SIX_SceneRoom::SwitchSitDownOrLeaveSeat(long long lUserId,int iTableNo,int iSeatNo,bool IsSitDown)
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
		pSprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("female.png");
	else
		pSprite = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("empty.png");
	
	if (!pSprite)
		return;
	
	CCScale9Sprite *pBg = pSeat->getBackgroundSprite();
	// -- 换图片前要先设置alpha
	pBg->setOpacity(255);
	pBg->setSpriteFrame(pSprite);
	//if (IsSitDown)
	//	CCLuaLog("SitDown.Done");
	//else
	//	CCLuaLog("LeaveSeat.Done");
}

void SIX_SceneRoom::update(float dt)
{
	if (SIX_Proxy::GetInstance()->IsChangeScene())
	{
		if (!pListView)
		{
			//CCMessageBox("WTF.B",0);
			return;
		}

		pListView->setTouchEnabled(false);

		SIX_Proxy::GetInstance()->SetChangeScene(false);

		// 切换到游戏场景
		LAST_SCENE_IDX = SCENE_IDX_MIN;
		
		if (!pSceneGame)
		{
			pSceneGame = SIX_SceneGame::scene();
			if (!pSceneGame)
			{
				//CCMessageBox("创建场景失败！",0);
				return;
			}
		}
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2f,pSceneGame->GetScene(),ccc3(255, 255, 255)));
	}
}

void SIX_SceneRoom::ShowLoading(bool IsShow)
{
	CCLayerColor *bg = (CCLayerColor*)(this->getChildren()->objectAtIndex(0));
	if (!bg)
		return;

	CCLayerColor *pLayer = dynamic_cast<CCLayerColor*>(bg->getChildByTag(2));
	if (!pLayer)
		return;

	pLayer->setVisible(IsShow);
}
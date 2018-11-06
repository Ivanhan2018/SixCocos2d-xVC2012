#include "SIX_PopWndTask.h"
#include "SIX_ClientHall.h"
#include "SIX_PlayerMgr.h"
#include "SIX_RoomMgr.h"

SIX_PopWndTask::~SIX_PopWndTask(void)
{
}

SIX_PopWndTask *SIX_PopWndTask::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup/*=false*/)
{
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_PopWndTask *pPopWnd = new SIX_PopWndTask();
	SIX_PopWndHaveListView::Create(pPopWnd, ccp(x,y), color, CCSize(width,height), bRedrawBorder, bCloseThenCleanup);
	
	pPopWnd->SetListViewCellSize(CCSize(width-c_smallWndBorderX*2-10, 73));
	pPopWnd->SetListViewRect(CCRect(c_smallWndBorderX+7, c_smallWndBorderY+10, width-c_smallWndBorderX*2-10, height-c_titleHeight-c_smallWndBorderY));
	return pPopWnd;
}

bool SIX_PopWndTask::init()
{
	if (!SIX_PopWndHaveListView::init())
		return false;

	SetTitlePath("task_titleBG.png");
	return true;
}

void SIX_PopWndTask::setCellContent()
{
	if (0 == GetListView())
		return;

	GetListView()->RemoveCellAll();
	map<int, CMD_SC_TaskList>::iterator mTaskList = m_mapTaskList.begin();
	for (; mTaskList != m_mapTaskList.end(); ++mTaskList)
	{
		if (2 < mTaskList->second.nState)
		{
			CCAssert(0, "已领奖的任务不需要发到客户端");
			continue;
		}

		SIX_ListViewCell *pCell = new SIX_ListViewCell();
		GetListView()->AppendCell(pCell);
		CCSize cellSize = GetListView()->getContentSize();
		// 项背景
		CCSprite *pItemBG = CCSprite::create("ItemBG.jpg");
		if (0 != pItemBG)
		{
			pItemBG->ignoreAnchorPointForPosition(true);
			pItemBG->setPosition(ccp(0,0));
			pCell->addChild(pItemBG);
		}
		// 任务标识
		CCString *pstrMark = CCString::createWithFormat("mark_%d.png",mTaskList->second.nTypeID);
		CCSprite *pMark = CCSprite::create(pstrMark->getCString());
		if (0==pMark)
		{
			pMark = CCSprite::create("mark_0.png");
		}
		if (0 != pMark)
		{
			pMark->ignoreAnchorPointForPosition(true);
			pMark->setPosition(ccp(5,(pItemBG->getContentSize().height-pMark->getContentSize().height)/2));
			pCell->addChild(pMark);
		}
		// 任务描述
		CCLabelTTF *pDescription = CCLabelTTF::create();
		pDescription->setString(SIX_Utility::GetInstance()->G2U(mTaskList->second.szTaskDescription).c_str());
		pDescription->setColor(ccc3(52,179,232));
		pDescription->setFontSize(18.0f);
		pDescription->setFontName("微软雅黑");
		pDescription->setOpacity(255);
		pDescription->ignoreAnchorPointForPosition(true);
		pDescription->setPosition(ccp(70,32));
		SIX_Utility::GetInstance()->FixedTexParameters(pDescription->getTexture(),true);
		pCell->addChild(pDescription);
		// 任务奖励
		CCLabelTTF *pTextReward = CCLabelTTF::create();
		char cReward[128]="";
		sprintf(cReward, "奖励：%d筹码", mTaskList->second.nReward);
		pTextReward->setString(SIX_Utility::GetInstance()->G2U(cReward).c_str());
		pTextReward->setColor(ccc3(253,255,3));
		pTextReward->setFontSize(18.0f);
		pTextReward->setFontName("微软雅黑");
		pTextReward->setOpacity(255);
		pTextReward->ignoreAnchorPointForPosition(true);
		pTextReward->setPosition(ccp(70,8));
		SIX_Utility::GetInstance()->FixedTexParameters(pTextReward->getTexture(),true);
		pCell->addChild(pTextReward);
		// 进度
		CCLabelTTF *pSchedule = CCLabelTTF::create();
		CCString *pStrSchedule = CCString::createWithFormat("进度：%d / %d", mTaskList->second.nCurSchedule, mTaskList->second.nTotalSchedule);
		pSchedule->setString(SIX_Utility::GetInstance()->G2U(pStrSchedule->getCString()).c_str());
		pSchedule->setColor(ccc3(255,255,255));
		pSchedule->setFontSize(20.0f);
		pSchedule->setFontName("微软雅黑");
		pSchedule->ignoreAnchorPointForPosition(true);
		pSchedule->setPosition(ccp(pItemBG->getContentSize().width-280,(pItemBG->getContentSize().height-pSchedule->getContentSize().height)/2));
		SIX_Utility::GetInstance()->FixedTexParameters(pSchedule->getTexture(),true);
		pCell->addChild(pSchedule);

		if (1 >= mTaskList->second.nState)
		{
			// 任务进行中
			CCLabelTTF *pTextReward = CCLabelTTF::create();
			pTextReward->setString(SIX_Utility::GetInstance()->G2U("进行中").c_str());
			pTextReward->setColor(ccc3(52,181,147));
			pTextReward->setFontSize(18.0f);
			pTextReward->setFontName("微软雅黑");
			pTextReward->setOpacity(255);
			pTextReward->ignoreAnchorPointForPosition(true);
			pTextReward->setPosition(ccp(pItemBG->getContentSize().width-110,(pItemBG->getContentSize().height-pTextReward->getContentSize().height)/2));
			SIX_Utility::GetInstance()->FixedTexParameters(pTextReward->getTexture(),true);
			pCell->addChild(pTextReward);
		}
		else
		{
			// 领奖按钮
			CCControlButton * pRewardButton = SIX_Utility::GetInstance()->CreateButtonWithFileCell("ReceiveRewardBT.png", 2);
			if (0 == pRewardButton)
				return;
			pRewardButton->setTag(mTaskList->first);
			pRewardButton->setObjName("Setting");
			pRewardButton->setZoomOnTouchDown(false);
			pRewardButton->setDefaultTouchPriority(m_nPriority-1);
			pRewardButton->addTargetWithActionForControlEvents(this,cccontrol_selector(SIX_PopWndTask::doEvents),32);
			pRewardButton->setPosition(ccp(cellSize.width-pRewardButton->getContentSize().width-30,(pItemBG->getContentSize().height-pRewardButton->getContentSize().height)/2-3));
			pCell->addChild(pRewardButton);
		}
	}

	GetListView()->refresh();
}

void SIX_PopWndTask::doEvents(CCObject* pSender, CCControlEvent event)
{
	CCControl *pControl = (CCControl*)pSender;
	int tag = pControl->getTag();

	switch (event)
	{
	case CCControlEventTouchUpInside:
		{
			map<int, CMD_SC_TaskList>::const_iterator mTask = m_mapTaskList.find(tag);
			if (m_mapTaskList.end() != mTask)
			{
				CMD_CSG_TaskAward taskAward;
				taskAward.lUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
				taskAward.nTaskID = mTask->first;
				//SIX_ClientHall::GetInstance()->Connect(false);
				SIX_ClientHall::GetInstance()->SendData(MAIN_MSG_TASK, SUB_CSG_RECEIVE_REWARD, (BYTE *)&taskAward, sizeof(taskAward));
			}
			else
			{
				SIXLog("SIX_SceneHall::doEvents 未知按钮事件,  tag=%d", tag);
			}
		}
	}
	return;
}

void SIX_PopWndTask::SetData(CMD_SC_TaskList *& pTask)
{
	CMD_SC_TaskList task;
	memcpy(&task, pTask, sizeof(task));
	m_mapTaskList.insert(make_pair(task.nID, task));
}

void SIX_PopWndTask::SetNextData(CMD_SC_GET_NEXT_TASK *& pTask)
{
	map<int, CMD_SC_TaskList>::iterator mFind = m_mapTaskList.find(pTask->nLastTaskID);
	if (mFind != m_mapTaskList.end())
	{
		m_mapTaskList.insert(mFind, make_pair(pTask->NextTask.nID, pTask->NextTask));
		map<int, CMD_SC_TaskList>::iterator mFind = m_mapTaskList.find(pTask->nLastTaskID);
		if (mFind != m_mapTaskList.end())
		{
			m_mapTaskList.erase(mFind);
		}
		setCellContent();
	}
}

void SIX_PopWndTask::onShowFinished()
{
	SIX_PopWndHaveListView::onShowFinished();

	SetReceiveDataComplete(false);
	m_mapTaskList.clear();
	if (0 != GetListView())
		GetListView()->RemoveCellAll();

	CMD_CS_TaskList tasklist;
	tasklist.lUserID = SIX_PlayerMgr::GetInstance()->getMyUserIdx();
	tasklist.nGame = GAME_ID;
	//SIX_ClientHall::GetInstance()->Connect(false);
	SIX_ClientHall::GetInstance()->SendData(MAIN_MSG_TASK, SUB_CSG_TASK_LIST, (BYTE *)&tasklist, sizeof(tasklist));
}
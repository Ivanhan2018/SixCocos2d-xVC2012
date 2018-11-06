#include "GameTaskCommon.h"
#include "globalUnits/GlobalUnits.h"
#include "gui/TaskInfo.h"
#include "DDZRes.h"
#include "common/DBHandler.h"

int taskNum[3] = {50,100,500};
int coinNum[3] = {10000,20000,100000};
bool GameTaskCommon::init()
{
	bool ret=false;
	do 
	{
		CCLayer::init();

		DBHandler *handler = DBHandler::sharedDBHandler();
		sqlite3 *DB = handler->getDB();
		sqlite3_stmt *stmt;
		char sql[200]={0};
		sprintf(sql, "select * from UserInfo where dwUserID=%ld",EntityMgr::instance()->getDispatch()->m_dwUserID);
		int rv = sqlite3_prepare(DB, sql, 100, &stmt, NULL);
		rv = sqlite3_step(stmt);
		if(rv == SQLITE_ROW)
		{
			LONG lWinCount = sqlite3_column_int(stmt, 5);
			LONG lLostCount = sqlite3_column_int(stmt, 6);
			LONG lDrawCount = sqlite3_column_int(stmt, 7);
			LONG lFleeCount = sqlite3_column_int(stmt, 8);
			totalCount=lWinCount+lLostCount+lDrawCount+lFleeCount;
		}else
		{
			totalCount = 0;
		}
		sqlite3_finalize(stmt);

		CCSize size=CCDirector::sharedDirector()->getWinSize();
		m_taskBk=CCSprite::createWithSpriteFrameName(texture_name::s_task_k);
		m_taskBk->setAnchorPoint(ccp(0.5,0.5f));
		m_taskBk->setPosition(ccp(size.width*0.5,size.height*0.5));

		CCDictionary * strings = CCDictionary::createWithContentsOfFile("xml/strings.xml");
		const char* buff1=((CCString*)strings->objectForKey("font_task"))->getCString();					//任务
		CCLabelTTF* label=CCLabelTTF::create(buff1,"黑体",20);
		label->setColor(ccc3(173,118,0));
		label->setAnchorPoint(ccp(0.5f,1.0f));
		label->setPosition(ccp(m_taskBk->getContentSize().width*0.5,m_taskBk->getContentSize().height-30));
		m_taskBk->addChild(label);

		m_tableView =CCTableView::create(this,CCSizeMake(450,240));
		m_tableView->setPosition(ccp(50,30));
		m_tableView->setDirection(kCCScrollViewDirectionVertical);

		m_tableView->setDelegate(this);  
		m_tableView->setVerticalFillOrder(kCCTableViewFillTopDown);  
		m_tableView->reloadData();  
		m_tableView->setTouchEnabled(true);
		m_taskBk->addChild(m_tableView, 1);  
		this->addChild(m_taskBk);
		this->setPosition(ccp(this->getPositionX(),size.height*1.0));
		memset(m_taskBUff,0,sizeof(m_taskBUff));
		//setTouchMode(kCCTouchesOneByOne);
		//setTouchEnabled(true);
		m_isOut =true;
		ret =true;
	} while (0);
	return true;
}

bool GameTaskCommon::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pt =pTouch->getLocation();
	if (m_isOut==true)return false;
	if (!m_taskBk->boundingBox().containsPoint(pt))
	{
		runOutOrIn();
		return true;
	}
	return true;
}

void GameTaskCommon::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameTaskCommon::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameTaskCommon::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameTaskCommon::runOutOrIn(bool isVisible)
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	m_isOut=!m_isOut; 
	m_tableView->reloadData();
	this->stopAllActions();
	this->runAction(CCMoveTo::create(0.2f,m_isOut?ccp(this->getPositionX(),size.height*1.0):ccp(this->getPositionX(),size.height*0.00)));
}
void GameTaskCommon::onEnter()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min)(),true);
	CCLayer::onEnter();
}

void GameTaskCommon::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

cocos2d::CCSize GameTaskCommon::cellSizeForTable( CCTableView *table )
{
	return CCSizeMake(100,50);  
}

CCTableViewCell* GameTaskCommon::tableCellAtIndex( CCTableView *table, unsigned int idx )
{
	CCDictionary * strings = CCDictionary::createWithContentsOfFile("xml/strings.xml");
	CCString* strbuff=NULL;

	if (idx>=3)
	{
		strbuff=((CCString*)strings->objectForKey(CCString::createWithFormat("xyx_task%d",idx)->getCString()));	
	}
	else
	{
		const char* buff1=((CCString*)strings->objectForKey(CCString::createWithFormat("xyx_task%d",0)->getCString()))->getCString();							//完成
		const char* buff2=((CCString*)strings->objectForKey(CCString::createWithFormat("xyx_task%d",1)->getCString()))->getCString();							//局任务

		const char* buff3=((CCString*)strings->objectForKey(CCString::createWithFormat("task%d_jl",0)->getCString()))->getCString();								//奖励
		const char* buff4=((CCString*)strings->objectForKey(CCString::createWithFormat("task%d_jl",1)->getCString()))->getCString();								//金币

		int count=taskNum[idx];
		int num=totalCount;

		strbuff=CCString::createWithFormat("%d%s%d%s      %s%d%s  %d/%d",idx+1,buff1,taskNum[idx],buff2,
			buff3,coinNum[idx],buff4,num>count?count:num,count);

		//strbuff=CCString::createWithFormat("%d%s%d%s    %s%d%s  %d/%d",idx+1,buff1,TaskInfo::ShareTaskInfo()->m_nTaskConfig[idx*2],buff2,
		//	buff3,TaskInfo::ShareTaskInfo()->m_nTaskConfig[idx*2+1],buff4,num>count?count:num,count);

	}
	CCTableViewCell *pCell = table->dequeueCell();
	if (!pCell) {
		pCell = new CCTableViewCell();
		pCell->autorelease();
		CCSprite *pSprite = CCSprite::createWithSpriteFrameName(texture_name::s_task_d);
		pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(CCPointZero);
		pCell->addChild(pSprite);
		pCell->setTag(idx);

		CCLabelTTF *pLabel = CCLabelTTF::create(strbuff->getCString(), "黑体", 20.0);
		pLabel->setAnchorPoint(ccp(0.5,0.5));
		pLabel->setPosition(ccp(pSprite->getContentSize().width*0.5,pSprite->getContentSize().height*0.5));
		pLabel->setTag(123);
		pCell->addChild(pLabel);
		pLabel->setColor(ccc3(173,118,0));
	}
	else
	{
		CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(123);
		pLabel->setString(strbuff->getCString());
		pCell->setTag(idx);
	}

	return pCell; 
}

unsigned int GameTaskCommon::numberOfCellsInTableView( CCTableView *table )
{
	return 4;
}

void GameTaskCommon::tableCellTouched( CCTableView* table, CCTableViewCell* cell )
{
	CCLOG("tableCellTouched\n"); 
	// 	CCfaceAndVioce* _data = CCfaceAndVioce::create(msgToLogic_face);
	// 	_data->m_Type =2;
	// 	_data->m_KeyID = cell->getTag();
	// 	CCNotificationCenter::sharedNotificationCenter()->postNotification(MESSAGE_TOLOGIC,_data);
	// 	if (s_face) s_face->runOutOrIn();
}

char GameTaskCommon::m_taskBUff[1024];


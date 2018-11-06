#include "tableViewLayer.h"
#include "CCTouchSprite.h"
#include "common/CocosUnits.h"
#include "event/GBEventIDs.h"
USING_NS_CC;
USING_NS_CC_EXT;

CCScene* tableViewLayer::scene()
{
	CCScene* se = CCScene::create();

	tableViewLayer* layer = tableViewLayer::create();

	se->addChild(layer);
	return se;
}

tableViewLayer* tableViewLayer::tableViewLayerWith1()
{
	tableViewLayer* view = new tableViewLayer();
	if (view && view->init())
	{
		view->autorelease();
		return view;
	}
	return NULL;
}

bool tableViewLayer::init()
{
	bool isRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCTableView* pTableView = CCTableView::create(this, CCSizeMake(123 * 4 + 175, 114*2 + 20));
		pTableView->setDirection(kCCScrollViewDirectionHorizontal);
		//pTableView->setViewLine();
		//pTableView->setViewOffset(ccp(30,20));
		//pTableView->set
		pTableView->setPosition(ccp(95,winSize.height / 5));
		pTableView->setDelegate(this);
		addChild(pTableView);
		pTableView->reloadData();

		isRet = true;
	} while (0);
	return isRet;
}

void tableViewLayer::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	//table->insertCellAtIndex(cell->getIdx());

	CCTouchSprite *label = (CCTouchSprite*)cell->getChildByTag(123);
	CCLog("cell m_uID at index: %i", label->m_uID);
}

CCSize tableViewLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	//return CCSizeMake(table->getContentSize().width,114);
	return CCSizeMake(123,114);
}

CCTableViewCell* tableViewLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		const char * str = CCString::createWithFormat("tubiao%d.png",idx)->getCString();

		//传入哪行哪列 回调函数
		CCTouchSprite* sprite=CCTouchSprite::createWithSpriteFrame(spriteFrame(str), idx, 0, this, callfuncN_selector(tableViewLayer::spriteClickCallBack));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		sprite->m_uID = idx;
		cell->addChild(sprite);
		sprite->setTag(123);
		//CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
		//label->setPosition(CCPointZero);
		//label->setAnchorPoint(CCPointZero);
		//label->setTag(1234);
		//cell->addChild(label);
	}
	else
	{
		CCTouchSprite *sprite = (CCTouchSprite*)cell->getChildByTag(123);
		sprite->m_uID = idx;

		//CCLabelTTF *label1 = (CCLabelTTF*)cell->getChildByTag(1234);
		//label1->setString(string->getCString());

		//CCLog("m_uID = %s",string->getCString());
	}
	return cell;
}

void tableViewLayer::spriteClickCallBack(cocos2d::CCNode* pNode)
{
	CCTouchSprite* pTouchSprite = (CCTouchSprite*)pNode;
	bool ret = isVisible();
	if (!isVisible())
	{
		return;
	}
	//CCLog("this is my click row is %d cell is %d, isdouble %d", pTouchSprite->getRowIndex(), pTouchSprite->getCellIndex(), pTouchSprite->isDoubleClick);
	CCObject obj;
	obj.m_uID = pTouchSprite->m_uID;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_UI_ANS_CLICKTIPS,&obj);

	CCLog("pTouchSprite m_uID = %d",pTouchSprite->m_uID);
}

unsigned int tableViewLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return 8;
}

void tableViewLayer::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{

}

void tableViewLayer::scrollViewDidZoom(CCScrollView *view)
{

}
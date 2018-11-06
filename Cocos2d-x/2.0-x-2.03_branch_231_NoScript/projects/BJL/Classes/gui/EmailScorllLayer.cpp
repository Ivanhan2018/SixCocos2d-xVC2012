#include "EmailScorllLayer.h"
#include "common/CocosUnits.h"
#include "CusTomTableViewCell.h"
#include "EmailCell.h"

EmailScorllLayer::EmailScorllLayer(void)
{
}


EmailScorllLayer::~EmailScorllLayer(void)
{

}

EmailScorllLayer* EmailScorllLayer::EmailScorllLayerWith(int type,int num)
{
	EmailScorllLayer* view = new EmailScorllLayer();
	if(view && view->intEmailScorllLayerWith(type,num))
	{
		view->autorelease();
		return view;
	}
	CC_SAFE_DELETE(view);
	return NULL;
}

bool EmailScorllLayer::intEmailScorllLayerWith(int type,int num)
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_nType = type;
	m_nMessageNum = num;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCTableView* tableView = CCTableView::create(this, CCSizeMake(774, 355));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(0,0));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();

	return true;
}

void EmailScorllLayer::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	CCLog("%d",cell->getIdx());
}

CCSize EmailScorllLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return CCSizeMake(774,116);
}

CCTableViewCell* EmailScorllLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell)
	{
		cell = new CusTomTableViewCell();
		int nScorllType = 0;
		if(m_nType == 0)
		{
			nScorllType = nScorllType+idx;
		}
		else if(m_nType == 1)
		{
			nScorllType = nScorllType+idx + 10;
		}
		EmailCell *sprite = EmailCell::EmailCellWith(nScorllType);
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		sprite->setTag(1234+idx);
		cell->addChild(sprite);
	}
	else
	{
		int nScorllType = 0;
		if(m_nType == 0)
		{
			nScorllType = nScorllType+idx;
		}
		else if(m_nType == 1)
		{
			nScorllType = nScorllType+idx + 10;
		}
		EmailCell *sprite = (EmailCell*)cell->getChildByTag(1234+idx);
		sprite->setCellIdx(nScorllType);
	}


	return cell;

}

unsigned int EmailScorllLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return m_nMessageNum;
}
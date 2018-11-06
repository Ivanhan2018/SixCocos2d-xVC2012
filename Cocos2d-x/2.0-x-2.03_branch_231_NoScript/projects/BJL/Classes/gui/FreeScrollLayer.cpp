#include "FreeScrollLayer.h"
#include "common/CocosUnits.h"
#include "CusTomTableViewCell.h"
#include "FreeCell.h"
#include "entity/EntityMgr.h"

FreeScrollLayer::FreeScrollLayer(void)
{
	
}


FreeScrollLayer::~FreeScrollLayer(void)
{
	
}

FreeScrollLayer* FreeScrollLayer::FreeScrollLayerWith(int num,SDownloadGamePrize_Returnn* data)
{
	FreeScrollLayer* view = new FreeScrollLayer();
	if(view && view->intFreeScrollLayerWith(num,data))
	{
		view->autorelease();
		return view;
	}
	CC_SAFE_DELETE(view);
	return NULL;
}

bool FreeScrollLayer::intFreeScrollLayerWith(int num,SDownloadGamePrize_Returnn* data)
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_nMessageNum = num;
	m_Data = data;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	/**���û���������������Ĵ�С**/
	CCTableView* tableView = CCTableView::create(this, CCSizeMake(808.0f, 384.0f));
	/**�б������Ǻ���kCCScrollViewDirectionHorizontal������������kCCScrollViewDirectionVertical����**/
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(0,0));
	tableView->setDelegate(this);
	/**�б����ôӴ�С��ʾ**/
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
	return true;
}

void FreeScrollLayer::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{

	CCLog("%d",cell->getIdx());
}

/**����ͼƬ��ͼƬ֮��ļ��**/
CCSize FreeScrollLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return CCSizeMake(780.0f,93.0f);
}

CCTableViewCell* FreeScrollLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell)
	{
		cell = new CusTomTableViewCell();
		cell->autorelease();
		cell->setTag(idx);
	}
	else
	{
		cell->setTag(idx);
		cell->removeAllChildrenWithCleanup(true); 

		FreeCell *sprite = FreeCell::FreeCellWith(idx,m_Data->dwDownloadGameInfo >> idx & 1);
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		cell->addChild(sprite,1,1234);
		sprite->setCellIdx(idx,m_Data->dwDownloadGameInfo >> idx & 1);
	}


	return cell;

}

unsigned int FreeScrollLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return m_nMessageNum;
}

void FreeScrollLayer::onGetDownData(CCObject* obj)
{
	
}
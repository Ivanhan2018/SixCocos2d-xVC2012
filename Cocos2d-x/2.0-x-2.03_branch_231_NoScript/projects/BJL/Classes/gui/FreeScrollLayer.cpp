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
	/**设置滑动操作可视区域的大小**/
	CCTableView* tableView = CCTableView::create(this, CCSizeMake(808.0f, 384.0f));
	/**列表设置是横屏kCCScrollViewDirectionHorizontal滑动还是竖屏kCCScrollViewDirectionVertical滑动**/
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(0,0));
	tableView->setDelegate(this);
	/**列表设置从大到小显示**/
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
	return true;
}

void FreeScrollLayer::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{

	CCLog("%d",cell->getIdx());
}

/**设置图片与图片之间的间距**/
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
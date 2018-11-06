#include "ChoosePhotoScrollLayer.h"
#include "common/CocosUnits.h"
#include "CusTomTableViewCell.h"
#include "ChoosePhotoCell.h"

ChoosePhotoScrollLayer::ChoosePhotoScrollLayer(void)

{
}


ChoosePhotoScrollLayer::~ChoosePhotoScrollLayer(void)
{

}

ChoosePhotoScrollLayer* ChoosePhotoScrollLayer::PhotoScrollLayerWith(int type,int num)
{
	ChoosePhotoScrollLayer* view = new ChoosePhotoScrollLayer();
	if(view && view->intPhotoScrollLayerWith(type,num))
	{
		view->autorelease();
		return view;
	}
	CC_SAFE_DELETE(view);
	return NULL;
}

bool ChoosePhotoScrollLayer::intPhotoScrollLayerWith(int type,int num)
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_nType = type;
	m_nMessageNum = num;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	/**设置滑动操作可视区域的大小**/
	CCTableView* tableView = CCTableView::create(this, CCSizeMake(723.0f, 156.0f));
	tableView->setDirection(kCCScrollViewDirectionHorizontal);
	tableView->setPosition(ccp(0,0));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
	return true;
}

void ChoosePhotoScrollLayer::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	
	//CCLog("%d",cell->getIdx());
}

/**设置图片与图片之间的间距**/
CCSize ChoosePhotoScrollLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return CCSizeMake(185.0f,140.0f);
}

CCTableViewCell* ChoosePhotoScrollLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
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
			nScorllType = nScorllType+idx + 100;
		}
		ChoosePhotoCell *sprite = ChoosePhotoCell::PhotoCellWith(nScorllType);
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(ccp(0, 0));
		sprite->setTag(1234);
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
			nScorllType = nScorllType+idx + 100;
		}
		ChoosePhotoCell *sprite = (ChoosePhotoCell*)cell->getChildByTag(1234);
		sprite->setCellIdx(nScorllType);

	}


	return cell;

}

unsigned int ChoosePhotoScrollLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return m_nMessageNum;
}
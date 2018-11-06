#include "gui/FMGameItemLayer.h"
#include <math.h>
#define PI acos(-1)
bool GameItemLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	inFlag = false;
	_angle = 0.0;
	animationDuration = 0.3f;
	this->ignoreAnchorPointForPosition(false);
	_selectedItem = NULL;
	CCSize WinSize =CCDirector::sharedDirector()->getWinSize(); 
	this->setContentSize(CCSize(WinSize.width/3*2,WinSize.height/3*2));
	this->setAnchorPoint(ccp(0.5f, 0.5f));

	//CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
	setTouchEnabled(true);
	//this->setTouchEnabled(true);
	return true;

}
void GameItemLayer::addMenuItem(cocos2d::CCMenuItem *item)
{
	item->setPosition(ccp(this->getContentSize().width / 2,this->getContentSize().height / 2));
	this->addChild(item);
	_items.push_back(item);
	setUnitAngle(2 * PI / _items.size());
	reset();
	updatePositionWithAnimation();
	return;
}
void GameItemLayer::updatePosition()
{
	CCSize menuSize = getContentSize();
	float disY = menuSize.height / 8;
	float disX = menuSize.width / 3;
	for (int i = 0; i < _items.size(); i++)
	{
		float x = menuSize.width / 2 + disX*sin(i*_unitAngle+getAngle());
		float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
		_items.at(i)->setPosition(ccp(x, y));
		//_items.at(i)->setZOrder(-(int)y);
		//Opacity  129~255
		//_items.at(i)->setOpacity(192 + 63 * cos(i*_unitAngle + getAngle()));
		_items.at(i)->setScale(0.75 + 0.25*cos(i*_unitAngle + getAngle()));
	}
	return;
}
void GameItemLayer::updatePositionWithAnimation()
{
	//先停止所有可能存在的动作
	for (int i = 0; i < _items.size(); i++)
		_items.at(i)->stopAllActions();
	CCSize menuSize = getContentSize();
	float disY = menuSize.height / 8;
	float disX = menuSize.width / 3;
	for (int i = 0; i < _items.size(); i++)
	{
		float x = menuSize.width / 2 + disX*sin(i*_unitAngle + getAngle());
		float y = menuSize.height / 2 - disY*cos(i*_unitAngle + getAngle());
		CCMoveTo *moveTo = CCMoveTo::create(animationDuration, ccp(x, y));
		_items.at(i)->runAction(moveTo);
		//Opacity  129~255
		CCFadeTo *fadeTo =CCFadeTo::create(animationDuration, (192 + 63 * cos(i*_unitAngle + getAngle())));
		_items.at(i)->runAction(fadeTo);
		//缩放比例  0.5~1
		CCScaleTo *scaleTo = CCScaleTo::create(animationDuration, 0.75 + 0.25*cos(i*_unitAngle + getAngle()));
		_items.at(i)->runAction(scaleTo);
		//_items.at(i)->setZOrder(-(int)y);
	}
	scheduleOnce(schedule_selector(GameItemLayer::actionEndCallBack), animationDuration);
	return;
}
void GameItemLayer::reset()
{
	_angle = 0;
}
void GameItemLayer::setAngle(float angle)
{
	this->_angle = angle;
}
float GameItemLayer::getAngle()
{
	return _angle;
}
void GameItemLayer::setUnitAngle(float angle)
{
	_unitAngle = angle;
}
float GameItemLayer::getUnitAngle()
{
	return _unitAngle;
}

float GameItemLayer::disToAngle(float dis)
{
	float width = this->getContentSize().width / 2;
	return dis / width*getUnitAngle();
}

CCMenuItem * GameItemLayer::getCurrentItem()
{
	if (_items.size() == 0)
		return NULL;
	//这里实际加上了0.1getAngle(),用来防止精度丢失
	int  index = (int)((2 * PI - getAngle()) / getUnitAngle()+0.1*getUnitAngle());
	index %= _items.size();
	return _items.at(index);
}
bool GameItemLayer::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	inFlag = false;
	//先停止所有可能存在的动作
	for (int i = 0; i < _items.size(); i++)
		_items.at(i)->stopAllActions();
	if (_selectedItem)
		_selectedItem->unselected();
	CCPoint position = this->convertToNodeSpace(touch->getLocation());
	CCSize size = this->getContentSize();
	CCRect rect;
	if (_selectedItem){
		CCSize itemSize = _selectedItem->getContentSize();
		rect = CCRect(size.width/2-itemSize.width/2, size.height/2-itemSize.height/2, itemSize.width, itemSize.height);
		if (rect.containsPoint(position)){
			inFlag = true;
		}
	}
	rect = CCRect(0, 0, size.width, size.height);
	if (rect.containsPoint(position)){
		return true;
	}
	return false;
}
void GameItemLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	float xDelta = touch->getLocation().x - touch->getPreviousLocation().x;
	rectify(xDelta>0);
	if (disToAngle(fabs(xDelta))<getUnitAngle() / 6&&_selectedItem){
		if(inFlag == true){
			_selectedItem->activate();
		}
	}
	updatePositionWithAnimation();
	return;
}
void GameItemLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	float angle = disToAngle(touch->getDelta().x);
	setAngle(getAngle() + angle);
	updatePosition();
	return;
}

void GameItemLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();  
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority+1,true);
}
void GameItemLayer::rectify(bool forward){
	float angle = getAngle();
	while (angle<0)
		angle += PI * 2;
	while (angle>PI * 2)
		angle -= PI * 2;
	if(forward>0)
		angle = ((int)((angle + getUnitAngle() / 3*2) / getUnitAngle()))*getUnitAngle();
	else
		angle = ((int)((angle + getUnitAngle() / 3 ) / getUnitAngle()))*getUnitAngle();
	setAngle(angle);
}

void GameItemLayer::actionEndCallBack(float dx)
{
	_selectedItem = getCurrentItem();
	if(_selectedItem)
		_selectedItem->selected();
}

void GameItemLayer::setEnabled(bool flag)
{
	CCArray *children = this->getChildren();
	if(children->count() == 0)
	{
		return;
	}
	for(int i = 0 ; i < children->count() ; i++)
	{
		CCMenuItem *item = (CCMenuItem *)children->objectAtIndex(i);
		item->setEnabled(flag);
	}
}
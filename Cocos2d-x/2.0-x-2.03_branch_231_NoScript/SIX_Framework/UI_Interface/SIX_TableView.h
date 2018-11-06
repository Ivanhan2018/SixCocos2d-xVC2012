/***************************************************************
Name£ºSIX_TableView
Desc£ºSIX_TableView
Auth£ºCool.Cat@2013-10-26
***************************************************************
http://www.cnblogs.com/moodlxs/archive/2012/12/27/2836004.html
***************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h> 
#ifdef WIN32
#include <time.h>
#elif defined(__linux__) || defined (__APPLE__)
#include <sys/time.h> 
#endif

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_TableView:public CCTableView
{
public:
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	static SIX_TableView* create(CCTableViewDataSource* dataSource, CCSize size);
	static SIX_TableView* create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container);

protected:
	CCPoint m_beginPoint;
	CCPoint m_lastPoint;
	struct timeval m_beginTime;
	struct timeval m_endTime;
};
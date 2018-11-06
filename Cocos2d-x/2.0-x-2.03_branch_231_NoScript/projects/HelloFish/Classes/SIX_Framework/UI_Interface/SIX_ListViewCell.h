/***********************************************
Name£ºSIX_ListViewCell
Desc£ºSIX_ListViewCell
Auth£ºCool.Cat@2013-04-24
***********************************************/
#pragma once
#include <cocos2d.h>
#include <SIX_Typedef.h>
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class SIX_ListViewCell : public CCTableViewCell
{
public:
	SIX_ListViewCell();
	~SIX_ListViewCell();
	virtual void draw();
};
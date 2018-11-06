//
//  BaseLayer.cpp
//  Game
//
//  Created by ÂÞÃô on 13-6-19.
//
//

#include "BaseLayer.h"


BaseLayer::BaseLayer()
{
    
}
BaseLayer::~BaseLayer()
{
    //unschedule(schedule_selector(BaseLayer::dispatch));
}

bool BaseLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    //schedule(schedule_selector(BaseLayer::dispatch));
    return true;
}
void BaseLayer::dispatch(float dt)
{
     //EntityMgr::instance()->getDispatch()->onDispatch();
}
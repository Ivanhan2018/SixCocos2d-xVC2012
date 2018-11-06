//
//  BaseLayer.h
//  Game
//
//  Created by ÂÞÃô on 13-6-19.
//
//

#ifndef __Game__BaseLayer__
#define __Game__BaseLayer__
#include "cocos2d.h"
#include "entity/EntityMgr.h"
#include "globalUnits/GlobalUnits.h"
#include "event/GBEvent.h"
#include "common/CocosUnits.h"

USING_NS_CC;

class BaseLayer : public cocos2d::CCLayer , public BaseObject
{
public:
    BaseLayer();
    virtual ~BaseLayer();
    
    CREATE_FUNC(BaseLayer);
    
    virtual bool init();
    
    virtual void dispatch(float dt);
};
#endif /* defined(__Game__BaseLayer__) */

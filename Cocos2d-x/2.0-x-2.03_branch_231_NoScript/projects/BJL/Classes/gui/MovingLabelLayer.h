//
//  MatchError.h
//  Game
//
//  Created by ÂÞÃô on 13-7-10.
//
//

#ifndef __Game__MovingLabelLayer__
#define __Game__MovingLabelLayer__

#include "cocos2d.h"
#include "common/CocosUnits.h"

class MovingLabelLayer : public CCNode
{
public:
    static MovingLabelLayer * MovingLabelLayerWith(const char* str,CCPoint pos);
    bool initMovingLabelLayer(const char* str,CCPoint pos);
    MovingLabelLayer();
    ~MovingLabelLayer();
	void onActionDown(CCNode* obj);
};

#endif /* defined(__Game__MatchError__) */

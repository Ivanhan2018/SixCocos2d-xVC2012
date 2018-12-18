//
//  GameLayer.h
//  TrexPush
//
//  Created by Nelson Andre on 12-10-01.
//
//

#pragma once

#include "cocos2d.h"

#include "Box2DLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GameLayer : public Box2DLayer
{
public:
    static CCScene* scene();
	static CCScene* scene(int stage, int level);

	void initializeLayerWithLevelData(CCDictionary *dict);
    
    CREATE_FUNC(GameLayer);
};
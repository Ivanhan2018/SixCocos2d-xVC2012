//
//  StageSelectionLayer.h
//  TrexPush
//
//  Created by Nelson Andre on 12-10-01.
//
//

#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class StageSelectionLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void stageClickCallback(CCObject * pSender);
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(StageSelectionLayer);
};
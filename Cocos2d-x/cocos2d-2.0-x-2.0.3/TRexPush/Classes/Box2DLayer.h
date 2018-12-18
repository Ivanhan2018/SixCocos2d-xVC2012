//
//  Box2DLayer.h
//  TrexPush
//
//  Created by Nelson Andre on 12-10-01.
//
//

#pragma once

#include "Box2D/Box2D.h"
#include "cocos2d.h"

#include "GLES-Render.h"

#include <string>

using namespace cocos2d;

class Box2DLayer : public CCLayer
{
    GLESDebugDraw* m_debugDraw;
    
    b2World* world;

    
    
public: Box2DLayer();
    ~Box2DLayer();
    
    void initPhysics();
    void update(float dt);
    void addNewSpriteAtPosition(CCPoint p);
	void addNewObjectAtPosition(std::string key, CCPoint p);
    
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void draw();
    
};





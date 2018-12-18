//
//  PhysicsSprite.h
//  TrexPush
//
//  Created by Nelson Andre on 12-10-01.
//
//

#pragma once

#include "Box2D/Box2D.h"
#include "cocos2d.h"

using namespace cocos2d;

class PhysicsSprite : public CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};
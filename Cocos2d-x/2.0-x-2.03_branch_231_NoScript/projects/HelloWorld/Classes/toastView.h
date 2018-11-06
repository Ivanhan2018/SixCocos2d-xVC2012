//
//  toastView.h
//  XXDDZ
//
//  Created by Eldder on 14-1-23.
//
//

#ifndef __XXDDZ__toastView__
#define __XXDDZ__toastView__


#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class XYToast: public CCLayerColor
{
public:
    CCSize visibleSize;
    CCPoint origin;
    CCScale9Sprite* bg;
public:
    
    XYToast();
    ~XYToast();
    void removeSelf();
    virtual bool init();
    void initToast(string msg,float time);
    CREATE_FUNC(XYToast);
    void onExit();
    
};

#endif /* defined(__XXDDZ__toastView__) */

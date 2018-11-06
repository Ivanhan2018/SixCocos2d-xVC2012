//
//  httpRequestdata.h
//  XXDDZ
//
//  Created by Eldder on 14-1-16.
//
//

#ifndef __XXDDZ__httpRequestdata__
#define __XXDDZ__httpRequestdata__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
class httpRequestdata{
    
    
public:
    
    CCHttpRequest* sendHTTPData(string _method , string prama);
    
    
};
#endif /* defined(__XXDDZ__httpRequestdata__) */

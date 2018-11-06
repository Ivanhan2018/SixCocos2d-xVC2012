//
//  DDDNumberLable.h
//  XXDZPK
//
//  Created by XXY on 14-1-13.
//
//

#ifndef __XXDZPK__DDDNumberLable__
#define __XXDZPK__DDDNumberLable__

#include "cocos2d.h"

USING_NS_CC;

#define MAX_NUM_VALVE 10000
#define MIN_NUM_CUT_FLG 1000
#define MIN_NUM_FLAG  999999

#define MARK_WAN 10
#define MARK_YI 11
#define MARK_Dot 12


class DDDNumberLab : public CCNode{
    
public:
    static DDDNumberLab* create();
    
    void initNumber();
    
    void setNumber(long long number);
    
    CC_PROPERTY(float, m_NumberSize, NumberSize);
    
private:
    
    CC_PROPERTY(bool, m_Minus, Minus);
    
    CCSpriteBatchNode *m_SpriteBatchNode;
    
    CCSprite *m_NumArr[15];
    
    //六位数及以内
    void Number_Length_Less(long long num);
    
    //整数部分�?000�?999之间�?    
	void Number_Intget_Max(long long num, int Mark);
    
    //整数部分�?00�?99之间�?    
	int Number_Intget_Less(long long num);
    
    //小数部分
    void Number_Float_Less(long long num, int dotIdx, int Mark);
    
    void Number_For_TwoPart(int intgerPart, int floatPart, int Mark);
    
    //大于9999亿的不再直接显示
    void Number_Length_Over();
};

#endif /* defined(__XXDZPK__DDDNumberLable__) */

//
//  MatchError.h
//  Game
//
//  Created by ÂÞÃô on 13-7-10.
//
//

#ifndef __Game__RuningBar__
#define __Game__RuningBar__

#include "cocos2d.h"
#include "common/CocosUnits.h"

class RuningBar : public CCLayer
{
public:
    CREATE_FUNC(RuningBar);
    virtual bool init();
    RuningBar();
    ~RuningBar();
	virtual void visit();
	void reSertRunHolePosition(CCNode* node);
private:
	CCLabelTTF* labelRunHole;				//ÅÜÂíÌõ
};

#endif /* defined(__Game__MatchError__) */

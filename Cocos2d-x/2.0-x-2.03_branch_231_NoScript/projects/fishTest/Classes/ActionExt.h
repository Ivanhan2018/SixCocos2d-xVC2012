
#include "cocos2d.h"

using namespace cocos2d;

class CCMoveByRound : public CCActionInterval
{
public:
	bool initWithDuration(float duration, float r, float a, float b);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void update(float time);

public:
	static CCMoveByRound* actionWithDuration(float duration,float r, float a, float b);

protected:
	CCPoint m_startPosition;
	float a;
	float b;
	float t;
	float r;
};
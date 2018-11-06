
#ifndef __FISH_H__
#define __FISH_H__

#include <vector>
#include "CCSprite.h"
#include "CCPointExtension.h"

using namespace cocos2d;
using namespace std;

class Fish :public cocos2d::CCSprite
{
public:
	Fish(CCTexture2D *texture, CCRect recet, float speed);
	~Fish(void);
	bool restart(std::vector<CCPoint>  *pathPoints, float delayTime = 0);

private:
	void fishMoveEnd(CCNode* sender);
	void nextPathPoint(void);
	CCPoint getControlPoint(const CCPoint *p_last, const CCPoint *p_start, const CCPoint *p_end);

private:
	std::vector<CCPoint> path;
	int nowPathIndex;
	float speed;
};

#endif
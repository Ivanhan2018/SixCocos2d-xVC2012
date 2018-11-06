#include "Fish.h"
#include "CCActionInterval.h"
#include "CCActionInstant.h"
#include "PointHelper.h"
#include "Define.h"

Fish::Fish(CCTexture2D *texture, CCRect recet, float speed)
{
	initWithTexture(texture, recet);
	path = vector<CCPoint>();
	nowPathIndex = 0;
	this->speed = speed;
}

Fish::~Fish(void)
{
}

bool Fish::restart(vector<CCPoint>  *pathPoints, float delayTime)
{
	if(pathPoints == NULL)
	{
		return false;
	}

	if(pathPoints->size() < 3)
	{
		return false;
	}

	path.clear();

	for (vector<CCPoint>::iterator it = pathPoints->begin(); it != pathPoints->end(); it++)
	{
		path.push_back(*it);
	}

	nowPathIndex = 0;

	this->setPosition(path[0]);
	this->setRotation(PointAngle(ccpSub(path[0], path[1])));
	
	float time = (float)(ccpDistance(path[0], path[1])/speed);

	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(time, path[1]);

	CCFiniteTimeAction* actionFade = CCFadeIn::actionWithDuration(1);

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Fish::fishMoveEnd));

	if(delayTime > 0)
	{
		CCFiniteTimeAction* actionDelayTime = CCDelayTime::actionWithDuration(delayTime);

		this->runAction(actionDelayTime);

		this->runAction(actionFade);

		this->runAction(CCSequence::actions(actionDelayTime, actionMove, actionMoveDone, NULL) );
	}
	else
	{
		this->runAction(actionFade);

		this->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL) );
	}
	return true;
}

void Fish::fishMoveEnd(CCNode* sender)
{
	//Fish *f = (Fish *)sender;
	if(++nowPathIndex >= ((int)path.size() - 2))
	{
		//ÒÆ¶¯½áÊø
		return;
	}
	nextPathPoint();
}

void Fish::nextPathPoint(void)
{
	float angleTo = PointAngle(ccpSub(path[nowPathIndex + 1], path[nowPathIndex]));
	float angle = angleTo - getRotation();

	while(angle > 180)
	{
		angle -= 360;
	}
	while(angle < -180)
	{
		angle += 360;
	}

	float time = (float)(ccpDistance(path[nowPathIndex], path[nowPathIndex + 1]) / speed);

	CCFiniteTimeAction* actionRotate = CCRotateBy::actionWithDuration(time, angle);
	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(time, path[nowPathIndex + 1]);

	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Fish::fishMoveEnd));

	this->runAction( CCSequence::actions(CCSpawn::actions(actionMove, actionRotate, NULL), actionMoveDone, NULL) );
}

CCPoint Fish::getControlPoint(const CCPoint *p_last, const CCPoint *p_start, const CCPoint *p_end)
{
	float length = ccpDistance(*p_start, *p_end) * 0.45f;

	if (CCPoint::CCPointEqualToPoint(*p_start, *p_last) && CCPoint::CCPointEqualToPoint(*p_start, *p_end))
	{
		return *p_end;
	}

	if (CCPoint::CCPointEqualToPoint(*p_start, *p_end))
	{
		return *p_start;
	}

	CCPoint v;
	if(CCPoint::CCPointEqualToPoint(*p_last, *p_end))
	{
		v = ccpSub(*p_end, *p_start);
	}
	else
	{
		v = ccpSub(*p_end, *p_last);
	}

	float len = ccpLength(v);
	v.x /= len;
	v.y /= len;
	v.x *= length;
	v.y *= length;
	v.x += p_start->x;
	v.y += p_start->y;
	return v;
}

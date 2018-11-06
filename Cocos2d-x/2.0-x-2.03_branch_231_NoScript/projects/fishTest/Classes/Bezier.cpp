
#include "Bezier.h"
#include "math.h"
#include "CCPointExtension.h"

Bezier::Bezier(void)
{
	this->anchor1 = CCPoint();
	this->anchor2 = ccp(0, 0);
	this->control1 = ccp(0, 0);
	this->control2 = ccp(0, 0);
	points = vector<CCPoint>();
	this->needUpdate = true;
	PointDistance = 0.6f;//设置点间距:越小游动越圆滑，但是越非资源
}

//参数1：锚点一，参数2：锚点二，参数3：控制点1，参数4：控制点2
Bezier::Bezier(CCPoint anchor1, CCPoint control1, CCPoint control2, CCPoint anchor2)
{
	this->anchor1 = anchor1;
	this->anchor2 = anchor2;
	this->control1 = control1;
	this->control2 = control2;
	points = vector<CCPoint>();
	this->needUpdate = true;
	PointDistance = 0.6f;//设置点间距:越小游动越圆滑，但是越非资源
}

Bezier::~Bezier(void)
{
}

void Bezier::Reset(CCPoint anchor1, CCPoint control1, CCPoint control2, CCPoint anchor2)
{
	this->needUpdate = true;
	this->anchor1 = anchor1;
	this->anchor2 = anchor2;
	this->control1 = control1;
	this->control2 = control2;
}

void Bezier::UpdatePointList(void)
{
	//是否需要更新
	if (this->needUpdate)
	{
		points.clear();
		CubicBezierToPointsI(anchor1, control1, control2, anchor2);
		needUpdate = false;
	}
}

void Bezier::SetAnchor1(CCPoint p)
{
	this->needUpdate = true;
	this->anchor1 = p;
}

void Bezier::SetAnchor2(CCPoint p)
{
	this->needUpdate = true;
	this->anchor2 = p;
}

void Bezier::SetControl1(CCPoint p)
{
	this->needUpdate = true;
	this->control1 = p;
}

void Bezier::SetControl2(CCPoint p)
{
	this->needUpdate = true;
	this->control2 = p;
}

//==========================================================================================

BezierPath::BezierPath(float controlLengthRate)
{
	this->controlLengthRate = controlLengthRate;
	needUpdate = true;
}

BezierPath::~BezierPath(void)
{
}

void BezierPath::ClearAnchorPoints(void)
{
	anchorPoints.clear();
}

void BezierPath::ClearPathPoints(void)
{
	pathPoints.clear();
}

void BezierPath::AddAnchorPoint(CCPoint p)
{
	anchorPoints.push_back(p);
}

void BezierPath::AddAnchorPointOnLine(CCPoint p)
{
	anchorPoints.push_back(p);
	CCPoint cp1 = GetControlPoint(&anchorPoints[anchorPoints.size() - 4], 
									&anchorPoints[anchorPoints.size() - 3], 
									&anchorPoints[anchorPoints.size() - 2]);

	CCPoint cp2 = GetControlPoint(&anchorPoints[anchorPoints.size() - 2], 
									&anchorPoints[anchorPoints.size() - 2], 
									&anchorPoints[anchorPoints.size() - 3]);

	AddToPath(anchorPoints[anchorPoints.size() - 3], cp1, cp2, anchorPoints[anchorPoints.size() - 2]);
}

void BezierPath::UpdatePath()
{
	pathPoints.clear();

	if (anchorPoints.size() > 0)
	{
		if (anchorPoints.size() == 1)
		{
			pathPoints.push_back(anchorPoints[0]);
		}
		else if (anchorPoints.size() == 2)
		{
			CCPoint cp1 = GetControlPoint(&anchorPoints[0], &anchorPoints[0], &anchorPoints[1]);
			CCPoint cp2 = GetControlPoint(&anchorPoints[1], &anchorPoints[1], &anchorPoints[0]);
			AddToPath(anchorPoints[0], cp1, cp2, anchorPoints[1]);
		}
		else
		{
			/*** 第一节 ***/
			CCPoint cp1 = GetControlPoint(&anchorPoints[0], &anchorPoints[0], &anchorPoints[1]);
			CCPoint cp2 = GetControlPoint(&anchorPoints[2], &anchorPoints[1], &anchorPoints[0]);
			AddToPath(anchorPoints[0], cp1, cp2, anchorPoints[1]);

			/*** 中间部分 ***/
			for (unsigned int i = 1; i < anchorPoints.size() - 2; i++)
			{
				cp1 = GetControlPoint(&anchorPoints[i - 1], &anchorPoints[i], &anchorPoints[i+1]);
				cp2 = GetControlPoint(&anchorPoints[i + 2], &anchorPoints[i+1], &anchorPoints[i]);
				AddToPath(anchorPoints[i], cp1, cp2, anchorPoints[i+1]);
			}

			/*** 最后一节 ***/
			cp1 = GetControlPoint(&anchorPoints[anchorPoints.size() - 3], &anchorPoints[anchorPoints.size() - 2], &anchorPoints[anchorPoints.size() - 1]);
			cp2 = GetControlPoint(&anchorPoints[anchorPoints.size() - 1], &anchorPoints[anchorPoints.size() - 1], &anchorPoints[anchorPoints.size() - 2]);
			AddToPath(anchorPoints[anchorPoints.size() - 2], cp1, cp2, anchorPoints[anchorPoints.size() - 1]);
		}
	}
}

void BezierPath::AddToPath(CCPoint a1, CCPoint c1,CCPoint c2, CCPoint a2)
{
	bezier.Reset(a1, c1, c2, a2);
	bezier.UpdatePointList();

	for(std::vector<CCPoint>::iterator it = bezier.points.begin(); it != bezier.points.end(); it++)
	{
		pathPoints.push_back(*it);
	}
}

CCPoint BezierPath::GetControlPoint(const CCPoint *p_last, const CCPoint *p_start, const CCPoint *p_end)
{
	float length = ccpDistance(*p_start, *p_end) * 0.4f;

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
		v =  ccpSub(*p_end, *p_start);
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

void BezierPath::CopyPathOut(vector<CCPoint> *path)
{
	for(std::vector<CCPoint>::iterator it = pathPoints.begin(); it != pathPoints.end(); it++)
	{
		path->push_back(ccp((*it).x, (*it).y));
	}
}

void BezierPath::SetControlLengthRate(float val)
{
	controlLengthRate = val;
}


#include "CCGeometry.h"
#include "CCPointExtension.h"
#include <vector>

using namespace cocos2d;
using namespace std;


class Bezier
{
public:
	Bezier(void);
	Bezier(CCPoint anchor1, CCPoint control1, CCPoint control2, CCPoint anchor2);
	~Bezier(void);
	void SetAnchor1(CCPoint p);
	void SetAnchor2(CCPoint p);
	void SetControl1(CCPoint p);
	void SetControl2(CCPoint p);
	void UpdatePointList(void);
	void Reset(CCPoint anchor1, CCPoint control1, CCPoint control2, CCPoint anchor2);

private:

	//根据起点、终点、控制点1、控制点2，计算曲线中所有锚点
	//p0：起点 p1:起点控制点 p2：终点控制点 p3终点
	inline void CubicBezierToPoints(CCPoint p0, CCPoint p1, CCPoint p2, CCPoint p3)
	{
		p1 = ccpSub(p1, p0);
		p2 = ccpSub(p2, p0);
		p3 = ccpSub(p3, p0);
		float xa = 0;
		float xb = p1.x;
		float xc = p2.x;
		float xd = p3.x;

		float ya = 0;
		float yb = p1.y;
		float yc = p2.y;
		float yd = p3.y;

		float x  = 0;
		float y = 0;

		for(float time = 0; time <= 1.0f; time += PointDistance)
		{
			x = bezierat(xa, xb, xc, xd, time);
			y = bezierat(ya, yb, yc, yd, time);
			points.push_back(ccpAdd(ccp(x,y), p0));
		}
	}

	inline float bezierat( float a, float b, float c, float d, float t )
	{
		return (powf(1-t,3) * a + 3*t*(powf(1-t,2))*b + 3*powf(t,2)*(1-t)*c + powf(t,3)*d );
	}

	inline void CubicBezierToPointsI(CCPoint p0, CCPoint p1, CCPoint p2, CCPoint p3)
	{
		//PointDistance 中间点距离两端点连线的距离，越大锚点越疏
		if (Distance(p1, p0, p3) < PointDistance && Distance(p2, p0, p3) < PointDistance)
		{
			points.push_back(p3);
		}
		else
		{
			CCPoint p01 = ccp((p0.x + p1.x) / 2, (p0.y + p1.y) / 2);
			CCPoint p12 = ccp((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
			CCPoint p23 = ccp((p2.x + p3.x) / 2, (p2.y + p3.y) / 2);
			CCPoint p012 = ccp((p01.x + p12.x) / 2, (p01.y + p12.y) / 2);
			CCPoint p123 = ccp((p12.x + p23.x) / 2, (p12.y + p23.y) / 2);
			CCPoint p = ccp((p012.x + p123.x) / 2, (p012.y + p123.y) / 2);

			CubicBezierToPoints(p0, p01, p012, p);
			CubicBezierToPoints(p, p123, p23, p3);
		}
	}

	inline float Distance(CCPoint p, CCPoint a, CCPoint b)
	{
		float paX = p.x - a.x;
		float paY = p.y - a.y;
		float baX = b.x - a.x;
		float baY = b.y - a.y;
		float pa2 = paX * paX + paY * paY;
		float ba2 = baX * baX + baY * baY;
		float apab = paX * baX + paY * baY;
		float apab2 = apab * apab;
		return pa2 - apab2 / ba2;
	}

public:
	std::vector<CCPoint> points;

private:
	bool needUpdate;
	CCPoint anchor1;
	CCPoint anchor2;
	CCPoint control1;
	CCPoint control2;
	float PointDistance;
};

class BezierPath
{
public:
	BezierPath(float controlLengthRate = 1.0);
	~BezierPath(void);
	void UpdatePath();
	void ClearAnchorPoints(void);
	void ClearPathPoints(void);
	void AddAnchorPoint(CCPoint p);
	void AddAnchorPointOnLine(CCPoint p);
	void CopyPathOut(vector<CCPoint> *path);
	void SetControlLengthRate(float val);

private:
	CCPoint GetControlPoint(const CCPoint *p_last, const CCPoint *p_start, const CCPoint *p_end);
	void AddToPath(CCPoint a1,CCPoint c1,CCPoint c2,CCPoint a2);

public:
	vector<CCPoint> pathPoints;
	vector<CCPoint> anchorPoints;

private:
	Bezier bezier;
	bool needUpdate;
	float controlLengthRate; 
};
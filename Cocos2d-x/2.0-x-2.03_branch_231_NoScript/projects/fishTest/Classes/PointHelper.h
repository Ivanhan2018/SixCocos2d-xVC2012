
#include "CCGeometry.h"
#include "math.h"



//·µ»Ø½Ç¶È
inline float PointAngle(CCPoint p)
{
	float r = 0;

	if(abs(p.x) <= 0.0001f)
	{
		if(p.y > 0)
		{
			r = 3.1415926f + 1.5707963f;
		}
		else
		{
			r = 1.5707963f;
		}
	}
	else if(p.x > 0)
	{
		r = atanf(p.y / p.x);
	}
	else
	{
		r = atanf(p.y / p.x) - 3.1415926f;
	}

	float rr = -CC_RADIANS_TO_DEGREES(r);

	while(rr >= 360)
	{
		rr -= 360;
	}

	while(rr < 0)
	{
		rr += 360;
	}

	return rr;
}
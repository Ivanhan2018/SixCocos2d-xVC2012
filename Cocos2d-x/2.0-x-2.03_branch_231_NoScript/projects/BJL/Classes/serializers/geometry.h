/*
** 实现 cocos2dx 的一些简单扩展
**                      
** date: 2012.08.01
*/

#ifndef __COCOS2D_EX_H__
#define __COCOS2D_EX_H__

#include "cocos2d.h"
#include "ans/AnsGeomethry.h"

using namespace cocos2d;

// -----------------------------------------------------------------------
// CCGeometry
// -----------------------------------------------------------------------
template<typename T>
class CCVector2 : public ans::TVector2<T>
{
public:
	inline CCVector2() 
		: ans::TVector2<float>()
	{}
	inline CCVector2(float x, float y)
		: ans::TVector2<float>(x, y)
	{}
	inline CCVector2(const CCPoint &point)
		: ans::TVector2<float>(point.x, point.y)
	{}
	inline CCVector2(const CCSize &size)
		: ans::TVector2<float>(size.width, size.height)
	{}

	// -----------------------------------------------
	inline CCVector2 operator+(const CCVector2 &v2) const { return CCVector2(this->x + v2.x, this->y + v2.y); }
	inline CCVector2 operator-(const CCVector2 &v2) const { return CCVector2(this->x - v2.x, this->y - v2.y); }
	inline CCVector2 operator*(const CCVector2 &v2) const { return CCVector2(this->x * v2.x, this->y * v2.y); }
	inline CCVector2 operator/(const CCVector2 &v2) const { return CCVector2(this->x / v2.x, this->y / v2.y); }
	inline CCVector2& operator+=(const CCVector2 &v2) { this->x += v2.x; this->y += v2.y; return *this; }
	inline CCVector2& operator-=(const CCVector2 &v2) { this->x -= v2.x; this->y -= v2.y; return *this; }
	inline CCVector2& operator*=(const CCVector2 &v2) { this->x *= v2.x; this->y *= v2.y; return *this; }
	inline CCVector2& operator/=(const CCVector2 &v2) { this->x /= v2.x; this->y /= v2.y; return *this; }

	template<typename ST>
	inline CCVector2 operator*(ST scale) const { return CCVector2(this->x * scale, this->y * scale); }
	template<typename ST>
	inline CCVector2 operator/(ST scale) const { return CCVector2(this->x / scale, this->y / scale); }
	template<typename ST>
	inline CCVector2& operator*=(ST scale) { this->x *= scale; this->y *= scale; return *this; }
	template<typename ST>
	inline CCVector2& operator/=(ST scale) { this->x /= scale; this->y /= scale; return *this; }

	// -----------------------------------------------
	inline CCVector2& operator=(const CCPoint &point) { this->x = point.x; this->y = point.y; return *this;}
	inline CCVector2& operator=(const CCSize &size) { this->x = size.width; this->y = size.height; return *this;}
	inline operator CCPoint() const { return CCPoint(this->x, this->y); }
	inline operator CCSize() const { return CCSize(this->x, this->y); }

	inline CCVector2 operator+(const CCPoint &point) const { return CCVector2(this->x + point.x, this->y + point.y);}
	inline CCVector2 operator-(const CCPoint &point) const { return CCVector2(this->x - point.x, this->y - point.y);}
	inline CCVector2 operator*(const CCPoint &point) const { return CCVector2(this->x * point.x, this->y * point.y);}
	inline CCVector2 operator/(const CCPoint &point) const { return CCVector2(this->x / point.x, this->y / point.y);}
	inline CCVector2& operator+=(const CCPoint &point) { this->x += point.x; this->y += point.y; return *this; }
	inline CCVector2& operator-=(const CCPoint &point) { this->x -= point.x; this->y -= point.y; return *this; }
	inline CCVector2& operator*=(const CCPoint &point) { this->x *= point.x; this->y *= point.y; return *this; }
	inline CCVector2& operator/=(const CCPoint &point) { this->x /= point.x; this->y /= point.y; return *this; }

	inline CCVector2 operator+(const CCSize &size) const { return CCVector2(this->x + size.width, this->y + size.height);}
	inline CCVector2 operator-(const CCSize &size) const { return CCVector2(this->x - size.width, this->y - size.height);}
	inline CCVector2 operator*(const CCSize &size) const { return CCVector2(this->x * size.width, this->y * size.height);}
	inline CCVector2 operator/(const CCSize &size) const { return CCVector2(this->x / size.width, this->y / size.height);}
	inline CCVector2& operator+=(const CCSize &size) { this->x += size.width; this->y += size.height; return *this; }
	inline CCVector2& operator-=(const CCSize &size) { this->x -= size.width; this->y -= size.height; return *this; }
	inline CCVector2& operator*=(const CCSize &size) { this->x *= size.width; this->y *= size.height; return *this; }
	inline CCVector2& operator/=(const CCSize &size) { this->x /= size.width; this->y /= size.height; return *this; }
};

typedef CCVector2<float> Vector2;
typedef ans::TVector3<float> Vector3;
typedef ans::TVector4<float> Vector4;

#define vv2(x, y) Vector2((x), (y))
#define vv3(x, y, z) Vector3((x), (y), (z))
#define vv4(x, y, z, w) Vector4((x), (y), (z), (w))

// -------------------------------------------------------------
// CCPoint
// -------------------------------------------------------------
// CCPoint + CCPoint
inline Vector2 operator+(const CCPoint &p1, const CCPoint &p2) { return vv2(p1.x + p2.x, p1.y + p2.y); }

// CCPoint - CCPoint
inline Vector2 operator-(const CCPoint &p1, const CCPoint &p2) { return vv2(p1.x - p2.x, p1.y - p2.y); }

// CCPoint * CCPoint
inline Vector2 operator*(const CCPoint &point1, const CCPoint &point2) { return vv2(point1.x * point2.x, point1.y * point2.y); }

// CCPoint * scale
inline Vector2 operator*(const CCPoint &point, float scale) { return vv2(point.x * scale, point.y * scale); }

// scale * CCPoint
inline Vector2 operator*(float scale, const CCPoint &point) { return vv2(point.x * scale, point.y * scale); }

// CCPoint / CCPoint
inline Vector2 operator/(const CCPoint &point1, const CCPoint &point2) { return vv2(point1.x / point2.x, point1.y / point2.y);}

// CCPoint / scale
inline Vector2 operator/(const CCPoint &point, float scale) { return vv2(point.x / scale, point.y / scale);}

// CCPoint += CCPoint
inline CCPoint& operator+=(CCPoint &p1, const CCPoint &p2) { p1.x += p2.x; p1.y += p2.y; return p1; }

// CCPoint -= CCPoint
inline CCPoint& operator-=(CCPoint &p1, const CCPoint &p2) { p1.x -= p2.x; p1.y -= p2.y; return p1; }

// CCPoint *= scale
inline CCPoint& operator*=(CCPoint &point, float scale) { point.x *= scale; point.y *= scale; return point; }

// CCPoint /= scale
inline CCPoint& operator/=(CCPoint &point, float scale) { point.x /= scale; point.y /= scale; return point; }


// ---------------------------------------------------
// CCPoint + CCSize
inline Vector2 operator+(const CCPoint &point, const CCSize &size) { return vv2(point.x + size.width, point.y + size.height); }

// CCPoint - CCSize
inline Vector2 operator-(const CCPoint &point, const CCSize &size) { return vv2(point.x - size.width, point.y - size.height); }

// CCPoint * CCSize
inline Vector2 operator*(const CCPoint &point, const CCSize &size) { return vv2(point.x * size.width, point.y * size.height); }

// CCPoint / CCSize
inline Vector2 operator/(const CCPoint &point, const CCSize &size) { return vv2(point.x / size.width, point.y / size.height); }

// CCPoint += CCSize
inline CCPoint& operator+=(CCPoint &point, const CCSize &size) { point.x += size.width, point.y += size.height; return point;}

// CCPoint -= CCSize
inline CCPoint& operator-=(CCPoint &point, const CCSize &size) { point.x -= size.width, point.y -= size.height; return point;}

// CCPoint *= CCSize
inline CCPoint& operator*=(CCPoint &point, const CCSize &size) { point.x *= size.width, point.y *= size.height; return point;}

// CCPoint /= CCSize
inline CCPoint& operator/=(CCPoint &point, const CCSize &size) { point.x /= size.width, point.y /= size.height; return point;}


// -------------------------------------------------------------
// CCSize
// -------------------------------------------------------------
// CCSize + CCSize
inline Vector2 operator+(const CCSize &p1, const CCSize &p2) { return vv2(p1.width + p2.width, p1.height + p2.height); }

// CCSize - CCSize
inline Vector2 operator-(const CCSize &p1, const CCSize &p2) { return vv2(p1.width - p2.width, p1.height - p2.height); }

// CCSize * scale
inline Vector2 operator*(const CCSize &point, float scale) { return vv2(point.width * scale, point.height * scale); }

// scale * CCSize
inline Vector2 operator*(float scale, const CCSize &point) { return vv2(point.width * scale, point.height * scale); }

// CCSize / scale
inline Vector2 operator/(const CCSize &point, float scale) { return vv2(point.width / scale, point.height / scale);}

// CCSize += CCSize
inline CCSize& operator+=(CCSize &p1, const CCSize &p2) { p1.width += p2.width; p1.height += p2.height; return p1; }

// CCSize -= CCSize
inline CCSize& operator-=(CCSize &p1, const CCSize &p2) { p1.width -= p2.width; p1.height -= p2.height; return p1; }

// CCSize *= scale
inline CCSize& operator*=(CCSize &point, float scale) { point.width *= scale; point.height *= scale; return point; }

// CCSize /= scale
inline CCSize& operator/=(CCSize &point, float scale) { point.width /= scale; point.height /= scale; return point; }


// -------------------------------------------------------------
// Vector2 & CCPoint & CCSize
// -------------------------------------------------------------
// CCPoint + Vector2
inline Vector2 operator+(const CCPoint &point, const Vector2 &v2) { return Vector2(v2.x + point.x, v2.y + point.y);}

// CCPoint - Vector2
inline Vector2 operator-(const CCPoint &point, const Vector2 &v2) { return Vector2(point.x - v2.x, point.y - v2.y);}

// CCPoint * Vector2
inline Vector2 operator*(const CCPoint &point, const Vector2 &v2) { return Vector2(v2.x * point.x, v2.y * point.y);}

// CCPoint / Vector2
inline Vector2 operator/(const CCPoint &point, const Vector2 &v2) { return Vector2(v2.x / point.x, v2.y / point.y);}

// ---------------------------------------------------
// CCSize + Vector2
inline Vector2 operator+(const CCSize &size, const Vector2 &v2) { return Vector2(v2.x + size.width, v2.y + size.height);}

// CCSize - Vector2
inline Vector2 operator-(const CCSize &size, const Vector2 &v2) { return Vector2(size.width - v2.x, size.height - v2.y);}

// CCSize * Vector2
inline Vector2 operator*(const CCSize &size, const Vector2 &v2) { return Vector2(v2.x * size.width, v2.y * size.height);}

// CCSize / Vector2
inline Vector2 operator/(const CCSize &size, const Vector2 &v2) { return Vector2(v2.x / size.width, v2.y / size.height);}


// -------------------------------------------------------------
// CCRect
// -------------------------------------------------------------
// CCRect + CCPoint
inline CCRect operator+(const CCRect &rect, const CCPoint &point){return CCRect(rect.origin.x + point.x, rect.origin.y + point.y, rect.size.width, rect.size.height);}

// CCRect - CCPoint
inline CCRect operator-(const CCRect &rect, const CCPoint &point){return CCRect(rect.origin.x - point.x, rect.origin.y - point.y, rect.size.width, rect.size.height);}

// CCRect * scale
inline CCRect operator*(const CCRect &rect, float scale) { return CCRect(rect.origin.x, rect.origin.y, rect.size.width * scale, rect.size.height * scale);}

// scale * CCRect
inline CCRect operator*(float scale, const CCRect &rect) { return CCRect(rect.origin.x, rect.origin.y, rect.size.width * scale, rect.size.height * scale);}

// CCRect / scale
inline CCRect operator/(const CCRect &rect, float scale) { return CCRect(rect.origin.x, rect.origin.y, rect.size.width / scale, rect.size.height / scale);}

// CCRect += CCPoint
inline CCRect& operator+=(CCRect &rect, const CCPoint &point) { rect.origin.x += point.x; rect.origin.y += point.y; return rect;}

// CCRect -= CCPoint
inline CCRect& operator-=(CCRect &rect, const CCPoint &point) { rect.origin.x -= point.x; rect.origin.y -= point.y; return rect;}

// CCRect *= scale
inline CCRect& operator*=(CCRect &rect, float scale) { rect.size *= scale; return rect; }

// CCRect /= sacle
inline CCRect& operator/=(CCRect &rect, float scale) { rect.size /= scale; return rect; }


#endif
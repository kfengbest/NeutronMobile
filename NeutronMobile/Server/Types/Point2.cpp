#define __COMPILING_NS_POINT2_CPP__
#include "Point2.h"
#undef __COMPILING_NS_POINT2_CPP__
 
#include "Size2.h"

using namespace Ns;
using namespace Ns::Core;


Point2::Point2() : x(0), y(0)
{
}

Point2::Point2(const Size2& size) : x(size.width), y(size.height)
{
}

Point2::Point2(int32 xPos, int32 yPos) : x(xPos), y(yPos)
{
}

IString Point2::toString() const 
{
	IString strText;
	return strText;
}

void Point2::point(int32 xPos, int32 yPos)			{ x = xPos; y = yPos; }

void Point2::offset(int32 xOffset, int32 yOffset)	{ x += xOffset; y += yOffset; }
void Point2::offset(const Point2& point)			{ x += point.x; y += point.y; }
void Point2::offset(const Size2& size)				{ x += size.width; y += size.height; }

bool Point2::operator==(const Point2& point) const	{ return (x == point.x && y == point.y); }
bool Point2::operator!=(const Point2& point) const	{ return (x != point.x || y != point.y); }

void Point2::operator+=(const Size2& size)			{ x += size.width; y += size.height; }
void Point2::operator-=(const Size2& size)			{ x -= size.width; y -= size.height; }
void Point2::operator+=(const Point2& point)		{ x += point.x; y += point.y; }
void Point2::operator-=(const Point2& point)		{ x -= point.x; y -= point.y; }

Point2 Point2::operator+(const Size2& size) const	{ return Point2(x + size.width, y + size.height); }
Point2 Point2::operator-(const Size2& size) const	{ return Point2(x - size.width, y - size.height); }
Point2 Point2::operator+(const Point2& point) const	{ return Point2(x + point.x, y + point.y); }
Size2 Point2::operator-(const Point2& point) const	{ return Size2(x - point.x, y - point.y); }

Point2 Point2::operator-() const					{ return Point2(-x, -y); }

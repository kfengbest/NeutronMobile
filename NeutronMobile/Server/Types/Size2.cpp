#define __COMPILING_NS_SIZE2_CPP__
#include "Size2.h"
#undef __COMPILING_NS_SIZE2_CPP__

#include "Point2.h"

using namespace Ns;
using namespace Ns::Core;

Size2::Size2() : width(0), height(0)
{
}

Size2::Size2(const Point2& point) : width(point.x), height(point.y)
{
}

Size2::Size2(int32 w, int32 h) : width(w), height(h)
{
}

IString Size2::toString() const 
{
	IString strText;
	return strText;
}

void Size2::size(int32 w, int32 h)					{ width = w; height = h; }

bool Size2::operator==(const Size2& size) const		{ return (width == size.width && height == size.height); }
bool Size2::operator!=(const Size2& size) const		{ return (width != size.width || height != size.height); }

void Size2::operator+=(const Size2& size)			{ width += size.width; height += size.height; }
void Size2::operator-=(const Size2& size)			{ width -= size.width; height -= size.height; }

Size2 Size2::operator+(const Size2& size) const		{ return Size2(width + size.width, height + size.height); }
Size2 Size2::operator-(const Size2& size) const		{ return Size2(width - size.width, height - size.height); }
Point2 Size2::operator+(const Point2& point) const	{ return Point2(width + point.x, height + point.y); }
Point2 Size2::operator-(const Point2& point) const	{ return Point2(width - point.x, height - point.y); }

Size2 Size2::operator-() const						{ return Size2(-width, -height); }

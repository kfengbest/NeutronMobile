#pragma once

// A Point2 is a 2-D point, used to represent values such as positions in the x-y coordinate plane and
// other similar situation.
 
#include "../Base/Globals.h"

#ifdef NS_TYPES_EXPORTS
 #ifdef __COMPILING_NS_POINT2_CPP__
  #define NS_TYPES_API NS_EXPORT
 #else
  #define NS_TYPES_API
 #endif
#else
 #define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {


	class Size2;
	class NS_TYPES_API Point2 {
	public:

		Point2();
		Point2(const Size2& size);
		Point2(int32 xPos, int32 yPos);

		IString toString() const;	// For debug

		void point(int32 xPos, int32 yPos);

		void offset(int32 xOffset, int32 yOffset);
		void offset(const Point2& point);
		void offset(const Size2& size);

		bool operator==(const Point2& point) const;
		bool operator!=(const Point2& point) const;

		void operator+=(const Size2& size);
		void operator-=(const Size2& size);
		void operator+=(const Point2& point);
		void operator-=(const Point2& point);

		Point2 operator+(const Size2& size) const;
		Point2 operator-(const Size2& size) const;
		Point2 operator+(const Point2& point) const;
		Size2 operator-(const Point2& point) const;

		Point2 operator-() const;

		int32 x;
		int32 y;
	};

	typedef Point2 ScreenPoint2;


}}

#undef NS_TYPES_API

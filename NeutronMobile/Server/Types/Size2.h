#pragma once

// A Size2 is an extent, used to represent values such as width-height pairs and other similar situation
 
#include "../Base/Globals.h"

#ifdef NS_TYPES_EXPORTS
 #ifdef __COMPILING_NS_SIZE2_CPP__
  #define NS_TYPES_API NS_EXPORT
 #else
  #define NS_TYPES_API
 #endif
#else
 #define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {


	class Point2;
	class NS_TYPES_API Size2 {
	public:
	
		Size2();
		Size2(const Point2& point);
		Size2(int32 w, int32 h);

		IString toString() const;	// For debug

		void size(int32 w, int32 h);

		bool operator==(const Size2& size) const;
		bool operator!=(const Size2& size) const;

		void operator+=(const Size2& size);
		void operator-=(const Size2& size);

		Size2 operator+(const Size2& size) const;
		Size2 operator-(const Size2& size) const;
		Point2 operator+(const Point2& point) const;
		Point2 operator-(const Point2& point) const;

		Size2 operator-() const;

		int32 width;
		int32 height;
	};

	typedef Size2 ScreenSize2;

}}

#undef NS_TYPES_API

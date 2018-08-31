#pragma once
//
//  Plane.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//


#include "../Base/Globals.h"
#include "Vector3f.h"

#ifdef NS_TYPES_EXPORTS
 #ifdef __COMPILING_NS_PLANE_CPP__
  #define NS_TYPES_API NS_EXPORT
 #else
  #define NS_TYPES_API
 #endif
#else
 #define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {

	class NS_TYPES_API Plane
	{
    public:
		Plane() {}
		~Plane() {}
		
		void Set(const Vector &p, const Vector &normal) { m_p = p; m_normal = normal; }
		bool IsOutside(const Vector &p, float radius);
		
		Vector m_p;
		Vector m_normal;
	};



}}

#undef NS_TYPES_API

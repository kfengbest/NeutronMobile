#pragma once
//
//  Matrix.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//


#include "../Base/Globals.h"

#ifdef NS_TYPES_EXPORTS
 #ifdef __COMPILING_NS_MATRIX_CPP__
  #define NS_TYPES_API NS_EXPORT
 #else
  #define NS_TYPES_API
 #endif
#else
 #define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {


	class NS_TYPES_API Matrix
	{
    public:
		float m[16];
	};

}}


#undef NS_TYPES_API

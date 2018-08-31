#pragma once
//
//  Quaternion.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//


#include "../Base/Globals.h"
#include "Vector3f.h"

#ifdef NS_TYPES_EXPORTS
 #ifdef __COMPILING_NS_QUATERNION_CPP__
  #define NS_TYPES_API NS_EXPORT
 #else
  #define NS_TYPES_API
 #endif
#else
 #define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {


	struct NS_TYPES_API Quaternion
	{
    public:
        
		Quaternion();
		Quaternion(float x, float y, float z, float w);
        
		void Set(float x, float y, float z, float w);
		void FromRotation(const Vector& axis, float angle);
		void GetRotation(Vector &axis, float &theta);
		void FromTwoVectors(const Vector& a, const Vector& b);
		void FromThreeVectors(const Vector& x, const Vector& y, const Vector& z);
		void SetEulerAngles(const Vector &e);
		void GetEulerAngles(Vector &e) const;
        
		void Normalize();
		void Interpolate(const Quaternion &A, const Quaternion &B, float s);
		void Invert(const Quaternion &src);
		
		void Multiply(const Quaternion &qa, const Quaternion &qb);
        
		bool MakeYUp(const Quaternion &tip);
        
		void ExtractMatrix(Matrix &M) const;
        
		float m_x;
		float m_y;
		float m_z;
		float m_w;
	};



}}

#undef NS_TYPES_API

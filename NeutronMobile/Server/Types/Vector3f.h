#pragma once
//
//  Vector3d.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//


#include "../Base/Globals.h"
#include "Matrix.h"
#include <cmath>

#ifdef NS_TYPES_EXPORTS
 #ifdef __COMPILING_NS_VECTOR3F_CPP__
  #define NS_TYPES_API NS_EXPORT
 #else
  #define NS_TYPES_API
 #endif
#else
 #define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {


    class Transform;
    class Quaternion;
    
	class NS_TYPES_API Vector
	{
    public:
        
		Vector();
		Vector(float x, float y, float z);
        
		void Set(float x, float y, float z);
		void Normalize();
		float Magnitude() const;
		float MagnitudeSquared();
		float DistanceSquared(const Vector& v);
		float Dot(const Vector& v);
		float Dot(const Vector& v) const;
		void Cross(const Vector& va, const Vector& vb);
		void Scale(float scale);
		void Scale(float scale, const Vector& src);
		void Scale(const Vector &s);
        
		void Multiply(const Transform &T, const Vector &v);
		void Multiply(const Quaternion &q, const Vector &v);
		void Multiply(const Matrix &M, const Vector &v);
		void Multiply(const Vector &a, const Vector &b);
		void Add(const Vector& va, const Vector& vb);
		void Subtract(const Vector& va, const Vector& vb);
		void Interpolate(const Vector &va, const Vector &vb, float s);
        
        
		float m_x;
		float m_y;
		float m_z; 
	};
    
}}



#undef NS_TYPES_API

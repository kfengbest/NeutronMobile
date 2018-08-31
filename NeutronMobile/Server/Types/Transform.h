#pragma once
//
//  Transform.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//


#include "../Base/Globals.h"
#include "Vector3f.h"
#include "Quaternion.h"

#ifdef NS_TYPES_EXPORTS
 #ifdef __COMPILING_NS_TRANSFORM_CPP__
  #define NS_TYPES_API NS_EXPORT
 #else
  #define NS_TYPES_API
 #endif
#else
 #define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {
    
	class NS_TYPES_API Transform
	{
    public:
		Transform();
		
		// construct a transform from a 4x4 column major matrix (a float array with 16 elements where
		// m[12], m[13], and m[14] are the translation x, y, z values respectively)
		void FromColumnMajor4x4(float *m);
        
		void Identity()	{ m_position.Set(0,0,0); m_rotation.Set(0,0,0,1); }
		void Invert(const Transform &T);
		void SetPosition(const Vector& pos);
		void SetRotation(const Quaternion& rot);
		void SetScale(const Vector& scale);
		void EyeLookUp(const Vector &eye, const Vector &look, const Vector &up);
        
		void Multiply(const Transform &A, const Transform &B);
        
		void ExtractMatrix(Matrix &M) const;
        
		void Interpolate(const Transform &A, const Transform &B, float s);
        
		float GetMaxScale();
        
		Vector m_position;
		Quaternion m_rotation;
		Vector m_scale;
	};



}}

#undef NS_TYPES_API

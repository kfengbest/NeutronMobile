//
//  Geometry.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "Geometry.h"


#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_PARAMETRICSURFACE_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif


namespace Ns { namespace Scene {
    
    
    class Scene;
    
    struct ParametricInterval{
        ivec2 Divisions;
        vec2 UpperBound;
        vec2 TextureCount;
    };
    
    class NS_SCENE_API ParametricSurface : public Geometry
    {
    public:
		ParametricSurface(Scene* scene);
		virtual ~ParametricSurface();
        
        virtual int GetVertexCount() const;
        virtual int GetLineIndexCount() const;
        virtual int GetTriangleIndexCount() const;
        virtual void GenerateVertices(std::vector<float>& vertices, unsigned char flags = 0) const ;
        virtual void GenerateLineIndices(std::vector<unsigned short>& indices) const;
        virtual void GenerateTriangleIndices(std::vector<unsigned short>& indices) const;
        
    protected:
        void SetInterval(const ParametricInterval& interval);
        virtual vec3 Evaluate(const vec2& domain) const = 0;
        virtual bool InvertNormal(const vec2& domain) const { return false; }
        
    private:
        vec2 ComputeDomain(float i, float j) const;
        ivec2 m_slices;
        ivec2 m_divisions;
        vec2 m_upperBound;
        vec2 m_textureCount;
    };
}}


#undef NS_SCENE_API


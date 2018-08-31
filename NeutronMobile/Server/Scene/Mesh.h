//
//  Mesh.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "Geometry.h"

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_SCENE_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif


namespace Ns { namespace Scene {
    
    struct Vertex {
        vec3 Position;
        vec4 Color;
    };
    
    
    class Scene;
    class NS_SCENE_API Mesh : public Geometry
    {
    public:
		Mesh(Scene* scene);
		virtual ~Mesh();
        
    public:

        // unimplemented yet!!!
        virtual int GetVertexCount() const { return 0;}
        virtual int GetLineIndexCount() const { return 0;}
        virtual int GetTriangleIndexCount() const { return 0;}
        virtual void GenerateVertices(std::vector<float>& vertices, unsigned char flags = 0) const  {}
        virtual void GenerateLineIndices(std::vector<unsigned short>& indices) const {}
        virtual void GenerateTriangleIndices(std::vector<unsigned short>& indices) const {}

        const std::vector<Vertex>& vertices();
        std::vector<unsigned char> indices();
        
        // temp
        int bodyIndexCount() const {return m_bodyIndexCount;}
        void bodyIndexCount(int n) {m_bodyIndexCount = n;}
        
        int diskIndexCount() const { return m_diskIndexCount;}
        void diskIndexCount(int n) { m_diskIndexCount = n;}
        
    private:
        std::vector<Vertex> m_coneVertices;
        std::vector<unsigned char> m_coneIndices;

        // temp:
        int m_bodyIndexCount;
        int m_diskIndexCount;
    };
}}


#undef NS_SCENE_API


//
//  Geometry.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "Geometry.h"
#include <vector>
#include <string>

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_OBJMESH_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif


namespace Ns { namespace Scene {
    
    class Scene;
    
    class NS_SCENE_API ObjMesh : public Geometry
    {
    public:
		ObjMesh(Scene* scene, const std::string& name);
		virtual ~ObjMesh();
        
        virtual int GetVertexCount() const;
        virtual int GetLineIndexCount() const {return 0;};
        virtual int GetTriangleIndexCount() const;
        virtual void GenerateVertices(std::vector<float>& vertices, unsigned char flags = 0) const ;
        virtual void GenerateLineIndices(std::vector<unsigned short>& indices) const {}
        virtual void GenerateTriangleIndices(std::vector<unsigned short>& indices) const;
        

    private:
        std::string m_name;
        std::vector<ivec3> m_faces;
        mutable size_t m_faceCount;
        mutable size_t m_vertexCount;
        static const int MaxLineSize = 128;
    };
    
}}


#undef NS_SCENE_API


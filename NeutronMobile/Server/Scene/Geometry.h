//
//  Geometry.h
//  NeutronMobile
//
//  Created by fengka on 8/18/12.
//  Copyright (c) 2012 fengka. All rights reserved.
//

#pragma once

#include "../Base/Globals.h"
#include "../Types/Vector.hpp"
#include "../Base/Types/Object.h"
#include <vector>

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_GEOMETRY_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif


namespace Ns { namespace Scene {
    
    
    class Scene;
    
    enum VertexFlags {
        VertexFlagsNormals = 1 << 0,
        VertexFlagsTexCoords = 1 << 1,
    };
    
    class NS_SCENE_API Geometry
    {
    public:
		Geometry(Scene* scene);
		virtual ~Geometry();
        
        virtual int GetVertexCount() const = 0;
        virtual int GetLineIndexCount() const = 0;
        virtual int GetTriangleIndexCount() const = 0;
        virtual void GenerateVertices(std::vector<float>& vertices, unsigned char flags = 0) const = 0;
        virtual void GenerateLineIndices(std::vector<unsigned short>& indices) const = 0;
        virtual void GenerateTriangleIndices(std::vector<unsigned short>& indices) const = 0;
        
        void setAttachment(Ns::Object *data)		{ delete m_attachment; m_attachment = data; }
		Ns::Object*  getAttachment()				{ return m_attachment; }
    
    private:
        Ns::Object* m_attachment;
    };
}}


#undef NS_SCENE_API


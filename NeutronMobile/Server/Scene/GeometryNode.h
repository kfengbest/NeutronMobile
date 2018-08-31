#pragma once

#include "../Base/Globals.h"
#include "Node.h"
#include "Geometry.h"

#ifdef NS_SCENE_EXPORTS
# ifdef __COMPILING_NS_GEOMETRYNODE_CPP__
#  define NS_SCENE_API NS_EXPORT
# else
#  define NS_SCENE_API
# endif
#else
# define NS_SCENE_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    
    class Scene;
    
    class NS_SCENE_API GeometryNode : public Node
    {
    public:
        GeometryNode();
        virtual ~GeometryNode();
        
        Geometry* geometry() const;
        void geometry(Geometry* pMesh);
        
    private:
        Geometry* m_pMesh;
    };
}}


#undef NS_SCENE_API


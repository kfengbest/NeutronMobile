#pragma once

#include "../Base/Globals.h"
#include "../Scene/ParametricSurface.h"

#ifdef NS_GEOMETRY3D_EXPORTS
# ifdef __COMPILING_NS_GEOMETRY3D_CPP__
#  define NS_GEOMETRY3D_API NS_EXPORT
# else
#  define NS_GEOMETRY3D_API
# endif
#else
# define NS_GEOMETRY3D_API NS_IMPORT
#endif

namespace Ns { namespace Scene {
    class Scene;
}}

namespace Ns { namespace Geometry {
        
    class NS_GEOMETRY3D_API Geometry3D : public Ns::Scene::ParametricSurface
    {
    public:
        Geometry3D(Ns::Scene::Scene* scene);
        virtual ~Geometry3D();
    
    };
}}


#undef NS_GEOMETRY3D_API

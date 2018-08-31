#pragma once

#include "../Base/Globals.h"
#include "Geometry3D.h"

#ifdef NS_GEOMETRY3D_EXPORTS
# ifdef __COMPILING_NS_CONE_CPP__
#  define NS_GEOMETRY3D_API NS_EXPORT
# else
#  define NS_GEOMETRY3D_API
# endif
#else
# define NS_GEOMETRY3D_API NS_IMPORT
#endif

namespace Ns { namespace Geometry {
    
    class NS_GEOMETRY3D_API Cone : public Geometry3D {
    public:
        Cone(Ns::Scene::Scene* scene, float height, float radius);
        vec3 Evaluate(const vec2& domain) const;
        
    private:
        float m_height;
        float m_radius;
    };
}}


#undef NS_GEOMETRY3D_API

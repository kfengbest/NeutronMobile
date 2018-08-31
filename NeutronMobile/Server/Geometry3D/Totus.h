#pragma once

#include "../Base/Globals.h"
#include "Geometry3D.h"

#ifdef NS_GEOMETRY3D_EXPORTS
# ifdef __COMPILING_NS_TOTUS_CPP__
#  define NS_GEOMETRY3D_API NS_EXPORT
# else
#  define NS_GEOMETRY3D_API
# endif
#else
# define NS_GEOMETRY3D_API NS_IMPORT
#endif

namespace Ns { namespace Geometry {
    
    
    class NS_GEOMETRY3D_API Torus : public Geometry3D {
    public:
        Torus(Ns::Scene::Scene* scene, float majorRadius, float minorRadius);
        vec3 Evaluate(const vec2& domain) const;

    private:
        float m_majorRadius;
        float m_minorRadius;
    };
}}


#undef NS_GEOMETRY3D_API

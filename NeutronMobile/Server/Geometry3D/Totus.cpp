
#define __COMPILING_NS_TOTUS_CPP__
#include "Totus.h"
#undef __COMPILING_NS_TOTUS_CPP__

#include "../Scene/Scene.h"

using namespace Ns::Geometry;

Torus::Torus(Ns::Scene::Scene* scene, float majorRadius, float minorRadius)
:Geometry3D(scene),
m_majorRadius(majorRadius),
m_minorRadius(minorRadius)
{
    Ns::Scene::ParametricInterval interval = { ivec2(20, 20), vec2(TwoPi, TwoPi), vec2(40, 10) };
    SetInterval(interval);
}
vec3 Torus::Evaluate(const vec2& domain) const
{
    const float major = m_majorRadius;
    const float minor = m_minorRadius;
    float u = domain.x, v = domain.y;
    float x = (major + minor * cos(v)) * cos(u);
    float y = (major + minor * cos(v)) * sin(u);
    float z = minor * sin(v);
    return vec3(x, y, z);
}
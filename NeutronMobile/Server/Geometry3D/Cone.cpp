
#define __COMPILING_NS_CONE_CPP__
#include "Cone.h"
#undef __COMPILING_NS_CONE_CPP__

#include "../Scene/Scene.h"

using namespace Ns::Geometry;

Cone::Cone(Ns::Scene::Scene* scene, float height, float radius)
: Geometry3D(scene), m_height(height), m_radius(radius)
{
    Ns::Scene::ParametricInterval interval = { ivec2(20, 20), vec2(TwoPi, 1), vec2(30, 20) };
    SetInterval(interval);
}
vec3 Cone::Evaluate(const vec2& domain) const
{
    float u = domain.x, v = domain.y;
    float x = m_radius * (1 - v) * cos(u);
    float y = m_height * (v - 0.5f);
    float z = m_radius * (1 - v) * -sin(u);
    return vec3(x, y, z);
}

#define __COMPILING_NS_SPHERE_CPP__
#include "Sphere.h"
#undef __COMPILING_NS_SPHERE_CPP__

#include "../Scene/Scene.h"

using namespace Ns::Geometry;

Sphere::Sphere(Ns::Scene::Scene* scene, float radius)
: Geometry3D(scene), m_radius(radius)
{
    Ns::Scene::ParametricInterval interval = { ivec2(20, 20), vec2(Pi, TwoPi), vec2(20, 35) };
    SetInterval(interval);
}
vec3 Sphere::Evaluate(const vec2& domain) const
{
    float u = domain.x, v = domain.y;
    float x = m_radius * sin(u) * cos(v);
    float y = m_radius * cos(u);
    float z = m_radius * -sin(u) * sin(v);
    return vec3(x, y, z);
}
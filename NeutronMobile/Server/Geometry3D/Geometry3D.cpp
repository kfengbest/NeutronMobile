
#define __COMPILING_NS_GEOMETRY3D_CPP__
#include "Geometry3D.h"
#undef __COMPILING_NS_GEOMETRY3D_CPP__

#include "../Scene/Scene.h"

using namespace Ns::Geometry;

Geometry3D::Geometry3D(Ns::Scene::Scene* scene)
: Ns::Scene::ParametricSurface(scene)
{
    
}

Geometry3D::~Geometry3D()
{
    
}
#define __COMPILING_NS_PLANE_CPP__
#include "Plane.h"
#undef __COMPILING_NS_PLANE_CPP__
 

using namespace Ns;
using namespace Ns::Core;

bool Plane::IsOutside(const Vector &p, float radius)
{
	Vector dir;
	dir.Subtract(p, m_p);
	
	float d = dir.Dot(m_normal);
	
	return (d > radius);
}
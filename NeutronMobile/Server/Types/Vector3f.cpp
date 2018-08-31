#define __COMPILING_NS_VECTOR3F_CPP__
#include "Vector3f.h"
#undef __COMPILING_NS_VECTOR3F_CPP__
 
#include "Transform.h"
#include "Quaternion.h"

using namespace Ns;
using namespace Ns::Core;

Vector::Vector() :
m_x(0.0),
m_y(0.0),
m_z(0.0)
{
    
}

Vector::Vector(float x, float y, float z) :
m_x(x),
m_y(y),
m_z(z)
{
    
}

//////////////////////
//
// Set the elements of the vector
//
void Vector::Set(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

//////////////////////
//
// Normalize the vector
//
void Vector::Normalize()
{
	float l = sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
	m_x /= l;
	m_y /= l;
	m_z /= l;
}

//////////////////////
//
// Return the magnitude of the vector
//
float Vector::Magnitude() const
{
	return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

//////////////////////
//
// Return the magnitude squared of the vector
//
float Vector::MagnitudeSquared()
{
	return m_x*m_x + m_y*m_y + m_z*m_z;
}

//////////////////////
//
// Return the dot product of the vector and the input
//
float Vector::Dot(const Vector& v)
{
	return m_x*v.m_x + m_y*v.m_y + m_z*v.m_z;
}

//////////////////////
//
// Return the dot product of the vector and the input
//
float Vector::Dot(const Vector& v) const
{
	return m_x*v.m_x + m_y*v.m_y + m_z*v.m_z;
}

//////////////////////
//
// Return the distance squared from the vector to the input
//
float Vector::DistanceSquared(const Vector& v)
{
	return (m_x-v.m_x)*(m_x-v.m_x) + (m_y-v.m_y)*(m_y-v.m_y) + (m_z-v.m_z)*(m_z-v.m_z);
}

//////////////////////
//
// Compute the cross product
//
void Vector::Cross(const Vector& va, const Vector& vb)
{
	float x, y, z;
	
	x = (va.m_y * vb.m_z) - (va.m_z * vb.m_y);
	y = (va.m_z * vb.m_x) - (va.m_x * vb.m_z);
	z = (va.m_x * vb.m_y) - (va.m_y * vb.m_x);
    
	m_x = x;
	m_y = y;
	m_z = z;
}

//////////////////////
//
// Scale the vector
//
void Vector::Scale(float s)
{
	m_x *= s;
	m_y *= s;
	m_z *= s;
}

//////////////////////
//
// Scale the vector
//
void Vector::Scale(float s, const Vector& src)
{
	m_x = src.m_x*s;
	m_y = src.m_y*s;
	m_z = src.m_z*s;
}

//////////////////////
//
// Scale the vector
//
void Vector::Scale(const Vector &s)
{
	m_x *= s.m_x;
	m_y *= s.m_y;
	m_z *= s.m_z;
}

//////////////////////
//
// Multiply a vector by a transform
//
void Vector::Multiply(const Transform &T, const Vector &v)
{
    float ssvv, vr, s;
    Vector tmp;
    
    
    ssvv = (T.m_rotation.m_w * T.m_rotation.m_w) -
    ((T.m_rotation.m_x * T.m_rotation.m_x) + (T.m_rotation.m_y * T.m_rotation.m_y) + (T.m_rotation.m_z * T.m_rotation.m_z));
    vr = 2.0f * ((T.m_rotation.m_x * v.m_x) + (T.m_rotation.m_y * v.m_y) + (T.m_rotation.m_z * v.m_z));
    s = 2.0f * T.m_rotation.m_w;
    
    tmp.m_x = (ssvv * v.m_x) + (vr * T.m_rotation.m_x) + (s * (T.m_rotation.m_y * v.m_z - T.m_rotation.m_z * v.m_y));
    tmp.m_y = (ssvv * v.m_y) + (vr * T.m_rotation.m_y) + (s * (T.m_rotation.m_z * v.m_x - T.m_rotation.m_x * v.m_z));
    tmp.m_z = (ssvv * v.m_z) + (vr * T.m_rotation.m_z) + (s * (T.m_rotation.m_x * v.m_y - T.m_rotation.m_y * v.m_x));
    
    
    m_x = T.m_scale.m_x*tmp.m_x + T.m_position.m_x;
    m_y = T.m_scale.m_y*tmp.m_y + T.m_position.m_y;
    m_z = T.m_scale.m_z*tmp.m_z + T.m_position.m_z;
    
}

//////////////////////
//
// Multiply a vector by a quaternion
//
void Vector::Multiply(const Quaternion &q, const Vector &v)
{
    float ssvv, vr, s;
	float x, y, z;
    
	ssvv = (q.m_w * q.m_w) - (q.m_x * q.m_x + q.m_y * q.m_y + q.m_z * q.m_z);
	vr = 2.0f * (q.m_x * v.m_x + q.m_y * v.m_y + q.m_z * v.m_z);
	s = 2.0f * q.m_w;
    
	x = ssvv * v.m_x + vr * q.m_x + s * (q.m_y * v.m_z - q.m_z * v.m_y);
	y = ssvv * v.m_y + vr * q.m_y + s * (q.m_z * v.m_x - q.m_x * v.m_z);
	z = ssvv * v.m_z + vr * q.m_z + s * (q.m_x * v.m_y - q.m_y * v.m_x);
    
	m_x = x;
	m_y = y;
	m_z = z;
}

//////////////////////
//
// Multiply a vector by a matrix
//
void Vector::Multiply(const Matrix &M, const Vector &v)
{
	float x, y, z;
    
    
	x = M.m[0] * v.m_x + M.m[4] * v.m_y + M.m[8] * v.m_z + M.m[12];
	y = M.m[1] * v.m_x + M.m[5] * v.m_y + M.m[9] * v.m_z + M.m[13];
	z = M.m[2] * v.m_x + M.m[6] * v.m_y + M.m[10] * v.m_z + M.m[14];
    
	m_x = x;
	m_y = y;
	m_z = z;
}

//////////////////////
//
// Multiply two vectors
//
void Vector::Multiply(const Vector &a, const Vector &b)
{
	m_x = a.m_x * b.m_x;
	m_y = a.m_y * b.m_y;
	m_z = a.m_z * b.m_z;
}


//////////////////////
//
// Add two vectors
//
void Vector::Add(const Vector& va, const Vector& vb)
{
	m_x = va.m_x + vb.m_x;
	m_y = va.m_y + vb.m_y;
	m_z = va.m_z + vb.m_z;
}


//////////////////////
//
// Subtract two vectors
//
void Vector::Subtract(const Vector& va, const Vector& vb)
{
	m_x = va.m_x - vb.m_x;
	m_y = va.m_y - vb.m_y;
	m_z = va.m_z - vb.m_z;
}



//////////////////////
//
// Interpolate between two vectors
//
void Vector::Interpolate(const Vector &va, const Vector &vb, float s)
{
	if(s < 0)
		s = 0;
	if(s > 1)
		s = 1;
    
    m_x = va.m_x + s*(vb.m_x - va.m_x);
    m_y = va.m_y + s*(vb.m_y - va.m_y);
    m_z = va.m_z + s*(vb.m_z - va.m_z);
}

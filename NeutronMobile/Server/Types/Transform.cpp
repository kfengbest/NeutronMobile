#define __COMPILING_NS_TRANSFORM_CPP__
#include "Transform.h"
#undef __COMPILING_NS_TRANSFORM_CPP__
 


using namespace Ns;
using namespace Ns::Core;

Transform::Transform() :
m_scale(1,1,1)
{
}

//////////////////////
//
// Construct a transform from a 4x4 row major matrix (a float array with 16 elements where
// m[12], m[13], and m[14] are the translation x, y, z values respectively)
//
void Transform::FromColumnMajor4x4(float *m)
{
	// extract the position
	m_position.Set(m[12], m[13], m[14]);
    
	// extract the scale
	Vector r;
	r.Set(m[0], m[1], m[2]);
	m_scale.m_x = r.Magnitude();
	m[0] /= m_scale.m_x; m[1] /= m_scale.m_x; m[2] /= m_scale.m_x;
    
	r.Set(m[4], m[5], m[6]);
	m_scale.m_y = r.Magnitude();
	m[4] /= m_scale.m_y; m[5] /= m_scale.m_y; m[6] /= m_scale.m_y;
    
	r.Set(m[8], m[9], m[10]);
	m_scale.m_z = r.Magnitude();
	m[8] /= m_scale.m_z; m[9] /= m_scale.m_z; m[10] /= m_scale.m_z;
    
	// extract the quaternion
	float A = 1.0f + m[0] - m[5] - m[10], S, X, Y, Z, W;
	if(A < 0.00001f)
		m_rotation.Set(0,0,0,1);
	else
	{
		S  = sqrt(A) * 2;
		if(m[0] > m[5] && m[0] > m[10])
		{
			X = 0.25f * S;
			Y = (m[4] + m[1] ) / S;
			Z = (m[2] + m[8] ) / S;
			W = (m[6] - m[9] ) / S;
		}
		else if( m[5] > m[10] )
		{
			X = (m[4] + m[1] ) / S;
			Y = 0.25f * S;
			Z = (m[9] + m[6] ) / S;
			W = (m[8] - m[2] ) / S;
		}
		else
		{
			X = (m[2] + m[8] ) / S;
			Y = (m[9] + m[6] ) / S;
			Z = 0.25f * S;
			W = (m[1] - m[4] ) / S;
		}
		m_rotation.Set(X,Y,Z,W);
	}
}

//////////////////////
//
// Invert the transform
//
void Transform::Invert(const Transform &T)
{
	float x, y, z;
	float ssvv, vr, s;
    
	// invert scale
	m_scale.m_x = 1.0f/T.m_scale.m_x;
	m_scale.m_y = 1.0f/T.m_scale.m_y;
	m_scale.m_z = 1.0f/T.m_scale.m_z;
    
	// invert rotation
	m_rotation.Invert(T.m_rotation);
    
	// invert translation
	m_position.m_x = -T.m_position.m_x;
	m_position.m_y = -T.m_position.m_y;
	m_position.m_z = -T.m_position.m_z;
    
    // translation * rotation
    x = m_position.m_x;
    y = m_position.m_y;
    z = m_position.m_z;
    
    ssvv = (m_rotation.m_w*m_rotation.m_w) - (m_rotation.m_x*m_rotation.m_x + m_rotation.m_y*m_rotation.m_y + m_rotation.m_z*m_rotation.m_z);
    vr = 2.0f*(m_rotation.m_x*x + m_rotation.m_y*y + m_rotation.m_z*z);
    s = 2.0f*m_rotation.m_w;
    
    
    m_position.m_x = (ssvv*m_position.m_x + vr*m_rotation.m_x + s*(m_rotation.m_y*z - m_rotation.m_z*y))*m_scale.m_x;
    m_position.m_y = (ssvv*m_position.m_y + vr*m_rotation.m_y + s*(m_rotation.m_z*x - m_rotation.m_x*z))*m_scale.m_y;
    m_position.m_z = (ssvv*m_position.m_z + vr*m_rotation.m_z + s*(m_rotation.m_x*y - m_rotation.m_y*x))*m_scale.m_z;
}

//////////////////////
//
// Set the position value of the transform
//
void Transform::SetPosition(const Vector& pos)
{
	m_position = pos;
}


//////////////////////
//
// Set the rotation value of the transform
//
void Transform::SetRotation(const Quaternion& rot)
{
	m_rotation = rot;
}

//////////////////////
//
// Set the scale value of the transform
//
void Transform::SetScale(const Vector& scale)
{
	m_scale = scale;
}

//////////////////////
//
// Create a transform from a camera eye, look and up parameter
//
void Transform::EyeLookUp(const Vector &eye, const Vector &look, const Vector &up)
{
	Vector x,y,z;
    
	z.Subtract(eye, look);
	z.Normalize();
	x.Cross(up, z);
	x.Normalize();
	y.Cross(z, x);
    
	m_position = eye;
	m_rotation.FromThreeVectors(x,y,z);
}

//////////////////////
//
// Multiply two transforms
//
void Transform::Multiply(const Transform &A, const Transform &B)
{
	float ssvv, vr, s;
	Quaternion rotation;
	Vector position;
    
	rotation.m_w = (A.m_rotation.m_w * B.m_rotation.m_w) - (A.m_rotation.m_x * B.m_rotation.m_x) -
    (A.m_rotation.m_y * B.m_rotation.m_y) - (A.m_rotation.m_z * B.m_rotation.m_z);
	rotation.m_x = (A.m_rotation.m_w * B.m_rotation.m_x) + (A.m_rotation.m_x * B.m_rotation.m_w) +
    (A.m_rotation.m_y * B.m_rotation.m_z) - (A.m_rotation.m_z * B.m_rotation.m_y);
	rotation.m_y = (A.m_rotation.m_w * B.m_rotation.m_y) + (A.m_rotation.m_y * B.m_rotation.m_w) +
    (A.m_rotation.m_z * B.m_rotation.m_x) - (A.m_rotation.m_x * B.m_rotation.m_z);
	rotation.m_z = (A.m_rotation.m_w * B.m_rotation.m_z) + (A.m_rotation.m_z * B.m_rotation.m_w) +
    (A.m_rotation.m_x * B.m_rotation.m_y) - (A.m_rotation.m_y * B.m_rotation.m_x);
    
    ssvv = (A.m_rotation.m_w*A.m_rotation.m_w) - (A.m_rotation.m_x*A.m_rotation.m_x + A.m_rotation.m_y*A.m_rotation.m_y + A.m_rotation.m_z*A.m_rotation.m_z);
    vr = 2.0f*(A.m_rotation.m_x*B.m_position.m_x + A.m_rotation.m_y*B.m_position.m_y + A.m_rotation.m_z*B.m_position.m_z);
    s = 2.0f*A.m_rotation.m_w;
    
	position.m_x = A.m_scale.m_x*((ssvv*B.m_position.m_x) + (vr*A.m_rotation.m_x) + (s*((A.m_rotation.m_y*B.m_position.m_z) - (A.m_rotation.m_z*B.m_position.m_y)))) + A.m_position.m_x;
    position.m_y = A.m_scale.m_y*((ssvv*B.m_position.m_y) + (vr*A.m_rotation.m_y) + (s*((A.m_rotation.m_z*B.m_position.m_x) - (A.m_rotation.m_x*B.m_position.m_z)))) + A.m_position.m_y;
    position.m_z = A.m_scale.m_z*((ssvv*B.m_position.m_z) + (vr*A.m_rotation.m_z) + (s*((A.m_rotation.m_x*B.m_position.m_y) - (A.m_rotation.m_y*B.m_position.m_x)))) + A.m_position.m_z;
    
	rotation.Normalize();
    
	m_position = position;
	m_rotation = rotation;
	m_scale.Multiply(A.m_scale, B.m_scale);
}



//////////////////////
//
// Extract the 4x4 matrix representation of the transform
//
void Transform::ExtractMatrix(Matrix &M) const
{
	float xx = m_rotation.m_x * m_rotation.m_x;
	float yy = m_rotation.m_y * m_rotation.m_y;
	float zz = m_rotation.m_z * m_rotation.m_z;
    
	float xy = m_rotation.m_x * m_rotation.m_y;
	float xz = m_rotation.m_x * m_rotation.m_z;
	float yz = m_rotation.m_y * m_rotation.m_z;
    
	float wx = m_rotation.m_w * m_rotation.m_x;
	float wy = m_rotation.m_w * m_rotation.m_y;
	float wz = m_rotation.m_w * m_rotation.m_z;
    
    
    
	M.m[0] = m_scale.m_x*(1.0f - 2.0f * (yy + zz));
	M.m[4] = m_scale.m_y*(2.0f * (xy - wz));
	M.m[8] = m_scale.m_z*(2.0f * (xz + wy));
    
	M.m[1] = m_scale.m_x*(2.0f * (xy + wz));
	M.m[5] = m_scale.m_y*(1.0f - 2.0f * (xx + zz));
	M.m[9] = m_scale.m_z*(2.0f * (yz - wx));
    
	M.m[2] = m_scale.m_x*(2.0f * (xz - wy));
	M.m[6] = m_scale.m_y*(2.0f * (yz + wx));
	M.m[10] = m_scale.m_z*(1.0f - 2.0f * (xx + yy));
    
	M.m[12] = (m_position.m_x);
	M.m[13] = (m_position.m_y);
	M.m[14] = (m_position.m_z);
    
	M.m[3] = 0.0f;
	M.m[7] = 0.0f;
	M.m[11] = 0.0f;
	M.m[15] = 1.0f;
}

//////////////////////
//
// Interpolate between two transforms
//
void Transform::Interpolate(const Transform &A, const Transform &B, float s)
{
	if(s < 0)
		s = 0;
	if(s > 1)
		s = 1;
	m_position.Interpolate(A.m_position, B.m_position, s);
	m_rotation.Interpolate(A.m_rotation, B.m_rotation, s);
	m_scale.Interpolate(A.m_scale, B.m_scale, s);
}

//////////////////////
//
// Extract the max scale factor on the transform
//
float Transform::GetMaxScale()
{
	if(m_scale.m_x >= m_scale.m_y && m_scale.m_x >= m_scale.m_z)
		return m_scale.m_x;
	else if(m_scale.m_y >= m_scale.m_x && m_scale.m_y >= m_scale.m_z)
		return m_scale.m_y;
	else
		return m_scale.m_z;
    
}

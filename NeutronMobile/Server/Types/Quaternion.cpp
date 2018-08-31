#define __COMPILING_NS_QUATERNION_CPP__
#include "Quaternion.h"
#undef __COMPILING_NS_QUATERNION_CPP__
 

using namespace Ns;
using namespace Ns::Core;

Quaternion::Quaternion() :
m_x(0.0),
m_y(0.0),
m_z(0.0),
m_w(1.0)
{
    
}

Quaternion::Quaternion(float x, float y, float z, float w) :
m_x(x),
m_y(y),
m_z(z),
m_w(w)
{
	Normalize();
}

//////////////////////
//
// Set the elements of the quaternion
//
void Quaternion::Set(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
	Normalize();
}

//////////////////////
//
// Set the elements of the quaternion from an angle/axis pair
//
void Quaternion::FromRotation(const Vector& axis, float angle)
{
    float s = (float)sin(angle * 0.5f);
    m_x = s * axis.m_x;
    m_y = s * axis.m_y;
    m_z = s * axis.m_z;
    m_w = (float)cos(angle * 0.5f);
    
    Normalize();
}


//////////////////////
//
// Get the axis and angle representation
//
void Quaternion::GetRotation(Vector &axis, float &theta)
{
	if ((m_w > COS_THRESH) || (m_w < -COS_THRESH))
	{
		theta = 0.0f;
		axis.m_x = 1.0f;
		axis.m_y = 0.0f;
		axis.m_z = 0.0f;
	}
	else
	{
		theta = 2.0f*acos(m_w);
        
		float len = sqrt((m_x*m_x) + (m_y*m_y) + (m_z*m_z));
		if (len < FY_EPSILON)
			axis.Set(1,0,0);
		else
		{
			axis.m_x = m_x/len;
			axis.m_y = m_y/len;
			axis.m_z = m_z/len;
		}
	}
}

//////////////////////
//
// Set the elements of the quaternion from based on a from and to vector
//
void Quaternion::FromTwoVectors(const Vector& a, const Vector& b)
{
	float fct = b.Dot(a);
    
	if(fct > COS_THRESH)
	{
		// the vectors are the same
		m_w = 1.0f;
		m_x = m_y = m_z = 0.0f;
	}
	else if(fct < -COS_THRESH)
	{
		// the vectors are opposing
		m_y = 1.0f;
		m_w = m_x = m_z = 0.0f;
	}
	else
	{
		Vector axis;
		axis.Cross(b, a);
		
		if(axis.MagnitudeSquared() < 0.000001f)
		{
			// the vectors are the same
			m_w = 1.0f;
			m_x = m_y = m_z = 0.0f;
		}
		else
		{
			axis.Normalize();
			FromRotation(axis, float(acos(fct)));
		}
	}
}


//////////////////////
//
// Set the elements of the quaternion from 3 axes vectors
//
void Quaternion::FromThreeVectors(const Vector& x, const Vector& y, const Vector& z)
{
	float x2, y2, w2 = (1 + x.m_x + y.m_y + z.m_z);
    
	if (w2 > FY_EPSILON)
	{
		m_w = 0.5f*(float)sqrt(w2);
		m_x = (y.m_z - z.m_y) / (4.0f * m_w);
		m_y = (z.m_x - x.m_z) / (4.0f * m_w);
		m_z = (x.m_y - y.m_x) / (4.0f * m_w);
	}
	else
	{
		m_w = 0.0f;
		x2 = -0.5f * (y.m_y + z.m_z);
        
		if (x2 > FY_EPSILON)
		{
			m_x = (float)sqrt(x2);
			m_y = y.m_x / (2.0f * m_x);
			m_z = z.m_x / (2.0f * m_x);
		}
		else
		{
			m_x = 0.0f;
			y2 = 0.5f * (1.0f - z.m_z);
            
			if (y2 > FY_EPSILON)
			{
				m_y = (float)sqrt(y2);
				m_z = z.m_y / (2.0f * m_y);
			}
			else
			{
				m_y = 0.0f;
				m_z = 1.0f;
			}
		}
	}
	Normalize();
}

//////////////////////
//
// Normalize the quaternion
//
void Quaternion::Normalize()
{
	float l = (float)sqrt(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
	m_x /= l;
	m_y /= l;
	m_z /= l;
	m_w /= l;
}

//////////////////////
//
// Multiply two quaternions together
//
void Quaternion::Multiply(const Quaternion &qa, const Quaternion &qb)
{
	float x, y, z, w;
	x =  qa.m_x * qb.m_w + qa.m_y * qb.m_z - qa.m_z * qb.m_y + qa.m_w * qb.m_x;
	y = -qa.m_x * qb.m_z + qa.m_y * qb.m_w + qa.m_z * qb.m_x + qa.m_w * qb.m_y;
	z =  qa.m_x * qb.m_y - qa.m_y * qb.m_x + qa.m_z * qb.m_w + qa.m_w * qb.m_z;
	w = -qa.m_x * qb.m_x - qa.m_y * qb.m_y - qa.m_z * qb.m_z + qa.m_w * qb.m_w;
	
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}


//////////////////////
//
// Correct the rotation to force the y axis of the rotation to be
// perpindicular to the x-z plane
//
bool Quaternion::MakeYUp(const Quaternion &tip)
{
	Vector y;
    
	y.Multiply(*this, Vector(0,1,0));
	y.m_z = 0;
	y.Normalize();
    
	Quaternion fix;
	
	fix.FromTwoVectors(Vector(0,1,0), y);
    
	Multiply(tip, *this);
	Multiply(fix, *this);
	Normalize();
    
    
	return true;
}


//////////////////////
//
// Extract the 4x4 matrix representation of the quaternion
//
void Quaternion::ExtractMatrix(Matrix &M) const
{
	float xx = m_x * m_x;
	float yy = m_y * m_y;
	float zz = m_z * m_z;
    
	float xy = m_x * m_y;
	float xz = m_x * m_z;
	float yz = m_y * m_z;
    
	float wx = m_w * m_x;
	float wy = m_w * m_y;
	float wz = m_w * m_z;
    
	M.m[0] = (1.0f - 2.0f * (yy + zz));
	M.m[4] = (2.0f * (xy - wz));
	M.m[8] = (2.0f * (xz + wy));
    
	M.m[1] = (2.0f * (xy + wz));
	M.m[5] = (1.0f - 2.0f * (xx + zz));
	M.m[9] = (2.0f * (yz - wx));
    
	M.m[2] = (2.0f * (xz - wy));
	M.m[6] = (2.0f * (yz + wx));
	M.m[10] = (1.0f - 2.0f * (xx + yy));
    
	M.m[12] = 0.0f;
	M.m[13] = 0.0f;
	M.m[14] = 0.0f;
    
	M.m[3] = 0.0f;
	M.m[7] = 0.0f;
	M.m[11] = 0.0f;
	M.m[15] = 1.0f;
}

//////////////////////
//
// Set the quaternion from euler angles
//
void Quaternion::SetEulerAngles(const Vector &e)
{
    float sx = (float)sin(e.m_x/2.0f);
    float sy = (float)sin(e.m_y/2.0f);
    float sz = (float)sin(e.m_z/2.0f);
    float cx = (float)cos(e.m_x/2.0f);
    float cy = (float)cos(e.m_y/2.0f);
    float cz = (float)cos(e.m_z/2.0f);
    
    m_x = cz*cy*sx - sz*sy*cx;
    m_y = cz*sy*cx + sz*cy*sx;
    m_z = sz*cy*cx - cz*sy*sx;
    m_w = cz*cy*cx + sz*sy*sx;
}

//////////////////////
//
// Extract the euler angles from the quaternion
//
void Quaternion::GetEulerAngles(Vector &e) const
{
	Matrix M;
    
	ExtractMatrix(M);
    
	float a, b, rx, ry, rz, cy;
    
	a = -M.m[2];
	b = (float)sqrt((M.m[0] * M.m[0]) + (M.m[1] * M.m[1]));
	ry = (float)atan2(a, b);
	cy = (float)cos(ry);
    
	if(ry < 0)
		ry += TWOPI;
    
	if(fyfastabs(cy) > FY_EPSILON)
	{
		rz = (float)atan2(M.m[1] / cy, M.m[0] / cy);
		rx = (float)atan2(M.m[6] / cy, M.m[10] / cy);
    }
    else
    {
		rz = 0.0f;
		if(ry > PI*0.5f)
			rx = -(float)atan2(M.m[4], M.m[5]);
		else
			rx = (float)atan2(M.m[4], M.m[5]);
	}
    
	if(rx < 0)
		rx += TWOPI;
	if(rz < 0)
		rz += TWOPI;
    
    e.Set(rx, ry, rz);
}

//////////////////////
//
// Interpolate between two quaternions (slerp)
//
void Quaternion::Interpolate(const Quaternion &A, const Quaternion &B, float s)
{
	if(s < 0)
		s = 0;
	if(s > 1)
		s = 1;
    
    
	float fScale1, fScale2, fCosTheta, fTheta, fSinTheta;
	float Ax, Ay, Az, Aw, Bx, By, Bz, Bw;
    
	fCosTheta = (A.m_x * B.m_x) + (A.m_y * B.m_y) + (A.m_z * B.m_z) + (A.m_w * B.m_w);
    
	if (fCosTheta < 0.0f)
	{
		Ax = -A.m_x; Ay = -A.m_y; Az = -A.m_z; Aw = -A.m_w;
		fCosTheta = -fCosTheta;
	}
	else
    {
		Ax = A.m_x; Ay = A.m_y; Az = A.m_z; Aw = A.m_w;
    }
    
    if ((fCosTheta + 1.0f) > 0.05f)
    {
		if ((1.0f - fCosTheta) < 0.05f)
		{
			fScale1 = 1.0f - s;
			fScale2 = s;
		}
		else
		{
			fTheta = (float)acos(fCosTheta);
			fSinTheta = (float)sin(fTheta);
			fScale1 = (float)sin(fTheta - (s * fTheta)) / fSinTheta;
			fScale2 = (float)sin(fTheta * s) / fSinTheta;
		}
        
		Bx = B.m_x;
		By = B.m_y;
		Bz = B.m_z;
		Bw = B.m_w;
	}
	else
	{
		Bx = -Ay;
		By =  Ax;
		Bz = -Aw;
		Bw =  Az;
        
		fScale1 = (float)sin(3.1415927f * (0.5f - s));
		fScale2 = (float)sin(3.1415927f * s);
	}
    
	m_x = (fScale1 * Ax) + (fScale2 * Bx);
	m_y = (fScale1 * Ay) + (fScale2 * By);
	m_z = (fScale1 * Az) + (fScale2 * Bz);
	m_w = (fScale1 * Aw) + (fScale2 * Bw);
}

//////////////////////
//
// Invert a quaternion
//
void Quaternion::Invert(const Quaternion &src)
{
	m_x = -src.m_x; 
	m_y = -src.m_y; 
	m_z = -src.m_z; 
	m_w =  src.m_w; 
}

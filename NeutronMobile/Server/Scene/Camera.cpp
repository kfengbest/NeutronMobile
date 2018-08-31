
#define __COMPILING_NS_CAMERA_CPP__
#include "Camera.h"
#undef __COMPILING_NS_CAMERA_CPP__

using namespace Ns::Scene;

Camera::Camera()
: m_spinning(false),
m_trackballRadius(),
m_screenSize(),
m_centerPoint(),
m_orientation()
{
    
}

Camera::~Camera()
{
    
}

void Camera::initialize(int width, int height)
{
    m_trackballRadius = width / 3;
    m_screenSize = ivec2(width, height);
    m_centerPoint = m_screenSize / 2;
}

void Camera::onFingerUp(ivec2 location)
{
    m_spinning = false;
}

void Camera::onFingerDown(ivec2 location)
{
    m_fingerStart = location;
    m_previousOrientation = m_orientation;

    m_spinning = true;
}

void Camera::onFingerMove(ivec2 oldLocation, ivec2 location)
{
    if (m_spinning) {
        vec3 start = mapToSphere(m_fingerStart);
        vec3 end = mapToSphere(location);
        Quaternionf delta = Quaternionf::CreateFromVectors(start, end);
        m_orientation = delta.Rotated(m_previousOrientation);
    }
    
}

vec3 Camera::mapToSphere(ivec2 touchpoint) const
{
    vec2 p = touchpoint - m_centerPoint;
    
    // Flip the Y axis because pixel coords increase towards the bottom.
    p.y = -p.y;
    
    const float radius = m_trackballRadius;
    const float safeRadius = radius - 1;
    
    if (p.Length() > safeRadius) {
        float theta = atan2(p.y, p.x);
        p.x = safeRadius * cos(theta);
        p.y = safeRadius * sin(theta);
    }
    
    float z = sqrt(radius * radius - p.LengthSquared());
    vec3 mapped = vec3(p.x, p.y, z);
    return mapped / radius;
}
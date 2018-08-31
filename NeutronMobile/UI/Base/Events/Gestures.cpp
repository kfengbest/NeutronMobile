#define __COMPILING_NU_GESTURE_CPP__
#include "Gestures.h"
#undef __COMPILING_NU_GESTURE_CPP__

using namespace Nu;
 
// ----------------------------------------------------------------------------
// Gesture
// ----------------------------------------------------------------------------
Gesture::Gesture()
{
}

Gesture::~Gesture()
{
}

// ----------------------------------------------------------------------------
// PanGesture
// ----------------------------------------------------------------------------

PanGesture::PanGesture()
	: Nu::Gesture(),
	m_delta(),
	m_hotspot()
{
}

PanGesture::~PanGesture()
{
}
 

Nu::PanGesture*
PanGesture::make()
{
	return new PanGesture();
}

float
PanGesture::delta() const
{
	return m_delta;
}

void 
PanGesture::delta(float deltaValue)
{
	m_delta = deltaValue;
}

float
PanGesture::hotSpot() const
{
	return m_hotspot;
}

void 
PanGesture::hotSpot(float hotSpot)
{
	m_hotspot = hotSpot;
}

// ----------------------------------------------------------------------------
// SwipeGesture
// ----------------------------------------------------------------------------

SwipeGesture::SwipeGesture(SwipeGesture::SwipeDirection hDirection, SwipeGesture::SwipeDirection vDirection)
	: Nu::Gesture(),
	m_hDirection(hDirection),
	m_vDirection(vDirection)
{
}

SwipeGesture::~SwipeGesture()
{
}

Nu::SwipeGesture*
	SwipeGesture::make(SwipeGesture::SwipeDirection hDirection, SwipeGesture::SwipeDirection vDirection)
{
	return new SwipeGesture(hDirection, vDirection);
}

SwipeGesture::SwipeDirection 
	SwipeGesture::horizontalDirection() const
{
	return m_hDirection;
}

SwipeGesture::SwipeDirection 
	SwipeGesture::verticalDirection() const
{
	return m_vDirection;
}

// ----------------------------------------------------------------------------
// PinchGesture
// ----------------------------------------------------------------------------

PinchGesture::PinchGesture()
: Gesture(),
m_changeFlags(Nu::PinchGesture::eNoneChanged),
m_scaleFactor(0.0f),
m_rotationAngle(0.0f)
{
}

PinchGesture::~PinchGesture()
{
}


Nu::PinchGesture*
	PinchGesture::make()
{
	return new PinchGesture();
}

Nu::PinchGesture::EChangeFlag 
PinchGesture::changeFlags() const
{
	return m_changeFlags;
}

void 
PinchGesture::changeFlags(PinchGesture::EChangeFlag flags)
{
	m_changeFlags = flags;
}

float
PinchGesture::scaleFactor() const
{
	return m_scaleFactor;
}

void 
PinchGesture::scaleFactor(float factor)
{
	m_scaleFactor = factor;
}

float
PinchGesture::rotationAngle() const
{
	return m_rotationAngle;
}

void 
PinchGesture::rotationAngle(float angle)
{
	m_rotationAngle = angle;
}

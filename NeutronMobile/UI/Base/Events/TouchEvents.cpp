#define __COMPILING_NU_TOUCHEVENTS_CPP__
#include "TouchEvents.h"
#undef __COMPILING_NU_TOUCHEVENTS_CPP__

using namespace Nu;

TouchEvent::TouchEvent(const Touches& touches, ETiming timing)
	: Event(timing),
	  m_touches(touches)
{
}

const Touches&
TouchEvent::touches() const
{
	return m_touches;
}

Touch* TouchEvent::anyTouch()
{
 return *(m_touches.begin());
}
#define __COMPILING_NU_GESTUREEVENTS_CPP__
#include "GestureEvents.h"
#undef __COMPILING_NU_GESTUREEVENTS_CPP__
 
#include "Gestures.h"

using namespace Nu;

GestureEvent::GestureEvent(Gesture* pGesture, ETiming timing)
: Ns::Event(timing),
    m_pGesture(pGesture)
{
}

GestureEvent::~GestureEvent()
{

}

Gesture*
GestureEvent::gesture() const
{
	return m_pGesture;
}
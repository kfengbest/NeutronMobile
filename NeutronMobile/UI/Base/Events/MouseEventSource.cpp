#define __COMPILING_NU_MOUSEEVENTSOURCE_CPP__
#include "MouseEventSource.h"
#undef __COMPILING_NU_MOUSEEVENTSOURCE_CPP__
 
#include "MouseEvents.h"
#include "MouseEventSite.h"

using namespace Ns;
using namespace Nu;

MouseEventSource::MouseEventSource()
	: EventSource()
{
}


MouseEventSource::~MouseEventSource()
{
}


MouseEventSource*
MouseEventSource::get()
{
	static MouseEventSource s_theOneAndOnly;
	return &s_theOneAndOnly;
}


void
MouseEventSource::subscribe(MouseEventSite* pSite)
{
	EventSource::subscribe(pSite);
}


void
MouseEventSource::unsubscribe(MouseEventSite* pSite)
{
	EventSource::unsubscribe(pSite);
}

void
MouseEventSource::fireMouseDown(const MouseEvent* pEvent)
{
	EventSource::fireEvent(&MouseEventSite::mouseDown, pEvent);
}


void
MouseEventSource::fireMouseMove(const MouseEvent* pEvent)
{
	EventSource::fireEvent(&MouseEventSite::mouseMove, pEvent);


}


void
MouseEventSource::fireMouseUp(const MouseEvent* pEvent)
{
	EventSource::fireEvent(&MouseEventSite::mouseUp, pEvent);
}

void
MouseEventSource::fireMouseEnter(const MouseEvent* pEvent)
{
	EventSource::fireEvent(&MouseEventSite::mouseEnter, pEvent);
}

void
MouseEventSource::fireMouseLeave(const MouseEvent* pEvent)
{
	EventSource::fireEvent(&MouseEventSite::mouseLeave, pEvent);
}


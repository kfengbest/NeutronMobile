#define __COMPILING_NU_TOUCHEVENTSOURCE_CPP__
#include "TouchEventSource.h"
#undef __COMPILING_NU_TOUCHEVENTSOURCE_CPP__

#include "TouchEvents.h"
#include "TouchEventSite.h"

using namespace Ns;
using namespace Nu;


TouchEventSource::TouchEventSource()
	: EventSource()
{
}

TouchEventSource::~TouchEventSource()
{
}

TouchEventSource*
TouchEventSource::get()
{
	static TouchEventSource s_theOneAndOnly;
	return &s_theOneAndOnly;
}

void
TouchEventSource::subscribe(TouchEventSite* pSite)
{
	EventSource::subscribe(pSite);
}

void
TouchEventSource::unsubscribe(TouchEventSite* pSite)
{
	EventSource::unsubscribe(pSite);
}

void
TouchEventSource::fireTouchPress(TouchEvent* pEvent)
{
	EventSource::fireEvent(&TouchEventSite::touchPress, pEvent);
}
void
TouchEventSource::fireTouchMove(TouchEvent* pEvent)
{
	EventSource::fireEvent(&TouchEventSite::touchMove, pEvent);
}

void
TouchEventSource::fireTouchStationary(TouchEvent* pEvent)
{
	EventSource::fireEvent(&TouchEventSite::touchStationary, pEvent);
}

void
TouchEventSource::fireTouchRelease(TouchEvent* pEvent)
{
	EventSource::fireEvent(&TouchEventSite::touchRelease, pEvent);
}

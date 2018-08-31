#define __COMPILING_NU_GESTUREEVENTSOURCE_CPP__
#include "GestureEventSource.h"
#undef __COMPILING_NU_GESTUREEVENTSOURCE_CPP__
 
#include "GestureEvents.h"
#include "GestureEventSite.h"

using namespace Ns;
using namespace Nu;


GestureEventSource::GestureEventSource()
	: EventSource()
{
}

GestureEventSource::~GestureEventSource()
{
}

GestureEventSource*
GestureEventSource::get()
{
	static GestureEventSource s_theOneAndOnly;
	return &s_theOneAndOnly;
}

void
GestureEventSource::subscribe(GestureEventSite* pSite)
{
	EventSource::subscribe(pSite);
}

void
GestureEventSource::unsubscribe(GestureEventSite* pSite)
{
	EventSource::unsubscribe(pSite);
}

void
GestureEventSource::fireGestureBegin(GestureEvent* pEvent)
{
    EventSource::fireEvent(&GestureEventSite::gestureBegin, pEvent);
}

void
	GestureEventSource::fireGestureUpdated(GestureEvent* pEvent)
{
	EventSource::fireEvent(&GestureEventSite::gestureUpdated, pEvent);
}

void
	GestureEventSource::fireGestureEnd(GestureEvent* pEvent)
{
	EventSource::fireEvent(&GestureEventSite::gestureEnd, pEvent);
}

void
GestureEventSource::fireGestureCanceled(GestureEvent* pEvent)
{
	EventSource::fireEvent(&GestureEventSite::gestureCanceled, pEvent);
}

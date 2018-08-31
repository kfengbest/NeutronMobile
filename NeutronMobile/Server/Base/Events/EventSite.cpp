#define __COMPILING_NS_EVENTSITE_CPP__
#include "EventSite.h"
#undef __COMPILING_NS_EVENTSITE_CPP__
 
#include "EventSource.h"

using namespace Ns;

EventSite::EventSite()
{
	m_eventSource = NULL;
}

EventSite::~EventSite()
{
	if (NULL != m_eventSource)
	{
		m_eventSource->destructing(this);
		m_eventSource = NULL;
	}
}

Ns::HString EventSite::toString() const
{
	return this->onToString();
}

EventSource* EventSite::eventSource() const
{
	return m_eventSource;
}

Ns::HString EventSite::onToString() const
{
	return _DNGH("EventSite");
}

void EventSite::eventSource(EventSource* eventSource)
{
	m_eventSource = eventSource;
}

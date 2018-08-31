#define __COMPILING_NS_EVENTS_CPP__
#include "EventSource.h"
#undef __COMPILING_NS_EVENTS_CPP__

#include "../Assert/Assert.h"
#include "EventSite.h"
 
using namespace Ns;


EventSource::EventSource()
	: m_queue(false)
{
}

EventSource::~EventSource()
{
    EventSites::iterator itb = m_sites.begin();
    EventSites::iterator ite = m_sites.end();
    for (; itb != ite; ++itb) {
        (*itb)->eventSource(NULL);
    }
}

Ns::HString EventSource::toString() const
{
	return this->onToString();
}

const EventSource::EventSites* EventSource::sites() const
{
	return &m_sites;
}

Ns::HString EventSource::onToString() const
{
	return _DNGH("EventSource");
}

void EventSource::subscribe(EventSite* site)
{
	if (m_queue)
	{
		m_queuedAdditions.insert(site);
	} else {
		site->eventSource(this);
		m_sites.insert(site);
	}
}

void EventSource::unsubscribe(EventSite* site)
{
	if (m_queue)
	{
		site->eventSource(NULL);
		m_queuedRemovals.insert(site);
	} else {

		m_sites.erase(site);
		site->eventSource(NULL);
	}
}

void EventSource::destructing(EventSite* site)
{
	m_sites.erase(site);
}

void
EventSource::queueBegin()
{
	m_queue = true;
}

void
EventSource::queueEnd()
{

	// Flush...
	m_queue = false;
	for (Ns::EventSource::EventSites::const_iterator itr = m_queuedRemovals.begin();
		 itr != m_queuedRemovals.end(); 
		 ++itr )
	{
		m_sites.erase(*itr);
	}
	m_queuedRemovals.clear();
	for (Ns::EventSource::EventSites::const_iterator itr = m_queuedAdditions.begin();
		 itr != m_queuedAdditions.end(); 
		 ++itr )
	{
		this->subscribe(*itr);
	}
	m_queuedAdditions.clear();
}
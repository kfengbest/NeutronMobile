#pragma once

// ------------------------------------------------------------
// Events is a base class for all categorizations of events
// supported in the system.  A concrete class must be derived
// from this class.  Events classes should always be singletons
// that provide static methods for accessing them.  Events
// classes provide methods for sending events, and maintain a
// list of EventSites that are recpients of these events.
// ------------------------------------------------------------
 
#include "../Assert/Assert.h"
#include "../Globals.h"
#include <set>

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_EVENTS_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns {

	class EventSite;

	class NS_BASE_API EventSource
	{
	public:
		typedef std::set<EventSite*> EventSites;

	protected:
		EventSource();
		virtual ~EventSource();

	public:
		Ns::HString				toString() const;
		const EventSites*		sites() const;

	protected:
		virtual Ns::HString		onToString() const;
		void					subscribe(EventSite* site);
		void					unsubscribe(EventSite* site);

	protected:
		template<typename TEventSite, typename TEvent>
		void fireEvent(void (TEventSite::*fire)(TEvent* event),
					   TEvent* event);

	friend class EventSite;
	private:
		// Notifies this source that a client site is going out of scope...
		void destructing(EventSite* site);

		// Begins queueing additions and removals.  All changes are pending.
		void queueBegin();

		// Ends queueing additions and removals and makes the changes.
		void queueEnd();

	private:
		EventSites m_sites;
		EventSites m_queuedAdditions;
		EventSites m_queuedRemovals;
		bool m_queue;
	}; 

	template<typename TEventSite, typename TEvent>
	inline void
	EventSource::fireEvent(void (TEventSite::*fire)(TEvent* event),
						   TEvent* event)
	{
		// Queue additions / removals so that we don't modify the
		// list as it's being fired...
		this->queueBegin();
		for (Ns::EventSource::EventSites::const_iterator itr = sites()->begin();
			 itr != sites()->end(); 
			 ++itr )
		{
			TEventSite* appSite = dynamic_cast<TEventSite*>(*itr);
			(appSite->*fire)( event );
		}
		this->queueEnd();
	}

}

#undef NS_BASE_API

#pragma once

// ------------------------------------------------------------
// EventSite is a base class for all sites.  An EventSite is
// a declaration of events that an 'Events' class supports.
// ------------------------------------------------------------
 
#include "../Globals.h"

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_EVENTSITE_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns {

	class EventSource;

	class NS_BASE_API EventSite 
	{
	protected:
		EventSite();
		virtual ~EventSite();

	public:
		Ns::HString				toString() const;
		EventSource*			eventSource() const;

	protected:
		virtual Ns::HString		onToString() const;

	friend class EventSource;
	private:
		void					eventSource(EventSource* eventSource);

	private:
		EventSource*			m_eventSource;
	}; 
}

#undef NS_BASE_API

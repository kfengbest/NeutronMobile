#pragma once

// ------------------------------------------------------------
// Event repressents the base class for all event notifications
// sent.  The event class must be subclassed by a concrete class.
// Events are fired from 'Events' objects and received by
// 'EventSite' objects
// ------------------------------------------------------------

#include "../Globals.h"

#ifdef NS_BASE_EXPORTS
# ifdef __COMPILING_NS_EVENT_CPP__
#  define NS_BASE_API NS_EXPORT
# else
#  define NS_BASE_API
# endif
#else
# define NS_BASE_API NS_IMPORT
#endif

namespace Ns {

	class NS_BASE_API Event 
	{
	public:
		enum ETiming 
		{
			eNone,
			eBefore,
			eAfter
		};

	protected:
		Event(ETiming timing = Event::eNone);
		virtual ~Event();
		Event(const Event&);

	public:
		void					accept();
		bool					accepted() const;
		void					ignore();
		ETiming					timing() const;
		void					timing(ETiming timing);
		Ns::HString				toString() const;

	protected:
		virtual Ns::HString		onToString() const;

	private:
		ETiming					m_timing;
		bool					m_accepted;
	}; 
}

#undef NS_BASE_API



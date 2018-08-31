#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/EventSite.h"

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_TOUCHEVENTSITE_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class TouchEvent;

	class NU_BASE_API TouchEventSite : public Ns::EventSite
	{
	protected:
		TouchEventSite();
		virtual ~TouchEventSite();

	friend class TouchEventSource;
	protected:

		// The touch point is now pressed...
		virtual void touchPress(TouchEvent* pEvent) {};

		// The touch point is now moved...
		virtual void touchMove(TouchEvent* pEvent) {};

		// The touch point did not move...
		virtual void touchStationary(TouchEvent* pEvent) {};

		// The touch point was released...
		virtual void touchRelease(TouchEvent* pEvent) {};

	};

}

#undef NU_BASE_API



#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/EventSite.h"
 
#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_GESTUREEVENTSITE_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class GestureEvent;

	class NU_BASE_API GestureEventSite : public Ns::EventSite
	{
	protected:
		GestureEventSite();
		virtual ~GestureEventSite();

	friend class GestureEventSource;
	protected:

		virtual void gestureBegin(GestureEvent* pEvent) {};
		virtual void gestureUpdated(GestureEvent* pEvent) {};
		virtual void gestureEnd(GestureEvent* pEvent) {};
		virtual void gestureCanceled(GestureEvent* pEvent) {};

	};

}

#undef NU_BASE_API



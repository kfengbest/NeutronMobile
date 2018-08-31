#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/EventSource.h"
 
#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_GESTUREEVENTSOURCE_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class GestureEvent;
	class GestureEventSite;

	class NU_BASE_API GestureEventSource : public Ns::EventSource
	{
	protected:
		GestureEventSource();
		virtual ~GestureEventSource();

	public:
		static GestureEventSource* get();

		void subscribe(GestureEventSite* pSite);
		void unsubscribe(GestureEventSite* pSite);

		void fireGestureBegin(GestureEvent* pEvent);
		void fireGestureUpdated(GestureEvent* pEvent);
		void fireGestureEnd(GestureEvent* pEvent);
		void fireGestureCanceled(GestureEvent* pEvent);
	};
}

#undef NU_BASE_API

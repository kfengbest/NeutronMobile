#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/EventSource.h"

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_TOUCHEVENTSOURCE_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class TouchEvent;
	class TouchEventSite;

	class NU_BASE_API TouchEventSource : public Ns::EventSource
	{
	protected:
		TouchEventSource();
		virtual ~TouchEventSource();

	public:
		static TouchEventSource* get();

		void subscribe(TouchEventSite* pSite);
		void unsubscribe(TouchEventSite* pSite);

		void fireTouchPress(TouchEvent* pEvent);
		void fireTouchMove(TouchEvent* pEvent);
		void fireTouchStationary(TouchEvent* pEvent);
		void fireTouchRelease(TouchEvent* pEvent);

	};
}

#undef NU_BASE_API

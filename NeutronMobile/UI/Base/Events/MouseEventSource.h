#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/EventSource.h"

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_MOUSEEVENTSOURCE_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class MouseEvent;
	class MouseEventSite;

	class NU_BASE_API MouseEventSource : public Ns::EventSource
	{
	protected:
		MouseEventSource();
		virtual ~MouseEventSource();

	public:
		static MouseEventSource* get();

		void subscribe(MouseEventSite* pSite);
		void unsubscribe(MouseEventSite* pSite);

		void fireMouseDown(const MouseEvent* pEvent);
		void fireMouseMove(const MouseEvent* pEvent);
		void fireMouseUp(const MouseEvent* pEvent);

		void fireMouseEnter(const MouseEvent* pEvent);
		void fireMouseLeave(const MouseEvent* pEvent);
	};
}

#undef NU_BASE_API

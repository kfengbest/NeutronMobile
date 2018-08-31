#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/EventSite.h"

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_MOUSEEVENTSITE_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class MouseEvent;

	class NU_BASE_API MouseEventSite : public Ns::EventSite
	{
	protected:
		MouseEventSite();
		virtual ~MouseEventSite();

	friend class MouseEventSource;
	protected:
		virtual void mouseDown(const MouseEvent* pEvent) {};
		virtual void mouseMove(const MouseEvent* pEvent) {};
		virtual void mouseUp(const MouseEvent* pEvent) {};
		virtual void mouseEnter(const MouseEvent* pEvent) {};
		virtual void mouseLeave(const MouseEvent* pEvent) {};
	};

}

#undef NU_BASE_API



#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/Event.h"

#include "Touch.h"

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_TOUCHEVENTS_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class NU_BASE_API TouchEvent : public Ns::Event
	{
	public:
		TouchEvent(const Touches& touches, ETiming timing = Event::eNone);

		const Touches& touches() const;
        Touch* anyTouch();
        
	private:
		Touches m_touches;
	};

}

#undef NU_BASE_API

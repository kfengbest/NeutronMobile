#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/Event.h"
#include "Gestures.h"

#ifdef NU_BASE_EXPORTS 
# ifdef __COMPILING_NU_GESTUREEVENTS_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class Gesture;

	class NU_BASE_API GestureEvent : public Ns::Event
	{
	public:
		GestureEvent(Nu::Gesture* pGesture, ETiming timing = Event::eNone);
		virtual ~GestureEvent();

		Gesture* gesture() const;

	private:
		Nu::Gesture* m_pGesture;
	};

}

#undef NU_BASE_API

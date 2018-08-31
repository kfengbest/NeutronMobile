#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Base/Events/Event.h"
#include "../../../Server/Types/Point2.h"
 
#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_MOUSEEVENTS_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class Control;

	class NU_BASE_API MouseEvent : public Ns::Event
	{
	public:
		enum EButtonMask
		{
			eButtonNone		= 0x0,
			eButtonLeft		= 0x1,
			eButtonRight	= 0x2,
			eButtonMiddle	= 0x4,
		};

		enum EType
		{
			eDown, eMove, eUp, eEnter, eLeave
		};

	public:
		MouseEvent(Control *pSender, EType type, int button, int buttonMask, int modifierMask,
			int clickCount, const Ns::Core::ScreenPoint2 &pos,
				   ETiming timing = Event::eNone);
		virtual ~MouseEvent();

		EType				type() const;
		int					button() const;
		int					buttonMask() const;
		int					modifierMask() const;
		int					clickCount() const;
		const Ns::Core::ScreenPoint2&	position() const;
		Control*			sender() const;

		bool				isFirstDown() const;
		bool				isFirstDown(EButtonMask button) const;

		bool				isLastUp() const;
		bool				isLastUp(EButtonMask button) const;

	private:
		Control*			m_pSender;
		EType				m_type;
		int					m_button;
		int					m_buttonMask;
		int					m_modifierMask;
		int					m_clickCount;
		Ns::Core::ScreenPoint2			m_pos;
	};

}

#undef NU_BASE_API

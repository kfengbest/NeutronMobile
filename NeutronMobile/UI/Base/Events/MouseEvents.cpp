#define __COMPILING_NU_MOUSEEVENTS_CPP__
#include "MouseEvents.h"
#undef __COMPILING_NU_MOUSEEVENTS_CPP__
 
using namespace Nu;

MouseEvent::MouseEvent(Control *pSender, EType type, int button, int buttonMask, int modifierMask,
					   int clickCount, const Ns::Core::ScreenPoint2& pos,
					   ETiming timing)
	: Event(timing),
	  m_pSender(pSender),
	  m_type(type),
	  m_button(button),
	  m_buttonMask(buttonMask),
	  m_modifierMask(modifierMask),
	  m_clickCount(clickCount),
	  m_pos(pos)
{
}

MouseEvent::~MouseEvent()
{
}

MouseEvent::EType
MouseEvent::type() const
{
	return m_type;
}


int
MouseEvent::button() const
{
	return m_button;
}


int
MouseEvent::buttonMask() const
{
	return m_buttonMask;
}


int
MouseEvent::modifierMask() const
{
	return m_modifierMask;
}


int
MouseEvent::clickCount() const
{
	return m_clickCount;
}


const Ns::Core::ScreenPoint2&
MouseEvent::position() const
{
	return m_pos;
}

Control*
MouseEvent::sender() const
{
	return m_pSender;
}

bool
MouseEvent::isFirstDown() const
{
	return
		type() == eDown &&
		buttonMask() == button();
}


bool
MouseEvent::isFirstDown(EButtonMask button_) const
{
	return isFirstDown() &&
		button() == button_;
}


bool
MouseEvent::isLastUp() const
{
	return
		type() == eUp &&
		buttonMask() == eButtonNone;

}


bool
MouseEvent::isLastUp(EButtonMask button_) const
{
	return isLastUp() &&
		button() == button_;
}
#define __COMPILING_NS_EVENT_CPP__
#include "Event.h"
#undef __COMPILING_NS_EVENT_CPP__
 
 
using namespace Ns;


Event::Event(ETiming timing)
{
	m_timing = timing;
	m_accepted = false;
}

Event::~Event()
{
}

Event::Event(const Event& other)
	: m_timing(other.m_timing),
	  m_accepted(other.m_accepted)
{
}

void Event::accept()
{
	m_accepted = true;
}

bool Event::accepted() const
{
	return m_accepted;
}

void Event::ignore()
{
	m_accepted = false;
}

Event::ETiming Event::timing() const
{
	return m_timing;
}

void Event::timing(Event::ETiming timing)
{
	m_timing = timing;
}

Ns::HString Event::toString() const
{
	return this->onToString();
}

Ns::HString Event::onToString() const
{
	switch(timing())
	{
	case Event::eBefore:	return _DNGH("Before");
	case Event::eAfter:		return _DNGH("After");
	default:				return _DNGH("None");
	}
}

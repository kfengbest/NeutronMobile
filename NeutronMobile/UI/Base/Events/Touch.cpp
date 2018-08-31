
#define __COMPILING_NU_TOUCH_CPP__
#include "Touch.h"
#undef __COMPILING_NU_TOUCH_CPP__


using namespace Nu;

Touch::Touch( Ns::int32 id,
	const Touch::TouchPoint& pos,
	const Touch::TouchPoint& prevPos,
	Ns::int32 tapCount,
	Touch::TouchPhase phase,
	double timestamp )
: m_id(id),
m_pos(pos),
m_prevPos(prevPos),
m_phase(phase),
m_tapCount(tapCount),
m_timestamp(timestamp)
{
}

Touch::~Touch()
{

}

Ns::int32 
Touch::id() const
{
	return m_id;
}

const Touch::TouchPoint& 
Touch::position() const
{
	return m_pos;
}

const Touch::TouchPoint& 
Touch::previousPosition() const
{
	return m_prevPos;
}

Touch::TouchPhase 
Touch::touchPhase() const
{
	return m_phase;
}

Ns::int32 
Touch::tapCount() const
{
	return m_tapCount;
}

double 
Touch::timestamp() const
{
	return m_timestamp;
}
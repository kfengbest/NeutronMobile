#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Types/Point2.h"

#include <Set>

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_TOUCH_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class Touch;
	
	typedef std::set<Touch*> Touches;

	class NU_BASE_API Touch 
	{
        
	public:
		typedef Ns::Core::Point2 TouchPoint;

		enum TouchPhase
		{
			eTouchUnknown,
			eTouchPress,
			eTouchMove,
			eTouchStationary,
			eTouchRelease,
			eTouchCancelled
		};

		Touch(	Ns::int32 id,
				const TouchPoint& pos,
				const TouchPoint& prevPos,
				Ns::int32 tapCount,
				TouchPhase phase,
				double timestamp );
		~Touch();

	public:
		Ns::int32 id() const;
		const TouchPoint& position() const;
		const TouchPoint& previousPosition() const;
		TouchPhase touchPhase() const;
		Ns::int32 tapCount() const;
		double timestamp() const;

	private:
        Ns::int32			m_id;
		Touch::TouchPoint	m_pos;
		Touch::TouchPoint	m_prevPos;
		Touch::TouchPhase	m_phase;
		Ns::int32			m_tapCount;
		double				m_timestamp;
	};
}

#undef NU_BASE_API

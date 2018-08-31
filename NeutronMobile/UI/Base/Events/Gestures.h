#pragma once

#include "../../../Server/Base/Globals.h"
#include "../../../Server/Types/Point2.h"

#ifdef NU_BASE_EXPORTS
# ifdef __COMPILING_NU_GESTURE_CPP__
#  define NU_BASE_API NS_EXPORT
# else
#  define NU_BASE_API
# endif
#else
# define NU_BASE_API NS_IMPORT
#endif

namespace Nu {

	class NU_BASE_API Gesture
	{
	private:
		Gesture(const Gesture& src);
		Gesture& operator=(const Gesture& rhs);

	protected:
		Gesture();
		virtual~Gesture();

	};

	class NU_BASE_API PanGesture : public Nu::Gesture
	{
	private:
		PanGesture(const PanGesture& src);
		PanGesture& operator=(const PanGesture& rhs);

	public:
		
		static Nu::PanGesture* make();

		float delta() const;
		void delta(float deltaValue);
		
        float hotSpot() const;
		void hotSpot(float hotSpot);
		
	protected:
		PanGesture();
		virtual ~PanGesture();
	
	private:
		float m_delta;
		float m_hotspot;
	};

	class NU_BASE_API SwipeGesture : public Nu::Gesture
	{
	public:
		enum SwipeDirection 
		{
			eNoDirection, 
			eLeft, 
			eRight, 
			eUp, 
			eDown 
		};

	private:
		SwipeGesture(const SwipeGesture& src);
		SwipeGesture& operator=(const SwipeGesture& rhs);
		
	public:
 
		
		static Nu::SwipeGesture* make( SwipeGesture::SwipeDirection hDirection = SwipeGesture::eNoDirection, 
														SwipeGesture::SwipeDirection vDirection  = SwipeGesture::eNoDirection);

		SwipeGesture::SwipeDirection horizontalDirection() const;
		SwipeGesture::SwipeDirection verticalDirection() const;

	protected:

		SwipeGesture(SwipeGesture::SwipeDirection hDirection, SwipeGesture::SwipeDirection vDirection);
		virtual ~SwipeGesture();

	private:
		SwipeGesture::SwipeDirection m_hDirection;
		SwipeGesture::SwipeDirection m_vDirection;

	};

	class NU_BASE_API PinchGesture : public Nu::Gesture
	{
	public:
		enum EChangeFlag
		{
			eNoneChanged			= 0x0,
			eScaleFactorChanged		= 0x1,
			eRotationAngleChanged	= 0x2
		};

	private:
		PinchGesture(const PinchGesture& src);
		PinchGesture& operator=(const PinchGesture& rhs);

	public:
 
		
		static Nu::PinchGesture* make();
		
		PinchGesture::EChangeFlag changeFlags() const;
		void changeFlags(PinchGesture::EChangeFlag flags);
		
		float scaleFactor() const;
		void scaleFactor(float factor);
		
		float rotationAngle() const;
		void rotationAngle(float angle);
		
	protected:
		PinchGesture();
		virtual ~PinchGesture();
		
	private:
		Nu::PinchGesture::EChangeFlag m_changeFlags;
		float m_scaleFactor;
		float m_rotationAngle;

	};

}

#undef NU_BASE_API

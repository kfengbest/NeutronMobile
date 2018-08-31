#pragma once

// Color contains RGB and Alpha values in it

#include "../Base/Globals.h"

#ifdef NS_TYPES_EXPORTS
#ifdef __COMPILING_NS_COLOR_CPP__
#define NS_TYPES_API NS_EXPORT
#else
#define NS_TYPES_API
#endif
#else
#define NS_TYPES_API NS_IMPORT
#endif

namespace Ns { namespace Core {

	class Color
	{
		// Copy constructors and assignment operators work great.
	public:
		Color();
		// Valid argument range is 0.0 - 1.0
		Color(float r, float g, float b, float a);
		~Color();	// No derivation, value class.

		float red() const;
		float green() const;
		float blue() const;
		float alpha() const;

		void red(float val);
		void green(float val);
		void blue(float val);
		void alpha(float val);

		// Return value for a valid color is 0-255
		int redAsInt() const;
		int greenAsInt() const;
		int blueAsInt() const;
		int alphaAsInt() const;

		Color operator * (double) const;

		//Ns::IString toString() const;	// For debug

		//// Returns a string representation of all four fields 
		//// (red, green, blue, alpha) with the pound sign in front
		//// such as the following: '#336699CC'.
		//Ns::IString toHex(bool includeAlpha = true) const;

		//// Constructs a color from a hex string sequence.  The 
		//// algorithm takes the first 4 hexidecimal number
		//// pairs it finds regardless of string annotation.  So
		//// valid inputs are: FF, CCFF, 33B, 336699, #336699, etc.
		//static Color fromHex(const Ns::HString& value);

		// Returns a random color.
		static Color random();

		// Returns true if the color is valid; otherwise returns false.
		bool isValid() const;

		//bool operator==(const Color& rhs) const;
		//bool operator!=(const Color& rhs) const;


	private:
		float	m_red;
		float	m_green;
		float	m_blue;
		float	m_alpha;
	};

}}

#undef NS_SCENE_API
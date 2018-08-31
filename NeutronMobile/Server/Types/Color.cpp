
#define __COMPILING_NS_COLOR_CPP__
#include "Color.h"
#undef __COMPILING_NS_COLOR_CPP__

using namespace Ns::Core;

Color::Color()
: m_red(0.0f), m_green(0.0f), m_blue(0.0f), m_alpha(1.0f)
{
}

Color::Color(float r, float g, float b, float a)
: m_red(r), m_green(g), m_blue(b), m_alpha(a)
{
}

Color::~Color()
{}

float Color::red() const		{ return m_red; }
float Color::green() const		{ return m_green; }
float Color::blue() const		{ return m_blue; }
float Color::alpha() const		{ return m_alpha; }

void Color::red(float val)		{ m_red = val; }
void Color::green(float val)	{ m_green = val; }
void Color::blue(float val)		{ m_blue = val; }
void Color::alpha(float val)	{ m_alpha = val; }

int Color::redAsInt() const			{ return (int)(m_red * 255.0); }
int Color::greenAsInt() const		{ return (int)(m_green * 255.0); }
int Color::blueAsInt() const		{ return (int)(m_blue * 255.0); }
int Color::alphaAsInt() const		{ return (int)(m_alpha * 255.0); }

Color
Color::operator*(double d) const
{
	float f = static_cast<float>(d);
	return Color(red()*f, green()*f, blue()*f, alpha());
}
//
//IString Color::toString() const
//{
//	IString strText = (boost::wformat(_DNGI("(Red: %1%, Green: %2%, Blue: %3%, Alpha: %4%)"))
//		%red() %green() %blue() %alpha()).str();
//	return strText;
//}
//
//IString
//Color::toHex(bool includeAlpha) const
//{
//	IString result;
//	if (includeAlpha) {
//		result = (boost::wformat(_DNGI("%#1$02X%2$02X%3$02X%4$02X")) %this->redAsInt() %this->greenAsInt() %this->blueAsInt() %this->alphaAsInt()).str();
//	} else {
//		result = (boost::wformat(_DNGI("#%1$02X%2$02X%3$02X")) %this->redAsInt() %this->greenAsInt() %this->blueAsInt()).str();
//	}
//
//	return result;
//}
//
//Color
//Color::fromHex(const Ns::HString &value)
//{
//	Color result(0, 0, 0, 1);
//
//	static boost::regex exp(_DNGH("[0-9A-Fa-f]{2,2}"));
//	Ns::HString::const_iterator start = value.begin();
//	Ns::HString::const_iterator stop = value.end();
//	boost::smatch results;
//	int ndx = 0;
//	while (boost::regex_search(start, stop, results, exp) && (ndx < 4))
//	{
//		int hexValue;
//		Ns::HString hexCode = results[0];
//		int rc = sscanf(hexCode.c_str(), _DNGH("%x"), &hexValue);
//		float param = (hexValue / 255.0f);
//		switch(ndx)
//		{
//			case 0:	result.red(param);		break;
//			case 1:	result.green(param);	break;
//			case 2:	result.blue(param);		break;
//			case 3:	result.alpha(param);	break;
//
//		}
//		start = results[0].second;
//		ndx++;
//	}
//
//	return result;
//}

Color
Color::random()
{
	Color result(0, 0, 0, 1);

	//typedef boost::variate_generator<boost::mt19937&, boost::uniform_int<> > int_gen_type;
	//static boost::mt19937 rng(37u);
	//static boost::uniform_int<> twoHundredAndFiftySix(0, 255);
	//static int_gen_type gen(rng, twoHundredAndFiftySix);

	//int nRed = gen();
	//int nGreen = gen();
	//int nBlue = gen();

	//result.red(nRed / 256.0f);
	//result.green(nGreen / 256.0f);
	//result.blue(nBlue / 256.0f);

	return result;
}

bool 
Color::isValid() const
{
	bool bR = (m_red >= 0.0 && m_red <= 1.0f) ? true : false;
	bool bG = (m_green >= 0.0 && m_green <= 1.0f) ? true : false;
	bool bB = (m_blue >= 0.0 && m_blue <= 1.0f) ? true : false;
	bool bA = (m_alpha >= 0.0 && m_alpha <= 1.0f) ? true : false;

	return bR && bG && bB && bA;
}

//bool
//Color::operator==(const Color& rhs) const
//{
//	float tol(0.0001f);
//
//
//	//return
//	//	fabs(m_red - rhs.m_red) < tol &&
//	//	fabs(m_green - rhs.m_green) < tol &&
//	//	fabs(m_blue - rhs.m_blue) < tol &&
//	//	fabs(m_alpha - rhs.m_alpha) < tol;
//}

//bool
//Color::operator!=(const Color& rhs) const
//{
//	return !(*this == rhs);
//}

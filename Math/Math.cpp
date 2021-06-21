// Math.cpp: implementation of the Math class.
//
//////////////////////////////////////////////////////////////////////

#include "Math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

float Math::PI()
{
	return 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067f;
}

float Math::RAD2DEG(float radiant)
{
	return radiant * 180 / PI();
}

float Math::DEG2RAD(float degrees)
{
	return degrees * PI() / 180;
}

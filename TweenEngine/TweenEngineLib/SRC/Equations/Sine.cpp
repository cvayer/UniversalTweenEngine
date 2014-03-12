#include<stdafx.h>
#include"Sine.h"
#include <math.h>

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Sine
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

float SineIn::Compute(float _t, float _b, float _c, float _d)  const
{
	const float PI = 3.14159265f;
	return -_c * cos(_t/_d * (PI/2.0f)) + _c + _b;
}

float SineIn::Compute(float _t, float _d)  const
{
	const float PI = 3.14159265f;
	return - cos(_t/_d * (PI/2.0f)) + 1.0f;
}

//--------------------------------------------------------------------------------------
float SineOut::Compute(float _t, float _b, float _c, float _d)  const
{
	const float PI = 3.14159265f;
	return _c * sin(_t/_d * (PI/2.0f)) + _b;
}

//--------------------------------------------------------------------------------------
float SineOut::Compute(float _t, float _d)  const
{
	const float PI = 3.14159265f;
	return sin(_t/_d * (PI/2.0f));
}

//--------------------------------------------------------------------------------------
float SineInOut::Compute(float _t, float _b, float _c, float _d)  const
{
	const float PI = 3.14159265f;
	return -_c/2 * (cos(PI*_t/_d) - 1) + _b;
}

//--------------------------------------------------------------------------------------
float SineInOut::Compute(float _t, float _d)  const
{
	const float PI = 3.14159265f;
	return -0.5f * (cos(PI*_t/_d) - 1);
}

}// Namespace Easing
}// Namespace Tween
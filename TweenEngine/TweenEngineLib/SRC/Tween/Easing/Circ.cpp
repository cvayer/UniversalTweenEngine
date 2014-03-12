#include<stdafx.h>
#include"Circ.h"

#include <math.h>

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Circ
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

float CircIn::Compute(float _t, float _b, float _c, float _d)  const
{
	return -_c * ((float)sqrt(1 - (_t/=_d)*_t) - 1) + _b;
}

float CircIn::Compute(float _t, float _d)  const
{
	return -1.0f * ((float)sqrt(1 - (_t/=_d)*_t) - 1);
}

//--------------------------------------------------------------------------------------
float CircOut::Compute(float _t, float _b, float _c, float _d)  const
{
	return _c * (float)sqrt(1 - (_t=_t/_d-1)*_t) + _b;
}

//--------------------------------------------------------------------------------------
float CircOut::Compute(float _t, float _d)  const
{
	return (float)sqrt(1 - (_t=_t/_d-1)*_t);
}

//--------------------------------------------------------------------------------------
float CircInOut::Compute(float _t, float _b, float _c, float _d)  const
{
	if ((_t/=_d/2) < 1)
		return -_c/2 * ((float)sqrt(1 - _t*_t) - 1) + _b;

    return _c/2 * ((float)sqrt(1 - (_t-=2)*_t) + 1) + _b;
}

//--------------------------------------------------------------------------------------
float CircInOut::Compute(float _t, float _d)  const
{
	if ((_t/=_d/2) < 1)
		return -0.5f * ((float)sqrt(1 - _t*_t) - 1);

	return 0.5f * ((float)sqrt(1 - (_t-=2)*_t) + 1);
}

}// Namespace Easing
}// Namespace Tween
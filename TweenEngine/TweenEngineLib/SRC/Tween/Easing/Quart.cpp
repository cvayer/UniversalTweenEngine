#include<stdafx.h>
#include"Quart.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Quart
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

float QuartIn::Compute(float _t, float _b, float _c, float _d)  const
{
	return _c*(_t/=_d)*_t*_t*_t + _b;
}

float QuartIn::Compute(float _t, float _d)  const
{
	return (_t/=_d)*_t*_t*_t;
}

//--------------------------------------------------------------------------------------
float QuartOut::Compute(float _t, float _b, float _c, float _d)  const
{
	return -_c * ((_t = _t/_d-1.0f)*_t*_t*_t - 1.0f) + _b;
}

//--------------------------------------------------------------------------------------
float QuartOut::Compute(float _t, float _d)  const
{
	return -1.0f * ((_t = _t/_d-1.0f)*_t*_t*_t - 1.0f);
}

//--------------------------------------------------------------------------------------
float QuartInOut::Compute(float _t, float _b, float _c, float _d)  const
{
	if ((_t /= _d/2.0f) < 1.0f) 
	{
		return _c/2.0f*_t*_t*_t*_t + _b;
	}

	return -_c/2.0f * ((_t -= 2.0f)*_t*_t*_t - 2.0f) + _b;
}

//--------------------------------------------------------------------------------------
float QuartInOut::Compute(float _t, float _d)  const
{
	if ((_t /= _d/2.0f) < 1.0f) 
	{
		return 0.5f*_t*_t*_t*_t;
	}
	return -0.5f* ((_t -= 2.0f)*_t*_t*_t - 2.0f);
}

}// Namespace Easing
}// Namespace Tween
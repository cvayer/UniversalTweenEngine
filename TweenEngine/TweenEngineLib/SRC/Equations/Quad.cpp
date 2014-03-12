#include<stdafx.h>
#include"Quad.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Quad
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

float QuadIn::Compute(float _t, float _b, float _c, float _d)  const
{
	return _c*(_t/=_d)*_t + _b;
}

float QuadIn::Compute(float _t, float _d)  const
{
	return (_t/=_d)*_t;
}

//--------------------------------------------------------------------------------------
float QuadOut::Compute(float _t, float _b, float _c, float _d)  const
{
	return -_c*(_t/=_d)*(_t-2.0f) + _b;
}

//--------------------------------------------------------------------------------------
float QuadOut::Compute(float _t, float _d)  const
{
	return -1.0f*(_t/=_d)*(_t-2.0f);
}

//--------------------------------------------------------------------------------------
float QuadInOut::Compute(float _t, float _b, float _c, float _d)  const
{
	if ((_t /= _d/2.0f) < 1) 
		return _c/2.0f*_t*_t + _b;
	return -_c/2.0f * ((--_t)*(_t-2.0f) - 1.0f) + _b;
}

//--------------------------------------------------------------------------------------
float QuadInOut::Compute(float _t, float _d)  const
{
	if ((_t /= _d/2.0f) < 1.0f) 
		return 0.5f*_t*_t;
	return -0.5f * ((--_t)*(_t-2.0f) - 1.0f);
}

}// Namespace Easing
}// Namespace Tween
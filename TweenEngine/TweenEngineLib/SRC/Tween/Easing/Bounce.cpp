#include<stdafx.h>
#include"Bounce.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// BounceBase
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

float BounceIn::Compute(float _t, float _b, float _c, float _d)  const
{
	BounceOut bounce;
	return _c - bounce.Compute(_d-_t, 0.0f, _c, _d) + _b;
}

//--------------------------------------------------------------------------------------
float BounceIn::Compute(float _t, float _d)  const
{
	BounceOut bounce;
	return 1.0f - bounce.Compute(_d-_t, _d);
}

//--------------------------------------------------------------------------------------
float BounceOut::Compute(float _t, float _b, float _c, float _d)  const
{
	_t /= _d;
	if(_t < (1.0f / 2.75f))
		return _c*(7.5625f*_t*_t) + _b;
	else if( _t < (2.0f / 2.75f))
		return _c*(7.5625f*(_t-=(1.5f/2.75f))*_t + 0.75f) + _b;
    else if (_t < (2.5/2.75)) 
        return _c*(7.5625f*(_t-=(2.25f/2.75f))*_t + 0.9375f) + _b;
    else 
        return _c*(7.5625f*(_t-=(2.625f/2.75f))*_t + 0.984375f) + _b;
}

//--------------------------------------------------------------------------------------
float BounceOut::Compute(float _t, float _d)  const
{
	_t /= _d;
	if(_t < (1.0f / 2.75f))
		return (7.5625f*_t*_t);
	else if( _t < (2.0f / 2.75f))
		return (7.5625f*(_t-=(1.5f/2.75f))*_t + 0.75f);
	else if (_t < (2.5/2.75)) 
		return (7.5625f*(_t-=(2.25f/2.75f))*_t + 0.9375f);
	else 
		return (7.5625f*(_t-=(2.625f/2.75f))*_t + 0.984375f);
}

//--------------------------------------------------------------------------------------
float BounceInOut::Compute(float _t, float _b, float _c, float _d)  const
{
	if (_t < _d/2) 
	{
		BounceIn bounce;
		return bounce.Compute(_t*2, 0.0f, _c, _d) * 0.5f + _b;
	}
    else 
	{
		BounceOut bounce;
		return bounce.Compute(_t*2-_d, 0.0f, _c, _d) * 0.5f + _c*0.5f + _b;
	}
}

//--------------------------------------------------------------------------------------
float BounceInOut::Compute(float _t, float _d)  const
{
	if (_t < _d/2) 
	{
		BounceIn bounce;
		return bounce.Compute(_t*2,_d) * 0.5f;
	}
	else 
	{
		BounceOut bounce;
		return bounce.Compute(_t*2-_d, _d) * 0.5f + 0.5f ;
	}
}

}// Namespace Easing
}// Namespace Tween
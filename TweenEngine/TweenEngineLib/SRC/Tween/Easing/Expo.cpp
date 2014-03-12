#include<stdafx.h>
#include"Expo.h"
#include <math.h>

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Expo
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

float ExpoIn::Compute(float _t, float _b, float _c, float _d)  const
{
	return (_t == 0.0f) ? _b : _c * pow(2.0f, 10.0f * (_t/_d - 1.0f)) + _b;
}

float ExpoIn::Compute(float _t, float _d)  const
{
	return (_t == 0.0f) ? 0.0f :  pow(2.0f, 10.0f * (_t/_d - 1.0f));
}

//--------------------------------------------------------------------------------------
float ExpoOut::Compute(float _t, float _b, float _c, float _d)  const
{
	return (_t == _d) ? _b + _c : _c * (-pow(2.0f, -10.0f * _t/_d) + 1.0f) + _b;
}

//--------------------------------------------------------------------------------------
float ExpoOut::Compute(float _t, float _d)  const
{
	return (_t == _d) ? 1.0f : (-pow(2.0f, -10.0f * _t/_d) + 1.0f);
}


//--------------------------------------------------------------------------------------
float ExpoInOut::Compute(float _t, float _b, float _c, float _d)  const
{
	if (_t == 0) 
	{
		return _b;
	}

	if (_t == _d) 
	{
		return _b + _c;
	}

	if ((_t /= _d/2.0f) < 1.0f) 
	{
		return _c/2.0f * pow(2.0f, 10.0f * (_t - 1.0f)) + _b;
	}

	return _c/2.0f * (-pow(2.0f, -10.0f * --_t) + 2.0f) + _b;
}

//--------------------------------------------------------------------------------------
float ExpoInOut::Compute(float _t, float _d)  const
{
	if (_t == 0) 
	{
		return 0.0f;
	}

	if (_t == _d) 
	{
		return 1.0f;
	}

	if ((_t /= _d/2.0f) < 1.0f) 
	{
		return 0.5f * pow(2.0f, 10.0f * (_t - 1.0f));
	}

	return 0.5f * (-pow(2.0f, -10.0f * --_t) + 2.0f);
}

}// Namespace Easing
}// Namespace Tween
#include<stdafx.h>
#include"Easing.h"

namespace Tween
{
namespace Easing
{

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Back
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------

BackBase::BackBase()
	: m_s(1.70158f)
{

}

//--------------------------------------------------------------------------------------
BackBase& BackBase::SetS(float _s)
{
	m_s = _s;
	return (*this);
}

//--------------------------------------------------------------------------------------
float BackIn::Compute(float _t)  const
{
	float s = m_s;
	return _t*_t*((s+1.0f)*_t - s);
}

//--------------------------------------------------------------------------------------
float BackOut::Compute(float _t)  const
{
	float s = m_s;
	_t -= 1.0f;
	return (_t*_t*((s+1.0f)*_t + s) + 1.0f);
}

//--------------------------------------------------------------------------------------
float BackInOut::Compute(float _t)  const
{
	float s = m_s;
	_t*=2.0f;
	if (_t < 1.0f) 
	{
		return 0.5f*(_t*_t*(((s*=(1.525f))+1.0f)*_t - s));
	}
	return 0.5f*((_t-=2.0f)*_t*(((s*=(1.525f))+1.0f)*_t + s) + 2.0f);
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Bounce
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
float BounceIn::Compute(float _t)  const
{
	BounceOut bounceOut;
	return 1.0f - bounceOut.Compute(1.0f -_t);
}

//--------------------------------------------------------------------------------------
float BounceOut::Compute(float _t)  const
{
	if(_t < (1.0f / 2.75f))
	{
		return (7.5625f*_t*_t);
	}
	else if( _t < (2.0f / 2.75f))
	{
		return (7.5625f*(_t-=(1.5f/2.75f))*_t + 0.75f);
	}
	else if (_t < (2.5/2.75)) 
	{
		return (7.5625f*(_t-=(2.25f/2.75f))*_t + 0.9375f);
	}
	else 
	{
		return (7.5625f*(_t-=(2.625f/2.75f))*_t + 0.984375f);
	}
}

//--------------------------------------------------------------------------------------
float BounceInOut::Compute(float _t)  const
{
	if (_t < 0.5f) 
	{
		BounceIn bounce;
		return bounce.Compute(_t*2.0f) * 0.5f;
	}
	else 
	{
		BounceOut bounce;
		return bounce.Compute((_t*2.0f) - 1.0f) * 0.5f + 0.5f ;
	}
}

}// Namespace Easing
}// Namespace Tween

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

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Circ
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------

float CircIn::Compute(float _t)  const
{
    return -1.0f * ((float)sqrt(1.0f - _t*_t) - 1.0f);
}

//--------------------------------------------------------------------------------------
float CircOut::Compute(float _t)  const
{
    return (float)sqrt(1.0f - (_t-=1)*_t);
}

//--------------------------------------------------------------------------------------
float CircInOut::Compute(float _t)  const
{
    if ((_t*=2.0f) < 1.0f)
    {
        return -0.5f * ((float)sqrt(1 - _t*_t) - 1);
    }

    return 0.5f * ((float)sqrt(1 - (_t-=2)*_t) + 1);
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Cubic
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------

float CubicIn::Compute(float _t)  const
{
    return _t*_t*_t;
}

//--------------------------------------------------------------------------------------
float CubicOut::Compute(float _t)  const
{
    return ((_t-=1.0f)*_t*_t + 1.0f);
}

//--------------------------------------------------------------------------------------
float CubicInOut::Compute(float _t)  const
{
    if ((_t*=2.0f) < 1.0f) 
    {
        return 0.5f*_t*_t*_t;
    }
    return 0.5f*((_t-=2.0f)*_t*_t + 2.0f);
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Elastic
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------
ElasticBase::ElasticBase()
    : m_a(0.0f)
    , m_p(0.0f)
    , m_isASet(false)
    , m_isPSet(false)
{

}

//--------------------------------------------------------------------------------------
ElasticBase& ElasticBase::SetA(float _a)
{
    m_a = _a;
    m_isASet = (_a != 0.0f) ? true : false;
    return *this;
}

//--------------------------------------------------------------------------------------
ElasticBase& ElasticBase::SetP(float _p)
{
    m_p = _p;
    m_isPSet = (_p != 0.0f) ? true : false;
    return *this;
}

//--------------------------------------------------------------------------------------
float ElasticIn::Compute(float _t)  const
{
    const float PI = 3.14159265f;
    float a = m_a;
    float p = m_p;

    if (_t ==  0.0f) 
    {
        return 0.0f;  
    }

    if (_t == 1.0f) 
    {
        return 1.0f; 
    }

    if (!m_isPSet) 
    {
        p = 0.3f;
    }

    float s = 0.0f;
    if (!m_isASet || a < 1.0f) 
    { 
        a=1.0f; 
        s= p/4; 
    }
    else 
    {
        s = p/(2.0f*PI)*asin(1.0f/a);
    }

    return -(a*pow(2.0f,10.0f*(_t-=1.0f)) * sin( (_t-s)*(2.0f*PI)/p ));
}

//--------------------------------------------------------------------------------------
float ElasticOut::Compute(float _t)  const
{
    const float PI = 3.14159265f;
    float a = m_a;
    float p = m_p;

    if (_t ==  0.0f) 
    {
        return 0.0f; 
    }

    if (_t == 1.0f) 
    {
        return 1.0f; 
    }

    if (!m_isPSet) 
    {
        p = 0.3f;
    }

    float s = 0.0f;
    if (!m_isASet || a < 1.0f) 
    { 
        a=1.0f; 
        s= p/4; 
    }
    else 
    {
        s = p/(2.0f*PI)*asin(1.0f/a);
    }

    return (a*pow(2.0f,-10.0f*_t) * sin( (_t-s)*(2.0f*PI)/p ) + 1.0f);
}

//--------------------------------------------------------------------------------------
float ElasticInOut::Compute(float _t)  const
{
    const float PI = 3.14159265f;
    float a = m_a;
    float p = m_p;

    if (_t ==  0.0f) 
    {
        return 0.0f; 
    }

    if (_t == 1.0f) 
    {
        return 1.0f; 
    }

    if (!m_isPSet) 
    {
        p = 0.3f*1.5f;
    }

    float s = 0.0f;
    if (!m_isASet || a < 1.0f) 
    { 
        a= 1.0f; 
        s= p/4; 
    }
    else 
    {
        s = p/(2.0f*PI)*asin(1.0f/a);
    }

    if (_t < 1.0f) 
    {
        return -0.5f*(a*pow(2.0f,10.0f*(_t-=1.0f)) * sin( (_t-s)*(2.0f*PI)/p ));
    }

    return a*pow(2.0f,-10.0f*(_t-=1)) * sin( (_t-s)*(2.0f*PI)/p )*0.5f + 1.0f;
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Expo
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------
float ExpoIn::Compute(float _t)  const
{
    return (_t == 0.0f) ? 0.0f :  pow(2.0f, 10.0f * (_t - 1.0f));
}

//--------------------------------------------------------------------------------------
float ExpoOut::Compute(float _t)  const
{
    return (_t == 1.0f) ? 1.0f : (-pow(2.0f, -10.0f * _t) + 1.0f);
}

//--------------------------------------------------------------------------------------
float ExpoInOut::Compute(float _t)  const
{
    if (_t == 0) 
    {
        return 0.0f;
    }

    if (_t == 1.0f) 
    {
        return 1.0f;
    }

    if ((_t *= 2.0f) < 1.0f) 
    {
        return 0.5f * pow(2.0f, 10.0f * (_t - 1.0f));
    }

    return 0.5f * (-pow(2.0f, -10.0f * --_t) + 2.0f);
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Linear
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------
float Linear::Compute(float _t)  const
{
    return _t;
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Quad
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------
float QuadIn::Compute(float _t)  const
{
    return _t*_t;
}

//--------------------------------------------------------------------------------------
float QuadOut::Compute(float _t)  const
{
    return -1.0f*_t*(_t-2.0f);
}

//--------------------------------------------------------------------------------------
float QuadInOut::Compute(float _t)  const
{
    if ((_t *= 2.0f) < 1.0f) 
    {
        return 0.5f*_t*_t;
    }

    return -0.5f * ((--_t)*(_t-2.0f) - 1.0f);
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Quart
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------
float QuartIn::Compute(float _t)  const
{
    return _t*_t*_t*_t;
}

//--------------------------------------------------------------------------------------
float QuartOut::Compute(float _t)  const
{
    return -1.0f * ((_t -=1.0f)*_t*_t*_t - 1.0f);
}

//--------------------------------------------------------------------------------------
float QuartInOut::Compute(float _t)  const
{
    if ((_t *= 2.0f) < 1.0f) 
    {
        return 0.5f*_t*_t*_t*_t;
    }
    return -0.5f* ((_t -= 2.0f)*_t*_t*_t - 2.0f);
}

//--------------------------------------------------------------------------------------
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Quint
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------
float QuintIn::Compute(float _t)  const
{
    return _t*_t*_t*_t*_t;
}

//--------------------------------------------------------------------------------------
float QuintOut::Compute(float _t)  const
{
    return ((_t -= 1.0f)*_t*_t*_t*_t + 1.0f);
}

//--------------------------------------------------------------------------------------
float QuintInOut::Compute(float _t)  const
{
    if ((_t *= 2.0f) < 1.0f)
    {
        return 0.5f*_t*_t*_t*_t*_t;
    }
    return 0.5f*((_t -= 2.0f)*_t*_t*_t*_t + 2.0f);
}

//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
// Sine
//oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
//--------------------------------------------------------------------------------------
float SineIn::Compute(float _t)  const
{
    const float PI = 3.14159265f;
    return - cos(_t * (PI/2.0f)) + 1.0f;
}

//--------------------------------------------------------------------------------------
float SineOut::Compute(float _t)  const
{
    const float PI = 3.14159265f;
    return sin(_t * (PI/2.0f));
}

//--------------------------------------------------------------------------------------
float SineInOut::Compute(float _t)  const
{
    const float PI = 3.14159265f;
    return -0.5f * (cos(PI*_t) - 1);
}

}// Namespace Easing
}// Namespace Tween

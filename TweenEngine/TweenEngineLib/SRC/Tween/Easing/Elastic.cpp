#include<stdafx.h>
#include"Elastic.h"
#include <math.h>

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// ElasticBase
//--------------------------------------------------------------------------------------
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
float ElasticIn::Compute(float _t, float _b, float _c, float _d)  const
{
	const float PI = 3.14159265f;
	float a = m_a;
	float p = m_p;

	if (_t ==  0.0f) 
	{
		return _b;  
	}

	if ((_t/=_d) == 1.0f) 
	{
		return _b +_c; 
	}

	if (!m_isPSet) 
	{
		p = _d* 0.3f;
	}

	float s = 0.0f;
	if (!m_isASet || a < abs(_c)) 
	{ 
		a=_c; 
		s= p/4; 
	}
	else 
	{
		s = p/(2.0f*PI)*asin(_c/a);
	}

	return -(a*pow(2.0f,10.0f*(_t-=1.0f)) * sin( (_t*_d-s)*(2.0f*PI)/p )) + _b;
}

//--------------------------------------------------------------------------------------
float ElasticIn::Compute(float _t, float _d)  const
{
	const float PI = 3.14159265f;
	float a = m_a;
	float p = m_p;

	if (_t ==  0.0f) 
	{
		return 0.0f;  
	}

	if ((_t/=_d) == 1.0f) 
	{
		return 1.0f; 
	}

	if (!m_isPSet) 
	{
		p = _d* 0.3f;
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

	return -(a*pow(2.0f,10.0f*(_t-=1.0f)) * sin( (_t*_d-s)*(2.0f*PI)/p ));
}

//--------------------------------------------------------------------------------------
float ElasticOut::Compute(float _t, float _b, float _c, float _d)  const
{
	const float PI = 3.14159265f;
	float a = m_a;
	float p = m_p;

	if (_t ==  0.0f) 
	{
		return _b;  
	}

	if ((_t/=_d) == 1.0f) 
	{
		return _b +_c; 
	}

	if (!m_isPSet) 
	{
		p = _d* 0.3f;
	}

	float s = 0.0f;
	if (!m_isASet || a < abs(_c)) 
	{ 
		a=_c; 
		s= p/4; 
	}
	else 
	{
		s = p/(2.0f*PI)*asin(_c/a);
	}

	return (a*pow(2.0f,-10.0f*_t) * sin( (_t*_d-s)*(2.0f*PI)/p ) + _c + _b);
}

//--------------------------------------------------------------------------------------
float ElasticOut::Compute(float _t, float _d)  const
{
	const float PI = 3.14159265f;
	float a = m_a;
	float p = m_p;

	if (_t ==  0.0f) 
	{
		return 0.0f; 
	}

	if ((_t/=_d) == 1.0f) 
	{
		return 1.0f; 
	}

	if (!m_isPSet) 
	{
		p = _d* 0.3f;
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

	return (a*pow(2.0f,-10.0f*_t) * sin( (_t*_d-s)*(2.0f*PI)/p ) + 1.0f);
}

//--------------------------------------------------------------------------------------
float ElasticInOut::Compute(float _t, float _b, float _c, float _d)  const
{
	const float PI = 3.14159265f;
	float a = m_a;
	float p = m_p;
	if (_t ==  0.0f) 
	{
		return _b;  
	}

	if ((_t/=_d) == 1.0f) 
	{
		return _b +_c; 
	}

	if (!m_isPSet) 
	{
		p = _d* 0.3f*1.5f;
	}

	float s = 0.0f;
	if (!m_isASet || a < abs(_c)) 
	{ 
		a=_c; 
		s= p/4; 
	}
	else 
	{
		s = p/(2.0f*PI)*asin(_c/a);
	}

	if (_t < 1.0f) 
	{
		return -0.5f*(a*pow(2.0f,10.0f*(_t-=1.0f)) * sin( (_t*_d-s)*(2.0f*PI)/p )) + _b;
	}

	return a*pow(2.0f,-10.0f*(_t-=1)) * sin( (_t*_d-s)*(2.0f*PI)/p )*0.5f + _c + _b;
}

//--------------------------------------------------------------------------------------
float ElasticInOut::Compute(float _t, float _d)  const
{
	const float PI = 3.14159265f;
	float a = m_a;
	float p = m_p;

	if (_t ==  0.0f) 
	{
		return 0.0f; 
	}

	if ((_t/=_d) == 1.0f) 
	{
		return 1.0f; 
	}

	if (!m_isPSet) 
	{
		p = _d* 0.3f*1.5f;
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
		return -0.5f*(a*pow(2.0f,10.0f*(_t-=1.0f)) * sin( (_t*_d-s)*(2.0f*PI)/p ));
	}

	return a*pow(2.0f,-10.0f*(_t-=1)) * sin( (_t*_d-s)*(2.0f*PI)/p )*0.5f + 1.0f;
}

}// Namespace Easing
}// Namespace Tween
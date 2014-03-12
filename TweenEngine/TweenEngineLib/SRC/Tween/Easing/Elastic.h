#ifndef __TWEENELASTIC__H__
#define __TWEENELASTIC__H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Elastic
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

class ElasticBase : public Easing
{
public : 
	ElasticBase();

	virtual float Compute(float _t, float _b, float _c, float _d)  const = 0;
	virtual float Compute(float _t, float _d) const = 0;

	ElasticBase& A(float _a);
	ElasticBase& P(float _p);

protected : 
	float	m_fA;
	float	m_fP;
	bool	m_bSetA;
	bool	m_bSetP;
};

//--------------------------------------------------------------------------------------
// ElasticIn
//--------------------------------------------------------------------------------------
class ElasticIn : public ElasticBase
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// ElasticOut
//--------------------------------------------------------------------------------------
class ElasticOut : public ElasticBase
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// ElasticInOut
//--------------------------------------------------------------------------------------
class ElasticInOut : public ElasticBase
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
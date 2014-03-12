#ifndef __TWEENQUINT_H__
#define __TWEENQUINT_H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
// QuintIn
//--------------------------------------------------------------------------------------
class QuintIn : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// QuintOut
//--------------------------------------------------------------------------------------
class QuintOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// QuintInOut
//--------------------------------------------------------------------------------------
class QuintInOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
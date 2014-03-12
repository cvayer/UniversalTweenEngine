#ifndef __TWEENQUAD_H__
#define __TWEENQUAD_H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
// QuadIn
//--------------------------------------------------------------------------------------
class QuadIn : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// QuadOut
//--------------------------------------------------------------------------------------
class QuadOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// QuadInOut
//--------------------------------------------------------------------------------------
class QuadInOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
#ifndef __TWEENCIRC__H__
#define __TWEENCIRC__H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{

//--------------------------------------------------------------------------------------
// CircIn
//--------------------------------------------------------------------------------------
class CircIn : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// CircOut
//--------------------------------------------------------------------------------------
class CircOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// CircInOut
//--------------------------------------------------------------------------------------
class CircInOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
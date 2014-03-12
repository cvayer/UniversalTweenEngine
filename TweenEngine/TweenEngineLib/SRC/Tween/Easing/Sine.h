#ifndef __TWEENSINE_H__
#define __TWEENSINE_H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
// SineIn
//--------------------------------------------------------------------------------------
class SineIn : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// SineOut
//--------------------------------------------------------------------------------------
class SineOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// SineInOut
//--------------------------------------------------------------------------------------
class SineInOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
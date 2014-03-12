#ifndef __TWEENEXPO__H__
#define __TWEENEXPO__H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
// ExpoIn
//--------------------------------------------------------------------------------------
class ExpoIn : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// ExpoOut
//--------------------------------------------------------------------------------------
class ExpoOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// ExpoInOut
//--------------------------------------------------------------------------------------
class ExpoInOut : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
#ifndef __TWEENBACK__H__
#define __TWEENBACK__H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Back
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
class BackBase : public Easing
{
public : 
	BackBase();

	virtual float Compute(float _t, float _b, float _c, float _d)  const = 0;
	virtual float Compute(float _t, float _d) const = 0;
	BackBase& S(float _s);

protected : 
	float	_S;
};

//--------------------------------------------------------------------------------------
// BackIn
//--------------------------------------------------------------------------------------
class BackIn : public BackBase
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// BackOut
//--------------------------------------------------------------------------------------
class BackOut : public BackBase
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

//--------------------------------------------------------------------------------------
// BackInOut
//--------------------------------------------------------------------------------------
class BackInOut : public BackBase
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d)  const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
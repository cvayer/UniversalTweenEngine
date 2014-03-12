#ifndef __TWEENLINEAR__H__
#define __TWEENLINEAR__H__

#include "Easing.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Linear
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

class Linear : public Easing
{
public : 
	virtual float Compute(float _t, float _b, float _c, float _d) const;
	virtual float Compute(float _t, float _d) const;
};

}// Namespace Easing
}// Namespace Tween

#endif
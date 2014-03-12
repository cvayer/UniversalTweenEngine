#include <stdafx.h>
#include "Linear.h"

namespace Tween
{
namespace Easing
{
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// Linear
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

float Linear::Compute(float _t, float _b, float _c, float _d)  const
{
	return _c * _t/_d + _b;
}

float Linear::Compute(float _t, float _d)  const
{
	return _t/_d;
}

}// Namespace Easing
}// Namespace Tween
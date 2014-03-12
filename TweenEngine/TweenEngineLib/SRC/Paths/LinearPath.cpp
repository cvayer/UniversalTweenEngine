#include <stdafx.h>
#include "LinearPath.h"

namespace Tween
{
namespace Path
{
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// LinearPath
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------


	float LinearPath::Compute(float _t, const float* _Points, const int& _PointsCount)
	{
		int segment = GetSegment(_t, _PointsCount);
		return _Points[segment] + _t * (_Points[segment+1] - _Points[segment]);
	}

}// Namespace Path
}// Namespace Tween
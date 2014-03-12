#include <stdafx.h>
#include "Path.h"

namespace Tween
{
namespace Path
{
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// Path
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	int	Path::GetSegment(float & _t, const int& _PointsCount) const
	{
		int segment = (int) floor((_PointsCount-1) * _t);
		segment = (segment > 0) ? segment : 0;
		segment = (segment < _PointsCount-2) ? segment : _PointsCount-2;
		_t = _t * (_PointsCount-1) - segment;
		return segment;
	}

}// Namespace Path
}// Namespace Tween
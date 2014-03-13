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

    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // LinearPath
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------

    float LinearPath::Compute(float _t, const float* _Points, const int& _PointsCount) const
    {
        int segment = GetSegment(_t, _PointsCount);
        return _Points[segment] + _t * (_Points[segment+1] - _Points[segment]);
    }

    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------
    // CatmullRomPath
    //--------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------


    float CatmullRomPath::Compute(float _t, const float* _Points, const int& _PointsCount) const
    {
        int segment = GetSegment(_t, _PointsCount);

        if (segment == 0) {
            return GetSplineValue(_Points[0], _Points[0], _Points[1], _Points[2], _t);
        }

        if (segment == _PointsCount-2) {
            return GetSplineValue(_Points[_PointsCount-3], _Points[_PointsCount-2], _Points[_PointsCount-1], _Points[_PointsCount-1], _t);
        }

        return GetSplineValue(_Points[segment-1], _Points[segment], _Points[segment+1], _Points[segment+2], _t);
    }

    //--------------------------------------------------------------------------------------
    float  CatmullRomPath::GetSplineValue(float _a, float _b, float _c, float _d, float _t) const
    {
        float t1 = (_c - _a) * 0.5f;
        float t2 = (_d - _b) * 0.5f;

        float h1 = +2.0f * _t * _t * _t - 3.0f * _t * _t + 1.0f;
        float h2 = -2.0f * _t * _t * _t + 3.0f * _t * _t;
        float h3 = _t * _t * _t - 2.0f * _t * _t + _t;
        float h4 = _t * _t * _t - _t * _t;

        return _b * h1 + _c * h2 + t1 * h3 + t2 * h4;
    }

}// Namespace Path
}// Namespace Tween
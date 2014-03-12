#ifndef __TWEENCATMULLROMPATH__H__
#define __TWEENCATMULLROMPATH__H__

#include "Path.h"

namespace Tween
{
namespace Path
{
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// CatmullRomPath
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	class CatmullRomPath : public Path
	{
	public : 
		virtual float Compute(float _t, const float* _Points, const int& _PointsCount) const;

	private : 
		float GetSplineValue(float _a, float _b, float _c, float _d, float _t) const;
	};

}// Namespace Path
}// Namespace Tween


#endif
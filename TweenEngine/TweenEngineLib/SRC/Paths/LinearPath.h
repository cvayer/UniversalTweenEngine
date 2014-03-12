#ifndef __TWEENLINEARPATH__H__
#define __TWEENLINEARPATH__H__

#include "Path.h"

namespace Tween
{
namespace Path
{
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// LinearPath
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------

	class LinearPath : public Path
	{
	public : 
		virtual float Compute(float t, const float* _Points, const int& _PointsCount);
	};

}// Namespace Path
}// Namespace Tween


#endif
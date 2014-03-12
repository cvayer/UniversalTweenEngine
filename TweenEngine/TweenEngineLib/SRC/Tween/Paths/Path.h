#ifndef __TWEENPATHBASE__H__
#define __TWEENPATHBASE__H__

namespace Tween
{
namespace Path
{
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// Path
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	class Path
	{
	public : 
		/**
		 * Computes the next value of the interpolation, based on its waypoints and
		 * the current progress.
		 *
		 * @param _t The progress of the interpolation, between 0 and 1. May be out
		 * of these bounds if the easing equation involves some kind of rebounds.
		 * @param _Points The waypoints of the tween, from start to target values.
		 * @param _PointsCount The number of valid points in the array.
		 * @return The next value of the interpolation.
		 */
		virtual float Compute(float _t, const float* _Points, const int& _PointsCount) = 0;

	protected : 
		int		GetSegment(float & _t, const int& _PointsCount);

	};
}// Namespace Path
}// Namespace Tween


#endif
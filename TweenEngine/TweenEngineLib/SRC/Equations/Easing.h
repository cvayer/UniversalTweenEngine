#ifndef __TWEENEASINGBASE__H__
#define __TWEENEASINGBASE__H__

namespace Tween
{
namespace Easing
{
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	// Easing
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	/**
	@brief Base class for all easing interpolations.
	@details If you want to define your own interpolations, they should derivate from that class.
	*/
	class Easing
	{
	public : 
		/**@brief Computes the next value of the interpolation.
		*  @param _t Current time, in seconds.
		*  @param _b Initial value.
		*  @param _c Offset between target and initial value.
		*  @param _d Total duration, in seconds.
		*  @return the current interpolation value. */
		virtual float Compute(float _t, float _b, float _c, float _d) const = 0;

		/**@brief Computes the next value of the interpolation.
		*  @param _t Current time, in seconds.
		*  @param _d Total duration, in seconds.
		*  @details The equation from the Compute function with 4 parameters is rewritten assuming that _b == 0.0f and _c == 1.0f, to increase performances.
		*  @return the current interpolation value. */
		virtual float Compute(float _t, float _d) const = 0;
	};

}// Namespace Easing
}// Namespace Tween


#endif
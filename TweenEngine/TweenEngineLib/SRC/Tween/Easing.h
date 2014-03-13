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

	// TODO have only one compute function with one t parameter

	/**
	@brief Base class for all easing interpolations.
	@details If you want to define your own interpolations, they should derivate from that class.
	*/
	class Easing
	{
	public : 
		/**@brief Computes the next value of the interpolation. Used in the Tween class.
		*  @param _t Current time cursor (time/duration) [0, 1]
		*  @return the current interpolation value. */
		virtual float Compute(float _t) const = 0;
	};

#define DECLARE_EASING_CLASS(name, parentName)	\
	class name : public parentName				\
	{											\
	public :									\
	virtual float Compute(float _t) const;		\
	};											\


#define DECLARE_EASING_INOUT_CLASSES(name, parentName)	\
	DECLARE_EASING_CLASS(name##In,	parentName) 	\
	DECLARE_EASING_CLASS(name##Out,	parentName) 	\
	DECLARE_EASING_CLASS(name##InOut, parentName) 	\
	//--------------------------------------------------------------------------------------
	// Back
	//--------------------------------------------------------------------------------------
	class BackBase : public Easing
	{
	public : 
		BackBase();
		BackBase&	SetS(float _s);

	protected : 
		float	m_s;
	};

	DECLARE_EASING_INOUT_CLASSES(Back, BackBase)

	//--------------------------------------------------------------------------------------
	// Bounce
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Bounce, Easing)

	//--------------------------------------------------------------------------------------
	// Circ
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Circ, Easing)

	//--------------------------------------------------------------------------------------
	// Cubic
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Cubic, Easing)

	//--------------------------------------------------------------------------------------
	// Elastic
	//--------------------------------------------------------------------------------------
	class ElasticBase : public Easing
	{
	public : 
		ElasticBase();

		ElasticBase& SetA(float _a);
		ElasticBase& SetP(float _p);

	protected : 
		float	m_a;
		float	m_p;
		bool	m_isASet;
		bool	m_isPSet;
	};

	DECLARE_EASING_INOUT_CLASSES(Elastic, ElasticBase)

	//--------------------------------------------------------------------------------------
	// Expo
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Expo, Easing)

	//--------------------------------------------------------------------------------------
	// Linear
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_CLASS(Linear, Easing)

	//--------------------------------------------------------------------------------------
	// Quad
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Quad, Easing)

	//--------------------------------------------------------------------------------------
	// Quart
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Quart, Easing)

	//--------------------------------------------------------------------------------------
	// Quint
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Quint, Easing)

	//--------------------------------------------------------------------------------------
	// Sine
	//--------------------------------------------------------------------------------------
	DECLARE_EASING_INOUT_CLASSES(Sine, Easing)

	//--------------------------------------------------------------------------------------
	// Static
	//--------------------------------------------------------------------------------------
	static const BackIn			BACK_IN;
	static const BackOut		BACK_OUT;
	static const BackInOut		BACK_INOUT;

	static const BounceIn		BOUNCE_IN;
	static const BounceOut		BOUNCE_OUT;
	static const BounceInOut	BOUNCE_INOUT;

	static const CircIn			CIRC_IN;
	static const CircOut		CIRC_OUT;
	static const CircInOut		CIRC_INOUT;

	static const CubicIn		CUBIC_IN;
	static const CubicOut		CUBIC_OUT;
	static const CubicInOut		CUBIC_INOUT;

	static const ElasticIn		ELASTIC_IN;
	static const ElasticOut		ELASTIC_OUT;
	static const ElasticInOut	ELASTIC_INOUT;

	static const ExpoIn			EXPO_IN;
	static const ExpoOut		EXPO_OUT;
	static const ExpoInOut		EXPO_INOUT;

	static const Linear			LINEAR;

	static const QuadIn			QUAD_IN;
	static const QuadOut		QUAD_OUT;
	static const QuadInOut		QUAD_INOUT;

	static const QuartIn		QUART_IN;
	static const QuartOut		QUART_OUT;
	static const QuartInOut		QUART_INOUT;

	static const QuintIn		QUINT_IN;
	static const QuintOut		QUINT_OUT;
	static const QuintInOut		QUINT_INOUT;

	static const SineIn			SINE_IN;
	static const SineOut		SINE_OUT;
	static const SineInOut		SINE_INOUT;

}// Namespace Easing
}// Namespace Tween


#endif
#ifndef __TWEENEASING__H__
#define __TWEENEASING__H__

#include "Back.h"
#include "Bounce.h"
#include "Circ.h"
#include "Cubic.h"
#include "Elastic.h"
#include "Expo.h"
#include "Linear.h"
#include "Quad.h"
#include "Quart.h"
#include "Quint.h"
#include "Sine.h"

namespace Tween
{
//--------------------------------------------------------------------------------------
// Easing static equations
//--------------------------------------------------------------------------------------
namespace Easing
{
	static BackIn	    BACK_IN;
	static BackOut		BACK_OUT;
	static BackInOut	BACK_INOUT;

	static BounceIn		BOUNCE_IN;
	static BounceOut	BOUNCE_OUT;
	static BounceInOut	BOUNCE_INOUT;

	static CircIn		CIRC_IN;
	static CircOut		CIRC_OUT;
	static CircInOut	CIRC_INOUT;

	static CubicIn		CUBIC_IN;
	static CubicOut		CUBIC_OUT;
	static CubicInOut	CUBIC_INOUT;

	static ElasticIn	ELASTIC_IN;
	static ElasticOut	ELASTIC_OUT;
	static ElasticInOut	ELASTIC_INOUT;

	static ExpoIn		EXPO_IN;
	static ExpoOut		EXPO_OUT;
	static ExpoInOut	EXPO_INOUT;

	static Linear		LINEAR;

	static QuadIn		QUAD_IN;
	static QuadOut		QUAD_OUT;
	static QuadInOut	QUAD_INOUT;

	static QuartIn		QUART_IN;
	static QuartOut		QUART_OUT;
	static QuartInOut	QUART_INOUT;

	static QuintIn		QUINT_IN;
	static QuintOut		QUINT_OUT;
	static QuintInOut	QUINT_INOUT;

	static SineIn		SINE_IN;
	static SineOut		SINE_OUT;
	static SineInOut	SINE_INOUT;

}// Namespace Easing
}// Namespace Tween

#endif
#ifndef __TWEENABLEVALUE__H__
#define __TWEENABLEVALUE__H__

#include "ITweenable.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// TweenableInt
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

template <class T> class TweenableValue : public ITweenable
{
public : 
	TweenableValue()
	: m_val(0)
	{

	}

	TweenableValue(T _value)
	: m_val(_value)
	{
		
	}

	TweenableValue(const TweenableValue& _tweenableValue)
	{
		m_val = _tweenableValue.m_val;
	}

	virtual ~TweenableValue() {}


	TweenableValue &operator = (const TweenableValue &_tweenableValue)
	{
		m_val = _tweenableValue.m_val;
		return *this;
	}

	TweenableValue &operator = (const T & _value)
	{
		m_val = _value;
		return *this;
	}

	// Cast operator
	inline  operator    T () const
	{
		return m_val;
	}

protected : 
	virtual void		GetValues	(int _type, float* _returnValues, uint8 _arraySize) const
	{
		_returnValues[0] = (float)m_val;
	}

	virtual void	SetValues	(int _type, const float* _newValues,	uint8 _arraySize)
	{	
		m_val = (T)_newValues[0];
	}

	virtual int	GetValuesCount	(int _type) const
	{	
		return 1;
	}

protected : 
	T m_val;
};

typedef TweenableValue<double>	TweenableDouble;
typedef TweenableValue<float>	TweenableFloat;
typedef TweenableValue<int>		TweenableInt;

} // Namespace Tween

#endif
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
	: m_Val(0)
	{

	}

	TweenableValue(T _Value)
	: m_Val(_Value)
	{
		
	}

	TweenableValue(const TweenableValue& _TV)
	{
		m_Val = _TV.m_Val;
	}

	virtual ~TweenableValue() {}


	TweenableValue &operator = (const TweenableValue &_TV)
	{
		m_Val = _TV.m_Val;
		return *this;
	}

	TweenableValue &operator = (const T & _Value)
	{
		m_Val = _Value;
		return *this;
	}

	// Cast operator
	inline  operator    T () const
	{
		return m_Val;
	}

protected : 
	virtual void		_GetValues	(int _Type, float* _ReturnValues, uint8 _ucArraySize) const
	{
		_ReturnValues[0] = (float)m_Val;
	}

	virtual void	_SetValues	(int _Type, const float* _NewValues,	uint8 _ucArraySize)
	{	
		m_Val = (T)_NewValues[0];
	}

	virtual int	_GetValuesCount	(int _Type) const
	{	
		return 1;
	}

protected : 
	T m_Val;
};

typedef TweenableValue<float>	TweenableFloat;
typedef TweenableValue<int>		TweenableInt;

} // Namespace Tween

#endif
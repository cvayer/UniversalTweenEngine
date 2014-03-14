#ifndef __ITWEENABLE__H__
#define __ITWEENABLE__H__

#include "TweenTypeDefs.h"

namespace Tween
{
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// ITweenable
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
class ITweenable
{
protected :
	virtual void	GetValues			(int _type,				float* _returnValues,		uint8 _arraySize)	const	= 0;
	virtual void	SetValues			(int _type,		const	float* _newValues,			uint8 _arraySize)			= 0;
	virtual int		GetValuesCount		(int _type)																const	= 0;

public : 
	friend class BaseTween;
	friend class Tween;
	virtual ~ITweenable() {}
};

} // Namespace Tween

#endif

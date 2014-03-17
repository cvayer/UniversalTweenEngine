#ifndef __ITWEENABLE__H__
#define __ITWEENABLE__H__

#include "TweenDefines.h"

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
	virtual void	GetValues			(TweenType _type,				float* _returnValues,		uint8 _arraySize)	const	= 0;
	virtual void	SetValues			(TweenType _type,		const	float* _newValues,			uint8 _arraySize)			= 0;
	virtual int		GetValuesCount		(TweenType _type)																const	= 0;

public : 
	friend class BaseTween;
	friend class Tween;
	virtual ~ITweenable() {}
};

} // Namespace Tween

#endif

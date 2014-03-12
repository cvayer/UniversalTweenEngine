#ifndef __ITWEENABLE__H__
#define __ITWEENABLE__H__

#include "Tools/TweenTypeDefs.h"

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
	virtual void	_GetValues			(int _Type,				float* _ReturnValues,		uint8 _ucArraySize)	const	= 0;
	virtual void	_SetValues			(int _Type,		const	float* _NewValues,			uint8 _ucArraySize)			= 0;
	virtual int		_GetValuesCount		(int _Type)																const	= 0;

public : 
	friend class BaseTween;
	friend class Tween;
	virtual ~ITweenable() {}
};

} // Namespace Tween

#endif

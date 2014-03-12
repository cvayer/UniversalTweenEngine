#ifndef __TEMPLATEDTWEEN__H__
#define __TEMPLATEDTWEEN__H__

#include "BaseTween.h"

namespace Tween
{
class Manager;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
// TemplatedTween
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

template <class T> class TemplatedTween : public BaseTween
{
public : 

	TemplatedTween()
		: BaseTween()
	{

	}

	virtual	~TemplatedTween()
	{

	}


	T*			Build()
	{
		_Build();
		return (T*)this;
	}

	T*			Start()
	{
		_Start();
		return (T*)this;
	}

	T*	Start(Manager* _pManager)
	{
		_Start(_pManager);
		return (T*)this;
	}

	T*	Start(Manager* _pManager, uint8 _GroupID)
	{
		_Start(_pManager, _GroupID);
		return (T*)this;
	}

	T*	Delay(float _fDelay)
	{
		_Delay(_fDelay);
		return (T*)this;
	}


	T*	Repeat(int _Count, float _fDelay, bool _bYoyo = false)
	{
		_Repeat(_Count, _fDelay, _bYoyo);
		return (T*)this;
	}

	T*	SetListener(ITweenListener* _pListener, int _iID = -1, int _iTriggers = ITweenListener::eComplete)
	{
		_SetListener(_pListener, _iID, _iTriggers);
		return (T*)this;
	}
};

} // Namespace Tween

#endif
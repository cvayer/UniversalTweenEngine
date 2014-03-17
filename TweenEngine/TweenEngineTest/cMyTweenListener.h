#ifndef __CMYTWEENLISTENER__H__
#define __CMYTWEENLISTENER__H__

#include "Tween\ITweenListener.h"

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
// cMyTweenListener
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

class cMyTweenListener : public Tween::ITweenListener
{
public : 
	cMyTweenListener() {}
	virtual ~cMyTweenListener() {}

	virtual void OnEvent(Tween::ETweenEventType _eType, Tween::TweenListenerID _iTweenID)
	{
		printf("OnEvent ID = %d\n", _iTweenID);
        const char* name = Tween::ITweenListener::GetTweenEventTypeName(_eType);
        printf("Event : %s\n", name);
	}
};

#endif